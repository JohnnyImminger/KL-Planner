# KL-Planner

An algorithm for scheduling exams for an examination period according to some constraints:
+ the examination period are 9 days
+ each day starts at 8 am and ends at 6 pm


+ students may not write more than 2 exams per day
    + between 2 exams students have at least 4 hour break
+ between 2 exams professors have at least 30 minutes break
+ between 2 exams rooms are empty for at least 1 hour


+ the room capacity is divided by 4 to reduce the amount of students in one room

Constraints can be modified in <a href="#utility">Utility</a>

Input-Files
---

- _Raumliste.csv:_

        Art des Hörsaals (unwichtig) ; Adresse (adresseBau/adresseRaum) ; Kapazität
        
- _Anmeldungen.csv:_

        Matrikelnummer ; Studiengang (Kürzel); Prüfungsversion ; Prüfungsnummer ; Prüfungsform (Kürzel); Prüfungsform Text (ausführlich); Prüfungssemester (Jahr+Semester)

- _Pruefungen.csv:_

        Studiengang (Kürzel) ; Vertiefung (unwichtig) ; Prüfungsversion ; Prüfungsnummer ; Prüfungsname Text (ausführlich); PrüferID1 ; Prüfername1 (anonym) ; PrüferID2 ; Prüfername2 ; Prüfungsform (Kürzel) ; Prüfungssemester (Jahr+Semester) ; Angeboten (J/N)

Algorithmus:
---

    ReadInput data;                                     --> Speichert Listen von allen Datenobjekten
    vector<Room> days [Utility::examinationPeriod];     --> 9 Tage Prüfungszeit mit je 50+ Räumen in denen TimeSlots gebucht werden können
                                                        --> Bildet die Ressource die gebucht wird

<a id="utility" />Utility:
---

    float profBreak = 0.5;                              --> 30min break between exams
    float studentBreak = 4;                             --> 4h break between exams
    float roomBreak = 1;                                --> 1h break between exams
    int maxExamsPerDayStudent = 2;                      --> maximum of exams per day for students
    float startTimePerDay = 8;                          --> start time for each day in period
    float endTimePerDay = 18;                           --> end time for each day
    int examinationPeriod = 9;                          --> examination period in days
    float availableTimePerDay = endTimePerDay - startTimePerDay;            --> availabe time per day regardless of start time
    int roomDivider = 4;                                --> divider for reducing the capacity of rooms
    
    int timeSlotsPerHour = 12; //5min                                       --> amount of time slices per hour. internal time unit for easier handling
                                                                            --> smalles common divider of exam-durations and breaks
    int timeSlotsProfBreak = (int) profBreak * timeSlotsPerHour;            --> converting constraints to timeSlots
    int timeSlotsStudentBreak = (int) studentBreak * timeSlotsPerHour;      --> converting constraints to timeSlots
    int timeSlotsRoomBreak = (int) roomBreak * timeSlotsPerHour;            --> converting constraints to timeSlots
    int timeSlotsPerDay = (int) availableTimePerDay * timeSlotsPerHour;     --> converting constraints to timeSlots
        

DatenObjekte:
---

- ___Raum(Room):___

        string kindOfRoom;                                  --> aus csv  
        int building;                                       --> aus csv  
        int adrRoom;                                        --> aus csv  
        int capacity                                        --> aus csv / festgelegten Teiler [4]

        bool timeSlots[Utility::timeSlotsPerDay + Utility::timeSlotsRoomBreak] = {false};

            //TODO jeder timeSlot sollte eine capacity haben um 2 exams gleichzeitig stattfinden zu lassen
            --> Room ist eine Ressource die eine buchbare TimeSlots besitzt.
            --> Zur leichteren Handhabung wird mit einer immaginären Pause am Ende gerechnet
            --> Timeslot = 15min
            --> false = NICHT belegt

- ___Anmeldung(Registration):___

        int martrikelNummer;                                --> aus csv
        string course;                                      --> aus csv
        int version;                                        --> aus csv
        int id;                                             --> aus csv
        string kindOfExamShort;                             --> aus csv
        string KindOfExamLong;                              --> aus csv
        int examSemester;                                   --> aus csv

        --> Anmeldungen bilden die Verknüfung zwischen Klausuren und Studenten

- ___Prüfung(Exam):___

        string course;                                      --> aus csv
        int vertiefung;                                     --> aus csv
        int version;                                        --> aus csv
        int id;                                             --> aus csv
        string name;                                        --> aus csv
        int prof1Id;                                        --> aus csv
        string prof1Name;                                   --> aus csv
        int prof2Id;                                        --> aus csv
        string prof2Name;                                   --> aus csv
        float duration;                                     --> aus csv
        string kindOfExamShort;                             --> aus csv
        int examSemester;                                   --> aus csv
        bool offered;                                       --> aus csv

        int index;                                          --> Speicherindex im Data-Array
        vector<int> studentIndices;                         --> Indices der Studenten im Data-Array
        int memberCount;                                    --> Size von studentIndices

        int durationTimeSlots;                              --> Umgerechnete duration
        int day;                                            --> ERGEBNIS
        int startTimeSlot;                                  --> ERGEBNIS
        vector<int> roomIndices;                            --> ERGEBNIS

- ___Student:___

        int martrikelNummer;                                --> aus Registration
        string course;                                      --> aus Registration
        int examCount;                                      --> Anzahl der angemeldeten Klausuren
        vector<int> examIndices;                            --> Speicherindices der Exams im Data-Array
        int index;                                          --> Speicherindex im Data-Array

- ___Professor:___

        int identNr;                                        --> aus Exam
        string name;                                        --> aus Exam
        int examCount;                                      --> Size von examIndices
        vector<int> examIndices;                            --> Speicerindices der Exams im Data-Array

- ___ReadInput:___

        vector <Exam> exams;                                --> Speichert ALLE Exams --> Ziel aller Referenzen
        vector <Registration> registrations;                --> Speichert ALLE Registrations --> Ziel aller Referenzen
        vector <Room> rooms;                                --> Speichert ALLE Rooms --> Ziel aller Referenzen
        vector <Professor> profs;                           --> Speichert ALLE Profs --> Ziel aller Referenzen
        vector <Student> studentIndices;                    --> Speichert ALLE Students --> Ziel aller Referenzen

# KL-Planner

Input-Files
---

- _Raumliste.csv:_

        Art des Hoersaals (unwichtig) ; Adresse (adresseBau/adresseRaum) ; Kapazitaet
        
- _Anmeldungen.csv:_

        Matrikelnummer ; Studiengang (Kuerzel); Pruefungsversion ; Prüfungsnummer ; Prüfungsform (Kürzel); Prüfungsform Text (ausführlich); Prüfungssemester (Jahr+Semester)

- _Pruefungen.csv:_

        Studiengang (Kuerzel) ; Vertiefung (unwichtig) ; Prüfungsversion ; Prüfungsnummer ; Prüfungsname Text (ausführlich); PrüferID1 ; Prüfername1 (anonym) ; PrüferID2 ; Prüfername2 ; Prüfungsform (Kürzel) ; Prüfungssemester (Jahr+Semester) ; Angeboten (J/N)


DatenObjekte:
---

- ___Raum:___

        string kindOfRoom;                             --> aus csv  
        int building;                                 --> aus csv  
        int adrRoom;                                --> aus csv  
        int capacity                                --> aus csv / festgelegten Teiler [4]

        bool timeSlots[Utility::timeSlotsProTag + Utility::timeSlotsPauseRaum] = {false};

            //TODO jeder timeSlot sollte eine capacity haben um 2 exams gleichzeitig stattfinden zu lassen
            --> Room ist eine Ressource die eine buchbare TimeSlots besitzt.
            --> Zur leichteren Handhabung wird mit einer immaginären Pause am Ende gerechnet
            --> Timeslot = 15min
            --> false = NICHT belegt

- ___Anmeldung:___

        int martrikelNummer;                         --> aus csv
        string course;                     --> aus csv
        int version;                                --> aus csv
        int id;                                 --> aus csv
        string kindOfExamShort;                         --> aus csv
        string KindOfExamLong;                     --> aus csv
        int examSemester;                        --> aus csv

        --> Anmeldungen bilden die Verknüfung zwischen Klausuren und Studenten

- ___Klausur (einfacher zu schreiben als Pruefungen):___

        string course;                     --> aus csv
        int vertiefung;                             --> aus csv
        int version;                                --> aus csv
        int id;                                 --> aus csv
        string name;                                --> aus csv
        int prof1Id;                        --> aus csv
        string prof1Name;                        --> aus csv
        int prof2Id;                        --> aus csv
        string prof2Name;                        --> aus csv
        float duration;                                --> aus csv
        string kindOfExamShort;                         --> aus csv
        int examSemester;                        --> aus csv
        bool offered;                             --> aus csv

        int index;                              --> Speicher Index im Data-Array    --> Referenz
        vector<int> studentIndices;                      --> Studenten Index aus Data-Array  --> Referenz
        int memberCount;                          --> Size von studentIndices

        int durationTimeSlots;                         --> Umgerechnete duration
        int day;                                    --> ERGEBNIS
        int startTimeSlot;                      --> ERGEBNIS
        vector<int> roomIndices;                       --> ERGEBNIS

- ___Student:___

        int martrikelNummer;                         --> aus Registration
        string course;                     --> aus Registration
        int ExamCount;                           --> Size von exams
        vector<int> examIndices;             --> Exam Index aus Data-Array    --> Referenz
        int index;                              --> Speicher Index im Data-Array    --> Referenz

- ___Professor:___

        int identNr;                                --> aus Exam
        string name;                                --> aus Exam
        int ExamCount;                           --> Size von examIndices
        vector<int> examIndices;             --> Exam Index aus Data-Array    --> Referenz

- ___ReadInput:___

        vector <Exam> exams;                 --> Speichert ALLE Daten --> Ziel aller Referenzen
        vector <Registration> registrations;             --> Speichert ALLE Daten --> Ziel aller Referenzen
        vector <Room> rooms;                       --> Speichert ALLE Daten --> Ziel aller Referenzen
        vector <Professor> profs;             --> Speichert ALLE Daten --> Ziel aller Referenzen
        vector <Student> studentIndices;                 --> Speichert ALLE Daten --> Ziel aller Referenzen

- ___Algorithmus:___

        ReadInput data;                             --> Objekt von ReadInput mit allen Daten
        vector<Room> days [Utility::klausurTage];   --> 9 Tage mit je 50+ Räumen in denen 40 TimeSlots gebucht werden können    --> Bildet die Ressource die gebucht wird
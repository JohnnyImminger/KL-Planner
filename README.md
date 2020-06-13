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

        string raumArt;                             --> aus csv  
        int adrBau;                                 --> aus csv  
        int adrRaum;                                --> aus csv  
        int capacity                                --> aus csv / festgelegten Teiler [4]

        bool timeSlots[Utility::timeSlotsProTag + Utility::timeSlotsPauseRaum] = {false};

            //TODO jeder timeSlot sollte eine capacity haben um 2 klausuren gleichzeitig stattfinden zu lassen
            --> Raum ist eine Ressource die eine buchbare TimeSlots besitzt.
            --> Zur leichteren Handhabung wird mit einer immaginären Pause am Ende gerechnet
            --> Timeslot = 15min
            --> false = NICHT belegt

- ___Anmeldung:___

        int studMatrikelNr;                         --> aus csv
        string studStudiengang;                     --> aus csv
        int version;                                --> aus csv
        int nummer;                                 --> aus csv
        string klausurForm;                         --> aus csv
        string klausurFormText;                     --> aus csv
        int klausurSemester;                        --> aus csv

        --> Anmeldungen bilden die Verknüfung zwischen Klausuren und Studenten

- ___Klausur (einfacher zu schreiben als Pruefungen):___

        string studStudiengang;                     --> aus csv
        int vertiefung;                             --> aus csv
        int version;                                --> aus csv
        int nummer;                                 --> aus csv
        string name;                                --> aus csv
        int pruefer1IdentNr;                        --> aus csv
        string pruefer1Name;                        --> aus csv
        int pruefer2IdentNr;                        --> aus csv
        string pruefer2Name;                        --> aus csv
        float dauer;                                --> aus csv
        string klausurForm;                         --> aus csv
        int klausurSemester;                        --> aus csv
        bool angeboten;                             --> aus csv

        int dataIndex;                              --> Speicher Index im Data-Array    --> Referenz
        vector<int> studenten;                      --> Studenten Index aus Data-Array  --> Referenz
        int anzTeilnehmer;                          --> Size von studenten

        int dauerTimeSlots;                         --> Umgerechnete dauer
        int tag;                                    --> ERGEBNIS
        int startZeitTimeSlot;                      --> ERGEBNIS
        vector<int> raumRefs;                       --> ERGEBNIS

- ___Student:___

        int studMatrikelNr;                         --> aus Anmeldung
        string studStudiengang;                     --> aus Anmeldung
        int anzKlausuren;                           --> Size von klausuren
        vector<int> klausurDataIndizes;             --> Klausur Index aus Data-Array    --> Referenz
        int dataIndex;                              --> Speicher Index im Data-Array    --> Referenz

- ___Professor:___

        int identNr;                                --> aus Klausur
        string name;                                --> aus Klausur
        int anzKlausuren;                           --> Size von klausurDataIndizes
        vector<int> klausurDataIndizes;             --> Klausur Index aus Data-Array    --> Referenz

- ___ReadInput:___

        vector <Klausur> klausuren;                 --> Speichert ALLE Daten --> Ziel aller Referenzen
        vector <Anmeldung> anmeldungen;             --> Speichert ALLE Daten --> Ziel aller Referenzen
        vector <Raum> raeume;                       --> Speichert ALLE Daten --> Ziel aller Referenzen
        vector <Professor> professoren;             --> Speichert ALLE Daten --> Ziel aller Referenzen
        vector <Student> studenten;                 --> Speichert ALLE Daten --> Ziel aller Referenzen

- ___Algorithmus:___

        ReadInput data;                             --> Objekt von ReadInput mit allen Daten
        vector<Raum> tage [Utility::klausurTage];   --> 9 Tage mit je 50+ Räumen in denen 40 TimeSlots gebucht werden können    --> Bildet die Ressource die gebucht wird
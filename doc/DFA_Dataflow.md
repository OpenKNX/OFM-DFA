```
                                                                     ---\
   Serielle Konsole <-----------------+                                 | 
                                      |                                 |
                                      V                                 |
                          +----------------------+                      |
                          |   OpenKNX-Konsole    |                      |
------------------------  +----------------------+                      |
KO Diagnose           <-> | Kommandoverarbeitung |<--------------+      |
------------------------  +----------------------+               |      |
                                                                 |      |
                                                                 |      |
   Logik-Ausgang 1  -----+      / Eingabekanal   \               |      |
     :                   :      \ Logik-Ausgang  /               |      |
   Logik-Ausgang n  -----+                                       |      |
                         |                                       |      |
KO Nr 1 -------------+   |      / Eingabekanal   \               |      | Existenz
     :               :   |      \ Bestehendes KO /               |      | unabhängig 
KO Nr n -------------+   |                                       |      | von DFA-Kanal
                     |   |                                       |   ---/
                     V   V                                       |   ---\
---------------  +--   -   -----+----------------+               |      | je DFA-Kanal
KO Eingang1  --> |   .   .      |                |               |      |
                 |          A/B |                |               |      |
KO Eingang2  --> |   .   .      |                |               |      |
---------------  +--   -   -----+                |               |      |
KO Eingang3  --> |   .   .      |                |               |      |
                 |          C/D |                |               |      | 
KO Eingang4  --> |   .   .      |    Eingangs    |               |      |
---------------  +--   -   -----+       -        |               |      |
KO Eingang5  --> |   .   .      |  Verarbeitung  |               |      |
                 |          E/F |                |               |      | 
KO Eingang6  --> |   .   .      |                |               |      |
---------------  +--   -   -----+                |               |      |
KO Eingang7  --> |   .   .      |                |               |      |
                 |          G/H |                |               |      | 
KO Eingang8  --> |              |                |               |      |
---------------  +--------------+                |               |      |
KO Eingang T --> |   .   .   T  |                |               |      |
---------------  +--------------+----------------+               |      |
                                        |                        |      |
                          Eingabesymbol |      +----+            |      |
                                        V      V    |            |      |
------------------------  +-----+----------------+  | Timeout    |      |
KO Aktueller Zustand  <-- |     |                |  |            |      |
KO Zustand (kombi)    <-> |     |                |--+            |      |
KO Zustand setzen     --> |     |    Zustands    |               |      |
------------------------  +-----+       -        |               |      |
KO starten/pausieren  --> |     |  Verarbeitung  |               |      |
                          |     |                |<--------------+      |
KO läuft              <-- |     |                |                      |
------------------------  +-----+----------------+                      |
                                        |                               |
                                        | Zustandsupdate                |
                                        V                               |
------------------------  +-----+----------------+                      |
KO Ausgang1           <-- |  O1 |                |                      |
------------------------  +-----+                |                      |
KO Ausgang2           <-- |  O2 |    Ausgabe     |                      |
------------------------  +-----+       -        |                      |
KO Ausgang3           <-- |  O3 |  Verarbeitung  |                      |
------------------------  +-----+                |                      |
KO Ausgang4           <-- |  O4 |                |                      |
------------------------  +-----+----------------+                      |
                                                                     ---/
```

### Ausgang n: ...

#### Sendeintervall bei zyklischer Wiederholung 

Definiert den Zeitraum bis der Wert erneut auf den Bus gesendet wird, falls ein zyklisches Sendeverhalten eingestellt wird.

#### Definition Ausgangswert

##### Sendeverhalten (je Zustand)

| Einstellungswert                          | bei Wertänderung (erfordert Zustand-Wechsel) | bei Zustands-Änderung (ohne Wertänderung) | bei Zustandsaufruf (selber Zustand) | zyklisch senden | Beschreibung                                                                                                                                                                   |
|-------------------------------------------|:--------------------------------------------:|:-----------------------------------------:|:-----------------------------------:|:---------------:|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| - `                                       |                      -                       |                     -                     |                  -                  |        -        | kein Wert (letzter Wert bleibt unverändert)                                                                                                                                    |
| kein Senden, nur KO setzen                |             nur KO aktualisieren             |                     -                     |                  -                  |        -        | nur Wert aktualisieren  (Abruf per Read-Request möglich)                                                                                                                       |
| Wert-Änderung                             |                    senden                    |                     -                     |                  -                  |        -        | nur bei Wertänderung <br>(wird nur bei Änderung von Zustand auftreten)                                                                                                         |
| Wert-Änderung                  + zyklisch |                    senden                    |                     -                     |                  -                  |       ja        | nur bei Wertänderung <br>(wird nur bei Änderung von Zustand auftreten)                                                                                                         |
| Zustands-Änderung                         |                    senden                    |                  senden                   |                  -                  |        -        | bei Statusänderung (z.B. beim Starten, durch Symboleingabe, durch Statuseingabe, durch Timeout)                                                                                |
| Zustands-Änderung           + zyklisch    |                    senden                    |                  senden                   |                  -                  |       ja        | bei Statusänderung (z.B. beim Starten, durch Symboleingabe, durch Statuseingabe, durch Timeout)                                                                                |
| jeder Zustands-Aufruf                     |                    senden                    |                  senden                   |               senden                |        -        | bei Statusaufruf (bei Statusänderung, aber z.B. auch bei Symboleingabe mit identischem Folgezustand, Statuseingabe des aktuellen Zustands, (Timeout mit selbem Folgezustand)); |
| jeder Zustands-Aufruf        + zyklisch   |                    senden                    |                  senden                   |               senden                |       ja        | bei Statusaufruf (bei Statusänderung, aber z.B. auch bei Symboleingabe mit identischem Folgezustand, Statuseingabe des aktuellen Zustands, (Timeout mit selbem Folgezustand)); |

<div style="background-color:red;">TODO: Was soll beim Fortsetzen passieren?</div>

##### Ausgabewert (je Zustand)

Falls ein Sendeverhalten für diesen Zustand definiert wurde, kann hier der Wert entsprechend des ausgangsspezifischen Types festgelegt werden.




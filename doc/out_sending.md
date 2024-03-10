
0bABCD_EFGH

0b0000_0000 -> kein Wert (letzter Wert bleibt unverändert)
0b0000_0001 -> nur Wert aktualisieren  (Abruf per Read-Request möglich)
0b0000_0011 -> senden nur bei Wertänderung
0b0000_0111 -> senden bei Statusänderung
0b0000_1111 -> senden bei Statusaufruf
0b0001_1111 -> senden bei Timeout-Reset

0b1000_0000 -> zyklisch senden



| 7     | 6 | 5 | 4 | 3 | 2 | 1 | 0 | decimal | current | Label "Senden bei                   | Beschreibung                                                                                                                                                                                                          |
|-------|---|---|---|---|---|---|---|--------:|---------|-------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 0     | 0 | 0 | 0 | 0 | 0 | 0 | 0 |       0 |         | - `                                 | kein Wert (letzter Wert bleibt unverändert)                                                                                                                                                                           |
| 0     | 0 | 0 | 0 | 0 | 0 | 0 | 1 |       1 |         | 0) nur KO-Wert setzen               | nur Wert aktualisieren  (Abruf per Read-Request möglich)                                                                                                                                                              |
| **0** | 0 | 0 | 0 | 0 | 0 | 1 | 1 |       3 |         | 1) Ausgabewert-Änderung             | nur bei Wertänderung <br>(wird nur bei Änderung von Status auftreten)                                                                                                                                                 |
| **1** | 0 | 0 | 0 | 0 | 0 | 1 | 1 |     131 |         | 1+) Ausgabewert-Änderung + zyklisch | nur bei Wertänderung <br>(wird nur bei Änderung von Status auftreten)                                                                                                                                                 |
| **0** | 0 | 0 | 0 | 0 | 1 | 1 | 1 |       7 |         | 2) Status-Änderung                  | bei Statusänderung (z.B. beim Starten, durch Symboleingabe, durch Statuseingabe, durch Timeout)                                                                                                                       |
| **1** | 0 | 0 | 0 | 0 | 1 | 1 | 1 |     135 |         | 2+) Status-Änderung + zyklisch      | bei Statusänderung (z.B. beim Starten, durch Symboleingabe, durch Statuseingabe, durch Timeout)                                                                                                                       |
| **0** | 0 | 0 | 0 | 1 | 1 | 1 | 1 |      15 |         | 3) Status-Aufruf                    | bei Statusaufruf (bei Statusänderung, aber z.B. auch bei Symboleingabe mit identischem Folgezustand, Statuseingabe des aktuellen Zustands, (Timeout mit selbem Folgezustand));<br>Was soll beim Fortsetzen passieren? |
| **1** | 0 | 0 | 0 | 1 | 1 | 1 | 1 |     143 |         | 3+) Status-Aufruf + zyklisch        | bei Statusaufruf (bei Statusänderung, aber z.B. auch bei Symboleingabe mit identischem Folgezustand, Statuseingabe des aktuellen Zustands, (Timeout mit selbem Folgezustand));<br>Was soll beim Fortsetzen passieren? |
| ?     | ? | ? | ? | ? | ? | ? | ? |         |         |                                     | bei Timeout-Reset - nicht nötig, kann durch Setzen von Folgezustand erreicht werden                                                                                                                                   |
|       |   |   |   |   |   |   |   |         |         |                                     | beim Pausenaufruf - bei Pause eher seltsam                                                                                                                                                                            |
|       |   |   |   |   |   |   |   |         |         |                                     | bei Fortsetzung - Abgrenzung von Status-Aufruf; sollte global eingestellt werden                                                                                                                                      |
| 1     | * | * | * | * | * | * | * |         |         |                                     | zyklisch                                                                                                                                                                                                              |

# Masken
* OUT_MASK_UPDATE_ONLY       = 0x01: update ko 
* OUT_MASK_ON_CHANGE_VALUE   = 0x02: send after compare
* OUT_MASK_ON_CHANGE_STATE   = 0x04: force sending, when _state!=newstate in setState
* OUT_MASK_ON_SET_STATE      = 0x08: force sending, after setState
* OUT_MASK_SEND_CYCLIC       = 0x80: cyclic
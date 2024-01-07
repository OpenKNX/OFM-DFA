
0xABCD_EFGH

0x0000_0000 -> kein Wert (letzter Wert bleibt unverändert)
0x0000_0001 -> nur Wert aktualisieren  (Abruf per Read-Request möglich)
0x0000_0011 -> senden nur bei Wertänderung
0x0000_0111 -> senden bei Statusänderung
0x0000_1111 -> senden bei Statusaufruf
0x0001_1111 -> senden bei Timeout-Reset

0x1000_0000 -> zyklisch senden

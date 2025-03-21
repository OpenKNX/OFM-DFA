### Diagnose

#### Zugriff über Diagnose-Objekt

Über das zentrale OpenKNX-Diagnose-Objekt des Gerätes kann, auch ohne verbundene Gruppenadressen, auf den Zustand der Automaten zugegriffen werden.

Ist die Option **Steuerung erlauben** gewählt, so kann auch eine direkte Manipulation des Automaten vorgenommen werden.
Insbesondere ist es auf diesem Wege möglich ein Erreichen des Timeout-Endes zu simulieren, 
zum einfachen Testen von Automaten-Definitionen, ohne auf das Ende von längeren Timeouts warten zu müssen. 

#### Diagnose-Kommandos

Die Kommandos beginnen jeweils mit `dfaNN`, wobei `NN` die Kanalnummer des Automaten angibt.

* `dfaNN` - Liefert den aktuellen Zustand und die verbleibende Timeout-Zeit von Automat `NN`.
* (Steuerung) `dfaNN state=SS` - Setzt den Zustand von Automat `NN` auf `SS` (`00` bis `16`).
* (Steuerung) `dfaNN symbol=X` - Gibt das Symbol `X` (`A` bis `H`) in Automat `NN` ein.
* (Steuerung) `dfaNN timeout!` - Beendet die Timeout-Zeit von Automat `NN` sofort.

***Bemerkung***:
Der Befehlssatz kann sich in zukünftigen Modul-Versionen verändern.



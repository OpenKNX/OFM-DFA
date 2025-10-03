### Ausgang n: ...

#### Sendeintervall bei zyklischer Wiederholung 

Definiert den Zeitraum bis der Wert erneut auf den Bus gesendet wird, falls ein zyklisches Sendeverhalten eingestellt wird.

#### Definition Ausgangswert

##### Sendeverhalten (je Zustand)

> ***Tipp zur erleichterten ETS-Konfiguration:*** Über die Tasten `-`, `k`(kein Senden), `w`(Wert), `z`(Zustand), `j`(jedes) kann die jeweilige Sendestrategie schnell ausgewählt, bzw. zwischen den verschiedenen Ausprägungen gewechselt, werden. Mit `<Tab>` kann zum nächsten Zustand gewechselt werden. 

Definiert, ob in dem Zustand ein Wert für diesen Ausgang zugewiesen wird und wenn ja, ob und wann dieser auf den Bus gesendet wird.

> ***Hinweis:*** Sofern keine guten Gründe vorliegen sollte jedem benutzten Zustand ein Wert zugewiesen werden. 

* **-**:                           Der Wert des KOs wird nicht verändert (d.h. der bereits gesetzte Wert bleibt erhalten) und es wird nicht auf den Bus gesendet.
  *Achtung:* Dieses Verhalten verletzt das Prinzip eines eindeutig allein vom aktuellen Zustand abhängigen Ausgangswertes und sollte daher nur in begründeten Ausnahmefällen genutzt werden (z.B. für Übergangszustände mit kurzen Timeouts). 
* **kein Senden, nur KO setzen**:  Das KO wird auf den angegebenen Wert gesetzt, ohne diesen auf den Bus zu senden. Anschließend ist ein Abruf per Read-Request möglich.
* **Wert-Änderung**:               Sendet dann auf den Bus, wenn der zugeordnete Wert vom vorherigen Wert im KO abweicht. Eine Wert-Änderung kann *nur* bei Änderung des Zustandes auftreten. 
* **Zustands-Änderung**:           Sendet bei jedem Wechsel des Zustands, unabhängig von den Werten die den Zuständen zugeordnet sind. Eine Zustands-Änderung erfolgt beim Starten und beim Wechsel in einen abweichenden Folgezustand durch Symboleingabe, Timeout oder direktes Setzen des Zustands.
* **jeder Zustands-Aufruf**:       Sendet unabhängig von einer Veränderung des Zustands oder des Ausgangswertes. Ein Zustands-Aufruf erfolgt beim Starten, durch direktes Setzen des Zustands, oder bei definierten (nicht zwingend abweichenden) Folgezuständen durch Symboleingabe bzw. Timeout. *Hinweis:* Dieses Verhalten impliziert ein Senden bei Rekonstruktion. 

> ***Anmerkung***: Die Sendehäufigkeit, bzw. die Auslöser für ein Senden, nehmen entsprechend der Reihenfolge der Optionen zu.

Optionen für zusätzliches Senden:

* **"... + Rekonstruktion"**:
  Falls die Option ***Rekonstruktion bei erneutem Start*** aktiviert ist,
  dann (und nur dann) kann beim Neustart ein "zusätzliches" einmaliges Senden veranlasst werden
  um die Ausgangswerte auch nach einem Geräte-Neustart oder kompletten Bus-Neustart bereitzustellen.
  *Hinweis:* In Szenarien, in denen der Empfang des Ausgangswertes als Trigger eine Aktion auslöst oder neu startet, sollte das Senden in diesem Fall unterbleiben.
* **... + zyklisch**:                               Sendet ergänzend den aktuellen Wert wiederholt im für diesen Zustand definierten ***Sendeintervall bei zyklischer Wiederholung***.

##### Ausgabewert (je Zustand)

Falls ein Sendeverhalten für diesen Zustand definiert wurde, kann hier der Wert entsprechend des ausgangsspezifischen Types festgelegt werden.




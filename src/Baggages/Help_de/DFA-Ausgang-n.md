### Ausgang n: ...

#### Sendeintervall bei zyklischer Wiederholung 

Definiert den Zeitraum bis der Wert erneut auf den Bus gesendet wird, falls ein zyklisches Sendeverhalten eingestellt wird.

#### Definition Ausgangswert

##### Sendeverhalten (je Zustand)

Definiert, ob in dem Zustand ein Wert für diesen Ausgang zugewiesen wird und wenn ja, ob und wann dieser auf den Bus gesendet wird.

Wenn auf den Bus gesendet wird, 
kann optional eine regelmäßige Wiederholung des Sendevorgangs eingestellt werden ("+ zyklisch"). 
Die Wiederholung erfolgt dann unabhängig vom Zustand im für diesen Ausgang eingestellten ***Sendeintervall bei zyklischer Wiederholung***.

* **-**:                                         Dem Zustand wird kein Ausgangswert zugeordnet. Der Wert des KOs wird nicht verändert (d.h. der bereits gesetzte Wert bleibt erhalten) und es wird nicht auf den Bus gesendet.
* **kein Senden, nur KO setzen**:                Das KO wird auf den angegebenen Wert gesetzt, ohne diesen auf den Bus zu senden. Anschließend ist ein Abruf per Read-Request möglich.
* **Wert-Änderung (+ zyklisch)**:                Sendet dann auf den Bus, wenn der zugeordnete Wert vom vorherigen Wert im KO abweicht. Eine Wert-Änderung kann *nur* bei Änderung des Zustandes auftreten, dem vorherigen Zustand ein anderer Wert zugeordnet war.
* **Zustands-Änderung** (+ zyklisch):            Senden immer dann auf den Bus, wenn ein Wechsel des Zustands erfolgt, unabhängig von den Werten die den Zuständen zugeordnet sind. Eine Zustandsänderung erfolgt beim Starten und beim Wechsel in einen abweichenden Folgezustand durch Symboleingabe, Timeout, oder direktes Setzen des Zustands.
* **jeder Zustands-Aufruf** (+ zyklisch):        Senden erfolgt bei jedem Aufruf des Zustands, unabhängig von einer Veränderung des Zustands oder des Augsgansgwertes. Ein Zustandsaufruf erfolgt beim Starten, durch direktes Setzen des Zustands, oder bei definierten (nicht zwingend abweichenden) Folgezuständen durch Symboleingabe bzw. Timeout. 

> Die Sendehäufigkeit, bzw. die Auslöser für ein Senden, nehmen entsprechend der Reihenfolge der Optionen zu.


##### Ausgabewert (je Zustand)

Falls ein Sendeverhalten für diesen Zustand definiert wurde, kann hier der Wert entsprechend des ausgangsspezifischen Types festgelegt werden.




### Pausieren erlauben

Steuert, ob die Ausführung des Automaten unterbrochen werden kann.

Wird das Starten und Pausieren aktiviert, dann werden zwei KOs eingeblendet:

* Über das erste KO können Start/Stop-Befehle empfangen werden:
  Durch `Stop` wird eine laufende Ausführung unterbrochen, anschließend werden alle Ereignisse bis auf ein `Start` ignoriert.
  Ein Timeout des aktiven Zustands wird unterbrochen und beim erneuten Start fortgesetzt.
* Ein zweites KO liefert den aktuellen Ausführungsstatus zurück.

##### nein (Ausführung niemals unterbrechen)

Der Automat wird kontinuierlich ausgeführt. Eine Unterbrechung ist nicht möglich.
Nach dem Einschalten wird der Automat gestartet.

##### per KO, nach Einschalten starten

Nach dem Einschalten verhält sich der Automat wie mit *nein (Ausführung niemals unterbrechen)*.
Über das eingeblendete Start/Stop-KO kann die Ausführung unterbrochen und fortgesetzt werden.

##### per KO, warten auf Start-Telegramm

Nach dem Einschalten ist der Automat zunächst inaktiv.
D.h. es werden keine Ereignisse verarbeitet.

Durch erstmaligen Eingang eines `Start`-Telegramms auf dem eingeblendeten Start/Stop-KO wird der Automat in den Startzustand versetzt.
Der Timeout beginnt ab diesem Zeitpunkt.
Anschließend kann die Ausführung erneut unterbrochen und fortgesetzt werden.


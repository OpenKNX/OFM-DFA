### Ausführung

#### Verzögerung nach Neustart
Nach dem Neustart ist der der Automat zunächst inaktiv und wird erst nach Ablauf der Verzögerungszeit (zusätzlich zur Startverzögerung im Gerät) auf Ereignisse (wie z.B. Eingaben, Setzen des Zustand) reagieren und einen ggf. definierten Timeout starten.

> Mit dieser Einstellung kann z.B. verhindert werden, dass beim Neustart des Bus durch initial versendete Telegramme zustandswechsel verursacht werden.

> Durch Definition eines eigenen Startzustandes mit Timeout kann ein ähnliches, aber nicht identisches, Verhalten erzielt werden:
> Ein Setzen des Zustandes wäre dann jedoch sofort möglich, sowie auch eine individuelle Definition auf welche Eingabesymbole reagiert werden und welche nicht.
> In Kombination mit einer Rekonstruktion des letzten Zustands ist dann jedoch keine besondere Behandlung des Startverhaltens möglich. 

#### Starten und Pausieren
| Einstellungswert               | Erklärung                                                                                                                                                                                                                                                                                                                                                                                                                                       | Start/Stop-KOs | starten nach dem Einschalten? |
|--------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|----------------|------------------------------|
| immer aktiv                    | Der Automat wird kontinuierlich ausgeführt. Eine Unterbrechnung ist nicht möglich.                                                                                                                                                                                                                                                                                                                                                              | -              | ja                           |
| per KO, ...                    | Die Ausführung des Automaten kann unterbrochen werden. Dazu werden zwei KOs eingeblendet. Über das erste KO können Start/Stop-Befehle empfangen werden. Ein zweites KO liefert den aktuellen Ausführungsstatus zurück. <br> Durch `Stop` wird eine laufende Ausführung unterbrochen, anschließend werden alle Ereignisse bis auf ein `Start` ignoriert. Ein Timeout des aktiven Zustands wird unterbrochen und beim erneuten Start fortgesetzt. | sichtbar       |                              |
| ... nach Einschalten starten   | Nach dem Einschalten verhält sich der Automat wie mit *immer aktiv*.                                                                                                                                                                                                                                                                                                                                                                            | sichtbar       | ja                           |
| ... warten auf Start-Telegramm | Nach dem Einschalten ist der Automat zunächst inaktiv. D.h. es werden keine Ereignisse verarbeitet.<br />Durch erstmaligen Eingang eines `Start`-Telegramms wird der Automat in den Startzustand versetzt. Der Timeout beginnt ab diesem Zeitpunkt.                                                                                                                                                                                             | sichtbar       | nein                         |




### Tabelle Zustände und Übergänge

##### Bezeichnung (je Zustand)

Hier sollte zur Dokumentation eine individuelle kurze Beschreibung des jeweiligen Zustands hinterlegt werden.
Der Wert wird ausschließlich in der ETS verwendet und hat keinen Einfluss auf das Geräteverhalten.

##### Übergangsfunktion (Spalte "A" bis "H")

Für jede Kombination aus (Ausgangs)Zustand (Zeile 1 bis 16) und Eingabesymbol (Spalte A bis H) 
kann ein möglicher Folgezustand (`1` bis `16`), oder ein Zurücksetzen des Timeouts (`<<`) festgelegt werden.
Falls kein Folgezustand festgelegt wird (`-`), so wird die Eingabe ignoriert.

*Folgezustand identisch zum Ausgangszustand:* Mit dieser Definition kann erreicht werden,
dass ein definierter Timeout zurückgesetzt wird und der Zustand erneut auf den Bus gesendet wird.

##### Timeout / Einheit / Spalte "T"

Durch die Timeout-Funktion kann ein Zustandswechsel erfolgen, wenn innerhalb eines definierten Zeitraums *keine* Zustandsveränderung erfolgt ist.
D.h.: Es wurde *nicht*

* basierend auf der Übergangsfunktion in einen anderen Zustand gewechselt
* basierend auf der Übergangsfunktion derselbe Zustand erneut aufgerufen
* der Zustand von außen überschrieben

*Anwendungsbeispiele für die Timeout-Funktion:*

* Rückfall auf einen Standardzustand
* zeitverzögerte Aktionen
* Sicherstellen, dass innerhalb eines Zeitraums ein Ereignis nicht eintritt 

###### Spalte T: zeitbasierter Folgezustand

Mit Auswahl eines Zustandes wird die Timeout-Definition aktiviert und die Konfiguration für die Timeout-Dauer eingeblendet.
Ohne Auswahl erfolgt keine zeitabhängige Reaktion.

###### Timeout / Einheit

Definiert die Dauer des Timeouts.

Die Zeitmessung beginnt mit Eintritt in den Zustand.
Bei erneutem Aufruf desselben Zustands oder Zurücksetzen des Timeouts beginn die Zeitmessung nochmal in voller definierten Länge.
Ein Pausieren unterbricht die Zeitmessung, bis zum Beenden der Pause.
Falls Rekonstruktion aktiviert ist, so wird nach Neustart des Gerätes mit der restlichen Zeit fortgesetzt oder die Zeitmessung erneut gestartet.




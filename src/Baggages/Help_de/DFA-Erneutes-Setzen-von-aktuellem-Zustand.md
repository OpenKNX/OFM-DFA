### Erneutes Setzen von aktuellem Zustand

Definiert das Verhalten beim Versuch den bereits aktuellen Zustand nochmals direkt zu setzen.


* **ignorieren**: Der Zustandsaufruf wird verworfen.
* **Zustand neu starten**: 
  Der Automat verhält sich so, als ob der Zustand erstmalig aufgerufen würde.
  Falls ein Timeout definiert ist, beginnt dieser erneut mit der definierten Dauer.
  Das Senden der Ausgaben wird erneut geprüft.



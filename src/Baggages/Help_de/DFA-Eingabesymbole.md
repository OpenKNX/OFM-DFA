### Eingabesymbole

Das Eingabealphabet des Automaten umfasst 8 Symbole, die in der Oberfläche kurz mit den Großbuchstaben A bis H bezeichnet sind. 
Die Eingabesymbole werden durch externe Ereignisse erzeugt, 
die jeweils durch die Kombination von einem binären Eingabekanal und einem oder mehrerer Auslösewerte definiert werden.

***Achtung:***
Bei der Konfiguration sollte sichergestellt werden, dass die erzeugenden Ereignisse der einzelnen Eingabesymbole disjunkt sind.
Sollte dasselbe externe Ereignis mehrere Eingabesymbole "gleichzeitig" auslösen, so ist das resultierende Verhalten nicht spezifiziert.
Auch ein deterministisches Erzeugen von Eingabesymbolen kann in diesem Fall nicht garantiert werden, 
d.h. selbst ohne Neustart, ohne Neuprgrammierung oder einer Änderung der Firmware, 
könnte dasselbe externe Ereignis unterschiedliche Eingabesysmbole und damit auch Folgezustände erzeugen.
Wer trotz dieser Warnung vor den schlimmen Dingen die passieren können eine entsprechende Konfiguration durchführt ist selbst schuld.

***Achtung:***
Die Erzeugung der Eingabesymbole sollte unabhängig von den Ausgabekanälen, oder Status-Ausgängen erfolgen.
Das resultierende Verhalten ist ansonsten nur schwer vorhersehbar und beherrschbar.


> Sollen Eingabesymbole auf Basis von Werten erzeugt werden, die nicht direkt einem Eingangstelegramm vom Typ DPT1 entsprechen, so kann über Logikkanäle eine Konvertierung und/oder Vorverarbeitung erfolgen.

#### Gemeinsamer Eingang (Symbole 1/0)

In vielen Fällen soll sowohl auf ein Ereignis, als auch ein zugehöriges negiertes Ereignis reagiert werden.
Zwei benachbarte Eingabesymbole können in diesem Fall als Paar zur vereinheitlichten gemeinsamen Konfiguration zusammengefasst werden.
Dadurch teilen sich beide Eingabesymbole denselben Eingang, 
wobei beim Eingang des Wertes `1` im Eingabekanal das erste Symbol und beim Werte `0` immer das zweite Symbol erzeugt wird.
Dadurch wird sichergestellt, dass derselbe Eingabekanal verwendet 

Wird eine Paar-Option aktiviert, dann werden die beiden Eingabesymbole bei eintreffenden Ereignissen, 
in Abhängigkeit vom Wert, im selben Eingabekanel erzeugt. 

Ohne Auswahl der Option werden die Eingabesysmbole vollkommen unabhängig voneinander konfiguriert.






#### Konfigurationstabelle der Eingabesymbole

Abhängig von der Konfiguration wird je Zeile ein Eingabesymbol, oder ein Paar von Eingabesymbolen konfiguriert, bzw. Informationen zur Konfiguration dargestellt. 


##### Bezeichnung (je Eingabesymbol oder Eingabesymbol-Paar)

Hier sollte zur Dokumentation eine individuelle kurze Beschreibung des jeweiligen Eingabesymbol(-paares) hinterlegt werden. 
Der Wert wird ausschließlich in der ETS verwendet und hat keinen Einfluss auf das Geräteverhalten.

Der eingegebene Wert wird als KO-Bezeichnung und Spaltenüberschrift in Zustandsübergangstabelle dargestellt.
Bei Konfiguration als Eingabesymbol-Paar wird in der dortigen Spaltenüberschrift der Auslösewert `(=1)` bzw.  `(=0)` angehängt.
Bei unabhängigen Symbolen sollten ggf. eigene Ergänzungen zur Nachvollziehbarkeit ergänzt werden. 

> ***Zu beachten:*** Angesichts der geringen dort verfügbaren Spaltenbreite sollten eher kurze Wörter verwendet werden, nur so ist ein gut lesbarer Zeilenumbruch möglich.  


##### Eingabekanal & Kanalauswahl (je Eingabesymbol oder Eingabesymbol-Paar)

* **inaktiv**:        Das Eingabesymbol wird niemals erzeugt und in der Automatendefinition nicht berücksichtigt.
* **Eigenes KO**:     Zur direkten Reaktion auf Werte die auf dem Bus bereit stehen. Eingabesymbole werden durch eingehende Telegramme erzeugt. Ein KO mit DPT1 wird eingeblendet.
* **Logik-Ausgang**:  Nutzung von Werten die durch einen Logikkanal erzeugt und als Ergebnis ausgegeben werden. *Empfohlenen*, wenn Eingangswerte zunächst in 0/1 konvertiert oder vorgefiltert werden müssen, zur Nutzung von Zeitschaltuhrfunktionen, oder ggf. weiterer Funktionen des ***Logikmoduls***. Der Logik-Ausgang muss durch die Kanal-Nummer (1 bis Anzahl der Logikkanäle) des Logikmoduls festgelegt werden. ***Achtung:*** Fehlfunktionen möglich, bei Auswahl eines Ausgangs mit nicht kompatiblem DPT.
* **Bestehendes KO**: Verwendung von Werten, die bereits in anderen KOs abgebildet sind, unabhängig von einer Übertragung auf den Bus. Ausgänge von Logik-Kanälen sollten *nicht* über die KO-Nummer verknüpft werden. ***Achtung:*** Fehlfunktionen möglich, bei Auswahl eines KO mit nicht kompatiblem DPT. Bei späteren Updates mit Veränderung der KO-Nummerierung muss eine manuelle Anpassung der Nummerierung vorgenommen werden. Auswahl über die KO-Nummer.

##### Auslösewert (je Eingabesymbol)

* **bei 0**:             Nur bei Eintreffen eines Wertes 0 wird das Eingabesymbol erzeugt. 1 wird ignoriert.
* **bei 1**:             Nur bei Eintreffen eines Wertes 1 wird das Eingabesymbol erzeugt. 0 wird ignoriert.
* **jeder (0 oder 1)**:  Es erfolgt keine Unterscheidung zwischen den Werten. Bei jedem Eintreffen eines Wertes wird ein Eingabesymbol erzeugt.

##### Auslösewert (je Eingabesymbol-Paar)
Anzeige der erzeugten Eingabesymbole für Auslösewerte 1 und 0.




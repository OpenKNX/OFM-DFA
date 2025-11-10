### Bedingte Übergänge

Die bedingten Übergänge können auf der Seite *Zustände & Übergänge* als Alternative zu "regulären" Folgezuständen angegeben werden.
Statt eines direkten Zustandsaufrufs führt dies dann - bei Symboleingang - zur Auswertung des angegebenen bedingten Übergangs. 
Die Auswertung basiert auf einem Logik-Kanal, der neben den Werten *1* und *0* zunächst auch *undefiniert* sein kann.
Für jeden dieser drei Werte kann ein individuelles Verhalten definiert werden.

*Beispiele:* Zustandswechsel in Abhängigkeit 
von Uhrzeit, Sonnenstand,
Temperaturgrenzen,
oder beliebige andere Bedingungen die direkt oder indirekt durch das Logikmodul abgebildet werden können.

> ***Wichtig:***
  Bedingte Übergänge sollten nur nach sorgfältiger Abwägung benutzt werden.
  Die Erweiterung im Vergleich zum übersichtlichen DEA-Modell führt zu einer deutlichen Erhöhung der Komplexität
  und reduziert die Nachvollziehbarkeit, kann jedoch auch sehr nützlich sein, 
  wenn damit z.B. eine Vervielfältigung aller Zustände vermieden werden kann.  


#### Tabelle  

##### Bezeichnung/Kommentar

Hier sollte zur Dokumentation eine individuelle kurze Beschreibung des jeweiligen *bedingten Übergangs* hinterlegt werden.
Der Wert wird ausschließlich in der ETS verwendet und hat keinen Einfluss auf das Geräteverhalten.

#### Logik-Ausgang (0=inaktiv)

Der Folgezustand eines bedingten Übergangs wird immer in Abhängigkeit vom Ausgangswert eines Logik-Kanals ermittelt.
Dieser Logik-Ausgang wird durch die Kanal-Nummer (1 bis Anzahl der Logikkanäle) des Logikmoduls festgelegt.
Mit 0 wird der bedingte Übergang deaktiviert; eine Konfiguration der Folgezustände ist dann nicht möglich.

***Achtung:*** Fehlfunktionen möglich bei Auswahl eines Ausgangs der nicht aktiv ist und nicht als DPT1 konfiguriert ist.

##### 1 > / 0 > / undefiniert >

Definiert die dynamische Entscheidung für jeden der drei möglichen Logik-Ausgangswerte.

***Hinweis:*** Der Ausgangswert *undefiniert* kann nur nach dem Start auftreten, solange noch keine Auswertung des Logik-Kanals erfolgt ist. 

Einstellungswerte:

* **(leere Auswahl)**: Der Automat verbleibt im momentanen Zustand (kein abweichender Folgezustand) und die Auswertung des bedingten Übergangs wird beendet.
* **1** bis **16**: Der Automat wechselt in den angegebenen Folgezustand.
* **ELSE**: Die Entscheidung wird an den bedingten Übergang in der direkt nachfolgenden Zeile übergeben.
            Auf diesem Wege können mehrstufige Auswertungen in Abhängigkeit von verschiedenen Bedingungen/Logik-Kanälen erfolgen.
            Falls die nächste Zeile inaktiv ist, oder nicht existiert, so wird die Auswertung ohne Zustandsänderung abgebrochen.



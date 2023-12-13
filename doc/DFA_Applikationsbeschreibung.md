<!-- SPDX-License-Identifier: AGPL-3.0-only -->
<!-- Copyright (C) 2023 Cornelius Koepp -->
# Applikationsbeschreibung OFM-DFA


* Konzepte
  * [Zeitbasierter Folgezustand (Timeout)](#zeitbasierter-folgezustand--timeout--)
* ETS-Konfiguration:
  * [**DEAs**](#deas)
    * [**DEA n: ...**](#dea-n--)
      * [DEA-Definition](#dea-definition) 
      * [(Start)Verhalten und Steuerungsmöglichkeiten]()
      * [Eingabesymbole](#eingabesymbole)
      * [Ausgabe]()
      * [**Zustände & Übergänge**]()
        * [Zustände und Übergangsfunktion einschließlich zeitbasierter Folgezustände](#zustände-und-übergangsfunktion-einschließlich-zeitbasierter-folgezustände)
      * [**Ausgang n: ...**](...)
* [Kommunikationsobjekte](#kommunikationsobjekte) 

# Konzepte

## Zeitbasierter Folgezustand (Timeout):
Für jeden Zustand kann optional ein Folgezustand definiert werden, zu dem gewechselt wird, 
falls innerhalb einer definierten Zeitspanne kein Wechsel in einen anderen Zustand erfolgt;
d.h.:
* keine Eingabe erfolgt die zu einem Zustandswechsel fühlt
* kein direkter Aufruf eines Zustandes erfolgt

Die Zeitmessung wird zurückgesetzt, falls derselbe Zustand erneut aufgerufen wird; d.h.:
* für jedes Eingabesymbol kann durch Auswahl desselben Folgezustands ein Reset umgesetzt werden


# DEAs (ETS-Applikationsteil)
## DEA n: ...
### DEA-Definition 

#### Beschreibung des DEA
Hier sollte zur Dokumentation eine individuelle kurze Beschreibung des Automaten hinterlegt werden.
Der Wert wird ausschließlich in der ETS verwendet (als Teil der Kanalbezeichnung) und hat keinen Einfluss auf das Geräteverhalten.

#### Kanal verwenden?
| Einstellungswert | Erklärung                                                                                                                                                                                                                                                                                  | ausführen | KOs/Konfiguration |
|------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-----------|-------------------|
| inaktiv          | *(Standardwert)* Dieser Kanal wird *nicht* genutzt.                                                                                                                                                                                                                                        | -         | -                 |
| aktiv            | Zur Verwendung muss diese Einstellung gewählt werden                                                                                                                                                                                                                                       | ja        | sichtbar          |
| temporär inaktiv | Die Konfiguration dieses Kanals wird *ignoriert*, aber die Kommunikationsobjekte und alle Einstellungen bleiben sichtbar. Dadurch müssen GA-Verknüpfungen des zuvor 'aktiv' konfigurierten Kanals *nicht* entfernt werden und ein erneutes hinzufügen beim späteren reaktivieren entfällt. | -         | sichtbar          |

> Bei Einstellung *inaktiv* sind alle nachfolgenden Konfigurationen ausgeblendet.

> Bei Einstellung *temporär inaktiv* sind alle nachfolgenden Konfigurationen unwirksam.

### (Start)Verhalten und Steuerungsmöglichkeiten
<div style="background-color:red;">TODO</div>

#### Verzögerung nach Neustart
<div style="background-color:red;">TODO</div>

#### Starten und Pausieren
| Einstellungswert               | Erklärung                                                                                                                                                                                                                                                                                                                                                                                                                                       | Start/Stop-KOs | starten nach dem Einschalten? |
|--------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|----------------|------------------------------|
| immer aktiv                    | Der Automat wird kontinuierlich ausgeführt. Eine Unterbrechnung ist nicht möglich.                                                                                                                                                                                                                                                                                                                                                              | -              | ja                           |
| per KO, ...                    | Die Ausführung des Automaten kann unterbrochen werden. Dazu werden zwei KOs eingeblendet. Über das erste KO können Start/Stop-Befehle empfangen werden. Ein zweites KO liefert den aktuellen Ausführungsstatus zurück. <br> Durch `Stop` wird eine laufende Ausführung unterbrochen, anschließend werden alle Ereignisse bis auf ein `Start` ignoriert. Ein Timeout des aktiven Zustands wird unterbrochen und beim erneuten Start fortgesetzt. | sichtbar       |                              |
| ... nach Einschalten starten   | Nach dem Einschalten verhält sich der Automat wie mit *immer aktiv*.                                                                                                                                                                                                                                                                                                                                                                            | sichtbar       | ja                           |
| ... warten auf Start-Telegramm | Nach dem Einschalten ist der Automat zunächst inaktiv. D.h. es werden keine Ereignisse verarbeitet.<br />Durch erstmaligen Eingang eines `Start`-Telegramms wird der Automat in den Startzustand versetzt. Der Timeout beginnt ab diesem Zeitpunkt.                                                                                                                                                                                             | sichtbar       | nein                         |

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


> Sollen Eingabesymbole auf Basis von Werten erzeugt werden, die nicht dem DPT1 entsprechen, so kann über Logikkanäle eine Konvertierung erfolgen. 

#### Gemeinsamer Eingang (Symbole 1/0)

In vielen Fällen soll sowohl auf ein Ereignis, als auch ein zugehöriges negiertes Ereignis reagiert werden.
Zwei benachbarte Eingabesymbole können in diesem Fall als Paar zur vereinheitlichten gemeinsamen Konfiguration zusammengefasst werden.
Dadurch teilen sich beide Eingabesymbole denselben Eingang, 
wobei beim Eingang des Wertes `1` im Eingabekanal das erste Symbol und beim Werte `0` immer das zweite Symbol erzeugt wird.
Dadurch wird sichergestellt, dass derselbe Eingabekanal verwendet 


| Einstellungswert | Erklärung                                                                                                                                                                                                                                                       | bei 1 | bei 0 |
|------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---------------------|---------------------|
| A/B              | Wenn Option aktiviert, dann werden die Eingabesymbole A und B bei eintreffenden Ereignissen, in Abhängigkeit vom Wert, im selben Eingabekanel erzeugt. <br />Ohne Auswahl der Option werden die Eingabesysmbole vollkommen unabhängig voneinander konfiguriert. | A                   | B                   |
| C/D              | Analog A/B.                                                                                                                                                                                                                                                     | C                   | D                   |
| E/F              | Analog A/B.                                                                                                                                                                                                                                                     | E                   | F                   |
| G/H              | Analog A/B.                                                                                                                                                                                                                                                     | G                   | H                   |

> Beispiele für Ereignispaare:
> * Last (1 bei Überschreitung / 0 bei Unterschreitung)
> * Präsenz (1 bei Beginn und bestehender Präsenz / 0 bei Ende und Abwesenheit)
> * Nachtmodus (1 bei Nacht bzw. deren Beginn / 0 bei Tag bzw. dessen Beginn)




#### Konfigurationstabelle der Eingabesymbole
Abhängig von der Konfiguration wird je Zeile ein Eingabesymbol, oder ein Paar von Eingabesymbolen konfiguriert, bzw. Informationen zur Konfiguration dargestellt. 

##### Bezeichnung (je Eingabesymbol oder Eingabesymbol-Paar)
Hier sollte zur Dokumentation eine individuelle kurze Beschreibung des jeweiligen Eingabesymbol(-paares) hinterlegt werden. 
Der Wert wird ausschließlich in der ETS verwendet und hat keinen Einfluss auf das Geräteverhalten.

Der eingegebene Wert wird als KO-Bezeichnung und Spaltenüberschrift in Zustandsübergangstabelle dargestellt.
Bei Konfiguration als Eingabesymbol-Paar wird in der dortigen Spaltenüberschrift der Auslösewert `(=1)` bzw.  `(=0)` angehängt.
Bei unabhängigen Symbolen sollten ggf. eigene Ergänzungen zur Nachvollziehbarkeit ergänzt werden. 
***Zu beachten:*** Angesichts der geringen dort verfügbaren Spaltenbreite sollten eher kurze Wörter verwendet werden, nur so ist ein gut lesbarer Zeilenumbruch möglich.  

##### Eingabekanal (je Eingabesymbol oder Eingabesymbol-Paar)

##### KO (je Eingabesymbol oder Eingabesymbol-Paar)

##### Auslösewert (je Eingabesymbol oder Eingabesymbol-Paar)


<div style="background-color:red;">TODO</div>
Die Tabelle gibt Aufschluss darüber, welcher Eingabewert auf welchem Kommunikationsobjekt dem jeweiligen Eingabesymbol zugrunde liegt.  

#### Bezeichnung
Hier sollte zur Dokumentation eine individuelle kurze Beschreibung des jeweiligen Eingabesymbols hinterlegt werden.
Der Wert wird ausschließlich in der ETS verwendet und hat keinen Einfluss auf das Geräteverhalten.

*Zu Beachten:*
Der eingegebene Wert wird in der [Tabelle zur Definition der Übergangsfunktion](#zustände-und-übergangsfunktion-einschließlich-zeitbasierter-folgezustände) wiederholt. 
Dort steht nur wenig Platz zur Verfügung, wodurch die Darstellung eingeschränkt wird.   

Standardwert: "x_1", ..., "x_8"

#### Eingabekanal
Zeigt das genutzte Kommunikationsobjekt (KO) *Eingabe 1* bis *Eingabe 4*.
Das Eingabesymbol kann nur ausgelöst werden, wenn Telegramme auf diesem KO eingehen.  

#### Wert
Das Eingabesymbol wird erzeugt, wenn auf dem Eingabekanal ein Telegramme mit dem angegebenen Eingabewert *ein* oder *aus* eingeht. 


### Zustände und Übergangsfunktion einschließlich zeitbasierter Folgezustände

#### Startzustand
Definiert den Zustand den der Automat beim Einschalten (genauer: bei erstmaliger) einnimmt.

#### Direktes Setzen von Zustand erlauben?
| Einstellungswert | Erklärung                                                                                                                                                                                |
|------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| nein             | Der Zustand wechselt ausschließlich durch Eingabe eines Symbols, oder Timeout.                                                                                                           |
| per KO           | Es wird ein weiteres KO eingeblendet, über das der aktuelle Zustand unmittelbar überschrieben werden kann. Zustände außerhalb des Definitionsbereichs (Szene 1 bos 16) werden ignoriert. |


#### Bezeichnung (je Zustand)
Hier sollte zur Dokumentation eine individuelle kurze Beschreibung des jeweiligen Zustands hinterlegt werden.
Der Wert wird ausschließlich in der ETS verwendet und hat keinen Einfluss auf das Geräteverhalten.

#### Übergangsfunktion (Spalte "A" bis "H")
Für jede Kombination aus (Ausgangs)Zustand (Zeile 1 bis 16) und Eingabesymbol (Spalte A bis H) kann ein möglicher Folgezustand festgelegt werden.
Falls kein Folgezustand festgelegt wird, so wird die Eingabe ignoriert.

*Folgezustand identisch zum Ausgangszustand:* Mit dieser Definition kann erreicht werden, dass ein definierter Timeout zurückgesetzt wird, oder Zustand erneut auf den Bus gesendet wird.

#### Timeout / Einheit / Spalte "T"
Durch die Timeout-Funktion kann ein Zustandswechsel erfolgen, wenn innerhalb eines definierten Zeitraums *keine* Zustandsveränderung erfolgt ist.
D.h.: Es wurde *nicht*
* basierend auf der Übergangsfunktion in einen anderen Zustand gewechselt
* basierend auf der Übergangsfunktion derselbe Zustand erneut aufgerufen
* der Zustand von außen überschrieben

*Anwendungsbeispiele für die Timeout-Funktion:*
* Rückfall auf einen Standardzustand
* zeitverzögerte Aktionen
* Sicherstellen, dass innerhalb eines Zeitraums nicht eintritt 

##### Spalte T: zeitbasierter Folgezustand
Mit Auswahl eines Zustandes wird die Timeout-Definition aktiviert und die Konfiguration für die Timeout-Dauer eingeblendet.
Ohne Auswahl erfolgt keine zeitabhängige Reaktion.

##### Timeout / Einheit
Definiert die Dauer des Timeouts.
Die Zeitmessung beginnt mit Eintritt in den Zustand. 

*Zurücksetzen des Timeouts:* Bei erneutem Aufruf desselben Zustands beginnt die Zeitmessung erneut.


# Kommunikationsobjekte
## Je DEA
|  KO  |    DPT | Bezeichnung       | Erklärung                                                                                                                                                                                                           |
|:----:|-------:|-------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|  +0  | 17.001 | aktueller Zustand | Gibt den momentanen Zustand aus, als `0=Szene 1` bis `15=Szene 16`.<br />Wert wird bei jedem Setzen des Zustandes geschrieben, auch wenn der Zustand sich nicht ändern sollte.                                      |
|  +1  |  1.??? | Eingang 1         | Erzeugt die Eingabesymbole **A** (bei Wert `1`) und **B** (bei Wert `0`)                                                                                                                                            |
|  +2  |  1.??? | Eingang 2         | Erzeugt die Eingabesymbole **C** (bei Wert `1`) und **D** (bei Wert `0`)                                                                                                                                            |
|  +3  |  1.??? | Eingang 3         | Erzeugt die Eingabesymbole **E** (bei Wert `1`) und **F** (bei Wert `0`)                                                                                                                                            |
|  +4  |  1.??? | Eingang 4         | Erzeugt die Eingabesymbole **G** (bei Wert `1`) und **H** (bei Wert `0`)                                                                                                                                            |
| (+5) | 17.001 | Zustand setzen    | [(Optional)](#direktes-setzen-von-zustand-erlauben) Erlaubt ein direktes Festlegen/Überschreiben des Zustands von außen. Verarbeitet werden die Werte `0=Szene 1` bis `15=Szene 16`, alle anderen werden ignoriert. |
| (+6) |  1.010 | starten/pausieren | [(Optional)](#starten-und-pausieren) Erlaubt ein Starten/Fortsetzen (`1=start`) und Pausieren/Unterbrechen (`0=stop`) des Automaten.                                                                                |
| (+7) |  1.011 | läuft?            | [(Optional)](#starten-und-pausieren) Gibt an ob der Automat ausgeführt wird (`1=aktiv`), oder unterbrochen wurde (`0=inaktiv`).                                                                                     |


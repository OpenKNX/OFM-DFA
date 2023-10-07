<!-- SPDX-License-Identifier: AGPL-3.0-only -->
<!-- Copyright (C) 2023 Cornelius Koepp -->
# Applikationsbeschreibung OFM-DFA


* Konzepte
  * [Zeitbasierter Folgezustand (Timeout)](#zeitbasierter-folgezustand--timeout--)
* ETS-Konfiguration:
  * [**DEAs**](#deas)
    * [**DEA n: ...**](#dea-n--)
      * [DEA-Definition](#dea-definition) 
      * [Eingabesymbole](#eingabesymbole)
      * [Zustände und Übergangsfunktion einschließlich zeitbasierter Folgezustände](#zustände-und-übergangsfunktion-einschließlich-zeitbasierter-folgezustände)
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

#### Starten und Pausieren
| Einstellungswert               | Erklärung                                                                                                                                                                                                                                                                                                                                                                                                                                       | Start/Stop-KOs | starten nach dem Einschalten? |
|--------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|----------------|------------------------------|
| immer aktiv                    | Der Automat wird kontinuierlich ausgeführt. Eine Unterbrechnung ist nicht möglich.                                                                                                                                                                                                                                                                                                                                                              | -              | ja                           |
| per KO, ...                    | Die Ausführung des Automaten kann unterbrochen werden. Dazu werden zwei KOs eingeblendet. Über das erste KO können Start/Stop-Befehle empfangen werden. Ein zweites KO liefert den aktuellen Ausführungsstatus zurück. <br> Durch `Stop` wird eine laufende Ausführung unterbrochen, anschließend werden alle Ereignisse bis auf ein `Start` ignoriert. Ein Timeout des aktiven Zustands wird unterbrochen und beim erneuten Start fortgesetzt. | sichtbar       |                              |
| ... nach Einschalten starten   | Nach dem Einschalten verhält sich der Automat wie mit *immer aktiv*.                                                                                                                                                                                                                                                                                                                                                                            | sichtbar       | ja                           |
| ... warten auf Start-Telegramm | Nach dem Einschalten ist der Automat zunächst inaktiv. D.h. es werden keine Ereignisse verarbeitet.<br />Durch erstmaligen Eingang eines `Start`-Telegramms wird der Automat in den Startzustand versetzt. Der Timeout beginnt ab diesem Zeitpunkt.                                                                                                                                                                                             | sichtbar       | nein                         |

### Eingabesymbole
> In der aktuellen Version kann die Eingangskonfiguration (noch) nicht verändert werden, bzw. nur die Bezeichnung innerhalb der ETS. 

Das Eingabealphabet des Automaten umfasst 8 Symbole, die in der Oberfläche kurz mit den Großbuchstaben A bis H bezeichnet werden. 
Die Eingabesymbole werden durch externe Ereignisse erzeugt.
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


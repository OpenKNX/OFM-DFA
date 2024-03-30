<!-- SPDX-License-Identifier: AGPL-3.0-only -->
<!-- Copyright (C) 2023 Cornelius Koepp -->
# Applikationsbeschreibung OFM-DFA


# Inhaltsverzeichnis
* [Konzepte](#konzepte)
  * [Zeitbasierter Folgezustand (Timeout)](#zeitbasierter-folgezustand--timeout--)
* ETS-Konfiguration:
  [**Zustandsmodelle (DEAs)**](#ets-applikationsteilbr-zustandsmodelle-deas)
    * [**Info &amp; Dokumentation**](#info--dokumentation)
    * [**Basiseinstellungen**](#basiseinstellungen)
      * [Kanalauswahl / Verfügbare Kanäle](#basiseinstellungen)
    * [**DEA n: ...**](#dea-n--)
      * [DEA-Definition](#dea-definition) 
      * [Ausführung](#ausführung)
        * [Starten und Pausieren](#starten-und-pausieren)
      * [Eingabesymbole](#eingabesymbole)
      * [Ausgabe]()
      * [**Zustände & Übergänge**]()
        * [Startzustand](#startzustand)
        * Rekonstruktion
        * [Direktes Setzen von Zustand](#direktes-setzen-von-zustand-erlauben)
        * [Übergangsfunktion einschließlich zeitbasierter Folgezustände](#zustände-und-übergangsfunktion-einschließlich-zeitbasierter-folgezustände)
      * [**Ausgang n: ...**](...)
* [Kommunikationsobjekte](#kommunikationsobjekte) 
  * Je DEA

# Konzepte


## Deterministische Endliche Automaten
DFA steht für englisch Deterministic Finite Automaton, 
auf Deutsch entsprechend DEA (Deterministischer Endlicher Automat); 
dies bildet die Basis für die Zustandsmodelle.

Siehe
[Grundidee in Anlehnung an gängige formale Definitionen](../README.md#grundidee-in-anlehnung-an-gängige-formale-definitionen)
in der einführenden README.md.


## Zeitbasierter Folgezustand (Timeout):
Für jeden Zustand kann optional ein Folgezustand definiert werden, zu dem gewechselt wird, 
falls innerhalb einer definierten Zeitspanne kein Wechsel in einen anderen Zustand erfolgt;
d.h.:
* keine Eingabe erfolgt die zu einem Zustandswechsel fühlt
* kein direkter Aufruf eines Zustandes erfolgt

Die Zeitmessung wird zurückgesetzt, falls derselbe Zustand erneut aufgerufen wird; d.h.:
* für jedes Eingabesymbol kann durch Auswahl desselben Folgezustands ein Reset umgesetzt werden


# ETS-Applikationsteil:<br />Zustandsmodelle (DEAs)


## Info &amp; Dokumentation
### Modul-Version
Zeigt die Version (Major.Minor) des Moduls OFM-DFA an.

## Basiseinstellungen
### Kanalauswahl
#### Verfügbare Kanäle
Je nach Applikation kann eine große Anzahl von DFA-Kanälen vorhanden sein, 
wobei oft nur einige wenige benötigt werden. 
Mit diesem Parameter können nicht benötigt Kanäle in der ETS ausgeblendet werden, bzw. nur die notwendigen angezeigt.

***Bemerkung***:
Ausgeblendete Kanäle sind nicht inaktiv und zugehörige KOs sind ausgeblendet. 


## DEA n: ...
### DEA-Definition 

#### Beschreibung des DEA
Hier sollte zur Dokumentation eine individuelle und eindeutige kurze Beschreibung des Automaten hinterlegt werden.
Der Wert wird ausschließlich in der ETS verwendet (als Teil der Kanalbezeichnung) und hat keinen Einfluss auf das Geräteverhalten.

#### Kommentar
Hier kann eine ausführlichere - auch mehrzeilige - Dokumention des Automaten erfolgen.
Es wird empfohlen zentrale Annahmen die dem Entwurf des Automaten zu Grunde liegen hier festzuhalten.
Die Dokumentation hat keinen Einfluss auf das Geräteverhalten.

> Eine mehrzeilige Eingabe ist auf Grund von Beschränkungen der ETS nicht direkt möglich, kann jedoch durch Eingabe mit `\n` und Drücken des Buttons erzeugt werden. 
> Anschließend kann der Text mehrzeilig bearbeitet werden.
> 
> Beispiel:
> 
> Der Text
> ```
> Ein Text\nmit mehreren\nZeilen!
> ```
> wird umgewandelt in
> ```
> Ein Text
> mit mehreren
> Zeilen!
> ```

#### Kanal verwenden?
| Einstellungswert | Erklärung                                                                                                                                                                                                                                                                                  | ausführen | KOs/Konfiguration |
|------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-----------|-------------------|
| inaktiv          | *(Standardwert)* Dieser Kanal wird *nicht* genutzt.                                                                                                                                                                                                                                        | -         | -                 |
| aktiv            | Zur Verwendung muss diese Einstellung gewählt werden                                                                                                                                                                                                                                       | ja        | sichtbar          |
| temporär inaktiv | Die Konfiguration dieses Kanals wird *ignoriert*, aber die Kommunikationsobjekte und alle Einstellungen bleiben sichtbar. Dadurch müssen GA-Verknüpfungen des zuvor 'aktiv' konfigurierten Kanals *nicht* entfernt werden und ein erneutes hinzufügen beim späteren reaktivieren entfällt. | -         | sichtbar          |

> Bei Einstellung *inaktiv* sind alle nachfolgenden Konfigurationen ausgeblendet.

> Bei Einstellung *temporär inaktiv* sind alle nachfolgenden Konfigurationen unwirksam.

### Ausführung

#### Verzögerung nach Neustart
<div style="background-color:red;">TODO: u.A. Prüfen Startverzögerung Gerät</div>
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
> 
> Beispiele zum Einsatz von Logikkanälen:
> * Prüfung ob nicht-binären Eingangswerte in einem bestimmten Wertebereich liegen
> * Reaktion auf Über-/Unterschreitung von Schwellwerten, ggf. mit Hysterese und Mindesthaltedauer
> * <div style="background-color:red;">TODO</div> Unterdrückung von Wiederholungen, um nur auf Wertänderungen zu reagieren 

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
> ***Zu beachten:*** Angesichts der geringen dort verfügbaren Spaltenbreite sollten eher kurze Wörter verwendet werden, nur so ist ein gut lesbarer Zeilenumbruch möglich.  

##### Eingabekanal & Kanalauswahl (je Eingabesymbol oder Eingabesymbol-Paar)


| Eingabekanal   | Erklärung                                                                                                                                                                                                                                                                                                                                                                                                                                                    | Eingangs-KO | Kanalauswahl                                                                         |
|----------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------------|--------------------------------------------------------------------------------------|
| inaktiv        | Das Eingabesymbol wird niemals erzeugt.                                                                                                                                                                                                                                                                                                                                                                                                                      | -           | -                                                                                    |
| Eigenes KO     | Zur direkten Reaktion auf Werte die auf dem Bus bereit stehen. Eingabesymbole werden durch eingehende Telegramme erzeugt. Ein KO mit DPT1 wird eingeblendet.                                                                                                                                                                                                                                                                                                 | sichtbar    | Keine Konfiguration.<br />Nur Anzeige von genutztem Eingang 1 bis 8.                 |
| Logik-Ausgang  | Nutzung von Werten die durch einen Logikkanal erzeugt und als Ergebnis ausgegeben werden. *Empfohlenen*, wenn Eingangswerte zunächst in 0/1 konvertiert oder vorgefiltert werden müssen, zur Nutzung von Zeitschaltuhrfunktionen, oder ggf. weiterer Funktionen des [Logikmoduls](/OpenKNX/OAM-LogicModule/blob/main/doc/Applikationsbeschreibung-Logik.md). ***Achtung:*** Fehlfunktionen möglich, bei Auswahl eines Ausgangs mit nicht kompatiblem DPT. | -           | Der Logik-Ausgang wird durch die Kanal-Nummer (1 bis 96) des Logikmoduls festgelegt. |
| Bestehendes KO | Verwendung von Werten, die bereits in anderen KOs abgebildet sind, unabhängig von einer Übertragung auf den Bus. Ausgänge von Logik-Kanälten sollten *nicht* über die KO-Nummer verknüpft werden. ***Achtung:*** Fehlfunktionen möglich, bei Auswahl eines KO mit nicht kompatiblem DPT. Bei späteren Updates mit Veränderung der KO-Nummerierung muss eine manuelle Anpassung der Nummerierung vorgenommen werden.                                          | -           | Auswahl über die KO-Nummer (1 bis 2047)                                              |

##### Auslösewert (je Eingabesymbol)


| Auslösewert      | Eintreffen des Wertes 1 | Eintreffen des Wertes 0 | Kommentar                                           |
|------------------|-------------------------|-------------------------|-----------------------------------------------------|
| bei 0            | ignorieren              | Eingabesymbol erzeugen  |                                                     |
| bei 1            | Eingabesymbol erzeugen  | ignorieren              |                                                     |
| jeder (0 oder 1) | Eingabesymbol erzeugen  | Eingabesymbol erzeugen  | Es erfolgt keine Unterscheidung zwischen den Werten |

##### Auslösewert (je Eingabesymbol-Paar)
Anzeige der erzeugten Eingabesymbole für Auslösewerte 1 und 0.


### Ausgabe
Es können bis zu 4 Ausgabekanäle (O1, O2, O3, O4) konfiguriert werden, für die bei Aktivierung jeweils ein KO mit gewähltem Datentyp bereitgestellt wird.
Es stehen gängige DPTs (DPT1,2,5,5.001,6,7,8,9,12,13,14,16,232.600) zur Auswahl, sowie (ausschließlich) für O4 auch Text (DPT17.001).
Für jede Kombination aus Zustand und Ausgang kann ein Wert und ein Sendeverhalten definiert werden.

#### Bezeichnung/Kommentar (je Ausgabekanal)
Hier sollte zur Dokumentation eine individuelle kurze Beschreibung des jeweiligen Ausgabekanal hinterlegt werden.
Der Wert wird ausschließlich in der ETS verwendet (Als Beschriftung von Konfigurationsseiten und KOs) und hat keinen Einfluss auf das Geräteverhalten.

#### Datentyp (je Ausgabekanal)
| Wert                | O1,O2,O3          | O4 | Bemerkung                                                                                                                      |
|---------------------|-------------------|----|--------------------------------------------------------------------------------------------------------------------------------|
| inaktiv             | 1                 | 1  | Der Ausgabekanal wird ausgeblendet.                                                                                            |
| DPT1.x              | 1                 | 1  |                                                                                                                                |
| DPT2.x              | 1                 | 1  |                                                                                                                                |
| DPT5.x              | 1                 | 1  |                                                                                                                                |
| DPT5.001            | 1                 | 1  |                                                                                                                                |
| DPT6.x              | 1                 | 1  |                                                                                                                                |
| DPT7.x, 8.x, 9.x    | 1                 | 1  | 2Byte (vorzeichenlos, vorzeichenbehaftet, Fließkomma mit geringer Genauigkeit)                                                 |
| DPT12.x, 13.x, 14.x | 1                 | 1  | 4Byte (vorzeichenlos, vorzeichenbehaftet, Fließkomma)                                                                          |
| DPT16.x             | 1                 | 1  | Szenen; Bei Aktivierung des Senden wird als Standardwerde der gewählte Zustand eingestellt.                                    |
| DPT17.001           | nicht unterstützt | 1  | Die Ausgabe von 14-Byte-Texten ist angesichts des deutlich höheren Speicherbedarfs nur auf den letzten Ausgabekanal verfügbar. |
| DPT232.600          | 1                 | 1  |                                                                                                                                |


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
|  KO   |    DPT | Bezeichnung                | Erklärung                                                                                                                                                                                                           |
|:-----:|-------:|----------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|  +0   | 17.001 | Aktueller Zustand          | Gibt den momentanen Zustand aus, als `0=Szene 1` bis `31=Szene 32`.<br />Wert wird bei jedem Setzen des Zustandes geschrieben, auch wenn der Zustand sich nicht ändern sollte.                                      |
|   "   | 17.001 | Zustand (Ausgang/Eingang)  | [(Alternativ/Optional)](#direktes-setzen-von-zustand-erlauben) Kombinierte Funktion von *Aktueller Zustand* und *Zustand setzen*.                                                                                   |
| (+1)  | 17.001 | Zustand setzen             | [(Optional)](#direktes-setzen-von-zustand-erlauben) Erlaubt ein direktes Festlegen/Überschreiben des Zustands von außen. Verarbeitet werden die Werte `0=Szene 1` bis `31=Szene 32`, alle anderen werden ignoriert. |
| (+2)  |  1.??? | Eingang 1 - Symbol A       | [(Optional)](#eingabekanal--kanalauswahl-je-eingabesymbol-oder-eingabesymbol-paar) Erzeugt das Eingabesymbol **A** (bei Eingang von konfiguriertem Trigger-Wert)                                                    |
|   "   |  1.??? | Eingang 1 - Symbol A/B     | [(Optional)](#eingabekanal--kanalauswahl-je-eingabesymbol-oder-eingabesymbol-paar) Erzeugt die Eingabesymbole **A** (bei Wert `1`) und **B** (bei Wert `0`)                                                         |
| (+3)  |  1.??? | Eingang 2 - Symbol B       | [(Optional)](#eingabekanal--kanalauswahl-je-eingabesymbol-oder-eingabesymbol-paar) Erzeugt das Eingabesymbol **B** (bei Eingang von konfiguriertem Trigger-Wert)                                                    |
| (+4)  |  1.??? | Eingang 3 - Symbol C       | Analog *Eingang 1 - Symbol A*                                                                                                                                                                                       |
|   "   |  1.??? | Eingang 3 - Symbol C/D     | Analog *Eingang 1 - Symbol A/B*                                                                                                                                                                                     |
| (+5)  |  1.??? | Eingang 4 - Symbol D       | Analog *Eingang 2 - Symbol B*                                                                                                                                                                                       |
| (+6)  |  1.??? | Eingang 5 - Symbol E       | Analog *Eingang 1 - Symbol A*                                                                                                                                                                                       |
|   "   |  1.??? | Eingang 5 - Symbol E/F     | Analog *Eingang 1 - Symbol A/B*                                                                                                                                                                                     |
| (+7)  |  1.??? | Eingang 6 - Symbol F       | Analog *Eingang 2 - Symbol B*                                                                                                                                                                                       |
| (+8)  |  1.??? | Eingang 7 - Symbol G       | Analog *Eingang 1 - Symbol A*                                                                                                                                                                                       |
|   "   |  1.??? | Eingang 7 - Symbol G/H     | Analog *Eingang 1 - Symbol A/B*                                                                                                                                                                                     |
| (+9)  |  1.??? | Eingang 8 - Symbol H       | Analog *Eingang 2 - Symbol B*                                                                                                                                                                                       |
| (+10) |  1.010 | starten/pausieren          | [(Optional)](#starten-und-pausieren) Erlaubt ein Starten/Fortsetzen (`1=start`) und Pausieren/Unterbrechen (`0=stop`) des Automaten.                                                                                |
| (+11) |  1.011 | läuft?                     | [(Optional)](#starten-und-pausieren) Gibt an ob der Automat ausgeführt wird (`1=aktiv`), oder unterbrochen wurde (`0=inaktiv`).                                                                                     |
| (+12) |      * | Ausgang 1 - Zustandswert 1 | [(Optional)](#) Gibt einen für **O1** definierten zustandsabhängigen Wert aus. Sendeverhalten abhängig von Konfiguration.                                                                                           |
| (+13) |      * | Ausgang 2 - Zustandswert 2 | Analog *Ausgang 1 - Zustandswert 1*                                                                                                                                                                                 |
| (+14) |      * | Ausgang 3 - Zustandswert 3 | Analog *Ausgang 1 - Zustandswert 1*                                                                                                                                                                                 |
| (+15) |      * | Ausgang 4 - Zustandswert 4 | Analog *Ausgang 1 - Zustandswert 1* mit zusätzlichem Ausgangstyp DPT16.001 Text.                                                                                                                                    |


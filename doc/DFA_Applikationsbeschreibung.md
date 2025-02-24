<!-- SPDX-License-Identifier: AGPL-3.0-only -->
<!-- Copyright (C) 2023 Cornelius Koepp -->
# Applikationsbeschreibung OFM-DFA


# Inhaltsverzeichnis
* [Konzepte](#konzepte)
  * [Zeitbasierter Folgezustand (Timeout)](#zeitbasierter-folgezustand--timeout--)
  * [Rekonstruktion nach Neustart](#rekonstruktion-nach-neustart)
* ETS-Konfiguration:
  [**Zustandsautomaten**](#ets-applikationsteilbr-zustandsautomaten)
    * [**Allgemein**](#allgemein)
      * [Diagnose](#diagnose)
    * [**DEA n: ...**](#dea-n--)
      * [DEA-Definition](#dea-definition) 
      * [Start und Ausführung](#ausführung)
        * [Pausieren erlauben](#pausieren-erlauben)
        * [Rekonstruktion bei erneutem Start](#rekonstruktion-bei-erneutem-start)
      * [Eingabesymbole](#eingabesymbole)
      * [Ausgabe]()
      * [**Zustände & Übergänge**]()
        * [Startzustand](#startzustand)
        * [Direktes Setzen von Zustand](#direktes-setzen-von-zustand-erlauben)
        * [Übergangsfunktion einschließlich zeitbasierter Folgezustände](#zustände-und-übergangsfunktion-einschließlich-zeitbasierter-folgezustände)
      * [**Ausgang n: ...**](#ausgang-n-)
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


## Rekonstruktion nach Neustart

<!-- 2d272170-a9e3-11ef-bd59-e7574d3ece74 BEGIN duplicate content -->

Bei Unterbrechung des Gerätebetriebs (Programmieren, Reset, Trennen/Verbinden vom Bus, Ausfall der Bus-Stromversorgung) endet auch die Verarbeitung der definierten Automaten.
Mit der optionalen Rekonstruktionsfunktion wird *versucht* die Verarbeitung nach dem Neustart fortzusetzen,
mit dem Ziel ein Verhalten zu erreichen als hätte keine Unterbrechung stattgefunden.  
D.h.:

* beim Starten kann alternativ zum regulären Startzustand der zuletzt gespeicherte Zustand aufgerufen werden
* ein ggf. vorhandener Timeout kann um die bereits abgelaufene Zeit verkürzt werden <!-- (geplant) alternativ soll der Rest-Timeout basierend auf dem zuvor berechneten absoluten Endzeitpunkt neu berechnet werden -->
* falls pausieren erlaubt ist, wird der gespeicherte Unterbrechnungs-Status genutzt 

Die Rekonstruktion erfordert das erfolgreiche Speichern des momentanen Zustands und des Rest-Timeouts unmittelbar bei Beendigung der Verarbeitung. 
Dies kann allerdings nicht immer gewährleistet werden. 
Während ein Neustart durch Programmiervorgang gut erkannt werden kann, 
erfordert die Erkennung einer unterbrochenen Stromversorgung eine entsprechende Hardwareausstattung.
Ein Neustart per Reset-Taste kann nicht erkannt werden. 

<!-- 2d272170-a9e3-11ef-bd59-e7574d3ece74 END duplicate content -->



# ETS-Applikationsteil:<br />Zustandsautomaten


## Allgemein

### Modul-Version

Zeigt die Version (Major.Minor) des Moduls OFM-DFA an.


<!-- DOC -->
### Kanalauswahl

#### Verfügbare Kanäle

Je nach Applikation kann eine größere Anzahl von Kanälen vorhanden sein, 
wobei oft nur einige wenige benötigt werden. 
Mit diesem Parameter können nicht benötigt Kanäle in der ETS ausgeblendet werden, bzw. nur die notwendigen angezeigt.

***Bemerkung***:
Ausgeblendete Kanäle sind inaktiv und zugehörige KOs sind ausgeblendet. 


<!-- DOC -->
### Diagnose

#### Zugriff über Diagnose-Objekt

Über das zentrale OpenKNX-Diagnose-Objekt des Gerätes kann, auch ohne verbundene Gruppenadressen, auf den Zustand der Automaten zugegriffen werden.

Ist die Option **Steuerung erlauben** gewählt, so kann auch eine direkte Manipulation des Automaten vorgenommen werden.
Insbesondere ist es auf diesem Wege möglich ein Erreichen des Timeout-Endes zu simulieren, 
zum einfachen Testen von Automaten-Definitionen, ohne auf das Ende von längeren Timeouts warten zu müssen. 

***Bemerkung***:
Der Befehlssatz kann sich in zukünftigen Modul-Versionen verändern.


## DEA n: ...

### DEA-Definition 


<!-- DOC -->
#### Beschreibung des DEA

Hier sollte zur Dokumentation eine individuelle und eindeutige kurze Beschreibung des Automaten hinterlegt werden.
Der Wert wird ausschließlich in der ETS verwendet (als Teil der Kanalbezeichnung) und hat keinen Einfluss auf das Geräteverhalten.


<!-- DOC -->
#### Kommentar

Hier kann eine ausführlichere - auch mehrzeilige - Dokumention des Automaten erfolgen.
Es wird empfohlen zentrale Annahmen die dem Entwurf des Automaten zu Grunde liegen hier festzuhalten.
Die Dokumentation hat keinen Einfluss auf das Geräteverhalten.

<!-- DOCEND -->
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


<!-- DOC -->
#### Kanal verwenden?

Legt fest, ob dieser Automat konfiguriert und ausgeführt wird. 

<!-- DOCCONTENT
##### inaktiv

*(Standardwert)* Dieser Kanal wird *nicht* genutzt.

##### aktiv

Zur Verwendung *muss* diese Einstellung gewählt werden.

##### temporär inaktiv

Die Konfiguration dieses Kanals wird *ignoriert*, aber die Kommunikationsobjekte und alle Einstellungen bleiben sichtbar. 
Dadurch müssen GA-Verknüpfungen des zuvor 'aktiv' konfigurierten Kanals *nicht* entfernt werden und ein erneutes Hinzufügen beim späteren reaktivieren entfällt.

Bei Einstellung *temporär inaktiv* sind alle nachfolgenden Konfigurationen unwirksam.
DOCCONTENT -->


<!-- DOCEND -->
| Einstellungswert | Erklärung                                                                                                                                                                                                                                                                                  | ausführen | KOs/Konfiguration |
|------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-----------|-------------------|
| inaktiv          | *(Standardwert)* Dieser Kanal wird *nicht* genutzt.                                                                                                                                                                                                                                        | -         | -                 |
| aktiv            | Zur Verwendung muss diese Einstellung gewählt werden.                                                                                                                                                                                                                                      | ja        | sichtbar          |
| temporär inaktiv | Die Konfiguration dieses Kanals wird *ignoriert*, aber die Kommunikationsobjekte und alle Einstellungen bleiben sichtbar. Dadurch müssen GA-Verknüpfungen des zuvor 'aktiv' konfigurierten Kanals *nicht* entfernt werden und ein erneutes Hinzufügen beim späteren reaktivieren entfällt. | -         | sichtbar          |

> Bei Einstellung *inaktiv* sind alle nachfolgenden Konfigurationen ausgeblendet.

> Bei Einstellung *temporär inaktiv* sind alle nachfolgenden Konfigurationen unwirksam.



### Ausführung


<!-- DOC -->
#### Verzögerung nach Gerätestart

Nach dem Neustart ist der Automat zunächst inaktiv und wird erst nach Ablauf der Verzögerungszeit (zusätzlich zur Startverzögerung im Gerät) auf Ereignisse (wie z.B. Eingaben, Setzen des Zustand) reagieren und einen ggf. definierten Timeout starten.

> Mit dieser Einstellung kann z.B. verhindert werden, dass beim Neustart des Bus durch initial versendete Telegramme Zustandswechsel verursacht werden.

> Durch Definition eines eigenen Startzustandes mit Timeout kann ein ähnliches, aber nicht identisches, Verhalten erzielt werden:
> Ein Setzen des Zustandes wäre dann jedoch sofort möglich, sowie auch eine individuelle Definition auf welche Eingabesymbole reagiert werden und welche nicht.
> In Kombination mit einer Rekonstruktion des letzten Zustands ist dann jedoch keine besondere Behandlung des Startverhaltens möglich. 


<!-- DOC -->
#### Pausieren erlauben

Steuert, ob die Ausführung des Automaten unterbrochen werden kann.

Wird das Starten und Pausieren aktiviert, dann werden zwei KOs eingeblendet:

* Über das erste KO können Start/Stop-Befehle empfangen werden:
  Durch `Stop` wird eine laufende Ausführung unterbrochen, anschließend werden alle Ereignisse bis auf ein `Start` ignoriert.
  Ein Timeout des aktiven Zustands wird unterbrochen und beim erneuten Start fortgesetzt.
* Ein zweites KO liefert den aktuellen Ausführungsstatus zurück.

<!-- DOCCONTENT
##### **nein (Ausführung niemals unterbrechen)**

Der Automat wird kontinuierlich ausgeführt. Eine Unterbrechung ist nicht möglich.
Nach dem Einschalten wird der Automat gestartet.

##### **per KO, nach Einschalten starten**

Nach dem Einschalten verhält sich der Automat wie mit *nein (Ausführung niemals unterbrechen)*.
Über das eingeblendete Start/Stop-KO kann die Ausführung unterbrochen und fortgesetzt werden.

##### **per KO, warten auf Start-Telegramm**

Nach dem Einschalten ist der Automat zunächst inaktiv.
D.h. es werden keine Ereignisse verarbeitet.

Durch erstmaligen Eingang eines `Start`-Telegramms auf dem eingeblendeten Start/Stop-KO wird der Automat in den Startzustand versetzt.
Der Timeout beginnt ab diesem Zeitpunkt.
Anschließend kann die Ausführung erneut unterbrochen und fortgesetzt werden.

DOCCONTENT -->
<!-- DOCEND -->
| Einstellungswert               | Erklärung                                                                                                                                                                                                                                           | Start/Stop-KOs | starten nach dem Einschalten? |
|--------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|----------------|------------------------------|
| nein (Ausführung niemals unterbrechen)                    | Der Automat wird kontinuierlich ausgeführt. Eine Unterbrechnng ist nicht möglich.                                                                                                                                                                   | -              | ja                           |
| per KO, ...                    | Die Ausführung des Automaten kann unterbrochen werden. Dazu werden zwei KOs eingeblendet.                                                                                                                                                           | sichtbar       |                              |
| ... nach Einschalten starten   | Nach dem Einschalten verhält sich der Automat wie mit *nein (Ausführung niemals unterbrechen)*.                                                                                                                                                                                | sichtbar       | ja                           |
| ... warten auf Start-Telegramm | Nach dem Einschalten ist der Automat zunächst inaktiv. D.h. es werden keine Ereignisse verarbeitet.<br />Durch erstmaligen Eingang eines `Start`-Telegramms wird der Automat in den Startzustand versetzt. Der Timeout beginnt ab diesem Zeitpunkt. | sichtbar       | nein                         |



<!-- DOC -->
#### Rekonstruktion bei erneutem Start

<!-- 2d272170-a9e3-11ef-bd59-e7574d3ece74 BEGIN duplicate content -->

Bei Unterbrechung des Gerätebetriebs endet auch die Verarbeitung der definierten Automaten.
Mit der Rekonstruktion wird *versucht* die Verarbeitung nach dem Neustart fortzusetzen,
basierend auf dem letzten bekannten Zustand, dessen Aufrufzeitpunkt und ggf. letztem Ausführungsstatus.

***Technische Limitation:***
Die Rekonstruktion erfordert das erfolgreiche Speichern des momentanen Zustands und des Rest-Timeouts unmittelbar bei Beendigung der Verarbeitung.
Dies kann allerdings *nicht* immer gewährleistet werden:

* Ein Neustart durch Programmiervorgang kann zuverlässig erkannt werden
* Die Erkennung einer unterbrochenen Stromversorgung setzt eine entsprechende Hardwareausstattung voraus
* Ein Neustart per Reset-Taste kann *nicht* erkannt werden.

<!-- 2d272170-a9e3-11ef-bd59-e7574d3ece74 END duplicate content -->


<!-- DOCCONTENT
Einstellungswerte:

* **nein (immer Starten wie konfiguriert):**      Der Zustand vor einem Neustart hat keinen Einfluss. Nach einem Neustart wird immer mit dem konfigurierte Startzustand begonnen.
* **Fortsetzen, aber Timeout neu beginnen:**      Der zuletzt gespeicherte Zustand (sofern vorhanden) wird anstelle des regulären Startzustandes genutzt. Falls für diesen einen ein Timeout definiert ist, so wird dieser neu gestartet.
* **Fortsetzen mit gespeichertem Rest-Timeout:**  Der zuletzt gespeicherte Zustand (sofern vorhanden) wird anstelle des regulären Startzustandes genutzt. Falls für diesen einen ein Timeout definiert ist, so wird dieser um die bereits bis zur Speicherung des Zustands abgelaufene Zeit vermindert.
DOCCONTENT -->
<!-- * letzten Zustand mit absolutem Timeout-Ende  | zuletzt gespeicherter Zustand, sonst Startzustand | berechnet aus Uhrzeit | **(Geplant)** Der zuletzt gespeicherte Zustand (sofern vorhanden) wird anstelle des regulären Startzustandes genutzt. Falls für diesen einen ein Timeout definiert ist, so wird die Restzeit neu berechnet, so dass der selbe (absolute) Endzeitpunkt erreicht wird wie ohne Unterbrechung.<br> Diese Option benötigt eine Zeitangabe. | -->
<!-- DOCEND -->
| Einstellungswert                          | Erster Zustand                                    | Erster Timeout        | Erklärung                                                                                                                                                                                                                                                                                                                              |
|-------------------------------------------|---------------------------------------------------|-----------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| nein (immer Starten wie konfiguriert)     | Startzustand                                      | vollständig           | Der Zustand vor einem Neustart hat keinen Einfluss. Nach einem Neustart wird immer mit dem konfigurierte Startzustand begonnen.                                                                                                                                                                                                        |
| Fortsetzen, aber Timeout neu beginnen     | zuletzt gespeicherter Zustand, sonst Startzustand | vollständig           | Der zuletzt gespeicherte Zustand (sofern vorhanden) wird anstelle des regulären Startzustandes genutzt. Falls für diesen einen ein Timeout definiert ist, so wird dieser neu gestartet.                                                                                                                                                |
| Fortsetzen mit gespeichertem Rest-Timeout | zuletzt gespeicherter Zustand, sonst Startzustand | nur Restzeit          | Der zuletzt gespeicherte Zustand (sofern vorhanden) wird anstelle des regulären Startzustandes genutzt. Falls für diesen einen ein Timeout definiert ist, so wird dieser um die bereits bis zur Speicherung des Zustands abgelaufene Zeit vermindert.                                                                                  |
<!--
| letzten Zustand mit absolutem Timeout-Ende  | zuletzt gespeicherter Zustand, sonst Startzustand | berechnet aus Uhrzeit | **(Geplant)** Der zuletzt gespeicherte Zustand (sofern vorhanden) wird anstelle des regulären Startzustandes genutzt. Falls für diesen einen ein Timeout definiert ist, so wird die Restzeit neu berechnet, sodass derselbe (absolute) Endzeitpunkt erreicht wird wie ohne Unterbrechung.<br> Diese Option benötigt eine Zeitangabe. |
-->



<!-- DOC -->
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
<!-- DOC Skip="5" -->
> 
> Beispiele zum Einsatz von Logikkanälen:
> * Prüfung ob nicht-binären Eingangswerte in einem bestimmten Wertebereich liegen
> * Reaktion auf Über-/Unterschreitung von Schwellwerten, ggf. mit Hysterese und Mindesthaltedauer
> * Unterdrückung von Wiederholungen, um nur auf Wertänderungen zu reagieren 

#### Gemeinsamer Eingang (Symbole 1/0)

In vielen Fällen soll sowohl auf ein Ereignis, als auch ein zugehöriges negiertes Ereignis reagiert werden.
Zwei benachbarte Eingabesymbole können in diesem Fall als Paar zur vereinheitlichten gemeinsamen Konfiguration zusammengefasst werden.
Dadurch teilen sich beide Eingabesymbole denselben Eingang, 
wobei beim Eingang des Wertes `1` im Eingabekanal das erste Symbol und beim Werte `0` immer das zweite Symbol erzeugt wird.
Dadurch wird sichergestellt, dass derselbe Eingabekanal verwendet 

<!-- DOCCONTENT
Wird eine Paar-Option aktiviert, dann werden die beiden Eingabesymbole bei eintreffenden Ereignissen, 
in Abhängigkeit vom Wert, im selben Eingabekanel erzeugt. 

Ohne Auswahl der Option werden die Eingabesysmbole vollkommen unabhängig voneinander konfiguriert.
DOCCONTENT -->

<!-- DOC Skip="6" -->
| Einstellungswert | Erklärung                                                                                                                                                                                                                                                       | bei 1 | bei 0 |
|------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---------------------|---------------------|
| A/B              | Wenn Option aktiviert, dann werden die Eingabesymbole A und B bei eintreffenden Ereignissen, in Abhängigkeit vom Wert, im selben Eingabekanel erzeugt. <br />Ohne Auswahl der Option werden die Eingabesysmbole vollkommen unabhängig voneinander konfiguriert. | A                   | B                   |
| C/D              | Analog A/B.                                                                                                                                                                                                                                                     | C                   | D                   |
| E/F              | Analog A/B.                                                                                                                                                                                                                                                     | E                   | F                   |
| G/H              | Analog A/B.                                                                                                                                                                                                                                                     | G                   | H                   |

<!-- DOC Skip="4" -->
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

<!-- DOCCONTENT
* **inaktiv**:        Das Eingabesymbol wird niemals erzeugt und in der Automatendefinition nicht berücksichtigt.
* **Eigenes KO**:     Zur direkten Reaktion auf Werte die auf dem Bus bereit stehen. Eingabesymbole werden durch eingehende Telegramme erzeugt. Ein KO mit DPT1 wird eingeblendet.
* **Logik-Ausgang**:  Nutzung von Werten die durch einen Logikkanal erzeugt und als Ergebnis ausgegeben werden. *Empfohlenen*, wenn Eingangswerte zunächst in 0/1 konvertiert oder vorgefiltert werden müssen, zur Nutzung von Zeitschaltuhrfunktionen, oder ggf. weiterer Funktionen des ***Logikmoduls***. Der Logik-Ausgang muss durch die Kanal-Nummer (1 bis Anzahl der Logikkanäle) des Logikmoduls festgelegt werden. ***Achtung:*** Fehlfunktionen möglich, bei Auswahl eines Ausgangs mit nicht kompatiblem DPT.
* **Bestehendes KO**: Verwendung von Werten, die bereits in anderen KOs abgebildet sind, unabhängig von einer Übertragung auf den Bus. Ausgänge von Logik-Kanälen sollten *nicht* über die KO-Nummer verknüpft werden. ***Achtung:*** Fehlfunktionen möglich, bei Auswahl eines KO mit nicht kompatiblem DPT. Bei späteren Updates mit Veränderung der KO-Nummerierung muss eine manuelle Anpassung der Nummerierung vorgenommen werden. Auswahl über die KO-Nummer.
DOCCONTENT -->
<!-- DOC Skip="6" -->
| Eingabekanal   | Erklärung                                                                                                                                                                                                                                                                                                                                                                                                                                                 | Eingangs-KO | Kanalauswahl                                                                                             |
|----------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------------|----------------------------------------------------------------------------------------------------------|
| inaktiv        | Das Eingabesymbol wird niemals erzeugt und in der Automatendefinition nicht berücksichtigt.                                                                                                                                                                                                                                                                                                                                                               | -           | -                                                                                                        |
| Eigenes KO     | Zur direkten Reaktion auf Werte die auf dem Bus bereit stehen. Eingabesymbole werden durch eingehende Telegramme erzeugt. Ein KO mit DPT1 wird eingeblendet.                                                                                                                                                                                                                                                                                              | sichtbar    | Keine Konfiguration.<br />Nur Anzeige von genutztem Eingang 1 bis 8.                                     |
| Logik-Ausgang  | Nutzung von Werten die durch einen Logikkanal erzeugt und als Ergebnis ausgegeben werden. *Empfohlenen*, wenn Eingangswerte zunächst in 0/1 konvertiert oder vorgefiltert werden müssen, zur Nutzung von Zeitschaltuhrfunktionen, oder ggf. weiterer Funktionen des [Logikmoduls](/OpenKNX/OAM-LogicModule/blob/main/doc/Applikationsbeschreibung-Logik.md). ***Achtung:*** Fehlfunktionen möglich, bei Auswahl eines Ausgangs mit nicht kompatiblem DPT. | -           | Der Logik-Ausgang wird durch die Kanal-Nummer (1 bis Anzahl der Logikkanäle) des Logikmoduls festgelegt. |
| Bestehendes KO | Verwendung von Werten, die bereits in anderen KOs abgebildet sind, unabhängig von einer Übertragung auf den Bus. Ausgänge von Logik-Kanälen sollten *nicht* über die KO-Nummer verknüpft werden. ***Achtung:*** Fehlfunktionen möglich, bei Auswahl eines KO mit nicht kompatiblem DPT. Bei späteren Updates mit Veränderung der KO-Nummerierung muss eine manuelle Anpassung der Nummerierung vorgenommen werden.                                        | -           | Auswahl über die KO-Nummer (1 bis maximale KO-Nummer)                                                    |

##### Auslösewert (je Eingabesymbol)

<!-- DOCCONTENT
* **bei 0**:             Nur bei Eintreffen eines Wertes 0 wird das Eingabesymbol erzeugt. 1 wird ignoriert.
* **bei 1**:             Nur bei Eintreffen eines Wertes 1 wird das Eingabesymbol erzeugt. 0 wird ignoriert.
* **jeder (0 oder 1)**:  Es erfolgt keine Unterscheidung zwischen den Werten. Bei jedem Eintreffen eines Wertes wird ein Eingabesymbol erzeugt.
DOCCONTENT -->
<!-- DOC Skip="5" -->
| Auslösewert      | Eintreffen des Wertes 1 | Eintreffen des Wertes 0 | Kommentar                                           |
|------------------|-------------------------|-------------------------|-----------------------------------------------------|
| bei 0            | ignorieren              | Eingabesymbol erzeugen  |                                                     |
| bei 1            | Eingabesymbol erzeugen  | ignorieren              |                                                     |
| jeder (0 oder 1) | Eingabesymbol erzeugen  | Eingabesymbol erzeugen  | Es erfolgt keine Unterscheidung zwischen den Werten |

##### Auslösewert (je Eingabesymbol-Paar)
Anzeige der erzeugten Eingabesymbole für Auslösewerte 1 und 0.



<!-- DOC -->
### Ausgabe

Es können bis zu 4 Ausgabekanäle (O1, O2, O3, O4) konfiguriert werden, für die bei Aktivierung jeweils ein KO mit gewähltem Datentyp bereitgestellt wird.
Es stehen gängige DPTs (1,2,5,5.001,6,7,8,9,12,13,14,17,232.600) zur Auswahl, sowie *ausschließlich* für O4 auch Text (DPT16.001).
Für jede Kombination aus Zustand und Ausgang kann ein Wert und ein Sendeverhalten definiert werden.

#### Bezeichnung/Kommentar (je Ausgabekanal)

Hier sollte zur Dokumentation eine individuelle kurze Beschreibung des jeweiligen Ausgabekanal hinterlegt werden.
Der Wert wird ausschließlich in der ETS verwendet (Als Beschriftung von Konfigurationsseiten und KOs) und hat keinen Einfluss auf das Geräteverhalten.

#### Datentyp (je Ausgabekanal)

<!-- DOCCONTENT
***DPT17.001 Textausgabe:*** Die Ausgabe von 14-Byte-Texten ist angesichts des deutlich höheren Speicherbedarfs nur auf den letzten Ausgabekanal verfügbar.
DOCCONTENT -->
<!-- DOCEND -->
| Wert             | O1,O2,O3          | O4 | Bemerkung                                                                                                                      |
|------------------|-------------------|----|--------------------------------------------------------------------------------------------------------------------------------|
| inaktiv          | 1                 | 1  | Der Ausgabekanal wird ausgeblendet.                                                                                            |
| 1.x              | 1                 | 1  | 1Bit                                                                                                                           |
| 2.x              | 1                 | 1  | 2Bit                                                                                                                           |
| 5.x              | 1                 | 1  | 1Byte vorzeichenlos                                                                                                            |
| 5.001            | 1                 | 1  | Prozentwert (1Byte)                                                                                                            |
| 6.x              | 1                 | 1  | 1byte vorzeichenbehaftet                                                                                                       |
| 7.x, 8.x, 9.x    | 1                 | 1  | 2Byte (vorzeichenlos, vorzeichenbehaftet, Fließkomma mit geringer Genauigkeit)                                                 |
| 12.x, 13.x, 14.x | 1                 | 1  | 4Byte (vorzeichenlos, vorzeichenbehaftet, Fließkomma)                                                                          |
| 16.x             | 1                 | 1  | Szenen; Bei Aktivierung des Senden wird als Standardwerte der gewählte Zustand eingestellt.                                    |
| 17.001           | nicht unterstützt | 1  | Die Ausgabe von 14-Byte-Texten ist angesichts des deutlich höheren Speicherbedarfs nur auf den letzten Ausgabekanal verfügbar. |
| 232.600          | 1                 | 1  |                                                                                                                                |


### Zustände und Übergangsfunktion einschließlich zeitbasierter Folgezustände


<!-- DOC -->
#### Startzustand

Definiert den Zustand den der Automat beim (erstmaligen) Einschalten einnimmt.


<!-- DOC -->
#### Direktes Setzen von Zustand erlauben?

Optional kann eine Änderung des Zustands, unabhängig vom aktuellen Zustand, den Eingabesymbolen oder dem Timeout erfolgen.

<!-- DOCCONTENT
* **nein**:                                    Der Zustand wechselt ausschließlich durch Eingabe eines Symbols, oder Timeout.
* **über separates KO**:                       Es wird ein weiteres KO eingeblendet, über das der aktuelle Zustand unmittelbar überschrieben werden kann. Zustände außerhalb des Definitionsbereichs (Szene 1 bis 16) werden ignoriert.
* **über gemeinsames KO mit Zustandsausgabe**: Der aktuelle Zustand kann über das KO mit Ausgabe des Momentan-Zustandes überschrieben werden. Zustände außerhalb des Definitionsbereichs (Szene 1 bis 16) werden ignoriert.
DOCCONTENT -->
<!-- DOCEND -->
| Einstellungswert                        | Erklärung                                                                                                                                                                                                                                                                             |
|-----------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| nein                                    | Der Zustand wechselt ausschließlich durch Eingabe eines Symbols, oder Timeout.                                                                                                                                                                                                        |
| über separates KO                       | Es wird ein weiteres KO eingeblendet, über das der aktuelle Zustand unmittelbar überschrieben werden kann. Zustände außerhalb des Definitionsbereichs (Szene 1 bis 16) werden ignoriert.                                                                                              |
| über gemeinsames KO mit Zustandsausgabe | Der aktuelle Zustand kann über das KO mit Ausgabe des Momentan-Zustandes überschrieben werden. Zustände außerhalb des Definitionsbereichs (Szene 1 bis 16) werden ignoriert. |


<!-- DOC -->
#### Erneutes Setzen von aktuellem Zustand

Definiert das Verhalten beim Versuch den bereits aktuellen Zustand nochmals direkt zu setzen.

<!-- DOC Skip="1" -->
> Nur einstellbar, wenn **[Direktes Setzen von Zustand](#direktes-setzen-von-zustand-erlauben)** erlaubt **über separates KO**. Beim **gemeinsamen KO** wird das Setzen immer ignoriert.

* **ignorieren**: Der Zustandsaufruf wird verworfen.
* **Zustand neu starten**: 
  Der Automat verhält sich so, als ob der Zustand erstmalig aufgerufen würde.
  Falls ein Timeout definiert ist, beginnt dieser erneut mit der definierten Dauer.
  Das Senden der Ausgaben wird erneut geprüft.


<!-- DOC -->
#### Tabelle Zustände und Übergänge  

##### **Bezeichnung (je Zustand)**

Hier sollte zur Dokumentation eine individuelle kurze Beschreibung des jeweiligen Zustands hinterlegt werden.
Der Wert wird ausschließlich in der ETS verwendet und hat keinen Einfluss auf das Geräteverhalten.

##### **Übergangsfunktion (Spalte "A" bis "H")**

Für jede Kombination aus (Ausgangs)Zustand (Zeile 1 bis 16) und Eingabesymbol (Spalte A bis H) 
kann ein möglicher Folgezustand (`1` bis `16`), oder ein Zurücksetzen des Timeouts (`<<`) festgelegt werden.
Falls kein Folgezustand festgelegt wird (`-`), so wird die Eingabe ignoriert.

*Folgezustand identisch zum Ausgangszustand:* Mit dieser Definition kann erreicht werden,
dass ein definierter Timeout zurückgesetzt wird und der Zustand erneut auf den Bus gesendet wird.

##### **Timeout / Einheit / Spalte "T"**

Durch die Timeout-Funktion kann ein Zustandswechsel erfolgen, wenn innerhalb eines definierten Zeitraums *keine* Zustandsveränderung erfolgt ist.
D.h.: Es wurde *nicht*

* basierend auf der Übergangsfunktion in einen anderen Zustand gewechselt
* basierend auf der Übergangsfunktion derselbe Zustand erneut aufgerufen
* der Zustand von außen überschrieben

*Anwendungsbeispiele für die Timeout-Funktion:*

* Rückfall auf einen Standardzustand
* zeitverzögerte Aktionen
* Sicherstellen, dass innerhalb eines Zeitraums ein Ereignis nicht eintritt 

###### **Spalte T: zeitbasierter Folgezustand**

Mit Auswahl eines Zustandes wird die Timeout-Definition aktiviert und die Konfiguration für die Timeout-Dauer eingeblendet.
Ohne Auswahl erfolgt keine zeitabhängige Reaktion.

###### **Timeout / Einheit**

Definiert die Dauer des Timeouts.

Die Zeitmessung beginnt mit Eintritt in den Zustand.
Bei erneutem Aufruf desselben Zustands oder Zurücksetzen des Timeouts beginn die Zeitmessung nochmal in voller definierten Länge.
Ein Pausieren unterbricht die Zeitmessung, bis zum Beenden der Pause.
Falls Rekonstruktion aktiviert ist, so wird nach Neustart des Gerätes mit der restlichen Zeit fortgesetzt oder die Zeitmessung erneut gestartet.



<!-- DOC -->
### Ausgang n: ...

#### Sendeintervall bei zyklischer Wiederholung 

Definiert den Zeitraum bis der Wert erneut auf den Bus gesendet wird, falls ein zyklisches Sendeverhalten eingestellt wird.

#### Definition Ausgangswert

##### **Sendeverhalten (je Zustand)**

> ***Tipp zur erleichterten ETS-Konfiguration:*** 
> Über die Tasten `-`, `k`(kein Senden), `w`(Wert), `z`(Zustand), `j`(jedes) kann die jeweilige Sendestrategie schnell ausgewählt, 
> bzw. zwischen den verschiedenen Ausprägungen gewechselt, werden. Mit `<Tab>` kann zum nächsten Zustand gewechselt werden. 

Definiert, ob in dem Zustand ein Wert für diesen Ausgang zugewiesen wird und wenn ja, ob und wann dieser auf den Bus gesendet wird.

Für den Fall der ***Rekonstruktion*** kann beim Neustart ein "zusätzliches" einmaliges Senden aktiviert werden 
("...&nbsp;+&nbsp;Rekonstruktion") um die Ausgangswerte auch nach einem Geräte-Neustart oder kompletten Bus-Neustart bereitzustellen.
Hinweis: In Szenarien, in denen der Empfang des Ausgangswertes als Trigger eine Aktion auslöst oder neu startet, sollte das Senden in diesem Fall unterbleiben.

Optional kann eine regelmäßige Wiederholung des Sendevorgangs eingestellt werden ("...&nbsp;+&nbsp;zyklisch"). 
Die Wiederholung erfolgt dann unabhängig vom Zustand im für diesen Ausgang eingestellten ***Sendeintervall bei zyklischer Wiederholung***.


<!-- DOCCONTENT
* **-**:                                            Dem Zustand wird kein Ausgangswert zugeordnet. Der Wert des KOs wird nicht verändert (d.h. der bereits gesetzte Wert bleibt erhalten) und es wird nicht auf den Bus gesendet.
* **kein Senden, nur KO setzen**:                   Das KO wird auf den angegebenen Wert gesetzt, ohne diesen auf den Bus zu senden. Anschließend ist ein Abruf per Read-Request möglich.
* **Wert-Änderung**:                                Sendet dann auf den Bus, wenn der zugeordnete Wert vom vorherigen Wert im KO abweicht. Eine Wert-Änderung kann *nur* bei Änderung des Zustandes auftreten, wenn dem vorherigen Zustand ein anderer Wert zugeordnet war. 
* **Wert-Änderung + Rekonstruktion**:               Wie **Wert-Änderung**, aber auch bei Rekonstruktion.  
* **Zustands-Änderung**:                            Senden immer dann auf den Bus, wenn ein Wechsel des Zustands erfolgt, unabhängig von den Werten die den Zuständen zugeordnet sind. Eine Zustands-Änderung erfolgt beim Starten und beim Wechsel in einen abweichenden Folgezustand durch Symboleingabe, Timeout oder direktes Setzen des Zustands.
* **Zustands-Änderung + Rekonstruktion**:           Wie **Zustands-Änderung**, aber auch bei Rekonstruktion.  
* **jeder Zustands-Aufruf + Rekonstruktion**:       Senden erfolgt bei jedem Aufruf des Zustands, unabhängig von einer Veränderung des Zustands oder des Augsgansgwertes. Ein Zustands-Aufruf erfolgt beim Starten, durch direktes Setzen des Zustands, oder bei definierten (nicht zwingend abweichenden) Folgezuständen durch Symboleingabe bzw. Timeout, sowie auch bei Rekonstruktion. 
* **... + zyklisch**:                               Sendet ergänzend den aktuellen Wert wiederholt im für diesen Zustand definierten **Sendeintervall**.                               

DOCCONTENT -->
<!-- DOC Skip="13" -->
| Einstellungswert                                  | nach Rekonstruktion | bei Wertänderung (erfordert Zustand-Wechsel) | bei Zustands-Änderung (ohne Wertänderung) | bei Zustandsaufruf (selber Zustand) | zyklisch senden | Beschreibung                                                                                                                                                                                                                     |
|---------------------------------------------------|:-------------------:|:--------------------------------------------:|:-----------------------------------------:|:-----------------------------------:|:---------------:|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| -                                                 |          -          |                      -                       |                     -                     |                  -                  |        -        | kein Wert (letzter Wert bleibt unverändert)                                                                                                                                                                                      |
| kein Senden, nur KO setzen                        |    nur KO setzen    |             nur KO aktualisieren             |                     -                     |                  -                  |        -        | nur Wert aktualisieren (Abruf per Read-Request möglich)                                                                                                                                                                          |
| Wert-Änderung                                     |    nur KO setzen    |                    senden                    |                     -                     |                  -                  |        -        | bei Wertänderung oder beim Start ohne Rekonstruktion (kann nur zusammen mit Änderung vom Zustand auftreten)                                                                                                                      |
| Wert-Änderung + Rekonstruktion                    |       senden        |                    senden                    |                     -                     |                  -                  |        -        | bei Wertänderung oder beim Start (mit oder ohne Rekonstruktion)                                                                                                                                                                  |
| Wert-Änderung + Rekonstruktion + zyklisch         |       senden        |                    senden                    |                     -                     |                  -                  |       ja        | bei Wertänderung oder beim Start (mit oder ohne Rekonstruktion) oder wiederholt im eingestellten Sendezyklus                                                                                                                     |
| Zustands-Änderung                                 |    nur KO setzen    |                    senden                    |                  senden                   |                  -                  |        -        | bei Zustandsänderung (z.B. beim Start ohne Rekonstruktion, durch Symboleingabe, durch Statuseingabe, durch Timeout)                                                                                                              |
| Zustands-Änderung + Rekonstruktion                |       senden        |                    senden                    |                  senden                   |                  -                  |        -        | bei Zustandsänderung (z.B. beim Start mit oder ohne Rekonstruktion, durch Symboleingabe, durch Statuseingabe, durch Timeout)                                                                                                     |
| Zustands-Änderung + Rekonstruktion + zyklisch     |       senden        |                    senden                    |                  senden                   |                  -                  |       ja        | bei Zustandsänderung (z.B. beim Start mit oder ohne Rekonstruktion, durch Symboleingabe, durch Statuseingabe, durch Timeout) oder wiederholt im eingestellten Sendezyklus                                                        |
| jeder Zustands-Aufruf + Rekonstruktion            |       senden        |                    senden                    |                  senden                   |               senden                |        -        | bei Zustandsaufruf (wie bei Zustandsänderung, aber z.B. auch bei Symboleingabe mit identischem Folgezustand, Statuseingabe des aktuellen Zustands, Timeout mit selbem Folgezustand)                                              |
| jeder Zustands-Aufruf + Rekonstruktion + zyklisch |       senden        |                    senden                    |                  senden                   |               senden                |       ja        | bei Zustandsaufruf (wie bei Zustandsänderung, aber z.B. auch bei Symboleingabe mit identischem Folgezustand, Statuseingabe des aktuellen Zustands, Timeout mit selbem Folgezustand) oder wiederholt im eingestellten Sendezyklus |

> Die Sendehäufigkeit, bzw. die Auslöser für ein Senden, nehmen entsprechend der Reihenfolge der Optionen zu.

##### **Ausgabewert (je Zustand)**

Falls ein Sendeverhalten für diesen Zustand definiert wurde, kann hier der Wert entsprechend des ausgangsspezifischen Types festgelegt werden.



# Kommunikationsobjekte

## Je DEA

|  KO   |    DPT | Bezeichnung                | Erklärung                                                                                                                                                                                                           |
|:-----:|-------:|----------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|  +0   | 17.001 | Aktueller Zustand          | Gibt den momentanen Zustand aus, als `0=Szene 1` bis `15=Szene 16`.<br />Wert wird bei jedem Setzen des Zustandes geschrieben, auch wenn der Zustand sich nicht ändern sollte.                                      |
|   "   | 17.001 | Zustand (Ausgang/Eingang)  | [(Alternativ/Optional)](#direktes-setzen-von-zustand-erlauben) Kombinierte Funktion von *Aktueller Zustand* und *Zustand setzen*.                                                                                   |
| (+1)  | 17.001 | Zustand setzen             | [(Optional)](#direktes-setzen-von-zustand-erlauben) Erlaubt ein direktes Festlegen/Überschreiben des Zustands von außen. Verarbeitet werden die Werte `0=Szene 1` bis `15=Szene 16`, alle anderen werden ignoriert. |
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


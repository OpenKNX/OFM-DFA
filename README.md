# OpenKNX-Modul zur Definition zustandsbehaftetem Verhalten auf Basis von Deterministischen Endlichen Automaten (DEA)

Implementierung von Zustandsautomaten mit funktionalen Erweiterungen für KNX, konfigurierbar über die ETS.

Von Cornelius Köpp 2023 -- 2026

**Hinweis:** 
Die [OpenKNX StateEngine](https://github.com/OpenKNX/OAM-StateEngine/) dient als Referenz-Applikation für dieses Modul
und bietet eine besonders hohe Anzahl von unabhängigen Automaten-Definitionen/Kanälen. 
Eine geringere Anzahl von Automaten ist u.A. im [OpenKNX RaumController](https://github.com/OpenKNX/OAM-RaumController/) integriert.



## Kurzbeschreibung
Dieses Modul erlaubt eine universelle Modellierung von zustandsabhängigem Verhalten:<br />
Jeder Kanal repräsentiert eine Automaten-Definition mit 16 verschiedenen Zuständen.
Zwischen den Zuständen kann durch 8 verschiedenen Eingabeereignisse oder Ablauf eines zustandsabhängigen Timeouts gewechselt werden.
Als optionale Erweiterung können bedingte Zustandsübergänge genutzt werden, die bei Eintritt des Eingabeereignisses dynamisch ausgewertet werden.
Über 4 Ausgangskanäle können zustandsspezifische Werte mit zustandsspezifischem Sendeverhalten ausgegeben werden, 
in verschiedenen gängigen DPTs.
Zusätzlich erfolgt eine Ausgabe des aktuellen Zustands. 
Optional kann auch ein Direktaufruf des Zustands erlaubt werden, 
eine Unterbrechung der Ausführung, 
sowie Rekonstruktion des letzten Zustands und Status nach einem Neustart.

Die Definition in der ETS erfolgt über eine (zwei-dimensionale) Zustandsübergangstabelle.<br />
Zur **Konfiguration in der ETS** siehe [Applikationsbeschreibung](doc/DFA_Applikationsbeschreibung.md#applikationsbeschreibung-ofm-dfa)

**Änderungen** zwischen den Versionen können im [**Changelog**](CHANGELOG.md) eingesehen werden. 


## Inhalte

<!-- * [Kurzbeschreibung](#kurzbeschreibung) -->
* [Einsatz](#einsatz)
  * [Hinweise und Tipps zur Modellierung & Nutzung (FAQs)](#hinweise-und-tipps-zur-modellierung--nutzung-faqs)
* [Beispiele](#beispiele)
* [Grundidee in Anlehnung an gängige formale Definitionen](#grundidee-in-anlehnung-an-gängige-formale-definitionen)
* [Für Entwickler: Integration in OpenKNX OAMs](#für-entwickler-integration-in-openknx-oams)


## Einsatz

Das Modul kann eingesetzt werden, um zustandsabhängiges Verhalten zu definieren,
das abhängig ist von der Reihenfolge, oder sogar genauer definierten zeitlichen Abfolge, von Ereignissen.
Die Verarbeitung erfolgt Ereignis-orientiert, bei Eingang von Telegrammen vom Bus, 
Aktualisierung von Logik-Ausgängen in der Vorverarbeitung (oder anderer KOs), oder nach Ablauf eines zustandsabhängigen Timeouts.  

Verhalten das nur von aktuellen Werten (z.B. logische Verknüpfung von mehreren Eingängen) oder der Uhrzeit abhängt, 
oder Umwandlung und Berechnung von Werten, kann mit dem [OpenKNX Logikmodul](https://github.com/OpenKNX/OFM-LogicModule) beschrieben werden.
Dies ist in vielen Fällen nützlich oder notwendig zur Vorbereitung von Eingangswerten dieses Moduls,
daher können Ausgänge von Logikkanälen direkt als Eingänge gewählt werden.

Für Standardprobleme sollten spezialisierte Module wie z.B.
[OpenKNX PresenceModule](https://github.com/OpenKNX/OFM-PresenceModule) genutzt werden;
dieses bieten eine auf den jeden Anwendungsfall optimierte Konfiguration.

### Hinweise und Tipps zur Modellierung & Nutzung (FAQs)

* [Warum ist die Auswahl und Definition des Startzustands so wichtig?](doc/DFA_Applikationsbeschreibung.md#warum-ist-die-auswahl-und-definition-des-startzustands-so-wichtig)
* [Warum ist es problematisch, wenn man Ausgabewerte für einzelne Zustände einfach weglässt?](doc/DFA_Applikationsbeschreibung.md#warum-ist-es-problematisch-wenn-man-ausgabewerte-für-einzelne-zustände-einfach-weglässt)
* [Kann ich die Eingabe der vielen Parameter irgendwie beschleunigen?](doc/DFA_Applikationsbeschreibung.md#kann-ich-die-eingabe-der-vielen-parameter-irgendwie-beschleunigen)
* [Was kann ich tun, wenn die 4 Ausgänge nicht ausreichen?](doc/DFA_Applikationsbeschreibung.md#was-kann-ich-tun-wenn-die-4-ausgänge-nicht-ausreichen)


## Beispiele

* [Einführungsbeispiel für KNX-Nutzer:<br>**Virtueller Schaltaktor mit Sperre und Treppenhaus-Funktion**](doc/DFA_Beispiel1_VirtuellerAktor.md#einführungsbeispiel-für-knx-nutzer-virtueller-schaltaktor-mit-sperre-und-treppenhaus-funktion)
* [Beispiel zur Vorverarbeitung durch Logik-Kanäle:<br>**Umwandlung von DPT2 (Zwangsführung) in Eingabesymbole**](doc/DFA_Beispiel2_DPT2.md#beispiel-zur-vorverarbeitung-durch-logik-kanäle-umwandlung-von-dpt2-zwangsführung-in-eingabesymbole)

Weitere Anwendungen (ohne detaillierte Dokumentation):

* Abbildung von Fertig-Meldung/Leerungs-Aufforderung für Waschmaschinen und Trockner und Erkennung von Leerung durch Präsenz
* Briefkasten
* Dunstabzugshaubensteuerung
* Einfache Menü-Steuerungen unter Einsatz von Text-Ausgabe
* Simulation von einfachen KNX-Geräten
* Umschaltungen zwischen mehrfachen Manuell und Automatik-Steuerungen mit Rückfall
* Spezialfälle von Präsenzsteuerung, die nicht durch das OpenKNX-VPM-Modul abgebildet werden können
* Manuelles Quittieren von Sensor-verursachten Änderungen
* Ausführung von Sequenzen mit Zeitablauf, z.B. Fahren von Rollläden nacheinander
* Erkennung von/Reaktion auf bestimmten aufeinanderfolgenden Ereignissen, oder deren Ausbleiben


## Grundidee in Anlehnung an gängige formale Definitionen
> Informatikern wird das Modell bekannt und vertraut vorkommen; 
> bei genauerem Hinsehen werden allerdings gewisse Abweichungen deutlich um das Konzept an den Praxisbedarf anzupassen.
> 
> ***Hinweis:*** 
> Die Erweiterung mit bedingten Übergängen ist nicht mehr durch das nachfolgend beschriebene Modell abgedeckt.
> Werden diese verwendet, so werden damit bestimmte Garantieren verloren.  

### Z&subset;{z<sub>1</sub>,..,z<sub>16</sub>} := Menge der Zustände
... wird als Teilmenge von DPT17.001 (Szenen: {0=Szene1,..,63=Szene64}) dargestellt.
In der aktuellen Implementierung eingeschränkt auf die Zustände 1 bis 16.
Bei Erreichen eines Zustandes können, durch die Ausgabe der korrespondierenden Szene, unmittelbar mehrere unabhängige Aktionen gleichzeitig ausgelöst werden.
Ergänzend können mehrere individuelle Ausgangswerte je Zustand definiert werden.

### z<sub>0</sub>&isin;Z := Startzustand
... wird beim Einschalten als erster Zustand angenommen, 
sofern nicht ein zuvor gewählter Zustand rekonstruiert wird.

### X := Eingabealphabet
... umfasst ***Symbole*** deren Eingabe (bzw. das damit verbundene Ereignis) eine Zustandsänderung bewirken kann. 
Abhängig von der Konfiguration setzt sich das Eingabealphabet aus den folgenden Symbol-Mengen zusammen:

* #### X<sub>e</sub>&subset;{A,..,H} := Eingangssignale
  
  Die Symbole **A** bis **H** werden durch bis zu 8 unabhängige DPT1 Eingabekanälen erzeugt; bei Eingang von 1 und/oder 0.
  Durch optionale Konfiguration als Eingabesymbolpaar kann z.B. ohne weiter Vorverarbeitung auf das Auftreten oder den Wegfall von erkannter Präsenz reagiert werden.

* #### X<sub>t</sub>={T} := Zeitablauf
  
  Das Symbol **T** wird erzeugt,
  wenn innerhalb eines zustands-spezifisch konfigurierten Zeitintervalls keine Eingabe erfolgt
  (bzw. kein anderes Ereignis eingetreten) ist.

* #### X<sub>z</sub>={z<sub>1</sub>,..,z<sub>16</sub>} := Zustandsdirektaufruf

  Abhängig von der Konfiguration kann durch Eingabe in einen DPT17.001 Zustandseingang ein entsprechendes Symbol erzeugt werden. 

Das Eingabealphabet kann die Form X=X<sub>e</sub>&cup;X<sub>t</sub> oder X=X<sub>e</sub>&cup;X<sub>t</sub>&cup;X<sub>z</sub> aufweisen.

### d:Z&times;X&rarr;Z&cup;{undef} := Überführungsfunktion mit partieller Definition
... beschreibt für jede Kombination aus Ausgangszustand und Eingabesymbol, ob und wenn ja in welchen Folgezustand bei Eingabe gewechselt wird.
Nicht angegebene Zustandsübergabe werden ignoriert und führen nicht in einen Fehlerzustand.

Falls X<sub>z</sub>&subset;X (*Direktes Setzen von Zuständen ist erlaubt*), 
so gilt d(z,z<sub>i</sub>)=z<sub>i</sub> 
für alle z<sub>i</sub>&in;X<sub>z</sub>\\{z} (*ignorieren von erneutem Aufruf des bereits gesetzten Zustands*), 
oder sogar für alle z<sub>i</sub>&in;X<sub>z</sub> (*Neustart von bereits gesetztem Zustand*).

> ***Hinweis:***
> Bei Nutzung von bedingten Übergängen ist der Folgezustand nicht mehr eindeutig
> und wird bei jedem Aufruf, durch den momentanen Ausgangswert von bis zu 16 Logikkanälen ermittelt.
> Der formale Zusammenhang ist damit deutlich komplizierter.


### *Endzustände* 
... werden nicht explizit abgebildet.
Im Rahmen einer Nachverarbeitung kann jedoch leicht ermittelt werden, ob ein Zustand aus dieser Menge eingenommen wurde.
Es können Zustände definiert werden, die nicht mehr durch Eingabe eines Symbols verlassen werden.


## Für Entwickler: Integration in OpenKNX OAMs

> ***Wichtig***:
Die Anzahl der Kanäle muss vor einer Integration kritisch abgewogen werden, 
da die je Kanal enthaltenen Anzahl von Parametern und der erforderliche Parameterspeicher deutlich größer sind als bei anderen OpenKNX-Modulen.
Eine zu hohe Anzahl von Kanälen kann sich negativ auf die Performance in der gesamten erzeugten ETS-Applikation auswirken.
Mit einem Bedarf von knapp 1 KB Parameterspeicher je Kanal wird u.U. eine Anpassung des Speicherlayouts erforderlich. 


Dieses Modul besteht aus
einem [Applikationsteil](#integration-in-ets-applikation)
und 
einem [Firmware-Modul](#integration-in-firmware).
Diese müssen beide innerhalb eines OpenKNX-Applikations-Projektes eingebunden werden, wie unten gezeigt.

### Abhängigkeiten

Das Modul erfordert die gleichzeitige Integration des [OpenKNX Logikmoduls](https://github.com/OpenKNX/OFM-LogicModule).
Da dieses i.d.R. in allen OpenKNX-Applikationen enthalten ist, stellt dies in der Praxis keine besondere Anforderung dar. 

### Integration in ETS-Applikation

Das Modul stellt folgende KOs bereit:

* 30 für jeden Kanal (Automatendefinition)
* keine kanalunabhängigen KOs

> ***Achtung***:
> `ModuleType` muss auf einen Wert im Bereich 2 bis 9 gesetzt werden, da ein vergrößerter Namespace für Parameter verwendet wird.
> Ein solcher einstelliger *ModuleType* `m` entspricht einer gleichzeitigen Belegung des vollständigen Bereichs von *ModuleType* `10*m` bis *ModuleType* `10*m+9`, 
> d.h. es darf kein anderes Modul mit einem *ModuleType* in diesem Bereich in der Applikation eingebunden werden.  
> 
> Beispiel: Der nachfolgend gezeigte *ModuleType* `2` verbietet andere Module mit einem *ModuleType* von `20` bis `29`.

An der gewünschten Stelle in der jeweiligen `{ApplikationName}.xml` den folgenden Code einbinden:

```
  <!-- Number of visible channels before configuration, can be defined in separate config file: -->
  <op:config name="%DFA_NumChannelsDefault%"  value="2" />

  <!-- 30 KOs / Channel, NO central KOs -->
  <!-- IMPORTANT: ModuleType must be set to 1-digit value from 2 to 9, without conflict to 2-digit values starting with the same digit; see documentation! -->
  <op:define prefix="DFA"
             share="../lib/OFM-DFA/src/DfaModule.share.xml"
             template="../lib/OFM-DFA/src/DfaModule.templ.xml"
             NumChannels="%DFA_NumChannels%"
             KoOffset="30"
             ModuleType="2" >
    <op:verify File="../lib/OFM-DFA/library.json" ModuleVersion="%DFA_VerifyVersion%" />
  </op:define>
```

### Integration in Firmware

<!-- * Sehr hoher Bedarf an Konfigurationsspeicher -->


```
// ...
#include "Logic.h"
#include "DfaModule.h"
// ...

void setup()
{
    // ...
    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxDfaModule);
    // ...
}

// ...
```
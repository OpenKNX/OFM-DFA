> # BETA-STATUS! <!-- (DE/German) -->
>
> Obgleich vorab ein länger andauernder interner Produktiv-Test erfolgt ist, 
> in dessen Rahmen nur noch Anpassungs- und Optimierungsbedarf bei der Behandlung von Spezialfällen indentifiziert wurde,
> besteht weiterhin ein erhöhtes Risiko von Fehlern.
> Vor allem bei der Nutzung von erweiterten Funktionen und solchen Anwendungsszenarien, die bei der Entwicklung nicht berücksichtigt wurden.
>
> In nachfolgenden Versionen sind Änderungen an der KO-Nummerierung möglich, 
> daher wird dringend von Verweisen auf KO-Nummern dieses Moduls abgeraten.
> Weitere kompatiblitätsbrechende Änderungen sind nicht auszuschließen, zum aktuellen Zeitpunkt jedoch nicht geplant. 

<!--
# Deterministic Finite Automaton (DFA) Module for OpenKNX

Implementation of state machines for KNX configurable via ETS.

By Cornelius Köpp 2023-09 -- 2025
-->

# OpenKNX-Modul zur Definition zustandsbehaftetem Verhalten auf Basis von  Deterministischen Endlichen Automaten (DEA)

Implementierung von Zustandsmodellen für KNX, konfigurierbar über die ETS.

Von Cornelius Köpp 2023-09 -- 2025

**Hinweis:** Dieses Modul kann (aktuell ausschließlich) mit der [OpenKNX StateEngine](https://github.com/OpenKNX/OAM-StateEngine/) genutzt werden.   



## Beschreibung <!-- (DE) -->
Dieses Modul erlaubt eine universelle Modellierung von zustandsabhängigem Verhalten:<br />
Jeder Kanal repräsentiert eine Automaten-Definition mit 32 verschiedenen Zuständen,
zwischen denen durch 8 verschiedenen Eingabeereignisse oder Ablauf eines zustandsabhängigen Timeouts gewechselt werden kann.
Über 4 Ausgangskanäle können zustandsspezifische Werte ausgegeben werden, mit verschiedenen zur Auswahl stehenden DPTs. Zus

Die Definition in der ETS erfolgt über eine (zwei-dimensionale) Zustandsübergangstabelle.<br />
Zur **Konfiguration in der ETS** siehe [Applikationsbeschreibung](doc/DFA_Applikationsbeschreibung.md)

## Grundidee in Anlehnung an gängige formale Definitionen:
> Informatikern wird das Modell bekannt und vertraut vorkommen; 
> bei genauerem Hinsehen werden allerdings gewisse Abweichungen deutlich um das Konzept an den Praxisbedarf anzupassen.

### Z&subset;{z<sub>1</sub>,..,z<sub>32</sub>} := Menge der Zustände
... wird als Teilmenge von DPT17.001 (Szenen: {0=Szene1,..,63=Szene64}) dargestellt.
In der aktuellen Implementierung eingeschränkt auf die Zustände 1 bis 32.
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

* #### X<sub>z</sub>={z<sub>1</sub>,..,z<sub>32</sub>} := Zustandsdirektaufruf

  Abhängig von der Konfiguration kann durch Eingabe in einen DPT17.001 Zustandseingang ein entsprechendes Symbol erzeugt werden. 

Das Eingabealphabet kann die Form X=X<sub>e</sub>&cup;X<sub>t</sub> oder X=X<sub>e</sub>&cup;X<sub>t</sub>&cup;X<sub>z</sub> aufweisen.

### d:Z&times;X&rarr;Z&cup;{undef} := Überführungsfunktion mit partieller Definition
... beschreibt für jede Kombination aus Ausgangszustand und Eingabesymbol ob, und wenn ja in welchen Folgezustand bei Eingabe gewechselt wird.
Nicht angegebene Zustandsübergabe werden ignoriert und führen nicht in einen Fehlerzustand.

Falls X<sub>z</sub>&subset;X (*Direktes Setzen von Zuständen ist erlaubt*), 
so gilt d(z,z<sub>i</sub>)=z<sub>i</sub> 
für alle z<sub>i</sub>&in;X<sub>z</sub>\\{z} (*ignorieren von erneutem Aufruf des bereits gesetzten Zustands*), 
oder sogar für alle z<sub>i</sub>&in;X<sub>z</sub> (*Neustart von bereits gesetzte, Zustand*).


### *Endzustände* 
... werden nicht explizit abgebildet.
Im Rahmen einer Nachverarbeitung kann jedoch leicht ermittelt werden, ob ein Zustand aus dieser Menge eingenommen wurde.
Es können Zustände definiert werden, die nicht mehr durch Eingabe eines Symbols verlassen werden. 

<!--
### Erweiterung: Zustandsspezifische Ausgabewerte

**o<sub>type</sub>:{1,2,3,4}&rarr;O&cup;{undef} := Ausgangsfunktion mit partieller Definition**

**o:Z&cup;{1,2,3,4}&rarr;O&cup;{undef} := Ausgangsfunktion mit partieller Definition**
-->

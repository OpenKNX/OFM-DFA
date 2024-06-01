# BETA-STATUS! (DE/German)
> Die vorliegende Version dient der Bereitstellung an Testnutzer.
>
> Obgleich die Implementierung auf einem bekannten formellen Modell aufbaut und möglichst kompakt gehalten wurde,
> und ein erster eingeschränkter Produktiv-Test erfolgt ist, besteht weiterhin ein erhöhtes Risiko von Fehlern.
> Vor allem in solchen Anwendungsszenarien die bei der Entwicklung nicht berücksichtigt wurden.
>
> Durch inkompatible Änderungen an der Konfiguration ist eine Übernahme der Konfiguration aus der ALPHA-Version nicht möglich.
> Die umgesetzten Änderungen zwischen den Versionen erfolgten jedoch auch mit dem Ziel zukünftigen kompatiblitätsbrechende Änderungen in der Produktiv-Nutzung möglichst überflüssig zu machen. 

# Deterministic Finite Automaton (DFA) Module for OpenKNX

Implementation of state machines for KNX configurable via ETS.

By Cornelius Köpp 2023-09

# OpenKNX-Modul für Deterministische Endliche Automaten (DEA)

Implementierung von Zustandsmodellen für KNX, konfigurierbar über die ETS.

Von Cornelius Köpp 2023-09



# Beschreibung (DE)
Das Modul bildet Zustandsmodelle basierend auf _deterministischen endlichen Automaten_ _(DEA; englisch DFA)_ ab.
Jeder Kanal repräsentiert einen solchen Automaten mit 32 verschiedenen Zuständen, und Zustandswechseln basierend auf 8 verschiedenen Eingabesymbolen/-ereignissen oder Ablauf eines Timeouts.
Über 4 Ausgangskanäle können individuelle Zustands-spezifische Werte ausgegeben werden. 
Die Definition in der ETS erfolgt über eine (zwei-dimensionale) Zustandsübergangstabelle. 

Zur **Konfiguration in der ETS** siehe [Applikationsbeschreibung](doc/DFA_Applikationsbeschreibung.md)

## Grundidee in Anlehnung an gängige formale Definitionen:
> Informatikern wird das Modell bekannt und vertraut vorkommen; 
> bei genauerem Hinsehen werden allerdings gewisse Abweichungen deutlich um das Konzept an den Praxisbedarf anzupassen.

**Z := Menge der Zustände** wird als Teilmenge von DPT17.001 (Szenen: {0=Szene1,..,63=Szene64}) dargestellt.
In der aktuellen Implementierung eingeschränkt auf die Szenen 1 bis 32.
Durch die Nutzung von Szenen können bei Erreichen eines Zustandes unmittelbar mehrere unabhängige Aktionen gleichzeitig ausgelöst werden.   

**z<sub>0</sub> &isin; Z := Startzustand** wird beim Einschalten (bzw. erstmaliger Aktivierung) als erster Zustand angenommen.

**X := Eingabealphabet** umfasst "Symbole" deren Eingabe (bzw. das damit verbundene Ereignis) eine Zustandsänderung bewirken kann.
In der aktuellen Implementierung eingeschränkt auf 8 Elemente, die durch Eingang von 1 oder 0 auf einem von bis zu 8 unabhängigen Eingabekanälen mit DPT1 ausgelöst werden.
Durch optionale Konfiguration als Eingabesymbolpaar kann z.B. ohne weiter Vorverarbeitung auf das Auftreten oder den Wegfall von erkannter Präsenz reagiert werden.

**d:Z&times;X&rarr;Z&cup;{undef} := Überführungsfunktion mit partieller Definition** beschreibt für jede Kombination aus Ausgangszustand und Eingabesymbol ob, und wenn ja in welchen Folgezustand bei Eingabe gewechselt wird.
Nicht angegebene Zustandsübergabe werden ignoriert und führen nicht in einen Fehlerzustand.

*Endzustände* werden nicht explizit abgebildet.
Im Rahmen einer Nachverarbeitung kann jedoch leicht ermittelt werden, ob ein Zustand aus dieser Menge eingenommen wurde.
Es können Zustände definiert werden, die nicht mehr durch Eingabe eines Symbols verlassen werden. 

### Erweiterung: Zustandsübergang bei Ausbleiben einer Eingabe innerhalb eines Zeitraums

**d<sub>t</sub>:Z&rarr;Z&cup;{undef} := Timeout-Überführungsfunktion mit partieller Definition**
beschreibt für jeden Zustand, ob in einen Folgezustand gewechselt werden soll, wenn innerhalb eines definierten Zeitintervalls keine Eingabe erfolgt (bzw. kein anderes Ereignis eingetreten) ist.  

**t:Z&rarr;T&cup;{undef} := Timeout-Dauer** (mit *t(z)=undef &hArr; d<sub>t</sub>=undef*) gibt die Wartedauer bis zum automatischen Zustandswechsel an. 


### Erweiterung: Zustandsspezifische Ausgabewerte

**o<sub>type</sub>:{1,2,3,4}&rarr;O&cup;{undef} := Ausgangsfunktion mit partieller Definition**

**o:Z&cup;{1,2,3,4}&rarr;O&cup;{undef} := Ausgangsfunktion mit partieller Definition**
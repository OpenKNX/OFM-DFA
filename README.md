# ALPHA-STATUS! (DE/German)
> Die vorliegende Version ist der erste veröffentliche Stand, zur Bereitstellung an Testnutzer.
>
> Obgleich die Implementierung auf einem bekannten formellen Modell aufbau und sehr kompakt gehalten wurde,
> besteht ein erhöhtes Risiko von Fehlern.
> Vor allem in solchen Anwendungsszenarien die bei der Entwicklung nicht berücksichtigt wurden.
>
> Die Art der Konfiguration ist Teil der Evaluation durch Testnutzer.
> Änderungen im Datenmodell sind möglich und könnten zu Inkompatiblität führen. 
> In diesem Fall ist eine Übernahme der Konfiguration womöglich nicht, oder nicht vollständig möglich.

# Deterministic Finite Automaton (DFA) Module for OpenKNX

Implementation of state machines for KNX configurable via ETS.

By Cornelius Köpp 2023-09

# OpenKNX-Modul für Deterministische Endliche Automaten (DEA)

Implementierung von Zustandsmodellen für KNX, konfigurierbar über die ETS.

Von Cornelius Köpp 2023-09



# Beschreibung (DE)
Das Modul bildet Zustandsmodelle basierend auf _deterministischen endlichen Automaten_ _(DEA; englisch DFA)_ ab.
Jeder Kanal repräsentiert einen solchen Automaten mit 16 verschiedenen Zuständen, und Zustandswechseln basierend auf 8 verschiedenen Eingabesymbolen/-ereignissen oder Ablauf eines Timeouts.
Die Definition in der ETS erfolgt über eine (zwei-dimensionale) Zustandsübergangstabelle. 

**Konfiguration in ETS** siehe [Applikationsbeschreibung](doc/DFA_Applikationsbeschreibung.md)

## Grundidee in Anlehnung an gängige formale Definitionen:
> Informatikern wird das Modell bekannt und vertraut vorkommen; 
> bei genauerem Hinsehen werden allerdings gewisse Abweichungen deutlich um das Konzept an den Praxisbedarf anzupassen.

**Z := Menge der Zustände** wird als Teilmenge DPT17.001 (Szenen: {0=Szene1,..,63=Szene64}) dargestellt.
In der aktuellen Implementierung  eingeschränkt auf die Szenen 1 bis 16.
Durch die Nutzung von Szenen können bei Erreichen eines Zustandes unmittelbar mehrere unabhängige Aktionen gleichzeitig ausgelöst werden.   

**z<sub>0</sub> &isin; Z := Startzustand** wird beim Einschalten (bzw. erstmaliger Aktivierung) als erster Zustand angenommen.

**X := Eingabealphabet** umfasst "Symbole" deren Eingabe (bzw. das damit verbundene Ereignis) eine Zustandsänderung bewirken kann.
In der aktuellen Implementierung eingeschränkt auf 8 Elemente, die durch Eingang von 1 und 0 auf eines von 4 KOs mit DPT1 ausgelöst werden.
Dadurch kann z.B. ohne weiter Vorverarbeitung auf Auftreten oder den Wegfall von erkannter Präsens reagiert werden.

**d:Z&times;X&rarr;Z&cup;{undef} := Überführungsfunktion mit partieller Definition** beschreibt für jede Kombination aus Ausgangszustand und Eingabesymbol ob, und wenn ja in welchen Folgezustand bei Eingabe gewechselt wird.
Nicht angegebene Zustandsübergabe werden ignoriert und führen nicht in einen Fehlerzustand.

*Endzustände* werden nicht explizit abgebildet.
Im Rahmen einer Nachverarbeitung kann jedoch leicht ermittelt werden, ob ein Zustand aus dieser Menge eingenommen wurde.
Es können Zustände definiert werden, die nicht mehr durch Eingabe eines Symbols verlassen werden. 

### Erweiterung: Zustandsübergang bei Ausbleiben einer Eingabe innerhalb eines Zeitraums

**d<sub>t</sub>:Z&rarr;Z&cup;{undef} := Timeout-Überführungsfunktion mit partieller Definition**
beschreibt für jeden Zustand, ob in einen Folgezustand gewechselt werden soll, wenn innerhalb eines definierten Zeitintervalls keine Eingabe erfolgt (bzw. kein anderes Ereignis eingetreten) ist.  

**t:Z&rarr;T&cup;{undef} := Timeout-Dauer** (mit *t(z)=undef &hArr; d<sub>t</sub>=undef*) gibt die Wartedauer bis zum automatischen Zustandswechsel an. 

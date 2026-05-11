# (upcoming with new xml version)
 
* Fix: ParameterType-Names were not in sync with id
  * DocText255, DfaInputLogicNumberOptional
  * Merged Part: DfaChoiceStateENUM (not included in resulting XML)

# (upcoming)

* Fix #72: Show Startup and do not include "NO_TIMEOUT" in Channel-State Response
* Cleanup/Fix: Misspelling call of `openknx.console` method `writeDiagenoseKo` -> `writeDiagnoseKo`
* Minor Cleanup: Compile-Time-Checks
* Doc: Minor Fixes


# 2026-04-04 v0.8.2 ("Bedingter Startzustand + Input Fixes")

* Fix #65: Für Symbol-Eingänge deren *Eingabekanal* als *Bestehendes KO* konfiguriert ist, wurde die KO-Nummer mit Faktor 2 multipliziert.
  * Hinweis: Dieser Fehler betrifft alle bislang veröffentlichten Versionen  
* Fix #66: Die Auslösung des Eingabesymbols T funktionierte nicht, oder hätte ein vollkommen undefiniertes Verhalten aufgewiesen.
  * Hinweis: Der Fehler bestand seit Einführung dieses Eingangs in v0.7.0. Eine Auslösung über das Diagnose-Objekt war möglich.
* Fix: Beim Laden der beim Geräte-Shutdown gespeicherten Modul-Kanal-Daten wurde nicht korrekt geprüft, ob der Kanal zuvor inaktiv war.
  * Dies hätte bei erlaubtem Pausieren dazu geführt, dass der Automat (unabhängig von der gewählten Konfiguration) pausiert startet, nachdem die Konfiguration von Inaktiv auf Aktiv geändert wurde
  * Hinweis: Dieser Fehler betrifft alle bislang veröffentlichten Versionen
* Fix: Rekonstruktionsfunktion hätte zu fehlerhaftem Rest-Timeout führen können, wenn das Speichern zeitnah zum, oder nach dem Timeout erfolgt
  * Eine Fortsetzung hätte mit extrem langem Timeout oder unter Ignorieren des gespeicherten Timeouts erfolgen können 
  * Hinweis: Dieser Fehler betrifft alle bislang veröffentlichten Versionen


# 2026-03-29 v0.8.1 ("Bedingter Startzustand")

* OpenKNX Update: Anpassungen für Producer-Versionen &gt;= v4.2.7
* Fix Changelog v0.8.0
* Dokumentation: Readme


# 2026-03-11 v0.8.0 ("Bedingter Startzustand")

* Feature: **Bedingte Zustandsübergänge können nun zur Ermittlung des Startzustands genutzt werden**
  * Ergänzend muss in diesem Fall ein Zustand angegeben werden, der genutzt wird, falls die Auswahl scheitert  
* Refactor: Verarbeitung von Zustandsübergängen wurde in der Struktur angepasst zur Unterstützung bedingter Startzustände
  * Phase 1: Ermittlung des Folgezustands (Direkte Rückgabe zur Vereinfachung Kontrollfluss)
  * Phase 2: Evaluation von bedingten Übergängen
  * Ersetzen von Zustandsaufrufen `setState(...)` durch `transfer(..)`
    * Direktes Setzen von Zuständen über KO oder Konsole
    * Erster Start des Automaten
* ETS-Applikation:
  * Überarbeitete **KO-Bezeichner (Name und Objektfunktion) entsprechend einheitlicher Konventionen für OpenKNX-Module**, inklusive KO-Baum
  * Überarbeiteter Modul-Titel
  * Context-Hilfe
    * Fix(Typo)
    * Hinweis auf Sichtbarkeit der Option im Hilfetext (der nur unter dieser Bedingung in der Kontexthilfe sichtbar ist)
* Feature: Diagnose-Kommando `dfa all` zur Statusübersicht aller aktiv konfigurierter Automaten
* Dokumentation:
  * Fix: Inhaltsverzeichnis in Applikationsbeschreibung
  * Fix und Erweiterung: Readme
* Kleinere Verbesserungen, ohne funktionale Änderungen:
  * Fixes: Bool statt uint8_t, Naming, Format, Define
  * Kommentare
  * Log-Ausgaben
  * Nutzung von Define-Constanten
  * Modul kann prüfen welche Automaten aktiviert sind
  * Abhängigkeit von Logikmodul deklariert (mit neuer Erweiterung aus Producer Version 4.0)


# 2025-11-09 v0.7.1 ("Bedingte Zustandsübergänge")

* Fix: Verarbeitung von Kommandos `*TEST*` und `history` auch ohne in der ETS aktivierte Steuerung
* Refactor: Kommando-Vorverarbeitung
* Doc: Hinweise und Tipps zur Modellierung & Nutzung (FAQs)
* Doc (Entwicklung): Konzept für Historien-Darstellung/Ausgabe
* Doc/Fix: Changelog v0.7.0


# 2025-11-02 v0.7.0 ("Bedingte Zustandsübergänge")

* Feature: Bedingte Zustandsübergänge (Verwandt, aber nicht identisch, mit UML "Choice" Pseudo-Zuständen)
  * Neuer Parameter-Block "Bedingte Übergänge"
  * Diagnose-Kommando `dfaNN choice=x` zum direkten Aufruf von bedingten Übergängen (unabhängig vom aktuellen Zustand)
* Refactor:
  * Interne Verarbeitung von Timeouts durch `transfer('T')`
  * Neue 3-phasige Verarbeitung von Zustandsübergängen (Voraussetzung für bedingte Zustandsübergänge)
  * Verschiebung von Constanten in eine DfaConstants.h
  * Code-Region definiert
* Feature: Eingabe-Symbol/Eingang T zum direkten Auslösen von Timeout 
* Fix/Verbesserung ETS-Applikation:
  * Applikationsbeschreibung und Kontexthilfen: "Kanal verwenden?", "Ausgabe", "Ausgang n", "Pausieren erlauben?"
  * Tabelle zur Definition der Ausgänge auf 100% Breite
  * Info-Text für Text-Ausgänge
  * Info-Text für Rekonstruktion
* Fix #57: Überlappende Parameter für sich sichtbare Kanäle und Diagnose mit Schriftzugriff (ohne bekannte Auswirkungen bei der Ausführung)
* OpenKNX Update: Unterstützung für OpenKNXproducer 3.12.2
* Doc: Hinweise zur Integration in OpenKNX OAMs
* Feature-Vorschau (Unvollständige Umsetzung!): Historien-Funktion zur Diagnose (Kommando `dfaNN history`)
* Bereinigung ETS-Applikation/XML<br/>u.A.:
  * Reihenfolge von Parameter-Definitionen
  * Vereinfachung Integration von Parts
  * Entfernen von Dummy-KOs (mit aktueller Producer-Version nicht mehr benötigt)
* Feature (Entwicklung): Kommando `dfaNN *TEST*` für Testing (nur in Builds mit `OPENKNX_DEBUG`)


# 2025-09-22 v0.6.1 ("Diagnose-Ausgabe-Fixes")

* Fix #52: Die Diagnose-Kommandos haben auch beim Aufruf von Konsole aufs KO geschrieben
* Fix #51: Das Kommando `dfaNN` lieferte keine (klare) Information, ob der Kanal aktiv ist und läuft


# 2025-09-18 v0.6.0 ("Detailverbesserungen und -fixes")

* Fix #48: Diagnose-Kommandos im Modul wurden auch angezeigt und verarbeitet, wenn das Gerät nicht konfiguriert ist
* Fix ETS-App XML: Falsche Zell-Koordinates for Eingangs-Paar-Parameter. Dies hatte keine bekannten Auswirkungen in der ETS5.7/6.3
* Verbesserung ETS-App: Detailanpassung FunctionText von KO
* OpenKNX Update: Anpassungen für neue Producer-Versionen


# 2025-07-11 v0.5.0 (mit "Output Fixes")

* **Fix #39: Für Ausgänge mit Typ DPT9 und DPT14** wurden (i.d.R. deutlich erkennbar) falsche Werte gesendet
  * Möglicher Workaround für ältere Versionen: Ausgabe des identischen Bitmusters über gleichlangen Ganzzahltyps (DPT7/12)
* **Fix #40: Für Ausgänge mit Typ DPT8 (uint16) und DPT13 (uint32)** wurden negative Werte fehlerhaft verarbeitet und als 0 auf den Bus gesendet 
  * Möglicher Workaround für ältere Versionen: Ausgabe des identischen Bitmusters über gleichlangen Ganzzahltyps (DPT7/12)
* Fix: Anzeigereihenfolge von KOs in Baumansicht unter dem Gerät korrigiert/an KO-Nummern angepasst
* Dokumentation
  * Ergänzung von Beispielen 
  * Ergänzung von Kommandos zur Nutzung über das Diagnose-Objekt (und die serielle Konsole) 
  * Kleinere Detailverbesserungen
* Refactoring: Ausgangsverarbeitung  


# 2025-03-01 v0.4.0-dev-Beta

* (BREAKING ConfigTransfer) Reduktion von 32 auf 16 Zuständen als Standard, 
  zur Vermeidung sehr langen Programmierzeiten bei regelmäßig vollständiger Programmierung
  und Verbesserung Geschwindigkeit in ETS
* (BREAKING KO-Numbers) Neuordnung KOs inkl. Vorbereitung für zukünftige Ergänzungen ohne erneute Verschiebung
* Fix/Verbesserung ETS-Applikation:
  * Kopf der Tabelle Zustände und Übergangsfunktion überarbeitet (zur Vermeidung leerer Zellen) 
  * Spaltenbreite und Options-Beschriftung für Ausgangs-Sendestrategie
  * Ausgänge: Nutzung generischer DPTs statt Subtypen (DPST) mit Einheit


# 2025-02-16 v0.3.0-Beta

* Fix: Rekonstruktion nur von gültigem Zustand (Fall trat auf, falls der Automat vor dem Neustart noch nicht gestartet war)
* Erweiterung/Fix: Pausieren-Status wird nun bei Rekonstruktion berücksichtigt 
* Erweiterung Sendeverhalten bei Rekonstruktion:
  * Zwei zusätzliche Optionen zur Steuerung des Ausgangs-Sendeverhalten.
    Für Wert-Änderung und Zustands-Änderung kann ein Senden nach Rekonstruktion nun unterdrückt werden, 
    da dies einem Verhalten ohne Neustart näher kommt.
* Fix/Verbesserung direkte Zustands-Steuerung über KOs:
  * Fix: Kombiniertes Zustands-KO
    * Erneutes Setzen von aktuellem Zustand ignorieren
    * Rücksetzen des KO-Wertes auf tatsächlichen Zustand, nach Telegramm-Eingang zur Vermeidung von Ausgabe ungültiger Zustände
    * Update-Flag entfernt zur Vermeidung von Zustandsänderung durch Read-Response-Telegramme
  * Erweiterung für getrennte KOs zur Ausgabe und Setzen von Zustand
    * Konfigurierbares Verhalten für erneutes Setzen von aktuellem Zustand ignorieren (bislang immer Neustart des Zustands)
* Anpassungen ETS-Applikation:
  * Überarbeitung der Konfiguration zur Rekonstruktion und Pausieren 
  * Einrückung
  * Optische Verbesserung: Breite und Position von Checkboxen für kombinierte Eingänge
  * Fix: Beschränkung der KO-Auswahl für Symboleingänge auf Intervall mit tatsächlich vorhandenen KO-Nummern
  * OpenKNX-Grundstruktur (Basiseinstellungen als erste Seite)
  * Optimierung Beschriftungstexte basierend auf User-Test
  * Optische Verbesserung: Erzwinge feste Breite für erste Spalte von Eingangskonfiguration
* Update Applikationsbeschreibung, Kontext-Hilfe und Readme
* Fix/Optimierung:
  * Restore von inaktiven Kanälen unterlassen
  * Berücksichtigung von `openknx.freeLoopTime()` zur Begrenzung der Modullaufzeit
* Nur Debug:
  * Fix: Ausgabe detaillierte Laufzeitstatistik des Moduls auf Kanal-Ebene
  * Optimierung: Anpassung Log-Level für Debug-Ausgaben
* Refactoring, Dokumentation, Cleanup


# 2024-07-01 v0.2.0-Beta (internal only)

* Fix: Zustände ohne Timeout wurden mit sehr langem Timeout rekonstruiert 
* Abbildung der sichtbaren DFA-Kanäle im Gerätespeicher
* Eingangs-Trigger
  * Fix: Parameter-Wert-Ermittlung (Bislang kein Problem aufgetreten)
  * Bereinigung Implementierung und Vorbeugen zukünftiger Fehler
* Kompatibilität: Erweiterung von Defines um das Präfix DFA_ 
* Diverse Bereinigungen im Code (Firmware und ETS-App)
* Kommandos über Diagnose-Objekt und Konsole
  * Bereinigung der Implementierung
  * Neue Kommandos zum Setzen von Zustand <!-- (`dfaNN state=SS`) --> und Eingabe von Symbolen <!-- (`dfaNN symbol=X`) -->
  * Ändernde Kommandos nur Dianose-KO nur erlauben, wenn in ETS konfiguriert


# 2024-04-25 DEV Beta-Version (PROD-Test, internal only)

* Verbesserung/Erweiterung: Neue Implementierung für flexibles Sendeverhalten der Ausgänge
* Fix: Timeout-Restore
* Verbesserung ETS-App: Darstellung der DPT-Auswahl mit DPT-Nummer am Anfang
* Diverse Bereinigungen im Code (Firmware und ETS-App)
* Änderung: Umbenennung von Parametern
* OpenKNX Update ETS-App: Neue XML-Struktur
* Erweiterung: Applikationsbeschreibung
* Fix ETS-App: Wertangabe von ColorType-Values
* Verbesserung ETS-App: Nur 2 DFA-Kanäle anzeigen in der Standardeinstellung
* Verbesserung ETS-App/OpenKNX: '... (mehr)'-Block zur einfachen Anpassung/Erweiterung der sichtbaren DFA-Kanäle
* Verbesserung ETS-App/OpenKNX: Integration von Icons für ETS-Channels und Blocks
* Verbesserung ETS-App: Integration Kontexthilfe
* (BREAKING) Kompatiblitätsbrechende Änderung:
  * Änderung Parameter-Codierung zur Schaffung von Optimierungsoptionen beim Speicherlayout
  * Bereinigung und Umstellung Parameter-Namen u.A. mit Blick auf Config-Transfer
* Update Hinweise in README und Applikation von ALPHA auf BETA
* Verbesserung ETS-App: Update Info-Block


# 2023-12-30 Second Alpha-Version (PROD-Test, internal only)

* Erweiterung: Ausgaben und Setzen von Status kann alternativ auch in gemeinsamen KO erfolgen
* Verbesserung ETS-App: Leere Standardwerte für Bezeichnungen von Eingabesymbolen und Zuständen
* Verbesserung ETS-App: Vergrößerung Spaltenbreite in Tabellen (zur Vermeidung Probleme bei HiDPI-Ausgabe)
* OpenKNX Update: Ausgabe der Modul-Version
* Erweiterung: Bis zu 8 unabhängige Eingabekanäle (zur Erzeugung von Eingabesymbolen)
  * Konfiguration einzeln oder als Paar
  * Einstellbare Eingabekanäle: Eigenes KO bereitstellen, Vorhandenes KO, Logik-Kanal-Ausgang, Inaktiv (Standard)  
  * Auslösebedingung einstellbar bei Einzelkanälen (0, 1, egal)
* Erweiterung: Konfigurierbare Startverzögerung je Kanal (DFA-Automatendefinition)
* Experimentelle Erweiterung: Optionale Rekonstruktion des Zustands nach Neustart 
  * Speichern des Zustands vor erkennbarem Neustart
* (BREAKING) Kompatibilitätsbrechende Änderung der ETS-App: 
  * Umstellung Parameter-IDs auf größeren Adressraum als Basis für Erweiterungen
  * Anpassung Codierung für schnellere (partielle) Geräte-Programmierung
* Erweiterung: Bis zu 4 Ausgänge (O1,..,O4) mit individuellen Werten und Sendeverhalten je Zustand
  * Unterstützung von verschiedenen numerischen DPTs (1.x, 2.x, 5.x, 5.001, 6.x, 7.x, 8.x, 9.x, 12.x, 13.x, 14.x, 17.001, 232.600) für alle Ausgänge
  * Unterstützung von Text (DTP16.001) für Ausgang O4
* (ENTWURF) Erweiterung: Timeout-Reset `<<` in Überführungsfunktion
* Erweiterung: 32 statt 16 Zustände
* Verbesserung ETS-App: Überführungsfunktion auf eigener Seite
* Verbesserung ETS-App: Kommentarfeld
* Verbesserung ETS-App: Ausblenden von Folgezuständen für inaktive Eingabesymbole
* Verbesserung ETS-App: Eingabesymbole inaktiv als Standard 
* Verbesserung ETS-App: Verbesserte Konfiguration der Zuordnung von Eingabekanälen und Eingabesymbolen
* Verbesserung ETS-App: Einstellbare Anzahl sichtbarer DFA-Kanäle


# 2023-10-09 First Alpha-Version (internal only)

* Working Stable implementation for demonstration and first feedback from users
# 2023-12-30 Second Alpha-Version (PROD-Test)
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
* (BREAKING) Kompatiblitätsbrechende Änderung der ETS-App: 
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
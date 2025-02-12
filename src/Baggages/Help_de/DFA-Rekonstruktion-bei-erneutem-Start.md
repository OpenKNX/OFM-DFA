### Rekonstruktion bei erneutem Start


Bei Unterbrechung des Gerätebetriebs endet auch die Verarbeitung der definierten Automaten.
Mit der Rekonstruktion wird *versucht* die Verarbeitung nach dem Neustart fortzusetzen,
basierend auf dem letzten bekannten Zustand, dessen Aufrufzeitpunkt und ggf. letztem Ausführungsstatus.

***Technische Limitation:***
Die Rekonstruktion erfordert das erfolgreiche Speichern des momentanen Zustands und des Rest-Timeouts unmittelbar bei Beendigung der Verarbeitung.
Dies kann allerdings *nicht* immer gewährleistet werden:

* Ein Neustart durch Programmiervorgang kann zuverlässig erkannt werden
* Die Erkennung einer unterbrochenen Stromversorgung setzt eine entsprechende Hardwareausstattung voraus
* Ein Neustart per Reset-Taste kann *nicht* erkannt werden.



Einstellungswerte:

* **nein (immer Starten wie konfiguriert):**      Der Zustand vor einem Neustart hat keinen Einfluss. Nach einem Neustart wird immer mit dem konfigurierte Startzustand begonnen.
* **Fortsetzen, aber Timeout neu beginnen:**      Der zuletzt gespeicherte Zustand (sofern vorhanden) wird anstelle des regulären Startzustandes genutzt. Falls für diesen einen ein Timeout definiert ist, so wird dieser neu gestartet.
* **Fortsetzen mit gespeichertem Rest-Timeout:**  Der zuletzt gespeicherte Zustand (sofern vorhanden) wird anstelle des regulären Startzustandes genutzt. Falls für diesen einen ein Timeout definiert ist, so wird dieser um die bereits bis zur Speicherung des Zustands abgelaufene Zeit vermindert.

### Zustand bei Neustart rekonstruieren?


Bei Unterbrechung des Gerätebetriebs endet auch die Verarbeitung der definierten Automaten.
Mit der Zustandsrekonstruktion kann *versucht werden* die Verarbeitung nach dem Neustart fortzusetzen, 
basierend auf dem letzten bekannten Zustand und dessen Aufrufzeitpunkt. 

***Technische Limitation:*** 
Die Rekonstruktion erfordert das erfolgreiche Speichern des momentanen Zustands und des Rest-Timeouts unmittelbar bei Beendigung der Verarbeitung. 
Dies kann allerdings *nicht* immer gewährleistet werden:

* Ein Neustart durch Programmiervorgang kann zuverlässig erkannt werden
* Die Erkennung einer unterbrochenen Stromversorgung setzt eine eine entsprechende Hardwareausstattung voraus
* Ein Neustart per Reset-Taste kann *nicht* erkannt werden. 



Einstellungswerte:

* **nicht speichern (immer Startzustand nutzen):** Der Zustand vor einem Neustart hat keinen Einfluss. Nach einem Neustart wird immer mit dem konfigurierte Startzustand begonnen.
* **gespeicherten Zustand neu starten:**           Der zuletzt gespeicherte Zustand (sofern vorhanden) wird anstelle des regulären Startzustandes genutzt. Falls für diesen einen ein Timeout definiert ist, so wird dieser neu gestartet.
* **gespeicherten Zustand fortsetzen:**            Der zuletzt gespeicherte Zustand (sofern vorhanden) wird anstelle des regulären Startzustandes genutzt. Falls für diesen einen ein Timeout definiert ist, so wird dieser um die bereits bis zur Speicherung des Zustands abgelaufene Zeit vermindert.

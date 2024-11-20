### Zustand bei Neustart rekonstruieren?

Mit den angebotenen Funktionen kann *versucht werden* den Einfluss einer unterbrochenen Ausführung des Automaten zu reduzieren.

***Technische Limitation:*** 
Eine korrekte Rekonstruktion kann nur erfolgen, 
wenn der Zustand unmittelbar vor dem Neustart gespeichert wurde.
Details siehe **[Zustandsrekonstruktion nach Neustart](#zustandsrekonstruktion-nach-neustart)**. 

* **nicht speichern (immer Startzustand nutzen):** Der Zustand vor einem Neustart hat keinen Einfluss. Nach einem Neustart wird immer mit dem konfigurierte Startzustand begonnen.
* **gespeicherten Zustand neu starten:**           Der zuletzt gespeicherte Zustand (sofern vorhanden) wird anstelle des regulären Startzustandes genutzt. Falls für diesen einen ein Timeout definiert ist, so wird dieser neu gestartet.
* **gespeicherten Zustand fortsetzen:**            Der zuletzt gespeicherte Zustand (sofern vorhanden) wird anstelle des regulären Startzustandes genutzt. Falls für diesen einen ein Timeout definiert ist, so wird dieser um die bereits bis zur Speicherung des Zustands abgelaufene Zeit vermindert.

### Direktes Setzen von Zustand erlauben?

Optional kann eine Änderung des Zustands, unabhängig vom aktuellen Zustand, den Eingabesymbolen oder dem Timeout erfolgen.

* **nein**:                                    Der Zustand wechselt ausschließlich durch Eingabe eines Symbols, oder Timeout.
* **über separates KO**:                       Es wird ein weiteres KO eingeblendet, über das der aktuelle Zustand unmittelbar überschrieben werden kann. Zustände außerhalb des Definitionsbereichs (Szene 1 bis 16) werden ignoriert.
* **über gemeinsames KO mit Zustandsausgabe**: Der aktuelle Zustand kann über das KO mit Ausgabe des Momentan-Zustandes überschrieben werden. Zustände außerhalb des Definitionsbereichs (Szene 1 bis 16) werden ignoriert.

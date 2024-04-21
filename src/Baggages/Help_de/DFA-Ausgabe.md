### Ausgabe

Es können bis zu 4 Ausgabekanäle (O1, O2, O3, O4) konfiguriert werden, für die bei Aktivierung jeweils ein KO mit gewähltem Datentyp bereitgestellt wird.
Es stehen gängige DPTs (1,2,5,5.001,6,7,8,9,12,13,14,17,232.600) zur Auswahl, sowie *ausschließlich* für O4 auch Text (DPT16.001).
Für jede Kombination aus Zustand und Ausgang kann ein Wert und ein Sendeverhalten definiert werden.

#### Bezeichnung/Kommentar (je Ausgabekanal)

Hier sollte zur Dokumentation eine individuelle kurze Beschreibung des jeweiligen Ausgabekanal hinterlegt werden.
Der Wert wird ausschließlich in der ETS verwendet (Als Beschriftung von Konfigurationsseiten und KOs) und hat keinen Einfluss auf das Geräteverhalten.

#### Datentyp (je Ausgabekanal)

***DPT17.001 Textausgabe:*** Die Ausgabe von 14-Byte-Texten ist angesichts des deutlich höheren Speicherbedarfs nur auf den letzten Ausgabekanal verfügbar.

### Verzögerung nach Gerätestart

Nach dem Neustart ist der Automat zunächst inaktiv und wird erst nach Ablauf der Verzögerungszeit (zusätzlich zur Startverzögerung im Gerät) auf Ereignisse (wie z.B. Eingaben, Setzen des Zustand) reagieren und einen ggf. definierten Timeout starten.

> Mit dieser Einstellung kann z.B. verhindert werden, dass beim Neustart des Bus durch initial versendete Telegramme Zustandswechsel verursacht werden.

> Durch Definition eines eigenen Startzustandes mit Timeout kann ein ähnliches, aber nicht identisches, Verhalten erzielt werden:
> Ein Setzen des Zustandes wäre dann jedoch sofort möglich, sowie auch eine individuelle Definition auf welche Eingabesymbole reagiert werden und welche nicht.
> In Kombination mit einer Rekonstruktion des letzten Zustands ist dann jedoch keine besondere Behandlung des Startverhaltens möglich. 



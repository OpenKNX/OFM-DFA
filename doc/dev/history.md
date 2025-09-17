# Historien-Funktion (Entwurf)

Ausgabe des "Pfades" (Zustände und Übergänge) bis zum aktuellen Zustand zur Diagnose.

Kommando: `dfaNN history`

* Zustände können alle erlaubten sein von 1 bis 16. zusätzlich muss abbildbar sein, wenn der Automat noch nicht gestartet wurde.
* Übergänge müssen nicht nur die regulären Symbole abbilden, sondern auch andere Ereignisse die Einfluss haben können auf den Automatenzustand bzw. darüber hinaus.
  * u.A. auch initialer Start des Gerätes, Start/Stop, Rekonstruktion, Direktaufruf von Zuständen, sowie ggf, auch Direktaufruf von bedingten Übergängen 

## Beispiel

gesamtsequenz: (nicht vollständig abbildbar)
```
1T4=5A5B5B13A13C14C14C14C15
```

Historie ab Beginn mit Verlängerung:
```
1
1T4
1T4=5
1T4=5A5
1T4=5A5B5
1T4=5A5B5B13
1T4=5A5B5B13A13
1T4=5A5B5B13A13C14
1T4=5A5B5B13A13C14C14
1T4=5A5B5B13A13C14C14C14
1T4=5A5B5B13A13C14C14C14C15
```


### Reduziert auf 14 Byte:
* Beginn immer mit Zustandsnummer
* Nachfolgend abwechselnd Symbol/Ereignis und Folgezustand
  * Symbole 'A'..'H'
  * Symbol 'T'
  * Symbol '<'
  * Direktaufruf Zustand
    * '=' für erfolg
    * '!' nicht ermöglichen, ggf. auch länger als '(nn)'
  * Direktaufruf *Bedingter Zustandsübergang*
    * 'a'..'p'

#### Ausgabe auf 14 Byte optimiert:
```
1
1T4
1T4=5
1T4=5A5
1T4=5A5B5
1T4=5A5B5B13
~4=5A5B5B13A13
5A5B5B13A13C14
~5B13A13C14C14
13A13C14C14C14
13C14C14C14C15 ende
```


#### Ausgabe auf 14 Byte vereinfacht (2 ziffern zustand):

```
01T04=05A05B05B13A13C14C14C14C15 volle Länge
```

```
01
01T04
01T04=05
01T04=05A05
01T04=05A05B05
04=05A05B05B13
05A05B05B13A13
05B05B13A13C14
05B13A13C14C14
13A13C14C14C14
13C14C14C14C15 ende
```

#### Ausgabe auf 14 Byte kompakt mir nur Anfangs und Endzustand:

```
01T04=05A05B05B13A13C14C14C14C15 volle Länge
```

```
01T=05ABBACCCC15
1T=5ABBACCCC15
```
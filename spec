A : set canal => @
B : set valeur => ENTER
C : clear (univers + variables canal, valeur...)
D : mettre à une valeur plusieurs canaux conjoints/selection de plusieurs canaux disjoints(jusqu'à 16)
=> switch ?
- : met 0 le canal en cours et à 100% le canal précédent => PREV
+ : met 0 le canal en cours et à 100% le canal suivant => NEXT


examples utilisations :

1/ Mettre le canal 103 à la valeur 50% (127)
103 :numéro canal
A 	: valider canal
127 : valeur pour le canal
B 	: Validation

2/ fonction THRU => Mettre à 100% (255) les canaux conjoints 12 (inclu) à 150 (inclu)
switch position a
D
12
+
150
A
255
B

2/ Mettre à 10% (26) les canaux 10, 77, 146
switch position b
D
10
+
77
+
146
A
26
B

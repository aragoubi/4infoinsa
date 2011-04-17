/*
TP 2 - Contraintes logiques
Graignic Guillaume
Addar Mehdi
*/

/* Pour les connecteurs logiques et les contraintes portant sur des variables entieres (dont les operateurs debutent par #) */
:- lib(ic).
/* Pour les contraintes symboliques (dont les operateurs debutent par & */
:- lib(ic_symbolic).

/* 1 - Puzzle logique */
/* Question 1.1 - Enonce */
/* Question 1.2 - Modelisation */

/* Question 2.1 - Domaines symboliques */
:- local domain(pays(angleterre,espagne,ukraine,norvegien,japonais)).
:- local domain(couleur(rouge,vert,blanc,bleu,jaune)).
:- local domain(boisson(cafe,the,lait,jusorange,eau)).
:- local domain(voiture(bmw,toyota,ford,honda,datsun)).
:- local domain(animal(chien,serpent,renard,cheval,zebre)).

/* Question 2.2 - domaines_maison */
domaines_maison(m(Pays,Couleur,Boisson,Voiture,Animal,_)) :- 
	Pays &:: pays,
	Couleur &:: couleur,
	Boisson &:: boisson,
	Voiture &:: voiture,
	Animal &:: animal.

/* Question 2.3 - rue */
rue([m(P1,C1,B1,V1,A1,N1),m(P2,C2,B2,V2,A2,N2),m(P3,C3,B3,V3,A3,N3),m(P4,C4,B4,V4,A4,N4),m(P5,C5,B5,V5,A5,N5)]):-
	domaines_maison(m(P1,C1,B1,V1,A1,N1)),
	domaines_maison(m(P2,C2,B2,V2,A2,N2)),
	domaines_maison(m(P3,C3,B3,V3,A3,N3)),
	domaines_maison(m(P4,C4,B4,V4,A4,N4)),
	domaines_maison(m(P5,C5,B5,V5,A5,N5)),
	N1 = 1,
	N2 = 2,
	N3 = 3,
	N4 = 4,
	N5 = 5,
	ic_symbolic:alldifferent([P1,P2,P3,P4,P5]),
	ic_symbolic:alldifferent([C1,C2,C3,C4,C5]),
	ic_symbolic:alldifferent([B1,B2,B3,B4,B5]),
	ic_symbolic:alldifferent([A1,A2,A3,A4,A5]).

/* Question 2.4 - ecrit_maisons */
ecrit_maisons(L) :-	( foreach(m(P,C,B,V,A,N),L)
				do
				write("Maison "),writeln(N),
				write("Pays: "),write(P),write(", "),
				write("Couleur: "),write(C),write(", "),
				write("Boisson: "),write(B),write(", "),
				write("Voiture: "),write(V),write(", "),
				write("Animal: "),writeln(A)
			).

/* Question 2.5 - getVarList */
getVarList(Rue,Liste) :-( foreach(m(P,C,B,V,A,N),Rue), fromto([], In, Out, Liste)
				do
				Out = [P,C,B,V,A,N | In]
			).

/* labeling_symbolic */
labeling_symbolic([]).
labeling_symbolic([ Elem | List ]) :-
	ic_symbolic:indomain(Elem),
	labeling_symbolic(List).

/* Question 2.6 - resoudre */
resoudre(Rue) :-
	rue(Rue),
	contraintes(Rue),
	getVarList(Rue,Liste),
	labeling_symbolic(Liste),
	ecrit_maisons(Rue).


contraintes(Rue) :-
 ( foreach(m(P,C,B,V,A,N),Rue)
	do
		(P &= angleterre) #= (C &= rouge),
		(P &= espagne) #= (A &= chien),
		(C &= vert) #= (B &= cafe),
		(P &= ukraine) #= (B &= the),
		/* Maison verte à droite de la maison blanche */
		(foreach(m(P1,C1,B1,V1,A1,N1),Rue),param(C,N)
			do 
				((C &= vert) and (C1 &= blanc)) => (N1 #= N+1)
		),
		(V &= bmw) #= (A &= serpent),
		(C &= jaune) #= (V &= toyota),
		(B &= lait) #= (N #= 3),
		(P &= norvegien) #= (N #= 1),
		/* Conducteur de la ford habite à coté de la personne qui possède un renard 
		(V &= ford) #= (N &= 1), */
		/* Conducteur de la Toyota habite à coté de la maison qui possède un cheval */
		
		(V &= honda) #= (B &= jusorange),
		(P &= japonais) #= (V &= datsun)
		/* Le norvegien habite à coté de la maison bleu 
		(P &= norvegien) #= (V &= datsun), */	
).
			












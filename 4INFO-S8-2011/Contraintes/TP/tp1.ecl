/* Graignic Guillaume
Addar Mehdi
*/

:- lib(ic).
:- lib(ic_symbolic).

/* 1 - Des Contraintes sur les arbres */
/* Question 1.1 */

coulVoiture(rouge).
coulVoiture(vert(clair)).
coulVoiture(gris).
coulVoiture(blanc).

coulBateau(vert(_)).
coulBateau(noir).
coulBateau(blanc).

choixCouleur(CouleurBateau, CouleurVoiture) :- 
	CouleurBateau=CouleurVoiture,
	coulVoiture(CouleurVoiture),
	coulBateau(CouleurBateau).

/*
[eclipse 18]: 7.
choixCouleur(X, Y).

X = vert(clair)
Y = vert(clair)
Yes (0.00s cpu, solution 1, maybe more) ? ;

X = blanc
Y = blanc
Yes (0.00s cpu, solution 2)
[eclipse 19]:  
*/

/* Question 1.2 */
/* Prolog peut être considéré comme un solveur de contraintes parceque */

/* Question 1.3 */
isBetween(Var,Var,_).
isBetween(Var,Min,Max):-
	Min \= Max,
	MinN is Min+1,
	isBetween(Var,MinN,Max).

/*
[eclipse 28]: 22.
isBetween(X, 2, 7).

X = 2
Yes (0.00s cpu, solution 1, maybe more) ? ;

X = 3
Yes (0.00s cpu, solution 2, maybe more) ? ;

X = 4
Yes (0.00s cpu, solution 3, maybe more) ? ;

X = 5
Yes (0.00s cpu, solution 4, maybe more) ? ;

X = 6
Yes (0.00s cpu, solution 5, maybe more) ? ;

X = 7
Yes (0.00s cpu, solution 6, maybe more) ? ;

No (0.00s cpu)
*/

/* Question 1.4 */
commande(NbResistance, NbCondensateur) :-
	isBetween(NbResistance,5000,10000),
	isBetween(NbCondensateur,9000,20000),
	NbResistance >= NbCondensateur.
/*
[eclipse 34]: 33.
commande(X, 9998).

X = 9998
Yes (8.39s cpu, solution 1, maybe more) ? ;

X = 9999
Yes (8.40s cpu, solution 2, maybe more) ? ;

X = 10000
Yes (8.40s cpu, solution 3, maybe more) ? ;

No (8.41s cpu)
*/

/* Question 1.5 */

/*
[eclipse 37]: commande(X,Y).
  (1) 1 CALL  commande(X, Y)   %> creep
  (2) 2 CALL  isBetween(X, 5000, 10000)   %> creep
  (2) 2 *EXIT  isBetween(5000, 5000, 10000)   %> creep
  (3) 2 CALL  isBetween(Y, 9000, 20000)   %> creep
  (3) 2 *EXIT  isBetween(9000, 9000, 20000)   %> creep
  (4) 2 CALL  5000 >= 9000   %> creep
  (4) 2 FAIL  ... >= ...   %> creep
  (3) 2 REDO  isBetween(Y, 9000, 20000)   %> skip
  (3) 2 *EXIT  isBetween(9001, 9000, 20000)   %> creep
  (8) 2 CALL  5000 >= 9001   %> creep
  (8) 2 FAIL  ... >= ...   %> creep
  (3) 2 REDO  isBetween(Y, 9000, 20000)   %> skip
  (3) 2 *EXIT  isBetween(9002, 9000, 20000)   %> creep
  (12) 2 CALL  5000 >= 9002   %> creep
  (12) 2 FAIL  ... >= ...   %> creep
  (3) 2 REDO  isBetween(Y, 9000, 20000)   %> 
*/

/* Question 1.6 */

/*
Le solveur Prolog de base interprète les nombres comme des termes. Il fait un parcours d'arbre selon la méthode "Generate & test". Il ne sait pas réduire les intervalles d'etude selon les contraintes.
*/

/* Question 1.7 */
commandeic(NbResistance, NbCondensateur) :-
	NbResistance #:: 5000..10000,
	NbCondensateur #:: 9000..20000,
	NbResistance #>= NbCondensateur.

/*
[eclipse 2]: commandeic(X,Y).

X = X{9000 .. 10000}
Y = Y{9000 .. 10000}


Delayed goals:
	Y{9000 .. 10000} - X{9000 .. 10000} #=< 0
Yes (0.00s cpu)
*/

/*
Le solveur ic à utiliser les contraintes pour réduire le domaine d'étude et il a conclu que les seules variables possibles de X et de Y sont dans l'intervalle [9000,10000] et qu'il faut que Y demeure inférieur à X.
*/

/* Question 1.8 */

/* Question 1.9 */
chapie(Chats, Pies, Pattes, Tetes) :-
	Chats #>= 0,
	Pies #>= 0,
	Pattes #>= 0,
	Tetes #>= 0,
	PattesChats #= 4*Chats,
	PattesPies #= 2*Pies,
	Pattes #= PattesChats + PattesPies,
	Tetes #= Chats + Pies.
/*
[eclipse 16]: chapie(2,P,Pa,5).

P = 3
Pa = 14
Yes (0.00s cpu)
*/

/* Question 1.10 */
/*
[eclipse 18]: chapie(C,P,Pa,T),Pa #=3*T.

C = C{0 .. 1.0Inf}
P = P{0 .. 1.0Inf}
Pa = Pa{0 .. 1.0Inf}
T = T{0 .. 1.0Inf}


Delayed goals:
	_746{0 .. 1.0Inf} - 4 * C{0 .. 1.0Inf} #= 0
	_846{0 .. 1.0Inf} - 2 * P{0 .. 1.0Inf} #= 0
	-(_846{0 .. 1.0Inf}) - _746{0 .. 1.0Inf} + Pa{0 .. 1.0Inf} #= 0
	T{0 .. 1.0Inf} - P{0 .. 1.0Inf} - C{0 .. 1.0Inf} #= 0
	-3 * T{0 .. 1.0Inf} + Pa{0 .. 1.0Inf} #= 0
Yes (0.00s cpu)
*/


/* Question 1.11 */
vabs(Val, AbsVal) :- AbsVal #>= 0, (AbsVal #= Val;AbsVal #= -Val).
/*
[eclipse 20]: vabs(-1,X).

X = 1
Yes (0.00s cpu)
[eclipse 21]: vabs(1,X).

X = 1
Yes (0.00s cpu, solution 1, maybe more) ? ;

No (0.00s cpu)
*/
vabsic(Val, AbsVal) :- AbsVal #>= 0, AbsVal #= Val or AbsVal #= -Val.
/*
[eclipse 26]: vabsic(-1,X).

X = 1
Yes (0.00s cpu)
[eclipse 27]: vabsic(1,X).

X = 1
Yes (0.00s cpu)
*/
/* Question 1.12 */
/*
[eclipse 28]: X #:: -10..10, vabs(X,Y).

X = X{0 .. 10}
Y = X{0 .. 10}
Yes (0.00s cpu, solution 1, maybe more) ? ;

X = X{-10 .. 0}
Y = Y{0 .. 10}


Delayed goals:
	Y{0 .. 10} + X{-10 .. 0} #= 0
Yes (0.00s cpu, solution 2)
[eclipse 29]: X #:: -10..10, vabsic(X,Y).

X = X{-10 .. 10}
Y = Y{0 .. 1.0Inf}


Delayed goals:
	#=(Y{0 .. 1.0Inf} - X{-10 .. 10}, 0, _397{[0, 1]})
	#=(Y{0 .. 1.0Inf} + X{-10 .. 10}, 0, _503{[0, 1]})
	-(_503{[0, 1]}) - _397{[0, 1]} #=< -1
Yes (0.00s cpu)

Dans le cas de vabsic on pose les contraintes mais on ne rentre pas dans l'arbre de recherche
*/

/* Question 1.13 */
faitListe([],0,_,_).
faitListe([A|R], Taille, Min, Max) :-
	TailleN #= Taille-1,
	A #:: Min..Max,
	faitListe(R,TailleN,Min,Max).
	
/*
[eclipse 38]: 36.         
faitListe(L, 2, 4, 6).

L = [_300{4 .. 6}, _421{4 .. 6}]
Yes (0.00s cpu, solution 1, maybe more) ? ;
*/

/* Question 1.14 */
suite([]).
suite([_]). 
suite([_,_|[]]). 
suite([A,B,C|R]) :-
	vabs(B, Babs),
	C #= Babs - A,
	suite([B,C|R]).
	
/*
[eclipse 43]: suite([1,2,1,-1,0]).

Yes (0.00s cpu, solution 1, maybe more) ? ;

No (0.00s cpu)
[eclipse 44]: suite([1,2,2,-1,0]).      

No (0.00s cpu)
*/

/* Question 1.15 */

q5 :- 
	suite(L),
	faitListe(L,20,0,50),
	A is L[X],
	B is L[X+9],
	A = B.













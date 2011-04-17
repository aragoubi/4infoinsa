/* 
Tp 6 : Sur une balancoire
Graignic Guillaume
Addar Mehdi
*/

:- lib(ic).
:- lib(branch_and_bound).

/* Partie prédicats de services*/
/* Produit scalaire */
produitScalaire(X,Y,S) :-
	dim(X,[DimX]),
	dim(Y,[DimY]),
	DimX = DimY,
	(for(Indice,1,DimX),param(X,Y),fromto(0,In,Out,S)
	do
		XVal is X[Indice],
		YVal is Y[Indice],
		Out #= In + XVal*YVal
	).
	
getVarList(T,L) :-
	dim(T,[Dim]),
	( for(Indice, 1, Dim), param(T), fromto([],In,Out,L)
	do
		Var is T[Indice],
		append(In,[Var],Out)
	).

/* Question 6.1 */
/* Partie Données */

poids([](24,39,85,60,165,6,32,123,7,14)).
noms([](ron,zoe,jim,lou,luc,dan,ted,tom,max,kim)).

getData(Poids,Noms) :-
	poids(Poids),
	noms(Noms).
	
defineVars(Places) :-
	noms(Noms),
	dim(Noms,[DimN]),
	dim(Places,[DimN]),
	(for(Indice,1,DimN),param(Places)
	do
		Courant is Places[Indice],
		Courant #:: [ -8.. -1, 1..8] 
	),
	alldifferent(Places).
	
moment(Places,Poids,Moment) :-
	dim(Places,[DimN]),
	(for(Indice,1,DimN),param(Places,Poids),fromto(0,In,Out,Moment)
	do
		V is Places[Indice],
		P is Poids[Indice],
		Courant #= P * abs(V),
		Out #= In + Courant
	).
	
	
/* Contraintes */
balancoireEquilibree(Places,Poids) :-
	produitScalaire(Places,Poids,0).
	
encadrerEnfants(Places) :-
	PlacePere is Places[8],
	PlaceMere is Places[4],
	ic:min(Places,Min),
	ic:max(Places,Max),
	PlacePere #= Min or PlacePere #= Max,
	PlaceMere #= Min or PlaceMere #= Max.
	
contraintesDanEtMax(Places) :-
	PlaceDan is Places[6],
	PlaceMax is Places[9],
	ic:min(Places,Min),
	ic:max(Places,Max),
	PlaceDan #= Min+1 or PlaceDan #= Max-1,
	PlaceMax #= Min+1 or PlaceMax #= Max-1.
	
contraintes5Personnes(Places) :-
	dim(Places,[DimN]),
	(for(Indice,1,DimN),param(Places),fromto(0,In,Out,Contrainte)
	do
		Var is Places[Indice],
		Courant #= Var/abs(Var),
		Out #= In + Courant
	),
	Contrainte #= 0.
	
solve(Places,Moment) :- 
 	getData(Poids,_),
 	defineVars(Places),
 	balancoireEquilibree(Places,Poids),
 	encadrerEnfants(Places),
  	contraintesDanEtMax(Places),
  	contraintes5Personnes(Places),
  	moment(Places,Poids,Moment),
	getVarList(Places,L),
	labeling(L).
	
/* Question ?? */

minimizeMoment(Places,Moment):-
	branch_and_bound:minimize(solve1(Places,Moment),Moment).
	
/* Version 1 */
solve1(Places,Moment) :- 
 	getData(Poids,_),
 	defineVars(Places),
 	balancoireEquilibree(Places,Poids),
 	encadrerEnfants(Places),
  	contraintesDanEtMax(Places),
  	contraintes5Personnes(Places),
  	moment(Places,Poids,Moment),
	getVarList(Places,L),
	search(L,0,most_constrained,indomain,complete,[]).
	
/* Version 2 */
solve2(Places,Moment) :- 
 	getData(Poids,_),
 	defineVars(Places),
 	balancoireEquilibree(Places,Poids),
 	encadrerEnfants(Places),
  	contraintesDanEtMax(Places),
  	contraintes5Personnes(Places),
  	moment(Places,Poids,Moment),
	getVarList(Places,L),
	search(L,0,most_constrained,indomain,complete,[]).
	












	
/* Question 5.4 */

minimizeEx(X,Y,Z,W) :-
	branch_and_bound:minimize(
		(	[X,Y,Z,W] #:: [0..10],
			X #= Z+Y+2*W,
			X #\= Z+Y+W,
			ic:labeling([X,Y,Z,W])),
		X).


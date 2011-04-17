/* 
TP 5 : Contraindre puis chercher
Graignic Guillaume
Addar Mehdi
*/

:- lib(ic).
:- lib(branch_and_bound).

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

/* Produit vectoriel */
produitVectoriel(X,Y,Z) :-
	dim(X,[DimX]),
	dim(Y,[DimY]),
	DimX = DimY,
	dim(Z,[DimY]),
	(for(Indice,1,DimX),param(X,Y,Z)
	do
		XVal is X[Indice],
		YVal is Y[Indice],
		ZVal is Z[Indice],
		ZVal #= XVal*YVal
	).

/* Question 5.1 */
techniciens([](5,7,2,6,9,3,7,5,3)).
quantites([](140,130,60,95,70,85,100,30,45)).
benefices([](4,5,8,5,6,4,7,10,11)).
fabrique(T) :- 
	techniciens(Tech),
	dim(Tech,[DimT]),
	dim(T,[DimT]),
	(for(Indice,1,DimT),param(T)
	do
		Courant is T[Indice],
		Courant #:: 0..1
	).

getData(Techniciens,Quantites,Benefices) :-
	techniciens(Techniciens),
	quantites(Quantites),
	benefices(Benefices).
	
getVarList(T,L) :-
	dim(T,[Dim]),
	( for(Indice, 1, Dim), param(T), fromto([],In,Out,L)
	do
		Var is T[Indice],
		append(In,[Var],Out)
	).
	
	
/* Question 5.2 */

ouvriersNecessaires(T,Techniciens,N) :- 
	produitScalaire(T,Techniciens,N).
	
beneficesTotaux(Quantites,Benefices,BeneficesTotaux) :-
	produitVectoriel(Quantites,Benefices,BeneficesTotaux).
	
profit(T,Quantites,Benefices,Profit) :-
	beneficesTotaux(Quantites,Benefices,BeneficesTotaux),
	produitScalaire(T,BeneficesTotaux,Profit).
	
/* Question 5.3 */
	
pose_contraintes(T,NbTechniciensTotal,Profit) :-
	getData(Techniciens,Quantites,Benefices),
	fabrique(T),
	ouvriersNecessaires(T,Techniciens,NbTechniciens),
	profit(T,Quantites,Benefices,Profit),
	NbTechniciens #=< NbTechniciensTotal.
	
solve(T, Profit) :- 
	pose_contraintes(T,22,Profit),
	getVarList(T,L),
	labeling(L).
	
/* Question 5.4 */

minimizeEx(X,Y,Z,W) :-
	branch_and_bound:minimize(
		(	[X,Y,Z,W] #:: [0..10],
			X #= Z+Y+2*W,
			X #\= Z+Y+W,
			ic:labeling([X,Y,Z,W])),
		X).
		
/*
Pour le labeling sur X:

Found a solution with cost 1
Found no solution with cost -1.0Inf .. 0

X = 1
Y = Y{[0, 1]}
Z = Z{[0, 1]}
W = 0

Pour le labeling sur X,Y,Z,W:

Found a solution with cost 2
Found no solution with cost -1.0Inf .. 1

X = 2
Y = 0
Z = 0
W = 1
Yes (0.00s cpu)
*/

/* Question 5.5 */

maximizeProfit(T,Profit):-
	branch_and_bound:minimize((solve(T,Profit),P is -Profit),P).
/*
[eclipse 44]: 42.
maximizeProfit(P).
Found a solution with cost 0
Found a solution with cost -495
Found a solution with cost -795
Found a solution with cost -1195
Found a solution with cost -1495
Found a solution with cost -1535
Found a solution with cost -1835
Found a solution with cost -1955
Found a solution with cost -1970
Found a solution with cost -2010
Found a solution with cost -2015
Found a solution with cost -2315
Found a solution with cost -2490
Found a solution with cost -2665
Found no solution with cost -1.0Inf .. -2666

P = 2665
Yes (0.00s cpu)
*/

/* Question 5.6 */
minimizeNbOuvrier(S,Profit):-
	branch_and_bound:minimize((pose_contraintes(T,22,Profit),techniciens(O),produitScalaire(T,O,S),Profit #>= 1000,getVarList(T,L),labeling(L)),S).	

/*
[eclipse 48]: 46.
minimizeNbOuvrier(X, Y).
Found a solution with cost 10
Found a solution with cost 9
Found a solution with cost 8
Found a solution with cost 7
Found no solution with cost -1.0Inf .. 6

X = 7
Y = 1040
Yes (0.00s cpu)
*/







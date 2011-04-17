/*
DS 2010 - Partie TP
Graignic Guillaume
Addar Mehdi
*/


/* Pour les connecteurs logiques et les contraintes portant sur des variables entieres (dont les operateurs debutent par #) */
:- lib(ic).

creation_carre(N,T) :-
	dim(T,[N,N]),
	T #:: 1..N*N,
	ic:alldifferent(T).

somme_magique(N,SommeMag) :-
	SommeMag is integer((N*(N*N+1))/2).
	
affiche(T) :-
	dim(T,[Dim1,Dim2]),
	(for(IndiceL,1,Dim1),param(T,Dim2)
		do
		(for(IndiceC,1,Dim2),param(T,IndiceL)
			do
			Sortie is T[IndiceL,IndiceC],
			write(Sortie),write(" ")
		),
		writeln(" ")
	).
		
contraintes(N,T) :-
	somme_magique(N,SommeMagique),
	dim(T,[Dim,Dim]),
	(for(IndiceL,1,Dim),param(T,Dim,SommeMagique)
		do
		(for(IndiceC,1,Dim),param(T,IndiceL),fromto(0,In,Out,Somme)
			do
			Element is T[IndiceL,IndiceC],
			Out #= In + Element
		),
		Somme #= SommeMagique
	),
	(for(IndiceC,1,Dim),param(T,Dim,SommeMagique)
		do
		(for(IndiceL,1,Dim),param(T,IndiceC),fromto(0,In,Out,Somme)
			do
			Element is T[IndiceL,IndiceC],
			Out #= In + Element
		),
		Somme #= SommeMagique
	),
	(for(Indice,1,Dim),param(T,N),fromto(0,In1,Out1,Diag1),fromto(0,In2,Out2,Diag2)
		do
		Element1 is T[Indice,Indice],
		Out1 #= In1 + Element1,
		Element2 is T[N+1-Indice,Indice],
		Out2 #= In2 + Element2
	),
	Diag1 #= SommeMagique,
	Diag2 #= SommeMagique.
		
getVarList(T,L) :-
	dim(T,[Dim,Dim]),
	(for(IndiceL,1,Dim),param(T,Dim),fromto([],In,Out,L)
		do
		(for(IndiceC,1,Dim),param(T,IndiceL),fromto([],In1,Out1,L1)
			do
			Element is T[IndiceL,IndiceC],
			append(In1,[Element],Out1)
		),
		append(In,L1,Out)
	).
	
solve(N,T) :-
	creation_carre(N,T),
	getVarList(T,L),
	contraintes(N,T),
	labeling(L),
	affiche(T).
	

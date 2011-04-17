/* 
TP 4 : Les régates 
Graignic Guillaume
Addar Mehdi
*/

:- lib(ic).

/*
capaciteBateaux([](7,6,5)).
tailleEquipes([](5,5,2,1)).
nbConf(3).
*/

capaciteBateaux([](10,10,9,8,8,8,8,8,8,7,6,4,4)).
tailleEquipes([](7,6,5,5,5,4,4,4,4,4,4,4,4,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2)).
nbConf(7).

getData(TailleEquipes,NbEquipes,CapaBateaux,NbBateaux,NbConf) :-
	tailleEquipes(TailleEquipes),
	dim(TailleEquipes,[NbEquipes]),
	capaciteBateaux(CapaBateaux),
	dim(CapaBateaux,[NbBateaux]),
	nbConf(NbConf).
	
defineVars(T, NbEquipes, NbConf, NbBateaux) :-
	dim(T,[NbEquipes,NbConf]),
	( for(IndiceI, 1, NbEquipes), param(T,NbConf,NbBateaux)
	do
		( for(IndiceJ, 1, NbConf), param(T,NbBateaux,IndiceI)
		do
			T[IndiceI,IndiceJ] #:: 1..NbBateaux
		)
	).
	
tri([],[]).
tri([A],[A]).
tri([A|R1],[A,B|R3]) :-
	append(R2,[B],R1),tri(R2,R3).	
	
/*
[eclipse 11]: tri([1,2,3,4,5,6],S).

S = [1, 6, 2, 5, 3, 4]
Yes (0.00s cpu, solution 1, maybe more) ? 
*/

getVarList(T,L) :-
	dim(T,[NbEquipes,NbConf]),
	( for(IndiceJ, 1, NbConf), param(T,NbEquipes), fromto([],In,Out,L)
	do
		( for(IndiceI, 1, NbEquipes), param(T,IndiceJ), fromto([],Ini,Outi,Li)
		do
			Var is T[IndiceI,IndiceJ],
			append(Ini,[Var],Outi)
		),
		tri(Li,LTrie),
		append(In,LTrie,Out)
	).
	
solve(T) :-
	getData(TailleEquipes,NbEquipes,CapaBateaux,NbBateaux,NbConf),
	defineVars(T, NbEquipes, NbConf, NbBateaux),
	pasMemeBateaux(T, NbEquipes, Nbconf),
	pasMemePartenaire(T,NbEquipes,NbConf),
	capaBateaux(T, TailleEquipes, NbEquipes, CapaBateaux, NbBateaux, NbConf),
	getVarList(T,L),
	labeling(L).
	
/*
On trouve énormement de solution (plus de 5000)
T = []([](1, 2, 3, 4, 5, 6, 7), [](2, 1, 4, 3, 6, 5, 8), [](3, 4, 1, 2, 8, 7, 9), [](4, 3, 5, 1, 2, 9, 11), [](5, 6, 2, 7, 1, 3, 10), [](6, 5, 7, 2, 1, 4, 3), [](6, 7, 8, 5, 2, 1, 4), [](7, 5, 6, 8, 9, 1, 2), [](8, 9, 7, 10, 4, 11, 5), [](8, 10, 9, 6, 11, 3, 4), [](9, 8, 12, 13, 7, 2, 3), [](10, 9, 8, 11, 13, 12, 2), [](12, 13, 11, 9, 10, 8, 1), [](11, 10, 13, 3, 8, 9, 1), [](11, 12, 10, 7, 3, 13, 9), [](13, 11, 10, 9, 6, 1, 5), [](13, 8, 11, 12, 4, 10, 2), [](10, 11, 9, 8, 12, 2, 1), [](9, 11, 6, 12, 10, 5, 13), [](9, 7, 10, 11, 12, 8, 6), [](7, 8, 9, 10, 3, 4, 6), [](7, 6, 5, 9, 11, 2, 8), [](5, 7, 1, 8, 3, 10, 13), [](4, 1, 6, 5, 3, 2, 12), [](3, 2, 4, 1, 7, 11, 6), [](3, 1, 2, 6, 9, 10, 5), [](2, 4, 3, 1, 9, 8, 12), [](2, 3, 1, 6, 7, 4, 10), [](1, 3, 2, 5, 4, 7, 6))
Yes (345.62s cpu, solution 5034, maybe more) ? 
*/
	
pasMemeBateaux(T, NbEquipes, Nbconf) :-
	dim(T,[NbEquipes,NbConf]),
	( for(IndiceI, 1, NbEquipes), param(T, NbConf)
	do
		( for(IndiceJ, 1, NbConf), param(T, IndiceI), fromto([],In,Out,L)
		do
			Var is T[IndiceI,IndiceJ],
			append(In,[Var],Out)
		),
		ic:alldifferent(L)
	).
	

pasMemePartenaire(T,NbEquipes,NbConf):-
	dim(T,[NbEquipes,NbConf]),
	( for(Equipe1,1,NbEquipes),param(T,NbConf,NbEquipes)
	do
		Indice is Equipe1+1,
		( for(Equipe2,Indice,NbEquipes), param(T,Equipe1,NbConf)
		do
						
			( for(Conf,1,NbConf),param(T,Equipe1,Equipe2),fromto(0,In,Out,Tot)
			do
				Bateau1 is T[Equipe1,Conf],
				Bateau2 is T[Equipe2,Conf],
				#=(Bateau1,Bateau2,Ans),
				Out #= In + Ans
			),
			Tot #=< 1
		)
	).



	
capaBateaux(T,TailleEquipes,NbEquipes,CapaB,NbBateaux,NbConf):-
	dim(T,[NbEquipes,NbConf]),
	( for(Bateau,1,NbBateaux), param(T,NbEquipes,NbConf,CapaB,TailleEquipes)
	do
		( for(Conf,1,NbConf), param(T,NbEquipes,Bateau,CapaB,TailleEquipes)
		do		
			( for(Equipe,1,NbEquipes),param(T,Bateau,Conf,TailleEquipes),fromto(0,In,Out,TotalPassagers)
			do
				Bateau1 is T[Equipe,Conf],
				#=(Bateau,Bateau1,Cond),
				Inc #= TailleEquipes[Equipe] * Cond,
				Out #= In + Inc
			),
			Capacite is CapaB[Bateau],
			TotalPassagers #=< Capacite
		)
	).

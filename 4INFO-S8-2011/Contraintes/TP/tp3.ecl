/*
TP 3 - Contraintes logiques
Graignic Guillaume
Addar Mehdi
*/

/* Pour les connecteurs logiques et les contraintes portant sur des variables entieres (dont les operateurs debutent par #) */
:- lib(ic).
/* Pour les contraintes symboliques (dont les operateurs debutent par & */
:- lib(ic_symbolic).

/* 3 Vers une solution en ECLiPSe */

/* Quesztion 3.1 */
taches([](tache(3,[],m1,_),
	tache(8,[],m1,_),
	tache(8,[4,5],m1,_),
	tache(6,[],m2,_),
	tache(3,[1],m2,_),
	tache(4,[1,7],m1,_),
	tache(8,[3,5],m1,_),
	tache(6,[4],m2,_),
	tache(6,[6,7],m2,_),
	tache(6,[9,12],m2,_),
	tache(3,[1],m2,_),
	tache(6,[7,8],m2,_))).

/* Question 3.2 */

affiche_taches(Taches) :-
	dim(Taches, [Dim]),
	( for(Indice,1,Dim),param(Taches)
		do
		tache(D,L,M,Deb) is Taches[Indice],
		write("Tache "),writeln(":"),
		write("Duree: "),write(D),write(", "),
		write("Liste des taches: "),
		( foreach(Elem,L)
			do
			write(Elem),write(", ")
		),
		write("Machine: "),write(M),write(", "),
		write("Debut: "),write(Deb),writeln(", ")
	).

/* Question 3.3 */
domaines(Taches,Fin) :- 
	dim(Taches, [Dim]),
	( for(Indice,1,Dim),param(Taches,Fin)
		do
		tache(D,_,_,Deb) is Taches[Indice],
		Deb #>= 0,
		Fin #>= Deb + D
	).

/* Question 3.4 */
getVarList(Taches,Fin,Liste) :-
	dim(Taches, [Dim]),
	( for(Indice,1,Dim),param(Taches),fromto([], In, Out, Liste2)
		do
		tache(_,_,_,Deb) is Taches[Indice],
		Out = [Deb | In]
	), Liste = [Fin | Liste2] .

/* Question 3.5 */
solve(L,Fin) :-
	taches(L),
	domaines(L,Fin),
	precedences(L),
	conflits(L),
	getVarList(L,Fin,Liste),
	labeling(Liste),
	affiche_taches(L).

/* Question 3.6 */
precedences(Taches) :-
	dim(Taches, [Dim]),
	( for(Indice,1,Dim),param(Taches)
		do
		tache(_,Prec,_,Deb) is Taches[Indice],
		(foreach(Tache,Prec),param(Taches,Deb)
			do
			tache(D1,_,_,Deb1) is Taches[Tache],
			Deb #>= D1+Deb1
		)
	).

/* Question 3.7 */
conflits(Taches) :- 
	dim(Taches, [Dim]),
	( for(Indice,1,Dim),param(Taches,Dim)
		do
		tache(Duree1,_,Machine1,Deb1) is Taches[Indice],
		( for(Indice1,Indice+1,Dim),param(Taches,Duree1,Machine1,Deb1)
			do
			tache(Duree2,_,Machine2,Deb2) is Taches[Indice1],
			(Machine1 = Machine2 ->
				 (Deb2 #>= Deb1 + Duree1) or (Deb1 #>= Deb2 + Duree2)
			; true)
		)
	).

/*

solve(X, Y).
Tache :
Duree: 3, Liste des taches: Machine: m1, Debut: 0, 
Tache :
Duree: 8, Liste des taches: Machine: m1, Debut: 29, 
Tache :
Duree: 8, Liste des taches: 4, 5, Machine: m1, Debut: 9, 
Tache :
Duree: 6, Liste des taches: Machine: m2, Debut: 0, 
Tache :
Duree: 3, Liste des taches: 1, Machine: m2, Debut: 6, 
Tache :
Duree: 4, Liste des taches: 1, 7, Machine: m1, Debut: 25, 
Tache :
Duree: 8, Liste des taches: 3, 5, Machine: m1, Debut: 17, 
Tache :
Duree: 6, Liste des taches: 4, Machine: m2, Debut: 12, 
Tache :
Duree: 6, Liste des taches: 6, 7, Machine: m2, Debut: 31, 
Tache :
Duree: 6, Liste des taches: 9, 12, Machine: m2, Debut: 37, 
Tache :
Duree: 3, Liste des taches: 1, Machine: m2, Debut: 9, 
Tache :
Duree: 6, Liste des taches: 7, 8, Machine: m2, Debut: 25, 

X = [](tache(3, [], m1, 0), tache(8, [], m1, 29), tache(8, [4, 5], m1, 9), tache(6, [], m2, 0), tache(3, [1], m2, 6), tache(4, [1, 7], m1, 25), tache(8, [3, 5], m1, 17), tache(6, [4], m2, 12), tache(6, [6, 7], m2, 31), tache(6, [9, 12], m2, 37), tache(3, [1], m2, 9), tache(6, [7, 8], m2, 25))
Y = 43

*/


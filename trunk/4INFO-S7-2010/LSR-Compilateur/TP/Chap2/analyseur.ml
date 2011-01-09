#use "scanner.ml";;
open List;;

type vnonterm = S | Expr | Termb | SuiteExpr | Facteurb | SuiteTermb | Relation | Op ;;

type vterm = T_OU | T_ET |
             T_SUP | T_INF | T_EGAL | T_DIFF |
	     T_SUPEGAL | T_INFEGAL |
	     T_SI | T_SINON | T_ALORS | T_FSI |
             T_IDENT | T_EOF |
             T_PAROUV | T_PARFERM;;

type v = Non_term of vnonterm | Term of vterm;;

type arbre_concret = ACNT of vnonterm * (arbre_concret list)
		     | ACT of unite_lexicale;;

type arbre_abstrait =
    Cond of arbre_abstrait * arbre_abstrait * arbre_abstrait
  | Comp of string * unite_lexicale * string
  | Ou of arbre_abstrait * arbre_abstrait
  | Et of arbre_abstrait * arbre_abstrait;;

(* fonction transformant les UL en Terminaux sauf pour UL_ERR*)
let term_of_ul = function
    UL_IDENT(_) -> T_IDENT
  | UL_OUVR -> T_PAROUV
  | UL_FERM -> T_PARFERM
  | UL_SUP -> T_SUP
  | UL_INF -> T_INF
  | UL_EGAL -> T_EGAL
  | UL_DIFF -> T_DIFF
  | UL_SUPEGAL -> T_SUPEGAL
  | UL_INFEGAL -> T_INFEGAL
  | UL_SI -> T_SI
  | UL_ALORS -> T_ALORS
  | UL_SINON -> T_SINON
  | UL_FSI -> T_FSI
  | UL_ET -> T_ET
  | UL_OU -> T_OU
  | UL_EOF -> T_EOF;;

exception Pas_de_derivation of vnonterm * unite_lexicale;;

(*Fonction donnant la dérivation des non terminaux de la grammaire en fonction de l'unité lexicale suivante*)
let (ma_derivation : vnonterm * unite_lexicale -> v list) = function
    S,_ -> [Non_term Expr;Term T_EOF]
  | Expr,_ -> [Non_term Termb;Non_term SuiteExpr]
  | SuiteExpr,UL_OU -> [Term T_OU;Non_term Expr]
  | SuiteExpr,_ -> []
  | Termb,_ -> [Non_term Facteurb;Non_term SuiteTermb]
  | SuiteTermb,UL_ET -> [Term T_ET;Non_term Termb]
  | SuiteTermb,_ -> []
  | Facteurb,UL_OUVR -> [Term T_PAROUV;Non_term Expr;Term T_PARFERM]
  | Facteurb,UL_SI -> [Term T_SI;Non_term Expr;Term T_ALORS;Non_term Expr;Term T_SINON;Non_term Expr;Term T_FSI]
  | Facteurb,_ -> [Non_term Relation]
  | Relation,UL_IDENT(_)  -> [Term T_IDENT;Non_term Op;Term T_IDENT]
  | Relation,ul -> raise(Pas_de_derivation(Relation,ul))
  | Op,(UL_SUP | UL_INF | UL_EGAL | UL_DIFF | UL_SUPEGAL | UL_INFEGAL as op) -> [Term (term_of_ul op)]
  | Op,ul -> raise(Pas_de_derivation(Op,ul));;

let rec 
(analyse_caractere : v * (unite_lexicale list) -> arbre_concret * (unite_lexicale list)) = function
    (Term (_)),liste -> (ACT (hd liste), tl liste)
  | (Non_term (_ as nterm)),liste -> let listeTerm = ma_derivation(nterm, hd liste) in
                                     let (listeAC,listeUL) = analyse_mot(listeTerm,liste) in
				       (ACNT(nterm,listeAC),listeUL)
and
(analyse_mot : (v list) * (unite_lexicale list) -> (arbre_concret list) * (unite_lexicale list)) = function
    [],liste -> [],liste
  | listeTerm,listeUL -> let (ac,nouvelleListe) = analyse_caractere(hd listeTerm,listeUL) in 
                         let (suiteListeAC,nouvelleListe) = analyse_mot(tl listeTerm,nouvelleListe) in
			   (ac::suiteListeAC,nouvelleListe);;


let rec construit_arbre_abstrait = function ACNT(nt,l) ->
    match (nt,l) with
	(S,[a;ACT UL_EOF])
      | (Facteurb,[ACT UL_OUVR;a;ACT UL_FERM])
      | (Facteurb,[a])
      | (Termb,[a;ACNT(SuiteTermb,[])])
      | (Expr,[a;ACNT(SuiteExpr,[])]) -> construit_arbre_abstrait a
      | (Expr,[a;ACNT(SuiteExpr,[ACT UL_OU;b])]) -> Ou (construit_arbre_abstrait a,construit_arbre_abstrait b) 
      | (Termb,[a;ACNT(SuiteTermb,[ACT UL_ET;b])]) -> Et (construit_arbre_abstrait a,construit_arbre_abstrait b)
      | (Relation,[ACT (UL_IDENT a);ACNT(Op,[ACT op]);ACT (UL_IDENT b)]) -> Comp(a,op,b)
      | (Facteurb,[ACT UL_SI;a;ACT UL_ALORS;b;ACT UL_SINON;c;ACT UL_FSI]) -> Cond(a,b,c);;

(*
(ACNT(S,
  [ACNT(Expr,
    [ACNT(Termb,
      [ACNT(Facteurb,
        [ACNT(Relation,
          [ACT(UL_IDENT "t");ACNT(Op,[ACT UL_INF]);ACT(UL_IDENT "y")])]);
       ACNT(SuiteTermb,
        [ACT UL_ET;
         ACNT (Termb,
          [ACNT(Facteurb,
            [ACNT(Relation,
              [ACT(UL_IDENT "x");ACNT(Op,[ACT UL_EGAL]);ACT(UL_IDENT "y")])]);
           ACNT(SuiteTermb,[])])])]);
       ACNT(SuiteExpr,[])]);
   ACT UL_EOF]),
 [])
*)


 let (arbConc,listeVide) =  analyse_caractere(Non_term S,[UL_IDENT "t";UL_INF;UL_IDENT "y";UL_ET;UL_IDENT "x";UL_EGAL;UL_IDENT "y"]);;


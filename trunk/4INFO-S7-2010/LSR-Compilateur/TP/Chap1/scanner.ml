type etat = Q_INITIAL | Q_IDENT | Q_FIN_NON_CONS | Q_FIN_CONS | Q_OP | Q_DEB_COMM | Q_COMM | Q_FIN_COMM | Q_EOF;;

type carac = BLANC | LETTRE | PARENTHESE | OPERATEUR | CHIFFRE | SLASH | ETOILE | EOF | AUTRE;;

type transition = etat -> carac -> etat;;

type automate = {
  init : etat;
  final_cons : etat;
  final_non_cons : etat;
  final_eof : etat;
  transitions : transition
};;

type unite_lexicale = 
    UL_IDENT of string
  | UL_OUVR | UL_FERM
  | UL_SUP | UL_INF | UL_EGAL | UL_DIFF
  | UL_ET | UL_OU
  | UL_EOF
  | UL_ERR of string;;

type lexeme = string;;

type crible = lexeme -> etat -> unite_lexicale;;

type grammaire = {
  automate : automate;
  crible : crible;
};;

let (type_du_carac : char -> carac) = function
       'a'..'z' | 'A'..'Z' -> LETTRE
  |    ' ' | '\t' | '\n' -> BLANC
  |    '(' | ')' -> PARENTHESE
  |    '+' | '-' | '<' | '>' | '=' -> OPERATEUR
  |    '0'..'9' -> CHIFFRE
  |    '/' -> SLASH
  |    '*' -> ETOILE
  |    '\000' -> EOF
  |    _ -> AUTRE;;

exception Pas_de_transition of etat * carac;;

let (trans : transition) =
  fun e c -> (match e with
     Q_INITIAL -> (match c with
		       BLANC -> Q_INITIAL
		      |LETTRE -> Q_IDENT
		      |PARENTHESE -> Q_FIN_CONS
		      |OPERATEUR -> Q_OP
		      |SLASH -> Q_DEB_COMM
		      |EOF -> Q_EOF
		      |_ -> raise (Pas_de_transition(e,c)))
    |Q_IDENT -> (match c with
		       LETTRE -> Q_IDENT
		      |CHIFFRE -> Q_IDENT
		      | _ -> Q_FIN_NON_CONS)
    |Q_OP -> (match c with
		       OPERATEUR -> Q_OP
		      |_ -> Q_FIN_NON_CONS)
    |Q_DEB_COMM -> (match c with
		       ETOILE -> Q_COMM
		      |_ -> raise (Pas_de_transition(e,c)))
    |Q_COMM -> (match c with
		       ETOILE -> Q_FIN_COMM
		      |EOF -> Q_EOF
		      |_ -> Q_COMM)
    |Q_FIN_COMM -> (match c with
		       ETOILE -> Q_FIN_COMM
		      |EOF -> Q_EOF
		      |SLASH -> Q_INITIAL
		      |_ -> Q_COMM)
    |_ -> raise (Pas_de_transition(e,c)));;

let (mon_crible : crible) =
  fun l e -> match e with
      Q_EOF -> UL_EOF
    | _ -> (match l with
		"(" -> UL_OUVR
	      | ")" -> UL_FERM
	      | ">" -> UL_SUP
	      | "<" -> UL_INF
	      | "=" -> UL_EGAL
	      | "<>" -> UL_DIFF
	      | "et" -> UL_ET
	      | "ou" -> UL_OU
              | _ ->(match type_du_carac(String.get l 0) with
			 LETTRE -> UL_IDENT(l)
		       | _ -> UL_ERR(l)));;

let (mon_fichier : in_channel) = open_in "test1";;

let rec (parcours_automate : in_channel -> automate -> etat -> string -> (etat * lexeme)) =
  fun fichier automate e s -> let (charlu : char) = (try input_char(fichier) with End_of_file -> '\000') in
                                  try
				        (match e with
					     Q_FIN_NON_CONS -> 
					       seek_in fichier (pos_in fichier -1);
					       (Q_FIN_NON_CONS, s)
					   | Q_FIN_CONS -> 
					       (Q_FIN_CONS, s)
					   | Q_EOF ->
					       (Q_EOF,s)
					   | _ -> 
					          let (new_e : etat) = (trans e (type_du_carac(charlu))) in
					            match new_e with 
					        	 Q_FIN_NON_CONS -> parcours_automate fichier automate new_e s
						       | Q_INITIAL      -> parcours_automate fichier automate new_e ""
					               | _              -> parcours_automate fichier automate new_e (s^(String.make 1 charlu))
 					)
			          with Pas_de_transition(_) -> (e,s);;

let (get_token : in_channel -> grammaire -> (unite_lexicale * lexeme)) =
   fun fichier gram -> let ((etat,lexeme) : (etat * lexeme)) = parcours_automate fichier gram.automate gram.automate.init "" in
     (gram.crible lexeme etat,lexeme);;

let rec (scanner : in_channel -> grammaire -> (unite_lexicale * lexeme) list) = 
   fun fichier gram -> let ((ul,lex) : (unite_lexicale * lexeme)) = get_token fichier gram in
     if (ul == UL_EOF) then (ul,lex)::[] else (ul,lex)::(scanner fichier gram);;
     


let (a : automate) = {
init = Q_INITIAL;
final_cons = Q_FIN_CONS;
final_non_cons = Q_FIN_NON_CONS;
final_eof = Q_EOF;
transitions = trans
};;

let (gram : grammaire) = {
automate = a;
crible = mon_crible;
};;



(* Test  

- : etat * string = (Q_FIN_NON_CONS, "jojo")
# parcours_automate mon_fichier a a.init "";;
- : etat * string = (Q_FIN_NON_CONS, "et")
# parcours_automate mon_fichier a a.init "";;
- : etat * string = (Q_FIN_CONS, ")")
# parcours_automate mon_fichier a a.init "";;

- : unite_lexicale * lexeme = (UL_IDENT "jojo", "jojo")
# get_token mon_fichier gram;;
- : unite_lexicale * lexeme = (UL_ET, "et")
# get_token mon_fichier gram;;
- : unite_lexicale * lexeme = (UL_FERM, ")")

*)



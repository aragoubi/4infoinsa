(* 
     Chapitre 3
     Graignic Guillaume
     Cadoret olivier 
     arbre.ml 
*)

(* Types possibles déclarés sous forme de liste énumérée*)
type decl = Bool | Int

(* Le type arbre abstrait syntaxique est défini ci-dessous 
*)
type arbre_abstrait =
      Ident of string
   |  Bloc of (arbre_abstrait list) * (arbre_abstrait list)
   |  Declaration of decl * string
   |  Plus of arbre_abstrait * arbre_abstrait
   |  Inf of arbre_abstrait * arbre_abstrait
   |  Et of arbre_abstrait * arbre_abstrait
   |  Affectation of string * arbre_abstrait;;   

(* 
     Chapitre 3
     Graignic Guillaume
     Cadoret olivier 
     main.ml 
*)

open Grammar;;
open Lexer;;

(* Pour des petits tests *)
let lexbuf = s scanner (Lexing.from_string "begin int a ; a <- b + c end");;
(*
val lexbuf : Arbre.arbre_abstrait =
  Arbre.Bloc ([Arbre.Declaration (Arbre.Int, "a")],
   [Arbre.Affectation ("a", Arbre.Plus (Arbre.Ident "b", Arbre.Ident "c"))])
*)

(* Pour les plus grand tests, on lit le fichier "test" qui contient un code à analyser 
Le fichier test contient "begin bool x ; begin int a ; a <- b + c end ; x <- (b and c) end" *)
let lexbuf2 = s scanner (Lexing.from_channel (open_in "test"));;
(*
val lexbuf2 : Arbre.arbre_abstrait =
  Arbre.Bloc ([Arbre.Declaration (Arbre.Bool, "x")],
   [Arbre.Bloc ([Arbre.Declaration (Arbre.Int, "a")],
     [Arbre.Affectation ("a", Arbre.Plus (Arbre.Ident "b", Arbre.Ident "c"))]);
    Arbre.Affectation ("x", Arbre.Et (Arbre.Ident "b", Arbre.Ident "c"))])
*)

(* TEST OK *)
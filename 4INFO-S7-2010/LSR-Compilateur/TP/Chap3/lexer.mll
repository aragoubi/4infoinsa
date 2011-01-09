(* 
     Chapitre 3
     Graignic Guillaume
     Cadoret olivier 
     lexer.mll 
*)

open Grammar

(* Definitions de l'ident*)
let id = ['a'-'z'] ['a'-'z' '0'-'9']*

(* Règles du crible *)
rule scanner = 
  parse "begin"    {BEGIN}
      | ";"        {PTVIRG}
      | "end"      {END}
      | ","        {VIRG}
      | "int"      {INT}
      | "bool"     {BOOL}
      | "<-"       {AFFEC}
      | "+"        {PLUS}
      | "<"        {INF}
      | "and"      {AND}
      | "("        {PAROUV}
      | ")"        {PARFERM}
      | id   as ident      {IDENT ident}
      | [' ' '\t' '\n'] {scanner lexbuf}
      | eof        {EOF}
      | _          {ERROR}

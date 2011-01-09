%{(* 
     Chapitre 3
     Graignic Guillaume
     Cadoret olivier 
     grammar.mly 
*)%}

%{
(* On ouvre arbre.ml qui définit le type arbre_abstrait*)
open Arbre   
%}

%{(* On définit les token possible *)%}  
%token <string> IDENT
%token BEGIN VIRG PTVIRG PLUS INT BOOL AFFEC INF AND PAROUV PARFERM END EOF ERROR

%{(* On gère les priorités entre les tokens AND INF et PLUS *)%}  
%left AND
%left INF
%left PLUS

%{(* On associe le type rendu par la régle s à un arbre abstrait *)%}  
%type <Arbre.arbre_abstrait> s

%{(* On commence par la régle de grammaire s*)%}  
%start s

%{(* On définit les régles de grammaire une à une et 
     on construit l'arbre_abstrait au fur et à mesure *)%}  
%%
s:
bloc EOF {$1}
;

bloc:
BEGIN sdecl PTVIRG sinst END {Bloc($2,$4)}
;

sdecl:
decl {$1::[]}
| decl VIRG sdecl {$1::$3}
;

decl:
typ IDENT {Declaration ($1,$2)}
;

typ:
INT {Int}
| BOOL {Bool}
;

sinst:
inst {$1::[]}
| inst PTVIRG sinst {$1::$3}
;

inst:
bloc {$1}
| IDENT AFFEC expr {Affectation($1,$3)}
;

expr:
expr PLUS expr {Plus($1,$3)}
| expr INF expr {Inf($1,$3)}
| expr AND expr {Et($1,$3)}
| PAROUV expr PARFERM {$2}
| IDENT {Ident($1)}
;

%{
#include"syntax2.tab.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "TSL.h"
int nb_ligne=1;
int Col=1;
extern YYSTYPE yylval;
%}

lettre [a-zA-Z]
chiffre [0-9]
num ([1-9]+{chiffre}*|0)("\."{chiffre}*[1-9]|{chiffre}*)
IDF {lettre}([a-z]|{chiffre}|_)*
cst ("(-"{num}")"|{num})
com ("//"[^"\n"]*|"/*"([^"*/"]*|"\n")*"*/")
%%

"PROGRAMME" {rechercher(yytext,"Mot cle",0,0, 1,0); Col= Col + strlen(yytext); printf("%s\t", yytext); return mc_prog;}
"INTEGER" {yylval.s=strdup(yytext);rechercher(yytext,"Mot cle",0,0, 1,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return mc_integ; }
"FLOAT" {yylval.s=strdup(yytext);rechercher(yytext,"Mot cle",0,0, 1,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return mc_real; }
"CONST" {rechercher(yytext,"Mot cle",0,0, 1,0); Col= Col + strlen(yytext);printf("%s\t ", yytext);return mc_cst; }
"VAR" {rechercher(yytext,"Mot cle",0,0, 1,0); Col= Col + strlen(yytext);printf("%s\t", yytext);  return mc_var; } 
"BEGIN" { rechercher(yytext,"Mot cle",0,0, 1,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return mc_beg; }
"IF" {rechercher(yytext,"Mot cle",0,0, 1,0); Col= Col + strlen(yytext); printf("%s\t", yytext);return mc_if; }
"ELSE" { rechercher(yytext,"Mot cle",0,0, 1,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return mc_else; }
"FOR" {rechercher(yytext,"Mot cle",0,0, 1,0); Col= Col + strlen(yytext); printf("%s\t", yytext);return mc_for; }
"WHILE" {rechercher(yytext,"Mot cle",0,0, 1,0); Col= Col + strlen(yytext); printf("%s\t", yytext);return mc_while; }
"readln" {rechercher(yytext,"Mot cle",0,0, 1,0); Col= Col + strlen(yytext); printf("%s\t", yytext);return mc_rd; }
"writeln" {rechercher(yytext,"Mot cle",0,0, 1,0); Col= Col + strlen(yytext); printf("%s\t", yytext);return mc_wr; }
"END." {rechercher(yytext,"Mot cle",0,0, 1,0); Col= Col + strlen(yytext); printf("%s\t", yytext);return mc_endp; }
{IDF} {yylval.s=strdup(yytext);rechercher(yytext,"IDF"," ",0,0,0);  Col= Col + strlen(yytext);
if (yyleng>7) 
printf ("Erreur Lexical:IDF trop long! line:%d ,Col:%d,E:%s \n ",nb_ligne, Col,yytext);
printf ("%s\t", yytext);return idf; }
{cst} {if(atof(yytext)==0){rechercher(yytext,"CST"," ",atof(yytext+1),0,0);yylval.r=atof(yytext+1);
if(yylval.r<-32768)printf ("Erreur Lexical: CST trop long a la ligne %d a la colonne %d \n ",nb_ligne, Col);}else{
rechercher(yytext,"CST"," ",atof(yytext),0,0);yylval.r=atof(yytext);
if(yylval.r>32767)printf ("Erreur Lexical: CST trop long a la ligne %d a la colonne %d \n ",nb_ligne, Col);}  Col= Col + strlen(yytext);printf("%s\t", yytext);return cst; }
"{" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf ("%s\t", yytext);return acO;}
"}" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf ("%s\t", yytext);return acF;}
"=" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf ("%s\t", yytext);return aff;}
";" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return pvg; }
"," {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return vrg; }
"[" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return cro; }
"]" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return crf; }
"(" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return po; }
")" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return pf; }
"+" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return add; }
"-" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return sub; }
"*" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return mul; }
"/" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return Div; }
"&&" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return and; }
"||" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return or; }
"!" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return not; }
"<" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return inf; }
"<=" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return infE; }
">" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return sup; }
">=" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return supE; }
"==" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return egl; }
"!=" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return diff; }
"'" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return apo; }
":" {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return dp; }
"." {rechercher(yytext,"SEP",0,0, 2,0); Col= Col + strlen(yytext);printf("%s\t", yytext);return pt; }
{com} {printf ("%s\t", yytext);}
[ \t] {Col= Col + strlen(yytext);}
\n {nb_ligne++;Col=1; printf("\n"); }
. printf ("err lexicale:Entite lexicale non reconnue ,line:%d ,Col:%d,E:%s \n", nb_ligne, Col,yytext);


 
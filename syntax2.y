%{
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "TSL.h"
extern int nb_ligne;
extern int Col;
int yylex();
int yyerror(char *msg);
int v;
char* suavType;
char* sauvName;
float val=0;
%}

%union {
    char* s;
    float r;
}

%token mc_prog mc_beg mc_endp <s>idf <r>cst aff pvg <s>mc_integ <s>mc_real mc_var acO acF 
vrg mc_cst cro crf dp pt apo po pf infE sup supE egl diff 
mc_if mc_else mc_for mc_while mc_rd mc_wr add sub mul Div and or not inf 
  
%%
S: mc_prog idf mc_var acO DEC acF mc_beg LIST_INST mc_endp {printf("\n syntaxe correcte \n"); YYACCEPT;}
;

DEC: TYPE ListIDF pvg DEC
   | mc_cst idf aff cst pvg DEC {
     if(doubleDeclaration($2)==0){
	 v=(int)$4; CstCode($2);
	 if($4 == v ) insererType($2,"INTEGER");
	 else insererType($2,"FLOAT");}
	 else{
	 printf("\n err semantique:double déclaration! ,line:%d, col:%d,E:%s \n",nb_ligne,Col,$2);
	 return 0;}}
   |
;

TYPE: mc_integ { suavType=strdup($1); }
    | mc_real { suavType=strdup($1); }
;

ListIDF: idf {
		 if(doubleDeclaration($1)==0){insererType($1,suavType);}
		 else{
		 printf("\n err semantique:double déclaration! ,line:%d, col:%d,E:%s \n",nb_ligne,Col,$1);
		 return 0;}} 
		 vrg ListIDF
       | idf {
	     if(doubleDeclaration($1)==0){insererType($1,suavType);}
		 else{
		 printf("\n err semantique:double déclaration! ,line:%d, col:%d,E:%s \n",nb_ligne,Col,$1);
		 return 0;}}
	   | idf cro cst crf vrg ListIDF { v=(int)$3; 
	     if($3>0 && v==$3){insererSize($1,$3);}
		 else{insererSize($1,-1);
	     printf("err semantique:Size table must be a pos int ! ,line:%d, col:%d,E:%f \n",nb_ligne,Col,$3);
		 return 0;}
	     if(doubleDeclaration($1)==0){insererType($1,suavType);}
		 else{
		 printf("\n err semantique:double déclaration! ,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1);
		 return 0;}
		 }
	   | idf cro cst crf {v=(int)$3;
	     if($3>0 && v==$3)insererSize($1,$3);
	     else{insererSize($1,-1);
	     printf("err semantique:Size table must be a pos int ! ,line:%d, col:%d,E:%f \n",nb_ligne,Col-1,$3);
		 return 0;}
	     if(doubleDeclaration($1)==0){insererType($1,suavType);}
	     else{
	     printf("\n err semantique:double déclaration! ,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1);
		 return 0;}
	   } 
;

LIST_INST: INST LIST_INST                  
         |                                
;	

INST: INST_AFF
	| INST_RD
	| INST_WR
	| INST_FOR
	| INST_WHILE
	| INST_IF
;




OPERATOR: add 
		| mul 
		| Div 
		| sub
;

EXPRESSION: EXPRESSION OPERATOR T
		  | T
;

T: OPERAND
 | po EXPRESSION pf 
;

OPERAND: idf {
		 if(ISdeclared($1)!=0){
		 printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1);
		 return 0;}else sauvName=strdup($1); 
		 }
	   | cst {val=$1;}
	   | idf cro cst crf {
	     if(ISdeclared($1)!=0){
		 printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1);
		 return 0;}
		 else sauvName=strdup($1); }
	   | idf cro idf crf {
	     if(ISdeclared($1)!=0){
		 printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1); 
		 return 0;}
		 else{
		 if(ISdeclared($3)!=0){
		 printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$3);
		 return 0;}
		 else sauvName=strdup($1); }}
;


INST_AFF: idf aff EXPRESSION  pvg {
		  if(ISdeclared($1)!=0){
		  printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1);
		  return 0;}
		  else{
		  if(IsCST($1)==0){
		  printf("err semantique:aff not allowed! %s is CST!,line:%d,Col:%d\n",$1,nb_ligne,Col);
		  return 0;}
		  else{
		  if(NotTable($1)!=0) {
		  printf("err semantique:%s est un tableau!\n",$1);return 0;}
		  else{
		  if(sameType($1,val)!=0){val=0;
		  printf("err semantique:type incompatible!,line:%d,Col:%d\n",nb_ligne,Col);return 0;
		  return 0;}
		  if(sauvName != NULL){
		  if(sameType2($1,sauvName)!=0){sauvName = NULL;
		  printf("err semantique:type incompatible!,line:%d,Col:%d\n",nb_ligne,Col);
		  return 0;}}
		  }
		  }}}
	    | idf cro cst crf aff EXPRESSION pvg {
		  if(ISdeclared($1)!=0){
		  printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1); 
		  return 0;}
		  else{
		  if(IsTable($1)!=0) {
		  printf("err semantique:%s n'est pas un tableau!",$1); return 0;}
		  else{
		  if(sameType($1,val)!=0){val=0;
		  printf("err semantique:type incompatible!,line:%d,Col:%d\n",nb_ligne,Col);
		  return 0;}
		  if(sauvName != NULL){
		  if(sameType2($1,sauvName)!=0){sauvName = NULL;
		  printf("err semantique:type incompatible!,line:%d,Col:%d\n",nb_ligne,Col);
		  return 0;}}
		  }}}
		| idf cro idf crf aff EXPRESSION pvg {
		  if(ISdeclared($1)!=0){
		  printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1); 
		  return 0;}
		  else{
		  if(ISdeclared($3)!=0){
		  printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$3);
		  return 0;}
		  else{
		  if(IsTable($1)!=0){
		  printf("err semantique:%s n'est pas un tableau!",$1); 
		  return 0;}
		  else{
		  if(sameType($1,val)!=0){val=0;
		  printf("err semantique:type incompatible!,line:%d,Col:%d\n",nb_ligne,Col);
		  return 0;}
		  if(sauvName != NULL){
		  if(sameType2($1,sauvName)!=0){sauvName = NULL;
		  printf("err semantique:type incompatible!,line:%d,Col:%d\n",nb_ligne,Col);
		  return 0;}}
		  }}}}

;

INST_RD: mc_rd po idf pf pvg {if(ISdeclared($3)!=0){
		 printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$3);
		 return 0;}}
;

INST_WR: mc_wr po apo WR1 apo WR2 pf pvg
;

WR1: idf WR1 {Delete($1);}
   | dp
   |
;

WR2: idf apo pt apo {if(ISdeclared($1)!=0){
	 printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1);
	 return 0;}  }
   |
;

INST_FOR: mc_for po idf dp P1 dp P1 dp P1 pf acO INST LIST_INST acF {
		  if(ISdeclared($3)!=0){
		  printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$3);
		  return 0;} }
;

P1: idf {
	if(ISdeclared($1)!=0){
	printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1);
	return 0;} }
  | cst 
;

OP: sup 
  | supE 
  | inf 
  | infE
;

INST_WHILE: mc_while po COND pf acO INST LIST_INST acF
;

INST_IF: mc_if po COND pf acO INST LIST_INST acF INST_ELS
;

INST_ELS: mc_else acO INST LIST_INST acF
		|
;

COND: EXPRESSION OPP EXPRESSION avec
	| not EXPRESSION avec
	| po COND pf avec
;

avec: and COND 
	| or COND 
	|
;

OPP: OP 
   | egl 
   | diff
;

%%

int main(){
    yyparse(); 
	afficherL();
}

int yywrap()
{return 1;}

int yyerror(char *msg){
	printf ("Erreur Syntaxique: line:%d ,Col:%d \n",nb_ligne,Col);
	return 1;

}
%{
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "TSL.h"
#include "qaud.h"
extern int nb_ligne;
extern int Col;
int yylex();
int yyerror(char *msg);
int v;
char* suavType;
char* sauvName;
char* sauvfor;
char* sauvfor1;
char* sauvfor3;
char* sauvidf;
float val=0;
char tmp [20];
char Z[20];
char* Z2;
char tabP [20];
int Fin_if=0,deb_else=0,deb_wh=0,deb_for,deb_else2=0,deb_wh1=0,deb_wh2=0;
int qc=0;
int errore=1;

%}

%union {
    char* s;
    float r;
}

%token mc_prog mc_beg mc_endp <s>idf <r>cst aff pvg <s>mc_integ <s>mc_real mc_var acO acF 
vrg mc_cst cro crf dp pt apo po pf infE sup supE egl diff 
mc_if mc_else mc_for mc_while mc_rd mc_wr add sub mul Div and or not inf 
  
%%
S: mc_prog idf mc_var acO DEC acF mc_beg LIST_INST mc_endp {errore=0;
   printf("\n syntaxe correcte \n"); YYACCEPT; }
;

DEC: TYPE ListIDF pvg DEC
   | mc_cst idf aff cst pvg DEC {
     if(doubleDeclaration($2)==0){
	 v=(int)$4; CstCode($2,$4);
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

INST: INST_AFF {if(quadExpre()) {
				printf("\n err semantique:division par 0!,line:%d, col:%d\n",nb_ligne,Col-1);return 0;}}
	| INST_RD
	| INST_WR
	| INST_FOR
	| INST_WHILE
	| INST_IF
;

OPERATOR: add {empiler("+");}
		| mul {empiler("*");}
		| Div {empiler("/");}
		| sub {empiler("-");}
;

EXPRESSION: EXPRESSION OPERATOR T
		  | T
;

T: OPERAND
 | po {empiler("(");} EXPRESSION pf {empiler(")");}
;

OPERAND: idf {
		 if(ISdeclared($1)!=0){
		 printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1);
		 return 0;}else{ sauvName=strdup($1);
		 empiler($1);} 
		 }
	   | cst {val=$1;sprintf(tmp,"%.2f",val);empiler(tmp);}
	   | idf cro cst crf {
	     if(ISdeclared($1)!=0){
		 printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1);
		 return 0;}
		 else {sauvName=strdup($1);
		 sprintf(tabP, "%s[%.0f]", $1, $3);
		 empiler(tabP);
		 } }
	   | idf cro idf crf {
	     if(ISdeclared($1)!=0){
		 printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1); 
		 return 0;}
		 else{
		 if(ISdeclared($3)!=0){
		 printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$3);
		 return 0;}
		 else{sauvName=strdup($1);
		 sprintf(tabP, "%s[%s]", $1, $3);
		 empiler(tabP);
		 } 
		 }}
;


INST_AFF: idf aff{empiler($1);empiler("=");} EXPRESSION  pvg {
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
		  if(sameType($1,val)!=0){
		  val=0;
		  printf("err semantique1:type incompatible!,line:%d,Col:%d\n",nb_ligne,Col);return 0;
		  return 0;}else {
		  if(sauvName != NULL) sauvName=strdup(NULL);
		  }
		  if(sauvName != NULL){
		  if(sameType2($1,sauvName)!=0){
		  sauvName = NULL;
		  printf("err semantique2:type incompatible!,line:%d,Col:%d\n",nb_ligne,Col);
		  return 0;}}
		  }
		  }}
		  empiler(";");

		  }
	    | idf cro cst crf aff {sprintf(tabP, "%s[%.0f]", $1, $3);
		  empiler(tabP);empiler("=");}EXPRESSION pvg {
		  if(ISdeclared($1)!=0){
		  printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1); 
		  return 0;}
		  else{
		  if(IsTable($1)!=0) {
		  printf("err semantique:%s n'est pas un tableau!",$1); return 0;}
		  else{
		  if(sameType($1,val)!=0){val=0;
		  printf("err semantique:type incompatible!,line:%d,Col:%d\n",nb_ligne,Col);
		  return 0;}else {
		  if(sauvName != NULL) sauvName=strdup(NULL);
		  }
		  if(sauvName != NULL){
		  if(sameType2($1,sauvName)!=0){sauvName = NULL;
		  printf("err semantique:type incompatible!,line:%d,Col:%d\n",nb_ligne,Col);
		  return 0;}}
		  }}empiler(";");

		  }
		| idf cro idf crf aff {sprintf(tabP, "%s[%s]", $1, $3);
		  empiler(tabP);empiler("=");}EXPRESSION pvg {
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
		  return 0;}else {
		  if(sauvName != NULL) sauvName=strdup(NULL);
		  }
		  if(sauvName != NULL){
		  if(sameType2($1,sauvName)!=0){sauvName = NULL;
		  printf("err semantique:type incompatible!,line:%d,Col:%d\n",nb_ligne,Col);
		  return 0;}}
		  }}}empiler(";");
	
		  
		  }

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

INST_FOR: D acO INST LIST_INST acF {
		  quadr("+",sauvidf ,sauvfor3, "Tmp");
		  quadr("=", "Tmp","	  ",sauvidf );

		  depiler5(&Z2);
		  quadr("BR", Z2,"	", "	"); 
		  sprintf(tmp,"%d",qc);
	  
		  ajour_quad(atoi(Z2),1,tmp);
		  }
;

D: mc_for po idf dp P1 dp P3 dp P2 pf { if(ISdeclared($3)!=0){
		  printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$3);
		  return 0;}
		  sauvidf=strdup($3);
		  quadr("=", sauvfor1,"	  ", $3);
		  deb_for=qc;
		  sprintf(Z,"%d",deb_for);
		  empiler5(Z);
		 
		  quadr("BG", "",$3, sauvfor);
		  }
;

P1: idf {
	if(ISdeclared($1)!=0){
	printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1);
	return 0;
	}else{
		sauvfor1=strdup($1);
	}
	
	}
  | cst { 
		sprintf(tmp,"%.2f",$1);
		sauvfor1=strdup(tmp); 
		
	} 
;

P3: idf {
	if(ISdeclared($1)!=0){
	printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1);
	return 0;
	}else{
		sauvfor3=strdup($1);
	}
	
	}
  | cst { 
		sprintf(tmp,"%.2f",$1);
		sauvfor3=strdup(tmp); 
		
	} 
;

P2: idf {
	if(ISdeclared($1)!=0){
	printf("err semantique:var non dec!,line:%d, col:%d,E:%s \n",nb_ligne,Col-1,$1);
	return 0;}else{
		sauvfor=strdup($1);
	}  }
  | cst { 
		sprintf(tmp,"%.2f",$1);
		sauvfor=strdup(tmp); 
		
	}
;

OP: sup {empiler(">"); }
  | supE {empiler(">=");}
  | inf {empiler("<");}
  | infE {empiler("<=");}
;

INST_WHILE: C acO INST LIST_INST acF { depiler5(&Z2);
									   
									   quadr("BR", Z2,"	", "	"); 
									   sprintf(tmp,"%d",qc);
									   
									   depiler5(&Z2);
									   if(atoi(Z2) != -1){
										    
											ajour_quad(atoi(Z2),1,tmp);
											deb_wh1 =0;
										}

										depiler5(&Z2);
										
										if(atoi(Z2) != 0){
											
											ajour_quad(atoi(Z2),1,tmp);
											deb_wh2 =0;
										}
										
									 }
;

C: mc_while po COND pf { deb_wh=qc;

						 if(quadCOND(&deb_wh1,&deb_wh2)) {
						 printf("\n err semantique:division par 0!,line:%d, col:%d\n",nb_ligne,Col-1);return 0;
						 }else{
							
							sprintf(Z,"%d",deb_wh2);
							empiler5(Z);
							
							
							sprintf(Z,"%d",deb_wh1);
							empiler5(Z);
							
							sprintf(Z,"%d",deb_wh);
							empiler5(Z);
						 }
						 
					     
					   }
;

INST_IF: A { Fin_if=qc;
			 
			 quadr("BR", "","	", "	"); 
			 sprintf(tmp,"%d",qc);
			 depiler5(&Z2);
			 if(atoi(Z2) != -1){
				ajour_quad(atoi(Z2),1,tmp);
				deb_else =0;
			 }
			 depiler5(&Z2);
			 if(atoi(Z2) != 0){
				ajour_quad(atoi(Z2),1,tmp);
				deb_else2 =0;
			 }
			 sprintf(Z,"%d",Fin_if);
			 empiler5(Z);
			 
             } INST_ELS
	   | A { sprintf(tmp,"%d",qc); 
			 depiler5(&Z2);
             if(atoi(Z2) != -1){
				ajour_quad(atoi(Z2),1,tmp);
				deb_else =0;
			 }
			 depiler5(&Z2);
			 if(atoi(Z2) != 0){
				ajour_quad(atoi(Z2),1,tmp);
				deb_else2 =0;
			 }		 
		   }
;

A:B acO INST LIST_INST acF
;

B:mc_if po COND pf { 
					 if(quadCOND(&deb_else,&deb_else2)) {
					 printf("\n err semantique:division par 0!,line:%d, col:%d\n",nb_ligne,Col-1);return 0;
					 }else{
						sprintf(Z,"%d",deb_else2);
						empiler5(Z);
							
							
						sprintf(Z,"%d",deb_else);
						empiler5(Z);
					 
					 
					 }
				   }
;

INST_ELS: mc_else acO INST LIST_INST acF { sprintf(tmp,"%d",qc);
										   depiler5(&Z2);
										   ajour_quad(atoi(Z2),1,tmp);}
;

COND: EXPRESSION OPP EXPRESSION avec
	| not {empiler("!");} EXPRESSION avec
	| po COND pf avec
;

avec: and {empiler("&");} COND 
	| or {empiler("|");} COND 
	|
;

OPP: OP 
   | egl {empiler("==");}
   | diff {empiler("!=");}
;

%%

int main(){
    yyparse();
	if(errore==0){
		evaluquad();
		afficherL();
		afficher_qdr();

	}

}

int yywrap()
{return 1;}

int yyerror(char *msg){
	printf ("Erreur Syntaxique: line:%d ,Col:%d \n",nb_ligne,Col);
	return 1;

}
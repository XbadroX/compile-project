// flex lex.l
// bison -d syn.y
// gcc lex.yy.c syn.tab.c qad.c -o qc.exe -lfl -ly
// qc<exp.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recursiv.h"


typedef struct qdr{

    char oper[100]; 
    char op1[100];   
    char op2[100];   
    char res[100];  
    
  }qdr;

typedef struct pile {
    char name[20];
    struct pile* svt;     
} Pile;
  
qdr quad[1000];
Pile *P1=NULL,*Q1,*T1,*Qt1;
Pile *P2=NULL,*Q2,*T2,*Qt2;
extern int qc;
int Tmp=1;

void quadr(char opr[],char op1[],char op2[],char res[]){

	strcpy(quad[qc].oper,opr);
	strcpy(quad[qc].op1,op1);
	strcpy(quad[qc].op2,op2);
	strcpy(quad[qc].res,res);
	
qc++;

}

void ajour_quad(int num_quad, int colon_quad, char val []){
	
if (colon_quad==0) strcpy(quad[num_quad].oper,val);
else if (colon_quad==1) strcpy(quad[num_quad].op1,val);
         else if (colon_quad==2) strcpy(quad[num_quad].op2,val);
                   else if (colon_quad==3) strcpy(quad[num_quad].res,val);

}

void afficher_qdr(){
	
printf("\n/*********************Les Quadruplets***********************/\n");

int i;

for(i=0;i<qc;i++){

 printf("\n %d - ( %s  ,  %s  ,  %s  ,  %s )",i,quad[i].oper,quad[i].op1,quad[i].op2,quad[i].res); 
 printf("\n--------------------------------------------------------\n");

}
}

void empiler(char name[]){
	if(P1==NULL){
		P1 = (Pile*)malloc(sizeof(Pile));
		T1 = P1;
			
	}else{
		Q1 = (Pile*)malloc(sizeof(Pile));
		T1->svt = Q1;
		T1 = Q1;
	}
	Q1=NULL;
	strcpy(T1->name,name);
	T1->svt=NULL;
}

void empiler2(char name[]){
	if(P2==NULL){
		P2 = (Pile*)malloc(sizeof(Pile));
		T2 = P2;
			
	}else{
		Q2 = (Pile*)malloc(sizeof(Pile));
		T2->svt = Q2;
		T2 = Q2;
	}
	Q2=NULL;
	strcpy(T2->name,name);
	T2->svt=NULL;
}

void depiler(char** N){

	T1=P1;
	Qt1=P1->svt;
	
	if(Qt1!= NULL){

		while(Qt1->svt != NULL){
			Qt1=Qt1->svt;
			T1=T1->svt;
		}
		*N=strdup(Qt1->name);
		free(Qt1);
		T1->svt=NULL;
	}else{
		*N=strdup(T1->name);
		free(T1);
		P1=NULL;
	}

}

void depiler2(char** N){

	T2=P2;
	Qt2=P2->svt;
	
	if(Qt2!= NULL){

		while(Qt2->svt != NULL){
			Qt2=Qt2->svt;
			T2=T2->svt;
		}
		*N=strdup(Qt2->name);
		free(Qt2);
		T2->svt=NULL;
	}else{
		*N=strdup(P2->name);
		free(T2);
		P2=NULL;
	}

}

void affichPILE(){
	  
	Qt1=P1;
	printf("\ndebut du pile:\n");
	while(Qt1->svt != NULL){
    
        printf("[%s]-->",Qt1->name);
        Qt1=Qt1->svt;
	}
	printf("[%s]",Qt1->name);
	printf("\nfin du pile!\n");
	
}

void affichPILE2(){
	  
	Qt2=P2;
	printf("\ndebut du pile:\n");
	while(Qt2->svt != NULL){
    
        printf("[%s]-->",Qt2->name);
        Qt2=Qt2->svt;
	}
	printf("[%s]",Qt2->name);
	printf("\nfin du pile!\n");
	
}

void EvaluExpre(){ 
	char Op1[10],Op2[10],Opr[10],Res[10],OP[10];
	char* X;
	depiler(&X);
	depiler(&X);
	empiler(X);
	strcpy(Res,X);
	etap1();
	int pof=0;
		
	depiler2(&X);
	if(strcmp(X,"=")==0) empiler(Res);
	while(strcmp(X,"=")!=0){
		
		while(strcmp(X,"(")==0){
			pof++;
			depiler2(&X);
		}
			
		strcpy(Op1,X);
		depiler2(&X);
		strcpy(Opr,X);
		depiler2(&X);	
		strcpy(Op2,X);
		sprintf(Res,"Tmp%d",Tmp);Tmp++;
			
		quadr(Opr,Op1,Op2,Res);
			
		if(P2!=NULL){
				
			depiler2(&X);
			if(strcmp(X,")")==0 && pof==1){
				pof--;
				if(P2!=NULL){ 
					depiler2(&X);
					if(strcmp(X,")")==0) empiler2(X);
				}
			}else{
				if(strcmp(X,")")==0 && pof==0) empiler2(X);

			}
			
			if(P2!=NULL){
				if(strcmp(X,")")!=0){ 
					empiler2(X);
					strcpy(OP,X);
				}
			}else strcpy(OP,"Vide");
			empiler2(Res);
			if(strcmp(X,")")==0){
				depiler(&X);
				if(strcmp(X,"(")!=0){
					if(strcmp(X,"=")==0) {
						empiler(X);
						empiler(Res);
						break;
					}
					empiler2(X);
					etap2(X);
					depiler2(&X);
				}else{
					char* Y;
					while(strcmp(X,"(")==0){
						depiler2(&X);
						depiler2(&X);
						if(P2!=NULL){	
							depiler2(&Y);
							empiler2(Y);
							if(strcmp(Y,")")!=0){
								empiler2(Res);
								break;
							}
						}
						else{
							Y=strdup("Vide");
							depiler(&X);
							break;
						}
						empiler2(Res);
						depiler(&X);
					}
					if(strcmp(X,"=")==0){
						empiler(X);
						empiler(Res);
						break;
					}else{
						if(strcmp(Y,"Vide")==0){
							
							empiler2(Res);
							empiler2(X);
							etap2(X);
							depiler2(&X);
							
						}else{
							etap3(Y);
							depiler2(&X);
						}
					}
				}
			}else {
				if(pof==0){ 
					if(strcmp(OP,"Vide")!=0) {
						etap3(OP); 
					}
					else{
					depiler(&X);
					empiler2(X);
					etap2(X);
					}
				}
				 
				depiler2(&X);  
			}
			
		}else{
			depiler(&X);
			if(strcmp(X,"=")!=0){
				empiler2(Res);
				empiler2(X);
				etap2(X);
				depiler2(&X);
			}else{
				empiler(X);
				empiler(Res);
			}
		}
	}
	//affichPILE();
	if(P2!=NULL) depiler2(&X);
	//if(P2!=NULL) affichPILE2();
	depiler(&X);
	strcpy(Op1,X);
	depiler(&X);
	strcpy(Opr,X);
	depiler(&X);
	strcpy(Op2,X);
	
	quadr(Opr,Op1,"   ",Op2);

}


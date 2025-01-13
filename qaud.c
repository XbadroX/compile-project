#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recursiv.h"
#include "TSL.h"

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
Pile *P3=NULL,*Q3,*T3,*Qt3;
Pile *P4=NULL,*Q4,*T4,*Qt4;
Pile *P5=NULL,*Q5,*T5,*Qt5;
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

void empiler3(char name[]){
	if(P3==NULL){
		P3 = (Pile*)malloc(sizeof(Pile));
		T3 = P3;
			
	}else{
		Q3 = (Pile*)malloc(sizeof(Pile));
		T3->svt = Q3;
		T3 = Q3;
	}
	Q3=NULL;
	strcpy(T3->name,name);
	T3->svt=NULL;
}

void empiler4(char name[]){
	if(P4==NULL){
		P4 = (Pile*)malloc(sizeof(Pile));
		T4 = P4;
			
	}else{
		Q4 = (Pile*)malloc(sizeof(Pile));
		T4->svt = Q4;
		T4 = Q4;
	}
	Q4=NULL;
	strcpy(T4->name,name);
	T4->svt=NULL;
}

void empiler5(char name[]){
	if(P5==NULL){
		P5 = (Pile*)malloc(sizeof(Pile));
		T5= P5;
			
	}else{
		Q5 = (Pile*)malloc(sizeof(Pile));
		T5->svt = Q5;
		T5 = Q5;
	}
	Q5=NULL;
	strcpy(T5->name,name);
	T5->svt=NULL;
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

void depiler3(char** N){

	T3=P3;
	Qt3=P3->svt;
	
	if(Qt3!= NULL){

		while(Qt3->svt != NULL){
			Qt3=Qt3->svt;
			T3=T3->svt;
		}
		*N=strdup(Qt3->name);
		free(Qt3);
		T3->svt=NULL;
	}else{
		*N=strdup(P3->name);
		free(T3);
		P3=NULL;
	}

}

void depiler4(char** N){

	T4=P4;
	Qt4=P4->svt;
	
	if(Qt4!= NULL){

		while(Qt4->svt != NULL){
			Qt4=Qt4->svt;
			T4=T4->svt;
		}
		*N=strdup(Qt4->name);
		free(Qt4);
		T4->svt=NULL;
	}else{
		*N=strdup(P4->name);
		free(T4);
		P4=NULL;
	}

}

void depiler5(char** N){

	T5=P5;
	Qt5=P5->svt;
	
	if(Qt5!= NULL){

		while(Qt5->svt != NULL){
			Qt5=Qt5->svt;
			T5=T5->svt;
		}
		*N=strdup(Qt5->name);
		free(Qt5);
		T5->svt=NULL;
	}else{
		*N=strdup(P5->name);
		free(T5);
		P5=NULL;
	}

}

void affichPILE(){
	  
	Qt1=P1;
	if(Qt1 == NULL) {printf("\npile1 vide!:\n");return; }
	printf("\ndebut du pile1:\n");
	while(Qt1->svt != NULL){
    
        printf("[%s]-->",Qt1->name);
        Qt1=Qt1->svt;
	}
	printf("[%s]",Qt1->name);
	printf("\nfin du pile1!\n");
	
}

void affichPILE2(){
	  
	Qt2=P2;
	if(Qt2 == NULL) {printf("\npile2 vide!:\n");return; }
	printf("\ndebut du pile2:\n");
	while(Qt2->svt != NULL ){
    
        printf("[%s]-->",Qt2->name);
        Qt2=Qt2->svt;
	}
	printf("[%s]",Qt2->name);
	printf("\nfin du pile2!\n");
	
}

void affichPILE3(){
	  
	Qt3=P3;
	if(Qt3 == NULL) {printf("\npile3 vide!:\n");return; }
	printf("\ndebut du pile3:\n");
	while(Qt3->svt != NULL ){
    
        printf("[%s]-->",Qt3->name);
        Qt3=Qt3->svt;
	}
	printf("[%s]",Qt3->name);
	printf("\nfin du pile3!\n");
	
}

void affichPILE4(){
	  
	Qt4=P4;
	if(Qt4 == NULL) {printf("\npile4 vide!:\n");return; }
	printf("\ndebut du pile4:\n");
	while(Qt4->svt != NULL ){
    
        printf("[%s]-->",Qt4->name);
        Qt4=Qt4->svt;
	}
	printf("[%s]",Qt4->name);
	printf("\nfin du pile4!\n");
	
}

void affichPILE5(){
	  
	Qt5=P5;
	if(Qt5 == NULL) {printf("\npile5 vide!:\n");return; }
	printf("\ndebut du pile5:\n");
	while(Qt5->svt != NULL ){
    
        printf("[%s]-->",Qt5->name);
        Qt5=Qt5->svt;
	}
	printf("[%s]",Qt5->name);
	printf("\nfin du pile5!\n");
	
}

int EvaluExpre2(char opr[],char op1[],char op2[]){
	float i,j,k;
	char* token;
	char* X;
	char res[100];
	if(ISExist(op1)==0){
		
		if(op1[0]=='-'){
			
			i=atof(op1);
		}else{
			
			if(op1[0]=='T'){
				depiler3(&X);
				i=atof(X);
			}else{
				i=atof(op1);
			}

		}

	}else{

		i=Valeur(op1);
	}

	if(ISExist(op2)==0){
		if(op2[0]=='-'){
			j=atof(op2);
		}else{
			if(op2[0]=='T'){
				depiler3(&X);
				j=atof(X);
			}else{
				j=atof(op2);
			}
	
		}
	}else{
		j=Valeur(op2);

	}
	
	switch(opr[0]){
		
		case '+':k=i+j;break;	
		case '-':k=i-j;break;
		case '*':k=i*j;break;
		case '/':if(j!=0) k=i/j;
				 else{
					 return 1;
				 }
				 break;
	}
	sprintf(res,"%f",k);
	empiler3(res);


	return 0;
	
}

int quadExpre(){ 
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
	while(strcmp(X,"=")!=0 ){
		
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
		if(EvaluExpre2(Opr,Op1,Op2)) return 1;	
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
				if(strcmp(X,"fin")==0) return 0;
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
			if(P1 == NULL) return 0;
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
	if(P1 == NULL) return 0;
	if(P2!=NULL) depiler2(&X);

	depiler(&X);
	strcpy(Op1,X);
	depiler(&X);
	strcpy(Opr,X);
	depiler(&X);
	strcpy(Op2,X);
	
	quadr(Opr,Op1,"   ",Op2);
	float VAL;
	if(P3!=NULL){
		depiler3(&X);
		VAL=atof(X);
		if(strcmp(TYPE(Op2),"INTEGER")==0) VAL=(int)VAL;
		insererval(Op2,VAL);
	}else{
		if(ISExist(Op1)==0){
			VAL=atof(Op1);
		}else{
			VAL=Valeur(Op1);
		}
		insererval(Op2,VAL);
	}

	return 0;

}

char* flag(char opr[]){
	if(strcmp(opr,"==")==0) return "BNE";
	if(strcmp(opr,"!=")==0) return "BE";
	if(strcmp(opr,"<")==0) return "BGE";
	if(strcmp(opr,"<=")==0) return "BG";
	if(strcmp(opr,">")==0) return "BLE";
	if(strcmp(opr,">=")==0) return "BL";
}

char* oprswitch(char opr[]){
	if(strcmp(opr,"==")==0) return "!=";
	if(strcmp(opr,"!=")==0) return "==";
	if(strcmp(opr,"<")==0) return ">=";
	if(strcmp(opr,"<=")==0) return ">";
	if(strcmp(opr,">")==0) return "<=";
	if(strcmp(opr,">=")==0) return "<";
}

int quadCOND(int* Delse,int* Delse2){
	char* X;
	char Op1[10],Op2[10],Opr[10],tmp[10];
	int Dif=0;
	while(P1 != NULL){
		depiler(&X);
		empiler4(X);
		
	}
	
	
	depiler4(&X);
	if(strcmp(X,"!")==0){
		strcpy(Op1,"0");
		depiler4(&X);
		strcpy(Op2,X);
		if(P4 != NULL){
			depiler4(&X);
			if(strcmp(X,"|")==0) {
				Dif=qc;
				quadr("BZ","",Op2,"    ");
				*Delse=-1;
				
				
			}else{
				*Delse=qc;

				quadr("BNZ","",Op2,"	");
			}
			
			depiler4(&X);
			if(strcmp(X,"!")==0){
				strcpy(Op1,"0");
				depiler4(&X);
				strcpy(Op2,X);
				*Delse2=qc;
				quadr("BNZ","",Op2,"	");
				if(Dif != 0) {
					sprintf(tmp,"%d",qc);
					ajour_quad(Dif,1,tmp);}
				return 0;
				
			}
			strcpy(Op1,X);
			depiler4(&X);
			if(strcmp(Op1,"(")==0 ||  X[0]=='/' || X[0]=='*' || X[0]=='-' || X[0]=='+'  ){
				
				empiler("fin");
				empiler(Op1);
				empiler(X);
				while(1){
					depiler4(&X);
					if(X[0]=='<' || X[0]=='>' || X[0]=='!' || X[0]=='=' ) break;
					empiler(X);
				}
				strcpy(Opr,X);//partie2 after && ||

				empiler(";");
				if( quadExpre()) return 1;
				while(P3 != NULL) depiler3(&X);
				strcpy(Op1,quad[qc-1].res);
				
				
				
			}else{
				strcpy(Opr,X);
			}
			
			depiler4(&X);
			if(P4!=NULL){
				empiler("fin");
				empiler(X);
				while(P4 != NULL){
					depiler4(&X);
					empiler(X);
				}
				empiler(";");
				if( quadExpre()) return 1;
				while(P3 != NULL) depiler3(&X);
				strcpy(Op2,quad[qc-1].res);

					
			}else{
				strcpy(Op2,X);

			}
			*Delse2=qc;

			quadr(flag(Opr),"",Op1,Op2);
			if(Dif != 0) {
					sprintf(tmp,"%d",qc);
					ajour_quad(Dif,1,tmp);
			}
			while(P2 != NULL) depiler2(&X);
			return 0;

		}else{
			*Delse =qc;
			quadr("BNZ","",Op2,"	");
			return 0;
		}
		
	}else{
		strcpy(Op1,X);
		depiler4(&X);
		if( strcmp(Op1,"(")==0 ||  X[0]=='/' || X[0]=='*' || X[0]=='-' || X[0]=='+'  ){
			empiler("fin");
			empiler(Op1);
			empiler(X);
			while(1){
				depiler4(&X);
				if(X[0]=='<' || X[0]=='>' || X[0]=='!' || X[0]=='=' ) break;
				empiler(X);
			}
			strcpy(Opr,X);
			empiler(";");

			if( quadExpre()) return 1;
			while(P3 != NULL) depiler3(&X);
			strcpy(Op1,quad[qc-1].res);
		}else{
			strcpy(Opr,X);
			
		}
		depiler4(&X);
		strcpy(Op2,X);
		if(P4 != NULL) depiler4(&X);
		if( strcmp(Op2,"(")==0 ||  X[0]=='/' || X[0]=='*' || X[0]=='-' || X[0]=='+'  ){
				empiler("fin");
				empiler(Op2);
				empiler(X);
				while(1){
					depiler4(&X);
					if(X[0]=='&' || X[0]=='|' || P4 == NULL  ) break;
					empiler(X);
				}
				empiler(";");

				if( quadExpre()) return 1;
				while(P3 != NULL) depiler3(&X);
				strcpy(Op2,quad[qc-1].res);
		}
		if(P4 ==NULL){
			*Delse=qc;
			quadr(flag(Opr),"",Op1,Op2);
			while(P2 != NULL) depiler2(&X);
			return 0;
			
		}else{
			if(strcmp(X,"|")==0) {
				Dif=qc;
				quadr(flag(oprswitch(Opr)),"",Op1,Op2);
				*Delse=-1;
				
			}else{
				*Delse=qc;
				quadr(flag(Opr),"",Op1,Op2);
			}
			
			depiler4(&X);
			if(strcmp(X,"!")==0){
				strcpy(Op1,"0");
				depiler4(&X);
				strcpy(Op2,X);
				*Delse2=qc;
				quadr("BNZ","",Op2,"	");
				if(Dif != 0) {
					sprintf(tmp,"%d",qc);
					ajour_quad(Dif,1,tmp);}
				while(P2 != NULL) depiler2(&X);
				return 0;
				
			}
			strcpy(Op1,X);
			depiler4(&X);
			if(strcmp(Op1,"(")==0 ||  X[0]=='/' || X[0]=='*' || X[0]=='-' || X[0]=='+'  ){
				empiler("fin");
				empiler(Op1);
				empiler(X);
				while(1){
					depiler4(&X);
					if(X[0]=='<' || X[0]=='>' || X[0]=='!' || X[0]=='=' ) break;
					empiler(X);
				}
				strcpy(Opr,X);
				empiler(";");

				if( quadExpre()) return 1;
				while(P3 != NULL) depiler3(&X);
				strcpy(Op1,quad[qc-1].res);

			}else{
				strcpy(Opr,X);
			}	
			depiler4(&X);
			if(P4!=NULL){
				empiler("fin");
				empiler(X);
				while(P4 != NULL){
					depiler4(&X);
					empiler(X);
				}
				empiler(";");

				if( quadExpre()) return 1;
				while(P3 != NULL) depiler3(&X);
				strcpy(Op2,quad[qc-1].res);
					
			}else{
				strcpy(Op2,X);
					
				
			}
			*Delse2=qc;
			quadr(flag(Opr),"",Op1,Op2);
			if(Dif != 0) {
					sprintf(tmp,"%d",qc);
					ajour_quad(Dif,1,tmp);}
			while(P2 != NULL) depiler2(&X);
			return 0;
			
		
					
		}
	
	}

}

void evaluquad(){
	
	int QC=0,k;
	float i,j;
	char* X;
	initIDF();
	while(P3 != NULL) depiler3(&X);
	while(QC != qc ){
		if(strcmp(quad[QC].oper,"=")==0){
			float VAL;
			if(P3!=NULL){
				depiler3(&X);
				VAL=atof(X);
				if(strcmp(TYPE(quad[QC].res),"INTEGER")==0) VAL=(int)VAL;
				insererval(quad[QC].res,VAL);
			}else{
				if(ISExist(quad[QC].op1)==0){
					VAL=atof(quad[QC].op1);
				}else{
					VAL=Valeur(quad[QC].op1);
				}
				insererval(quad[QC].res,VAL);
			}
			QC++;
			if(QC==qc) return ;
		}else{
			if((quad[QC].oper)[0]=='B'){
				if(strcmp(quad[QC].oper,"BR")==0){
					QC=atoi(quad[QC].op1);
				}else{
					if(ISExist(quad[QC].op2)==0){
		
						if((quad[QC].op2)[0]=='-'){
			
							i=atof(quad[QC].op2);
						}else{
			
							if((quad[QC].op2)[0]=='T'){
								depiler3(&X);
								i=atof(X);
							}else{
								i=atof(quad[QC].op2);
								}
						}

					}else{

						i=Valeur(quad[QC].op2);
					}
					if(strcmp(quad[QC].oper,"BZ")==0){
						if(i==0) QC=atoi(quad[QC].op1);
						else QC++;
					}else{
						if(strcmp(quad[QC].oper,"BNZ")==0){
							if(i != 0) QC=atoi(quad[QC].op1);
							else QC++;
						}else{
							if(ISExist(quad[QC].res)==0){
								if((quad[QC].res)[0]=='-'){
									j=atof(quad[QC].res);
								}else{
									if((quad[QC].res)[0]=='T'){
										depiler3(&X);
										j=atof(X);
									}else{
										j=atof(quad[QC].res);
									}	
								}
							}else{
								j=Valeur(quad[QC].res);
							}					
							if(strcmp(quad[QC].oper,"BE")==0){
								if(i==j) QC=atoi(quad[QC].op1);
								else QC++;
							}
							if(strcmp(quad[QC].oper,"BNE")==0){
								if(i!=j) QC=atoi(quad[QC].op1);
								else QC++;
							}
							if(strcmp(quad[QC].oper,"BG")==0){
								if(i>j) QC=atoi(quad[QC].op1);
								else QC++;
							}
							if(strcmp(quad[QC].oper,"BGE")==0){
								if(i>=j) QC=atoi(quad[QC].op1);
								else QC++;
							}
							if(strcmp(quad[QC].oper,"BL")==0){
								if(i<j) QC=atoi(quad[QC].op1);
								else QC++;
							}
							if(strcmp(quad[QC].oper,"BLE")==0){
								if(i<=j) QC=atoi(quad[QC].op1);
								else QC++;
							}
						}
					}
				}
				
			}else{
				k=EvaluExpre2(quad[QC].oper,quad[QC].op1,quad[QC].op2);
				QC++;
				if(QC==qc) return ;
			}
		}
	}
}


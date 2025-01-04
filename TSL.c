/*
flex lexical2.l
bison -d syntax2.y
gcc lex.yy.c syntax2.tab.c TSL.c qaud.c -o tpp.exe -lfl -ly
tpp<exp.txt
*/
/****************CREATION DE LA TABLE DES SYMBOLES ******************/
/***Step 1: Definition des structures de données ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    char name[20];
    char code[20];
    char type[20];
    float val;
	int size;
    struct list* svt;     
} Plist;

typedef struct list2 {
    char name[20];
    char type[20];             
    struct list2* svt;    
} P2list;

Plist *tab=NULL,*T,*Q,*Qt;
P2list *tabs=NULL,*Ts ,*tabm=NULL,*Tm,*P,*Pt;

/***Step 3: insertion des entititées lexicales dans les tables des symboles ***/
void inserer (char entite[], char code[],char type[],float val, int y,int s){
	int v = (int)val;
	if(strcmp(code, "CST")==0){
	if(v == val ){
		//strcpy(type ,"INTEGER");
		type=strdup("INTEGER");
	}else{
		//strcpy(type ,"FLOAT");
		type=strdup("FLOAT");
	}
	}
	
  switch (y)
 { 
   case 0:/*insertion dans la table des IDF et CONST*/
		if(tab==NULL){
			tab = (Plist*)malloc(sizeof(Plist));
			T=tab;
			
		}else{
			Q = (Plist*)malloc(sizeof(Plist));
			T->svt = Q;
			T=Q;
			
	   }
	   Q=NULL;
       strcpy(T->name,entite);
	   strcpy(T->code , code);
	   strcpy(T->type , type);
	   T->val = val;
	   T->size = s;
	   T->svt =NULL;
		
	   break;

   case 1:/*insertion dans la table des mots clés*/
       if(tabm==NULL){
			tabm = (P2list*)malloc(sizeof(P2list));
			Tm=tabm;
			
		}else{
			P= (P2list*)malloc(sizeof(P2list));
			Tm->svt = P;
			Tm=P;
	   }
	   P=NULL;
       strcpy(Tm->name , entite);
	   strcpy(Tm->type , code);
	   Tm->svt =NULL;
       break; 
    
   case 2:/*insertion dans la table des séparateurs*/
      if(tabs==NULL){
			tabs = (P2list*)malloc(sizeof(P2list));
			Ts=tabs;
			
		}else{
			P= (P2list*)malloc(sizeof(P2list));
			Ts->svt = P;
			Ts=P;
	   }
	   P=NULL;
       strcpy(Ts->name , entite);
	   strcpy(Ts->type , code);
	   Ts->svt =NULL;
       break; 
 }

}

/***Step 4: La fonction Rechercher permet de verifier  si l'entité existe dèja dans la table des symboles */
void rechercher (char entite[], char code[],char type[],float val,int y,int s)	{

int i=0;

switch(y) 
  {
   case 0:/*verifier si la case dans la tables des IDF et CONST est libre*/
        if(tab==NULL){
			inserer(entite,code,type,val,0,s);
			break;
			
		}else{
			Qt=tab;
			while(Qt != NULL && i==0){
				if(strcmp(Qt->name , entite)==0)
					i=1;
				
				Qt=Qt->svt;
			}
			Qt=NULL;
			if(i==0){
				inserer(entite,code,type,val,0,s);
				break;
			}
		}
		
		break;
		
   case 1:
			/*verifier si la case dans la tables des mots clés est libre*/
       
       if(tabm==NULL){
			inserer(entite,code,type,val,1,s);
			break;
			
		}else{
			Pt=tabm;
			while(Pt != NULL && i==0){
				if(strcmp(Pt->name , entite)==0)
					i=1;
				
				Pt=Pt->svt;
			}
			Pt=NULL;
			if(i==0){
				inserer(entite,code,type,val,1,s);
				break;
			}
		}
		
		break;
   
   case 2:/*verifier si la case dans la tables des séparateurs est libre*/
         if(tabs==NULL){
			inserer(entite,code,type,val,2,s);
			break;
			
		}else{
			Pt=tabs;
			while(Pt != NULL && i==0){
				if(strcmp(Pt->name , entite)==0)
					i=1;
				
				Pt=Pt->svt;
			}
			Pt=NULL;
			if(i==0){
				inserer(entite,code,type,val,2,s);
				break;
			}
		}
		
		break;
		 

  }

}

/***Step 5 L'affichage du contenue de la table des symboles ***/
void afficherL(){


printf("\n/***************Table DES symboles IDF*************/\n");
printf("_______________________________________________________________________________\n");
printf("\t| Nom_Entite |  Code_Entite | Type_Entite | Val_Entite | taille_Entite\n");
printf("_______________________________________________________________________________\n");
  
Qt=tab;
while(Qt != NULL){
    
        printf("\t|%11s |%13s | %11s | %10f | %13d\n",Qt->name,Qt->code,Qt->type,Qt->val,Qt->size);
        Qt=Qt->svt;
}  
Qt=NULL;

 
printf("\n/***************Table des symboles mots clés*************/\n");

printf("_____________________________________\n");
printf("\t| NomEntite |  CodeEntite | \n");
printf("_____________________________________\n");
Pt=tabm;
while(Pt != NULL){
        printf("\t|%10s |%12s | \n",Pt->name, Pt->type);
        Pt=Pt->svt;
}
Pt=NULL;

printf("\n/***************Table des symboles séparateurs*************/\n");

printf("_____________________________________\n");
printf("\t| NomEntite |  CodeEntite | \n");
printf("_____________________________________\n");
  
Pt=tabs;
while(Pt != NULL){
        printf("\t|%10s |%12s | \n",Pt->name, Pt->type);
        Pt=Pt->svt;
}
Pt=NULL;

}

void insererType(char entite[], char type[]){
	
	Q=tab;
	while(Q != NULL ){
		if(strcmp(Q->name , entite)==0){
			strcpy(Q->type , type);
			
			break;
		}
		Q=Q->svt;
		
	}
	Q=NULL;

	
}

void CstCode(char entite[]){
	Q=tab;
	while(Q != NULL ){
		if(strcmp(Q->name , entite)==0){
			strcpy(Q->code , "CST");
			
			break;
		}
		Q=Q->svt;
		
	}
	Q=NULL;
	
}

int doubleDeclaration(char entite[]){
	int i=0;
	Q=tab;
	while(Q != NULL ){
		if(strcmp(Q->name , entite)==0 && strcmp(Q->type , " ")!=0){
			
			i=1;
			break;
		}
		Q=Q->svt;
		
	}
	Q=NULL;
	
	return i;
	
}

int ISdeclared(char entite[]){
	int i=0;
	Q=tab;
	while(Q != NULL ){
		if(strcmp(Q->name , entite)==0 && strcmp(Q->type , " ")==0){
			
			i=1;
			break;
		}
		Q=Q->svt;
		
	}
	Q=NULL;
	
	return i;
	
}

int sameType(char entite[],float val){
	int i =0;
	char type1[10];
	char type2[10];
	Q=tab;
	Plist *p;
	while(Q != NULL ){
		if(strcmp(Q->name , entite)==0){
			strcpy(  type1,Q->type);
			p=Q;
		}
		if(Q->val==val){
			strcpy(  type2,Q->type);
		}
		Q=Q->svt;
		
	}
	Q=NULL;
	if(strcmp(type2 , type1)!=0 && strcmp(type1 , "FLOAT")!=0){
		i=1;
	}else{
		p->val=val;
	
	}
	if(val == 0) i= 0;
	
	return i;
}

void insererSize(char entite[], int s){
	
	Q=tab;
	while(Q != NULL ){
		if(strcmp(Q->name , entite)==0){
			Q->size=s;
			
			break;
		}
		Q=Q->svt;
		
	}
	Q=NULL;

	
}

int NotTable(char entite[]){
	
	int i=0;
	Q=tab;
	while(Q != NULL ){
		if(strcmp(Q->name , entite)==0 && Q->size != 0 ){
			i=1;
			break;
		}
		Q=Q->svt;
		
	}
	Q=NULL;
	
	return i;
}

int IsTable(char entite[]){
	
	int i=0;
	Q=tab;
	while(Q != NULL ){
		if(strcmp(Q->name , entite)==0 && Q->size == 0 ){
			i=1;
			break;
		}
		Q=Q->svt;
		
	}
	Q=NULL;
	
	return i;
}

void Delete(char entite[]){
	
	
	T=tab;
	Q=tab->svt;
	
	while(Q != NULL ){
		if(strcmp(Q->name , entite)==0 && strcmp(Q->type , " ")==0){
			
			T->svt=Q->svt;
			Q->svt=NULL;
			free(Q);
			break;
		}
		T=T->svt;
		Q=Q->svt;   
		
	}
	Q=NULL;

	
}

int IsCST(char entite[]){
	int i=1;
	Q=tab;
	while(Q != NULL ){
		if(strcmp(Q->name , entite)==0 && strcmp(Q->code ,"CST")==0){
			i=0;
			break;
		}
		Q=Q->svt;
		
	}
	Q=NULL;
	
	return i;
	
}

int sameType2(char entite[],char entite2[]){
	int i =0;
	char type1[10];
	char type2[10];
	Q=tab;
	Plist *p,*q;
	
	while(Q != NULL ){
		if(strcmp(Q->name , entite)==0){
			strcpy(  type1,Q->type);
			p=Q;
		}
		if(strcmp(Q->name , entite2)==0){
			strcpy(  type2,Q->type);
			q=Q;
		}
		Q=Q->svt;
		
	}
	Q=NULL;
	if(strcmp(type2 , type1)!=0 && strcmp(type1 , "FLOAT")!=0){
		i=1;
	}else{
		p->val=q->val;
	}
	return i;
}


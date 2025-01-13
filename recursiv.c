#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recursiv.h"
#include "qaud.h"


void etap3(char opar[]){
	char* X;
	
	depiler(&X);
	if(strcmp(X,"fin")==0) return;
	if(strcmp(X,"(")==0) {empiler2(X);return;}
	else{
	if(strcmp(X,"*")==0 || strcmp(X,"/")==0){
		if(strcmp(opar,"+")==0 || strcmp(opar,"-")==0){
			empiler2(X);
			etap2(X);
		}else empiler(X);
			
	}else empiler(X);}
	
	
}

void etap2(char opar[]){
	char* X;
	depiler(&X);
	empiler2(X);
	if(strcmp(X,")")==0) etap1();
	else{

		etap3(opar);
	}
	
	
}

void etap1(){
	char* X;
	depiler(&X);
	empiler2(X);
	while(strcmp(X,")")==0){
		depiler(&X);
		empiler2(X);	
	}
	depiler(&X);
	if(strcmp(X,"=")==0){
		depiler2(&X);
		empiler2("=");
		empiler("=");
		return;
	}
	empiler2(X);
	etap2(X);
	
}
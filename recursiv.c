#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recursiv.h"
#include "qaud.h"
// gcc lex.yy.c syntax2.tab.c TSL.c qaud.c recursiv.c -o tpp.exe -lfl -ly 

/*
// Function definitions
void funcA(int n) {
    if (n <= 0) {
        printf("funcA: Base case reached with n = %d\n", n);
        return;
    }
    printf("funcA: n = %d\n", n);
    funcB(n - 1); // Call funcB
}

void funcB(int n) {
    if (n <= 0) {
        printf("funcB: Base case reached with n = %d\n", n);
        return;
    }
    printf("funcB: n = %d\n", n);
    funcC(n - 1); // Call funcC
}

void funcC(int n) {
    if (n <= 0) {
        printf("funcC: Base case reached with n = %d\n", n);
        return;
    }
    printf("funcC: n = %d\n", n);
    funcA(n - 1); // Call funcA
}
*/


void etap3(char opar[]){
	char* X;
	depiler(&X);
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
		//depiler(&X);
		//empiler2(X);
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
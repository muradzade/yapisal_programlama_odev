#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myfunctions.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*
kilavuz olarak
1 char
2 float
3 long double
4 long
5 double
6 int
7 File
*/
//Var *degiskenler; // 7 tip degisken oldugu icin 7 boyutlu

extern char *degiskenler[8];

int main(int argc, char *argv[]) {

	//printf(">PseudocodeConverter ");
	char *pseudokod=argv[1], *ckodu=argv[2];
	//pseudokod=SatirAl(stdin);
//	ckodu=SatirAl(stdin);
	Cevir(pseudokod,ckodu);
	char *str=NULL;
	str=StringEkle(str,"./");
	int i=0;
	while(ckodu[i]!='.')
	{
		str=CharEkle(str,ckodu[i]);
		i++;
	}
	
	system("gcc -o cikti cikti.c");
	printf("Executable dosya olusturuldu\n");
	char *args[]={str,NULL}; 
	execvp(args[0],args);
	return 0;
}

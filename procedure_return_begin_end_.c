#include <stdio.h>
#include <string.h>
#include "myfunctions.h"

char* procedure(char* satirI)
{
	char *satirO=NULL ;
	char* satir = GetStrBetweenStrings(satirI,0,"procedure ",")");
	Var degisken;
	int i=0;
	while(satir[i])
	{
		if(HarfMi(satir[i]))
		{
			char *degiskenMi=NULL;
			while(HarfMi(satir[i]) || satir[i]=='_' || rakamMi(satir[i]))
			{
				degiskenMi=CharEkle(degiskenMi,satir[i]);
				i++;
			}
			if(ReservedWordControl(degiskenMi,"main"))
			{
				satirO=StringEkle(satirO,"main");
			}
			else if(Strstr(degiskenMi,"_",0)!=-1)
			{
				degisken=DegiskenTespit(degiskenMi);
				satirO=StringEkle(satirO,degisken._type);
				satirO=StringEkle(satirO,degisken._name);
			}
			else
				satirO=StringEkle(satirO,degiskenMi);
		}
		
		else
		{
			satirO=CharEkle(satirO,satir[i]);
			i++;
		}
	}
	//parantez ')' ilk basda kirparken gittigi icin simdi eklemek lazim
	satirO=CharEkle(satirO,')');
	
	return satirO;
}


Var Return(char* satirI)
{
	degiskenleriAl(satirI);
	char* satirO=NULL ;
	satirO = StringEkle(satirO,"return ");
	Var degisken;
	int i=0;
	while(satirI[i])
	{
		if(HarfMi(satirI[i]))
		{
			char *degiskenMi=NULL;
			while(HarfMi(satirI[i]) || satirI[i]=='_' || rakamMi(satirI[i]) )
			{
				degiskenMi=CharEkle(degiskenMi,satirI[i]);
				i++;
			}
			if(Strstr(degiskenMi,"_",0)!=-1)
			{
				degisken = DegiskenTespit(degiskenMi);
			}	
			else if (Strstr(degiskenMi,"void",0)!=-1)
			{
				degisken._name=(degisken._name,"void");
				degisken._type=NULL;
				degisken._format=NULL;
			}
		}
		else
			i++;
	}
	return degisken;
}

char* begin()
{
	char* satirO=NULL;
	satirO=CharEkle(satirO,'{');
	return satirO;
}

char* end()
{
	char* satirO=NULL;
	satirO=CharEkle(satirO,'}');
	return satirO;
}

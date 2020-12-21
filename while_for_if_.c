#include <stdio.h>
#include <string.h>
#include "myfunctions.h"

char* while_do(char* satirI) 
{
	int i=0;
	char* satirO=NULL;
	satirO=StringEkle(satirO,"while");
	char *parantezArasi=GetStrBetweenStrings(satirI,0,"while","do");
	Var tespitOlunmusDegisken;
	degiskenleriAl(satirI);
	
	while(parantezArasi[i]) //sonda segisken olursa NULL'da isleme dahil olsun diye i-1
	{
		if(HarfMi(parantezArasi[i]))
		{
			char* degisken=NULL;// degisken ihtimali
			while(HarfMi(parantezArasi[i]) || parantezArasi[i]=='_' || rakamMi(parantezArasi[i]))
			{
				degisken=CharEkle(degisken,parantezArasi[i]);
				i++;
			}
				
			if(Strstr(degisken,"_",0)!=-1 && Strstr(degisken,"not_equal",0)==-1)
			{
				tespitOlunmusDegisken=DegiskenTespit(degisken);
				satirO = StringEkle(satirO,tespitOlunmusDegisken._name);
				
				free(tespitOlunmusDegisken._name);
				free(tespitOlunmusDegisken._type);
				free(tespitOlunmusDegisken._format);
			}					
			else if(Strstr(degisken,"and",0)!=-1)
			{
				satirO=StringEkle(satirO,"&&");
			}
			else if(Strstr(degisken,"or",0)!=-1)
			{
				satirO=StringEkle(satirO,"||");
			}
			else if(Strstr(degisken,"equal",0)!=-1)
			{
				satirO=StringEkle(satirO,"==");
			}
			else if(Strstr(degisken,"not_equal",0)!=-1)
			{
				satirO=StringEkle(satirO,"!=");
			}
			
			free(degisken);	
		}
		else
		{
			satirO = CharEkle(satirO,parantezArasi[i]);
			i++;
		}
	}		
	return satirO;
}


char* for_loop(char* satirI) 
{
	int i=0;
	char* satirO=NULL;
	Var tespitOlunmusDegisken;
	degiskenleriAl(satirI);
	
	satirO=StringEkle(satirO,"for(");
	char *parantezArasi=GetStrBetweenStrings(satirI,0,"for","loop");
	while(parantezArasi[i]) 
	{
		if(HarfMi(parantezArasi[i]))
		{
			char* degisken=NULL;
			while(HarfMi(parantezArasi[i]) || parantezArasi[i]=='_' || rakamMi(parantezArasi[i]))
			{
				degisken=CharEkle(degisken,parantezArasi[i]);
				i++;
			}
			
			if(Strstr(degisken,"_",0)!=-1 && Strstr(degisken,"not_equal",0)==-1 )
			{
				tespitOlunmusDegisken=DegiskenTespit(degisken);
				satirO = StringEkle(satirO,tespitOlunmusDegisken._name);
								
				free(tespitOlunmusDegisken._name);
				free(tespitOlunmusDegisken._type);
				free(tespitOlunmusDegisken._format);
			}			
			else if(Strstr(degisken,"and",0)!=-1)
			{
				satirO=StringEkle(satirO,"&&");
			}
			else if(Strstr(degisken,"or",0)!=-1)
			{
				satirO=StringEkle(satirO,"||");
			}
			else if(Strstr(degisken,"equal",0)!=-1)
			{
				satirO=StringEkle(satirO,"==");
			}
			else if(Strstr(degisken,"not_equal",0)!=-1)
			{
				satirO=StringEkle(satirO,"!=");
			}

			free(degisken);
		}
		
		else if(parantezArasi[i]=='<' && parantezArasi[i+1]=='-')
		{
			satirO=CharEkle(satirO,'=');
			i+=2; // < bu isareyi atlamak icin... - bu isareyi while sonunda artan i atlayacak
		}
		else if(parantezArasi[i]=='.' && parantezArasi[i+1]=='.')
		{
			satirO=CharEkle(satirO,';');
			satirO=StringEkle(satirO,GetStrBetweenChars(satirO,0,'(','='));
			satirO=CharEkle(satirO,'<');
			i+=2;
		}
		
		else
		{
			satirO = CharEkle(satirO,parantezArasi[i]);
			i++;
		}
				
	}
		
	satirO=CharEkle(satirO,';');
	satirO=StringEkle(satirO,GetStrBetweenChars(satirO,0,'(','='));
	//( ile = arasindaki string artacak olan stringdir . for(string=0;.....;....)
	satirO=StringEkle(satirO,"++");
	satirO=CharEkle(satirO,')');
	return satirO;
}


char* if_then(char* satirI) 
{
	int i=0;
	char* satirO=NULL;
	degiskenleriAl(satirI);
	
	satirO=StringEkle(satirO,"if");
	Var tespitOlunmusDegisken;
	char *parantezArasi=GetStrBetweenStrings(satirI,0,"if","then");
	
	while(parantezArasi[i]) //sonda segisken olursa NULL'da isleme dahil olsun diye i-1
	{
		if(HarfMi(parantezArasi[i]))
		{
			char* degisken=NULL;
			while(HarfMi(parantezArasi[i]) || parantezArasi[i]=='_' || rakamMi(parantezArasi[i]))
			{
				degisken=CharEkle(degisken,parantezArasi[i]);
				i++;
			}
			if(Strstr(degisken,"_",0)!=-1 && Strstr(degisken,"not_equal",0)==-1)
			{
				tespitOlunmusDegisken=DegiskenTespit(degisken);
				satirO = StringEkle(satirO,tespitOlunmusDegisken._name);
					
				free(tespitOlunmusDegisken._name);
				free(tespitOlunmusDegisken._type);
				free(tespitOlunmusDegisken._format);
			}								
			else if(Strstr(degisken,"and",0)!=-1)
			{
				satirO=StringEkle(satirO,"&&");
			}
			else if(Strstr(degisken,"or",0)!=-1)
			{
				satirO=StringEkle(satirO,"||");
			}
			else if(Strstr(degisken,"equal",0)!=-1)
			{
				satirO=StringEkle(satirO,"==");
			}
			else if(Strstr(degisken,"not_equal",0)!=-1)
			{
				satirO=StringEkle(satirO,"!=");
			}

			free(degisken);
		}
		else
		{
			satirO = CharEkle(satirO,parantezArasi[i]);
			i++;
		}
		

	}
		
	return satirO;
}


char *assignment(char* satirI)
{
	degiskenleriAl(satirI);
	int i=0;
	char* satirO=NULL;
	degiskenleriAl(satirI);
	
	Var tespitOlunmusDegisken;
	satirI=trim(satirI);
	while(satirI[i]) //sonda segisken olursa NULL'da isleme dahil olsun diye i-1
	{
		if(HarfMi(satirI[i]))
		{
			char* degisken=NULL;
			while(HarfMi(satirI[i])||satirI[i]=='_' || rakamMi(satirI[i]))
			{
				degisken=CharEkle(degisken,satirI[i]);
				i++;
			}

			tespitOlunmusDegisken=DegiskenTespit(degisken);
			satirO = StringEkle(satirO,tespitOlunmusDegisken._name);
			
			free(tespitOlunmusDegisken._name);
			free(tespitOlunmusDegisken._type);
			free(tespitOlunmusDegisken._format);
			
			free(degisken);
		}
		else if(satirI[i]=='<' && satirI[i+1]=='-')
		{
			satirO=CharEkle(satirO,'=');
			i+=2;
		}
		else
		{
			satirO = CharEkle(satirO,satirI[i]);
			i++;
		}
		
	}	
	satirO=CharEkle(satirO,';');
	return satirO;
}

char* define(char *satirI)
{
	int i=0;
	char* satirO=NULL;
	Var tespitOlunmusDegisken;
	
	while(satirI[i]) //sonda segisken olursa NULL'da isleme dahil olsun diye i-1
	{
		if(HarfMi(satirI[i]))
		{
			char* degisken=NULL;
			while(HarfMi(satirI[i]) || satirI[i]=='_' || rakamMi(satirI[i]))
			{
				degisken=CharEkle(degisken,satirI[i]);
				i++;
			}
			if(!ReservedWordControl(degisken,"define"))
			{
				tespitOlunmusDegisken=DegiskenTespit(degisken);
				satirO=StringEkle(satirO,tespitOlunmusDegisken._name);
				
			}
			free(degisken);
		}
		else
		{
			satirO = CharEkle(satirO,satirI[i]);
			i++;
		}
	}
	DegiskenEkle(satirO,tespitOlunmusDegisken._type,2);
	free(tespitOlunmusDegisken._name);
	free(tespitOlunmusDegisken._type);
	free(tespitOlunmusDegisken._format);
}

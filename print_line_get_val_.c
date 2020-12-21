#include <stdio.h>
#include <string.h>
#include "myfunctions.h"

char* print_line(char* satirI)
{
	

	char* satirO=NULL;
	int i=0;
	satirO = StringEkle(satirO,"printf(");
	char* tirnakArasi=GetStrBetweenChars(satirI,0,'\"','\"');
	degiskenleriAl(tirnakArasi);
	char *parantezArasi_duzenli=parantezArasi_Print(tirnakArasi);
	satirO=StringEkle(satirO,parantezArasi_duzenli);

	satirO = StringEkle(satirO,");");
	free(tirnakArasi);
	free(parantezArasi_duzenli);
	
	return satirO;
	//satirO dizisini dosyaya karakter karakter yazmayi unutma,sonuna ; lazim
}

char* parantezArasi_Print(char* string)
{
	char *virguldenSonrakiKisim=NULL , *parantezArasi=NULL;
	int i=0;
	
	Var tespitOlunmusDegisken , dizininboyutDegiskeni;
	parantezArasi = CharEkle(parantezArasi,'\"');
	while(string[i]) //sonda segisken olursa NULL'da isleme dahil olsun diye i-1
	{
		if(string[i]=='$')//degisken cikabilir.degiskeni belirlemek icin $ anahtardir
		{		
			char* degisken=NULL;
			
			degisken = CharEkle(degisken,string[i]);//$ da ekledimki kirparken rahat kirpa bileyim
			i++;
			while(string[i]=='_' || HarfMi(string[i]) || string[i]=='[' || string[i]==']' || rakamMi(string[i]))
			{ //olasi durumlar disinda varsa bitir

				degisken = CharEkle(degisken,string[i]);
				i++;
			}
			degisken = CharEkle(degisken,string[i]);

			if(Strstr(degisken,"[",0)!=-1) //tirnak arasinda dizi olma olasiligi
			{
				tespitOlunmusDegisken=DegiskenTespit(GetStrBetweenChars(degisken,0,'$','['));
				dizininboyutDegiskeni=DegiskenTespit(GetStrBetweenChars(degisken,0,'[',']'));
				parantezArasi = StringEkle(parantezArasi,tespitOlunmusDegisken._format);
								
				virguldenSonrakiKisim = CharEkle(virguldenSonrakiKisim,','); //tirnak kapandiktan sonraki kisim icin
				virguldenSonrakiKisim = StringEkle(virguldenSonrakiKisim,tespitOlunmusDegisken._name);
				virguldenSonrakiKisim = CharEkle(virguldenSonrakiKisim,'[');
				virguldenSonrakiKisim = StringEkle(virguldenSonrakiKisim,dizininboyutDegiskeni._name);
				virguldenSonrakiKisim = CharEkle(virguldenSonrakiKisim,']');
				
				free(tespitOlunmusDegisken._type);
				free(tespitOlunmusDegisken._name);
				free(tespitOlunmusDegisken._format);
				free(dizininboyutDegiskeni._type);
				free(dizininboyutDegiskeni._name);
				free(dizininboyutDegiskeni._format);
			}
			else //tirnak arasinda normal degisken olma olasiligi
			{

				tespitOlunmusDegisken=DegiskenTespit(GetStrBetweenChars(degisken,0,'$',string[i]));
				parantezArasi = StringEkle(parantezArasi,tespitOlunmusDegisken._format);

				virguldenSonrakiKisim = CharEkle(virguldenSonrakiKisim,','); //tirnak kapandiktan sonraki kisim icin
				virguldenSonrakiKisim = StringEkle(virguldenSonrakiKisim,tespitOlunmusDegisken._name);

				free(tespitOlunmusDegisken._type);
				free(tespitOlunmusDegisken._name);
				free(tespitOlunmusDegisken._format);
			}
			free(degisken);
		}
		
		else
		{
			parantezArasi = CharEkle(parantezArasi,string[i]); //degisken veya \ li degilsedegilse normal olarak ekle
			i++;
		}
		switch(string[i]) //boyle birsey istemiyordu.ama yaptim
		{
			case '\n':	parantezArasi = StringEkle(parantezArasi,"\\n");i++;break;
			case '\t':	parantezArasi = StringEkle(parantezArasi,"\\t");i++;break;
			case '\b':	parantezArasi = StringEkle(parantezArasi,"\\b");i++;break;
			case '\a':	parantezArasi = StringEkle(parantezArasi,"\\a");i++;break;
			case '\r':	parantezArasi = StringEkle(parantezArasi,"\\r");i++;break;
		}			
		
	}
	parantezArasi = StringEkle(parantezArasi,"\\n");
	parantezArasi = CharEkle(parantezArasi,'\"');
	if(virguldenSonrakiKisim!=NULL)
		parantezArasi = StringEkle(parantezArasi,virguldenSonrakiKisim);
	
	free(virguldenSonrakiKisim);
	return parantezArasi;
}

char* get_val(char* satirI)
{
	char* satirO=NULL;
	satirO = StringEkle(satirO,"scanf(");
	char* tirnakArasi=GetStrBetweenChars(satirI,0,'\"','\"');
	degiskenleriAl(tirnakArasi);
	char *parantezArasi_duzenli=parantezArasi_Scan(tirnakArasi);
	satirO=StringEkle(satirO,parantezArasi_duzenli);

	satirO = StringEkle(satirO,");");
	free(tirnakArasi);
	free(parantezArasi_duzenli);
	
	return satirO;
	//satirO dizisini dosyaya karakter karakter yazmayi unutma,sonuna ; lazim
}

char* parantezArasi_Scan(char* string)
{		
	char *virguldenSonrakiKisim=NULL , *parantezArasi=NULL;
	int i=0;
	
	
	Var tespitOlunmusDegisken , dizininboyutDegiskeni;
	parantezArasi = CharEkle(parantezArasi,'\"');
	while(string[i])
	{
		if(string[i]=='$')//degisken cikabilir.degiskeni belirlemek icin $ anahtardir
		{
			char* degisken=NULL;
			degisken = CharEkle(degisken,string[i]);//$ da ekledimki kirparken rahat kirpa bileyim
			i++;
			while(string[i]=='_' || HarfMi(string[i]) || string[i]=='[' || string[i]==']' || rakamMi(string[i]))
			{ //olasi durumlar disinda varsa bitir

				degisken = CharEkle(degisken,string[i]);
				i++;
			}
			degisken = CharEkle(degisken,string[i]);
		//	printf("\n2 degisken|%s|",degisken);
			if(Strstr(degisken,"[",0)!=-1) //tirnak arasinda dizi olma olasiligi
			{
				tespitOlunmusDegisken=DegiskenTespit(GetStrBetweenChars(degisken,0,'$','['));
				dizininboyutDegiskeni=DegiskenTespit(GetStrBetweenChars(degisken,0,'[',']'));
				parantezArasi = StringEkle(parantezArasi,tespitOlunmusDegisken._format);

				virguldenSonrakiKisim = CharEkle(virguldenSonrakiKisim,','); //tirnak kapandiktan sonraki kisim icin
				virguldenSonrakiKisim = CharEkle(virguldenSonrakiKisim,'&');
				virguldenSonrakiKisim = StringEkle(virguldenSonrakiKisim,tespitOlunmusDegisken._name);
				virguldenSonrakiKisim = CharEkle(virguldenSonrakiKisim,'[');
				virguldenSonrakiKisim = StringEkle(virguldenSonrakiKisim,dizininboyutDegiskeni._name);
				virguldenSonrakiKisim = CharEkle(virguldenSonrakiKisim,']');
				
				free(tespitOlunmusDegisken._type);
				free(tespitOlunmusDegisken._name);
				free(tespitOlunmusDegisken._format);
				free(dizininboyutDegiskeni._type);
				free(dizininboyutDegiskeni._name);
				free(dizininboyutDegiskeni._format);
			}
			else //tirnak arasinda normal degisken olma olasiligi
			{
				tespitOlunmusDegisken=DegiskenTespit(GetStrBetweenChars(degisken,0,'$',string[i]));
				parantezArasi = StringEkle(parantezArasi,tespitOlunmusDegisken._format);
								
				virguldenSonrakiKisim = CharEkle(virguldenSonrakiKisim,','); //tirnak kapandiktan sonraki kisim icin
				virguldenSonrakiKisim = CharEkle(virguldenSonrakiKisim,'&');
				virguldenSonrakiKisim = StringEkle(virguldenSonrakiKisim,tespitOlunmusDegisken._name);

				free(tespitOlunmusDegisken._type);
				free(tespitOlunmusDegisken._name);
				free(tespitOlunmusDegisken._format);
			}
			free(degisken);
		}
		
		else
		{	
			parantezArasi = CharEkle(parantezArasi,string[i]); //degisken veya \ li degilsedegilse normal olarak ekle
			i++;
		}
	}
	parantezArasi = CharEkle(parantezArasi,'\"');
	
		parantezArasi = StringEkle(parantezArasi,virguldenSonrakiKisim);
	
	free(virguldenSonrakiKisim);
	return parantezArasi;
}

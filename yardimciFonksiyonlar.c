#include <stdio.h>
#include <string.h>
#include "myfunctions.h"

char *degiskenler[8];


char* trim(char* string)
{
	
	while(!HarfMi(string[0]))
	{
		if(string[0]==' ')
			string++;
	}
	return string;
}


int ReservedWordControl(char* string,char* word)
{
	string=trim(string);
	int i=0 , flag=0;
	
	while(word[i])
	{
		if(tolower(string[i])==tolower(word[i]))
			flag=1;
		else
			flag=0;
		
		i++;
	}
	
	return flag;
}


int Strstr(char* str,char* substr,int initialIndex)
{
	int i=initialIndex,j=0,flag=0;
	if(str==NULL || substr==NULL) return -1;
	while(substr[j])
	{
		if(!str[i]) return -1;//string bitti ama hala bulunmadi
		if(tolower(str[i])==tolower(substr[j]))
		{
			flag=1;
			j++;
		}
		else
		{
			flag=0;
			j=0;
		}
		i++;
	}
	if(flag==0) return -1;
	return (i-strlen(substr));
	
}

char *SatirAl(FILE *f )
{
	
	int size=10;
	char *string=(char *)calloc(size,sizeof(char));
	int i=0;
	char c;
	c=fgetc(f);
	while(c!=EOF &&  c !='\n')
	{		
		if(i+1==size)
		{
			size+=10;
			string=realloc(string,sizeof(char)*(size));
		}
		string[i]=c;
		i++;
		c=fgetc(f);
	}
	

	if(size>i+1)
	{
		size=i+1;
		string=realloc(string,sizeof(char)*(size));
		
	}
	string[i]='\0';	
	return string;
}

void Cevir(char* pseudoKod,char* cKodu)
{
	
	FILE *fout=fopen(pseudoKod,"r");
	FILE *fin=fopen("temp.txt","w");
	
	char *satir , *satirO;	
	Var degisken; degisken._name=NULL;degisken._type=NULL;
	int satirNo=0 , fonksiyonunYeri=-1 , tab=0 , j , beginyeri;
	DegiskenEkle(NULL,NULL,1); //matrisi resetlemek ve yeni degerler eklenmeye hazirlamak icin

	while(!feof(fout))
	{
		
		satirO=NULL;
		satir=SatirAl(fout);
		if(ReservedWordControl(satir,"procedure"))
		{
			satirO=procedure(satir);
			fonksiyonunYeri=ftell(fin);
		
			for(j=0;j<tab;j++) fprintf(fin,"\t");
			fprintf(fin,"%s\n",satirO);
		}
		
		else if(ReservedWordControl(satir,"define"))
		{
			define(satir);	
		}		
		
		else if(ReservedWordControl(satir,"return"))
		{
			degisken=Return(satir);
			satirO=StringEkle(satirO,"return ");			
			satirO=StringEkle(satirO,degisken._name);
			satirO=CharEkle(satirO,';');
			
			//fonksiyon pozisyonuna gedib var tipi eklemelisen
			for(j=0;j<tab;j++) fprintf(fin,"\t");
			fprintf(fin,"%s\n",satirO);				
						
		}
		
		else if(ReservedWordControl(satir,"for"))
		{
			satirO=for_loop(satir);
			for(j=0;j<tab;j++) fprintf(fin,"\t");
			fprintf(fin,"%s\n",satirO);	
		}
		
		else if(ReservedWordControl(satir,"while"))
		{
			satirO=while_do(satir);
			for(j=0;j<tab;j++) fprintf(fin,"\t");
			fprintf(fin,"%s\n",satirO);	
		}
		
		else if(ReservedWordControl(satir,"if"))
		{
			satirO=if_then(satir);
			for(j=0;j<tab;j++) fprintf(fin,"\t");
			fprintf(fin,"%s\n",satirO);			
		}
		
		else if(ReservedWordControl(satir,"print_line"))
		{
			satirO=print_line(satir);
			for(j=0;j<tab;j++) fprintf(fin,"\t");
			fprintf(fin,"%s\n",satirO);			
		}
		
		else if(ReservedWordControl(satir,"get_val"))
		{
			satirO=get_val(satir);
			for(j=0;j<tab;j++) fprintf(fin,"\t");
			fprintf(fin,"%s\n",satirO);	
		}		

		else if(Strstr(satir,"<-",0)!=-1)
		{
			satirO=assignment(satir);
			for(j=0;j<tab;j++) fprintf(fin,"\t");
			fprintf(fin,"%s\n",satirO);	
		}

		else if(ReservedWordControl(satir,"begin"))
		{
			satirO=begin(satir);	
			for(j=0;j<tab;j++) fprintf(fin,"\t");
			fprintf(fin,"%s\n",satirO);	
			if(tab==0) beginyeri=ftell(fin);
			tab++;		
		}
		
		else if(Strstr(satir,"define",0)!=-1)
		{
			define(satir);	
		}
				
		
		else if(ReservedWordControl(satir,"end"))
		{
			
			satirO=end(satir);
			tab--;
			if(tab==0)fprintf(fin,"\tgetch();\n");
			for(j=0;j<tab;j++) fprintf(fin,"\t");
			fprintf(fin,"%s\n",satirO);	
			
			if(tab==0) //yani sonuna gelmisse fonsiyonun
			{
				printf("Pseudocode dosyasi okundu\n");
				fclose(fin);
				fclose(fout);
				fout=fopen("temp.txt","r");
				fin=fopen(cKodu,"w");
				printf("C kaynak dosyasi olusturuluyor\n");
				fprintf(fin,"#include <stdlib.h>\n#include <stdio.h>\n#include <string.h>\n");
				while(!feof(fout))
				{
					if(fonksiyonunYeri==ftell(fout))
					{
						if(degisken._name==NULL)
							fprintf(fin,"void ");
						else if(Strstr(degisken._name,"*",0)!=-1)
							fprintf(fin,"%s* ",degisken._type);
						else
							fprintf(fin,"%s ",degisken._type);
					}
					
					if(beginyeri==ftell(fout))
					{
						int k=0 , initial=0;
						char* deg=NULL;
						if(degiskenler[7]!=NULL)
						{
							while(degiskenler[7][k])
							{
								if(degiskenler[7][k]=='{')
								{
									deg=GetStrBetweenChars(degiskenler[7],k,'{','}');
									if(deg!=0)
										fprintf(fin,"\t%s;\n",deg);
								}				
								k++;
							}
						}
						for(k=0;k<7;k++)
							if(degiskenler[k] !=NULL)
								fprintf(fin,"\t%s;\n",degiskenler[k]);
					}
					satir=SatirAl(fout);
					fprintf(fin,"%s\n",satir);
						
				}
				
				DegiskenEkle(NULL,NULL,1); //matrisi resetleyip bir sonraki fonksiyona hazirlar				
				
			}
		}

		free(satirO);
	}
	
	fclose(fout);
	fclose(fin);	
	remove("temp.txt");	

}

char* StringEkle(char* string,char* eklenecek)
{
	if(string==NULL)
		{
			string=(char*)calloc(1,sizeof(char));
			string[0]='\0';
		}
	int size=strlen(string) , newSize=size+strlen(eklenecek)+1;
	string=realloc(string,newSize*sizeof(char));
	strcat(string,eklenecek);
	return string;
//STRCAT ile ayni isi yapar
//	while(eklenecek[i])
//	{
//		satir[size+i]=eklenecek[i];
//		i++;
//	}
//	satir[newSize-1]='\0';
//	
}

char* CharEkle(char* string,char ch)
{
	if(string==NULL)
	{
		string=(char*)calloc(1,sizeof(char));
		string[0]='\0';
	}
	int size=strlen(string) , newSize=size+1+1;//biri karakter icin biri null icin
	string=realloc(string,newSize*sizeof(char));
	string[size]=ch;
	string[newSize-1]='\0';
	return string;
}

char* GetStrBetweenChars(char* string,int initialIndex,char begin,char end)
{
	int size=10,i=initialIndex,j=0,flag=0;
	char* newStr=(char*)calloc(size,sizeof(char));
	if(string==NULL) return 0;
	while(string[i])
	{
		if(j==size-1)
		{
			size+=10;
			newStr=realloc(newStr,size*sizeof(char));
		}		
		
		if(string[i+1]==end && flag)
		{	
			flag=0;
			break; //son elemansa ve ilk eleman bulunmussa donguye girmesin			
		}
		if(string[i]==begin) flag = 1;
		
		i++;
	
		if(flag)
		{		
			newStr[j]=string[i];
			j++; //baslangic bulunmussa j artsin
		}
	}
	if(flag) //ilk eleman bulundu ama sonu bulunamadi.Yalnis parametre verilmis demek
		{
			free(newStr);
			return 0;
		}
	if(size-1>j)
	{
		size=j+1;
		newStr=realloc(newStr,size*sizeof(char));
	}
	newStr[size-1]='\0';
	return newStr;
}

char* GetStrBetweenStrings(char* string,int initialIndex,char* begin,char* end)
{
	int size=10,flag=0,i=0;
	int temp=Strstr(string,begin,initialIndex);//bu baslangic sozun baslangic indisini tutar
	int firstIndex = temp + strlen(begin) ,	lastIndex=Strstr(string,end,initialIndex);
	char* newStr=(char*)calloc(size,sizeof(char));
	
	if(temp==-1||lastIndex==-1) return 0; //bu sozler stringde yok 

	while(firstIndex<lastIndex)
	{
		if(i==size-1)
		{
			size+=10;
			newStr=realloc(newStr,size*sizeof(char));
		}
		
		if(temp!=-1)
		{
			flag=1;
			newStr[i++]=string[firstIndex++];
		}
		else
		{
			flag=0;
		}
	}
	
	if(!flag) return 0;

	if(size-1>i)
	{
		size=i+1;
		newStr=realloc(newStr,size*sizeof(char));
	}
	newStr[size-1]='\0';
	
	return newStr;
}

int HarfMi(char karakter)
{
	if((karakter>='A' && karakter<='Z')||(karakter>='a' && karakter<='z'))
		return 1;
	return 0;
}

int rakamMi(char karakter)
{
	if(karakter>='0' && karakter<='9')
		return 1;
	return 0;
}

char* DegiskenTipi(char* string)
{
	char *tip=NULL;
	if(Strstr(string,"file",0)!=-1)	tip=StringEkle(tip," FILE ");	 
	else if(Strstr(string,"cp",0)!=-1) tip=StringEkle(tip," char ");
	else if(Strstr(string,"fp",0)!=-1) tip=StringEkle(tip," float "); 
	else if(Strstr(string,"ip",0)!=-1) tip=StringEkle(tip," int "); 
	else if(Strstr(string,"dp",0)!=-1) tip=StringEkle(tip," double "); 
	else if(Strstr(string,"ldp",0)!=-1) tip=StringEkle(tip," long double "); 
	else if(Strstr(string,"c",0)!=-1) tip=StringEkle(tip," char "); 
	else if(Strstr(string,"i",0)!=-1) tip=StringEkle(tip," int "); 
	else if(Strstr(string,"f",0)!=-1) tip=StringEkle(tip," float "); 
	else if(Strstr(string,"ld",0)!=-1) tip=StringEkle(tip," long double "); 
	else if(Strstr(string,"l",0)!=-1) tip=StringEkle(tip," long "); 
	else if(Strstr(string,"d",0)!=-1) tip=StringEkle(tip," double "); 
	else return 0;
	
	return tip;
}

char* DegiskenFormat(char* string)
{	 
	char *format=NULL;
	if(Strstr(string,"file",0)!=-1){} //file ise format null olacak	 
	else if(Strstr(string,"cp",0)!=-1) format=StringEkle(format,"%c");
	else if(Strstr(string,"fp",0)!=-1) format=StringEkle(format,"%f"); 
	else if(Strstr(string,"ip",0)!=-1) format=StringEkle(format,"%d"); 
	else if(Strstr(string,"dp",0)!=-1) format=StringEkle(format,"%f"); 
	else if(Strstr(string,"ldp",0)!=-1) format=StringEkle(format,"%f"); 
	else if(Strstr(string,"c",0)!=-1) format=StringEkle(format,"%c"); 
	else if(Strstr(string,"i",0)!=-1) format=StringEkle(format,"%d"); 
	else if(Strstr(string,"f",0)!=-1) format=StringEkle(format,"%f"); 
	else if(Strstr(string,"ld",0)!=-1) format=StringEkle(format,"%f"); 
	else if(Strstr(string,"l",0)!=-1) format=StringEkle(format,"%d"); 
	else if(Strstr(string,"d",0)!=-1) format=StringEkle(format,"%f"); 
	else return 0;
	
	return format;
}

Var DegiskenTespit(char *string)
{
	if(string==NULL) return;
	Var var;
	//adini belirlerme
	int i=0;

	int size=10;
	var._name=(char*)calloc(size,sizeof(char));
	while(string[i]!='_')
	{
		if(i==size-1)
		{
			size+=10;
			var._name=realloc(var._name,size*sizeof(char));
		}
		var._name[i]=string[i];
		i++;
	}
	if(size-1>i)
	{
		size=i+1;
		var._name=realloc(var._name,size*sizeof(char));
	}
	var._name[size-1]='\0';
	//tip belirleme
	size=5;
	char *pTip = (char*)calloc(size,sizeof(char)); //en fazla file(4) olur.o yuzden boyut 4
	int j = 0;
	
	i++;// alt cizgiyi ( _ ) atlamasi icin +1
	while(string[i]) 
	{
		pTip[j++]=string[i];
		i++;
		
	}
	pTip[j]='\0';
	
	var._type=DegiskenTipi(pTip);
	if(pTip[strlen(pTip)-1]=='p' || Strstr(pTip,"file",0)!=-1)
	{
		char *temp=var._name;
		var._name=NULL;
		var._name=CharEkle(var._name,'*');
		var._name=StringEkle(var._name,temp);
		
	}
	var._format=DegiskenFormat(pTip);
	return var;
}

char* DegiskeniDizidenKes(char* string)
{
	int i;
	int saga ,sola;
	for(i=0;i<strlen(string);i++) if(string[i]=='_') { saga=i; sola=i; } //'_' karakterin indisini bul
	//saga ve sola haraket edecegim icin guncel index'i yedeklemem lazim 
	char* degisken=NULL;
	//once saga
	degisken=CharEkle(degisken,'_');
	while( HarfMi(string[++saga]))
	{
		degisken=CharEkle(degisken,string[saga]);
	}
	
	//simdi sola gitme zamani
	while( HarfMi(string[--sola]))
	{
		char* temp=NULL;
		temp=CharEkle(temp,string[sola]);
		temp=StringEkle(temp,degisken);
		degisken=temp;
	}
	return degisken;
}

void DegiskenEkle(char *adi,char *tipi,int reset)
{
	if(reset==1)
	{
		int i;
		for(i=0;i<7;i++)
		{
			degiskenler[i] = NULL;
		}		
		return;
	}
	if(reset==2)
	{
		degiskenler[7]=CharEkle(degiskenler[7],'{');
		degiskenler[7]=StringEkle(degiskenler[7],tipi);
		
		degiskenler[7]=StringEkle(degiskenler[7],adi);
		degiskenler[7]=CharEkle(degiskenler[7],'}');
		return;
	}
	if(Strstr(tipi," char ",0) != -1) 
	{
		if(degiskenler[0]==NULL)
		{
			degiskenler[0]=StringEkle(degiskenler[0],"char ");
			degiskenler[0]=StringEkle(degiskenler[0],adi);
		}
		else
		{
			degiskenler[0]=CharEkle(degiskenler[0],',');
			degiskenler[0]=StringEkle(degiskenler[0],adi);			
		}

	}
	else if(Strstr(tipi," float ",0) != -1) 
	{
		if(degiskenler[1]==NULL)
		{
			degiskenler[1]=StringEkle(degiskenler[1],"float ");
			degiskenler[1]=StringEkle(degiskenler[1],adi);
		}
		else
		{
			degiskenler[1]=CharEkle(degiskenler[1],',');
			degiskenler[1]=StringEkle(degiskenler[1],adi);			
		}
	}
	else if(Strstr(tipi," long double ",0) != -1) 
	{
		if(degiskenler[2]==NULL)
		{
			degiskenler[2]=StringEkle(degiskenler[2],"long double ");
			degiskenler[2]=StringEkle(degiskenler[2],adi);
		}
		else
		{
			degiskenler[2]=CharEkle(degiskenler[2],',');
			degiskenler[2]=StringEkle(degiskenler[2],adi);			
		}				
	}
	else if(Strstr(tipi," long ",0) != -1) 
	{
		if(degiskenler[3]==NULL)
		{
			degiskenler[3]=StringEkle(degiskenler[3],"long ");
			degiskenler[3]=StringEkle(degiskenler[3],adi);
		}
		else
		{
			degiskenler[3]=CharEkle(degiskenler[3],',');
			degiskenler[3]=StringEkle(degiskenler[3],adi);			
		}				
	}
	else if(Strstr(tipi," double ",0) != -1) 
	{
		if(degiskenler[4]==NULL)
		{
			degiskenler[4]=StringEkle(degiskenler[4],"double ");
			degiskenler[4]=StringEkle(degiskenler[4],adi);
		}
		else
		{
			degiskenler[4]=CharEkle(degiskenler[4],',');
			degiskenler[4]=StringEkle(degiskenler[4],adi);			
		}		
	}			
	else if(Strstr(tipi," int ",0) != -1) 
	{
		if(degiskenler[5]==NULL)
		{
			degiskenler[5]=StringEkle(degiskenler[5],"int ");
			degiskenler[5]=StringEkle(degiskenler[5],adi);
		}
		else
		{
			degiskenler[5]=CharEkle(degiskenler[5],',');
			degiskenler[5]=StringEkle(degiskenler[5],adi);			
		}				
	}	
	else if(Strstr(tipi," file ",0) != -1) 
	{
		if(degiskenler[6]==NULL)
		{
			degiskenler[6]=StringEkle(degiskenler[6],"FILE ");
			degiskenler[6]=StringEkle(degiskenler[6],adi);
		}
		else
		{
			degiskenler[6]=CharEkle(degiskenler[6],',');
			degiskenler[6]=StringEkle(degiskenler[6],adi);			
		}				
	}
	
	else return;
}

char *degiskenlerdeVarmi(char *string)
{
	int i=0;
	while(i<8)
	{
		if(string!=NULL || degiskenler[i]!=NULL)
		{
			if(Strstr(degiskenler[i],string,0)!=-1) 
				return 1;		
		}
		i++;
	}
	return 0;
}

void degiskenleriAl(char* string)
{
	char *temp ,*degisken;
	int i=0 ;
	Var tespitOlunmusDegisken , dizininBoyutDegiskeni;
	while(string[i])
	{
		if(HarfMi(string[i]))
		{
			temp=NULL;
			
			while(HarfMi(string[i]) || string[i]=='_' || string[i]=='[' || string[i]==']' || rakamMi(string[i]))
			{
				temp=CharEkle(temp,string[i]);
				i++;
			}
				
			if(Strstr(temp,"_",0)!=-1 && Strstr(temp,"[",0)!=-1)
			{
				degisken=NULL;
				int j=0;
				while(temp[j]!='[')
				{
					degisken=CharEkle(degisken,temp[j]);
					j++;
				}
				
				tespitOlunmusDegisken=DegiskenTespit(degisken);
				//dizininBoyutDegisken=DegiskenTespit(GetStrBetweenChars(string,pos,'[',']'))
				
				if(degiskenlerdeVarmi(tespitOlunmusDegisken._name)==0)
				{
					char* eklenecek=NULL;
					eklenecek=StringEkle(eklenecek,tespitOlunmusDegisken._name);
					eklenecek=StringEkle(eklenecek,"[100]");
					DegiskenEkle(eklenecek,tespitOlunmusDegisken._type,0);
				}
			}
			
			else if(Strstr(temp,"_",0)!=-1)
			{
				degisken=temp;
				tespitOlunmusDegisken=DegiskenTespit(degisken);
				if(degiskenlerdeVarmi(tespitOlunmusDegisken._name)==0)
				{
					char* eklenecek=NULL;
					eklenecek=StringEkle(eklenecek,tespitOlunmusDegisken._name);
					DegiskenEkle(eklenecek,tespitOlunmusDegisken._type,0);
				}		
			}
		}
		
		else i++;
	}
}

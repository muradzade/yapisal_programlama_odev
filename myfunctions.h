#ifndef myfunctions_h
#define myfunctions_h


	//structs
	typedef struct
	{
		char* _name;
		char* _type;
		char* _format;
	}Var;

	//yardimci fonksiyonlar
	//Stringlerle alakali
	int Strstr(char* str,char* substr,int initialIndex); //eger substr ,str'nin icinde varsa substr'nin ilk adresi doner.yoksa -1 doner
	char* SatirAl(FILE *f); //dosyayi satir satir okumaya yarar
	void Cevir(char* pseudoKod,char* cKodu);
	char* StringEkle(char* satir,char* eklenecek);
	char* CharEkle(char* string,char ch);
	char* GetStrBetweenChars(char* string,int initialIndex,char begin,char end);
	char* GetStrBetweenStrings(char* string,int initialIndex,char* begin,char* end);
	int HarfMi(char karakter);
	int rakamMi(char karakter);	
	//degisken belirleme ile alakali
	char* DegiskenTipi(char* string);
	char* DegiskenFormat(char* string);
	Var DegiskenTespit(char* string);
	char* DegiskeniDizidenKes(char* string);
	
	//PRINT_LINE //GET_VAL
	char* parantezArasi_Print(char* string);
	char* print_line(char* satirI);	
	char* parantezArasi_Scan(char* string);
	char* get_val(char* satirI);
	
	//WHILE_DO  //FOR_LOOP  //IF_THEN //<-
	char* while_do(char* satirI);
	char* for_loop(char* satirI);
	char* if_then(char* satirI);
	char *assignment(char* satirI);
	char* define(char *satirI);

	//PROCEDURE // RETURN //BEGIN // END
	char* procedure(char* satirI);
	Var Return(char* satirI);
	char* begin();
	char* end();
		
	//degiskenleri barindiran dizi icin
	void DegiskenEkle(char *adi,char *tipi,int reset);
	char *degiskenlerdeVarmi(char *string);
	
	void degiskenleriAl(char* string);
#endif

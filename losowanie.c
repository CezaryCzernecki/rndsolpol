#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main ()
{
	int liczba_int=1;
	int dolny = 1, gorny = 4;
	int lnn=0; //licznik nawaisów niedomkniętych
	int i;
	int pozycja_s=0; //numer ostatniej komórki zapisanej w stosie
	int pozycja_w=0; //numer ostatniej komórki zapisanej w wyrazeniu
	float x;
	float y;
	float z;
	
	printf("Witaj użytkowniku!\nProszę podaj dowolną dodatnią nieparzystą liczbę całkowitą pozwalającym na wygenerowanie wyrażenia matematycznego:\n");
	scanf("%d", &liczba_int);
	while(liczba_int%2==0 || liczba_int<1)
	{
		printf("Proszę podaj liczbę jeszcze raz.\nPamiętaj, że musi ona spełniać poniższe wymagania:\n-dodatnia,\n-całkowita\n-nieparzysta\n");
		scanf("%d", &liczba_int);
	}
	printf("jest ok %d\n",liczba_int);
	char tablica[liczba_int];
	int licznik=liczba_int;
	int los;
	for (i=0;i<liczba_int;i++)
	{
		if(licznik>lnn)//wykonuj losowanie znaków tak długo jak liczba niewylosowanych znaków jest większa od liczby potrzebnej na domknięcie nawiasów
		{
			los = (rand() % (gorny - dolny + 1)) + dolny;
			if (los <4) //gdy zostanie wylosowana liczba
			{
				if (los==1)
				{
					tablica[i]='x';
				}
				if (los==2)
				{
					tablica[i]='y';
				}
				if (los==3)
				{
					tablica[i]='z';
				}
				dolny=5; //losujemny znak działania 
					if(lnn>0) //w przypadku gdy istnieją niedomknięte nawiasy
					{
						gorny=9;
					}
					else if(lnn==0) //w przypadku gdy nie ma niedomkniętych nawiasów
					{
						gorny=8;
					}
			}
			if (los == 4) //gdy zostanie wylosowany nawias otwierający
			{
				tablica[i]='(';
				dolny=1; //następnym wylosowany znakiem będzie liczba lub kolejny nawias otwierający
				gorny=4;
				lnn++; //zwiększenie licznika nawaisów niedomkniętych
			}
			if (los <9 && los >4) // gdy zostanie wylosowany znak działania
			{
				if (los==5)
				{
					tablica[i]='+';
				}
				if (los==6)
				{
					tablica[i]='-';
				}
				if (los==7)
				{
					tablica[i]='*';
				}
				if (los==8)
				{
					tablica[i]='/';
				}
				dolny=1;
				gorny=4;
				if (licznik<=lnn+3) //zapobiega wstawieniu nawiasu otwierającego jako ostatniego znaku w działaniu
				{
					gorny=3;
				}
			}
			if (los == 9) //gdy zostanie wylosowany nawias zamykający
			{
				tablica[i]=')';
				dolny=5;
				if(lnn>0) //w przypadku gdy istnieją niedomknięte nawiasy
					{
						gorny=9;
					}
					else if(lnn==0) //w przypadku gdy nie ma niedomkniętych nawiasów
					{
						gorny=8;
					}
				lnn--; //zmniejszenie licznika nawiasów niedomkniętych
			}
		}
		if(licznik==lnn)//jeśli liczba niewylosowanych znaków jest równa liczbie niedomkniętych nawiasów domknij je zamiast losować nowe znaki
		{
			tablica[i]=')';
			lnn--;
		}
		licznik--;
		printf("znak %c ", tablica[i]);
		printf("int %d, ", liczba_int);
		printf("los %d, ", los);
		printf("dolny %d, ", dolny);
		printf("gorny %d, ", gorny);
		printf("licznik %d, ", licznik);
		printf("lnn %d\n", lnn);
	}
	FILE * fp;
	fp = fopen ("dane.txt", "w+");
	printf("oto twoje równanie:\n");
	for (i=0;i<liczba_int;i++) //zapis równania do pliku oraz wyświetlenie go dla uzytkownika
	{
		printf("%c", tablica[i]);
		fprintf(fp, "%c",tablica[i]);
	}
   fclose(fp);
   printf("\nPodaj wartość x=");
		scanf("%f",&x);
	printf("\nPodaj wartość y=");
		scanf("%f",&y);
	printf("\nPodaj wartość z=");
		scanf("%f",&z);
	char stos[liczba_int];
	char wyrazenie_ONP[liczba_int];
	for (i=0;i<liczba_int;i++)
	{
		if(tablica[i]=='(' || tablica[i]=='+' || tablica[i]=='-' || tablica[i]=='*' || tablica[i]=='/')
		{
			stos[pozycja_s]=tablica[i];
			pozycja_s++;
			
		}
		if(tablica[i]=='x' || tablica[i]=='y' || tablica[i]=='z')
		{
			wyrazenie_ONP[pozycja_w]=tablica[i];
			pozycja_w++;	
		}
		if(tablica[i]==')')
		{
			while (stos[pozycja_s]!='(')
			{
			wyrazenie_ONP[pozycja_w]=stos[pozycja_s];
			pozycja_s--;
			pozycja_w++;
			}
			pozycja_s--;
		}
	}
	
	for (i=0;i<pozycja_w;i++)
	{
		printf("%c",wyrazenie_ONP[i]);
	}
	printf("\n%d",pozycja_s);
	printf("\n%d\n",pozycja_w);
	for (i=0;i<pozycja_s;i++)
	{
		printf("%c",stos[i]);
	}
	
}
//wylosowane liczny 1='x', 2='y',3='z',4='(',5='+',6='-',7='*',8='/',9=')'
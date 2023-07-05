#include <stdio.h>
#include <stdlib.h>
#include <time.h>
char[] losowanie(int liczba)
{
char tablica[liczba];
int licznik=liczba;
int dolny = 1, gorny = 4; //pierwszy zakres losujący liczbę lub otwarcie nawiasu
int lnn=0; //licznik nawaisów niedomkniętych
int i;
int los;
for (i=0;i<liczba;i++)
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
	}
	return tablica[liczba];
}
int main()
{
	int y=15;
	int i;
	char dd[y]=losowanie(y);
	for(i=0;i<y;i++)
	{
		printf("%c",dd[i]);
	}
}
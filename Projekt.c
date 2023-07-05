#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void losowanie(int liczba_int, char tablica[]);
void zapis(int liczba_int, char tablica[]);
void odczyt(int liczba_int, char tablica[]);
void dane(float *x, float *y, float *z);
void konwerter(int liczba_int, char tablica[], char rownanieONP[]);
float rozwiazanie(float x, float y, float z, char rownanieONP[], float wynik);

int main()
{
    int liczba_int = 1,i;
    float x, y, z;
    char tablica_1[liczba_int];
    char tablica_2[liczba_int];
    char rownanieONP[liczba_int];
    float wynik;
    srand(time(NULL));//ustawienie danych do loswania na podstawie czasu komputera

    printf("Witaj użytkowniku!\nProszę podaj dowolną dodatnią nieparzystą liczbę całkowitą pozwalającym na wygenerowanie wyrażenia matematycznego:\n");
    scanf("%d", &liczba_int);

    while (liczba_int % 2 == 0 || liczba_int < 1)
    {
        printf("Proszę podaj liczbę jeszcze raz.\nPamiętaj, że musi ona spełniać poniższe wymagania:\n-dodatnia,\n-całkowita\n-nieparzysta\n");
        scanf("%d", &liczba_int);
    }

    losowanie(liczba_int, tablica_1);
    zapis(liczba_int, tablica_1);
    odczyt(liczba_int, tablica_2);
    dane(&x, &y, &z);
    konwerter(liczba_int, tablica_2, rownanieONP);
    printf("RPN expression: %s\n", rownanieONP);
    rozwiazanie(x, y, z, rownanieONP, wynik);
    printf("wynik: %f\n", wynik);
}

void losowanie(int liczba_int, char tablica[])
{
    int dolny = 1, gorny = 4;
    int lnn = 0; //licznik nawiasów niedomkniętych
    int i;
    int pozycja_s = 0; //numer ostatniej komórki zapisanej w stosie
    int pozycja_w = 0; //numer ostatniej komórki zapisanej w wyrazeniu
    int licznik = liczba_int;
    int los;

    for (i = 0; i < liczba_int; i++)
    {
        if (licznik > lnn) //wykonuj losowanie znaków tak długo jak liczba niewylosowanych znaków jest większa od liczby potrzebnej na domknięcie nawiasów
        {
            los = (rand() % (gorny - dolny + 1)) + dolny;
            if (los < 4) //gdy zostanie wylosowana liczba
            {
                if (los == 1)
                {
                    tablica[i] = 'x';
                }
                if (los == 2)
                {
                    tablica[i] = 'y';
                }
                if (los == 3)
                {
                    tablica[i] = 'z';
                }
                dolny = 5; //losujemny znak działania
                if (lnn > 0) //w przypadku gdy istnieją niedomknięte nawiasy
                {
                    gorny = 9;
                }
                else if (lnn == 0) //w przypadku gdy nie ma niedomkniętych nawiasów
                {
                    gorny = 8;
                }
            }
            if (los == 4) //gdy zostanie wylosowany nawias otwierający
            {
                tablica[i] = '(';
                dolny = 1;  //następnym wylosowany znakiem będzie liczba lub kolejny nawias otwierający
                gorny = 4;
                lnn++; //zwiększenie licznika nawaisów niedomkniętych
            }
            if (los < 9 && los > 4) // gdy zostanie wylosowany znak działania
            {
                if (los == 5)
                {
                    tablica[i] = '+';
                }
                if (los == 6)
                {
                    tablica[i] = '-';
                }
                if (los == 7)
                {
                    tablica[i] = '*';
                }
                if (los == 8)
                {
                    tablica[i] = '/';
                }
                dolny = 1;
                gorny = 4;
                if (licznik <= lnn + 3) //zapobiega wstawieniu nawiasu otwierającego jako ostatniego znaku w działaniu
                {
                    gorny = 3;
                }
            }
            if (los == 9) //gdy zostanie wylosowany nawias zamykający
            {
                tablica[i] = ')';
                lnn--; //zmniejszenie licznika nawiasów niedomkniętych
                dolny = 5;
                if (lnn > 0) //w przypadku gdy istnieją niedomknięte nawiasy
                {
                    gorny = 9;
                }
                else if (lnn == 0) //w przypadku gdy nie ma niedomkniętych nawiasów
                {
                    gorny = 8;
                }
                
            }
        }
        if (licznik == lnn) //jeśli liczba niewylosowanych znaków jest równa liczbie niedomkniętych nawiasów domknij je zamiast losować nowe znaki
        {
            tablica[i] = ')';
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
}

void zapis(int liczba_int, char tablica[])
{
    FILE *fp;
    fp = fopen("dane.txt", "w+");
    printf("oto twoje zapisane równanie: \n");
    for (int i = 0; i < liczba_int; i++) //zapis równania do pliku oraz wyświetlenie go dla uzytkownika
    {
        printf("%c", tablica[i]);
        fprintf(fp, "%c", tablica[i]);
    }
    fclose(fp); 
}
void odczyt(int liczba_int, char tablica[])
{
FILE *fp;
    fp = fopen("dane.txt", "r+");
    printf("\noto twoje odczytane równanie: \n");
    for (int i = 0; i < liczba_int; i++) //zapis równania do pliku oraz wyświetlenie go dla uzytkownika
    {
       tablica[i]=fgetc(fp);
       printf("%c", tablica[i]);
    }
    fclose(fp);
}
void dane(float *x, float *y, float *z) //funkcja do pobierania znaków od uzytkownika
{
    printf("\nPodaj wartość x=");
    scanf("%f", x);
    printf("\nPodaj wartość y=");
    scanf("%f", y);
    printf("\nPodaj wartość z=");
    scanf("%f", z);
}

int test_znaku(char znak)
{
    return (znak == '+' || znak == '-' || znak == '*' || znak == '/');
}

int priorytet(char znak) //wunkcja nadająca priorytet poszczególnym znakom operacji na liczbach
{
    if (znak == '+' || znak == '-')
        return 1;
    else if (znak == '*' || znak == '/')
        return 2;
    else
        return 0;
}

void konwerter(int liczba_int, char tablica[], char rownanieONP[]) //funkcja konwertująca wyrazenie z nawiasami w sposób klayczny na takie w Odwróconej Notacji Polskiej 
{
    char stos[liczba_int];
    int pozycja_s = -1;
    int pozycja_r = 0;

    for (int i = 0; i < liczba_int; i++)
    {
        char znak = tablica[i];

        if (test_znaku(znak))
        {
            while (pozycja_s >= 0 && test_znaku(stos[pozycja_s]) &&
                   priorytet(znak) <= priorytet(stos[pozycja_s]))
            {
                rownanieONP[pozycja_r++] = stos[pozycja_s--];
            }
            stos[++pozycja_s] = znak;
        }
        else if (znak == '(')
        {
            stos[++pozycja_s] = znak;
        }
        else if (znak == ')')
        {
            while (pozycja_s >= 0 && stos[pozycja_s] != '(')
            {
                rownanieONP[pozycja_r++] = stos[pozycja_s--];
            }

            if (pozycja_s >= 0 && stos[pozycja_s] == '(')
            {
                pozycja_s--;
            }
        }
        else
        {
            rownanieONP[pozycja_r++] = znak;
        }
    }

    while (pozycja_s >= 0)
    {
        rownanieONP[pozycja_r++] = stos[pozycja_s--];
    }
    rownanieONP[pozycja_r] = '\0';
}
float rozwiazanie(float x, float y, float z, char rownanieONP[], float wynik)
{
    float stos[strlen(rownanieONP)];
    int liczba_s=-1;
    int i,j;
    for (i=0;i<strlen(rownanieONP);i++)
    {
        if (rownanieONP[i]==120)
        {
            liczba_s++;
            printf("x=%f ",x);
            stos[liczba_s]=x;
        }
        if (rownanieONP[i]==121)
        {
            liczba_s++;
            printf("y=%f ",y);
            stos[liczba_s]=y;
        }
        if (rownanieONP[i]==122)
        {
            liczba_s++;
            printf("z=%f ",z);
            stos[liczba_s]=z;
        }
        if (rownanieONP[i]==43)
        {
            wynik=stos[liczba_s]+stos[liczba_s-1];
            liczba_s--;
            stos[liczba_s]=wynik;
        }
        if (rownanieONP[i]==45)
        {
            wynik=stos[liczba_s-1]-stos[liczba_s];
            liczba_s--;
            stos[liczba_s]=wynik;
        }
        if (rownanieONP[i]==42)
        {
            wynik=stos[liczba_s]*stos[liczba_s-1];
            liczba_s--;
            stos[liczba_s]=wynik;
        }
        if (rownanieONP[i]==47)
        {
            wynik=stos[liczba_s-1]/stos[liczba_s];
            liczba_s--;
            stos[liczba_s]=wynik;
        }
        printf("rownanie=%d ",rownanieONP[i]);
        printf("liczba=%d ",liczba_s);
        printf("stos=%f ",stos[liczba_s]);
        printf("wynik=%f\n",wynik);
    }
    return wynik;
}
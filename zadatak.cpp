#include <iostream>
#include <cstdlib>
#include <cstring>

//#include "red_polje.h"
#include "red_pokazivac.h"
using namespace std;

salter *red = new salter;
salter *pomocni_red = new salter;
osoba *temp = new osoba;
int n;

struct podatak
{
  int ai; //Kada ulazi u red
  int bi; //Trajanje transakcije
  int ci; //Prioritet klijenta
  int di; //Tip transakcije
} *podatci;

void generator(salter *red)
{
  podatci = new podatak[n];
  for(int i=0; i < n; i++)
  {
    podatci[i].ai = rand() % 401 + 100;
    podatci[i].bi = rand() % 401 + 100;
    podatci[i].ci = rand() % 6 + 1;
    do
    {
      podatci[i].di = rand() % 4 + 1;
    } while(podatci[i].ci == 6 && (podatci[i].di == 2 || podatci[i].di == 4));
  }
}

void ispis(osoba *x)
{
  cout << "//=============================== \\\\\n";
  cout << "||Ime i prezime: " << x -> ime << endl;
  cout << "||Datum rodenja: " << x -> godina_rodenja << endl;
  cout << "||Stanje tekuceg racuna: " << x -> tekuci_racun << " kn\n";
  cout << "||Stanje deviznog racuna: " << x-> devizni_racun << " eur\n";
  cout << "||Vrijeme dolaska: " << x -> ai << endl;
  cout << "||Trajanje transakcije: " << x -> bi <<endl;
  cout << "||Prioritet: " << x -> ci << endl;
  cout << "||Tip transakcije: ";
  switch(x -> di)
  {
    case 1: cout << "Uplata\n"; break;
    case 2: cout << "Isplata\n";break;
    case 3: cout << "Placanje racuna\n"; break;
    case 4: cout << "Krediti\n";break;
  }
  cout << "\\\\=============================== //\n";
}

void dodaj_zapise(salter *red)
{
  for(int i=0; i < n; i++)
  {
    osoba *novi = new osoba;
    cout << "Ime i prezime: ";
    cin >> novi -> ime;
    cout << "Godina rodenja: ";
    cin >> novi -> godina_rodenja;
    cout << "Stanje tekuceg racuna: ";
    cin >> novi -> tekuci_racun;
    cout << "Stanje deviznog racuna: ";
    cin >> novi -> devizni_racun;
    novi -> ai = podatci[i].ai;
    novi -> bi = podatci[i].bi;
    novi -> ci = podatci[i].ci;
    novi -> di = podatci[i].di;
    EnQueueQ(red,novi);  
  }
  osoba pomocni_red[n];
  for(int i = 0; i < n; i++)
  {
    memcpy(&pomocni_red[i], FrontQ(red),sizeof(osoba));
    DeQueueQ(red);
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n-1; j++)
    {
      if (pomocni_red[j].ci > pomocni_red[j+1].ci)
      {
	osoba temp = pomocni_red[j];
	pomocni_red[j] = pomocni_red[j+1];
	pomocni_red[j+1] = temp;
      }
    }
  }
  InitQ(red);
  bool ispisano = false;
  system("clear");
  for(int i = 0; i < n; i++)
  {
    if(pomocni_red[i].devizni_racun * 7.5148 > 10000) //Konverzija iz eura u kune
    {
      if (!ispisano)
      {
	cout << " //==============================\\\\\n";
	cout << " ||==== Podatci o klijentima ====||\n";
      }
      ispisano = true;
      ispis(&pomocni_red[i]);
    }
    EnQueueQ(red,&pomocni_red[i]);
  }
}

void novi_brzi_red(salter *red)
{
  osoba stari_red[n];
  osoba brzi_red[n];
  int brojac_stari = 0;
  int brojac_brzi = 0;
  for(int i = 0; i < n; i++)
  {
    if(FrontQ(red) -> di == 3)
      memcpy(&brzi_red[brojac_brzi++],FrontQ(red),sizeof(osoba));
    else
      memcpy(&stari_red[brojac_stari++],FrontQ(red),sizeof(osoba));
    DeQueueQ(red);
  }
  InitQ(red);
  if(brojac_stari)
  {
    cout << " //==============================\\\\\n";
    cout << " ||=== Klijenti u starom redu ===||\n";
  for(int i = 0; i < brojac_stari; i++)
    ispis(&stari_red[i]);
  for(int i = --brojac_stari; i > 0; i--)
    EnQueueQ(red, &stari_red[i]);
  }
  if(brojac_brzi)
  {
    cout << " //==============================\\\\\n";
    cout << " ||=== Klijenti u brzom redu ====||\n";
    for(int i = 0; i < brojac_brzi; i++)
    {
      n--;
      ispis(&brzi_red[i]);
    }
  }
}

void brisanje(salter *red)
{
  osoba *novi = new osoba;
  osoba pomocni_red[n];
  for(int i = 0; i < n; i++)
  {
    novi = FrontQ(red);
    DeQueueQ(red);
    memcpy(&pomocni_red[i],novi,sizeof(osoba));
  }
  InitQ(red);
  for(int i = 0; i < n; i++)
  {
    memcpy(novi,&pomocni_red[i],sizeof(osoba));
    if(novi -> ci == 4 && (2012 - novi -> godina_rodenja) <30 && novi-> di == 1 && novi -> tekuci_racun < 100)
      n--;
    else 
      if(novi -> ci == 1 && novi -> di == 2 && novi -> tekuci_racun > 5000)
	n--;
      else 
      {
	EnQueueQ(red,novi);
      }
  }
  for(int i = 0; i < n; i++)
  {
    memcpy(novi,&pomocni_red[i],sizeof(osoba));
    ispis(novi);
  }
}

int main()
{
  InitQ(red);
  system("clear");
  cout << "Unesite broj klijenata: ";
  cin >> n;
  generator(red);
  short izbor;
  system("clear");
  do
  {
    cout << "//======= Glavni izbornik ======= \\\\\n";
    cout << "||1. Dodavanje zapisa o klijentima\n";
    cout << "||2. Red brzih transakcija\n";
    cout << "||3. Brisanje iz reda\n";
    cout << "||4. Otvaranje novog saltera\n";
    cout << "||0. Izlaz iz programa\n||";
    cin >> izbor;
    system("clear");
    switch(izbor)
    {
	case 1:
	    dodaj_zapise(red);
	    break;
	case 2:
	    novi_brzi_red(red);
	    break;
	case 3:
	    brisanje(red);
	    break;
	case 4:
	    break;
    }
  }while(izbor);
  system("clear");
}

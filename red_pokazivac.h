struct osoba
{
  char ime[40];
  int godina_rodenja;
  int ai; //Kada ulazi u red
  int bi; //Trajanje transakcije
  int ci; //Prioritet klijenta
  int di; //Tip transakcije
  float tekuci_racun,devizni_racun;
  osoba *sljedeci;
};

struct salter
{
  osoba *front;
  osoba *rear;  
};

void InitQ(salter *red)
{
  osoba *prvi = new osoba;
  prvi -> sljedeci = NULL;
  red -> front = prvi;
  red -> rear = prvi;
}

osoba* FrontQ(salter *red)
{
  return red -> front -> sljedeci;
}

bool IsEmptyQ(salter *red)
{
  if(red -> rear == red -> front)
    return true;
  return false;
}

void EnQueueQ(salter *red,osoba *x)
{
  red -> rear -> sljedeci = x;
  red -> rear = x;
  x -> sljedeci = NULL;
}

void DeQueueQ(salter *red)
{
  osoba *temp = red -> front;
  red -> front = temp -> sljedeci;
  delete temp;
}

struct osoba
{
  char ime[40];
  int godina_rodenja;
  int ai; //Kada ulazi u red
  int bi; //Trajanje transakcije
  int ci; //Prioritet klijenta
  int di; //Tip transakcije
  float tekuci_racun,devizni_racun;
};

struct salter
{
  int front,rear;
  osoba *polje[1000];
};

int AddOne(int rear)
{
  rear = (rear+1)%1000;
  return rear;
}

void InitQ(salter *red)
{
  red -> front=0;
  red -> rear=999;
}

osoba* FrontQ(salter *red)
{
  return red -> polje[red -> front];
} 

bool IsEmptyQ(salter *red)
{
  if(AddOne(red->rear) == red -> front)
    return true;
  return false;
}

void EnQueueQ(salter *red,osoba *x)
{
  int zadnji = red -> rear;
  zadnji = AddOne(zadnji);
  red -> polje[zadnji] = x;
  red -> rear = zadnji;
}

void DeQueueQ(salter *red)
{
  red -> front = AddOne(red -> front);
}

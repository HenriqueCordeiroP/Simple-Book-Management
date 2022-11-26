#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livro
{ 
    char Titulo[50];
    char Autor[50];
    int NumReg;
    double Preco;
    struct livro *next;
} Livro;

Livro GetLivro()
{ 
    // Get book input
    Livro livro;
    printf("\n\tDigite o titulo em letras maiúsculas: ");
    fgets(livro.Titulo,50,stdin);
    printf("\n\tDigite o nome do autor: ");
    fgets(livro.Autor,50,stdin);
    printf("\n\tDigite o numero do registro: ");
    scanf("%d",&livro.NumReg);
    printf("\n\tDigite o preco do livro: ");
    scanf("%lf", &livro.Preco);
    rewind(stdin);

    return livro;
}

void PrintLivro(Livro **head)
{
    Livro *aux = *head;
    printf("\n\t titulo: %s", aux->Titulo);
    printf("\tAutor: %s", aux->Autor);
    printf("\t No.Reg: %d", aux->NumReg);
    printf("\t Preco: %.2lf\n", aux->Preco);
}

double findTitle(Livro **head, char *titleSearch)
{ 
  // Iterate through the linked list and compare with the inserted title
  Livro *aux = *head;
  while(aux!= NULL)
  {
    if(strcmp(aux->Titulo, titleSearch)==0)
    {
      return aux->Preco;
    }
    aux=aux->next;
  }
  return -1;
}

double findRegister(Livro **head, int regSearch)
{ 
  // Iterate through the linked list and compare with the inserted register number
  Livro *aux = *head;
  while(aux!= NULL)
  {
    if(aux->NumReg==regSearch)
    {
      return aux->Preco;
    }
    aux=aux->next;
  }
  return -1;
}

void insertBook(Livro **head, Livro *livro)
{ 
    Livro *aux = *head; 
    Livro *novo = (Livro *) malloc(sizeof(Livro));
    strcpy(novo->Titulo, livro->Titulo);
    strcpy(novo->Autor, livro->Autor);
    novo->NumReg = livro->NumReg;
    novo->Preco = livro->Preco;
  
    if(aux == NULL)
    {
        *head = novo;
        aux = novo;
        novo->next = NULL;
    }

    // From here on, the first char of each book is compared and inserted
    // in the linked list alphabetically
    else if(strcmp(aux->Titulo, livro->Titulo)>0)
    {
        *head = novo;
        novo->next = aux;
    }
    else
    {
        while(aux->next != NULL && (strcmp(aux->next->Titulo, livro->Titulo)<0))
        {
            aux = aux->next;
        }
        if(aux->next == NULL)
        {
        novo->next = NULL;
        aux->next = novo; 
        }
        else
        {
        novo->next = aux->next;
        aux->next = novo;
        } 
    }
}


void removeTitle(Livro **head, char *titleRemove)
{
  // Iterates the linked list and removes the title by comparison
  Livro *aux = *head;
  Livro *temp;

  if(strcmp(aux->Titulo,titleRemove)==0)
  {
    *head = aux->next; 
    free(aux);
  }
  else
  {
    while(aux->next->next != NULL && strcmp(aux->next->Titulo, titleRemove)!=0)
    {
        aux = aux->next;
    }
    if(strcmp(aux->next->Titulo, titleRemove)==0)
    {
        temp = aux->next; 
        aux->next = aux->next->next;
        free(temp);
    }
  }
}

void removeRegister(Livro **head, long int regRemove)
{
  // Iterates the linked list and removes the register number by comparison
  Livro *aux = *head;
  Livro *temp;

  if(aux->NumReg == regRemove)
  {
    *head = aux->next; 
    free(aux);
  }
  else
  {
    while(aux->next->next != NULL && aux->next->NumReg != regRemove)
    {
        aux = aux->next;
    }
    if(aux->next->NumReg == regRemove )
    {
        temp = aux->next; 
        aux->next = aux->next->next;
        free(temp);
    }
  }
}

int checkNull(FILE *fptr)
{
    return fptr==NULL;
}
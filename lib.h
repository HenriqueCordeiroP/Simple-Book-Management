#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livro{
    char Titulo[50];
    char Autor[50];
    int NumReg;
    double Preco;
    struct livro *next;
} Livro;

Livro GetLivro();
void PrintLivro(Livro **head);
double findTitle(Livro **head, char *titleSearch);
double findRegister(Livro **head, int regSearch);
void insertBook(Livro **head, Livro *livro);
void removeTitle(Livro **head, char *titleRemove);
void removeRegister(Livro **head, long int regRemove);
int checkNull(FILE *fptr);
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  Livro *livro = (Livro *)malloc(sizeof(Livro));
  char resp;
  FILE *fptr; 
  char menu[2];
  char titleSearch[50], titleRemove[50];
  int regSearch, regRemove;

  fptr = fopen(argv[1], "w+");

  // Checks if pointer to file is NULL (file not found)
  if (checkNull(fptr)) 
  {
    exit(1);
  }

  Livro *head = NULL;

  // Creates linked list by inserting the head
  while (fread(livro, sizeof(Livro), 1, fptr) == 1) 
  {
    insertBook(&head, livro);
  }

  fclose(fptr);

  while (1) 
  {
    // Interactive Menu
    printf("\n--MENU--\n[1] Inserir um Livro\n[2] Buscar um Livro\n[3] Remover um Livro\n[4] Salvar em arquivo\n[X] Sair\n> ");
    scanf("%s", menu);
    getchar();

    // End program
    if (strcmp(menu, "X") == 0) 
    {
      break;
    }

    // Adds book to linked list
    if (strcmp(menu, "1") == 0) 
    {
      *livro = GetLivro();
      insertBook(&head, livro);
    } 

    // Iterates through the linked list to find title or register number and returns the price
    else if (strcmp(menu, "2") == 0) 
    {
      char tipoBusca[2];
      printf("\n--MENU--\n[T] Buscar por Título\n[R] Buscar por número de Registro\n> ");
      scanf("%s", tipoBusca);
      getchar();
      if (strcmp(tipoBusca, "T") == 0) 
      {
        printf("\nQual título você deseja buscar?\nObs.: o título deve ser digitado em letras maiúsculas.\n> ");
        fgets(titleSearch, 50, stdin);

        double title = findTitle(&head, titleSearch);
        if (title >= 0)
        {
            printf("\nPreço de %s - R$%.2lf\n", titleSearch, title);
        } 
        else 
        {
          printf("\nERROR 404: BOOK NOT FOUND");
        }
      } 
      else if (strcmp(tipoBusca, "R") == 0) 
      {
        printf("\nQual número de registro você deseja buscar?\n> ");
        scanf("%d", &regSearch);
        if (findRegister(&head, regSearch) >= 0) 
        {
          printf("\nPreço do Número de Registro %d - R$%.2lf", regSearch, findRegister(&head, regSearch));
        } 
        else 
        {
          printf("\nERROR 404: BOOK NOT FOUND");
        }
      }
    } 

    // Iterates through the linked list to find title or register number and removes it
    else if (strcmp(menu, "3") == 0) 
    {
      char tipoRemocao[2];
      printf("\n--MENU--\n[T] Remover por Título\n[R] Remover por número de "
             "Registro\n> ");
      scanf("%s", tipoRemocao);
      getchar();

      if (strcmp(tipoRemocao, "T") == 0)
       {
        printf("\nQual título você deseja remover?\nObs.: o título deve ser digitado em letras maiúsculas.\n> ");
        fgets(titleRemove, 50, stdin);
        getchar();

        removeTitle(&head, titleRemove);
        printf("Título %c%s%c removido com sucesso.", '"', titleRemove, '"');
      } 
      else if (strcmp(tipoRemocao, "R") == 0) 
      {
        printf("\nQual número de registro você deseja buscar?\n> ");
        scanf("%d", regRemove);
        removeRegister(&head, regRemove);
        printf("Registro %d removido com sucesso.", regRemove);
      }
    } 

    // Saves the linked list to the .dat file
    else if (strcmp(menu, "4") == 0) 
    {
      fptr = fopen(argv[1], "w+");
      if (checkNull(fptr)) 
      {
        exit(1);
      }
      Livro *aux = head;
      while (aux != NULL) 
      {
        fprintf(fptr,"Titulo: %s\tAutor:%s\tPreco:%.2lf\n\tNo.Reg%d\n---\n",aux->Titulo, aux->Autor, aux->Preco, aux->NumReg);
        aux = aux->next;
      }
      printf("Livros salvos com sucesso!\n");
      fclose(fptr);
    }
  }

  puts("\n\nLISTA DE LIVROS DO ARQUIVO ");
  puts("==================================");
  while (head != NULL) 
  {
    PrintLivro(&head);
    head = head->next;
  }
  fclose(fptr);

  return 0;
}
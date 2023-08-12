/*----------------------------------------------------------------
                         Trabalho_SB
                         (header.h)
 -----------------------------------------------------------------
 DESCRIÇÃO:
 ----------------
 Bliblioteca que possui os protótipos das funções principais do programa.

 DESENVOLVEDORES:
 ----------------
  Nome: Gustavo Rodrigues Ribeiro

  Nome: Luca Mascarenhas Plaster

  Nome: Rafael de Souza Porto

-----------------------------------------------------------------
 DATA DA ÚLTIMA ALTERAÇÃO: 03 / 08 / 2023       11:14
----------------------------------------------------------------*/

#ifndef __HEADER__
#define __HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaração dos protótipos das funções;
void defFunct(); // Definição das funções;
void defLocalVar(); // Definição das variávies locais;
void atribuicao(); // Atribuições;
void funcCall(); // Chamada de funções;
void funcExpressoes(); // Expressões aritméticas;
void accessArrayGet(); // Acesso ao arrey - get;
void accessArraySet(); // Acesso ao arrey - set;
void condicionalIf();  // Declaração de condicional;
void condicionalEndif(); // Declaração de fim da condicional;
void retorno(); // Retorno da função;
void leave(); // Saída da função.


void salvaRegVerde(); // Salva registrador verde na pilha
void recupRegVerde(); // Recupera registrador verde na pilha
void salvaParam(); // Salva parâmetro na pilha
void recupParam(); // Recupera parâmetro na pilha
void cmplCondicionalIf(); // Imprime a comparação da condicional de acordo com os termos envolvidos

#endif

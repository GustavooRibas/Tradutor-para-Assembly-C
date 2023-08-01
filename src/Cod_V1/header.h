/*----------------------------------------------------------------
                        Trabalho_SB
                         (header.c)
 -----------------------------------------------------------------
 DESCRIÇÃO:
 ----------------
 Bliblioteca que possui os protótipos das funções principais do programa.

 DESENVOLVEDORES:
 ----------------
  Nome: Gustavo Rodrigues Ribeiro

  Nome: Luca Mascarenhas Plaster

  Nome:  Rafael de Souza Porto

-----------------------------------------------------------------
 DATA DA ÚLTIMA ALTERAÇÃO: 25 / 07 / 2023
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

// Funções novas (modificar local posteriormente)
void salvaRegVerde(); // Move um reg qualquer para um reg verde
void salvaParam(); // Move um reg qualquer para um param
void recupParam(); // Move um reg de param de volta pro reg de origem
void recupRegVerde(); 

#endif

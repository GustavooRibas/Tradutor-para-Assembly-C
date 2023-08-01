/*----------------------------------------------------------------
                        Trabalho_SB
                         (header.c)
 -----------------------------------------------------------------
 DESCRIÇÃO:
 ---------
 Implementação das funções da biblioteca "header.h", que contêm os protótipos das funções
 e as variaveis globais com os registradores.

 DESENVOLVEDORES:
 ----------------
  Nome: Gustavo Rodrigues Ribeiro

  Nome: Luca Mascarenhas Plaster

  Nome: Rafael de Souza Porto

-----------------------------------------------------------------
 REPOSITÓRIO DO PROJETO: https://github.com/GustavooRibas/Trabalho-de-Software-Basico/tree/main
-----------------------------------------------------------------
 DATA DA ÚLTIMA ALTERAÇÃO: 25 / 07 / 2023
----------------------------------------------------------------*/
#include "header.h"

// Variáveis globais auxiliares para armazenar as strings
char str[100], s1[20], s2[20], s3[20], s4[20], s5[20], s6[20], s7[20];
// Variáveis globais para armazenar os valores decimais
int ax, a1, a2, a3;

// Matriz com o nome dos registradores de 32 bits.
char registradores32[16][6] = {
    {"\%eax"},
    {"\%ebx"},
    {"\%ecx"},
    {"\%edx"},
    {"\%esi"},
    {"\%edi"},
    {"\%ebp"},
    {"\%esp"},
    {"\%r8d"},
    {"\%r9d"},
    {"\%r10d"},
    {"\%r11d"},
    {"\%r12d"},
    {"\%r13d"},
    {"\%r14d"},
    {"\%r15d"},
};

// Matriz com o nome dos registradores de 64 bits.
char registradores64[16][6] = {
    {"\%rax"},
    {"\%rbx"},
    {"\%rcx"},
    {"\%rdx"},
    {"\%rsi"},
    {"\%rdi"},
    {"\%rbp"},
    {"\%rsp"},
    {"\%r8"},
    {"\%r9"},
    {"\%r10"},
    {"\%r11"},
    {"\%r12"},
    {"\%r13"},
    {"\%r14"},
    {"\%r15"},
};

//Matriz auxiliar para os registradores verdes
char vet_aux_reg_verde[16][6] = {

    {"     "},
    {"     "},
    {"     "},
    {"     "},
    {"     "},
    {"     "},
    {"     "},
    {"     "},
    {"     "},
    {"     "},
    {"     "},
    {"     "},
    {"     "},
    {"     "},
    {"     "},
    {"     "},
};

int qi = 0;        // Quantidade de ifs
short int pos[22]; // Posição dos elementos em uma pilha do vetor
char posparam = 0; // Quantidade de parâmetros de uma função
char qtd_reg_verde = 0; // Quantidade de registradores verdes utilizados na função (Variaveis reg)

void defFunct()
{
  sscanf(str, "%s %s %s %s %s", s1, s2, s3, s4, s5);
  printf(".globl %s\n", s2);
  printf("%s:\n", s2);
  printf("pushq %s\n", registradores64[6]);
  printf("movq %s, %s\n", registradores64[7], registradores64[6]);

  if (!strcmp(s3, "pa1") || !strcmp(s3, "pi1"))
    posparam++;
  if (!strcmp(s4, "pa2") || !strcmp(s4, "pi2"))
    posparam++;
  if (!strcmp(s5, "pa3") || !strcmp(s5, "pi3"))
    posparam++;

  qtd_reg_verde = 0;

}

//Função para salvar registradores verdes no inicio da função (Pilha)
void salvaRegVerde(){

  if(qtd_reg_verde!=0){ //Salva os registradores verdes no inicio da função (Pilha)

        int aux = 0;
        int aux2 = qtd_reg_verde;
        while (aux2)
        {
          printf("    movq %s, -%d(%s)\n", registradores64[12 + aux], pos[aux + 12], registradores64[6]);
          aux++;
          aux2--;
        }
  }
}

//Função para recuperar registradores verdes no final da função (Pilha)
void recupRegVerde(){

   if(qtd_reg_verde!=0){ //Recupera os registradores verdes no final da função (Pilha)

        int aux = 0;
        int aux2 = qtd_reg_verde;
        while (aux2)
        {
          printf("    movq -%d(%s), %s\n", pos[aux + 12], registradores64[6], registradores64[12 + aux]);
          aux++;
          aux2--;
        }

        printf("\n");
  }
}

// Função para a definição das variáveis locais, vetores locais e parâmetros
void defLocalVar()
{
  int cont = 0;
  while (1)
  {
    scanf("%[^\n]%*c", str);
    sscanf(str, "%s", s1);
    if (!strcmp("var", s1)) // Salva a variável local na pilha
    {
      sscanf(str, "%s %2s %d", s1, s2, &ax);
      sscanf(str, "%s %s", s1, s2);
      cont += 4;
      pos[ax - 1] = cont;
      printf("    # %s: -%d \n", s2, cont);
    }
    else if (!strcmp("vet", s1)) // Salva o vetor local na pilha
    {
      sscanf(str, "%s %2s %d %s %2s %d", s1, s2, &ax, s3, s4, &a1);
      cont += 4 * a1;
      pos[ax - 1] = cont;
      printf("    # %s%d: -%d \n", s2, ax, cont);
    }
    else if (!strcmp("reg", s1)) // Salva o registrador local (verde) na pilha
    {
      sscanf(str, "%s %2s %d", s1, s2, &ax);
      sscanf(str, "%s %s", s1, s2);

      if (cont % 8)
        cont += 4;

      cont += 8;
      pos[qtd_reg_verde + 12] = cont;
      printf("    # %s: -%d ----> %s\n", s2, cont, registradores32[qtd_reg_verde + 12]);
      strcpy(vet_aux_reg_verde[ax - 1], registradores32[qtd_reg_verde + 12]);
      qtd_reg_verde++;
    }
    else if (!strcmp("enddef", s1)) // Salva os parametros na pilha
    {
      if (posparam != 0)
      {
        int aux = cont;
        int aux2 = posparam;
        aux = aux + posparam * 8;

        if (aux % 16)
          aux = aux + 16 - (aux % 16);

  /**/  if (cont % 8)
          cont = cont + 8 - (cont % 8);

        int aux3 = 0;
        while (aux2--)
        {
          cont += 8;
          pos[18 + aux3] = cont; // Salva o endereço dos parâmetros , valor ant [7 + aux3]
          printf("    # %s ->   -%d   # %do param\n", registradores64[5 - aux3], cont, aux3 + 1);
          aux3++;
        }/**/

        printf("    subq $%d, %s\n\n", aux, registradores64[7]);
      }
      else
      {
        if (cont % 16)
          cont = cont + 16 - (cont % 16);
        if (cont != 0)
          printf("    subq $%d, %s\n", cont, registradores64[7]);
      }

      salvaRegVerde();

      break;
    }
  }
}

// Função para salvar o parâmetro na pilha quando ocorre uma chamada de função (call)
void salvaParam(){

  int aux = 0;
  int aux2 = posparam;
  while (aux2)
  {
    printf("    movq %s, -%d(%s)\n", registradores64[5 - aux], pos[18 + aux], registradores64[6]);
    aux++;
    aux2--;
  }
}

// Função para recuperar o parâmetro na pilha quando ocorre uma chamada de função (call)
void recupParam(){

  int aux = 0;
  int aux2 = posparam;
  while (aux2)
  {
    printf("    movq -%d(%s), %s\n", pos[18 + aux], registradores64[6], registradores64[5 - aux]);
    aux++;
    aux2--;
  }
}

// Função para a realização da chamada de função (call) durante uma atribuição
void funcCall()
{

  salvaParam();

  printf("\n");

  sscanf(str, "%s %s %s %s %s %s %s", s1, s2, s3, s4, s5, s6, s7); //vi2 = call f1 ri5 pa2 pa3
  // verificando se existe o primeiro parâmetro
  if (strlen(s5) > 1)
  {
    sscanf(s5, "%2s %d", s2, &ax);
    if (!strcmp(s2, "ci")) // Para constantes inteiras
      printf("    movl $%d, %s\n", ax, registradores32[5]);
    else if (s2[1] == 'a') // Para va (variáveis arrays) ou pa (parâmetros arrays)
    {
      if (!strcmp(s2, "va")) // Variável array
        printf("    leaq -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores64[5]);
      else
        printf("    movq -%d(%s), %s\n", pos[17 + ax], registradores64[6], registradores64[5]); // Parâmetro array
    }
    else if (s2[1] == 'i') // Para vi (variável inteira) ou pi (parâmetro inteiro)
    {
      if (!strcmp(s2, "vi")) // Variável inteira
        printf("    movl -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores32[5]);
      else {

        if(!strcmp(s2, "ri")){
          printf("    movl %s, %s\n", vet_aux_reg_verde[ax - 1], registradores32[5]); // Registrador inteiro
        }
        else {
          printf("    movl -%d(%s), %s\n", pos[17 + ax], registradores64[6], registradores32[5]); // Parâmetro inteiro
        }
      }
    }
  }

  // verificando se existe o segundo parâmetro
  if (strlen(s6) > 1)
  {
    sscanf(s6, "%2s %d", s2, &ax);
    if (!strcmp(s2, "ci")) // Para constantes inteiras
      printf("    movl $%d, %s\n", ax, registradores32[4]);
    else if (s2[1] == 'a') // Para va (variáveis arrays) ou pa (parâmetros arrays)
    {
      if (!strcmp(s2, "va")) // Variável array
        printf("    leaq -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores64[4]);
      else
        printf("    leaq -%d(%s), %s\n", pos[17 + ax], registradores64[6], registradores64[4]); // Parâmetro array
    }
    else if (s2[1] == 'i') // Para vi (variável inteira) ou pi (parâmetro inteiro)
    {
      if (!strcmp(s2, "vi")) // Variável inteira
        printf("    movl -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores32[4]);
      else {

        if(!strcmp(s2, "ri")){
          printf("    movl %s, %s\n", vet_aux_reg_verde[ax - 1], registradores32[5]); // Registrador inteiro
        }
        else {
          printf("    movl -%d(%s), %s\n", pos[17 + ax], registradores64[6], registradores32[5]); // Parâmetro inteiro
        }
      }
    }
  }

  // verificando se existe o terceiro parâmetro
  if (strlen(s7) > 1)
  {
    sscanf(s7, "%2s %d", s2, &ax);
    if (!strcmp(s2, "ci")) // Para constantes inteiras
      printf("    movl $%d, %s\n", ax, registradores32[3]);
    else if (s2[1] == 'a') // Para va (variáveis arrays) ou pa (parâmetros arrays)
    {
      if (!strcmp(s2, "va")) // Variável array
        printf("    leaq -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores64[3]);
      else
        printf("    leaq -%d(%s), %s\n", pos[17 + ax], registradores64[6], registradores64[3]); // Parâmetro array
    }
    else if (s2[1] == 'i') // Para vi (variáveis inteiras) e pi (parâmetros inteiros)
    {
      if (!strcmp(s2, "vi")) // Variáveis inteiras
        printf("    movl -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores32[3]);
      else {

        if(!strcmp(s2, "ri")){
          printf("    movl %s, %s\n", vet_aux_reg_verde[ax - 1], registradores32[5]); // Registrador inteiro
        }
        else {
          printf("    movl -%d(%s), %s\n", pos[17 + ax], registradores64[6], registradores32[5]); // Parâmetro inteiro
        }
      }
    }
  }
  printf("    call %s\n", s4); // Chamada da função
  sscanf(s1, "%2s %d", s2, &ax);

  if(!strcmp(s2, "ri")){
    printf("    movl %s, %s\n", registradores32[0], vet_aux_reg_verde[ax - 1]); // %eax para registrador verde
  }
  else {
    printf("    movl %s, -%d(%s)\n", registradores32[0], pos[ax - 1], registradores64[6]); // %eax para pilha
  }

  printf("\n");

  recupParam();
}

// Função para a realização da atribução por expressões aritméticas ou atribuição simples
void funcExpressoes()
{
  sscanf(str, "%s %s %s %s %s", s1, s2, s3, s4, s5);
  if (strlen(s5) > 2) // Expressões complexas
  {
    sscanf(s3, "%2s %d", s7, &ax);
    if (!strcmp("vi", s7))
      printf("    movl -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores32[8]);
    else if (!strcmp("pi", s7))
      printf("    movl -%d(%s), %s\n", pos[17 + ax], registradores64[6], registradores32[8]);
    else if (!strcmp("ri", s7))
      printf("    movl %s, %s\n", vet_aux_reg_verde[ax - 1], registradores32[8]);
    else
      printf("    movl $%d, %s\n", ax, registradores32[8]);

    sscanf(s5, "%2s %d", s7, &ax);
    if (!strcmp("vi", s7))
      printf("    movl -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores32[9]);
    else if (!strcmp("pi", s7))
      printf("    movl -%d(%s), %s\n", pos[17 + ax], registradores64[6], registradores32[9]);
    else if (!strcmp("ri", s7))
      printf("    movl %s, %s\n", vet_aux_reg_verde[ax - 1], registradores32[9]);
    else
      printf("    movl $%d, %s\n", ax, registradores32[9]);

    if (s4[0] == '*') // Multiplicação
      printf("    imull %s, %s\n", registradores32[8], registradores32[9]);
    else if (s4[0] == '+') // Soma
      printf("    addl %s, %s\n", registradores32[8], registradores32[9]);
    else if (s4[0] == '-') // Subtração
      printf("    subl %s, %s\n", registradores32[9], registradores32[8]);
    else if (s4[0] == '/') // Divisão
    {
      // Com base no gabarito do exercício 1 do laboratório de mecanismos de controle
      printf("    movl %s, %s\n", registradores32[8], registradores32[0]);
      printf("    cltd \n");
      printf("    movl %s, %s\n", registradores32[9], registradores32[2]);
      printf("    idivl %s \n", registradores32[2]);
      printf("    movl %s, %s \n", registradores32[0], registradores32[9]);
    }

    sscanf(s1, "%2s %d", s7, &ax);

    if (!strcmp("pi", s7)){ //Caso a variável que recebe seja um parâmetro inteiro

      if (s4[0] == '-') // Caso tenha sido uma subtração
      printf("    movl %s, -%d(%s)\n", registradores32[8], pos[17 + ax], registradores64[6]);
      else
      printf("    movl %s, -%d(%s)\n", registradores32[9], pos[17 + ax], registradores64[6]);
    }
    else if (!strcmp("vi", s7)){ //Caso a variável que recebe seja uma variável inteira

      if (s4[0] == '-') // Caso tenha sido uma subtração
      printf("    movl %s, -%d(%s)\n", registradores32[8], pos[ax - 1], registradores64[6]);
      else
      printf("    movl %s, -%d(%s)\n", registradores32[9], pos[ax - 1], registradores64[6]);
    }
    else if (!strcmp("ri", s7)){ //Caso a variável que recebe seja um registrador inteiro

      if (s4[0] == '-') // Caso tenha sido uma subtração
      printf("    movl %s, %s\n", registradores32[8], vet_aux_reg_verde[ax - 1]);
      else
      printf("    movl %s, %s\n", registradores32[9], vet_aux_reg_verde[ax - 1]);
    }
  }
  else // Expressões simples
  {
    sscanf(s1, "%2s %d", s2, &a1);
    sscanf(s3, "%2s %d", s7, &ax);
    if (!strcmp("vi", s7)) //Caso o valor atribuido seja uma variável inteira
    {
      if (!strcmp("ri", s2)){ //Caso quem receberá a atribuição seja um registrador inteiro
        printf("    movl -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores32[2]);
        printf("    movl %s, %s\n", registradores32[2], vet_aux_reg_verde[a1 - 1]);
      }
      else{ //Caso quem receberá a atribuição seja uma variável inteira
        printf("    movl -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores32[2]);
        printf("    movl %s, -%d(%s)\n", registradores32[2], pos[a1 - 1], registradores64[6]);
      }
    }
    else if (!strcmp("pi", s7)) //Caso o valor atribuido seja um parâmetro inteiro
    {
      if (!strcmp("ri", s2)){ //Caso quem receberá a atribuição seja um registrador inteiro
        printf("    movl -%d(%s), %s\n", pos[17 + ax], registradores64[6], registradores32[2]);
        printf("    movl %s, %s\n", registradores32[2], vet_aux_reg_verde[a1 - 1]);
      }
      else{ //Caso quem receberá a atribuição seja uma variável inteira
        printf("    movl -%d(%s), %s\n", pos[17 + ax], registradores64[6], registradores32[2]);
        printf("    movl %s, -%d(%s)\n", registradores32[2], pos[a1 - 1], registradores64[6]);
      }
    }
    else if (!strcmp("ri", s7)){ //Caso o valor atribuido seja um registrador inteiro

      if (!strcmp("ri", s2)){ //Caso quem receberá a atribuição seja um registrador inteiro
        printf("    movl %s, %s\n", vet_aux_reg_verde[ax - 1], registradores32[2]);
        printf("    movl %s, %s\n", registradores32[2], vet_aux_reg_verde[a1 - 1]);
      }
      else{ //Caso quem receberá a atribuição seja uma variável inteira
        printf("    movl %s, %s\n", vet_aux_reg_verde[ax - 1], registradores32[2]);
        printf("    movl %s, -%d(%s)\n", registradores32[2], pos[a1 - 1], registradores64[6]);
      }

    }
    else{ //Caso o valor atribuido seja uma constante
      if (!strcmp("ri", s2)){ //Caso quem receberá a atribuição seja um registrador inteiro
        printf("    movl $%d, %s\n", ax, vet_aux_reg_verde[a1 - 1]);
      }
      else{ //Caso quem receberá a atribuição seja uma variável inteira
        printf("    movl $%d, -%d(%s)\n", ax, pos[a1 - 1], registradores64[6]);
      }
    }
  }
}

//Função para a atribuição de valores na chamada de função (call), atribuição simples e atribuição por expressões
void atribuicao()
{
  sscanf(str, "%s %s %s", s1, s2, s3);

  if (!strcmp("call", s3)) // Chamada de função
    funcCall();
  else
    funcExpressoes(); // Expressões aritméticas e atribuições
  printf("\n");
}

//Função para recuperação de um valor de um array
void accessArrayGet()
{
  sscanf(str, "%s %2s %d %s %2s %d %s %2s %d", s1, s2, &ax, s3, s4, &a1, s5, s6, &a2);

  printf("    movabs $%d, %s\n", a1, registradores64[8]);

  printf("    imulq $4, %s\n", registradores64[8]);

  if (!strcmp(s2, "va"))
    printf("    leaq -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores64[9]);
  else
    printf("    movq -%d(%s), %s\n", pos[17 + ax], registradores64[6], registradores64[9]);

  printf("    addq %s, %s\n", registradores64[9], registradores64[8]);

  printf("    movl (%s), %s\n", registradores64[8], registradores32[9]);

  printf("    movl %s, -%d(%s)\n", registradores32[9], pos[a2 - 1], registradores64[6]);

  printf("\n");
}

//Função para modificar o valor de uma posição de um array
void accessArraySet()
{
  sscanf(str, "%s %2s %d %s %2s %d %s %2s %d", s1, s2, &ax, s3, s4, &a1, s5, s6, &a2);

  printf("    movabs $%d, %s\n", a1, registradores64[8]);

  printf("    imulq $4, %s\n", registradores64[8]);

  if (!strcmp(s2, "va"))
    printf("    leaq -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores64[9]);
  else
    printf("    movq -%d(%s), %s\n", pos[17 + ax], registradores64[6], registradores64[9]);

  printf("    addq %s, %s\n", registradores64[9], registradores64[8]);
  if (!strcmp("ci", s6))
    printf("    movl $%d, (%s)", a2, registradores64[8]);
  else
  {
    printf("    movl -%d(%s), %s\n", pos[a2 - 1], registradores64[6], registradores32[9]);

    printf("    movl %s, (%s)\n", registradores32[9], registradores64[8]);
  }
  printf("\n");
}

// Função para a impressão da comparação da condicional de acordo com os termos envolvidos
void cmplCondicionalIf(){

  if (!strcmp("vi", s1)){ // Se o termo 'A' for variável inteira em "A <comparação> B"
      printf("begin_if%d:\n\n", qi);

      if (!strcmp("vi", s5)){ // Se o termo 'B' for variável inteira em "A <comparação> B"
        printf("    cmpl -%d(%s), -%d(%s)\n", pos[a1 - 1], registradores64[6], pos[ax - 1], registradores64[6]);
      }
      else if (!strcmp("pi", s5)){ // Se o termo 'B' for parâmetro inteiro em "A <comparação> B"
        printf("    cmpl -%d(%s), -%d(%s)\n", pos[17 + a1], registradores64[6], pos[ax - 1], registradores64[6]);
      }
      else if (!strcmp("ri", s5)){ // Se o termo 'B' for registrador inteiro em "A <comparação> B"
        printf("    cmpl %s, -%d(%s)\n", vet_aux_reg_verde[a1 - 1], pos[ax - 1], registradores64[6]);
      }
      else if(!strcmp("ci", s5)){ // Se o termo 'B' for constante inteira em "A <comparação> B"
        printf("    cmpl $%d, -%d(%s)\n", a1, pos[ax - 1], registradores64[6]);
      }
  }

  else if (!strcmp("pi", s1)){ // Se o termo 'A' for parâmetro inteiro em "A <comparação> B"
      printf("begin_if%d:\n\n", qi);

      if (!strcmp("vi", s5)){ // Se o termo 'B' for variável inteira em "A <comparação> B"
        printf("    cmpl -%d(%s), -%d(%s)\n", pos[a1 - 1], registradores64[6], pos[17 + ax], registradores64[6]);
      }
      else if (!strcmp("pi", s5)){ // Se o termo 'B' for parâmetro inteiro em "A <comparação> B"
        printf("    cmpl -%d(%s), -%d(%s)\n", pos[17 + a1], registradores64[6], pos[17 + ax], registradores64[6]);
      }
      else if (!strcmp("ri", s5)){ // Se o termo 'B' for registrador inteiro em "A <comparação> B"
        printf("    cmpl %s, -%d(%s)\n", vet_aux_reg_verde[a1 - 1], pos[17 + ax], registradores64[6]);
      }
      else if(!strcmp("ci", s5)){ // Se o termo 'B' for constante inteira em "A <comparação> B"
        printf("    cmpl $%d, -%d(%s)\n", a1, pos[17 + ax], registradores64[6]);
      }
  }

  else if (!strcmp("ri", s1)){ // Se o termo 'A' for registrador inteiro em "A <comparação> B"
      printf("begin_if%d:\n\n", qi);

      if (!strcmp("vi", s5)){ // Se o termo 'B' for variável inteira em "A <comparação> B"
        printf("    cmpl -%d(%s), %s\n", pos[a1 - 1], registradores64[6], vet_aux_reg_verde[ax - 1]);
      }
      else if (!strcmp("pi", s5)){ // Se o termo 'B' for parâmetro inteiro em "A <comparação> B"
        printf("    cmpl -%d(%s), %s\n", pos[17 + a1], registradores64[6], vet_aux_reg_verde[ax - 1]);
      }
      else if (!strcmp("ri", s5)){ // Se o termo 'B' for registrador inteiro em "A <comparação> B"
        printf("    cmpl %s, %s\n", vet_aux_reg_verde[a1 - 1], vet_aux_reg_verde[ax - 1]);
      }
      else if(!strcmp("ci", s5)){ // Se o termo 'B' for constante inteira em "A <comparação> B"
        printf("    cmpl $%d, %s\n", a1, vet_aux_reg_verde[ax - 1]);
      }
  }

  else if (!strcmp("ci", s1)){ // Se o termo 'A' for constante inteira em "A <comparação> B"
      printf("begin_if%d:\n\n", qi);

      if (!strcmp("vi", s5)){ // Se o termo 'B' for variável inteira em "A <comparação> B"
        printf("    cmpl -%d(%s), $%d\n", pos[a1 - 1], registradores64[6], ax);
      }
      else if (!strcmp("pi", s5)){ // Se o termo 'B' for parâmetro inteiro em "A <comparação> B"
        printf("    cmpl -%d(%s), $%d\n", pos[17 + a1], registradores64[6], ax);
      }
      else if (!strcmp("ri", s5)){ // Se o termo 'B' for registrador inteiro em "A <comparação> B"
        printf("    cmpl %s, $%d\n", vet_aux_reg_verde[a1 - 1], ax);
      }
      else if(!strcmp("ci", s5)){ // Se o termo 'B' for constante inteira em "A <comparação> B"
        printf("    cmpl $%d, $%d\n", a1, ax);
      }
  }
}

// Função para a definição da condicional
void condicionalIf()
{
  sscanf(str, "%s %s %s %s", s1, s2, s3, s4);

  //printf("\n\n printf 1: %s %s %s %s\n\n", s1, s2, s3, s4);

  qi++;

  sscanf(s2, "%2s %d", s1, &ax);
  sscanf(s4, "%2s %d", s5, &a1);

  //printf("\n\n printf 2: %s %d\n\n", s1, ax);
  //printf("\n\n printf 2: %s %d\n\n", s5, a1);

  //printf("\n\n printf 3: %s\n\n", s3);

  if (!strcmp("eq", s3)){ // Comparação igual (==)

    cmplCondicionalIf();
    printf("    jne end_if%d\n", qi);
  }

  else if (!strcmp("ne", s3)){ // Comparação diferente (!=)

    cmplCondicionalIf();
    printf("    je end_if%d\n", qi);
  }
  else if (!strcmp("lt", s3)){ // Comparação menor (<)

    cmplCondicionalIf();
    printf("    jge end_if%d\n", qi);
  }
  else if (!strcmp("le", s3)){ // Comparação menor igual (<=)

    cmplCondicionalIf();
    printf("    jg end_if%d\n", qi);
  }
  else if (!strcmp("gt", s3)){ // Comparação maior (>)

    cmplCondicionalIf();
    printf("    jle end_if%d\n", qi);
  }
  else if (!strcmp("ge", s3)){ // Comparação maior igual (>=)

    cmplCondicionalIf();
    printf("    jl end_if%d\n", qi);
  }
}

// Função para o reconhecimento e impressão do 'endif' ao final de uma condicional
void condicionalEndif()
{

  if (!strcmp("endif", s1))
    printf("end_if%d:\n", qi);
}

// Função para a impressão do 'leave' e 'ret' durante o final de uma função
void leave()
{
  printf("leave\nret\n\n");
  posparam = 0;
}

// Função para a realização do retorno ao final de uma função
void retorno()
{
  sscanf(str, "%s %s", s1, s2);
  sscanf(s2, "%2s %d", s3, &ax);

  if(qtd_reg_verde!=0)
    recupRegVerde();

  if (!strcmp(s3, "vi")) //Caso o retorno seja uma variável inteira
    printf("    movl -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores32[0]);
  else if (!strcmp(s3, "pi")) //Caso o retorno seja um parâmetro inteiro
    printf("    movl -%d(%s), %s\n", pos[17 + ax], registradores64[6], registradores32[0]);
  else if (!strcmp(s3, "va")) //Caso o retorno seja um array local
    printf("    leaq -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores64[0]);
  else if (!strcmp(s3, "pa")) //Caso o retorno seja um array parâmetro
    printf("    movq -%d(%s), %s\n", pos[17 + ax], registradores64[6], registradores64[0]);
  else if (!strcmp(s3, "ri")) //Caso o retorno seja um registrador inteiro
    printf("    movl %s, %s\n", vet_aux_reg_verde[ax - 1], registradores32[0]);
  else //Caso o retorno seja uma constante
    printf("    movl $%d, %s\n", ax, registradores32[0]);

  printf("\n");
  leave();
}

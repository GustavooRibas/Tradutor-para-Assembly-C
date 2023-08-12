<h1 align="center"> Tabalho de Software Básico </h1>
<p align="center"><img src="images/ufg.png" alt="Logo UFG" height="170" width="240"></p>


## Tabela de Conteúdos

* [Tabela de conteúdos](#tabela-de-conteúdos)
* [Integrantes](#integrantes)
* [Descrição do Projeto](#descrição-do-projeto)
    * [Como  compilar e rodar](#como-compilar-e-rodar)
* [Descrição da Linguagem](#descrição-da-linguagem)
    * [Definição da função](#definição-da-função)
    * [Variáveis Locais](#variáveis-locais)
    * [Corpo da Função](#corpo-da-função)
* [BNF da Linguagem](#bnf-da-linguagem)


## Integrantes

 - [*Gustavo Rodrigues Ribeiro*](https://github.com/GustavooRibas)
 - [*Luca Mascarenhas Plaster*](https://github.com/LucaPlaster)
 - [*Rafael de Souza Porto*](https://github.com/Rafaelsporto)

## Descrição do Projeto

O trabalho se baseia na implementação de um tradutor de uma linguagem simples (chamada de BPL – Bruno’s Programming Language) para Assembly.

### Como compilar e rodar

- O tradutor deve ser escrito na linguagem C e será compilado e testado no ambiente Linux 
- Para compilar o código execute a seguinte linha de comando
```
gcc -lm -o tradutor main.c header.h
```
- O tradutor deve ler um arquivo em BPL da entrada padrão (e.g., usando o *scanf*) e imprimir
a tradução desse programa em Assembly na saída padrão (e.g., usando o *printf*). Pode-se
criar um arquivo com a linguagem e utilizar o redirecionamento para testar:
```
./tradutor < prog.blp
```
* No nosso caso a forma com que o grupo está executando
no windows (porém pode ser executado da forma acima sem problemas):
```
tradutor <testes/prog.blp >testes/out.S
```
No Linux :
```
./tradutor <testes/prog.blp >testes/out.S
```
---

**Observação:** O tradutor deve imprimir as posições dos elementos na pilha em forma de comentários,
antes da alocação da pilha. Isso inclui variáveis locais ou qualquer posição de salvamento de
registradores (como se fosse o desenho da pilha). Por exemplo
```
# vi1: -4
# va2: -16
# vi3: -32
# rbx: -36
subq $48, %rsp
```
---
## Descrição da Linguagem

A linguagem é baseada na definição de funções (uma ou várias). As funções sempre retornam
algum valor.

### Definição da função
A definição de função inicia com a palavra-chave function, seguido pelo nome da função e
depois de zero a três parâmetros. O nome da função segue o padrão fN, onde N é um índice único
começando de 1 (1, 2, 3, etc.).

### Variáveis locais
Uma função pode ter no máximo quatro variáveis inteiras de pilha (int), quatro variáveis
inteiras de registrador (int) ou quatro arrays de inteiros (int[]) - totalizando, no máximo, doze
variáveis locais. Tanto as variáveis inteiras de pilha ou os arrays inteiros devem ser alocados na
pilha e não possuem valor inicial (têm “lixo” de memória).

No caso de variáveis locais de registrador, deve-se alocar um registrador para cada variável.
Esses registradores devem ser efetivamente utilizado no corpo da função.

### Corpo da função
O corpo da função é um conjunto de comandos que inicia depois da definição das variáveis.
Um comando pode ser (i) atribuição de variável inteira, (ii) alteração de uma posição do array, (iii)
recuperação de valor de uma posição de um array, (iv) condicional if ou (v) returno de um valor.

- #### Atribuição
Uma atribuição de variável inteira pode ser uma atribuição simples, uma expressão ou o
retorno de uma chamada de função.

- #### Chamada da função
As chamadas de função são permitidas na atribuição e utiliza a palavra-chave call seguida do
nome da função. Depois do nome da função são passados os parâmetros para função a ser chamada
(até três parâmetros).

- #### Acessso ao array
A recuperação de um valor de um array utiliza o comando get, no seguinte formato:
```
get *array* index *índice* to *destino*
```

Para modificar uma posição de um array, utiliza-se o comando set, no seguinte formato:
```
set *array* index *índice* with *valor*
```

- #### Condicional
O condicional if não possui else. A expressão só pode comparar variáveis inteiras (pilha ou
registrador), parâmetros inteiros ou constantes inteiras. Os operadores relacionais são:
   
   -  eq: igual
   -  ne: não igual
   -  lt: menor
   -  le: menor igual
   -  gt: maior
   -  ge: maior igual

O formato do if é:
```
if *condição*
*comando*
endif
```

- #### Retorno da Função
O comando return só poderá aparecer como último comando do corpo da função ou no
corpo do if. Toda função terá obrigatoriamente um return como último comando do corpo.

O formato do return é:
```
return *valor*
```

## BNF da Linguagem
```
<prog>          →      <func>
                |      <func> <prog>

<func>          →      <header> <defs> <cmds> <ret> '\n' 'end' '\n'

<header>        →      'function' <fname> <params> '\n'

<fname>         →      'f'<num>

<params>        →      ε
                |      <param> <params>

<param>         →      <parint>
                |      <pararr>

<parint>        →      'pi'<num>

<pararr>        →      'pa'<num>

<defs>          →      'def' '\n' <vardef> 'enddef' '\n'

<vardef>        →      'var' <varint> '\n'
                |      'reg' <regint> '\n'
                |      'vet' <vararr> 'size' <const> '\n'

<varint>        →      'vi'<num>

<regint>        →      'vr'<num>

<vararr>        →      'va'<num>

<const>         →      'ci'<snum>

<cmds>          →      <cmd> '\n'
                |      <cmd> '\n' <cmds>

<cmd>           →      <attr>
                |      <arrayget>
                |      <arrayset>
                |      <if>

<attr>          →      <varint> '=' <expr>
                |      <regint> '=' <expr>

<expr>          →      <valint>
                |      <oper>
                |      <call>

<valint>        →      <varint>
                |      <regint>
                |      <parint>
                |      <const>

<oper>          →      <valint> <op> <valint>

<op>            →      '+' | '-' | '*' | '/'

<call>          →      'call' <fname> <args>

<args>          →      ε
                |      <arg> <args>

<arg>           →      <valint>
                |      <array>

<array>         →      <vararr>
                |      <pararr>

<arrayget>      →      'get' <array> 'index' <const> 'to' <varint>
                |      'get' <array> 'index' <const> 'to' <regint>

<arrayset>      →      'set' <array> 'index' <const> 'with' <valint>

<if>            →      'if' <valint> <oprel> <valint> '\n' <body> '\n' 'endif'

<oprel>         →      'eq' | 'ne' | 'lt' | 'le' | 'gt' | 'ge'

<body>          →      <attr>
                |      <arrayget>
                |      <arrayset>
                |      <ret>

<ret>           →      'return' <valint>

<num>           →      <digit>
                |      <digit> <num>

<snum>          →      <num>
                |      '-'<num>

<digit>         →      '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7'| '8' | '9'
```

# Busca de Países com LibCurl e Json-C

Este projeto é uma aplicação C que faz uma requisição a uma API REST para buscar países por região e nome. A aplicação utiliza a biblioteca libcurl para realizar as requisições HTTP e a json-c para manipular os dados JSON retornados pela API.

## Requisitos

Antes de executar o código, é necessário ter as bibliotecas e ferramentas instaladas no seu sistema:
### 1. Compilador GCC (ou outro compilador C)

O código foi desenvolvido em C, portanto, um compilador como GCC é necessário para compilar o programa.

Instalação no Ubuntu/Debian:

    bash:

    sudo apt-get install build-essential

### 2. libcurl

A biblioteca libcurl é utilizada para realizar requisições HTTP.

Instalação no Ubuntu/Debian:

    bash

    sudo apt-get install libcurl4-openssl-dev

### 3. json-c

A biblioteca json-c é utilizada para manipular e parsear os dados JSON retornados pela API.

Instalação no Ubuntu/Debian:

    bash:

    sudo apt-get install libjson-c-dev

### 4. Make (Opcional)

Se quiser automatizar a compilação do código, o uso de Make pode facilitar o processo.

## Instalação no Ubuntu/Debian:

    bash:

    sudo apt-get install make

## Compilação

Para compilar o código, você pode usar o gcc diretamente ou utilizar um Makefile (se preferir).
Compilação Manual

    bash:

    gcc -o find_countries main.c -lcurl -ljson-c

## Compilação com Makefile

Crie um arquivo chamado Makefile com o seguinte conteúdo:

    makefile:

    CC = gcc
    CFLAGS = -lcurl -ljson-c
    TARGET = find_countries
    
    all:
    $(CC) -o $(TARGET) main.c $(CFLAGS) 

Em seguida, execute o comando:

    bash:

    make

## Execução

Depois de compilar o código, o binário executável será criado. Para executar o programa, basta rodar o comando abaixo:

    bash:

        ./find_countries

Você também pode passar outros parâmetros para a função findCountries, modificando a região e o termo de pesquisa diretamente no código (atualmente, a região é "Europe" e o termo é "por").
Estrutura do Código

O código está organizado da seguinte forma:

    Estrutura Country:
        Contém dois campos: name (nome do país) e population (população do país).

    Função init_string:
        Inicializa uma estrutura que será usada para armazenar o conteúdo da resposta HTTP.

    Função write_func:
        Função de callback para armazenar os dados recebidos da API.

    Função findCountries:
        Realiza a requisição HTTP para buscar países.
        Faz o parse dos dados JSON usando json-c.
        Armazena os países e suas populações.
        Ordena os países por população (em ordem crescente) e nome.
        Exibe os países ordenados.

    Função compareCountries:
        Usada para comparar os países durante a ordenação por qsort.

## Comentários Pertinentes

    Uso de Memória Dinâmica: A função init_string e o uso de malloc e realloc garantem que a memória seja alocada dinamicamente à medida que os dados da API são recebidos. Após a utilização, é importante liberar a memória alocada com free().

    Ordenação com qsort: O código usa qsort para ordenar os países com base em dois critérios:
        População: A ordenação é feita pela população de cada país.
        Nome: Em caso de populações iguais, a comparação é feita pelo nome do país.

    Bibliotecas Utilizadas:
        libcurl: Para realizar a requisição HTTP.
        json-c: Para fazer o parse e manipulação dos dados JSON recebidos da API.

    Limitações:
        O código armazena no máximo 100 países. Se o número de países for maior, o array countries[100] pode precisar ser ajustado.
        O código atual busca apenas uma página de resultados da API. Se a API retornar várias páginas, será necessário implementar a lógica de paginação para coletar todos os países.

## Exemplo de Saída

Abaixo está um exemplo de saída para a região "Europe" e a palavra-chave "por":

    Portugal, 10286263


Gabriel Danilo

Este projeto foi criado como parte de um exemplo para busca de países utilizando requisições HTTP em C.

<div style="margin: 32px auto" align="center" >
  <img src="./assets/logo.png" alt="project logo" width="250" />
</div>

<h1 align="center">GSiC - Grocery Store in C</h1>

Este projeto realiza procedimentos comuns de um caixa em um mercado. Existe uma base de dados em formato `csv`, que contém os produtos disponíveis. Ao rodar o programa, os produtos podem ser passados no caixa um à um. Ao final da compra, se assim desejar, é gerada uma notinha, ou recibo, com as informações da compra, como a data, o valor de cada produto, e o preço total.

### [Clique aqui para ver uma demonstração em vídeo](https://drive.google.com/file/d/1yQ8eaLHOqkbEe810dovin0SWaka78f52/view?usp=sharing)

## Tecnologias usadas no projeto

- `C` (linguagem de programação, **na versão 11**)
- `gcc` (compilador)
- `Makefile` (para automatizar o processo de compilação)
- `valgrind` (para verificação de erros e vazamento de memória)

## Detalhes técnicos

### Base de dados

A base de dados foi implementada em formato `csv` para fins de simplicidade. Por mais que as linhas desse arquivo tenham seus ids colocados em ordem, isso não é necessário para o bom funcionamento do programa. Na primeira linha do arquivo foram colocados os nomes das colunas para facilitar a leitura. Por isso, essa primeira linha é ignorada durante a leitura da base de dados.

### Estruturas de dados

Logo ao iniciar, o programa lê a base de dados e organiza os produtos contidos nela em uma **_árvore binária_**. Os produtos que são passados no caixa também são organizados dessa forma. Para garantir o bom funcionamento da árvore, e evitar que ela fique desbalanceada e comece a parecer com uma **_linked list_**, foi implementado também um algoritmo para balancear a árvore, movendo a sua raiz para o mais próximo do centro possível.

Decidi usar essa estrutura de dados porque neste projeto o ato de consultar dados ocorre com muita frequência. **_Árvores binárias_** permitem fácil aplicação de **_buscas binárias_**, possuindo uma eficiência de `O(logn)`. Além disso, o consumo de memória delas é bem moderado, diferente de **_tries_**, que são muito mais rápidas, chegando a atingir até mesmo `constant time`, mas que consomem bem mais memória.

Acredito que a operação mais custosa da aplicação é a construção de uma árvore à partir de dados ordenados, porque ela só é balanceada depois de pronta. Então se todos os dados estiverem ordenados, a cada loop, será necessário um passo a mais para inserir um novo dado na árvore.

### Arquivos de recibo (notinhas) 

Para os arquivos de recibos, decidi usar o formato `txt`, porque em notinhas de super mercado não costuma ter apenas as informações dos produtos comprados, mas também outras coisas, como a data, o valor total, o nome e endereço do estabelecimento, e assim por diante. Então acredito que seja uma boa ecolha usar `txt`, pois permite uma formatação mais livre.


## Instruções

Para rodar esse projeto na sua máquina, é importante ter o compilador `gcc` instalado, e também a ferramenta `make` (já vem por padrão em sistemas unix, mas vale a pena conferir). Feito isso, na raiz do projeto (o mesmo diretório em que se encontra o arquivo `Makefile`), rode o comando:

```
make all
```

Isso irá gerar uma pasta `objects/` e um arquivo binário chamado `gsic`. Para executar o programa, digite:

```
./gsic
```

A utilização do programa é bem auto descritiva, mas vale a pena explicar aqui. Basicamente, aparecerá na tela uma mensagem pedindo para inserir o id de um produto. Não existe nenhuma visualização prévia de quais são os produtos, isso porque, imaginando a situação de um caixa, ele apenas vai escanear algum identificador único no código de barras do produto, e as informações do produto serão buscadas no banco. Então neste momento basta inserir um número.


Ao inserir o número zero, apertar Enter, ou inserir qualquer caractér não numérico, o programa entenderá que você não pretende mais passar nenhum produto no caixa, e prosseguirá para a próxima etapa, mostrando os produtos selecionados em uma tabela no terminal. Caso nenhum produto seja selecionado, o programa apenas mostra uma mensagem de despedida e é encerrado. Mas caso você tenha passado pelo menos um produto no caixa, então você terá a oportunidade de escolher gerar uma notinha ou não. Caso você apenas pressione Enter, o programa assumirá que você deseja uma notinha, e ela será gerada dentro de uma pasta `receipts/` no nível do diretório raiz.


Depois da notinha ser gerada, o programa será encerrado com uma mensagem amigável.


Se você possuir o `valgrind` instalado e quiser verificar se existe algum erro na aplicação ou algum vazamento de memória, basta rodar:

```
valgrind ./gsic
```

Caso deseje remover todos os arquivos gerados na compilação(ou seja, ao rodar `make all`), basta usar o comando:

```
make clean
```


## Considerações finais

Em grande parte, o objetivo deste projeto é fortalecer meu conhecimento em estruturas de dados e algoritmos, e na linguagem `C`. Essa é uma ferramenta que gosto muito. Apesar de antiga, é uma linguagem ainda muito usada, muito útil, divertida, e por debaixo dos panos está em todo lugar. Além disso, me traz um pouco de nostalgia, já que quando comecei a aprender conceitos de ciência da computação e programação pela primeira vez, foi utilizando linguagem `C`, no curso [CS50X](https://cs50.harvard.edu/x/2020/), no final de 2020. Acho muito legal a grande liberdade que essa ferramenta concede, e programar em _low-level_, por mais que seja mais trabalhoso em muitos aspectos, pode trazer maior eficiência. Sempre há um _trade off_.

Estou bem satisfeito com este projeto. Existem outras features que seriam legais de implementar, mas que não fazem parte do _MVP_. Por exemplo, um controle de estoque dos produtos, _CRUD_ da base de dados, login no modo gerente e base de dados para funcionários.

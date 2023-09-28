# Autocomplete
Terceiro projeto para a disciplina 'Linguagem de Programação I', desenvolvido em Abril de 2021. Universidade Federal do Rio Grande do Norte

Linguagem de Programação I - T01
Projeto de Programação #4

Aluno: Gabriel Alves Pinheiro Lima
Professor: Selan Rodrigues dos Santos

Comando de compilação: gpp main.cpp -o main
Comando de execução: ./main data/wiktionary.txt
Link do git: https://github.com/Gaplima/Autocomplete

Autocomplete

   Este trabalho consiste de desenvolver em c++ um programa em que o usuário digita uma certa string e o programa confere no banco de dados todas as palavras que possuem a string como "prefixo". Caso não tenham palavras com o prefixo, o código informa esta notícia ao usuário.
   O código foi feito inteiramente por mim, Gabriel Alves, utilizando de alguns conceitos aprendidos nos encontros do Zoom, em disciplinas anteriores ou em pesquisas. Este código é composto de um arquivo main.cpp e por uma pasta data contendo 1 arquivo .txt com a database. O arquivo principal consiste de 1 função do tipo int e duas do tipo void que facilitaram a dinamizar o desenvolvimento.

   Algumas partes solicitadas no arquivo .pdf eu não consegui fazer por motivos como erro de compilação, segmentation fault ou simplesmente por eu não saber como aplicar da maneira requisitada, são elas:
	-Não consegui fazer o código rodar com o arquivo cities.txt, deu segmentation fault em alguns trechos da execução, acredito que pela quantidade de linhas;
	-Não consegui converter as letras maiúsculas para minúsculas, nem das linhas do database, nem da string que o usuário insere;
	-O projeto não possui nenhuma classe.

   Já um detalhe do código foi feito de maneira diferente da solicitada no .pdf do projeto, para se adaptar melhor ao resto do código. Este detalhe é:
	-Não consegui fazer o jogador sair do programa apertando ctrl+d, adaptei para o programa encerrar quando o usuário digitar desejosair e apertar enter.

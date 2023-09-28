#include <iostream>
#include <string.h>
#include <fstream>
#include <algorithm>
using namespace std;

void menu(string alfab[], int qtt); //Função que ordena alfabeticamente as linhas da database e recebe a palavra que o usuário busca
void compara(string palavra, string alfab[], string texto[], int qtt); //Função que busca a palavra (inserida pelo usuário) na lista, ordena todas as ocorrências na ordem do parâmetro e exibe os resultados na tela

int main(int argc, char *argv[]){
 	cout << "============================================\n  Bem vindo ao programa Autocomplete 1.0\n  Copyright (C) 2021, Gabriel Alves P Lima\n============================================\n\n";
	int erro = 0; //Variável para ver se a abertura do arquivo foi bem sucedida
	string firstline; //String que recebe a primeira linha do arquivo, que contém a quantidade de linhas necessária
	int qtt;//int que receberá a quantidade de linhas do arquivo
	if (argc == 2){//Confere se a quantidade de argumentos da command line está correta
		cout << "Preparando-se para ler o arquivo de database " << argv[1] << "...\n";
		ifstream datab;
		datab.open(argv[1]);//Abre o arquivo

		if (datab.is_open()){
			cout << "Arquivo database aberto!\n"; //Confere se a abertura funcionou
			getline(datab, firstline);
			qtt = stoi(firstline); //A primeira linha do arquivo é copiada para o int qtt, que agora possui a quantidade de linhas correta
			string linhas[qtt]; //String com a quantidade de linhas "úteis" do arquivo
			int lin = 0;
			while (getline(datab, linhas[lin]) && lin < qtt -1){ //Pada linha do arquivo é passada para uma posição do vetor string
				if (lin == qtt){
					break;
				}
				lin++;
			}
			datab.close();
			string alfab[qtt]; 
			for (int i = 0; i < qtt; i++){ //String auxiliar idêntica à que tem as linhas do arquivo, por precaução
				alfab[i] = linhas[i].c_str();
			}
			menu(alfab, qtt); //A String auxiliar e o int qtt são enviados para a próxima função
		}
	}
	else{
		erro = 1;
	}
	if (erro == 1){
		cout << "Houve um erro na execução do programa!\n";
	}
	cout << "Programa encerrado!"; //O Código se encerra aqui
	return 0;
}

void menu(string alfab[], int qtt){
	string texto[qtt]; //String que receberá apenas a parte de texto de cada linha, para facilitar na ordenação alfabética
	cout << "Preparando-se para ordenar a lista alfabeticamente!\n";
	for (int i = 0; i < qtt; i++){
		for (int j = 0; j < alfab[i].length(); j++){
			if (j >= 15){ //No arquivo de database original as partes textuais se iniciam no 15º caractere de cada linha
				texto[i] += alfab[i][j];
			}
		}
	}
	for (int i = 0; i < qtt; i++){
		string auxiliar;
		for (int j = i+1; j < qtt; j++){
			if (texto[i] > texto[j]){ //Ordenação é feita comparando os strings do vetor texto[], mas as linhas do vetor alfab[] também trocam de posição
				auxiliar = alfab[j];
				alfab[j] = alfab[i];
				alfab[i] = auxiliar;
				auxiliar = texto[j];
				texto[j] = texto[i];
				texto[i] = auxiliar;
			}
		}
	}
	cout << "Lista ordenada com sucesso!\n";
	int sair = 0; //Variável para controlar o loop while
	string palavra;
	while (sair !=1){
		cout << "\n>>>Digite uma palavra e aperte ENTER, caso deseja sair digite 'desejosair': ";
		cin >> palavra; //Usuário insere o prefixo desejado
		cout << "\n";
		if (palavra == "desejosair"){ //Input de escape, que encerra o loop e o código
			sair = 1;
			break;
		}
		compara(palavra, alfab, texto, qtt); //Input do usuário, vetor ordenado, vetor com a parte textual e quantidade de elementos são levados à próxima função
	}
}

void compara(string palavra, string alfab[], string texto[], int qtt){
	//Três variáveis que representam o início, o meio e o fim da área buscada. Ao longo dos ifs/elses seus valores podem se alterar
	int ini = 0;
	int fim = qtt;
	int meio = (ini + fim)/2;

	//Duas variáveis que receberão a primeira e a última linhas em que o input é prefixo
	int posini = 0;
	int posfim = 0;

	for (int i = 0; meio > 1; i++){
		meio = (ini + fim)/2;
		if (texto[meio] < palavra){ //Confere se (alfabeticamente) a palavra desta posição está antes ou depois do input
			ini = meio;
		}
		else{ //Caso a da posição n esteja depois e a da n-1 esteja antes, chegamos a uma possível primeira ocorrência
			if (texto[meio -1] < palavra){
				posini = meio;
				meio = 0;
			}
			else{
				fim = meio;
			}
		}
	}

	int erro = 0; //Variável coringa para testar erro

	for (int i = 0; i < palavra.length(); i++){ //Código confere se foi encontrado algum resultado para o input. Caso negativo a segunda busca não é feita
		if (palavra[i] != texto[posini][i]){
			erro = 1;
			i = palavra.length() +1;
		}
	}
	if (erro == 1){
		cout << ">>>Não foram encontrados resultados para a string inserida.\n";
	}

	else{ //Como foi encontrada a primeira ocorrência, pegamos sua posição para a variável ini e vamos buscar binariamente a última ocorrência
		ini = posini;
		fim = qtt;
		palavra += "zzzz"; //Única forma que achei de buscar a última ocorrência de forma semelhante à que usei na da primeira ocorrência
		meio = (ini + fim)/2;
		for (int i = 0; meio > 1; i++){ //Fazemos novamente uma busca binárià
			meio = (ini + fim)/2;
			if (texto[meio] < palavra){
				if (texto[meio +1] > palavra){
					posfim = meio;
					meio = 0;
				}
				else{
					ini = meio;
				}
			}
			else{
					fim = meio;
			}
		}

		int final = posfim-posini + 1;
		string exib[final]; //Vetor string que receberá apenas as linhas que a input é prefixo
		int j = 0;

		for (int i = posini; i <= posfim; i++){ //For para copiar as linhas "certas" do vetor alfab[] ao vetor exib[]
			exib[j] = alfab[i];
			j++;
		}

		for (int i = 0; i < final; i++){ //For para ordenar o vetor exib pelo parâmetro original
			string auxiliar;
			for (int j = i+1; j < final; j++){
				if (exib[i] < exib[j]){
					auxiliar = exib[j];
					exib[j] = exib[i];
					exib[i] = auxiliar;
				}
			}
		}

		for (int i = 0; i < final; i++){ //For simples para exibir na tela as linhas certas
			cout << exib[i] << "\n";
		}
	}
}
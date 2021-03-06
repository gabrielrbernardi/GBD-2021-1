#include <bits/stdc++.h>
using namespace std;

/********
Integrantes do grupo
Bruno Oliveira Sinhoroto - 11821BCC044
Gabriel Ribeiro Bernardi - 11821BCC036
Guilherme Soares Correa - 11821BCC026
*********/

void limpa(){
    setbuf(stdin, NULL);
}

int main()
{
    ifstream arquivoEntrada("cep.txt");                             //Abre o arquivo para leitura
    ofstream arquivoSaida("cep2.txt");                               //Abre o arquivo para escrita

    if(!arquivoEntrada.is_open()){
        cout << "Arquivo de entrada nao encontrado. Por favor, verifique e tente novamente!" << endl << "Insira um arquivo com nome 'cep.txt'" << endl;
        return 0;
    }

    if(!arquivoSaida.is_open()){
        cout << "Nao foi possivel abrir o arquivo de saida. Por favor, verifique e tente novamente!" << endl;
        return 0;
    }

    string strTemp, inputStringFile;
    string breakString = "\t";
    string substring;
    int delimitadorWhile = 3;
    while(getline (arquivoEntrada, strTemp)){
        //formatacao da string para escrita no arquivo
        for(int i = 0; i <= delimitadorWhile; i++){
            int posicaoTabulacao = strTemp.find(breakString);       //Recebe a posicao da tabulacao
            substring = strTemp.substr(0, posicaoTabulacao);
            strTemp.erase(0, posicaoTabulacao+1);                   //Exclui campo + '\t'
            if(i != 0){
                inputStringFile.insert(0, "|");
            }
            inputStringFile.insert(0, substring);
        }
        arquivoSaida << inputStringFile << endl;                    //Escrita da string no arquivo de saida
        inputStringFile = "";
    }
    //Fecha arquivos de entrada e sa�da
    arquivoSaida.close();
    cout << "Arquivo 1 encerrado com sucesso" << endl;
    arquivoEntrada.close();
    cout << "Arquivo 2 encerrado com sucesso" << endl;

    ifstream arquivoEntrada1("cep2.txt");                           //Abre arquivo para leitura

    if(!arquivoEntrada1.is_open()){
        cout << "Arquivo de entrada n�o encontrado. Por favor, verifique e tente novamente!" << endl << "Insira um arquivo com nome 'cep2.txt'" << endl;
        return 0;
    }

    int opcao, qtdResultados, qtdLinhas;
    string termoBusca, resultado;
    while(1){
        cout << "1 - Busca por Logradouro\n2 - Busca por Cidade\n3 - Busca por UF\n4 - Busca por CEP\n5 - Sair" << endl;
        cout << "Digite uma opcao: ";
        scanf("%d", &opcao);
        if(opcao == 5){                                             //Opcao para encerra aplicacao
            arquivoEntrada1.close();                                //Encerra arquivo de leitura
            cout << "Programa finalizado" << endl;
            break;
        }
        cout << "Qual termo deseja buscar: ";
        limpa();                                                    //Limpa o buffer do teclado para a leitura da string de busca
        getline (cin, termoBusca);
        limpa();                                                    //Limpa o buffer do teclado para a leitura da string de busca

        string mensagem = "O tipo de busca escolhida foi: Busca por ";

        if(opcao == 1){                                             //Busca por rua
            mensagem.append("Logradouro");
            qtdResultados = 0;                                      //Variavel para mostrar a quantidade de resultados encontrados
            arquivoEntrada1.clear();                                //Limpa o estado do ifstream antes de chamar a proxima instrucao para leitura do arquivo
            arquivoEntrada1.seekg(0);                               //Posiciona o cursor na primeira linha e primeiro caractere do arquivo
            qtdLinhas = 0;                                          //Variavel para mostrar a quatidade de linhas lidas no arquivoEntrada1
            while(getline (arquivoEntrada1, resultado)){
                qtdLinhas++;
                strTemp = resultado.substr(0, resultado.find("|"));
                if(strTemp.find(termoBusca, 0) != string::npos){
                    cout << resultado << endl;
                    qtdResultados++;
                }
            }
        }else if(opcao == 2){                                       //Busca por cidade
            mensagem.append("Cidade");
            qtdResultados = 0;                                      //Variavel para mostrar a quantidade de resultados encontrados
            arquivoEntrada1.clear();                                //Limpa o estado do ifstream antes de chamar a proxima instrucao para leitura do arquivo
            arquivoEntrada1.seekg(0);                               //Posiciona o cursor na primeira linha e primeiro caractere do arquivo
            qtdLinhas = 0;                                          //Variavel para mostrar a quatidade de linhas lidas no arquivoEntrada1
            while(getline (arquivoEntrada1, resultado)){
                qtdLinhas++;
                strTemp = resultado.substr(resultado.find("|")+1, resultado.size());
                if(strTemp.find(termoBusca, 0) != string::npos){
                    cout << resultado << endl;
                    qtdResultados++;
                }
            }
        }else if(opcao == 3){                                       //Busca por UF
            mensagem.append("UF");
            qtdResultados = 0;                                      //Variavel para mostrar a quantidade de resultados encontrados
            arquivoEntrada1.clear();                                //Limpa o estado do ifstream antes de chamar a proxima instrucao para leitura do arquivo
            arquivoEntrada1.seekg(0);                               //Posiciona o cursor na primeira linha e primeiro caractere do arquivo
            qtdLinhas = 0;                                          //Variavel para mostrar a quatidade de linhas lidas no arquivoEntrada1
            while(getline (arquivoEntrada1, resultado)){
                qtdLinhas++;
                strTemp = resultado.substr(resultado.find("|")+1, resultado.size());
                strTemp = strTemp.substr(strTemp.find("|")+1, strTemp.size());
                if(strTemp.find(termoBusca, 0) != string::npos){
                    cout << resultado << endl;
                    qtdResultados++;
                }
            }
        }else if(opcao == 4){                                       //Busca por CEP
            mensagem.append("CEP");
            qtdResultados = 0;                                      //Variavel para mostrar a quantidade de resultados encontrados
            arquivoEntrada1.clear();                                //Limpa o estado do ifstream antes de chamar a proxima instrucao para leitura do arquivo
            arquivoEntrada1.seekg(0);                               //Posiciona o cursor na primeira linha e primeiro caractere do arquivo
            qtdLinhas = 0;                                          //Variavel para mostrar a quatidade de linhas lidas no arquivoEntrada1
            while(getline (arquivoEntrada1, resultado)){
                qtdLinhas++;
                strTemp = resultado.substr(resultado.find("|")+1, resultado.size());
                strTemp = strTemp.substr(strTemp.find("|")+1, strTemp.size());
                strTemp = strTemp.substr(strTemp.find("|")+1, strTemp.size());
                if(strTemp.find(termoBusca, 0) != string::npos){
                    cout << resultado << endl;
                    qtdResultados++;
                }
            }
        }
        cout << endl << mensagem << endl;
        cout << "O termo buscado foi: " << termoBusca << endl;
        cout << "Foram lidas " << qtdLinhas << " linhas" << endl;
        if(qtdResultados == 1){
            cout << "Foi encontrado " << qtdResultados << " resultado" << endl;
        }else{
            cout << "Foram encontrados " << qtdResultados << " resultados" << endl;
        }
    }
}

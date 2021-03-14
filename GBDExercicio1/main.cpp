#include <bits/stdc++.h>
using namespace std;

void limpa(){
    setbuf(stdin, NULL);
}

int main()
{
    ifstream arquivoEntrada("cep.txt");
    ofstream arquivoSaida("cep2.txt");

    string strTemp, inputStringFile;
    string breakString = "\t";
    string substring;
    int delimitadorWhile = 3;
    while(getline (arquivoEntrada, strTemp)){
        for(int i = 0; i <= delimitadorWhile; i++){
            int posicaoTabulacao = strTemp.find(breakString);   //Recebe a posicao da tabulacao
            substring = strTemp.substr(0, posicaoTabulacao);    //
            strTemp.erase(0, posicaoTabulacao+1);               //Exclui campo + '\t'
            if(i != 0){
                inputStringFile.insert(0, "|");                     //Prepara string para arquivo de saida
            }
            inputStringFile.insert(0, substring);
        }
        arquivoSaida << inputStringFile << endl;
        inputStringFile = "";
    }
    arquivoSaida.close();
    cout << "Arquivo fechado com sucesso" << endl;

    ifstream arquivoEntrada1("cep2.txt");
    int opcao, qtdResultados, qtdLinhas;
    string termoBusca;
    while(1){
        cout << "1 - Busca por Rua\n2 - Busca por Cidade\n3 - Busca por UF\n4 - Busca por CEP" << endl;
        cout << "Digite uma opcao: ";
        scanf("%d", &opcao);
        if(opcao == 5){
            break;
        }
        cout << "Qual termo deseja buscar: ";
        limpa();
        getline (cin, termoBusca);
        cout << termoBusca << endl;
        limpa();

        if(opcao == 1){
            qtdResultados = 0;                                      //Variavel para mostrar a quantidade de resultados encontrados
            arquivoEntrada1.clear();                                //Limpa o estado do ifstream antes de chamar a proxima instrucao para leitura do arquivo
            arquivoEntrada1.seekg(0);                               //Posiciona o cursor na primeira linha e primeiro caractere do arquivo
            qtdLinhas = 0;                                          //Variavel para mostrar a quatidade de linhas lidas no arquivoEntrada1
            while(getline (arquivoEntrada1, strTemp)){
                qtdLinhas++;
                strTemp = strTemp.substr(0, strTemp.find("|"));
                if(strTemp.find(termoBusca, 0) != string::npos){
                    cout << strTemp << endl;
                    qtdResultados++;
                }
            }
            cout << "Foram lidas " << qtdLinhas << " linhas" << endl;
            cout << "Foram encontrados " << qtdResultados << " resultados" << endl;
        }else if(opcao == 2){
            qtdResultados = 0;                                      //Variavel para mostrar a quantidade de resultados encontrados
            arquivoEntrada1.clear();                                //Limpa o estado do ifstream antes de chamar a proxima instrucao para leitura do arquivo
            arquivoEntrada1.seekg(0);                               //Posiciona o cursor na primeira linha e primeiro caractere do arquivo
            qtdLinhas = 0;                                          //Variavel para mostrar a quatidade de linhas lidas no arquivoEntrada1
            while(getline (arquivoEntrada1, strTemp)){
                qtdLinhas++;
                strTemp = strTemp.substr(strTemp.find("|")+1, strTemp.end());
                if(strTemp.find(termoBusca, 0) != string::npos){
                    cout << strTemp << endl;
                    qtdResultados++;
                }
            }
            cout << "Foram lidas " << qtdLinhas << " linhas" << endl;
            cout << "Foram encontrados " << qtdResultados << " resultados" << endl;
        }

    }
}

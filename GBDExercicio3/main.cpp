#include <bits/stdc++.h>
using namespace std;

#define pathArquivoBase "cep.txt"
#define pathArquivoIndex "cep2.txt"

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
    ifstream arquivoEntrada(pathArquivoBase);                              //Abre o arquivo para leitura
    ofstream arquivoSaida(pathArquivoIndex);                               //Abre o arquivo para escrita

    int qtdLinhasTotal = 0;

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
    arquivoSaida << arquivoEntrada.tellg() << endl;
    while(getline (arquivoEntrada, strTemp)){
        cout << arquivoEntrada.tellg() << endl;
        arquivoSaida << arquivoEntrada.tellg() << endl;
        qtdLinhasTotal++;
    }
    //Fecha arquivos de entrada e saida
    arquivoSaida.close();
    cout << "Arquivo 1 encerrado com sucesso" << endl;
    arquivoEntrada.close();
    cout << "Arquivo 2 encerrado com sucesso" << endl;

    ifstream arquivoIndex(pathArquivoIndex);                           //Abre arquivo para leitura
    ifstream arquivoBaseBusca(pathArquivoBase);

    if(!arquivoIndex.is_open()){
        cout << "Arquivo de index nao encontrado. Por favor, verifique e tente novamente!" << endl << "Insira um arquivo com nome " << pathArquivoIndex << endl;
        return 0;
    }
    if(!arquivoBaseBusca.is_open()){
        cout << "Arquivo de busca nao encontrado. Por favor, verifique e tente novamente!" << endl << "Insira um arquivo com nome " << pathArquivoBase << endl;
        return 0;
    }

    while(1){
        string linha, conteudoLinha;
        long int qtdLinha = 0, linhaBusca = 0;
        cout << "Digite a linha que deseja buscar: ";
        cin >> linhaBusca;
        if(linhaBusca > qtdLinhasTotal){
            cout << "Linha solicitada inexistente! Tente novamente!" << endl;
        }else{
            arquivoIndex.clear();
            arquivoIndex.seekg(0);
            while(getline(arquivoIndex, linha)){
                qtdLinha++;
                if(qtdLinha == linhaBusca){
                    break;
                }
            }
            try{
                arquivoBaseBusca.seekg(stoi(linha));
            }catch(...){
                cout << "Programa encerrado com falha na conversao!" << endl;
                return 0;
            }
            getline(arquivoBaseBusca, conteudoLinha);
            cout << conteudoLinha << endl;
        }
    }
}

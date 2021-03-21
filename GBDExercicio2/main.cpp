#include <bits/stdc++.h>
using namespace std;

void limpa(){
    setbuf(stdin, NULL);
}

//Tamanho da estrutura: 113 bytes
struct item{
    int cep;
    char uf[3];
    char cidade[39];
    char logradouro[67];
};

char *padronizatamanhocampos(char *texto, int tamanho){
    int cont=0;
    for(cont=0;cont<tamanho-1;cont++){
        if(texto[cont]=='\0'){
           texto[cont]=' ';
           texto[cont+1]='\0';
        }
    }
    return texto;
}

int main()
{
    FILE *arquivoEntrada = fopen("cep3.txt", "r");
    FILE *arquivoSaida = fopen("cep2.txt", "w");

    string inputStringFile;
    string breakString = "\t";
    string substring;
    struct item item;
    long long lSize;
    int qtdLinhas = 0;
    char cepescrita[8];

    char c;
    string teste;
    while(1){
        while(fread(&c, sizeof(char), 1, arquivoEntrada) == 1 && c != '\n'){
            teste.push_back(c);
        };
        string cep, uf, cidade, logradouro;
        cep = teste.substr(0, teste.find("\t"));
        try{
            item.cep = stoi(cep);
        }catch(...){
            cout << "Foram lidas " << qtdLinhas << " linhas" << endl;
            return 0;
        }
        teste.erase(0, teste.find("\t")+1);
        uf = teste.substr(0, teste.find("\t"));
        strcpy(item.uf, uf.c_str());
        teste.erase(0, teste.find("\t")+1);
        cidade = teste.substr(0, teste.find("\t"));
        strcpy(item.cidade, cidade.c_str());
        teste.erase(0, teste.find("\t")+1);
        logradouro = teste.substr(0, teste.find("\t"));
        strcpy(item.logradouro, logradouro.c_str());
        teste.erase(0, teste.find("\t")+1);
        qtdLinhas++;

// Linhas responsáveis por escrita no novo arquivo
        sprintf(cepescrita,"%d",item.cep); // transforma int em char;
        fwrite(padronizatamanhocampos(cepescrita,sizeof(cepescrita))           , sizeof(char) , sizeof(cepescrita) , arquivoSaida );
        fwrite(padronizatamanhocampos(item.uf,sizeof(item.uf))                 , sizeof(char) , sizeof(item.uf) , arquivoSaida );
        fwrite(padronizatamanhocampos(item.cidade,sizeof(item.cidade))         , sizeof(char) , sizeof(item.cidade) , arquivoSaida );
        fwrite(padronizatamanhocampos(item.logradouro,sizeof(item.logradouro)) , sizeof(char) , sizeof(item.logradouro) , arquivoSaida );
        fwrite("\n", sizeof(char) , 1 , arquivoSaida );
//        cout << item.cep << endl;
//        cout << item.uf[1] << endl;
//        cout << item.cidade << endl;
//        cout << item.logradouro << endl;
//        cout << endl;
        teste.erase(0, teste.size());
    }
    fclose(arquivoEntrada);
    fclose(arquivoSaida);
//    while(!feof(arquivoEntrada)){
//        fread(pedro, 1, lSize, arquivoEntrada);
//        cout << pedro << endl;
//    }

//    while(!feof(arquivoEntrada)){
//        fread(pedro, 1, lSize, arquivoEntrada);
//        int posicaoTabulacao;
//        string strTemp(pedro);
//        posicaoTabulacao = strTemp.find(breakString);           //Recebe a posicao da tabulacao
//        substring = strTemp.substr(0, posicaoTabulacao);        //Pega o cep
//        item.cep = stoi(substring);
//
//        strTemp.erase(0, posicaoTabulacao+1);                   //Exclui campo + '\t'
//        posicaoTabulacao = strTemp.find(breakString);           //Recebe a posicao da tabulacao
//        substring = strTemp.substr(0, posicaoTabulacao);        //Pega a UF
//        strcpy(item.uf, substring.c_str());
//
//        strTemp.erase(0, posicaoTabulacao+1);                   //Exclui campo + '\t'
//        posicaoTabulacao = strTemp.find(breakString);           //Recebe a posicao da tabulacao
//        substring = strTemp.substr(0, posicaoTabulacao);        //Pega a UF
//        strcpy(item.cidade, substring.c_str());
//
//        strTemp.erase(0, posicaoTabulacao+1);                   //Exclui campo + '\t'
//        posicaoTabulacao = strTemp.find(breakString);           //Recebe a posicao da tabulacao
//        substring = strTemp.substr(0, posicaoTabulacao);        //Pega a UF
//
//        cout << item.cep << endl;
//        cout << item.uf << endl;
//        cout << item.cidade << endl;
//        cout << item.logradouro << endl;
//
//        fwrite(item.uf, 1, sizeof(item.uf), arquivoEntrada);
//
////        strTemp.erase(0, posicaoTabulacao+1);                   //Exclui campo + '\t'
////        inputStringFile.insert(0, substring);
////        cout << inputStringFile << endl;
////        arquivoSaida << inputStringFile << endl;                    //Escrita da string no arquivo de saida
////        inputStringFile = "";
//    }
    //Fecha arquivos de entrada e sa�da
//    arquivoSaida.close();
//    cout << "Arquivo 1 encerrado com sucesso" << endl;
//    arquivoEntrada.close();
//    cout << "Arquivo 2 encerrado com sucesso" << endl;

//    ifstream arquivoEntrada1("cep2.txt");                           //Abre arquivo para leitura
//    int opcao, qtdResultados, qtdLinhas;
//    string termoBusca, resultado;
//    while(1){
//        cout << "1 - Busca por Rua\n2 - Busca por Cidade\n3 - Busca por UF\n4 - Busca por CEP\n5 - Sair" << endl;
//        cout << "Digite uma opcao: ";
//        scanf("%d", &opcao);
//        if(opcao == 5){                                             //Opcao para encerra aplicacao
//            arquivoEntrada1.close();                                //Encerra arquivo de leitura
//            cout << "Programa finalizado" << endl;
//            break;
//        }
//        cout << "Qual termo deseja buscar: ";
//        limpa();                                                    //Limpa o buffer do teclado para a leitura da string de busca
//        getline (cin, termoBusca);
//        cout << termoBusca << endl;
//        limpa();                                                    //Limpa o buffer do teclado para a leitura da string de busca
//
//        if(opcao == 1){                                             //Busca por rua
//            qtdResultados = 0;                                      //Variavel para mostrar a quantidade de resultados encontrados
//            arquivoEntrada1.clear();                                //Limpa o estado do ifstream antes de chamar a proxima instrucao para leitura do arquivo
//            arquivoEntrada1.seekg(0);                               //Posiciona o cursor na primeira linha e primeiro caractere do arquivo
//            qtdLinhas = 0;                                          //Variavel para mostrar a quatidade de linhas lidas no arquivoEntrada1
//            while(getline (arquivoEntrada1, resultado)){
//                qtdLinhas++;
//                strTemp = resultado.substr(0, resultado.find("|"));
//                if(strTemp.find(termoBusca, 0) != string::npos){
//                    cout << resultado << endl;
//                    qtdResultados++;
//                }
//            }
//        }else if(opcao == 2){                                       //Busca por cidade
//            qtdResultados = 0;                                      //Variavel para mostrar a quantidade de resultados encontrados
//            arquivoEntrada1.clear();                                //Limpa o estado do ifstream antes de chamar a proxima instrucao para leitura do arquivo
//            arquivoEntrada1.seekg(0);                               //Posiciona o cursor na primeira linha e primeiro caractere do arquivo
//            qtdLinhas = 0;                                          //Variavel para mostrar a quatidade de linhas lidas no arquivoEntrada1
//            while(getline (arquivoEntrada1, resultado)){
//                qtdLinhas++;
//                strTemp = resultado.substr(resultado.find("|")+1, resultado.size());
//                if(strTemp.find(termoBusca, 0) != string::npos){
//                    cout << resultado << endl;
//                    qtdResultados++;
//                }
//            }
//        }else if(opcao == 3){                                       //Busca por UF
//            qtdResultados = 0;                                      //Variavel para mostrar a quantidade de resultados encontrados
//            arquivoEntrada1.clear();                                //Limpa o estado do ifstream antes de chamar a proxima instrucao para leitura do arquivo
//            arquivoEntrada1.seekg(0);                               //Posiciona o cursor na primeira linha e primeiro caractere do arquivo
//            qtdLinhas = 0;                                          //Variavel para mostrar a quatidade de linhas lidas no arquivoEntrada1
//            while(getline (arquivoEntrada1, resultado)){
//                qtdLinhas++;
//                strTemp = resultado.substr(resultado.find("|")+1, resultado.size());
//                strTemp = strTemp.substr(strTemp.find("|")+1, strTemp.size());
//                if(strTemp.find(termoBusca, 0) != string::npos){
//                    cout << resultado << endl;
//                    qtdResultados++;
//                }
//            }
//        }else if(opcao == 4){                                       //Busca por CEP
//            qtdResultados = 0;                                      //Variavel para mostrar a quantidade de resultados encontrados
//            arquivoEntrada1.clear();                                //Limpa o estado do ifstream antes de chamar a proxima instrucao para leitura do arquivo
//            arquivoEntrada1.seekg(0);                               //Posiciona o cursor na primeira linha e primeiro caractere do arquivo
//            qtdLinhas = 0;                                          //Variavel para mostrar a quatidade de linhas lidas no arquivoEntrada1
//            while(getline (arquivoEntrada1, resultado)){
//                qtdLinhas++;
//                strTemp = resultado.substr(resultado.find("|")+1, resultado.size());
//                strTemp = strTemp.substr(strTemp.find("|")+1, strTemp.size());
//                strTemp = strTemp.substr(strTemp.find("|")+1, strTemp.size());
//                if(strTemp.find(termoBusca, 0) != string::npos){
//                    cout << resultado << endl;
//                    qtdResultados++;
//                }
//            }
//        }
//
//        cout << "Foram lidas " << qtdLinhas << " linhas" << endl;
//        cout << "Foram encontrados " << qtdResultados << " resultados" << endl;
//    }
}

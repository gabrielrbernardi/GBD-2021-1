#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream arquivoEntrada("cep.txt");
    ofstream arquivoSaida("cep2.txt");

    string strTemp, inputStringFile;
    string breakString = "\t";
    string substring;
    int pos = 0;
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
}

#include <bits/stdc++.h>
#include <ctype.h>
/********
Integrantes do grupo
Bruno Oliveira Sinhoroto - 11821BCC044
Gabriel Ribeiro Bernardi - 11821BCC036
Guilherme Soares Correa  - 11821BCC026
*********/
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
        if(texto[cont]=='\0'){ // verifica se chegou no final do arquivo
           texto[cont]=' ';    // adiciona espaço até padronizar o tamanho da struct.
           texto[cont+1]='\0'; // coloca o final do arquivo manualmente para os dados não se perderem.
        }
    }
    return texto;
}

char *semespaco(char *texto, int tamanho){
    int cont=0, cont2=0, posfin=0;
    //percorro para verificar a ultima ocorrencia de caractere, ignorando espços
    for(cont=0;cont<tamanho-1;cont++){
        if ((texto[cont]!='\0')&&(!(texto[cont] == ' ' || texto[cont] == '\t' || texto[cont] == '\r' || texto[cont] == '\n' || texto[cont] == '\x0b')))
            posfin = cont;
    }
    // criando nova variável sem os espaços.
    texto[posfin+1] = '\0';
    return texto;
}

// Compara manualmente o texto até o '\0' (final do char)
int comaparaChar(char *texto1, const char *texto2){
    int cont=0;
    cout<< texto1;
    while (texto1[cont]!='\0'){
        cout << texto1[cont] << texto2[cont] << endl;
        if (texto1[cont]!=texto2[cont])
            return 0;
        cont++;
    }
    return 1;
}

int separaStringDados(string dados, struct item *item, int posCep, int posUf, int posCid, int posLog){
    string cep, uf, cidade, logradouro;
    try{
        item->cep = stoi(dados.substr(0, ((posCep == 0) ? dados.find("\t") : posCep)));
    }catch(...){
        return 1;
    }
    dados.erase(0, ((posCep == 0) ? dados.find("\t")+1 : posCep));
    uf = dados.substr(0, ((posUf == 0) ? dados.find("\t") : posUf));
    strcpy(item->uf, uf.c_str());
    dados.erase(0, ((posUf == 0) ? dados.find("\t")+1 : posUf));
    cidade = dados.substr(0, ((posCid == 0) ? dados.find("\t") : posCid));
    strcpy(item->cidade, cidade.c_str());
    dados.erase(0, ((posCid == 0) ? dados.find("\t")+1 : posCid));
    logradouro = dados.substr(0, ((posLog == 0) ? dados.find("\t") : posCid));
    strcpy(item->logradouro, logradouro.c_str());
    dados.erase(0, ((posLog == 0) ? dados.find("\t")+1 : posLog));
    return(0);
}

void pesquisa(FILE *arquivoSaida, int opPes, string descPes)
{   int numEnc=0;
    char cepChar[8], leitura;
    struct item percorre;
    string dadosP;
    while(1){
        while(fread(&leitura, sizeof(char), 1, arquivoSaida) == 1 && leitura != '\n'){
            dadosP.push_back(leitura);
        }
        if (separaStringDados(dadosP, &percorre, 8, 3, 39, 67)){
           break;}
        sprintf(cepChar,"%d",percorre.cep); // transforma int em char;
        if (opPes==1){
            if (semespaco(cepChar, sizeof(cepChar)) == descPes)
                {numEnc++;}}
        else if (opPes==2){
            if (semespaco(percorre.cidade,sizeof(percorre.cidade)) == descPes)
                {numEnc++;}
        }
        else if (opPes==3){
            if (semespaco(percorre.logradouro,sizeof(percorre.logradouro)) == descPes)
                {numEnc++;}
        }
        else if (opPes==4){
            if (semespaco(percorre.uf,sizeof(percorre.uf)) == descPes)
                {numEnc++;}
        }
        dadosP.erase(0, dadosP.size());
    }
    cout<< "Registros encontrados na pesquisa: " << numEnc << endl;
}

int main()
{
    string inputStringFile;
    string breakString = "\t";
    string substring;
    struct item item;
    long long lSize;
    int qtdLinhas = 0, opcao, cont=0;
    char cepescrita[8];
    string termoBusca;

    char c;
    string dados;
    // escrita no novo arquivo
    cout << "Trabalho, 1 - topico 1, 2 - topico 2, 3 - topico 3 "<<endl;
    scanf("%d", &opcao);

    if (opcao==1){
        FILE *arquivoEntrada = fopen("cep3.txt", "r");
        FILE *arquivoSaida = fopen("cep2.bin", "wb");
        while(1){
            while(fread(&c, sizeof(char), 1, arquivoEntrada) == 1 && c != '\n'){
                dados.push_back(c);
            };
            if (separaStringDados(dados, &item, 0, 0, 0, 0)){
                cout << "Foram lidas " << qtdLinhas << " linhas" << endl;
                fclose(arquivoEntrada);
                fclose(arquivoSaida);
               return 0;}
            qtdLinhas++;
            sprintf(cepescrita,"%d",item.cep); // transforma int em char;
            fwrite(padronizatamanhocampos(cepescrita,sizeof(cepescrita))           , sizeof(char) , sizeof(cepescrita) , arquivoSaida );
            fwrite(padronizatamanhocampos(item.uf,sizeof(item.uf))                 , sizeof(char) , sizeof(item.uf) , arquivoSaida );
            fwrite(padronizatamanhocampos(item.cidade,sizeof(item.cidade))         , sizeof(char) , sizeof(item.cidade) , arquivoSaida );
            fwrite(padronizatamanhocampos(item.logradouro,sizeof(item.logradouro)) , sizeof(char) , sizeof(item.logradouro) , arquivoSaida );
            fwrite("\n", sizeof(char) , 1 , arquivoSaida );
            dados.erase(0, dados.size());
        }
        fclose(arquivoEntrada);
        fclose(arquivoSaida);}
    else if (opcao==2){
        // busca sequencial no arquivo criado
        FILE *arquivoSaida = fopen("cep2.bin", "r");
        while(1){
            cout << "1 - Busca por CEP\n2 - Busca por Cidade\n3 - Busca por Rua\n4 - Busca por UF\n5 - Sair" << endl;
            cout << "Digite uma opcao: ";
            scanf("%d", &opcao);
            if(opcao == 5){                                             //Opcao para encerra aplicacao
                break;
            }
            cout << "Qual termo deseja buscar: ";
            limpa();                                                    //Limpa o buffer do teclado para a leitura da string de busca
            getline (cin, termoBusca);
            cout << termoBusca << endl;
            limpa();

            pesquisa(arquivoSaida, opcao, termoBusca);
            rewind(arquivoSaida);
            }
        fclose(arquivoSaida);
        }else if (opcao==3){
            FILE *arquivoSaida = fopen("cep2.bin", "r");
            // busca por linha
            cout << "Digite a linha a ser buscada: ";
            scanf("%d", &opcao);
            while(fread(&c, sizeof(char), 1, arquivoSaida) == 1 && c != '\n'){
                dados.push_back(c);
            };
            cout<<sizeof(dados)<<endl;
            if (separaStringDados(dados, &item, 8, 3, 39, 67)){
                cout << "Foram lidas " << qtdLinhas << " linhas" << endl;
                return 0;}
            cout<<"Cep:    "<<item.cep <<endl;
            cout<<"Cidade: "<<item.cidade<<endl;
            cout<<"UF:     "<<item.uf <<endl;
            cout<<"Rua:    "<<item.logradouro<<endl;
            fclose(arquivoSaida);
          }
}

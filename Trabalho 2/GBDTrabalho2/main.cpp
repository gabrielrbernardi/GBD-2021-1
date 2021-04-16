/*
 * File:   main.cpp
 * Author: seunome
 */

#include <bits/stdc++.h>

using namespace std;

class MeuArquivo {
public:
    struct cabecalho { int quantidade; int disponivel = -1; } cabecalho;
    struct registro { int quantidade; int disponivel; } registro;
    typedef struct removeRegistro { int tamanho; int prox; } removeRegistro;

    // construtor: abre arquivo. Essa aplicacao deveria ler o arquivo se existente ou criar um novo.
    // Entretando recriaremos o arquivo a cada execucao ("w+").
    MeuArquivo() {
        fd = fopen("dados.dat","w+");
        fwrite(&cabecalho, sizeof(cabecalho), 1, fd);
        fflush(fd);
    }

    // Destrutor: fecha arquivo
    ~MeuArquivo() {
        fclose(fd);
    }

    // Insere uma nova palavra, consulta se h� espaco dispon�vel ou se deve inserir no final
    void inserePalavra(char *palavra) {
        this->substituiBarraNporBarraZero(palavra); // funcao auxiliar substitui terminador por \0

        char *str;
        if(strlen(palavra) + 1 < 8) {
            str = (char*) malloc(8);  //Alocando tamanho da palavra a ser inserida
            strcpy(str, palavra);     //Copia valor string palavra para str
        }else{
            str = palavra;
        }
        palavra = str;

        if(inserePalavra1(palavra) == 0) {
            fseek(fd, 0, SEEK_END);

            //Insere palavra ao final do arquivo caso nao seja possivel insercao no decorrer do dicionario
            int offset = ftell(fd);
            int tamanhoPalavra = strlen(palavra);
            int tamanho = max(int(sizeof(removeRegistro) - sizeof(int)), tamanhoPalavra + 1);

            if(fwrite(&tamanho, sizeof(int), 1, fd) != 1) {
                cout << "Nao foi possivel escrever o tamanho da palavra no final." << endl;
            }
            if(fwrite(palavra, sizeof(char), tamanho, fd) != tamanho) {
                cout << "Nao foi possivel escrever a palavra no final." << endl;
            }
            fflush(fd);

//            printf("Palavra inserida com sucesso.\n");
        }
        atualizaCabecalho(1);
    }

    int inserePalavra1(char *palavra){
        int tamanhoPalavra = strlen(palavra)+1; // considerando \0
        int desloc = cabecalho.disponivel, anterior = 0;
        fseek(fd, 0, SEEK_SET);

        while(desloc != -1){
            cout << "Desloc: " << desloc << endl;
            fseek(fd, desloc - ftell(fd), SEEK_CUR);

            removeRegistro remRegistro;
            fread(&remRegistro, sizeof(removeRegistro), 1, fd);

            if(remRegistro.tamanho >= tamanhoPalavra){
                //volta ponteiro do arquivo para o inicio do registro, desconsiderando o int do tamanho do registro
                fseek(fd, -(sizeof(removeRegistro) - sizeof(int)), SEEK_CUR);
                if(fwrite(palavra, sizeof(char), tamanhoPalavra, fd) != tamanhoPalavra) {
                    cout << "Nao foi possivel escrever a palavra: " << palavra << endl;
                }
                fflush(fd);
                proximoOffset(anterior, remRegistro.prox);
                break;
            }
            anterior = desloc;
            desloc = remRegistro.prox;
        }
        if(desloc != -1){
            cout << "A palavra foi inserida!" << endl;
            return 1;
        }
        return 0;
    }

    void proximoOffset(int desloc, int proxDesloc) {
        if(desloc != 0) {
            removeRegistro tempStruct;

            fseek(fd, desloc, SEEK_SET);
            fread(&tempStruct, sizeof(removeRegistro), 1, fd);

            tempStruct.prox = proxDesloc;

            fseek(fd, -sizeof(removeRegistro), SEEK_CUR);
            if(fwrite(&tempStruct, sizeof(removeRegistro), 1, fd) != 1) {
                printf("Problema ao configurar o no anterior.\n");
            }
            fflush(fd);
        }else{
            cabecalho.disponivel = proxDesloc;
        }
    }

    void atualizaCabecalho(int delta) {
        cabecalho.quantidade += delta;
    }

    // Marca registro como removido, atualiza lista de dispon�veis, incluindo o cabecalho
    void removePalavra(int offset) {
        fseek(fd, 0, SEEK_END);
        int tamanhoArquivo = ftell(fd);
        if(!cabecalho.quantidade || tamanhoArquivo <= offset){
            cout << "Nao foi possivel remover a palavra." << endl;
            return; //Para a execucao da funcao
        }else{
            removeRegistro remRegistro;
            fseek(fd, offset, SEEK_SET);
            fread(&remRegistro.tamanho, sizeof(int), 1, fd);
            remRegistro.prox = cabecalho.disponivel;
            fseek(fd, offset - ftell(fd), SEEK_CUR);

            if(fwrite(&remRegistro, sizeof(removeRegistro), 1, fd) != 1) {
                cout << "Nao foi possivel remover." << endl;
            }
            fflush(fd);
            cabecalho.disponivel = offset;
            atualizaCabecalho(-1);
        }

    }

    // BuscaPalavra: retorno � o offset para o registro
    // Nao deve considerar registro removido
    int buscaPalavra(char *palavra) {
        this->substituiBarraNporBarraZero(palavra); // funcao auxiliar substitui terminador por \0

        char str[75];
        int posicao = sizeof(cabecalho);

        fseek(fd, 0, SEEK_END);
        int finalArquivo = ftell(fd);

        fseek(fd, posicao, SEEK_SET);

        while(posicao < finalArquivo) {
            int tamanhoPalavra;
            fread(&tamanhoPalavra, sizeof(int), 1, fd);
            fread(str, sizeof(char), tamanhoPalavra, fd);
            this -> substituiBarraNporBarraZero(str);

            if(str[0] == '*') {
                continue;       //Ignora a string encontrada por ser considerada vazia para a busca
            }else{
                if(!strcmp(str, palavra)) {     //Verifica se string string atual eh igual a string que deseja-se buscar
                    cout << "A palavra " << palavra << " foi encontrada" << endl;
                    return posicao;
                }
            }
            posicao = ftell(fd);
        }
        // retornar -1 caso nao encontrar
        return -1;
    }

private:
    // descritor do arquivo � privado, apenas m�todos da classe podem acessa-lo
    FILE *fd;

    // funcao auxiliar substitui terminador por \0
    void substituiBarraNporBarraZero(char *str) {
        int tam = strlen(str); for (int i = 0; i < tam; i++) if (str[i] == '\n') str[i] = '\0';
    }
};

int main(int argc, char** argv) {
    // abrindo arquivo dicionario.txt
    FILE *f = fopen("dicionario.txt","rt");

    // se n�o abriu
    if (f == NULL) {
        printf("Erro ao abrir arquivo.\n\n");
        return 0;
    }

    char *palavra = new char[50];

    // criando arquivo de dados
    MeuArquivo *arquivo = new MeuArquivo();
    while (!feof(f)) {
        fgets(palavra,50,f);
        arquivo->inserePalavra(palavra);
    }

    // fechar arquivo dicionario.txt
    fclose(f);

    printf("Arquivo criado.\n\n");

    char opcao;
    do {
        printf("\n\n1-Insere\n2-Remove\n3-Busca\n4-Sair\nOpcao:");
        opcao = getchar();
        if (opcao == '1') {
            printf("Palavra: ");
            scanf("%s",palavra);
            arquivo->inserePalavra(palavra);
        }
        else if (opcao == '2') {
            printf("Palavra: ");
            scanf("%s",palavra);
            int offset = arquivo->buscaPalavra(palavra);
            if (offset >= 0) {
                arquivo->removePalavra(offset);
                printf("Removido.\n\n");
            }
        }
        else if (opcao == '3') {
            printf("Palavra: ");
            scanf("%s",palavra);
            int offset = arquivo->buscaPalavra(palavra);
            if (offset >= 0)
                printf("Encontrou %s na posicao %d\n\n",palavra,offset);
            else
                printf("Nao encontrou %s\n\n",palavra);
        }
        if (opcao != '4') opcao = getchar();
    } while (opcao != '4');

    printf("\n\nAte mais!\n\n");

    return (EXIT_SUCCESS);
}

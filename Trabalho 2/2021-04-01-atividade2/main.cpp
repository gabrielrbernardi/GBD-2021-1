/*
 * File:   main.cpp
 * Author: seunome
 */

//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
#include <bits/stdc++.h>

//using namespace std;

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

    // Insere uma nova palavra, consulta se há espaco disponível ou se deve inserir no final
    void inserePalavra(char *palavra) {
        this->substituiBarraNporBarraZero(palavra); // funcao auxiliar substitui terminador por \0

        char *str;
        if(strlen(palavra) + 1 < 8) {
            str = (char*) malloc(8);
            strcpy(str, palavra);
        }else{
            str = palavra;
        }
        palavra = str;

        if(inserePalavra1(palavra) == 0) {
            fseek(fd, 0, SEEK_END);

            //Insere palavra ao final do arquivo caso nao seja possivel insercao no decorrer do dicionario
            int offset = ftell(fd);
            int tamanhoPalavra = strlen(palavra);
            int tamanho = std::max(int(sizeof(removeRegistro) - sizeof(int)), tamanhoPalavra + 1);

            if(fwrite(&tamanho, sizeof(int), 1, fd) != 1) {
                printf("Nao foi possivel escrever o tamanho da palavra no final.\n");
            }
            if(fwrite(palavra, sizeof(char), tamanho, fd) != tamanho) {
                printf("Nao foi possivel escrever a palavra no final.\n");
            }
            fflush(fd);

            printf("Palavra inserida com sucesso.");
        }
        cabecalho.quantidade =+ 1;
    }

    int inserePalavra1(char *palavra){
        int tamanhoPalavra = strlen(palavra)+1; // considerando \0
        int desloc = cabecalho.disponivel, anterior = 0;
        fseek(fd, 0, SEEK_SET);

        while(desloc != -1){
            printf("Desloc: %d\n", desloc);
            fseek(fd, desloc-ftell(fd), SEEK_CUR);

            removeRegistro remRegistro;
            fread(&remRegistro, sizeof(removeRegistro), 1, fd);

            if(remRegistro.tamanho >= tamanhoPalavra){
                //volta ponteiro do arquivo para o inicio do registro, desconsiderando o int do tamanho do registro
                fseek(fd, -(sizeof(removeRegistro) - sizeof(int)), SEEK_CUR);
                if(fwrite(palavra, sizeof(char), tamanhoPalavra, fd) != tamanhoPalavra) {
                    printf("Nao foi possivel escrever a palavra: %s\n", palavra);
                }
                fflush(fd);
                proximoOffset(anterior, remRegistro.prox);
                break;
            }
            anterior = desloc;
            desloc = remRegistro.prox;
        }
        if(desloc != -1){
            printf("A palavra foi inserida!");
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

    // Marca registro como removido, atualiza lista de disponíveis, incluindo o cabecalho
    void removePalavra(int offset) {
        // implementar aqui
    }

    // BuscaPalavra: retorno é o offset para o registro
    // Nao deve considerar registro removido
    int buscaPalavra(char *palavra) {
        this->substituiBarraNporBarraZero(palavra); // funcao auxiliar substitui terminador por \0

        // implementar aqui

        // retornar -1 caso nao encontrar
        return -1;
    }

private:
    // descritor do arquivo é privado, apenas métodos da classe podem acessa-lo
    FILE *fd;

    // funcao auxiliar substitui terminador por \0
    void substituiBarraNporBarraZero(char *str) {
        int tam = strlen(str); for (int i = 0; i < tam; i++) if (str[i] == '\n') str[i] = '\0';
    }
};

int main(int argc, char** argv) {
    // abrindo arquivo dicionario.txt
    FILE *f = fopen("dicionario.txt","rt");

    // se não abriu
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
                printf("Encontrou %s na posição %d\n\n",palavra,offset);
            else
                printf("Não encontrou %s\n\n",palavra);
        }
        if (opcao != '4') opcao = getchar();
    } while (opcao != '4');

    printf("\n\nAte mais!\n\n");

    return (EXIT_SUCCESS);
}

/*
 * File:   main.cpp
 * Author: seunome
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

#define MAX_WORD_LENGTH 50

class MeuArquivo {
public:
    struct cabecalho { int quantidade = 0; int disponivel = -1; } cabecalho;
    typedef struct registroRemovido {
        int tamanho;
        char ast = '*';
        int prox;
    }RegistroRemovido;

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
        printf("\n========= Insere Palavra =========\n");
        this->substituiBarraNporBarraZero(palavra); // funcao auxiliar substitui terminador por \0
        palavra = arrumaTamanhoDaPalavra(palavra);

        if(!insereNaLista(palavra)) {
            insereNoFinal(palavra);
        }
        atualizaCabecalho(1);
    }

    // Marca registro como removido, atualiza lista de disponíveis, incluindo o cabecalho
    void removePalavra(int offset) {
        printf("remove palavra no offset %d\n", offset);
        if(!cabecalho.quantidade || tamanhoDoArquivo() <= offset) {
            printf("Remocao invalida!\n");
            return;
        }
        RegistroRemovido r;
        fseek(fd, offset, SEEK_SET);

        // le o tamanho do registro naquele offset especificado
        fread(&(r.tamanho), sizeof(int), 1, fd);
        // esse registro sera o primeiro da lista, logo,
        // seu prox vai ser a cabeca da lista no momento anterior
        r.prox = cabecalho.disponivel;
        // reseta o ponteiro do arquivo pro offset especificado
        fseek(fd, offset-ftell(fd), SEEK_CUR);

        printf("r = {tam = %d, ast = %c, prox = %d}\n", r.tamanho, r.ast, r.prox);
        printf("write struct removida no byte: %d\n", ftell(fd));
        if(fwrite(&r, sizeof(RegistroRemovido), 1, fd) != 1) {
            printf("write da struct removida falhou!\n");
        }
        fflush(fd);

        // faz esse registro que acabou de ser removido virar a cabeca da lista
        cabecalho.disponivel = offset;
        atualizaCabecalho(-1);
    }

    // BuscaPalavra: retorno é o offset para o registro
    // Nao deve considerar registro removido
    int buscaPalavra(char *palavra) {
        this->substituiBarraNporBarraZero(palavra); // funcao auxiliar substitui terminador por \0

        char str[MAX_WORD_LENGTH];
        int pos = sizeof(cabecalho);
        int endFile = tamanhoDoArquivo();

        printf("\n===================== Busca Palavra =====================\n");
        printf("endFile = %d\n", endFile);
        fseek(fd, pos, SEEK_SET);
        for(; pos < endFile; pos = ftell(fd)) {
            int wordsize;
            fread(&wordsize, sizeof(int), 1, fd);
            fread(str, sizeof(char), wordsize, fd);
            this->substituiBarraNporBarraZero(str);

            printf("passei pela palavra: %s, byte = %d, wordsize = %d, ftell = %lld\n", str, pos, wordsize, ftell(fd));

            if(str[0] == '*') {
                continue;
            }
            if(!strcmp(str, palavra)) {
                printf("->>> Palavra buscada: <%s>, encontrada na pos = %d\n", palavra, pos);
                return pos;
            }
        }

        return -1;
    }

private:
    // descritor do arquivo é privado, apenas métodos da classe podem acessa-lo
    FILE *fd;

    int tamanhoDoArquivo() {
        fseek(fd, 0, SEEK_END);
        return ftell(fd);
    }

    bool insereNaLista(char *palavra) {
        int wordLen = strlen(palavra)+1; // \0
        int offset = cabecalho.disponivel, previous=0;
        fseek(fd, 0, SEEK_SET);
        while(offset != -1) {
            printf("offset = %d\n", offset);
            // coloca o arquivo na posicao "offset"
            fseek(fd, offset-ftell(fd), SEEK_CUR);

            RegistroRemovido r;

            // le um no da lista
            fread(&r, sizeof(RegistroRemovido), 1, fd);
            printf("r = {tam = %d, ast = %c, prox = %d}\n", r.tamanho, r.ast, r.prox);

            // encontrou um slot valido
            if(r.tamanho >= wordLen) {
                // volta pro inicio da palavra no slot, apos o int do tamanho
                fseek(fd, -(sizeof(RegistroRemovido) - sizeof(int)), SEEK_CUR);

                // escreve a palavra no slot
                if(fwrite(palavra, sizeof(char), wordLen, fd) != wordLen) {
                    printf("Problema ao escrever a palavra\n");
                }
                fflush(fd);

                // atualiza ponteiro do anterior na lista de slots vagos
                atualizaProximoNaLista(previous, r.prox);
                break;
            }
            previous = offset;
            offset = r.prox;
        }
        if(offset != -1) {
            printf("Palavra <%s> inserida na lista com sucesso! pos = %d\n", palavra, offset);
            return true;
        }
        return false;
    }

    void insereNoFinal(char *palavra) {
        fseek(fd, 0, SEEK_END);
        int offset = ftell(fd);
        int tamPalavra = strlen(palavra);
        int len = max(int(sizeof(RegistroRemovido) - sizeof(int)), tamPalavra + 1);
        printf("Insere %s no final, byte %d, len = %d\n", palavra, ftell(fd), len);

        if(fwrite(&len, sizeof(int), 1, fd) != 1) {
            printf("problema ao escrever tamanho da palavra ao final do arquivo\n");
        }
        if(fwrite(palavra, sizeof(char), len, fd)!=len) {
            printf("problema ao escrever a palavra ao final do arquivo\n");
        }
        fflush(fd);

        printf("Palavra <%s> inserida no fim do arquivo com sucesso! pos = %d\n", palavra, offset);
    }

    // garante que toda palavra inserida tem pelo menos 8 bytes (contando com o \0)
    char* arrumaTamanhoDaPalavra(char* palavra) {
        char *str;
        if(strlen(palavra) + 1 < 8) {
            str = (char*) malloc(8);
            strcpy(str, palavra);
        }else{
            str = palavra;
        }
        return str;
    }

    void atualizaProximoNaLista(int offset, int proximoOffset) {
        if(offset != 0) {
            RegistroRemovido tmp;

            // vai pro offset a ser atualizado e le o no da lista
            fseek(fd, offset, SEEK_SET);
            fread(&tmp, sizeof(RegistroRemovido), 1, fd);

            // atualiza o ponteiro pro proximo
            tmp.prox = proximoOffset;

            // reescreve o no atualizado
            fseek(fd, -sizeof(RegistroRemovido), SEEK_CUR);
            if(fwrite(&tmp, sizeof(RegistroRemovido), 1, fd) != 1) {
                printf("Problema ao atualizar o no anterior na lista\n");
            }
            fflush(fd);
        }else{
            cabecalho.disponivel = proximoOffset;
        }
    }

    void atualizaCabecalho(int delta) {
        cabecalho.quantidade += delta;
    }

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
    while (fgets(palavra,50,f) != NULL) {
        puts(palavra);
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

#include <stdio.h>
#include <string.h>
#include "arquivo.h"
#include "analise.h"   /* para recalcular GC apos carregar */

/* ===================================================================
 * arquivo.c
 * Implementacao das funcoes de salvar/carregar arquivo.
 * =================================================================== */

/* ---------- TODO: implementar salvarArquivo ----------
 *
 * Passos:
 *   1) Abra o arquivo ARQUIVO_PADRAO com fopen no modo "w".
 *   2) Verifique se a abertura funcionou (NULL = erro).
 *   3) Para cada sequencia (loop de 0 ate total-1), use fprintf
 *      para gravar duas linhas:
 *          fprintf(arq, "%s\n", banco[i].nome);
 *          fprintf(arq, "%s\n", banco[i].dna);
 *   4) Feche o arquivo com fclose.
 *   5) Imprima mensagem informando quantas foram salvas.
 *
 * Atencao: nunca esqueca de testar se fopen retornou NULL,
 * porque acessar um ponteiro NULL trava o programa!
 * ------------------------------------------------------- */
/*a função recebe o vetor de sequencias e o total de elementos para salvar*/
void salvarArquivo(Sequencia *banco, int total) {
    FILE *file;
    /*abre o arquivo no modo escrita (sobrescreve se já existir)*/
    file = fopen(ARQUIVO_PADRAO, "w");
    /*verifica se conseguiu abrir o arquivo, caso não, exibe mensagem e encerra*/
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    /*o laço vai percorrer todas as sequencias do vetor*/
    for(int i = 0; i < total; i++) {
        /*escreve o nome da sequencia no arquivo*/
        fprintf(file, "%s\n", banco[i].nome);
        /*escreve a sequencia de dna no arquivo*/
        fprintf(file, "%s\n", banco[i].dna);
    }
    /*fecha o arquivo*/
    fclose(file);
    /*exibe mensagem de sucesso*/
    printf(">> Sequencias salvas com sucesso!\n");
}

/* ---------- TODO: implementar carregarArquivo ----------
 *
 * Passos:
 *   1) Abra o arquivo ARQUIVO_PADRAO com fopen no modo "r".
 *   2) Verifique se a abertura funcionou (se NULL, mensagem
 *      "Arquivo nao encontrado" e retorna).
 *   3) Zere o contador *total (sobrescreve o banco atual).
 *   4) Em um laco while, leia duas linhas por vez (uma com o nome
 *      e outra com o DNA) usando fgets:
 *
 *          while (*total < MAX_SEQ &&
 *                 fgets(banco[*total].nome, TAM_NOME, arq) != NULL &&
 *                 fgets(banco[*total].dna,  TAM_DNA,  arq) != NULL) {
 *              // remove o '\n' do final de cada linha
 *              banco[*total].nome[strcspn(banco[*total].nome, "\n")] = '\0';
 *              banco[*total].dna [strcspn(banco[*total].dna,  "\n")] = '\0';
 *              // atualiza tamanho e GC
 *              banco[*total].tamanho = strlen(banco[*total].dna);
 *              banco[*total].gc = calcularGC(banco[*total].dna,
 *                                            banco[*total].tamanho);
 *              (*total)++;
 *          }
 *
 *   5) Feche o arquivo.
 *   6) Imprima quantas sequencias foram carregadas.
 * ------------------------------------------------------- */
/* A função recebe um ponteiro para o vetor de sequencias 
e um ponteiro para o total de sequencias*/
void carregarArquivo(Sequencia *banco, int *total) {
    FILE *arq;
    /*abre o arquivo no modo leitura*/
    arq = fopen(ARQUIVO_PADRAO, "r");
    /*verifica se conseguiu abrir o arquivo, caso não, exibe mensagem e encerra*/
    if (arq == NULL) {
    printf("Arquivo não encontrado!\n");
    return;
    }
    /*zera o contador total de sequencias*/
    *total = 0;

    /*o laço vai percorrer enquanto não atingir o limite maximo de sequencias
    e conseguir ler o nome e o dna do arquivo*/
    while (*total < MAX_SEQ &&
    fgets(banco[*total].nome, TAM_NOME, arq) != NULL && fgets(banco[*total].dna, TAM_DNA, arq) != NULL) {
    /*remove o caractere de quebra de linha '\n' do final de cada string lida*/
    banco[*total].nome[strcspn(banco[*total].nome, "\n")] = '\0';
    banco[*total].dna [strcspn(banco[*total].dna, "\n")] = '\0';
    /*calcula o tamanho da sequencia de dna e o percentual de GC*/
    banco[*total].tamanho = strlen(banco[*total].dna);
    banco[*total].gc = calcularGC(banco[*total].dna, banco[*total].tamanho);
    /*incrementa o contador total de sequencias*/
    (*total)++;
    }
    /*fecha o arquivo*/
    fclose(arq);
    /*exibe quantas sequencias foram carregadas com sucesso*/
    printf("%d sequencia(s) carregada(s).\n", *total);
}

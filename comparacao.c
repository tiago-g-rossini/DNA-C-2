#include <stdio.h>
#include <string.h>
#include "comparacao.h"

/* ===================================================================
 * comparacao.c
 * Comparacao entre sequencias usando distancia de Hamming.
 * =================================================================== */

/* ---------- TODO: implementar distanciaHamming ----------
 *
 * A distancia de Hamming entre duas sequencias de MESMO TAMANHO e
 * o numero de posicoes onde elas diferem.
 *
 * Exemplo:
 *     s1 = "ATGCC"
 *     s2 = "ATCCC"
 *            x         (diferenca na posicao 3, base 0: indice 2)
 *     distancia = 1
 *
 * Passos:
 *   1) Verifique se s1->tamanho == s2->tamanho. Se nao, retorne -1.
 *   2) Inicialize um contador 'distancia = 0'.
 *   3) Percorra cada posicao i de 0 ate tamanho-1.
 *   4) Se s1->dna[i] != s2->dna[i], incremente 'distancia'.
 *   5) Retorne 'distancia'.
 *
 * Atencao: para acessar campos de uma struct via ponteiro, use o
 * operador seta:  s1->dna[i]  e equivalente a  (*s1).dna[i].
 * ------------------------------------------------------- */

 /* Os dois parametros da função são ponteiros, ou seja, duas sequencias de DNA*/
int distanciaHamming(Sequencia *s1, Sequencia *s2) {

/*verifica se o tamanho da sequencia 1 é igual ao da sequencia 2, caso não for, return -1*/
    if (s1->tamanho != s2->tamanho) {
        return -1;
    }
    /*zera o contador*/
    int distancia = 0;

    /*o laço vai percorrer os dois vetores posição por posição verificando se
    o conteúdo das posições são iguais*/
    for (int i = 0; i < s1->tamanho; i++) {
        if (s1->dna[i] != s2->dna[i]) {
            /*caso o conteúdo for diferente, realizaa soma +1 no contador*/
            distancia++;
        }
    }
    /*retorna a soma da distancia*/
    return distancia;
}

/* ---------- IMPLEMENTADO: menu de comparacao ---------- */
void menuCompararSequencias(Sequencia *banco, int total) {
    if (total < 2) {
        printf("\n>> E preciso ter pelo menos 2 sequencias cadastradas.\n");
        return;
    }

    char nome1[TAM_NOME];
    char nome2[TAM_NOME];

    printf("\nNome da PRIMEIRA sequencia: ");
    scanf(" %30[^\n]", nome1);

    printf("Nome da SEGUNDA sequencia: ");
    scanf(" %30[^\n]", nome2);

    /* Busca as duas sequencias no banco */
    int idx1 = -1, idx2 = -1;
    for (int i = 0; i < total; i++) {
        if (strcmp(banco[i].nome, nome1) == 0) idx1 = i;
        if (strcmp(banco[i].nome, nome2) == 0) idx2 = i;
    }

    if (idx1 == -1) {
        printf(">> Sequencia '%s' nao encontrada.\n", nome1);
        return;
    }
    if (idx2 == -1) {
        printf(">> Sequencia '%s' nao encontrada.\n", nome2);
        return;
    }

    /* Chama a funcao passando ponteiros */
    int dist = distanciaHamming(&banco[idx1], &banco[idx2]);

    if (dist == -1) {
        printf("\n>> Nao e possivel comparar: tamanhos diferentes ");
        printf("(%d vs %d).\n", banco[idx1].tamanho, banco[idx2].tamanho);
        return;
    }

    float similaridade = (float)(banco[idx1].tamanho - dist) /
                         banco[idx1].tamanho * 100.0;

    printf("\nComparando %s vs %s...\n", banco[idx1].nome, banco[idx2].nome);
    printf("Tamanho: %d bases\n", banco[idx1].tamanho);
    printf("Distancia de Hamming: %d\n", dist);
    printf("Similaridade: %.2f%%\n", similaridade);
}

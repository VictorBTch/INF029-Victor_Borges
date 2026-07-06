#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

// Estrutura interna para gerenciar as estruturas auxiliares (Apenas em Memória RAM)
typedef struct {
    int *dados;     // Vetor dinâmico
    int tamanho;    // Capacidade máxima
    int qtd;        // Quantidade de elementos inseridos
} EstruturaAuxiliar;

EstruturaAuxiliar vetorPrincipal[TAM];

// Função auxiliar de validação
int ehPosicaoValida(int posicao)
{
    if (posicao < 1 || posicao > 10)
        return POSICAO_INVALIDA;
    return SUCESSO;
}

// Algoritmo de ordenação simples (Bubble Sort)
void ordenarVetor(int vetor[], int tamanho) {
    int i, j, temp;
    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

/*
Objetivo: inicializa o programa limpando o vetor principal.
Removida completamente a persistência em arquivo para garantir um ambiente 100% limpo a cada execução.
*/
void inicializar()
{
    for (int i = 0; i < TAM; i++) {
        vetorPrincipal[i].dados = NULL;
        vetorPrincipal[i].tamanho = 0;
        vetorPrincipal[i].qtd = 0;
    }
}

int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;
        
    if (tamanho < 1)
        return TAMANHO_INVALIDO;
        
    int index = posicao - 1;
    if (vetorPrincipal[index].dados != NULL)
        return JA_TEM_ESTRUTURA_AUXILIAR;
        
    vetorPrincipal[index].dados = (int *)malloc(tamanho * sizeof(int));
    if (vetorPrincipal[index].dados == NULL)
        return SEM_ESPACO_DE_MEMORIA;
        
    vetorPrincipal[index].tamanho = tamanho;
    vetorPrincipal[index].qtd = 0;
    
    return SUCESSO;
}

int inserirNumeroEmEstrutura(int posicao, int valor)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;
        
    int index = posicao - 1;
    if (vetorPrincipal[index].dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
        
    if (vetorPrincipal[index].qtd >= vetorPrincipal[index].tamanho)
        return SEM_ESPACO;
        
    vetorPrincipal[index].dados[vetorPrincipal[index].qtd] = valor;
    vetorPrincipal[index].qtd++;
    
    return SUCESSO;
}

int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;
        
    int index = posicao - 1;
    if (vetorPrincipal[index].dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
        
    if (vetorPrincipal[index].qtd == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;
        
    vetorPrincipal[index].qtd--; // Remoção lógica eficiente
    return SUCESSO;
}

int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;
        
    int index = posicao - 1;
    if (vetorPrincipal[index].dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
        
    if (vetorPrincipal[index].qtd == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;
        
    int encontrado = -1;
    for (int i = 0; i < vetorPrincipal[index].qtd; i++) {
        if (vetorPrincipal[index].dados[i] == valor) {
            encontrado = i;
            break;
        }
    }
    
    if (encontrado == -1)
        return NUMERO_INEXISTENTE;
        
    // Desloca os elementos posteriores para manter a contiguidade
    for (int i = encontrado; i < vetorPrincipal[index].qtd - 1; i++) {
        vetorPrincipal[index].dados[i] = vetorPrincipal[index].dados[i + 1];
    }
    vetorPrincipal[index].qtd--;
    
    return SUCESSO;
}

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;
        
    int index = posicao - 1;
    if (vetorPrincipal[index].dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
        
    for (int i = 0; i < vetorPrincipal[index].qtd; i++) {
        vetorAux[i] = vetorPrincipal[index].dados[i];
    }
    
    return SUCESSO;
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);
    if (retorno == SUCESSO) {
        int index = posicao - 1;
        if (vetorPrincipal[index].qtd > 0) {
            ordenarVetor(vetorAux, vetorPrincipal[index].qtd);
        }
    }
    return retorno;
}

int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int totalElementos = 0;
    int k = 0;
    
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].dados != NULL) {
            totalElementos += vetorPrincipal[i].qtd;
            for (int j = 0; j < vetorPrincipal[i].qtd; j++) {
                vetorAux[k++] = vetorPrincipal[i].dados[j];
            }
        }
    }
    
    if (totalElementos == 0)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
        
    return SUCESSO;
}

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int totalElementos = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].dados != NULL) {
            totalElementos += vetorPrincipal[i].qtd;
        }
    }
    
    int retorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);
    if (retorno == SUCESSO) {
        ordenarVetor(vetorAux, totalElementos);
    }
    return retorno;
}

int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;
        
    int index = posicao - 1;
    if (vetorPrincipal[index].dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
        
    int tamanhoResultante = vetorPrincipal[index].tamanho + novoTamanho;
    if (tamanhoResultante < 1)
        return NOVO_TAMANHO_INVALIDO;
        
    // Ajusta a quantidade lógica de itens antes de diminuir o bloco via realloc
    if (vetorPrincipal[index].qtd > tamanhoResultante) {
        vetorPrincipal[index].qtd = tamanhoResultante;
    }
        
    int *novoBloco = (int *)realloc(vetorPrincipal[index].dados, tamanhoResultante * sizeof(int));
    if (novoBloco == NULL)
        return SEM_ESPACO_DE_MEMORIA;
        
    vetorPrincipal[index].dados = novoBloco;
    vetorPrincipal[index].tamanho = tamanhoResultante;
    
    return SUCESSO;
}

int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;
        
    int index = posicao - 1;
    if (vetorPrincipal[index].dados == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
        
    if (vetorPrincipal[index].qtd == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;
        
    return vetorPrincipal[index].qtd;
}

No *montarListaEncadeadaComCabecote()
{
    No *cabecote = (No *)malloc(sizeof(No));
    if (cabecote == NULL) return NULL;
    
    cabecote->conteudo = 0;
    cabecote->prox = NULL;
    
    No *atualLista = cabecote;
    int temDados = 0;
    
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].dados != NULL) {
            for (int j = 0; j < vetorPrincipal[i].qtd; j++) {
                No *novo = (No *)malloc(sizeof(No));
                
                // Evita vazamento de memória liberando nós anteriores se o malloc falhar no caminho
                if (novo == NULL) {
                    destruirListaEncadeadaComCabecote(&cabecote);
                    return NULL;
                }
                
                novo->conteudo = vetorPrincipal[i].dados[j];
                novo->prox = NULL;
                
                atualLista->prox = novo;
                atualLista = novo;
                temDados = 1;
            }
        }
    }
    
    if (!temDados) {
        free(cabecote);
        return NULL;
    }
    
    return cabecote;
}

void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    if (inicio == NULL) return;
    No *atual = inicio->prox; // Pula o nó de controle (cabeçote)
    int i = 0;
    while (atual != NULL) {
        vetorAux[i++] = atual->conteudo;
        atual = atual->prox;
    }
}

void destruirListaEncadeadaComCabecote(No **inicio)
{
    if (inicio == NULL || *inicio == NULL) return;
    No *atual = *inicio;
    while (atual != NULL) {
        No *aux = atual->prox;
        free(atual);
        atual = aux;
    }
    *inicio = NULL;
}

/*
Objetivo: Limpa toda a memória heap alocada ao encerrar o ciclo do programa.
Removido o bloco de gravação em arquivo para focar estritamente no escopo exigido.
*/
void finalizar()
{
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].dados != NULL) {
            free(vetorPrincipal[i].dados);
            vetorPrincipal[i].dados = NULL;
        }
        vetorPrincipal[i].tamanho = 0;
        vetorPrincipal[i].qtd = 0;
    }
}

void dobrar(int *x) {
    if (x) {
        *x = (*x) * 2;
    }
}
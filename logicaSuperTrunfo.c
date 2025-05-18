#include <stdio.h>
#include <string.h>

#define LIMITE_PONTOS 3

typedef struct {
    char estado;
    char codigo[4];
    char nome[50];
    unsigned long int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade;
    float pib_per_capita;
    float super_poder;
} Carta;

void limpar_tela() {
    system("cls || clear");
}

void calcular_atributos(Carta *c) {
    c->densidade = c->populacao / c->area;
    c->pib_per_capita = c->pib / c->populacao;
    c->super_poder = c->populacao + c->area + c->pib + c->pontos_turisticos + c->pib_per_capita + (1 / c->densidade);
}

void cadastrar_carta(Carta *c) {
    printf("----- Cadastro da Carta -----\n");
    printf("Digite o estado (letra): ");
    scanf(" %c", &c->estado);

    printf("Digite o codigo da carta (ex: A01): ");
    scanf("%3s", c->codigo);

    printf("Digite o nome da cidade: ");
    scanf(" %[^\n]", c->nome);

    printf("Digite a populacao (numero inteiro grande): ");
    scanf("%lu", &c->populacao);

    printf("Digite a area (em km2): ");
    scanf("%f", &c->area);

    printf("Digite o PIB (em bilhoes, ex: 1234.56): ");
    scanf("%f", &c->pib);

    printf("Digite o numero de pontos turisticos: ");
    scanf("%d", &c->pontos_turisticos);

    calcular_atributos(c);

    printf("\nCadastro realizado com sucesso para a cidade %s!\n\n", c->nome);
}

void exibir_carta(Carta c) {
    printf("=== Informacoes da Cidade %s ===\n", c.nome);
    printf("Estado: %c\n", c.estado);
    printf("Codigo da Carta: %s\n", c.codigo);
    printf("Populacao: %lu habitantes\n", c.populacao);
    printf("Area: %.2f km2\n", c.area);
    printf("PIB: %.2f bilhoes\n", c.pib);
    printf("Pontos Turisticos: %d\n", c.pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km2\n", c.densidade);
    printf("PIB per Capita: %.2f\n", c.pib_per_capita);
    printf("Super Poder: %.2f\n\n", c.super_poder);
}

int comparar_atributo(Carta c1, Carta c2, int atributo) {
    float val1, val2;

    switch(atributo) {
        case 1:
            if (c1.populacao > c2.populacao) return 1;
            else if (c1.populacao < c2.populacao) return 0;
            else return -1;
        case 2:
            if (c1.area > c2.area) return 1;
            else if (c1.area < c2.area) return 0;
            else return -1;
        case 3:
            if (c1.pib > c2.pib) return 1;
            else if (c1.pib < c2.pib) return 0;
            else return -1;
        case 4:
            if (c1.pontos_turisticos > c2.pontos_turisticos) return 1;
            else if (c1.pontos_turisticos < c2.pontos_turisticos) return 0;
            else return -1;
        case 5:
            if (c1.densidade < c2.densidade) return 1; // menor vence
            else if (c1.densidade > c2.densidade) return 0;
            else return -1;
        case 6:
            if (c1.pib_per_capita > c2.pib_per_capita) return 1;
            else if (c1.pib_per_capita < c2.pib_per_capita) return 0;
            else return -1;
        case 7:
            if (c1.super_poder > c2.super_poder) return 1;
            else if (c1.super_poder < c2.super_poder) return 0;
            else return -1;
        default:
            return -1;
    }
}

void exibir_resultado(int res, Carta c1, Carta c2, const char* nome_atributo) {
    printf(">>> Comparacao pelo atributo: %s\n", nome_atributo);
    if (res == 1) {
        printf("Vencedor: %s ??\n", c1.nome);
    } else if (res == 0) {
        printf("Vencedor: %s ??\n", c2.nome);
    } else {
        printf("Empate! ??\n");
    }
    printf("\n");
}

int menu_atributos() {
    int escolha;
    printf("Escolha o atributo para comparar:\n");
    printf("1 - Populacao\n");
    printf("2 - Area\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Turisticos\n");
    printf("5 - Densidade Populacional (menor vence)\n");
    printf("6 - PIB per Capita\n");
    printf("7 - Super Poder\n");
    printf("0 - Sair do jogo\n");
    printf("Sua opcao: ");
    scanf("%d", &escolha);
    return escolha;
}

int main() {
    Carta carta1, carta2;
    int escolha, res;
    int pontos1 = 0, pontos2 = 0;

    printf("Bem-vindo ao jogo Super Trunfo - Paises!\n\n");

    printf("Vamos cadastrar a primeira carta:\n");
    cadastrar_carta(&carta1);
    limpar_tela();

    printf("Agora vamos cadastrar a segunda carta:\n");
    cadastrar_carta(&carta2);
    limpar_tela();

    printf("Aqui estao as cartas cadastradas:\n\n");
    exibir_carta(carta1);
    exibir_carta(carta2);

    while(1) {
        escolha = menu_atributos();

        if (escolha == 0) {
            printf("\nObrigado por jogar! Encerrando o jogo.\n");
            break;
        }

        limpar_tela();

        res = comparar_atributo(carta1, carta2, escolha);

        switch(escolha) {
            case 1: exibir_resultado(res, carta1, carta2, "Populacao"); break;
            case 2: exibir_resultado(res, carta1, carta2, "Area"); break;
            case 3: exibir_resultado(res, carta1, carta2, "PIB"); break;
            case 4: exibir_resultado(res, carta1, carta2, "Pontos Turisticos"); break;
            case 5: exibir_resultado(res, carta1, carta2, "Densidade Populacional"); break;
            case 6: exibir_resultado(res, carta1, carta2, "PIB per Capita"); break;
            case 7: exibir_resultado(res, carta1, carta2, "Super Poder"); break;
            default:
                printf("Opcao invalida! Tente novamente.\n\n");
                continue;
        }

        if (res == 1) pontos1++;
        else if (res == 0) pontos2++;

        printf("Placar Atual:\n");
        printf("%s: %d ponto(s)\n", carta1.nome, pontos1);
        printf("%s: %d ponto(s)\n\n", carta2.nome, pontos2);

        if (pontos1 >= LIMITE_PONTOS || pontos2 >= LIMITE_PONTOS) {
            printf("O limite de %d pontos foi atingido!\n", LIMITE_PONTOS);
            break;
        }
    }

    printf("========== PLACAR FINAL ==========\n");
    printf("%s: %d ponto(s)\n", carta1.nome, pontos1);
    printf("%s: %d ponto(s)\n", carta2.nome, pontos2);

    if (pontos1 > pontos2) {
        printf("Parabens, %s! Voce e o vencedor do jogo! ??\n", carta1.nome);
    } else if (pontos2 > pontos1) {
        printf("Parabens, %s! Voce e o vencedor do jogo! ??\n", carta2.nome);
    } else {
        printf("O jogo terminou empatado. Que disputa equilibrada! ??\n");
    }

    return 0;
}

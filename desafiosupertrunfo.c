#include <stdio.h>
#include <stdlib.h>

// estrutura das Carta
typedef struct {
    char estado;
    char codigo[10];
    char nomeCidade[50];
    long int populacao;
    float area;
    float pib;
    long int pontosTuristicos;
    float densidade;
    float pibpercapita;
    float superPoder;
} Carta;

// valor inicial de variáveis
Carta clearVars() {
    Carta carta; // cria uma nova instância de Carta
    carta.estado = '\0';
    carta.codigo[0] = '\0';
    carta.nomeCidade[0] = '\0';
    carta.populacao = 0;
    carta.area = 0;
    carta.pib = 0;
    carta.pontosTuristicos = 0;
    carta.densidade = 0;
    carta.pibpercapita = 0;
    carta.superPoder = 0;
    return carta;
}

// Calculando a densidade populacional
float densiPopula(Carta carta) {
    if (carta.populacao == 0 || carta.area == 0) {
        return 0; // evitar que seja realizado o cálculo com zero
    }
    return ((float)carta.populacao * 1e6) / carta.area;
}

// Calculando o PIB per capita
float PIBpercapita(Carta carta) {
    if (carta.populacao == 0 || carta.pib == 0) {
        return 0; // evitar que seja realizado o cálculo com zero
    }
    return (carta.pib * 1e9) / ((float)carta.populacao * 1e6);
}

// Calculando o super poder
float calcularSuperPoder(Carta carta) {
    if (carta.populacao == 0 || carta.area == 0) {
        return 0; // evitar que seja realizado o cálculo com zero
    }
    float densidadeInvertida = carta.area / (float)carta.populacao;
    return carta.populacao + carta.area + carta.pib + carta.pibpercapita + densidadeInvertida + carta.pontosTuristicos;
}

// Gerando o código da cidad baseado no estado
void gerarCodCidades(char estado, char* codigo) {
    static int contadorCidades[4] = {0}; // contador de cidades por estado
    int indiceEstado = estado - 'A'; // índice do estado na tabela ASCII

    if (contadorCidades[indiceEstado] < 4) { // define o limite de 4 cidades por estado
        contadorCidades[indiceEstado]++; // acrescenta o contador de cidades

        sprintf(codigo, "%c%02d", estado, contadorCidades[indiceEstado]); // formata a string para o padrão do código ex: A01
    } else {
        printf("Erro: Estado %c já atingiu o limite de 4 cidades.\n", estado);
    }
}

//exibe Dados para o cadastro da carta
Carta cadastrarCarta() {
    Carta carta = clearVars(); // inicializa a estrutura
    printf("Digite o estado (1 caractere): ");
    scanf(" %c", &carta.estado);
    getchar(); // adicionado para consumir o caractere de newline
    
    printf("Digite o nome da cidade: ");
    fgets(carta.nomeCidade, 50, stdin); // fgets para contornar o problema do scanf com strings

    printf("Digite a população: ");
    char populacaoStr[10];
    fgets(populacaoStr, 10, stdin);
    carta.populacao = atol(populacaoStr);
    
    printf("Digite a área em km²: ");
    scanf("%f", &carta.area);
    
    printf("Digite o PIB: ");
    scanf("%f", &carta.pib);
    
    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &carta.pontosTuristicos);

    // Calcula densidade populacional e PIB per capita
    carta.densidade = densiPopula(carta);
    carta.pibpercapita = PIBpercapita(carta);
    // Calcula o super poder
    carta.superPoder = calcularSuperPoder(carta);

    return carta; // retorna a estrutura preenchida
}

// Função para imprimir os dados da carta cadastrada
void exibirCarta(Carta carta) {
    char codigo[10];
    gerarCodCidades(carta.estado, codigo); // chama a função para gerar o código único da carta
    printf("\n--- Dados da Carta ---\n");
    printf("Estado: %c\n", carta.estado);
    printf("Código da Carta: %s\n", codigo);
    printf("Nome da Cidade: %s", carta.nomeCidade);
    printf("População: %ld\n", carta.populacao);
    printf("Densidade populacional: %.2f pessoas/km²\n", carta.densidade);
    printf("Área: %.2f km²\n", carta.area);
    printf("PIB: %.2f bilhões de reais\n", carta.pib);
    printf("PIB per capita: %.2f reais\n", carta.pibpercapita);
    printf("Número de Pontos Turísticos: %d\n", carta.pontosTuristicos);
    printf("Super Poder: %.2f\n", carta.superPoder);
}

// Função para comparar duas cartas e determinar a vencedora
int compararCartas(Carta carta1, Carta carta2) {
    int resultado = 0; // Inicialmente assume que Carta 2 vence
    int pontosCarta1 = 0;
    int pontosCarta2 = 0;

    // Comparação de densidade populacional (menor valor é melhor)
    if (carta1.densidade < carta2.densidade) {
        pontosCarta1++;
    } else if (carta1.densidade > carta2.densidade) {
        pontosCarta2++;
    }
    //printf("Densidade populacional: Carta 1: %.2f | Carta 2: %.2f\n", carta1.densidade, carta2.densidade);

    // Comparação de PIB (maior valor é melhor)
    if (carta1.pib > carta2.pib) {
        pontosCarta1++;
    } else if (carta1.pib < carta2.pib) {
        pontosCarta2++;
    }
    //printf("PIB: Carta 1: %.2f | Carta 2: %.2f\n", carta1.pib, carta2.pib);

    // Comparação de PIB per capita (maior valor é melhor)
    if (carta1.pibpercapita > carta2.pibpercapita) {
        pontosCarta1++;
    } else if (carta1.pibpercapita < carta2.pibpercapita) {
        pontosCarta2++;
    }
    //printf("PIB per capita: Carta 1: %.2f | Carta 2: %.2f\n", carta1.pibpercapita, carta2.pibpercapita);

    // Comparação de área (maior valor é melhor)
    if (carta1.area > carta2.area) {
        pontosCarta1++;
    } else if (carta1.area < carta2.area) {
        pontosCarta2++;
    }
    //printf("Área: Carta 1: %.2f | Carta 2: %.2f\n", carta1.area, carta2.area);

    // Comparação de pontos turísticos (maior valor é melhor)
    if (carta1.pontosTuristicos > carta2.pontosTuristicos) {
        pontosCarta1++;
    } else if (carta1.pontosTuristicos < carta2.pontosTuristicos) {
        pontosCarta2++;
    }
    //printf("Número de Pontos Turísticos: Carta 1: %ld | Carta 2: %ld\n", carta1.pontosTuristicos, carta2.pontosTuristicos);

    // Comparação do super poder (maior valor é melhor)
    if (carta1.superPoder > carta2.superPoder) {
        pontosCarta1++;
    } else if (carta1.superPoder < carta2.superPoder) {
        pontosCarta2++;
    }
    //printf("Super Poder: Carta 1: %.2f | Carta 2: %.2f\n", carta1.superPoder, carta2.superPoder);

    // Determina a carta vencedora com base no total de pontos
    if (pontosCarta1 > pontosCarta2) {
        resultado = 1;
        printf("A Carta 1 é a vencedora!\n");
    } else if (pontosCarta1 < pontosCarta2) {
        resultado = 0;
        printf("A Carta 2 é a vencedora!\n");
    } else {
        printf("As duas cartas são equivalentes!\n");
    }

    return resultado;
}


int main() {
    Carta cartas[2];

    for (int cont = 0; cont < 2; cont++) {
        printf("\n--- Insira os dados da Carta %d ---\n", cont + 1);
        cartas[cont] = cadastrarCarta(); // recebe a carta cadastrada
        printf("\n--- Dados da Carta %d ---\n", cont + 1);
        exibirCarta(cartas[cont]);
    } 

    // Comparar as duas cartas e mostrara a vencedora
    compararCartas(cartas[0], cartas[1]);
    return 0;
}

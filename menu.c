#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define N 5

void novo_vetor(float [], int, float *);
void mostra(float [], int);
void ordena(float [], int, int);
void inverte(float [], int);
float *busca(float [], int, float, int *);
float soma(float [], int);
float argmax(float [], int);
void normaliza(float [], int);
float maiordif(float vetor[], int tam);

void novo_vetor(float vetor[], int tam, float *backup_vetor) {
	system("cls");
  printf("Menu de manipulação vetorial\n\nComo começar:\nDigite um número decimal e aperte Enter.\nEx: *.**\n\n");
	for(int v = 0; v < tam; v++) {
		printf("%dº número do vetor: ", v + 1);
		scanf("%f", &vetor[v]);
	}
	for(int v = 0; v < N; v++) {
		backup_vetor[v] = vetor[v];
	}
}

void mostra(float vetor[], int tam) {
	printf("Vetor:");
	for(int v = 0; v < tam; v++) {
		printf(" %.2f", vetor[v]);
	}
}

void ordena(float vetor[], int tam, int escolha) {
	int i, j;
	float aux;

	switch (escolha) {
		case 1:
			for(i = 0; i < tam-1; i++) {
				for(j = i+1; j < tam; j++) {
					if(vetor[i] > vetor[j]) {
						aux = vetor[i];
						vetor[i] = vetor[j];
						vetor[j] = aux;
					}
				}
			}
		break;

		case 2:
			for(i = 0; i < tam - 1; i++) {
				for(j = i+1; j < tam; j++) {
					if(vetor[i] < vetor[j]) {
						aux = vetor[i];
						vetor[i] = vetor[j];
						vetor[j] = aux;
					}
				}
			}
		break;
  }
}

void inverte(float vetor[], int tam) {
	int i, j = tam-1;
	float aux;
	
	for(i = 0; i < j; i++) {
		aux = vetor[i];
		vetor[i] = vetor[j];
		vetor[j] = aux;
		j--;
	}
}

float *busca(float vetor[], int tam, float valor, int *escolha) {
	int aux_resultado = 0;
	float *resultado = (float *)malloc(tam * sizeof(float));

	if (resultado == NULL) {
    printf("\nErro ao alocar memória.\n");
    exit(1);
  }

	for(int v = 0; v < tam; v++) {
		if(vetor[v] == valor) {
			resultado[aux_resultado] = v + 1;
			aux_resultado++;
		}
	}
	*escolha = aux_resultado;
	return resultado;
}

float soma(float vetor[], int tam) {
	float resultado = 0;

	for(int v = 0; v < tam; v++) {
		resultado += vetor[v];
	}
	return resultado;
}

float argmax(float vetor[], int tam) {
  float resultado = 0;

  for(int v = 0; v < tam; v++) {
    if(vetor[v] > resultado) {
      resultado = vetor[v];
    }
  }
  return resultado;
}

void normaliza(float vetor[], int tam) {
  float maior_valor = 0;

  for(int v = 0; v < tam; v++) {
    if(vetor[v] > maior_valor) {
      maior_valor = vetor[v];
    }
  }
  for(int n = 0; n < tam; n++) {
    vetor[n] = vetor[n] / maior_valor;
  }
}

float maiordif(float vetor[], int tam) {
  float resultado = 0;

  for(int v = 0; v < tam - 1; v++) { 
    if(vetor[v] - vetor[v+1] > resultado) {
      resultado = vetor[v] - vetor[v+1];
    }
  }
  return resultado;
}

int main() {
	int escolha, aux_escolha = 1;
	float vetor[N], backup_vetor[N], aux_escolha2;

  UINT CPAGE_UTF8 = 65001;
	UINT CPAGE_DEFAULT = GetConsoleOutputCP();
	SetConsoleOutputCP(CPAGE_UTF8);
	
  novo_vetor(vetor, N, backup_vetor);
  do{	
    system("cls");
    
    while(aux_escolha) {
      mostra(vetor, N);
      printf("\n\nO que deseja fazer?\n1- Ordenar em ordem crescente/decrescente\n2- Inverter a ordem do vetor\n3- Buscar a posição de um valor do vetor\n4- Realizar a soma dos valores do vetor\n5- Descobrir qual o maior valor do vetor\n6- Dividir todos os valores pelo maior valor\n7- Descobrir a maior diferença entre valores consecutivos\n8- Restaurar ordem inicial do vetor\n9- Reescrever vetor\n10- Fechar o app\n\nSua escolha: ");
      scanf("%d", &escolha);

      if(escolha == 10) {
        system("cls");
        exit(0);
      }
      if(escolha > 10 || escolha < 1) {
        system("cls");
        printf("Escolha inválida. Tente novamente.\n\n");
      }
      else break;
    }

    system("cls");

    switch(escolha) {
      case 1:
        while(aux_escolha) {
          mostra(vetor, N);
          printf("\n\nDeseja ordenar em ordem:\n1- Crescente\n2- Decrescente\n3- Voltar ao menu principal\n\nSua escolha: ");
          scanf("%d", &escolha);

          switch (escolha) {
            case 1: case 2:
              ordena(vetor, N, escolha);
              system("cls");
            break;

            case 3:
              aux_escolha = 0;
            break;

            default:
              system("cls");
              printf("Escolha inválida. Tente novamente.\n\n");
            break;
          }
        }
      break;

      case 2:
        inverte(vetor, N);
      break;

      case 3:
        do {
          system("cls");
          mostra(vetor, N);
          printf("\n\nQual valor deseja procurar?\nSua resposta: ");
          scanf("%f", &aux_escolha2);
          
          float *resultado = busca(vetor, N, aux_escolha2, &escolha);

          if(escolha > 0) {
            printf("\nValor(es) encontrado(s) na(s) posição(ões):");
            for(int v = 0; v < escolha; v++) {
              printf(" %.0f", resultado[v]);
            }
          }
          else printf("\nValor não encontrado no vetor. ");
          
          while(aux_escolha) {
            printf("\n\nDeseja procurar outro valor no vetor?\n1- Sim, procurar outro valor\n2- Não, voltar ao menu principal\n\nSua resposta: ");
            scanf("%d", &escolha);

            if(escolha == 1 || escolha == 2) {
              aux_escolha = 0;
            }
            else {
              system("cls");
              printf("Escolha inválida. Tente novamente.\n\n");
              mostra(vetor, N);
            }
          }
          aux_escolha = 1;
          free(resultado);
        } while (escolha == 1);
      break;

      case 4:
        do{
          while(aux_escolha) {
            mostra(vetor, N);

            aux_escolha2 = soma(vetor, N);
            printf("\n\nResultado da soma dos valores do vetor: %.2f\n", aux_escolha2);

            printf("\nDigitar novos valores para a soma?\n1- Sim, digitar novos valores para a soma\n2- Não, voltar para o menu principal\n\nSua escolha: ");
            scanf("%d", &escolha);

            switch(escolha) {
              case 1:
                novo_vetor(vetor, N, backup_vetor);
                system("cls");
              break;
  
              case 2:
                aux_escolha = 0;
              break;

              default:
                system("cls");
                printf("Escolha inválida. Tente novamente.\n\n");
              break;
            }
          }
        } while(escolha == 1);
      break;

      case 5:
        while(aux_escolha) {
          mostra(vetor, N);
          aux_escolha2 = argmax(vetor, N);
          printf("\n\nO maior valor é: %.2f", aux_escolha2);

          printf("\n\nDigitar um novo vetor?\n1- Sim, digitar um novo vetor\n2- Não, voltar para o menu principal\n\nSua escolha: ");
          scanf("%d", &escolha);

          switch(escolha) {
            case 1:
              novo_vetor(vetor, N, backup_vetor);
              system("cls");
            break;
  
            case 2:
              aux_escolha = 0;
            break;

            default:
              system("cls");
              printf("Escolha inválida. Tente novamente.\n\n");
            break;   
          }       
        }
      break;

      case 6:
        normaliza(vetor, N);
      break;

      case 7:
        while(aux_escolha) {
          mostra(vetor, N);
          aux_escolha2 = maiordif(vetor, N);
          printf("\n\nA maior diferença consecutiva é de: %.2f", aux_escolha2);

          printf("\n\nDigitar um novo vetor?\n1- Sim, digitar um novo vetor\n2- Não, voltar para o menu principal\n\nSua escolha: ");
          scanf("%d", &escolha);

          switch(escolha) {
            case 1:
              novo_vetor(vetor, N, backup_vetor);
              system("cls");
            break;
  
            case 2:
              aux_escolha = 0;
            break;

            default:
              system("cls");
              printf("Escolha inválida. Tente novamente.\n\n");
            break;   
          }       
        }
      break;

      case 8:
        for(int v = 0; v < N; v++) {
          vetor[v] = backup_vetor[v];
        }
			break;

      case 9:
				novo_vetor(vetor, N, backup_vetor);
			break;
    }
    aux_escolha = 1;
  } while(aux_escolha == 1);

  SetConsoleOutputCP(CPAGE_DEFAULT);

	return 0;
}
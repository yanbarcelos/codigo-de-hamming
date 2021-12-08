#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void geradorHamming(){

    int tamanhoMsg, contador = 1;

    printf("\nDigite a quantidade de bits da mensagem original: ");
    scanf("%d", &tamanhoMsg);
    printf("\n");

    int msg[tamanhoMsg + 1];
    for(int i = 1; i <= tamanhoMsg; i++){
        printf("Digite o bit numero %d: ", i);
        scanf("%d", &msg[i]);
    }

    printf("\nMensagem original: ");
    for(int i = 1; i <= tamanhoMsg; i++)
        printf("%d", msg[i]);
    printf("\n");

    int nroBitsRdn = 1;
    while(tamanhoMsg > (pow(2, nroBitsRdn) - nroBitsRdn - 1))
        nroBitsRdn++;

    int msgHamming[tamanhoMsg + nroBitsRdn + 1];

    for(int i = 0; i < nroBitsRdn; i++)
        msgHamming[(int)pow(2, i)] = -1;

    for(int i = 1; i <= (tamanhoMsg + nroBitsRdn); i++){
        if(msgHamming[i] != -1){
            msgHamming[i] = msg[contador];
            contador++;
        }
    }

    int paridade = 0;

    for(int i = 1; i <= (tamanhoMsg + nroBitsRdn); i++){
        if(msgHamming[i] == -1){
            msgHamming[i] = 0;
            paridade = 0;
            for(int j = i+1; j < (tamanhoMsg + nroBitsRdn); j++){
                for(int k = 0; k <= i; k++){
                    if(msgHamming[j] == 1)
                        paridade++;
                    j++;
                }
                j = j * i - 1;
            }
            if(paridade % 2 == 0)
                msgHamming[i] = 0;
            else
                msgHamming[i] = 1;
        }
    }

    printf("\nMensagem codificada: ");
    for(int i = 1; i <= (tamanhoMsg + nroBitsRdn); i++)
        printf("%d", msgHamming[i]);
    printf("\n");

}

void verificadorHamming(){

    int tamanhoMsg;

    printf("\nDigite a quantidade de bits recebida: ");
    scanf("%d", &tamanhoMsg);
    printf("\n");

    int msgHamming[tamanhoMsg + 1];
    for(int i = 1; i <= tamanhoMsg; i++){
        printf("Digite o bit numero %d: ", i);
        scanf("%d", &msgHamming[i]);
    }

    int aux2[tamanhoMsg + 1];
    for(int i = 1; i <= tamanhoMsg; i++){
        aux2[i] = msgHamming[i];
    }

    int nroBitsRdn = 2;
    while(tamanhoMsg > (pow(2, nroBitsRdn) - nroBitsRdn - 1 + nroBitsRdn))
        nroBitsRdn++;

    int aux[tamanhoMsg + 1];
    for(int i = 0; i < nroBitsRdn; i++){
        aux[(int)pow(2, i)] = msgHamming[(int)pow(2, i)];
        msgHamming[(int)pow(2, i)] = -1;
    }

    int paridade = 0;

    for(int i = 1; i <= (tamanhoMsg); i++){
        if(msgHamming[i] == -1){
            msgHamming[i] = 0;
            paridade = 0;
            for(int j = i+1; j < tamanhoMsg; j++){
                for(int k = 0; k <= i; k++){
                    if(msgHamming[j] == 1)
                        paridade++;
                    j++;
                }
                j = j * i - 1;
            }
            if(paridade % 2 == 0)
                msgHamming[i] = 0;
            else
                msgHamming[i] = 1;
        }
    }

    int somaIndice = 1;
    for(int i = 0; i < nroBitsRdn; i++){
        if(msgHamming[(int)pow(2, i)] != aux[(int)pow(2, i)]){
            aux[(int)pow(2, i)] = 5;
            somaIndice = somaIndice + pow(2, i);
        }
    }

    if(somaIndice != 1){
        printf("\nFoi detectado um erro no bit numero %d do grupo: ", somaIndice);
        for(int i = 1; i <= tamanhoMsg; i++)
            printf("%d", aux2[i]);

        if(msgHamming[somaIndice] == 0)
            msgHamming[somaIndice] = 1;

        if(msgHamming[somaIndice] == 1)
            msgHamming[somaIndice] = 0;
    }

    for(int i = 0; i < nroBitsRdn; i++)
        msgHamming[(int)pow(2, i)] = -1;

    int msg[tamanhoMsg - nroBitsRdn + 1], contador = 1;
    for(int i = 1; i <= tamanhoMsg; i++){
        if(msgHamming[i] != -1){
            msg[contador] = msgHamming[i];
            contador++;
        }
    }

    printf("\nGrupo de bits final (corrigido se houve erro): ");
    for(int i = 1; i <= (tamanhoMsg - nroBitsRdn); i++)
        printf("%d", msg[i]);

}

int main(){

    int opcao;

    do{
    system("cls");
    printf("..:: GERADOR E VERIFICADOR DE CODIGO DE HAMMING ::..\n");
	printf("1 - Enviar um grupo de bits\n");
    printf("2 - Verificar um grupo de bits recebido\n");
    printf("3 - Sair\n");
    printf("\nDigite a sua opcao: ");
    scanf("%d", &opcao);
    switch (opcao){
      case 1 :
           geradorHamming();
	       break;
      case 2 :
           verificadorHamming();
	       break;
    }
    printf("\nTecle algo!\n");
	getch();
    }while(opcao != 3);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "prod.h"
#include "cons.h"

void buffer() {
    FILE *file = fopen("buffer.txt", "w");
    if (file == NULL) {
        perror("Erro ao criar o arquivo buffer.txt");
        exit(EXIT_FAILURE);
    }

    // Inicializa o arquivo com 10 inteiros (0-9)
    //for (int i = 0; i < 10; i++) {
        //fprintf(file, "%d\n", i);
    //}

    srand(time(NULL));
    
    // Inicializa o arquivo com 10 valores aleatórios
    for (int i = 0; i < 10; i++) {
        int value = rand() % 100;
        fprintf(file, "%d\n", value);
    }

    fclose(file);
}

int main() {
    buffer();

    //Armazena o identificador de processo (O processo pai recebe o PID do processo filho)
    pid_t pidProdutor = fork(); 
    if (pidProdutor < 0) {
        perror("Erro ao criar o produtor");
        exit(EXIT_FAILURE);
    } else if (pidProdutor == 0) {
        produtor();
        exit(EXIT_SUCCESS);
    }

    pid_t pidConsumidor = fork();
    if (pidConsumidor < 0) {
        perror("Erro ao criar o consumidor");
        exit(EXIT_FAILURE);
    } else if (pidConsumidor == 0) {
        consumidor();
        exit(EXIT_SUCCESS);
    }

    // Aguarda a finalização dos processos produtor e consumidor
    waitpid(pidProdutor, NULL, 0);
    waitpid(pidConsumidor, NULL, 0);

    return 0;
}
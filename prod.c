#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "prod.h"

void produtor() {
    while (1) { //Loop infinito
        // Espera s segundos
        int s = (rand() % 3) + 1;
        sleep(s);

        // Gera um valor aleatório (0-99)
        int value = rand() % 100;

        // Abre o arquivo buffer.txt.lock para indicar que está sendo utilizado
        FILE* lockFile = fopen("buffer.txt.lock", "w");
        if (lockFile == NULL) {
            perror("Erro ao abrir o arquivo buffer.txt.lock");
            exit(EXIT_FAILURE);
        }
        fclose(lockFile);

        // Abre o arquivo buffer.txt no modo de adição
        FILE* file = fopen("buffer.txt", "a");
        if (file == NULL) {
            perror("Erro ao abrir o arquivo buffer.txt");
            exit(EXIT_FAILURE);
        }

        // Escreve o valor no final do arquivo
        fprintf(file, "%d\n", value);
        fclose(file);

        // Remove o arquivo buffer.txt.lock para indicar que a escrita foi concluída
        remove("buffer.txt.lock");

        printf("[Produtor] %d\n", value);
    }
}
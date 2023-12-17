#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cons.h"

#define MAX_VALUES 10

void consumidor() {
    while (1) { //Loop infinito
        // Espera s segundos
        int s = (rand() % 3) + 1;
        sleep(s);

        // Verifica se o arquivo buffer.txt.lock existe
        FILE* lockFile = fopen("buffer.txt.lock", "r");
        if (lockFile != NULL) {
            fclose(lockFile);
            continue;
        }

        // Abre o arquivo buffer.txt para leitura e escrita
        FILE* file = fopen("buffer.txt", "r+");
        if (file == NULL) {
            perror("Erro ao abrir o arquivo buffer.txt");
            exit(EXIT_FAILURE);
        }

        // Le o primeiro valor do arquivo
        int value;
        fscanf(file, "%d", &value);

        // Remove o primeiro valor do arquivo
        FILE* tempFile = fopen("buffer_temp.txt", "w");
        if (tempFile == NULL) {
            perror("Erro ao criar o arquivo temporário buffer_temp.txt");
            exit(EXIT_FAILURE);
        }

        // Copia os valores restantes para o arquivo temporário
        for (int i = 1; i < MAX_VALUES; i++) {
            int nextValue;
            fscanf(file, "%d", &nextValue);
            fprintf(tempFile, "%d\n", nextValue);
        }

        fclose(file);
        fclose(tempFile);

        // Substitui o arquivo original pelo arquivo temporário
        if (rename("buffer_temp.txt", "buffer.txt") != 0) {
            perror("Erro ao renomear o arquivo buffer_temp.txt");
            exit(EXIT_FAILURE);
        }

        printf("[Consumidor] %d\n", value);
    }
}
#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct {
    int x;
    int y;
    int tam_x;
    int tam_y;
    int velocidade;
    int score;
    int ball_y_final_pos;
    int cpu_random_pos;
} Jogador;

typedef struct {
    int x;
    int y;
    int tam;
    int direcao;
    int velocidade_x;
    int velocidade_y;
} Bola;

#endif

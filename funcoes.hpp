#ifndef FUNCOES_H
#define FUNCOES_H

void sairJogo() {
    quit = true;
}

void incrementaTimer() {
    timer++;
}

void telaMenu(BITMAP *buffer, FONT *fontm, int &modo, int &t) {
    while (!key[KEY_ENTER]) {
        textprintf_centre_ex(buffer, fontm, APP_WIDTH/2, APP_HEIGHT/2 -60, WHITE, -1, "GAME MODE");
        textprintf_centre_ex(buffer, fontm, APP_WIDTH/2, APP_HEIGHT/2, WHITE, -1, "1 PLAYER");
        textprintf_centre_ex(buffer, fontm, APP_WIDTH/2, APP_HEIGHT/2 + 40, WHITE, -1, "2 PLAYER");

        if (key[KEY_DOWN]) {
            modo = MULTIPLAYER;
        }

        if (key[KEY_UP]) {
            modo = SINGLEPLAYER;
        }

        if (key[KEY_T]) {
            set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, APP_WIDTH, APP_HEIGHT, 0, 0);
        }

        if (key[KEY_Y]) {
            set_gfx_mode(GFX_AUTODETECT_WINDOWED, APP_WIDTH, APP_HEIGHT, 0, 0);
        }

        if (modo == SINGLEPLAYER) {
            textprintf_centre_ex(buffer, fontm, APP_WIDTH/2, APP_HEIGHT/2, RED, -1, "1 PLAYER");
        } else {
            textprintf_centre_ex(buffer, fontm, APP_WIDTH/2, APP_HEIGHT/2 + 40, RED, -1, "2 PLAYER");
        }

        draw_sprite(screen, buffer, 0, 0);

        if (quit) {
            break;
        }
    }

    t = GAME_SCREEN;
}

void desenhaBackground(BITMAP *buffer) {
    int i, j;

    for (i = 0; i < 3; i++) {
        vline(buffer, i, i, APP_HEIGHT, makecol(150, 150, 150));
    }

    for (j = 0; j < 3; j++) {
        hline(buffer, j, j, APP_WIDTH, makecol(100, 100, 100));
    }

    vline(buffer, APP_WIDTH/2, 0, APP_HEIGHT, WHITE);
}

void iniciaJogador(Jogador &jog, int x, int y) {
    jog.x = x;
    jog.y = y;
    jog.tam_x = 10;
    jog.tam_y = 50;
    jog.velocidade = 8;
    jog.score = 0;
    jog.ball_y_final_pos = 0;
    jog.cpu_random_pos = 0;
}

void movimentaPalhetaCima(Jogador &jog) {
    if (jog.y > 0) {
        jog.y -= jog.velocidade;
    } else {
        jog.y = 0;
    }
}

void movimentaPalhetaBaixo(Jogador &jog) {
    if (jog.y + jog.tam_y < APP_HEIGHT) {
        jog.y += jog.velocidade;
    } else {
        jog.y = APP_HEIGHT - jog.tam_y;
    }
}

void movimentaMultiplayer(Jogador &jog) {
    if (jog.y + jog.tam_y/2 + jog.cpu_random_pos < jog.ball_y_final_pos) {
        jog.y += 4;
    }
    else if (jog.y + jog.tam_y/2 + jog.cpu_random_pos > jog.ball_y_final_pos + 4) {
        jog.y -= 4;
    }

    if (jog.y < 0) {
        jog.y = 0;
    }
    else if (jog.y > APP_HEIGHT - jog.tam_y ) {
        jog.y = APP_HEIGHT - jog.tam_y;
    }
}

void desenhaPalheta(BITMAP *buffer, Jogador &jog) {
    int i, j;

    for (i = 1; i < 4; i++) {
        hline(buffer, jog.x+i, jog.y+jog.tam_y+i, jog.x+jog.tam_x+i, makecol(100, 100, 100));
    }

    for (j = 1; j < 4; j++) {
        vline(buffer, jog.x+jog.tam_x+j, jog.y+j, jog.y+jog.tam_y+j, makecol(150, 150, 150));
    }

    rectfill(buffer, jog.x, jog.y, jog.x + jog.tam_x, jog.y + jog.tam_y, makecol(240, 240, 240));
}

void iniciaBolinha(Bola &b) {
    b.tam = 7;
    b.x = APP_WIDTH/2;
    b.y = abs(rand()%APP_HEIGHT - 30);
    b.direcao = (rand() % 2) ? OESTE : LESTE;

    switch (b.direcao) {
        case OESTE:
            b.velocidade_x = -3;
            break;
        case LESTE:
            b.velocidade_x = 3;
            break;
    }

    b.velocidade_y = 0;
}

void movimentaBolinha(Bola &b) {
    b.x += b.velocidade_x;
    b.y += b.velocidade_y;
}

void resetaBolinha(Bola &b, int direcao) {
    b.x = b.x = APP_WIDTH/2;
    b.y = abs(rand()%APP_HEIGHT - 30);
    b.direcao = direcao;

    switch (b.direcao) {
        case OESTE:
            b.velocidade_x = -3;
            break;
        case LESTE:
            b.velocidade_x = 3;
            break;
    }

    b.velocidade_y = 0;
}

void trocaDirecao(Bola &b) {
    if (b.direcao == SUDOESTE) {
        b.velocidade_x = (5 + rand()%4) * -1;
        b.velocidade_y = (3 + rand()%1);
    }

    else if (b.direcao == SUDESTE) {
        b.velocidade_x = (5 + rand()%4);
        b.velocidade_y = (3 + rand()%1);
    }

    else if (b.direcao == NORDESTE) {
        b.velocidade_x = (5 + rand()%4);
        b.velocidade_y = (3 + rand()%1) * -1;
    }

    else if (b.direcao == NOROESTE) {
        b.velocidade_x = (5 + rand()%4) * -1;
        b.velocidade_y = (3 + rand()%1) * -1;
    }

    else if (b.direcao == OESTE) {
        b.velocidade_x = (5 + rand()%4) * -1;
        b.velocidade_y = 0;
    }

    else if (b.direcao == LESTE) {
        b.velocidade_x = (5 + rand()%4);
        b.velocidade_y = 0;
    }
}

void desenhaBolinha(BITMAP *buffer, Bola &b) {
    int i, j;

    for (i = 1; i < 4; i++) {
        hline(buffer, b.x+i, b.y+b.tam+i, b.x+b.tam+i, makecol(100, 100, 100));
    }

    for (j = 1; j < 4; j++) {
        vline(buffer, b.x+b.tam+j, b.y+j, b.y+b.tam+j, makecol(150, 150, 150));
    }

    rectfill(buffer, b.x, b.y, b.x + b.tam, b.y + b.tam, makecol(255, 255, 255));
}

bool colisaoBolaPalheta(Bola &b, Jogador &jog) {
    if (b.x > (jog.x + jog.tam_x)
     || b.y > (jog.y + jog.tam_y)
     || jog.x > (b.x + b.tam)
     || jog.y > (b.y + b.tam)) {
        return false;
    }

    return true;
}

bool colisaoBolaParede(Bola &b) {
    if (b.x > 0
     && b.x < APP_WIDTH
     && b.y > 0
     && b.y < APP_HEIGHT - b.tam) {
           return false;
    }

    return true;
}

int eq_reta_y_final(int x0, int y0, int v_x, int v_y, int x_final) {
    float m = (float) ((y0+v_y) - y0) / ((x0+v_x) - x0);
    return (m*(x_final - x0)) + y0;
}

#endif

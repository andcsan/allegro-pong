#include <allegro.h>
#include <time.h>
#include <iostream>
#include "constantes.hpp"
#include "globais.hpp"
#include "estruturas.hpp"
#include "prototipos.hpp"
#include "funcoes.hpp"

int main()
{
    allegro_init();
    install_timer();
    install_keyboard();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0);
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, APP_WIDTH, APP_HEIGHT, 0, 0);
    set_window_title(APP_NAME);
    set_close_button_callback(sairJogo);
    srand(time(NULL));

    LOCK_VARIABLE(timer);
    LOCK_FUNCTION(incrementaTimer);
    install_int_ex(incrementaTimer, BPS_TO_TIMER(FPS));

    int game_mode =  SINGLEPLAYER;
    int tela = MENU_SCREEN;
    FONT *pongfont   = NULL;
    BITMAP *buffer   = NULL;
    SAMPLE *wallhit  = NULL;
    SAMPLE *stickhit = NULL;
    SAMPLE *pointhit = NULL;
    wallhit  = load_sample("sounds/wall.wav");
    stickhit = load_sample("sounds/stick.wav");
    pointhit = load_sample("sounds/point.wav");
    buffer   = create_bitmap(APP_WIDTH, APP_HEIGHT);
    pongfont = load_font("assets/pongf.pcx", 0, NULL);

    Jogador jogador[2];
    Bola bola;

    iniciaJogador(jogador[0], 10, APP_HEIGHT/2);
    iniciaJogador(jogador[1], APP_WIDTH - 20, APP_HEIGHT/2);
    iniciaBolinha(bola);

    while (!quit) {
        if (tela == MENU_SCREEN) {
            telaMenu(buffer, pongfont, game_mode, tela);
            timer = 0;
        }

        else if (tela == GAME_SCREEN) {
            while (timer >= 0 && tela == GAME_SCREEN) {
                timer--;

                // entrada de dados do usuário
                if (key[KEY_W]) {
                    movimentaPalhetaCima(jogador[0]);
                } else if (key[KEY_S]) {
                    movimentaPalhetaBaixo(jogador[0]);
                }

                if (key[KEY_M]) {
                    iniciaJogador(jogador[0], 10, APP_HEIGHT/2);
                    iniciaJogador(jogador[1], APP_WIDTH - 20, APP_HEIGHT/2);
                    iniciaBolinha(bola);
                    tela = MENU_SCREEN;
                }

                if (game_mode == SINGLEPLAYER) {
                    if (bola.direcao == NORDESTE || bola.direcao == SUDESTE || bola.direcao == LESTE) {
                        jogador[1].ball_y_final_pos = eq_reta_y_final(bola.x, bola.y, bola.velocidade_x, bola.velocidade_y, jogador[1].x);
                        movimentaMultiplayer(jogador[1]);
                    }
                } else if (game_mode == MULTIPLAYER) {
                    if (key[KEY_8_PAD]) {
                        movimentaPalhetaCima(jogador[1]);
                    } else if (key[KEY_5_PAD]) {
                        movimentaPalhetaBaixo(jogador[1]);
                    }
                }

                if (key[KEY_ESC]) {
                    quit = true;
                }

                movimentaBolinha(bola);

                // checa colisão com as palhetas
                if (colisaoBolaPalheta(bola, jogador[0])) {
                    bola.direcao = 4 + rand()%2;
                    trocaDirecao(bola);
                    play_sample(stickhit, 255, 128, 1000, 0);
                    jogador[1].cpu_random_pos = (rand()%DIFICULDADE) - DIFICULDADE/2;
                } else if (colisaoBolaPalheta(bola, jogador[1])) {
                    bola.direcao = 1 + rand()%2;
                    trocaDirecao(bola);
                    play_sample(stickhit, 255, 128, 1000, 0);

                }

                // checa colisão com as paredes
                if (colisaoBolaParede(bola)) {
                    if (bola.x <= 0) {
                        play_sample(pointhit, 255, 128, 1000, 0);
                        jogador[1].score++;
                        resetaBolinha(bola, OESTE);
                    } else if (bola.x >= APP_WIDTH) {
                        play_sample(pointhit, 255, 128, 1000, 0);
                        jogador[0].score++;
                        resetaBolinha(bola, LESTE);
                        jogador[1].cpu_random_pos = (rand()%20) - 10;
                    } else if (bola.y < 0 || bola.y > APP_HEIGHT - bola.tam) {
                        play_sample(wallhit, 255, 128, 1000, 0);
                        if (bola.direcao == NORDESTE) {
                            bola.direcao = SUDESTE;
                            trocaDirecao(bola);
                        } else if (bola.direcao == NOROESTE) {
                            bola.direcao = SUDOESTE;
                            trocaDirecao(bola);
                        } else if (bola.direcao == SUDOESTE) {
                            bola.direcao = NOROESTE;
                            trocaDirecao(bola);
                        } else if (bola.direcao == SUDESTE) {
                            bola.direcao = NORDESTE;
                            trocaDirecao(bola);
                        }
                    }
                }

                // desenha no buffer
                textprintf_ex(buffer, pongfont, APP_WIDTH/2+30, 20, SHADOW, -1, "%d", jogador[1].score);
                textprintf_ex(buffer, pongfont, APP_WIDTH/2+31, 21, SHADOW, -1, "%d", jogador[1].score);
                textprintf_ex(buffer, pongfont, APP_WIDTH/2+32, 22, WHITE, -1, "%d", jogador[1].score);
                textprintf_right_ex(buffer, pongfont, APP_WIDTH/2-32, 20, SHADOW, -1, "%d", jogador[0].score);
                textprintf_right_ex(buffer, pongfont, APP_WIDTH/2-31, 21, SHADOW, -1, "%d", jogador[0].score);
                textprintf_right_ex(buffer, pongfont, APP_WIDTH/2-30, 22, WHITE, -1, "%d", jogador[0].score);
                desenhaBackground(buffer);
                desenhaPalheta(buffer, jogador[0]);
                desenhaBolinha(buffer, bola);
                desenhaPalheta(buffer, jogador[1]);
                draw_sprite(screen, buffer, 0, 0);
                clear_to_color(buffer, makecol(50, 50 , 50));
            }
        }
    }

    destroy_bitmap(buffer);
    destroy_sample(wallhit);
    destroy_sample(stickhit);
    destroy_sample(pointhit);
    destroy_font(pongfont);

    allegro_exit();

    return 0;
} END_OF_MAIN();

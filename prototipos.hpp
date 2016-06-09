#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

void sairJogo();
void incrementaTimer();
void telaMenu(BITMAP *buffer, FONT *fontm, int &modo, int &t);
void desenhaBackground(BITMAP *buffer);
void iniciaJogador(Jogador &jog, int x, int y);
void movimentaPlahetaCima(Jogador &jog);
void movimentaPalhetaBaixo(Jogador &jog);
void movimentaMultiplayer(Jogador &jog, Bola &b);
void desenhaPalheta(BITMAP *buffer, Jogador &jog);
void iniciaBolinha(Bola &b);
void resetaBolinha(Bola &b, int direcao);
void trocaDirecao(Bola &b);
void movimentaBolinha(Bola &b);
void desenhaBolinha(BITMAP *buffer, Bola &b);
bool colisaoBolaPalheta(Bola &b, Jogador &jog);
bool colisaoBolaParede(Bola &b);

#endif //  PROTOTIPOS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// ______________________________

//BIBLIOTECAS DO ALLEGRO
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

//INCLUDES DO JOGO

#include "pilha.h"
// ______________________________
//VARIAVEIS GLOBAIS


const float FPS = 60; //frequencia de atualização da tela
const int TELA_LARGURA = 800;
const int TELA_ALTURA = 600;
bool musica_estado = true;
int mouse;

//display
ALLEGRO_DISPLAY *janela = NULL; 
ALLEGRO_EVENT_QUEUE *eventos_fila = NULL, *timer_fila = NULL; //cria fila de eventos
ALLEGRO_TIMER *timer = NULL;// temporizador de atualização da tela do jogo
ALLEGRO_TIMER *contador1 = NULL;
ALLEGRO_TIMER *contador2 = NULL;
ALLEGRO_TIMER *contador3 = NULL;
ALLEGRO_TIMER *contador4 = NULL;

//imagens
ALLEGRO_BITMAP *janela_icone = NULL;

ALLEGRO_FONT *fonte = NULL;

//imagens do menu
ALLEGRO_BITMAP *img_menu = NULL;
ALLEGRO_BITMAP *img_menu1 = NULL;
ALLEGRO_BITMAP *img_menu2 = NULL;
ALLEGRO_BITMAP *img_menu3 = NULL;
ALLEGRO_BITMAP *img_menu4 = NULL;

ALLEGRO_BITMAP *creditos1 = NULL;
ALLEGRO_BITMAP *creditos2 = NULL;
ALLEGRO_BITMAP *instrucoes1 = NULL;
ALLEGRO_BITMAP *instrucoes2 = NULL;
//Audio
ALLEGRO_SAMPLE *musica = NULL;
ALLEGRO_SAMPLE_INSTANCE *musica_instancia = NULL;

//Jogo
ALLEGRO_BITMAP *base1 = NULL;
ALLEGRO_BITMAP *base2 = NULL;
ALLEGRO_BITMAP *base3 = NULL;
ALLEGRO_BITMAP *base4 = NULL;
ALLEGRO_BITMAP *base5 = NULL;

ALLEGRO_BITMAP *recheio1 = NULL;
ALLEGRO_BITMAP *recheio2 = NULL;
ALLEGRO_BITMAP *recheio3 = NULL;
ALLEGRO_BITMAP *recheio4 = NULL;
ALLEGRO_BITMAP *recheio5 = NULL;

ALLEGRO_BITMAP *cima1 = NULL;
ALLEGRO_BITMAP *cima2 = NULL;
ALLEGRO_BITMAP *cima3 = NULL;
ALLEGRO_BITMAP *cima4 = NULL;
ALLEGRO_BITMAP *cima5 = NULL;

ALLEGRO_BITMAP *cobertura1 = NULL;
ALLEGRO_BITMAP *cobertura2 = NULL;
ALLEGRO_BITMAP *cobertura3 = NULL;
ALLEGRO_BITMAP *cobertura4 = NULL;
ALLEGRO_BITMAP *cobertura5 = NULL;

ALLEGRO_BITMAP *cenario_vazio = NULL;
ALLEGRO_BITMAP *cenario = NULL;

ALLEGRO_BITMAP *tela_bolo_modelo = NULL;

//Controle de telas
enum{inicio,menu_jogo,jogar,instrucoes,creditos,sair};
int estado = inicio;
int opcao;

// ______________________________

//FUNÇÕES PRINCIPAIS - Protótipo
bool inicializa();
int menu();
void gera_mostra_pronto(int tempo, Pilha &pilha_gera);
void credito();
void instrucao();
void destrutores();
bool inicializa_imagens();
void imprime_elemento_baixo(Pilha pilha);
void imprime_elemento_cima(Pilha pilha);
void imprime_elemento_recheio(Pilha pilha);
void imprime_elemento_cobertura(Pilha pilha);
void gerador_bolo_modelo(Pilha &pilha);
void imprime_bolo(Pilha &pilha);
int tempo_random();
void captura_bolo(Pilha &pilha);
// ______________________________

int main(int argc, char **argv) {

	Pilha pilha_gera;
	Pilha pilha_jogo;

	if (!inicializa()) {
		destrutores();
		return 0;
	}
	if (!inicializa_imagens()) {
		destrutores();
		return 0;
	}
	while (estado == inicio) {
		opcao = menu();
		if (opcao == jogar) {
			int tempo = tempo_random();
			gera_mostra_pronto(1, pilha_gera);
			captura_bolo(pilha_jogo);
		}
		else if (opcao == creditos)
			credito();
		else if (opcao == instrucoes)
			instrucao();
		else
			estado = sair;
	}
	//DESTRUTORES
	destrutores();
	return 0;
}

///*
//FUNÇÕES PRINCIPAIS
void captura_bolo(Pilha &pilha) {
	bool ok;
	int sair_captura = 0;
	int tempo = 23;
	bool flag1 = false, flag2 = false, flag3 = false, flag4 = false;
	bool iflag1 = false, iflag2 = false, iflag3 = false, iflag4 = false, iflag5 = false;
		al_flip_display();
		al_draw_scaled_bitmap(cenario, 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
		al_flip_display();
		al_register_event_source(eventos_fila, al_get_mouse_event_source());

	while (tempo != 0)
	{
		al_register_event_source(eventos_fila, al_get_timer_event_source(timer));

		al_start_timer(timer);
		while (!al_is_event_queue_empty(eventos_fila))
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(eventos_fila, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{

				if (evento.mouse.x >= 0 && evento.mouse.x <= 200 && evento.mouse.y >= 400 && evento.mouse.y <= 600 && !flag1)
				{
					//Lugar baixo
					if (evento.mouse.x >= 20 && evento.mouse.x <= 90 && evento.mouse.y >= 420 && evento.mouse.y <= 460) {
						al_draw_rectangle(20, 420, 90, 460, al_map_rgb(240, 0, 0), 7);
						flag1 = true;
						pilha.Empilha(4,ok);
					}
					else if (evento.mouse.x >= 110 && evento.mouse.x <= 190 && evento.mouse.y >= 420 && evento.mouse.y <= 460) {
						al_draw_rectangle(110, 420, 190, 460, al_map_rgb(240, 0, 0), 7);
						al_flip_display();
						flag1 = true;
						pilha.Empilha(1, ok);
					}
					else if (evento.mouse.x >= 60 && evento.mouse.x <= 140 && evento.mouse.y >= 480 && evento.mouse.y <= 520) {
						al_draw_rectangle(60, 480, 140, 520, al_map_rgb(240, 0, 0), 7);
						al_flip_display();
						flag1 = true;
						pilha.Empilha(0, ok);
					}
					else if (evento.mouse.x >= 20 && evento.mouse.x <= 90 && evento.mouse.y >= 540 && evento.mouse.y <= 580) {
						al_draw_rectangle(20, 540, 90, 580, al_map_rgb(240, 0, 0), 7);
						al_flip_display();
						flag1 = true;
						pilha.Empilha(2, ok);
					}
					else if (evento.mouse.x >= 110 && evento.mouse.x <= 190 && evento.mouse.y >= 540 && evento.mouse.y <= 580) {
						al_draw_rectangle(110, 540, 190, 580, al_map_rgb(240, 0, 0), 7);
						al_flip_display();
						flag1 = true;
						pilha.Empilha(3, ok);
					}
					imprime_elemento_baixo(pilha);
				}
				else if (evento.mouse.x > 200 && evento.mouse.x <= 400 && evento.mouse.y > 400 && evento.mouse.y <= 600 && !flag2)
				{
					//Lugar recheio
					if (evento.mouse.x >= 210 && evento.mouse.x <= 300 && evento.mouse.y >= 420 && evento.mouse.y <= 460) {
						al_draw_rectangle(210, 420, 300, 460, al_map_rgb(240, 0, 0), 7);
						flag2 = true;
						pilha.Empilha(5, ok);
					}
					else if (evento.mouse.x >= 305 && evento.mouse.x <= 390 && evento.mouse.y >= 420 && evento.mouse.y <= 460) {
						al_draw_rectangle(305, 420, 390, 460, al_map_rgb(240, 0, 0), 7);
						al_flip_display();
						flag2 = true;
						pilha.Empilha(6, ok);
					}
					else if (evento.mouse.x >= 260 && evento.mouse.x <= 340 && evento.mouse.y >= 480 && evento.mouse.y <= 520) {
						al_draw_rectangle(260, 480, 340, 520, al_map_rgb(240, 0, 0), 7);
						al_flip_display();
						flag2 = true;
						pilha.Empilha(9, ok);
					}
					else if (evento.mouse.x >= 208 && evento.mouse.x <= 295 && evento.mouse.y >= 540 && evento.mouse.y <= 580) {
						al_draw_rectangle(208, 540, 295, 580, al_map_rgb(240, 0, 0), 7);
						al_flip_display();
						flag2 = true;
						pilha.Empilha(7, ok);
					}
					else if (evento.mouse.x >= 300 && evento.mouse.x <= 395 && evento.mouse.y >= 540 && evento.mouse.y <= 580) {
						al_draw_rectangle(300, 540, 395, 580, al_map_rgb(240, 0, 0), 7);
						al_flip_display();
						flag2 = true;
						pilha.Empilha(8, ok);
					}
					imprime_elemento_recheio(pilha);
				}
				else if (evento.mouse.x > 400 && evento.mouse.x <= 600 && evento.mouse.y > 400 && evento.mouse.y <= 600 && !flag3) 
				{
						//Lugar cima
						if (evento.mouse.x >= 410 && evento.mouse.x <= 480 && evento.mouse.y >= 420 && evento.mouse.y <= 460) {
							al_draw_rectangle(410, 420, 480, 460, al_map_rgb(240, 0, 0), 7);
							flag3 = true;
							pilha.Empilha(10, ok);
						}
						else if (evento.mouse.x >= 510 && evento.mouse.x <= 580 && evento.mouse.y >= 420 && evento.mouse.y <= 460) {
							al_draw_rectangle(510, 420, 580, 460, al_map_rgb(240, 0, 0), 7);
							al_flip_display();
							flag3 = true;
							pilha.Empilha(13, ok);
						}
						else if (evento.mouse.x >= 460 && evento.mouse.x <= 525 && evento.mouse.y >= 480 && evento.mouse.y <= 520) {
							al_draw_rectangle(460, 480, 525, 520, al_map_rgb(240, 0, 0), 7);
							al_flip_display();
							flag3 = true;
							pilha.Empilha(12, ok);
						}
						else if (evento.mouse.x >= 410 && evento.mouse.x <= 480 && evento.mouse.y >= 540 && evento.mouse.y <= 580) {
							al_draw_rectangle(410, 540, 480, 580, al_map_rgb(240, 0, 0), 7);
							al_flip_display();
							flag3 = true;
							pilha.Empilha(11, ok);
						}
						else if (evento.mouse.x >= 510 && evento.mouse.x <= 580 && evento.mouse.y >= 540 && evento.mouse.y <= 580) {
							al_draw_rectangle(510, 540, 580, 580, al_map_rgb(240, 0, 0), 7);
							al_flip_display();
							flag3 = true;
							pilha.Empilha(14, ok);
						}
						imprime_elemento_cima(pilha);
				}
				//else if (evento.mouse.x > 600 && evento.mouse.x <= 800 && evento.mouse.y >= 400 && evento.mouse.y <= 600 && !flag4) {
				else if (evento.mouse.x > 600 && evento.mouse.x <= 800 && evento.mouse.y >= 400 && evento.mouse.y <= 600 && !flag4) 
				{
					//Lugar cobertura
					if (evento.mouse.x >= 610 && evento.mouse.x <= 695 && evento.mouse.y >= 420 && evento.mouse.y <= 460) {
						al_draw_rectangle(610, 420, 695, 460, al_map_rgb(240, 0, 0), 7);
						flag4 = true;
						pilha.Empilha(19, ok);
					}
					else if (evento.mouse.x >= 700 && evento.mouse.x <= 790 && evento.mouse.y >= 420 && evento.mouse.y <= 460) {
						al_draw_rectangle(700, 420, 790, 460, al_map_rgb(240, 0, 0), 7);
						al_flip_display();
						flag4 = true;
						pilha.Empilha(17, ok);
					}
					else if (evento.mouse.x >= 650 && evento.mouse.x <= 745 && evento.mouse.y >= 480 && evento.mouse.y <= 520) {
						al_draw_rectangle(650, 480, 745, 520, al_map_rgb(240, 0, 0), 7);
						al_flip_display();
						flag4 = true;
						pilha.Empilha(18, ok);
					}
					else if (evento.mouse.x >= 610 && evento.mouse.x <= 690 && evento.mouse.y >= 540 && evento.mouse.y <= 580) {
						al_draw_rectangle(610, 540, 690, 580, al_map_rgb(240, 0, 0), 7);
						al_flip_display();
						flag4 = true;
						pilha.Empilha(18, ok);
					}
					else if (evento.mouse.x >= 700 && evento.mouse.x <= 790 && evento.mouse.y >= 540 && evento.mouse.y <= 580) {
						al_draw_rectangle(700, 540, 790, 580, al_map_rgb(240, 0, 0), 7);
						al_flip_display();
						flag4 = true;
						pilha.Empilha(15, ok);
					}
					imprime_elemento_cobertura(pilha);
				}
			}
		}
		//al_flip_display();
		if (!al_is_event_queue_empty(timer_fila))
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(timer_fila, &evento);

			if (evento.type == ALLEGRO_EVENT_TIMER)
			{
				tempo--;
			}
		}
		al_draw_scaled_bitmap(cenario_vazio ,0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
		al_draw_textf(fonte, al_map_rgb(240, 0, 0), 710, 5, ALLEGRO_ALIGN_CENTRE, "%d", tempo);

	}
}
//*/

void imprime_elemento_cima(Pilha pilha){
	int aux;
	bool ok;
	pilha.Desempilha(aux, ok);

	if (aux == 10) {
		al_draw_bitmap(cima1, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio5) / 2), 140, 0);
	}
	else if (aux == 11) {
		al_draw_bitmap(cima2, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio5) / 2), 140, 0);
	}
	else if (aux == 12) {
		al_draw_bitmap(cima3, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio5) / 2), 140, 0);
	}
	else if (aux == 13) {
		al_draw_bitmap(cima4, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio5) / 2), 140, 0);
	}
	else if (aux == 14) {
		al_draw_bitmap(cima5, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio5) / 2), 140, 0);
	}

	pilha.Empilha(aux, ok);
	al_flip_display();
}

void imprime_elemento_recheio(Pilha pilha){
	int aux;
	bool ok;
	pilha.Desempilha(aux, ok);

	if (aux == 5) {
		al_draw_bitmap(recheio1, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio1) / 2), 200, 0);
	}
	else if (aux == 6) {
		al_draw_bitmap(recheio2, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio2) / 2), 200, 0);
	}
	else if (aux == 7) {
		al_draw_bitmap(recheio3, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio3) / 2), 200, 0);
	}
	else if (aux == 8) {
		al_draw_bitmap(recheio4, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio4) / 2), 200, 0);
	}
	else if (aux == 9) {
		al_draw_bitmap(recheio5, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio5) / 2), 200, 0);
	}

	pilha.Empilha(aux, ok);
	al_flip_display();
}

void imprime_elemento_cobertura(Pilha pilha){
	int aux;
	bool ok;
	pilha.Desempilha(aux, ok);

	if (aux == 15) {
		al_draw_bitmap(cobertura1, (TELA_LARGURA / 2) - (al_get_bitmap_width(cobertura1) / 2), 115, 0);
	}
	else if (aux == 16) {
		al_draw_bitmap(cobertura2, (TELA_LARGURA / 2) - (al_get_bitmap_width(cobertura2) / 2), 115, 0);
	}
	else if (aux == 17) {
		al_draw_bitmap(cobertura3, (TELA_LARGURA / 2) - (al_get_bitmap_width(cobertura3) / 2), 115, 0);
	}
	else if (aux == 18) {
		al_draw_bitmap(cobertura4, (TELA_LARGURA / 2) - (al_get_bitmap_width(cobertura4) / 2), 115, 0);
	}
	else if (aux == 19) {
		al_draw_bitmap(cobertura5, (TELA_LARGURA / 2) - (al_get_bitmap_width(cobertura5) / 2), 115, 0);
	}

	pilha.Empilha(aux, ok);
	al_flip_display();
}

void imprime_elemento_baixo(Pilha pilha) {
	int aux;
	bool ok;
	pilha.Desempilha(aux, ok);
	if (aux == 0) {
		al_draw_bitmap(base1, (TELA_LARGURA / 2) - (al_get_bitmap_width(base1) / 2), 230, 0);
	}
	else if (aux == 1) {
		al_draw_bitmap(base2, (TELA_LARGURA / 2) - (al_get_bitmap_width(base2) / 2), 230, 0);
	}
	else if (aux == 2) {
		al_draw_bitmap(base3, (TELA_LARGURA / 2) - (al_get_bitmap_width(base3) / 2), 230, 0);
	}
	else if (aux == 3) {
		al_draw_bitmap(base4, (TELA_LARGURA / 2) - (al_get_bitmap_width(base4) / 2), 230, 0);
	}
	else if (aux == 4) {
		al_draw_bitmap(base5, (TELA_LARGURA / 2) - (al_get_bitmap_width(base5) / 2), 230, 0);
	}
	pilha.Empilha(aux, ok);
	al_flip_display();
}

bool inicializa() {

	al_init();
	al_init_font_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();

	if (!al_init())
	{
		fprintf(stderr, "Falha ao inicializar Allegro.\n");
		return false;
	}

	if (!al_install_audio())
	{
		fprintf(stderr, "Falha ao inicializar áudio.\n");
		return false;
	}

	if (!al_init_acodec_addon())
	{
		fprintf(stderr, "Falha ao inicializar codecs de áudio.\n");
		return false;
	}

	if (!al_reserve_samples(1))
	{
		fprintf(stderr, "Falha ao alocar canais de áudio.\n");
		return false;
	}

	if (!al_install_keyboard())
	{
		fprintf(stderr, "Falha ao inicializar teclado.\n");
		return false;
	}

	janela = al_create_display(TELA_LARGURA, TELA_ALTURA);
	if (!janela)
	{
		fprintf(stderr, "Falha ao criar a janela.\n");
		return false;
	}

	musica = al_load_sample("../sons/caketown.ogg");
	if (!musica)
	{
		fprintf(stderr, "Falha ao carregar sample.\n");
		al_destroy_display(janela);
		return false;
	}

	if (!al_install_mouse())
	{
		fprintf(stderr, "Falha ao inicializar o mouse.\n");
		al_destroy_display(janela);
		return -1;
	}

	if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
	{
		fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
		al_destroy_display(janela);
		return -1;
	}

	fonte = al_load_font("../imagens/NANO-LOW.TTF", 35, 0);
	if (!fonte)
	{
		fprintf(stderr, "Falha ao carregar fonte.\n");
		al_destroy_timer(contador1);
		al_destroy_timer(contador2);
		al_destroy_timer(contador3);
		al_destroy_timer(contador4);
		al_destroy_font(fonte);
		al_destroy_timer(timer);
		al_destroy_event_queue(eventos_fila);
		al_destroy_event_queue(timer_fila);
		al_destroy_display(janela);
		return false;
	}

	timer = al_create_timer(0.1);
	if (!timer)
	{
		fprintf(stderr, "Falha ao criar timer.\n");
		al_destroy_font(fonte);
		al_destroy_timer(timer);
		al_destroy_event_queue(eventos_fila);
		al_destroy_display(janela);
		return false;
	}

	contador1 = al_create_timer(1.0);
	if (!contador1)
	{
		fprintf(stderr, "Falha ao criar timer.\n");
		al_destroy_font(fonte);
		al_destroy_timer(contador1);
		al_destroy_timer(timer);
		al_destroy_event_queue(eventos_fila);
		al_destroy_display(janela);
		return false;
	}

	eventos_fila = al_create_event_queue();
	if (!eventos_fila)
	{
		fprintf(stderr, "Falha ao criar fila de eventos.\n");
		al_destroy_display(janela);
		al_destroy_sample(musica);
		return false;
	}

	timer_fila = al_create_event_queue();
	if (!timer_fila)
	{
		fprintf(stderr, "Falha ao criar fila do contador.\n");
		al_destroy_timer(contador1);
		al_destroy_timer(contador2);
		al_destroy_timer(contador3);
		al_destroy_timer(contador4);
		al_destroy_font(fonte);
		al_destroy_timer(timer);
		al_destroy_event_queue(eventos_fila);
		al_destroy_event_queue(timer_fila);
		al_destroy_display(janela);
		return false;
	}

	al_set_window_title(janela, "Fabrica de Bolos");

	janela_icone = al_load_bitmap("../imagens/janela_icone.png");
	if (!janela_icone) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize bg_main!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_reserve_samples(2); //quantos sons podem tocar AO MESMO TEMPO?
	musica = al_load_sample("../sons/caketown.ogg");
	if (!musica) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize musica",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	musica_instancia = al_create_sample_instance(musica);
	al_set_sample_instance_playmode(musica_instancia, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(musica_instancia, al_get_default_mixer());
	al_set_mixer_gain(al_get_default_mixer(), 1.0); //amplificador da musica
	al_play_sample_instance(musica_instancia); //da play na musica

	al_set_window_title(janela, "Fabrica de Bolos");
	al_set_display_icon(janela, janela_icone);

	return true;
}

bool inicializa_imagens() {

	img_menu = al_load_bitmap("../imagens/tela1.png");
	if (!img_menu) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize img_menu!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	img_menu1 = al_load_bitmap("../imagens/tela2.png");
	if (!img_menu1) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize img_menu1!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	img_menu2 = al_load_bitmap("../imagens/tela3.png");
	if (!img_menu2) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize img_menu2!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	img_menu3 = al_load_bitmap("../imagens/tela4.png");
	if (!img_menu3) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize img_menu3!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	img_menu4 = al_load_bitmap("../imagens/tela5.png");
	if (!img_menu4) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize img_menu4!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	base1 = al_load_bitmap("../imagens/bolo1.png");
	if (!base1) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize base1!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	base2 = al_load_bitmap("../imagens/bolo2.png");
	if (!base2) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize base2!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	base3 = al_load_bitmap("../imagens/bolo3.png");
	if (!base3) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize base3!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	base4 = al_load_bitmap("../imagens/bolo4.png");
	if (!base4) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize base4!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	base5 = al_load_bitmap("../imagens/bolo5.png");
	if (!base5) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize base5!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	recheio1 = al_load_bitmap("../imagens/recheio1.png");
	if (!recheio1) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize recheio1!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	recheio2 = al_load_bitmap("../imagens/recheio2.png");
	if (!recheio2) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize recheio2!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	recheio3 = al_load_bitmap("../imagens/recheio3.png");
	if (!recheio3) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize recheio3!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	recheio4 = al_load_bitmap("../imagens/recheio4.png");
	if (!recheio4) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize recheio4!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	recheio5 = al_load_bitmap("../imagens/recheio5.png");
	if (!recheio5) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize recheio5!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	cima1 = al_load_bitmap("../imagens/bolo6.png");
	if (!cima1) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize cima1!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	cima2 = al_load_bitmap("../imagens/bolo7.png");
	if (!cima2) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize cima2!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	cima3 = al_load_bitmap("../imagens/bolo8.png");
	if (!cima3) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize cima3!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	cima4 = al_load_bitmap("../imagens/bolo9.png");
	if (!cima4) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize cima4!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	cima5 = al_load_bitmap("../imagens/bolo10.png");
	if (!cima5) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize cima5!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	cobertura1 = al_load_bitmap("../imagens/cobertura1.png");
	if (!cobertura1) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize cobertura1!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	cobertura2 = al_load_bitmap("../imagens/cobertura2.png");
	if (!cobertura2) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize cobertura2!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	cobertura3 = al_load_bitmap("../imagens/cobertura3.png");
	if (!cobertura3) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize cobertura3!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	cobertura4 = al_load_bitmap("../imagens/cobertura4.png");
	if (!cobertura4) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize cobertura4!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	cobertura5 = al_load_bitmap("../imagens/cobertura5.png");
	if (!cobertura5) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize cobertura5!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	cenario_vazio = al_load_bitmap("../imagens/cenario.png");
	if (!cenario_vazio) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize cenario vazio!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	creditos1 = al_load_bitmap("../imagens/creditos1.png");
	if (!creditos1) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize creditos1!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	creditos2 = al_load_bitmap("../imagens/creditos2.png");
	if (!creditos2) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize creditos2!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	instrucoes1 = al_load_bitmap("../imagens/instrucoes1.png");
	if (!instrucoes1) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize instrucoes1!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	instrucoes2 = al_load_bitmap("../imagens/instrucoes2.png");
	if (!instrucoes2) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize cenario!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	cenario = al_load_bitmap("../imagens/cenario_novo.png");
	if (!cenario) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize cenario!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	tela_bolo_modelo = al_load_bitmap("../imagens/tela_bolo_modelo.png");
	if (!tela_bolo_modelo) {
		al_show_native_message_box(janela, "Error", "Error", "Failed to initialize cenario!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	return true;
}

int menu() {
	int sair_menu = 0;

	al_flip_display();
	al_draw_scaled_bitmap(img_menu, 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
	al_flip_display();
	al_register_event_source(eventos_fila, al_get_mouse_event_source());
	
	while (!sair_menu)
	{
		while (!al_is_event_queue_empty(eventos_fila))
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(eventos_fila, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
			{
				
				if (evento.mouse.x >= 20 && evento.mouse.x <= 200 && evento.mouse.y >= 480 && evento.mouse.y <= 540)
				{
					al_flip_display();
					al_draw_scaled_bitmap(img_menu1, 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
					al_flip_display();
				}
				else if (evento.mouse.x >= 220 && evento.mouse.x <= 390 && evento.mouse.y >= 480 && evento.mouse.y <= 540) {
					al_flip_display();
					al_draw_scaled_bitmap(img_menu2, 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
					al_flip_display();
				}
				else if (evento.mouse.x >= 420 && evento.mouse.x <= 590 && evento.mouse.y >= 480 && evento.mouse.y <= 540) {
					al_flip_display();
					al_draw_scaled_bitmap(img_menu3, 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
					al_flip_display();
				}
				else if (evento.mouse.x >= 610 && evento.mouse.x <= 790 && evento.mouse.y >= 480 && evento.mouse.y <= 540) {
					al_flip_display();
					al_draw_scaled_bitmap(img_menu4, 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
					al_flip_display();
				}
				else {
					al_flip_display();
					al_draw_scaled_bitmap(img_menu, 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
					al_flip_display();
				}
			}
			// Ou se o evento foi um clique do mouse
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				if (evento.mouse.x >= 20 && evento.mouse.x <= 200 && evento.mouse.y >= 480 && evento.mouse.y <= 540) {
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_flip_display();
					return jogar;
				}
				else if (evento.mouse.x >= 220 && evento.mouse.x <= 390 && evento.mouse.y >= 480 && evento.mouse.y <= 540) {
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_flip_display();
					return instrucoes;
				}
				else if (evento.mouse.x >= 420 && evento.mouse.x <= 590 && evento.mouse.y >= 480 && evento.mouse.y <= 540) {
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_flip_display();
					return creditos;
				}
				else if (evento.mouse.x >= 610 && evento.mouse.x <= 790 && evento.mouse.y >= 480 && evento.mouse.y <= 540)
				{
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_flip_display();
					return sair;
				}
			}
		}
	}
}

void gerador_bolo_modelo(Pilha &pilha) {
	int pedido_bolo[4];
	bool ok;
	srand(time(NULL));
	pedido_bolo[0] = rand() % 5; //0 a 4 - base
	pedido_bolo[1] = rand() % 5 + 5; //5 a 9 - recheio
	pedido_bolo[2] = rand() % 5 + 10; //10 a 14 - cima
	pedido_bolo[3] = rand() % 5 + 15; //14 a 19 - cobertura
	for (int i = 0; i < 4; i++) {
		pilha.Empilha(pedido_bolo[i], ok);
	}
}

void imprime_bolo(Pilha &pilha) {
	int pedido_bolo[4];
	bool ok;
	for (int i = 3; i >= 0; i--) {
		pilha.Desempilha(pedido_bolo[i], ok);
	}
	if (pedido_bolo[0] == 0) {
		al_draw_bitmap(base1, (TELA_LARGURA / 2) - (al_get_bitmap_width(base1) / 2), 290, 0);
	}
	else if (pedido_bolo[0] == 1) {
		al_draw_bitmap(base2, (TELA_LARGURA / 2) - (al_get_bitmap_width(base2) / 2), 290, 0);
	}
	else if (pedido_bolo[0] == 2) {
		al_draw_bitmap(base3, (TELA_LARGURA / 2) - (al_get_bitmap_width(base3) / 2), 290, 0);
	}
	else if (pedido_bolo[0] == 3) {
		al_draw_bitmap(base4, (TELA_LARGURA / 2) - (al_get_bitmap_width(base4) / 2), 290, 0);
	}
	else if (pedido_bolo[0] == 4) {
		al_draw_bitmap(base5, (TELA_LARGURA / 2) - (al_get_bitmap_width(base5) / 2), 290, 0);
	}

	//recheio
	if (pedido_bolo[1] == 5) {
		al_draw_bitmap(recheio1, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio1) / 2), 260, 0);
	}
	else if (pedido_bolo[1] == 6) {
		al_draw_bitmap(recheio2, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio2) / 2), 260, 0);
	}
	else if (pedido_bolo[1] == 7) {
		al_draw_bitmap(recheio3, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio3) / 2), 260, 0);
	}
	else if (pedido_bolo[1] == 8) {
		al_draw_bitmap(recheio4, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio4) / 2), 260, 0);
	}
	else if (pedido_bolo[1] == 9) {
		al_draw_bitmap(recheio5, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio5) / 2), 260, 0);
	}

	//cima

	if (pedido_bolo[2] == 10) {
		al_draw_bitmap(cima1, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio5) / 2), 200, 0);
	}
	else if (pedido_bolo[2] == 11) {
		al_draw_bitmap(cima2, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio5) / 2), 200, 0);
	}
	else if (pedido_bolo[2] == 12) {
		al_draw_bitmap(cima3, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio5) / 2), 200, 0);
	}
	else if (pedido_bolo[2] == 13) {
		al_draw_bitmap(cima4, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio5) / 2), 200, 0);
	}
	else if (pedido_bolo[2] == 14) {
		al_draw_bitmap(cima5, (TELA_LARGURA / 2) - (al_get_bitmap_width(recheio5) / 2), 200, 0);
	}

	//cobertura
	if (pedido_bolo[3] == 15) {
		al_draw_bitmap(cobertura1, (TELA_LARGURA / 2) - (al_get_bitmap_width(cobertura1) / 2), 160, 0);
	}
	else if (pedido_bolo[3] == 16) {
		al_draw_bitmap(cobertura2, (TELA_LARGURA / 2) - (al_get_bitmap_width(cobertura2) / 2), 160, 0);
	}
	else if (pedido_bolo[3] == 17) {
		al_draw_bitmap(cobertura3, (TELA_LARGURA / 2) - (al_get_bitmap_width(cobertura3) / 2), 160, 0);
	}
	else if (pedido_bolo[3] == 18) {
		al_draw_bitmap(cobertura4, (TELA_LARGURA / 2) - (al_get_bitmap_width(cobertura4) / 2), 160, 0);
	}
	else if (pedido_bolo[3] == 19) {
		al_draw_bitmap(cobertura5, (TELA_LARGURA / 2) - (al_get_bitmap_width(cobertura5) / 2), 160, 0);
	}

	for (int i = 0; i < 4; i++) {
		pilha.Empilha(pedido_bolo[i], ok);
	}

	al_flip_display();
}

void credito(){

	int sair_creditos = 0;

	al_flip_display();
	al_draw_scaled_bitmap(creditos1, 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
	al_flip_display();
	al_register_event_source(eventos_fila, al_get_mouse_event_source());

	while (!sair_creditos)
	{
		while (!al_is_event_queue_empty(eventos_fila))
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(eventos_fila, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
			{

				if (evento.mouse.x >= 645 && evento.mouse.x <= 780 && evento.mouse.y >= 540 && evento.mouse.y <= 780)
				{
					al_flip_display();
					al_draw_scaled_bitmap(creditos2, 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
					al_flip_display();
				}
			}
			// Ou se o evento foi um clique do mouse
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				if (evento.mouse.x >= 645 && evento.mouse.x <= 780 && evento.mouse.y >= 540 && evento.mouse.y <= 780) {
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_flip_display();
					sair_creditos = 1;
				}
			}
		}
	}
}

void instrucao(){

	int sair_instrucoes = 0;

	al_flip_display();
	al_draw_scaled_bitmap(instrucoes1, 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
	al_flip_display();
	al_register_event_source(eventos_fila, al_get_mouse_event_source());

	while (!sair_instrucoes)
	{
		while (!al_is_event_queue_empty(eventos_fila))
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(eventos_fila, &evento);

			if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
			{

				if (evento.mouse.x >= 645 && evento.mouse.x <= 780 && evento.mouse.y >= 540 && evento.mouse.y <= 780)
				{
					al_flip_display();
					al_draw_scaled_bitmap(instrucoes2, 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
					al_flip_display();
				}
			}
			// Ou se o evento foi um clique do mouse
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				if (evento.mouse.x >= 645 && evento.mouse.x <= 780 && evento.mouse.y >= 540 && evento.mouse.y <= 780) {
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_flip_display();
					sair_instrucoes = 1;
				}
			}
		}
	}
}

void gera_mostra_pronto(int tempo, Pilha &pilha_gera) {
	
	//al_register_event_source(eventos_fila, al_get_timer_event_source(timer));
	al_register_event_source(timer_fila, al_get_timer_event_source(contador1));

	//al_start_timer(timer);
	al_start_timer(contador1);
	gerador_bolo_modelo(pilha_gera);
	while (tempo != 0)
	{
		//if (!al_is_event_queue_empty(eventos_fila))
		//{
		//	ALLEGRO_EVENT evento;
		//	al_wait_for_event(eventos_fila, &evento);
		//}
		if (!al_is_event_queue_empty(timer_fila))
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(timer_fila, &evento);

			if (evento.type == ALLEGRO_EVENT_TIMER)
			{
				tempo--;
			}
		}
		al_draw_scaled_bitmap(tela_bolo_modelo, 0, 0, 800, 600, 0, 0, al_get_display_width(janela), al_get_display_height(janela), 0);
		al_draw_textf(fonte, al_map_rgb(240, 0, 0), 710, 5, ALLEGRO_ALIGN_CENTRE, "%d", tempo);
		imprime_bolo(pilha_gera);
	}
}

int tempo_random() {
	srand(time(NULL));
	int tempo_bolo = rand() % 10;
	return tempo_bolo;
}

void destrutores() {
	al_destroy_bitmap(img_menu);
	al_destroy_bitmap(img_menu1);
	al_destroy_bitmap(img_menu2);
	al_destroy_bitmap(img_menu3);
	al_destroy_bitmap(img_menu4);
	al_destroy_bitmap(tela_bolo_modelo);

	al_destroy_bitmap(base1);
	al_destroy_bitmap(base2);
	al_destroy_bitmap(base3);
	al_destroy_bitmap(base4);
	al_destroy_bitmap(base5);

	al_destroy_bitmap(recheio1);
	al_destroy_bitmap(recheio2);
	al_destroy_bitmap(recheio3);
	al_destroy_bitmap(recheio4);
	al_destroy_bitmap(recheio5);

	al_destroy_bitmap(cima1);
	al_destroy_bitmap(cima2);
	al_destroy_bitmap(cima3);
	al_destroy_bitmap(cima4);
	al_destroy_bitmap(cima5);

	al_destroy_bitmap(cobertura1);
	al_destroy_bitmap(cobertura2);
	al_destroy_bitmap(cobertura3);
	al_destroy_bitmap(cobertura4);
	al_destroy_bitmap(cobertura5);

	al_destroy_bitmap(cenario);
	al_destroy_bitmap(cenario_vazio);

	al_destroy_bitmap(janela_icone);

	al_destroy_timer(timer);//
	al_destroy_timer(contador1);
	al_destroy_timer(contador2);
	al_destroy_timer(contador3);
	al_destroy_timer(contador4);

	al_destroy_bitmap(creditos1);
	al_destroy_bitmap(creditos2);
	al_destroy_bitmap(instrucoes1);
	al_destroy_bitmap(instrucoes2);

	al_destroy_display(janela);//
	al_destroy_event_queue(eventos_fila);//
}
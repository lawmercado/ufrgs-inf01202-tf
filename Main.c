#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "./codigos/Aplicacao.c"
#include "./codigos/Menu.c"
#include "./codigos/Jogo.c"

int main( )
{
    bool redesenhar = true;

    Aplicacao aplicacao;
    aplicacao.contemErros = false;

    inicializar(&aplicacao);

    if( aplicacao.contemErros )
    {
        return -1;
    }

    Menu menu;
    definirPadroesDoMenu(&menu);

    Jogo jogo;
    definirPadroesDoJogo(&jogo);

    while(aplicacao.modo != MODO_SAIR)
    {
        if( !al_is_event_queue_empty(aplicacao.filaEventos) )
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(aplicacao.filaEventos, &evento);

            switch(evento.type)
            {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                {
                    aplicacao.modo = MODO_SAIR;

                    break;
                }

                case ALLEGRO_EVENT_TIMER:
                {
                    if( evento.timer.source == aplicacao.timerFPS )
                    {
                        redesenhar = true;
                    }

                    break;
                }
            }

            switch(aplicacao.modo)
            {
                case MODO_MENU:
                {
                    processarEventoDoMenu(&menu, evento);

                    if( menu.haOpcaoSelecionada )
                    {
                        aplicacao.modo = menu.opcaoIndicada;
                        limparConteudoDaJanela();
                    }

                    break;
                }

                case MODO_JOGO:
                {
                    carregarJogoConformeNivel(&jogo, jogo.jogador.nivelAtual);
                    processarEventoDoJogo(&jogo, evento);

                    break;
                }
            }

            if( redesenhar && al_is_event_queue_empty(aplicacao.filaEventos) )
            {
                redesenhar = false;

                switch(aplicacao.modo)
                {
                    case MODO_MENU:
                    {
                        desenharMenu(&menu, &aplicacao.recursos);

                        break;
                    }

                    case MODO_JOGO:
                    {
                        desenharJogo(&jogo, &aplicacao.recursos);

                        break;
                    }
                }

                al_flip_display();
            }
        }
    }

    finalizar(&aplicacao);

    return 0;
}
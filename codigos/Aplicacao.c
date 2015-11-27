/**
 * Arquivo contendo os métodos referentes a aplicação em si
 * 
 * @author Luís Augusto Weber Mercado
 */

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "../cabecalhos/Aplicacao.h"

void inicializar( Aplicacao *aplicacao )
{
    if( !al_init() )
    {
        printf("Falha ao iniciar a Allegro.\n");
        aplicacao->contemErros = true;
    }

    if( !al_init_image_addon() )
    {
        printf("Não foi possível carregar o addon de imagens.\n");
        aplicacao->contemErros = true;
    }
    
    if( !al_install_keyboard() )
    {
        printf("Falha ao inicializar a integração com o teclado.\n");
        aplicacao->contemErros = true;
    }
    
    al_init_font_addon();
    al_init_ttf_addon();
   
    criarJanela(aplicacao);
    criarFilaDeEventos(aplicacao);
    criarTimers(aplicacao);

    al_register_event_source(aplicacao->filaEventos, al_get_keyboard_event_source());
    al_register_event_source(aplicacao->filaEventos, al_get_timer_event_source(aplicacao->timerFPS));
    al_register_event_source(aplicacao->filaEventos, al_get_timer_event_source(aplicacao->timerRelogio));
    al_register_event_source(aplicacao->filaEventos, al_get_display_event_source(aplicacao->janela));
    
    // Seta os defaults da aplicação
    aplicacao->modo = MODO_MENU;
    aplicacao->recursos = obterRecursos();
    
    al_start_timer(aplicacao->timerFPS);
    al_start_timer(aplicacao->timerRelogio);
}

void criarJanela( Aplicacao *aplicacao )
{
    aplicacao->janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if( !aplicacao->janela )
    {
        printf("Falha ao criar a janela.\n");
        aplicacao->contemErros = true;
    }

    al_set_window_title(aplicacao->janela, "Bomberman");

    limparConteudoDaJanela();
}

void limparConteudoDaJanela( )
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void criarFilaDeEventos( Aplicacao *aplicacao )
{
    aplicacao->filaEventos = al_create_event_queue();
    if( !aplicacao->filaEventos )
    {
        printf("Falha ao criar fila de eventos.\n");
        aplicacao->contemErros = true;
    }
}

void criarTimers( Aplicacao *aplicacao )
{
    aplicacao->timerFPS = al_create_timer(1.0 / FPS);
    aplicacao->timerRelogio = al_create_timer(1.0);
}

Recursos obterRecursos( )
{
    Recursos recursos;

    recursos.menuTela = al_load_bitmap("./recursos/imagens/menu/tela.png");
    recursos.menuIndicador = al_load_bitmap("./recursos/imagens/menu/indicador.png");
    
    recursos.jogoFundo = al_load_bitmap("./recursos/imagens/jogo/fundo.png");
    recursos.jogoRodape = al_load_bitmap("./recursos/imagens/jogo/rodape.png");
    recursos.jogoObstaculo = al_load_bitmap("./recursos/imagens/jogo/obstaculos/obstaculo.png");
    recursos.jogoObstaculoFixo = al_load_bitmap("./recursos/imagens/jogo/obstaculos/obstaculoFixo.png");
    recursos.jogoTelaPausa = al_load_bitmap("./recursos/imagens/jogo/telaPausa.png");
    recursos.jogadorFrenteSprite = al_load_bitmap("./recursos/imagens/jogo/bomberman/Bomberman_F_Sprite.png");
    recursos.jogadorFrenteParado = al_load_bitmap("./recursos/imagens/jogo/bomberman/Bomberman_FP.png");
    recursos.jogadorTrasSprite = al_load_bitmap("./recursos/imagens/jogo/bomberman/Bomberman_T_Sprite.png");
    recursos.jogadorTrasParado = al_load_bitmap("./recursos/imagens/jogo/bomberman/Bomberman_TP.png");
    recursos.jogadorLadoSprite = al_load_bitmap("./recursos/imagens/jogo/bomberman/Bomberman_L_Sprite.png");
    recursos.jogadorLadoParado = al_load_bitmap("./recursos/imagens/jogo/bomberman/Bomberman_LP.png");
    recursos.monstroFrenteSprite = al_load_bitmap("./recursos/imagens/jogo/monstro/Monstro_F_Sprite.png");
    recursos.monstroFrenteParado = al_load_bitmap("./recursos/imagens/jogo/monstro/Monstro_FP.png");
    recursos.monstroTrasSprite = al_load_bitmap("./recursos/imagens/jogo/monstro/Monstro_T_Sprite.png");
    recursos.monstroTrasParado = al_load_bitmap("./recursos/imagens/jogo/monstro/Monstro_TP.png");
    recursos.monstroLadoSprite = al_load_bitmap("./recursos/imagens/jogo/monstro/Monstro_L_Sprite.png");
    recursos.monstroLadoParado = al_load_bitmap("./recursos/imagens/jogo/monstro/Monstro_LP.png");
    
    recursos.fonteCantarellRegular = al_load_ttf_font("./recursos/fonte/CantarellRegular.ttf", 40, 0);
    recursos.fonteCantarellBold = al_load_ttf_font("./recursos/fonte/CantarellBold.ttf", 40, 0);
    
    return recursos;
}

void finalizar( Aplicacao* aplicacao )
{
    al_destroy_bitmap(aplicacao->recursos.menuTela);
    al_destroy_bitmap(aplicacao->recursos.menuIndicador);
    al_destroy_bitmap(aplicacao->recursos.jogoObstaculo);
    al_destroy_bitmap(aplicacao->recursos.jogoObstaculoFixo);
    al_destroy_event_queue(aplicacao->filaEventos);
    al_destroy_timer(aplicacao->timerFPS);
    al_destroy_timer(aplicacao->timerRelogio);
    al_destroy_display(aplicacao->janela);
}

ALLEGRO_COLOR obterCorDeFundo( )
{
    return al_map_rgb(25, 55, 47);
}
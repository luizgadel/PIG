
/********************************
A fun��o CriaJogo() � respons�vel pela cria��o da janela do jogo e pelos componentes audio-visuais.
Ela deve ser chamada antes de qualquer outra fun��o da biblioetac PIG.h. N�o � poss�vel criar dois
jogos no mesmo progama. Logo, somente a primeira chamada ter� efeito.
Par�metros:
nome_Janela (entrada, passagem por refer�ncia*): indica o nome que a janela do jogo mostrar� no seu t�tulo.
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
cursor_Proprio (entrada, passagem por valor): indica se o jogo utilizar� cursores (ponteiros) pr�prios para o mouse ou utilizar� o cursor padr�o.
********************************/
void PIG_criarJanela(char const *nome_Janela, int largura, int altura)
{
    if (jogo == NULL)
    {
        jogo = new CJogo(nome_Janela, 0);
        CAssetLoader::Inicia();
        CGerenciadorTimers::Inicia();
        CGerenciadorObjetos::Inicia(jogo->renderer);
        CGerenciadorParticulas::Inicia(jogo->renderer);
        CGerenciadorAnimacoes::Inicia(jogo->renderer);
        PIG_teclado = jogo->PegaTeclado();
        PIG_mouse = jogo->PegaMouse();

        srand(time(NULL));
    }
}

/********************************
A fun��o FinalizaJogo() � respons�vel por encerrar com a PIG. Ap�s tudo o jogo ser executado
a fun��o deve ser chamada e ela ir� realizar a libera��o de mem�ria dos elementos criados pela PIG.
********************************/
void PIG_finalizarJanela()
{
    CGerenciadorAnimacoes::Encerra();
    CGerenciadorParticulas::Encerra();
    CGerenciadorObjetos::Encerra();
    CGerenciadorTimers::Encerra();
    CAssetLoader::Encerra();
    delete jogo;
}

void PIG_exibirCursor(int cursorExibido)
{
    SDL_ShowCursor(cursorExibido);
}

/********************************
A fun��o pegarEvento() indica se houve algum tipo de evento desde a �ltima vez que a fun��o foi chamada.
Um evento pode ser uma tecla pressionada, um clique do mouse ou outra coisa relacionada � tela do jogo.
Maiores informa��e podem ser vistas no arquivo Tipo_PIG.h
Retorno:
O valor de retorno � um struct contendo o tipo de evento ocorrido e v�rios outros structs com informa��es espec�ficas.
********************************/
PIG_Evento PIG_pegarEvento()
{
    return jogo->PegaEvento();
}

/********************************
A fun��o PegarTecla reconhece o apertar ou soltar de uma tecla e retorna um codigo.

Se o valor retornado for positivo isso significa que a tecla foi apertada
Se o valor retornado for negativo isso significa que a tecla foi "soltada"

********************************/
int PIG_pegarTecla()
{
    if (PIG_evento.tipoEvento == EVENTO_TECLADO)
    {
        if (PIG_evento.teclado.acao == TECLA_PRESSIONADA)
        {
            return PIG_evento.teclado.tecla;
        }
        if (PIG_evento.teclado.acao == TECLA_LIBERADA)
        {
            return -PIG_evento.teclado.tecla;
        }
    }
    return 0;
}

/********************************
A fun��o PegarBotao reconhece qual botao do mouse foi clicado.

0 = bot�o esquerdo
1 = bot�o central (a rodinha)
2 = bot�o direito

Se o valor retornado for positivo isso significa que a tecla foi apertada
Se o valor retornado for negativo isso significa que a tecla foi "soltada"

********************************/
int PIG_pegarBotao()
{
    if (PIG_evento.tipoEvento == EVENTO_MOUSE)
    {
        if (PIG_evento.mouse.acao == MOUSE_PRESSIONADO)
        {
            return PIG_evento.mouse.botao;
        }
        if (PIG_evento.mouse.acao == MOUSE_LIBERADO)
        {
            return -(PIG_evento.mouse.botao);
        }
    }
    return 0;
}

/********************************
A fun��o atualizarJanela() � repons�vel por detectar todos os eventos e atualizar as variaveis internas da biblioteca.
********************************/
void PIG_atualizarJanela()
{
    PIG_evento = PIG_pegarEvento();
    PIG_botao = PIG_pegarBotao();
    PIG_tecla = PIG_pegarTecla();
}

/********************************
A fun��o IniciaDesenho() � respons�vel por preparar a janela do jogo para que os objetos gr�ficos
possam ser mostrados, al�m de desenhar a imagem de fundo do jogo, caso tenha sido definida.
Deve ser chamada repetidamente a cada novo quadro (frame) a ser desenhado.
********************************/
void PIG_iniciarDesenho()
{
    jogo->IniciaDesenho();
}

/********************************
A fun��o EncerraDesenho() � respons�vel por encerrar o desenho que foi criado, mostrando na tela do jogo.
Deve ser chamado sempre ao final do loop principal do jogo.
********************************/
void PIG_encerrarDesenho()
{
    jogo->EncerraDesenho();
}

/********************************
A fun��o getJogoRodando � repons�vel por retornar se o jogo ainda est� ativo ou n�o.
O jogo ser� encerrado se a janela do jogo for fechada, por exemplo.
Retorno:
inteiro que indica se o jogo ainda est� sendo executado (valor diferente de zero) ou n�o (valor igual a 0, zero).
********************************/
int PIG_jogoRodando()
{
    return jogo->GetRodando();
}

/********************************
A fun��o Espera() "congela" a tela do jogo por alguns milisegundos, impedindo que qualquer outro comando seja executado enquanto isso.
Par�metros:
tempo (entrada, passagem por valor): indica a quantidade de milisegundos durante a qual o jogo ser� pausado.
********************************/
void PIG_esperar(int tempo)
{
    SDL_Delay(tempo);
}

/********************************
A fun��o GetFPS() � respons�vel por calcular o valor do Frames Per Seconds (FPS), que representa a quantidade de
frames (quadros) desenhados por segundo pela PIG.
Retorno:
double que indica a m�dia de quadros desenhados por segundo.
********************************/
double PIG_pegarFPS()
{
    return jogo->GetFPS();
}

void DrawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void draw_circle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color)
{

    SDL_SetRenderDrawColor(jogo->renderer, BRANCO.r, BRANCO.r, BRANCO.r, 255);
    DrawCircle(jogo->renderer, x, y, radius);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    radius -= 1;
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void PIG_desenhaCirculo(int32_t centreX, int32_t centreY, int32_t radius, SDL_Color color)
{
    draw_circle(jogo->renderer, centreX, centreY, radius, color);
}

int SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx)
    {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0)
        {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx)
        {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety))
        {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else
        {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

int SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color)
{
    int offsetx, offsety, d;
    int status;

    SDL_SetRenderDrawColor(jogo->renderer, BRANCO.r, BRANCO.g, BRANCO.b, 255);
    SDL_RenderDrawCircle(jogo->renderer, x, y, radius);

    SDL_SetRenderDrawColor(jogo->renderer, color.r, color.g, color.b, color.a);
    radius -= 1;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx)
    {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0)
        {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx)
        {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety))
        {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else
        {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

void SDL_desenhaCirculo(int x, int y, int radius, SDL_Color color)
{
    SDL_RenderFillCircle(jogo->renderer, x, y - 2, radius, color);
}
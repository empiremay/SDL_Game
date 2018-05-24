//Using SDL, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <list>
#include <fstream>
#include <math.h>
#include "estado.hpp"
#include "inicializaciones.cpp"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* bloques[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "Version 1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
            else
            {
                //Get window surface
                gScreenSurface = SDL_GetWindowSurface( gWindow );
            }
        }
    }

    return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load personaje surface
	bloques[PERSONAJE] = loadSurface( "bloques/personaje.png" );
	if( bloques[PERSONAJE] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load personaje_inmortal surface
	bloques[PERSONAJE_INMORTAL] = loadSurface( "bloques/personaje_inmortal.png" );
	if( bloques[PERSONAJE_INMORTAL] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load personaje_espada surface
	bloques[PERSONAJE_INMORTAL_ESPADA] = loadSurface( "bloques/personaje_inmortal_espada.png" );
	if( bloques[PERSONAJE_INMORTAL_ESPADA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load personaje_escudo surface
	bloques[PERSONAJE_INMORTAL_ESCUDO] = loadSurface( "bloques/personaje_inmortal_escudo.png" );
	if( bloques[PERSONAJE_INMORTAL_ESCUDO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load personaje_espada surface
	bloques[PERSONAJE_ESPADA] = loadSurface( "bloques/personaje_espada.png" );
	if( bloques[PERSONAJE_ESPADA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load personaje_escudo surface
	bloques[PERSONAJE_ESCUDO] = loadSurface( "bloques/personaje_escudo.png" );
	if( bloques[PERSONAJE_ESCUDO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load inmortalidad surface
	bloques[INMORTALIDAD] = loadSurface( "bloques/inmortalidad.png" );
	if( bloques[INMORTALIDAD] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load fondo surface
	bloques[FONDO] = loadSurface( "bloques/fondo.png" );
	if( bloques[FONDO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load borde_vida surface
	bloques[BORDE_VIDA] = loadSurface( "bloques/borde_vida.png" );
	if( bloques[BORDE_VIDA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load barra_mana surface
	bloques[BARRA_MANA] = loadSurface( "bloques/barra_mana.png" );
	if( bloques[BARRA_MANA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load dano_1 surface
	bloques[DANO_1] = loadSurface( "bloques/danno_1.png" );
	if( bloques[DANO_1] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load dano_2 surface
	bloques[DANO_2] = loadSurface( "bloques/danno_2.png" );
	if( bloques[DANO_2] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load dano_3 surface
	bloques[DANO_3] = loadSurface( "bloques/danno_3.png" );
	if( bloques[DANO_3] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load muro surface
	bloques[MURO] = loadSurface( "bloques/muro.png" );
	if( bloques[MURO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load objetivo surface
	bloques[OBJETIVO] = loadSurface( "bloques/objetivo.png" );
	if( bloques[OBJETIVO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load vida surface
	bloques[VIDA] = loadSurface( "bloques/vida.png" );
	if( bloques[VIDA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load vida_gris surface
	bloques[VIDA_GRIS] = loadSurface( "bloques/vida_gris.png" );
	if( bloques[VIDA_GRIS] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load penalizacion surface
	bloques[PENALIZACION] = loadSurface( "bloques/penalizacion.png" );
	if( bloques[PENALIZACION] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load no_vida surface
	bloques[NO_VIDA] = loadSurface( "bloques/no_vida.png" );
	if( bloques[NO_VIDA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load estamina_1 surface
	bloques[ESTAMINA_1] = loadSurface( "bloques/estamina_1.png" );
	if( bloques[ESTAMINA_1] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load estamina_2 surface
	bloques[ESTAMINA_2] = loadSurface( "bloques/estamina_2.png" );
	if( bloques[ESTAMINA_2] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load no_estamina surface
	bloques[NO_ESTAMINA] = loadSurface( "bloques/no_estamina.png" );
	if( bloques[NO_ESTAMINA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load estamina_aux surface
	bloques[MANA_AUX] = loadSurface( "bloques/estamina_aux.png" );
	if( bloques[MANA_AUX] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load cerradura surface
	bloques[CERRADURA] = loadSurface( "bloques/cerradura.png" );
	if( bloques[CERRADURA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load cerradura surface
	bloques[CERRADURA_DOBLE] = loadSurface( "bloques/cerradura_doble.png" );
	if( bloques[CERRADURA_DOBLE] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load no_marca surface
	bloques[NO_MARCA] = loadSurface( "bloques/no_marca.png" );
	if( bloques[NO_MARCA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load llave surface
	bloques[LLAVE] = loadSurface( "bloques/llave.png" );
	if( bloques[LLAVE] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load icono_llave surface
	bloques[ICONO_LLAVE] = loadSurface( "bloques/icono_llave.png" );
	if( bloques[ICONO_LLAVE] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load curacion surface
	bloques[CURACION] = loadSurface( "bloques/curacion.png" );
	if( bloques[CURACION] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load bola surface
	bloques[BOLA] = loadSurface( "bloques/bola.png" );
	if( bloques[BOLA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load agujero surface
	bloques[AGUJERO] = loadSurface( "bloques/agujero.png" );
	if( bloques[AGUJERO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load agujero_relleno surface
	bloques[AGUJERO_RELLENO] = loadSurface( "bloques/agujero_relleno.png" );
	if( bloques[AGUJERO_RELLENO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load placa_presion surface
	bloques[PLACA_PRESION] = loadSurface( "bloques/placa_presion.png" );
	if( bloques[PLACA_PRESION] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load barra_arriba surface
	bloques[BARRA_ARRIBA] = loadSurface( "bloques/barra_arriba.png" );
	if( bloques[BARRA_ARRIBA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load barra_abajo surface
	bloques[BARRA_ABAJO] = loadSurface( "bloques/barra_abajo.png" );
	if( bloques[BARRA_ABAJO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load marca surface
	bloques[MARCA] = loadSurface( "bloques/marca.png" );
	if( bloques[MARCA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load icono_veneno surface
	bloques[ICONO_VENENO] = loadSurface( "bloques/icono_veneno.png" );
	if( bloques[ICONO_VENENO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load icono_veneno2 surface
	bloques[ICONO_VENENO2] = loadSurface( "bloques/icono_veneno2.png" );
	if( bloques[ICONO_VENENO2] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load icono_regen surface
	bloques[ICONO_REGEN] = loadSurface( "bloques/icono_regen.png" );
	if( bloques[ICONO_REGEN] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load icono_regen2 surface
	bloques[ICONO_REGEN2] = loadSurface( "bloques/icono_regen2.png" );
	if( bloques[ICONO_REGEN2] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load icono_noregen surface
	bloques[ICONO_NOREGEN] = loadSurface( "bloques/icono_noregen.png" );
	if( bloques[ICONO_NOREGEN] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

    //Load roca_arriba surface
	bloques[ROCA_ARRIBA] = loadSurface( "bloques/roca_arriba.png" );
	if( bloques[ROCA_ARRIBA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load roca_abajo surface
	bloques[ROCA_ABAJO] = loadSurface( "bloques/roca_abajo.png" );
	if( bloques[ROCA_ABAJO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load roca_izquierda surface
	bloques[ROCA_IZQUIERDA] = loadSurface( "bloques/roca_izquierda.png" );
	if( bloques[ROCA_IZQUIERDA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load roca_derecha surface
	bloques[ROCA_DERECHA] = loadSurface( "bloques/roca_derecha.png" );
	if( bloques[ROCA_DERECHA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load polvo surface
	bloques[POLVO] = loadSurface( "bloques/polvo.png" );
	if( bloques[POLVO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load placa_averiada surface
	bloques[PLACA_AVERIADA] = loadSurface( "bloques/placa_averiada.png" );
	if( bloques[PLACA_AVERIADA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load planta_veneno surface
	bloques[PLANTA_VENENO] = loadSurface( "bloques/planta_veneno.png" );
	if( bloques[PLANTA_VENENO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load planta_veneno_rota surface
	bloques[PLANTA_VENENO_ROTA] = loadSurface( "bloques/planta_veneno_rota.png" );
	if( bloques[PLANTA_VENENO_ROTA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load mana surface
	bloques[MANA] = loadSurface( "bloques/mana.png" );
	if( bloques[MANA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load g_contador surface
	bloques[G_CONTADOR] = loadSurface( "bloques/g_contador.png" );
	if( bloques[G_CONTADOR] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load g_contadormax surface
	bloques[G_CONTADORMAX] = loadSurface( "bloques/g_contadormax.png" );
	if( bloques[G_CONTADORMAX] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load esqueleto_vidaalta surface
	bloques[ESQUELETO_VIDAALTA] = loadSurface( "bloques/esqueleto_vidaalta.png" );
	if( bloques[ESQUELETO_VIDAALTA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load esqueleto_vidamedia surface
	bloques[ESQUELETO_VIDAMEDIA] = loadSurface( "bloques/esqueleto_vidamedia.png" );
	if( bloques[ESQUELETO_VIDAMEDIA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load esqueleto_vidabaja surface
	bloques[ESQUELETO_VIDABAJA] = loadSurface( "bloques/esqueleto_vidabaja.png" );
	if( bloques[ESQUELETO_VIDABAJA] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load esqueleto_muerto surface
	bloques[ESQUELETO_MUERTO] = loadSurface( "bloques/esqueleto_muerto.png" );
	if( bloques[ESQUELETO_MUERTO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load esqueleto_vidaalta_atacando surface
	bloques[ESQUELETO_VIDAALTA_ATACANDO] = loadSurface( "bloques/esqueleto_vidaalta_atacando.png" );
	if( bloques[ESQUELETO_VIDAALTA_ATACANDO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load hueso surface
	bloques[HUESO] = loadSurface( "bloques/hueso.png" );
	if( bloques[HUESO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load esqueleto_vidaalta_antesdeatacar surface
	bloques[ESQUELETO_VIDAALTA_ANTESDEATACAR] = loadSurface( "bloques/esqueleto_vidaalta_antesdeatacar.png" );
	if( bloques[ESQUELETO_VIDAALTA_ANTESDEATACAR] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load esqueleto_vidamedia_atacando surface
	bloques[ESQUELETO_VIDAMEDIA_ATACANDO] = loadSurface( "bloques/esqueleto_vidamedia_atacando.png" );
	if( bloques[ESQUELETO_VIDAMEDIA_ATACANDO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load esqueleto_vidamedia_antesdeatacar surface
	bloques[ESQUELETO_VIDAMEDIA_ANTESDEATACAR] = loadSurface( "bloques/esqueleto_vidamedia_antesdeatacar.png" );
	if( bloques[ESQUELETO_VIDAMEDIA_ANTESDEATACAR] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load esqueleto_vidabaja_atacando surface
	bloques[ESQUELETO_VIDABAJA_ATACANDO] = loadSurface( "bloques/esqueleto_vidabaja_atacando.png" );
	if( bloques[ESQUELETO_VIDABAJA_ATACANDO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load esqueleto_vidabaja_antesdeatacar surface
	bloques[ESQUELETO_VIDABAJA_ANTESDEATACAR] = loadSurface( "bloques/esqueleto_vidabaja_antesdeatacar.png" );
	if( bloques[ESQUELETO_VIDABAJA_ANTESDEATACAR] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load esqueleto_vidaalta_aturdido surface
	bloques[ESQUELETO_VIDAALTA_ATURDIDO] = loadSurface( "bloques/esqueleto_vidaalta_aturdido.png" );
	if( bloques[ESQUELETO_VIDAALTA_ATURDIDO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load esqueleto_vidamedia_aturdido surface
	bloques[ESQUELETO_VIDAMEDIA_ATURDIDO] = loadSurface( "bloques/esqueleto_vidamedia_aturdido.png" );
	if( bloques[ESQUELETO_VIDAMEDIA_ATURDIDO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load esqueleto_vidabaja_aturdido surface
	bloques[ESQUELETO_VIDABAJA_ATURDIDO] = loadSurface( "bloques/esqueleto_vidabaja_aturdido.png" );
	if( bloques[ESQUELETO_VIDABAJA_ATURDIDO] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surfaces
	for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
		SDL_FreeSurface( bloques[i] );
		bloques[i] = NULL;
	}
	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );
        if( optimizedSurface == NULL ) {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    return optimizedSurface;
}

void pintar(const estado& est) {
    SDL_Rect stretchRect;
    for(int i=0; i<est.filas(); i++) {
        for(int j=0; j<est.cols(); j++) {
            stretchRect.x=SCREEN_WIDTH*j/est.cols();
            stretchRect.y=(SCREEN_HEIGHT-barra)*i/est.filas()+barra;//SCREEN_HEIGHT*i/est.filas();
            stretchRect.h=(SCREEN_HEIGHT-barra)*(i+1)/est.filas()-stretchRect.y+barra;//SCREEN_HEIGHT*(i+1)/est.filas()-stretchRect.y;
            stretchRect.w=SCREEN_WIDTH*(j+1)/est.cols()-stretchRect.x;
            switch(est.bloque(i,j)) {
                case 0: gCurrentSurface = bloques[PERSONAJE];
                        if(est.arma()==1) {gCurrentSurface = bloques[PERSONAJE_ESPADA];}
                        if(est.arma()==2) {gCurrentSurface = bloques[PERSONAJE_ESCUDO];}
                        if(est.inmortal()) {
                            if(est.arma()==0) {gCurrentSurface = bloques[PERSONAJE_INMORTAL];}
                            if(est.arma()==1) {gCurrentSurface = bloques[PERSONAJE_INMORTAL_ESPADA];}
                            if(est.arma()==2) {gCurrentSurface = bloques[PERSONAJE_INMORTAL_ESCUDO];}
                        } break;
                case 1: gCurrentSurface = bloques[FONDO]; break;
                case 2: gCurrentSurface = bloques[DANO_1]; break;
                case 3: gCurrentSurface = bloques[DANO_2]; break;
                case 4: gCurrentSurface = bloques[DANO_3]; break;
                case 5: gCurrentSurface = bloques[OBJETIVO]; break;
                case 6: gCurrentSurface = bloques[MURO]; break;
                case 7: gCurrentSurface = bloques[CERRADURA]; break;
                case 8: gCurrentSurface = bloques[LLAVE]; break;
                case 9: gCurrentSurface = bloques[CURACION]; break;
                case 10: gCurrentSurface = bloques[BOLA]; break;
                case 11: gCurrentSurface = bloques[CERRADURA_DOBLE]; break;
                case 12: gCurrentSurface = bloques[AGUJERO]; break;
                case 13: gCurrentSurface = bloques[AGUJERO_RELLENO]; break;
                case 14: gCurrentSurface = bloques[INMORTALIDAD]; break;
                case 15: gCurrentSurface = bloques[PLACA_PRESION]; break;
                case 16: gCurrentSurface = bloques[BARRA_ARRIBA]; break;
                case 17: gCurrentSurface = bloques[BARRA_ABAJO]; break;
                case 18: gCurrentSurface = bloques[ROCA_ARRIBA]; break;
                case 19: gCurrentSurface = bloques[ROCA_ABAJO]; break;
                case 20: gCurrentSurface = bloques[ROCA_IZQUIERDA]; break;
                case 21: gCurrentSurface = bloques[ROCA_DERECHA]; break;
                case 22: gCurrentSurface = bloques[POLVO]; break;
                case 23: gCurrentSurface = bloques[PLACA_AVERIADA]; break;
                case 24: gCurrentSurface = bloques[PLANTA_VENENO]; break;
                case 25: gCurrentSurface = bloques[PLANTA_VENENO_ROTA]; break;
                case 26: gCurrentSurface = bloques[MANA]; break;
                case 50: gCurrentSurface = bloques[ESQUELETO_VIDAALTA]; break;
                case 51: gCurrentSurface = bloques[ESQUELETO_VIDAMEDIA]; break;
                case 52: gCurrentSurface = bloques[ESQUELETO_VIDABAJA]; break;
                case 53: gCurrentSurface = bloques[ESQUELETO_MUERTO]; break;
                case 54: gCurrentSurface = bloques[ESQUELETO_VIDAALTA_ATACANDO]; break;
                case 55: gCurrentSurface = bloques[HUESO]; break;
                case 56: gCurrentSurface = bloques[ESQUELETO_VIDAALTA_ANTESDEATACAR]; break;
                case 57: gCurrentSurface = bloques[ESQUELETO_VIDAMEDIA_ATACANDO]; break;
                case 58: gCurrentSurface = bloques[ESQUELETO_VIDAMEDIA_ANTESDEATACAR]; break;
                case 59: gCurrentSurface = bloques[ESQUELETO_VIDABAJA_ATACANDO]; break;
                case 60: gCurrentSurface = bloques[ESQUELETO_VIDABAJA_ANTESDEATACAR]; break;
                case 61: gCurrentSurface = bloques[ESQUELETO_VIDAALTA_ATURDIDO]; break;
                case 62: gCurrentSurface = bloques[ESQUELETO_VIDAMEDIA_ATURDIDO]; break;
                case 63: gCurrentSurface = bloques[ESQUELETO_VIDABAJA_ATURDIDO]; break;
                default: gCurrentSurface = bloques[FONDO]; break;
            }
            SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &stretchRect );
        }
    }
    //Pintar marca del teletransporte encima
    if(est.poder1() && (est.fila()!=est.filapoder1() || est.col()!=est.colpoder1())) {
        SDL_Rect marca;
        if(est.puedoTeletransportarme()) {
            gCurrentSurface=bloques[MARCA];
        }
        else {
            gCurrentSurface=bloques[NO_MARCA];
        }
        marca.x=(SCREEN_WIDTH*est.colpoder1()/est.cols())+(SCREEN_WIDTH/est.cols())/3;
        marca.y=((SCREEN_HEIGHT-barra)*est.filapoder1()/est.filas()+barra)+((SCREEN_HEIGHT-barra)/est.filas())/3;//SCREEN_HEIGHT*i/est.filas();
        marca.h=((SCREEN_HEIGHT-barra)/est.filas())/3;
        marca.w=(SCREEN_WIDTH/est.cols())/3;
        SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &marca);
    }
    //Mostrar barra con vida
    SDL_Rect vidaRect;
    double vida=est.vida()/50;
    int val=0;
    int maxvida=20; //Resolución de la vida
    gCurrentSurface=bloques[VIDA];
    int i=0;
    while(i<vida) {
        if(i<maxvida) {
            //Pintar cuadrado de vida
            vidaRect.x=val;
            vidaRect.y=10*RAZON;
            vidaRect.h=38*RAZON;
            vidaRect.w=12*RAZON;
            val+=12*RAZON;
            SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &vidaRect );
        }
        i++;
    }
    int valvida=val;
    //Separación de los cuadros de vida
    SDL_Rect cuadrovidaRect;
    gCurrentSurface=bloques[BORDE_VIDA];
    int i4=0;
    int cuadros_vida=ceil(est.vida()/100);
    int maxcuadros_vida=10;
    int val4=(240/maxcuadros_vida-1)*RAZON;
    while(i4<(cuadros_vida-1)) {
        cuadrovidaRect.x=val4;
        cuadrovidaRect.y=10*RAZON;
        cuadrovidaRect.h=6*RAZON;     //Valía 12
        cuadrovidaRect.w=2*RAZON;
        val4+=(240/maxcuadros_vida)*RAZON;
        SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &cuadrovidaRect );
        i4++;
    }
    //Mostrar penalización
    if(est.poder1()) {
        int penalizacion=abs(est.fila()-est.filapoder1())+abs(est.col()-est.colpoder1());
        int maxpenalizacion=20;
        gCurrentSurface=bloques[PENALIZACION];
        int i2=0;
        int val2=val-12*RAZON;
        while(i2<penalizacion) {
            if(i2<maxpenalizacion) {
                //Pintar cuadrado de vida
                vidaRect.x=val2;
                vidaRect.y=10*RAZON;
                vidaRect.h=38*RAZON;
                vidaRect.w=12*RAZON;
                val2-=12*RAZON;
                SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &vidaRect );
            }
            i2++;
        }
    }
    gCurrentSurface=bloques[NO_VIDA];
    for(int j=i; j<20; j++) {
        vidaRect.x=val;
        vidaRect.y=10*RAZON;
        vidaRect.h=38*RAZON;    //Valía 50
        vidaRect.w=12*RAZON;
        val+=12*RAZON;
        SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &vidaRect );
    }
    //Mostrar vida gris
    if(est.vidagris()>0) {
        int vidagris=est.vidagris()/50;
        int i3=0;
        int val3=valvida;
        gCurrentSurface=bloques[VIDA_GRIS];
        SDL_Rect vidagrisRect;
        while(i3<vidagris) {
            //Pintar cuadrado de vida gris
            vidagrisRect.x=val3;
            vidagrisRect.y=10*RAZON;
            vidagrisRect.h=38*RAZON;
            vidagrisRect.w=12*RAZON;
            val3+=12*RAZON;
            SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &vidagrisRect );
            i3++;
        }
    }
    /*SDL_Rect bordeVida;
    gCurrentSurface=bloques[BORDE_VIDA];
    bordeVida.x=0;
    bordeVida.y=10*RAZON;
    bordeVida.w=10*RAZON;
    bordeVida.h=50*RAZON;
    SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &bordeVida);*/
    //Mostrar barra de maná
    SDL_Rect manaRect;
    SDL_Rect manaauxRect;
    int manamax=est.manamax();
    int mana=est.mana();
    val=0;
    i=0;
    while(i<manamax) {
        if(mana>0) {
            gCurrentSurface=bloques[BARRA_MANA];
            mana--;
        }
        else {
            gCurrentSurface=bloques[FONDO];
        }
        manaRect.x=val;
        manaRect.y=48*RAZON;
        manaRect.h=12*RAZON;
        manaRect.w=(240/manamax)*RAZON;
        val+=(240/manamax)*RAZON;
        SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &manaRect );
        i++;
    }
    gCurrentSurface=bloques[MANA_AUX];
    val=(240/manamax-1)*RAZON;
    i=0;
    mana=est.mana();
    while(i<(mana-1)) {
        manaauxRect.x=val;
        manaauxRect.y=48*RAZON;
        manaauxRect.h=4*RAZON;     //Valía 12
        manaauxRect.w=2*RAZON;
        val+=(240/manamax)*RAZON;
        SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &manaauxRect );
        i++;
    }
    //Mostrar barra de estamina
    SDL_Rect estaminaRect;
    int estamina=est.estamina();
    bool recargando=est.recargar_estamina();
    gCurrentSurface=bloques[ESTAMINA_1];
    i=0;
    val=286*RAZON;
    while(i<estamina) {
        //Pintar cuadrado de estamina
        estaminaRect.x=val;
        estaminaRect.y=10*RAZON;
        estaminaRect.h=20*RAZON;
        estaminaRect.w=24*RAZON;
        val+=24*RAZON;
        if(recargando) {
            SDL_BlitScaled(bloques[ESTAMINA_2], NULL, gScreenSurface, &estaminaRect);
        }
        else {
            SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &estaminaRect);
        }
        i++;
    }
    gCurrentSurface=bloques[NO_ESTAMINA];
    for(int j=i; j<6; j++) {
        estaminaRect.x=val;
        estaminaRect.y=10*RAZON;
        estaminaRect.h=20*RAZON;
        estaminaRect.w=24*RAZON;
        val+=24*RAZON;
        SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &estaminaRect );
    }
    //Mostrar estamina aux
    SDL_Rect estauxRect;
    gCurrentSurface=bloques[ESTAMINA_2];
    i=0;
    val=286*RAZON;
    int estamina_aux=est.estamina_aux();
    while(i<estamina_aux) {
        estauxRect.x=val;
        estauxRect.y=10*RAZON;
        estauxRect.h=5*RAZON;
        estauxRect.w=24*RAZON;
        val+=24*RAZON;
        SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &estauxRect);
        i++;
    }
    //Mostrar icono_llave
    gCurrentSurface=bloques[ICONO_LLAVE];
    SDL_Rect llaveRect;
    llaveRect.x=286*RAZON;
    llaveRect.y=33*RAZON;
    llaveRect.h=30*RAZON;
    llaveRect.w=30*RAZON;
    SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &llaveRect );
    //Mostrar g_contador
    gCurrentSurface=bloques[FONDO];
    SDL_Rect fondoRect;
    val=340*RAZON;
    i=0;
    while(i<3) {
        fondoRect.x=val;
        fondoRect.y=33*RAZON;
        fondoRect.h=30*RAZON;
        fondoRect.w=30*RAZON;
        val+=30*RAZON;
        SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &fondoRect );
        i++;
    }
    gCurrentSurface=bloques[G_CONTADOR];
    SDL_Rect g_contadorRect;
    val=340*RAZON;
    i=0;
    if(est.g_contador()==3) {
        gCurrentSurface=bloques[G_CONTADORMAX];
    }
    while(i<est.g_contador()) {
        g_contadorRect.x=val;
        g_contadorRect.y=33*RAZON;
        g_contadorRect.h=30*RAZON;
        g_contadorRect.w=30*RAZON;
        val+=30*RAZON;
        SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &g_contadorRect );
        i++;
    }
    //Mostrar icono_veneno
    if(est.turnos_veneno()>0) {
        if(est.veneno()==1) {
            gCurrentSurface=bloques[ICONO_VENENO];
        }
        else {
            gCurrentSurface=bloques[ICONO_VENENO2];
        }
    } else {
        gCurrentSurface=bloques[FONDO];
    }
    SDL_Rect venenoRect;
    venenoRect.x=440*RAZON;
    venenoRect.y=10*RAZON;
    venenoRect.h=30*RAZON;
    venenoRect.w=30*RAZON;
    SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &venenoRect );
    //Mostrar icono_regeneracion
    if(est.turnos_regen()>0) {
        if(est.turnos_veneno()>0) {
            gCurrentSurface=bloques[ICONO_NOREGEN];
        }
        else {
            if(est.regen()==1) {
                gCurrentSurface=bloques[ICONO_REGEN];
            }
            else {
                gCurrentSurface=bloques[ICONO_REGEN2];
            }
        }
    } else {
        gCurrentSurface=bloques[FONDO];
    }
    SDL_Rect regenRect;
    regenRect.x=440*RAZON;
    regenRect.y=40*RAZON;
    regenRect.h=30*RAZON;
    regenRect.w=30*RAZON;
    SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &regenRect );
    //.......................................
    SDL_UpdateWindowSurface(gWindow);
}

bool testObjetivo(const estado& est) {
    return (est.bloque(est.objfila(), est.objcol())==0);
}

bool esValido(const estado& est, const SDL_Event& e, bool agujero_negro=false) {
    bool valido;
    estado nuevo=est;
    //Pasar o PowerUp
    if(e.key.keysym.sym==SDLK_p || e.key.keysym.sym==SDLK_f || e.key.keysym.sym==SDLK_g || e.key.keysym.sym==SDLK_h || (nuevo.gpulsada() && (e.key.keysym.sym==SDLK_UP || e.key.keysym.sym==SDLK_DOWN || e.key.keysym.sym==SDLK_RIGHT || e.key.keysym.sym==SDLK_LEFT))) {
        return true;
    }
    //ESPADA
    if(nuevo.arma()==1) {
        switch(e.key.keysym.sym) {
            case SDLK_UP: valido=nuevo.puedoatacarEsqueleto(nuevo.fila()-1, nuevo.col()); break;
            case SDLK_DOWN: valido=nuevo.puedoatacarEsqueleto(nuevo.fila()+1, nuevo.col()); break;
            case SDLK_RIGHT: valido=nuevo.puedoatacarEsqueleto(nuevo.fila(), nuevo.col()+1); break;
            case SDLK_LEFT: valido=nuevo.puedoatacarEsqueleto(nuevo.fila(), nuevo.col()-1); break;
            default: valido=false; break;
        }
        if(nuevo.estamina()==0) {return false;}
        return valido;
    }
    //ESCUDO
    if(nuevo.arma()==2) {
        switch(e.key.keysym.sym) {
            case SDLK_UP: valido=nuevo.puedoaturdirEsqueleto(nuevo.fila()-1, nuevo.col()); break;
            case SDLK_DOWN: valido=nuevo.puedoaturdirEsqueleto(nuevo.fila()+1, nuevo.col()); break;
            case SDLK_RIGHT: valido=nuevo.puedoaturdirEsqueleto(nuevo.fila(), nuevo.col()+1); break;
            case SDLK_LEFT: valido=nuevo.puedoaturdirEsqueleto(nuevo.fila(), nuevo.col()-1); break;
            default: valido=false; break;
        }
        if(nuevo.estamina()==0) {return false;}
        return valido;
    }
    //......
    switch(e.key.keysym.sym) {
        case SDLK_UP: valido=est.fila()>0;
                      if(valido) {
                            nuevo.fila()=est.fila()-1;
                      }
                      break;
        case SDLK_DOWN: valido=est.fila()<(est.filas()-1);
                        if(valido) {
                            nuevo.fila()=est.fila()+1;
                        }
                        break;
        case SDLK_RIGHT: valido=est.col()<(est.cols()-1);
                         if(valido) {
                            nuevo.col()=est.col()+1;
                         }
                         break;
        case SDLK_LEFT: valido=est.col()>0;
                        if(valido) {
                            nuevo.col()=est.col()-1;
                        }
                        break;
        default: valido=false; break;
    }
    switch(nuevo.bloque(nuevo.fila(), nuevo.col())) {
        case 6: valido=false; break;
        case 7: if(est.llaves()<=0) {valido=false;} break;
        case 10: switch(e.key.keysym.sym) {
                    case SDLK_UP: valido=(nuevo.fila()>0 && (nuevo.bloque(nuevo.fila()-1, nuevo.col())==1 || nuevo.bloque(nuevo.fila()-1, nuevo.col())==12 || nuevo.bloque(nuevo.fila()-1, nuevo.col())==13 || nuevo.bloque(nuevo.fila()-1, nuevo.col())==17 || nuevo.bloque(nuevo.fila()-1, nuevo.col())==2 || nuevo.bloque(nuevo.fila()-1, nuevo.col())==3 || nuevo.bloque(nuevo.fila()-1, nuevo.col())==4 || nuevo.bloque(nuevo.fila()-1, nuevo.col())==53 || nuevo.bloque(nuevo.fila()-1, nuevo.col())==22 || nuevo.bloque(nuevo.fila()-1, nuevo.col())==24 || nuevo.bloque(nuevo.fila()-1, nuevo.col())==25 || nuevo.bloque(nuevo.fila()-1, nuevo.col())==26)); break;
                    case SDLK_DOWN: valido=(nuevo.fila()<(nuevo.filas()-1) && (nuevo.bloque(nuevo.fila()+1, nuevo.col())==1 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==12 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==13 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==17 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==2 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==3 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==4 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==53 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==22 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==24 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==25 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==26)); break;
                    case SDLK_RIGHT: valido=(nuevo.col()<(nuevo.cols()-1) && (nuevo.bloque(nuevo.fila(), nuevo.col()+1)==1 || nuevo.bloque(nuevo.fila(), nuevo.col()+1)==12 || nuevo.bloque(nuevo.fila(), nuevo.col()+1)==13 || nuevo.bloque(nuevo.fila(), nuevo.col()+1)==17 || nuevo.bloque(nuevo.fila(), nuevo.col()+1)==2 || nuevo.bloque(nuevo.fila(), nuevo.col()+1)==3 || nuevo.bloque(nuevo.fila(), nuevo.col()+1)==4 || nuevo.bloque(nuevo.fila(), nuevo.col()+1)==53 || nuevo.bloque(nuevo.fila(), nuevo.col()+1)==22 || nuevo.bloque(nuevo.fila(), nuevo.col()+1)==24 || nuevo.bloque(nuevo.fila(), nuevo.col()+1)==25 || nuevo.bloque(nuevo.fila(), nuevo.col()+1)==26)); break;
                    case SDLK_LEFT: valido=(nuevo.col()>0 && (nuevo.bloque(nuevo.fila(), nuevo.col()-1)==1 || nuevo.bloque(nuevo.fila(), nuevo.col()-1)==12 || nuevo.bloque(nuevo.fila(), nuevo.col()-1)==13 || nuevo.bloque(nuevo.fila(), nuevo.col()-1)==17 || nuevo.bloque(nuevo.fila(), nuevo.col()-1)==2 || nuevo.bloque(nuevo.fila(), nuevo.col()-1)==3 || nuevo.bloque(nuevo.fila(), nuevo.col()-1)==4 || nuevo.bloque(nuevo.fila(), nuevo.col()-1)==53 || nuevo.bloque(nuevo.fila(), nuevo.col()-1)==22 || nuevo.bloque(nuevo.fila(), nuevo.col()-1)==24 || nuevo.bloque(nuevo.fila(), nuevo.col()-1)==25 || nuevo.bloque(nuevo.fila(), nuevo.col()-1)==26)); break;
                } break;
        case 11: if(est.llaves()<=0) {valido=false;} break;
        case 12:
        case 16:
        case 18:
        case 19:
        case 20:
        case 21:
        case 50:
        case 51:
        case 52:
        case 54:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63: valido=false; break;
    }
    if(agujero_negro) {
        if(nuevo.anillo()<est.anillo()) {
            valido=false;
        }
    }
    return valido;
}

bool atrapado(const estado& est) {
    bool atrapado=false;
    estado copia=est;
    copia.arma()=0;
    if(copia.estamina()==0 || copia.recargar_estamina()) {
        SDL_Event e;
        int mov_invalidos=0;
        e.key.keysym.sym=SDLK_RIGHT;
        if(!esValido(copia, e)) {
            ++mov_invalidos;
        }
        e.key.keysym.sym=SDLK_LEFT;
        if(!esValido(copia, e)) {
            ++mov_invalidos;
        }
        e.key.keysym.sym=SDLK_UP;
        if(!esValido(copia, e)) {
            ++mov_invalidos;
        }
        e.key.keysym.sym=SDLK_DOWN;
        if(!esValido(copia, e)) {
            ++mov_invalidos;
        }
        if(mov_invalidos==4) {
            atrapado=true;
        }
    }
    return atrapado;
}

bool atrapado_parcial(const estado& est) {  //Como atrapado, pero no importa el nivel de estamina
    bool atrapado=false;
    estado copia=est;
    copia.arma()=0;
    SDL_Event e;
    int mov_invalidos=0;
    e.key.keysym.sym=SDLK_RIGHT;
    if(!esValido(copia, e)) {
        ++mov_invalidos;
    }
    e.key.keysym.sym=SDLK_LEFT;
    if(!esValido(copia, e)) {
        ++mov_invalidos;
    }
    e.key.keysym.sym=SDLK_UP;
    if(!esValido(copia, e)) {
        ++mov_invalidos;
    }
    e.key.keysym.sym=SDLK_DOWN;
    if(!esValido(copia, e)) {
        ++mov_invalidos;
    }
    if(mov_invalidos==4) {
        atrapado=true;
    }
    return atrapado;
}

estado aplicaVeneno(const estado& est) {    //Aplicar veneno, regeneración, etc
    estado nuevo=est;
    if(nuevo.turnos_veneno()==0) {
        nuevo.veneno()=0;
    }
    else {
        nuevo.turnos_veneno()--;
    }
    if(nuevo.turnos_regen()==0) {
        nuevo.regen()=0;
    }
    else {
        nuevo.turnos_regen()--;
    }
    if(nuevo.veneno()>0) {
        if(nuevo.vida()<=0) {
            return nuevo;
        }
        nuevo.modificar_vida(nuevo.vida()-50*nuevo.veneno(), true);
        if(nuevo.vida()<=0) {
            nuevo.vida()=50;
        }
    }
    if(nuevo.regen()>0 && nuevo.veneno()==0) {
        nuevo.modificar_vida(nuevo.vida()+100*nuevo.regen());
    }
    //Ajustar vida gris
    if(nuevo.vida()+nuevo.vidagris()>1000) {
        nuevo.vidagris()=1000-nuevo.vida();
    }
    //Regenerar vida gris
    if(!atrapado_parcial(nuevo)) {
        if(nuevo.vidagris()>0) {
            if(nuevo.vidagris()==50) {
                nuevo.modificar_vida(nuevo.vida()+50);
                nuevo.vidagris()-=50;
            }
            else {
                nuevo.modificar_vida(nuevo.vida()+100);
                nuevo.vidagris()-=100;
            }
        }
    }
    return nuevo;
}

estado aplicaOperador(const estado& est, const SDL_Event& e, bool& consumir_turno, bool bandera=true) {
    estado nuevo=est;
    nuevo.tiempo()++;
    double extra=0;
    bool doble_cerradura=false;
    //PowerUp
    if(e.key.keysym.sym==SDLK_f || e.key.keysym.sym==SDLK_g || e.key.keysym.sym==SDLK_h || (nuevo.gpulsada() && (e.key.keysym.sym==SDLK_UP || e.key.keysym.sym==SDLK_DOWN || e.key.keysym.sym==SDLK_RIGHT || e.key.keysym.sym==SDLK_LEFT))) {
        //Ver que pueda lanzar powerup
        if(nuevo.powerupon()) {
            //Casos en los que no hay maná suficiente
            if((e.key.keysym.sym==SDLK_f && !nuevo.poder1() && nuevo.mana()==0) || (nuevo.mana()<2 && e.key.keysym.sym==SDLK_h) || (e.key.keysym.sym==SDLK_g && nuevo.g_contador()<3 && nuevo.mana()==0)) {
                consumir_turno=false;
                cout << "OUT OF MANA" << endl;
            }
            else {
                switch(e.key.keysym.sym) {
                    case SDLK_f: nuevo.powerUp(1, consumir_turno); break;
                    case SDLK_g: if(nuevo.gpulsada()) {
                                    //Quitar marca de g
                                    nuevo.gpulsada()=false;
                                    consumir_turno=false;
                                 }
                                 else {
                                    if(nuevo.g_contador()==3) {
                                        //Disparar en todas las direcciones
                                        bool consumir=false;
                                        nuevo.powerUp(2, consumir_turno, 1);
                                        if(consumir_turno) {
                                            consumir=true;
                                        }
                                        nuevo.powerUp(2, consumir_turno, 2);
                                        if(consumir_turno) {
                                            consumir=true;
                                        }
                                        nuevo.powerUp(2, consumir_turno, 3);
                                        if(consumir_turno) {
                                            consumir=true;
                                        }
                                        nuevo.powerUp(2, consumir_turno, 4);
                                        if(consumir_turno) {
                                            consumir=true;
                                        }
                                        consumir_turno=consumir;
                                        nuevo.gpulsada()=false;
                                        //Actualizar g_contador
                                        nuevo.g_contador()=0;
                                        nuevo.powerupon()=false;
                                    }
                                    else {
                                        //Marcar g y, posteriormente, leerá una dirección
                                        nuevo.gpulsada()=true;
                                        consumir_turno=false;
                                    }
                                 } break;
                    case SDLK_UP: nuevo.powerUp(2, consumir_turno, 1);
                                  nuevo.gpulsada()=false;
                                  //Actualizar g_contador
                                  if(consumir_turno) {
                                    nuevo.mana()--;
                                    nuevo.g_contador()++;
                                    nuevo.powerupon()=false;
                                  }
                                  break;
                    case SDLK_DOWN: nuevo.powerUp(2, consumir_turno, 2);
                                    nuevo.gpulsada()=false;
                                    //Actualizar g_contador
                                    if(consumir_turno) {
                                      nuevo.mana()--;
                                      nuevo.g_contador()++;
                                      nuevo.powerupon()=false;
                                    }
                                    break;
                    case SDLK_LEFT: nuevo.powerUp(2, consumir_turno, 3);
                                    nuevo.gpulsada()=false;
                                    //Actualizar g_contador
                                    if(consumir_turno) {
                                      nuevo.mana()--;
                                      nuevo.g_contador()++;
                                      nuevo.powerupon()=false;
                                    }
                                    break;
                    case SDLK_RIGHT: nuevo.powerUp(2, consumir_turno, 4);
                                     nuevo.gpulsada()=false;
                                     //Actualizar g_contador
                                     if(consumir_turno) {
                                       nuevo.mana()--;
                                       nuevo.g_contador()++;
                                       nuevo.powerupon()=false;
                                     }
                                     break;
                    case SDLK_h: nuevo.powerUp(3, consumir_turno);
                                 nuevo.powerupon()=false;
                                 break;
                }
            }
        }
        else {
            consumir_turno=false;
            cout << "POWERUP USADO" << endl;
        }
        return nuevo;
    }
    //Pasar
    if(nuevo.pasar()) {
        nuevo.pasar()=false;
        return nuevo;
    }
    //Actualizar estamina
    if(nuevo.recargar_estamina()) {
        nuevo.estamina()=nuevo.estamina()+1;
        if(nuevo.estamina()==6) {
            nuevo.recargar_estamina()=false;
            nuevo.cambiar()=true;
        }
    }
    //ESPADA
    if(nuevo.arma()==1) {
        switch(e.key.keysym.sym) {
            case SDLK_UP: nuevo.atacarEsqueleto(nuevo.fila()-1, nuevo.col()); break;
            case SDLK_DOWN: nuevo.atacarEsqueleto(nuevo.fila()+1, nuevo.col()); break;
            case SDLK_RIGHT: nuevo.atacarEsqueleto(nuevo.fila(), nuevo.col()+1); break;
            case SDLK_LEFT: nuevo.atacarEsqueleto(nuevo.fila(), nuevo.col()-1); break;
        }
        if(nuevo.estamina()==0 && !nuevo.recargar_estamina()) {
            nuevo.cambiar()=false;
            nuevo.arma()=0;
            nuevo.recargar_estamina()=true;
        }
        //Resetear estamina auxiliar
        nuevo.estamina_aux()=0;
        //...
        return nuevo;
    }
    //ESCUDO
    if(nuevo.arma()==2) {
        switch(e.key.keysym.sym) {
            case SDLK_UP: nuevo.aturdirEsqueleto(nuevo.fila()-1, nuevo.col()); break;
            case SDLK_DOWN: nuevo.aturdirEsqueleto(nuevo.fila()+1, nuevo.col()); break;
            case SDLK_RIGHT: nuevo.aturdirEsqueleto(nuevo.fila(), nuevo.col()+1); break;
            case SDLK_LEFT: nuevo.aturdirEsqueleto(nuevo.fila(), nuevo.col()-1); break;
        }
        if(nuevo.estamina()==0) {
            nuevo.cambiar()=false;
            nuevo.arma()=0;
            nuevo.recargar_estamina()=true;
        }
        //Resetear estamina auxiliar
        nuevo.estamina_aux()=0;
        //...
        return nuevo;
    }
    if(nuevo.estamina()<6 && !nuevo.recargar_estamina()) {
        //Incrementar estamina auxiliar
        if(nuevo.estamina_aux()==5) {
            nuevo.estamina()=6;
            nuevo.estamina_aux()=0;
        }
        else {
            nuevo.estamina_aux()++;
        }
    }
    //....
    int antbloque=est.bloque();
    //....
    switch(e.key.keysym.sym) {
        case SDLK_UP: nuevo.fila()=nuevo.fila()-1; break;
        case SDLK_DOWN: nuevo.fila()=nuevo.fila()+1; break;
        case SDLK_RIGHT: nuevo.col()=nuevo.col()+1; break;
        case SDLK_LEFT: nuevo.col()=nuevo.col()-1; break;
    }
    //....
    nuevo.bloque()=nuevo.bloque(nuevo.fila(), nuevo.col());
    //....
    nuevo.filaant()=est.fila(); nuevo.colaant()=est.col();
    switch(nuevo.bloque(nuevo.fila(), nuevo.col())) {
        case 2: nuevo.modificar_vida(nuevo.vida()-100); break;
        case 3: nuevo.modificar_vida(nuevo.vida()-200); break;
        case 4: nuevo.modificar_vida(nuevo.vida()-300); break;
        case 7: if(nuevo.llaves()!=0) nuevo.llaves()--; break;
        case 8: nuevo.llaves()++; break;
        case 9: /*extra=-0.33*est.vida()+333;
                nuevo.modificar_vida(nuevo.vida()+extra);
                for(int i=100; i<=1000; i+=100) {
                    if(nuevo.vida()<i && nuevo.vida()>i-100) nuevo.modificar_vida(i);
                }
                if(nuevo.vida()>1000) {nuevo.modificar_vida(1000);}*/
                nuevo.regen()=1;
                nuevo.turnos_regen()=2;
                //Si estas por debajo del 50% de la vida, añadir un turno de regeneración
                if(nuevo.vida()<500) {
                    nuevo.turnos_regen()++;
                }
                break;
        case 10: switch(e.key.keysym.sym) {
                    case SDLK_UP: if(nuevo.bloque(nuevo.fila()-1, nuevo.col())==13 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==2 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==3 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==4) {
                                  //Hay objeto, guardar objeto
                                    nuevo.filaagujero()=nuevo.fila()-1;
                                    nuevo.colagujero()=nuevo.col();
                                    nuevo.objeto()=nuevo.bloque(nuevo.fila()-1, nuevo.col());
                                    if(nuevo.objeto()==2 || nuevo.objeto()==3 || nuevo.objeto()==4) {
                                        nuevo.objeto()=1;
                                    }
                                  }
                                  if(nuevo.bloque(nuevo.fila()-1, nuevo.col())==12) {
                                    nuevo.bloque(nuevo.fila()-1, nuevo.col())=13;
                                  }
                                  else {
                                    nuevo.bloque(nuevo.fila()-1, nuevo.col())=10;
                                  } break;
                    case SDLK_DOWN:   if(nuevo.bloque(nuevo.fila()+1, nuevo.col())==13 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==2 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==3 || nuevo.bloque(nuevo.fila()+1, nuevo.col())==4) {
                                      //Hay objeto, guardar objeto
                                        nuevo.filaagujero()=nuevo.fila()+1;
                                        nuevo.colagujero()=nuevo.col();
                                        nuevo.objeto()=nuevo.bloque(nuevo.fila()+1, nuevo.col());
                                        if(nuevo.objeto()==2 || nuevo.objeto()==3 || nuevo.objeto()==4) {
                                            nuevo.objeto()=1;
                                        }
                                      }
                                      if(nuevo.bloque(nuevo.fila()+1, nuevo.col())==12) {
                                        nuevo.bloque(nuevo.fila()+1, nuevo.col())=13;
                                      }
                                      else {
                                        nuevo.bloque(nuevo.fila()+1, nuevo.col())=10;
                                      } break;
                    case SDLK_RIGHT:  if(nuevo.bloque(nuevo.fila(), nuevo.col()+1)==13 || nuevo.bloque(nuevo.fila(), nuevo.col()+1)==2 || nuevo.bloque(nuevo.fila(), nuevo.col()+1)==3 || nuevo.bloque(nuevo.fila(), nuevo.col()+1)==4) {
                                      //Hay objeto, guardar objeto
                                        nuevo.filaagujero()=nuevo.fila();
                                        nuevo.colagujero()=nuevo.col()+1;
                                        nuevo.objeto()=nuevo.bloque(nuevo.fila(), nuevo.col()+1);
                                        if(nuevo.objeto()==2 || nuevo.objeto()==3 || nuevo.objeto()==4) {
                                            nuevo.objeto()=1;
                                        }
                                      }
                                      if(nuevo.bloque(nuevo.fila(), nuevo.col()+1)==12) {
                                        nuevo.bloque(nuevo.fila(), nuevo.col()+1)=13;
                                      }
                                      else {
                                        nuevo.bloque(nuevo.fila(), nuevo.col()+1)=10;
                                      } break;
                    case SDLK_LEFT:   if(nuevo.bloque(nuevo.fila(), nuevo.col()-1)==13 || nuevo.bloque(nuevo.fila(), nuevo.col()-1)==2 || nuevo.bloque(nuevo.fila(), nuevo.col()-1)==3 || nuevo.bloque(nuevo.fila(), nuevo.col()-1)==4) {
                                      //Hay objeto, guardar objeto
                                        nuevo.filaagujero()=nuevo.fila();
                                        nuevo.colagujero()=nuevo.col()-1;
                                        nuevo.objeto()=nuevo.bloque(nuevo.fila(), nuevo.col()-1);
                                        if(nuevo.objeto()==2 || nuevo.objeto()==3 || nuevo.objeto()==4) {
                                            nuevo.objeto()=1;
                                        }
                                      }
                                      if(nuevo.bloque(nuevo.fila(), nuevo.col()-1)==12) {
                                        nuevo.bloque(nuevo.fila(), nuevo.col()-1)=13;
                                      }
                                      else {
                                        nuevo.bloque(nuevo.fila(), nuevo.col()-1)=10;
                                      } break;
                } break;
        case 11: if(nuevo.llaves()>=1) {doble_cerradura=true; nuevo.llaves()--;} break;
        case 14: nuevo.inmortal()=true; break;
        case 24: nuevo.veneno()=1;
                 nuevo.turnos_veneno()=5; break;    //Aplicar veneno durante varios turnos
        case 26: if(nuevo.mana()<nuevo.manamax()) {
                    nuevo.mana()++;
                    nuevo.recogermana()=true;
                 }
                 else {
                    nuevo.recogermana()=false;
                 } break;
    }
    if(nuevo.inmortal()) {
        nuevo.cont_invencibilidad()++;
        if(nuevo.cont_invencibilidad()==6) {    //6 equivale a 5 turnos con invencibilidad
            nuevo.inmortal()=false;
        }
    }
    if(doble_cerradura) {
        nuevo.bloque(nuevo.fila(), nuevo.col())=7;
        nuevo.fila()=est.fila();
        nuevo.col()=est.col();
        return nuevo;
    }
    if(!bandera) {
        nuevo.bloque(est.fila(), est.col())=1;
        nuevo.bloque(nuevo.fila(), nuevo.col())=0;
        return nuevo;
    }
    switch(antbloque) {
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 14:
        case 26: if(nuevo.recogermana()) {
                    nuevo.bloque(est.fila(), est.col())=1;
                 }
                 else {
                    nuevo.bloque(est.fila(), est.col())=26;
                 } break;
        case 24: nuevo.bloque(est.fila(), est.col())=25; break; //Al pisar una planta, se rompe y se convierte en planta rota
        default: nuevo.bloque(est.fila(), est.col())=antbloque; break;
    }
    if(nuevo.rellenaragujero()) {   //Rellenar objeto, no agujero
        nuevo.bloque(est.fila(), est.col())=nuevo.objeto();
        nuevo.rellenaragujero()=false;
    }
    nuevo.bloque(nuevo.fila(), nuevo.col())=0;
    //Comprobar si está encima de un agujero
    if(nuevo.fila()==nuevo.filaagujero() && nuevo.col()==nuevo.colagujero()) {
        nuevo.rellenaragujero()=true;
    }
    return nuevo;
}

void cambiaArma(estado& est) {
    if(est.cambiar()) {
        if(est.arma()==2) {
            est.arma()=0;
        } else {
            est.arma()++;
        }
    }
}

int** begin_level(string nivel, int& filas, int& cols) {
    ifstream lectura("niveles/"+nivel+".txt");
    string cadena;
    int ncols=0;
    int nfilas=0;
    bool c=false;
    std::list<int> valores;
    while(!lectura.eof()) {
        lectura >> cadena;
        if(cadena[0]!='#') {
            valores.push_back(atoi(cadena.c_str()));
        }
        if(cadena[0]=='#') {
            c=true;  //Parar de contar columnas
            ++nfilas;
        }
        if(!c) {++ncols;}
    }
    lectura.close();
    int** matriz=new int*[nfilas];
    for(int i=0; i<nfilas; i++) {
        matriz[i]=new int[ncols];
    }
    std::list<int>::iterator it=valores.begin();
    for(int i=0; i<nfilas; i++) {
        for(int j=0; j<ncols; j++) {
            matriz[i][j]=(*it);
            ++it;
        }
    }
    filas=nfilas;
    cols=ncols;
    return matriz;
}

int main(int argc, char* args[]) {
	//Start up SDL and create window
	if(!init()) {
		printf( "Failed to initialize!\n" );
	}
	else {
		//Load media
		if(!loadMedia()) {
			printf( "Failed to load media!\n" );
		}
		else {
			//Main loop flag
			bool quit = false;
            srand(time(NULL));
            //Inicializar Nivel 1
            int filas=0, cols=0;
            int** matriz=begin_level("nivel1", filas, cols);
            estado nivel1(matriz, filas, cols, 1000, 0, 0);
            //
            //............................
            //Inicializar Nivel 2.........
            int** matriz2=new int*[6];
            for(int i=0; i<6; i++) {
                matriz2[i]=new int[6];
            }
            matriz2[0][0]=1; matriz2[0][1]=1; matriz2[0][2]=1; matriz2[0][3]=1; matriz2[0][4]=1; matriz2[0][5]=0;
            matriz2[1][0]=1; matriz2[1][1]=1; matriz2[1][2]=1; matriz2[1][3]=1; matriz2[1][4]=1; matriz2[1][5]=1;
            matriz2[2][0]=1; matriz2[2][1]=1; matriz2[2][2]=1; matriz2[2][3]=1; matriz2[2][4]=1; matriz2[2][5]=1;
            matriz2[3][0]=1; matriz2[3][1]=1; matriz2[3][2]=1; matriz2[3][3]=1; matriz2[3][4]=1; matriz2[3][5]=1;
            matriz2[4][0]=1; matriz2[4][1]=1; matriz2[4][2]=1; matriz2[4][3]=1; matriz2[4][4]=1; matriz2[4][5]=1;
            matriz2[5][0]=1; matriz2[5][1]=1; matriz2[5][2]=1; matriz2[5][3]=1; matriz2[5][4]=1; matriz2[5][5]=5;
            estado nivel2(matriz2, 6, 6, 600, 3, 0);
            //............................
            //Inicializar Nivel 3.........
            filas=0, cols=0;
            int** matriz3=begin_level("nivel3", filas, cols);
            estado nivel3(matriz3, filas, cols, 700, 0, 0);
            //............................
            //Inicializar Nivel 4.........
            int** matriz4=new int*[7];
            for(int i=0; i<7; i++) {
                matriz4[i]=new int[7];
            }
            matriz4[0][0]=0; matriz4[0][1]=1; matriz4[0][2]=1; matriz4[0][3]=1; matriz4[0][4]=1; matriz4[0][5]=1; matriz4[0][6]=1;
            matriz4[1][0]=1; matriz4[1][1]=1; matriz4[1][2]=6; matriz4[1][3]=1; matriz4[1][4]=1; matriz4[1][5]=1; matriz4[1][6]=1;
            matriz4[2][0]=1; matriz4[2][1]=1; matriz4[2][2]=1; matriz4[2][3]=1; matriz4[2][4]=1; matriz4[2][5]=1; matriz4[2][6]=1;
            matriz4[3][0]=1; matriz4[3][1]=1; matriz4[3][2]=1; matriz4[3][3]=5; matriz4[3][4]=1; matriz4[3][5]=1; matriz4[3][6]=1;
            matriz4[4][0]=1; matriz4[4][1]=1; matriz4[4][2]=1; matriz4[4][3]=1; matriz4[4][4]=1; matriz4[4][5]=1; matriz4[4][6]=1;
            matriz4[5][0]=1; matriz4[5][1]=1; matriz4[5][2]=1; matriz4[5][3]=1; matriz4[5][4]=1; matriz4[5][5]=1; matriz4[5][6]=1;
            matriz4[6][0]=1; matriz4[6][1]=1; matriz4[6][2]=1; matriz4[6][3]=1; matriz4[6][4]=1; matriz4[6][5]=1; matriz4[6][6]=1;
            estado nivel4(matriz4, 7, 7, 1000);
            //............................
            estado actual=nivel1;     //Ctor. de copia
            estado nuevo=actual;
            int nivel=1;
            int tiempo_dentro=0;    //Nivel Agujero Negro
            bool consumir_turno=true;
            esqueleto skeleton(300, 2);
            esqueleto skeleton2(200, 2);
            placa presion(1, 0, 5);
            placa presion2(2, 4, 5);
            placa presion3(2, 0, 3);
            placa presion4(2, 3, 1);
            //............................
            actual.anadir(skeleton, 5, 4);
            /*actual.anadir(skeleton, 4, 3);
            actual.anadir(skeleton, 2, 3);
            actual.anadir(skeleton, 3, 2);
            actual.anadir(skeleton, 3, 4);*/
            actual.anadir(presion, skeleton, 5, 5, true);
            //actual.anadir(skeleton, 4, 4);
            //actual.anadir(skeleton2, 3, 2);
            //actual.anadirBarra(presion3, true, 5, 0);
            //actual.anadirBarra(presion4, true, 2, 5);
            pintar(actual);

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit ) {
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 ) {
					//User requests quit
					if( e.type == SDL_QUIT ) {
						quit = true;
					}
					//User presses a key
					else {
                        if(actual.vida()<=0) {
                            std::cout << "HAS MUERTO. FIN DEL JUEGO" << std::endl;
                            return 0;
                        }
                        if(testObjetivo(actual)) {
                            nivel++;
                            if(nivel%2!=0) {    //Incrementar en una unidad el maná cada dos niveles
                                actual.manamax()++;
                            }
                            switch(nivel) {
                                case 2: nivel2.g_contador()=actual.g_contador();
                                        nivel2.llaves()=actual.llaves();
                                        nivel2.mana()=actual.mana();
                                        nivel2.manamax()=actual.manamax();
                                        actual=nivel2;
                                        //actual.anadir(skeleton, 1, 5);
                                        //actual.anadir(skeleton, 3, 3);
                                        //actual.anadir(skeleton, 0, 1);
                                        //actual.anadirBarra(presion, true, 0, 0);
                                        //actual.anadirBarra(presion2, true, 3, 1);
                                        ////actual.anadir(presion2, skeleton1, 4, 0);
                                        pintar(actual);
                                        break;
                                case 3: nivel3.g_contador()=actual.g_contador();
                                        nivel3.llaves()=actual.llaves();
                                        nivel3.mana()=actual.mana();
                                        nivel3.manamax()=actual.manamax();
                                        actual=nivel3;
                                        pintar(actual);
                                        break;
                                case 4: nivel4.g_contador()=actual.g_contador();
                                        nivel4.llaves()=actual.llaves();
                                        nivel4.mana()=actual.mana();
                                        nivel4.manamax()=actual.manamax();
                                        actual=nivel4;
                                        pintar(nivel4);
                                        break;
                                case 5: std::cout << "HAS GANADO. FIN DEL JUEGO" << std::endl;
                                        return 0;
                            }
                        }
                        if( e.type == SDL_KEYDOWN ) {
                            if(e.key.keysym.sym==SDLK_a) {
                                cambiaArma(actual);
                                pintar(actual);
                            }
                            else {
                                if(e.key.keysym.sym==SDLK_p) {
                                    actual.pasar()=true;
                                }
                                switch(nivel) {
                                    case 1: if(esValido(actual, e)) {
                                                nuevo=aplicaOperador(actual, e, consumir_turno);
                                                if(consumir_turno) {
                                                    //Actualizar rocas
                                                    nuevo.actualizarRocas();
                                                    //Actualizar esqueletos
                                                    nuevo.actualizarEsqueletos();
                                                    //Aplicar efectos de curación
                                                    nuevo=aplicaVeneno(nuevo);
                                                }
                                                //Actualizar placas de presion
                                                nuevo.actualizarPlacas();
                                                if(atrapado(nuevo)) {
                                                    nuevo.aplicarVidaGris();
                                                }
                                                //....
                                                consumir_turno=true;
                                                actual=nuevo;
                                                pintar(actual);
                                            } break;
                                    case 2: if(esValido(actual, e)) {
                                                nuevo=aplicaOperador(actual, e, consumir_turno);
                                                if(consumir_turno) {
                                                    //Actualizar rocas
                                                    nuevo.actualizarRocas();
                                                    //Actualizar esqueletos
                                                    nuevo.actualizarEsqueletos();
                                                    //Aplicar efectos de curación
                                                    nuevo=aplicaVeneno(nuevo);
                                                }
                                                //Actualizar placas de presion
                                                nuevo.actualizarPlacas();
                                                //....
                                                consumir_turno=true;
                                                actual=nuevo;
                                                pintar(actual);
                                            } break;
                                    case 3: if(esValido(actual, e)) {
                                                nuevo=aplicaOperador(actual, e, consumir_turno);
                                                if(consumir_turno) {
                                                    //Actualizar rocas
                                                    nuevo.actualizarRocas();
                                                    //Actualizar esqueletos
                                                    nuevo.actualizarEsqueletos();
                                                    //Aplicar efectos de curación
                                                    nuevo=aplicaVeneno(nuevo);
                                                }
                                                //Actualizar placas de presion
                                                nuevo.actualizarPlacas();
                                                //....
                                                consumir_turno=true;
                                                actual=nuevo;
                                                pintar(actual);
                                            } break;
                                    case 4: if(esValido(actual, e, true)) { //Último true se refiere al nivel del agujero negro
                                                nuevo=aplicaOperador(actual, e, consumir_turno);
                                                if(consumir_turno) {
                                                    //Actualizar rocas
                                                    nuevo.actualizarRocas();
                                                    //Actualizar esqueletos
                                                    nuevo.actualizarEsqueletos();
                                                    //Aplicar efectos de curación
                                                    nuevo=aplicaVeneno(nuevo);
                                                }
                                                //Actualizar placas de presion
                                                nuevo.actualizarPlacas();
                                                //....
                                                consumir_turno=true;
                                                actual=nuevo;
                                                pintar(actual);
                                                tiempo_dentro+=actual.anillo()+1;
                                                //std::cout << tiempo_dentro << std::endl;
                                            } break;
                                    default:if(esValido(actual, e)) {
                                                nuevo=aplicaOperador(actual, e, consumir_turno);
                                                consumir_turno=true;
                                                actual=nuevo;
                                                pintar(actual);
                                            } break;
                                }
                            }
                        }
                    }
				}
			}
		}
	}

	//Free resources and close SDL
	close();
	return 0;
}

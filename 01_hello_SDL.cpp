/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include "SDL.h"
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* message = NULL;
SDL_Surface* background = NULL;
SDL_Surface* screen = NULL;
SDL_Surface* gXOut = NULL;
//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;
SDL_Surface* gKeyPressSurfaces = NULL;
SDL_Surface* gCurrentSurface = NULL;
//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}
bool loadMedia_hello()
{
    //Loading success flag
    bool success = true;

    //Load splash image
    gHelloWorld = SDL_LoadBMP( "02_getting_an_image_on_the_screen/hello_world.bmp" );
    if( gHelloWorld == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}
bool loadMedia_xout()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gXOut = SDL_LoadBMP( "x.bmp" );
	if( gXOut == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "03_event_driven_programming/x.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}
//loads invidiual image
SDL_Surface* loadSurface( std::string path )
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    return loadedSurface;
}
bool loadMedia_keypresses()
{
    //Loading success flag
    bool success = true;

    //Load default surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface("pic_test_keypresses/default.bmp");
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "pic_test_keypresses/up.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "pic_test_keypresses/down.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        printf( "Failed to load down image!\n" );
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "pic_test_keypresses/left.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
        printf( "Failed to load left image!\n" );
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "pic_test_keypresses/right.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }

    return success;
}
void close()
{

    //Deallocate surface
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&(e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
        return;
        SDL_Delay(100);
    }
}
/*SDL_Surface *load_image( std::string filename )
{
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    //Load the image
    loadedImage = SDL_LoadBMP( filename.c_str() );
    //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_ConvertSurfaceFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    }
    //Return the optimized image
    return optimizedImage;
}*/

int main( int argc, char* args[])
{
	//Start up SDL and create window
	std::cout << init() << '\n';
		//Load media
	std::cout << loadMedia_keypresses() << '\n';
/****************************/
    //Main loop flag
    bool quit = false;
    //Event handler
    SDL_Event e;
    //Set default current surface
    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
    //While application is running
    while( !quit )
    {
    //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                //Select surfaces based on key press
                switch( e.key.keysym.sym)
                {
                    case SDLK_UP:
                    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                    break;

                    case SDLK_DOWN:
                    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                    break;

                    case SDLK_LEFT:
                    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                    break;

                    case SDLK_RIGHT:
                    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                    break;

                    default:
                    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                    break;
                }
            }
        }
        //Apply the image
        SDL_BlitSurface( gXOut, NULL, gScreenSurface, NULL );
        //Update the surface
        SDL_UpdateWindowSurface( gWindow );
    }
    waitUntilKeyPressed();
	//Free resources and close SDL
	close();
	return 0;
}
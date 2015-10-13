#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define TRUE 1
#define FALSE 0

//#include <iostream>

// Setup
int InitEverything();
int InitSDL();
int CreateWindow();
int CreateRenderer();
void SetupRenderer();

// Our new function for setting uo SDL_TTF
int SetupTTF( const char *nomefont /*const std::string &fontName*/ );
SDL_Texture* SurfaceToTexture( SDL_Surface* surf );
void CreateTextTextures();

// Update ( happens every frame )
void Render();
void RunGame();

// Stuff for text rendering
TTF_Font* font;
SDL_Color textColor = { 255, 255, 255, 255 }; // white
SDL_Color backgroundColor = { 0, 0, 0, 255 }; // black

SDL_Texture* solidTexture;
SDL_Texture* blendedTexture;
SDL_Texture* shadedTexture;

SDL_Rect solidRect;
SDL_Rect blendedRect;
SDL_Rect shadedRect;

SDL_Rect windowRect = { 900, 300, 400, 400 };
SDL_Window* window;
SDL_Renderer* renderer;

int main( int argc, char* args[] )
{
	if ( !InitEverything() )
		return -1;

	RunGame();

        // Clean up font
        TTF_CloseFont( font );
}
void RunGame()
{
    SDL_Event event; //um evento enviado pela SDL
    int quit = 0; //devemos encerrar o programa?
	Render();
	while(!quit) //rodar enquanto nao for para encerrar :)
    {
        while(SDL_PollEvent(&event)) //checar eventos
        {
            if(event.type == SDL_QUIT) //fechar a janela?
            {
                quit = 1; //sair do loop principal
            }
        }

        //SDL_Flip(screen); //atualizar a tela
        //SDL_UpdateWindowSurface(janela);
    }
	//std::cout << "Press any key to exit\n";
	//std::cin.ignore();
}
void Render()
{
	// Clear the window and make it all red
	SDL_RenderClear( renderer );

	// Render our text objects ( like normal )
	SDL_RenderCopy( renderer, solidTexture, NULL, &solidRect ); 
	SDL_RenderCopy( renderer, blendedTexture, NULL, &blendedRect ); 
	SDL_RenderCopy( renderer, shadedTexture, NULL, &shadedRect ); 

	// Render the changes above
	SDL_RenderPresent( renderer);
}
// Initialization ++
// ==================================================================
int SetupTTF( const char *nomefont/*const std::string &fontName*/)
{
	// SDL2_TTF needs to be initialized just like SDL2
	if ( TTF_Init() == -1 )
	{
		//std::cout << " Failed to initialize TTF : " << TTF_GetError() << std::endl;
		return FALSE;
	}

	// Load our fonts, with a huge size
	font = TTF_OpenFont( nomefont/*fontName.c_str()*/, 90 );
	
	// Error check
	if ( font == NULL )
	{
		//std::cout << " Failed to load font : " << TTF_GetError() << std::endl;
		return FALSE;
	}

	return TRUE;
}
void CreateTextTextures()
{
	SDL_Surface* solid = TTF_RenderText_Solid( font, "solid", textColor );
	solidTexture = SurfaceToTexture( solid );

	SDL_QueryTexture( solidTexture, NULL, NULL, &solidRect.w, &solidRect.h );
	solidRect.x = 0;
	solidRect.y = 0;

	SDL_Surface* blended = TTF_RenderText_Blended( font, "blended", textColor );
	blendedTexture = SurfaceToTexture( blended );

	SDL_QueryTexture( blendedTexture, NULL, NULL, &blendedRect.w, &blendedRect.h );
	blendedRect.x = 0;
	blendedRect.y = solidRect.y + solidRect.h +  20;

	SDL_Surface* shaded = TTF_RenderText_Shaded( font, "shaded", textColor, backgroundColor );
	shadedTexture = SurfaceToTexture( shaded );

	SDL_QueryTexture( shadedTexture , NULL, NULL, &shadedRect.w, &shadedRect.h );
	shadedRect.x = 0;
	shadedRect.y = blendedRect.y + blendedRect.h + 20;
}
// Convert an SDL_Surface to SDL_Texture. We've done this before, so I'll keep it short
SDL_Texture* SurfaceToTexture( SDL_Surface* surf )
{
	SDL_Texture* text;

	text = SDL_CreateTextureFromSurface( renderer, surf );

	SDL_FreeSurface( surf );

	return text;
}
int InitEverything()
{
	if ( !InitSDL() )
		return FALSE;

	if ( !CreateWindow() )
		return FALSE;

	if ( !CreateRenderer() )
		return FALSE;

	SetupRenderer();

	if ( !SetupTTF( "sketchy.ttf" ) )
		return FALSE;

	CreateTextTextures();

	return TRUE;
}
int InitSDL()
{
	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		//std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
		return FALSE;
	}

	return TRUE;
}
int CreateWindow()
{
	window = SDL_CreateWindow( "Server", windowRect.x, windowRect.y, windowRect.w, windowRect.h, 0 );

	if ( window == NULL )
	{
		//std::cout << "Failed to create window : " << SDL_GetError();
		return FALSE;
	}

	return TRUE;
}
int CreateRenderer()
{
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

	if ( renderer == NULL )
	{
		//std::cout << "Failed to create renderer : " << SDL_GetError();
		return FALSE;
	}

	return TRUE;
}
void SetupRenderer()
{
	// Set size of renderer to the same as window
	SDL_RenderSetLogicalSize( renderer, windowRect.w, windowRect.h );

	// Set color of renderer to red
	SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
}*/

/// My own version of Hello World! test

#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[])
{
	SDL_Window * window = nullptr;
	SDL_Surface * surface = nullptr;
	SDL_PixelFormat * fmt = nullptr;
	Uint32 temp, pixel;
	Uint8 red, green, blue, alpha;

	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize!"
		"SDL_ERROR: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("SDL Tutorial",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if(!window)
		{
			printf("Window could not be created!"
			"SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			surface = SDL_GetWindowSurface(window);
			fmt = surface->format;
			SDL_LockSurface(surface);
			pixel = * ((Uint32 *) surface->pixels);
			Uint32 * pixels = (Uint32 *) surface->pixels;

			for (int j = 0; j < SCREEN_HEIGHT; ++j) 
			{
				for (int i = 0; i < SCREEN_WIDTH; ++i) 
				{
					auto r = double(i) / (SCREEN_WIDTH-1);
					auto g = double(j) / (SCREEN_HEIGHT-1);
					auto b = 0;
                
					int ir = static_cast<int>(255.999 * r);
					int ig = static_cast<int>(255.999 * g);
					int ib = static_cast<int>(255.999 * b);
			
					pixels[(j * surface->w) + i] = SDL_MapRGBA(fmt, ir, ig, ib, 1);
				}
			}


			SDL_UnlockSurface(surface);
			SDL_UpdateWindowSurface(window);
				
			SDL_Event e;
			bool quit = false;
			while(!quit)
			{
				while(SDL_PollEvent(&e))
				{
					if(e.type == SDL_QUIT) quit = true;
				}
			}
		}
	}

	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

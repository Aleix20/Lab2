#include "application.h"
#include "utils.h"
#include "image.h"


int clicks = 0;
int var = 0;
bool finished = false;

int x_position;
int y_position;
int x2_position;
int y2_position;
int x3_position;
int y3_position;





Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	// initialize attributes
	// Warning: DO NOT CREATE STUFF HERE, USE THE INIT 
	// things create here cannot access opengl
	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(NULL);

	framebuffer.resize(w, h);
}

//Here we have already GL working, so we can create meshes and textures
void Application::init(void)
{
	std::cout << "initiating app..." << std::endl;

	//Alçada de la taula
	
	
	//here add your init stuff
}

//render one frame
void Application::render( Image& framebuffer )
{
	//clear framebuffer if we want to start from scratch
	framebuffer.fill(Color::BLACK);

	//here you can add your code to fill the framebuffer

	//fill every pixel of the image with some random data

	if (var == 1) {
		framebuffer.fill(Color::BLACK);
		if (clicks == 1) {
			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::RED, true);
		}
		if (finished) {
			framebuffer.drawLineDDA(x_position, y_position, x2_position, y2_position, Color(255, 0, 0));
			clicks = 0;
		}
	}
	if(var == 2) {
		framebuffer.fill(Color::BLACK);
		if (clicks == 1) {
			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::RED, true);
		}
		if (finished) {
			framebuffer.drawLineBresenham(x_position, y_position, x2_position, y2_position, Color(255, 0, 0));
			clicks = 0;
		}
	}

	if (var == 3) {
		framebuffer.fill(Color::BLACK);
		if (clicks == 1) {
			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::BLUE, true);
		}
		if (finished) {
			int radius = abs(sqrt((x2_position - x_position) * (x2_position - x_position) + (y2_position - y_position) * (y2_position - y_position)));
			framebuffer.BresenhamCircle(x_position, y_position, radius, Color::BLUE, true);
			clicks = 0;
		}
	}

	if (var == 4) {
		framebuffer.fill(Color::BLACK);
		if (clicks == 1) {
			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::BLUE, true);
		}
		if (finished) {
			int radius = abs(sqrt((x2_position - x_position) * (x2_position - x_position) + (y2_position - y_position) * (y2_position - y_position)));
			framebuffer.BresenhamCircle(x_position, y_position, radius, Color::BLUE, false);
			clicks = 0;
		}
	}
	if (var==5) {
		framebuffer.fill(Color::BLACK);
		if (clicks == 1) {
			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::RED, true);
		}
		if (clicks==2) {

			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::RED, true);
			framebuffer.BresenhamCircle(x2_position, y2_position, 1, Color::RED, true);
			
		}
		if (finished)
		{
			framebuffer.drawTriangle(x_position,y_position,x2_position, y2_position, x3_position, y3_position, Color{ 0,255,0 }, true);
			clicks = 0;
		}
	}
	if (var == 6) {
		framebuffer.fill(Color::BLACK);
		if (clicks == 1) {
			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::RED, true);
		}
		if (clicks == 2) {

			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::RED, true);
			framebuffer.BresenhamCircle(x2_position, y2_position, 1, Color::RED, true);

		}
		if (finished)
		{
			framebuffer.drawTriangleInterpolated(x_position, y_position, x2_position, y2_position, x3_position, y3_position, Color{ 0,255,0 }, Color{ 255,0,0 }, Color{ 0,0,255 });
			clicks = 0;
		}
	}
}

//called after render
void Application::update(double seconds_elapsed)
{
	//to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	if (keystate[SDL_SCANCODE_SPACE]) //if key space is pressed
	{
		//...
	}

	//to read mouse position use mouse_position
}

//keyboard press event 
void Application::onKeyDown( SDL_KeyboardEvent event )
{
	//to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	switch(event.keysym.scancode)
	{
		case SDL_SCANCODE_ESCAPE:
			exit(0); 
			break; //ESC key, kill the app

		case SDL_SCANCODE_1:
			var = 1;
			finished = false;
			break;

		case SDL_SCANCODE_2:
			var = 2;
			finished = false;
			break;

		case SDL_SCANCODE_3:
			var = 3;
			finished = false;
			break;
		case SDL_SCANCODE_4:
			var = 4;
			finished = false;
			break;
		case SDL_SCANCODE_5:
			var = 5;
			finished = false;
			break;
		case SDL_SCANCODE_6:
			var = 6;
			finished = false;
			break;
	}
}

//keyboard key up event 
void Application::onKeyUp(SDL_KeyboardEvent event)
{
	//...
}

//mouse button event
void Application::onMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //left mouse pressed
	{
		//if you read mouse position from the event, careful, Y is reversed, use mouse_position instead
		
		if (var == 1 || var == 2 || var == 3 || var == 4) {
			
			finished = false;
			if (clicks == 0) {
				x_position = mouse_position.x;
				y_position = mouse_position.y;
			}

			if (clicks == 1) {
				x2_position = mouse_position.x;
				y2_position = mouse_position.y;
				finished = true;
			}

			clicks++;
		}
		if (var==5 || var == 6) {
			finished = false;
			if (clicks == 0) {
				x_position = mouse_position.x;
				y_position = mouse_position.y;
			}

			if (clicks == 1) {
				x2_position = mouse_position.x;
				y2_position = mouse_position.y;
				
			}
			if (clicks == 2) {
				x3_position = mouse_position.x;
				y3_position = mouse_position.y;
				finished = true;
			}

			clicks++;
		}
	}
}

void Application::onMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //left mouse unpressed
	{

	}
}

//when the app starts
void Application::start()
{
	std::cout << "launching loop..." << std::endl;
	launchLoop(this);
}

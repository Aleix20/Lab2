#include "application.h"
#include "utils.h"
#include "image.h"

int clicks = 0;
int var = 0;
bool first_click = true;
bool second_click = false;
bool finished = false;

int x_position;
int y_position;
int x2_position;
int y2_position;

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

	//here add your init stuff
}

//render one frame
void Application::render( Image& framebuffer )
{
	//clear framebuffer if we want to start from scratch
	framebuffer.fill(Color::BLACK);

	//here you can add your code to fill the framebuffer

	//fill every pixel of the image with some random data
	
	if(var == 1) {
		//framebuffer.drawLineBresenham(0,50,5,20,Color(255,0,0));
		if (finished) {
			framebuffer.drawLineBresenham(x_position, y_position, x2_position, y2_position, Color(255, 0, 0));
			clicks = 0;
		}
	}

	if (var == 2) {
		framebuffer.BresenhamCircle(200, 500, 200, Color::BLUE, true);
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
			break;

		case SDL_SCANCODE_2:
			var = 2;
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

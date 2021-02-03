#include "application.h"
#include "utils.h"
#include "image.h"


int clicks = 0; //Declaració de les variables globals que utilitzem durant la pràctica.
int var = 0;
bool finished = false;

int x_position = 0;
int y_position = 0;
int x2_position = 0;
int y2_position = 0;
int x3_position = 0;
int y3_position = 0;


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

	if (var == 1) { //Tasca 1
		
		framebuffer.fill(Color::BLACK); //Omplim el framebuffer de color negre
		
		if (clicks == 1) { //Si només hem fet un click dibuixem el punt on l'hem fet
			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::RED, true);
		}
		
		if (finished) { //Si ja hem fet els dos clicks dibuixem la recta que uneix els punts on hem fet click i reiniciem el número de clicks fets
			framebuffer.drawLineDDA(x_position, y_position, x2_position, y2_position, Color(255, 0, 0));
			clicks = 0;
		}
	}
	if(var == 2) { //Tasca 2, el mateix que la tasca 1 però amb la funció corresponent a Bresenham
		
		framebuffer.fill(Color::BLACK);
		
		if (clicks == 1) {
			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::RED, true);
		}
		
		if (finished) {
			framebuffer.drawLineBresenham(x_position, y_position, x2_position, y2_position, Color(255, 0, 0));
			clicks = 0;
		}
	}

	if (var == 3) { //Tasca 3, similar a les tasques anteriors però aplicant la funció per dibuixar cercles
		
		framebuffer.fill(Color::BLACK);
		
		if (clicks == 1) {
			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::BLUE, true);
		}
		
		if (finished) {
			int radius = abs(sqrt((x2_position - x_position) * (x2_position - x_position) + (y2_position - y_position) * (y2_position - y_position))); //Calculem el radi del cercle restant la posició del segon click a la posició del primer click.
			framebuffer.BresenhamCircle(x_position, y_position, radius, Color::BLUE, true);
			clicks = 0;
		}
	}

	if (var == 4) { //Tasca 3 però sense pintar l'interior del cercle
		
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
	if (var==5) { //Tasca 4, similar a les anteriors però amb 1 click més i dibuixant un triangle
		
		framebuffer.fill(Color::BLACK);
		
		if (clicks == 1) {
			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::RED, true);
		}
		
		if (clicks==2) {
			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::RED, true); //Dibuixem el punt anterior donat que cada vegada netegem el framebuffer
			framebuffer.BresenhamCircle(x2_position, y2_position, 1, Color::RED, true);
		}
		
		if (finished){
			framebuffer.drawTriangle(x_position,y_position,x2_position, y2_position, x3_position, y3_position, Color{ 0,255,0 }, true);
			clicks = 0;
		}
	}
	if (var == 6) { //Tasca 4 però sense pintar l'interior del triangle

		framebuffer.fill(Color::BLACK);

		if (clicks == 1) {
			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::RED, true);
		}

		if (clicks == 2) {
			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::RED, true); //Dibuixem el punt anterior donat que cada vegada netegem el framebuffer
			framebuffer.BresenhamCircle(x2_position, y2_position, 1, Color::RED, true);
		}

		if (finished) {
			framebuffer.drawTriangle(x_position, y_position, x2_position, y2_position, x3_position, y3_position, Color{ 0,255,0 }, false);
			clicks = 0;
		}
	}
	if (var == 7) { //Tasca 4 amb interpolació (el mateix que l'anterior però dibuixant un triangle amb un color que sorgeix de la interpolació baricèntrica dels vèrtexs d'aquest)
		
		framebuffer.fill(Color::BLACK);
		
		if (clicks == 1) {
			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::RED, true);
		}
		
		if (clicks == 2) {
			framebuffer.BresenhamCircle(x_position, y_position, 1, Color::RED, true);
			framebuffer.BresenhamCircle(x2_position, y2_position, 1, Color::RED, true);
		}
		
		if (finished){
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

		case SDL_SCANCODE_1: //Casos per gestionar les diferents tasques de la pràctica
			var = 1;
			finished = false; //Cada vegada haurem de resetejar l'estat de la figura a dibuixar com a no acabada i els clicks realitzats a 0 per tal d'evitar que es pintin punts d'altres tasques.
			clicks = 0;
			break;
		
		case SDL_SCANCODE_2:
			var = 2;
			finished = false;
			clicks = 0;
			break;
		
		case SDL_SCANCODE_3:
			var = 3;
			finished = false;
			clicks = 0;
			break;
		
		case SDL_SCANCODE_4:
			var = 4;
			finished = false;
			clicks = 0;
			break;
		
		case SDL_SCANCODE_5:
			var = 5;
			finished = false;
			clicks = 0;
			break;
		
		case SDL_SCANCODE_6:
			var = 6;
			finished = false;
			clicks = 0;
			break;
		
		case SDL_SCANCODE_7:
			var = 7;
			finished = false;
			clicks = 0;
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
		
		if (var == 1 || var == 2 || var == 3 || var == 4) { //En el cas de que ens trobem a la tasca 1,2 o 3 apliquem el següent algoritme per emmagatzemar les posicions on fem els clicks per dibuixar la figura.
			
			finished = false; //En un inici sempre estarà inacabada la figura
			if (clicks == 0) { //En el cas de no haver fet cap click abans, ens guardem la posició del primer click
				x_position = mouse_position.x;
				y_position = mouse_position.y;
			}

			if (clicks == 1) { //Si ja havíem fet 1 click, ens guardem la posició del segon click i canviem l'estat de la figura a acabada
				x2_position = mouse_position.x;
				y2_position = mouse_position.y;
				finished = true;
			}

			clicks++; //Augmentem en 1 el número de clicks
		}
		if (var==5 || var == 6 || var == 7) { //En el cas de que ens trobem a la tasca 4, realitzarem el mateix però amb un click més degut a que ens trobem en la situació en la que volem dibuixar un triangle
			
			finished = false;
			if (clicks == 0) {
				x_position = mouse_position.x;
				y_position = mouse_position.y;
			}

			if (clicks == 1) {
				x2_position = mouse_position.x;
				y2_position = mouse_position.y;
				
			}
			if (clicks == 2) { //Si ja havíem fet 2 clicks, emmagatzemem la posició de l'últim click i canviem l'estat de la figura a acabada
				x3_position = mouse_position.x;
				y3_position = mouse_position.y;
				finished = true;
			}

			clicks++; //Augmentem en 1 el número de clicks.
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

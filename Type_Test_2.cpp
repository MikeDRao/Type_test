#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <gtkmm.h>
#include <gtkmm/application.h>
#include "New_Game.h"
#include "Diver_Widget.h"
#include "menu_input.h"
#include <ctime>
#include <cstdlib>
#include <time.h>



//new
class On_Screen_Char {
public:

	Diver_Widget& widget;
	New_Game_Window& New_G;
	//BackGround
	sf::Sprite BackGround_sprite;
	sf::Texture background;

	//Diver
	sf::Sprite New_Diver;
	sf::Texture Diver_image;

	static constexpr int nFrame = 5;
	static constexpr float holdTime = 0.05f;
	sf::IntRect frames[nFrame];
	int iFrame;
	float time;

	int x_width;
	int y_height;
	int width;
	int height;
	sf::Vector2f dir;
	sf::Vector2f position = { 0.f, 500.f };

	int Game_Speed;

	int check_num = 0;
	int Num_correct = 0;


	On_Screen_Char(Diver_Widget& widget, New_Game_Window& New_G) : widget(widget), New_G(New_G)
	{
		x_width = 0;
		y_height = 0;
		width = 240;
		height = 240;
		dir = { 0.0f,0.0f };
		this->Game_Speed = this->New_G.Game_Speed;


		background.loadFromFile("Underwater_background_new.jpg");
		BackGround_sprite.setTexture(background);

		iFrame = 0;
		time = 0.0f;

		Diver_image.loadFromFile("New_diver_Boy.png");
		
		
		New_Diver.setPosition(position);

		//call animate every 50ms
		Glib::signal_timeout().connect(sigc::bind_return(sigc::mem_fun(this, &On_Screen_Char::animate), true), 100);

		// call move_widget
		Glib::signal_timeout().connect(sigc::bind_return(sigc::mem_fun(this, &On_Screen_Char::move_widget), true), Game_Speed);

		//Makes draw method beeing drawn everytime the widget itself gets drawn
		widget.signal_draw().connect(sigc::bind_return(sigc::hide(sigc::mem_fun(this, &On_Screen_Char::draw)), true));

		//Adjust the view everytime thhe widget gets resized
		widget.signal_size_allocate().connect(sigc::hide(sigc::mem_fun(this, &On_Screen_Char::resize_view)));
	}

	void moveToStartPoint()
	{
		this->position = { 0.f, 500.f };
		New_Diver.setPosition(position);
	}
	
	void move_widget()
	{


		if (this->New_G.user_letter_vec[check_num] == this->New_G.displayed_chars[check_num])
		{
			
			cout << "Correct" << endl;
			Num_correct++;
			check_num++;
			position.x += 50.f;
			New_Diver.setPosition(position);
			if (position.x > widget.renderWindow.getSize().x)
				moveToStartPoint();

		}
		else
		{
			check_num++;
		}
		
	}

	void animate()
	{
			
		if (++iFrame >= nFrame)
		{
			iFrame = 0;
		}
		frames[iFrame] = { x_width + iFrame * width,y_height,width,height };

		New_Diver.setTexture(Diver_image);
		New_Diver.setTextureRect(frames[iFrame]);

		widget.invalidate();
	}

	void draw()
	{

		// Clear screen
		widget.renderWindow.clear();

		//Apply Sprite Texture
		widget.renderWindow.draw(BackGround_sprite);

		widget.renderWindow.draw(New_Diver);

		// Update the window
		widget.display();
	}

	void resize_view()
	{
		//let the view fit the pixels of the window.
		sf::Vector2f lower_right(widget.renderWindow.getSize().x, widget.renderWindow.getSize().y);
		sf::View view(lower_right * 0.5f,lower_right);
		widget.renderWindow.setView(view);
	}



};


int main(int argc, char* argv[])
{
	Gtk::Main kit(argc, argv);

	//main menu 

	//top level gtk window 
	New_Game_Window New_G;

	// Create the main window
	Diver_Widget ourRenderWindow(sf::VideoMode(1280, 1024));
	On_Screen_Char Our_new_Diver(ourRenderWindow,New_G);

	//doesn't draw the renderWindow but makes it so it will draw
	ourRenderWindow.show();

	//Packs rendered window into the New_Game main box
	New_G.box.pack_start(ourRenderWindow);
	Gtk::Main::run(New_G);

	return EXIT_SUCCESS;
}
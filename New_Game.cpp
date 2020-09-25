#include "New_Game.h"
//#include "menu_input.h"


using namespace std;

New_Game_Window::New_Game_Window() :box(Gtk::ORIENTATION_VERTICAL,0), button_close("close"), Sub_box(Gtk::ORIENTATION_VERTICAL, 0)
{

	Diver New_Player;
	this->Player_Name = New_Player.get_name();
	this->Game_Speed = New_Player.get_speed();
	cout << Player_Name << endl;
	srand(clock());

	set_title("Type Test");
	add(box);

	entry1.set_max_length(50);
	entry1.select_region(0, entry1.get_text_length());

	//********** Create very first char *******
	Rand_int = rand() % 26;
	new_letter = 'a' + Rand_int;
	oss_in << new_letter;
	string next_letter = oss_in.str();
	
	displayed_chars.push_back(next_letter);

	oss << "Next Letter: " << new_letter;
	out = oss.str();

	LetterLabel.set_text(out);
	oss_in.str("");
	oss.str("");
	//**************************************

	Sub_box.pack_start(LetterLabel);
	Sub_box.pack_start(entry1);
	Sub_box.pack_start(textbox1);

	//***********where I think the problem is***************
	Glib::signal_timeout().connect(sigc::bind_return(sigc::mem_fun(*this, &New_Game_Window::Next_Letter), true), Game_Speed);
	Glib::signal_timeout().connect(sigc::bind_return(sigc::mem_fun(*this, &New_Game_Window::Pull_Letter), true), Game_Speed);
	//**
	//Glib::signal_timeout().connect(sigc::bind_return(sigc::mem_fun(*this, &New_Game_Window::Check_Letter), true), 2050);
	button_close.signal_clicked().connect(sigc::mem_fun(*this, &New_Game_Window::close_button));


	button_close.set_can_default();
	button_close.grab_default();
	Sub_box.pack_start(button_close);

	box.pack_start(Sub_box, Gtk::PACK_SHRINK);

	show_all_children();
}

New_Game_Window::~New_Game_Window()
{
}

void New_Game_Window::close_button()
{
	hide();
	int correct = 0;
	int b;

	for (b = 0; b < i; b++)
	{
		cout << displayed_chars[b] << " " << user_letter_vec[b] << endl;
		if (displayed_chars[b] == user_letter_vec[b])
			correct++;
	}

	ostringstream oss;
	oss <<Player_Name<<" you got "<<correct<<" of "<<b<<"!";
	string out = oss.str();
	Gtk::MessageDialog dialog(*this, out, false, Gtk::MESSAGE_INFO);
	dialog.run();
}

void New_Game_Window::Next_Letter()
{
	
	Rand_int = rand() % 26;
	new_letter = 'a' + Rand_int;
	oss_in << new_letter;
	string next_letter = oss_in.str();

	//********** Possible Solution to what was preceived to be lag!!! *******
	if (next_letter == displayed_chars[i])
	{
		oss.str("");
		Rand_int = rand() % 26;
		new_letter = 'a' + Rand_int;
		oss_in << new_letter;
		next_letter = oss_in.str();
	}

	displayed_chars.push_back(next_letter);

	oss <<"Next Letter: " << new_letter;
	out = oss.str();
	
	LetterLabel.set_text(out);
	oss_in.str("");
	oss.str("");
	i++;
}

void New_Game_Window::Pull_Letter()
{
	user_letter = entry1.get_text();
	
	user_letter_vec.push_back(user_letter);

	cout << user_letter <<  endl;
	entry1.set_text("");
	
}


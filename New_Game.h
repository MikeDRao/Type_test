#ifndef _NEW_GAME_H
#define _NEW_GAME_H

#include <gtkmm.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <vector>
#include <iostream>
#include <sstream>
#include "menu_input.h"


using namespace std;

class New_Game_Window :public Gtk::Window
{
public:
	New_Game_Window();
	Gtk::Box box;
	virtual ~New_Game_Window();
	int Game_Speed;

	vector<string> displayed_chars;
	vector<string> user_letter_vec;

protected:
	// signal handlers
	
	void close_button();
	void Next_Letter();
	
	void Pull_Letter();

	

	int i = 0;
	int Rand_int;


	char new_letter;
	
	string user_letter;
	
	ostringstream oss;
	ostringstream oss_in;

	string out;
	string Player_Name;

	Gtk::Label LetterLabel;
	Gtk::Box textbox1;
	Gtk::Entry entry1;
	Gtk::Button button_close;
	
	Gtk::Box Sub_box;

};


#endif

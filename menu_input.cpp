#include "menu_input.h"
#include <gtkmm.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Diver::Diver()
{
	Gtk::Window w;
	Gtk::Dialog *dialog = new Gtk::Dialog();
	dialog->set_transient_for(w);
	dialog->set_title("Type Test Menu");

	Gtk::Label *label = new Gtk::Label("Enter name:");
	dialog->get_content_area()->pack_start(*label);
	label->show();
	dialog->add_button("Slow", 0)->signal_clicked().connect(sigc::mem_fun(*this, &Diver::Slow_but));
	dialog->add_button("Medium", 1)->signal_clicked().connect(sigc::mem_fun(*this, &Diver::Med_but));
	dialog->add_button("Fast", 0)->signal_clicked().connect(sigc::mem_fun(*this, &Diver::Fast_but));
	dialog->add_button("Quit", 1)->signal_clicked().connect(sigc::mem_fun(*this, &Diver::Quit_but));
	dialog->set_default_response(0);

	Gtk::Entry *entry_first = new Gtk::Entry();
	entry_first->set_text("Name");
	entry_first->set_max_length(50);
	entry_first->show();
	dialog->get_vbox()->pack_start(*entry_first);

	int result = dialog->run();
	name = entry_first->get_text();


	dialog->close();

	delete dialog;
	delete label;
}
string Diver::get_name()
{
	return name;
}
int Diver::get_speed()
{
	return speed;
}

//Slow
void Diver::Slow_but() 
{
	this->speed = 2000;
}

//Medium
void Diver::Med_but()  
{
	this->speed = 1500;
}

//Fast
void Diver::Fast_but()   
{
	this->speed = 1000;
}

//Quit
void Diver::Quit_but()   
{

}


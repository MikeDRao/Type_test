#ifndef	MENU_INPUT_H
#define	MENU_INPUT_H
#include <gtkmm.h>
using namespace std;

class Diver {
public:
	string name;
	int speed;
	Diver();

	//pass to New_Game
	string get_name();
	int get_speed();

	void Slow_but();
	void Med_but();
	void Fast_but();
	void Quit_but();
};

#endif

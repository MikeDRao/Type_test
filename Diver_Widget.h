#ifndef DIVER_WIDGET_H_
#define DIVER_WIDGET_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <gtkmm/widget.h>


class Diver_Widget : public Gtk::Widget
{
protected:
	sf::VideoMode m_vMode;

	virtual void on_size_allocate(Gtk::Allocation& allocation);
	virtual void on_realize();
	virtual void on_unrealize();

	Glib::RefPtr<Gdk::Window> m_refGdkWindow;
public:
	sf::RenderWindow renderWindow;

	Diver_Widget(sf::VideoMode mode, int size_request = -1);
	virtual ~Diver_Widget();
	void invalidate();
	void display();
	void close_button();
};

#endif
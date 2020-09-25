#include "Diver_Widget.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#if defined(SFML_SYSTEM_WINDOWS)

#include <gdk/gdkwin32.h>
#define GET_WINDOW_HANDLE_FROM_GDK GDK_WINDOW_HANDLE

#elif defined(SFML_SYSTEM_LINUX) || defined(SFML_SYSTEM_FREEBSD)

#include <gdk/gdkx.h>
#define GET_WINDOW_HANDLE_FROM_GDK GDK_WINDOW_XID

#elif defined(SFML_SYSTEM_MACOS)

#error Note: Unsupported Operating System

#else 

#error Unsupported Operating System

#endif

Diver_Widget::Diver_Widget(sf::VideoMode mode, int size_request)
{

	if (size_request <= 0)
	{
		size_request = std::max<int>(1, std::min<int>(mode.width, mode.height)/1.25);
	}

	set_size_request(size_request, size_request);

	set_has_window(false);


}

Diver_Widget::~Diver_Widget()
{
}

void Diver_Widget::on_size_allocate(Gtk::Allocation& allocation)
{
	this->set_allocation(allocation);

	if (m_refGdkWindow)
	{
		m_refGdkWindow->move_resize(allocation.get_x(),
			allocation.get_y(),
			allocation.get_width(),
			allocation.get_height());
		renderWindow.setSize(sf::Vector2u(allocation.get_width(),
			allocation.get_height()));
	}
}

void Diver_Widget::on_realize()
{
	Gtk::Widget::on_realize();

	if (!m_refGdkWindow)
	{
		//create gdk window (gdk is a library used by Gtk?
		GdkWindowAttr attributes;
		memset(&attributes, 0, sizeof(attributes));

		Gtk::Allocation allocation = get_allocation();

		//set initial position and size of the Gdk::Window:
		attributes.x = allocation.get_x();
		attributes.y = allocation.get_y();
		attributes.width = allocation.get_width();
		attributes.height = allocation.get_height();

		attributes.event_mask = get_events () | Gdk::EXPOSURE_MASK;
		attributes.window_type = GDK_WINDOW_CHILD;
		attributes.wclass = GDK_INPUT_OUTPUT;

		m_refGdkWindow = Gdk::Window::create(get_window(), &attributes, GDK_WA_X | GDK_WA_Y);
		set_has_window(true);
		set_window(m_refGdkWindow);

		//transparent background

#if GTK_VERSION_GE(3,0)
		this->unset_background_color();
#else 
		this->get_window()->set_back_pixmap(Glib::RefPtr<Gdk::Pixmap>());
#endif
		this->set_double_buffered(false);

		//make the widget receive expose events
		m_refGdkWindow->set_user_data(gobj());

		renderWindow.create(GET_WINDOW_HANDLE_FROM_GDK(m_refGdkWindow->gobj()));
	}
}

void Diver_Widget::on_unrealize()
{
	m_refGdkWindow.clear();

	//call base class:
	Gtk::Widget::on_unrealize();
}

void Diver_Widget::display()
{
	if (m_refGdkWindow)
	{
		renderWindow.display();
	}
}

void Diver_Widget::invalidate()
{
	if (m_refGdkWindow)
	{
		m_refGdkWindow->invalidate(true);
	}
}

void Diver_Widget::close_button()
{
	hide();
}

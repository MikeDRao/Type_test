CXXFLAGS += -std=c++11
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
LDLIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

ex: Type_Test_2.o Diver_Widget.o New_Game.o menu_input.o
	$(CXX) $(CXXFLAGS) -o Type_Test_2 Type_Test_2.o Diver_Widget.o New_Game.o menu_input.o $(GTKFLAGS) $(LDFLAGS) $(LDLIBS)
Type_Test_2.o: Type_Test_2.cpp Diver_Widget.o New_Game.o menu_input.o
	$(CXX) $(CXXFLAGS) -c Type_Test_2.cpp $(GTKFLAGS) $(LDFLAGS) $(LDLIBS)
Diver_Widget.o: Diver_Widget.h Diver_Widget.cpp 
	$(CXX) $(CXXFLAGS) -c Diver_Widget.cpp $(GTKFLAGS) $(LDFLAGS) $(LDLIBS)
menu_input.o: menu_input.h menu_input.cpp 
	$(CXX) $(CXXFLAGS) -c menu_input.cpp $(GTKFLAGS) $(LDFLAGS) $(LDLIBS)
New_Game.o: New_Game.h New_Game.cpp menu_input.o
	$(CXX) $(CXXFLAGS) -c New_Game.cpp $(GTKFLAGS) $(LDFLAGS) $(LDLIBS)

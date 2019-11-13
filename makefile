CXXFLAGS= -std=c++11
GTKFLAGS= `pkg-config gtkmm-3.0 --cflags --libs`

ex: project_main.cpp project.cpp
	$(CXX) $(CXXFLAGS) project_main.cpp project.cpp $(GTKFLAGS)
	./a.out
clean:
	rm -rf *.o

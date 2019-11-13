#include "project.h"
#include <gtkmm.h>
int main(int argc, char** argv)
{
    Gtk::Main app(argc, argv);
    main_window w;
    Gtk::Main::run(w);
    return 0;
}

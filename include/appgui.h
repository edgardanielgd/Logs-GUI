#ifndef APPGUI_H
#define APPGUI_H

#include <gtkmm.h>

class GUIApp : public Gtk::Window{
    public:
        GUIApp();

    private:
        Gtk::Label lblTitle;
        Gtk::Menu menMainMenu;
        Gtk::Fixed fixMainLayout;

};
#endif
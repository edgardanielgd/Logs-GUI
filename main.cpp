#include <gtkmm.h>
#include <iostream>

#include "directed_graph.h"
#include "player.h"
#include "appgui.h"

using namespace std;

DirectedGraph<string,char,IP,Player> *playersIndexedByName = new DirectedGraph<string,char,IP,Player>();

int main(int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv,
      "com.projects.logsinterface");

  GUIApp GUIWindow;

  return app->run( GUIWindow );
}
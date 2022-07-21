#include <gtkmm.h>
#include <iostream>

#include "directed_graph.h"
#include "default_decoder.h"
#include "player.h"
#include "include/linked_list.h"

using namespace std;

DirectedGraph<string,char,IP,Player> *playersIndexedByName = new DirectedGraph<string,char,IP,Player>();
DirectedGraph<IP,int,string,Player> *playersIndexedByIp = new DirectedGraph<IP,int,string,Player>();

int main(int argc, char *argv[])
{

  Gtk::Main kit(argc, argv);

  Glib::RefPtr<Gtk::Builder> builder =   
         Gtk::Builder::create_from_file(".\\glade\\LogsGUI.glade");
         
  Gtk::Window *GUIWindow = 0;

  builder->get_widget("winLogsGUIMainWindow",GUIWindow);

  Gtk::Main::run(*GUIWindow);

  delete playersIndexedByName;
  delete playersIndexedByIp;
}
#include "appgui.h"

GUIApp::GUIApp(){
    set_title("Logs GUI");
    set_default_size(600,400);

    lblTitle.set_text("Welcome to Logs Interface");
    
    add( fixMainLayout );

    fixMainLayout.put( lblTitle, 100, 50);
    
    show_all_children();
}
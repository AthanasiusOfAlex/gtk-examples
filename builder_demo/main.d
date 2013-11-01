module main;

import gtk.Main;
import ApplicationWindow;

void main(string[] args)
{
    Main.init(args);

    new ApplicationWindow("main_window.glade", "main_window");

    Main.run();
}

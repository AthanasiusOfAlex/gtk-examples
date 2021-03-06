module ApplicationWindow;

import gtk.Window;
import gtk.Widget;
import gtk.Button;
import gtk.ToolButton;
import gtk.ToggleToolButton;
import gtk.Grid;
import gtk.Builder;
import gtk.Image;
import gtk.ImageMenuItem;
import gtk.MenuItem;
import gtk.Main;
import std.stdio;

/**
 * This class creates the main application window. It inherites the Gtk.Window
 * class using the interface provided by the Glade file.
 */
class ApplicationWindow : Window
{
public:
    this(string glade_file, string toplevel_object)
    {
        // Open the Glade file.
        _builder = new Builder();
        _builder.addFromFile(glade_file);
        
        // Get the_top level window
        _toplevel_window = cast(Window)_builder.getObject(toplevel_object);
        
        // Use the Gtk struct to call the parent's constructor.
        // This will make the ApplicationWindow class "own" the window.
        // (The Window class can take a GtkWindow* pointer as an initializer,
        // which is what we are doing here.)
        super(_toplevel_window.getWindowStruct());
        
        // Retrieve some buttons. This is done by calling the getObject() method
        // from a Builder object. All you need to do is put in the name of the desired widget
        // and type-cast it to the correct type.
        _btnStar = cast(Button)_builder.getObject("btnStar");

        // To connect a signal handler, simply pass a reference to the handler to addOn[Signal]().
        // (There is a method for each available signal.)
        // Note that the method ordinarily takes an object of the same type as the widget
        // as its first argument. (Have a look at _starOnClicked() below.)
        _btnStar.addOnClicked(&_starOnClicked);

        // Some more widgets and their signal handlers:
        _tbtExit = cast(ToolButton)_builder.getObject("tbtExit");
        _tbtExit.addOnClicked(&_exitOnClicked);

        _tbtOpen = cast(ToggleToolButton)_builder.getObject("tbtOpen");
        _tbtOpen.addOnClicked(&_openOnClicked);

        // The On Activate signal is used to capture choosing a menu item.
        // Note that "On Activate" signal handles take a MenuItem as an argument,
        // since the signal is defined by that (parent) class.
        _imiQuit = cast(ImageMenuItem)_builder.getObject("imiQuit");
        _imiQuit.addOnActivate(&_quitOnActivate);
    
        // We will now add a custom button that was not contemplated in the Glade file.

        // Prepare a custom button to be added (with an image in it).
        _btnNewButton = new Button();
        _imgNew = new Image("new.svg");
        _btnNewButton.add(_imgNew);                 // Adds the image to the button.
        _btnNewButton.setHasTooltip(true);          // These two lines make a tooltip.
        _btnNewButton.setTooltipText("New Button");

        _btnNewButton.setMarginTop(5);              // Give it a little more space.
        _btnNewButton.setMarginBottom(5);
        _btnNewButton.setMarginLeft(5);
        _btnNewButton.setMarginRight(5);

        // Let's specify a simple signal handler, too. Since the handler is so simple, this time
        // we will use a lambda function instead of defining a method.
        _btnNewButton.addOnClicked(delegate void (Button){writeln("The new button was clicked.");});

        // Get the grid.
        _grid = cast(Grid)_builder.getObject("main_grid");

        // We will need to add a row in order to make room.
        _grid.insertRow(4);

        //  Add the prepared button to the grid.
        // The first two numbers are coordinates in the grid (starting with 0 at the top left),
        // and the other two specify how many rows and columns the widget takes up.
        _grid.attach(_btnNewButton,1,3,1,1); 

        // Make sure the program exits when the main window is hidden.
        // We will take advantage of the "Hide" signal to do this.
        addOnHide(delegate void(Widget){ writeln("The Exit button was not used to quit."); Main.quit(); });

        // I would like the star to be the application's icon.
        setIconFromFile("star.svg");

        // Show the window and all the child widgets.
        showAll;
    }

protected:
    GtkWindow* _gtkWindow;      // Pointer to the underlying struct for the window
    Builder _builder;           // Builder object

    // Various widgets.
    Window _toplevel_window;    // Top-level window
    Grid _grid;                 // Grid
    Button _btnStar;            // Star button.
    ToolButton _tbtExit;        // Exit button on the toolbar.
    ToggleToolButton _tbtOpen;  // Open button on the toolbar.
    Button _btnNewButton;       // A new button that we will add.
    Image _imgNew;              // An image to place in the new button.
    ImageMenuItem _imiQuit;     // The "quit" menu item.

    // Signal handlers.
    void _starOnClicked(Button button)
    {
        static long times = 0;
        write("The 'star' button was hit ", ++times, " time");
        if (times==1) {
            writeln(".");
        } else {
            writeln("s.");
        }
    }
    
    void _exitOnClicked(ToolButton button)
    {
        writeln("The 'Exit' toolbar button was used to exit.");
        Main.quit();
    }

    void _openOnClicked(ToolButton button)
    {
        auto state = _tbtOpen.getActive();
        writeln("State of toggle button: ", state);
    }

    void _quitOnActivate(MenuItem item)
    {
        writeln("The 'Quit' menu item was used to exit.");
        Main.quit();
    }
}

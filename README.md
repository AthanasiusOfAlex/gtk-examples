gtk-examples
=============

A couple of examples for how to use GtkD and Gtkmm

###builder_demo

`builder_demo` shows how to use the Builder class, importing a Glade file. It can be compiled with the command

```
dmd -oftest_dmd main.d ApplicationWindow.d `pkg-config --cflags --libs gtkd2`
```

Or else, with GDC:
```
gdc -o test_gdc main.d ApplicationWindow.d `pkg-config --cflags --libs gtkd-2`
```


Make sure that the resource files (`star.svg`, `new.svg`, `main_window.glade`) are in the same directory (as well as in the same directory you run the program).

###gtkmm-transparent-slider

`gtkmm-transparent-slider` gives an example of how to bypass Gtk's normal window-drawing. It is possible to create a transparent or translucent window with widgets on it.

Compile with the following command:

```
g++ -otransparent-slider main.cpp transparent-slider.cpp `pkg-config gtkmm-3.0 --cflags --libs` -std=c++11 -O3
```

Leave out the `O3` if you want to do any debugging. (I hope it is not necessary!)

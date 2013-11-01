gtkd-examples
=============

A couple of examples for how to use GtkD.

`builder_demo` shows how to use the Builder class, importing a Glade file. It can be compiled with the command

```
dmd main.d ApplicationWindow.d `pkg-config --cflags --libs gtkd2`
```

Make sure that the resource files (`star.svg`, `new.svg`, `main_window.glade`) are in the same directory (as well as in the same directory you run the program).

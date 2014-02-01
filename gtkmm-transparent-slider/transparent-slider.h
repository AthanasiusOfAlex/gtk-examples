/**
 * transparent.h
 *
 * This file is part of Transparent-Slider.
 * Transparent-Slider is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 *  Transparent-Slider is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Transparent-Slider.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  (c) Louis Melahn, L.C. February 1, 2014.
 */

#ifndef TRANSPARENTSLIDER_H_
#define TRANSPARENTSLIDER_H_

#include <iostream>
#include <gtk/gtk.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/alignment.h>
#include <gtkmm/button.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/scale.h>

class TransparentSlider : public Gtk::Window
{

private:
    double _redInit;
    double _greenInit;
    double _blueInit;
    double _alphaInit;

    std::string _buttonLabel;

public:
    TransparentSlider();
    void set_visual(Glib::RefPtr<Gdk::Visual> visual);
    virtual ~TransparentSlider();

protected:
    // Signal handlers:
    // Note that on_draw is actually overriding a virtual function
    // from the Gtk::Window class. I set it as virtual here in case
    // someone wants to override it again in a derived class.
    void on_button_clicked();
    virtual bool on_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr);
    void on_screen_changed(const Glib::RefPtr<Gdk::Screen>& previous_screen);
    bool on_window_clicked(GdkEventButton* event);

    // Member widgets:
    Gtk::Box _box;
    Gtk::Box _inner_box;
    Gtk::Alignment _alignment;
    Gtk::Button _button;
    Glib::RefPtr <Gtk::Adjustment> _adjustmentRed;
    Glib::RefPtr <Gtk::Adjustment> _adjustmentGreen;
    Glib::RefPtr <Gtk::Adjustment> _adjustmentBlue;
    Glib::RefPtr <Gtk::Adjustment> _adjustmentAlpha;

    Gtk::Scale _scaleRed;
    Gtk::Scale _scaleGreen;
    Gtk::Scale _scaleBlue;
    Gtk::Scale _scaleAlpha;

    // Fields
    bool _SUPPORTS_ALPHA = false;

    // Member methods
    long _round(double x);
};

#endif /* TRANSPARENTSLIDER_H_ */

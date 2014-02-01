/**
 * main.cpp
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
#include "transparent-slider.h"
#include <gtkmm/application.h>

int main (int argc, char *argv[])
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example.transparent");

    TransparentSlider transparent_slider;

    //Shows the window and returns when it is closed.
    return app->run(transparent_slider);
}

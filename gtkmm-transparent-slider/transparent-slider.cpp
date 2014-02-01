/**
 * transparent-slider.cpp
 *
 * Louis Melahn, L.C. January 31, 2014.
 */
#include "transparent-slider.h"

TransparentSlider::TransparentSlider() :
    _redInit(0.5),
    _greenInit(1),
    _blueInit(0.5),
    _alphaInit(0.5),
	_buttonLabel("Close"),
	_box(Gtk::ORIENTATION_VERTICAL),
	_inner_box(Gtk::ORIENTATION_HORIZONTAL),
	_alignment(Gtk::ALIGN_END, Gtk::ALIGN_END, 0.0, 0.0),
    _button(_buttonLabel),
    _adjustmentRed(Gtk::Adjustment::create(_redInit, 0, 1.0, 0.1, 0.1, 0)),
    _adjustmentGreen(Gtk::Adjustment::create(_greenInit, 0, 1.0, 0.1, 0.1, 0)),
    _adjustmentBlue(Gtk::Adjustment::create(_blueInit, 0, 1.0, 0.1, 0.1, 0)),
    _adjustmentAlpha(Gtk::Adjustment::create(_alphaInit, 0, 1.0, 0.1, 0.1, 0)),
    _scaleRed(_adjustmentRed, Gtk::ORIENTATION_VERTICAL),
    _scaleGreen(_adjustmentGreen, Gtk::ORIENTATION_VERTICAL),
    _scaleBlue(_adjustmentBlue, Gtk::ORIENTATION_VERTICAL),
    _scaleAlpha(_adjustmentAlpha, Gtk::ORIENTATION_VERTICAL)
{

    // Set up the top-level window.
	set_border_width(10);
    set_title("Color Slider Test");
    set_default_size(400,400);
    set_decorated(false);
    add_events(Gdk::BUTTON_PRESS_MASK);
    set_position(Gtk::WIN_POS_CENTER);
    set_app_paintable(true);

    // Signal handlers
    signal_draw().connect(sigc::mem_fun(*this, &TransparentSlider::on_draw));
    signal_screen_changed().connect(sigc::mem_fun(*this, &TransparentSlider::on_screen_changed));
    signal_button_press_event().connect(sigc::mem_fun(*this, &TransparentSlider::on_window_clicked));
    _button.signal_clicked().connect(sigc::mem_fun(*this, &TransparentSlider::on_button_clicked));

    // Widgets

    // Add the box and pack it.
    add(_box);
    _box.pack_start(_inner_box);
    _box.pack_start(_alignment);

    // Pack the inner box
    _inner_box.set_homogeneous();
    _inner_box.pack_start(_scaleRed);
    _inner_box.pack_start(_scaleGreen);
    _inner_box.pack_start(_scaleBlue);
    _inner_box.pack_start(_scaleAlpha);

    // Set up the scales:
    _scaleRed.set_digits(3);
    _scaleRed.set_inverted();
    _scaleGreen.set_digits(3);
    _scaleGreen.set_inverted();
    _scaleBlue.set_digits(3);
    _scaleBlue.set_inverted();
    _scaleAlpha.set_digits(3);
    _scaleAlpha.set_inverted();

    // Set up the close button
    _alignment.add(_button);
    _button.set_size_request(100, 10);

    // Initialize the process of drawing the colored part.
    on_screen_changed(get_screen());

    // Show the window and all its children.
    show_all_children();
}

TransparentSlider::~TransparentSlider()
{
}

void TransparentSlider::on_button_clicked()
{
    std::cout << "The '" << _buttonLabel << "' button was pressed." << std::endl;
    hide();
}

bool TransparentSlider::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    auto window = get_window();

    Cairo::RectangleInt window_size;
    Cairo::RectangleInt clip;
    double x1, y1, x2, y2;
    cr->get_clip_extents(x1, y1, x2, y2);

    clip.height = _round(y2-y1);
    clip.width = _round(x2-x1);
    clip.x = _round(x1);
    clip.y = _round(y1);

    window_size.x = 0;
    window_size.y = 0;
    window_size.height = window->get_height();
    window_size.width = window->get_width();

    cr->save();

    if (_SUPPORTS_ALPHA) {
        cr->set_source_rgba(                    // transparent
                _adjustmentRed->get_value(),
                _adjustmentGreen->get_value(),
                _adjustmentBlue->get_value(),
                _adjustmentAlpha->get_value());
    } else {
        cr->set_source_rgb(                     // opaque
                _adjustmentRed->get_value(),
                _adjustmentGreen->get_value(),
                _adjustmentBlue->get_value());
    }
    cr->set_operator(Cairo::OPERATOR_SOURCE);

    if (clip.height==window_size.height && clip.width==window_size.width && clip.x==window_size.x && clip.y==window_size.y) {
    } else {
        window->invalidate(true);
    }
    cr->reset_clip();
    cr->paint();
    cr->restore();

    return Gtk::Window::on_draw(cr);
}

/**
 * Checks to see if the display supports alpha channels
 */
void TransparentSlider::on_screen_changed(const Glib::RefPtr<Gdk::Screen>& previous_screen) {
	auto screen = get_screen();
    auto visual = screen->get_rgba_visual();

    if (!visual) {
    	std::cout << "Transparency is not supported." << std::endl;
    } else {
        std::cout << "Transparency is supported." << std::endl;
        _SUPPORTS_ALPHA = TRUE;
    }

    set_visual(visual);
}

/**
 * This simply adds a method which seems to be missing in Gtk::Widget,
 * so I had to use Gtk+ manually.
 *
 * Sets the visual for 'this' (the current widget).
 */
void TransparentSlider::set_visual(Glib::RefPtr<Gdk::Visual> visual) {
	gtk_widget_set_visual(GTK_WIDGET(gobj()), visual->gobj());
}

/**
 * I don't know if I really want to use this event. Perhaps I will remove it.
 */
bool TransparentSlider::on_window_clicked(GdkEventButton* event) {
	//set_decorated(!get_decorated());
	return false;
}

long TransparentSlider::_round(double x) {
    if( (x + 0.5) >= (static_cast<long>(x) + 1) ) {
        return static_cast<long>(x) + 1;
    } else {
        return static_cast<long>(x);
    }
}

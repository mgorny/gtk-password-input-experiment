#include <gtkmm.h>
#include <iostream>

class PasswordEntry : public Gtk::Entry {
	bool was_modified, ignore_event;
	Gdk::Color dimmed_text_color;

	bool on_focus_in_event(GdkEventFocus*) {
		if (!was_modified) {
			ignore_event = true;
			get_buffer()->set_text("");
			ignore_event = false;
			set_visibility(false);
			unset_text(Gtk::STATE_NORMAL);
		}

		return false;
	}

	bool on_focus_out_event(GdkEventFocus*) {
		if (!was_modified) {
			ignore_event = true;
			get_buffer()->set_text("[Password not displayed]");
			ignore_event = false;
			set_visibility(true);
			modify_text(Gtk::STATE_NORMAL, dimmed_text_color);
		}

		return false;
	}

	void on_changed() {
		if (!ignore_event)
			was_modified = true;
	}

public:
	PasswordEntry():
			Gtk::Entry(),
			was_modified(false),
			ignore_event(false),
			dimmed_text_color("gray")
	{
		this->on_focus_out_event(NULL);
	}
};

void clk() {
	std::cout << "click" << std::endl;
}

int main(int argc, char *argv[]) {
	Gtk::Main kit(argc, argv);

	Gtk::Window w;
	Gtk::VBox v;
	PasswordEntry e;
	Gtk::Button b("foo");

	e.set_size_request(400);

	w.set_border_width(10);
	e.show();
	b.show();
	v.show();

	v.add(b);
	v.add(e);
	w.add(v);

	b.signal_clicked().connect(sigc::ptr_fun(&clk));

	Gtk::Main::run(w);

	return 0;
}

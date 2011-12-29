#include <gtkmm.h>
#include <iostream>

class PasswordEntry : public Gtk::Entry {
	bool was_modified;
	sigc::connection entry_inserted_conn;

	void password_entry_inserted(const Glib::ustring s, int *len) {
		if (!was_modified) {
			get_buffer()->set_text(s);
			set_visibility(false);
			was_modified = true;
			entry_inserted_conn.disconnect();
		}
	}

public:
	PasswordEntry():
			Gtk::Entry(),
			was_modified(false)
	{
		get_buffer()->set_text("[Password not displayed]");
		entry_inserted_conn = signal_insert_text().connect(
				sigc::mem_fun(*this, &PasswordEntry::password_entry_inserted));
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

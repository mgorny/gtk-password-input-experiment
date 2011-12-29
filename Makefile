CXX = clang++
CPPFLAGS = $(shell pkg-config --cflags gtkmm-2.4)
LIBS = $(shell pkg-config --libs gtkmm-2.4)

m: m.c++
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $(LDFLAGS) $(LIBS) $<

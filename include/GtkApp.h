#ifndef KRYPTO_GTK_APP_H
#define KRYPTO_GTK_APP_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <vector>

#include "GtkMenuBar.h"

class GtkMapToolApp {
public:
    GtkMapToolApp();
    int run();
private:
    void initWindow();
private:
    struct{
        int width;
        int height;
    } m_windowSize;
    Glib::RefPtr<Gtk::Application> m_application;
    std::unique_ptr<Gtk::Window> m_window;
    Gtk::Box m_box;
    std::unique_ptr<GtkWindowMenuBar> m_menuBar;
};

#endif //KRYPTO_GTK_APP_H
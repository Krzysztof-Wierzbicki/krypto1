#ifndef KRYPTO_GTK_APP_H
#define KRYPTO_GTK_APP_H

#include <vector>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/textview.h>
#include <gtkmm/paned.h>
#include <gtkmm/button.h>

#include "GtkMenuBar.h"
#include "CipherInterface.h"

class GtkApp {
public:
    GtkApp();
    int run();
private:
    void initWindow();
private:
    struct{
        int width;
        int height;
    } m_windowSize;
    CipherInterface m_cipherInterface;
    Glib::RefPtr<Gtk::Application> m_application;
    std::unique_ptr<Gtk::Window> m_window;
    Gtk::Box m_box;
    Gtk::Paned m_paned, m_buttonBox;
    std::unique_ptr<GtkWindowMenuBar> m_menuBar;
    Gtk::TextView m_text;
    Gtk::Button m_encryptButton, m_decryptButton;
};

#endif //KRYPTO_GTK_APP_H
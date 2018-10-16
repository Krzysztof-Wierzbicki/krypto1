#ifndef KRYPTO_APPLICATION_H
#define KRYPTO_APPLICATION_H

#include <vector>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/textview.h>
#include <gtkmm/paned.h>
#include <gtkmm/button.h>
#include <gtkmm/scrolledwindow.h>

#include "MenuBar.h"
#include "CipherInterface.h"

class Application {
public:
    Application();
    int run();
private:
    void initWindow();
    void loadFile(const std::string& fileName);
    void handleEncrypt();
    void handleDecrypt();
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
    std::unique_ptr<MenuBar> m_menuBar;
    Gtk::TextView m_text;
    Gtk::Button m_encryptButton, m_decryptButton;
    Gtk::ScrolledWindow m_scrolled;
    CipherType m_cipherType;
};

#endif //KRYPTO_APPLICATION_H
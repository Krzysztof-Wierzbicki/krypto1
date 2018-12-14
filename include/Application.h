#ifndef KRYPTO_APPLICATION_H
#define KRYPTO_APPLICATION_H

#include <vector>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/textview.h>
#include <gtkmm/paned.h>
#include <gtkmm/button.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/grid.h>
#include <gtkmm/entry.h>
#include <gtkmm/filechooser.h>
#include <gtkmm/filechooserwidget.h>

#include "MenuBar.h"
#include "CipherInterface.h"

class Application {
public:
    Application();
    int run();
private:
    void initWindow();
    void loadKey(const std::string &fileName);
    void keyGen(std::string q, std::string p, std::string g);
    void handleEncrypt();
    void handleDecrypt();
    void setInputMethod(IOMethod method);
    void setOutputMethod(IOMethod method);
private:
    struct{
        int width;
        int height;
    } m_windowSize;
    CipherInterface m_cipherInterface;
    Glib::RefPtr<Gtk::Application> m_application;
    std::unique_ptr<Gtk::Window> m_window;
    Gtk::Box m_bigBox, m_buttonBox;
    Gtk::Paned m_paned, m_outPaned;
    Gtk::Grid m_keyBox;
    Gtk::Entry m_key1, m_key2, m_key3, m_outFile;
    std::unique_ptr<MenuBar> m_menuBar;
    Gtk::Button m_encryptButton, m_decryptButton;
    CipherType m_cipherType;
    IOMethod m_inputMethod, m_outputMethod;

    Gtk::TextView m_inText, m_outText;
    Gtk::ScrolledWindow m_inScrolled, m_outScrolled;
    Gtk::FileChooserWidget m_inChooser, m_outChooser;
};

#endif //KRYPTO_APPLICATION_H
#ifndef KRYPTO_GTK_WINDOW_MENU_BAR_H
#define KRYPTO_GTK_WINDOW_MENU_BAR_H

#include <vector>
#include <gtkmm/menubar.h>
#include <gtkmm/menu.h>
#include <gtkmm/radiomenuitem.h>
#include "CipherInterface.h"

class MenuBar : public Gtk::MenuBar{

public:
    MenuBar();
    void onLoadFile(Gtk::Window &window, std::function<void(const std::string&)> responseHandler);
    void onCipherChange(std::function<void(CipherType)> responseHandler);
private:
    Gtk::MenuItem m_file, m_openFile, m_cipher;
    Gtk::RadioMenuItem m_stream, m_dsa, m_des;
    Gtk::Menu m_fileSubmenu, m_cipherSubmenu;
    Gtk::RadioButtonGroup m_radioGroup;
};

#endif //KRYPTO_GTK_WINDOW_MENU_BAR_H
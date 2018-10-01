#ifndef KRYPTO_GTK_WINDOW_MENU_BAR_H
#define KRYPTO_GTK_WINDOW_MENU_BAR_H

#include <gtkmm/menubar.h>
#include <gtkmm/menu.h>
#include <vector>

class GtkWindowMenuBar : public Gtk::MenuBar{

public:
    GtkWindowMenuBar();
private:
    Gtk::MenuItem m_testSubmenu, m_test;
    Gtk::Menu m_menu;
};

#endif //KRYPTO_GTK_WINDOW_MENU_BAR_H
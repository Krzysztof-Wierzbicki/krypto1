#include <gtkmm/entry.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/filechooserdialog.h>
#include "GtkMenuBar.h"

GtkWindowMenuBar::GtkWindowMenuBar(){
    std::setlocale(LC_NUMERIC, "en_US.UTF-8");

    //main menu
    m_testSubmenu.set_label("TestSubmenu");
    m_testSubmenu.set_submenu(m_menu);
    this->append(m_testSubmenu);

    //submenu File
    m_test.set_label("Test");
    m_menu.append(m_test);
}

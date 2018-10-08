#include <vector>
#include <GtkApp.h>
#include "GtkApp.h"

GtkApp::GtkApp()
        : m_windowSize{1200, 800}
        , m_application(Gtk::Application::create())
        , m_box(Gtk::Orientation::ORIENTATION_VERTICAL)
        , m_paned(Gtk::Orientation::ORIENTATION_VERTICAL)
        , m_buttonBox(Gtk::Orientation::ORIENTATION_HORIZONTAL) {

    m_window = std::make_unique<Gtk::Window>();
    m_menuBar = std::make_unique<GtkWindowMenuBar>();

    initWindow();
}

int GtkApp::run() {
    return m_application->run(*m_window);
}

void GtkApp::initWindow() {
    m_box.pack_start(*m_menuBar, Gtk::PackOptions::PACK_SHRINK);
    m_box.pack_start(m_paned, Gtk::PackOptions::PACK_EXPAND_WIDGET);
    m_paned.add1(m_text);
    m_paned.add2(m_buttonBox);
    m_buttonBox.add1(m_encryptButton);
    m_buttonBox.add2(m_decryptButton);
    m_encryptButton.set_label("Encrypt");
    m_decryptButton.set_label("Decrypt");

    m_window->resize(m_windowSize.width, m_windowSize.height);
    m_window->add(m_box);
    m_window->show_all_children();
    m_window->set_size_request(200, 120);

    m_window->signal_check_resize().connect([this]{
        int width, height;
        m_window->get_size(width, height);
        m_windowSize.width = width;
        m_windowSize.height = height;
        m_paned.set_position(m_windowSize.height - 80);
        m_buttonBox.set_position(m_windowSize.width/2);
    });
}
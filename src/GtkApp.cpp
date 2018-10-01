#include <vector>
#include "GtkApp.h"

GtkMapToolApp::GtkMapToolApp()
        : m_windowSize{1200, 800}
        , m_application(Gtk::Application::create())
        , m_box(Gtk::Orientation::ORIENTATION_HORIZONTAL) {

    m_window = std::make_unique<Gtk::Window>();
    m_menuBar = std::make_unique<GtkWindowMenuBar>();

    initWindow();
}

int GtkMapToolApp::run() {
    return m_application->run(*m_window);
}

void GtkMapToolApp::initWindow() {
    m_box.pack_start(*m_menuBar, Gtk::PackOptions::PACK_SHRINK);

    m_window->resize(m_windowSize.width, m_windowSize.height);
    m_window->add(m_box);
    m_window->show_all_children();

    m_window->signal_check_resize().connect([this]{
        int width, height;
        m_window->get_size(width, height);
        m_windowSize.width = width;
        m_windowSize.height = height;
    });
}
#include <vector>
#include <fstream>
#include "Application.h"

Application::Application()
        : m_windowSize{1200, 800}
        , m_application(Gtk::Application::create())
        , m_box(Gtk::Orientation::ORIENTATION_VERTICAL)
        , m_paned(Gtk::Orientation::ORIENTATION_VERTICAL)
        , m_buttonBox(Gtk::Orientation::ORIENTATION_HORIZONTAL)
        , m_cipherType(CipherType::Stream) {

    m_window = std::make_unique<Gtk::Window>();
    m_menuBar = std::make_unique<MenuBar>();

    initWindow();
    m_menuBar->onLoadFile(*m_window, [this](const auto& s){ this->loadFile(s); });
    m_menuBar->onCipherChange([this](const CipherType& type){
        m_cipherType = type;
    });
}

int Application::run() {
    return m_application->run(*m_window);
}

void Application::initWindow() {
    m_box.pack_start(*m_menuBar, Gtk::PackOptions::PACK_SHRINK);
    m_box.pack_start(m_paned, Gtk::PackOptions::PACK_EXPAND_WIDGET);
    m_paned.add1(m_scrolled);
    m_paned.add2(m_buttonBox);
    m_scrolled.add(m_text);
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

    m_encryptButton.signal_clicked().connect([this](){ handleEncrypt(); });
    m_decryptButton.signal_clicked().connect([this](){ handleDecrypt(); });
}

void Application::loadFile(const std::string& fileName) {
    try{
        auto file = std::ifstream(fileName);
        std::string text;
        while(file.good()){
            char* tmp = new char[1000];
            file.read(tmp, 1000);
            text += std::string(tmp, tmp+999);
        }
        m_text.get_buffer()->set_text(text);
    }catch(...){}
}

void Application::handleEncrypt(){
    auto text = m_text.get_buffer()->get_text();
    std::vector<uint8_t> inBytes;
    inBytes.reserve(text.size());
    for(auto c : text){
        inBytes.push_back(c);
    }

    std::vector<uint8_t> outBytes;
    switch(m_cipherType){
        case CipherType::Stream:
            outBytes = m_cipherInterface.encrypt<CipherType::Stream>(inBytes);
            break;
        case CipherType::DSA:
            outBytes = m_cipherInterface.encrypt<CipherType::DSA>(inBytes);
            break;
        case CipherType::DES:
            outBytes = m_cipherInterface.encrypt<CipherType::DES>(inBytes);
            break;
    }

    std::string outText(outBytes.begin(), outBytes.end());
    m_text.get_buffer()->set_text(outText);
}

void Application::handleDecrypt(){
    //m_cipherInterface.encrypt(m_text.get_buffer()->get_text(), m_cipherType);
}
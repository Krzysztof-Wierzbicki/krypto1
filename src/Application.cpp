#include <vector>
#include <fstream>
#include "Application.h"
#include "TrippleDes.h"

Application::Application()
        : m_windowSize{1200, 800}
        , m_application(Gtk::Application::create())
        , m_bigBox(Gtk::Orientation::ORIENTATION_VERTICAL)
        , m_paned(Gtk::Orientation::ORIENTATION_HORIZONTAL)
        , m_buttonBox(Gtk::Orientation::ORIENTATION_HORIZONTAL)
        , m_cipherType(CipherType::Stream){

    m_window = std::make_unique<Gtk::Window>();
    m_menuBar = std::make_unique<MenuBar>();

    initWindow();
    setInputMethod(IOMethod::Text);
    setOutputMethod(IOMethod::Text);
    m_menuBar->onLoadKey(*m_window, [this](const auto &s) { this->loadKey(s); });
    m_menuBar->onCipherChange([this](const CipherType& type){
        m_cipherType = type;
        switch(m_cipherType){
            case CipherType::Stream:
                m_key1.set_tooltip_text("Generator");
                m_key1.set_placeholder_text("Generator");
                m_key2.set_tooltip_text("Prime");
                m_key2.set_placeholder_text("Prime");
                m_key3.set_tooltip_text("Seed");
                m_key3.set_placeholder_text("Seed");
                break;
            case CipherType::DSA:
                //TODO: same as above
                break;
            case CipherType::DES:
                m_key1.set_tooltip_text("Key1");
                m_key1.set_placeholder_text("Key1");
                m_key2.set_tooltip_text("Key2");
                m_key2.set_placeholder_text("Key2");
                m_key3.set_tooltip_text("Key3");
                m_key3.set_placeholder_text("Key");
                break;
        }
    });
    m_menuBar->onInputMethodChange([this](IOMethod method){ setInputMethod(method); });
    m_menuBar->onOutputMethodChange([this](IOMethod method){ setOutputMethod(method); });
}

int Application::run() {
    return m_application->run(*m_window);
}

void Application::initWindow() {
    m_bigBox.pack_start(*m_menuBar, Gtk::PackOptions::PACK_SHRINK);
    m_bigBox.pack_start(m_keyBox, Gtk::PackOptions::PACK_SHRINK);
    m_bigBox.pack_start(m_paned, Gtk::PackOptions::PACK_EXPAND_WIDGET);
    m_bigBox.pack_end(m_buttonBox, Gtk::PackOptions::PACK_SHRINK);

    m_inScrolled.add(m_inText);
    m_outScrolled.add(m_outText);

    m_buttonBox.pack_start(m_encryptButton);
    m_buttonBox.pack_end(m_decryptButton);
    m_encryptButton.set_label("Encrypt");
    m_decryptButton.set_label("Decrypt");
    m_keyBox.attach(m_key1, 0, 0, 1, 1);
    m_keyBox.attach(m_key2, 1, 0, 1, 1);
    m_keyBox.attach(m_key3, 2, 0, 1, 1);
    m_key1.set_has_tooltip(true);
    m_key2.set_has_tooltip(true);
    m_key3.set_has_tooltip(true);
    m_keyBox.set_column_homogeneous(true);
    m_keyBox.set_column_spacing(10);
    m_keyBox.set_margin_start(10);
    m_keyBox.set_margin_end(10);
    m_keyBox.set_margin_top(15);
    m_keyBox.set_margin_bottom(15);

    m_window->resize(m_windowSize.width, m_windowSize.height);
    m_window->add(m_bigBox);
    m_window->show_all_children();
    m_window->set_size_request(200, 220);
    m_buttonBox.set_size_request(200, 60);

    m_window->signal_check_resize().connect([this]{
        int width, height;
        m_window->get_size(width, height);
        m_windowSize.width = width;
        m_windowSize.height = height;
        m_paned.set_position(m_windowSize.width/2);
    });

    m_encryptButton.signal_clicked().connect([this](){ handleEncrypt(); });
    m_decryptButton.signal_clicked().connect([this](){ handleDecrypt(); });
}

void Application::loadKey(const std::string &fileName) {
    try{
        auto file = std::ifstream(fileName);

        char* tmp = new char[257];
        file.getline(tmp, 257);
        m_key1.set_text(std::string(tmp, 256));
        file.getline(tmp, 257);
        m_key2.set_text(std::string(tmp, 256));
        file.getline(tmp, 257);
        m_key3.set_text(std::string(tmp, 256));
    }catch(...){}
}

void Application::handleEncrypt(){
    std::vector<uint8_t> inBytes;
    std::vector<wchar_t> testBytes;
    if(m_inputMethod == IOMethod::Text){
        Glib::ustring inText = m_inText.get_buffer()->get_text();
        inBytes.reserve(inText.size());
        for(auto c : inText){
            inBytes.push_back(c);
        }
        for(size_t i=0; i<inText.length(); i++){
            testBytes.push_back(inText[i]);
        }
    }else{
        if(m_inChooser.get_filename().empty()){
            throw std::logic_error("Application: input file not chosen");
        }
        std::ifstream inStream(m_inChooser.get_filename());
        while(inStream.good()){
            uint8_t c;
            inStream.get(reinterpret_cast<char&>(c));
            inBytes.push_back(c);
        }
    };

    std::vector<uint8_t> outBytes;
    switch(m_cipherType){
        case CipherType::Stream:
            outBytes = m_cipherInterface.encrypt<CipherType::Stream>(inBytes);
            break;
        case CipherType::DSA:
            outBytes = m_cipherInterface.encrypt<CipherType::DSA>(inBytes);
            break;
        case CipherType::DES:
            TrippleDES des(0x0E329232EA6D0D73, 0x0E329232EA6D0D73, 0x0E329232EA6D0D73);
            // TrippleDES des(std::stoi(m_key1.get_buffer()->get_text()),
            //                std::stoi(m_key2.get_buffer()->get_text()),
            //                std::stoi(m_key3.get_buffer()->get_text()));    
            outBytes = des.encrypt(inBytes);
            break;
    }

    if(m_outputMethod == IOMethod::Text){
        Glib::ustring outText;
        std::transform(outBytes.begin(), outBytes.end(), std::back_inserter(outText), [](auto x){ return x; });
        m_outText.get_buffer()->set_text(outText);
    }else{
        if(m_outChooser.get_filename().empty()){
            throw std::logic_error("Application: output file not chosen");
        }
        std::ofstream outStream(m_outChooser.get_filename());
        outStream.write(reinterpret_cast<char*>(outBytes.data()), outBytes.size());
    }
}

void Application::handleDecrypt(){
    std::vector<uint8_t> inBytes;
    std::vector<wchar_t> testBytes;
    if(m_inputMethod == IOMethod::Text){
        Glib::ustring inText = m_inText.get_buffer()->get_text();
        inBytes.reserve(inText.size());
        for(auto c : inText){
            inBytes.push_back(c);
        }
        for(size_t i=0; i<inText.length(); i++){
            testBytes.push_back(inText[i]);
        }
    }else{
        if(m_inChooser.get_filename().empty()){
            throw std::logic_error("Application: input file not chosen");
        }
        std::ifstream inStream(m_inChooser.get_filename());
        while(inStream.good()){
            uint8_t c;
            inStream.get(reinterpret_cast<char&>(c));
            inBytes.push_back(c);
        }
    };

    std::vector<uint8_t> outBytes;
    switch(m_cipherType){
        case CipherType::Stream:
            outBytes = m_cipherInterface.encrypt<CipherType::Stream>(inBytes);
            break;
        case CipherType::DSA:
            outBytes = m_cipherInterface.encrypt<CipherType::DSA>(inBytes);
            break;
        case CipherType::DES:
            TrippleDES des(0x0E329232EA6D0D73, 0x0E329232EA6D0D73, 0x0E329232EA6D0D73);
            // TrippleDES des(std::stoi(m_key1.get_buffer()->get_text()),
            //                std::stoi(m_key2.get_buffer()->get_text()),
            //                std::stoi(m_key3.get_buffer()->get_text()));    
            outBytes = des.decrypt(inBytes);
            break;
    }

    if(m_outputMethod == IOMethod::Text){
        Glib::ustring outText;
        std::transform(outBytes.begin(), outBytes.end(), std::back_inserter(outText), [](auto x){ return x; });
        m_outText.get_buffer()->set_text(outText);
    }else{
        if(m_outChooser.get_filename().empty()){
            throw std::logic_error("Application: output file not chosen");
        }
        std::ofstream outStream(m_outChooser.get_filename());
        outStream.write(reinterpret_cast<char*>(outBytes.data()), outBytes.size());
    }
}

void Application::setInputMethod(IOMethod method) {
    m_inputMethod = method;
    if(method == IOMethod::Text){
        m_paned.remove(m_inChooser);
        m_paned.add1(m_inScrolled);
    }else {
        m_paned.remove(m_inScrolled);
        m_paned.add1(m_inChooser);
    }
    m_window->check_resize();
    m_window->show_all_children();
}

void Application::setOutputMethod(IOMethod method) {
    m_outputMethod = method;
    if(method == IOMethod::Text){
        m_paned.remove(m_outChooser);
        m_paned.add2(m_outScrolled);
    }else{
        m_paned.remove(m_outScrolled);
        m_paned.add2(m_outChooser);
    }
    m_window->check_resize();
    m_window->show_all_children();
}

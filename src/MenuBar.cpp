#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/filechooserdialog.h>
#include <MenuBar.h>

#include "MenuBar.h"

MenuBar::MenuBar(){
    std::setlocale(LC_NUMERIC, "en_US.UTF-8");

    //main menu
    m_file.set_label("File");
    m_file.set_submenu(m_fileSubmenu);
    this->append(m_file);
    m_cipher.set_label("Cipher");
    m_cipher.set_submenu(m_cipherSubmenu);
    this->append(m_cipher);
    m_input.set_label("Input");
    m_input.set_submenu(m_inputSubmenu);
    this->append(m_input);
    m_output.set_label("Output");
    m_output.set_submenu(m_outputSubmenu);
    this->append(m_output);
    m_generate.set_label("Generate");
    m_generate.set_submenu(m_generateSubmenu);
    this->append(m_generate);

    //submenu File
    m_openKey.set_label("Open key file");
    m_fileSubmenu.append(m_openKey);

    //submenu cipher
    m_des.set_label("3DES");
    m_des.set_group(m_cipherGroup);
    m_cipherSubmenu.append(m_des);
    m_stream.set_label("Stream");
    m_stream.set_group(m_cipherGroup);
    m_cipherSubmenu.append(m_stream);
    m_dsa.set_label("DSA");
    m_dsa.set_group(m_cipherGroup);
    m_cipherSubmenu.append(m_dsa);

    //submenu Input
    m_iText.set_label("Text");
    m_iText.set_group(m_inputGroup);
    m_inputSubmenu.append(m_iText);
    m_iFile.set_label("File");
    m_iFile.set_group(m_inputGroup);
    m_inputSubmenu.append(m_iFile);

    //submenu Output
    m_oText.set_label("Text");
    m_oText.set_group(m_outputGroup);
    m_outputSubmenu.append(m_oText);
    m_oFile.set_label("File");
    m_oFile.set_group(m_outputGroup);
    m_outputSubmenu.append(m_oFile);

    //submenu Generate
    m_generateDSA.set_label("Generate DSA params");
    m_generateSubmenu.append(m_generateDSA);
}

void MenuBar::onLoadKey(Gtk::Window &window, std::function<void(const std::string &)> responseHandler) {
    m_openKey.signal_activate().connect([&window, responseHandler = std::move(responseHandler)]{
        Gtk::FileChooserDialog* dialog = new Gtk::FileChooserDialog("Choose key file", Gtk::FILE_CHOOSER_ACTION_OPEN);
        dialog->set_transient_for(window);
        dialog->set_select_multiple();

        dialog->add_button("Cancel", Gtk::RESPONSE_CANCEL);
        dialog->add_button("Open", Gtk::RESPONSE_OK);

        int result = dialog->run();

        switch(result) {
            case(Gtk::RESPONSE_OK):
                responseHandler(dialog->get_filename());
                break;
        }
        delete dialog;
    });
}

void MenuBar::onCipherChange(std::function<void(CipherType)> responseHandler) {
    m_des.signal_activate().connect([responseHandler]{ responseHandler(CipherType::DES); });
    m_stream.signal_activate().connect([responseHandler]{ responseHandler(CipherType::Stream); });
    m_dsa.signal_activate().connect([responseHandler]{ responseHandler(CipherType::DSA); });
}

void MenuBar::onInputMethodChange(std::function<void(IOMethod)> responseHandler) {
    m_iFile.signal_activate().connect([responseHandler]{ responseHandler(IOMethod::File); });
    m_iText.signal_activate().connect([responseHandler]{ responseHandler(IOMethod::Text); });
}

void MenuBar::onOutputMethodChange(std::function<void(IOMethod)> responseHandler) {
    m_oFile.signal_activate().connect([responseHandler]{ responseHandler(IOMethod::File); });
    m_oText.signal_activate().connect([responseHandler]{ responseHandler(IOMethod::Text); });
}

void MenuBar::onGenerateDSA(std::function<void(CipherType)> responseHandler) {
    m_generateDSA.signal_activate().connect([responseHandler]{ responseHandler(CipherType::DSA); });
}
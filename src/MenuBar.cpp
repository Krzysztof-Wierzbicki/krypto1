#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/filechooserdialog.h>
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

    //submenu File
    m_openFile.set_label("Open");
    m_fileSubmenu.append(m_openFile);

    //submenu cipher
    m_des.set_label("3DES");
    m_des.set_group(m_radioGroup);
    m_cipherSubmenu.append(m_des);
    m_stream.set_label("Stream");
    m_stream.set_group(m_radioGroup);
    m_cipherSubmenu.append(m_stream);
    m_dsa.set_label("DSA");
    m_dsa.set_group(m_radioGroup);
    m_cipherSubmenu.append(m_dsa);
}

void MenuBar::onLoadFile(Gtk::Window &window, std::function<void(const std::string&)> responseHandler) {
    m_openFile.signal_activate().connect([&window, responseHandler = std::move(responseHandler)]{
        Gtk::FileChooserDialog* dialog = new Gtk::FileChooserDialog("Choose file", Gtk::FILE_CHOOSER_ACTION_OPEN);
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

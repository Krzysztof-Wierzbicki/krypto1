#ifndef KRYPTO_MENU_BAR_H
#define KRYPTO_MENU_BAR_H

#include <vector>
#include <gtkmm/menubar.h>
#include <gtkmm/menu.h>
#include <gtkmm/radiomenuitem.h>
#include "CipherInterface.h"

enum class IOMethod{
    File,
    Text,
};

class MenuBar : public Gtk::MenuBar{

public:
    MenuBar();
    void onLoadKey(Gtk::Window &window, std::function<void(const std::string &)> responseHandler);
    void onCipherChange(std::function<void(CipherType)> responseHandler);
    void onInputMethodChange(std::function<void(IOMethod)> responseHandler);
    void onOutputMethodChange(std::function<void(IOMethod)> responseHandler);
    void onGenerateDSA(std::function<void(CipherType)> responseHandler);
private:
    Gtk::MenuItem m_file, m_openKey, m_cipher, m_input, m_output, m_generate, m_generateDSA;
    Gtk::RadioMenuItem m_stream, m_dsa, m_des, m_iFile, m_iText, m_oFile, m_oText;
    Gtk::Menu m_fileSubmenu, m_cipherSubmenu, m_inputSubmenu, m_outputSubmenu, m_generateSubmenu;
    Gtk::RadioButtonGroup m_cipherGroup, m_inputGroup, m_outputGroup;
};

#endif //KRYPTO_MENU_BAR_H
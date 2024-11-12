#ifndef NOTES_CONFIG_H
#define NOTES_CONFIG_H

#include <filesystem>

namespace fs = std::filesystem;

class Config {
  public:
    Config();
    fs::path configDir;
    fs::path groupDir;
    fs::path indexFile;

    void add_group (std::string name);
    void add_note (std::string name);
    void add_note_ingroup (std::string name, std::string group_name);
    void select_group (std::string name);
    void select_note (std::string name);
    void getselected_group ();
    std::string GetSelected_Note ();
  private:
    const char* homeDir;
    void init ();
    
};


#endif

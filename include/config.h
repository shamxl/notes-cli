#ifndef NOTES_CONFIG_H
#define NOTES_CONFIG_H

#include <filesystem>

namespace fs = std::filesystem;

class Config {
  public:
    Config();
    fs::path configDir;
    fs::path indexFile;

    void Add_Group (std::string name);
    void Add_Note (std::string name);
    void Add_Note_InGroup (std::string name, std::string group_name);
    void Select_Group (std::string name);
    void Select_Note (std::string name);
    std::string GetSelected_Group ();
    std::string GetSelected_Note ();
  private:
    const char* homeDir;
    void init ();
    
};


#endif

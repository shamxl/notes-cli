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

  private:
    const char* homeDir;
    void init ();
    
};


#endif

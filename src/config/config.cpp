#include "config.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>

Config::Config () {
  init();
}

void Config::init () {
  homeDir = getenv("HOME");

  if (homeDir == nullptr) {
    std::cerr << "Could not retrieve `HOME` env variable" << std::endl;
  }

  configDir = (std::string) homeDir + "/.notes";
  indexFile = (std::string) configDir + "/index.json";
  groupDir = (std::string) configDir + "/groups";
  if (!fs::exists(configDir)) {
    fs::create_directory(configDir);
  }

  if (!fs::exists(groupDir)) {
    fs::create_directory(groupDir);
  }

  if (!fs::exists(indexFile)) {
    std::ofstream ofile (indexFile);

    if (ofile.is_open()) {
      ofile << "{\"groups\": {}}";
    } else {
      std::cerr << "Failed to create `index.json` at " << configDir << std::endl;
    }
    
    ofile.close();
  }
}

#include <condition_variable>
#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "config.h"
#include "nlohmann/json_fwd.hpp"
#include <nlohmann/json.hpp>

Config::Config() {
  init ();
}

void Config::init () {
  homeDir = getenv ("HOME");

  if (homeDir != nullptr) {
    configDir = std::string(homeDir) + "/.notes";
    indexFile = (std::string) configDir + "/index.json";


    if (!fs::exists (configDir)) {
      // create .notes dir at home if it doesnt exists
      fs::create_directory(configDir);
      fs::create_directory((std::string) configDir + "/groups");
    }

    if (!fs::exists(indexFile)) {
      // creates index file at .notes dir if it doesnt exists

      std::ofstream ifile (indexFile);
      if (ifile.is_open()) {
       
        ifile << "{}";
        ifile.close();

      } else {
        // failed to create index file. :( 
        
        std::cout << "Failed to create index file at: " << indexFile << std::endl;
      }
    }
  
  } else {
    std::cout << "Failed to retrieve `HOME` env variable." << std::endl;
  }
}


void Config::add_group (std::string name) {
  std::ifstream ifile (indexFile);
  nlohmann::json data = nlohmann::json::parse(ifile);
  
  if (!data.contains("groups")) {
    data["groups"] = nlohmann::json::object();
  }
 
  if (!data["groups"].contains(name)) {
    std::string path = (std::string) configDir + "/" + "groups/" + name + "/";
    data["groups"][name] = path;

    fs::create_directory(path);

  } else {
    std::cout << "Group already exists." << std::endl;
    std::exit (1);
  }

  ifile.close();
  std::ofstream ofile(indexFile);
  
  if (ofile.is_open()) {
    ofile << data.dump(2);
    ofile.close();
    std::cout << "Done." << std::endl;
  } else {
    std::cout << "Failed." << std::endl;
    std::exit(1);
  }


}

void Config::add_note (std::string name) {
}

void Config::add_note_ingroup (std::string name, std::string group_name) {
}

void Config::select_note (std::string name) {}

void Config::getselected_group () {
  std::ifstream ifile(indexFile);
  nlohmann::json data = nlohmann::json::parse(ifile);
  if (data.contains("selected_group")) {
    std::cout << "Selected group: " << data["selected_group"] << std::endl;;
  } else {
    std::cout << "No group selected";
  }

  ifile.close();
}

void Config::select_group (std::string name) {

  std::ifstream ifile (indexFile);
  nlohmann::json data = nlohmann::json::parse(ifile);
  
  if (data["groups"].contains(name)) {
    data["selected_group"] = name;
    ifile.close();
  } else {
    std::cout << "No such group." << std::endl;
    std::exit(1);
  }


  std::ofstream ofile (indexFile);
  ofile << data.dump(2);
  ofile.close();

  std::cout << "selected group: " << name << std::endl;
}



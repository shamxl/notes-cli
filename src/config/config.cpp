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


void Config::Add_Group (std::string name) {
  std::ifstream ifile (indexFile);
  nlohmann::json data = nlohmann::json::parse(ifile);
  
  if (!data.contains("groups")) {
    data["groups"] = nlohmann::json::object();
  }
 
  if (!data["groups"].contains(name)) {
    data["groups"][name] = (std::string) configDir + "/" + name + "/";
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

void Config::Add_Note (std::string name) {
}

void Config::Add_Note_InGroup (std::string name, std::string group_name) {
}


std::string Config::GetSelected_Group () {
  std::ifstream ifile(indexFile);
  nlohmann::json data = nlohmann::json::parse(ifile);
  if (data.contains("selected_group")) {
    return data["selected_group"];
  } else {
    return nullptr;
  }

  ifile.close();
}

void Config::Select_Group (std::string name) {

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



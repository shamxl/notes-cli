#include "helpers.h"
#include "config.h"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

namespace Helpers {

  nlohmann::json data;
  Config config;
  void load_config () {
    std::ifstream ifile (config.indexFile);
    data = nlohmann::json::parse(ifile);
    if (!data.contains("groups")) {
      data["groups"] = nlohmann::json::object();
    }
  }

  void save_config () {
    std::ofstream ofile(config.indexFile);
    if (!ofile.is_open()) {
      std::cerr << "Failed to save config file" << std::endl;
    }
    ofile << data.dump(2);
    ofile.close();
  }

  bool create_group (std::string name) {
    if (data["groups"].contains(name)) {
      return false;
    }

    std::string group_path = std::string (config.groupDir) + "/" + name;

    data["groups"][name] = {
      {"path", group_path},
      {"notes", nlohmann::json::object()}
    };

    if (!fs::create_directory(group_path)) {
      return false;
    }

    save_config();
    return true;
  }

  bool select_group (std::string name) {
    if (!data["groups"].contains(name)) {
      return false;
    } 
    data["selected_group"] = name;
    save_config();
    return true;
  }

  bool create_note (std::string name, std::string group_name) {
    nlohmann::json& cur_group = data["groups"][group_name];
    nlohmann::json& notes = cur_group["notes"];

    if (notes.contains(name)) {
      return false;
    }

    if (notes.contains(name)) {
      return false;
    }

    std::string note_path = std::string (cur_group["path"]) + "/" + name + ".txt";
    

    std::ofstream ofile (note_path);
    ofile.close();
    
    notes[name] = note_path;

    save_config ();
    return true;
  }

  bool select_note (std::string name, std::string group_name) {
    if (!data["groups"][group_name]["notes"].contains(name)) {
      return false;
    }
    data["groups"][group_name]["selected_note"] = name;
    save_config ();
    return true;
  }

  bool write_to_note(std::string name, std::string group_name, std::vector<std::string> &notes) {
    nlohmann::json& cur_group = data["groups"][group_name];
    nlohmann::json& cur_note = cur_group["notes"][name];

    std::ofstream ofile((std::string) cur_note, std::ios::app);
    if (ofile.is_open()) {
      for (const auto& val : notes) {
        ofile << val << " ";
      }

      ofile << "\n";
    } else {
      return false;
    }

    ofile.close();
    return true;
  }

  std::string get_selected_group () {
    if (!data.contains("selected_group")) {
      return std::string();
    }

    return data["selected_group"];
  }

  std::string get_selected_note (std::string group_name) {
    nlohmann::json& cur_group = data["groups"][group_name];
    if (!cur_group.contains("selected_note")) {
      return std::string();
    } 
    
    return cur_group["selected_note"];
  }

  std::string get_note_path(std::string group_name, std::string note_name) {
    nlohmann::json& notes = data["groups"][group_name]["notes"];
    if (!notes.contains(note_name)) {
      return std::string();
    } 

    return notes[note_name];
  }

  bool delete_group(std::string name) {
    
    nlohmann::json& groups = data["groups"];
    if (!groups.contains(name)) {
      return false;
    } 
    
    nlohmann::json& cur_group = groups[name];
    fs::remove_all (cur_group["path"]);
    groups.erase (name);
    if (get_selected_group() == name) {
      data["selected_group"] = "";
    }
    save_config ();
    return true;
  }

  bool delete_note(std::string group_name, std::string note_name) {
    nlohmann::json& groups = data["groups"];
    if (!groups.contains(group_name)) {
      return false;
    }

    nlohmann::json& notes = groups[group_name]["notes"];
    if (!notes.contains(note_name)) {
      return false;
    }

    std::string note_path = get_note_path(group_name, note_name);
    notes.erase(note_name);
    fs::remove (note_path);
    save_config();
    return true;
  }
} 



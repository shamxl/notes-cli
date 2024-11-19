#include <fstream>
#include <iostream>
#include <argparse/argparse.hpp>
#include <string>
#include "parser.h"
#include "helpers.h"

int main (int argc, char* argv[]) {
  argparse::ArgumentParser cli ("Notes");
  init_arguments (cli);

  try {
    cli.parse_args(argc, argv);
  } catch (std::exception& _err) {
    std::cout << cli << std::endl;
    std::exit(1);
  }
  
  
  Helpers::load_config();
  

  if (auto value = cli.present("-ng")) {
    std::cout << (Helpers::create_group(*value) ? "Group created: " : "Group already exists: ") << *value << std::endl; 
    if (cli["-s"] == true) {
      Helpers::select_group(*value);
    }
  } else if (auto value = cli.present ("-sg")) {
    std::cout << (Helpers::select_group(*value) ? "Selected group: " : "Group doesn't exists: ") << *value << std::endl;
  } else if (auto value = cli.present("-nn")) {
    std::string selected_group = Helpers::get_selected_group();
    if (selected_group.empty()) {
      std::cout << "Select a group first!" << std::endl;
    } else {
      
    } 
    
    if (Helpers::create_note(*value, selected_group)) {
      std::cout << "Created note \"" << *value << "\" in group \"" << selected_group << "\"" << std::endl;
    } else {
      std::cout << "Note \"" << *value << "\" already exists in group \"" << selected_group << "\"" << std::endl;
    }

    if (cli["-s"] == true) {
      Helpers::select_note(*value, selected_group);
    }
    
  } else if (auto value = cli.present ("-sn")) {
    std::string selected_group = Helpers::get_selected_group();
    if (selected_group.empty()) {
      std::cout << "Select a group first!" << std::endl;
      std::exit (1);
    }
    bool select_status = Helpers::select_note(*value, selected_group);
    std::cout << (select_status ? "Selected note: " : "Note doesn't exists: ") << *value << std::endl;
  } else if (cli["-p"] == true) {
    std::string selected_group = Helpers::get_selected_group();
    if (selected_group.empty()) {
      std::cout << "Select a group first!" << std::endl;
      std::exit(1);
    }
    
    std::string selected_note = Helpers::get_selected_note(selected_group);

    if (selected_note.empty()) {
      std::cout << "Select a note first!" << std::endl;
      std::exit(1);
    }

    std::string path = Helpers::get_note_path(selected_group, selected_note);
    
    std::ifstream ifile(path);
    std::string line;

    while (std::getline(ifile, line)) {
      std::cout << line << std::endl;
    }

    ifile.close();

  } else {
    try {
      auto notes = cli.get<std::vector<std::string>>("notes");
      std::string selected_group = Helpers::get_selected_group();
      if (selected_group.empty()) {
        std::cout << "Select a group first!" << std::endl;
        std::exit(1);
      }
      std::string selected_note = Helpers::get_selected_note(selected_group);
      if (selected_note.empty()) {
        std::cout << "No note selected in group: " << selected_group << std::endl;
        std::exit(1);
      }

      bool write_status = Helpers::write_to_note(selected_note, selected_group, notes);

      if (!write_status) {
        std::cout << "Writing failed." << std::endl;
      } else {
        std::cout << "Wrote to:" << std::endl;
        std::cout << "  note: " << selected_note << std::endl;
        std::cout << "  group: " << selected_group << std::endl;
      }
    } catch (nlohmann::json::exception& _e) {
      cli.help();
    }
  }

  return 0;
}



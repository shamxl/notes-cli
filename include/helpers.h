#ifndef NOTES_HELPERS_H
#define NOTES_HELPERS_H

#include <nlohmann/json.hpp>
namespace  Helpers {
  void load_config ();
  void save_config ();
  bool create_group (std::string name);
  bool select_group (std::string name);
  bool create_note (std::string name, std::string group_name);
  bool select_note (std::string name, std::string group_name);
  bool write_to_note (std::string name, std::string group_name, std::vector<std::string> &notes);
  std::string get_selected_group ();
  std::string get_selected_note (std::string group_name);
  
  std::string get_note_path (std::string group_name, std::string note_name);
  bool delete_group (std::string name);
  bool delete_note (std::string group_name, std::string note_name);
}

#endif

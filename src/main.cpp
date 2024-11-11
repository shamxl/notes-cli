#include <iostream>
#include <argparse/argparse.hpp>
#include "config.h"
#include "parser.h"

int main (int argc, char* argv[]) {
  argparse::ArgumentParser cli ("Notes");
  init_arguments (cli);
  Config config;

  try {
    cli.parse_args(argc, argv);
  } catch (std::exception& _err) {
    std::cout << cli << std::endl;
    std::exit(1);
  }

  std::string command = cli.get<std::string>("command");

  if (cli["--new"] == true) {
    
    if (cli["--group"] == true) {
      config.add_group(command);
    }
    if (cli["--note"] == true) {
      config.add_note(command);
    }

  } else if (cli["--select"] == true) {

    if (cli["--note"] == true) {
      config.select_note(command);
    }
    if (cli["--group"] == true) {
      config.select_group(command);
    }

  } else if (cli["--group"] == true) {
      config.getselected_group();
  } else if (cli["--note"] == true) {
    std::cout << "No note selected" << std::endl;
  } else {}


  return 0;
}



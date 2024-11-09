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


  if (cli["--select"] == true && cli["--group"] == true) {
    config.Select_Group(command);
    std::exit(0);
  }


  return 0;
}



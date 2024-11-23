#include <argparse/argparse.hpp>
#include "parser.h"

void init_arguments (argparse::ArgumentParser & cli) {
  
  cli.add_argument ("--new-note", "-nn");
  cli.add_argument ("--new-group", "-ng");
  cli.add_argument ("--select-group", "-sg");
  cli.add_argument ("--select-note", "-sn");
  cli.add_argument ("--select", "-s")
    .help ("Select a group or note immediately after creation.")
    .flag();

  cli.add_argument("--list", "-l")
    .help ("List notes inside a group.")
    .flag();

  cli.add_argument("--delete-group", "-dg")
    .help ("Deletes the specified group");

  cli.add_argument("--delete-note", "-dn")
    .help ("Deletes the specified note from the selected group");

  cli.add_argument("--print", "-p")
    .help ("Print the selected note")
    .flag();

  cli.add_argument ("notes")
    .remaining();
}

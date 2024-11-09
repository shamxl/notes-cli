#include <argparse/argparse.hpp>
#include "parser.h"

void init_arguments (argparse::ArgumentParser & cli) {
  
  cli.add_argument ("--new", "-N")
    .help ("Create a new note/group")
    .flag ();

  cli.add_argument ("--note", "-n")
    .flag ();

  cli.add_argument ("--group", "-g")
    .flag ();

  cli.add_argument ("--select", "-s")
    .flag ();

  cli.add_argument ("--delete", "-D")
    .flag ();



  cli.add_argument ("command");

}

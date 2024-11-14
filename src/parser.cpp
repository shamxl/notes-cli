#include <argparse/argparse.hpp>
#include "parser.h"

void init_arguments (argparse::ArgumentParser & cli) {
  
  cli.add_argument ("--new-note", "-nn");
  cli.add_argument ("--new-group", "-ng");
  cli.add_argument ("--select-group", "-sg");
  cli.add_argument ("--select-note", "-sn");
  cli.add_argument ("note").remaining();
}

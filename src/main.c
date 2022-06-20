#include "./Control/Control.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  execute_control();
  return 0;
}

#include "utils.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

int main(const int argc, const char *argv[]) {
  if (argc < 2)
    return EXIT_FAILURE;

  printf("Hello World!\n");

  const char *filename = argv[1];

  //

  return 0;
}

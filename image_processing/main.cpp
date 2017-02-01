#include "utils.h"
#include "file.h"

using namespace std;

int main(int argc, char **argv) {

  if (argc < 2) {
    fprintf(stderr, "%s", "Need to pass at least 3 args");
  }

  Pixel* DATA_STREAM;

  DATA_STREAM = fileRead(argv[1]);

  cout << "GOOD" << endl;

  return 0;
}

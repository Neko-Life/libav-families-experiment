#include <cstdint>
#include <cstdio>
#include "opus/opus.h"
#include "opus/opusfile.h"

#define OPEN_FILE ""

int main() {
  printf("Hello World!");

  int status;
  OggOpusFile  *of = op_open_file(OPEN_FILE,&status);
  int32_t samp_rate = 48000;
  int channels = 2;

  // init decoder
  /* int error; */
  /* OpusDecoder *dec; */
  /* dec = opus_decoder_create(samp_rate, channels, &error); */

  return 0;
}

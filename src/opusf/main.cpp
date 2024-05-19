#include "opus/opus.h"
#include "opus/opusfile.h"
#include "utils.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

int main(const int argc, const char *argv[]) {
  if (argc < 2)
    return EXIT_FAILURE;

  printf("Hello World!\n");

  const char *filename = argv[1];

  int status;
  ogg_int64_t duration;

  // to get duration we need to seek
  int output_seekable;

  OggOpusFile *of = op_open_file(filename, &status);

  if (of == NULL) {
    fprintf(stderr, "Failed to open file '%s': %i\n", filename, status);
    return EXIT_FAILURE;
  }

  duration = 0;
  output_seekable = fseek(stdout, 0, SEEK_CUR) != -1;
  if (op_seekable(of)) {
    opus_int64 size;
    duration = op_pcm_total(of, -1);
    fprintf(stderr, "Total duration: ");
    print_duration(stderr, duration, 3);
    fprintf(stderr, " (%li samples @ 48 kHz)\n", (long)duration);
    size = op_raw_total(of, -1);
    fprintf(stderr, "Total size: ");
    print_size(stderr, size, 0, "");
    fprintf(stderr, " bytes: %lld", size);
    fprintf(stderr, "\n");
  }

  int32_t samp_rate = 48000;
  int channels = 2;

  // init decoder
  /* int error; */
  /* OpusDecoder *dec; */
  /* dec = opus_decoder_create(samp_rate, channels, &error); */

  op_free(of);
  of = NULL;

  return 0;
}

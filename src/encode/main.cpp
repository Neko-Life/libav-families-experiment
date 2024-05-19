#include "opus/opus.h"
#include "opus/opusfile.h"
#include "opus_defines.h"
#include "utils.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

// 20ms per frame
#define FRAME_SIZE 960
#define SAMPLING_RATE 48000
#define MAX_PACKET (1500)

int main(const int argc, const char *argv[]) {

  int error;
  OpusEncoder *enc;
  enc = opus_encoder_create(SAMPLING_RATE, 2, OPUS_APPLICATION_AUDIO, &error);

  unsigned char packet[MAX_PACKET + 257];
  int len;

  ssize_t sread = 0;
  opus_int16 inbuf[FRAME_SIZE];
  while ((sread = read(STDIN_FILENO, inbuf, FRAME_SIZE)) > 0) {
    len = opus_encode(enc, inbuf, FRAME_SIZE, packet, MAX_PACKET);
    if (len < 0 || len > MAX_PACKET) {
      fprintf(stderr, "opus_encode() returned %d\n", len);
      return -1;
    }
    write(STDOUT_FILENO, packet, len);
  }

  opus_encoder_destroy(enc);

  return 0;
}

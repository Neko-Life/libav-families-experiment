#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "opus/opusfile.h"

void print_duration(FILE *_fp, ogg_int64_t _nsamples, int _frac);

void print_size(FILE *_fp, opus_int64 _nbytes, int _metric,
                const char *_spacer);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // UTILS_H

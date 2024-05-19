#include "utils.h"

void print_duration(FILE *_fp, ogg_int64_t _nsamples, int _frac) {
  ogg_int64_t seconds;
  ogg_int64_t minutes;
  ogg_int64_t hours;
  ogg_int64_t days;
  ogg_int64_t weeks;
  _nsamples += _frac ? 24 : 24000;
  seconds = _nsamples / 48000;
  _nsamples -= seconds * 48000;
  minutes = seconds / 60;
  seconds -= minutes * 60;
  hours = minutes / 60;
  minutes -= hours * 60;
  days = hours / 24;
  hours -= days * 24;
  weeks = days / 7;
  days -= weeks * 7;
  if (weeks)
    fprintf(_fp, "%liw", (long)weeks);
  if (weeks || days)
    fprintf(_fp, "%id", (int)days);
  if (weeks || days || hours) {
    if (weeks || days)
      fprintf(_fp, "%02ih", (int)hours);
    else
      fprintf(_fp, "%ih", (int)hours);
  }
  if (weeks || days || hours || minutes) {
    if (weeks || days || hours)
      fprintf(_fp, "%02im", (int)minutes);
    else
      fprintf(_fp, "%im", (int)minutes);
    fprintf(_fp, "%02i", (int)seconds);
  } else
    fprintf(_fp, "%i", (int)seconds);
  if (_frac)
    fprintf(_fp, ".%03i", (int)(_nsamples / 48));
  fprintf(_fp, "s");
}

void print_size(FILE *_fp, opus_int64 _nbytes, int _metric,
                const char *_spacer) {
  static const char SUFFIXES[7] = {' ', 'k', 'M', 'G', 'T', 'P', 'E'};
  opus_int64 val;
  opus_int64 den;
  opus_int64 round;
  int base;
  int shift;
  base = _metric ? 1000 : 1024;
  round = 0;
  den = 1;
  for (shift = 0; shift < 6; shift++) {
    if (_nbytes < den * base - round)
      break;
    den *= base;
    round = den >> 1;
  }
  val = (_nbytes + round) / den;
  if (den > 1 && val < 10) {
    if (den >= 1000000000)
      val = (_nbytes + (round / 100)) / (den / 100);
    else
      val = (_nbytes * 100 + round) / den;
    fprintf(_fp, "%li.%02i%s%c", (long)(val / 100), (int)(val % 100), _spacer,
            SUFFIXES[shift]);
  } else if (den > 1 && val < 100) {
    if (den >= 1000000000)
      val = (_nbytes + (round / 10)) / (den / 10);
    else
      val = (_nbytes * 10 + round) / den;
    fprintf(_fp, "%li.%i%s%c", (long)(val / 10), (int)(val % 10), _spacer,
            SUFFIXES[shift]);
  } else
    fprintf(_fp, "%li%s%c", (long)val, _spacer, SUFFIXES[shift]);
}

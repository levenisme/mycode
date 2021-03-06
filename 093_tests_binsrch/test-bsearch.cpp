#include <math.h>

#include <cstdio>
#include <cstdlib>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high);
template<typename T>
class SinFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};
template<typename T>
class Arrangearray : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return arg; }
};
template<typename T>
class CountedIntFn : public Function<int, int>
{
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};
void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  int invoke = 0;
  if (high > low) {
    invoke = log(high - low) / log(2) + 1;
  }
  else {
    invoke = 1;
  }
  CountedIntFn<int> * con = new CountedIntFn<int>(invoke, f, mesg);
  int ans = binarySearchForZero(con, low, high);
  if (ans != expected_ans) {
    fprintf(stderr, "%s", mesg);
    exit(EXIT_FAILURE);
  }
}
int main() {
  SinFunction<int> * sin = new SinFunction<int>();
  Arrangearray<int> * arr = new Arrangearray<int>();
  check(sin, 0, 150000, 52359, "sin fail");
  check(arr, -2, 1, 0, "arr fail 1");
  check(arr, -2, -1, -2, "arr fail 2");
  check(arr, -100, -1, -2, "arr fail3");
  check(arr, 1, 100, 1, "arr fail 4");
  check(arr, -1, -1, -1, "arr fail 5");
  check(arr, 3, 2, 3, "arr fail 6");
  check(arr, -6776987, -23, -24, "arr fail 7");
  check(arr, -5678998, 1, 0, "arr fail 8");
  check(arr, -99999999, -1, -2, "arr fail 9");
  check(arr, -1, 10000000, 0, "arr fail 10");
  check(arr, 1, 10000000, 1, "arr fail 11");
  check(arr, -99999999, 10000000, 0, "arr fail 12");
}

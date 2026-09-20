#include <cstdint>
#include <cstdio>
#include <cstring>
#include <unistd.h>

#define R(mul, shift, x, y)                                                    \
  do {                                                                         \
    _ = (x);                                                                   \
    (x) -= (mul) * (y) >> (shift);                                             \
    (y) += (mul) * _ >> (shift);                                               \
    _ = (3145728 - (x) * (x) - (y) * (y)) >> 11;                               \
    (x) = (x) * _ >> 10;                                                       \
    (y) = (y) * _ >> 10;                                                       \
  } while (0)

std::int8_t b[1760];
std::int8_t z[1760];

int main() {
  int sA = 1024;
  int cA = 0;
  int sB = 1024;
  int cB = 0;
  int _;

  std::printf("\x1b[?25l"); // Hide cursor
  std::printf("\x1b[2J\x1b[H");

  for (;;) {
    std::memset(b, 32, sizeof b);
    std::memset(z, 127, sizeof z);

    int sj = 0;
    int cj = 1024;

    for (int j = 0; j < 90; j++) {
      int si = 0;
      int ci = 1024;

      for (int i = 0; i < 324; i++) {
        int R1 = 1;
        int R2 = 2048;
        int K2 = 5120 * 1024;

        int x0 = R1 * cj + R2;
        int x1 = ci * x0 >> 10;
        int x2 = cA * sj >> 10;
        int x3 = si * x0 >> 10;
        int x4 = R1 * x2 - (sA * x3 >> 10);
        int x5 = sA * sj >> 10;
        int x6 = K2 + R1 * 1024 * x5 + cA * x3;
        int x7 = cj * si >> 10;
        int x = 40 + 30 * (cB * x1 - sB * x4) / x6;
        int y = 12 + 15 * (cB * x4 + sB * x1) / x6;

        int N = (((-cA * x7 - cB * (((-sA * x7) >> 10) + x2) -
                   ci * ((cj * sB) >> 10)) >>
                  10) -
                 x5) >>
                7;

        int o = x + 80 * y;
        std::int8_t zz = static_cast<std::int8_t>((x6 - K2) >> 15);

        if (22 > y && y > 0 && x > 0 && 80 > x && zz < z[o]) {
          z[o] = zz;

          const char shades[] = ".,-~:;=!*#$@";
          b[o] = static_cast<std::int8_t>(shades[N > 0 ? N : 0]);
        }

        R(5, 8, ci, si);
      }

      R(9, 7, cj, sj);
    }

    for (int k = 0; k < 1760; k++) {
      std::putchar(k % 80 ? b[k] : '\n');
    }

    std::fflush(stdout);

    R(5, 7, cA, sA);
    R(5, 8, cB, sB);

    usleep(15000);
    std::printf("\x1b[H\x1b[2J");
  }
}

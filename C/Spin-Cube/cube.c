#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

enum { WIDTH = 80, HEIGHT = 44, BUFFER_SIZE = WIDTH * HEIGHT };

static float A = 0.0f;
static float B = 0.0f;
static float C = 0.0f;

static const float K1 = 40.0f;
static const float INCREMENT_SPEED = 0.6f;
static const float DISTANCE_FROM_CAM = 100.0f;

static float zBuffer[BUFFER_SIZE];
static char buffer[BUFFER_SIZE];

static float calculateX(float i, float j, float k) {
  return j * sinf(A) * sinf(B) * cosf(C) - k * cosf(A) * sinf(B) * cosf(C) +
         j * cosf(A) * sinf(C) + k * sinf(A) * sinf(C) + i * cosf(B) * cosf(C);
}

static float calculateY(float i, float j, float k) {
  return j * cosf(A) * cosf(C) + k * sinf(A) * cosf(C) -
         j * sinf(A) * sinf(B) * sinf(C) + k * cosf(A) * sinf(B) * sinf(C) -
         i * cosf(B) * sinf(C);
}

static float calculateZ(float i, float j, float k) {
  return k * cosf(A) * cosf(B) - j * sinf(A) * cosf(B) + i * sinf(B);
}

static void calculateForSurface(float cubeX, float cubeY, float cubeZ,
                                float horizontalOffset, char character) {
  const float x = calculateX(cubeX, cubeY, cubeZ);
  const float y = calculateY(cubeX, cubeY, cubeZ);
  const float z = calculateZ(cubeX, cubeY, cubeZ) + DISTANCE_FROM_CAM;

  const float oneOverZ = 1.0f / z;

  const int xp =
      (int)((float)WIDTH / 2.0f + horizontalOffset + K1 * oneOverZ * x * 2.0f);

  const int yp = (int)((float)HEIGHT / 2.0f + K1 * oneOverZ * y);

  if (xp < 0 || xp >= WIDTH || yp < 0 || yp >= HEIGHT) {
    return;
  }

  const int index = xp + yp * WIDTH;

  if (oneOverZ > zBuffer[index]) {
    zBuffer[index] = oneOverZ;
    buffer[index] = character;
  }
}

static void drawCube(float cubeWidth, float horizontalOffset) {
  for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += INCREMENT_SPEED) {
    for (float cubeY = -cubeWidth; cubeY < cubeWidth;
         cubeY += INCREMENT_SPEED) {
      calculateForSurface(cubeX, cubeY, -cubeWidth, horizontalOffset, '@');

      calculateForSurface(cubeWidth, cubeY, cubeX, horizontalOffset, '$');

      calculateForSurface(-cubeWidth, cubeY, -cubeX, horizontalOffset, '~');

      calculateForSurface(-cubeX, cubeY, cubeWidth, horizontalOffset, '#');

      calculateForSurface(cubeX, -cubeWidth, -cubeY, horizontalOffset, ';');

      calculateForSurface(cubeX, cubeWidth, cubeY, horizontalOffset, '+');
    }
  }
}

int main(void) {
  /*
   * Clear the terminal, move the cursor home, and hide the cursor.
   */
  fputs("\x1b[2J\x1b[H\x1b[?25l", stdout);
  fflush(stdout);

  for (;;) {
    memset(buffer, ' ', sizeof buffer);
    memset(zBuffer, 0, sizeof zBuffer);

    /*
     * Draw three separated cubes.
     * The offsets are screen-column offsets relative to the center.
     */

    drawCube(10.0f, 0.0f);

    /*
     * Move home before writing the next frame.
     */
    fputs("\x1b[H", stdout);

    for (int k = 0; k < BUFFER_SIZE; ++k) {
      putchar((k % WIDTH == 0) ? '\n' : buffer[k]);
    }

    fflush(stdout);

    A += 0.05f;
    B += 0.05f;
    C += 0.01f;

    usleep(16000);
  }

  return 0;
}

#include <chrono>
#include <cmath>
#include <cstring>
#include <iostream>
#include <thread>

constexpr int WIDTH = 80;
constexpr int HEIGHT = 44;
constexpr int BUFFER_SIZE = WIDTH * HEIGHT;

static float A = 0.0f;
static float B = 0.0f;
static float C = 0.0f;

constexpr float K1 = 40.0f;
constexpr float INCREMENT_SPEED = 0.6f;
constexpr float DISTANCE_FROM_CAM = 100.0f;

static float zBuffer[BUFFER_SIZE];
static char buffer[BUFFER_SIZE];

static float calculateX(float i, float j, float k) {
  return j * std::sin(A) * std::sin(B) * std::cos(C) -
         k * std::cos(A) * std::sin(B) * std::cos(C) +
         j * std::cos(A) * std::sin(C) + k * std::sin(A) * std::sin(C) +
         i * std::cos(B) * std::cos(C);
}

static float calculateY(float i, float j, float k) {
  return j * std::cos(A) * std::cos(C) + k * std::sin(A) * std::cos(C) -
         j * std::sin(A) * std::sin(B) * std::sin(C) +
         k * std::cos(A) * std::sin(B) * std::sin(C) -
         i * std::cos(B) * std::sin(C);
}

static float calculateZ(float i, float j, float k) {
  return k * std::cos(A) * std::cos(B) - j * std::sin(A) * std::cos(B) +
         i * std::sin(B);
}

static void calculateForSurface(float cubeX, float cubeY, float cubeZ,
                                float horizontalOffset, char character) {
  const float x = calculateX(cubeX, cubeY, cubeZ);
  const float y = calculateY(cubeX, cubeY, cubeZ);
  const float z = calculateZ(cubeX, cubeY, cubeZ) + DISTANCE_FROM_CAM;

  const float oneOverZ = 1.0f / z;

  const int xp = static_cast<int>(static_cast<float>(WIDTH) / 2.0f +
                                  horizontalOffset + K1 * oneOverZ * x * 2.0f);

  const int yp =
      static_cast<int>(static_cast<float>(HEIGHT) / 2.0f + K1 * oneOverZ * y);

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

int main() {
  // Clear the terminal, move the cursor home, and hide the cursor.
  std::cout << "\x1b[2J\x1b[H\x1b[?25l";
  std::cout.flush();

  while (true) {
    std::memset(buffer, ' ', sizeof(buffer));
    std::memset(zBuffer, 0, sizeof(zBuffer));

    drawCube(10.0f, 0.0f);

    // Move the cursor home before writing the next frame.
    std::cout << "\x1b[H";

    for (int k = 0; k < BUFFER_SIZE; ++k) {
      if (k % WIDTH == 0) {
        std::cout << '\n';
      } else {
        std::cout << buffer[k];
      }
    }

    std::cout.flush();

    A += 0.05f;
    B += 0.05f;
    C += 0.01f;

    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }

  return 0;
}

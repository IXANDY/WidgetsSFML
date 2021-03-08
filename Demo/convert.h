//
// Created by ixandy on 2/22/2021.
//

#ifndef WIDGETS_DEMO_CONVERT_H
#define WIDGETS_DEMO_CONVERT_H

#include <cstdlib>

float rgbToXyzFunc(float x) {
  if (x - 0.04045 >= 0) {
    return std::pow(((x + 0.055) / 1.055), 2.4f);
  } else {
    return x / 12.92f;
  }
}
float xyzToRgbFunc(float x) {
  if (x - 0.0031308 >= 0) {
    return (1.055f * std::pow(x, 1 / 2.4f) - 0.055f);
  } else {
    return 12.92f * x;
  }
}

float xyzToLabFunc(float x) {
  if (x - 0.008856 >= 0) {
    return std::pow(x, 1 / 3.f);
  } else {
    return (7.787f * x + 16 / 116.f);
  }
}
float labToXyzFunc(float x) {
  if (std::pow(x, 3) - 0.008856 >= 0) {
    return std::pow(x, 3);
  } else {
    return (x - 16 / 116.f) / 7.787f;
  }
}

std::vector<float> rgbToCmyk(const std::vector<float> &);
std::vector<float> rgbToLab(const std::vector<float> &);
std::vector<float> cmykToRgb(const std::vector<float> &);
std::vector<float> cmykToLab(const std::vector<float> &);
std::vector<float> labToCmyk(const std::vector<float> &);
std::vector<float> labToRgb(const std::vector<float> &);

std::vector<float> rgbToXyz(const std::vector<float> &);
std::vector<float> xyzToRgb(const std::vector<float> &);

std::vector<float> labToXyz(const std::vector<float> &);
std::vector<float> xyzToLab(const std::vector<float> &);

std::vector<float> rgbToCmyk(const std::vector<float> &color) {
  float red = color[0] / 255, green = color[1] / 255, blue = color[2] / 255;
  float key = 1 - std::max(std::max(red, blue), green);
  float cyan = (1 - red - key) / (1 - key);
  float magenta = (1 - green - key) / (1 - key);
  float yellow = (1 - blue - key) / (1 - key);
  return {cyan * 100, magenta * 100, yellow * 100, key * 100};
}
std::vector<float> cmykToRgb(const std::vector<float> &color) {
  float key = color[3] / 100, cyan = color[0] / 100, magenta = color[1] / 100, yellow = color[2] / 100;
  float red = 255 * (1 - cyan) * (1 - key);
  float green = 255 * (1 - magenta) * (1 - key);
  float blue = 255 * (1 - yellow) * (1 - key);
  return {red, green, blue};
}

std::vector<float> rgbToLab(const std::vector<float> &color) {
  return xyzToLab(rgbToXyz(color));
}
std::vector<float> labToRgb(const std::vector<float> &color) {
  return xyzToRgb(labToXyz(color));
}

std::vector<float> cmykToLab(const std::vector<float> &color) {
  return rgbToLab(cmykToRgb(color));
}
std::vector<float> labToCmyk(const std::vector<float> &color) {
  return rgbToCmyk(labToRgb(color));
}

std::vector<float> rgbToXyz(const std::vector<float> &color) {
  float red = color[0], green = color[1], blue = color[2];

  float rN = rgbToXyzFunc(red / 255) * 100;
  float gN = rgbToXyzFunc(green / 255) * 100;
  float bN = rgbToXyzFunc(blue / 255) * 100;

  float x = 0.412453f * rN + 0.357580f * gN + 0.180423f * bN;
  float y = 0.212671f * rN + 0.715160f * gN + 0.072169f * bN;
  float z = 0.019334f * rN + 0.119193f * gN + 0.950227f * bN;

  return {x, y, z};
}
std::vector<float> xyzToRgb(const std::vector<float> &color) {
  float x = color[0], y = color[1], z = color[2];

  float rN = 3.2406f * x / 100 - 1.5372f * y / 100 - 0.4986f * z / 100;
  float gN = -0.9689f * x / 100 + 1.8758f * y / 100 + 0.0415f * z / 100;
  float bN = 0.0557f * x / 100 - 0.2040f * y / 100 + 1.0570f * z / 100;

  float red = xyzToRgbFunc(rN) * 255;
  float green = xyzToRgbFunc(gN) * 255;
  float blue = xyzToRgbFunc(bN) * 255;

  return {red, green, blue};
}

std::vector<float> xyzToLab(const std::vector<float> &color) {
  float x = color[0], y = color[1], z = color[2];
  float l = 116 * xyzToLabFunc(y / 100.f) - 16;
  float a = 500 * (xyzToLabFunc(x / 95.047f) - xyzToLabFunc(y / 100.f));
  float b = 200 * (xyzToLabFunc(y / 100.f) - xyzToLabFunc(z / 108.883f));

  return {l, a, b};
}
std::vector<float> labToXyz(const std::vector<float> &color) {
  float l = color[0], a = color[1], b = color[2];
  float y = labToXyzFunc((l + 16) / 116.f) * 95.047f;
  float x = labToXyzFunc(a / 500 + (l + 16) / 116.f) * 100.f;
  float z = labToXyzFunc((l + 16) / 116.f - b / 200.f) * 108.883f;

  return {x, y, z};
}

#endif //WIDGETS_DEMO_CONVERT_H

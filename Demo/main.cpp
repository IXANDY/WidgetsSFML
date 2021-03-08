#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include "../Slider.h"
#include "../TextBox.h"
#include "../Palette.h"
#include "ColorSystem.h"
#include "convert.h"

int main() {

  sf::RenderWindow window(sf::VideoMode(1000, 300), "RGB", sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(100);

  Palette palette;

  sf::Image icon;
  icon.loadFromFile("RGB.png");

  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  ColorSystem rgb(3,
                  {46, 20},
                  {"0", "0", "0"},
                  6,
                  {255, 8},
                  {2, 10},
                  {0, 0, 0},
                  {0, 0, 0},
                  {255, 255, 255},
                  {1, 1, 1},
                  "UniversCondensed.ttf");
  rgb.move(300, 175);

  ColorSystem lab(3,
                  {46, 20},
                  {"0", "0", "0"},
                  6,
                  {255, 8},
                  {2, 10}, {0, 0, 0},
                  {0, -128, -128},
                  {100, 127, 127},
                  {1, 1, 1},
                  "UniversCondensed.ttf");
  lab.move(300, 50);

  ColorSystem cmyk(4,
                   {46, 20},
                   {"0", "0", "0", "0"},
                   6,
                   {255, 8},
                   {2, 10},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {100, 100, 100, 100},
                   {1, 1, 1, 1},
                   "UniversCondensed.ttf");
  cmyk.move(650, 50);

  TextBox rgbText({30, 20}, "RGB", 4);
  rgbText.setFontSize(18);
  rgbText.setFontColor(sf::Color::Black);
  rgbText.loadFont("UniversCondensed.ttf");
  rgbText.setLoadedFont();
  rgbText.move(300, 150);

  TextBox labText({30, 20}, "Lab", 4);
  labText.setFontSize(18);
  labText.setFontColor(sf::Color::Black);
  labText.loadFont("UniversCondensed.ttf");
  labText.setLoadedFont();
  labText.move(300, 25);

  TextBox cmykText({45, 20}, "CMYK", 4);
  cmykText.setFontSize(18);
  cmykText.setFontColor(sf::Color::Black);
  cmykText.loadFont("UniversCondensed.ttf");
  cmykText.setLoadedFont();
  cmykText.move(650, 25);

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {

      palette.handleEvents(event);
      rgb.handleEvents(event);
      lab.handleEvents(event);
      cmyk.handleEvents(event);

      if (palette.changed) {
        sf::Vector3f color = palette.getColor();
        std::vector<float> newColor = {color.x, color.y, color.z};
        rgb.setColor(newColor);
        lab.setColor(rgbToLab(newColor));
        cmyk.setColor(rgbToCmyk(newColor));
        palette.changed = false;
      }
      if (rgb.changed) {
        auto newColor = rgb.getColor();
        lab.setColor(rgbToLab(newColor));
        cmyk.setColor(rgbToCmyk(newColor));
        rgb.changed = false;
      }
      if (lab.changed) {
        auto newColor = lab.getColor();
        rgb.setColor(labToRgb(newColor));
        cmyk.setColor(labToCmyk(newColor));
        lab.changed = false;
      }
      if (cmyk.changed) {
        auto newColor = cmyk.getColor();
        rgb.setColor(cmykToRgb(newColor));
        lab.setColor(cmykToLab(newColor));
        cmyk.changed = false;
      }

      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::Resized) {

        float screenWidth = event.size.width;
        float screenHeight = event.size.height;

        window.setView(sf::View(sf::FloatRect(0, 0, screenWidth, screenHeight)));
      }
    }
    auto color = rgb.getColor();
    window.clear(sf::Color(color[0], color[1], color[2]));

    window.draw(palette);
    window.draw(rgb);
    window.draw(lab);
    window.draw(cmyk);
    window.draw(rgbText);
    window.draw(labText);
    window.draw(cmykText);

    window.display();
  }
  return 0;
}
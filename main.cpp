#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include "Slider.h"

int main() {

  sf::RenderWindow window(sf::VideoMode(700, 700), "My window");
  window.setFramerateLimit(100);

  Slider slider;
  slider.move(70, 70);
  slider.scale(2, 2);

  Slider slider1({100, 5}, {2, 8}, 0, 0, 100, 1);
  slider1.scale(3, 3);

  while (window.isOpen()) {
    sf::Event event{};

    while (window.pollEvent(event)) {

      slider.handleEvents(event);
      slider1.handleEvents(event);
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::Resized) {

        float screenWidth = event.size.width;
        float screenHeight = event.size.height;

        window.setView(sf::View(sf::FloatRect(0, 0, screenWidth, screenHeight)));
      }
    }
    window.clear();

    window.draw(slider);
    window.draw(slider1);

    window.display();
  }
  return 0;
}
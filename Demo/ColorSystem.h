//
// Created by ixandy on 3/2/2021.
//

#ifndef WIDGETS_DEMO_COLORSYSTEM_H_
#define WIDGETS_DEMO_COLORSYSTEM_H_

#include "../Widget.h"
#include "../TextBox.h"
#include "../Slider.h"

class ColorSystem : public Widget {
  std::vector<TextBox> texts;
  std::vector<Slider> sliders;

  void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  static bool isFloat(const std::string &string);

 public:

  bool changed;
  ColorSystem(int num,
              const sf::Vector2f &textSize,
              const std::vector<std::string> &textValue,
              unsigned int maxTextLength,
              const sf::Vector2f &lineSize,
              const sf::Vector2f &handleSize,
              const std::vector<float> &values,
              const std::vector<float> &minValues,
              const std::vector<float> &maxValues,
              const std::vector<float> &valueSteps,
              const std::string &fontPath);
  void handleEvents(const sf::Event &event);
  std::vector<float> getColor();
  void setColor(const std::vector<float> &color);
};

#endif //WIDGETS_DEMO_COLORSYSTEM_H_

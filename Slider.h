//
// Created by ixandy on 2/16/2021.
//

#ifndef UNTITLED_SLIDER_H
#define UNTITLED_SLIDER_H

#include "Widget.h"

class Slider : public Widget {

 private:

  sf::RectangleShape sliderLine;
  sf::RectangleShape sliderHandle;
  Widget::State curState;

  float value;
  float minValue;
  float maxValue;
  float valueStep;

  void onMouseMoved(const sf::Event &event);
  void onMouseButtonPressed(const sf::Event &event);
  void onMouseReleased(const sf::Event &event);
  void onKeyPressed(const sf::Event &event);

  void updateHandlePosition();

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

 protected:

  bool setValue(const sf::Vector2f &mousePosition);
  bool checkValue(float value);

 public:

  bool changed;
  Slider();
  Slider(const sf::Vector2f &lineSize,
         const sf::Vector2f &handleSize,
         float value,
         float minValue,
         float maxValue,
         float valueStep);

  Slider(float lineSizeX,
         float lineSizeY,
         float handleSizeX,
         float handleSizeY,
         float value,
         float minValue,
         float maxValue,
         float valueStep);

  Slider(const Slider &copy);

  void handleEvents(const sf::Event &event);
  bool setValue(float value);
  float getValue();
  float getMinValue();
  float getMaxValue();

  enum TextPosition {
    Left,
    Right,
    Bottom,
    Top
  };

};

#endif //UNTITLED_SLIDER_H

//
// Created by ixandy on 3/2/2021.
//

#ifndef WIDGETS__PALETTE_H_
#define WIDGETS__PALETTE_H_

#include "Widget.h"

class Palette : public Widget {

  sf::VertexArray paletteSurface;
  sf::VertexArray paletteSlider;
  sf::RectangleShape paletteBox;

  Widget::State curState;

  sf::Vector3f color;
  sf::Vector3f paletteSliderColor;

  sf::Vector2f paletteColorPosition;
  sf::Vector2f sliderColorPosition;

  sf::Vector2f palettePosition;
  sf::Vector2f sliderPosition;

  void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  void updatePaletteSurface();
  void updatePaletteSurfaceValue();
  void updateSliderValue();
  void onMouseMoved(const sf::Event &event);
  void onMouseButtonPressed(const sf::Event &event);
  void onMouseButtonReleased(const sf::Event &event);

 public:

  Palette();
  void handleEvents(const sf::Event &event);
  const sf::Vector3f &getColor();
  bool changed;
};

#endif //WIDGETS__PALETTE_H_

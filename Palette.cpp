//
// Created by ixandy on 3/2/2021.
//

#include "Palette.h"
Palette::Palette() :
    paletteSurface(sf::Points, 65536),
    paletteSlider(sf::Lines, 504),
    Widget(290, 258),
    paletteBox() {
  paletteColorPosition = {255, 0};
  palettePosition = {2, 2};
  sliderColorPosition = {270, 2};
  sliderPosition = {270, 2};
  curState = Widget::State::Idle;
  paletteBox.setSize({290, 258});
  paletteBox.setFillColor(sf::Color(128, 128, 64));
  paletteSliderColor = {255, 0, 0};
  sf::Vector3i maxColor = {255, 255, 255};
  for (int i = 0; i < 256; ++i) {
    for (int j = 0; j < 256; ++j) {
      paletteSurface[i * 256 + j].position = sf::Vector2f(j, i);
      paletteSurface[i * 256 + j].color = sf::Color(maxColor.x - i,
                                                    maxColor.y - i - j * (maxColor.y - i) / 256,
                                                    maxColor.z - i - j * (maxColor.z - i) / 256);
    }
  }
  sf::Vector3f curColor = paletteSliderColor;
  int line = 0;
  float linesPerLevel = 252.f / 6;
  float valuePerLine = 255.f / linesPerLevel;
  for (int i = 0; i < 503; i += 2) {
    paletteSlider[i].position = sf::Vector2f(268, line);
    paletteSlider[i + 1].position = sf::Vector2f(286, line);
    if (line < linesPerLevel) {
      curColor.z += valuePerLine;
      paletteSlider[i].color = sf::Color(curColor.x, curColor.y, curColor.z);
      paletteSlider[i + 1].color = sf::Color(curColor.x, curColor.y, curColor.z);
    }
    if (line >= linesPerLevel &&
        line < linesPerLevel * 2) {
      curColor.x -= valuePerLine;
      paletteSlider[i].color = sf::Color(curColor.x, curColor.y, curColor.z);
      paletteSlider[i + 1].color = sf::Color(curColor.x, curColor.y, curColor.z);
    }
    if (line >= linesPerLevel * 2 &&
        line < linesPerLevel * 3) {
      curColor.y += valuePerLine;
      paletteSlider[i].color = sf::Color(curColor.x, curColor.y, curColor.z);
      paletteSlider[i + 1].color = sf::Color(curColor.x, curColor.y, curColor.z);
    }
    if (line >= linesPerLevel * 3 &&
        line < linesPerLevel * 4) {
      curColor.z -= valuePerLine;
      paletteSlider[i].color = sf::Color(curColor.x, curColor.y, curColor.z);
      paletteSlider[i + 1].color = sf::Color(curColor.x, curColor.y, curColor.z);
    }
    if (line >= linesPerLevel * 4 &&
        line < linesPerLevel * 5) {
      curColor.x += valuePerLine;
      paletteSlider[i].color = sf::Color(curColor.x, curColor.y, curColor.z);
      paletteSlider[i + 1].color = sf::Color(curColor.x, curColor.y, curColor.z);
    }
    if (line >= linesPerLevel * 5 &&
        line < linesPerLevel * 6) {
      curColor.y -= valuePerLine;
      paletteSlider[i].color = sf::Color(curColor.x, curColor.y, curColor.z);
      paletteSlider[i + 1].color = sf::Color(curColor.x, curColor.y, curColor.z);
    }
    ++line;
  }
  paletteBox.setPosition(-2, -2);
  this->setOrigin({-2, -2});
  updatePaletteSurfaceValue();
  this->changed = true;
}

void Palette::updatePaletteSurface() {
  sf::Vector3i maxColor = {255, 255, 255};
  sf::Vector3f minSliderColor = paletteSliderColor;
  for (int i = 0; i < 256; ++i) {
    for (int j = 0; j < 256; ++j) {
      float maxColorX = maxColor.x - i;
      float maxColorY = maxColor.y - i;
      float maxColorZ = maxColor.z - i;
      float minColorX = minSliderColor.x - i * minSliderColor.x / 255;
      float minColorY = minSliderColor.y - i * minSliderColor.y / 255;
      float minColorZ = minSliderColor.z - i * minSliderColor.z / 255;
      paletteSurface[i * 256 + j].position = sf::Vector2f(j, i);
      paletteSurface[i * 256 + j].color = sf::Color(maxColorX - j * (maxColorX - minColorX) / 255,
                                                    maxColorY - j * (maxColorY - minColorY) / 255,
                                                    maxColorZ - j * (maxColorZ - minColorZ) / 255);
    }
  }
  updatePaletteSurfaceValue();
}

void Palette::onMouseMoved(const sf::Event &event) {
  sf::Vector2f sliderPos = sliderPosition + this->getPosition() + this->getSystemPos();
  sf::Vector2f palettePos = palettePosition + this->getPosition() + this->getSystemPos();

  sf::FloatRect sliderBounds = paletteSlider.getBounds();
  sf::FloatRect paletteBounds = paletteSurface.getBounds();

  sf::FloatRect sliderCollider = {sliderPos, {sliderBounds.width, sliderBounds.height + 1}};
  sf::FloatRect paletteCollider = {palettePos, {paletteBounds.width + 1, paletteBounds.height + 1}};

  float mousePosX = event.mouseMove.x;
  float mousePosY = event.mouseMove.y;
  sf::Vector2f mousePosition = {mousePosX, mousePosY};

  if (sliderCollider.contains(mousePosition)) {
    switch (curState) {

      case Idle : {
        curState = Hovered;
        break;
      }
      case Focused : {
        sliderColorPosition = mousePosition - sliderPos;
        updateSliderValue();
        changed = true;
      }
      default : {
        break;
      }
    }
  } else if (paletteCollider.contains(mousePosition)) {
    switch (curState) {

      case Idle : {
        curState = Hovered;
        break;
      }
      case Focused : {
        paletteColorPosition = mousePosition - palettePos;
        updatePaletteSurfaceValue();
        changed = true;
      }
      default : {
        break;
      }
    }
  } else {
    curState = Idle;
  }
}

void Palette::onMouseButtonPressed(const sf::Event &event) {
  sf::Vector2f sliderPos = sliderPosition + this->getPosition() + this->getSystemPos();
  sf::Vector2f palettePos = palettePosition + this->getPosition() + this->getSystemPos();

  sf::FloatRect sliderBounds = paletteSlider.getBounds();
  sf::FloatRect paletteBounds = paletteSurface.getBounds();

  sf::FloatRect sliderCollider = {sliderPos, {sliderBounds.width, sliderBounds.height + 1}};
  sf::FloatRect paletteCollider = {palettePos, {paletteBounds.width + 1, paletteBounds.height + 1}};

  float mousePosX = event.mouseButton.x;
  float mousePosY = event.mouseButton.y;
  sf::Vector2f mousePosition = {mousePosX, mousePosY};

  if (sliderCollider.contains(mousePosition)) {
    sliderColorPosition = mousePosition - sliderPos;
    curState = Focused;
    updateSliderValue();
    changed = true;
  } else if (paletteCollider.contains(mousePosition)) {
    paletteColorPosition = mousePosition - palettePos;
    curState = Focused;
    updatePaletteSurfaceValue();
    changed = true;
  } else {
    curState = Idle;
  }
}

void Palette::onMouseButtonReleased(const sf::Event &event) {
  sf::Vector2f sliderPos = sliderPosition + this->getPosition() + this->getSystemPos();
  sf::Vector2f palettePos = palettePosition + this->getPosition() + this->getSystemPos();

  sf::FloatRect sliderBounds = paletteSlider.getBounds();
  sf::FloatRect paletteBounds = paletteSurface.getBounds();

  sf::FloatRect sliderCollider = {sliderPos, {sliderBounds.width, sliderBounds.height + 1}};
  sf::FloatRect paletteCollider = {palettePos, {paletteBounds.width + 1, paletteBounds.height + 1}};

  float mousePosX = event.mouseButton.x;
  float mousePosY = event.mouseButton.y;
  sf::Vector2f mousePosition = {mousePosX, mousePosY};

  if (sliderCollider.contains(mousePosition)) {
    curState = Hovered;
  } else if (paletteCollider.contains(mousePosition)) {
    curState = Hovered;
  } else {
    curState = Idle;
  }
}

void Palette::handleEvents(const sf::Event &event) {
  switch (event.type) {
    case sf::Event::MouseMoved : {
      onMouseMoved(event);
      break;
    }
    case sf::Event::MouseButtonPressed : {
      onMouseButtonPressed(event);
      break;
    }
    case sf::Event::MouseButtonReleased : {
      onMouseButtonReleased(event);
      break;
    }
    default : {
      break;
    }
  }
}

void Palette::updatePaletteSurfaceValue() {
  float row = paletteColorPosition.y;
  float column = paletteColorPosition.x;

  sf::Color newColor = paletteSurface[row * 256 + column].color;
  color = {float(newColor.r), float(newColor.g), float(newColor.b)};
}

void Palette::updateSliderValue() {
  float line = sliderColorPosition.y * 2;
  sf::Color newColor = paletteSlider[line].color;
  paletteSliderColor = {float(newColor.r), float(newColor.g), float(newColor.b)};
  updatePaletteSurface();
}

void Palette::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();

  target.draw(paletteBox, states);
  target.draw(paletteSlider, states);
  target.draw(paletteSurface, states);
}
const sf::Vector3f &Palette::getColor() {
  return this->color;
}

//
// Created by ixandy on 2/24/2021.
//

#include "Widget.h"

Widget::~Widget() {
  font.reset(nullptr);
}

Widget::Widget(const sf::Vector2f &size) {
  this->font = std::make_unique<sf::Font>();
  this->setSize(size);
  this->systemPos = {0, 0};
}

Widget::Widget(const Widget &copy) {
  this->font = std::make_unique<sf::Font>();
  this->setSize(copy.getSize());
  this->systemPos = copy.getPosition();
}

Widget::Widget(float width, float height) :
    Widget(sf::Vector2f(width, height)) {
}

sf::Vector2f Widget::getSize() const {
  sf::Vector2f scale = this->getScale();
  return {scale.x * size.x, scale.y * size.y};
}

void Widget::setSize(const sf::Vector2f &size) {
  this->size = size;
}

void Widget::setSize(float width, float height) {
  this->setSize({width, height});
}

void Widget::loadFont(const std::string &fontPath) {
  if (!font->loadFromFile(fontPath)) {
    throw std::invalid_argument("Font couldn't load");
  }
}
const sf::Vector2f &Widget::getSystemPos() {
  return this->systemPos;
}
void Widget::setSystemPos(const sf::Vector2f &systemPos) {
  this->systemPos = systemPos;
}




//
// Created by ixandy on 2/27/2021.
//

#include "TextBox.h"
#include <cstring>

TextBox::TextBox() :
    Widget(150, 20),
    text(),
    box() {
  value = "0";
  curState = Widget::State::Idle;
  maxLength = 16;
  box.setSize({50, 20});
  text.move(0, 0);
  changed = false;
}

TextBox::TextBox(const TextBox &copy) :
    Widget(copy.box.getSize()) {
  this->changed = copy.changed;
  this->text = sf::Text(copy.text);
  this->curState = copy.curState;
  this->value = copy.value;
  this->maxLength = copy.maxLength;
  this->box = sf::RectangleShape(copy.box);
  text.move(0, 0);
}

TextBox::TextBox(const sf::Vector2f &size, const std::string &value, unsigned int maxLength) :
    Widget(size),
    text(),
    box() {
  changed = false;
  this->curState = Idle;
  box.setSize(size);
  this->maxLength = maxLength;
  this->setValue(value);
  text.move(0, 0);
}

void TextBox::setFontSize(unsigned int size) {
  text.setCharacterSize(size);
}

bool TextBox::setValue(const std::string &value) {
  if (checkValue(value)) {
    this->value = value;
    updateText();
    changed = false;
    return true;
  }
  changed = false;
  return false;
}

bool TextBox::checkValue(const std::string &value) {
  return value.length() <= maxLength;
}

void TextBox::updateText() {
  text.setString(this->value);
}

void TextBox::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();

  target.draw(box, states);
  target.draw(text, states);
}

void TextBox::setLoadedFont() {
  text.setFont(*this->font);
}

void TextBox::setFontColor(sf::Color color) {
  text.setFillColor(color);
}

const std::string &TextBox::getValue() {
  return this->value;
}

void TextBox::onMouseButtonPressed(const sf::Event &event) {
  sf::Vector2f position = this->getPosition() + this->getSystemPos();
  sf::Vector2f size = this->getSize();
  sf::FloatRect sliderCollider = {position, size};

  float mousePosX = event.mouseButton.x;
  float mousePosY = event.mouseButton.y;
  sf::Vector2f mousePosition = {mousePosX, mousePosY};

  if (sliderCollider.contains(mousePosition)) {
    curState = Focused;
  } else {
    curState = Idle;
  }
}

void TextBox::onTextEntered(const sf::Event &event) {
  if (curState == Widget::State::Focused &&
      event.text.unicode < 128) {
    std::string newValue = std::string(getValue());
    if (event.text.unicode == 8) {
      if (!newValue.empty()) {
        newValue.erase(newValue.size() - 1);
      }
    } else {
      newValue.push_back(event.text.unicode);
    }
    setValue(newValue);
    changed = true;
  }
}

void TextBox::handleEvents(const sf::Event &event) {
  switch (event.type) {
    case sf::Event::MouseButtonPressed : {
      onMouseButtonPressed(event);
      break;
    }
    case sf::Event::TextEntered : {
      onTextEntered(event);
      break;
    }
    default : {
      break;
    }
  }
}

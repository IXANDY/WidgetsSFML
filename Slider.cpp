//
// Created by ixandy on 2/16/2021.
//

#include <iostream>
#include <cmath>
#include "Slider.h"

Slider::Slider() :
    Widget(120, 16),
    sliderLine(),
    sliderHandle() {

  value = 0;
  minValue = 0;
  maxValue = 100;
  valueStep = 1;

  sliderLine.setSize({120, 11});
  sliderHandle.setSize({5, 16});

  sliderHandle.setPosition({0, -2.5});
  sliderHandle.setOrigin({2.5, 0});

  this->setOrigin({0, -2.5});
}

Slider::Slider(const sf::Vector2f &lineSize,
               const sf::Vector2f &handleSize,
               float value,
               float minValue,
               float maxValue,
               float valueStep) :
    Widget(lineSize.x, handleSize.y),
    sliderLine(),
    sliderHandle() {

  changed = false;
  this->value = value;
  this->minValue = minValue;
  this->maxValue = maxValue;
  this->valueStep = valueStep;

  sliderLine.setSize(lineSize);
  sliderHandle.setSize(handleSize);

  sf::Vector2f handlePos = {0, -(handleSize.y - lineSize.y) / 2};
  sliderHandle.setPosition(handlePos);
  sliderHandle.setOrigin({handleSize.x / 2, 0});

  sf::Vector2f sliderOrigin = {0, -(handleSize.y - lineSize.y) / 2};
  this->setOrigin(sliderOrigin);
}

Slider::Slider(float lineSizeX,
               float lineSizeY,
               float handleSizeX,
               float handleSizeY,
               float value,
               float minValue,
               float maxValue,
               float valueStep) :
    Slider({lineSizeX, lineSizeY}, {handleSizeX, handleSizeY}, value, minValue, maxValue, valueStep) {
}

Slider::Slider(const Slider &copy) :
    Widget(copy.getSize()) {
  this->changed = copy.changed;
  this->value = copy.value;
  this->curState = copy.curState;
  this->minValue = copy.minValue;
  this->maxValue = copy.maxValue;
  this->sliderHandle = copy.sliderHandle;
  this->sliderLine = copy.sliderLine;
  this->valueStep = copy.valueStep;
}

bool Slider::setValue(float value) {
  if (checkValue(value)) {
    float valueByStep = std::round(value / valueStep);
    this->value = valueByStep * valueStep;
    updateHandlePosition();
    changed = false;
    return true;
  }
  changed = false;
  return false;
}

bool Slider::setValue(const sf::Vector2f &mousePosition) {
  float valueByWidth = mousePosition.x - this->getPosition().x - this->getSystemPos().x;
  float valuePerPixel = (this->maxValue - this->minValue) / this->getSize().x;
  float value = valuePerPixel * valueByWidth + minValue;
  return setValue(value);
}

bool Slider::checkValue(float value) {
  if (value >= minValue &&
      value <= maxValue) {
    return true;
  }
  return false;
}

float Slider::getValue() {
  return this->value;
}

void Slider::onMouseMoved(const sf::Event &event) {
  sf::Vector2f handleHalfWidth = {sliderHandle.getSize().x / 2, 0};
  sf::Vector2f position = this->getPosition() + this->getSystemPos() - handleHalfWidth;
  sf::Vector2f size = this->getSize() + handleHalfWidth * 2.f;
  sf::FloatRect sliderCollider = {position, size};

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
        setValue(mousePosition);
        changed = true;
        break;
      }
      default : {
        break;
      }
    }
  } else {
    curState = Idle;
  }
}

void Slider::onMouseButtonPressed(const sf::Event &event) {
  sf::Vector2f handleHalfWidth = {sliderHandle.getSize().x / 2, 0};
  sf::Vector2f position = this->getPosition() + this->getSystemPos() - handleHalfWidth;
  sf::Vector2f size = this->getSize() + handleHalfWidth * 2.f;
  sf::FloatRect sliderCollider = {position, size};

  float mousePosX = event.mouseButton.x;
  float mousePosY = event.mouseButton.y;
  sf::Vector2f mousePosition = {mousePosX, mousePosY};

  if (sliderCollider.contains(mousePosition)) {
    curState = Focused;
    setValue(mousePosition);
    changed = true;
  } else {
    curState = Idle;
  }
}

void Slider::onMouseReleased(const sf::Event &event) {
  sf::Vector2f handleHalfWidth = {sliderHandle.getSize().x / 2, 0};
  sf::Vector2f position = this->getPosition() + this->getSystemPos() - handleHalfWidth;
  sf::Vector2f size = this->getSize() + handleHalfWidth * 2.f;
  sf::FloatRect sliderCollider = {position, size};

  float mousePosX = event.mouseButton.x;
  float mousePosY = event.mouseButton.y;
  sf::Vector2f mousePosition = {mousePosX, mousePosY};

  if (sliderCollider.contains(mousePosition)) {
    curState = Hovered;
  } else {
    curState = Idle;
  }
}

void Slider::onKeyPressed(const sf::Event &event) {
  if (curState == Focused || curState == Hovered) {
    if (event.key.code == sf::Keyboard::Left) {
      setValue(this->getValue() - this->valueStep);
      changed = true;
    }
    if (event.key.code == sf::Keyboard::Right) {
      setValue(this->getValue() + this->valueStep);
      changed = true;
    }
  }
}

void Slider::handleEvents(const sf::Event &event) {
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
      onMouseReleased(event);
      break;
    }
    case sf::Event::KeyPressed : {
      onKeyPressed(event);
      break;
    }
    default : {
      break;
    }
  }
}

void Slider::updateHandlePosition() {
  float sliderWidth = sliderLine.getSize().x;
  float valuePerPixel = (this->maxValue - this->minValue) / sliderWidth;
  float handlePosY = sliderHandle.getPosition().y;
  float handlePosX = this->value / valuePerPixel - minValue;

  sliderHandle.setPosition(handlePosX, handlePosY);
}

void Slider::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();

  target.draw(sliderLine, states);
  target.draw(sliderHandle, states);
}
float Slider::getMinValue() {
  return this->minValue;
}
float Slider::getMaxValue() {
  return this->maxValue;
}

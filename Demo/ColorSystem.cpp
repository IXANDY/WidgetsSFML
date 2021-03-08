//
// Created by ixandy on 3/2/2021.
//

#include <sstream>
#include <cmath>
#include "ColorSystem.h"
ColorSystem::ColorSystem(int num,
                         const sf::Vector2f &textSize,
                         const std::vector<std::string> &textValue,
                         unsigned int maxTextLength,
                         const sf::Vector2f &lineSize,
                         const sf::Vector2f &handleSize,
                         const std::vector<float> &values,
                         const std::vector<float> &minValues,
                         const std::vector<float> &maxValues,
                         const std::vector<float> &valueSteps,
                         const std::string &fontPath) :
    Widget(lineSize.x + textSize.x + 5, textSize.y * num),
    texts(num),
    sliders(num) {
  texts.resize(0);
  sliders.resize(0);
  changed = false;
  for (int i = 0; i < num; ++i) {
    texts.emplace_back(textSize, textValue[i], maxTextLength);
    texts[i].move(0, 3 * i * (textSize.y) / 2);
    sliders.emplace_back(lineSize, handleSize, values[i], minValues[i], maxValues[i], valueSteps[i]);
    sliders[i].move(3 * textSize.x / 2, 3 * i * (textSize.y) / 2 + textSize.y / 4);
    texts[i].setFontSize(15);
    texts[i].loadFont(fontPath);
    texts[i].setLoadedFont();
    texts[i].setFontColor(sf::Color::Black);
    texts[i].setValue("0");
  }
}

void ColorSystem::handleEvents(const sf::Event &event) {
  for (int i = 0; i < sliders.size(); ++i) {
    sliders[i].setSystemPos(this->getPosition());
    texts[i].setSystemPos(this->getPosition());
    sliders[i].handleEvents(event);
    texts[i].handleEvents(event);

    if (isFloat(texts[i].getValue()) &&
        texts[i].changed) {
      sliders[i].setValue(std::stof(texts[i].getValue()));
      texts[i].changed = false;
      this->changed = true;
    }
    if (sliders[i].changed) {
      this->changed = true;
      std::ostringstream ss;
      ss << sliders[i].getValue();
      sliders[i].changed = false;
      std::string newValue(ss.str());
      texts[i].setValue(newValue);
    }
  }
}

void ColorSystem::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();
  for (int i = 0; i < sliders.size(); ++i) {
    target.draw(sliders[i], states);
    target.draw(texts[i], states);
  }
}

bool ColorSystem::isFloat(const std::string &string) {
  std::istringstream iss(string);
  float f;
  iss >> std::noskipws >> f;
  return iss.eof() && !iss.fail();
}

void ColorSystem::setColor(const std::vector<float> &color) {
  for (int i = 0; i < sliders.size(); ++i) {
    float newValue = std::round(color[i] * 100) / 100;
    std::ostringstream ss;
    ss << newValue;
    std::string s(ss.str());
    if (sliders[i].setValue(newValue)) {
      texts[i].setValue(s);
    } else {
      std::ostringstream newVal;
      float minValue = std::abs(sliders[i].getMinValue() - newValue);
      float maxValue = std::abs(sliders[i].getMaxValue() - newValue);
      if (minValue < maxValue) {
        newVal << sliders[i].getMinValue();
        sliders[i].setValue(sliders[i].getMinValue());
      } else {
        newVal << sliders[i].getMaxValue();
        sliders[i].setValue(sliders[i].getMaxValue());
      }
      std::string val(newVal.str());
      texts[i].setValue(val);
    }
    this->changed = false;
  }
}

std::vector<float> ColorSystem::getColor() {
  std::vector<float> color;
  for (auto &slider : sliders) {
    color.push_back(slider.getValue());
  }
  return color;
}


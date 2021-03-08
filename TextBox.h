//
// Created by ixandy on 2/27/2021.
//

#ifndef WIDGETS__TEXTBOX_H_
#define WIDGETS__TEXTBOX_H_

#include "Widget.h"

class TextBox : public Widget {

 private :

  std::string value;
  unsigned int maxLength;

  sf::Text text;
  sf::RectangleShape box;
  Widget::State curState;

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

  void onMouseButtonPressed(const sf::Event &event);
  void onTextEntered(const sf::Event &event);

 protected:

  bool checkValue(const std::string &value);
  void updateText();

 public:

  bool changed;

  TextBox();
  TextBox(const sf::Vector2f &size,
          const std::string &value,
          unsigned int maxLength);
  TextBox(const TextBox &copy);

  void setFontSize(unsigned int size);
  void setLoadedFont();
  bool setValue(const std::string &value);
  void setFontColor(sf::Color color);
  const std::string &getValue();
  void handleEvents(const sf::Event &event);
};

#endif //WIDGETS__TEXTBOX_H_

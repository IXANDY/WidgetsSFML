//
// Created by ixandy on 2/18/2021.
//

#ifndef UNTITLED_WIDGET_H
#define UNTITLED_WIDGET_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Widget : public sf::Drawable, public sf::Transformable {

 private :

  sf::Vector2f size;
  std::unique_ptr<sf::Font> font;

 protected :

  ~Widget() override;
  Widget(const sf::Vector2f &);
  Widget(float, float);
  void setSize(const sf::Vector2f &);
  void setSize(float, float);

 public:
  enum State {
    Hovered,
    Focused,
    Idle
  };

  void setFont(const std::string &);
  sf::Vector2f getSize();

};

#endif //UNTITLED_WIDGET_H

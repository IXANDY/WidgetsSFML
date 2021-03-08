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
  sf::Vector2f systemPos;

 protected :

  std::unique_ptr<sf::Font> font;
  ~Widget() override;
  Widget(const Widget &copy);
  Widget(const sf::Vector2f &size);
  Widget(float width, float height);
  void setSize(const sf::Vector2f &size);
  void setSize(float width, float height);

 public:
  enum State {
    Hovered,
    Focused,
    Idle
  };

  void loadFont(const std::string &fontPath);
  sf::Vector2f getSize() const;
  const sf::Vector2f &getSystemPos();
  void setSystemPos(const sf::Vector2f &systemPos);

};

#endif //UNTITLED_WIDGET_H

#ifndef KEYINPUT_H
#define KEYINPUT_H

#include <SFML/Graphics.hpp>

class KeyInput
{
public:
    KeyInput();
    KeyInput(sf::Keyboard::Key);

    sf::Keyboard::Key key;
    std::string name;
    bool isDown;
    bool toggled;

};

#endif // KEYINPUT_H
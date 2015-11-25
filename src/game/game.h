#ifndef GAME_H
#define GAME_H

#include <SFML/System/Sleep.hpp>
#include <memory>
#include <gamewindow.h>
#include <debugutils.h>
#include <mathsutils.h>
#include <grid.h>
#include<inputmap.h>
#include<gameobjectstack.h>
#include<gameobjectfactory.h>
#include<eventfactory.h>
#include<componentfactory.h>
#include<transformengine.h>
#include<eventengine.h>

typedef std::shared_ptr<BQ::GameWindow> window_ptr;

namespace BQ
{
class Game
{
public:
    Game();

    void setGameWindow(window_ptr);
    window_ptr getGameWindow();

    void setFrameRate(float);
    float getFrameRate();

    void stabiliseFrameRate(float);

    void run();

    void initialiseInjections();
    void initialiseClocks();
    void initialiseInput();
    void initialiseTests();
    void initialisePlayers();

    void runTests();
    void runEngines();

    void setDebug(DebugUtils *value);

    GameObjectStack gameObjects;


private:

    //factories
    GameObjectFactory gameObjectFactory;
    ComponentFactory componentFactory;
    EventFactory eventFactory;

    //engines
    TransformEngine transformEngine;
    InputEngine inputEngine;
    EventEngine eventEngine;


    //inherited properties
    DebugUtils* debug;
    window_ptr gameWindow;

    //utilities owned by game
    MathsUtils math;

    //global properties
    Grid grid;
    InputMap input;

    //variables
    float frameRate;
    float targetFrameDuration;



};
}
#endif // GAME_H
#include "eventengine.h"

#include<eventfactory.h>
#include<componentloader.h>
#include<game.h>

using namespace BQ;

EventEngine::EventEngine() : Engine()
{
    placeholder = "event_";
}

GameLogic *EventEngine::addGameLogic()
{
    gameLogics.resize(gameLogics.size() + 1);
    return &gameLogics.back();
}

void EventEngine::run()
{
    TimeUtils& time = (debug->time);
    for(int i=0; i<events.size();i++)
    {
        resolve(events[i]);
    }
    delta = time.getSeconds("logicTime");
    for(unsigned int i=0; i<toUpdate.size();i++)
    {
        int j = toUpdate[i];
        gameLogics[j].setDelta(delta);
        gameLogics[j].update();
    }
    events.clear();
    toUpdate.clear();
}

void EventEngine::pushEvent(Event event)
{
    events.push_back(event);

}

std::map<std::string,std::string> EventEngine::parseEvent(std::string event)
{
    int openSq = event.find("{");
    int closeSq = event.find("}");

    std::string type = event.substr(0,openSq);
    std::string script = event.substr(openSq+1,closeSq-openSq-1);

    int openBr = script.find("(");
    int closeBr = script.find(")");

    std::string action = script;
    std::string val = "";
    if(openBr > -1 && closeBr > -1){
        action = script.substr(0,openBr);
        val = script.substr(openBr+1,closeBr-openBr-1);
    }

    std::map<std::string,std::string> parsed;

    parsed["type"] = type;
    parsed["action"] = action;
    parsed["val"] = val;
    return parsed;
}

void EventEngine::resolveGlobally(Event& event)
{
    float speed = delta*200.0;
    event.parsedScript = parseEvent(event.script);

}

void EventEngine::resolveLocally(Event& event)
{

    for(unsigned int i=0; i<gameLogics.size(); i++){
        if(gameLogics[i].getParent() == event.triggeredBy) //todo: dynamic cast this instead
        {

            gameLogics[i].addEvent(event.script,event.triggeredBy,event.parsedScript);
            toUpdate.push_back(i);
            break;
        }
    }
}

void EventEngine::resolve(Event& event)
{
    resolveGlobally(event);
    resolveLocally(event);
}

float EventEngine::getDelta() const
{
    return delta;
}

void EventEngine::setDelta(float value)
{
    delta = value;
}


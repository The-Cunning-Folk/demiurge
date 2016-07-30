#include "gameobjectpattern.h"

using namespace BQ;

GameObjectPattern::GameObjectPattern()
{

}

bool GameObjectPattern::parseFromJson(std::string rawJson)
{
    rapidjson::Document doc;
    doc.Parse(rawJson.c_str());

    rapidjson::Value & components = doc["components"];

    if(components.HasMember("spriterenderers"))
    {
        rapidjson::Value spriteRenderers = components["spriterenderers"].GetArray();
        for (rapidjson::SizeType i = 0; i < spriteRenderers.Size(); i++)
        {
            spriteRendererPatterns.push_back(parseSpriteRenderer(spriteRenderers[i]));
        }
    }

    if(components.HasMember("collidables"))
    {
        rapidjson::Value collidables = components["collidables"].GetArray();
        for (rapidjson::SizeType i = 0; i < collidables.Size(); i++)
        {
            CollidablePattern c = parseCollidable(collidables[i]);
            if(collidables[i].HasMember("polygon"))
            {
                for(rapidjson::SizeType p = 0; p<collidables[i]["polygon"].Size(); p++)
                {

                    rapidjson::Value point = collidables[i]["polygon"][p].GetObject();
                    c.polygon.push_back(sf::Vector2f(point["x"].GetFloat(),point["y"].GetFloat()));
                }
            }
            collidablePatterns.push_back(c);
        }
    }
    if(components.HasMember("rigidbodies"))
    {
        rapidjson::Value rigidbodies = components["rigidbodies"].GetArray();
        for (rapidjson::SizeType i = 0; i < rigidbodies.Size(); i++)
        {
            RigidBodyPattern r;
            r.parse(rigidbodies[i]);
            rigidBodyPatterns.push_back(r);
        }
    }
    if(components.HasMember("rayemitters"))
    {
        rapidjson:: Value rayemitters = components["rayemitters"].GetArray();
        for(rapidjson::SizeType i = 0; i<rayemitters.Size(); i++)
        {
            RayEmitterPattern r;
            if(rayemitters[i].HasMember("targets") && rayemitters[i]["targets"].IsArray())
            {
                for(rapidjson::SizeType t = 0; t<rayemitters[i]["targets"].Size(); t++)
                {
                    if(rayemitters[i]["targets"][t].IsString())
                    {
                        r.targets.push_back(rayemitters[i]["targets"][t].GetString());
                    }
                }
            }
            if(rayemitters[i].HasMember("positions") && rayemitters[i]["positions"].IsArray())
            {
                for(rapidjson::SizeType p = 0; p<rayemitters[i]["positions"].Size(); p++)
                {
                    if(rayemitters[i]["positions"][p].IsObject())
                    {
                        rapidjson::Value jPos = rayemitters[i]["positions"][p].GetObject();
                        sf::Vector2f pos;
                        pos.x = jPos.HasMember("x") && jPos["x"].IsNumber() ? jPos["x"].GetFloat() : 0;
                        pos.y = jPos.HasMember("t") && jPos["y"].IsNumber() ? jPos["y"].GetFloat() : 0;
                        r.positions.push_back(pos);
                    }
                }
            }
            rayEmitterPatterns.push_back(r);
        }
    }

    return true;
}

SpriteRendererPattern GameObjectPattern::parseSpriteRenderer(rapidjson::Value & json)
{

    SpriteRendererPattern sprite;

    if(!json.HasMember("sheet"))
    {
        return sprite;
    }
    sprite.sheet = json["sheet"].GetString();

    if(json.HasMember("clip"))
    {
        sprite.clip = json["clip"].GetString();
    }
    if(json.HasMember("offset"))
    {
        rapidjson::Value offset = json["offset"].GetObject();
        sprite.offset.x = offset.HasMember("x") ? offset["x"].GetFloat() : 0;
        sprite.offset.y = offset.HasMember("y") ? offset["y"].GetFloat() : 0;
    }

    sprite.depthOffset = json.HasMember("depth_offset") ? json["depth_offset"].GetFloat() : 0;

    sprite.paused = json.HasMember("paused") ? json["paused"].GetBool() : false;
    sprite.spf = json.HasMember("spf")
            ? json["spf"].GetFloat()
            : json.HasMember("fps")
            ? 1.0f/json["fps"].GetFloat()
            : 0.05;

    return sprite;
}

CollidablePattern GameObjectPattern::parseCollidable(rapidjson::Value & json)
{
    CollidablePattern collidable;

    collidable.immovable = json.HasMember("immovable") ? json["immovable"].GetBool() : false;
    collidable.solid = json.HasMember("solid") ? json["solid"].GetBool() : true;
    collidable.diminutive = json.HasMember("diminutive") ? json["diminutive"].GetBool() : false;
    collidable.opaque = json.HasMember("opaque") ? json["opaque"].GetBool() : true;
    collidable.pathable = json.HasMember("pathable") ? json["pathable"].GetBool() : false;

    return collidable;
}


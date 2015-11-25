#ifndef TRANSFORMENGINE_H
#define TRANSFORMENGINE_H

#include <engine.h>
#include <transform.h>

namespace BQ{

class TransformEngine : public Engine
{
public:
    TransformEngine();

    void run();
    void drawDebug();

    std::vector<Transform> transforms;

    Transform* addTransform();

};
}

#endif // TRANSFORMENGINE_H
#include "spriterenderer.h"

#include <gameobject.h>
#include <componentloader.h>
#include <gameobjectloader.h>

using namespace BQ;


SpriteRenderer::SpriteRenderer()
{
    typeId = "spriterenderer";
    transform = 0;
    centreOrigin = true;
    depth = 0;
    offset.x = offset.y = 0;
    depthOffset = 0;
    textureRect.left = textureRect.top = textureRect.height = textureRect.width = 0;
    frame = 0;
    clip = "";
}


void SpriteRenderer::update()
{
    animation.frame = frame;
    animation.update();
    frame = animation.frame;

}

void SpriteRenderer::wake()
{

}


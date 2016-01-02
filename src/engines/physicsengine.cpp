#include "physicsengine.h"

#include<eventfactory.h>
#include<componentloader.h>
#include<gameobjectloader.h>
#include<game.h>

using namespace BQ;

PhysicsEngine::PhysicsEngine()
{
    placeholder = "auto_phys_";
}

void PhysicsEngine::run()
{
    for(int i=0; i<rigidbodies.size(); i++)
    {
        RigidBody& r = rigidbodies[i];
        r.loadTransform().setVelocity(r.getInvmass()*r.momentum);
    }
}

void PhysicsEngine::addCollision(const PhysicalCollision & c)
{
    collisions.push_back(c);
}

RigidBody &PhysicsEngine::addRigidBody()
{
    rigidbodies.resize(rigidbodies.size()+1);
    rigidbodies.back().index = rigidbodies.size()-1;
    return rigidbodies.back();
}

RigidBody &PhysicsEngine::getRigidBody(int index)
{
    return rigidbodies[index];
}
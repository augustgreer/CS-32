#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <vector>
#include "Actor.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Actor;
class NachenBlaster;
class Star;
class DamageableObject;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void addActor(Actor* actor);
    bool inLineOfFire(const Actor* a);
    void maybeAddNewAlien();
    void destroyedAlien();
    int aliensToKill();
    int aliensDestroyed();
    void alienGone();
    bool collision(Actor* a, Actor* b);
    NachenBlaster* getShip();
    std::vector<Actor*>::iterator  actorsBegin();
    std::vector<Actor*>::iterator  actorsEnd();
    void setGameStatText();
private:
    std::vector<Actor*> m_actors;
    NachenBlaster* m_ship;
    int m_aliensDestroyed;
    int m_aliensToKill;
    int m_aliensOnScreen;
};

#endif // STUDENTWORLD_H_

#ifndef ACTOR_H_
#define ACTOR_H_

#include "StudentWorld.h"
#include "GraphObject.h"

class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(int ID, int startX, int startY, int startDir, double size, int depth, StudentWorld* world);
    virtual ~Actor();
    virtual void doSomething() = 0;
    bool isAlive() const;
    bool isAlien() const;
    void die();
    StudentWorld* getWorld() const;
    void makeAlien();
    bool flewOffLeft();
    bool flewOffRight();
    bool offScreen();
private:
    StudentWorld* m_world;
    bool m_isAlive;
    bool m_alien;
    bool m_projectile;
};

class Star: public Actor
{
public:
    Star(int startX, int startY, StudentWorld* world);
    virtual ~Star();
    virtual void doSomething();
private:
};

class Explosion : public Actor
{
public:
    Explosion(StudentWorld* w, double startX, double startY);
    virtual void doSomething();
private:
    int m_ticksAlive;
};

class DamageableObject: public Actor
{
public:
    DamageableObject(int ID, int startX, int startY, int startDir, double size, int depth, StudentWorld* world, double health);
    virtual ~DamageableObject();
    int getHealth() const;
    virtual void setHealth(int health);
private:
    int m_health;
};

class NachenBlaster: public DamageableObject
{
public:
    NachenBlaster(StudentWorld* world);
    virtual ~NachenBlaster();
    virtual void doSomething();
    int cabbageEnergy() const;
    int torpedoes() const;
    void addTorpedos(int torpedos);
private:
    int m_cabbageEnergy;
    int m_torpedoes;
};

class Alien: public DamageableObject
{
public:
    Alien(int ID, int startX, int startY, int startDir, StudentWorld* world, double health, double damageAmt, double deltaX, double deltaY, double speed, unsigned int scoreValue, int length);
    ~Alien();
    unsigned int scoreValue() const;
    double damageAmt() const;
    int getLength() const;
    void setDeltaX(double x);
    void setDeltaY(double y);
    void setLength(int length);
    double getDeltaX() const;
    double getDeltaY() const;
    void move();
    void maybeNewFlightPLan();
    bool maybeShoot(int sound, bool isSmoregon, int chance1, int chance2);
    void setSpeed(double speed);
    double getSpeed() const;
    bool possiblyHitPlayer();
    virtual void possiblyDropGoodie() = 0;
    
private:
    double m_deltaX;
    double m_deltaY;
    double m_speed;
    unsigned int m_scoreValue;
    double m_damageAmt;
    int m_length;
};

class Smallgon: public Alien
{
public:
    Smallgon(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
    virtual void possiblyDropGoodie();
};

class Smoregon: public Alien
{
public:
    Smoregon(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
    virtual void possiblyDropGoodie();
};

class Snagglegon: public Alien
{
public:
    Snagglegon(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
    virtual void possiblyDropGoodie();
};

class Projectile: public Actor
{
public:
    Projectile(int ID, int startX, int startY, int startDir, StudentWorld* world, double damage);
    virtual void doSomething() = 0;
    bool possiblyHitShip();
    bool hitAlien();
    bool hitAlien(Alien* a);
private:
    double m_damage;
};

class Cabbage: public Projectile
{
public:
    Cabbage(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
};

class Turnip: public Projectile
{
public:
    Turnip(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
};

class FlatulanceTorpedo: public Projectile
{
public:
    FlatulanceTorpedo(int startX, int startY, StudentWorld* world, int startDir);
    virtual void doSomething() = 0;
};

class PlayerTorpedo: public FlatulanceTorpedo
{
public:
    PlayerTorpedo(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
};

class AlienTorpedo: public FlatulanceTorpedo
{
public:
    AlienTorpedo(int startX, int startY, StudentWorld* world);
    virtual void doSomething();
};

class Goodie: public Actor
{
public:
    Goodie(int ID, int startX, int startY, StudentWorld* world);
    virtual void doSomething();
    bool possiblyHitShip();
    virtual void action() = 0;
};

class ExtraLifeGoodie: public Goodie
{
public:
    ExtraLifeGoodie(int startX, int startY, StudentWorld* world);
    virtual void action();
};

class RepairGoodie: public Goodie
{
public:
    RepairGoodie(int startX, int startY, StudentWorld* world);
    virtual void action();
};

class TorpedoGoodie: public Goodie
{
public:
    TorpedoGoodie(int startX, int startY, StudentWorld* world);
    virtual void action();
};


#endif // ACTOR_H_

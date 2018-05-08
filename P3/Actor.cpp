#include "Actor.h"
#include "StudentWorld.h"

class StudentWorld;

//////////////////////////////////
//              Actor           //
//////////////////////////////////

Actor::Actor(int ID, int startX, int startY, int startDir, double size, int depth, StudentWorld* world)
:GraphObject(ID, startX, startY, startDir, size, depth), m_world(world), m_isAlive(true), m_alien(false)
{}

Actor::~Actor()
{
    die();
}

bool Actor::isAlive() const     //return true if actor object is alive, false otherwise
{
    return m_isAlive;
}

bool Actor::isAlien() const
{
    return m_alien;
}

void Actor::die()
{
    m_isAlive = false;
}

StudentWorld* Actor::getWorld() const       //returns pointer to the world current actor is in
{
    return m_world;
}

void Actor::makeAlien()
{
    m_alien = true;
}

bool Actor::flewOffLeft()
{
    if (getX() < 0)
    {
        die();
        return true;
    }
    return false;
}

bool Actor::offScreen()
{
    if (flewOffRight() || flewOffLeft() || getY() >= VIEW_HEIGHT || getY() < 0)
    {
        die();
        return true;
    }
    return false;
}

bool Actor::flewOffRight()
{
    if (getX() >= VIEW_WIDTH)
    {
        die();
        return true;
    }
    return false;
}

//////////////////////////////////
//              Star            //
//////////////////////////////////

Star::Star(int startX, int startY, StudentWorld* world)
:Actor(IID_STAR, startX, startY, 0, (randInt(5, 50) / 100.0), 3, world)
{}

Star::~Star()
{
    die();
}

void Star::doSomething()
{
    moveTo(getX() - 1, getY());     //move left 1
    if (getX() < -9
        )                 //die at the far left of screen
        die();
}


//////////////////////////////////
//           Explosion          //
//////////////////////////////////


Explosion::Explosion(StudentWorld* w, double startX, double startY)
:Actor(IID_EXPLOSION, startX, startY, 0, 1, 0, w), m_ticksAlive(0)
{}

void Explosion::doSomething()
{
    setSize(getSize() * 1.5);
    m_ticksAlive++;
    if (m_ticksAlive >= 4) //check if should be ">="
        die();
}


//////////////////////////////////////////
//            Damageable Object         //
//////////////////////////////////////////

DamageableObject::DamageableObject(int ID, int startX, int startY, int startDir, double size, int depth, StudentWorld* world, double health)
:Actor(ID, startX, startY, startDir, size, depth, world), m_health(health)
{}

DamageableObject::~DamageableObject()
{
    die();
}

int DamageableObject::getHealth() const
{
    return m_health;
}

void DamageableObject::setHealth(int health)
{
    m_health = health;
    if (m_health <= 0)
        die();
}


//////////////////////////////////////
//          NachenBlaster           //
//////////////////////////////////////

NachenBlaster::NachenBlaster(StudentWorld* world)
:DamageableObject(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0, world, 50), m_cabbageEnergy(30), m_torpedoes(0)
{}

NachenBlaster::~NachenBlaster()
{
    die();
}

void NachenBlaster::doSomething()           //function that processes nachenblaster's behavior per tick
{
    if(!isAlive())      //maker sure ship is alive
        return;
    
    int ch;
    if (getWorld()->getKey(ch))
        switch(ch)                  //process the last key press
    {
        case KEY_PRESS_UP:
            if (getY() + 1 < VIEW_HEIGHT)
            {
                moveTo(getX(), getY() + 6);
            }
            break;
        case KEY_PRESS_DOWN:
            if (getY() - 1 >= 0)
            {
                moveTo(getX(), getY() - 6);
            }
            break;
        case KEY_PRESS_LEFT:
            if (getX() - 1 >= 0)
            {
                moveTo(getX() - 6, getY());
            }
            break;
        case KEY_PRESS_RIGHT:
            if (getX() + 1 < VIEW_WIDTH)
            {
                moveTo(getX() + 6, getY());
            }
            break;
        case KEY_PRESS_TAB:
            if (m_torpedoes > 0)
            {
                getWorld()->addActor(new PlayerTorpedo(getX() + 12, getY(),getWorld()));
                getWorld()->playSound(SOUND_TORPEDO);
                m_torpedoes--;
            }
            break;
        case KEY_PRESS_SPACE:
            if (m_cabbageEnergy >= 5)
            {
                getWorld()->addActor(new Cabbage(getX() + 12, getY(),getWorld()));
                getWorld()->playSound(SOUND_PLAYER_SHOOT);
                m_cabbageEnergy -= 5;
            }
            break;
        case KEY_PRESS_ESCAPE:
            die();
    }
    if (m_cabbageEnergy < 30)
        m_cabbageEnergy++;
}

int NachenBlaster::cabbageEnergy() const
{
    return m_cabbageEnergy;
}

int NachenBlaster::torpedoes() const
{
    return m_torpedoes;
}

void NachenBlaster::addTorpedos(int torpedos)
{
    m_torpedoes += torpedos;
}

//////////////////////////////////
//             Alien            //
//////////////////////////////////

Alien::Alien(int ID, int startX, int startY, int startDir, StudentWorld* world, double health, double damageAmt, double deltaX, double deltaY, double speed, unsigned int scoreValue, int length)
:DamageableObject(ID, startX, startY, startDir, 1.5, 1, world, health), m_deltaX(deltaX), m_deltaY(deltaY), m_speed(speed), m_scoreValue(scoreValue), m_damageAmt(damageAmt), m_length(length)
{
    makeAlien();
}

Alien::~Alien()
{
    getWorld()->alienGone();
    die();
}

unsigned int Alien::scoreValue() const
{
    return m_scoreValue;
}

double Alien::damageAmt() const
{
    return m_damageAmt;
}

int Alien::getLength() const
{
    return m_length;
}

void Alien::setDeltaX(double x)
{
    m_deltaX = x;
}

void Alien::setDeltaY(double y)
{
    m_deltaY = y;
}

void Alien::setLength(int length)
{
    m_length = length;
}

double Alien::getDeltaX() const
{
    return m_deltaX;
}

double Alien::getDeltaY() const
{
    return m_deltaY;
}

void Alien::move()
{
    if (getDeltaX() == -1 && getDeltaY() == 1)              //up and left
        moveTo(getX() - getSpeed(), getY() + getSpeed());
    else if (getDeltaX() == -1 && getDeltaY() == -1)           //down and left
        moveTo(getX() - getSpeed(), getY() - getSpeed());
    else                                                       //due left
        moveTo(getX() - getSpeed(), getY());
}

double Alien::getSpeed() const
{
    return m_speed;
}

void Alien::maybeNewFlightPLan()
{
    if (getLength() == 0 || getY() >= VIEW_HEIGHT - 1 || getY() < 0)    //if the flight plan needs changing (runs out or hits the top or bottom of screen)
    {
        if (getY() >= VIEW_HEIGHT - 1)      //if top of screen
        {
            setDeltaX(-1);          //down and left
            setDeltaY(-1);
        }
        else if (getY() < 0)            //if bottom of screen
        {
            setDeltaX(-1);          //up and left
            setDeltaY(1);
        }
        else if (getLength() == 0)     //if plan runs out
        {
            int i = randInt(1, 3);
            if (i == 1)
            {
                setDeltaX(-1);          //due left
                setDeltaY(0);
            }
            else if (i == 2)
            {
                setDeltaX(-1);          //up and left
                setDeltaY(1);
            }
            else
            {
                setDeltaX(-1);          //down and left
                setDeltaY(-1);
            }
        }
        setLength(randInt(1, 32));       //set new length between 1 and 32
    }
}

void Alien::setSpeed(double speed)
{
    m_speed = speed;
}

bool Alien::maybeShoot(int sound, bool isSmoregon, int chance1, int chance2)
{
    if (getWorld()->inLineOfFire(this))
    {
        int i = randInt(1, (chance1 / (getWorld()->getLevel()) + chance2));            //1 in 20(or 15) / (getLevel()) + 5(or 10) chance of the following
        if (i == 1)
        {
            if (sound == SOUND_TORPEDO)
                getWorld()->addActor(new AlienTorpedo(getX() - 14, getY(), getWorld()));
            else
                getWorld()->addActor(new Turnip(getX() - 14, getY(), getWorld()));
            getWorld()->playSound(sound);
            return true;
        }
        if (isSmoregon)                 //a smoregon might RAM
        {
            if (i == 2)                 //1 in 20 / (getLevel()) + 5 chance of the following
            {
                setDeltaX(-1);
                setDeltaY(0);
                setLength(VIEW_WIDTH);
                setSpeed(5.0);
            }
        }
    }
    return false;
}


bool Alien::possiblyHitPlayer()
{
    NachenBlaster* ship = getWorld()->getShip();
    StudentWorld* world = getWorld();
    if (getWorld()->collision(this, ship))
    {
        ship->setHealth(ship->getHealth() - m_damageAmt);
        die();
        world->increaseScore(scoreValue());
        world->playSound(SOUND_DEATH);
        world->addActor(new Explosion(world, getX(), getY()));
        return true;
    }
    return false;
}


//////////////////////////////////
//           Smallgon           //
//////////////////////////////////

Smallgon::Smallgon(int startX, int startY, StudentWorld* world)
:Alien(IID_SMALLGON, startX, startY, 0, world, (5 * (1 + (world->getLevel() - 1) * .1)), 5, 0, 0, 2.0, 250, 0)
{}

void Smallgon::doSomething()
{
    if (isAlive())
    {
        if (flewOffLeft())
            return;
        possiblyHitPlayer();
        maybeNewFlightPLan();
        if (maybeShoot(SOUND_ALIEN_SHOOT, false, 20, 5))
            return;
        move();
        setLength(getLength() - 1);
        possiblyHitPlayer();
    }
}

void Smallgon::possiblyDropGoodie()
{
    return;
}


//////////////////////////////////
//           Smoregon           //
//////////////////////////////////

Smoregon::Smoregon(int startX, int startY, StudentWorld* world)
:Alien(IID_SMOREGON, startX, startY, 0, world, (5 * (1 + (world->getLevel() - 1) * .1)), 5, 0, 0, 2.0, 250, 0)
{}

void Smoregon::doSomething()
{
    if (isAlive())
    {
        if (flewOffLeft())
            return;
        if (possiblyHitPlayer())
            possiblyDropGoodie();
        maybeNewFlightPLan();
        if (maybeShoot(SOUND_ALIEN_SHOOT, true, 20, 5))
            return;
        move();
        setLength(getLength() - 1);
        if (possiblyHitPlayer())
            possiblyDropGoodie();
    }
}

void Smoregon::possiblyDropGoodie()
{
    int i = randInt(1, 3);
    if (i == 1)
    {
        int j = randInt(1, 2);
        if (j == 1)
            getWorld()->addActor(new RepairGoodie(getX(), getY(), getWorld()));
        else
            getWorld()->addActor(new TorpedoGoodie(getX(), getY(), getWorld()));
    }
}

//////////////////////////////////
//           Snagglegon         //
//////////////////////////////////

Snagglegon::Snagglegon(int startX, int startY, StudentWorld* world)
:Alien(IID_SNAGGLEGON, startX, startY, 0, world, (10 * (1 + (world->getLevel() - 1) * .1)), 15, -1, -1, 1.75, 1000, 0)
{}

void Snagglegon::doSomething()
{
    if (isAlive())
    {
        if (flewOffLeft())
            return;
       if (possiblyHitPlayer())
           possiblyDropGoodie();
        
        
        if (getY() >= VIEW_HEIGHT - 1 || getY() < 0)    //if the flight plan needs changing (hits the top or bottom of screen)
        {
            if (getY() >= VIEW_HEIGHT - 1)      //if top of screen
            {
                setDeltaX(-1);          //down and left
                setDeltaY(-1);
            }
            else if (getY() < 0)            //if bottom of screen
            {
                setDeltaX(-1);          //up and left
                setDeltaY(1);
            }
        }
        
        if (maybeShoot(SOUND_TORPEDO, false, 15, 10))
            return;
        move();
        setLength(getLength() - 1);
        if (possiblyHitPlayer())
            possiblyDropGoodie();
    }
}

void Snagglegon::possiblyDropGoodie()
{
    int i = randInt(1, 6);
    if (i == 1)
        getWorld()->addActor(new ExtraLifeGoodie(getX(), getY(), getWorld()));
}

//////////////////////////////////
//           Projectile         //
//////////////////////////////////


Projectile::Projectile(int ID, int startX, int startY, int startDir, StudentWorld* world, double damage)
:Actor(ID, startX, startY, startDir, .5, 1, world), m_damage(damage)
{}

bool Projectile::possiblyHitShip()
{
    NachenBlaster* ship = getWorld()->getShip();
    if (getWorld()->collision(this, ship))
    {
        ship->setHealth(ship->getHealth() - m_damage);        //damage the ship
        die();
        return true;
    }
    return false;
}

bool Projectile::hitAlien()
{
    std::vector<Actor*>::iterator it = getWorld()->actorsBegin();
    while (it != getWorld()->actorsEnd())
    {
        if ((*it)->isAlien())
            if (hitAlien(dynamic_cast<Alien*>(*it)))
                return true;
        it++;
    }
    return false;
}

bool Projectile::hitAlien(Alien* a)
{
    if (getWorld()->collision(this, a))
    {
        a->setHealth(a->getHealth() - m_damage);
        if  (a->getHealth() <= 0)
        {
            getWorld()->addActor(new Explosion(getWorld(), getX(), getY()));
            getWorld()->playSound(SOUND_DEATH);
            getWorld()->destroyedAlien();
            a->possiblyDropGoodie();
        }
        die();
        return true;
    }
    return false;
}
            

            
//////////////////////////////////
//           Cabbage            //
//////////////////////////////////


Cabbage::Cabbage(int startX, int startY, StudentWorld* world)
:Projectile(IID_CABBAGE, startX, startY, 0, world, 2)
{}

void Cabbage::doSomething()
{
    if (isAlive())
    {
        if (flewOffRight())         //sets dead if off screen
            return;
        if (hitAlien())
            return;
        moveTo(getX() + 8, getY());
        setDirection(getDirection() + 20);
        hitAlien();
    }
}


//////////////////////////////////
//           Turnip             //
//////////////////////////////////

Turnip::Turnip(int startX, int startY, StudentWorld* world)
:Projectile(IID_TURNIP, startX, startY, 0, world, 2)
{}

void Turnip::doSomething()
{
    if (isAlive())
    {
        if (flewOffLeft())          //sets dead if off screen
            return;
        if (possiblyHitShip())
            return;
    moveTo(getX() - 6, getY());
    setDirection(getDirection() + 20);
        possiblyHitShip();
    }
}

////////////////////////////////////
//       Flatulance Torpedo       //
////////////////////////////////////

FlatulanceTorpedo::FlatulanceTorpedo(int startX, int startY, StudentWorld* world, int startDir)
:Projectile(IID_TORPEDO, startX, startY, startDir, world, 8)
{}


////////////////////////////////////
//         Player Torpedo         //
////////////////////////////////////


PlayerTorpedo::PlayerTorpedo(int startX, int startY, StudentWorld* world)
:FlatulanceTorpedo(startX, startY, world, 0)
{}

void PlayerTorpedo::doSomething()
{
    if (isAlive())
    {
        if (flewOffRight())         //sets dead if off screen
            return;
        if (hitAlien())
            return;
        moveTo(getX() + 8, getY());
        possiblyHitShip();
    }
}



////////////////////////////////////
//          Alien Torpedo         //
////////////////////////////////////

AlienTorpedo::AlienTorpedo(int startX, int startY, StudentWorld* world)
:FlatulanceTorpedo(startX, startY, world, 180)
{}

void AlienTorpedo::doSomething()
{
    if (isAlive())
    {
        if (flewOffLeft())      //sets dead if off screen
            return;
        if (possiblyHitShip())
            return;
        moveTo(getX() - 8, getY());
        possiblyHitShip();
    }
}



//////////////////////////////////
//           Goodie             //
//////////////////////////////////

Goodie::Goodie(int ID, int startX, int startY, StudentWorld* world)
:Actor(ID, startX, startY, 0, .5, 1, world)
{}

bool Goodie::possiblyHitShip()
{
    if (getWorld()->collision(this, getWorld()->getShip()))
    {
        getWorld()->increaseScore(100);
        die();
        getWorld()->playSound(SOUND_GOODIE);
        action();
        return true;
    }
    return false;
}

void Goodie::doSomething()
{
    if (isAlive())
            {
                if (offScreen())        //sets dead if off screen
                    return;
                if (possiblyHitShip())
                    return;
                moveTo(getX() - .75, getY() - .75);
                possiblyHitShip();
           }
}

////////////////////////////////////
//        Extra Life Goodie       //
////////////////////////////////////

ExtraLifeGoodie::ExtraLifeGoodie(int startX, int startY, StudentWorld* world)
:Goodie(IID_LIFE_GOODIE, startX, startY, world)
{}

void ExtraLifeGoodie::action()
{
    getWorld()->incLives();
}



////////////////////////////////////
//         Repair Goodie          //
////////////////////////////////////

RepairGoodie::RepairGoodie(int startX, int startY, StudentWorld* world)
:Goodie(IID_REPAIR_GOODIE, startX, startY, world)
{}

void RepairGoodie::action()
{
    int l = getWorld()->getShip()->getHealth();
    if (l < 50)                                         //health has to be less than 50 to get more
    {
        if (l <= 40)                                    //if we can freely add all 10 while remaining <= 50
            getWorld()->getShip()->setHealth(l + 10);
        else
            getWorld()->getShip()->setHealth(50);    //add to make 50
    }
}

////////////////////////////////////
//         Torpedo Goodie         //
////////////////////////////////////

TorpedoGoodie::TorpedoGoodie(int startX, int startY, StudentWorld* world)
:Goodie(IID_TORPEDO_GOODIE, startX, startY, world)
{}

void TorpedoGoodie::action()
{
    getWorld()->getShip()->addTorpedos(5);
}





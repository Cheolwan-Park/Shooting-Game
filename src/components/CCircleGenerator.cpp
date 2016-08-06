#include "CCircleGenerator.hpp"
#include "CStraightMove.hpp"

// CCircleBullet class

// constructor
CCircleGenerator::CCircleGenerator(const CVector2 &location, const CVector2 &direction,
                                      float angle, float interval, unsigned short count,
                                      float speed, int tag)
:CObject::CObject(location, tag), _count(count), _nowcount(0),
_eachAngle(angle/count), _nextGen(0.0f), _interval(interval),
_elapseTime(0.0f), _speed(speed), _direction(CVector2::normalize(direction)),
_right(CVector2::rotate(direction, angle/(-2)))
{
  CObject *newobject = nullptr;
  for(unsigned int i=0; i<_count; ++i)
  {
    newobject = new CObject(getLocation(), getTag());
    newobject->setActive(false);
    _objects.push_back(newobject);
    newobject = nullptr;
  }
}

 // copy constructor
 CCircleGenerator::CCircleGenerator(const CCircleGenerator &other)
 :CObject::CObject(other)
 {
   PRINT_INFO(CCircleGenerator::CopyOperator(), "this function must not be called.");
   exit(-1);
 }

 // destuctor
 CCircleGenerator::~CCircleGenerator()
 {
   for(auto iter : _objects)
   {
     SAFE_DELETE_PTR(iter);
   }
 }

 // copy assignment operator
 CCircleGenerator &CCircleGenerator::operator=(const CCircleGenerator &other)
 {
   CObject::operator=(other);
   PRINT_INFO(CCircleGenerator::CopyOperator(), "this function must not be called.");
   exit(-1);
   return (*this);
 }

 // add component to objects that is in _objectMap
 void CCircleGenerator::addComponentToAll(CSprite *component)
 {
   if(nullptr == component)
   {
     PRINT_ERROR(CCircleGenerator::addComponentToAll(), "param is nullptr");
     return;
   }
   component->setVisible(false);
   addComponentToAll<CSprite>(component);
 }


// update CCircleGenerator object
 void CCircleGenerator::update(float delta)
 {
   CObject::update(delta);
   if(_nowcount >= _count)
   {
     deleteObject();
     return;
   }

   CVector2 dir(0.0f, 0.0f);
   CObject *newobject = nullptr;

   if(_interval == 0.0f)
   {
     for(_nowcount=0; _nowcount<_count; ++_nowcount)
     {
       dir = CVector2::rotate(_right, _eachAngle*_nowcount);
       newobject = _objects.back();
       newobject->setActive(true);
       newobject->addComponent(new CMoveInfo(dir, _speed));
       newobject->getComponent<CSprite>()->setVisible(true);
       _parent->addChild(newobject);
       newobject = nullptr;
       _objects.pop_back();
     }
     delete this;
     return;
   }

   else
   {
     if(_nextGen <= _elapseTime)
     {
       dir = CVector2::rotate(_right, _eachAngle*_nowcount);
       newobject = _objects.back();
       newobject->setActive(true);
       newobject->addComponent(new CMoveInfo(dir, 100.0f));
       newobject->getComponent<CSprite>()->setVisible(true);
       _parent->addChild(newobject);
       ++_nowcount;
       _nextGen += _interval;
       _objects.pop_back();
     }
     _elapseTime += delta;
   }
 }

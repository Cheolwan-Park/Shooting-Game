//
// CCircleGenerator.hpp
//

#ifndef __OBJECTS_CCIRCLEGENERATOR_HPP__
#define __OBJECTS_CCIRCLEGENERATOR_HPP__

#include "../engine/engine.hpp"
#include <vector>

class CCircleGenerator;

// object that this generator gens already has CMoveInfo component
class CCircleGenerator
:public CObject
{
public:
  // constructor
  explicit CCircleGenerator(const CVector2 &location, const CVector2 &direction,
                                  float angle, float interval, unsigned short count,
                                  float speed, int tag);

  // copy constructor
  CCircleGenerator(const CCircleGenerator &other);

  // destructor
  virtual ~CCircleGenerator();

  // copy assignment operator
  CCircleGenerator &operator=(const CCircleGenerator &other);

  // add component to objects that is in _objectMap
  template <typename T>
  void addComponentToAll(T* component)
  {
    for(auto iter : _objects)
    {
      iter->addComponent(new T(*component));
    }
    SAFE_DELETE_PTR(component);
  }

  // add sprite component
  void addComponentToAll(CSprite* component);

  // update CCircleGenerator object
  virtual void update(float delta);

protected:
    unsigned short _count;              // count of object that this generator will gen
    unsigned short _nowcount;           // count of genned object
    float _eachAngle;                   // angle that will add to _nowAngle when gen object
    float _nextGen;                     // this generator will gen next object at _nextGen
    float _interval;                    // interval between genning time of last object and current object
    float _elapseTime;                  // elapse time from create
    float _speed;                       // moving speed of objects
    CVector2 _direction;                // direction
    CVector2 _right;                    // base vector to rotate
    std::vector<CObject*> _objects;     // object that this generator will generate
};

#endif

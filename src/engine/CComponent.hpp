//
// CController.hpp
//

#ifndef __ENGINE_CCONTROLLER_HPP__
#define __ENGINE_CCONTROLLER_HPP__

class CComponent;
class CObject;

#define MAKE_COMPONENT_ID_CPP(__COMPONENT__)                  \
const char* __COMPONENT__::_id = #__COMPONENT__

#define MAKE_COMPONENT_ID_HPP()                               \
public:                                                       \
static const char *getComponentID()                           \
{                                                             \
  return _id;                                                 \
}                                                             \
private:                                                      \
static const char* _id;                                       \


class CComponent
{
public:
  // constructor
  explicit CComponent();

  // copy constructor
  CComponent(const CComponent &other);

  // destructor
  virtual ~CComponent();

  // copy assignment operator
  virtual CComponent &operator=(const CComponent &other);

  // update component
  virtual void update(float delta);

  // called when owner object has collision
  virtual void onColliderEnter(CObject *other);

  // get functions
  virtual float getElapseTime()const
  {
    return _elapseTime;
  }

  virtual CObject *getOwner()const
  {
    return _owner;
  }

  // set functions
  virtual void setOwner(CObject *owner)
  {
    _owner = owner;
  }

  MAKE_COMPONENT_ID_HPP();

protected:
  float _elapseTime;              // elapse time from generate
  CObject *_owner;                // owner object of controller
};


#endif

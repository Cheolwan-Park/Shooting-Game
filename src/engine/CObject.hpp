//
// CObject.hpp
//

#ifndef __ENGINE_COBJECT_HPP__
#define __ENGINE_COBJECT_HPP__

#include <unordered_map>
#include "CVector2.hpp"
#include "utility.hpp"

class CObject;
class CComponent;
typedef std::unordered_map<CObject*, CObject*> child_hash;
typedef std::unordered_map<const char*, CComponent*> component_hash;
const int DEFAULT_OBJECT = 0;				// default tag


class CObject
{
public:
  // default constructor
  explicit CObject(const CVector2 &location, int tag = DEFAULT_OBJECT);

  // copy constructor
  // this constructor only copy location and tag information
  CObject(const CObject &other);

  // destructor
  virtual ~CObject();

  // copy assignment operator
  // this copy assignment operator only copy location and tag information
  virtual CObject &operator=(const CObject &other);

  // add component to _components
  template <typename T>
  void addComponent(T *component)
  {
  	if(nullptr == component)
  	{
      PRINT_ERROR(CObject::addComponent(), "param is nullptr");
  		return;
  	}

  	auto find = _components.find(T::getComponentID());
  	if(find != _components.end())
  	{
      PRINT_ERROR(CObject::addComponent(),
      "this object already has same component in component hash")
  		return;
  	}

  	component->setOwner(this);
  	_components.insert(component_hash::value_type(T::getComponentID(),
  																									component));
  }

  // get component in _components
  template <typename T>
  T *getComponent()
  {
  	component_hash::iterator find = _components.find(T::getComponentID());
    if(find == _components.end())
    {
      std::string msg = "CObject doesn't have ";
      msg += T::getComponentID();
      msg += " component";
      PRINT_ERROR(CObject::addComponent(), msg.c_str());
      return nullptr;
    }
  	T* result = static_cast<T*>(find->second);
  	return result;
  }

  // add child to _childs
  virtual CObject *addChild(CObject *child);

  // erase child from _childs
  virtual void eraseChild(CObject *child);

  // delete all child
  // this function calls delete function
  virtual void deleteAllChild();

  // update object
  virtual void update(float delta);

  // called when collision
  virtual void onColliderEnter(CObject *other);

  // call to delete object
  virtual void deleteObject();

  // get functions
  virtual inline bool getActive()const
  {
    return _active;
  }

  virtual inline int getTag()const
  {
    return _tag;
  }

  virtual inline CObject *getParent()const
  {
    return _parent;
  }

  virtual inline const CVector2 &getLocation()const
  {
    return _location;
  }

  // set functions
  virtual void move(const CVector2 &v)
  {
    _location += v;
    if(_childs.empty())
    {
      return;
    }
    for(auto iter : _childs)
    {
      iter.second->move(v);
    }
  }

  virtual void setLocation(const CVector2 &location)
  {
    if(!(_childs.empty()))
    {
      CVector2 v = location - _location;
      for(auto iter : _childs)
      {
        iter.second->move(v);
      }
    }
    _location = location;
  }

  virtual inline void setActive(bool active)
  {
    _active = active;
  }

  virtual inline void setTag(const int tag)
  {
    _tag = tag;
  }

protected:
  bool _willDelete;                   // to delete object
  bool _active;                       // if this object is active, true
  int _tag;                           // tag of object
  CObject *_parent;                   // pointer of owner object
  CVector2 _location;                 // location of object
  child_hash _childs;                 // hash of child
  component_hash _components;         // hash of component
};

#endif

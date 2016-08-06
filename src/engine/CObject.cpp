#include "CObject.hpp"
#include "CComponent.hpp"

// CObject class

// default constructor
CObject::CObject(const CVector2 &location, int tag)
:_willDelete(false), _active(true), _tag(tag), _parent(nullptr), _location(location)
{
	;
}

// copy constructor
CObject::CObject(const CObject &other)
:_tag(other._tag), _location(other._location)
{
	;
}

// destructor
CObject::~CObject()
{
	for(auto iter : _components)
	{
		SAFE_DELETE_PTR(iter.second);
	}
	deleteAllChild();

	if(_parent)
	{
		_parent->eraseChild(this);
	}
}

// copy assignment operator
CObject &CObject::operator=(const CObject &other)
{
	this->_tag = other._tag;
	this->_location = other._location;
	return (*this);
}

// add child to _childs
CObject *CObject::addChild(CObject *child)
{
	if(nullptr == child)
	{
		PRINT_ERROR(CObject::addChild(), "param is nullptr");
		return nullptr;
	}

	auto find = _childs.find(child);
	// if _childs already has same object
	if(find != _childs.end())
	{
		PRINT_ERROR(CObject::addChild(),
		"this object already has same child object in child hash");
		return child;
	}

	child->_parent = this;
	_childs.insert(child_hash::value_type(child, child));
	return child;
}

// delete child from _childs
void CObject::eraseChild(CObject *child)
{
	_childs.erase(child);
}

// delete all child
void CObject::deleteAllChild()
{
	CObject *child = nullptr;
	for(auto iter = _childs.begin();
			iter != _childs.end();)
			{
				child = iter->second;
				++iter;
				SAFE_DELETE_PTR(child);
			}
	_childs.clear();
}

// update object
void CObject::update(float delta)
{
	if(_willDelete)
	{
		delete this;
		return;
	}
	if(true == _active)
	{
		CObject *child = nullptr;
		for(auto iter : _components)
		{
			iter.second->update(delta);
		}
		for(auto iter = _childs.begin();
				iter != _childs.end();)
				{
					child = iter->second;
					++iter;
					child->update(delta);
				}
	}
}

// called when collision
void CObject::onColliderEnter(CObject *other)
{
	if(nullptr == other)
	{
		PRINT_ERROR(CObject::onColliderEnter(), "param is nullptr");
		return;
	}
	for(auto iter : _components)
	{
		iter.second->onColliderEnter(other);
	}
}

// call to delete object
void CObject::deleteObject()
{
	_willDelete = true;
}

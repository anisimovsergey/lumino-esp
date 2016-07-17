// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_I_ENTITY_HPP
#define CORE_I_ENTITY_HPP

#include <WString.h>

namespace Core {

// The class type identifier, should be unique at least within an inheritance hierarchy
#define TYPE_INFO(Class, SuperClass, ClassTypeId) \
public: \
  static constexpr const char* TypeId = ClassTypeId; \
  virtual const char* getTypeId() const override { return TypeId; } \
  static  bool        isType(String typeId) { \
    return (typeId == ClassTypeId || SuperClass::isType(typeId)); \
  } \
  static Class* cast(Core::IEntity* entity) { \
    if (entity->is<Class>()) \
      return static_cast<Class*>(entity); \
    return nullptr; \
  } \

class IEntity {
  public:
    virtual ~IEntity();
    virtual const char* getTypeId() const = 0;

    static bool isType(String typeId) {
      // All entities are of IEntity type
      return true;
    }

    template<typename T> bool is() const {
      auto thisType = getTypeId();
      return T::isType(thisType);
    }

    template<typename T> T* cast() {
      if (is<T>())
        return static_cast<T*>(this);

      return nullptr;
    }

    template<typename T> const T* cast() const {
      if (is<T>())
        return static_cast<T*>(this);

      return nullptr;
    }
};

}

#endif /* end of include guard: CORE_I_ENTITY_HPP */

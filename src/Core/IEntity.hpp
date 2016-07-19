// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_I_ENTITY_HPP
#define CORE_I_ENTITY_HPP

#include <WString.h>
#include <memory>

namespace Core {

#define TYPE_PTRS(Class) \
public: \
  typedef std::shared_ptr<Class> Shared; \
  typedef std::unique_ptr<Class> Unique; \
  \
  template <typename... Args> \
  static Unique makeUnique(Args&&... args) { \
    return Unique(new Class(std::forward<Args>(args)...)); \
  } \

#define TYPE_INFO(Class, SuperClass, ClassTypeId) \
public: \
  TYPE_PTRS(Class) \
  \
  static constexpr const char* TypeId = ClassTypeId; \
  \
  virtual const char* getTypeId() const override { return TypeId; } \
  \
  static  bool        isType(String typeId) { \
    return (typeId == ClassTypeId || SuperClass::isType(typeId)); \
  } \
  \
  static Class* cast(Core::IEntity* entity) { \
    if (Class::isType(entity->getTypeId())) \
      return static_cast<Class*>(entity); \
    return nullptr; \
  } \
  \
  static const Class* cast(const Core::IEntity* entity) { \
    if (Class::isType(entity->getTypeId())) \
      return static_cast<const Class*>(entity); \
    return nullptr; \
  } \


class IEntity {
  TYPE_PTRS(IEntity)
  public:
    virtual ~IEntity();
    virtual const char* getTypeId() const = 0;

    static bool isType(String typeId) {
      return false;
    }
};

}

#endif /* end of include guard: CORE_I_ENTITY_HPP */

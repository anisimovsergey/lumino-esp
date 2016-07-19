// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef CORE_MEMORY_HPP
#define CORE_MEMORY_HPP

#include <memory>

// A simple implementation of make_unique
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<class Derived, class Base, class Del>
std::unique_ptr<Derived, Del>
castToUnique(std::unique_ptr<Base, Del>&& base)
{
   if (auto result = Derived::cast(base.get())){
        base.release();
        return std::unique_ptr<Derived, Del>(result, std::move(base.get_deleter()));
    }
    return std::unique_ptr<Derived, Del>(nullptr, base.get_deleter());
}

template<class Derived, class Base, class Del>
std::shared_ptr<Derived>
castToShared(std::unique_ptr<Base, Del>&& base)
{
   if (auto result = Derived::cast(base.get())){
        base.release();
        return std::shared_ptr<Derived>(result);
    }
    return std::shared_ptr<Derived>();
}

template< class Derived, class Base>
std::shared_ptr<Derived>
castToShared(const std::shared_ptr<Base>& base) noexcept
{
    if (auto p = Derived::Shared::element_type::cast(base.get())) {
        return std::shared_ptr<Derived>(base, p);
    } else {
        return std::shared_ptr<Derived>();
    }
}

#endif /* end of include guard: CORE_MEMORY_HPP */

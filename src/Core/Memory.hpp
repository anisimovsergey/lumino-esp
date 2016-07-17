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
dynamic_cast_to_unique(std::unique_ptr<Base, Del>&& p)
{
   if (auto result = Derived::cast(p.get())){
        p.release();
        return std::unique_ptr<Derived, Del>(result, std::move(p.get_deleter()));
    }
    return std::unique_ptr<Derived, Del>(nullptr, p.get_deleter());
}

template<class Derived, class Base, class Del>
std::shared_ptr<Derived>
dynamic_cast_to_shared(std::unique_ptr<Base, Del>&& p)
{
   if (auto result = Derived::cast(p.get())){
        p.release();
        return std::shared_ptr<Derived>(result);
    }
    return std::shared_ptr<Derived>();
}

template< class Derived, class Base>
std::shared_ptr<Derived>
dynamic_cast_to_shared(const std::shared_ptr<Base>& r) noexcept
{
    if (auto p = std::shared_ptr<Derived>::element_type::cast(r.get())) {
        return std::shared_ptr<Derived>(r, p);
    } else {
        return std::shared_ptr<Derived>();
    }
}

#endif /* end of include guard: CORE_MEMORY_HPP */

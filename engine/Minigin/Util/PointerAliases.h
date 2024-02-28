#ifndef POINTERALIASES_H
#define POINTERALIASES_H

#include <memory>

template<typename T>
using NonOwningPtr = const T *;

template<typename T>
using NonOwningPtrMut = T *;

template<typename T>
using OwningPtr = std::unique_ptr<T>;

template<typename T>
using SharedOwningPtr = std::shared_ptr<T>;

#endif//POINTERALIASES_H

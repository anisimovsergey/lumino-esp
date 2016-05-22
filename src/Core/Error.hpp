// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef ERROR_H
#define ERROR_H

#include <WString.h>

class Error {
public:
  Error(String code, String title);

  String getCode() const { return code; };
  String getTitle() const { return title; };

private:
  String code;
  String title;
};


#endif /* end of include guard: ERROR_H */

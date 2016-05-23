// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef ERRORSERIALIZER_H
#define ERRORSERIALIZER_H

class Error; 
class ISerializationContext;

class ErrorSerializer {
public:
  Error deserialie(const ISerializationContext& context);
  void serialie(const Error& settings, ISerializationContext& context);
};

#endif /* end of include guard: ERRORSERIALIZER_H */

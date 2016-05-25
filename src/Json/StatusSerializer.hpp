// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef MOIKOT_JSON_STATUSSERIALIZER_H
#define MOIKOT_JSON_STATUSSERIALIZER_H

class Status;
class ISerializationContext;

class StatusSerializer {
public:
  Status deserialie(const ISerializationContext& context);
  void serialie(const Status& status, ISerializationContext& context);
};

#endif /* end of include guard: MOIKOT_JSON_STATUSSERIALIZER_H */

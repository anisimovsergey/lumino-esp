// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef MODELS_NETWORKS_HPP
#define MODELS_NETWORKS_HPP

#include "Core/List.hpp"
#include "Models/Network.hpp"

namespace Models {

class Networks : public Core::List<Models::Network> {
  TYPE_INFO(Networks, Core::List<Models::Network>, "networks")
};

}

#endif /* end of include guard: MODELS_NETWORKS_HPP */

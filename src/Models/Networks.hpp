// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Lumino
// https://github.com/anisimovsergey/lumino-esp

#ifndef MODELS_NETWORKS_HPP
#define MODELS_NETWORKS_HPP

#include "Core/List.hpp"
#include "Models/Network.hpp"

namespace Models {

class Networks final : public Core::List<Models::Network> {
  TYPE_INFO(Networks, Core::List<Models::Network>, "networks")
};

}

#endif /* end of include guard: MODELS_NETWORKS_HPP */

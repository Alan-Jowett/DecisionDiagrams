#ifndef LIBTEDDY_TSL_SYSTEM_DESCRIPTION_HPP
#define LIBTEDDY_TSL_SYSTEM_DESCRIPTION_HPP

#include <fmt/core.h>

#include <ostream>
#include <vector>

namespace teddy::tsl {

struct system_description {
  int systemId_;
  int stateCount_;
  int componentCount_;
  std::vector<int> structureFunction_;
  std::vector<int> domains_;
  std::vector<std::vector<double>> componentProbabilities_;
  std::vector<double> stateProbabilities_;
  std::vector<double> availabilities_;
  std::vector<double> unavailabilities_;
  std::vector<std::vector<std::vector<int>>> mcvs_;
  std::vector<std::vector<std::vector<int>>> mpvs_;

  // component index; system state; component state
  std::vector<std::vector<std::vector<double>>> structuralImportances_;
  std::vector<std::vector<std::vector<double>>> birnbaumImportances_;
  std::vector<std::vector<std::vector<double>>> fussellVeselyImportances_;

  double floatingTolerance_;
};

auto operator<< (std::ostream &ost, system_description const &system)
  -> std::ostream &;

} // namespace teddy::tsl

#endif

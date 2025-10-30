#include <libtsl/inc/generators.hpp>

namespace teddy::tsl {

auto make_probability_vector (int32 const varCount, std::ranlux48 &rng)
  -> std::vector<double> {
  std::vector<double> probs(as_usize(varCount));
  for (int32 i = 0; i < ssize(probs); ++i) {
    std::uniform_real_distribution<double> dist(.0, 1.0);
    probs[as_uindex(i)] = dist(rng);
  }
  return probs;
}

auto make_time_probability_vector (int32 const varCount, std::ranlux48 &rng)
  -> std::vector<probs::prob_dist> {
  std::vector<probs::prob_dist> probs;

  auto const mkExponential = [] (std::ranlux48 &gen) -> probs::prob_dist {
    double const from = 0.2;
    double const to   = 1.0;
    std::uniform_real_distribution<double> distRate(from, to);
    return probs::exponential(distRate(gen));
  };

  // auto const mkWeibull = [] (std::ranlux48& gen) -> probs::prob_dist
  // {
  //     std::uniform_real_distribution<double> distShape(0.5, 1.0);
  //     return probs::weibull(1.0, distShape(gen));
  // };

  // auto const mkConstant = [] (std::ranlux48& gen) -> probs::prob_dist
  // {
  //     std::uniform_real_distribution<double> distProb(0.2, 1.0);
  //     return probs::constant(distProb(gen));
  // };

  std::vector<probs::prob_dist (*)(std::ranlux48 &)> distGenerators(
    // {+mkExponential, +mkWeibull, +mkConstant}
    {+mkExponential}
  );

  std::uniform_int_distribution<std::size_t> distGen(
    std::size_t {0},
    distGenerators.size() - 1
  );
  for (int i = 0; i < varCount; ++i) {
    auto const gen = distGenerators[distGen(rng)];
    probs.push_back(gen(rng));
  }

  return probs;
}

#ifdef LIBTEDDY_SYMBOLIC_RELIABILITY

auto make_time_symprobability_vector (int32 const varCount, std::ranlux48 &rng)
  -> std::vector<symprobs::expression> {
  std::vector<symprobs::expression> probs;

  auto const mkExponential = [] (std::ranlux48 &gen) -> symprobs::expression {
    std::uniform_real_distribution<double> distRate(0.2, 1.0);
    return symprobs::exponential(distRate(gen));
  };

  // auto const mkWeibull = [] (std::ranlux48& gen) -> symprobs::expression
  // {
  //     std::uniform_real_distribution<double> distShape(0.5, 1.0);
  //     return symprobs::weibull(1.0, distShape(gen));
  // };

  // auto const mkConstant = [] (std::ranlux48& gen) -> symprobs::expression
  // {
  //     std::uniform_real_distribution<double> distProb(0.2, 1.0);
  //     return symprobs::constant(distProb(gen));
  // };

  std::vector<symprobs::expression (*)(std::ranlux48 &)> distGenerators(
    // {+mkExponential, +mkWeibull, +mkConstant}
    {+mkExponential}
  );

  std::uniform_int_distribution<std::size_t> distGen(
    std::size_t {0},
    distGenerators.size() - 1
  );
  probs.reserve(as_usize(varCount));
  for (int i = 0; i < varCount; ++i) {
    probs.push_back(mkExponential(rng));
  }

  return probs;
}

#endif

}  // namespace teddy::tsl

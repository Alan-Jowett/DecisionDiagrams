#include <libtsl/inc/probabilities.hpp>

namespace teddy::tsl {

template<class Degree, class Domain>
auto make_prob_vector (
  diagram_manager<Degree, Domain> const &manager,
  std::ranlux48 &rng
) -> std::vector<double> {
  auto const domains = manager.get_domains();
  auto probs         = std::vector<double>(as_usize(manager.get_var_count()));
  for (auto i = 0; i < ssize(probs); ++i) {
    auto dist           = std::uniform_real_distribution<double>(.0, 1.0);
    probs[as_uindex(i)] = dist(rng);
  }
  return probs;
}

template<class Degree, class Domain>
auto make_prob_matrix (
  diagram_manager<Degree, Domain> const &manager,
  std::ranlux48 &rng
) -> std::vector<std::vector<double>> {
  auto const domains = manager.get_domains();
  auto probs
    = std::vector<std::vector<double>>(as_usize(manager.get_var_count()));
  for (auto i = 0; i < ssize(probs); ++i) {
    auto dist = std::uniform_real_distribution<double>(.0, 1.0);
    probs[as_uindex(i)].resize(as_usize(domains[as_uindex(i)]));
    for (auto j = 0; j < domains[as_uindex(i)]; ++j) {
      probs[as_uindex(i)][as_uindex(j)] = dist(rng);
    }
    auto const sum = std::reduce(
      begin(probs[as_uindex(i)]),
      end(probs[as_uindex(i)]),
      0.0,
      std::plus<>()
    );
    for (auto j = 0; j < domains[as_uindex(i)]; ++j) {
      probs[as_uindex(i)][as_uindex(j)] /= sum;
    }
  }
  return probs;
}

}  // namespace teddy::tsl

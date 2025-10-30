#ifndef LIBTEDDY_TSL_ITERATORS_HPP
#define LIBTEDDY_TSL_ITERATORS_HPP

#include <iterator>
#include <utility>
#include <vector>

namespace teddy::tsl {

/**
 * \brief Sentinel for domain iterator.
 */
struct domain_iterator_sentinel { };

/**
 * \brief Iterator for domain of a function.
 */
class domain_iterator {
public:
  using difference_type   = std::ptrdiff_t;
  using value_type        = std::vector<int>;
  using pointer           = value_type *;
  using reference         = value_type &;
  using iterator_category = std::input_iterator_tag;

public:
  /**
   * \brief Initializes this as end iterator.
   */
  domain_iterator();

  /**
   * \brief Initializes using implicit order.
   *  Uses implicit order where x0 is the
   *  least significant (changes most often).
   *  \p domains of individual variables
   */
  explicit domain_iterator(std::vector<int> domains);

  /**
   * \brief Initializes using explicitly provided order.
   *
   *  Uses order of variables defined in \p order . Variable with
   *  index \c order[0] changes most often, then variable with
   *  index \c order[1] and so on...
   *  \p domains of individual variables
   *  \p order   order in which variables are incremented
   */
  domain_iterator(std::vector<int> domains, std::vector<int> order);

  /**
   * \brief Initializes using explicitly provided order and fixed values.
   *
   *  Uses order of variables defined in \p order . Variable with
   *  index \c order[0] changes most often, then variable with
   *  index \c order[1] and so on... while skipping variables
   *  defined as fixed by \p fixed .
   *  \p domains of individual variables
   *  \p order   order in which variables are incremented
   *  \p fixed   defines variables with fixed value
   */
  domain_iterator(
    std::vector<int> domains,
    std::vector<int> order,
    std::vector<std::pair<int, int>> fixed
  );

  auto operator* () const -> std::vector<int> const &;

  auto operator++ () -> domain_iterator &;

  auto operator++ (int) -> domain_iterator;

  auto operator== (domain_iterator const &rhs) const -> bool;

  auto operator!= (domain_iterator const &rhs) const -> bool;

  auto operator== (domain_iterator_sentinel) const -> bool;

  auto operator!= (domain_iterator_sentinel) const -> bool;

private:
  std::vector<int> domains_;
  std::vector<int> indices_;
  std::vector<int> varVals_;
};

/**
 * \brief Sentinel for evaluating iterator.
 */
struct evaluating_iterator_sentinel { };

/**
 * \brief Iterator that evaluates an expression over a domain.
 */
template<class Expression>
class evaluating_iterator {
public:
  using difference_type   = std::ptrdiff_t;
  using value_type        = int;
  using pointer           = value_type *;
  using reference         = value_type &;
  using iterator_category = std::input_iterator_tag;

public:
  evaluating_iterator();

  evaluating_iterator(domain_iterator iterator, Expression const &expr);

  auto operator* () const -> int;

  auto operator++ () -> evaluating_iterator &;

  auto operator++ (int) -> evaluating_iterator;

  auto operator== (evaluating_iterator_sentinel s) const -> bool;

  auto operator!= (evaluating_iterator_sentinel s) const -> bool;

  [[nodiscard]]
  auto get_var_vals () const -> const std::vector<int> &;

private:
  domain_iterator domainIterator_;
  const Expression *expr_;
};

template<class Expression>
auto operator== (
  evaluating_iterator_sentinel s,
  evaluating_iterator<Expression> const &it
) -> bool {
  return it == s;
}

template<class Expression>
auto operator!= (
  evaluating_iterator_sentinel s,
  evaluating_iterator<Expression> const &it
) -> bool {
  return it != s;
}

/**
 * \brief Output iterator that feeds outputed values into a function.
 */
template<class OutputFunction>
class forwarding_iterator {
public:
  using difference_type   = std::ptrdiff_t;
  using value_type        = forwarding_iterator &;
  using pointer           = value_type;
  using reference         = value_type;
  using iterator_category = std::output_iterator_tag;

public:
  forwarding_iterator() = default;

  explicit forwarding_iterator(OutputFunction f) : outputFunction_(std::move(f)) {
  }

  auto operator++ () -> forwarding_iterator & {
    return *this;
  }

  auto operator++ (int) -> forwarding_iterator & {
    return *this;
  }

  auto operator* () -> forwarding_iterator & {
    return *this;
  }

  auto operator= (auto &&arg) -> forwarding_iterator & {
    outputFunction_(std::forward<decltype(arg)>(arg));
    return *this;
  }

  auto operator= (auto &&arg) const -> forwarding_iterator & {
    outputFunction_(std::forward<decltype(arg)>(arg));
    return *this;
  }

private:
  OutputFunction outputFunction_;
};

} // namespace teddy::tsl

#endif

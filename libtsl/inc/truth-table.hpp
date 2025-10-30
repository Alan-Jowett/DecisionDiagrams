#ifndef LIBTEDDY_TSL_TRUTH_TABLE_HPP
#define LIBTEDDY_TSL_TRUTH_TABLE_HPP

#include <cassert>
#include <vector>

namespace teddy::tsl {

/**
 *  \brief TODO
 */
struct truth_table {
  truth_table(std::vector<int> vector, std::vector<int> domains);

  [[nodiscard]]
  auto get_var_count () const -> int;
  [[nodiscard]]
  auto get_vector () const -> std::vector<int> const &;
  [[nodiscard]]
  auto get_domains () const -> std::vector<int> const &;
  [[nodiscard]]
  auto get_offsets () const -> std::vector<int> const &;
  [[nodiscard]]
  auto get_max_val () const -> int;

  std::vector<int> vector_;
  std::vector<int> domain_;
  std::vector<int> offset_;
  int maxValue_;
};

/**
 *  \brief TODO
 */
auto satisfy_count (truth_table const &table, int val) -> long long;

/**
 *  \brief TODO
 */
auto satisfy_all (truth_table const &table, int val)
  -> std::vector<std::vector<int>>;

/**
 *  \brief TODO
 */
auto domain_size (truth_table const &table) -> long long;

/**
 *  \brief TODO
 */
auto evaluate (truth_table const &table, std::vector<int> const &vars)
  -> int;

/**
 *  \brief Maps values of variables to index in the vector.
 */
auto to_index (truth_table const &table, std::vector<int> const &vars)
  -> int;

/**
 *  \brief Invokes \p f with each element of the domain.
 */
template<class F>
auto domain_for_each (
  int varcount,
  std::vector<int> const &vector,
  std::vector<int> const &domains,
  F f
) -> void;

/**
 *  \brief Invokes \p f with each element of the domain.
 */
template<class F>
auto domain_for_each (truth_table const &table, F f) -> void;

template<class Op>
auto apply (truth_table const &lhs, truth_table const &rhs, Op operation)
  -> truth_table;

template<class Op>
auto apply_mutable (truth_table &lhs, truth_table const &rhs, Op operation)
  -> void;

/**
 *  \brief Element-wise comparison of vectors using \p cmp
 *  \param lhs first vector
 *  \param rhs first vector
 *  \param op comparison operation, e.g. <
 *  \return true iff each element of \p lsh is \p cmp than \p rhs
 */
template<class T, class Cmp>
auto compare (std::vector<T> const &lhs, std::vector<T> const &rhs, Cmp cmp)
  -> bool;

} // namespace teddy::tsl

#include <libtsl/impl/truth-table.inl>

#endif

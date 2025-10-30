#ifndef LIBTEDDY_TSL_EXPRESSION_HPP
#define LIBTEDDY_TSL_EXPRESSION_HPP

#include <memory>
#include <random>
#include <variant>
#include <vector>

namespace teddy::tsl {

/**
 *  \brief Strong type for vector of terms.
 */
struct minmax_expr {
  std::vector<std::vector<int>> terms_;
};

/**
 *  \brief Makes random minmax expression.
 */
auto make_minmax_expression (
  std::ranlux48 &indexRng,
  int varCount,
  int termCount,
  int termSize
) -> minmax_expr;

/**
 *  \brief Evaluates \p expr using values of variables in \p vs .
 */
auto evaluate_expression (minmax_expr const &expr, std::vector<int> const &vs)
  -> int;

/**
 *  \brief Tags expression node representing variable.
 */
struct expr_node_variable { };

/**
 *  \brief Tags expression node representing constant.
 */
struct expr_node_constant { };

/**
 *  \brief Tags expression node representing operation.
 */
struct expr_node_operation { };

/**
 *  \brief Specifies operation of the operation node.
 */
enum class operation_type {
  Min,
  Max
};

/**
 *  \brief Node of an expression tree.
 */
class expr_node {
private:
  struct operation_t {
    operation_t(
      operation_type o,
      std::unique_ptr<expr_node> l,
      std::unique_ptr<expr_node> r
    );
    operation_type op_;
    std::unique_ptr<expr_node> l_;
    std::unique_ptr<expr_node> r_;
  };

  struct variable_t {
    explicit variable_t(int i);
    int i_;
  };

  struct constant_t {
    explicit constant_t(int c);
    int c_;
  };

public:
  expr_node(expr_node_variable, int i);

  expr_node(expr_node_constant, int c);

  expr_node(
    expr_node_operation,
    operation_type o,
    std::unique_ptr<expr_node> l,
    std::unique_ptr<expr_node> r
  );

  [[nodiscard]] auto is_variable () const -> bool;

  [[nodiscard]] auto is_constant () const -> bool;

  [[nodiscard]] auto is_operation () const -> bool;

  [[nodiscard]] auto get_index () const -> int;

  [[nodiscard]] auto get_value () const -> int;

  [[nodiscard]] auto evaluate (int l, int r) const -> int;

  [[nodiscard]] auto get_left () const -> const expr_node &;

  [[nodiscard]] auto get_right () const -> const expr_node &;

private:
  std::variant<operation_t, variable_t, constant_t> data_;
};

/**
 *  \brief Makes random minmax expression tree.
 */
auto make_expression_tree (int varcount, std::ranlux48 &rngtype, std::ranlux48 &rngbranch)
  -> std::unique_ptr<expr_node>;

/**
 *  \brief Evaluates \p expr using values of variables in \p vs .
 */
auto evaluate_expression (expr_node const &expr, std::vector<int> const &vs)
  -> int;

} // namespace teddy::tsl

#endif

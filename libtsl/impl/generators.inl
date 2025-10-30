#include <libtsl/inc/generators.hpp>

namespace teddy::tsl {

template<class Degree, class Domain>
auto make_diagram (
  minmax_expr const &expr,
  diagram_manager<Degree, Domain> &manager,
  fold_type const foldtype
) {
  auto const min_fold = [&manager, foldtype] (auto &diagrams) {
    return foldtype == fold_type::Left
           ? manager.template left_fold<ops::MIN>(diagrams)
           : manager.template tree_fold<ops::MIN>(diagrams);
  };

  auto const max_fold = [&manager, foldtype] (auto &diagrams) {
    return foldtype == fold_type::Left
           ? manager.template left_fold<ops::MAX>(diagrams)
           : manager.template tree_fold<ops::MAX>(diagrams);
  };

  using diagram_t = typename diagram_manager<Degree, Domain>::diagram_t;
  std::vector<diagram_t> termDs;
  for (auto const &eTerm : expr.terms_) {
    auto vars = manager.variables(eTerm);
    termDs.push_back(min_fold(vars));
  }
  return max_fold(termDs);
}

template<class Degree, class Domain>
auto make_diagram (
  std::unique_ptr<tsl::expr_node> const &expr,
  diagram_manager<Degree, Domain> &manager
) {
  return manager.from_expression_tree(*expr);
}

template<class Degree, class Domain>
auto make_diagram (
  tsl::expr_node const &expr,
  diagram_manager<Degree, Domain> &manager
) {
  return manager.from_expression_tree(expr);
}

}  // namespace teddy::tsl

#include <libtsl/inc/truth-table-reliability.hpp>

namespace teddy::tsl {

template<class F>
auto dpld (truth_table const &table, var_change const var, F change)
  -> truth_table {
  auto result = std::vector<int>(table.get_vector().size());

  domain_for_each(
    table,
    [&,
     tmpElem
     = std::vector<int>()] (auto const fFrom, auto const &elem) mutable {
      if (elem[as_uindex(var.index_)] == var.from_) {
        auto const varIndex  = as_uindex(var.index_);
        tmpElem              = elem;
        tmpElem[varIndex]    = var.to_;
        auto const fTo       = evaluate(table, tmpElem);
        auto const derValue  = change(fFrom, fTo) ? 1 : 0;
        auto const varDomain = table.get_domains()[varIndex];
        for (auto varValue = 0; varValue < varDomain; ++varValue) {
          tmpElem[varIndex]   = varValue;
          auto const derIndex = as_uindex(to_index(table, tmpElem));
          result[derIndex]    = derValue;
        }
      }
    }
  );

  return {std::move(result), table.get_domains()};
}

template<class F>
auto dpld_e (truth_table const &table, var_change const var, F change)
  -> truth_table {
  auto result = std::vector<int>(table.get_vector().size());

  domain_for_each(
    table,
    [&,
     index = 0U,
     tmpelem
     = std::vector<int>()] (auto const ffrom, auto const &elem) mutable {
      if (elem[as_uindex(var.index_)] != var.from_) {
        result[index] = Undefined;
      } else {
        tmpelem                       = elem;
        tmpelem[as_uindex(var.index_)] = var.to_;
        auto const fto                = evaluate(table, tmpelem);
        result[index]                 = change(ffrom, fto) ? 1 : 0;
      }
      ++index;
    }
  );

  return {std::move(result), table.get_domains()};
}

}  // namespace teddy::tsl

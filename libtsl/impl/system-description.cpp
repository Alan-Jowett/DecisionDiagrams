#include <libtsl/inc/system-description.hpp>

namespace teddy::tsl {

auto operator<< (std::ostream &ost, system_description const &system)
  -> std::ostream & {
  ost << fmt::format("[system_{}]", system.systemId_);
  return ost;
}


}

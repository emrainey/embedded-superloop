#include <jarnax/spi/Driver.hpp>

namespace jarnax {
namespace spi {

Driver::Driver(jarnax::spi::Transactor& tr) : jarnax::spi::Coordinator{tr} {}

}    // namespace spi
}    // namespace jarnax
#include <jarnax/i2c/Driver.hpp>

namespace jarnax {
namespace i2c {

Driver::Driver(jarnax::i2c::Transactor& tr) : jarnax::i2c::Coordinator{tr} {}

}    // namespace i2c
}    // namespace jarnax
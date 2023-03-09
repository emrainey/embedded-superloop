#include "jarnax/system.h"

namespace system {

__attribute__((used, section(".vectors"))) cortex::m4::VectorTable vector_table;

}
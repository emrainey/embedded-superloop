#include "cortex/mcu.hpp"

namespace cortex {
namespace swo {
void emit(Port port, std::uint8_t value) {
    auto index = to_underlying(port);
    while (instruction_trace_macrocell.stimulus_port[index].read.fifo_ready == 0U) { /* spin */
    }
    instruction_trace_macrocell.stimulus_port[index].write.u08 = value;
}

void emit(Port port, char const array[], std::size_t bytes) {
    for (std::size_t i = 0; i < bytes; ++i) {
        emit(port, std::uint8_t(array[i]));
    }
}

void emit(Port port, char const* const str) {
    char const* tmp = str;
    while (*tmp != '\0') {
        emit(port, std::uint8_t(*tmp++));
    }
}

void emit(Port port, std::uint8_t array[], std::size_t bytes) {
    for (std::size_t i = 0; i < bytes; ++i) {
        emit(port, array[i]);
    }
}
}    // namespace swo
}    // namespace cortex
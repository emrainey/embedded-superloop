#include "cortex/core.hpp"
#include "cortex/nvic.hpp"

namespace cortex {

namespace nvic {

void Enable(std::uint32_t interrupt) {
    std::uint32_t index = interrupt & nvic::mask;
    std::uint32_t element = interrupt >> nvic::shift;
    nested_interrupt_vector_controller.enable[element] = (1 << index);
}

bool IsEnabled(std::uint32_t interrupt) {
    std::uint32_t index = interrupt & nvic::mask;
    std::uint32_t element = interrupt >> nvic::shift;
    std::uint32_t element_mask = (1 << index);
    return bool(nested_interrupt_vector_controller.enable[element] & element_mask);
}

inline void Disable(std::uint32_t interrupt) {
    std::uint32_t index = interrupt & nvic::mask;
    std::uint32_t element = interrupt >> nvic::shift;
    nested_interrupt_vector_controller.clear[element] = (1 << index);
}

void Cancel(std::uint32_t interrupt) {
    std::uint32_t index = interrupt & nvic::mask;
    std::uint32_t element = interrupt >> nvic::shift;
    nested_interrupt_vector_controller.cancel[element] = (1 << index);
}

void Pend(std::uint32_t interrupt) {
    std::uint32_t index = interrupt & nvic::mask;
    std::uint32_t element = interrupt >> nvic::shift;
    nested_interrupt_vector_controller.pending[element] = (1 << index);
}

bool IsPending(std::uint32_t interrupt) {
    std::uint32_t index = interrupt & nvic::mask;
    std::uint32_t element = interrupt >> nvic::shift;
    std::uint32_t element_mask = (1 << index);
    return bool(nested_interrupt_vector_controller.pending[element] & element_mask);
}

bool IsActive(std::uint32_t interrupt) {
    std::uint32_t index = interrupt & nvic::mask;
    std::uint32_t element = interrupt >> nvic::shift;
    std::uint32_t element_mask = (1 << index);
    return bool(nested_interrupt_vector_controller.active[element] & element_mask);
}

void Prioritize(std::uint32_t interrupt, std::uint8_t value) {
    if (interrupt < limit) {
        nested_interrupt_vector_controller.priority[interrupt] = value;
    }
}
}    // namespace nvic
}    // namespace cortex
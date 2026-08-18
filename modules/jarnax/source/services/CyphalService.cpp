#include "jarnax/services/CyphalService.hpp"
#include "core/Status.hpp"

namespace jarnax {
namespace cyphal {

CyphalService::CyphalService()
    : m_nodes{} {
    for (std::size_t i = 0U; i < m_nodes.count(); ++i) {
        m_nodes[i] = nullptr;
    }
}

bool CyphalService::Execute() {
    for (std::size_t i = 0U; i < m_nodes.count(); ++i) {
        auto& node = m_nodes[i];
        if (node != nullptr) {
            bool keep_going = node->RunOnce();
            if (not keep_going) {
                // the node was allocated else where, so we just null it out here
                node = nullptr;
            }
        }
    }
    return true;
}

core::Status CyphalService::Enlist(Node* node) {
    for (std::size_t i = 0U; i < m_nodes.count(); ++i) {
        auto& existing_node = m_nodes[i];
        if (existing_node == nullptr) {
            existing_node = node;
            return core::Status{};
        }
    }
    return core::Status{core::Result::NotAvailable, core::Cause::Resource};
}

core::Status CyphalService::Dismiss(Node* node) {
    for (std::size_t i = 0U; i < m_nodes.count(); ++i) {
        auto& existing_node = m_nodes[i];
        if (existing_node == node) {
            existing_node = nullptr;
            return core::Status{};
        }
    }
    return core::Status{core::Result::NotAvailable, core::Cause::Resource};
}

}    // namespace cyphal
}    // namespace jarnax

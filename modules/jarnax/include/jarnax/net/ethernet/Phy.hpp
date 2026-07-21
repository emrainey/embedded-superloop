#ifndef JARNAX_NET_ETHERNET_PHY_HPP
#define JARNAX_NET_ETHERNET_PHY_HPP

/// @file
/// The Ethernet PHY Declaration

#include "jarnax/Driver.hpp"
#include "jarnax/Transactable.hpp"
#include "jarnax/net/ethernet/Driver.hpp"

namespace jarnax {
namespace net {
namespace ethernet {
namespace mdio {

/// The MDIO operation type for the MDIO transactions. This is used to specify the type of MDIO transaction being performed (e.g., read, write,
/// address).
enum class Operation : uint16_t {
    /// Address operation for MDIO transactions, used to specify the address of the PHY register for subsequent read or write operations.
    Address = 0U,
    /// Read operation for MDIO transactions, used to read data from a PHY register.
    Read = 1U,
    /// Write operation for MDIO transactions, used to write data to a PHY register.
    Write = 2U,
};

/// The MDIO clause for the MDIO transactions. This is used to specify the format of the MDIO transaction (e.g., Clause 22 or Clause 45) being
/// performed.
enum class Clause : uint16_t {
    /// Clause 22 MDIO transaction format, which uses a 5-bit PHY address and a 5-bit register address for communicating with the PHY.
    _22 = 22U,
    /// Clause 45 MDIO transaction format, which uses a 5-bit device address and a 16-bit register address for communicating with the PHY.
    _45 = 45U,
};

/// The number of times an MDIO transaction should be retried if it fails. This is used as the default number of retries for MDIO transactions, and it
/// can be overridden on a per-transaction basis if needed. The number of retries can be adjusted based on the reliability of the MDIO communication
/// and the requirements of the application. A higher number of retries can improve the chances of successful communication with the PHY in the
/// presence of transient errors, but it can also increase the latency of MDIO transactions if there are persistent issues with the communication.
constexpr static std::size_t DefaultRetries{3U};

/// The MDIO structure is used for communicating with the Ethernet PHY over the MDIO interface. The MDIO interface is a serial bus that is used to
/// read and write registers on the Ethernet PHY, which is a separate chip from the Ethernet controller. The MDIO structure contains the address of
/// the PHY register to read or write, as well as the data to write to the PHY register or the data read from the PHY register. The Ethernet Driver
/// can use the MDIO structure to communicate with the PHY and configure it. This structure supports both Clause 22 and Clause 45 MDIO transactions,
/// which are two different formats for communicating with the PHY over the MDIO interface. The address field can be used to specify the register
/// address for Clause 22 transactions, or the device address and register address for Clause 45 transactions.
struct Transaction final : public jarnax::Transactable<Transaction, DefaultRetries> {
    Clause clause;    ///< The MDIO clause for the transaction, indicating the format of the MDIO transaction (e.g., Clause 22 or Clause 45).
    //+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    /// The MDIO operation type for the transaction, indicating the type of MDIO transaction being performed (e.g., read,
    /// write, address).
    Operation operation       : 2;
    /// The address for the MDIO transaction, which can be used to specify the register address for Clause 22 transactions,
    /// or the device address and register address for Clause 45 transactions.
    uint16_t phy_address      : 5;
    /// The address for the MDIO transaction, which can be used to specify the register address for Clause 22 transactions, or the device address and
    /// register address for Clause 45 transactions. The interpretation of this field depends on the clause specified for the transaction. For Clause
    /// 22 transactions, this field is used to specify the register address of the PHY. For Clause 45 transactions, this field is used to specify the
    /// device address of the PHY, and the register address is specified in the data field of the transaction.
    uint16_t register_address : 5;
    uint16_t                  : 4;    ///< Reserved bits for alignment, should be set to 0.
    //+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    uint16_t data;    ///< The data to write to the PHY register for write operations, or the data read from the PHY register for read operations.
    //+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    /// The device address for Clause 45 MDIO transactions, which is used to specify the device address of the PHY for Clause 45 transactions. This
    /// field is only used for Clause 45 transactions, and it is ignored for Clause 22 transactions.
    uint16_t device_address : 5;
    uint16_t                : 11;    ///< Reserved bits for alignment, should be set to 0.
    //+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

    void Clear() {
        clause = Clause::_22;
        operation = Operation::Address;
        phy_address = 0U;
        register_address = 0U;
        data = 0U;
        device_address = 0U;
    }
};

}    // namespace mdio

/// The pure virtual interface which all Ethernet PHY Drivers implement. The Ethernet PHY Driver is responsible for controlling the physical layer of
/// the Ethernet communication, which includes tasks such as initializing the PHY, configuring the link speed and
class Phy : public jarnax::Driver {
public:
    /// Schedules a PHY operation to be performed on the next execution of the Ethernet Driver. This method is used by higher-level network protocols
    /// (e.g., ARP, IP) to request that the Ethernet Driver perform a PHY operation (e.g., reading or writing a PHY register) on the next execution of
    /// the Ethernet Driver. The Ethernet Driver is responsible for scheduling the PHY operation and ensuring that it is performed at the appropriate
    /// time during the execution of the Driver. The MDIO structure is used to specify the details of the PHY operation, such as the register address
    /// and the data to write or read from the PHY register. The Ethernet Driver can use this method to perform PHY operations as needed to configure
    /// the PHY or to read status information from the PHY during the execution of the Driver.
    virtual core::Status Schedule(mdio::Transaction* mdio) = 0;

protected:
    ~Phy() = default;
};

}    // namespace ethernet
}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_ETHERNET_PHY_HPP

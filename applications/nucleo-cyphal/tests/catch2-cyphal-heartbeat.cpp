#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "uavcan/node/Heartbeat_1_0.h"

#include <cstdint>
#include <cstring>

namespace {

void Zero(uint8_t* const data, size_t const size) {
    std::memset(data, 0, size);
}

}    // namespace

// The Heartbeat payload serializes to 7 bytes on the wire:
//
//   obligate uint32 uptime                    (LE bytes 0..3)
//   obligated uavcan.node.Health.1.0 health   (byte 4)
//   obligated uavcan.node.Mode.1.0 mode       (byte 5)
//   saturated uint8 vendor_specific_status_code (byte 6)
TEST_CASE("Heartbeat serialize produces the expected 7-byte wire format", "[cyphal][heartbeat]") {
    uavcan_node_Heartbeat_1_0 heartbeat{};
    uavcan_node_Heartbeat_1_0_initialize_(&heartbeat);
    heartbeat.uptime = 1U;
    heartbeat.health.value = uavcan_node_Health_1_0_NOMINAL;
    heartbeat.mode.value = uavcan_node_Mode_1_0_OPERATIONAL;
    heartbeat.vendor_specific_status_code = 0U;

    uint8_t buffer[uavcan_node_Heartbeat_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_]{};
    size_t size = sizeof(buffer);
    REQUIRE(uavcan_node_Heartbeat_1_0_serialize_(&heartbeat, buffer, &size) == NUNAVUT_SUCCESS);
    REQUIRE(size == uavcan_node_Heartbeat_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_);

    // uptime=1 (LE), nominal health=0, operational mode=0, vendor code=0
    uint8_t const expected[] = {0x01U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};
    REQUIRE(std::memcmp(buffer, expected, sizeof(expected)) == 0);
}

TEST_CASE("Heartbeat serialize reflects uptime and health/mode/vendor fields", "[cyphal][heartbeat]") {
    uavcan_node_Heartbeat_1_0 heartbeat{};
    uavcan_node_Heartbeat_1_0_initialize_(&heartbeat);
    heartbeat.uptime = 0x01020304U;
    heartbeat.health.value = uavcan_node_Health_1_0_CAUTION;
    heartbeat.mode.value = uavcan_node_Mode_1_0_MAINTENANCE;
    heartbeat.vendor_specific_status_code = 0xABU;

    uint8_t buffer[uavcan_node_Heartbeat_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_]{};
    size_t size = sizeof(buffer);
    REQUIRE(uavcan_node_Heartbeat_1_0_serialize_(&heartbeat, buffer, &size) == NUNAVUT_SUCCESS);

    // uptime 0x04030201 LE, caution health=2, maintenance mode=2, vendor=0xAB
    uint8_t const expected[] = {0x04U, 0x03U, 0x02U, 0x01U, 0x02U, 0x02U, 0xABU};
    REQUIRE(std::memcmp(buffer, expected, sizeof(expected)) == 0);
}

TEST_CASE("Heartbeat deserialize round-trips the serialized payload", "[cyphal][heartbeat]") {
    uavcan_node_Heartbeat_1_0 heartbeat{};
    uavcan_node_Heartbeat_1_0_initialize_(&heartbeat);
    heartbeat.uptime = 1234U;
    heartbeat.health.value = uavcan_node_Health_1_0_WARNING;
    heartbeat.mode.value = uavcan_node_Mode_1_0_OPERATIONAL;
    heartbeat.vendor_specific_status_code = 7U;

    uint8_t buffer[uavcan_node_Heartbeat_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_]{};
    size_t size = sizeof(buffer);
    REQUIRE(uavcan_node_Heartbeat_1_0_serialize_(&heartbeat, buffer, &size) == NUNAVUT_SUCCESS);
    REQUIRE(size == uavcan_node_Heartbeat_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_);

    uavcan_node_Heartbeat_1_0 deserialized{};
    Zero(reinterpret_cast<uint8_t*>(&deserialized), sizeof(deserialized));
    size_t deserialize_size = size;
    REQUIRE(uavcan_node_Heartbeat_1_0_deserialize_(&deserialized, buffer, &deserialize_size) == NUNAVUT_SUCCESS);

    REQUIRE(deserialized.uptime == 1234U);
    REQUIRE(deserialized.health.value == uavcan_node_Health_1_0_WARNING);
    REQUIRE(deserialized.mode.value == uavcan_node_Mode_1_0_OPERATIONAL);
    REQUIRE(deserialized.vendor_specific_status_code == 7U);
}

TEST_CASE("Heartbeat defaultdicts match the Cyphal version", "[cyphal][heartbeat]") {
    uavcan_node_Heartbeat_1_0 heartbeat{};
    uavcan_node_Heartbeat_1_0_initialize_(&heartbeat);
    REQUIRE(heartbeat.uptime == 0U);
    REQUIRE(heartbeat.health.value == uavcan_node_Health_1_0_NOMINAL);
    REQUIRE(heartbeat.mode.value == uavcan_node_Mode_1_0_OPERATIONAL);
    REQUIRE(heartbeat.vendor_specific_status_code == 0U);

    // The publication-period and offline-timeout constants from the DSDL.
    REQUIRE(uavcan_node_Heartbeat_1_0_MAX_PUBLICATION_PERIOD == 1U);
    REQUIRE(uavcan_node_Heartbeat_1_0_OFFLINE_TIMEOUT == 3U);
}
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "uavcan/node/GetInfo_1_0.h"

#include <cstdint>
#include <cstring>

namespace {

uavcan_node_GetInfo_Response_1_0 MakeAssignedResponse() {
    uavcan_node_GetInfo_Response_1_0 info{};
    uavcan_node_GetInfo_Response_1_0_initialize_(&info);

    info.protocol_version.major = 1U;
    info.protocol_version.minor = 0U;

    info.hardware_version.major = 0U;
    info.hardware_version.minor = 0U;

    info.software_version.major = 1U;
    info.software_version.minor = 0U;

    info.software_vcs_revision_id = 0U;

    uint8_t const unique_id[16U] = {0xDEU, 0xADU, 0xBEU, 0xEFU, 0x00U, 0x01U, 0x02U, 0x03U,
                                    0x10U, 0x11U, 0x12U, 0x13U, 0x20U, 0x21U, 0x22U, 0x23U};
    std::memcpy(info.unique_id, unique_id, sizeof(unique_id));

    char const name[] = "com.emrainey.superloop.nucleo";
    info.name.count = sizeof(name) - 1U;    // exclude the NUL terminator
    std::memcpy(info.name.elements, name, info.name.count);
    return info;
}

// The GetInfo request is sealed; its serialized payload is always empty (zero bytes).
TEST_CASE("GetInfo Request serializes to zero bytes", "[cyphal][getinfo][request]") {
    uavcan_node_GetInfo_Request_1_0 request{};
    uavcan_node_GetInfo_Request_1_0_initialize_(&request);

    uint8_t buffer[uavcan_node_GetInfo_Request_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_ + 4U]{0xAAU, 0xBBU};
    size_t size = sizeof(buffer);
    REQUIRE(uavcan_node_GetInfo_Request_1_0_serialize_(&request, buffer, &size) == NUNAVUT_SUCCESS);
    REQUIRE(size == 0U);
}

TEST_CASE("GetInfo Request deserialize is a no-op", "[cyphal][getinfo][request]") {
    uint8_t const data[] = {0x01U, 0x02U, 0x03U};
    uavcan_node_GetInfo_Request_1_0 request{};
    uavcan_node_GetInfo_Request_1_0_initialize_(&request);
    size_t size = sizeof(data);
    REQUIRE(uavcan_node_GetInfo_Request_1_0_deserialize_(&request, data, &size) == NUNAVUT_SUCCESS);
    REQUIRE(size == 0);
}

TEST_CASE("GetInfo Response round-trips the assigned fields", "[cyphal][getinfo][response]") {
    uavcan_node_GetInfo_Response_1_0 info = MakeAssignedResponse();

    uint8_t buffer[uavcan_node_GetInfo_Response_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_]{};
    size_t size = sizeof(buffer);
    REQUIRE(uavcan_node_GetInfo_Response_1_0_serialize_(&info, buffer, &size) == NUNAVUT_SUCCESS);

    uavcan_node_GetInfo_Response_1_0 deserialized{};
    std::memset(&deserialized, 0, sizeof(deserialized));
    size_t deserialized_size = size;
    REQUIRE(uavcan_node_GetInfo_Response_1_0_deserialize_(&deserialized, buffer, &deserialized_size) == NUNAVUT_SUCCESS);
    REQUIRE(deserialized_size == size);

    REQUIRE(deserialized.protocol_version.major == 1U);
    REQUIRE(deserialized.protocol_version.minor == 0U);
    REQUIRE(deserialized.hardware_version.major == 0U);
    REQUIRE(deserialized.hardware_version.minor == 0U);
    REQUIRE(deserialized.software_version.major == 1U);
    REQUIRE(deserialized.software_version.minor == 0U);
    REQUIRE(deserialized.software_vcs_revision_id == 0U);
    REQUIRE(std::memcmp(deserialized.unique_id, info.unique_id, sizeof(info.unique_id)) == 0);
    REQUIRE(deserialized.name.count == info.name.count);
    REQUIRE(std::memcmp(deserialized.name.elements, info.name.elements, info.name.count) == 0);
}

TEST_CASE("GetInfo Response default-initializes to zeros by the library", "[cyphal][getinfo][response]") {
    uavcan_node_GetInfo_Response_1_0 info{};
    uavcan_node_GetInfo_Response_1_0_initialize_(&info);
    REQUIRE(info.protocol_version.major == 0U);
    REQUIRE(info.protocol_version.minor == 0U);
    REQUIRE(info.unique_id[0] == 0U);
    REQUIRE(info.name.count == 0U);
}

}    // namespace
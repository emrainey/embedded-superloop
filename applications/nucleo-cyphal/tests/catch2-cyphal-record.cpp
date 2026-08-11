#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "uavcan/diagnostic/Record_1_0.h"

#include <cstdint>
#include <cstring>

namespace {

void Zero(uint8_t* const data, size_t const size) {
    std::memset(data, 0, size);
}

}    // namespace

TEST_CASE("Record serialize with empty text produces the expected wire layout", "[cyphal][record]") {
    uavcan_diagnostic_Record_1_0 record{};
    uavcan_diagnostic_Record_1_0_initialize_(&record);
    record.timestamp.microsecond = 0U;
    record.severity.value = uavcan_diagnostic_Severity_1_0_INFO;
    record.text.count = 0U;

    uint8_t buffer[uavcan_diagnostic_Record_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_]{};
    size_t size = sizeof(buffer);
    REQUIRE(uavcan_diagnostic_Record_1_0_serialize_(&record, buffer, &size) == NUNAVUT_SUCCESS);
    // Serialized size is trimmed to the actual payload: 7 (timestamp) + 1 (severity) + 1 (text len).
    REQUIRE(size == 9U);

    // timestamp UNKNOWN=0 (56-bit LE zero), severity=INFO(2), text length 0
    uint8_t const expected[] = {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x02U, 0x00U};
    REQUIRE(std::memcmp(buffer, expected, sizeof(expected)) == 0);
}

TEST_CASE("Record serialize places severity and text after the 56-bit timestamp", "[cyphal][record]") {
    uavcan_diagnostic_Record_1_0 record{};
    uavcan_diagnostic_Record_1_0_initialize_(&record);
    record.timestamp.microsecond = 0x01020304050607ULL;
    record.severity.value = uavcan_diagnostic_Severity_1_0_WARNING;
    char const text[] = "hi";
    record.text.count = 2U;
    record.text.elements[0] = static_cast<uint8_t>(text[0]);
    record.text.elements[1] = static_cast<uint8_t>(text[1]);

    uint8_t buffer[uavcan_diagnostic_Record_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_]{};
    size_t size = sizeof(buffer);
    REQUIRE(uavcan_diagnostic_Record_1_0_serialize_(&record, buffer, &size) == NUNAVUT_SUCCESS);

    // timestamp 0x01020304050607 -> LE 07 06 05 04 03 02 01, severity=WARNING(4), len=2, 'h','i'
    uint8_t const expected[] = {0x07U, 0x06U, 0x05U, 0x04U, 0x03U, 0x02U, 0x01U, 0x04U, 0x02U, 'h', 'i'};
    REQUIRE(std::memcmp(buffer, expected, sizeof(expected)) == 0);
}

TEST_CASE("Record deserialize round-trips timestamp, severity and text", "[cyphal][record]") {
    uavcan_diagnostic_Record_1_0 record{};
    uavcan_diagnostic_Record_1_0_initialize_(&record);
    record.timestamp.microsecond = 1234U;
    record.severity.value = uavcan_diagnostic_Severity_1_0_ERROR;
    char const text[] = "nucleo-cyphal";
    record.text.count = sizeof(text) - 1U;
    for (size_t i = 0U; i < record.text.count; ++i) {
        record.text.elements[i] = static_cast<uint8_t>(text[i]);
    }

    uint8_t buffer[uavcan_diagnostic_Record_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_]{};
    size_t size = sizeof(buffer);
    REQUIRE(uavcan_diagnostic_Record_1_0_serialize_(&record, buffer, &size) == NUNAVUT_SUCCESS);

    uavcan_diagnostic_Record_1_0 deserialized{};
    Zero(reinterpret_cast<uint8_t*>(&deserialized), sizeof(deserialized));
    size_t deserialize_size = size;
    REQUIRE(uavcan_diagnostic_Record_1_0_deserialize_(&deserialized, buffer, &deserialize_size) == NUNAVUT_SUCCESS);

    REQUIRE(deserialized.timestamp.microsecond == 1234U);
    REQUIRE(deserialized.severity.value == uavcan_diagnostic_Severity_1_0_ERROR);
    REQUIRE(deserialized.text.count == sizeof(text) - 1U);
    for (size_t i = 0U; i < deserialized.text.count; ++i) {
        REQUIRE(deserialized.text.elements[i] == static_cast<uint8_t>(text[i]));
    }
}

TEST_CASE("Record text is capped at the 112-byte array capacity", "[cyphal][record]") {
    uavcan_diagnostic_Record_1_0 record{};
    uavcan_diagnostic_Record_1_0_initialize_(&record);
    // Saturating member of the struct; the array cannot exceed its capacity.
    REQUIRE(uavcan_diagnostic_Record_1_0_text_ARRAY_CAPACITY_ == 112U);

    record.text.count = 112U;
    for (size_t i = 0U; i < record.text.count; ++i) {
        record.text.elements[i] = static_cast<uint8_t>('A' + (i % 26U));
    }

    uint8_t buffer[uavcan_diagnostic_Record_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_]{};
    size_t size = sizeof(buffer);
    REQUIRE(uavcan_diagnostic_Record_1_0_serialize_(&record, buffer, &size) == NUNAVUT_SUCCESS);

    uavcan_diagnostic_Record_1_0 deserialized{};
    Zero(reinterpret_cast<uint8_t*>(&deserialized), sizeof(deserialized));
    size_t deserialize_size = size;
    REQUIRE(uavcan_diagnostic_Record_1_0_deserialize_(&deserialized, buffer, &deserialize_size) == NUNAVUT_SUCCESS);
    REQUIRE(deserialized.text.count == 112U);
    REQUIRE(deserialized.text.elements[0] == static_cast<uint8_t>('A'));
    REQUIRE(deserialized.text.elements[111] == 'A' + (111U % 26U));
}

TEST_CASE("Record fixed subject ID matches the registry (8184)", "[cyphal][record]") {
    REQUIRE(uavcan_diagnostic_Record_1_0_HAS_FIXED_PORT_ID_ == true);
    REQUIRE(uavcan_diagnostic_Record_1_0_FIXED_PORT_ID_ == 8184U);
}
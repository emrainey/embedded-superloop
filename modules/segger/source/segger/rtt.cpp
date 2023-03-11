#include "segger/rtt.hpp"
#include "thumb.hpp"

namespace rtt {

BufferInfo::BufferInfo(char const* n, size_t s, uint8_t d[]) : name_{n}, data_{d}, size_(s) {
}

size_t BufferInfo::Write(size_t const size, char const string[]) {
    if (data_) {
        size_t space_left = GetCountAvailableSpace();
        size_t bytes_written = 0u;
        size_t offset = write_offset_;
        for (size_t i = 0; i < space_left and i < size; i++) {
            data_[offset] = static_cast<uint8_t>(string[i]);
            offset++;
            bytes_written++;
            if (offset >= size_) {
                offset = 0U;
            }
        }
        thumb::data_synchronization_barrier();
        write_offset_ = offset;
        thumb::data_synchronization_barrier();
        return bytes_written;
    }
    return 0u;
}

size_t BufferInfo::Read(size_t const size, char string[]) {
    if (data_) {
        size_t bytes_left = GetCountAvailableData();
        size_t bytes_read = 0u;
        size_t offset = read_offset_;
        for (size_t i = 0; i < bytes_left and i < size; i++) {
            string[i] = static_cast<char>(data_[offset]);
            offset++;
            bytes_read++;
            if (offset >= size_) {
                offset = 0U;
            }
        }
        thumb::data_synchronization_barrier();
        read_offset_ = offset;
        thumb::data_synchronization_barrier();
        return bytes_read;
    }
    return 0u;
}

bool BufferInfo::IsEmpty(void) const volatile {
    if (data_) {
        return (read_offset_ == write_offset_);
    } else {
        return true;
    }
}

size_t BufferInfo::GetCountAvailableSpace(void) const volatile {
    if (data_) {
        if (read_offset_ > write_offset_) {
            return read_offset_ - write_offset_ - 1;
        } else {
            return size_ - 1U - write_offset_ + read_offset_;
        }
    }
    return 0U;
}

size_t BufferInfo::GetCountAvailableData(void) const volatile {
    if (data_) {
        if (read_offset_ > write_offset_) {
            return size_ - 1U - write_offset_ + read_offset_;
        } else {
            return read_offset_ - write_offset_ - 1;
        }
    }
    return 0U;
}

char const* BufferInfo::GetName(void) const volatile {
    return name_;
}

BufferInfo::Flags::Flags() : mode_{Mode::NoBlockTrim}, check_{0u} {
}

}    // namespace rtt
// int main(void) {

//     alignas(8) uint8_t buffer[1024];
//     alignas(8) uint8_t buffer2[1024];
//     alignas(8) uint8_t keys[16];
//     rtt::ControlBlock cb{};
//     cb.emplace_up("Terminal", 1024, buffer);
//     cb.emplace_up("MicroNet", 1024, buffer2);
//     cb.emplace_down("Terminal", 16, keys);
//     printf("%s %s\r\n", cb.id, cb.GetUp(0).GetName());
//     printf("%s %s\r\n", cb.id, cb.GetUp(1).GetName());
//     printf("%s %s\r\n", cb.id, cb.GetDown(0).GetName());
//     return 0;
// }

//
// Created by SlepiK on 11.03.2024.
//

#ifndef STREAM_V1_TYPES_DATATYPE_DTUINT16_HPP
#define STREAM_V1_TYPES_DATATYPE_DTUINT16_HPP

#include <cstdint>
#include <string_view>

namespace Energyleaf::Stream::V1::Types::Datatype {
    class DtUInt16 {
    public:
        static constexpr std::string_view Identifier{"DtUInt16"};
        [[nodiscard]] virtual uint16_t toUInt16() const = 0;
    };
}

#endif //STREAM_V1_TYPES_DATATYPE_DTUINT16_HPP

#ifndef APALINEA_CORE_TYPE_DATATYPE_DTUINT64_HPP
#define APALINEA_CORE_TYPE_DATATYPE_DTUINT64_HPP

#include <cstdint>
#include <string_view>
#include <cmath>
#include <utility>
#include "Core/Type/Datatype/IDt.hpp"
#include "Core/Type/Datatype/DtFloat.hpp"
#include "Core/Type/Datatype/DtInt.hpp"
#include "Core/Type/Datatype/DtInt8.hpp"
#include "Core/Type/Datatype/DtInt16.hpp"
#include "Core/Type/Datatype/DtInt32.hpp"
#include "Core/Type/Datatype/DtSizeT.hpp"
#include "Core/Type/Datatype/DtUInt8.hpp"
#include "Core/Type/Datatype/DtUInt16.hpp"
#include "Core/Type/Datatype/DtUInt32.hpp"
#include "Core/Type/Datatype/DtInt64.hpp"
#include "Core/Type/Datatype/DtDouble.hpp"
#include "Core/Type/Datatype/DtBool.hpp"

namespace Apalinea::Core::Type::Datatype {
    class DtUInt64 : public IDt {
    public:
        static constexpr DtRegistry::DtRegistryIdentifier IDENTIFIER{"DtUInt64"};

        explicit DtUInt64() : IDt({IDENTIFIER}) {
        }

        explicit DtUInt64(uint64_t data) : IDt({IDENTIFIER}), data(data) {
        }

        [[nodiscard]] DtRegistry::DtRegistryIdentifier getIdentifier() const override {
            return IDENTIFIER;
        }

        DtUInt64& operator=(const DtUInt64 &other) {
            if(&other != this) {
                this->data = other.data;
            }
            return *this;
        }

        [[nodiscard]] std::unique_ptr<Core::Type::Datatype::IDt> copy() const override {
            return std::make_unique<DtUInt64>(*this);
        }

        [[nodiscard]] virtual uint64_t toUInt64() const {
            return this->data;
        }

        bool operator==(const IDt& other) const override {
            if(other.getIdentifier() == this->getIdentifier()) {
                return this->toUInt64() == (static_cast<const DtUInt64&>(other)).toUInt64();
            }
            return false;
        }

        bool operator!=(const IDt& other) const override {
            if(other.getIdentifier() == this->getIdentifier()) {
                return this->toUInt64() != (static_cast<const DtUInt64&>(other)).toUInt64();
            }
            return false;
        }

        bool operator<(const IDt& other) const override {
            if(other.getIdentifier() == this->getIdentifier()) {
                return this->toUInt64() < (static_cast<const DtUInt64&>(other)).toUInt64();
            }
            return false;
        }

        bool operator>(const IDt& other) const override {
            if(other.getIdentifier() == this->getIdentifier()) {
                return this->toUInt64() > (static_cast<const DtUInt64&>(other)).toUInt64();
            }
            return false;
        }

        bool operator<=(const IDt& other) const override {
            if(other.getIdentifier() == this->getIdentifier()) {
                return this->toUInt64() <= (static_cast<const DtUInt64&>(other)).toUInt64();
            }
            return false;
        }

        bool operator>=(const IDt& other) const override {
            if(other.getIdentifier() == this->getIdentifier()) {
                return this->toUInt64() >= (static_cast<const DtUInt64&>(other)).toUInt64();
            }
            return false;
        }

        IDt* operator+(const IDt& other) const override;
        IDt* operator-(const IDt& other) const override;
        IDt* operator*(const IDt& other) const override;
        IDt* operator/(const IDt& other) const override;
        IDt* operator^(const IDt& other) const override;
        IDt* operator%(const IDt& other) const override;

    protected:
        uint64_t data{};
    };
} // Apalinea::Core::Type::Datatype

#endif //APALINEA_CORE_TYPE_DATATYPE_DTUINT64_HPP

#ifndef APALINEA_CORE_TYPE_DATATYPE_DTIMAGE_HPP
#define APALINEA_CORE_TYPE_DATATYPE_DTIMAGE_HPP

#include <utility>

#include "Core/Type/Datatype/IDt.hpp"
#include "Core/Exception/NotImplementedException.hpp"
#include "Core/Type/Image/Image.hpp"

namespace Apalinea::Core::Type::Datatype {
    class DtImage : public IDt {
    public:
        static constexpr DtRegistry::DtRegistryIdentifier IDENTIFIER{"DtImage"};

        DtImage() : IDt(IDENTIFIER,{IDENTIFIER}) {
        }

        explicit DtImage(Image data) : IDt({IDENTIFIER}), data(std::move(data)) {
        }

        [[nodiscard]] DtRegistry::DtRegistryIdentifier getIdentifier() const override {
            return IDENTIFIER;
        }

        DtImage& operator=(const DtImage &other) {
            if(&other != this) {
                this->data = other.data;
            }
            return *this;
        }

        [[nodiscard]] std::unique_ptr<Core::Type::Datatype::IDt> copy() const override {
            return std::make_unique<DtImage>(*this);
        }

        [[nodiscard]] virtual Image toImage() const {
            return this->data;
        }

        bool operator==(const IDt& other) const override {
            throw Exception::NotImplementedException("Method not supported here!");
        }

        bool operator!=(const IDt& other) const override {
            throw Exception::NotImplementedException("Method not supported here!");
        }

        bool operator<(const IDt& other) const override {
            throw Exception::NotImplementedException("Method not supported here!");
        }

        bool operator>(const IDt& other) const override {
            throw Exception::NotImplementedException("Method not supported here!");
        }

        bool operator<=(const IDt& other) const override {
            throw Exception::NotImplementedException("Method not supported here!");
        }

        bool operator>=(const IDt& other) const override {
            throw Exception::NotImplementedException("Method not supported here!");
        }

        IDt* operator+(const IDt& other) const override;
        IDt* operator-(const IDt& other) const override;
        IDt* operator*(const IDt& other) const override;
        IDt* operator/(const IDt& other) const override;
        IDt* operator^(const IDt& other) const override;
        IDt* operator%(const IDt& other) const override;

    protected:
        Image data{};
    };
} // Apalinea::Core::Type::Datatype


#endif //APALINEA_CORE_TYPE_DATATYPE_DTIMAGE_HPP

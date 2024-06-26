#ifndef APALINEA_CORE_TYPE_IMAGE_HPP
#define APALINEA_CORE_TYPE_IMAGE_HPP

#include <cstdint>
#include <utility>
#include "Core/Constants/Settings.hpp"
#include "Core/Type/Image/ImageFormat.hpp"

namespace Apalinea::Core::Type {
    class Image {
    public:
        Image()
                : vWidth(0), vHeight(0), vBytesPerPixel(0), vFormat(ImageFormat::FB_RGB888), vData(nullptr){
        };

        [[maybe_unused]] Image(int width, int height, int bytesPerPixel, ImageFormat format, std::uint8_t* data)
                : vWidth(width), vHeight(height), vBytesPerPixel(bytesPerPixel), vFormat(format) {
            size_t arraySize = this->vWidth * this->vHeight * this->vBytesPerPixel;
            this->vData = Core::Constants::Settings::uint8_tCreator.getCreator().create(arraySize);
            if (!vData) {
                throw std::bad_alloc();
            }
            std::copy(data, data + arraySize, vData);
        }

        Image(int width, int height, int bytesPerPixel, ImageFormat format)
                : vWidth(width), vHeight(height), vBytesPerPixel(bytesPerPixel), vFormat(format) {
            size_t arraySize = this->vWidth * this->vHeight * this->vBytesPerPixel;
            this->vData = Core::Constants::Settings::uint8_tCreator.getCreator().create(arraySize);
            if (!vData) {
                throw std::bad_alloc();
            }
        }

        Image(Image &&other)
        noexcept: vWidth(other.vWidth), vHeight(other.vHeight), vBytesPerPixel(other.vBytesPerPixel), vFormat(other.vFormat), vData(other.vData){
            other.vWidth = 0;
            other.vHeight = 0;
            other.vBytesPerPixel = 0;
            other.vFormat = ImageFormat::FB_RGB888;
            other.vData = nullptr;
        }

        Image(const Image& other) {
            this->vWidth = other.vWidth;
            this->vHeight = other.vHeight;
            this->vBytesPerPixel = other.vBytesPerPixel;
            this->vFormat = other.vFormat;
            size_t arraySize = this->vWidth * this->vHeight * this->vBytesPerPixel;
            this->vData = Core::Constants::Settings::uint8_tCreator.getCreator().create(arraySize);
            if (!vData) {
                throw std::bad_alloc();
            }
            std::copy(other.vData, other.vData + arraySize, vData);
        }

        Image& operator=(Image&& other) noexcept {
            if (this != &other) {
                Core::Constants::Settings::uint8_tCreator.getCreator().destroy(vData,Extras::Memory::CreatorArgument::MULTI);
                this->vWidth = other.vWidth;
                this->vHeight = other.vHeight;
                this->vBytesPerPixel = other.vBytesPerPixel;
                this->vFormat = other.vFormat;
                this->vData = other.vData;
                other.vWidth = 0;
                other.vHeight = 0;
                other.vBytesPerPixel = 0;
                other.vFormat = ImageFormat::FB_RGB888;
                other.vData = nullptr;
            }
            return *this;
        }

        Image& operator=(const Image& other) {
            if(this == &other) return *this;
            this->vWidth = other.vWidth;
            this->vHeight = other.vHeight;
            this->vBytesPerPixel = other.vBytesPerPixel;
            this->vFormat = other.vFormat;
            size_t arraySize = this->vWidth * this->vHeight * this->vBytesPerPixel;
            this->vData = Core::Constants::Settings::uint8_tCreator.getCreator().create(arraySize);
            if (!vData) {
                throw std::bad_alloc();
            }
            std::copy(other.vData, other.vData + arraySize, vData);
            return *this;
        }

        virtual ~Image() {
            if(this->vData) {
                Core::Constants::Settings::uint8_tCreator.getCreator().destroy(vData,Extras::Memory::CreatorArgument::MULTI);
                this->vData = nullptr;
            }
        }

        [[nodiscard]] int getWidth() const {
            return this->vWidth;
        }

        [[nodiscard]] int getHeight() const {
            return this->vHeight;
        }

        [[nodiscard]] int getBytesPerPixel() const {
            return this->vBytesPerPixel;
        }

        [[nodiscard]] ImageFormat getFormat() const {
            return this->vFormat;
        }

        std::uint8_t* getData() {
            return this->vData;
        }

        [[maybe_unused]] void setWidth(int width) {
            this->vWidth = width;
        }

        [[maybe_unused]] void setHeight(int height) {
            this->vHeight = height;
        }

        [[maybe_unused]] void setBytesPerPixel(int bytesPerPixel) {
            this->vBytesPerPixel = bytesPerPixel;
        }

        [[maybe_unused]] void setFormat(ImageFormat format) {
            this->vFormat = format;
        }

        [[maybe_unused]] void initData() {
            if(this->vData != nullptr) {
                Core::Constants::Settings::uint8_tCreator.getCreator().destroy(vData,Extras::Memory::CreatorArgument::MULTI);
            }
            this->vData = Core::Constants::Settings::uint8_tCreator.getCreator().create(this->vWidth * this->vHeight * this->vBytesPerPixel);
            if (!vData) {
                throw std::bad_alloc();
            }
        }

    private:
        int vWidth;
        int vHeight;
        int vBytesPerPixel;
        ImageFormat vFormat;
        std::uint8_t* vData;
    };
} // Apalinea::Core::Type

#endif //APALINEA_CORE_TYPE_IMAGE_HPP

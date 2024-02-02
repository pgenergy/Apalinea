//
// Created by SlepiK on 01.02.24.
//

#ifndef ENERGYLEAF_STREAM_V1_EXPTRAS_VISION_ABSTRACTCAMERA_HPP
#define ENERGYLEAF_STREAM_V1_EXPTRAS_VISION_ABSTRACTCAMERA_HPP

#include <stdexcept>
#include "Types/Image/Image.hpp"

namespace Energyleaf::Stream::V1::Extras::Vision {
    template<typename Config>
    class AbstractCamera {
    public:
        AbstractCamera() : vStarted(false) {
        };

        virtual ~AbstractCamera() = default;

        void start() {
            if (this->vStarted) {
                throw std::runtime_error("AbstractCamera is already started!");
            }

            this->internalStart();

            this->vStarted = true;
        };

        void stop() {
            if (!this->vStarted) {
                throw std::runtime_error("AbstractCamera is not started!");
            }

            this->internalStop();

            this->vStarted = false;
        }

        [[nodiscard]] bool isStarted() const {
            return this->vStarted;
        }

        Energyleaf::Stream::V1::Types::Image getImage() {
            if (!this->vStarted) {
                throw std::runtime_error("AbstractCamera is not started!");
            }

            return this->getInternalImage();
        }

        virtual const Config& getConfig() = 0;

        virtual void setConfig(Config&& config) = 0;

        virtual void setConfig(Config& config) = 0;

    private:
    protected:
        bool vStarted;
        virtual void internalStart() = 0;
        virtual void internalStop() = 0;
        virtual Energyleaf::Stream::V1::Types::Image getInternalImage() = 0;
    };
}

#endif //ENERGYLEAF_STREAM_V1_EXPTRAS_VISION_ABSTRACTCAMERA_HPP

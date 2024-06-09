//
// Created by SlepiK on 27.01.2024.
//

#ifndef STREAM_V1_OPERATOR_SOURCEOPERATOR_HPP
#define STREAM_V1_OPERATOR_SOURCEOPERATOR_HPP

#include "Operator/AbstractOperator.hpp"

namespace Energyleaf::Stream::V1::Operator {

    class AbstractSourceOperator : public AbstractOperator {
    public:
        AbstractSourceOperator() = default;

        ~AbstractSourceOperator() override = default;

        [[nodiscard]] OperatorType getOperatorType() const override {
            return OperatorType::SOURCE;
        }

        [[nodiscard]] OperatorMode getOperatorMode() const override {
            return OperatorMode::TASK;
        }

        virtual void process(Tuple::Tuple& outputTuple) final {
            if (this->vProcessing) throw std::runtime_error("Operator is already processing!");
            if (this->vProcessed) this->vProcessed = false;
            if (!this->vProcessing) this->vProcessing = true;

            this->work(outputTuple);

            this->vProcessing = false;
            this->vProcessed = true;
        }

    private:
    protected:
        virtual void work(Tuple::Tuple& outputTuple) = 0;
    };

} // Stream::V1::Operator

#endif //STREAM_V1_OPERATOR_SOURCEOPERATOR_HPP

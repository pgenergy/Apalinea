//
// Created by SlepiK on 12.03.2024.
//

#ifndef STREAM_V1_EXPRESSION_DATATYPE_DTINTEXPRESSION_HPP
#define STREAM_V1_EXPRESSION_DATATYPE_DTINTEXPRESSION_HPP

#include "Core/Tuple/Tuple.hpp"
#include "Core/Type/Datatype/DtInt.hpp"
#include "Expression/IExpression.hpp"

namespace Apalinea::Expression::DataType {
    class DtIntExpression : public IExpression {
    public:
        static constexpr std::string_view IDENTIFIER = Core::Types::Datatype::DtInt::IDENTIFIER;

        explicit DtIntExpression(std::string&& entry) : IExpression({IDENTIFIER}), entry(std::move(entry)), load(true) {
        }

        explicit DtIntExpression(int&& value) : IExpression({IDENTIFIER}), load(false), data(std::move(value)) {
        }

        ~DtIntExpression() override = default;

        [[nodiscard]] bool isComposite() const override {
            return false;
        }

        void setTuple(Core::Tuple::Tuple& tuple) override {
            if(load) {
                this->tuple = tuple;
            }
        }

        [[nodiscard]] const Core::Types::Datatype::IDt& getData() const override {
            return this->data;
        }

        void execute() override {
            if(load) {
                if (this->tuple.getItems().empty()) {
                    throw std::runtime_error("Tuple is empty!");
                }

                if (this->tuple.containsItem(this->entry)) {
                    this->data = this->tuple.getEntry(this->entry).get<Core::Types::Datatype::DtInt>();
                } else {
                    throw std::runtime_error("Entry was not found in the given tuple!");
                }
            }
        }

        [[nodiscard]] std::string_view getIdentifier() const override {
            return IDENTIFIER;
        }
    private:
        Core::Tuple::Tuple tuple;
        std::string entry;
        Core::Types::Datatype::DtInt data;
        bool load;
    };
}

#endif //STREAM_V1_EXPRESSION_DATATYPE_DTINTEXPRESSION_HPP

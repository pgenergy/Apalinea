//
// Created by SlepiK on 27.01.2024.
//

#include "Core/Operator/SinkOperator/CoutSinkOperator/CoutSinkOperator.hpp"
#include "Core/Operator/SourceOperator/StringDemoSourceOperator/StringDemoSourceOperator.hpp"

#include "Core/Plan/Plan.hpp"

int main(int argc, char *argv[])
{
    Stream::V1::Core::Plan::Plan plan;
    auto sourcelink = plan.createLink(Stream::V1::Link::make_SourceLinkUPtr<Stream::V1::Core::Operator::SourceOperator::StringDemoSourceOperator>());
    auto sinklink = plan.createLink(Stream::V1::Link::make_SinkLinkUPtr<Stream::V1::Core::Operator::SinkOperator::CoutSinkOperator>());
    plan.connect(sourcelink,sinklink);
    plan.process();
}
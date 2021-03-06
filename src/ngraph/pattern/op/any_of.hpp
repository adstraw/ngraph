//*****************************************************************************
// Copyright 2017-2020 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF AnyOf KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************

#pragma once

#include "ngraph/node.hpp"
#include "ngraph/pattern/op/pattern.hpp"

namespace ngraph
{
    namespace pattern
    {
        namespace op
        {
            class AnyOf;
        }
    }
}

/// The graph value is added to the matched values list. If the predicate is true for
/// the
/// graph node, a submatch is performed on the input of AnyOf and each input of the
/// graph node. The first match that succeeds results in a successful match. Otherwise
/// the match fails.
///
/// AnyOf may be given a type and shape for use in strict mode.
class NGRAPH_API ngraph::pattern::op::AnyOf : public Pattern
{
public:
    static constexpr NodeTypeInfo type_info{"patternAnyOf", 0};
    const NodeTypeInfo& get_type_info() const override;
    /// \brief creates a AnyOf node containing a sub-pattern described by \sa type and
    ///        \sa shape.
    AnyOf(const element::Type& type,
          const PartialShape& s,
          ValuePredicate pred,
          const OutputVector& wrapped_values)
        : Pattern(wrapped_values, pred)
    {
        if (wrapped_values.size() != 1)
        {
            throw ngraph_error("AnyOf expects exactly one argument");
        }
        set_output_type(0, type, s);
    }

    /// \brief creates a AnyOf node containing a sub-pattern described by the type and
    ///        shape of \sa node.
    AnyOf(const Output<Node>& node, ValuePredicate pred, const OutputVector& wrapped_values)
        : AnyOf(node.get_element_type(), node.get_partial_shape(), pred, wrapped_values)
    {
    }
    bool match_value(Matcher* matcher,
                     const Output<Node>& pattern_value,
                     const Output<Node>& graph_value) override;
};

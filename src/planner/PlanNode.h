/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#ifndef PLANNER_PLANNODE_H_
#define PLANNER_PLANNODE_H_

#include "base/Base.h"
#include "filter/Expressions.h"
#include "planner/IdGenerator.h"

namespace nebula {
namespace graph {

class ExecutionPlan;

/**
 * PlanNode is an abstraction of nodes in an execution plan which
 * is a kind of directed cyclic graph.
 */
class PlanNode {
public:
    enum class Kind : uint8_t {
        kUnknown = 0,
        kStart,
        kEnd,
        kGetNeighbors,
        kGetVertices,
        kGetEdges,
        kReadIndex,
        kFilter,
        kUnion,
        kIntersect,
        kMinus,
        kProject,
        kSort,
        kLimit,
        kAggregate,
        kSelector,
        kLoop,
        kRegisterSpaceToSession,
        kDedup,
    };

    PlanNode() = default;

    virtual ~PlanNode() = default;

    /**
     * To explain how a query would be executed
     */
    virtual std::string explain() const = 0;

    Kind kind() const {
        return kind_;
    }

    int64_t id() const {
        return id_;
    }

    const ExecutionPlan* plan() const {
        return plan_;
    }

    void setId(int64_t id) {
        id_ = id;
    }

    void setPlan(ExecutionPlan* plan) {
        plan_ = plan;
    }

protected:
    Kind                                     kind_{Kind::kUnknown};
    int64_t                                  id_{IdGenerator::INVALID_ID};
    ExecutionPlan*                           plan_;
    using VariableName = std::string;
    std::unordered_set<VariableName>         availableVars_;
};
}  // namespace graph
}  // namespace nebula
#endif  // PLANNER_PLANNODE_H_

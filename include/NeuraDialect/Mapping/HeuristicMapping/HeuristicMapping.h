#ifndef NEURA_BACKTRACK_MAPPING_H
#define NEURA_BACKTRACK_MAPPING_H

#include "NeuraDialect/Mapping/MappingState.h"
#include "NeuraDialect/Mapping/MappingStrategy.h"
#include <climits>
#include <map>
#include <set>

namespace mlir {
namespace neura {
class HeuristicMapping : public MappingStrategy {
public:
  HeuristicMapping(int max_location_to_try = 5, int max_backtrack_depth = 3)
      : max_location_to_try(max_location_to_try), max_backtrack_depth(3) {}
  bool map(std::vector<Operation *> &sorted_ops,
           const Architecture &architecture,
           MappingState &mapping_state) override;
  std::string getName() const override {
    if (max_backtrack_depth == 1 && max_location_to_try == INT_MAX) {
      return "greedy";
    } else if (max_backtrack_depth == INT_MAX &&
               max_location_to_try == INT_MAX) {
      return "exhaustive";
    } else {
      return "heuristic";
    }
  }

private:
  bool mapWithBacktrack(std::vector<Operation *> &sorted_ops,
                        const Architecture &architecture,
                        MappingState &mapping_state, size_t current_index,
                        int backtrack_depth);

  // Configuration parameters.
  int max_location_to_try; // Maximum number of locations to try for
                           // each op
  int max_backtrack_depth; // Maximum depth for backtracking
};
} // namespace neura
} // namespace mlir

namespace mlir {
namespace neura {
class MappingStateSnapshot {
public:
  MappingStateSnapshot(const MappingState &mapping_state);

  void restore(MappingState &mapping_state);

  std::map<Operation *, std::vector<MappingLoc>> getOpToLocs() {
    return this->op_to_locs;
  }

private:
  std::set<MappingLoc> occupied_locs;
  std::map<MappingLoc, Operation *> loc_to_op;
  std::map<Operation *, std::vector<MappingLoc>> op_to_locs;
};
} // namespace neura
} // namespace mlir

#endif // NEURA_BACKTRACK_MAPPING_H
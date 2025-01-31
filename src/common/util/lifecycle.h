/** Copyright 2020-2022 Alibaba Group Holding Limited.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef SRC_COMMON_UTIL_LIFECYCLE_H_
#define SRC_COMMON_UTIL_LIFECYCLE_H_

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common/memory/payload.h"
#include "common/util/boost.h"
#include "common/util/status.h"
#include "common/util/uuid.h"

namespace vineyard {

namespace detail {
/**
 * @brief LifeCycleTracker is a CRTP class provides the lifecycle management for
 * its derived classes. It requires the derived class to implement the:
 *  - `OnRelease(ID)` method to describe what will happens when `ref_count`
 * reaches zero.
 *  - `OnDelete(ID)` method to describe what will happens when `ref_count`
 * reaches zero and the object is marked as to be deleted.
 *  - `FetchAndModify(ID, int, int)` method to fetch the current `ref_count` and
 * modify it by the given value.
 */
template <typename ID, typename P, typename Der>
class LifeCycleTracker {
 public:
  LifeCycleTracker() {}

  Status IncreaseReferenceCount(ID const& id) {
    int64_t ref_cnt = 0;
    return FetchAndModify(id, ref_cnt, 1);
  }

  Status DecreaseReferenceCount(ID const& id) {
    int64_t ref_cnt = 0;
    RETURN_ON_ERROR(FetchAndModify(id, ref_cnt, -1));

    if (ref_cnt > 0) {
      return Status::OK();
    }

    // If reaches zero, trigger `OnRelease` behavior.
    VINEYARD_CHECK_OK(Self().OnRelease(id));

    // If the object is marked as to be deleted, trigger `OnDelete` behavior.
    if (pending_to_delete_.count(id) > 0) {
      pending_to_delete_.erase(id);
      VINEYARD_CHECK_OK(Self().OnDelete(id));
    }
    return Status::OK();
  }

  /**
   * @brief: Defer deletion until reference count goes to zero.
   */
  Status PreDelete(ID const& id) {
    int64_t ref_cnt = 0;
    RETURN_ON_ERROR(FetchAndModify(id, ref_cnt, 0));
    if (ref_cnt != 0) {
      pending_to_delete_.emplace(id);
    } else {
      VINEYARD_CHECK_OK(Self().OnDelete(id));
    }
    return Status::OK();
  }

  void ClearCache() {
    for (auto const& id : pending_to_delete_) {
      VINEYARD_CHECK_OK(Self().OnDelete(id));
    }
    pending_to_delete_.clear();
  }

 protected:
  Status FetchAndModify(ID const& id, int64_t& ref_cnt, int64_t change) {
    return Self().FetchAndModify(id, ref_cnt, change);
  }

  bool IsInDeletion(ID const& id) {
    return pending_to_delete_.find(id) != pending_to_delete_.end();
  }

 private:
  inline Der& Self() { return static_cast<Der&>(*this); }
  /// Cache the objects that client wants to delete but `ref_count > 0`
  /// Race condition should be settled by Der.
  std::unordered_set<ID> pending_to_delete_;
};

}  // namespace detail

}  // namespace vineyard
#endif  // SRC_COMMON_UTIL_LIFECYCLE_H_

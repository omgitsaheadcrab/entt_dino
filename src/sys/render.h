/**
 * @file      render.h
 * @brief     Render system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-13
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_RENDER_H_
#define ENTT_DINO_SRC_SYS_RENDER_H_

#include "core/base_system.h"
#include "core/window.h"

#include <cstdint>

namespace systems {

class Render : public omg::BaseSystem {
 public:
  Render() = delete;
  explicit Render(omg::Window* window);
  ~Render() = default;

  void Update(const double alpha) override;

 private:
  omg::Window* window_;
  uint32_t frame_count_ = 0;
  double fps_interval_ = 0.0;

};

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_RENDER_H_

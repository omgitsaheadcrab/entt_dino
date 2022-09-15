/**
 * @file      render.h
 * @brief     Render system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-13
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_RENDER_H_
#define ENTT_DINO_SRC_SYS_RENDER_H_

#include <cstdint>

#include "core/base_system.h"
#include "core/window.h"

namespace systems {

class Render : public omg::BaseSystem {
 public:
  Render() = delete;
  explicit Render(omg::Window* window);
  virtual ~Render() = default;

  void Update(const double alpha) override;

 protected:
  void OnInit() override;

 private:
  omg::Window* window_;
};

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_RENDER_H_

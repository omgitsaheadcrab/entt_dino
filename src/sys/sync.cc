/**
 * @file      sync.cc
 * @brief     Synchronize graphics with physics
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#include "sys/sync.h"

#include "comp/graphics/transform.h"
#include "comp/physics/transform.h"

void systems::Sync::Update(const double dt) {
  const auto kView = registry_->view<components::graphics::Transform,
                                     components::physics::Transform>();
  kView.each([&](auto& gfx, const auto& kPhysx) {
    gfx.position.x = kPhysx.position.x;
    gfx.position.y = kPhysx.position.y;
    gfx.position.w = kPhysx.position.w;
    gfx.position.h = kPhysx.position.h;
  });
}

/**
 * @file      running.cc
 * @brief     Running scene
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-25
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "scenes/running.h"

#include "core/base_scene.h"
#include "ctx/game_states.h"
#include "ctx/graphics.h"

scenes::Running::Running() : omg::BaseScene("running") {}

void scenes::Running::Init() { entity_manager_.Init(game_); }

void scenes::Running::HandleEvents() {}

void scenes::Running::Update(const double dt) {}

void scenes::Running::Render(const double alpha) {}

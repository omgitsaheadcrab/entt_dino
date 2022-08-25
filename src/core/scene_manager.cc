/**
 * @file      scene_manager.cc
 * @brief     Scene manager
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-25
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "core/scene_manager.h"
#include "core/base_scene.h"

#include "core/game.h"

omg::SceneManager::SceneManager(omg::Game* game) : game_ {game} {}

omg::BaseScene* omg::SceneManager::current_scene() const { return current_scene_; }

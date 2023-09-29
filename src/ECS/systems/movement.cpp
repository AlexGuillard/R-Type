/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** movement
*/

#include <raylib.h>

#include "ECS/Systems/movement.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Containers/zipper/Zipper.hpp"

namespace ECS::Systems {

    void movement(
        [[maybe_unused]] Containers::Registry &registry,
        Containers::SparseArray<Components::PositionComponent> &positions,
        Containers::SparseArray<Components::VelocityComponent> &velocities)
    {
        for (auto &&[position, velocity] : Containers::Zipper(positions, velocities)) {
            position->x += velocity->x * GetFrameTime();
            position->y += velocity->y * GetFrameTime();
        }
    }

}; // namespace ECS::Systems

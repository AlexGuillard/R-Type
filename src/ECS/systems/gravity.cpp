/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** gravity
*/

#include <raylib.h>
#include "ECS/Systems/gravity.hpp"
#include "ECS/Components/GravityComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Containers/zipper/Zipper.hpp"

namespace ECS::Systems {

    void gravity(
        [[maybe_unused]] Containers::Registry &registry,
        ECS::Containers::SparseArray<ECS::Components::VelocityComponent> &velocities, Containers::SparseArray<Components::GravityComponent> &gravity)
    {
        for (auto &&[velocity, gravity] : ECS::Containers::Zipper(velocities, gravity)) {
            velocity->y += gravity->gravity;
        }
    }

}; // namespace ECS::systems

/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** sinMovement
*/

#include <cmath>

#include "GameEngine/GameEngine.hpp"
#include "ECS/Systems/sinMovement.hpp"
#include "ECS/Components/SinMovementComponent.hpp"
#include "ECS/Containers/zipper/Zipper.hpp"

namespace ECS::Systems {

    void sinMovement(
        Containers::Registry &registry,
        Containers::SparseArray<Components::SinMovementComponent> &sinMovements,
        Containers::SparseArray<Components::VelocityComponent> &velocities)
    {
        for (auto &&[sinMovement, velocity] : Containers::Zipper(sinMovements, velocities)) {
            sinMovement->t += sinMovement->speed * GameEngine::GameEngine::getDeltaTime();
            velocity->x = sinMovement->speed;
            velocity->y =
                sinMovement->amplitude *
                cos(sinMovement->frequency * (sinMovement->t + sinMovement->horizontalOffset));
        }
    }

}; // namespace ECS::Systems

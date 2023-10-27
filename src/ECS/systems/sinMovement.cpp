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
        Containers::SparseArray<Components::PositionComponent> &positions)
    {
        for (auto &&[sinMovement, position] : Containers::Zipper(sinMovements, positions)) {
            sinMovement->t += sinMovement->speed * GameEngine::GameEngine::getDeltaTime();
            position->x = sinMovement->horizontalOffset + sinMovement->t;
            position->y =
                sinMovement->amplitude *
                sin(sinMovement->frequency * (sinMovement->t + sinMovement->horizontalOffset))
                + sinMovement->verticalOffset;
        }
    }

}; // namespace ECS::Systems

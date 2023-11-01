/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** bossIntro
*/

#include "ECS/Systems/bossIntro.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"
#include "GameEngine/GameEngine.hpp"


void ECS::Systems::bossIntro(
    Containers::Registry &registry,
    Containers::SparseArray<Components::PositionComponent> &positions,
    Containers::SparseArray<Components::HitBoxComponent> &hitBoxes,
    Containers::SparseArray<Components::BossIntroComponent> &bossIntros)
{
    std::vector<ECS::Entity> toRemoveIntros;

    for (auto &&[eId, bossIntro, position, hitBox]
        : Containers::IndexedZipper(bossIntros, positions, hitBoxes)
        ) {
        if (bossIntro->_timer == -1) {
            bossIntro->_timer = bossIntro->length;
            bossIntro->_startX = position->x;
        }
        position->x = bossIntro->_startX - (1 - bossIntro->_timer / bossIntro->length) * hitBox->width;
        bossIntro->_timer -= GameEngine::GameEngine::getDeltaTime();
        if (bossIntro->_timer <= 0) {
            position->x = bossIntro->_startX - hitBox->width;
            toRemoveIntros.push_back(registry.entityFromIndex(eId));
        }
    }
    for (auto &&e : toRemoveIntros) {
        registry.removeComponent<Components::BossIntroComponent>(e);
    }
}

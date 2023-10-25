/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** shooting
*/

#include <string>
#include <cstring>
#include <sys/types.h>
#include <cstdint>

#include <raylib.h>

#include "ECS/Systems/shooting.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/VelocityComponent.hpp"
#include "ECS/Components/DamageComponent.hpp"
#include "ECS/Components/HPComponent.hpp"
#include "ECS/Components/DrawableComponent.hpp"
#include "ECS/Containers/zipper/IndexedZipper.hpp"
#include "Assets/generatedAssets.hpp"

namespace ECS::Systems {

    /**
     * @brief Get the Drawable For Missile object
     * @return Components::DrawableComponent
     */
    static Components::DrawableComponent getDrawableForMissile()
    {
        const uint8_t nbFrameInSpriteSheet = 6;
        const Utils::Vector2 missileFramePos(2, 0);
        Components::DrawableComponent drawable = {
                Assets::AssetsIndex::MISSILE_PNG,
                Utils::Vector2(nbFrameInSpriteSheet, 1), // frameRatio
                missileFramePos, // start
                missileFramePos // end
        };
        return drawable;
    }

    /**
     * @brief Spawns missiles from missile requests
     * @param registry Registry into which the missiles will be spawned
     * @param missileRequests SparseArray of missile requests
     */
    static void shootMissiles(
        Containers::Registry &registry,
        Containers::SparseArray<Components::MissileComponent> &missileRequests)
    {
        for (auto &&[entityId, missileRequest] : Containers::IndexedZipper(missileRequests)) {
            auto missileEntity = registry.spawnEntity();

            registry.emplaceComponent<Components::PositionComponent>(
                missileEntity,
                missileRequest->x,
                missileRequest->y
            );
            registry.emplaceComponent<Components::VelocityComponent>(
                missileEntity,
                Components::missileSpeed,
                0
            );
            registry.emplaceComponent<Components::DamageComponent>(
                missileEntity,
                missileRequest->damage
            );
            registry.emplaceComponent<Components::HPComponent>(
                missileEntity,
                0 // Die on collision
            );
            registry.emplaceComponent<Components::TeamComponent>(
                missileEntity,
                missileRequest->team
            );
            Components::DrawableComponent drawable = getDrawableForMissile();
            registry.addComponent<Components::DrawableComponent>(
                missileEntity, std::move(drawable)
            );
            auto entity = registry.entityFromIndex(entityId);
            registry.removeComponent<Components::MissileComponent>(entity);
        }
    }

    /**
     * @brief Get the Drawable For Wave Beam object
     * @param strength Number between 1 and 5 that represents the strength of the wave beam
     * @return Components::DrawableComponent
     */
    static Components::DrawableComponent getDrawableForWaveBeam(uint8_t strength)
    {
        const uint8_t nbFrameInSpriteSheet = 2;
        const Utils::Vector2 waveBeamFrameStart(0, 0);
        const Utils::Vector2 waveBeamFrameEnd(1, 0);
        const Assets::AssetsIndex waveBeams[] = { Assets::AssetsIndex::WAVEBEAM_OUT1_PNG, Assets::AssetsIndex::WAVEBEAM_OUT2_PNG, Assets::AssetsIndex::WAVEBEAM_OUT3_PNG, Assets::AssetsIndex::WAVEBEAM_OUT4_PNG, Assets::AssetsIndex::WAVEBEAM_OUT5_PNG };
        Components::DrawableComponent drawable = {
                .spriteSheetIndex = waveBeams[strength - 1],
                .frameRatio = Utils::Vector2(nbFrameInSpriteSheet, 1),
                .start = waveBeamFrameStart,
                .end = waveBeamFrameEnd
        };
        return drawable;
    }

    /**
     * @brief Spawns wave beams from wave beam requests
     * @param registry Registry into which the wave beams will be spawned
     * @param waveBeamRequests SparseArray of wave beam requests
     */
    static void shootWaveBeams(
        Containers::Registry &registry,
        Containers::SparseArray<Components::WaveBeamComponent> &waveBeamRequests)
    {
        for (auto &&[entityId, waveBeamRequests] : Containers::IndexedZipper(waveBeamRequests)) {
            auto waveBeamEntity = registry.spawnEntity();

            registry.emplaceComponent<Components::PositionComponent>(
                waveBeamEntity,
                waveBeamRequests->x,
                waveBeamRequests->y
            );
            registry.emplaceComponent<Components::VelocityComponent>(
                waveBeamEntity,
                Components::waveBeamSpeed,
                0
            );
            registry.emplaceComponent<Components::DamageComponent>(
                waveBeamEntity,
                waveBeamRequests->damage
            );
            registry.emplaceComponent<Components::TeamComponent>(
                waveBeamEntity,
                waveBeamRequests->team
            );
            Components::DrawableComponent drawable = getDrawableForWaveBeam(waveBeamRequests->strength);
            registry.addComponent<Components::DrawableComponent>(
                waveBeamEntity, std::move(drawable)
            );
            auto entity = registry.entityFromIndex(entityId);
            registry.removeComponent<Components::WaveBeamComponent>(entity);
        }
    }

    void shooting(
        Containers::Registry &registry,
        Containers::SparseArray<Components::MissileComponent> &missileRequests,
        Containers::SparseArray<Components::WaveBeamComponent> &waveBeamRequests
    )
    {
        shootMissiles(registry, missileRequests);
        shootWaveBeams(registry, waveBeamRequests);
    }
}; // namespace ECS::Systems

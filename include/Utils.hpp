/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Utils
*/

#pragma once

namespace Utils {
    // Vector2, 2 components
    typedef struct Vector2 {
        float x;                // Vector x component
        float y;                // Vector y component
    } Vector2;

    // Vector3, 3 components
    typedef struct Vector3 {
        float x;                // Vector x component
        float y;                // Vector y component
        float z;                // Vector z component
    } Vector3;

    // Vector4, 4 components
    typedef struct Vector4 {
        float x;                // Vector x component
        float y;                // Vector y component
        float z;                // Vector z component
        float w;                // Vector w component
    } Vector4;
} // namespace Utils

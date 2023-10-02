/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** Zipper
*/

#include <gtest/gtest.h>

#include "ECS/Containers/zipper/Zipper.hpp"

using namespace ECS::Containers;

typedef struct {
	int x;
	int y;
} PositionComponent;

TEST(Zipper, ZippingEmptyArray)
{
	SparseArray<PositionComponent> a;
	SparseArray<PositionComponent> b;
	int i = 0;

	for (auto &&[valueA, valueB] : Zipper(a, b)) {
		FAIL();
	}
}

TEST(Zipper, ZippingArrayWithSizeOne)
{
	SparseArray<PositionComponent> a(10);
	SparseArray<PositionComponent> b(10);
	int i = 0;

	for (int i = 0; i < 10; i++) {
		a.insertAt(i, { 0, i });
		b.insertAt(i, { i, 0 });
	}
	for (auto &&[valueA, valueB] : Zipper(a, b)) {
		valueA->x = i * 2;
		valueA->y = i * 2;
		valueB->x = i * 2;
		valueB->y = i * 2;
		i++;
	}
	for (i = 0; i < a.size(); i++) {
		EXPECT_EQ(a[i]->x, i * 2);
		EXPECT_EQ(a[i]->y, i * 2);
		EXPECT_EQ(b[i]->x, i * 2);
		EXPECT_EQ(b[i]->y, i * 2);
	}
}

TEST(Zipper, ZipIgnoresHoles)
{
	SparseArray<PositionComponent> a(10);
	SparseArray<PositionComponent> b(10);
	int i = 0;

	for (int i = 0; i < 10; i++) {
		a.insertAt(i, { 0, i });
		b.insertAt(i, { i, 0 });
	}
	a.erase(5);
	b.erase(5);
	a.erase(7);
	b.erase(3);
	i = 0;
	for (auto &&[valueA, valueB] : Zipper(a, b)) {
		valueA->x = i * 2;
		valueA->y = i * 2;
		valueB->x = i * 2;
		valueB->y = i * 2;
		i++;
	}
	ASSERT_FALSE(a[5].has_value());
	ASSERT_FALSE(b[5].has_value());
	ASSERT_FALSE(a[7].has_value());
	ASSERT_EQ(b[7]->x, 7);
	ASSERT_EQ(b[7]->y, 0);
	ASSERT_EQ(a[3]->x, 0);
	ASSERT_EQ(a[3]->y, 3);
	ASSERT_FALSE(b[3].has_value());
	ASSERT_EQ(a[8]->x, 10);
	ASSERT_EQ(a[8]->y, 10);
	ASSERT_EQ(b[8]->x, 10);
	ASSERT_EQ(b[8]->y, 10);
}

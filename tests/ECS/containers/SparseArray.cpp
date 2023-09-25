/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** SparseArray
*/

#include <gtest/gtest.h>
#include <stdexcept>

#include "ECS/containers/SparseArray.hpp"
#include "Errors/ValueNotFound.hpp"

using namespace ECS::containers;

TEST(SparseArray, increasingInsertion)
{
	SparseArray<int> arr;

	ASSERT_EQ(arr.size(), 0);

	arr.insertAt(0, 1);
	arr.insertAt(1, 2);
	arr.insertAt(2, 3);

	ASSERT_EQ(arr[0], 1);
	ASSERT_EQ(arr[1], 2);
	ASSERT_EQ(arr[2], 3);
	ASSERT_EQ(arr.size(), 3);
}


TEST(SparseArray, insertionWithHoles)
{
	SparseArray<int> arr;

	ASSERT_EQ(arr.size(), 0);

	arr.insertAt(0, 1);
	arr.insertAt(2, 2);
	arr.insertAt(4, 3);

	ASSERT_EQ(arr[0], 1);
	ASSERT_FALSE(arr[1].has_value());
	ASSERT_EQ(arr[2], 2);
	ASSERT_FALSE(arr[3].has_value());
	ASSERT_EQ(arr[4], 3);

	ASSERT_EQ(arr.size(), 5);
}

TEST(SparseArray, insertionMovedValue)
{
	SparseArray<std::vector<int>> arr;
	std::vector<int> vec = { 1, 2, 3 };

	ASSERT_EQ(arr.size(), 0);

	arr.insertAt(0, std::move(vec));

	ASSERT_EQ(arr[0], std::vector<int>({ 1, 2, 3 }));
	ASSERT_EQ(arr.size(), 1);
}

class TestClass {
public:
	TestClass() = default;
	TestClass(int a, int b, std::vector<float> c) : a(a), b(b), c(c) {}
	int a;
	int b;
	std::vector<float> c;
};

TEST(SparseArray, emplace)
{
	SparseArray<TestClass> arr;

	ASSERT_EQ(arr.size(), 0);

	arr.emplaceAt(0, 1, 2, std::vector<float>({ 1.0f, 2.0f, 3.0f }));

	ASSERT_EQ(arr[0]->a, 1);
	ASSERT_EQ(arr[0]->b, 2);
	ASSERT_EQ(arr[0]->c, std::vector<float>({ 1.0f, 2.0f, 3.0f }));
	ASSERT_EQ(arr.size(), 1);
}

TEST(SparseArray, eraseExistingValue)
{
	SparseArray<int> arr;

	ASSERT_EQ(arr.size(), 0);

	arr.insertAt(0, 1);
	arr.insertAt(1, 2);
	arr.insertAt(2, 3);

	ASSERT_EQ(arr.size(), 3);

	arr.erase(1);

	ASSERT_EQ(arr.size(), 3) << "erase should not resize the array";
	ASSERT_EQ(arr[0], 1);
	ASSERT_FALSE(arr[1].has_value()) << "erase should set the value to std::nullopt";
	ASSERT_EQ(arr[2], 3);
}

TEST(SparseArray, eraseNonExistingValue)
{
	SparseArray<int> arr;

	ASSERT_EQ(arr.size(), 0);

	arr.insertAt(0, 1);
	arr.insertAt(1, 2);
	arr.insertAt(2, 3);

	ASSERT_EQ(arr.size(), 3);

	arr.erase(3);

	ASSERT_EQ(arr.size(), 3);
	ASSERT_EQ(arr[0], 1);
	ASSERT_EQ(arr[1], 2);
	ASSERT_EQ(arr[2], 3);
}

TEST(SparseArray, insertReturnValue)
{
	SparseArray<std::vector<int>> arr;

	auto &index0 = arr.insertAt(0, { 1, 2, 3 });
	ASSERT_TRUE(index0.has_value()) << "insertAt should return a reference to the inserted value";
	auto &value0 = arr[0].value();

	auto &index1 = arr.insertAt(1, { 4, 5, 6 });
	ASSERT_TRUE(index1.has_value());
	auto &value1 = arr[1].value();

	EXPECT_FALSE(index0.has_value()) << "Resizing the vector0 should invalidate the references";
	EXPECT_TRUE(index1.has_value()) << "Resizing the vector1 should invalidate the references";

	ASSERT_NE(&value0, &arr[0].value()) << "Resizing the vector should move the values";
	ASSERT_EQ(&value1, &arr[1].value()) << "Resizing the vector should not move the newly inserted value";
	ASSERT_EQ(value1, arr[1].value());
}

TEST(SparseArray, getIndexExistingValue)
{
	SparseArray<std::vector<int>> arr;
	std::vector<std::optional<int>> vec;

	arr.insertAt(0, { 1, 2, 3 });
	auto &index1 = arr.insertAt(1, { 4, 5, 6 });

	ASSERT_EQ(arr.getIndex(arr.at(0)), 0);
	ASSERT_EQ(arr.getIndex(arr.at(1)), 1);
	ASSERT_EQ(arr.getIndex(index1), 1);
}

TEST(SparseArray, getIndexNonExistingValue)
{
	SparseArray<std::vector<int>> arr;
	std::vector<std::optional<int>> vec;

	arr.insertAt(0, { 1, 2, 3 });
	arr.insertAt(1, { 4, 5, 6 });

	ASSERT_THROW(arr.getIndex(arr.at(2)), Errors::ValueNotFound);
}

TEST(SparseArray, constructedWithBaseSize)
{
	SparseArray<std::vector<int>> arr(10);

	ASSERT_EQ(arr.size(), 10);
	for (int i = 0; i < arr.size(); i++) {
		ASSERT_FALSE(arr[i].has_value());
	}
}

TEST(SparseArray, constructedWithBaseSizeCanBeUsed)
{
	SparseArray<std::vector<int>> arr(10);

	ASSERT_EQ(arr.size(), 10);
	for (int i = 0; i < arr.size(); i++) {
		arr[i] = { i, i, i };
	}
	for (int i = 0; i < arr.size(); i++) {
		ASSERT_EQ(arr[i], std::vector<int>({ i, i, i }));
	}
}

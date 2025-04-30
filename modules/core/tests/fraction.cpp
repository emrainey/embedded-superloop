#include <gtest/gtest.h>
#include <iostream>
#include <core/Fraction.hpp>

TEST(FractionTest, ClassScalarArthimetic) {
    using core::Fraction;
    Fraction f{3, 8};
    f += 1;
    std::cout << f << std::endl;
    ASSERT_EQ(f, Fraction(11, 8));
    f -= 2;
    std::cout << f << std::endl;
    ASSERT_EQ(f, Fraction(-5, 8));
    f *= 4;
    std::cout << f << std::endl;
    ASSERT_EQ(f, Fraction(-20, 8));
    f /= 5;
    std::cout << f << std::endl;
    ASSERT_EQ(f, Fraction(-20, 40));
}

TEST(FractionTest, ClassFractionArithmetic) {
    using core::Fraction;
    Fraction f{3, 8};
    Fraction g{1, 2};
    f += g;
    std::cout << f << std::endl;
    ASSERT_EQ(f, Fraction(7, 8));
    f -= g;
    std::cout << f << std::endl;
    ASSERT_EQ(f, Fraction(3, 8));
    f *= g;
    std::cout << f << std::endl;
    ASSERT_EQ(f, Fraction(3, 16));
    f /= g;
    std::cout << f << std::endl;
    ASSERT_EQ(f, Fraction(3, 8));
}

TEST(FractionTest, FriendScalarArithmetic) {
    using core::Fraction;
    Fraction f{3, 8};
    f = f + 1;
    std::cout << f << std::endl;
    ASSERT_EQ(f, Fraction(11, 8));
    f = f - 2;
    std::cout << f << std::endl;
    ASSERT_EQ(f, Fraction(-5, 8));
    f = f * 4;
    std::cout << f << std::endl;
    ASSERT_EQ(f, Fraction(-20, 8));
    f = f / 5;
    std::cout << f << std::endl;
    ASSERT_EQ(f, Fraction(-4, 8));
}

TEST(FractionTest, FriendFractionArithmetic) {
    using core::Fraction;
    Fraction f{3, 8};
    Fraction g{1, 2};
    f = f + g;
    std::cout << f << std::endl;
    ASSERT_EQ(f, Fraction(7, 8));
    f = f - g;
    std::cout << f << std::endl;
    ASSERT_EQ(f, Fraction(3, 8));
    f = f * g;
    std::cout << f << std::endl;
    ASSERT_EQ(f, Fraction(3, 16));
    f = f / g;
    std::cout << f << std::endl;
    ASSERT_EQ(f, Fraction(3, 8));
}

TEST(FractionTest, Comparison) {
    using core::Fraction;
    Fraction f{3, 8};
    ASSERT_TRUE(f < 1);
    ASSERT_TRUE(f < Fraction(1, 2));
    ASSERT_TRUE(f <= 1);
    ASSERT_TRUE(f <= Fraction(3, 8));
    ASSERT_FALSE(f > 1);
    ASSERT_FALSE(f > Fraction(1, 2));
    ASSERT_FALSE(f >= 1);
    ASSERT_TRUE(f >= Fraction(3, 8));
    ASSERT_TRUE(f == Fraction(3, 8));
    ASSERT_FALSE(f != Fraction(3, 8));
}

TEST(FractionTest, Conversion) {
    using core::Fraction;
    Fraction f{355, 113};    // this is an approximation of pi from antiquity
    auto g = f.as<float>();
    auto h = f.as<int>();
    ASSERT_FLOAT_EQ(g, 3.14159292f);
    ASSERT_EQ(h, 3);
}

TEST(FractionTest, InfiniteAndZero) {
    using core::Fraction;
    Fraction f{6, 0};
    ASSERT_FALSE(f.IsZero());
    ASSERT_TRUE(f.IsInfinite());
    Fraction g{3, 4};
    ASSERT_FALSE(g.IsZero());
    ASSERT_FALSE(g.IsInfinite());
    auto h = g / 0;
    ASSERT_FALSE(h.IsZero());
    ASSERT_TRUE(h.IsInfinite());
    auto i = g * 0;
    ASSERT_FALSE(i.IsInfinite());
    auto j = g * f;
    ASSERT_FALSE(j.IsZero());
    ASSERT_TRUE(j.IsInfinite());
    Fraction k{0, 10};
    ASSERT_TRUE(k.IsZero());
    ASSERT_FALSE(k.IsInfinite());
    auto m = g / k;
    ASSERT_FALSE(m.IsZero());
    ASSERT_TRUE(m.IsInfinite());
}
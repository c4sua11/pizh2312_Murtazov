import math


class Triangle:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c

    def change_size(self, percent):
        factor = 1 + percent / 100
        self.a *= factor
        self.b *= factor
        self.c *= factor

    def perimeter(self):
        return self.a + self.b + self.c

    def radius(self):
        p = self.perimeter() / 2
        area = math.sqrt(p * (p - self.a) * (p - self.b) * (p - self.c))
        return (self.a * self.b * self.c) / (4 * area)

    def angles(self):
        angle_a = math.degrees(
            math.acos((self.b**2 + self.c**2 - self.a**2) / (2 * self.b * self.c))
        )
        angle_b = math.degrees(
            math.acos((self.a**2 + self.c**2 - self.b**2) / (2 * self.a * self.c))
        )
        angle_c = 180 - angle_a - angle_b
        return angle_a, angle_b, angle_c


triangle = Triangle(3, 4, 5)

print("Периметр:", triangle.perimeter())
print("Радиус описанной окружности:", triangle.circumcircle_radius())
print("Углы треугольника:", triangle.angles())

triangle.change_size(10)

print("Периметр после увеличения:", triangle.perimeter())
print("Радиус описанной окружности после увеличения:", triangle.circumcircle_radius())
print("Углы треугольника после увеличения:", triangle.angles())

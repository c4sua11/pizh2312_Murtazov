from abc import ABC, abstractmethod
import math


class Shape(ABC):
    """
    Абстрактный класс, представляющий геометрическую фигуру.
    """

    @abstractmethod
    def perimeter(self):
        """
        Абстрактный метод для расчета периметра фигуры.
        """
        pass

    @abstractmethod
    def change_size(self, percent):
        """
        Абстрактный метод для изменения размеров фигуры.
        :param percent: Процент изменения размера (положительное значение – увеличение, отрицательное – уменьшение).
        """
        pass


class TriangleCalculator:
    """
    Вспомогательный класс для выполнения расчетов, связанных с треугольником.
    """

    @staticmethod
    def perimeter(a, b, c):
        """
        Рассчитывает периметр треугольника.
        """
        return a + b + c

    @staticmethod
    def radius(a, b, c):
        """
        Рассчитывает радиус описанной окружности вокруг треугольника.
        """
        p = TriangleCalculator.perimeter(a, b, c) / 2
        area = math.sqrt(p * (p - a) * (p - b) * (p - c))
        return (a * b * c) / (4 * area)

    @staticmethod
    def angles(a, b, c):
        """
        Рассчитывает углы треугольника в градусах.
        """
        angle_a = math.degrees(math.acos((b**2 + c**2 - a**2) / (2 * b * c)))
        angle_b = math.degrees(math.acos((a**2 + c**2 - b**2) / (2 * a * c)))
        angle_c = 180 - angle_a - angle_b
        return angle_a, angle_b, angle_c


class Triangle(Shape):
    """
    Класс, представляющий треугольник. Наследуется от Shape.
    """

    def __init__(self, a, b, c):
        """
        Инициализация треугольника со сторонами a, b и c.
        """
        self.__a = a
        self.__b = b
        self.__c = c
        self.__calculator = TriangleCalculator()

    def get_sides(self):
        """
        Возвращает текущие значения сторон треугольника.
        """
        return self.__a, self.__b, self.__c

    def set_sides(self, a, b, c):
        """
        Устанавливает новые значения сторон треугольника.
        """
        self.__a = a
        self.__b = b
        self.__c = c

    def perimeter(self):
        """
        Реализация абстрактного метода. Возвращает периметр треугольника.
        """
        return self.__calculator.perimeter(self.__a, self.__b, self.__c)

    def radius(self):
        """
        Возвращает радиус описанной окружности вокруг треугольника.
        """
        return self.__calculator.radius(self.__a, self.__b, self.__c)

    def angles(self):
        """
        Возвращает углы треугольника.
        """
        return self.__calculator.angles(self.__a, self.__b, self.__c)

    def change_size(self, percent):
        """
        Увеличивает или уменьшает стороны треугольника на указанный процент.
        """
        factor = 1 + percent / 100
        self.__a *= factor
        self.__b *= factor
        self.__c *= factor

    def __call__(self):
        """
        Возвращает строковое представление треугольника.
        """
        return f"Triangle with sides {self.__a:.2f}, {self.__b:.2f}, {self.__c:.2f}"


triangle = Triangle(3, 4, 5)

print("Периметр:", triangle.perimeter())
print("Радиус описанной окружности:", triangle.radius())
print("Углы треугольника:", triangle.angles())

triangle.change_size(10)

print("Периметр после увеличения:", triangle.perimeter())
print("Радиус описанной окружности после увеличения:", triangle.radius())
print("Углы треугольника после увеличения:", triangle.angles())

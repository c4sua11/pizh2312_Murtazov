from typing import Union


class Roman:
    """
    Класс для работы с римскими числами.
    
    Поддерживает арифметические операции: +, -, *, /
    Имеет статические методы для преобразования между римскими и арабскими числами.
    """

    # Словари для преобразования между римскими и арабскими числами
    _roman_to_int = {
        'I': 1, 'V': 5, 'X': 10, 'L': 50,
        'C': 100, 'D': 500, 'M': 1000
    }
    _int_to_roman = [
        (1000, 'M'), (900, 'CM'), (500, 'D'), (400, 'CD'),
        (100, 'C'), (90, 'XC'), (50, 'L'), (40, 'XL'),
        (10, 'X'), (9, 'IX'), (5, 'V'), (4, 'IV'), (1, 'I')
    ]

    def __init__(self, value: Union[str, int]):
        """
        Инициализация римского числа.
        
        :param value: Значение римского числа в виде строки или целого числа.
        """
        if isinstance(value, str):
            self.value = self._roman_to_integer(value)
        elif isinstance(value, int):
            self.value = value
        else:
            raise ValueError("Значение должно быть строкой или целым числом")

    @staticmethod
    def _roman_to_integer(roman: str) -> int:
        """
        Преобразование римского числа в арабское.
        
        :param roman: Римское число в виде строки.
        :return: Арабское число.
        """
        result = 0
        prev_value = 0
        for char in reversed(roman):
            current_value = Roman._roman_to_int[char]
            if current_value < prev_value:
                result -= current_value
            else:
                result += current_value
            prev_value = current_value
        return result

    @staticmethod
    def _integer_to_roman(num: int) -> str:
        """
        Преобразование арабского числа в римское.
        
        :param num: Арабское число.
        :return: Римское число в виде строки.
        """
        result = []
        for (arabic, roman) in Roman._int_to_roman:
            while num >= arabic:
                result.append(roman)
                num -= arabic
        return ''.join(result)

    def __str__(self) -> str:
        """
        Возвращает строковое представление римского числа.
        
        :return: Римское число в виде строки.
        """
        return self._integer_to_roman(self.value)

    def __add__(self, other: 'Roman') -> 'Roman':
        """
        Оператор сложения.
        
        :param other: Другое римское число.
        :return: Результат сложения.
        """
        return Roman(self.value + other.value)

    def __sub__(self, other: 'Roman') -> 'Roman':
        """
        Оператор вычитания.
        
        :param other: Другое римское число.
        :return: Результат вычитания.
        """
        result = self.value - other.value
        if result <= 0:
            raise ValueError("Результат вычитания должен быть положительным римским числом")
        return Roman(result)

    def __mul__(self, other: 'Roman') -> 'Roman':
        """
        Оператор умножения.
        
        :param other: Другое римское число.
        :return: Результат умножения.
        """
        return Roman(self.value * other.value)

    def __truediv__(self, other: 'Roman') -> 'Roman':
        """
        Оператор деления.
        
        :param other: Другое римское число.
        :return: Результат деления.
        """
        if other.value == 0:
            raise ZeroDivisionError("Деление на ноль недопустимо")
        result = self.value // other.value
        if result <= 0:
            raise ValueError("Результат деления должен быть положительным римским числом")
        return Roman(result)
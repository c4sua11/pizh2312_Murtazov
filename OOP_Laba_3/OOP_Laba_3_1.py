from abc import ABC, abstractmethod

class Number(ABC):
    """
    Абстрактный базовый класс для чисел.
    """
    
    @abstractmethod
    def display(self):
        """
        Абстрактный метод для отображения числа.
        """
        pass
    
    @abstractmethod
    def to_int(self):
        """
        Абстрактный метод для преобразования числа в целое число.
        """
        pass
    
    @abstractmethod
    def __add__(self, other):
        """
        Абстрактный метод для сложения чисел.
        """
        pass
    
    @abstractmethod
    def __sub__(self, other):
        """
        Абстрактный метод для вычитания чисел.
        """
        pass
    
    @abstractmethod
    def __mul__(self, other):
        """
        Абстрактный метод для умножения чисел.
        """
        pass
    
    @abstractmethod
    def __truediv__(self, other):
        """
        Абстрактный метод для деления чисел.
        """
        pass

class Roman(Number):
    """
    Класс для работы с римскими числами.
    """
    
    # Словарь для преобразования римских чисел в арабские
    _roman_to_int = {
        'I': 1,
        'V': 5,
        'X': 10,
        'L': 50,
        'C': 100,
        'D': 500,
        'M': 1000
    }
    
    # Список кортежей для преобразования арабских чисел в римские
    _int_to_roman = [
        (1000, 'M'), (900, 'CM'), (500, 'D'), (400, 'CD'),
        (100, 'C'), (90, 'XC'), (50, 'L'), (40, 'XL'),
        (10, 'X'), (9, 'IX'), (5, 'V'), (4, 'IV'), (1, 'I')
    ]
    
    def __init__(self, value):
        """
        Инициализация римского числа.
        
        :param value: Значение римского числа (строка) или арабского числа (целое число).
        """
        if isinstance(value, str):
            self._value = self._roman_to_int_value(value)
        elif isinstance(value, int):
            self._value = value
        else:
            raise ValueError("Значение должно быть строкой (римское число) или целым числом (арабское число)")
    
    @staticmethod
    def _roman_to_int_value(roman):
        """
        Преобразование римского числа в арабское.
        
        :param roman: Римское число (строка).
        :return: Арабское число (целое число).
        """
        total = 0
        prev_value = 0
        for char in reversed(roman):
            value = Roman._roman_to_int[char]
            if value < prev_value:
                total -= value
            else:
                total += value
            prev_value = value
        return total
    
    @staticmethod
    def _int_to_roman_value(number):
        """
        Преобразование арабского числа в римское.
        
        :param number: Арабское число (целое число).
        :return: Римское число (строка).
        """
        result = ''
        for (arabic, roman) in Roman._int_to_roman:
            while number >= arabic:
                result += roman
                number -= arabic
        return result
    
    def display(self):
        """
        Отображение римского числа.
        
        :return: Римское число (строка).
        """
        return self._int_to_roman_value(self._value)
    
    def to_int(self):
        """
        Преобразование римского числа в арабское.
        
        :return: Арабское число (целое число).
        """
        return self._value
    
    def __add__(self, other):
        """
        Сложение двух римских чисел.
        
        :param other: Другое римское число.
        :return: Новое римское число, результат сложения.
        """
        if isinstance(other, Roman):
            return Roman(self._value + other._value)
        return NotImplemented
    
    def __sub__(self, other):
        """
        Вычитание двух римских чисел.
        
        :param other: Другое римское число.
        :return: Новое римское число, результат вычитания.
        """
        if isinstance(other, Roman):
            result = self._value - other._value
            if result < 0:
                raise ValueError("Результат вычитания не может быть отрицательным римским числом")
            return Roman(result)
        return NotImplemented
    
    def __mul__(self, other):
        """
        Умножение двух римских чисел.
        
        :param other: Другое римское число.
        :return: Новое римское число, результат умножения.
        """
        if isinstance(other, Roman):
            return Roman(self._value * other._value)
        return NotImplemented
    
    def __truediv__(self, other):
        """
        Деление двух римских чисел.
        
        :param other: Другое римское число.
        :return: Новое римское число, результат деления.
        """
        if isinstance(other, Roman):
            if other._value == 0:
                raise ZeroDivisionError("Деление на ноль")
            result = self._value // other._value
            return Roman(result)
        return NotImplemented
    
    def __str__(self):
        """
        Строковое представление римского числа.
        
        :return: Римское число (строка).
        """
        return self.display()
    
    def __int__(self):
        """
        Целочисленное представление римского числа.
        
        :return: Арабское число (целое число).
        """
        return self.to_int()

class Calculator:
    """
    Класс для выполнения арифметических операций с римскими числами.
    """
    
    def add(self, num1, num2):
        """
        Сложение двух римских чисел.
        
        :param num1: Первое римское число.
        :param num2: Второе римское число.
        :return: Результат сложения (римское число).
        """
        if isinstance(num1, Roman) and isinstance(num2, Roman):
            return num1 + num2
        raise TypeError("Оба операнда должны быть объектами класса Roman")
    
    def subtract(self, num1, num2):
        """
        Вычитание двух римских чисел.
        
        :param num1: Первое римское число.
        :param num2: Второе римское число.
        :return: Результат вычитания (римское число).
        """
        if isinstance(num1, Roman) and isinstance(num2, Roman):
            return num1 - num2
        raise TypeError("Оба операнда должны быть объектами класса Roman")
    
    def multiply(self, num1, num2):
        """
        Умножение двух римских чисел.
        
        :param num1: Первое римское число.
        :param num2: Второе римское число.
        :return: Результат умножения (римское число).
        """
        if isinstance(num1, Roman) and isinstance(num2, Roman):
            return num1 * num2
        raise TypeError("Оба операнда должны быть объектами класса Roman")
    
    def divide(self, num1, num2):
        """
        Деление двух римских чисел.
        
        :param num1: Первое римское число.
        :param num2: Второе римское число.
        :return: Результат деления (римское число).
        """
        if isinstance(num1, Roman) and isinstance(num2, Roman):
            return num1 / num2
        raise TypeError("Оба операнда должны быть объектами класса Roman")

# Пример использования
roman1 = Roman('X')   # 10
roman2 = Roman('V')   # 5

calculator = Calculator()

result_add = calculator.add(roman1, roman2)
print(f"X + V = {result_add}")  # X + V = XV

result_sub = calculator.subtract(roman1, roman2)
print(f"X - V = {result_sub}")  # X - V = V

result_mul = calculator.multiply(roman1, roman2)
print(f"X * V = {result_mul}")  # X * V = L

result_div = calculator.divide(roman1, roman2)
print(f"X / V = {result_div}")  # X / V = II
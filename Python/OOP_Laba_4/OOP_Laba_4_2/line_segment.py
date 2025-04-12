import json
from typing import Tuple

class LineSegment:
    """
    Класс для представления математического отрезка на числовой прямой.
    """
    
    def __init__(self, start: float, end: float):
        """
        Инициализация отрезка.
        :param start: Начальная точка отрезка.
        :param end: Конечная точка отрезка.
        """
        if start > end:
            start, end = end, start  # Обеспечиваем правильный порядок точек
        self.__start = start
        self.__end = end
    
    def __str__(self) -> str:
        """
        Возвращает строковое представление отрезка.
        """
        return f"Отрезок: [{self.__start}, {self.__end}]"
    
    def __add__(self, other: 'LineSegment') -> 'LineSegment':
        """
        Перегрузка оператора + (объединение отрезков).
        """
        return LineSegment(min(self.__start, other.__start), max(self.__end, other.__end))
    
    def __sub__(self, value: float) -> 'LineSegment':
        """
        Перегрузка оператора - (сдвиг отрезка влево на value).
        """
        return LineSegment(self.__start - value, self.__end - value)
    
    def length(self) -> float:
        """
        Возвращает длину отрезка.
        """
        return self.__end - self.__start
    
    def contains(self, point: float) -> bool:
        """
        Проверяет, принадлежит ли точка отрезку.
        """
        return self.__start <= point <= self.__end
    
    def midpoint(self) -> float:
        """
        Возвращает середину отрезка.
        """
        return (self.__start + self.__end) / 2
    
    @classmethod
    def from_string(cls, str_value: str) -> 'LineSegment':
        """
        Создает объект LineSegment из строки вида "(a, b)".
        """
        start, end = map(float, str_value.strip("() ").split(","))
        return cls(start, end)
    
    def save(self, filename: str):
        """
        Сохраняет объект в JSON-файл.
        """
        with open(filename, 'w') as file:
            json.dump({'start': self.__start, 'end': self.__end}, file)
    
    @classmethod
    def load(cls, filename: str) -> 'LineSegment':
        """
        Загружает объект из JSON-файла.
        """
        with open(filename, 'r') as file:
            data = json.load(file)
        return cls(data['start'], data['end'])
    
    @property
    def start(self) -> float:
        """
        Свойство: начальная точка отрезка.
        """
        return self.__start
    
    @property
    def end(self) -> float:
        """
        Свойство: конечная точка отрезка.
        """
        return self.__end
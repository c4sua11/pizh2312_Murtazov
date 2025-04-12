import json
from line_segment import LineSegment
from typing import List

class LineSegmentCollection:
    """
    Класс-контейнер для хранения и управления набором объектов LineSegment.
    """
    
    def __init__(self):
        """
        Инициализация пустого контейнера.
        """
        self._data: List[LineSegment] = []
    
    def __str__(self) -> str:
        """
        Возвращает строковое представление контейнера.
        """
        return "\n".join(str(segment) for segment in self._data)
    
    def __getitem__(self, index: int) -> LineSegment:
        """
        Позволяет обращаться к элементам по индексу.
        """
        return self._data[index]
    
    def add(self, value: LineSegment):
        """
        Добавляет объект LineSegment в контейнер.
        """
        if isinstance(value, LineSegment):
            self._data.append(value)
        else:
            raise TypeError("Можно добавлять только объекты LineSegment")
    
    def remove(self, index: int):
        """
        Удаляет объект по индексу.
        """
        if 0 <= index < len(self._data):
            del self._data[index]
        else:
            raise IndexError("Индекс выходит за границы списка")
    
    def save(self, filename: str):
        """
        Сохраняет контейнер в JSON-файл.
        """
        with open(filename, 'w') as file:
            json.dump([{'start': seg.start, 'end': seg.end} for seg in self._data], file)
    
    def load(self, filename: str):
        """
        Загружает контейнер из JSON-файла.
        """
        with open(filename, 'r') as file:
            data = json.load(file)
        self._data = [LineSegment(item['start'], item['end']) for item in data]

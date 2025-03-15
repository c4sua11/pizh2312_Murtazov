from abc import ABC, abstractmethod

class WritingInstrument(ABC):
    """
    Базовый класс для всех пишущих принадлежностей.
    """
    
    def __init__(self, brand: str, color: str):
        """
        Инициализация пишущей принадлежности.
        :param brand: Производитель
        :param color: Цвет чернил
        """
        self.brand = brand  # Открытое поле
        self._color = color  # Защищённое поле
        self.__ink_level = 100  # Приватное поле (процент чернил)
    
    @abstractmethod
    def write(self, text: str) -> None:
        """
        Абстрактный метод для написания текста.
        """
        pass
    
    def _decrease_ink(self, amount: int) -> None:
        """
        Уменьшает уровень чернил.
        """
        self.__ink_level = max(0, self.__ink_level - amount)
    
    def get_ink_level(self) -> int:
        """
        Возвращает текущий уровень чернил.
        """
        return self.__ink_level
    
class Pencil(WritingInstrument):
    """
    Класс Карандаша.
    """
    
    def __init__(self, brand: str, hardness: str):
        super().__init__(brand, "серый")
        self.hardness = hardness  # Твёрдость грифеля
    
    def write(self, text: str) -> None:
        print(f"Карандаш {self.brand} ({self.hardness}) пишет: {text}")
    
class Pen(WritingInstrument):
    """
    Класс обычной Ручки.
    """
    
    def write(self, text: str) -> None:
        if self.get_ink_level() > 0:
            print(f"Ручка {self.brand} ({self._color}) пишет: {text}")
            self._decrease_ink(len(text))
        else:
            print("Чернила закончились!")
    
class GelPen(Pen):
    """
    Класс Гелевой Ручки.
    """
    
    def write(self, text: str) -> None:
        if self.get_ink_level() > 0:
            print(f"Гелевая ручка {self.brand} ({self._color}) пишет мягко: {text}")
            self._decrease_ink(len(text) * 2)  # Гель расходуется быстрее
        else:
            print("Чернила закончились!")

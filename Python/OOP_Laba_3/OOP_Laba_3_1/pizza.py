from typing import List

class Pizza:
    """
    Базовый класс для всех видов пицц.
    """

    def __init__(self, name: str, dough: str, sauce: str, toppings: List[str], price: int) -> None:
        """
        Инициализация пиццы.

        :param name: Название пиццы
        :param dough: Тесто пиццы
        :param sauce: Соус пиццы
        :param toppings: Начинка пиццы
        :param price: Цена пиццы
        """
        self.name: str = name
        self.dough: str = dough
        self.sauce: str = sauce
        self.toppings: List[str] = toppings
        self.price: int = price

    def prepare(self) -> None:
        """
        Подготовка пиццы: замес теста, добавление соуса и начинки.
        """
        print(f"Подготавливаем {self.name}: замес теста {self.dough}, добавляем соус {self.sauce} и начинку {', '.join(self.toppings)}.")

    def bake(self) -> None:
        """
        Выпечка пиццы.
        """
        print(f"Выпекаем {self.name}.")

    def cut(self) -> None:
        """
        Порезка пиццы.
        """
        print(f"Режем {self.name}.")

    def box(self) -> None:
        """
        Упаковка пиццы.
        """
        print(f"Упаковываем {self.name}.")

    def __str__(self) -> str:
        """
        Возвращает строковое представление пиццы.

        :return: Строка с названием и ценой пиццы
        """
        return f"{self.name} - {self.price} руб."


class PepperoniPizza(Pizza):
    """
    Класс для пиццы Пепперони.
    """

    def __init__(self) -> None:
        super().__init__(
            name="Пепперони",
            dough="Тонкое тесто",
            sauce="Томатный соус",
            toppings=["Пепперони", "Моцарелла"],
            price=500
        )


class BarbecuePizza(Pizza):
    """
    Класс для пиццы Барбекю.
    """

    def __init__(self) -> None:
        super().__init__(
            name="Барбекю",
            dough="Пышное тесто",
            sauce="Соус барбекю",
            toppings=["Курочка", "Ананас", "Моцарелла"],
            price=600
        )


class SeafoodPizza(Pizza):
    """
    Класс для пиццы Дары Моря.
    """

    def __init__(self) -> None:
        super().__init__(
            name="Дары Моря",
            dough="Пышное тесто",
            sauce="Сливочный соус",
            toppings=["Лосось", "Креветки", "Моцарелла"],
            price=700
        )
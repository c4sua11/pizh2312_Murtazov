from typing import List
from pizza import Pizza

class Order:
    """
    Класс для представления заказа.
    """

    def __init__(self) -> None:
        """
        Инициализация заказа.
        """
        self.pizzas: List[Pizza] = []

    def add_pizza(self, pizza: Pizza) -> None:
        """
        Добавление пиццы в заказ.

        :param pizza: Объект Pizza, который нужно добавить в заказ
        """
        self.pizzas.append(pizza)
        print(f"{pizza.name} добавлена в заказ.")

    def get_total_price(self) -> int:
        """
        Подсчет общей стоимости заказа.

        :return: Общая стоимость заказа
        """
        total_price: int = sum(pizza.price for pizza in self.pizzas)
        return total_price

    def __str__(self) -> str:
        """
        Возвращает строковое представление заказа.

        :return: Строка с списком пицц и общей стоимостью
        """
        order_details: str = "\n".join(str(pizza) for pizza in self.pizzas)
        return f"Ваш заказ:\n{order_details}\nОбщая стоимость: {self.get_total_price()} руб."
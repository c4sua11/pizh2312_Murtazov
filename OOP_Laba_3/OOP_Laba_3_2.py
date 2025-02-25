from abc import ABC, abstractmethod

class Pizza(ABC):
    """
    Абстрактный базовый класс для пицц.
    """
    
    def __init__(self, name, dough, sauce, toppings, price):
        """
        Инициализация пиццы.
        
        :param name: Название пиццы.
        :param dough: Тесто.
        :param sauce: Соус.
        :param toppings: Начинка.
        :param price: Цена пиццы.
        """
        self._name = name
        self._dough = dough
        self._sauce = sauce
        self._toppings = toppings
        self._price = price
    
    @property
    def name(self):
        """
        Получение названия пиццы.
        
        :return: Название пиццы.
        """
        return self._name
    
    @property
    def price(self):
        """
        Получение цены пиццы.
        
        :return: Цена пиццы.
        """
        return self._price
    
    @abstractmethod
    def prepare(self):
        """
        Абстрактный метод для подготовки пиццы.
        """
        print(f"Подготовка {self._name}: замес теста, добавление соуса и начинки.")
    
    def bake(self):
        """
        Готовка пиццы.
        """
        print(f"Ипечь {self._name} в течение 25 минут при 220 градусах.")
    
    def cut(self):
        """
        Порезка пиццы.
        """
        print(f"Порезать {self._name} на 8 кусочков.")
    
    def box(self):
        """
        Упаковка пиццы.
        """
        print(f"Упаковать {self._name} в специальную пиццерийскую упаковку.")

class PepperoniPizza(Pizza):
    """
    Конкретный класс для пиццы Пепперони.
    """
    
    def __init__(self):
        super().__init__(
            name="Пепперони",
            dough="Тонкое тесто",
            sauce="Томатный соус",
            toppings=["Пепперони", "Моцарелла", "Шампиньоны"],
            price=1200
        )
    
    def prepare(self):
        """
        Подготовка пиццы Пепперони.
        """
        print(f"Подготовка {self._name}: замес теста, добавление соуса и начинки.")
        for topping in self._toppings:
            print(f"Добавление {topping}")

class BarbecuePizza(Pizza):
    """
    Конкретный класс для пиццы Барбекю.
    """
    
    def __init__(self):
        super().__init__(
            name="Барбекю",
            dough="Тонкое тесто",
            sauce="Соус барбекю",
            toppings=["Курочка", "Бекон", "Лук", "Моцарелла"],
            price=1500
        )
    
    def prepare(self):
        """
        Подготовка пиццы Барбекю.
        """
        print(f"Подготовка {self._name}: замес теста, добавление соуса и начинки.")
        for topping in self._toppings:
            print(f"Добавление {topping}")

class SeafoodPizza(Pizza):
    """
    Конкретный класс для пиццы Дары Моря.
    """
    
    def __init__(self):
        super().__init__(
            name="Дары Моря",
            dough="Толстое тесто",
            sauce="Сливочный соус",
            toppings=["Креветки", "Мидии", "Октопус", "Моцарелла"],
            price=2000
        )
    
    def prepare(self):
        """
        Подготовка пиццы Дары Моря.
        """
        print(f"Подготовка {self._name}: замес теста, добавление соуса и начинки.")
        for topping in self._toppings:
            print(f"Добавление {topping}")

class Order:
    """
    Класс для управления заказом.
    """
    
    def __init__(self):
        """
        Инициализация заказа.
        """
        self._pizzas = []
    
    def add_pizza(self, pizza):
        """
        Добавление пиццы в заказ.
        
        :param pizza: Пицца для добавления.
        """
        self._pizzas.append(pizza)
    
    def remove_pizza(self, index):
        """
        Удаление пиццы из заказа по индексу.
        
        :param index: Индекс пиццы для удаления.
        """
        if 0 <= index < len(self._pizzas):
            removed_pizza = self._pizzas.pop(index)
            print(f"Удалена пицца: {removed_pizza.name}")
        else:
            print("Неверный индекс пиццы.")
    
    def calculate_total_price(self):
        """
        Расчет общей стоимости заказа.
        
        :return: Общая стоимость заказа.
        """
        total_price = sum(pizza.price for pizza in self._pizzas)
        return total_price
    
    def display_order(self):
        """
        Отображение списка заказанных пицц.
        """
        if not self._pizzas:
            print("Заказ пуст.")
            return
        print("Заказ:")
        for i, pizza in enumerate(self._pizzas, start=1):
            print(f"{i}. {pizza.name} - {pizza.price} руб.")
        print(f"Общая стоимость: {self.calculate_total_price()} руб.")

class Terminal:
    """
    Класс для взаимодействия с пользователем.
    """
    
    def __init__(self):
        """
        Инициализация терминала.
        """
        self._order = Order()
        self._menu = [
            PepperoniPizza(),
            BarbecuePizza(),
            SeafoodPizza()
        ]
    
    def display_menu(self):
        """
        Отображение меню.
        """
        print("Меню пиццерии:")
        for i, pizza in enumerate(self._menu, start=1):
            print(f"{i}. {pizza.name} - {pizza.price} руб.")
    
    def take_order(self):
        """
        Прием заказа от пользователя.
        """
        while True:
            self.display_menu()
            choice = input("Выберите номер пиццы (0 для завершения): ")
            if choice == '0':
                break
            try:
                choice = int(choice)
                if 1 <= choice <= len(self._menu):
                    pizza = self._menu[choice - 1]
                    self._order.add_pizza(pizza)
                    print(f"Добавлена пицца: {pizza.name}")
                else:
                    print("Неверный номер пиццы. Попробуйте снова.")
            except ValueError:
                print("Введите корректный номер пиццы.")
    
    def confirm_order(self):
        """
        Подтверждение заказа.
        """
        self._order.display_order()
        confirm = input("Подтвердить заказ? (да/нет): ").strip().lower()
        if confirm == 'да':
            self.process_payment()
        else:
            print("Заказ отменен.")
    
    def process_payment(self):
        """
        Обработка оплаты.
        """
        total_price = self._order.calculate_total_price()
        print(f"К оплате: {total_price} руб.")
        payment = input("Введите сумму для оплаты: ")
        try:
            payment = float(payment)
            if payment >= total_price:
                change = payment - total_price
                print(f"Спасибо за покупку! Ваша сдача: {change:.2f} руб.")
                self.prepare_order()
            else:
                print("Недостаточно средств.")
        except ValueError:
            print("Введите корректную сумму.")
    
    def prepare_order(self):
        """
        Подготовка заказа.
        """
        print("Подготовка заказа:")
        for pizza in self._order._pizzas:
            pizza.prepare()
            pizza.bake()
            pizza.cut()
            pizza.box()
        print("Ваш заказ готов!")

# Пример использования
if __name__ == "__main__":
    terminal = Terminal()
    terminal.take_order()
    terminal.confirm_order()
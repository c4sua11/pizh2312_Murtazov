from order import Order
from pizza import PepperoniPizza, BarbecuePizza, SeafoodPizza

class Terminal:
    """
    Класс для представления терминала взаимодействия с пользователем.
    """

    def __init__(self) -> None:
        """
        Инициализация терминала.
        """
        self.current_order: Order = Order()

    def run(self) -> None:
        """
        Запуск терминала и начала взаимодействия с пользователем.
        """
        print("Добро пожаловать в нашу пиццерию!")
        while True:
            self.show_menu()
            choice: str = input("Выберите пиццу или подтвердите заказ: ")

            if choice == "1":
                self.current_order.add_pizza(PepperoniPizza())
            elif choice == "2":
                self.current_order.add_pizza(BarbecuePizza())
            elif choice == "3":
                self.current_order.add_pizza(SeafoodPizza())
            elif choice == "4":
                self.confirm_order()
                return
            else:
                print("Неверный выбор, попробуйте снова.")

    def show_menu(self) -> None:
        """
        Отображение меню на экране.
        """
        print("\nМеню:")
        print("1. Пепперони")
        print("2. Барбекю")
        print("3. Дары Моря")
        print("4. Подтвердить заказ")

    def confirm_order(self) -> None:
        """
        Подтверждение заказа и вывод общей стоимости.
        """
        if not self.current_order.pizzas:
            print("Вы не выбрали ни одной пиццы.")
            return

        print(self.current_order)
        print("Спасибо за заказ!")
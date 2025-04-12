from abc import ABC, abstractmethod
import math
from typing import Tuple, Dict


class TimeDeposit(ABC):
    """
    Абстрактный класс для всех типов вкладов.
    """
    def __init__(self, name: str, interest_rate: float, period_limit: Tuple[int, int], sum_limit: Tuple[float, float]):
        self.name = name
        self.__interest_rate = interest_rate
        self.__period_limit = period_limit
        self.__sum_limit = sum_limit
        self._check_self()

    def __str__(self) -> str:
        return (f"Наименование: {self.name}\n"
                f"Валюта: {self.currency}\n"
                f"Процентная ставка: {self.__interest_rate}%\n"
                f"Срок (мес.): {self.__period_limit}\n"
                f"Сумма: {self.__sum_limit}")

    @property
    def currency(self) -> str:
        return "руб."

    def _check_self(self):
        """Проверяет корректность параметров вклада."""
        assert 0 < self.__interest_rate <= 100, "Процентная ставка должна быть в пределах (0, 100]"
        assert 1 <= self.__period_limit[0] < self.__period_limit[1], "Некорректные границы срока вклада"
        assert 0 < self.__sum_limit[0] <= self.__sum_limit[1], "Некорректные границы суммы вклада"

    def _check_user_params(self, initial_sum: float, period: int):
        """Проверяет, соответствует ли вклад ограничениям."""
        assert self.__sum_limit[0] <= initial_sum < self.__sum_limit[1], "Некорректная сумма вклада"
        assert self.__period_limit[0] <= period < self.__period_limit[1], "Некорректный срок вклада"

    @abstractmethod
    def get_profit(self, initial_sum: float, period: int) -> float:
        """Абстрактный метод для расчета прибыли."""
        pass

    def get_sum(self, initial_sum: float, period: int) -> float:
        """Возвращает итоговую сумму вклада."""
        return initial_sum + self.get_profit(initial_sum, period)


class BonusTimeDeposit(TimeDeposit):
    """
    Вклад с бонусом, который начисляется при превышении определенной суммы.
    """
    def __init__(self, name: str, interest_rate: float, period_limit: Tuple[int, int], sum_limit: Tuple[float, float], bonus: Dict[str, float]):
        self.__bonus = bonus
        super().__init__(name, interest_rate, period_limit, sum_limit)

    def __str__(self) -> str:
        return super().__str__() + f"\nБонус (%): {self.__bonus['percent']}\nБонус (мин. сумма): {self.__bonus['sum']}"

    def get_profit(self, initial_sum: float, period: int) -> float:
        """Рассчитывает прибыль с учетом бонуса."""
        profit = initial_sum * 5 / 100 * period / 12  # Расчет по обычной формуле
        if initial_sum >= self.__bonus['sum']:
            profit += profit * self.__bonus['percent'] / 100
        return profit


class CompoundTimeDeposit(TimeDeposit):
    """
    Вклад с ежемесячной капитализацией процентов.
    """
    def __str__(self) -> str:
        return super().__str__() + "\nКапитализация: Да"

    def get_profit(self, initial_sum: float, period: int) -> float:
        """Рассчитывает прибыль с капитализацией."""
        return initial_sum * (math.pow(1 + 5 / 100 / 12, period) - 1)


# Данные для вкладов
deposits_data = dict(interest_rate=5, period_limit=(6, 18), sum_limit=(1000, 100000))

deposits = (
    BonusTimeDeposit("Бонусный", **deposits_data, bonus={"percent": 5, "sum": 2000}),
    CompoundTimeDeposit("С капитализацией", **deposits_data)
)
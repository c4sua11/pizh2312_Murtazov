# Программирование на языке высокого уровня (Python).
# Задание week_04_1. Вариант !!!
#
# Выполнил: Муртазов Р.Р.
# Группа: ПИЖ-б-о-23-1(2)

from deposit import deposits

if __name__ == "__main__":
    print("Добро пожаловать в систему подбора вкладов!")
    while True:
        print("\n-----")
        print("Нажмите 1, чтобы подобрать вклад, или что угодно для выхода.")
        if input() != "1":
            break
        initial_sum = float(input("Введите начальную сумму вклада: "))
        period = int(input("Введите срок вклада (мес.): "))
        
        matched_deposits = [dep for dep in deposits if dep._check_user_params(initial_sum, period) is None]
        
        if matched_deposits:
            print("{0:18} | {1:13} | {2:13}".format("Вклад", "Прибыль", "Итоговая сумма"))
            for deposit in matched_deposits:
                print("{0:18} | {1:8,.2f} {3:4} | {2:8,.2f} {3:4}".format(
                    deposit.name,
                    deposit.get_profit(initial_sum, period),
                    deposit.get_sum(initial_sum, period),
                    deposit.currency))
        else:
            print("Нет подходящих вкладов.")
    print("Спасибо за использование сервиса!")
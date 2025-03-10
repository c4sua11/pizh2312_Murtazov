from roman import Roman


def main():
    # Пример использования класса Roman
    try:
        num1 = Roman('XV')  # 15
        num2 = Roman('V')   # 5

        print(f"{num1} + {num2} = {num1 + num2}")  # XV + V = XX
        print(f"{num1} - {num2} = {num1 - num2}")  # XV - V = X
        print(f"{num1} * {num2} = {num1 * num2}")  # XV * V = LXXV
        print(f"{num1} / {num2} = {num1 / num2}")  # XV / V = III

    except Exception as e:
        print(f"Ошибка: {e}")


if __name__ == "__main__":
    main()
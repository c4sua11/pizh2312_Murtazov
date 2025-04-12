# Программирование на языке высокого уровня (Python).
# Задание №1. Вариант 17
#
# Выполнил: Муртазов Р.Р
# Группа: ПИЖ-б-о-23-1(2)

from writing_tools import Pencil, Pen, GelPen

def main():
    print("Тестирование пишущих принадлежностей\n")
    
    # Создание объектов
    pencil = Pencil("Faber-Castell", "HB")
    pen = Pen("Parker", "синий")
    gel_pen = GelPen("Pilot", "чёрный")
    
    # Тестирование методов
    print("--- Пишем карандашом ---")
    pencil.write("Привет, мир!")
    
    print("\n--- Пишем ручкой ---")
    pen.write("Это тестовая запись.")
    print("Уровень чернил в ручке:", pen.get_ink_level())
    
    print("\n--- Пишем гелевой ручкой ---")
    gel_pen.write("Гелевые ручки пишут плавно.")
    print("Уровень чернил в гелевой ручке:", gel_pen.get_ink_level())
    
    # Проверка расхода чернил
    print("\n--- Исчерпываем чернила у обычной ручки ---")
    for _ in range(5):
        pen.write("Тест")  # Пишем слово "Тест" несколько раз
    print("Оставшиеся чернила:", pen.get_ink_level())
    
if __name__ == "__main__":
    main()

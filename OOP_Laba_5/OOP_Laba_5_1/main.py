# Программирование на языке высокого уровня (Python).
# Задание №______. Вариант !!!
#
# Выполнил: Фамилия И.О.
# Группа: !!!
# E-mail: !!!

from line_segment import LineSegment
from line_segment_collection import LineSegmentCollection

def main():
    print("Тестирование класса LineSegmentCollection\n")
    
    # Создание коллекции
    collection = LineSegmentCollection()
    
    # Добавление отрезков
    collection.add(LineSegment(1, 5))
    collection.add(LineSegment(3, 7))
    collection.add(LineSegment(10, 15))
    
    print("Содержимое коллекции:")
    print(collection)
    
    # Доступ по индексу
    print("\nОтрезок с индексом 1:", collection[1])
    
    # Удаление элемента
    collection.remove(0)
    print("\nПосле удаления первого элемента:")
    print(collection)
    
    # Сохранение в JSON
    filename = "segments.json"
    collection.save(filename)
    print(f"\nКоллекция сохранена в {filename}")
    
    # Загрузка из JSON
    new_collection = LineSegmentCollection()
    new_collection.load(filename)
    print("\nЗагруженная коллекция:")
    print(new_collection)
    
if __name__ == "__main__":
    main()

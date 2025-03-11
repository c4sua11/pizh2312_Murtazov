from line_segment import LineSegment

def main():
    print("Тестирование класса LineSegment\n")
    
    # Создание отрезка
    segment1 = LineSegment(2, 5)
    print("Создан отрезок:", segment1)
    print("Длина отрезка:", segment1.length())
    print("Середина отрезка:", segment1.midpoint())
    print("Точка 3 принадлежит отрезку?", segment1.contains(3))
    
    # Сложение отрезков
    segment2 = LineSegment(4, 8)
    merged_segment = segment1 + segment2
    print("Объединенный отрезок:", merged_segment)
    
    # Вычитание (сдвиг влево)
    shifted_segment = segment1 - 1
    print("Отрезок после сдвига влево:", shifted_segment)
    
    # Сохранение в файл
    filename = "segment.json"
    segment1.save(filename)
    print(f"Отрезок сохранен в {filename}")
    
    # Загрузка из файла
    loaded_segment = LineSegment.load(filename)
    print("Загруженный отрезок:", loaded_segment)
    
    # Создание из строки
    segment3 = LineSegment.from_string("(10, 15)")
    print("Созданный из строки отрезок:", segment3)
    
if __name__ == "__main__":
    main()

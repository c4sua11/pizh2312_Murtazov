# -*- coding: utf-8 -*-
import random
import math
from room import Room
from random import randrange


#Задание 1.
"""
class Warrior:
    def makeHealth(self, value):
        self.health = value
    def makeKick(enemy):
        enemy.health -= 20

unit1 = Warrior()
unit2 = Warrior()
unit1.makeHealth(100)
unit2.makeHealth(100)


while unit1.health > 0 and unit2.health > 0:
    number = random.randint(1,2)
    if number == 1:
        Warrior.makeKick(unit2)
        print("Первый юнит бьет, здоровье второго юнита: ", unit2.health)
        print()
    else:
        Warrior.makeKick(unit1)
        print("Второй юнит бьет, здоровье первого юнита: ", unit2.health)
        print()

if unit1.health > unit2.health:
    print("Превый юнит победил")
elif unit2.health > unit1.health:
    print("Второй юнит победил")
"""    
    
#Задание 2.
"""
class Person:
    def __init__(self, n, s, q = 1):
        self.name = n
        self.surname = s
        self.qualification = q

    def information(self):
        return "{0} {1}, квалификация: {2}".format(self.name, self.surname, self.qualification)
    
    def __del__(self):
        print(f"До свидания, мистер {self.name} {self.surname}")


first = Person("Иван", "Иванов")
second = Person("Петр", "Петров", 2)
third = Person("Сергей", "Сергеев", 3)
print(first.information())
print(second.information())
print(third.information())

del first

input()

"""

#Задание 3
"""
class Unit:
    count = 0
    def __init__(self, t):
        self.id = Unit.count
        Unit.count += 1
        Unit.team = t
class Soldier(Unit):
    def __init__(self, t):
        Unit.__init__(self, t)
    def folow_hero(self, t):
        print("Иду за героем")
class Hero(Unit):
    def __init__(self, t):
        Unit.__init__(self, t)
        self.level = 1
    def lvl_up(self):
        self.level += 1

hero1 = Hero(1)
hero2 = Hero(2)

team_1 = []
team_2 = []

for i in range(10):
    r = random.randint(1, 2)
    if r == 1:
        team_1.append(Soldier(r))
    else:
        team_2.append(Soldier(r))

print(len(team_1), len(team_2))

if len(team_1) > len(team_2):
    hero1.lvl_up()
else:
    hero2.lvl_up()

team_1[0].folow_hero(hero1)
print(team_1[0].id, hero1.id)

"""

#Задание 4
"""
class Rectangle:
    def __init__(self, width, height, sign):
        self.w = int(width)
        self.h = int(height)
        self.s = str(sign)
    def __str__(self):
        rect = []
        for i in range(self.h):
            rect.append(self.s * self.w)
        rect = '\n'.join(rect)
        return rect
    def __add__(self, other):
        return Rectangle(self.w + other.w, self.h + other.h, self.s)
    
a = Rectangle(4, 2, 'w')
print(a)
b = Rectangle(8, 3, 'z')
print(b)
print(a + b)
print(b + a)

"""

#Задание 5

"""
class Rectangle:
    def __init__(self, width, height):
        self.__w = Rectangle.__test(width)
        self.__h = Rectangle.__test(height)
        print(self)
    def set_width(self, width):
        self.__w = Rectangle.__test(width)
    def set_height(self, height):
        self.__h = Rectangle.__test(height)
    def get_width(self):
        return self.__w
    def get_height(self):
        return self.__h
    def __test(value):
        return abs(value)
    def __str__(self):
        return "Rectangle {0}x{1}".format(self.__w, self.__h)

a = Rectangle(3, 4)
print(a.get_width())
a.set_width(5)
print(a)

b = Rectangle(-2, 4)

"""

#Задание 6

"""
class WinDoor:
    def __init__(self, w, h):
        self.square = w * h

class Room:
    def __init__(self, l, w, h):
        self.length = l
        self.width = w
        self.height = h
        self.wd = []
    def add_wd(self, w, h):
        self.wd.append(WinDoor(w, h))
    def full_surface(self):
        return 2 * self.height * (self.length + self.width)
    def work_surface(self):
        new_square = self.full_surface()
        for i in self.wd:
            new_square -= i.square
        return new_square
    def wallpapers(self, l, w):
        return math.ceil(self.work_surface() / (w * l))

print("Размеры помещения:")
l = float(input("Длина - "))
w = float(input("Ширина - "))
h = float(input("Высота - "))
r1 = Room(l, w, h)

flag = input("Есть неоклеиваемая поверхность? (1 - да, 2 - нет) ")
while flag == '1':
    w = float(input("Ширина - "))
    h = float(input("Высота - "))
    r1.add_wd(w, h)
    flag = input("Добавить еще? (1 - да, 2 - нет) ")

print("Размеры рулона:")
l = float(input("Длина - "))
w = float(input("Ширина - "))

print("Площадь оклейки", r1.work_surface())
print("Количество рулонов", r1.wallpapers(l, w))

"""

#Задание 7

"""
class Snow:
    def __init__(self, qty):
        self.snow = qty
    def __call__(self, qty):
        self.snow = qty
    def __add__(self, n):
        self.snow += n
    def __sub__(self, n):
        self.snow -= n
    def __mul__(self, n):
        self.snow *= n
    def __truediv__(self, n):
        self.snow = round(self.snow / n)
    def makeSnow(self, row):
        qty_row = int(self.snow / row)
        s = ''
        for i in range(qty_row):
            s += '*' * row + '\n'
        s += (self.snow - qty_row * row) * '*' 
        if s[-1] == '\n': 
            s = s[:-1] 
        return s
        
"""

#Задание 8
"""
print("Размеры помещения:")
l = float(input("Длина - "))
w = float(input("Ширина - "))
h = float(input("Высота - "))
r1 = Room(l, w, h)

flag = input("Есть неоклеиваемая поверхность? (1 - да, 2 - нет) ")
while flag == '1':
    w = float(input("Ширина - "))
    h = float(input("Высота - "))
    r1.addWD(w, h)
    flag = input("Добавить еще? (1 - да, 2 - нет) ")

print("Размеры рулона:")
l = float(input("Длина - "))
w = float(input("Ширина - "))

print("Площадь оклейки", r1.workSurface())
print("Количество рулонов", r1.wallpapers(l, w))

"""

#Задание 9
"""
class Pupil:
    def __init__(self):
        self.knowledge = []
    def take(self, info):
        self.knowledge.append(info)
    def lose(self):
        if self.knowledge:
            i = randrange(len(self.knowledge))
        del self.knowledge[i]
"""
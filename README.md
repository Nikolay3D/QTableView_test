# Тестовое задание

## Модель данных
Есть набор объектов и у каждого из них уникальное имя и произвольный набор данных вида ключ/значение.
- Тип ключа - всегда QString.
- Тип значения - double, bool либо QString.
- В пределах объекта элементы с разными ключами могут иметь разный тип значения
- Допустимы элементы с ключом, но без значения. При этом тип значения должен быть определен
- Допустимы одинаковые имена ключей в разных объектах
- Допустимы уникальные ключи, имеющиеся только в одном объекте

## Представление данных
- Отображать и редактировать все объекты через общий QTableView.
- В горизонтальном хедере отображать имена объектов, в вертикальном - ключи.
- Одинаковые ключи у разных объектов не дублируются (отображаются в одной строке).

# Редактирование данных
- Редактируемыми являются только данные, для которых заранее определен тип значения
- Реализовать изменение существующих значений
- Реализовать создание новых значений для элементов с определенным заранее типом

### Пример данных:

>Объект 1
"Ключ 1" - Значение типа bool
"Ключ 2" - Значение типа QString

>Объект 2
"Ключ 2" - Значение типа double
"Ключ 3" - Значение типа QString
"Ключ 4" - Пустое значение типа bool

## Необходимый стек
- С++
- Qt-5
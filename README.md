# Консольная программа "Калькулятор"

<h2>Задание </h2> 
<h3>
По запросу с клавиатуры в консольном приложении вводится строка, которая может содержать: знаки операций +,-,*,/; константы (целые или вещественные); скобки (); имена функций sin, cos, tg, ctg, exp; а также переменную x.
После проверки правильности формулы запрашивается значение переменной x, если переменная есть в формуле, и вычисляется результат.
</h3>
<h2>Алгоритм работы программы </h2>
<h3>
1. Из консоли считывается формула.
2. Проводится проверка наличия в строке символов (qwrfy), на которые будем заменять названия функций. Их не должно быть в исходной формуле.
3. В начале и в конце добавляются круглые скобки. Для удобства работы с унарными минусами и числами на концах формулы.
4. Все имена функций заменяются на более короткие (состоящие из 1 символа).
5. Унарные минусы заменяются на 0-.
6. Стираются все пробелы.
7. Проводится проверка на правильность расстановки скобок и лишние символы.
8. Из консоли считывается значение переменной х и вставляется в формулу.
9. Происходит разделение строки на числа и знаки операций: создаётся вектор объектов, которые имеют поля тип(число, операция или функция) и значение.
10. С помощью простого алгоритма получаем постфиксную запись нашей формулы :
    1. Создаём пустой стэк и пустой дэк.
    2. Идём по вектору слева направо, просматриваем каждый элемент.
    3. Если элемент число - сразу добавляем его в дэк.
    4. Если '(' - добавляем в стэк.
    5. Если знак: если его приоритет больше, чем приоритет верхнего в стеке, то добавляем его. иначе перемещаем все операторы из стека в дэк до скобки и в стек записываем наш.
    6. Если оператор функции(буква) - добавляем в стэк.
    7. Если ')' - перемещаем все операторы из стека в дэк до скобки, удаляем открывающую скобку из стэка.
    8. Вконце переписываем всё что осталось в стэке в дэк.
    9. Полученный дэк и есть искомая постфиксная запись.
11. Считаем наше постфиксное выражение:
    1. Создаём пустой стэк.
    2. В него пишем все числа.
    3. Если встретили знак(+-*/) - применяем его к двум верхним числам, удаляем их из стэка, пишем туда результат.
    4. Если встретили операцию функции(букву) - применяем её к двум верхнему числу, удаляем его из стэка, пишем туда результат.
    5. Элемент, оставшийся в стэке и будет искомым значением выражения.
12. Выводим результат в консоль.
</h3>

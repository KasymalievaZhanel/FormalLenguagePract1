# FormalLenguagePract1
Задание:

Даны α, буква x и натуральное число k. Вывести, есть ли в языке L слова, содержащие ровно k букв x.

Решение:
По мере обработки регулярного выражения в обратной польской записи, будем создавать массив expr для каждой его части, так, сначала мы создадим его для каждой буквы(or 1), а потом будем изменять, в зависимости от операций. Размер каждого массива k + 1, где expr[i] означает, можно ли вывести в данной части регулярного выражения ровно i букв x.
Таким образом, ответ содержится в expr[k] для всего регулярного выражения.
Рассмотрим алгоритм:

Если на вход подается буква a или 1:
a) a = x → можем получить только одну букву x.
b) a != x →не можем получить ни одной буквы x.
Итого совершено O(k) действий.

Reg1 + Reg2

Если складываются два регулярных выражения, то определенное количество символов x можно получить либо из Reg1, либо из Reg2. Значит, если хотя бы в одной из Reg1 или Reg2 выводится буквa x, то и в (Reg1 + Reg2) можно вывести букву x. Тогда expr_res[i] = expr1[i] | expr2[i]. Действий O(k).

Reg1.Reg2

Вывод n символов x из (Reg1.Reg2) происходит как вывод i символов x из Reg1 и (n - i) символов из Reg2. А значит необходимо для каждого n ∈ [0, k] перебрать количество букв x, выводимых из Reg1. Тогда, если в Reg1 выводится i букв x(т.е. expr1[i] = true), а из Reg2 выводится (n - i) букв x(т.е. expr2[n - i] = true), то expr_res[n] = true. Действий O(k^2).

Reg*

Так как итерация - это Σ(Reg^n), то expr_res =expr_res || expr_res*expr. Так как нас интересует тольно вывод  k символов x, то можно совершить k + 1 итераций.Так как совершаем не более k + 1 итерации, а на каждой итерации производим умножение и сложение регулярных выражений, которые работают суммарно за O(k^2), то общая асимптотика обработки составляет O(k^3).


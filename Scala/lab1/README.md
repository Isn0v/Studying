# Задача 1. "Калькулятор PROC"

4 балла (основная часть) + 1 балл (дополнительное задание)

## Основная часть (4 балла)

В компании RoutineTech разработали устройство под названием PROC
(PROstoy Calculator) -- программируемый калькулятор, который принимает
на вход последовательность команд, кодирующих процесс вычисления
некоторого целого числа, производит необходимые вычисления и печатает
конечный результат. Вам предлагается реализовать программную версию
данного устройства в качестве процедуры на языке программирования
Scala, в соответствии с описанием его кодирующих инструкций и принципа
работы.

### Описание калькулятора PROC

Калькулятор содержит регистры, предназначенные для хранения промежуточных
результатов вычислений и операндов арифметических команд, а именно:

- регистр `acc` -- аккумулятор, хранящий результат вычисления
  очередной арифметической команды;
- регистр `A`, в который записываются "левые" операнды бинарных операций;
- регистр `B`, в который записываются "правые" операнды бинарных операций;
- регистр `blink`, состоящий из одного бита, показывающего, в какой из набора
  регистров `{A, B}` следует произвести запись значения, закодированного
  специальными инструкциями. 

Регистры `acc`, `A`, `B` могут быть представлены программно в виде
целых чисел типа `Int`, регистр `blink` -- в виде значения типа `Boolean`.

Перед началом процесса декодирования инструкций и исполнения последовательности
команд, регистры `acc`, `A`, `B` содержат значение `0`, в регистр `blink` записан
нулевой бит.

Далее начинается процесс разбора команд и выполнения соответствующих
им действий.  Программно команды могут быть представлены в виде
значений типа `String`. Представлены следующие команды:

- `+`, записывает в регистр `acc` сумму значений в регистрах `A`, `B`, затем снимает бит в регистре `blink` (записывает в него нулевой бит);
- `-`, записывает в регистр `acc` разность значений в регистрах `A` и `B`, затем снимает бит в регистре `blink`;
- `*`, записывает в регистр `acc` произведение значений в регистрах `A` и `B`, затем снимает бит в регистре `blink`;
- `/`, записывает в регистр `acc` частное от деления значения регистра `A` на значение регистра `B`, затем снимает бит в регистре `blink`; в случае деления на `0` все регистры зануляются;
- `swap`, меняет содержимое регистров `A` и `B` местами;
- `blink`, меняет значение бита в регистре `blink` на противоположное;
- `acc`, записывает содержимое регистра `acc` в один из регистров `{A, B}`: в `A`, если в регистре `blink` выставлен бит `0`, в `B`, в обратном случае; затем меняет значение бита в регистре `blink` на противоположное;
- `X`, где `X` - произвольное целое число -- записывает число `X` в один из регистров `{A, B}`: в `A`, если в регистре `blink` выставлен бит `0`, в `B`, в обратном случае; затем меняет значение бита в регистре `blink` на противоположное.

После исполнения последней команды, калькулятор печатает содержимое регистра `acc`. Программно такое поведение может быть представлено записью `acc` в стандартный поток вывода.

### Рекомендации по выполнению задания

1. В директории с этим файлом лежит `calculator.scala`, в котором
   находится заготовка процедуры `calculator`. Эту процедуру требуется
   дополнить таким образом, чтобы она соответствовала условию задачи
   (выше).
2. Процедура `calculator` аннотирована `main` и имеет `commands:
   String*` в качестве параметра. Это означает, что процедура является
   точкой входа в программу; передаваемые в неё параметры являются
   строковым представлением команд, которые должен исполнить
   калькулятор.
3. Внутри `calculator` определена вспомогательная функция `parseInt`,
   которая переводит строку в значение типа `Int`. Эта функция может
   быть полезна при реализации поведения команды `X`. Некорректный
   ввод в таком случае обрабатывать необязательно, можно считать, что
   в программу будут передаваться только корректные данные.
4. Первая задача очень простая, и не требует наличия каких-то сложных
   средств для редактирования кода, компиляции и запуска программ;
   поэтому рекомендуется взять любой редактор с поддержкой синтаксиса
   Scala, [бинарное распространение версии
   3.3.3](https://github.com/scala/scala3/releases/tag/3.3.3),
   написать код и затем проверить решение, запустив его как скрипт
   (`scala calculator.scala arg1 arg2 arg3 ...` в вашей оболочке
   командной строки).
   
   

### Примеры

```bash
> scala calculator.scala 22 20 +
42
> scala calculator.scala 22 20 -
2
> scala calculator.scala 22 20 swap -
-2
> scala calculator.scala 20 20 + acc 2 +
42
> scala calculator.scala 20 20 + acc 2 /
20
> scala calculator.scala 20 2 *
40
> scala calculator.scala 20 0 /
0
scala calculator.scala blink 1 -
-1
```

## Дополнительное задание (1 балл)

Компания RoutineTech представила вторую версию своего калькулятора --
PROC mk. 2.  Новая версия отличается от предыдущей наличием новой
кодирующей инструкции -- команды `break`, которая прерывает процесс
вычислений, после чего печатает текущее содержимое регистра `acc`. Вам
предлагается поддержать эту команду в процедуре `calculator`,
используя механизм
['boundary/break'](https://www.scala-lang.org/api/3.3.0/scala/util/boundary$.html).

### Примеры

```bash
> scala calculator.scala break 1 2 + 3 4 +
0
> scala calculator.scala 1 2 + break acc 0 /
3
```

# Как я делал свою собственную брейн-ринг систему

### Disclaimer:
В этом репозитории будет больше слов и картинок, чем кода.

## Предыстория
Мы с друзьями любим играть в интеллектуальные игры (ЧГК, Свояк, Брэйн-Ринг) и порой посещаем очные турниры, где часто используют брейн-системы. К сожалению, порой мы даже боялись садиться за игровое место, не говоря уже о нажатии на игровую кнопку. Поэтому я решил сделать свою систему с кнопками и лампочками, чтобы играть в своем кругу и тренироваться.

## 1. Выбор платформы
Сперва в проекте задумывалось всего 3 кнопки (как в стандартной "Своей Игре" по телевизору), но позже было расширено до пяти. Исходя из этого, мне была необходима плата с шестью (5 игроков и кнопка старта) цифровым входами и 6 аналоговыми. Связываться с [ЛУТ](https://cxem.net/master/45.php) мне совершенно не хотелось, поэтому я решил остановиться на чем-то более простом и понятном. Например, на Arduino. По количеству портов и компактности мне приглянулась Arduino Nano. Вот распиновка платы: ![ArduinoNanoPinout](https://i.pinimg.com/originals/80/71/27/807127e3a4d875efdea4f912cd67b1b7.jpg)

## 2. Периферия
### Порты подключения
В качестве портов подключения (между кнопкой и корпусом системы) я сразу же рассматривал audio jack 3.5mm, так как предполагалось, что кнопки будут часто двигаться (ведь игроки деражт их в руках), а у jack есть фиксация контакта. Более того, на случай резкого выдергивания кнопки из корпуса системы больше подходил jack чем RJ-22 или RJ-45. Да и использовать RJ-45 для двухконтактного соединения мне показалось слишком жирным. Плюсом являлось и то, что на случай выхода из строя провода, его можно было бы купить в любом магазине бытовой техники. Также положительной стороной оказалось легкое крепление в корпус. Необходимо лишь сделать отверстие определенного диаметра и закрепить кольцом с обратной стороны![jack](https://olvit.by/image/cache/catalog/Razjemy/4ead83a14905c-500x500.jpg)
### Лампочки и кнопки...
..были выбраны самые простые. Так как к середине проекта я решил уложиться хотя бы в 3000₽, то выбирать антивандальные кнопки за 290₽-340₽ было нецелесообразно. По итогу кнопка стала выглядеть как-то так: ![Кнопка](images/button.jpg)
### Корпуса
Корпуса оказались самыми дорогими элементами в этом проекте. Корпус для системы вышел в 450₽, а для кнопки в 250₽. (при учете, что кнопок стало 5).
### Провода
Провода выбрал экранированные, двухжильные. Достаточно толстые.
### Схема подключения
(тут будет схема, а пока вот)![схема](images/scheme1.0.jpg)

## 3. Логика работы системы
Логика работы системы достаточно проста:
1. Система ожидает старта таймера.
2. Если таймер запущен, то происходит опрос кнопок.
3. Если кнопка нажата, то таймер останавливается, и зажигается лампочка.

## 4. Реализация
Конечно же, реализовывать систему я начал постепенно. Сперва спаял одну кнопку и проверил код, потом втору, потом третью. Но представим, что уже все подключено.    

Переменная `timeLimit` определяет ограничение по времени (в мсек) на один вопрос. Сейчас это 30 секунд.
```cpp
int timeLimit = 30000;
```

`delayForLED` определяет частоту моргания (в мсек) светодиодов при включении.
```cpp
int delayForLED = 20; 
```

Функция `startTimer` запускает таймер.
```cpp
void startTimer()
{
  timerStarted = true;
  turnOffLights();
  analogWrite(ledMonitor, 255);
  Serial.println("status:timer_started");
}
```

Функция `stopTimer` останавливает таймер.
```cpp
void stopTimer()
{
  timerStarted = false;
  analogWrite(ledMonitor, 0);
  Serial.println("status:timer_stopped");
} 
```

Функция `checkButtons` проверяет нажатие каждой из кнопок.
```cpp
void checkButtons()
{
  if (digitalRead(btnOne))
  {
    stopTimer();
    analogWrite(ledOne, 255);
    ...
  }
  ...
  else if (digitalRead(btnFive))
  {
    stopTimer();
    analogWrite(ledTwo, 255);
    ...
  }
}
```
Полную версию кода можно посмотреть в файле [arduino-code.ino](https://github.com/ph1l74/my-own-private-brainringsystem/blob/master/arduino-code.ino);

## 5. Результат
![working](images/inprocess.jpg)
После пары уикендов пайки и программирования система полностью заработала. Видео тестового запуска можно посмотреть [тут](https://twitter.com/ph1l74/status/1098666316205035520).

## 6. Плюсы и минусы системы
Из плюсов: 
* компактность
* простота реализации
* эргономика
* дешевизна
* питание от батарейки, по USB или сети 220В.

Из минусов: 
* при питании от сети с нестабильным напряжением (в электричке) наблюдается некорректная работа системы
* отсутствие множества режимов

## 7. Предполагаемые доработки
- [ ] Добавление режимов (фальстарты)
- [ ] Добавление динамика для обозначения нажатия
- [ ] Добавление автономного источника питания (батарейки с автозарядкой, напирмер литий-ионных аккумуляторов)
- [ ] Добавление многопоточности
- [ ] Добавление визуального интерфейса при подключении к компьютеру

# Home-AVR-Clock

Напоминаю, что в качестве примера у нас выбран популярный AVR микроконтроллер Atmega8, а в качестве основного языка программирования – Си.
Однако приступим к делу:

И начнём мы с программирования портов ввода-вывода микроконтроллера.

1. Регистр выбора направления передачи данных DDR

Выводы (порты) микроконтроллера могут работать как входы и как выходы.
Ещё один пример с 8-разрядным портом D:
DDRD = 0b10001000;

Перепишем наши примеры с шестнадцатеричными числами:
DDRC = 0x01;
DDRD = 0x88;

Для того, чтобы нам настроить PC0 как выход, в этом случае следует записать следующую команду:
DDRC |= ( 1 << 0 );

А вот, если бы нам туда понадобилось прописать ноль, т. е. настроить PC0 как вход, то команда выглядела бы так:
DDRC &= ~( 1 << 0 );

Запишем в побитовой форме и второй пример – настроим третий и седьмой биты порта D как выходы:
DDRD |= ( 1 << 3 );
DDRD |= ( 1 << 7 );

Эти две команды можно заменить одной:
DDRD |= ( 1 << 3 )|( 1 << 7 );


2. Регистр выходных данных порта PORT

Служит для управления состоянием вывода.
Воспользуемся предыдущими примером, в котором мы установили вывод PC0 как выход, т. е. использовали команду:
DDRC = 0b0000001;

Тогда, чтобы установить на этом выходе высокий логический уровень, нам надо прописать:
PORTС = 0b0000001; – в двоичном коде, либо
PORTС = 0x01; – в 16-ричном, либо
PORTC |= (1 << PC0); – в побитовом

А для того, чтобы установить низкий уровень –
PORTС = 0b0000000; – в двоичном коде, либо
PORTС = 0x00; – в 16-ричном, либо
PORTC &= ~(1 << PC0); – в побитовом

Если мы введём:
PORTС = 0b0000101; – в двоичном коде, либо
PORTС = 0x05; – в 16-ричном, либо
PORTC |= (1 << PC0)|( 1 << PC2 ); – в побитовом,

Для некоторых приложений может оказаться полезной команда, которая переключает отдельный бит в противоположное состояние, т. е. единицу в ноль и наоборот. :
PORTD ^= (1 << 3);


3. Регистр считывания состояния вывода PIN

Данный регистр непрерывно отражает текущее состояние выводов порта, причём независимо от того, используется вывод как вход или как выход.
Давайте посмотрим, как можно считывать информацию из регистра PIN на примере оператора if.
if (PINB & (1 << PINB1)) {какой-либо код}

ожидает появления на выводе PB1 высокого уровня (единицы).

А вот команда:
if (!(PINB & (1<<PINB1))) {какой-либо код}

ожидает появления на выводе PB1 низкого уровня (нуля).

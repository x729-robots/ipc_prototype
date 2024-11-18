# Архитектура системного уровня ПО блока

## Описание
Программный комплекс состоит из нескольких процессов, приведённых ниже. Данные процессы запускаются на выполнение каждый из своего файла соответственно. В составе каждого процесса исполняется один или более потоков с различными политиками поанирования, описываемыми ниже по тексту. Биение на процессы в некоторой степени обеспечивает независимость работы одного процесса от другого, что повышает работоспособность процессов по отдельности. Биение на процесс см. п.п. "Описание процессов". В то же время непосредственное исполнение программных функций и взаимодействие между процессами осуществляестя именно на уровне потоков, в том числе потоков находящися в разных процессах. Поэтому в п. "Описание потоков" приведено укрупнённое описание архитектуры всех потоков и используемых IPC.

## Описание процессов
Процессы 2 и 3 представляют из себя прототипы процессов для управления транспортным средством на целевом вычислителе с многоядерным процессором архитектуры Arm64. 

Процессы 1, 4, 5 необходимы для демонстрационных целей и отладки.

Более подробное описание каждого процесса приведено ниже:
1. Процесс 1 необходим для демострационного ввода-вывода данных в комплекс с целью обмена данными с процессом 4 (CANopen test slave process) и для отладки, например для возможности анализа характеристик реального времени потоков реального времени процесса 2 (Ведущий процесс).
1. Процесс 2 является прототипом процесса, выполняющего функции:
    - исполнения алгоритмов управления с фиксированной периодичностью управления по данным полученным извне, зараннее определённой в конфигурационном файле
    - ведущего REALTIME-процесса, т.е. процесса, генерирующего синхронизационные "сигналы" REALTIME-процессам комплекса (в данном "сигнал" посредством механизма условной переменной передаётся в процесс 3)
    Процесс 2 имеет в своём составе как минимум 1 Realtime-поток.
1. Процесс 3 - это прототип процесса CANopen мастера, обеспечивающего ввод/вывод данных процесса 2 по протоколу CANopen с внешних интерфейсов CAN или UDP.
Процесс 3 имеет в своём составе как минимум 1 Realtime-поток, выполняющий C-функции библиотеки CANopen циклически в реальном времени.
1. Процесс 4 представляет из программу, реализующую простой тестовый слейв CANopen, взаимодействующий с CANopen мастером через CAN/UDP.
1. Процесс 5 необходим для отладки, например для возможности анализа характеристик реального времени потоков реального времени процесса 3 (CANopen мастер). 

![](OS_Processes_Arch.png)

## Описание потоков

Realtime-потоки процессов 2 и 3 вместе с внешими процессами/устройствами, подключенным к CAN/VCAN шине или Ethernet/Localhost образуют контур управления с периодичностью, указываемой в конфигурационном файле. 

![](Thread_Arch.png)

Ниже приведена временная диаграмма, описывающая то, как Realtime-потоки должны быть синхронизированы во времени.
TODO
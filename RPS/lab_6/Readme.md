## [Задание][0]

---

### Описание программы 'Messages'

Реализовано:
* Передача сообщений между несколькими пользователями.

---

### Описание программы 'Billing' (дополнительное задание)

Модифицированная версия программы **Messages**. 

Добавлено:
* Баланс у каждого телефона (может уходить в минус).
**Start balance: 50** 
* Списание средств с баланса отправителя при отправке SMS.
**Price: 10** 
* Возможность посмотреть баланс.
**Command: \*100#**

---

### Компиляция и запуск 

**Важно:** 
* Компиляция и запуск одинаковы для обеих программ.
* После запуска сервера и телефонов, варианты действий будут отображаться на экране.

#### Сервер и телефоны на одном компьютере

1. Скопировать все файлы (*Cell.idl*, *StationServer.java*, *Tube.java*) в рабочую директорию.
2. Открыть один терминал для сервера и, как минимум, два для телефонов.
3. В каждом терминале последовательно ввести команды:

```bash
$ idlj -fall Cell.idl
$ javac Cell/*.java
$ javac StationServer.java
$ javac Tube.java
```

Короче:

```bash
$ idlj -fall Cell.idl && javac Cell/*.java && javac StationServer.java && javac Tube.java
```

4. В терминале, который играет роль сервера, последовательно ввести команды:

```bash
$ orbd -ORBInitialPort 1050 -ORBInitialHost localhost &
$ java StationServer -ORBInitialPort 1050 -ORBInitialHost localhost
```

**Важно:** при запуске первой команды возможны следующие результаты:

* Появится много предупреждений и вёрнется управление консолью.
* Появится сообщение вроде `[1] 12521`.
    * В этих двух случаях делать ничего не нужно. Просто запускаем вторую команду `java StationServer ...`.
* Появится много предупреждений и управление консолью не вёрнется.
    * В данном случае нажимаем `Ctrl + C` и запускаем вторую команду `java StationServer ...`.



5. В каждом терминале, который играет роль телефона, ввести команду:

```bash
$ java Tube -ORBInitialPort 1050 -ORBInitialHost <server_IP>
```

**server_IP** - IP адрес сервера, к которому вы подключаетесь. В данном случае - **localhost**.

---

#### Сервер и телефоны на разных компьютерах

1. Скопировать все файлы (*Cell.idl*, *StationServer.java*, *Tube.java*) в рабочую директорию на каждом ПК.
2. Определиться, какой ПК будет играть роль сервера, а какие (минимум два) - телефонов.
2. На каждом ПК открыть терминал и последовательно ввести команды:

```bash
$ idlj -fall Cell.idl
$ javac Cell/*.java
$ javac StationServer.java
$ javac Tube.java
```

Короче:

```bash
$ idlj -fall Cell.idl && javac Cell/*.java && javac StationServer.java && javac Tube.java
```

4. В терминале ПК, который играет роль сервера, последовательно ввести команды:

```bash
$ orbd -ORBInitialPort 1050 -ORBInitialHost localhost &
$ java StationServer -ORBInitialPort 1050 -ORBInitialHost localhost
```

**Варианты результатов при запуске команды `orbd -ORBInitialPort 1050...` см. выше.**

5. В терминалах ПК, которые играют роль телефонов, ввести команду:

```bash
$ java Tube -ORBInitialPort 1050 -ORBInitialHost <server_IP>
```

**server_IP** - IP адрес сервера, к которому вы подключаетесь. 

**Как узнать server_IP**:

1. Открываем второй терминал на ПК-сервере и вводим команду `ifconfig`.
2. В качестве *server_IP* указываем IP адрес из верхней строки `linet addr`.

[0]: http://fedoruk.comcor.ru/Dev_bach/java+corba.html
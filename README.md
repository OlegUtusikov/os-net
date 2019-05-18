## Знакомство с сокетами

---

### POP3 server

Постарался имплементировать POP3 server в согласовании с [rfc][link].

#### Команды для ввода в клиент:

Для теста в локальной базе данных сохранён пользователь с login: test, password: test. 

###### Авторизация:
* USER login
* PASS password

###### После авторизации:
* STAT  - количество и суммарный размер сообщений пользователя.
* LIST [index_of_message] - список размеров каждого сообщения или конкретного.
* RETR index_of_message - текст конкретного сообщения.
* DELE index_of_message - удалить сообщение.
* NOOP - ничего не делает.
* RSET - удаляет предыдущие команды.

#### Сборка и запуск:
make - собрать.
make runServer - запустить сервер.
make runClient - запустить клиент.
make clean - очистить.

@ OlegUtusikov

PS: приветствуется поиск багов и ошибок).

[link]: https://rfc2.ru/1939.rfc

DROP TABLE IF EXISTS ПРЕПОДАВАТЕЛЬ;
DROP TABLE IF EXISTS ПРЕДМЕТ;
DROP TABLE IF EXISTS СТУДЕНЧЕСКАЯ_ГРУППА;
DROP TABLE IF EXISTS ПРЕПОДАВАТЕЛЬ_ПРЕПОДАЕТ_ПРЕДМЕТЫ_В_ГРУППАХ;


CREATE TABLE ПРЕПОДАВАТЕЛЬ
(
    ЛичныйНомер VARCHAR(10) PRIMARY KEY,
    Фамилия VARCHAR(20) NOT NULL,
    Должность VARCHAR(20) NOT NULL,
    Кафедра VARCHAR(10) NOT NULL,
    Специальность VARCHAR(30) NOT NULL,
    ТелефонДомашний SMALLINT UNSIGNED NOT NULL
);

CREATE TABLE ПРЕДМЕТ
(
    КодовыйНомерПредмета VARCHAR(10) PRIMARY KEY,
    НазваниеПредмета VARCHAR(20) NOT NULL,
    КоличествоЧасов SMALLINT UNSIGNED NOT NULL,
    Специальность VARCHAR(30) NOT NULL,
    Семестр TINYINT UNSIGNED NOT NULL
);

CREATE TABLE СТУДЕНЧЕСКАЯ_ГРУППА
(
    КодовыйНомерГруппы VARCHAR(10) PRIMARY KEY,
    НазваниеГруппы VARCHAR(10) NOT NULL,
    КоличествоЧеловек TINYINT UNSIGNED NOT NULL,
    Специальность VARCHAR(30) NOT NULL,
    ФамилияСтаросты VARCHAR(20) NOT NULL
);

CREATE TABLE ПРЕПОДАВАТЕЛЬ_ПРЕПОДАЕТ_ПРЕДМЕТЫ_В_ГРУППАХ
(
    КодовыйНомерГруппы VARCHAR(10) NOT NULL,
    КодовыйНомерПредмета VARCHAR(10) NOT NULL,
    ЛичныйНомер VARCHAR(10) NOT NULL,
    НомерАудитории SMALLINT UNSIGNED NOT NULL
);
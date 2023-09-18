-- 4
/*Получить все отправки, где количество находится
 в диапазоне от 300 до 750 включительно.*/
SELECT * 
FROM количестводеталей
WHERE S BETWEEN 300 AND 750;

-- 13*
/*Получить номера проектов, обеспечиваемых по крайней мере 
одним поставщиком не из того же города.*/
SELECT DISTINCT d_count.ПР 
FROM КоличествоДеталей AS d_count
INNER JOIN ПроектыJ AS pr ON pr.ПР = d_count.ПР 
INNER JOIN ПоставщикиS AS s ON s.П = d_count.П 
WHERE pr.Город != s.Город;

-- 16
/*Получить общее количество деталей Д1, поставляемых поставщиком П1.*/
SELECT sum(S)
FROM количестводеталей
WHERE Д = 'Д1' AND П = 'П1';

-- 17
/*Для каждой детали, поставляемой для проекта, получить номер детали, 
номер проекта и соответствующее общее количество.*/
SELECT Д, ПР, sum(S)
FROM КоличествоДеталей
GROUP BY Д, ПР
ORDER BY Д, ПР;

-- 20
/*Получить цвета деталей, поставляемых поставщиком П1.*/
SELECT DISTINCT d.Цвет 
FROM ДеталиP AS d
INNER JOIN КоличествоДеталей AS d_count ON d.Д = d_count.Д
WHERE d_count.П = 'П1';

-- 21
/*Получить номера деталей, поставляемых для какого-либо проекта в Лондоне*/
SELECT DISTINCT d_count.Д
FROM КоличествоДеталей AS d_count
INNER JOIN ПроектыJ AS pr ON pr.ПР = d_count.ПР
WHERE pr.Город = 'Псков';

-- 22 
/*. Получить номера проектов, использующих по крайней мере одну деталь,
 имеющуюся у поставщика П1*/
SELECT pr.ПР
FROM ПроектыJ AS pr
INNER JOIN КоличествоДеталей AS d_count ON pr.ПР = d_count.ПР
WHERE d_count.П = 'П1';

-- 26
/*Получить номера проектов, для которых среднее количество
 поставляемых деталей Д1 больше,
чем наибольшее количество любых деталей, поставляемых для проекта ПР1.*/

SELECT ПР
FROM КоличествоДеталей
WHERE Д = 'Д1'
GROUP BY ПР
HAVING avg(S) > (
    SELECT max(S) as pr1
    FROM КоличествоДеталей
    WHERE ПР = 'ПР1'
)

-- 28
WITH details AS (
    SELECT Д 
    FROM ДеталиP 
    WHERE Город = 'Москва' AND Цвет = 'Красный'
),
projest_with_details AS (
    SELECT d_count.ПР
    FROM КоличествоДеталей AS d_count
    WHERE d_count.Д in (SELECT * FROM details)
)

SELECT DISTINCT ПР 
FROM КоличествоДеталей
WHERE ПР NOT IN (SELECT * FROM projest_with_details);

-- 34 
/*Получить номера деталей, поставляемых либо лондонским поставщиком, 
либо для лондонского проекта*/
SELECT d_count.Д 
FROM КоличествоДеталей AS d_count
INNER JOIN ПоставщикиS AS s ON s.П = d_count.П
INNER JOIN ПроектыJ AS pr ON pr.ПР = d_count.ПР
WHERE s.Город = 'Москва' OR pr.Город = 'Москва';
//Удалить все связные ноды:
match (n)-[r]-() DELETE n,r

//Удалить все не связаные ноды
MATCH (n)
DELETE (n)

//Найти все страны
MATCH (country:Country)
RETURN country

//Найти игроков, играющих на позиции нападающего
MATCH (player:Player)-[:HAS_POSITION]->(:Position{name: "Striker"})
RETURN player

//Найти позиции, на которых играет игрок с именем "Virgil van Dijk"
MATCH (player:Player{name: "Virgil van Dijk"})-[:HAS_POSITION]->(position:Position)
RETURN position

//Вывести игроков, играющих в клубе Барселона или Реал Мадрид
MATCH (club:FootballClub)-[:HAS_PLAYER]->(player:Player)
WHERE club.name IN ["Barcelona", "Real Madrid"]
RETURN player

//Вывести игроков, играющих за сборную Бразилии
MATCH (country:Country)-[:HAS_PLAYER]->(player:Player)
WHERE country.name = "Brazil"
RETURN player

//Вывести все футбольные клубы Испании
MATCH (country:Country{name: "Spain"})-[:HAS_CLUB]->(club:FootballClub)
RETURN club

//Вывести всех футболистов в возрастном ограничении [23, 30]
MATCH (player:Player)
WHERE player.age >= 23 AND player.age <= 30
RETURN player

//Вывести самого возрастного игрока из Барселоны
MATCH (barcelona:FootballClub {name: "Barcelona"})-[:HAS_PLAYER]->(player:Player)
RETURN player
ORDER BY player.age DESC
LIMIT 1

//Вывести средний возраст игроков из Хорватии
MATCH (croatia:Country {name: "Croatia"})-[:HAS_PLAYER]->(player:Player)
RETURN avg(player.age) AS average_age

//Вывести клуб, у которого больше всего трофеев
MATCH (club:FootballClub)
RETURN club.name, club.trophy_count
ORDER BY club.trophy_count DESC
LIMIT 1
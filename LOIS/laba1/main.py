'''
Лабораторная работа №1
по дисциплине ЛОИС
Выполнена студентами группы 121703
Тарбая Данила Игоревич, Терлеев Алексей Сергеевич, Якимович Илья Викторович
Вариант 21:
Реализовать прямой нечеткий логический вывод используя импликацию Геделя
'''


from src import operations
from src.data_loader import load_from_file
from src.utils import print_table


def main():
    facts, functions = load_from_file("data")

    function_tables, function_tables_titles = {}, []
    for function_head, function_obj in functions.items():
        function_tables_titles.append(function_obj.head)
        first_set_name, second_set_name = function_obj.tail_without_variables
        first_set, second_set = facts[first_set_name], facts[second_set_name]
        function_tables[function_head] = operations.matrix_impl(first_set.tail, second_set.tail)

    for table_title, table_tail in zip(function_tables_titles, function_tables.values()):
        print_table(table_title, table_tail)

    result = []

    for table_title, function_table in zip(function_tables_titles, function_tables.values()):
        for fact in facts.values():
            try:
                tmp = operations.built_impl_table(fact.tail, function_table)
                print_table(f"{table_title}/~\{fact.head}", tmp)
                result.append(operations.compress(tmp))
            except ValueError:
                ...
    
    result_str = [", ".join(f"({pair[0]}, {pair[1]})" for pair in conclusion_set.items()) for conclusion_set in result]
    print("Ответ: {", "}, {".join(result_str), "}.", sep ="")


if __name__ == "__main__":
    main()

# Вывод всех возможных формул
# Отчет (проверить нормализованный и ненормализованный ввод (пары до и после импликации))
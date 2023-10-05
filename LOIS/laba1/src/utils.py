from prettytable import PrettyTable


def print_table(name, table):
    pretty_table = PrettyTable()
    rows_names = list(table.keys())
    cols_names = [name, *list(table[rows_names[0]].keys())]
    pretty_table.field_names = cols_names
    for row_name in rows_names:
        pretty_table.add_row([row_name, *table[row_name].values()])
    print(pretty_table)
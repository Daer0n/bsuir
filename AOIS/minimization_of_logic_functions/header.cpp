//
// Created by Daer0n
//
#include "header.h"

TruthTable::TruthTable()
{
    this->table[0].a = 0;
    this->table[0].b = 0;
    this->table[0].c = 0;

    this->table[1].a = 0;
    this->table[1].b = 0;
    this->table[1].c = 1;

    this->table[2].a = 0;
    this->table[2].b = 1;
    this->table[2].c = 1;

    this->table[3].a = 0;
    this->table[3].b = 1;
    this->table[3].c = 0;

    this->table[4].a = 1;
    this->table[4].b = 0;
    this->table[4].c = 0;

    this->table[5].a = 1;
    this->table[5].b = 0;
    this->table[5].c = 1;

    this->table[6].a = 1;
    this->table[6].b = 1;
    this->table[6].c = 1;

    this->table[7].a = 1;
    this->table[7].b = 1;
    this->table[7].c = 0;
}


void TruthTable::push_char(Stack*& top, char info)
{
    Stack* new_element = new Stack;
    new_element->next = top;
    new_element->info = info;
    top = new_element;
}

void TruthTable::push_bool(Stack*& top, bool info)
{
    Stack* new_element = new Stack;
    new_element->next = top;
    new_element->info = info;
    top = new_element;
}

void TruthTable::pop_char(Stack*& top, char* info)
{
    Stack* temp_pointer = top;
    *info = top->info;
    top = top->next;
    delete temp_pointer;

}

void TruthTable::pop_bool(Stack*& top, bool* info)
{
    Stack* temp_pointer = top;
    *info = top->info;
    top = top->next;
    delete temp_pointer;
}

int TruthTable::prior(char oper)
{
    switch (oper)
    {
    case '(':
        return 1;
    case '+':
        return 2;
    case '*':
        return 3;
    case '!':
        return 4;
    default:
        return 0;
    }
}

std::string TruthTable::translate_to_opz(std::string expression)
{
    std::string result;
    Stack* top = NULL;
    char element;

    for (size_t i = 0; i < expression.size(); i++) {

        if (expression[i] == '(')
            push_char(top, expression[i]);

        else if (expression[i] == ')') {
            while (top->info != '(') {
                pop_char(top, &element);
                result += element;
            }
            pop_char(top, &element);
        }

        else if (expression[i] >= 'a' and expression[i] <= 'c')
            result += expression[i];

        else if (expression[i] == '*' or expression[i] == '+' or expression[i] == '!') {
            while (top != NULL and prior(top->info) >= prior(expression[i])) {
                pop_char(top, &element);
                result += element;
            }
            push_char(top, expression[i]);
        }
    }

    while (top != NULL) {
        pop_char(top, &element);
        result += element;
    }

    return result;
}

bool TruthTable::truth_table(std::string expression, bool a, bool b, bool c)
{
    Stack* top = NULL;
    bool first, second, result;
    expression = translate_to_opz(expression);

    for (size_t i = 0; i < expression.size(); i++) {
        switch (expression[i])
        {
        case 'a':
            push_bool(top, a);
            break;
        case 'b':
            push_bool(top, b);
            break;
        case 'c':
            push_bool(top, c);
            break;
        case '+': {
            pop_bool(top, &first);
            pop_bool(top, &second);
            result = first | second;
            push_bool(top, result);
            break;
        }
        case '*': {
            pop_bool(top, &first);
            pop_bool(top, &second);
            result = first & second;
            push_bool(top, result);
            break;
        }
        case '!': {
            pop_bool(top, &first);
            result = !first;
            push_bool(top, result);
            break;
        }
        }
    }

    return result;
}

void TruthTable::run_truth_table(std::string expression)
{
    for (size_t i = 0; i < SIZE; i++)
        this->table[i].result = this->truth_table(expression, this->table[i].a, this->table[i].b, this->table[i].c);
}

void TruthTable::print(std::string expression)
{
    std::cout << expression << "\n";
}

void TruthTable::print_table()
{
    std::cout << "\n                       Truth table";
    std::cout << "\n" << "---------------------------------------------------------\n";
    std::cout << "\t" << "|  1  " << "|  2  "
        << "|  3  " << "|  4  "
        << "|  5  " << "|  6  "
        << "|  7  " << "|  8  |\n";
    std::cout << "---------------------------------------------------------\n" << "  a\t";

    for (size_t i = 0; i < SIZE; i++)
        std::cout << "|  " << this->table[i].a << "  ";
    std::cout << "|\n" << "---------------------------------------------------------\n" << "  b\t";
    for (size_t i = 0; i < SIZE; i++)
        std::cout << "|  " << this->table[i].b << "  ";
    std::cout << "|\n" << "---------------------------------------------------------\n" << "  c\t";
    for (size_t i = 0; i < SIZE; i++)
        std::cout << "|  " << this->table[i].c << "  ";
    std::cout << "|\n" << "---------------------------------------------------------\n" << "  res\t";
    for (size_t i = 0; i < SIZE; i++)
        std::cout << "|  " << this->table[i].result << "  ";
    std::cout << "|\n" << "---------------------------------------------------------\n\n";
}

std::vector<std::vector<int>> TruthTable::gluing(bool sign)
{
    std::vector<std::vector<int>> table;

    for (int i = 0; i < SIZE; i++) {
        for (int j = i + 1; j < SIZE; j++) {
            if (this->table[i].result == sign and this->table[j].result == sign) {
                std::vector<int> table_element;

                if (this->table[i].a == this->table[j].a and this->table[i].b == this->table[j].b) {
                    table_element.push_back(this->table[i].a);
                    table_element.push_back(this->table[i].b);
                    table_element.push_back(-1);
                    table.push_back(table_element);
                    this->table[i].visit = true;
                    this->table[j].visit = true;
                }
                else if (this->table[i].a == this->table[j].a and this->table[i].c == this->table[j].c) {
                    table_element.push_back(this->table[i].a);
                    table_element.push_back(-1);
                    table_element.push_back(this->table[i].c);
                    table.push_back(table_element);
                    this->table[i].visit = true;
                    this->table[j].visit = true;
                }
                else if (this->table[i].b == this->table[j].b and this->table[i].c == this->table[j].c) {
                    table_element.push_back(-1);
                    table_element.push_back(this->table[i].b);
                    table_element.push_back(this->table[i].c);
                    table.push_back(table_element);
                    this->table[i].visit = true;
                    this->table[j].visit = true;
                }
            }
        }
    }
    if (table.empty()) {
        for (size_t i = 0; i < SIZE; i++) {
            if (this->table[i].result == sign) {
                std::vector<int> table_element;

                if (this->table[i].a == 1 or this->table[i].a == 0)
                    table_element.push_back(this->table[i].a);
                else
                    table_element.push_back(-1);
                if (this->table[i].b == 1 or this->table[i].b == 0)
                    table_element.push_back(this->table[i].b);
                else
                    table_element.push_back(-1);
                if (this->table[i].c == 1 or this->table[i].c == 0)
                    table_element.push_back(this->table[i].c);
                else
                    table_element.push_back(-1);

                table.push_back(table_element);

            }
        }
    }

    return table;
}

std::vector<std::vector<int>> TruthTable::regluing(std::vector<std::vector<int>> table, bool sign)
{
    std::vector<std::vector<int>> regluing_table;

    for (int i = 0; i < table.size(); i++) {
        for (int j = i + 1; j < table.size(); j++) {
            std::vector<int> table_element;

            if (table[i][0] == table[j][0] and table[i][0] != -1 and (table[i][1] == table[j][1] or table[i][2] == table[j][2])) {
                table_element.push_back(table[i][0]);
                table_element.push_back(-1);
                table_element.push_back(-1);
            }
            else if (table[i][1] == table[j][1] and table[i][1] != -1 and (table[i][0] == table[j][0] or table[i][2] == table[j][2])) {
                table_element.push_back(-1);
                table_element.push_back(table[i][1]);
                table_element.push_back(-1);
            }
            else if (table[i][2] == table[j][2] and table[i][2] != -1 and (table[i][0] == table[j][0] or table[i][1] == table[j][1])) {
                table_element.push_back(-1);
                table_element.push_back(-1);
                table_element.push_back(table[i][2]);
            }

            if (!table_element.empty())
                regluing_table.push_back(table_element);
        }
    }

    remove(regluing_table);

    return regluing_table;
}

void TruthTable::remove(std::vector<std::vector<int>>& table)
{
    auto end = table.end();

    for (auto it = table.begin(); it != end; ++it) 
        end = std::remove(it + 1, end, *it);

    table.erase(end, table.end());

    for (size_t i = 0; i < table.size(); i++) 
        if (table[i][0] == -1 and table[i][1] == -1 and table[i][2] == -1)
            table.erase(table.begin() + i);
}

std::string TruthTable::create_short_form(std::vector<std::vector<int>> table, bool sign)
{
    std::string short_expression;

    if (sign) {
        for (size_t i = 0; i < table.size(); i++) {
            short_expression += "(";

            if (table[i][0] == 1) 
                short_expression += "a*";
            else if (table[i][0] == 0) 
                short_expression += "!a*";
            if (table[i][1] == 1) 
                short_expression += "b*";
            else if (table[i][1] == 0) 
                short_expression += "!b*";
            if (table[i][2] == 1) 
                short_expression += "c*";
            else if (table[i][2] == 0) 
                short_expression += "!c*";

            short_expression.erase(short_expression.size() - 1);
            short_expression += ")+";
        }
    }
    else {
        for (size_t i = 0; i < table.size(); i++) {
            short_expression += "(";

            if (table[i][0] == 1) 
                short_expression += "!a+";
            else if (table[i][0] == 0) 
                short_expression += "a+";
            if (table[i][1] == 1) 
                short_expression += "!b+";
            else if (table[i][1] == 0) 
                short_expression += "b+";
            if (table[i][2] == 1) 
                short_expression += "!c+";
            else if (table[i][2] == 0) 
                short_expression += "c+";

            short_expression.erase(short_expression.size() - 1);
            short_expression += ")*";
        }
    }

    if(!short_expression.empty())
        short_expression.erase(short_expression.size() - 1);

    return short_expression;
}

std::string TruthTable::calculation_method(bool sign)
{
    std::vector<std::vector<int>> table = gluing(sign);
    std::vector<std::vector<int>> regluing_table = regluing(table, sign);

    for (size_t i = 0; i < regluing_table.size(); i++) 
        table.push_back(regluing_table[i]);

    if (table.size() == 1)
        return create_short_form(table, sign);

    std::vector<std::vector<int>> finish_table = getting_rid_extra_implicant(table, sign);

    for (int i = 0; i < SIZE; i++) 
        if (this->table[i].result == sign and !this->table[i].visit) 
            table.push_back(check_unvisited(i));

    if (finish_table.empty()) 
        finish_table = regluing(table, sign);
    else 
        finish_table = getting_rid_extra_implicant(table, sign);

    return create_short_form(finish_table, sign);
}

std::vector<int> TruthTable::check_unvisited(int ind)
{
    bool visit_a, visit_b, visit_c;
    std::vector<int> table_element;

    for (size_t i = 0; i < SIZE; i++) {
        if (i = ind)
            continue;
        if (this->table[i].a == this->table[ind].a)
            visit_a = true;
        if (this->table[i].b == this->table[ind].b)
            visit_b = true;
        if (this->table[i].c == this->table[ind].c)
            visit_c = true;
    }

    if(!visit_a)
        table_element.push_back(this->table[ind].a);
    else 
        table_element.push_back(-1);
    if (!visit_b)
        table_element.push_back(this->table[ind].b);
    else
        table_element.push_back(-1);
    if (!visit_c)
        table_element.push_back(this->table[ind].c);
    else
        table_element.push_back(-1);

    return table_element;
}


std::vector<std::vector<int>> TruthTable::getting_rid_extra_implicant(std::vector<std::vector<int>> table, bool sign)
{
    std::string deadlock_form;
    std::vector<std::vector<int>> finish_table;

    for (size_t i = 0; i < table.size(); i++) {
        bool res1, res2;

        if (table[i][0] == -1 and table[i][1] == -1) {
            res1 = true;
            res2 = false;
        }
        else if (table[i][0] == -1 and table[i][2] == -1) {
            res1 = true;
            res2 = false;
        }
        else if (table[i][1] == -1 and table[i][2] == -1) {
            res1 = true;
            res2 = false;
        }
        else if (table[i][0] == -1) {
            std::vector<std::vector<int>> buf_table = gluing(sign);

            buf_table.erase(buf_table.begin() + i);
            deadlock_form = create_short_form(buf_table, sign);
            res1 = truth_table(deadlock_form, 1, table[i][1], table[i][2]);
            res2 = truth_table(deadlock_form, 0, table[i][1], table[i][2]);
        }
        else if (table[i][1] == -1) {
            std::vector<std::vector<int>> buf_table = gluing(sign);

            buf_table.erase(buf_table.begin() + i);
            deadlock_form = create_short_form(buf_table, sign);
            res1 = truth_table(deadlock_form, table[i][0], 1, table[i][2]);
            res2 = truth_table(deadlock_form, table[i][0], 0, table[i][2]);
        }
        else if (table[i][2] == -1) {
            std::vector<std::vector<int>> buf_table = gluing(sign);

            buf_table.erase(buf_table.begin() + i);
            deadlock_form = create_short_form(buf_table, sign);
            res1 = truth_table(deadlock_form, table[i][0], table[i][1], 1);
            res2 = truth_table(deadlock_form, table[i][0], table[i][1], 0);
        }
        if (res1 != res2) {
            std::vector<int> implicant;

            implicant.push_back(table[i][0]);
            implicant.push_back(table[i][1]);
            implicant.push_back(table[i][2]);
            finish_table.push_back(implicant);
        }
    }

    return finish_table;
}

std::vector<std::vector<int>> TruthTable::create_constituents(bool sign)
{
    std::vector<std::vector<int>> constituents;

    for (size_t i = 0; i < SIZE; i++) {
        if (this->table[i].result == sign) {
            std::vector<int> elements_of_table;

            elements_of_table.push_back(this->table[i].a);
            elements_of_table.push_back(this->table[i].b);
            elements_of_table.push_back(this->table[i].c);;
            constituents.push_back(elements_of_table);
        }
    }
    return constituents;
}

std::string TruthTable::tabular_method(bool sign)
{
    std::vector<std::vector<int>> implicants = gluing(sign);
    std::vector<std::vector<int>> regluing_implicants = regluing(implicants, sign);
    std::vector<std::vector<int>> constituents = create_constituents(sign);
    std::vector<std::vector<int>> table, short_table;
    std::vector<int> large_amount, implicant_index;

    implicants.insert(implicants.end(), regluing_implicants.begin(), regluing_implicants.end());

    for (size_t j = 0; j < implicants.size(); j++) {
        std::vector<int> table_element;

        for (size_t i = 0; i < constituents.size(); i++) {
            if ((implicants[j][0] == constituents[i][0]) and (implicants[j][1] == constituents[i][1])) 
                table_element.push_back(1);
            else if ((implicants[j][0] == constituents[i][0]) and (implicants[j][2] == constituents[i][2])) 
                table_element.push_back(1);
            else if ((implicants[j][1] == constituents[i][1]) and (implicants[j][2] == constituents[i][2])) 
                table_element.push_back(1);
            else
                table_element.push_back(0);
        }

        table.push_back(table_element);
    }

    std::vector<std::vector<int>> buf_table = table;

    for (size_t i = 0; i < table.size() - regluing_implicants.size(); i++) {
        for (size_t j = 0; j < table[i].size(); j++) {
            for (size_t k = i + 1; k < table.size() - regluing_implicants.size(); k++) {
                if (table[i][j] == 1 and table[k][j] == 1) {
                    buf_table[i][j] = 0;
                    buf_table[k][j] = 0;
                }
            }
        }
    }

    for (size_t i = 0; i < buf_table.size(); i++) 
        for (size_t j = 0; j < buf_table[i].size(); j++) 
            if (buf_table[i][j] == 1) 
                implicant_index.push_back(i);
 

    for (size_t i = 0; i < regluing_implicants.size(); i++) 
        implicant_index.push_back(implicants.size() -  i - 1);
    
    for (size_t i = 0; i < implicant_index.size(); i++) 
        short_table.push_back(implicants[implicant_index[i]]);

    remove(short_table);

    return create_short_form(short_table, sign);
}

void TruthTable::create_carno_map(std::vector<std::vector<int>>& table)
{
    std::vector<int> table_elements;

    for (size_t i = 0; i < SIZE / 2; i++)
        table_elements.push_back(this->table[i].result);

    table.push_back(table_elements);
    table_elements.clear();

    for (size_t i = 4; i < SIZE; i++)
        table_elements.push_back(this->table[i].result);

    table.push_back(table_elements);
}

std::vector<std::vector<int>> TruthTable::check_row(std::vector<std::vector<int>>& carno_map, bool sign)
{
    std::string implicant;
    std::vector<std::vector<int>> table;
    int row = -1;

    if (amount_of_sign_result(carno_map, 0, sign)) {
        row = 0;
        std::vector<int> table_element;
        table_element.push_back(this->table[0].a);
        table_element.push_back(-1);
        table_element.push_back(-1);
        table.push_back(table_element);
    }

    if (amount_of_sign_result(carno_map, 1, sign)) {
        row = 1;
        std::vector<int> table_element;
        table_element.push_back(this->table[5].a);
        table_element.push_back(-1);
        table_element.push_back(-1);
        table.push_back(table_element);
    }

    if (row == 0) {
        for (size_t j = 0; j < carno_map[0].size(); j++)
            if (carno_map[0][j] == sign and carno_map[1][j] != sign)
                carno_map[0][j] = -1;
    }
    else if (row == 1) {
        for (size_t j = 0; j < carno_map[0].size(); j++)
            if (carno_map[1][j] == sign and carno_map[0][j] != sign)
                carno_map[1][j] = -1;
    }

    return table;
}

std::vector<std::vector<int>> TruthTable::check_single_row(std::vector<std::vector<int>>& carno_map, bool sign)
{
    std::vector<std::vector<int>> table;

    for (size_t i = 0; i < carno_map.size(); i++) {
        for (size_t j = 0; j < carno_map[i].size() - 1; j++) {
            for (size_t k = j + 1; k < carno_map[i].size(); k++) {
                if (carno_map[i][j] == sign and carno_map[i][k] == sign) {
                    std::vector<int> table_element = create_implicamt(carno_map, j, k, i, sign);
                    table.push_back(table_element);
                }
            }
        }
    }

    return table;

}

std::vector<int> TruthTable::create_implicamt(std::vector<std::vector<int>> &carno_map, int indx_1, int indx_2, int row, bool sign)
{
    std::vector<int> table_element;

    if (parity_check(carno_map, sign)) {
        carno_map[row][indx_1] = -1;
        carno_map[row][indx_2] = -1;
    }
    else {
        if (row == 0) {
            if (carno_map[row + 1][indx_1] != sign)
                carno_map[row][indx_1] = -1;
            if (carno_map[row + 1][indx_2] != sign)
                carno_map[row][indx_2] = -1;
        }
        else {
            if (carno_map[row - 1][indx_1] != sign)
                carno_map[row][indx_1] = -1;
            if (carno_map[row - 1][indx_2] != sign)
                carno_map[row][indx_2] = -1;
        }
    }

    if (row == 1) {
        indx_1 += 4;
        indx_2 += 4;
    }

    if (this->table[indx_1].a == this->table[indx_2].a)
        table_element.push_back(this->table[indx_1].a);
    else
        table_element.push_back(-1);
    if (this->table[indx_1].b == this->table[indx_2].b)
        table_element.push_back(this->table[indx_1].b);
    else
        table_element.push_back(-1);
    if (this->table[indx_1].c == this->table[indx_2].c)
        table_element.push_back(this->table[indx_1].c);
    else
        table_element.push_back(-1);

    return table_element;
}

bool TruthTable::amount_of_sign_result(std::vector<std::vector<int>> table, int row, bool sign)
{
    int amount = 0;

    for (size_t j = 0; j < table[row].size(); j++)
        if (table[row][j] == sign)
            amount++;

    if (amount == 4)
        return true;

    return false;
}

std::vector<std::vector<int>> TruthTable::check_column(std::vector<std::vector<int>> &carno_map, bool sign)
{
    std::vector<std::vector<int>> table;

    for (size_t j = 0; j < carno_map[0].size() - 1; j++) {
        std::vector<int> table_element;

        if ((carno_map[0][j] == sign and carno_map[1][j] == sign) and (carno_map[0][j + 1] == sign and carno_map[1][j + 1] == sign)) {
                carno_map[0][j] = -1;
                carno_map[1][j] = -1;
            if (j % 2 == 0) {
                table_element.push_back(-1);
                table_element.push_back(this->table[j].b);
                table_element.push_back(-1);
            }
            else {
                table_element.push_back(-1);
                table_element.push_back(-1);
                table_element.push_back(this->table[j].c);
            }

            table.push_back(table_element);
        }
    }


    if ((carno_map[0][0] == sign and carno_map[1][0] == sign) and (carno_map[0][3] == sign and carno_map[1][3] == sign)) {
        std::vector<int> table_element;
        table_element.push_back(-1);
        table_element.push_back(-1);
        table_element.push_back(this->table[0].c);
        table.push_back(table_element);

        if (carno_map[0][1] != sign)
            carno_map[0][0] = -1;
        if (carno_map[1][1] != sign)
            carno_map[1][0] = -1;
        if (carno_map[0][2] != sign)
            carno_map[0][3] = -1;
        if (carno_map[1][2] != sign)
            carno_map[1][3] = -1;
    }

    return table;
}

bool TruthTable::parity_check(std::vector<std::vector<int>> carno_map, bool sign)
{
    int amount = 0;

    for (size_t i = 0; i < carno_map.size(); i++) 
        for (size_t j = 0; j < carno_map[i].size(); j++)
            if (carno_map[i][j] == sign)
                amount++;

    if (amount % 2 == 0)
        return true;
    else
        return false;
}

std::vector<std::vector<int>> TruthTable::check_single_column(std::vector<std::vector<int>>& carno_map, bool sign)
{
    std::vector<std::vector<int>> table;

    for (size_t j = 0; j < carno_map[0].size(); j++) {
        if (carno_map[0][j] == sign and carno_map[1][j] == sign) {
            std::vector<int> table_element;
            
            if (this->table[j].a == this->table[j + 4].a)
                table_element.push_back(this->table[j].a);
            else
                table_element.push_back(-1);
            if (this->table[j].b == this->table[j + 4].b)
                table_element.push_back(this->table[j].b);
            else
                table_element.push_back(-1);
            if (this->table[j].c == this->table[j + 4].c)
                table_element.push_back(this->table[j].c);
            else
                table_element.push_back(-1);

            table.push_back(table_element);

            carno_map[0][j] = -1;
            carno_map[1][j] = -1;
        }
    }

    return table;
}

std::vector<std::vector<int>> TruthTable::check_remaining(std::vector<std::vector<int>>& carno_map, bool sign)
{
    std::vector<std::vector<int>> table;

    for (size_t i = 0; i < carno_map.size(); i++) {
        for (size_t j = 0; j < carno_map[i].size(); j++) {
            if (carno_map[i][j] == sign) {
                std::vector<int> table_element;
                
                if (i == 0) {
                    table_element.push_back(this->table[j].a);
                    table_element.push_back(this->table[j].b);
                    table_element.push_back(this->table[j].c);
                    carno_map[i][j] = -1;
                }
                else {
                    table_element.push_back(this->table[j + 4].a);
                    table_element.push_back(this->table[j + 4].b);
                    table_element.push_back(this->table[j + 4].c);
                    carno_map[i][j] = -1;
                }

                table.push_back(table_element);
            }
        }
    }

    return table;
}

std::string TruthTable::tabular_calculation_method(bool sign)
{
    std::vector<std::vector<int>> carno_map;
    std::vector<std::vector<int>> table;
    std::vector<std::vector<int>> buf_table;

    create_carno_map(carno_map);

    buf_table = check_row(carno_map, sign);
    table.insert(table.end(), buf_table.begin(), buf_table.end());

    buf_table = check_column(carno_map, sign);
    table.insert(table.end(), buf_table.begin(), buf_table.end());

    buf_table = check_single_row(carno_map, sign);
    table.insert(table.end(), buf_table.begin(), buf_table.end());

    buf_table = check_single_column(carno_map, sign);
    table.insert(table.end(), buf_table.begin(), buf_table.end());

    buf_table = check_remaining(carno_map, sign);
    table.insert(table.end(), buf_table.begin(), buf_table.end());

    return create_short_form(table, sign);
}

std::string TruthTable::create_normal_form(bool sign)
{
    if (sign) {
        std::string sdnf;

        for (size_t i = 0; i < SIZE; i++) {
            if (this->table[i].result == sign) {
                sdnf += '(';

                if (this->table[i].a == 0)
                    sdnf += "!a*";
                else
                    sdnf += "a*";
                if (this->table[i].b == 0)
                    sdnf += "!b*";
                else
                    sdnf += "b*";
                if (this->table[i].c == 0)
                    sdnf += "!c";
                else
                    sdnf += "c";

                sdnf += ")+";
            }
        }
        if (sdnf.size()) {
            sdnf.erase(sdnf.size() - 1);

            return sdnf;
        }
    }
    else {
        std::string sknf;

        for (size_t i = 0; i < SIZE; i++) {
            if (this->table[i].result == 0)
            {
                sknf += "(";

                if (this->table[i].a == 0)
                    sknf += "a+";
                else
                    sknf += "!a+";
                if (this->table[i].b == 0)
                    sknf += "b+";
                else
                    sknf += "!b+";
                if (this->table[i].c == 0)
                    sknf += "c";
                else
                    sknf += "!c";

                sknf += ")*";
            }
        }
        if (sknf.size() >= 1) {
            sknf.erase(sknf.size() - 1);

            return sknf;
        }
        else
            return "does not exist";
    }
}
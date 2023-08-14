//
// Created by Daer0n
//
#ifndef LAB3_HEADER_H
#define LAB3_HEADER_H


#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#define SIZE 8

struct Stack {
    Stack* next;
    char info;
};

struct Set {
    bool a;
    bool b;
    bool c;
    bool result;
    bool visit = false;
};

class TruthTable
{
public:
    TruthTable();
    Set table[8];
    std::string calculation_method(bool sign);
    std::string tabular_method(bool sign);
    std::string tabular_calculation_method(bool sign);
    std::string create_normal_form(bool sign);
    static void print(std::string expression);
    void print_table();
    void run_truth_table(std::string expression);
private:
    std::vector<std::vector<int>> getting_rid_extra_implicant(std::vector<std::vector<int>> table, bool sign);
    std::vector<std::vector<int>> regluing(std::vector<std::vector<int>> table, bool sign);
    std::vector<std::vector<int>> check_row(std::vector<std::vector<int>>& carno_map, bool sign);
    std::vector<std::vector<int>> check_column(std::vector<std::vector<int>>& carno_map, bool sign);
    std::vector<std::vector<int>> check_single_row(std::vector<std::vector<int>>& carno_map, bool sign);
    std::vector<std::vector<int>> check_single_column(std::vector<std::vector<int>>& carno_map, bool sign);
    std::vector<std::vector<int>> check_remaining(std::vector<std::vector<int>>& carno_map, bool sign);
    std::vector<std::vector<int>> gluing(bool sign);
    std::vector<std::vector<int>> create_constituents(bool sign);
    std::vector<int> create_implicamt(std::vector<std::vector<int>>& carno_map, int indx_1, int indx_2, int row, bool sign);
    std::vector<int> check_unvisited(int ind);
    std::string create_short_form(std::vector<std::vector<int>> table, bool sign);
    std::string translate_to_opz(std::string expression);
    void push_char(Stack*& top, char info);
    void push_bool(Stack*& top, bool info);
    void pop_char(Stack*& top, char* info);
    void pop_bool(Stack*& top, bool* info);
    void remove(std::vector<std::vector<int>>& table);
    void create_carno_map(std::vector<std::vector<int>>& table);
    int prior(char oper);
    bool amount_of_sign_result(std::vector<std::vector<int>> table, int row, bool sign);
    bool truth_table(std::string expression, bool a, bool b, bool c);
    bool parity_check(std::vector<std::vector<int>> carno_map, bool sign);

};

#endif //LAB3_HEADER_H

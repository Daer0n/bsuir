#include <iostream>
#include "header.cpp"

int main() {
    std::string expression, sknf, sdnf;
    TruthTable Sdnf, Sknf;
    std::cout << "Enter formula: ";
    std::getline(std::cin, expression);
    Sknf.run_truth_table(expression);
    Sdnf.run_truth_table(expression);
    Sknf.print_table();
    sdnf = Sdnf.create_normal_form(1);
    sknf = Sknf.create_normal_form(0);
    std::cout << "SDNF: "; TruthTable::print(sdnf);
    std::cout << "SKNF: "; TruthTable::print(sknf);
    sdnf = Sdnf.calculation_method(1);
    sknf = Sknf.calculation_method(0);
    std::cout << "Calculation method:\n";
    std::cout << "TDNF: "; TruthTable::print(sdnf);
    std::cout << "TKNF: "; TruthTable::print(sknf);
    sknf = Sknf.tabular_method(0);
    sdnf = Sdnf.tabular_method(1);
    std::cout << "Tabular method:\n";
    std::cout << "TDNF: "; TruthTable::print(sdnf);
    std::cout << "TKNF: "; TruthTable::print(sknf);
    sdnf = Sdnf.tabular_calculation_method(1);
    sknf = Sknf.tabular_calculation_method(0);
    std::cout << "Tabular-calculation method:\n";
    std::cout << "TDNF: "; TruthTable::print(sdnf);
    std::cout << "TKNF: "; TruthTable::print(sknf);


}

//  (a*b)+(!a*c)
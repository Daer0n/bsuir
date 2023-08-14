
#include "header.h"
#include "header.cpp"



int main()
{
    TruthTable t;
    SKNF Sknf;
    SDNF Sdnf;
    std::string expression, sknf, sdnf;
    std::cout << "Enter formula: ";
    std::getline(std::cin, expression);
    Sknf.run_truth_table(expression);
    sknf = Sknf.create_sknf();
    Sknf.print_table();
    SKNF::print_sknf(sknf);
    Sdnf.run_truth_table(expression);
    sdnf = Sdnf.create_sdnf();
    SDNF::print_sdnf(sdnf);
    Sknf.print_binary_sknf();
    Sdnf.print_binary_sdnf();
    Sknf.print_decimal_sknf();
    Sdnf.print_decimal_sdnf();
    Sdnf.print_index(); 
}

// !((!b+c)*(!(!a*c)))
// !(a+!b)*(a*c)
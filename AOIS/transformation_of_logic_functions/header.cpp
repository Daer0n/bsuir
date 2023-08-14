

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
    this->table[2].c = 0;

    this->table[3].a = 0;
    this->table[3].b = 1;
    this->table[3].c = 1;

    this->table[4].a = 1;
    this->table[4].b = 0;
    this->table[4].c = 0;

    this->table[5].a = 1;
    this->table[5].b = 0;
    this->table[5].c = 1;

    this->table[6].a = 1;
    this->table[6].b = 1;
    this->table[6].c = 0;

    this->table[7].a = 1;
    this->table[7].b = 1;
    this->table[7].c = 1;
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
            while (top->info != '(')
            {
                pop_char(top, &element);
                result += element;
            }
            pop_char(top, &element);
        }
        else if (expression[i] >= 'a' and expression[i] <= 'c')
            result += expression[i];
        else if (expression[i] == '*' or expression[i] == '+' or expression[i] == '!') {
            while (top != NULL and prior(top->info) >= prior(expression[i]))
            {
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

std::string SKNF::create_sknf()
{
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
            sknf += ")";
            sknf += "*";
        }
    }
    if (sknf.size() >= 1) {
        sknf.erase(sknf.size() - 1);
        return sknf;
    }
    else 
        return "does not exist";
}

std::string SDNF::create_sdnf()
{
    std::string sdnf;
    for (size_t i = 0; i < SIZE; i++) {
        if (this->table[i].result == 1) {
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
            sdnf += "+";
        }
    }
    if (sdnf.size()) {
        sdnf.erase(sdnf.size() - 1);
        return sdnf;
    }
    else
        return "does not exist";
}

void SDNF::print_sdnf(std::string sdnf)
{
    std::cout << "SDNF: " << sdnf << "\n";
}

void SKNF::print_sknf(std::string sdnf)
{
    std::cout << "SKNF: " << sdnf << "\n";
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

void TruthTable::print_index()
{
    std::vector<int> nums;
    int num;
    for (size_t i = 0; i < SIZE; i++)
        nums.push_back(this->table[i].result);
    num = direct_code_to_int(nums);
    std::cout << "Index: " << num << "\n";
}

int TruthTable::direct_code_to_int(std::vector<int> nums)
{
    int number = 0;
    std::reverse(nums.begin(), nums.end());
    for (size_t i = 0; i < nums.size(); i++)
        if (nums[i] == 1)
            number += pow(2, i);
    return number;
}

std::vector<int> TruthTable::int_to_direct_code(int number, int size)
{
    std::vector<int> nums;
    int num = abs(number);
    while (num) {
        nums.push_back(num & 2);
        num /= 2;
    }
    int length = nums.size();
    for (int i = 0; i < size - length; i++)
        nums.push_back(0);
    std::reverse(nums.begin(), nums.end());
    if (number < 0)
        nums[0] = 1;
    return nums;
}

void SDNF::print_binary_sdnf()
{
    std::string sdnf;
    sdnf += "+(";
    for (size_t i = 0; i < SIZE; i++) {
        if (this->table[i].result == 1) {
            if (this->table[i].a)
                sdnf += "1";
            else 
                sdnf += "0";
            if (this->table[i].b)
                sdnf += "1";
            else
                sdnf += "0";
            if (this->table[i].c)
                sdnf += "1";
            else
                sdnf += "0";
            sdnf += ",";
        }
    }
    sdnf.erase(sdnf.size() - 1);
    sdnf += ")";
    if (sdnf.size() > 3)
        std::cout << "Binary sdnf: " << sdnf << "\n";
    else
        std::cout << "Binary sdnf: does not exist\n";
}

void SKNF::print_binary_sknf()
{
    std::string sknf;
    sknf += "*(";
    for (size_t i = 0; i < SIZE; i++) {
        if (this->table[i].result == 0) {
            if (this->table[i].a)
                sknf += "1";
            else
                sknf += "0";
            if (this->table[i].b)
                sknf += "1";
            else
                sknf += "0";
            if (this->table[i].c)
                sknf += "1";
            else
                sknf += "0";
            sknf += ",";
        }
    }
    sknf.erase(sknf.size() - 1);
    sknf += ")";
    if(sknf.size() > 3)
        std::cout << "Binary sknf: " << sknf << "\n";
    else 
        std::cout << "Binary sknf: does not exist\n";
}

void SKNF::print_decimal_sknf()
{
    std::string sknf;
    sknf += "*(";
    for (size_t i = 0; i < SIZE; i++) {
        if (this->table[i].result == 0) {
            std::vector<int> nums;
            int num;
            if (this->table[i].a)
                nums.push_back(1);
            else
                nums.push_back(0);
            if (this->table[i].b)
                nums.push_back(1);
            else
                nums.push_back(0);
            if (this->table[i].c)
                nums.push_back(1);
            else
                nums.push_back(0);
            num = SKNF::direct_code_to_int(nums);
            std::stringstream ss;
            ss << num;
            std::string str = ss.str();
            sknf += str;
            sknf += ",";
        }
    }
    sknf.erase(sknf.size() - 1);
    sknf += ")";
    if (sknf.size() > 3)
        std::cout << "Decimal sknf: " << sknf << "\n";
    else
        std::cout << "Decimal sknf: does not exist\n";
}

void SDNF::print_decimal_sdnf()
{
    std::string sdnf;
    sdnf += "+(";
    for (size_t i = 0; i < SIZE; i++) {
        if (this->table[i].result == 1) {
            std::vector<int> nums;
            int num;
            if (this->table[i].a)
                nums.push_back(1);
            else
                nums.push_back(0);
            if (this->table[i].b)
                nums.push_back(1);
            else
                nums.push_back(0);
            if (this->table[i].c)
                nums.push_back(1);
            else
                nums.push_back(0);
            num = SDNF::direct_code_to_int(nums);
            std::stringstream ss;
            ss << num;
            std::string str = ss.str();
            sdnf += str;
            sdnf += ",";
        }
    }
    sdnf.erase(sdnf.size() - 1);
    sdnf += ")";
    if (sdnf.size() > 3)
        std::cout << "Decimal sdnf: " << sdnf << "\n";
    else
        std::cout << "Decimal sdnf: does not exist\n";
}
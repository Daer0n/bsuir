
#include <iostream>
#include <vector>
#include <sstream>

#define BASE_8 8
#define BASE_16 16
#define BASE_23 23

struct Float
{
    std::vector<int> sign = { 0 };
    std::vector<int> index;
    std::vector<int> mantissa;
};
// 1 - sign
// 8 - index 
// 23 - mantissa
std::vector<int> int_to_direct_code(int number, int size) 
{
    std::vector<int> nums;
    int buf = 0;
    int num = abs(number);
    while (num) {
        buf = num % 2;
        nums.push_back(buf);
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

std::vector<int> direct_to_reverse_code(std::vector<int>& nums) 
{
    for (size_t i = 1; i < nums.size(); i++) {
        if (nums[i] == 1)
            nums[i] = 0;
        else
            nums[i] = 1;
    }
    return nums;
}

std::vector<int> direct_to_additional_code(std::vector<int>& nums) 
{
    nums = direct_to_reverse_code(nums);
    if (nums[nums.size() - 1] == 0) {
        nums[nums.size() - 1] = 1;
        return nums;
    }
    for (size_t i = nums.size() - 1; i > 0; i--) {
        if (nums[i - 1] == 0) {
            nums[i] = 0;
            nums[i - 1] = 1;
            break;
        }
        else
            nums[i] = 0;
    }
    return nums;
}

int direct_code_to_int(std::vector<int> nums)
{
    int number = 0;
    std::reverse(nums.begin(), nums.end());
    for (size_t i = 0; i < nums.size() - 1; i++) 
        if (nums[i] == 1) 
            number += pow(2, i);
    if (nums[nums.size() - 1] == 1)
        return -number;
    else 
        return number;
}

std::vector<int> reverse_code_to_direct(std::vector<int>& nums)
{
    for (size_t i = 1; i < nums.size(); i++) {
        if (nums[i] == 1)
            nums[i] = 0;
        else
            nums[i] = 1;
    }
    return nums;
}

std::vector<int> additional_code_to_direct(std::vector<int>& nums)
{
    for (size_t i = nums.size() - 1; i > 0; i--) {
        if (nums[i] == 1 and (nums[i - 1] == 1 or nums[i - 1] == 0)) {
            nums[i] = 0; 
            break;
        }
        if (nums[i] == 0)
            nums[i] = 1;
        else
            nums[i] = 0;
    }
    return reverse_code_to_direct(nums);
}


void print_bi_code(std::vector<int>& nums)
{
    for (int i = 0; i < nums.size(); i++)
        std::cout << nums[i];
    std::cout << "\n";
}

std::vector<int> addition(std::vector<int> nums1, std::vector<int> nums2)
{
    std::vector<int> nums;
    bool flag = false;
    for (size_t i = nums1.size(); i > 0; i--) {
        if (flag and ((nums1[i - 1] == 0 and nums2[i - 1] == 1) or (nums1[i - 1] == 1 and nums2[i - 1] == 0))) {
            nums.push_back(0);
            flag = true;
        }
        else if (!flag and ((nums1[i - 1] == 0 and nums2[i - 1] == 1) or (nums1[i - 1] == 1 and nums2[i - 1] == 0))) {
            nums.push_back(1);
            flag = false;
        }
        else if (nums1[i - 1] == 0 and nums2[i - 1] == 0 and !flag) {
            nums.push_back(0);
            flag = false;
        }
        else if (nums1[i - 1] == 0 and nums2[i - 1] == 0 and flag) {
            nums.push_back(1);
            flag = false;
        }
        else if (nums1[i - 1] == 1 and nums2[i - 1] == 1 and !flag) {
            nums.push_back(0);
            flag = true;
        }
        else if (nums1[i - 1] == 1 and nums2[i - 1] == 1 and flag) {
            nums.push_back(1);
            flag = true;
        }
    }
    std::reverse(nums.begin(), nums.end());
    if (nums[0] == 1)
        additional_code_to_direct(nums);
    return nums;
}

std::vector<int> bi_sum(std::vector<int> nums1, std::vector<int> nums2)
{
    if (nums1[0] == 1 and nums2[0] == 1) {
        nums1 = direct_to_additional_code(nums1);
        nums2 = direct_to_additional_code(nums2);
    }
    else if (nums2[0] == 1)
        nums2 = direct_to_additional_code(nums2);
    else if (nums1[0] == 1) 
        nums1 = direct_to_additional_code(nums1);
    return addition(nums1, nums2);
}

std::vector<int> bi_multiplication(std::vector<int> nums1, std::vector<int> nums2)
{
    std::vector<int> nums;
    std::vector<int> buf_nums_of_one;
    std::vector<int> buf_nums_of_zero;
    bool sign = false;
    if (nums1[0] == 1 and nums2[0] == 1) {
        nums1[0] = 0;
        nums2[0] = 0;
    }
    else if (nums1[0] == 1) {
        nums1[0] = 0;
        sign = true;
    }
    else if (nums2[0] == 1) {
        nums2[0] = 0;
        sign = true;
    }
    for (size_t i = 0; i < nums1.size(); i++) {
        buf_nums_of_one.push_back(1);
        buf_nums_of_zero.push_back(0);
    }
    nums = buf_nums_of_zero;
    while (nums2 != buf_nums_of_zero) {
        nums = addition(nums, nums1);
        nums2 = addition(nums2, buf_nums_of_one);
    }
    if (sign)
        nums[0] = 1;
    else
        nums[0] = 0;
    return nums;
}

std::vector<int> bi_division(std::vector<int> nums1, std::vector<int> nums2)
{
    std::vector<int> nums;
    std::vector<int> buf_nums;
    std::vector<int> nums_of_null;
    bool sign = false;
    if (nums1[0] == 1 and nums2[0] == 1) 
        nums1[0] = 0;
    else if (nums1[0] == 1) {
        sign == true;
        nums1[0] = 0;
    }
    else if (nums2[0] == 1) 
        sign = true;
    for (size_t i = 0; i < BASE_16; i++) {
        nums.push_back(0);
        buf_nums.push_back(0);
        nums_of_null.push_back(0);
    }
    buf_nums[15] = 1;
    nums[15] = 1;
    nums[0] = 1;
    nums2[0] = 1;
    while (nums1[0] != 1 or nums1 == nums_of_null) {
        nums1 = bi_sum(nums1, nums2);
        nums = bi_sum(nums, buf_nums);
    }
    if (sign)
        nums[0] = 1;
    return nums;
}

Float float_to_bi_code(float& num)
{
    Float nums;
    std::ostringstream ss;
    ss << num;
    std::string s(ss.str());
    int ind = 0;
    if (num < 0) {
        nums.sign[0] = 1;
        num = -num;
    }
    for (size_t i = s.size() - 1; i > 0; i--) {
        if (s[i] == '.')
            break;
        else
            ind++;
    }
    num *= pow(10, ind);
    num = int(num);
    nums.index = int_to_direct_code(ind, BASE_8);
    nums.mantissa = int_to_direct_code(num, BASE_23);

    return nums;
}

void print_float_bi_code(Float& nums)
{
    std::cout << nums.sign[0] << '|';
    for (size_t i = 0; i < nums.index.size(); i++)
        std::cout << nums.index[i];
    std::cout << "|";
    for (size_t i = 0; i < nums.mantissa.size(); i++)
        std::cout << nums.mantissa[i];
    std::cout << "\n";
}

void float_addition(Float& nums1, Float& nums2)
{
    Float nums;
    if (nums1.sign[0] == 1 and nums2.sign[0] == 1) {
        nums.sign[0] = 1;
        nums1.mantissa[0] = 1;
        nums2.mantissa[0] = 1;
    }
    else if (nums1.sign[0] == 1)
        nums1.mantissa[0] = 1;
    else if (nums2.sign[0] == 1)
        nums2.mantissa[0] = 1;
    nums.index = bi_sum(nums1.index, nums2.index);
    nums.mantissa = bi_sum(nums1.mantissa, nums2.mantissa);
    float rez = direct_code_to_int(nums.mantissa) * pow(10, -direct_code_to_int(nums.index) / 2);
    std::cout << rez << "\n";
    print_float_bi_code(nums);
}

void run_int(int num1, int num2)
{
    std::vector<int> nums1;
    std::vector<int> nums2;
    std::vector<int> nums;
    std::cout << "X1 = " << num1 << "\n"
        << "X2 = " << num2 << "\n";
    nums1 = int_to_direct_code(num1, BASE_16);
    nums2 = int_to_direct_code(num2, BASE_16);
    nums = bi_sum(nums1, nums2);
    std::cout << "X1 + X2 = " << direct_code_to_int(nums) << "\n";
    print_bi_code(nums);
    nums = bi_multiplication(nums1, nums2);
    std::cout << "X1 * X2 = " << direct_code_to_int(nums) << "\n";
    print_bi_code(nums);
    nums = bi_division(nums1, nums2);
    std::cout << "X1 / X2 = " << direct_code_to_int(nums) << "\n";
    print_bi_code(nums);
    nums = bi_division(nums2, nums1);
    std::cout << "X2 / X1 = " << direct_code_to_int(nums) << "\n";
    print_bi_code(nums);
    std::cout << "\n" << "-------------------------------------------------------------------" << "\n";
}

int main()
{
    int num1 = 13, num2 = 5;

    run_int(num1, num2);
    run_int(num1, -num2);
    run_int(-num1, num2);
    run_int(-num1, -num2);

    float number1 = 7.125, number2 = 5.125;
    Float nums1, nums2;
    std::cout << "X1 = " << number1 << "\n"
        << "X2 = " << number2 << "\n"
        << "X1 + X2 = ";
    nums1 = float_to_bi_code(number1);
    nums2 = float_to_bi_code(number2);
    float_addition(nums1, nums2);
}

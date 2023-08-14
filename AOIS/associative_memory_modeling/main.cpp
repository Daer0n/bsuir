
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#define SIZE 16

class AssociativeArray
{
public:
	std::vector<std::vector<int>> array;
	std::vector<std::vector<int>> diagonal_array;
	AssociativeArray();
	void print(std::vector<std::vector<int>> array);
	void create_diagonal_array();
	void get_adress(int adress);
	void arithmetic_operations(std::vector<int> v);
	void function_2(int adress_1, int adress_2, int adress_3);
	void function_7(int adress_1, int adress_2, int adress_3);
	void function_8(int adress_1, int adress_2, int adress_3);
	void function_13(int adress_1, int adress_2, int adress_3);
	void border_search(int adress_1, int adress_2);

private:
	std::vector<std::vector<int>> border_find(std::vector<int> binary_value, std::string flag);
	std::vector<int> slicing(std::vector<int> word, int x, int y);
	std::vector<int> sum(std::vector<int> word_1, std::vector<int> word_2);
	std::vector<bool> vector_int_to_vector_bool(std::vector<int> word);
	std::vector<int> vector_bool_to_vector_int(std::vector<bool> bool_word);
	void create_column_of_diagonal_array(std::vector<int> word, int row);
	bool comparison(std::vector<int> word_1, std::vector<int> word_2);
	void assignment(std::vector<int>& word_1, std::vector<int> word_2);
	void sort(std::vector<std::vector<int>>& word_array);
};


AssociativeArray::AssociativeArray()
{
	srand(time(NULL));

	for (size_t i = 0; i < SIZE; i++) {
		std::vector<int> word;

		for (size_t j = 0; j < SIZE; j++) 
			word.push_back(rand() % 2);

		this->array.push_back(word);
		this->diagonal_array.push_back(word);
	}
}

void AssociativeArray::print(std::vector<std::vector<int>> array)
{
	std::cout << "\n";
	for (size_t i = 0; i < array.size(); i++) {
		for (size_t j = 0; j < array[i].size(); j++)
			std::cout << array[i][j] << " ";

		std::cout << " \n";
	}
	std::cout << "\n";
}

void AssociativeArray::create_diagonal_array()
{
	for (size_t i = 0; i < this->array.size(); i++)
		create_column_of_diagonal_array(this->array[i], i);
}

void AssociativeArray::create_column_of_diagonal_array(std::vector<int> word, int row)
{
	for (size_t i = row; i < SIZE; i++)
		this->diagonal_array[i][row] = word[i - row];

	for (size_t i = 0; i < row; i++)
		this->diagonal_array[i][row] = word[SIZE + i - row];
}

void AssociativeArray::get_adress(int adress)
{
	std::cout << adress << "th word in the matrix:\n";
	for (size_t i = 0; i < this->diagonal_array[adress].size(); i++)
		std::cout << this->diagonal_array[adress][i] << " ";
	std::cout << "\n\n";
}

std::vector<int> AssociativeArray::slicing(std::vector<int> word, int x, int y)
{

	auto start = word.begin() + x;
	auto end = word.begin() + y + 1;

	std::vector<int> vec(start, end);

	return vec;
}

std::vector<int> AssociativeArray::sum(std::vector<int> word_1, std::vector<int> word_2)
{
	std::vector<int> word;
	int counter = 0;

	std::reverse(word_1.begin(), word_1.end());
	std::reverse(word_2.begin(), word_2.end());

	for (size_t i = 0; i < word_1.size(); i++) {
		if ((word_1[i] + word_2[i] + counter) == 0)
			word.push_back(0);
		else if ((word_1[i] + word_2[i] + counter) == 1) {
			word.push_back(1);
			counter = 0;
		}
		else if ((word_1[i] + word_2[i] + counter) == 2) {
			word.push_back(0);
			counter = 1;
		}
		else if ((word_1[i] + word_2[i] + counter) == 3) {
			word.push_back(1);
			counter = 1;
		}
	}

	word.push_back(counter);

	std::reverse(word.begin(), word.end());

	return word;
}

void AssociativeArray::assignment(std::vector<int>& word_1, std::vector<int> word_2)
{
	std::reverse(word_1.begin(), word_1.end());
	std::reverse(word_2.begin(), word_2.end());

	for (size_t i = 0; i < word_2.size(); i++)
		word_1[i] = word_2[i];

	std::reverse(word_1.begin(), word_1.end());
}

void AssociativeArray::arithmetic_operations(std::vector<int> v)
{
	for (size_t i = 0; i < this->diagonal_array.size(); i++) {
		std::vector<int> slicing_word = slicing(this->diagonal_array[i], 0, 2);

		if (slicing_word == v) {
			std::vector<int> Aj = slicing(this->diagonal_array[i], 3, 6);
			std::vector<int> Bj = slicing(this->diagonal_array[i], 7, 10);

			slicing_word = sum(Aj, Bj);

			std::cout << "\nVj = V in word " << i << "\n";
			get_adress(i);

			assignment(this->diagonal_array[i], slicing_word);

			get_adress(i);
		}
	}
}

std::vector<bool> AssociativeArray::vector_int_to_vector_bool(std::vector<int> word)
{
	std::vector<bool> bool_word;

	for (size_t i = 0; i < word.size(); i++) {
		if (word[i] == 1)
			bool_word.push_back(true);
		else
			bool_word.push_back(false);
	}

	return bool_word;
}

std::vector<int> AssociativeArray::vector_bool_to_vector_int(std::vector<bool> bool_world)
{
	std::vector<int> word;

	for (size_t i = 0; i < bool_world.size(); i++) {
		if (bool_world[i])
			word.push_back(1);
		else
			word.push_back(0);
	}
	
	return word;
}

void AssociativeArray::function_2(int adress_1, int adress_2, int adress_3)
{
	std::vector<bool> result;
	std::vector<bool> word_1 = vector_int_to_vector_bool(this->diagonal_array[adress_1]);
	std::vector<bool> word_2 = vector_int_to_vector_bool(this->diagonal_array[adress_2]);

	for (size_t i = 0; i < word_1.size(); i++) {
		result.push_back(word_1[i] * !word_2[i]);
	}

	this->diagonal_array[adress_3] = vector_bool_to_vector_int(result);

	std::cout << "Function №2: x1 * !x2\n";
	std::cout << "For reading: "; get_adress(adress_1);
	std::cout << "For reading: "; get_adress(adress_2);
	std::cout << "For writting: "; get_adress(adress_3);
}

void AssociativeArray::function_7(int adress_1, int adress_2, int adress_3)
{
	std::vector<bool> result;
	std::vector<bool> word_1 = vector_int_to_vector_bool(this->diagonal_array[adress_1]);
	std::vector<bool> word_2 = vector_int_to_vector_bool(this->diagonal_array[adress_2]);

	for (size_t i = 0; i < word_1.size(); i++) {
		result.push_back(word_1[i] + word_2[i]);
	}

	this->diagonal_array[adress_3] = vector_bool_to_vector_int(result);

	std::cout << "Function №7: x1 + x2\n";
	std::cout << "For reading: "; get_adress(adress_1);
	std::cout << "For reading: "; get_adress(adress_2);
	std::cout << "For writting: "; get_adress(adress_3);
}

void AssociativeArray::function_8(int adress_1, int adress_2, int adress_3)
{
	std::vector<bool> result;
	std::vector<bool> word_1 = vector_int_to_vector_bool(this->diagonal_array[adress_1]);
	std::vector<bool> word_2 = vector_int_to_vector_bool(this->diagonal_array[adress_2]);

	for (size_t i = 0; i < word_1.size(); i++) {
		result.push_back(!(word_1[i] + word_2[i]));
	}

	this->diagonal_array[adress_3] = vector_bool_to_vector_int(result);

	std::cout << "Function №8: !(x1 + x2)\n";
	std::cout << "For reading: "; get_adress(adress_1);
	std::cout << "For reading: "; get_adress(adress_2);
	std::cout << "For writting: "; get_adress(adress_3);
}

void AssociativeArray::function_13(int adress_1, int adress_2, int adress_3)
{
	std::vector<bool> result;
	std::vector<bool> word_1 = vector_int_to_vector_bool(this->diagonal_array[adress_1]);
	std::vector<bool> word_2 = vector_int_to_vector_bool(this->diagonal_array[adress_2]);

	for (size_t i = 0; i < word_1.size(); i++) {
		result.push_back(!word_1[i] + word_2[i]);
	}

	this->diagonal_array[adress_3] = vector_bool_to_vector_int(result);

	std::cout << "Function №13: !x1 + x2\n";
	std::cout << "For reading: "; get_adress(adress_1);
	std::cout << "For reading: "; get_adress(adress_2);
	std::cout << "For writting: "; get_adress(adress_3);
}

void AssociativeArray::sort(std::vector<std::vector<int>>& word_array)
{
	for (size_t i = 0; i < word_array.size() - 1; i++)
		for (size_t j = i + 1; j < word_array.size(); j++)
			if (comparison(word_array[i], word_array[j]))
				std::swap(word_array[i], word_array[j]);
}

bool AssociativeArray::comparison(std::vector<int> word_1, std::vector<int> word_2)
{
	bool g = false, l = false;

	for (size_t i = 0; i < word_1.size(); i++) {

		if (g or (word_1[i] == 0 and word_2[i] == 1 and !l))
			g = true;
		else
			g = false;

		if (l or (word_1[i] == 1 and word_2[i] == 0 and !g))
			l = true;
		else
			l = false;
	}

	if (g)
		return true;

	if (l)
		return false;
}

void AssociativeArray::border_search(int adress_1, int adress_2)
{
	std::vector<int> binary_value_1 = this->diagonal_array[adress_1];
	std::vector<int> binary_value_2 = this->diagonal_array[adress_2];
	std::vector<std::vector<int>> array_by_border;
	std::vector<std::vector<int>> array_by_max_border;
	std::vector<std::vector<int>> array_by_min_border;

	if (!comparison(binary_value_1, binary_value_2)) {
		array_by_max_border = border_find(binary_value_1, "max");
		array_by_min_border = border_find(binary_value_2, "min");
		std::cout << "\nBottom border:\n"; get_adress(adress_2);
		std::cout << "\nTop border:\n"; get_adress(adress_1);
	}
	else {
		array_by_max_border = border_find(binary_value_1, "max");
		array_by_min_border = border_find(binary_value_2, "min");
		std::cout << "\nBottom border:\n"; get_adress(adress_1);
		std::cout << "\nTop border:\n"; get_adress(adress_2);
	}


	std::sort(array_by_max_border.begin(), array_by_max_border.end());
	std::sort(array_by_min_border.begin(), array_by_min_border.end());


	std::set_intersection(array_by_max_border.begin(), array_by_max_border.end(), array_by_min_border.begin(), array_by_min_border.end(), std::back_inserter(array_by_border));
	if(array_by_border.size())
		array_by_border.pop_back();

	for (size_t i = 0; i < array_by_border.size(); i++) {
		for (size_t j = 0; j < array_by_border[i].size(); j++)
			std::cout << array_by_border[i][j] << " ";

		std::cout << "\n";
	}
}

std::vector<std::vector<int>> AssociativeArray::border_find(std::vector<int> binary_value, std::string flag)
{
	std::vector<std::vector<int>> array_on_one_border;

	if (flag == "max") {
		for (size_t i = 0; i < this->array.size(); i++)
			if (comparison(binary_value, this->array[i]))
				array_on_one_border.push_back(this->array[i]);
	}
	else if (flag == "min") {
		for (size_t i = 0; i < this->array.size(); i++)
			if (!comparison(binary_value, this->array[i]))
				array_on_one_border.push_back(this->array[i]);
	}

	return array_on_one_border;
}

int main()
{
	system("chcp 1251");

	std::vector<int> v{ 0, 0, 1 };
	AssociativeArray aa;

	std::cout << "Normal matrix:\n"; aa.print(aa.array);

	aa.create_diagonal_array();

	std::cout << "\nDiagonal matrix:\n"; aa.print(aa.diagonal_array);

	aa.get_adress(5);

	std::cout << "\n___________________Arithmetic operations___________________\n";
	aa.arithmetic_operations(v);
	aa.print(aa.diagonal_array);


	std::cout << "\n_____________________Logical operations____________________\n\n";

	aa.function_2(0, 1, 2); std::cout << "\n";
	aa.function_7(3, 4, 5); std::cout << "\n";
	aa.function_8(6, 7, 8); std::cout << "\n";
	aa.function_13(9, 10, 11);
	aa.print(aa.diagonal_array);

	std::cout << "\n_____________________Task____________________\n\n";
	int bottom_border, top_border;
	std::cout << "Enter bottom border: "; std::cin >> bottom_border;
	std::cout << "\nEnter top border: "; std::cin >> top_border;
	aa.border_search(bottom_border, top_border);
}


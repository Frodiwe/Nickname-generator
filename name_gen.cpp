#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iterator>
#include <cctype>
#include <map>
#include <stdexcept>

const std::vector< std::vector<int> > weights = {
	{15,97,104,184,65,28,59,142,211,15,68,504,228,1029,19,27,12,691,198,184,88,130,30,24,133,45} ,
	{114,13,0,4,155,0,0,3,72,1,0,26,0,1,37,0,0,135,4,1,21,0,0,0,28,0} ,
	{201,0,6,0,148,0,0,222,97,0,62,53,0,0,116,0,3,18,1,12,14,0,1,0,30,0} ,
	{297,0,0,23,275,3,4,4,162,0,0,14,6,9,132,0,0,79,8,0,38,1,11,0,61,1} ,
	{150,33,32,110,103,25,36,16,79,5,30,562,114,504,57,20,4,536,180,175,27,96,27,19,132,13} ,
	{68,0,0,0,48,23,1,0,53,1,0,21,0,1,24,0,0,48,0,3,5,0,1,0,5,0} ,
	{150,0,0,5,98,0,12,37,81,0,0,20,1,10,35,0,0,35,3,4,42,0,9,0,8,1} ,
	{422,3,0,3,209,0,1,0,149,0,1,15,6,16,91,0,0,24,2,9,45,0,2,0,24,1} ,
	{430,24,166,105,281,27,56,8,2,9,77,303,92,561,99,24,10,158,309,175,26,54,2,12,22,29} ,
	{130,0,0,0,82,0,0,0,20,0,1,0,0,0,74,0,0,0,0,0,44,0,1,0,2,0} ,
	{266,0,0,0,157,0,0,8,122,0,7,7,0,3,72,0,0,18,7,3,17,0,2,0,38,0} ,
	{540,22,9,70,439,11,6,5,496,1,11,309,26,1,199,10,0,3,23,35,63,32,5,0,137,0} ,
	{511,29,4,2,167,1,0,2,217,0,1,6,22,4,123,11,0,6,3,0,28,0,0,0,25,0} ,
	{625,1,71,227,392,5,95,13,295,13,14,14,0,243,129,0,1,10,33,130,29,2,4,1,74,12} ,
	{27,27,35,61,23,7,10,28,18,3,38,173,62,500,23,28,0,338,104,43,37,35,33,7,27,10} ,
	{93,0,0,0,75,0,0,72,33,0,0,7,0,1,21,13,0,31,3,3,5,0,0,0,4,0} ,
	{4,0,0,0,1,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,51,0,2,0,0,0} ,
	{491,22,37,84,333,3,37,13,561,5,20,91,47,71,223,5,0,110,44,81,61,29,14,1,114,3} ,
	{233,5,24,4,151,0,1,227,123,0,14,28,23,6,89,21,0,3,90,186,43,5,5,0,27,1} ,
	{366,2,10,0,214,1,1,183,155,2,2,11,1,6,174,0,0,88,9,103,38,0,4,0,59,5} ,
	{38,17,32,39,52,5,19,3,37,4,15,82,39,75,11,11,0,103,120,21,0,8,2,2,17,10} ,
	{163,0,0,0,141,0,0,0,169,0,1,5,0,0,27,0,0,7,0,0,2,1,0,0,9,0} ,
	{73,0,0,2,57,0,0,10,57,0,1,2,1,11,11,0,0,6,4,1,0,0,0,0,23,2} ,
	{22,0,0,0,11,0,0,1,24,0,0,1,1,0,6,0,0,0,0,7,4,0,1,0,3,0} ,
	{151,6,10,23,45,0,2,0,10,0,3,82,13,130,42,4,0,35,35,17,12,4,1,1,1,0} ,
	{89,2,0,0,46,0,0,5,52,1,0,4,0,0,23,0,0,3,2,0,22,0,2,0,7,7}
};

const int default_max_namelen 	= 7;
const int default_min_namelen 	= 5;
const int default_count_names	= 1;

// Выводит двухмерный вектор какой-то хуйни
template <class VectorType>
void print_out(const std::vector< std::vector<VectorType> >& print_vector)
{
	std::for_each(print_vector.cbegin(), print_vector.cend(), [](const std::vector<VectorType>& curr_row)
	{
		std::for_each(curr_row.cbegin(), curr_row.cend(), [](const VectorType& curr_cell)
		{
			std::cout << std::left << std::setw(5) << curr_cell;
		});

		std::cout << std::endl;
	});
};

void create_letters(const std::vector< std::vector<int> >& weights, std::vector< std::vector<int> >& letters)
{
	int cvar, tvar;

	for (int row = 0; row < 26; row++)
	{
		cvar = tvar = 0;

		for (int col = 0; col < 26; col++)
			cvar += weights[row][col];

		for (int col = 0; col < 26; col++) {
			tvar += weights[row][col];
			letters[row][col] = static_cast<int>(static_cast<float>(tvar) / cvar * 1000);
		}
	}
}

std::string gen_name(const std::vector< std::vector<int> >& letters, const int& namelen)
{
	std::string name = "";
	std::vector<int> curar;
	int firstchar, nextchar, curchar;

	curchar = rand() % 26;

	firstchar = curchar;

	for (int cnt = 0; cnt < namelen; cnt++)
	{
		int ran = rand() % 1000;
		nextchar = 0;
		curar = letters[firstchar];

		while (ran >= static_cast<int>(curar[nextchar]))
			nextchar++;

		firstchar = nextchar;
		name += 97 + nextchar;
	}

	return name;
}

void can_generate_n_unique_names(const std::vector< std::vector<int> >& letters, const int& namelen, const int& count_names)
{
	std::vector<std::string> test_names;

	for (int name_idx = 1; name_idx <= count_names; name_idx++)
	{
		std::string curr_name = gen_name(letters, namelen);
		curr_name[0] = toupper(curr_name[0]);

		test_names.push_back(curr_name);

		std::cout << name_idx << "." << std::left << test_names.back() << std::endl;
	}

	// Проверяем на уникальность 10000 ников
	std::map<std::string, int> count;

	for (int name_idx = 0; name_idx < count_names; name_idx++)
		count[test_names[name_idx]]++;

	// Ищем повторяющиеся ники
	auto it = std::find_if(count.cbegin(), count.cend(), [] (const std::pair<std::string, int>& value) -> bool
	{
		return value.second > 1? true: false;
	});

	std::cout << std::endl;
	if(it == count.end())
		std::cout << count_names << " unique names generated successfully." << std::endl;
	else
		std::cout << ":(" << std::endl;
}

void process_cmd_args(int argc, char* argv[], int& count, int& min, int& max)
{
    switch (argc) {
        case 1:
            count 	= default_count_names;
            min		= default_min_namelen;
            max 	= default_max_namelen;
            return;
        case 2:
            count 	= atoi(argv[1]);
            min		= default_min_namelen;
            max 	= default_max_namelen;
            return;
        case 3:
            count 	= atoi(argv[1]);
            min		= atoi(argv[2]);
            max 	= atoi(argv[2]);
            return;
        case 4:
            count 	= atoi(argv[1]);
            min		= atoi(argv[2]);
            max 	= atoi(argv[3]);
            return;
        default:
            throw std::invalid_argument("Invalid arguments count!");
    }

	// Процессим аргументы
	/*if ( (argc != 4) && (argc != 1) && (argc != 2) && (argc != 3))
		throw std::invalid_argument("Invalid arguments count!");

	int temp_argv1;
	int temp_argv2;
	int temp_argv3;

	if (4 == argc)
	{
		temp_argv1 = atoi(argv[1]);
		temp_argv2 = atoi(argv[2]);
		temp_argv3 = atoi(argv[3]);

		if (temp_argv1 <= 0)
			throw std::invalid_argument("Invalid names count!");

		if ( (temp_argv2 <= 0) || (temp_argv3 <= 0) )
			throw std::invalid_argument("Invalid length!");

		count 	= temp_argv1;
		min 	= temp_argv2;
		max 	= temp_argv3;

		if (min > max)
			throw std::invalid_argument("Invalid range!");

		return;
	}

	if (1 == argc)
	{
		count 	= default_count_names;
		min		= default_min_namelen;
		max 	= default_max_namelen;

		return;
	}

	if (2 == argc)
	{
		count 	= atoi(argv[1]);
		min		= default_min_namelen;
		max 	= default_max_namelen;

		return;
	}

	if (3 == argc)
	{
		count 	= atoi(argv[1]);
		min		= atoi(argv[2]);
		max 	= atoi(argv[2]);

		return;
	}*/
}

int main(int argc, char* argv[])
{
	srand(time(0));
	// Инициализируем вектор 26х26 для букв?
	std::vector< std::vector<int> > letters(26, std::vector<int>(26));
	int max_namelen;
	int min_namelen;
	int count_names;
	int namelen;

	try
	{
		process_cmd_args(argc, argv, count_names, min_namelen, max_namelen);
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}

	// Создаем буквы?
	create_letters(weights, letters);

	// Генерируем ник(-и)
	for (int curr_name = 0; curr_name < count_names; curr_name++)
	{
		namelen = rand() % (max_namelen - min_namelen + 1) + min_namelen;

		std::string name = gen_name(letters, namelen);
		name[0] = toupper(name[0]);

		std::cout << name << std::endl;
	}

	// Тест на уникальность (10.000 ников)
	//can_generate_n_unique_names(letters, 9, 10000);

	//system("pause");

	return 0;
}

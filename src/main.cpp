#include "IOperation.hpp"
#include <memory>
#include <vector>
#include <iostream>
#include <sstream>

int main(int argc, char* argv[])
{
	std::vector<std::shared_ptr<IOperation>> operations;
	std::istringstream iss(argv[1]);
	std::vector<std::string> parsed_arg;
	std::string curr_arg;
	for (int i = 0; getline(iss, curr_arg, '|'); i++)
	{
		parsed_arg.push_back(curr_arg);
	}
	for (int i = 0; i < parsed_arg.size(); i++)
	{
		std::istringstream iss(parsed_arg[i]);
		getline(iss, curr_arg, ' ');
		if (curr_arg.empty())
			getline(iss, curr_arg, ' ');
		if (curr_arg == "echo")
		{
			operations.push_back(std::make_shared<EchoOperation>());
			getline(iss, curr_arg, ' ');
			operations.back()->ProcessLine(curr_arg);
		}
		else if (curr_arg == "cat")
		{
			getline(iss, curr_arg, ' ');
			operations.push_back(std::make_shared<CatOperation>(curr_arg));
		}
		else if (curr_arg == "wc")
		{
			getline(iss, curr_arg, ' ');
			getline(iss, curr_arg, ' ');
			operations.push_back(std::make_shared<WcOperation>());
			operations.back()->ProcessLine(curr_arg);
		}
		else
		{
			std::cout << "Wrong input" << curr_arg << std::endl;
			return 0;
		}
		if(operations.size() > 1)
			operations[operations.size() - 2]->SetNextOperation(operations[operations.size() - 1]);
	}
	operations[0]->HandleEndOfInput();
	return 0;
}

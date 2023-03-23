#include "IOperation.hpp"
#include <memory>
#include <vector>
#include <iostream>
#include <sstream>

int main(int argc, char* argv[])
{
	std::vector<std::shared_ptr<IOperation>> operations;
	std::string curr_arg;
	std::istringstream iss(argv[1]);
	for (int i = 0; getline(iss, curr_arg, ' '); i++)
	{
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
			operations.push_back(std::make_shared<wcOperation>(curr_arg));
		}
		else if (curr_arg == "|")
		{
			getline(iss, curr_arg, ' ');
			if (curr_arg == "echo")
			{
				getline(iss, curr_arg, ' ');
				operations.push_back(std::make_shared<EchoOperation>());
				operations.back()->ProcessLine(curr_arg);
				operations[operations.size() - 2]->SetNextOperation(operations[operations.size() - 1]);
			}
			else if (curr_arg == "cat")
			{
				getline(iss, curr_arg, ' ');
				operations.push_back(std::make_shared<CatOperation>(curr_arg));
				operations[operations.size() - 2]->SetNextOperation(operations[operations.size() - 1]);
			}
			else if (curr_arg == "wc")
			{
				getline(iss, curr_arg, ' ');
				getline(iss, curr_arg, ' ');
				operations.push_back(std::make_shared<wcOperation>(curr_arg));
				operations[operations.size() - 2]->SetNextOperation(operations[operations.size() - 1]);
			}
		}
	}
	operations[0]->HandleEndOfInput();
	return 0;
}
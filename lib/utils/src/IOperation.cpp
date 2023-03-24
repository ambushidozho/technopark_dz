#include "IOperation.hpp"
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

bool isNumeric(std::string const& str)
{
	return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}


void EchoOperation::ProcessLine(const std::string& str)
{
	buff.push_back(str);
}
void EchoOperation::HandleEndOfInput()
{
	if (next_ == nullptr)
	{
		std::cout << buff[0] << std::endl;
	}
	else
	{
		next_->ProcessLine(buff[0]);
		next_->ProcessLine("\n");
		next_->HandleEndOfInput();
	}
	
}
void EchoOperation::SetNextOperation(std::shared_ptr<IOperation> next)
{
	next_ = next;
}



CatOperation::CatOperation()
{

}
CatOperation::CatOperation(const std::string& filename)
{
	filename_ = filename;
}
void CatOperation::ProcessLine(const std::string& str)
{
	buff.push_back(str);
}
void CatOperation::HandleEndOfInput()
{
	std::ifstream fin;
	fin.open(filename_);
	std::string token;
	if (fin.is_open())
	{
		while (getline(fin,token))
		{
			buff.push_back(token);
		}
	}
	fin.close();
	if (next_ == nullptr)
	{
		for (auto& el : buff)
		{
			std::cout << el;
		}
		std::cout << std::endl;
	}
	else
	{
		for (auto& el : buff)
		{
			next_->ProcessLine(el);
		}
		next_->ProcessLine("\n");
		next_->HandleEndOfInput();
	}
}
void CatOperation::SetNextOperation(std::shared_ptr<IOperation> next)
{
	next_ = next;
}




wcOperation::wcOperation(const std::string& str)
{
	size = 0;
	ProcessLine(str);
}
void wcOperation::ProcessLine(const std::string& str)
{
	if (str == "\n")
	{

	}
	else
	{
		if (isNumeric(str))
		{
			size += sizeof(std::stoi(str));
		}
		else
		{
			size += str.size();
		}
	}
}
void wcOperation::HandleEndOfInput()
{
	if (next_ == nullptr)
	{
		std::cout << size << std::endl;
	}
	else
	{
		next_->ProcessLine(std::to_string(size));
		next_->ProcessLine("\n");
		next_->HandleEndOfInput();
	}
}
void wcOperation::SetNextOperation(std::shared_ptr<IOperation> next)
{
	next_ = next;
}




#include "IOperation.hpp"
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>




void EchoOperation::ProcessLine(const std::string& str)
{
	str_ = str;
}
void EchoOperation::HandleEndOfInput()
{
	if (next_ == nullptr)
	{
		std::cout << str_ << std::endl;
	}
	else
	{
		next_->ProcessLine(str_ + "\n");
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
	ProcessLine(str);
	size = 0;
}
void wcOperation::ProcessLine(const std::string& str)
{
	buff.push_back(str);
}
void wcOperation::HandleEndOfInput()
{
	if (next_ == nullptr)
	{
		for (auto& el : buff)
		{
			size += sizeof(el);
		}
		std::cout << size;
	}
	else
	{
		for (auto& el : buff)
		{
			size += sizeof(el);
		}
		next_->ProcessLine(std::to_string(size));
		next_->ProcessLine("\n");
		next_->HandleEndOfInput();
	}
}
void wcOperation::SetNextOperation(std::shared_ptr<IOperation> next)
{
	next_ = next;
}




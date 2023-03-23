
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class IOperation
{
public:
	void virtual ProcessLine(const std::string& str) = 0;
	void virtual HandleEndOfInput() = 0;
	void virtual SetNextOperation(std::shared_ptr<IOperation> IOperation) = 0;
private:

};

class EchoOperation : public IOperation
{
public:
	void ProcessLine(const std::string& str) override;
	void HandleEndOfInput() override;
	void SetNextOperation(std::shared_ptr<IOperation> next) override;
private:
	std::shared_ptr<IOperation> next_;
	std::string str_;
};


class CatOperation : public IOperation
{
public:
	CatOperation();
	CatOperation(const std::string& filename);
	void ProcessLine(const std::string& str) override;
	void HandleEndOfInput() override;
	void SetNextOperation(std::shared_ptr<IOperation> next) override;

private:
	std::shared_ptr<IOperation> next_;
	std::string filename_;
	std::vector<std::string> buff;
};


class wcOperation : public IOperation
{
public:
	wcOperation(const std::string& str);
	void ProcessLine(const std::string& str) override;
	void HandleEndOfInput() override;
	void SetNextOperation(std::shared_ptr<IOperation> next) override;

private:
	std::shared_ptr<IOperation> next_;
	int size;
	std::vector<std::string> buff;
};



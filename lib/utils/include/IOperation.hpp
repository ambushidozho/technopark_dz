
#include <string>
#include <memory>
#include <vector>

bool isNumeric(std::string const& str);

class IOperation
{
public:
	void virtual ProcessLine(const std::string& str) = 0;
	void virtual HandleEndOfInput() = 0;
	void virtual SetNextOperation(std::shared_ptr<IOperation> IOperation) = 0;
};

class EchoOperation : public IOperation
{
public:
	void ProcessLine(const std::string& str) override;
	void HandleEndOfInput() override;
	void SetNextOperation(std::shared_ptr<IOperation> next) override;
private:
	std::shared_ptr<IOperation> next_;
	std::vector<std::string> buff;
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


class WcOperation : public IOperation
{
public:
	WcOperation();
	void ProcessLine(const std::string& str) override;
	void HandleEndOfInput() override;
	void SetNextOperation(std::shared_ptr<IOperation> next) override;

private:
	std::shared_ptr<IOperation> next_;
	int size;
	std::vector<std::string> buff;
};



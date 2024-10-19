#pragma once
#include <string>
#include <vector>

class OpenARG
{
public:
	using item_t = struct
	{
		std::string Name;
		std::string Value;
	};
	using data_t = struct
	{
	};

public:
	OpenARG(int argc, char** argv);
	OpenARG(std::string const& args);
	~OpenARG();

	item_t const& item(size_t index) const;
	std::vector<item_t> const& items() const;
	bool exist(std::string const& name) const;
	bool index(std::string const& name, size_t& result) const;
	bool index(std::string const& name, std::vector<size_t>& result) const;
	std::string value(std::string const& name, std::string const& value = std::string()) const;
	std::vector<std::string> value(std::string const& name, std::vector<std::string> const& value = {}) const;

protected:
	data_t* m_Private;
};
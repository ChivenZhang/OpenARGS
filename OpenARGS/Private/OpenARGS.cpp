#include "OpenARGS.h"

struct OpenARGSPrivate : public OpenARGS::data_t
{
	std::vector<OpenARGS::item_t> Items;
};
#define PRIVATE() ((OpenARGSPrivate*)m_Private)

OpenARGS::OpenARGS(int argc, char** argv)
{
	m_Private = new OpenARGSPrivate;

	std::vector<item_t> items;
	for (size_t i = 0; i < argc && argv && argv[i]; ++i)
	{
		std::string text((const char*)argv[i]);

		auto index = text.find('=');
		if (index == std::string::npos)
		{
			auto& item = items.emplace_back();

			if (text.size() && text[0] == '-')
			{
				auto name = text;
				if (name.size() && name[0] == '-') name = name.substr(1);
				if (name.size() && name[0] == '-') name = name.substr(1);
				if (name.size() && name[0] == '"') name = name.substr(1);
				if (name.size() && name[name.size() - 1] == '"') name = name.substr(0, name.size() - 1);
				item.Name = name;
			}
			else
			{
				auto value = text;
				if (value.size() && value[0] == '"') value = value.substr(1);
				if (value.size() && value[value.size() - 1] == '"') value = value.substr(0, value.size() - 1);
				item.Value = value;
			}
		}
		else
		{
			auto& item = items.emplace_back();

			auto name = text.substr(0, index);
			auto value = text.substr(index + 1);

			if (name.size() && name[0] == '-') name = name.substr(1);
			if (name.size() && name[0] == '-') name = name.substr(1);
			if (name.size() && name[0] == '"') name = name.substr(1);
			if (name.size() && name[name.size() - 1] == '"') name = name.substr(0, name.size() - 1);
			item.Name = name;

			if (value.size() && value[0] == '"') value = value.substr(1);
			if (value.size() && value[value.size() - 1] == '"') value = value.substr(0, value.size() - 1);
			item.Value = value;
		}
	}

	PRIVATE()->Items = std::move(items);
}

OpenARGS::OpenARGS(std::string const& args)
{
	std::vector<std::string> items;

	bool comma = false;
	for (size_t i = 0, s = 0; i < args.size(); ++i)
	{
		auto code = args[i];
		if (code == '"') comma = !comma;
		auto split = (code == ' ' || code == '\f' || code == '\n' || code == '\r' || code == '\t' || code == '\v' || code == '\0' || code == EOF);
		if (comma == false && split)
		{
			if (i != s) items.push_back(args.substr(s, (i - s)));
			s = i + 1;
		}
		else
		{
			if (i + 1 == args.size()) items.push_back(args.substr(s));
		}
	}

	std::vector<const char*> newArgs;
	for (size_t i = 0; i < items.size(); ++i) newArgs.push_back(items[i].c_str());
	auto argc = (int32_t)newArgs.size();
	auto argv = const_cast<char**>(newArgs.data());
	new (this)OpenARGS(argc, argv);
}

OpenARGS::~OpenARGS()
{
	delete m_Private; m_Private = nullptr;
}

OpenARGS::item_t const& OpenARGS::item(size_t index) const
{
	static const item_t NonItem;
	if (index < PRIVATE()->Items.size()) return PRIVATE()->Items[index];
	return NonItem;
}

std::vector<OpenARGS::item_t> const& OpenARGS::items() const
{
	return PRIVATE()->Items;
}

bool OpenARGS::exist(std::string const& name) const
{
	auto& items = PRIVATE()->Items;
	auto result = std::find_if(items.begin(), items.end(), [&name](item_t& e)->bool { return e.Name == name; });
	if (result == items.end()) return false;
	return true;
}

bool OpenARGS::index(std::string const& name, size_t& index) const
{
	auto& items = PRIVATE()->Items;
	auto result = std::find_if(items.begin(), items.end(), [&name](item_t& e)->bool { return e.Name == name; });
	if (result == items.end()) return false;
	index = std::distance(items.begin(), result);
	return true;
}

bool OpenARGS::index(std::string const& name, std::vector<size_t>& result) const
{
	auto size = result.size();
	auto& items = PRIVATE()->Items;
	for (size_t i = 0; i < items.size(); ++i)
		if (items[i].Name == name) result.push_back(i);
	return size != result.size();
}

std::string OpenARGS::value(std::string const& name, std::string const& value) const
{
	auto& items = PRIVATE()->Items;
	auto result = std::find_if(items.begin(), items.end(), [&name](item_t& e)->bool { return e.Name == name; });
	if (result == items.end()) return value;
	return (*result).Value;
}

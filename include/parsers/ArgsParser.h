#ifndef ARGSPARSER_H_
#define ARGSPARSER_H_

#include <string>
#include <list>
#include <map>
#include <functional>

#include "utility/ArgsUtility.h"

struct ArgsInfo
{
	std::string fen;
	unsigned int window_width;
	unsigned int window_height;
	bool fullscreen;
};

class ArgsParser
{
public:
	ArgsParser(const std::list<std::string>& args);

	ArgsInfo Parse();

	const std::list<std::string>& get_args() const;
	void set_args(const std::list<std::string>& args);

private:
	void ParseWidth(const std::string& width);
	void ParseHeight(const std::string& height);
	void ParseSize(const std::string& size);

	std::list<std::string> m_args;
	ArgsInfo m_args_info;

	std::map<std::string, std::function<void(const std::string&)>> m_args_handlers;
};

#endif //ARGSPARSER_H_

#include "parsers/ArgsParser.h"

ArgsParser::ArgsParser(const std::list<std::string>& args)
	: m_args{ args }
	, m_args_info{}
{
    m_args_handlers["-h"] = m_args_handlers["--help"] = [](const std::string& program_name){ ISXUtility::PrintHelp(program_name); };
    m_args_handlers["-v"] = m_args_handlers["--version"] = [](const std::string&){ ISXUtility::PrintVersion(); };
    m_args_handlers["-f"] = m_args_handlers["--fen"] = [this](const std::string& fen){ m_args_info.fen = fen; };
    m_args_handlers["-W"] = m_args_handlers["--width"] = [this](const std::string& width){ ParseWidth(width); };
    m_args_handlers["-H"] = m_args_handlers["--height"] = [this](const std::string& height){ ParseHeight(height); };
    m_args_handlers["-S"] = m_args_handlers["--size"] = [this](const std::string& size){ ParseSize(size); };
    m_args_handlers["-F"] = m_args_handlers["--fullscreen"] = [this](const std::string&){ m_args_info.fullscreen = true; };
}

ArgsInfo ArgsParser::Parse()
{
    m_args_info = {};

    if (m_args.size() < 2)
    {
        return m_args_info;
    }

    std::list<std::string>::iterator it = m_args.begin();
    const std::string& program_name = *it;

    ++it;

    for (; it != m_args.end(); ++it)
    {
        const std::string& arg = *it;

        if (m_args_handlers.find(arg) == m_args_handlers.end())
        {
            throw std::runtime_error("Invalid option: " + arg);
        }

        if (arg == "-h" || arg == "--help")
        {
            m_args_handlers[arg](program_name);
            continue;
        }
        else if (arg == "-v" || arg == "--version" || arg == "-F" || arg == "--fullscreen")
        {
            m_args_handlers[arg]("");
            continue;
        }

        const std::string& value = *++it;

        if (it == m_args.end())
        {
            throw std::runtime_error("Option " + arg + " needs a value");
        }
        else if (value[0] == '-')
        {
            throw std::runtime_error(value + " is not valid for option " + arg);
        }

        m_args_handlers[arg](value);
    }

    return m_args_info;
}

const std::list<std::string>& ArgsParser::get_args() const
{
	return this->m_args;
}

void ArgsParser::set_args(const std::list<std::string>& args)
{
	this->m_args = args;
}

void ArgsParser::ParseWidth(const std::string& width)
{
	char *width_ptr;
	m_args_info.window_width = std::strtoul(width.c_str(), &width_ptr, 10);

	if (*width_ptr)
	{
		throw std::runtime_error("Width is not a number");
	}
}

void ArgsParser::ParseHeight(const std::string& height)
{
	char *height_ptr;
	m_args_info.window_height = std::strtoul(height.c_str(), &height_ptr, 10);

	if (*height_ptr)
	{
		throw std::runtime_error("Height is not a number");
	}
}

void ArgsParser::ParseSize(const std::string& size)
{
    std::istringstream size_stream{ size };
    std::string width, height;

    std::getline(size_stream, width, 'x');
    std::getline(size_stream, height, 'x');

    if (size_stream.fail())
    {
        throw std::runtime_error("Invalid size format");
    }

    m_args_handlers["-W"](width);
    m_args_handlers["-H"](height);
}

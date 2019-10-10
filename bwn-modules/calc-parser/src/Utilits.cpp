#include "Utilits.h"
#include "Exceptions.h"

#include <cctype>

std::string bwn::calc_parser::ProcessStringLiteral(const std::string& str)
{
	std::string out;
	out.reserve(str.size());

	for (auto it = str.begin(); it != str.end(); ++it)
	{
		if (*it == '\\')
		{
			if (str.end() - it == 1) {
				throw ParserException{ "Incorect special character" };
			}

			char temp_char = 0;

			switch (*(it + 1))
			{
			case '\"':
				temp_char = '\"';
				break;
			case '?':
				temp_char = '\?';
				break;
			case '\\':
				temp_char = '\\';
				break;
			case '0':
				temp_char = '\0';
				break;
			case 'a':
				temp_char = '\a';
				break;
			case 'b':
				temp_char = '\b';
				break;
			case 'f':
				temp_char = '\f';
				break;
			case 'n':
				temp_char = '\n';
				break;
			case 'r':
				temp_char = '\r';
				break;
			case 't':
				temp_char = '\t';
				break;
			case 'v':
				temp_char = '\v';
				break;
			case 'x':

				if (str.end() - it < 3) {
					throw ParserException{ "Incorect special character" };
				}

				try
				{
					temp_char = static_cast<char>(std::stoull(std::string(it + 1, it + 3), nullptr, 16));
				}
				catch (const std::exception&)
				{
					throw ParserException{ "Incorect special character" };
				}

				it += 2;
				break;

			default:
				if (std::isdigit(*it))
				{
					if (str.end() - it < 3) {
						throw ParserException{ "Incorect special character" };
					}

					try
					{
						temp_char = static_cast<char>(std::stoull(std::string(it, it + 3), nullptr, 8));
					}
					catch (const std::exception&)
					{
						throw ParserException{ "Incorect special character" };
					}

					it += 2;
				}
				else 
				{
					throw ParserException{ "Incorect special character" };
				}

				break;
			}

			out.push_back(temp_char);
			++it;

			continue;
		}

		out.push_back(*it);
	}

	return out;
}

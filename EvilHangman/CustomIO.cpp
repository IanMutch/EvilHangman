#include "CustomIO.h"

/*
Returns true if the input argument is an integer with no other non numeric characters.
The integer value is passed back as the output argument.
*/
bool GetInputAsIntStrict(const std::string &input, int &output)
{
	for (auto const& c : input)
	{
		if (!isdigit(c))
		{
			return false;
		}
	}

	output = std::atoi(input.c_str());
	return true;
}
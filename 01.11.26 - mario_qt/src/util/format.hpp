#pragma once

#include <string>

namespace biv {
	std::string format_string(const std::string& format);

	template<typename T, typename... Args>
	std::string format_string(const std::string& format, T first, Args... rest);
}

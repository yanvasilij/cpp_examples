#include <iostream>
#include <memory>
#include <string>
#include <cstdarg>

std::string format (const char * format, ...)
{
	va_list args;
	va_start (args, format);
	ssize_t l = vsnprintf(nullptr, 0, format, args);
	va_end (args);

	auto buf = std::unique_ptr<char[]>{new char[l]};

	va_start (args, format);
	vsprintf(buf.get(), format, args);
	va_end (args);

	std::string s(buf.get());

	return s;
}

int main (void)
{
	char c_str[] = "one one one";
    auto s = format("Formated %x %d %s", 0xAA, 15, c_str);
    std::cout << s << std::endl;
	return 0;
}

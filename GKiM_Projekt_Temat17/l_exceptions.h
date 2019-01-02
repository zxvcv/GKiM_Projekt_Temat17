#ifndef L_EXCEPTIONS
#define L_EXCEPTIONS

#include <exception>
#include <string>

namespace MyRuntimeExceptions {

	class LoadImageException : public std::runtime_error
	{
	public:
		LoadImageException() : runtime_error("Blad pobrania obrazu\n") {}
		LoadImageException(std::string msg) : runtime_error(msg) {}
	};

	class ReadImageException : public std::runtime_error
	{
	public:
		ReadImageException() : runtime_error("Blad pobrania obrazu\n") {}
		ReadImageException(std::string msg) : runtime_error(msg) {}
	};

	class LoadFontException : public std::runtime_error
	{
	public:
		LoadFontException() : runtime_error("Blad pobrania czcionki\n") {}
		LoadFontException(std::string msg) : runtime_error(msg) {}
	};

}

#endif
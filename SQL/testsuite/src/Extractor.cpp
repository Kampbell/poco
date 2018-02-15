//
// Extractor.cpp
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Extractor.h"
#include "Poco/SQL/LOB.h"
#include "Poco/Exception.h"


namespace Poco {
namespace SQL {
namespace Test {


Extractor::Extractor()
{
}


Extractor::~Extractor()
{
}


bool Extractor::extract(std::size_t pos, Poco::Int8& val)
{
	val = 0;
	return true;
}


bool Extractor::extract(std::size_t pos, Poco::UInt8& val)
{
	val = 0;
	return true;
}


bool Extractor::extract(std::size_t pos, Poco::Int16& val)
{
	val = 0;
	return true;
}


bool Extractor::extract(std::size_t pos, Poco::UInt16& val)
{
	val = 0;
	return true;
}


bool Extractor::extract(std::size_t pos, Poco::Int32& val)
{
	val = 0;
	return true;
}


bool Extractor::extract(std::size_t pos, Poco::UInt32& val)
{
	val = 0;
	return true;
}


bool Extractor::extract(std::size_t pos, Poco::Int64& val)
{
	val = 0;
	return true;
}


bool Extractor::extract(std::size_t pos, Poco::UInt64& val)
{
	val = 0;
	return true;
}


bool Extractor::extract(std::size_t pos, bool& val)
{
	val = false;
	return true;
}


bool Extractor::extract(std::size_t pos, float& val)
{
	val = 0;
	return true;
}


bool Extractor::extract(std::size_t pos, double& val)
{
	val = 0;
	return true;
}


bool Extractor::extract(std::size_t pos, char& val)
{
	val = '\0';
	return true;
}


bool Extractor::extract(std::size_t pos, std::string& val)
{
	val = "";
	return true;
}


bool Extractor::extract(std::size_t pos, Poco::UTF16String& val)
{
	std::string str("");
	Poco::UnicodeConverter::convert(str, val);
	return true;
}


bool Extractor::extract(std::size_t pos, Poco::SQL::BLOB& val)
{
	return true;
}


bool Extractor::extract(std::size_t pos, Poco::SQL::CLOB& val)
{
	return true;
}

bool Extractor::extract(std::size_t pos, Poco::SQL::Date& val)
{
	return true;
}


bool Extractor::extract(std::size_t pos, Poco::SQL::Time& val)
{
	return true;
}



bool Extractor::extract(std::size_t pos, Poco::DateTime& val)
{
	return true;
}


bool Extractor::extract(std::size_t pos, Poco::Any& val)
{
	return true;
}


bool Extractor::extract(std::size_t pos, Poco::Dynamic::Var& val)
{
	return true;
}


} } } // namespace Poco::SQL::Test

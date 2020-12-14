#ifndef __SERIALIZE_MEMMORY_HPP__
#define __SERIALIZE_MEMMORY_HPP__

#include <cstring>
#include <string>

#include "def/basedef.hpp"

const int ONE_BYTE_LENTH = 8;
const int BYTE8_AND_RIGHT = 0x00000001;
const int BYTE4_AND_RIGHT = 0x0001;
const int FORMAT_NUM_HEX = 16;	//十六进制
const int HEX_TO_NUM_BY_BIN = 4;// 二进制 4 位计算16进制
const char HEX_OVER_START = 65;
const char HEX_OVER_END = HEX_OVER_START + 5;
const char HEX_SUB = 55;
const int HEX_STR_ARR_SIZE = FORMAT_NUM_HEX + 1;

typedef char HexFormat[HEX_STR_ARR_SIZE];
extern const HexFormat hex_f;
extern const char *hex_bin[FORMAT_NUM_HEX];

int FindCharFromHexStr(char _find, const std::string _input_hex_str);

std::string StrToBin(std::string &_input);

std::string BinToStr(std::string &_bin_str);

std::string BinToHex(std::string &_bin_str);

std::string HexToBin(std::string &_hex_str);

std::string StrToHex(std::string &_input_str);

std::string HexToStr(std::string &_input_hex);

template<class SeriStruct>
bool SerializationByMemory(SeriStruct &st, std::string &out_hex_str)
{
	std::string str_ = "";
	std::string bin_ = "";

	for (int idx = 0; idx < sizeof(SeriStruct); ++idx)
	{
		str_ += CastTo(std::string, (*(((const char*)(&st)) + idx)));
	}

	bin_ = StrToBin(std::string(str_));
	out_hex_str = BinToHex(bin_);
	if (out_hex_str.compare("") == 0)
	{
		return false;
	}

	return true;
}

template<class SeriStruct>
bool UnSerializationByMemory(SeriStruct &out_st, std::string &hex_str)
{
	std::string hex_bin = HexToBin(hex_str);
	std::string bin_str = BinToStr(hex_bin);

	char *p_get_sp = (char *)&out_st;

	memcpy(p_get_sp, bin_str.c_str(), sizeof(SeriStruct));

	if (strcmp(p_get_sp, bin_str.c_str()) == 0)
	{
		return false;
	}
	return true;
}

#endif // !__SERIALIZE_MEMMORY_HPP__

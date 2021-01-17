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
const HexFormat hex_f = "0123456789ABCDEF";
const char *hex_bin[FORMAT_NUM_HEX] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111", };

int FindCharFromHexStr(char _find, const HexFormat _input_hex_str)
{
	for (int i = 0; i < strlen(_input_hex_str); ++i)
	{
		if (_input_hex_str[i] == _find) return i;
	}
	return -1;
}

std::string StrToBin(std::string &_input)
{
	std::string STRING_TO_BINARY;
	for (int i = _input.size() - 1; i >= 0; --i)
	{
		for (int j = 0; j < ONE_BYTE_LENTH; ++j)
		{
			if (((_input[i] >> j)&BYTE8_AND_RIGHT) == BYTE8_AND_RIGHT)
			{
				STRING_TO_BINARY += "1";
			} else
			{
				STRING_TO_BINARY += "0";
			}
		}
	}
	reverse(STRING_TO_BINARY.begin(), STRING_TO_BINARY.end());
	return STRING_TO_BINARY;
}

std::string BinToStr(std::string &_bin_str)
{
	std::string BINARY_TO_STRING;
	int get_pow = 0;

	int begin = 0;
	int end = ONE_BYTE_LENTH;
	for (int i = begin; i < end; ++i)
	{
		if (_bin_str[i] == '1')
		{
			get_pow += int(pow(2, (end - 1) - i));
		}
		if (i == end - 1)
		{
			BINARY_TO_STRING += boost::lexical_cast<std::string>(char(get_pow));
			get_pow = 0;

			if (end + ONE_BYTE_LENTH <= _bin_str.size())
			{
				end += ONE_BYTE_LENTH;
			}

		}

	}
	return BINARY_TO_STRING;
}

std::string BinToHex(std::string &_bin_str)
{
	std::string BINARY_TO_HEX = "0x";
	int get_hex_num = 0;

	int begin_h = 0;
	int end_h = HEX_TO_NUM_BY_BIN;

	for (int i = begin_h; i < end_h; ++i)
	{
		if (_bin_str[i] == '1')
		{
			get_hex_num += int(pow(2, (end_h - 1) - i));
		}

		if (i == end_h - 1)
		{
			BINARY_TO_HEX += boost::lexical_cast<std::string>(hex_f[get_hex_num]);
			get_hex_num = 0;

			if (end_h + HEX_TO_NUM_BY_BIN <= _bin_str.size())
			{
				end_h += HEX_TO_NUM_BY_BIN;
			}

		}
	}
	return BINARY_TO_HEX;
}

std::string HexToBin(std::string &_hex_str)
{
	std::string HEX_TO_BIN_STRNG;
	int get_num = 0;
	for (int i = 0; i < _hex_str.size(); ++i)
	{
		if (i == 0)
		{
			if (_hex_str[i] == '0' && _hex_str[i + 1] == 'x') continue;;
		} else if (i == 1)
		{
			if (_hex_str[i] == 'x' && _hex_str[i - 1] == '0') continue;
		}

		if (_hex_str[i] >= 0 && _hex_str[i] < 10)
		{
			const char *tmp_str = hex_bin[boost::lexical_cast<int>(_hex_str[i])];
			HEX_TO_BIN_STRNG += boost::lexical_cast<std::string>(tmp_str);
		} else
		{
			int index = FindCharFromHexStr(_hex_str[i], hex_f);
			if (index != -1)
			{
				const char *tmp_str = hex_bin[index];
				HEX_TO_BIN_STRNG += boost::lexical_cast<std::string>(tmp_str);
			}

		}

	}

	return HEX_TO_BIN_STRNG;
}

std::string StrToHex(std::string &_input_str)
{
	std::string bin_tmp = StrToBin(_input_str);
	return BinToHex(bin_tmp);
}

std::string HexToStr(std::string &_input_hex)
{
	std::string hex_tmp = HexToBin(_input_hex);
	return BinToStr(hex_tmp);
}

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

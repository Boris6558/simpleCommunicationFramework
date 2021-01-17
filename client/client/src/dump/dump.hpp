#ifndef __DUMP_HPP__
#define __DUMP_HPP__

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>
#include <DbgHelp.h>
#pragma comment(lib, "dbghelp.lib")

#ifdef UNICODE
#define TSprintf wsprintf
#else
#define TSprintf sprintf
#endif

class MiniDump	//!< dmp �����ļ����
{
private:
	MiniDump();
	~MiniDump();

public:
	// �������ʱ�Ƿ������Զ�����dump�ļ�;
	// ֻ��Ҫ��main������ʼ�����øú�������;
	static void EnableAutoDump(bool bEnable = true);

private:

	static LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException);

	static void CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException);
};

#endif // !__DUMP_HPP__
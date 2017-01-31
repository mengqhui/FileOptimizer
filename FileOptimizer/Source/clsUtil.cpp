// --------------------------------------------------------------------------
/*
 3.42. 12/01/2017. FileOptimizer. Allow writting comments in .INI files
 3.41. 08/08/2016. FileOptimizer. Added ShutdownWindows
 3.40. 27/12/2015. FileOptimizer. Added GetWindowsVersion since GetVersion on Windows 8.1 or later do not work unless application is manifested
 3.30. 05/05/2015. FileOptimizer. Added 64 bit version of GetIni/SetIni. Added MemMem, CopyFile
 3.25. 05/04/2015. FileOptimizer. Added Random
 3.20. 14/03/2015. FileOptimizer. Added Serialize and Unserialize
 3.10. 20/01/2015. FileOptimizer. Minor tweaks and fixes
 3.00. 23/09/2012. FileOptimizer. Added LoadForm, SaveForm, CopyToRecycleBin, SetTaskListProgress
 2.00. 09/08/2012. FileOptimizer. Added clsUtil static class wrapper, optimized SizeFile, mapped to TCHAR and merged clsPreferences common functions
 1.00. 18/08/2011. TBClamAV. Initial version
 */
// ---------------------------------------------------------------------------
#include "FileOptimizerPCH1.h"


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::ReplaceString(const TCHAR *pacString, const TCHAR *pacSearch, const TCHAR *pacReplace)
{
	 return(StringReplace(pacString, pacSearch, pacReplace, TReplaceFlags() << rfReplaceAll).c_str());

	/*
	TCHAR *tok;
	TCHAR *newstr;
	TCHAR *oldstr;
	newstr = _tcsdup(pacString);
	while ((tok = _tcsstr(newstr, pacSearch)) != NULL)
	{
		oldstr = newstr;
		newstr = new TCHAR[_tcslen(oldstr) - _tcslen(pacSearch) + _tcslen(pacReplace) + 1];
		memcpy(newstr, oldstr, (tok - oldstr) * sizeof(TCHAR));
		memcpy(newstr + (tok - oldstr), pacReplace, _tcslen(pacReplace) * sizeof(TCHAR));
		memcpy(newstr + (tok - oldstr) + _tcslen(pacReplace) * sizeof(TCHAR), tok + _tcslen(pacSearch),
			_tcslen(oldstr) - _tcslen(pacSearch) - (tok - oldstr));
		memset(newstr + _tcslen(oldstr) - _tcslen(pacSearch) + _tcslen(pacReplace), 0, 1);
		delete oldstr;
	}
	return newstr;
	*/
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void * __fastcall clsUtil::MemMem (const void *buf, size_t buf_len, const void *byte_sequence, size_t byte_sequence_len)
{
	unsigned char *bf = (unsigned char *) buf;
	unsigned char *bs = (unsigned char *) byte_sequence;
	unsigned char *p  = bf;

	while (byte_sequence_len <= (buf_len - (p - bf)))
	{
		unsigned int b = *bs & 0xFF;
		if ((p = (unsigned char *) memchr(p, b, buf_len - (p - bf))) != NULL)
		{
			if ((memcmp(p, byte_sequence, byte_sequence_len)) == 0)
			{
				return (p);
			}
			else  
			{
				p++;
			}
		}
		else
		{
			break;
		}
	}
	return (NULL);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int __fastcall clsUtil::MsgBox(HWND phWnd, const TCHAR *pacText, const TCHAR *pacTitle, int piType)
{
	int iButton = 0;
	Winapi::Commctrl::TASKDIALOGCONFIG udtFlags = {};


	HMODULE hDLL = LoadLibrary(_T("COMCTL32.DLL"));
	if (hDLL)
	{
		typedef int (WINAPI TaskDialogType)(const Winapi::Commctrl::TASKDIALOGCONFIG *pTaskConfig, int *pnButton, int *pnRadioButton, bool *pfVerificationFlagChecked);
		TaskDialogType *TaskDialogProc = (TaskDialogType *) GetProcAddress(hDLL, "TaskDialogIndirect");
		if (TaskDialogProc)
		{
			udtFlags.cbSize = sizeof(udtFlags);
			udtFlags.hwndParent = phWnd;
			udtFlags.dwFlags = TDF_ALLOW_DIALOG_CANCELLATION | TDF_CAN_BE_MINIMIZED | TDF_SIZE_TO_CONTENT;

			if ((piType & MB_ABORTRETRYIGNORE) == MB_ABORTRETRYIGNORE)
			{
				udtFlags.dwCommonButtons = TDCBF_CANCEL_BUTTON | TDCBF_RETRY_BUTTON | TDCBF_CLOSE_BUTTON;
				udtFlags.nDefaultButton = IDRETRY;
				iButton = IDCANCEL;
			}
			else if ((piType & MB_CANCELTRYCONTINUE) == MB_CANCELTRYCONTINUE)
			{
				udtFlags.dwCommonButtons = TDCBF_CANCEL_BUTTON | TDCBF_RETRY_BUTTON | TDCBF_OK_BUTTON;
				udtFlags.nDefaultButton = IDRETRY;
				iButton = IDCANCEL;
			}
			else if ((piType & MB_OKCANCEL) == MB_OKCANCEL)
			{
				udtFlags.dwCommonButtons = TDCBF_OK_BUTTON | TDCBF_CANCEL_BUTTON;
				udtFlags.nDefaultButton = IDOK;
				iButton = IDCANCEL;
			}
			else if ((piType & MB_RETRYCANCEL) == MB_RETRYCANCEL)
			{
				udtFlags.dwCommonButtons = TDCBF_RETRY_BUTTON | TDCBF_CANCEL_BUTTON;
				udtFlags.nDefaultButton = IDRETRY;
				iButton = IDCANCEL;
			}
			else if ((piType & MB_YESNO) == MB_YESNO)
			{
				udtFlags.dwCommonButtons = TDCBF_YES_BUTTON | TDCBF_NO_BUTTON;
				udtFlags.nDefaultButton = IDYES;
				iButton = IDNO;
			}
			else if ((piType & MB_YESNOCANCEL) == MB_YESNOCANCEL)
			{
				udtFlags.dwCommonButtons = TDCBF_YES_BUTTON | TDCBF_NO_BUTTON | TDCBF_CANCEL_BUTTON;
				udtFlags.nDefaultButton = IDYES;
				iButton = IDCANCEL;
			}
			else
			{
				udtFlags.dwCommonButtons = TDCBF_OK_BUTTON;
				udtFlags.nDefaultButton = IDOK;
				iButton = IDOK;
			}

			if (((piType & MB_ICONEXCLAMATION) == MB_ICONEXCLAMATION) || ((piType & MB_ICONWARNING) == MB_ICONWARNING))
			{
				udtFlags.pszMainIcon = TD_WARNING_ICON;
			}
			else if (((piType & MB_ICONINFORMATION) == MB_ICONINFORMATION) || ((piType & MB_ICONASTERISK) == MB_ICONASTERISK))
			{
				udtFlags.pszMainIcon = TD_INFORMATION_ICON;
			}
			else if (((piType & MB_ICONSTOP) == MB_ICONSTOP) || ((piType & MB_ICONERROR) == MB_ICONERROR) || ((piType & MB_ICONHAND) == MB_ICONHAND))
			{
				udtFlags.pszMainIcon = TD_ERROR_ICON;
			}
			//else if ((piType & MB_ICONQUESTION) == MB_ICONQUESTION)
			else
			{
				udtFlags.pszMainIcon = NULL;
			}

			udtFlags.pszWindowTitle = (TCHAR *) pacTitle;
			if (_tcslen(pacText) < 256)
			{
				udtFlags.pszMainInstruction = (TCHAR *) pacText;
			}
			else
			{
				udtFlags.pszMainInstruction = (TCHAR *) pacTitle;
				udtFlags.pszContent = (TCHAR *) pacText;
			}
			(*TaskDialogProc)(&udtFlags, &iButton, NULL, NULL);
		}
		FreeLibrary(hDLL);
	}

	//Fallback when library not loaded or TaskDialogIndirect not exists
	if (iButton == NULL)
	{
		iButton = MessageBox(phWnd, pacText, pacTitle, piType);
	}
	return (iButton);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HANDLE __fastcall clsUtil::FindProcess(const TCHAR *pacProcess)
{
	PROCESSENTRY32 udtEntry;


	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	udtEntry.dwSize = sizeof(PROCESSENTRY32);
	bool bRes = Process32First(hSnapshot, &udtEntry);
	HANDLE hProcess = NULL;
	while (bRes)
	{
		if (_tcsicmp(udtEntry.szExeFile, pacProcess) == 0)
		{
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, udtEntry.th32ProcessID);
			break;
		}
		bRes = Process32Next(hSnapshot, &udtEntry);
	}

	CloseHandle(hSnapshot);
	return (hProcess);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned long __fastcall clsUtil::RunProcess(const TCHAR *pacProcess, const TCHAR *pacDirectory, TCHAR *pacOutput, unsigned int piOutputLen, bool pbWait)
{
	unsigned long lExitCode;
	STARTUPINFO udtSI;
	PROCESS_INFORMATION udtPI = {0};
	SECURITY_ATTRIBUTES udtSA = {0};
	HANDLE hRead, hWrite;


	Screen->Cursor = crHourGlass;
	if ((pacOutput != NULL) && (piOutputLen > 0))
	{
		udtSA.nLength = sizeof(udtSA);
		udtSA.bInheritHandle = true;
		udtSA.lpSecurityDescriptor = NULL;
		CreatePipe(&hRead, &hWrite, &udtSA, 0);

		udtSI.cb = sizeof(udtSI);
		udtSI.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
		udtSI.hStdInput = hRead;
		udtSI.hStdOutput = hWrite;
		udtSI.wShowWindow = SW_HIDE;

		if (!CreateProcess(NULL, (TCHAR *) pacProcess, &udtSA, &udtSA, false, NULL, NULL, (TCHAR *) pacDirectory, &udtSI,
				&udtPI))
		{
			//_stprintf(acTmp, _T("Cannot launch %s"), pacProcess);
			//MsgBox(NULL, acTmp, _T("Error"), MB_OK | MB_ICONASTERISK);
		}
	}
	else
	{
		udtSA.nLength = sizeof(udtSA);
		udtSA.bInheritHandle = true;
		udtSA.lpSecurityDescriptor = NULL;

		udtSI.cb = sizeof(udtSI);
		udtSI.dwFlags = STARTF_USESHOWWINDOW;
		udtSI.wShowWindow = SW_HIDE;

		if (!CreateProcess(NULL, (TCHAR *) pacProcess, &udtSA, &udtSA, false, NULL, NULL, (TCHAR *) pacDirectory,
				&udtSI, &udtPI))
		{
			//_stprintf(acTmp, _T("Cannot launch %s"), pacProcess);
			//MsgBox(NULL, acTmp, _T("Error"), MB_OK | MB_ICONASTERISK);
		}
	}

	if (pbWait)
	{
		do
		{
			Application->ProcessMessages();
			WaitForSingleObject(udtPI.hProcess, INFINITE);
			GetExitCodeProcess(udtPI.hProcess, &lExitCode);
		}
		while (lExitCode == STILL_ACTIVE);
	}
	else
	{
		GetExitCodeProcess(udtPI.hProcess, &lExitCode);
	}

	if ((pacOutput != NULL) && (piOutputLen > 0))
	{
		memset(pacOutput, 0, piOutputLen);
		unsigned long lRead;
		PeekNamedPipe(hRead, NULL, NULL, NULL, &lRead, NULL);
		if (lRead > 0)
		{
			::ReadFile(hRead, pacOutput, piOutputLen, &lRead, NULL);
		}
		CloseHandle(hRead);
		CloseHandle(hWrite);
	}

	CloseHandle(udtPI.hProcess);
	CloseHandle(udtPI.hThread);

	Screen->Cursor = crDefault;

	return (lExitCode);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::ExistsFile(const TCHAR *pacFile)
{
	unsigned int iAttributes = GetFileAttributes(pacFile);
	return (iAttributes != INVALID_FILE_ATTRIBUTES);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned long long __fastcall clsUtil::SizeFile(const TCHAR *pacFile)
{
	unsigned long long lSize = 0;
	WIN32_FILE_ATTRIBUTE_DATA udtFileAttribute;


	if (GetFileAttributesEx(pacFile, GetFileExInfoStandard, (void*) &udtFileAttribute))
	{
		lSize = ((unsigned long long) udtFileAttribute.nFileSizeHigh << 32) + udtFileAttribute.nFileSizeLow;
	}
	return (lSize);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::ReadFile(const TCHAR *pacFile, void *pvData, unsigned int *piSize)
{
	unsigned long lSize;
	bool bRes = false;


	HANDLE hFile = CreateFile(pacFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		lSize = GetFileSize(hFile, NULL);
		if (*piSize != 0)
		{
			lSize = *piSize;
		}
		if (lSize > 0)
		{
			// Use file mapped IO
			HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, lSize, NULL);
			if (hMapping != INVALID_HANDLE_VALUE)
			{
				void *pacBuffer = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, lSize);
				if (pacBuffer != NULL)
				{
					memcpy(pvData, pacBuffer, lSize);
					bRes = UnmapViewOfFile(pacBuffer);
				}
				CloseHandle(hMapping);
			}
			// Use regular IO
			else
			{
				bRes = ::ReadFile(hFile, pvData, (unsigned long) piSize, &lSize, NULL);
			}
		}
		*piSize = lSize;
	}
	CloseHandle(hFile);
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::WriteFile(const TCHAR *pacFile, const void *pvData, unsigned int piSize)
{
	unsigned long lSize;
	bool bRes = false;


	HANDLE hFile = CreateFile(pacFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_FLAG_WRITE_THROUGH, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		// Use file mapped IO
		HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, piSize, NULL);
		if (hMapping != INVALID_HANDLE_VALUE)
		{
				void *pacBuffer = MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, piSize);
			if (pacBuffer != NULL)
			{
				memcpy(pacBuffer, pvData, piSize);
				bRes = UnmapViewOfFile(pacBuffer);
			}
			CloseHandle(hMapping);
		}
		// Use regular IO
		else
		{
			bRes = ::WriteFile(hFile, pvData, piSize, &lSize, NULL);
		}
	}
	CloseHandle(hFile);
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::GetFileTimestamp(const TCHAR *pacFile, FILETIME *pudtCreated, FILETIME *pudtAccessed, FILETIME *pudtModified)
{
	bool bRes = false;


	HANDLE hFile = CreateFile(pacFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		bRes = GetFileTime(hFile, pudtCreated, pudtAccessed, pudtModified);
		CloseHandle(hFile);
	}
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::SetFileTimestamp(const TCHAR *pacFile, const FILETIME *pudtCreated, const FILETIME *pudtAccessed, const FILETIME *pudtModified)
{
	bool bRes = false;


	HANDLE hFile = CreateFile(pacFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		bRes = SetFileTime(hFile, pudtCreated, pudtAccessed, pudtModified);
		CloseHandle(hFile);
	}
	return (bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::DirectoryCreate(String psDirectory)
{
	bool bRes = false;
	TCHAR *acDirectory;

	if (!EndsStr("\\", psDirectory))
	{
		psDirectory += "\\";
	}
	acDirectory = psDirectory.c_str();
	unsigned int iDirectoryLen = (unsigned int) _tcslen(acDirectory);

	for (unsigned int iCount = 0; iCount < iDirectoryLen; iCount++)
	{
		//If found a backslash we try to create that component (it should end with backslash
		if (acDirectory[iCount] == '\\')
		{
			acDirectory[iCount] = NULL;
			bRes = (CreateDirectory(acDirectory, NULL) != 0);
			acDirectory[iCount] = '\\';
		}
	}
	return(bRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::DownloadFile(const TCHAR *pacUrl, void *pvData, unsigned int piSize)
{
	bool bRes = false;


	GetModuleFileName(NULL, (TCHAR *) pvData, piSize - 1);
	_stprintf((TCHAR *) pvData, _T("%s/%s"), Application->Name.c_str(), ExeVersion((const TCHAR *) pvData));
	HINTERNET hInternet = InternetOpen((const TCHAR *) pvData, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
	if (hInternet != NULL)
	{
		HINTERNET hHttp = InternetOpenUrl(hInternet, pacUrl, NULL, 0, INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_HYPERLINK, NULL);
		if (hHttp != NULL)
		{
			memset(pvData, 0, piSize);
			unsigned long lRead;
			if (InternetReadFile(hHttp, pvData, piSize, &lRead))
			{
				bRes = true;
			}
		}
		InternetCloseHandle(hHttp);
	}
	InternetCloseHandle(hInternet);
	return (bRes);
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::CopyFile(const TCHAR *pacSource, const TCHAR *pacDestination)
{
	bool bRes;

	
	//Try copying file with faster no buffering only available in Windows XP
	bRes = CopyFileEx(pacSource, pacDestination, NULL, NULL, NULL, COPY_FILE_ALLOW_DECRYPTED_DESTINATION|COPY_FILE_NO_BUFFERING);
	if (!bRes)
	{
		//Try copying file with buffering
		bRes = ::CopyFile(pacSource, pacDestination, false);
	}
	return(bRes);
}




// --------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::ExeVersion(const TCHAR *pacFile)
{
	unsigned int iVersionSize;
	TCHAR *pacVersionData;
	void *a;
	VS_FIXEDFILEINFO udtVersionInfo;
	TCHAR acRes[2048] = _T("");


	iVersionSize = GetFileVersionInfoSize(pacFile, 0);
	pacVersionData = new TCHAR[iVersionSize];
	if (pacVersionData)
	{
		if (GetFileVersionInfo(pacFile, 0, iVersionSize, pacVersionData))
		{
			if (VerQueryValue(pacVersionData, _T("\\"), &a, &iVersionSize))
			{
				memcpy(&udtVersionInfo, a, iVersionSize);
				_stprintf(acRes, _T("%d.%d%d.%d"), HIWORD(udtVersionInfo.dwFileVersionMS), LOWORD(udtVersionInfo.dwFileVersionMS), HIWORD(udtVersionInfo.dwFileVersionLS), LOWORD(udtVersionInfo.dwFileVersionLS));
			}
		}
		delete[] pacVersionData;
	}
	return (acRes);
}



//---------------------------------------------------------------------------
int __fastcall clsUtil::GetFileVersionField(const TCHAR *fn, const TCHAR *info, TCHAR *ret, int len)
{
	DWORD hVersion;
	DWORD vis = GetFileVersionInfoSize(fn, &hVersion);


	if (vis == 0)
	{
		return(0);
	}
	void *vData;
	vData = (void *) new TCHAR[(UINT) vis];

	if (!GetFileVersionInfo(fn, hVersion, vis, vData))
	{
		//delete vData;
		delete (TCHAR *) vData;
		return(0);
	}
	TCHAR vn[100];
	_tcscpy(vn, _T("\\VarFileInfo\\Translation"));

	LPVOID transblock;
	UINT vsize;

	BOOL res = VerQueryValue(vData, vn, &transblock, &vsize);
	if (!res)
	{
		//delete vData;
		delete (TCHAR *) vData;
		return 0;
	}
	// Swap the words so wsprintf will print the lang-charset in the correct format.
	*(DWORD *) transblock = MAKELONG(HIWORD(*(DWORD *) transblock), LOWORD(*(DWORD *) transblock));
	_stprintf(vn, _T("\\StringFileInfo\\%08lx\\%s"),*(DWORD *) transblock, info);
	TCHAR *ver;
	res = VerQueryValue(vData, vn, (LPVOID*) &ver, &vsize);
	if (!res)
	{
		//delete vData;
		delete (TCHAR *) vData;
		return(0);
	}
	int vlen = _tcsclen(ver);
	if (ret != NULL)
	{
		int clen = vlen+1;
		if (clen >= len-1)
			clen = len-1;
		// ie. we'll try to copy the \0 in vData, but we'll leave space
		// for the thing.
		for (int i = 0; i < clen; i++)
			ret[i] = ver[i];
		ret[len-1] = 0;
	}
  //delete vData;
  delete (TCHAR *) vData;
  return(vlen);
}




// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::GetIniPath(void)
{
	TCHAR acTmp[2048];
	static TCHAR acPath[PATH_MAX] = _T("");


	// Check if we already have it cached
	if (acPath[0] == NULL)
	{
		GetModuleFileName(NULL, acTmp, sizeof(acTmp) - 1);
		*_tcsrchr(acTmp, '.') = NULL;
		_tcscat(acTmp, _T(".ini"));
		// Check if we can write to that location
		HANDLE hFile = CreateFile(acTmp, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			_stprintf(acPath, _T("%s\\%s"), _tgetenv(_T("USERPROFILE")), (Application->Name + ".ini").c_str());
		}
		else
		{
			CloseHandle(hFile);
			_tcscpy(acPath, acTmp);
		}
	}
	return (acPath);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::GetIni(const TCHAR *pacSection, const TCHAR *pacKey, const TCHAR *pacDefault)
{
	TCHAR acRes[2048];
	TCHAR *pcSemicolon;

	GetPrivateProfileString(pacSection, pacKey, pacDefault, acRes, sizeof(acRes), GetIniPath());
	//Remove comments
	pcSemicolon = _tcsrchr(acRes, ';');
	if (pcSemicolon)
	{
    	*pcSemicolon = NULL;
	}
	//Remove tabs
	pcSemicolon = _tcschr(acRes, '\t');
	if (pcSemicolon)
	{
    	*pcSemicolon = NULL;
	}

	return (acRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int __fastcall clsUtil::GetIni(const TCHAR *pacSection, const TCHAR *pacKey, int piDefault)
{
	TCHAR acDefault[2048];


	_itot(piDefault, acDefault, 10);
	return(_ttoi(GetIni(pacSection, pacKey, acDefault)));
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
long long __fastcall clsUtil::GetIni(const TCHAR *pacSection, const TCHAR *pacKey, long long plDefault)
{
	TCHAR acDefault[2048];


	_i64tot(plDefault, acDefault, 10);
	return(_ttoi64(GetIni(pacSection, pacKey, acDefault)));
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
double __fastcall clsUtil::GetIni(const TCHAR *pacSection, const TCHAR *pacKey, double pdDefault)
{
	TCHAR acDefault[2048];


	_stprintf(acDefault, _T("%f"), pdDefault);
	return(_ttof(GetIni(pacSection, pacKey, acDefault)));
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool __fastcall clsUtil::GetIni(const TCHAR *pacSection, const TCHAR *pacKey, bool pbDefault)
{
	TCHAR acDefault[2048];


	if (pbDefault)
	{
		_tcscpy(acDefault, _T("true"));
	}
	else
	{
		_tcscpy(acDefault, _T("false"));
	}
	return((_tcsicmp(GetIni(pacSection, pacKey, acDefault), _T("true")) == 0));
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::SetIni(const TCHAR *pacSection, const TCHAR *pacKey, const TCHAR *pacValue, const TCHAR *pacComment)
{
	if (pacComment[0] == NULL)
	{
		WritePrivateProfileString(pacSection, pacKey, pacValue, GetIniPath());
	}
	else
	{
		TCHAR acValue[2048];

		_tcscpy(acValue, pacValue);
		_tcscat(acValue, _T("\t\t; "));
		_tcscat(acValue, pacComment);
		WritePrivateProfileString(pacSection, pacKey, acValue, GetIniPath());
	}
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::SetIni(const TCHAR *pacSection, const TCHAR *pacKey, bool pbValue, const TCHAR *pacComment)
{
	TCHAR acValue[2048];


	if (pbValue)
	{
		_tcscpy(acValue, _T("true"));
	}
	else
	{
		_tcscpy(acValue, _T("false"));
	}
	SetIni(pacSection, pacKey, acValue, pacComment);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::SetIni(const TCHAR *pacSection, const TCHAR *pacKey, int piValue, const TCHAR *pacComment)
{
	TCHAR acValue[2048];


	_itot(piValue, acValue, 10);
	SetIni(pacSection, pacKey, acValue, pacComment);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::SetIni(const TCHAR *pacSection, const TCHAR *pacKey, long long plValue, const TCHAR *pacComment)
{
	TCHAR acValue[2048];


	_i64tot(plValue, acValue, 10);
	SetIni(pacSection, pacKey, acValue, pacComment);
}





// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::SetIni(const TCHAR *pacSection, const TCHAR *pacKey, double pdValue, const TCHAR *pacComment)
{
	TCHAR acValue[2048];


	_stprintf(acValue, _T("%f"), pdValue);
	SetIni(pacSection, pacKey, acValue, pacComment);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::GetRegistry(HKEY phKey, const TCHAR *pacSubkey, const TCHAR *pacName)
{
	HKEY hKey;
	TCHAR acRes[2048] = {0};


	RegOpenKeyEx(phKey, pacSubkey, NULL, KEY_QUERY_VALUE, &hKey);
	RegSetValueEx(hKey, pacName, NULL, REG_SZ, (BYTE *) acRes, NULL);
	RegCloseKey(hKey);
	return (acRes);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::SetRegistry(HKEY phKey, const TCHAR *pacSubkey, const TCHAR *pacName, const TCHAR *pacValue)
{
	HKEY hKey;


	RegOpenKeyEx(phKey, pacSubkey, NULL, KEY_SET_VALUE, &hKey);
	RegQueryValueEx(hKey, pacName, NULL, NULL, (BYTE *) pacValue, NULL);
	RegCloseKey(hKey);
}



// ---------------------------------------------------------------------------
unsigned int __fastcall clsUtil::Serialize (void *pacBuffer, unsigned int piSize)
{
	for (int iBuffer = (int) piSize - 1; iBuffer >= 0; iBuffer--)
	{
		unsigned char iByte = ((unsigned char *) pacBuffer)[iBuffer];
		((unsigned char *) pacBuffer)[iBuffer << 1] = (iByte & 15) + '0';
		((unsigned char *) pacBuffer)[(iBuffer << 1) + 1] = (iByte >> 4) + '0';
	}
	return(piSize << 1);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned int __fastcall clsUtil::Unserialize (void *pacBuffer, unsigned int piSize)
{
	for (unsigned int iBuffer = 0; iBuffer < piSize; iBuffer+=2)
	{
		unsigned char iNibbleL = ((unsigned char *) pacBuffer)[iBuffer] - '0';
		unsigned char iNibbleH = ((unsigned char *) pacBuffer)[iBuffer + 1] - '0';

		//Do a simple integrity check
		if ((iNibbleL > 15) || (iNibbleH > 15))
		{
			return(0);
		}
		else
		{
			((unsigned char *) pacBuffer)[iBuffer >> 1] = (unsigned char) (iNibbleL + (iNibbleH << 4));
		}
	}
	return(piSize >> 1);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int __fastcall clsUtil::Random(int piMin, int piMax)
{
	static int iSeed = clock();
	

	iSeed = 36969 * (iSeed & 32767) + (iSeed >> 16);
	return((iSeed % (piMax - piMin)) + piMin);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const TCHAR * __fastcall clsUtil::GetLogPath(void)
{
	TCHAR acTmp[2048];
	static TCHAR acPath[PATH_MAX] = _T("");


	// Check if we already have it cached
	if (acPath[0] == NULL)
	{
		GetModuleFileName(NULL, acTmp, sizeof(acTmp) - 1);
		*_tcsrchr(acTmp, '.') = NULL;
		_tcscat(acTmp, _T(".log"));
		// Check if we can write to that location
		HANDLE hFile = CreateFile(acTmp, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			_stprintf(acPath, _T("%s\\%s"), _tgetenv(_T("USERPROFILE")), (Application->Name + ".log").c_str());
		}
		else
		{
			CloseHandle(hFile);
			_tcscpy(acPath, acTmp);
		}
	}
	return (acPath);
}



// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall clsUtil::LogAdd(const TCHAR *pacFile, int piLine, const TCHAR *pacFunc, int piLevel, const TCHAR *pacValue, int piDesiredLevel)
{
	TCHAR acPath[PATH_MAX];
	TCHAR acLevel[][32] = { _T("CRITICAL"), _T("ERROR"), _T("WARNING"), _T("INFORMATION"), _T("NONE") };
	

	if ((piDesiredLevel) > piLevel)
	{
		_tcscpy(acPath, GetLogPath());
		FILE *pLog = _tfopen(acPath, _T("at"));
		TDateTime dteDate = dteDate.CurrentDateTime();
		_ftprintf(pLog, _T("[%s %s]	%s	%s	(%d)	%s()	%s\n"), dteDate.DateString().c_str(), dteDate.TimeString().c_str(), acLevel[piLevel], pacFile, piLine, pacFunc, pacValue);
		fclose(pLog);
	}
}



// ---------------------------------------------------------------------------
bool __fastcall clsUtil::LoadForm(TForm *pfrmForm)
{
	int iWindowState;


	pfrmForm->Left = GetIni(pfrmForm->Name.c_str(), _T("Left"), (Screen->Width - pfrmForm->Width) >> 1);
	pfrmForm->Top = GetIni(pfrmForm->Name.c_str(), _T("Top"), (Screen->Height - pfrmForm->Height) >> 1);
	pfrmForm->Width = GetIni(pfrmForm->Name.c_str(), _T("Width"), pfrmForm->Width);
	pfrmForm->Height = GetIni(pfrmForm->Name.c_str(), _T("Height"), pfrmForm->Height);
	iWindowState = GetIni(pfrmForm->Name.c_str(), _T("WindowState"), (int) pfrmForm->WindowState);
	//We do not want to reopen FileOptimizer in minimized state
	if (iWindowState == (int) wsMinimized)
	{
		iWindowState = (int) wsNormal;
	}
	pfrmForm->WindowState = (TWindowState) iWindowState;
	pfrmForm->DefaultMonitor = (TDefaultMonitor) GetIni(pfrmForm->Name.c_str(), _T("DefaultMonitor"), pfrmForm->DefaultMonitor);
	return (true);
}



// ---------------------------------------------------------------------------
bool __fastcall clsUtil::SaveForm(TForm *pfrmForm)
{
	SetIni(pfrmForm->Name.c_str(), _T("Left"), pfrmForm->Left);
	SetIni(pfrmForm->Name.c_str(), _T("Top"), pfrmForm->Top);
	SetIni(pfrmForm->Name.c_str(), _T("Width"), pfrmForm->Width);
	SetIni(pfrmForm->Name.c_str(), _T("Height"), pfrmForm->Height);
	SetIni(pfrmForm->Name.c_str(), _T("WindowState"), (int) pfrmForm->WindowState);
	SetIni(pfrmForm->Name.c_str(), _T("DefaultMonitor"), (int) pfrmForm->DefaultMonitor);
	return (true);
}



// ---------------------------------------------------------------------------
bool __fastcall clsUtil::CopyToRecycleBin(const TCHAR *pacSource)
{
	int iRes;
	SHFILEOPSTRUCT udtFileOp = {0};
	TCHAR acSource[PATH_MAX] = {0}, acDestination[PATH_MAX];


	Application->ProcessMessages();
	// ShFileOperation expect strings ending in double NULL
	_tcscpy(acSource, pacSource);
	_tcscpy(acDestination, acSource);
	_tcscat(acDestination, _T(".tmp"));

	CopyFile(acSource, acDestination);

	udtFileOp.wFunc = FO_DELETE;
	udtFileOp.fFlags = FOF_ALLOWUNDO | FOF_NO_UI;
	udtFileOp.pFrom = acSource;

	iRes = SHFileOperation(&udtFileOp);
	if (iRes == 0)
	{
		DeleteFile(acSource);
		MoveFile(acDestination, acSource);
		DeleteFile(acDestination);
		return (true);
	}
	else
	{
		DeleteFile(acDestination);
		return (false);
	}
}



// ---------------------------------------------------------------------------
bool __fastcall clsUtil::SetTaskListProgress(unsigned int piCompleted, unsigned int piTotal)
{
	ITaskbarList3 *pTaskList = NULL;


	// In 7 or newer use new TaskDialog
	if (GetWindowsVersion() >= 601)
	{
		HRESULT hRes = ::CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (void **) &pTaskList);
		if (pTaskList)
		{
			if (SUCCEEDED(hRes))
			{
				pTaskList->HrInit();
				if (Application->MainForm)
				{
					pTaskList->SetProgressState(Application->MainForm->Handle, TBPF_NORMAL);
					pTaskList->SetProgressValue(Application->MainForm->Handle, piCompleted, piTotal);
				}
				return (true);
			}
			pTaskList->Release();
		}
	}
	return (false);
}


// ---------------------------------------------------------------------------
unsigned int __fastcall clsUtil::GetWindowsVersion(void)
{
	static unsigned int iWindowsVersion = NULL;
	

	//Get true Windows version, even for non manifested applications under Windows 8.1 or later
	if (iWindowsVersion == NULL)
	{
		HMODULE hDLL = LoadLibrary(_T("NTDLL.DLL"));
		if (hDLL)
		{
			typedef NTSTATUS (WINAPI RtlGetVersionType)(RTL_OSVERSIONINFOW *pudtRtlVersionInfo);
			RtlGetVersionType *RtlGetVersionProc = (RtlGetVersionType *) GetProcAddress(hDLL, "RtlGetVersion");
			if (RtlGetVersionProc)
			{
				RTL_OSVERSIONINFOW udtRtlVersionInfo;
				RtlGetVersionProc(&udtRtlVersionInfo);
				iWindowsVersion = (udtRtlVersionInfo.dwMajorVersion * 100) + udtRtlVersionInfo.dwMinorVersion;
			}
			FreeLibrary(hDLL);
		}
		//Fallback when library not loaded or RtlGetVersion not exists
		if (iWindowsVersion == NULL)
		{
			iWindowsVersion = GetVersion();
			iWindowsVersion = (LOBYTE(LOWORD(iWindowsVersion))) * 100 + (HIBYTE(LOWORD(iWindowsVersion)));
		}
	}
	//500: Windows 2000; 501: Windows XP; 502: Windows XP x64/Windows 2003; 600: Windows Vista/2008; 601: Windows 7/Windows 2008 R2; 602: Windows 8/Windows 2012; 603: Windows 8.1; 1000: Windows 10
	return(iWindowsVersion);
}


// ---------------------------------------------------------------------------
bool __fastcall clsUtil::IsWindows64(void)
{
	static unsigned int iWindowsArchitecture = NULL;


	if (iWindowsArchitecture == NULL)
	{
		#if defined(_WIN64)
			iWindowsArchitecture = PROCESSOR_ARCHITECTURE_AMD64;
		#else
			SYSTEM_INFO udtSystemInfo;
			GetNativeSystemInfo(&udtSystemInfo);
			iWindowsArchitecture = udtSystemInfo.wProcessorArchitecture;
		#endif
	}
	return(iWindowsArchitecture == PROCESSOR_ARCHITECTURE_AMD64);
}



// ---------------------------------------------------------------------------
bool __fastcall clsUtil::ShutdownWindows(void)
{
	bool bRes = false;
	HANDLE hToken; 
	TOKEN_PRIVILEGES udtTokenPrivileges; 


	//Get a token for this process
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
	{
		//Get the LUID for the shutdown privilege.
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &udtTokenPrivileges.Privileges[0].Luid); 
		udtTokenPrivileges.PrivilegeCount = 1;  //One privilege to set    
		udtTokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 

		// Get the shutdown privilege for this process. 
		AdjustTokenPrivileges(hToken, false, &udtTokenPrivileges, 0, (PTOKEN_PRIVILEGES) NULL, 0); 
		if (GetLastError() == ERROR_SUCCESS) 
		{
			//Shut down the system and force all applications to close. 
			if (ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE | SHTDN_REASON_FLAG_PLANNED))
			{
				bRes = true;
			}
		}
	}
	return(bRes);
}

#include "clipboard.h"
#include <windows.h>



Clipboard::Clipboard()
{
    OpenClipboard(NULL);
}

Clipboard::~Clipboard()
{
    CloseClipboard();
}

QByteArray Clipboard::getData()
{
    Clipboard obj;

    HANDLE hData= GetClipboardData(CF_TEXT);
    DWORD size = GlobalSize(hData);
    LPVOID pData= GlobalLock(hData);
    return QByteArray((char*)pData,size);
}

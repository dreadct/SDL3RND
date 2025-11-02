#include "HResultUtils.h"

#include <cassert>
#include <codecvt>
#include <locale>

bool getHResultErrorDescription(
    const HRESULT hResult,
    std::string *pOutString
) {
    assert(pOutString);
    if (pOutString == nullptr) {
        return false;
    }

    if (SUCCEEDED(hResult)) {
        *pOutString = "";
        return false;
    }

    LPWSTR pwszMessage = nullptr;
    DWORD dwChars = FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        hResult,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&pwszMessage,
        0,
        NULL
    );

    if (dwChars == 0 || pwszMessage == nullptr) {
        *pOutString = "";
        return false;
    }

    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    *pOutString = converter.to_bytes(pwszMessage);

    LocalFree(pwszMessage);

    return true;
}

#pragma once

#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern bool getHResultErrorDescription(
    const HRESULT hResult,
    std::string *pOutString
);

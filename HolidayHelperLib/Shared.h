#pragma once

#ifdef HOLIDAYHELPERLIB_EXPORTS
#define DllExport _declspec(dllexport)
#else
#define DllExport _declspec(dllimport)
#endif
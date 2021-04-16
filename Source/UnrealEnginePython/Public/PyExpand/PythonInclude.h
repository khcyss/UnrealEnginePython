#pragma once


#if PLATFORM_MAC
#include <Headers/Python.h>
#include <Headers/structmember.h>
#elif PLATFORM_LINUX
#include <Python.h>
#include <structmember.h>
#elif PLATFORM_ANDROID
#include <Python.h>
#include <structmember.h>
#elif PLATFORM_WINDOWS
#include <include/pyconfig.h>
#ifndef SIZEOF_PID_T
#define SIZEOF_PID_T 4
#endif
#include <include/Python.h>
#include <include/structmember.h>
#endif
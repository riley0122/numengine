#include "eadk_vars.hpp"
#include "eadk.h"

#ifndef __RODATA_EADK_APP_NAME__
    const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "NAME";
#else
    const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = __RODATA_EADK_APP_NAME__;
#endif
const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

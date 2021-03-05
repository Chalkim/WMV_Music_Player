#ifndef __FILE_H_
#define __FILE_H_

#include "stm32f1xx_hal.h"
#include "GUI.h"
#include "lcd.h"
#include "fatfs.h"
#include "key.h"
#include <string.h>

FRESULT SD_mount(void);
FRESULT scan_files (char* path);

#endif

multiline_comment|/*&n; * PreP compliant NVRAM access&n; * This needs to be updated for PPC64&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _PPC64_NVRAM_H
DECL|macro|_PPC64_NVRAM_H
mdefine_line|#define _PPC64_NVRAM_H
DECL|macro|NVRAM_AS0
mdefine_line|#define NVRAM_AS0  0x74
DECL|macro|NVRAM_AS1
mdefine_line|#define NVRAM_AS1  0x75
DECL|macro|NVRAM_DATA
mdefine_line|#define NVRAM_DATA 0x77
multiline_comment|/* RTC Offsets */
DECL|macro|MOTO_RTC_SECONDS
mdefine_line|#define MOTO_RTC_SECONDS&t;0x1FF9
DECL|macro|MOTO_RTC_MINUTES
mdefine_line|#define MOTO_RTC_MINUTES&t;0x1FFA
DECL|macro|MOTO_RTC_HOURS
mdefine_line|#define MOTO_RTC_HOURS&t;&t;0x1FFB
DECL|macro|MOTO_RTC_DAY_OF_WEEK
mdefine_line|#define MOTO_RTC_DAY_OF_WEEK&t;0x1FFC
DECL|macro|MOTO_RTC_DAY_OF_MONTH
mdefine_line|#define MOTO_RTC_DAY_OF_MONTH&t;0x1FFD
DECL|macro|MOTO_RTC_MONTH
mdefine_line|#define MOTO_RTC_MONTH&t;&t;0x1FFE
DECL|macro|MOTO_RTC_YEAR
mdefine_line|#define MOTO_RTC_YEAR&t;&t;0x1FFF
DECL|macro|MOTO_RTC_CONTROLA
mdefine_line|#define MOTO_RTC_CONTROLA       0x1FF8
DECL|macro|MOTO_RTC_CONTROLB
mdefine_line|#define MOTO_RTC_CONTROLB       0x1FF9
macro_line|#endif /* _PPC64_NVRAM_H */
eof

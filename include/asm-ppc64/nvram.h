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
macro_line|#ifndef BCD_TO_BIN
DECL|macro|BCD_TO_BIN
mdefine_line|#define BCD_TO_BIN(val) ((val)=((val)&amp;15) + ((val)&gt;&gt;4)*10)
macro_line|#endif
macro_line|#ifndef BIN_TO_BCD
DECL|macro|BIN_TO_BCD
mdefine_line|#define BIN_TO_BCD(val) ((val)=(((val)/10)&lt;&lt;4) + (val)%10)
macro_line|#endif
multiline_comment|/* PowerMac specific nvram stuffs */
r_enum
(brace
DECL|enumerator|pmac_nvram_OF
id|pmac_nvram_OF
comma
multiline_comment|/* Open Firmware partition */
DECL|enumerator|pmac_nvram_XPRAM
id|pmac_nvram_XPRAM
comma
multiline_comment|/* MacOS XPRAM partition */
DECL|enumerator|pmac_nvram_NR
id|pmac_nvram_NR
multiline_comment|/* MacOS Name Registry partition */
)brace
suffix:semicolon
multiline_comment|/* Return partition offset in nvram */
r_extern
r_int
id|pmac_get_partition
c_func
(paren
r_int
id|partition
)paren
suffix:semicolon
multiline_comment|/* Direct access to XPRAM */
r_extern
id|u8
id|pmac_xpram_read
c_func
(paren
r_int
id|xpaddr
)paren
suffix:semicolon
r_extern
r_void
id|pmac_xpram_write
c_func
(paren
r_int
id|xpaddr
comma
id|u8
id|data
)paren
suffix:semicolon
multiline_comment|/* Some offsets in XPRAM */
DECL|macro|PMAC_XPRAM_MACHINE_LOC
mdefine_line|#define PMAC_XPRAM_MACHINE_LOC&t;0xe4
DECL|macro|PMAC_XPRAM_SOUND_VOLUME
mdefine_line|#define PMAC_XPRAM_SOUND_VOLUME&t;0x08
multiline_comment|/* Machine location structure in XPRAM */
DECL|struct|pmac_machine_location
r_struct
id|pmac_machine_location
(brace
DECL|member|latitude
id|u32
id|latitude
suffix:semicolon
multiline_comment|/* 2+30 bit Fractional number */
DECL|member|longitude
id|u32
id|longitude
suffix:semicolon
multiline_comment|/* 2+30 bit Fractional number */
DECL|member|delta
id|u32
id|delta
suffix:semicolon
multiline_comment|/* mix of GMT delta and DLS */
)brace
suffix:semicolon
multiline_comment|/* /dev/nvram ioctls */
DECL|macro|PMAC_NVRAM_GET_OFFSET
mdefine_line|#define PMAC_NVRAM_GET_OFFSET   _IOWR(&squot;p&squot;, 0x40, int) /* Get NVRAM partition offset */
macro_line|#endif /* _PPC64_NVRAM_H */
eof

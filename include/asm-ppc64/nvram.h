multiline_comment|/*&n; * PreP compliant NVRAM access&n; * This needs to be updated for PPC64&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _PPC64_NVRAM_H
DECL|macro|_PPC64_NVRAM_H
mdefine_line|#define _PPC64_NVRAM_H
DECL|macro|NVRW_CNT
mdefine_line|#define NVRW_CNT 0x20
DECL|macro|NVRAM_HEADER_LEN
mdefine_line|#define NVRAM_HEADER_LEN 16 /* sizeof(struct nvram_header) */
DECL|macro|NVRAM_BLOCK_LEN
mdefine_line|#define NVRAM_BLOCK_LEN 16
DECL|macro|NVRAM_MAX_REQ
mdefine_line|#define NVRAM_MAX_REQ (2080/NVRAM_BLOCK_LEN)
DECL|macro|NVRAM_MIN_REQ
mdefine_line|#define NVRAM_MIN_REQ (1056/NVRAM_BLOCK_LEN)
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
DECL|macro|NVRAM_SIG_SP
mdefine_line|#define NVRAM_SIG_SP&t;0x02&t;/* support processor */
DECL|macro|NVRAM_SIG_OF
mdefine_line|#define NVRAM_SIG_OF&t;0x50&t;/* open firmware config */
DECL|macro|NVRAM_SIG_FW
mdefine_line|#define NVRAM_SIG_FW&t;0x51&t;/* general firmware */
DECL|macro|NVRAM_SIG_HW
mdefine_line|#define NVRAM_SIG_HW&t;0x52&t;/* hardware (VPD) */
DECL|macro|NVRAM_SIG_FLIP
mdefine_line|#define NVRAM_SIG_FLIP&t;0x5a&t;/* Apple flip/flop header */
DECL|macro|NVRAM_SIG_APPL
mdefine_line|#define NVRAM_SIG_APPL&t;0x5f&t;/* Apple &quot;system&quot; (???) */
DECL|macro|NVRAM_SIG_SYS
mdefine_line|#define NVRAM_SIG_SYS&t;0x70&t;/* system env vars */
DECL|macro|NVRAM_SIG_CFG
mdefine_line|#define NVRAM_SIG_CFG&t;0x71&t;/* config data */
DECL|macro|NVRAM_SIG_ELOG
mdefine_line|#define NVRAM_SIG_ELOG&t;0x72&t;/* error log */
DECL|macro|NVRAM_SIG_VEND
mdefine_line|#define NVRAM_SIG_VEND&t;0x7e&t;/* vendor defined */
DECL|macro|NVRAM_SIG_FREE
mdefine_line|#define NVRAM_SIG_FREE&t;0x7f&t;/* Free space */
DECL|macro|NVRAM_SIG_OS
mdefine_line|#define NVRAM_SIG_OS&t;0xa0&t;/* OS defined */
DECL|macro|NVRAM_SIG_PANIC
mdefine_line|#define NVRAM_SIG_PANIC&t;0xa1&t;/* Apple OSX &quot;panic&quot; */
multiline_comment|/* If change this size, then change the size of NVNAME_LEN */
DECL|struct|nvram_header
r_struct
id|nvram_header
(brace
DECL|member|signature
r_int
r_char
id|signature
suffix:semicolon
DECL|member|checksum
r_int
r_char
id|checksum
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nvram_partition
r_struct
id|nvram_partition
(brace
DECL|member|partition
r_struct
id|list_head
id|partition
suffix:semicolon
DECL|member|header
r_struct
id|nvram_header
id|header
suffix:semicolon
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|nvram_write_error_log
c_func
(paren
r_char
op_star
id|buff
comma
r_int
id|length
comma
r_int
r_int
id|err_type
)paren
suffix:semicolon
r_extern
r_int
id|nvram_read_error_log
c_func
(paren
r_char
op_star
id|buff
comma
r_int
id|length
comma
r_int
r_int
op_star
id|err_type
)paren
suffix:semicolon
r_extern
r_int
id|nvram_clear_error_log
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|nvram_partition
op_star
id|nvram_find_partition
c_func
(paren
r_int
id|sig
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_int
id|pSeries_nvram_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pmac_nvram_init
c_func
(paren
r_void
)paren
suffix:semicolon
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
multiline_comment|/* Direct access to XPRAM on PowerMacs */
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
multiline_comment|/* Synchronize NVRAM */
r_extern
r_int
id|nvram_sync
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Some offsets in XPRAM */
DECL|macro|PMAC_XPRAM_MACHINE_LOC
mdefine_line|#define PMAC_XPRAM_MACHINE_LOC&t;0xe4
DECL|macro|PMAC_XPRAM_SOUND_VOLUME
mdefine_line|#define PMAC_XPRAM_SOUND_VOLUME&t;0x08
multiline_comment|/* Machine location structure in PowerMac XPRAM */
DECL|struct|pmac_machine_location
r_struct
id|pmac_machine_location
(brace
DECL|member|latitude
r_int
r_int
id|latitude
suffix:semicolon
multiline_comment|/* 2+30 bit Fractional number */
DECL|member|longitude
r_int
r_int
id|longitude
suffix:semicolon
multiline_comment|/* 2+30 bit Fractional number */
DECL|member|delta
r_int
r_int
id|delta
suffix:semicolon
multiline_comment|/* mix of GMT delta and DLS */
)brace
suffix:semicolon
multiline_comment|/*&n; * /dev/nvram ioctls&n; *&n; * Note that PMAC_NVRAM_GET_OFFSET is still supported, but is&n; * definitely obsolete. Do not use it if you can avoid it&n; */
DECL|macro|OBSOLETE_PMAC_NVRAM_GET_OFFSET
mdefine_line|#define OBSOLETE_PMAC_NVRAM_GET_OFFSET &bslash;&n;&t;&t;&t;&t;_IOWR(&squot;p&squot;, 0x40, int)
DECL|macro|IOC_NVRAM_GET_OFFSET
mdefine_line|#define IOC_NVRAM_GET_OFFSET&t;_IOWR(&squot;p&squot;, 0x42, int)&t;/* Get NVRAM partition offset */
macro_line|#endif /* _PPC64_NVRAM_H */
eof

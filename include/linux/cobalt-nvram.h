multiline_comment|/*&n; * $Id: cobalt-nvram.h,v 1.20 2001/10/17 23:16:55 thockin Exp $&n; * cobalt-nvram.h : defines for the various fields in the cobalt NVRAM&n; *&n; * Copyright 2001,2002 Sun Microsystems, Inc.&n; */
macro_line|#ifndef COBALT_NVRAM_H
DECL|macro|COBALT_NVRAM_H
mdefine_line|#define COBALT_NVRAM_H
macro_line|#include &lt;linux/nvram.h&gt;
DECL|macro|COBT_CMOS_INFO_MAX
mdefine_line|#define COBT_CMOS_INFO_MAX&t;&t;0x7f&t;/* top address allowed */
DECL|macro|COBT_CMOS_BIOS_DRIVE_INFO
mdefine_line|#define COBT_CMOS_BIOS_DRIVE_INFO&t;0x12&t;/* drive info would go here */
DECL|macro|COBT_CMOS_CKS_START
mdefine_line|#define COBT_CMOS_CKS_START&t;&t;NVRAM_OFFSET(0x0e)
DECL|macro|COBT_CMOS_CKS_END
mdefine_line|#define COBT_CMOS_CKS_END&t;&t;NVRAM_OFFSET(0x7f)
multiline_comment|/* flag bytes - 16 flags for now, leave room for more */
DECL|macro|COBT_CMOS_FLAG_BYTE_0
mdefine_line|#define COBT_CMOS_FLAG_BYTE_0&t;&t;NVRAM_OFFSET(0x10)
DECL|macro|COBT_CMOS_FLAG_BYTE_1
mdefine_line|#define COBT_CMOS_FLAG_BYTE_1&t;&t;NVRAM_OFFSET(0x11)
multiline_comment|/* flags in flag bytes - up to 16 */
DECL|macro|COBT_CMOS_FLAG_MIN
mdefine_line|#define COBT_CMOS_FLAG_MIN&t;&t;0x0001
DECL|macro|COBT_CMOS_CONSOLE_FLAG
mdefine_line|#define COBT_CMOS_CONSOLE_FLAG&t;&t;0x0001 /* console on/off */
DECL|macro|COBT_CMOS_DEBUG_FLAG
mdefine_line|#define COBT_CMOS_DEBUG_FLAG&t;&t;0x0002 /* ROM debug messages */
DECL|macro|COBT_CMOS_AUTO_PROMPT_FLAG
mdefine_line|#define COBT_CMOS_AUTO_PROMPT_FLAG&t;0x0004 /* boot to ROM prompt? */
DECL|macro|COBT_CMOS_CLEAN_BOOT_FLAG
mdefine_line|#define COBT_CMOS_CLEAN_BOOT_FLAG&t;0x0008 /* set by a clean shutdown */
DECL|macro|COBT_CMOS_HW_NOPROBE_FLAG
mdefine_line|#define COBT_CMOS_HW_NOPROBE_FLAG&t;0x0010 /* go easy on the probing */
DECL|macro|COBT_CMOS_SYSFAULT_FLAG
mdefine_line|#define COBT_CMOS_SYSFAULT_FLAG&t;&t;0x0020 /* system fault detected */
DECL|macro|COBT_CMOS_OOPSPANIC_FLAG
mdefine_line|#define COBT_CMOS_OOPSPANIC_FLAG&t;0x0040 /* panic on oops */
DECL|macro|COBT_CMOS_DELAY_CACHE_FLAG
mdefine_line|#define COBT_CMOS_DELAY_CACHE_FLAG&t;0x0080 /* delay cache initialization */
DECL|macro|COBT_CMOS_NOLOGO_FLAG
mdefine_line|#define COBT_CMOS_NOLOGO_FLAG&t;&t;0x0100 /* hide &quot;C&quot; logo @ boot */
DECL|macro|COBT_CMOS_VERSION_FLAG
mdefine_line|#define COBT_CMOS_VERSION_FLAG&t;&t;0x0200 /* the version field is valid */
DECL|macro|COBT_CMOS_FLAG_MAX
mdefine_line|#define COBT_CMOS_FLAG_MAX&t;&t;0x0200
multiline_comment|/* leave byte 0x12 blank - Linux looks for drive info here */
multiline_comment|/* CMOS structure version, valid if COBT_CMOS_VERSION_FLAG is true */
DECL|macro|COBT_CMOS_VERSION
mdefine_line|#define COBT_CMOS_VERSION&t;&t;NVRAM_OFFSET(0x13)
DECL|macro|COBT_CMOS_VER_BTOCODE
mdefine_line|#define COBT_CMOS_VER_BTOCODE&t;&t;1 /* min. version needed for btocode */
multiline_comment|/* index of default boot method */
DECL|macro|COBT_CMOS_BOOT_METHOD
mdefine_line|#define COBT_CMOS_BOOT_METHOD&t;&t;NVRAM_OFFSET(0x20)
DECL|macro|COBT_CMOS_BOOT_METHOD_DISK
mdefine_line|#define COBT_CMOS_BOOT_METHOD_DISK&t;0
DECL|macro|COBT_CMOS_BOOT_METHOD_ROM
mdefine_line|#define COBT_CMOS_BOOT_METHOD_ROM&t;1
DECL|macro|COBT_CMOS_BOOT_METHOD_NET
mdefine_line|#define COBT_CMOS_BOOT_METHOD_NET&t;2
DECL|macro|COBT_CMOS_BOOT_DEV_MIN
mdefine_line|#define COBT_CMOS_BOOT_DEV_MIN&t;&t;NVRAM_OFFSET(0x21)
multiline_comment|/* major #, minor # of first through fourth boot device */
DECL|macro|COBT_CMOS_BOOT_DEV0_MAJ
mdefine_line|#define COBT_CMOS_BOOT_DEV0_MAJ&t;&t;NVRAM_OFFSET(0x21)
DECL|macro|COBT_CMOS_BOOT_DEV0_MIN
mdefine_line|#define COBT_CMOS_BOOT_DEV0_MIN&t;&t;NVRAM_OFFSET(0x22)
DECL|macro|COBT_CMOS_BOOT_DEV1_MAJ
mdefine_line|#define COBT_CMOS_BOOT_DEV1_MAJ&t;&t;NVRAM_OFFSET(0x23)
DECL|macro|COBT_CMOS_BOOT_DEV1_MIN
mdefine_line|#define COBT_CMOS_BOOT_DEV1_MIN&t;&t;NVRAM_OFFSET(0x24)
DECL|macro|COBT_CMOS_BOOT_DEV2_MAJ
mdefine_line|#define COBT_CMOS_BOOT_DEV2_MAJ&t;&t;NVRAM_OFFSET(0x25)
DECL|macro|COBT_CMOS_BOOT_DEV2_MIN
mdefine_line|#define COBT_CMOS_BOOT_DEV2_MIN&t;&t;NVRAM_OFFSET(0x26)
DECL|macro|COBT_CMOS_BOOT_DEV3_MAJ
mdefine_line|#define COBT_CMOS_BOOT_DEV3_MAJ&t;&t;NVRAM_OFFSET(0x27)
DECL|macro|COBT_CMOS_BOOT_DEV3_MIN
mdefine_line|#define COBT_CMOS_BOOT_DEV3_MIN&t;&t;NVRAM_OFFSET(0x28)
DECL|macro|COBT_CMOS_BOOT_DEV_MAX
mdefine_line|#define COBT_CMOS_BOOT_DEV_MAX&t;&t;NVRAM_OFFSET(0x28)
multiline_comment|/* checksum of bytes 0xe-0x7f */
DECL|macro|COBT_CMOS_CHECKSUM
mdefine_line|#define COBT_CMOS_CHECKSUM&t;&t;NVRAM_OFFSET(0x2e)
multiline_comment|/* running uptime counter, units of 5 minutes (32 bits =~ 41000 years) */
DECL|macro|COBT_CMOS_UPTIME_0
mdefine_line|#define COBT_CMOS_UPTIME_0&t;&t;NVRAM_OFFSET(0x30)
DECL|macro|COBT_CMOS_UPTIME_1
mdefine_line|#define COBT_CMOS_UPTIME_1&t;&t;NVRAM_OFFSET(0x31)
DECL|macro|COBT_CMOS_UPTIME_2
mdefine_line|#define COBT_CMOS_UPTIME_2&t;&t;NVRAM_OFFSET(0x32)
DECL|macro|COBT_CMOS_UPTIME_3
mdefine_line|#define COBT_CMOS_UPTIME_3&t;&t;NVRAM_OFFSET(0x33)
multiline_comment|/* count of successful boots (32 bits) */
DECL|macro|COBT_CMOS_BOOTCOUNT_0
mdefine_line|#define COBT_CMOS_BOOTCOUNT_0&t;&t;NVRAM_OFFSET(0x38)
DECL|macro|COBT_CMOS_BOOTCOUNT_1
mdefine_line|#define COBT_CMOS_BOOTCOUNT_1&t;&t;NVRAM_OFFSET(0x39)
DECL|macro|COBT_CMOS_BOOTCOUNT_2
mdefine_line|#define COBT_CMOS_BOOTCOUNT_2&t;&t;NVRAM_OFFSET(0x3a)
DECL|macro|COBT_CMOS_BOOTCOUNT_3
mdefine_line|#define COBT_CMOS_BOOTCOUNT_3&t;&t;NVRAM_OFFSET(0x3b)
multiline_comment|/* 13 bytes: system serial number, same as on the back of the system */
DECL|macro|COBT_CMOS_SYS_SERNUM_LEN
mdefine_line|#define COBT_CMOS_SYS_SERNUM_LEN&t;13
DECL|macro|COBT_CMOS_SYS_SERNUM_0
mdefine_line|#define COBT_CMOS_SYS_SERNUM_0&t;&t;NVRAM_OFFSET(0x40)
DECL|macro|COBT_CMOS_SYS_SERNUM_1
mdefine_line|#define COBT_CMOS_SYS_SERNUM_1&t;&t;NVRAM_OFFSET(0x41)
DECL|macro|COBT_CMOS_SYS_SERNUM_2
mdefine_line|#define COBT_CMOS_SYS_SERNUM_2&t;&t;NVRAM_OFFSET(0x42)
DECL|macro|COBT_CMOS_SYS_SERNUM_3
mdefine_line|#define COBT_CMOS_SYS_SERNUM_3&t;&t;NVRAM_OFFSET(0x43)
DECL|macro|COBT_CMOS_SYS_SERNUM_4
mdefine_line|#define COBT_CMOS_SYS_SERNUM_4&t;&t;NVRAM_OFFSET(0x44)
DECL|macro|COBT_CMOS_SYS_SERNUM_5
mdefine_line|#define COBT_CMOS_SYS_SERNUM_5&t;&t;NVRAM_OFFSET(0x45)
DECL|macro|COBT_CMOS_SYS_SERNUM_6
mdefine_line|#define COBT_CMOS_SYS_SERNUM_6&t;&t;NVRAM_OFFSET(0x46)
DECL|macro|COBT_CMOS_SYS_SERNUM_7
mdefine_line|#define COBT_CMOS_SYS_SERNUM_7&t;&t;NVRAM_OFFSET(0x47)
DECL|macro|COBT_CMOS_SYS_SERNUM_8
mdefine_line|#define COBT_CMOS_SYS_SERNUM_8&t;&t;NVRAM_OFFSET(0x48)
DECL|macro|COBT_CMOS_SYS_SERNUM_9
mdefine_line|#define COBT_CMOS_SYS_SERNUM_9&t;&t;NVRAM_OFFSET(0x49)
DECL|macro|COBT_CMOS_SYS_SERNUM_10
mdefine_line|#define COBT_CMOS_SYS_SERNUM_10&t;&t;NVRAM_OFFSET(0x4a)
DECL|macro|COBT_CMOS_SYS_SERNUM_11
mdefine_line|#define COBT_CMOS_SYS_SERNUM_11&t;&t;NVRAM_OFFSET(0x4b)
DECL|macro|COBT_CMOS_SYS_SERNUM_12
mdefine_line|#define COBT_CMOS_SYS_SERNUM_12&t;&t;NVRAM_OFFSET(0x4c)
multiline_comment|/* checksum for serial num - 1 byte */
DECL|macro|COBT_CMOS_SYS_SERNUM_CSUM
mdefine_line|#define COBT_CMOS_SYS_SERNUM_CSUM&t;NVRAM_OFFSET(0x4f)
DECL|macro|COBT_CMOS_ROM_REV_MAJ
mdefine_line|#define COBT_CMOS_ROM_REV_MAJ&t;&t;NVRAM_OFFSET(0x50)
DECL|macro|COBT_CMOS_ROM_REV_MIN
mdefine_line|#define COBT_CMOS_ROM_REV_MIN&t;&t;NVRAM_OFFSET(0x51)
DECL|macro|COBT_CMOS_ROM_REV_REV
mdefine_line|#define COBT_CMOS_ROM_REV_REV&t;&t;NVRAM_OFFSET(0x52)
DECL|macro|COBT_CMOS_BTO_CODE_0
mdefine_line|#define COBT_CMOS_BTO_CODE_0&t;&t;NVRAM_OFFSET(0x53)
DECL|macro|COBT_CMOS_BTO_CODE_1
mdefine_line|#define COBT_CMOS_BTO_CODE_1&t;&t;NVRAM_OFFSET(0x54)
DECL|macro|COBT_CMOS_BTO_CODE_2
mdefine_line|#define COBT_CMOS_BTO_CODE_2&t;&t;NVRAM_OFFSET(0x55)
DECL|macro|COBT_CMOS_BTO_CODE_3
mdefine_line|#define COBT_CMOS_BTO_CODE_3&t;&t;NVRAM_OFFSET(0x56)
DECL|macro|COBT_CMOS_BTO_IP_CSUM
mdefine_line|#define COBT_CMOS_BTO_IP_CSUM&t;&t;NVRAM_OFFSET(0x57)
DECL|macro|COBT_CMOS_BTO_IP_0
mdefine_line|#define COBT_CMOS_BTO_IP_0&t;&t;NVRAM_OFFSET(0x58)
DECL|macro|COBT_CMOS_BTO_IP_1
mdefine_line|#define COBT_CMOS_BTO_IP_1&t;&t;NVRAM_OFFSET(0x59)
DECL|macro|COBT_CMOS_BTO_IP_2
mdefine_line|#define COBT_CMOS_BTO_IP_2&t;&t;NVRAM_OFFSET(0x5a)
DECL|macro|COBT_CMOS_BTO_IP_3
mdefine_line|#define COBT_CMOS_BTO_IP_3&t;&t;NVRAM_OFFSET(0x5b)
macro_line|#endif /* COBALT_NVRAM_H */
eof

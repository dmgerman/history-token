multiline_comment|/*&n; * linux/include/asm-arm/arch-l7200/hardware.h&n; *&n; * Copyright (C) 2000 Rob Scott (rscott@mtrob.fdns.net)&n; *                    Steve Hill (sjhill@cotw.com)&n; *&n; * This file contains the hardware definitions for the &n; * LinkUp Systems L7200 SOC development board.&n; *&n; * Changelog:&n; *   02-01-2000&t; RS&t;Created L7200 version, derived from rpc code&n; *   03-21-2000&t;SJH&t;Cleaned up file&n; *   04-21-2000&t; RS &t;Changed mapping of I/O in virtual space&n; *   04-25-2000&t;SJH&t;Removed unused symbols and such&n; *   05-05-2000&t;SJH&t;Complete rewrite&n; *   07-31-2000&t;SJH&t;Added undocumented debug auxillary port to&n; *&t;&t;&t;get at last two columns for keyboard driver&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
multiline_comment|/* Hardware addresses of major areas.&n; *  *_START is the physical address&n; *  *_SIZE  is the size of the region&n; *  *_BASE  is the virtual address&n; */
DECL|macro|RAM_START
mdefine_line|#define RAM_START&t;&t;0xf0000000
DECL|macro|RAM_SIZE
mdefine_line|#define RAM_SIZE&t;&t;0x02000000
DECL|macro|RAM_BASE
mdefine_line|#define RAM_BASE&t;&t;0xc0000000
DECL|macro|IO_START
mdefine_line|#define IO_START&t;&t;0x80000000      /* I/O */
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;0x01000000
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0xd0000000
DECL|macro|IO_START_2
mdefine_line|#define IO_START_2&t;&t;0x90000000      /* I/O */
DECL|macro|IO_SIZE_2
mdefine_line|#define IO_SIZE_2&t;&t;0x01000000
DECL|macro|IO_BASE_2
mdefine_line|#define IO_BASE_2&t;&t;0xd1000000
DECL|macro|AUX_START
mdefine_line|#define AUX_START&t;&t;0x1a000000      /* AUX PORT */
DECL|macro|AUX_SIZE
mdefine_line|#define AUX_SIZE &t;&t;0x01000000
DECL|macro|AUX_BASE
mdefine_line|#define AUX_BASE&t;&t;0xd2000000
DECL|macro|FLASH1_START
mdefine_line|#define FLASH1_START&t;&t;0x00000000      /* FLASH BANK 1 */
DECL|macro|FLASH1_SIZE
mdefine_line|#define FLASH1_SIZE &t;&t;0x01000000
DECL|macro|FLASH1_BASE
mdefine_line|#define FLASH1_BASE&t;&t;0xd3000000
DECL|macro|FLASH2_START
mdefine_line|#define FLASH2_START&t;&t;0x10000000      /* FLASH BANK 2 */
DECL|macro|FLASH2_SIZE
mdefine_line|#define FLASH2_SIZE &t;&t;0x01000000
DECL|macro|FLASH2_BASE
mdefine_line|#define FLASH2_BASE&t;&t;0xd4000000
DECL|macro|ISA_START
mdefine_line|#define ISA_START&t;&t;0x20000000&t;/* ISA */
DECL|macro|ISA_SIZE
mdefine_line|#define ISA_SIZE&t;&t;0x20000000
DECL|macro|ISA_BASE
mdefine_line|#define ISA_BASE&t;&t;0xe0000000
DECL|macro|FLUSH_BASE_PHYS
mdefine_line|#define FLUSH_BASE_PHYS&t;&t;0x40000000&t;/* ROM */
DECL|macro|FLUSH_BASE
mdefine_line|#define FLUSH_BASE&t;&t;0xdf000000
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;IO_BASE
macro_line|#endif
eof

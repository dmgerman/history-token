multiline_comment|/*&n; * linux/include/asm-mips/tx4927/smsc_fdc37m81x.h&n; *&n; * Interface for smsc fdc48m81x Super IO chip&n; *&n; * Author: MontaVista Software, Inc. source@mvista.com&n; *&n; * 2001-2003 (c) MontaVista Software, Inc. This file is licensed under&n; * the terms of the GNU General Public License version 2. This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; *&n; * Copyright (C) 2004 MontaVista Software Inc.&n; * Manish Lachwani, mlachwani@mvista.com&n; */
macro_line|#ifndef _SMSC_FDC37M81X_H_
DECL|macro|_SMSC_FDC37M81X_H_
mdefine_line|#define _SMSC_FDC37M81X_H_
multiline_comment|/* Common Registers */
DECL|macro|SMSC_FDC37M81X_CONFIG_INDEX
mdefine_line|#define SMSC_FDC37M81X_CONFIG_INDEX  0x00
DECL|macro|SMSC_FDC37M81X_CONFIG_DATA
mdefine_line|#define SMSC_FDC37M81X_CONFIG_DATA   0x01
DECL|macro|SMSC_FDC37M81X_CONF
mdefine_line|#define SMSC_FDC37M81X_CONF          0x02
DECL|macro|SMSC_FDC37M81X_INDEX
mdefine_line|#define SMSC_FDC37M81X_INDEX         0x03
DECL|macro|SMSC_FDC37M81X_DNUM
mdefine_line|#define SMSC_FDC37M81X_DNUM          0x07
DECL|macro|SMSC_FDC37M81X_DID
mdefine_line|#define SMSC_FDC37M81X_DID           0x20
DECL|macro|SMSC_FDC37M81X_DREV
mdefine_line|#define SMSC_FDC37M81X_DREV          0x21
DECL|macro|SMSC_FDC37M81X_PCNT
mdefine_line|#define SMSC_FDC37M81X_PCNT          0x22
DECL|macro|SMSC_FDC37M81X_PMGT
mdefine_line|#define SMSC_FDC37M81X_PMGT          0x23
DECL|macro|SMSC_FDC37M81X_OSC
mdefine_line|#define SMSC_FDC37M81X_OSC           0x24
DECL|macro|SMSC_FDC37M81X_CONFPA0
mdefine_line|#define SMSC_FDC37M81X_CONFPA0       0x26
DECL|macro|SMSC_FDC37M81X_CONFPA1
mdefine_line|#define SMSC_FDC37M81X_CONFPA1       0x27
DECL|macro|SMSC_FDC37M81X_TEST4
mdefine_line|#define SMSC_FDC37M81X_TEST4         0x2B
DECL|macro|SMSC_FDC37M81X_TEST5
mdefine_line|#define SMSC_FDC37M81X_TEST5         0x2C
DECL|macro|SMSC_FDC37M81X_TEST1
mdefine_line|#define SMSC_FDC37M81X_TEST1         0x2D
DECL|macro|SMSC_FDC37M81X_TEST2
mdefine_line|#define SMSC_FDC37M81X_TEST2         0x2E
DECL|macro|SMSC_FDC37M81X_TEST3
mdefine_line|#define SMSC_FDC37M81X_TEST3         0x2F
multiline_comment|/* Logical device numbers */
DECL|macro|SMSC_FDC37M81X_FDD
mdefine_line|#define SMSC_FDC37M81X_FDD           0x00
DECL|macro|SMSC_FDC37M81X_PARALLEL
mdefine_line|#define SMSC_FDC37M81X_PARALLEL      0x03
DECL|macro|SMSC_FDC37M81X_SERIAL1
mdefine_line|#define SMSC_FDC37M81X_SERIAL1       0x04
DECL|macro|SMSC_FDC37M81X_SERIAL2
mdefine_line|#define SMSC_FDC37M81X_SERIAL2       0x05
DECL|macro|SMSC_FDC37M81X_KBD
mdefine_line|#define SMSC_FDC37M81X_KBD           0x07
DECL|macro|SMSC_FDC37M81X_AUXIO
mdefine_line|#define SMSC_FDC37M81X_AUXIO         0x08
DECL|macro|SMSC_FDC37M81X_NONE
mdefine_line|#define SMSC_FDC37M81X_NONE          0xff
multiline_comment|/* Logical device Config Registers */
DECL|macro|SMSC_FDC37M81X_ACTIVE
mdefine_line|#define SMSC_FDC37M81X_ACTIVE        0x30
DECL|macro|SMSC_FDC37M81X_BASEADDR0
mdefine_line|#define SMSC_FDC37M81X_BASEADDR0     0x60
DECL|macro|SMSC_FDC37M81X_BASEADDR1
mdefine_line|#define SMSC_FDC37M81X_BASEADDR1     0x61
DECL|macro|SMSC_FDC37M81X_INT
mdefine_line|#define SMSC_FDC37M81X_INT           0x70
DECL|macro|SMSC_FDC37M81X_INT2
mdefine_line|#define SMSC_FDC37M81X_INT2          0x72
DECL|macro|SMSC_FDC37M81X_LDCR_F0
mdefine_line|#define SMSC_FDC37M81X_LDCR_F0       0xF0
multiline_comment|/* Chip Config Values */
DECL|macro|SMSC_FDC37M81X_CONFIG_ENTER
mdefine_line|#define SMSC_FDC37M81X_CONFIG_ENTER  0x55
DECL|macro|SMSC_FDC37M81X_CONFIG_EXIT
mdefine_line|#define SMSC_FDC37M81X_CONFIG_EXIT   0xaa
DECL|macro|SMSC_FDC37M81X_CHIP_ID
mdefine_line|#define SMSC_FDC37M81X_CHIP_ID       0x4d
r_int
r_int
id|__init
id|smsc_fdc37m81x_init
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_void
id|smsc_fdc37m81x_config_beg
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|smsc_fdc37m81x_config_end
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|smsc_fdc37m81x_config_set
c_func
(paren
id|u8
id|reg
comma
id|u8
id|val
)paren
suffix:semicolon
macro_line|#endif
eof

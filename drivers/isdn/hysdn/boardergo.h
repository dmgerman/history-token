multiline_comment|/* $Id: boardergo.h,v 1.2.6.1 2001/09/23 22:24:54 kai Exp $&n; *&n; * Linux driver for HYSDN cards, definitions for ergo type boards (buffers..).&n; *&n; * Author    Werner Cornelius (werner@titro.de) for Hypercope GmbH&n; * Copyright 1999 by Werner Cornelius (werner@titro.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
multiline_comment|/************************************************/
multiline_comment|/* defines for the dual port memory of the card */
multiline_comment|/************************************************/
DECL|macro|ERG_DPRAM_PAGE_SIZE
mdefine_line|#define ERG_DPRAM_PAGE_SIZE 0x2000&t;/* DPRAM occupies a 8K page */
DECL|macro|BOOT_IMG_SIZE
mdefine_line|#define BOOT_IMG_SIZE 4096
DECL|macro|ERG_DPRAM_FILL_SIZE
mdefine_line|#define ERG_DPRAM_FILL_SIZE (ERG_DPRAM_PAGE_SIZE - BOOT_IMG_SIZE)
DECL|macro|ERG_TO_HY_BUF_SIZE
mdefine_line|#define ERG_TO_HY_BUF_SIZE  0x0E00&t;/* 3072 bytes buffer size to card */
DECL|macro|ERG_TO_PC_BUF_SIZE
mdefine_line|#define ERG_TO_PC_BUF_SIZE  0x0E00&t;/* 3072 bytes to PC, too */
multiline_comment|/* following DPRAM layout copied from OS2-driver boarderg.h */
DECL|struct|ErgDpram_tag
r_typedef
r_struct
id|ErgDpram_tag
(brace
DECL|member|ToHyBuf
multiline_comment|/*0000 */
id|uchar
id|ToHyBuf
(braket
id|ERG_TO_HY_BUF_SIZE
)braket
suffix:semicolon
DECL|member|ToPcBuf
multiline_comment|/*0E00 */
id|uchar
id|ToPcBuf
(braket
id|ERG_TO_PC_BUF_SIZE
)braket
suffix:semicolon
DECL|member|bSoftUart
multiline_comment|/*1C00 */
id|uchar
id|bSoftUart
(braket
id|SIZE_RSV_SOFT_UART
)braket
suffix:semicolon
multiline_comment|/* size 0x1B0 */
DECL|member|ErrLogMsg
multiline_comment|/*1DB0 */
multiline_comment|/* tErrLogEntry */
id|uchar
r_volatile
id|ErrLogMsg
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* size 64 bytes */
multiline_comment|/*1DB0  ulong ulErrType;               */
multiline_comment|/*1DB4  ulong ulErrSubtype;            */
multiline_comment|/*1DB8  ulong ucTextSize;              */
multiline_comment|/*1DB9  ulong ucText[ERRLOG_TEXT_SIZE]; */
multiline_comment|/* ASCIIZ of len ucTextSize-1 */
multiline_comment|/*1DF0 */
DECL|member|ToHyChannel
multiline_comment|/*1DF0 */
id|word
r_volatile
id|ToHyChannel
suffix:semicolon
DECL|member|ToHySize
multiline_comment|/*1DF2 */
id|word
r_volatile
id|ToHySize
suffix:semicolon
DECL|member|ToHyFlag
multiline_comment|/*1DF4 */
id|uchar
r_volatile
id|ToHyFlag
suffix:semicolon
multiline_comment|/* !=0: msg for Hy waiting */
DECL|member|ToPcFlag
multiline_comment|/*1DF5 */
id|uchar
r_volatile
id|ToPcFlag
suffix:semicolon
multiline_comment|/* !=0: msg for PC waiting */
DECL|member|ToPcChannel
multiline_comment|/*1DF6 */
id|word
r_volatile
id|ToPcChannel
suffix:semicolon
DECL|member|ToPcSize
multiline_comment|/*1DF8 */
id|word
r_volatile
id|ToPcSize
suffix:semicolon
DECL|member|bRes1DBA
multiline_comment|/*1DFA */
id|uchar
id|bRes1DBA
(braket
l_int|0x1E00
op_minus
l_int|0x1DFA
)braket
suffix:semicolon
multiline_comment|/* 6 bytes */
DECL|member|bRestOfEntryTbl
multiline_comment|/*1E00 */
id|uchar
id|bRestOfEntryTbl
(braket
l_int|0x1F00
op_minus
l_int|0x1E00
)braket
suffix:semicolon
DECL|member|TrapTable
multiline_comment|/*1F00 */
id|ulong
id|TrapTable
(braket
l_int|62
)braket
suffix:semicolon
DECL|member|bRes1FF8
multiline_comment|/*1FF8 */
id|uchar
id|bRes1FF8
(braket
l_int|0x1FFB
op_minus
l_int|0x1FF8
)braket
suffix:semicolon
multiline_comment|/* low part of reset vetor */
DECL|member|ToPcIntMetro
multiline_comment|/*1FFB */
id|uchar
id|ToPcIntMetro
suffix:semicolon
multiline_comment|/* notes:&n;&t; * - metro has 32-bit boot ram - accessing&n;&t; *   ToPcInt and ToHyInt would be the same;&n;&t; *   so we moved ToPcInt to 1FFB.&n;&t; *   Because on the PC side both vars are&n;&t; *   readonly (reseting on int from E1 to PC),&n;&t; *   we can read both vars on both cards&n;&t; *   without destroying anything.&n;&t; * - 1FFB is the high byte of the reset vector,&n;&t; *   so E1 side should NOT change this byte&n;&t; *   when writing!&n;&t; */
DECL|member|ToHyNoDpramErrLog
multiline_comment|/*1FFC */
id|uchar
r_volatile
id|ToHyNoDpramErrLog
suffix:semicolon
multiline_comment|/* note: ToHyNoDpramErrLog is used to inform&n;&t; *       boot loader, not to use DPRAM based&n;&t; *       ErrLog; when DOS driver is rewritten&n;&t; *       this becomes obsolete&n;&t; */
DECL|member|bRes1FFD
multiline_comment|/*1FFD */
id|uchar
id|bRes1FFD
suffix:semicolon
DECL|member|ToPcInt
multiline_comment|/*1FFE */
id|uchar
id|ToPcInt
suffix:semicolon
multiline_comment|/* E1_intclear; on CHAMP2: E1_intset   */
DECL|member|ToHyInt
multiline_comment|/*1FFF */
id|uchar
id|ToHyInt
suffix:semicolon
multiline_comment|/* E1_intset;   on CHAMP2: E1_intclear */
DECL|typedef|tErgDpram
)brace
id|tErgDpram
suffix:semicolon
multiline_comment|/**********************************************/
multiline_comment|/* PCI9050 controller local register offsets: */
multiline_comment|/* copied from boarderg.c                     */
multiline_comment|/**********************************************/
DECL|macro|PCI9050_INTR_REG
mdefine_line|#define PCI9050_INTR_REG    0x4C&t;/* Interrupt register */
DECL|macro|PCI9050_USER_IO
mdefine_line|#define PCI9050_USER_IO     0x51&t;/* User I/O  register */
multiline_comment|/* bitmask for PCI9050_INTR_REG: */
DECL|macro|PCI9050_INTR_REG_EN1
mdefine_line|#define PCI9050_INTR_REG_EN1    0x01&t;/* 1= enable (def.), 0= disable */
DECL|macro|PCI9050_INTR_REG_POL1
mdefine_line|#define PCI9050_INTR_REG_POL1   0x02&t;/* 1= active high (def.), 0= active low */
DECL|macro|PCI9050_INTR_REG_STAT1
mdefine_line|#define PCI9050_INTR_REG_STAT1  0x04&t;/* 1= intr. active, 0= intr. not active (def.) */
DECL|macro|PCI9050_INTR_REG_ENPCI
mdefine_line|#define PCI9050_INTR_REG_ENPCI  0x40&t;/* 1= PCI interrupts enable (def.) */
multiline_comment|/* bitmask for PCI9050_USER_IO: */
DECL|macro|PCI9050_USER_IO_EN3
mdefine_line|#define PCI9050_USER_IO_EN3     0x02&t;/* 1= disable      , 0= enable (def.) */
DECL|macro|PCI9050_USER_IO_DIR3
mdefine_line|#define PCI9050_USER_IO_DIR3    0x04&t;/* 1= output (def.), 0= input         */
DECL|macro|PCI9050_USER_IO_DAT3
mdefine_line|#define PCI9050_USER_IO_DAT3    0x08&t;/* 1= high (def.)  , 0= low           */
DECL|macro|PCI9050_E1_RESET
mdefine_line|#define PCI9050_E1_RESET    (                     PCI9050_USER_IO_DIR3)&t;&t;/* 0x04 */
DECL|macro|PCI9050_E1_RUN
mdefine_line|#define PCI9050_E1_RUN      (PCI9050_USER_IO_DAT3|PCI9050_USER_IO_DIR3)&t;&t;/* 0x0C */
eof

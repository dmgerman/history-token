macro_line|#ifndef _NACA_H
DECL|macro|_NACA_H
mdefine_line|#define _NACA_H
multiline_comment|/* &n; * c 2001 PPC 64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/systemcfg.h&gt;
macro_line|#ifndef __ASSEMBLY__
DECL|struct|naca_struct
r_struct
id|naca_struct
(brace
multiline_comment|/*==================================================================&n;&t; * Cache line 1: 0x0000 - 0x007F&n;&t; * Kernel only data - undefined for user space&n;&t; *==================================================================&n;&t; */
DECL|member|xItVpdAreas
r_void
op_star
id|xItVpdAreas
suffix:semicolon
multiline_comment|/* VPD Data                  0x00 */
DECL|member|xRamDisk
r_void
op_star
id|xRamDisk
suffix:semicolon
multiline_comment|/* iSeries ramdisk           0x08 */
DECL|member|xRamDiskSize
id|u64
id|xRamDiskSize
suffix:semicolon
multiline_comment|/* In pages                  0x10 */
DECL|member|paca
r_struct
id|paca_struct
op_star
id|paca
suffix:semicolon
multiline_comment|/* Ptr to an array of pacas  0x18 */
DECL|member|debug_switch
id|u64
id|debug_switch
suffix:semicolon
multiline_comment|/* Debug print control       0x20 */
DECL|member|banner
id|u64
id|banner
suffix:semicolon
multiline_comment|/* Ptr to banner string      0x28 */
DECL|member|log
id|u64
id|log
suffix:semicolon
multiline_comment|/* Ptr to log buffer         0x30 */
DECL|member|serialPortAddr
id|u64
id|serialPortAddr
suffix:semicolon
multiline_comment|/* Phy addr of serial port   0x38 */
DECL|member|interrupt_controller
id|u64
id|interrupt_controller
suffix:semicolon
multiline_comment|/* Type of int controller    0x40 */
DECL|member|slb_size
id|u64
id|slb_size
suffix:semicolon
multiline_comment|/* SLB size in entries       0x48 */
DECL|member|pftSize
id|u64
id|pftSize
suffix:semicolon
multiline_comment|/* Log 2 of page table size  0x50 */
DECL|member|systemcfg
r_void
op_star
id|systemcfg
suffix:semicolon
multiline_comment|/* Pointer to systemcfg data 0x58 */
DECL|member|dCacheL1LogLineSize
id|u32
id|dCacheL1LogLineSize
suffix:semicolon
multiline_comment|/* L1 d-cache line size Log2 0x60 */
DECL|member|dCacheL1LinesPerPage
id|u32
id|dCacheL1LinesPerPage
suffix:semicolon
multiline_comment|/* L1 d-cache lines / page   0x64 */
DECL|member|iCacheL1LogLineSize
id|u32
id|iCacheL1LogLineSize
suffix:semicolon
multiline_comment|/* L1 i-cache line size Log2 0x68 */
DECL|member|iCacheL1LinesPerPage
id|u32
id|iCacheL1LinesPerPage
suffix:semicolon
multiline_comment|/* L1 i-cache lines / page   0x6c */
DECL|member|smt_snooze_delay
id|u64
id|smt_snooze_delay
suffix:semicolon
multiline_comment|/* Delay (in usec) before    0x70 */
multiline_comment|/* entering ST mode               */
DECL|member|smt_state
id|u8
id|smt_state
suffix:semicolon
multiline_comment|/* 0 = SMT off               0x78 */
multiline_comment|/* 1 = SMT on                     */
multiline_comment|/* 2 = SMT dynamic                */
DECL|member|resv0
id|u8
id|resv0
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* Reserved           0x70 - 0x7F */
)brace
suffix:semicolon
r_extern
r_struct
id|naca_struct
op_star
id|naca
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|NACA_PAGE
mdefine_line|#define NACA_PAGE      0x4
DECL|macro|NACA_PHYS_ADDR
mdefine_line|#define NACA_PHYS_ADDR (NACA_PAGE&lt;&lt;PAGE_SHIFT)
DECL|macro|NACA_VIRT_ADDR
mdefine_line|#define NACA_VIRT_ADDR (KERNELBASE+NACA_PHYS_ADDR)
macro_line|#endif /* _NACA_H */
eof

macro_line|#ifndef _NACA_H
DECL|macro|_NACA_H
mdefine_line|#define _NACA_H
multiline_comment|/* &n; * c 2001 PPC 64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/types.h&gt;
DECL|struct|naca_struct
r_struct
id|naca_struct
(brace
DECL|member|xItVpdAreas
r_void
op_star
id|xItVpdAreas
suffix:semicolon
DECL|member|xRamDisk
r_void
op_star
id|xRamDisk
suffix:semicolon
DECL|member|xRamDiskSize
id|u64
id|xRamDiskSize
suffix:semicolon
multiline_comment|/* In pages */
DECL|member|paca
r_struct
id|paca_struct
op_star
id|paca
suffix:semicolon
multiline_comment|/* Ptr to an array of pacas */
DECL|member|debug_switch
id|u64
id|debug_switch
suffix:semicolon
multiline_comment|/* Bits to control debug printing */
DECL|member|processorCount
id|u16
id|processorCount
suffix:semicolon
multiline_comment|/* # of physical processors */
DECL|member|dCacheL1LineSize
id|u16
id|dCacheL1LineSize
suffix:semicolon
multiline_comment|/* Line size of L1 DCache in bytes */
DECL|member|dCacheL1LogLineSize
id|u16
id|dCacheL1LogLineSize
suffix:semicolon
multiline_comment|/* Log-2 of DCache line size */
DECL|member|dCacheL1LinesPerPage
id|u16
id|dCacheL1LinesPerPage
suffix:semicolon
multiline_comment|/* DCache lines per page */
DECL|member|iCacheL1LineSize
id|u16
id|iCacheL1LineSize
suffix:semicolon
multiline_comment|/* Line size of L1 ICache in bytes */
DECL|member|iCacheL1LogLineSize
id|u16
id|iCacheL1LogLineSize
suffix:semicolon
multiline_comment|/* Log-2 of ICache line size */
DECL|member|iCacheL1LinesPerPage
id|u16
id|iCacheL1LinesPerPage
suffix:semicolon
multiline_comment|/* ICache lines per page */
DECL|member|slb_size
id|u16
id|slb_size
suffix:semicolon
multiline_comment|/* SLB size in entries */
DECL|member|physicalMemorySize
id|u64
id|physicalMemorySize
suffix:semicolon
multiline_comment|/* Size of real memory in bytes */
DECL|member|pftSize
id|u64
id|pftSize
suffix:semicolon
multiline_comment|/* Log base 2 of page table size */
DECL|member|serialPortAddr
id|u64
id|serialPortAddr
suffix:semicolon
multiline_comment|/* Phyical address of serial port */
DECL|member|interrupt_controller
id|u8
id|interrupt_controller
suffix:semicolon
multiline_comment|/* Type of interrupt controller */
DECL|member|resv0
id|u8
id|resv0
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Padding */
)brace
suffix:semicolon
r_extern
r_struct
id|naca_struct
op_star
id|naca
suffix:semicolon
macro_line|#endif /* _NACA_H */
eof

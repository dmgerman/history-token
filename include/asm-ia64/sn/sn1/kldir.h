multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_SN1_KLDIR_H
DECL|macro|_ASM_SN_SN1_KLDIR_H
mdefine_line|#define _ASM_SN_SN1_KLDIR_H
multiline_comment|/*&n; * The upper portion of the memory map applies during boot&n; * only and is overwritten by IRIX/SYMMON.  The minimum memory bank&n; * size on IP35 is 64M, which provides a limit on the amount of space&n; * the PROM can assume it has available.&n; *&n; * Most of the addresses below are defined as macros in this file, or&n; * in SN/addrs.h or SN/SN1/addrs.h.&n; *&n; *                                    MEMORY MAP PER NODE&n; *&n; * 0x4000000 (64M)         +-----------------------------------------+&n; *                         |                                         |&n; *                         |                                         |&n; *                         |      IO7 TEXT/DATA/BSS/stack            |&n; * 0x3000000 (48M)         +-----------------------------------------+&n; *                         |      Free                               |&n; * 0x2102000 (&gt;33M)        +-----------------------------------------+&n; *                         |      IP35 Topology (PCFG) + misc data   |&n; * 0x2000000 (32M)         +-----------------------------------------+&n; *                         |      IO7 BUFFERS FOR FLASH ENET IOC3    |&n; * 0x1F80000 (31.5M)       +-----------------------------------------+&n; *                         |      Free                               |&n; * 0x1C00000 (28M)         +-----------------------------------------+&n; *                         |      IP35 PROM TEXT/DATA/BSS/stack      |&n; * 0x1A00000 (26M)         +-----------------------------------------+&n; *                         |      Routing temp. space                |&n; * 0x1800000 (24M)         +-----------------------------------------+&n; *                         |      Diagnostics temp. space            |&n; * 0x1500000 (21M)         +-----------------------------------------+&n; *                         |      Free                               |&n; * 0x1400000 (20M)         +-----------------------------------------+&n; *                         |      IO7 PROM temporary copy            |&n; * 0x1300000 (19M)         +-----------------------------------------+&n; *                         |                                         |&n; *                         |      Free                               |&n; *                         |      (UNIX DATA starts above 0x1000000) |&n; *                         |                                         |&n; *                         +-----------------------------------------+&n; *                         |      UNIX DEBUG Version                 |&n; * 0x0310000 (3.1M)        +-----------------------------------------+&n; *                         |      SYMMON, loaded just below UNIX     |&n; *                         |      (For UNIX Debug only)              |&n; *                         |                                         |&n; *                         |                                         |&n; * 0x006C000 (432K)        +-----------------------------------------+&n; *                         |      SYMMON STACK [NUM_CPU_PER_NODE]    |&n; *                         |      (For UNIX Debug only)              |&n; * 0x004C000 (304K)        +-----------------------------------------+&n; *                         |                                         |&n; *                         |                                         |&n; *                         |      UNIX NON-DEBUG Version             |&n; * 0x0040000 (256K)        +-----------------------------------------+&n; *&n; *&n; * The lower portion of the memory map contains information that is&n; * permanent and is used by the IP35PROM, IO7PROM and IRIX.&n; *&n; * 0x40000 (256K)          +-----------------------------------------+&n; *                         |                                         |&n; *                         |      KLCONFIG (64K)                     |&n; *                         |                                         |&n; * 0x30000 (192K)          +-----------------------------------------+&n; *                         |                                         |&n; *                         |      PI Error Spools (64K)              |&n; *                         |                                         |&n; * 0x20000 (128K)          +-----------------------------------------+&n; *                         |                                         |&n; *                         |      Unused                             |&n; *                         |                                         |&n; * 0x19000 (100K)          +-----------------------------------------+&n; *                         |      Early cache Exception stack (CPU 3)|&n; * 0x18800 (98K)           +-----------------------------------------+&n; *&t;&t;&t;   |      cache error eframe (CPU 3)&t;     |&n; * 0x18400 (97K)           +-----------------------------------------+&n; *                         |      Exception Handlers (CPU 3)         |&n; * 0x18000 (96K)           +-----------------------------------------+&n; *                         |                                         |&n; *                         |      Unused                             |&n; *                         |                                         |&n; * 0x13c00 (79K)           +-----------------------------------------+&n; *                         |      GPDA (8k)                          |&n; * 0x11c00 (71K)           +-----------------------------------------+&n; *                         |      Early cache Exception stack (CPU 2)|&n; * 0x10800 (66k)&t;   +-----------------------------------------+&n; *&t;&t;&t;   |      cache error eframe (CPU 2)&t;     |&n; * 0x10400 (65K)           +-----------------------------------------+&n; *                         |      Exception Handlers (CPU 2)         |&n; * 0x10000 (64K)           +-----------------------------------------+&n; *                         |                                         |&n; *                         |      Unused                             |&n; *                         |                                         |&n; * 0x0b400 (45K)           +-----------------------------------------+&n; *                         |      GDA (1k)                           |&n; * 0x0b000 (44K)           +-----------------------------------------+&n; *                         |      NMI Eframe areas (4)       &t;     |&n; * 0x0a000 (40K)           +-----------------------------------------+&n; *                         |      NMI Register save areas (4)        |&n; * 0x09000 (36K)           +-----------------------------------------+&n; *                         |      Early cache Exception stack (CPU 1)|&n; * 0x08800 (34K)           +-----------------------------------------+&n; *&t;&t;&t;   |      cache error eframe (CPU 1)&t;     |&n; * 0x08400 (33K)           +-----------------------------------------+&n; *                         |      Exception Handlers (CPU 1)         |&n; * 0x08000 (32K)           +-----------------------------------------+&n; *                         |                                         |&n; *                         |                                         |&n; *                         |      Unused                             |&n; *                         |                                         |&n; *                         |                                         |&n; * 0x04000 (16K)           +-----------------------------------------+&n; *                         |      NMI Handler (Protected Page)       |&n; * 0x03000 (12K)           +-----------------------------------------+&n; *                         |      ARCS PVECTORS (master node only)   |&n; * 0x02c00 (11K)           +-----------------------------------------+&n; *                         |      ARCS TVECTORS (master node only)   |&n; * 0x02800 (10K)           +-----------------------------------------+&n; *                         |      LAUNCH [NUM_CPU]                   |&n; * 0x02400 (9K)            +-----------------------------------------+&n; *                         |      Low memory directory (KLDIR)       |&n; * 0x02000 (8K)            +-----------------------------------------+&n; *                         |      ARCS SPB (1K)                      |&n; * 0x01000 (4K)            +-----------------------------------------+&n; *                         |      Early cache Exception stack (CPU 0)|&n; * 0x00800 (2k)&t;           +-----------------------------------------+&n; *&t;&t;&t;   |      cache error eframe (CPU 0)&t;     |&n; * 0x00400 (1K)            +-----------------------------------------+&n; *                         |      Exception Handlers (CPU 0)         |&n; * 0x00000 (0K)            +-----------------------------------------+&n; */
multiline_comment|/*&n; * NOTE:  To change the kernel load address, you must update:&n; *  - the appropriate elspec files in irix/kern/master.d&n; *  - NODEBUGUNIX_ADDR in SN/SN1/addrs.h&n; *  - IP27_FREEMEM_OFFSET below&n; *  - KERNEL_START_OFFSET below (if supporting cells)&n; */
multiline_comment|/*&n; * This is defined here because IP27_SYMMON_STK_SIZE must be at least what&n; * we define here.  Since it&squot;s set up in the prom.  We can&squot;t redefine it later&n; * and expect more space to be allocated.  The way to find out the true size&n; * of the symmon stacks is to divide SYMMON_STK_SIZE by SYMMON_STK_STRIDE&n; * for a particular node.&n; */
DECL|macro|SYMMON_STACK_SIZE
mdefine_line|#define SYMMON_STACK_SIZE&t;&t;0x8000
macro_line|#if defined (PROM) || defined (SABLE)
multiline_comment|/*&n; * These defines are prom version dependent.  No code other than the IP35&n; * prom should attempt to use these values.&n; */
DECL|macro|IP27_LAUNCH_OFFSET
mdefine_line|#define IP27_LAUNCH_OFFSET&t;&t;0x2400
DECL|macro|IP27_LAUNCH_SIZE
mdefine_line|#define IP27_LAUNCH_SIZE&t;&t;0x400
DECL|macro|IP27_LAUNCH_COUNT
mdefine_line|#define IP27_LAUNCH_COUNT&t;&t;4
DECL|macro|IP27_LAUNCH_STRIDE
mdefine_line|#define IP27_LAUNCH_STRIDE&t;&t;0x100 /* could be as small as 0x80 */
DECL|macro|IP27_KLCONFIG_OFFSET
mdefine_line|#define IP27_KLCONFIG_OFFSET&t;&t;0x30000
DECL|macro|IP27_KLCONFIG_SIZE
mdefine_line|#define IP27_KLCONFIG_SIZE&t;&t;0x10000
DECL|macro|IP27_KLCONFIG_COUNT
mdefine_line|#define IP27_KLCONFIG_COUNT&t;&t;1
DECL|macro|IP27_KLCONFIG_STRIDE
mdefine_line|#define IP27_KLCONFIG_STRIDE&t;&t;0
DECL|macro|IP27_NMI_OFFSET
mdefine_line|#define IP27_NMI_OFFSET&t;&t;&t;0x3000
DECL|macro|IP27_NMI_SIZE
mdefine_line|#define IP27_NMI_SIZE&t;&t;&t;0x100
DECL|macro|IP27_NMI_COUNT
mdefine_line|#define IP27_NMI_COUNT&t;&t;&t;4
DECL|macro|IP27_NMI_STRIDE
mdefine_line|#define IP27_NMI_STRIDE&t;&t;&t;0x40
DECL|macro|IP27_PI_ERROR_OFFSET
mdefine_line|#define IP27_PI_ERROR_OFFSET&t;&t;0x20000
DECL|macro|IP27_PI_ERROR_SIZE
mdefine_line|#define IP27_PI_ERROR_SIZE&t;&t;0x10000
DECL|macro|IP27_PI_ERROR_COUNT
mdefine_line|#define IP27_PI_ERROR_COUNT&t;&t;1
DECL|macro|IP27_PI_ERROR_STRIDE
mdefine_line|#define IP27_PI_ERROR_STRIDE&t;&t;0
DECL|macro|IP27_SYMMON_STK_OFFSET
mdefine_line|#define IP27_SYMMON_STK_OFFSET&t;&t;0x4c000
DECL|macro|IP27_SYMMON_STK_SIZE
mdefine_line|#define IP27_SYMMON_STK_SIZE&t;&t;0x20000
DECL|macro|IP27_SYMMON_STK_COUNT
mdefine_line|#define IP27_SYMMON_STK_COUNT&t;&t;4
multiline_comment|/* IP27_SYMMON_STK_STRIDE must be &gt;= SYMMON_STACK_SIZE */
DECL|macro|IP27_SYMMON_STK_STRIDE
mdefine_line|#define IP27_SYMMON_STK_STRIDE&t;&t;0x8000
DECL|macro|IP27_FREEMEM_OFFSET
mdefine_line|#define IP27_FREEMEM_OFFSET&t;&t;0x40000
DECL|macro|IP27_FREEMEM_SIZE
mdefine_line|#define IP27_FREEMEM_SIZE&t;&t;-1
DECL|macro|IP27_FREEMEM_COUNT
mdefine_line|#define IP27_FREEMEM_COUNT&t;&t;1
DECL|macro|IP27_FREEMEM_STRIDE
mdefine_line|#define IP27_FREEMEM_STRIDE&t;&t;0
macro_line|#endif /* PROM || SABLE*/
multiline_comment|/*&n; * There will be only one of these in a partition so the IO7 must set it up.&n; */
DECL|macro|IO6_GDA_OFFSET
mdefine_line|#define IO6_GDA_OFFSET&t;&t;&t;0xb000
DECL|macro|IO6_GDA_SIZE
mdefine_line|#define IO6_GDA_SIZE&t;&t;&t;0x400
DECL|macro|IO6_GDA_COUNT
mdefine_line|#define IO6_GDA_COUNT&t;&t;&t;1
DECL|macro|IO6_GDA_STRIDE
mdefine_line|#define IO6_GDA_STRIDE&t;&t;&t;0
multiline_comment|/*&n; * save area of kernel nmi regs in the prom format&n; */
DECL|macro|IP27_NMI_KREGS_OFFSET
mdefine_line|#define IP27_NMI_KREGS_OFFSET&t;&t;0x9000
DECL|macro|IP27_NMI_KREGS_CPU_SIZE
mdefine_line|#define IP27_NMI_KREGS_CPU_SIZE&t;&t;0x400
multiline_comment|/*&n; * save area of kernel nmi regs in eframe format &n; */
DECL|macro|IP27_NMI_EFRAME_OFFSET
mdefine_line|#define IP27_NMI_EFRAME_OFFSET&t;&t;0xa000
DECL|macro|IP27_NMI_EFRAME_SIZE
mdefine_line|#define IP27_NMI_EFRAME_SIZE&t;&t;0x400
DECL|macro|GPDA_OFFSET
mdefine_line|#define GPDA_OFFSET&t;&t;&t;0x11c00
macro_line|#endif /* _ASM_SN_SN1_KLDIR_H */
eof

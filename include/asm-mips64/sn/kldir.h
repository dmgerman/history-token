multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Derived from IRIX &lt;sys/SN/kldir.h&gt;, revision 1.21.&n; *&n; * Copyright (C) 1992 - 1997, 1999, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 1999, 2000 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_SN_KLDIR_H
DECL|macro|_ASM_SN_KLDIR_H
mdefine_line|#define _ASM_SN_KLDIR_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_SGI_IO)
macro_line|#include &lt;asm/hack.h&gt;
macro_line|#endif
multiline_comment|/*&n; * The kldir memory area resides at a fixed place in each node&squot;s memory and&n; * provides pointers to most other IP27 memory areas.  This allows us to&n; * resize and/or relocate memory areas at a later time without breaking all&n; * firmware and kernels that use them.  Indices in the array are&n; * permanently dedicated to areas listed below.  Some memory areas (marked&n; * below) reside at a permanently fixed location, but are included in the&n; * directory for completeness.&n; */
DECL|macro|KLDIR_MAGIC
mdefine_line|#define KLDIR_MAGIC&t;&t;0x434d5f53505f5357
multiline_comment|/*&n; * The upper portion of the memory map applies during boot&n; * only and is overwritten by IRIX/SYMMON.&n; *&n; *                                    MEMORY MAP PER NODE&n; *&n; * 0x2000000 (32M)         +-----------------------------------------+&n; *                         |      IO6 BUFFERS FOR FLASH ENET IOC3    |&n; * 0x1F80000 (31.5M)       +-----------------------------------------+&n; *                         |      IO6 TEXT/DATA/BSS/stack            |&n; * 0x1C00000 (30M)         +-----------------------------------------+&n; *                         |      IO6 PROM DEBUG TEXT/DATA/BSS/stack |&n; * 0x0800000 (28M)         +-----------------------------------------+&n; *                         |      IP27 PROM TEXT/DATA/BSS/stack      |&n; * 0x1B00000 (27M)         +-----------------------------------------+&n; *                         |      IP27 CFG                           |&n; * 0x1A00000 (26M)         +-----------------------------------------+&n; *                         |      Graphics PROM                      |&n; * 0x1800000 (24M)         +-----------------------------------------+&n; *                         |      3rd Party PROM drivers             |&n; * 0x1600000 (22M)         +-----------------------------------------+&n; *                         |                                         |&n; *                         |      Free                               |&n; *                         |                                         |&n; *                         +-----------------------------------------+&n; *                         |      UNIX DEBUG Version                 |&n; * 0x190000 (2M--)         +-----------------------------------------+&n; *                         |      SYMMON                             |&n; *                         |      (For UNIX Debug only)              |&n; * 0x34000 (208K)          +-----------------------------------------+&n; *                         |      SYMMON STACK [NUM_CPU_PER_NODE]    |&n; *                         |      (For UNIX Debug only)              |&n; * 0x25000 (148K)          +-----------------------------------------+&n; *                         |      KLCONFIG - II (temp)               |&n; *                         |                                         |&n; *                         |    ----------------------------         |&n; *                         |                                         |&n; *                         |      UNIX NON-DEBUG Version             |&n; * 0x19000 (100K)          +-----------------------------------------+&n; *&n; *&n; * The lower portion of the memory map contains information that is&n; * permanent and is used by the IP27PROM, IO6PROM and IRIX.&n; *&n; * 0x19000 (100K)          +-----------------------------------------+&n; *                         |                                         |&n; *                         |      PI Error Spools (32K)              |&n; *                         |                                         |&n; * 0x12000 (72K)           +-----------------------------------------+&n; *                         |      Unused                             |&n; * 0x11c00 (71K)           +-----------------------------------------+&n; *                         |      CPU 1 NMI Eframe area       &t;     |&n; * 0x11a00 (70.5K)         +-----------------------------------------+&n; *                         |      CPU 0 NMI Eframe area       &t;     |&n; * 0x11800 (70K)           +-----------------------------------------+&n; *                         |      CPU 1 NMI Register save area       |&n; * 0x11600 (69.5K)         +-----------------------------------------+&n; *                         |      CPU 0 NMI Register save area       |&n; * 0x11400 (69K)           +-----------------------------------------+&n; *                         |      GDA (1k)                           |&n; * 0x11000 (68K)           +-----------------------------------------+&n; *                         |      Early cache Exception stack        |&n; *                         |             and/or                      |&n; *&t;&t;&t;   |      kernel/io6prom nmi registers&t;     |&n; * 0x10800  (66k)&t;   +-----------------------------------------+&n; *&t;&t;&t;   |      cache error eframe   &t; &t;     |&n; * 0x10400 (65K)           +-----------------------------------------+&n; *                         |      Exception Handlers (UALIAS copy)   |&n; * 0x10000 (64K)           +-----------------------------------------+&n; *                         |                                         |&n; *                         |                                         |&n; *                         |      KLCONFIG - I (permanent) (48K)     |&n; *                         |                                         |&n; *                         |                                         |&n; *                         |                                         |&n; * 0x4000 (16K)            +-----------------------------------------+&n; *                         |      NMI Handler (Protected Page)       |&n; * 0x3000 (12K)            +-----------------------------------------+&n; *                         |      ARCS PVECTORS (master node only)   |&n; * 0x2c00 (11K)            +-----------------------------------------+&n; *                         |      ARCS TVECTORS (master node only)   |&n; * 0x2800 (10K)            +-----------------------------------------+&n; *                         |      LAUNCH [NUM_CPU]                   |&n; * 0x2400 (9K)             +-----------------------------------------+&n; *                         |      Low memory directory (KLDIR)       |&n; * 0x2000 (8K)             +-----------------------------------------+&n; *                         |      ARCS SPB (1K)                      |&n; * 0x1000 (4K)             +-----------------------------------------+&n; *                         |      Early cache Exception stack        |&n; *                         |             and/or                      |&n; *&t;&t;&t;   |      kernel/io6prom nmi registers&t;     |&n; * 0x800  (2k)&t;           +-----------------------------------------+&n; *&t;&t;&t;   |      cache error eframe   &t; &t;     |&n; * 0x400 (1K)              +-----------------------------------------+&n; *                         |      Exception Handlers                 |&n; * 0x0   (0K)              +-----------------------------------------+&n; */
macro_line|#ifdef LANGUAGE_ASSEMBLY
DECL|macro|KLDIR_OFF_MAGIC
mdefine_line|#define KLDIR_OFF_MAGIC&t;&t;&t;0x00
DECL|macro|KLDIR_OFF_OFFSET
mdefine_line|#define KLDIR_OFF_OFFSET&t;&t;0x08
DECL|macro|KLDIR_OFF_POINTER
mdefine_line|#define KLDIR_OFF_POINTER&t;&t;0x10
DECL|macro|KLDIR_OFF_SIZE
mdefine_line|#define KLDIR_OFF_SIZE&t;&t;&t;0x18
DECL|macro|KLDIR_OFF_COUNT
mdefine_line|#define KLDIR_OFF_COUNT&t;&t;&t;0x20
DECL|macro|KLDIR_OFF_STRIDE
mdefine_line|#define KLDIR_OFF_STRIDE&t;&t;0x28
macro_line|#endif /* LANGUAGE_ASSEMBLY */
macro_line|#if !defined(CONFIG_SGI_IO)
multiline_comment|/*&n; * This is defined here because IP27_SYMMON_STK_SIZE must be at least what&n; * we define here.  Since it&squot;s set up in the prom.  We can&squot;t redefine it later&n; * and expect more space to be allocated.  The way to find out the true size&n; * of the symmon stacks is to divide SYMMON_STK_SIZE by SYMMON_STK_STRIDE&n; * for a particular node.&n; */
DECL|macro|SYMMON_STACK_SIZE
mdefine_line|#define SYMMON_STACK_SIZE&t;&t;0x8000
macro_line|#if defined (PROM) || defined (SABLE)
multiline_comment|/*&n; * These defines are prom version dependent.  No code other than the IP27&n; * prom should attempt to use these values.&n; */
DECL|macro|IP27_LAUNCH_OFFSET
mdefine_line|#define IP27_LAUNCH_OFFSET&t;&t;0x2400
DECL|macro|IP27_LAUNCH_SIZE
mdefine_line|#define IP27_LAUNCH_SIZE&t;&t;0x400
DECL|macro|IP27_LAUNCH_COUNT
mdefine_line|#define IP27_LAUNCH_COUNT&t;&t;2
DECL|macro|IP27_LAUNCH_STRIDE
mdefine_line|#define IP27_LAUNCH_STRIDE&t;&t;0x200
DECL|macro|IP27_KLCONFIG_OFFSET
mdefine_line|#define IP27_KLCONFIG_OFFSET&t;&t;0x4000
DECL|macro|IP27_KLCONFIG_SIZE
mdefine_line|#define IP27_KLCONFIG_SIZE&t;&t;0xc000
DECL|macro|IP27_KLCONFIG_COUNT
mdefine_line|#define IP27_KLCONFIG_COUNT&t;&t;1
DECL|macro|IP27_KLCONFIG_STRIDE
mdefine_line|#define IP27_KLCONFIG_STRIDE&t;&t;0
DECL|macro|IP27_NMI_OFFSET
mdefine_line|#define IP27_NMI_OFFSET&t;&t;&t;0x3000
DECL|macro|IP27_NMI_SIZE
mdefine_line|#define IP27_NMI_SIZE&t;&t;&t;0x40
DECL|macro|IP27_NMI_COUNT
mdefine_line|#define IP27_NMI_COUNT&t;&t;&t;2
DECL|macro|IP27_NMI_STRIDE
mdefine_line|#define IP27_NMI_STRIDE&t;&t;&t;0x40
DECL|macro|IP27_PI_ERROR_OFFSET
mdefine_line|#define IP27_PI_ERROR_OFFSET&t;&t;0x12000
DECL|macro|IP27_PI_ERROR_SIZE
mdefine_line|#define IP27_PI_ERROR_SIZE&t;&t;0x4000
DECL|macro|IP27_PI_ERROR_COUNT
mdefine_line|#define IP27_PI_ERROR_COUNT&t;&t;1
DECL|macro|IP27_PI_ERROR_STRIDE
mdefine_line|#define IP27_PI_ERROR_STRIDE&t;&t;0
DECL|macro|IP27_SYMMON_STK_OFFSET
mdefine_line|#define IP27_SYMMON_STK_OFFSET&t;&t;0x25000
DECL|macro|IP27_SYMMON_STK_SIZE
mdefine_line|#define IP27_SYMMON_STK_SIZE&t;&t;0xe000
DECL|macro|IP27_SYMMON_STK_COUNT
mdefine_line|#define IP27_SYMMON_STK_COUNT&t;&t;2
multiline_comment|/* IP27_SYMMON_STK_STRIDE must be &gt;= SYMMON_STACK_SIZE */
DECL|macro|IP27_SYMMON_STK_STRIDE
mdefine_line|#define IP27_SYMMON_STK_STRIDE&t;&t;0x7000
DECL|macro|IP27_FREEMEM_OFFSET
mdefine_line|#define IP27_FREEMEM_OFFSET&t;&t;0x19000
DECL|macro|IP27_FREEMEM_SIZE
mdefine_line|#define IP27_FREEMEM_SIZE&t;&t;-1
DECL|macro|IP27_FREEMEM_COUNT
mdefine_line|#define IP27_FREEMEM_COUNT&t;&t;1
DECL|macro|IP27_FREEMEM_STRIDE
mdefine_line|#define IP27_FREEMEM_STRIDE&t;&t;0
macro_line|#endif /* PROM || SABLE*/
multiline_comment|/*&n; * There will be only one of these in a partition so the IO6 must set it up.&n; */
DECL|macro|IO6_GDA_OFFSET
mdefine_line|#define IO6_GDA_OFFSET&t;&t;&t;0x11000
DECL|macro|IO6_GDA_SIZE
mdefine_line|#define IO6_GDA_SIZE&t;&t;&t;0x400
DECL|macro|IO6_GDA_COUNT
mdefine_line|#define IO6_GDA_COUNT&t;&t;&t;1
DECL|macro|IO6_GDA_STRIDE
mdefine_line|#define IO6_GDA_STRIDE&t;&t;&t;0
multiline_comment|/*&n; * save area of kernel nmi regs in the prom format&n; */
DECL|macro|IP27_NMI_KREGS_OFFSET
mdefine_line|#define IP27_NMI_KREGS_OFFSET&t;&t;0x11400
DECL|macro|IP27_NMI_KREGS_CPU_SIZE
mdefine_line|#define IP27_NMI_KREGS_CPU_SIZE&t;&t;0x200
multiline_comment|/*&n; * save area of kernel nmi regs in eframe format &n; */
DECL|macro|IP27_NMI_EFRAME_OFFSET
mdefine_line|#define IP27_NMI_EFRAME_OFFSET&t;&t;0x11800
DECL|macro|IP27_NMI_EFRAME_SIZE
mdefine_line|#define IP27_NMI_EFRAME_SIZE&t;&t;0x200
DECL|macro|KLDIR_ENT_SIZE
mdefine_line|#define KLDIR_ENT_SIZE&t;&t;&t;0x40
DECL|macro|KLDIR_MAX_ENTRIES
mdefine_line|#define KLDIR_MAX_ENTRIES&t;&t;(0x400 / 0x40)
macro_line|#endif&t;/* !CONFIG_SGI_IO */
macro_line|#ifdef _LANGUAGE_C
DECL|struct|kldir_ent_s
r_typedef
r_struct
id|kldir_ent_s
(brace
DECL|member|magic
id|u64
id|magic
suffix:semicolon
multiline_comment|/* Indicates validity of entry      */
DECL|member|offset
id|off_t
id|offset
suffix:semicolon
multiline_comment|/* Offset from start of node space  */
macro_line|#if defined(CONFIG_SGI_IO)&t;/* FIXME */
DECL|member|pointer
id|__psunsigned_t
id|pointer
suffix:semicolon
multiline_comment|/* Pointer to area in some cases    */
macro_line|#else
DECL|member|pointer
r_int
r_int
id|pointer
suffix:semicolon
multiline_comment|/* Pointer to area in some cases    */
macro_line|#endif
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* Size in bytes &t;&t;    */
DECL|member|count
id|u64
id|count
suffix:semicolon
multiline_comment|/* Repeat count if array, 1 if not  */
DECL|member|stride
r_int
id|stride
suffix:semicolon
multiline_comment|/* Stride if array, 0 if not        */
DECL|member|rsvd
r_char
id|rsvd
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Pad entry to 0x40 bytes          */
multiline_comment|/* NOTE: These 16 bytes are used in the Partition KLDIR&n;&t;   entry to store partition info. Refer to klpart.h for this. */
DECL|typedef|kldir_ent_t
)brace
id|kldir_ent_t
suffix:semicolon
macro_line|#endif /* _LANGUAGE_C */
macro_line|#if defined(CONFIG_SGI_IO)
DECL|macro|KLDIR_ENT_SIZE
mdefine_line|#define KLDIR_ENT_SIZE&t;&t;&t;0x40
DECL|macro|KLDIR_MAX_ENTRIES
mdefine_line|#define KLDIR_MAX_ENTRIES&t;&t;(0x400 / 0x40)
multiline_comment|/*&n; * The actual offsets of each memory area are machine-dependent&n; */
macro_line|#ifdef CONFIG_SGI_IP27
singleline_comment|// Not yet #include &lt;asm/sn/sn0/kldir.h&gt;
macro_line|#elif defined(CONFIG_SGI_IP35)
macro_line|#include &lt;asm/sn/sn1/kldir.h&gt;
macro_line|#else
macro_line|#error &quot;kldir.h is currently defined for IP27 and IP35 platforms only&quot;
macro_line|#endif
macro_line|#endif&t;/* CONFIG_SGI_IO */
macro_line|#endif /* _ASM_SN_KLDIR_H */
eof

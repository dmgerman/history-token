multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Derived from IRIX &lt;sys/SN/SN0/addrs.h&gt;, revision 1.126.&n; *&n; * Copyright (C) 1992 - 1997, 1999 Silicon Graphics, Inc.&n; * Copyright (C) 1999 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_SN_SN0_ADDRS_H
DECL|macro|_ASM_SN_SN0_ADDRS_H
mdefine_line|#define _ASM_SN_SN0_ADDRS_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * SN0 (on a T5) Address map&n; *&n; * This file contains a set of definitions and macros which are used&n; * to reference into the major address spaces (CAC, HSPEC, IO, MSPEC,&n; * and UNCAC) used by the SN0 architecture.  It also contains addresses&n; * for &quot;major&quot; statically locatable PROM/Kernel data structures, such as&n; * the partition table, the configuration data structure, etc.&n; * We make an implicit assumption that the processor using this file&n; * follows the R10K&squot;s provisions for specifying uncached attributes;&n; * should this change, the base registers may very well become processor-&n; * dependent.&n; *&n; * For more information on the address spaces, see the &quot;Local Resources&quot;&n; * chapter of the Hub specification.&n; *&n; * NOTE: This header file is included both by C and by assembler source&n; *&t; files.  Please bracket any language-dependent definitions&n; *&t; appropriately.&n; */
multiline_comment|/*&n; * Some of the macros here need to be casted to appropriate types when used&n; * from C.  They definitely must not be casted from assembly language so we&n; * use some new ANSI preprocessor stuff to paste these on where needed.&n; */
DECL|macro|CAC_BASE
mdefine_line|#define CAC_BASE&t;&t;0xa800000000000000
DECL|macro|HSPEC_BASE
mdefine_line|#define HSPEC_BASE&t;&t;0x9000000000000000
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE&t;&t;&t;0x9200000000000000
DECL|macro|MSPEC_BASE
mdefine_line|#define MSPEC_BASE&t;&t;0x9400000000000000
DECL|macro|UNCAC_BASE
mdefine_line|#define UNCAC_BASE&t;&t;0x9600000000000000
DECL|macro|TO_PHYS
mdefine_line|#define TO_PHYS(x)&t;&t;(&t;      ((x) &amp; TO_PHYS_MASK))
DECL|macro|TO_CAC
mdefine_line|#define TO_CAC(x)&t;&t;(CAC_BASE   | ((x) &amp; TO_PHYS_MASK))
DECL|macro|TO_UNCAC
mdefine_line|#define TO_UNCAC(x)&t;&t;(UNCAC_BASE | ((x) &amp; TO_PHYS_MASK))
DECL|macro|TO_MSPEC
mdefine_line|#define TO_MSPEC(x)&t;&t;(MSPEC_BASE | ((x) &amp; TO_PHYS_MASK))
DECL|macro|TO_HSPEC
mdefine_line|#define TO_HSPEC(x)&t;&t;(HSPEC_BASE | ((x) &amp; TO_PHYS_MASK))
multiline_comment|/*&n; * The following couple of definitions will eventually need to be variables,&n; * since the amount of address space assigned to each node depends on&n; * whether the system is running in N-mode (more nodes with less memory)&n; * or M-mode (fewer nodes with more memory).  We expect that it will&n; * be a while before we need to make this decision dynamically, though,&n; * so for now we just use defines bracketed by an ifdef.&n; */
macro_line|#ifdef CONFIG_SGI_SN0_N_MODE
DECL|macro|NODE_SIZE_BITS
mdefine_line|#define NODE_SIZE_BITS&t;&t;31
DECL|macro|BWIN_SIZE_BITS
mdefine_line|#define BWIN_SIZE_BITS&t;&t;28
DECL|macro|NASID_BITS
mdefine_line|#define NASID_BITS&t;&t;9
DECL|macro|NASID_BITMASK
mdefine_line|#define NASID_BITMASK&t;&t;(0x1ffLL)
DECL|macro|NASID_SHFT
mdefine_line|#define NASID_SHFT&t;&t;31
DECL|macro|NASID_META_BITS
mdefine_line|#define NASID_META_BITS&t;&t;5
DECL|macro|NASID_LOCAL_BITS
mdefine_line|#define NASID_LOCAL_BITS&t;4
DECL|macro|BDDIR_UPPER_MASK
mdefine_line|#define BDDIR_UPPER_MASK&t;(UINT64_CAST 0x7ffff &lt;&lt; 10)
DECL|macro|BDECC_UPPER_MASK
mdefine_line|#define BDECC_UPPER_MASK&t;(UINT64_CAST 0x3ffffff &lt;&lt; 3)
macro_line|#else /* !defined(CONFIG_SGI_SN0_N_MODE), assume that M-mode is desired */
DECL|macro|NODE_SIZE_BITS
mdefine_line|#define NODE_SIZE_BITS&t;&t;32
DECL|macro|BWIN_SIZE_BITS
mdefine_line|#define BWIN_SIZE_BITS&t;&t;29
DECL|macro|NASID_BITMASK
mdefine_line|#define NASID_BITMASK&t;&t;(0xffLL)
DECL|macro|NASID_BITS
mdefine_line|#define NASID_BITS&t;&t;8
DECL|macro|NASID_SHFT
mdefine_line|#define NASID_SHFT&t;&t;32
DECL|macro|NASID_META_BITS
mdefine_line|#define NASID_META_BITS&t;&t;4
DECL|macro|NASID_LOCAL_BITS
mdefine_line|#define NASID_LOCAL_BITS&t;4
DECL|macro|BDDIR_UPPER_MASK
mdefine_line|#define BDDIR_UPPER_MASK&t;(UINT64_CAST 0xfffff &lt;&lt; 10)
DECL|macro|BDECC_UPPER_MASK
mdefine_line|#define BDECC_UPPER_MASK&t;(UINT64_CAST 0x7ffffff &lt;&lt; 3)
macro_line|#endif /* !defined(CONFIG_SGI_SN0_N_MODE) */
DECL|macro|NODE_ADDRSPACE_SIZE
mdefine_line|#define NODE_ADDRSPACE_SIZE&t;(UINT64_CAST 1 &lt;&lt; NODE_SIZE_BITS)
DECL|macro|NASID_MASK
mdefine_line|#define NASID_MASK&t;&t;(UINT64_CAST NASID_BITMASK &lt;&lt; NASID_SHFT)
DECL|macro|NASID_GET
mdefine_line|#define NASID_GET(_pa)&t;&t;(int) ((UINT64_CAST (_pa) &gt;&gt;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;NASID_SHFT) &amp; NASID_BITMASK)
macro_line|#if _LANGUAGE_C &amp;&amp; !defined(_STANDALONE)
DECL|macro|NODE_SWIN_BASE
mdefine_line|#define NODE_SWIN_BASE(nasid, widget)&t;&t;&t;&t;&t;&bslash;&n;&t;((widget == 0) ? NODE_BWIN_BASE((nasid), SWIN0_BIGWIN)&t;&t;&bslash;&n;&t;: RAW_NODE_SWIN_BASE(nasid, widget))
macro_line|#else
DECL|macro|NODE_SWIN_BASE
mdefine_line|#define NODE_SWIN_BASE(nasid, widget) &bslash;&n;     (NODE_IO_BASE(nasid) + (UINT64_CAST (widget) &lt;&lt; SWIN_SIZE_BITS))
macro_line|#endif /* _LANGUAGE_C */
multiline_comment|/*&n; * The following definitions pertain to the IO special address&n; * space.  They define the location of the big and little windows&n; * of any given node.&n; */
DECL|macro|BWIN_INDEX_BITS
mdefine_line|#define BWIN_INDEX_BITS&t;&t;3
DECL|macro|BWIN_SIZE
mdefine_line|#define BWIN_SIZE&t;&t;(UINT64_CAST 1 &lt;&lt; BWIN_SIZE_BITS)
DECL|macro|BWIN_SIZEMASK
mdefine_line|#define&t;BWIN_SIZEMASK&t;&t;(BWIN_SIZE - 1)
DECL|macro|BWIN_WIDGET_MASK
mdefine_line|#define&t;BWIN_WIDGET_MASK&t;0x7
DECL|macro|NODE_BWIN_BASE0
mdefine_line|#define NODE_BWIN_BASE0(nasid)&t;(NODE_IO_BASE(nasid) + BWIN_SIZE)
DECL|macro|NODE_BWIN_BASE
mdefine_line|#define NODE_BWIN_BASE(nasid, bigwin)&t;(NODE_BWIN_BASE0(nasid) + &t;&bslash;&n;&t;&t;&t;(UINT64_CAST (bigwin) &lt;&lt; BWIN_SIZE_BITS))
DECL|macro|BWIN_WIDGETADDR
mdefine_line|#define&t;BWIN_WIDGETADDR(addr)&t;((addr) &amp; BWIN_SIZEMASK)
DECL|macro|BWIN_WINDOWNUM
mdefine_line|#define&t;BWIN_WINDOWNUM(addr)&t;(((addr) &gt;&gt; BWIN_SIZE_BITS) &amp; BWIN_WIDGET_MASK)
multiline_comment|/*&n; * Verify if addr belongs to large window address of node with &quot;nasid&quot;&n; *&n; *&n; * NOTE: &quot;addr&quot; is expected to be XKPHYS address, and NOT physical&n; * address&n; *&n; *&n; */
DECL|macro|NODE_BWIN_ADDR
mdefine_line|#define&t;NODE_BWIN_ADDR(nasid, addr)&t;&bslash;&n;&t;&t;(((addr) &gt;= NODE_BWIN_BASE0(nasid)) &amp;&amp; &bslash;&n;&t;&t; ((addr) &lt; (NODE_BWIN_BASE(nasid, HUB_NUM_BIG_WINDOW) + &bslash;&n;&t;&t;&t;&t;BWIN_SIZE)))
multiline_comment|/*&n; * The following define the major position-independent aliases used&n; * in SN0.&n; *&t;CALIAS -- Varies in size, points to the first n bytes of memory&n; *&t;&t;  &t;on the reader&squot;s node.&n; */
DECL|macro|CALIAS_BASE
mdefine_line|#define CALIAS_BASE&t;&t;CAC_BASE
DECL|macro|BRIDGE_REG_PTR
mdefine_line|#define BRIDGE_REG_PTR(_base, _off)&t;((volatile bridgereg_t *) &bslash;&n;&t;((__psunsigned_t)(_base) + (__psunsigned_t)(_off)))
DECL|macro|SN0_WIDGET_BASE
mdefine_line|#define SN0_WIDGET_BASE(_nasid, _wid)&t;(NODE_SWIN_BASE((_nasid), (_wid)))
multiline_comment|/* Turn on sable logging for the processors whose bits are set. */
macro_line|#ifdef SABLE
DECL|macro|SABLE_LOG_TRIGGER
mdefine_line|#define SABLE_LOG_TRIGGER(_map)&t;&bslash;&n;&t;&t;*((volatile hubreg_t *)(IO_BASE + 0x17ffff0)) = (_map)
macro_line|#else
DECL|macro|SABLE_LOG_TRIGGER
mdefine_line|#define SABLE_LOG_TRIGGER(_map)
macro_line|#endif /* SABLE */
macro_line|#if _LANGUAGE_C
DECL|macro|KERN_NMI_ADDR
mdefine_line|#define KERN_NMI_ADDR(nasid, slice)&t;&t;&t;&t;&t;&bslash;&n;                    TO_NODE_UNCAC((nasid), IP27_NMI_KREGS_OFFSET + &t;&bslash;&n;&t;&t;&t;&t;  (IP27_NMI_KREGS_CPU_SIZE * (slice)))
macro_line|#endif /* _LANGUAGE_C */
macro_line|#ifdef PROM
DECL|macro|MISC_PROM_BASE
mdefine_line|#define MISC_PROM_BASE&t;&t;PHYS_TO_K0(0x01300000)
DECL|macro|MISC_PROM_SIZE
mdefine_line|#define MISC_PROM_SIZE&t;&t;0x200000
DECL|macro|DIAG_BASE
mdefine_line|#define DIAG_BASE&t;&t;PHYS_TO_K0(0x01500000)
DECL|macro|DIAG_SIZE
mdefine_line|#define DIAG_SIZE&t;&t;0x300000
DECL|macro|ROUTE_BASE
mdefine_line|#define ROUTE_BASE&t;&t;PHYS_TO_K0(0x01800000)
DECL|macro|ROUTE_SIZE
mdefine_line|#define ROUTE_SIZE&t;&t;0x200000
DECL|macro|IP27PROM_FLASH_HDR
mdefine_line|#define IP27PROM_FLASH_HDR&t;PHYS_TO_K0(0x01300000)
DECL|macro|IP27PROM_FLASH_DATA
mdefine_line|#define IP27PROM_FLASH_DATA&t;PHYS_TO_K0(0x01301000)
DECL|macro|IP27PROM_CORP_MAX
mdefine_line|#define IP27PROM_CORP_MAX&t;32
DECL|macro|IP27PROM_CORP
mdefine_line|#define IP27PROM_CORP&t;&t;PHYS_TO_K0(0x01800000)
DECL|macro|IP27PROM_CORP_SIZE
mdefine_line|#define IP27PROM_CORP_SIZE&t;0x10000
DECL|macro|IP27PROM_CORP_STK
mdefine_line|#define IP27PROM_CORP_STK&t;PHYS_TO_K0(0x01810000)
DECL|macro|IP27PROM_CORP_STKSIZE
mdefine_line|#define IP27PROM_CORP_STKSIZE&t;0x2000
DECL|macro|IP27PROM_DECOMP_BUF
mdefine_line|#define IP27PROM_DECOMP_BUF&t;PHYS_TO_K0(0x01900000)
DECL|macro|IP27PROM_DECOMP_SIZE
mdefine_line|#define IP27PROM_DECOMP_SIZE&t;0xfff00
DECL|macro|IP27PROM_BASE
mdefine_line|#define IP27PROM_BASE&t;&t;PHYS_TO_K0(0x01a00000)
DECL|macro|IP27PROM_BASE_MAPPED
mdefine_line|#define IP27PROM_BASE_MAPPED&t;(K2BASE | 0x1fc00000)
DECL|macro|IP27PROM_SIZE_MAX
mdefine_line|#define IP27PROM_SIZE_MAX&t;0x100000
DECL|macro|IP27PROM_PCFG
mdefine_line|#define IP27PROM_PCFG&t;&t;PHYS_TO_K0(0x01b00000)
DECL|macro|IP27PROM_PCFG_SIZE
mdefine_line|#define IP27PROM_PCFG_SIZE&t;0xd0000
DECL|macro|IP27PROM_ERRDMP
mdefine_line|#define IP27PROM_ERRDMP&t;&t;PHYS_TO_K1(0x01bd0000)
DECL|macro|IP27PROM_ERRDMP_SIZE
mdefine_line|#define IP27PROM_ERRDMP_SIZE&t;0xf000
DECL|macro|IP27PROM_INIT_START
mdefine_line|#define IP27PROM_INIT_START&t;PHYS_TO_K1(0x01bd0000)
DECL|macro|IP27PROM_CONSOLE
mdefine_line|#define IP27PROM_CONSOLE&t;PHYS_TO_K1(0x01bdf000)
DECL|macro|IP27PROM_CONSOLE_SIZE
mdefine_line|#define IP27PROM_CONSOLE_SIZE&t;0x200
DECL|macro|IP27PROM_NETUART
mdefine_line|#define IP27PROM_NETUART&t;PHYS_TO_K1(0x01bdf200)
DECL|macro|IP27PROM_NETUART_SIZE
mdefine_line|#define IP27PROM_NETUART_SIZE&t;0x100
DECL|macro|IP27PROM_UNUSED1
mdefine_line|#define IP27PROM_UNUSED1&t;PHYS_TO_K1(0x01bdf300)
DECL|macro|IP27PROM_UNUSED1_SIZE
mdefine_line|#define IP27PROM_UNUSED1_SIZE&t;0x500
DECL|macro|IP27PROM_ELSC_BASE_A
mdefine_line|#define IP27PROM_ELSC_BASE_A&t;PHYS_TO_K0(0x01bdf800)
DECL|macro|IP27PROM_ELSC_BASE_B
mdefine_line|#define IP27PROM_ELSC_BASE_B&t;PHYS_TO_K0(0x01bdfc00)
DECL|macro|IP27PROM_STACK_A
mdefine_line|#define IP27PROM_STACK_A&t;PHYS_TO_K0(0x01be0000)
DECL|macro|IP27PROM_STACK_B
mdefine_line|#define IP27PROM_STACK_B&t;PHYS_TO_K0(0x01bf0000)
DECL|macro|IP27PROM_STACK_SHFT
mdefine_line|#define IP27PROM_STACK_SHFT&t;16
DECL|macro|IP27PROM_STACK_SIZE
mdefine_line|#define IP27PROM_STACK_SIZE&t;(1 &lt;&lt; IP27PROM_STACK_SHFT)
DECL|macro|IP27PROM_INIT_END
mdefine_line|#define IP27PROM_INIT_END&t;PHYS_TO_K0(0x01c00000)
DECL|macro|SLAVESTACK_BASE
mdefine_line|#define SLAVESTACK_BASE&t;&t;PHYS_TO_K0(0x01580000)
DECL|macro|SLAVESTACK_SIZE
mdefine_line|#define SLAVESTACK_SIZE&t;&t;0x40000
DECL|macro|ENETBUFS_BASE
mdefine_line|#define ENETBUFS_BASE&t;&t;PHYS_TO_K0(0x01f80000)
DECL|macro|ENETBUFS_SIZE
mdefine_line|#define ENETBUFS_SIZE&t;&t;0x20000
DECL|macro|IO6PROM_BASE
mdefine_line|#define IO6PROM_BASE&t;&t;PHYS_TO_K0(0x01c00000)
DECL|macro|IO6PROM_SIZE
mdefine_line|#define IO6PROM_SIZE&t;&t;0x400000
DECL|macro|IO6PROM_BASE_MAPPED
mdefine_line|#define&t;IO6PROM_BASE_MAPPED&t;(K2BASE | 0x11c00000)
DECL|macro|IO6DPROM_BASE
mdefine_line|#define IO6DPROM_BASE&t;&t;PHYS_TO_K0(0x01c00000)
DECL|macro|IO6DPROM_SIZE
mdefine_line|#define IO6DPROM_SIZE&t;&t;0x200000
DECL|macro|NODEBUGUNIX_ADDR
mdefine_line|#define NODEBUGUNIX_ADDR&t;PHYS_TO_K0(0x00019000)
DECL|macro|DEBUGUNIX_ADDR
mdefine_line|#define DEBUGUNIX_ADDR&t;&t;PHYS_TO_K0(0x00100000)
DECL|macro|IP27PROM_INT_LAUNCH
mdefine_line|#define IP27PROM_INT_LAUNCH&t;10&t;/* and 11 */
DECL|macro|IP27PROM_INT_NETUART
mdefine_line|#define IP27PROM_INT_NETUART&t;12&t;/* through 17 */
macro_line|#endif /* PROM */
multiline_comment|/*&n; * needed by symmon so it needs to be outside #if PROM&n; */
DECL|macro|IP27PROM_ELSC_SHFT
mdefine_line|#define IP27PROM_ELSC_SHFT&t;10
DECL|macro|IP27PROM_ELSC_SIZE
mdefine_line|#define IP27PROM_ELSC_SIZE&t;(1 &lt;&lt; IP27PROM_ELSC_SHFT)
multiline_comment|/*&n; * This address is used by IO6PROM to build MemoryDescriptors of&n; * free memory. This address is important since unix gets loaded&n; * at this address, and this memory has to be FREE if unix is to&n; * be loaded.&n; */
DECL|macro|FREEMEM_BASE
mdefine_line|#define FREEMEM_BASE&t;&t;PHYS_TO_K0(0x2000000)
DECL|macro|IO6PROM_STACK_SHFT
mdefine_line|#define IO6PROM_STACK_SHFT&t;14&t;/* stack per cpu */
DECL|macro|IO6PROM_STACK_SIZE
mdefine_line|#define IO6PROM_STACK_SIZE&t;(1 &lt;&lt; IO6PROM_STACK_SHFT)
multiline_comment|/*&n; * IP27 PROM vectors&n; */
DECL|macro|IP27PROM_ENTRY
mdefine_line|#define IP27PROM_ENTRY&t;&t;PHYS_TO_COMPATK1(0x1fc00000)
DECL|macro|IP27PROM_RESTART
mdefine_line|#define IP27PROM_RESTART&t;PHYS_TO_COMPATK1(0x1fc00008)
DECL|macro|IP27PROM_SLAVELOOP
mdefine_line|#define IP27PROM_SLAVELOOP&t;PHYS_TO_COMPATK1(0x1fc00010)
DECL|macro|IP27PROM_PODMODE
mdefine_line|#define IP27PROM_PODMODE&t;PHYS_TO_COMPATK1(0x1fc00018)
DECL|macro|IP27PROM_IOC3UARTPOD
mdefine_line|#define IP27PROM_IOC3UARTPOD&t;PHYS_TO_COMPATK1(0x1fc00020)
DECL|macro|IP27PROM_FLASHLEDS
mdefine_line|#define IP27PROM_FLASHLEDS&t;PHYS_TO_COMPATK1(0x1fc00028)
DECL|macro|IP27PROM_REPOD
mdefine_line|#define IP27PROM_REPOD&t;&t;PHYS_TO_COMPATK1(0x1fc00030)
DECL|macro|IP27PROM_LAUNCHSLAVE
mdefine_line|#define IP27PROM_LAUNCHSLAVE&t;PHYS_TO_COMPATK1(0x1fc00038)
DECL|macro|IP27PROM_WAITSLAVE
mdefine_line|#define IP27PROM_WAITSLAVE&t;PHYS_TO_COMPATK1(0x1fc00040)
DECL|macro|IP27PROM_POLLSLAVE
mdefine_line|#define IP27PROM_POLLSLAVE&t;PHYS_TO_COMPATK1(0x1fc00048)
DECL|macro|KL_UART_BASE
mdefine_line|#define KL_UART_BASE&t;LOCAL_HUB_ADDR(MD_UREG0_0)&t;/* base of UART regs */
DECL|macro|KL_UART_CMD
mdefine_line|#define KL_UART_CMD&t;LOCAL_HUB_ADDR(MD_UREG0_0)&t;/* UART command reg */
DECL|macro|KL_UART_DATA
mdefine_line|#define KL_UART_DATA&t;LOCAL_HUB_ADDR(MD_UREG0_1)&t;/* UART data reg */
DECL|macro|KL_I2C_REG
mdefine_line|#define KL_I2C_REG&t;MD_UREG0_0&t;&t;&t;/* I2C reg */
macro_line|#if !_LANGUAGE_ASSEMBLY
multiline_comment|/* Address 0x400 to 0x1000 ualias points to cache error eframe + misc&n; * CACHE_ERR_SP_PTR could either contain an address to the stack, or&n; * the stack could start at CACHE_ERR_SP_PTR&n; */
macro_line|#if defined (HUB_ERR_STS_WAR)
DECL|macro|CACHE_ERR_EFRAME
mdefine_line|#define CACHE_ERR_EFRAME&t;0x480
macro_line|#else /* HUB_ERR_STS_WAR */
DECL|macro|CACHE_ERR_EFRAME
mdefine_line|#define CACHE_ERR_EFRAME&t;0x400
macro_line|#endif /* HUB_ERR_STS_WAR */
DECL|macro|CACHE_ERR_ECCFRAME
mdefine_line|#define CACHE_ERR_ECCFRAME&t;(CACHE_ERR_EFRAME + EF_SIZE)
DECL|macro|CACHE_ERR_SP_PTR
mdefine_line|#define CACHE_ERR_SP_PTR&t;(0x1000 - 32)&t;/* why -32? TBD */
DECL|macro|CACHE_ERR_IBASE_PTR
mdefine_line|#define CACHE_ERR_IBASE_PTR&t;(0x1000 - 40)
DECL|macro|CACHE_ERR_SP
mdefine_line|#define CACHE_ERR_SP&t;&t;(CACHE_ERR_SP_PTR - 16)
DECL|macro|CACHE_ERR_AREA_SIZE
mdefine_line|#define CACHE_ERR_AREA_SIZE&t;(ARCS_SPB_OFFSET - CACHE_ERR_EFRAME)
macro_line|#endif&t;/* !_LANGUAGE_ASSEMBLY */
DECL|macro|_ARCSPROM
mdefine_line|#define _ARCSPROM
macro_line|#ifdef _STANDALONE
multiline_comment|/*&n; * The PROM needs to pass the device base address and the&n; * device pci cfg space address to the device drivers during&n; * install. The COMPONENT-&gt;Key field is used for this purpose.&n; * Macros needed by SN0 device drivers to convert the&n; * COMPONENT-&gt;Key field to the respective base address.&n; * Key field looks as follows:&n; *&n; *  +----------------------------------------------------+&n; *  |devnasid | widget  |pciid |hubwidid|hstnasid | adap |&n; *  |   2     |   1     |  1   |   1    |    2    |   1  |&n; *  +----------------------------------------------------+&n; *  |         |         |      |        |         |      |&n; *  64        48        40     32       24        8      0&n; *&n; * These are used by standalone drivers till the io infrastructure&n; * is in place.&n; */
macro_line|#if _LANGUAGE_C
DECL|macro|uchar
mdefine_line|#define uchar unsigned char
DECL|macro|KEY_DEVNASID_SHFT
mdefine_line|#define KEY_DEVNASID_SHFT  48
DECL|macro|KEY_WIDID_SHFT
mdefine_line|#define KEY_WIDID_SHFT&t;   40
DECL|macro|KEY_PCIID_SHFT
mdefine_line|#define KEY_PCIID_SHFT&t;   32
DECL|macro|KEY_HUBWID_SHFT
mdefine_line|#define KEY_HUBWID_SHFT&t;   24
DECL|macro|KEY_HSTNASID_SHFT
mdefine_line|#define KEY_HSTNASID_SHFT  8
DECL|macro|MK_SN0_KEY
mdefine_line|#define MK_SN0_KEY(nasid, widid, pciid) &bslash;&n;&t;&t;&t;((((__psunsigned_t)nasid)&lt;&lt; KEY_DEVNASID_SHFT |&bslash;&n;&t;&t;&t;&t;((__psunsigned_t)widid) &lt;&lt; KEY_WIDID_SHFT) |&bslash;&n;&t;&t;&t;&t;((__psunsigned_t)pciid) &lt;&lt; KEY_PCIID_SHFT)
DECL|macro|ADD_HUBWID_KEY
mdefine_line|#define ADD_HUBWID_KEY(key,hubwid)&bslash;&n;&t;&t;&t;(key|=((__psunsigned_t)hubwid &lt;&lt; KEY_HUBWID_SHFT))
DECL|macro|ADD_HSTNASID_KEY
mdefine_line|#define ADD_HSTNASID_KEY(key,hstnasid)&bslash;&n;&t;&t;&t;(key|=((__psunsigned_t)hstnasid &lt;&lt; KEY_HSTNASID_SHFT))
DECL|macro|GET_DEVNASID_FROM_KEY
mdefine_line|#define GET_DEVNASID_FROM_KEY(key)&t;((short)(key &gt;&gt; KEY_DEVNASID_SHFT))
DECL|macro|GET_WIDID_FROM_KEY
mdefine_line|#define GET_WIDID_FROM_KEY(key)&t;&t;((uchar)(key &gt;&gt; KEY_WIDID_SHFT))
DECL|macro|GET_PCIID_FROM_KEY
mdefine_line|#define GET_PCIID_FROM_KEY(key)&t;&t;((uchar)(key &gt;&gt; KEY_PCIID_SHFT))
DECL|macro|GET_HUBWID_FROM_KEY
mdefine_line|#define GET_HUBWID_FROM_KEY(key)&t;((uchar)(key &gt;&gt; KEY_HUBWID_SHFT))
DECL|macro|GET_HSTNASID_FROM_KEY
mdefine_line|#define GET_HSTNASID_FROM_KEY(key)&t;((short)(key &gt;&gt; KEY_HSTNASID_SHFT))
DECL|macro|PCI_64_TARGID_SHFT
mdefine_line|#define PCI_64_TARGID_SHFT&t;&t;60
DECL|macro|GET_PCIBASE_FROM_KEY
mdefine_line|#define GET_PCIBASE_FROM_KEY(key)  (NODE_SWIN_BASE(GET_DEVNASID_FROM_KEY(key),&bslash;&n;&t;&t;&t;&t;&t;GET_WIDID_FROM_KEY(key))&bslash;&n;&t;&t;&t;&t;&t;| BRIDGE_DEVIO(GET_PCIID_FROM_KEY(key)))
DECL|macro|GET_PCICFGBASE_FROM_KEY
mdefine_line|#define GET_PCICFGBASE_FROM_KEY(key) &bslash;&n;&t;&t;&t;(NODE_SWIN_BASE(GET_DEVNASID_FROM_KEY(key),&bslash;&n;&t;&t;&t;      GET_WIDID_FROM_KEY(key))&bslash;&n;&t;&t;&t;| BRIDGE_TYPE0_CFG_DEV(GET_PCIID_FROM_KEY(key)))
DECL|macro|GET_WIDBASE_FROM_KEY
mdefine_line|#define GET_WIDBASE_FROM_KEY(key) &bslash;&n;                        (NODE_SWIN_BASE(GET_DEVNASID_FROM_KEY(key),&bslash;&n;                              GET_WIDID_FROM_KEY(key)))
DECL|macro|PUT_INSTALL_STATUS
mdefine_line|#define PUT_INSTALL_STATUS(c,s)&t;&t;c-&gt;Revision = s
DECL|macro|GET_INSTALL_STATUS
mdefine_line|#define GET_INSTALL_STATUS(c)&t;&t;c-&gt;Revision
macro_line|#endif /* LANGUAGE_C */
macro_line|#endif /* _STANDALONE */
macro_line|#if defined (HUB_ERR_STS_WAR)
DECL|macro|ERR_STS_WAR_REGISTER
mdefine_line|#define ERR_STS_WAR_REGISTER&t;IIO_IIBUSERR
DECL|macro|ERR_STS_WAR_ADDR
mdefine_line|#define ERR_STS_WAR_ADDR&t;LOCAL_HUB_ADDR(IIO_IIBUSERR)
DECL|macro|ERR_STS_WAR_PHYSADDR
mdefine_line|#define ERR_STS_WAR_PHYSADDR&t;TO_PHYS((__psunsigned_t)ERR_STS_WAR_ADDR)
multiline_comment|/* Used to match addr in error reg. */
DECL|macro|OLD_ERR_STS_WAR_OFFSET
mdefine_line|#define OLD_ERR_STS_WAR_OFFSET&t;((MD_MEM_BANKS * MD_BANK_SIZE) - 0x100)
macro_line|#endif /* HUB_ERR_STS_WAR */
macro_line|#endif /* _ASM_SN_SN0_ADDRS_H */
eof

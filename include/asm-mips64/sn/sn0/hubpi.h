multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Derived from IRIX &lt;sys/SN/SN0/hubpi.h&gt;, revision 1.28.&n; *&n; * Copyright (C) 1992 - 1997, 1999 Silicon Graphics, Inc.&n; * Copyright (C) 1999 by Ralf Baechle&n; */
macro_line|#ifndef&t;_ASM_SN_SN0_HUBPI_H
DECL|macro|_ASM_SN_SN0_HUBPI_H
mdefine_line|#define&t;_ASM_SN_SN0_HUBPI_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * Hub I/O interface registers&n; *&n; * All registers in this file are subject to change until Hub chip tapeout.&n; * All register &quot;addresses&quot; are actually offsets.  Use the LOCAL_HUB&n; * or REMOTE_HUB macros to synthesize an actual address&n; */
DECL|macro|PI_BASE
mdefine_line|#define PI_BASE&t;&t;&t;0x000000
multiline_comment|/* General protection and control registers */
DECL|macro|PI_CPU_PROTECT
mdefine_line|#define PI_CPU_PROTECT&t;&t;0x000000 /* CPU Protection &t;&t;    */
DECL|macro|PI_PROT_OVERRD
mdefine_line|#define PI_PROT_OVERRD&t;&t;0x000008 /* Clear CPU Protection bit &t;    */
DECL|macro|PI_IO_PROTECT
mdefine_line|#define&t;PI_IO_PROTECT&t;&t;0x000010 /* Interrupt Pending Protection    */
DECL|macro|PI_REGION_PRESENT
mdefine_line|#define PI_REGION_PRESENT&t;0x000018 /* Indicates whether region exists */
DECL|macro|PI_CPU_NUM
mdefine_line|#define PI_CPU_NUM&t;&t;0x000020 /* CPU Number ID &t;&t;    */
DECL|macro|PI_CALIAS_SIZE
mdefine_line|#define PI_CALIAS_SIZE&t;&t;0x000028 /* Cached Alias Size &t;&t;    */
DECL|macro|PI_MAX_CRB_TIMEOUT
mdefine_line|#define PI_MAX_CRB_TIMEOUT&t;0x000030 /* Maximum Timeout for CRB &t;    */
DECL|macro|PI_CRB_SFACTOR
mdefine_line|#define PI_CRB_SFACTOR&t;&t;0x000038 /* Scale factor for CRB timeout    */
multiline_comment|/* CALIAS values */
DECL|macro|PI_CALIAS_SIZE_0
mdefine_line|#define PI_CALIAS_SIZE_0&t;0
DECL|macro|PI_CALIAS_SIZE_4K
mdefine_line|#define PI_CALIAS_SIZE_4K&t;1
DECL|macro|PI_CALIAS_SIZE_8K
mdefine_line|#define PI_CALIAS_SIZE_8K&t;2
DECL|macro|PI_CALIAS_SIZE_16K
mdefine_line|#define PI_CALIAS_SIZE_16K&t;3
DECL|macro|PI_CALIAS_SIZE_32K
mdefine_line|#define PI_CALIAS_SIZE_32K&t;4
DECL|macro|PI_CALIAS_SIZE_64K
mdefine_line|#define PI_CALIAS_SIZE_64K&t;5
DECL|macro|PI_CALIAS_SIZE_128K
mdefine_line|#define PI_CALIAS_SIZE_128K&t;6
DECL|macro|PI_CALIAS_SIZE_256K
mdefine_line|#define PI_CALIAS_SIZE_256K&t;7
DECL|macro|PI_CALIAS_SIZE_512K
mdefine_line|#define PI_CALIAS_SIZE_512K&t;8
DECL|macro|PI_CALIAS_SIZE_1M
mdefine_line|#define PI_CALIAS_SIZE_1M&t;9
DECL|macro|PI_CALIAS_SIZE_2M
mdefine_line|#define PI_CALIAS_SIZE_2M&t;10
DECL|macro|PI_CALIAS_SIZE_4M
mdefine_line|#define PI_CALIAS_SIZE_4M&t;11
DECL|macro|PI_CALIAS_SIZE_8M
mdefine_line|#define PI_CALIAS_SIZE_8M&t;12
DECL|macro|PI_CALIAS_SIZE_16M
mdefine_line|#define PI_CALIAS_SIZE_16M&t;13
DECL|macro|PI_CALIAS_SIZE_32M
mdefine_line|#define PI_CALIAS_SIZE_32M&t;14
DECL|macro|PI_CALIAS_SIZE_64M
mdefine_line|#define PI_CALIAS_SIZE_64M&t;15
multiline_comment|/* Processor control and status checking */
DECL|macro|PI_CPU_PRESENT_A
mdefine_line|#define PI_CPU_PRESENT_A&t;0x000040 /* CPU Present A &t;&t;    */
DECL|macro|PI_CPU_PRESENT_B
mdefine_line|#define PI_CPU_PRESENT_B&t;0x000048 /* CPU Present B &t;&t;    */
DECL|macro|PI_CPU_ENABLE_A
mdefine_line|#define PI_CPU_ENABLE_A&t;&t;0x000050 /* CPU Enable A &t;&t;    */
DECL|macro|PI_CPU_ENABLE_B
mdefine_line|#define PI_CPU_ENABLE_B&t;&t;0x000058 /* CPU Enable B &t;&t;    */
DECL|macro|PI_REPLY_LEVEL
mdefine_line|#define PI_REPLY_LEVEL&t;&t;0x000060 /* Reply Level&t;&t; &t;    */
DECL|macro|PI_HARDRESET_BIT
mdefine_line|#define PI_HARDRESET_BIT&t;0x020068 /* Bit cleared by s/w on SR&t;    */
DECL|macro|PI_NMI_A
mdefine_line|#define PI_NMI_A&t;&t;0x000070 /* NMI to CPU A &t;&t;    */
DECL|macro|PI_NMI_B
mdefine_line|#define PI_NMI_B&t;&t;0x000078 /* NMI to CPU B &t;&t;    */
DECL|macro|PI_NMI_OFFSET
mdefine_line|#define PI_NMI_OFFSET&t;&t;(PI_NMI_B - PI_NMI_A)
DECL|macro|PI_SOFTRESET
mdefine_line|#define PI_SOFTRESET&t;&t;0x000080 /* Softreset (to both CPUs) &t;    */
multiline_comment|/* Regular Interrupt register checking.  */
DECL|macro|PI_INT_PEND_MOD
mdefine_line|#define PI_INT_PEND_MOD&t;&t;0x000090 /* Write to set pending ints&t;    */
DECL|macro|PI_INT_PEND0
mdefine_line|#define PI_INT_PEND0&t;&t;0x000098 /* Read to get pending ints &t;    */
DECL|macro|PI_INT_PEND1
mdefine_line|#define PI_INT_PEND1&t;&t;0x0000a0 /* Read to get pending ints &t;    */
DECL|macro|PI_INT_MASK0_A
mdefine_line|#define PI_INT_MASK0_A&t;&t;0x0000a8 /* Interrupt Mask 0 for CPU A &t;    */
DECL|macro|PI_INT_MASK1_A
mdefine_line|#define PI_INT_MASK1_A&t;&t;0x0000b0 /* Interrupt Mask 1 for CPU A &t;    */
DECL|macro|PI_INT_MASK0_B
mdefine_line|#define PI_INT_MASK0_B&t;&t;0x0000b8 /* Interrupt Mask 0 for CPU B &t;    */
DECL|macro|PI_INT_MASK1_B
mdefine_line|#define PI_INT_MASK1_B&t;&t;0x0000c0 /* Interrupt Mask 1 for CPU B &t;    */
DECL|macro|PI_INT_MASK_OFFSET
mdefine_line|#define PI_INT_MASK_OFFSET&t;0x10&t; /* Offset from A to B &t;&t;    */
multiline_comment|/* Crosscall interrupts */
DECL|macro|PI_CC_PEND_SET_A
mdefine_line|#define PI_CC_PEND_SET_A&t;0x0000c8 /* CC Interrupt Pending Set, CPU A */
DECL|macro|PI_CC_PEND_SET_B
mdefine_line|#define PI_CC_PEND_SET_B&t;0x0000d0 /* CC Interrupt Pending Set, CPU B */
DECL|macro|PI_CC_PEND_CLR_A
mdefine_line|#define PI_CC_PEND_CLR_A&t;0x0000d8 /* CC Interrupt Pending Clr, CPU A */
DECL|macro|PI_CC_PEND_CLR_B
mdefine_line|#define PI_CC_PEND_CLR_B&t;0x0000e0 /* CC Interrupt Pending Clr, CPU B */
DECL|macro|PI_CC_MASK
mdefine_line|#define PI_CC_MASK&t;&t;0x0000e8 /* CC Interrupt mask &t;&t;    */
DECL|macro|PI_INT_SET_OFFSET
mdefine_line|#define PI_INT_SET_OFFSET&t;0x08&t; /* Offset from A to B &t;&t;    */
multiline_comment|/* Realtime Counter and Profiler control registers */
DECL|macro|PI_RT_COUNT
mdefine_line|#define PI_RT_COUNT&t;&t;0x030100 /* Real Time Counter &t;&t;    */
DECL|macro|PI_RT_COMPARE_A
mdefine_line|#define PI_RT_COMPARE_A&t;&t;0x000108 /* Real Time Compare A &t;    */
DECL|macro|PI_RT_COMPARE_B
mdefine_line|#define PI_RT_COMPARE_B&t;&t;0x000110 /* Real Time Compare B &t;    */
DECL|macro|PI_PROFILE_COMPARE
mdefine_line|#define PI_PROFILE_COMPARE&t;0x000118 /* L5 int to both cpus when == RTC */
DECL|macro|PI_RT_PEND_A
mdefine_line|#define PI_RT_PEND_A&t;&t;0x000120 /* Set if RT int for A pending     */
DECL|macro|PI_RT_PEND_B
mdefine_line|#define PI_RT_PEND_B&t;&t;0x000128 /* Set if RT int for B pending     */
DECL|macro|PI_PROF_PEND_A
mdefine_line|#define PI_PROF_PEND_A&t;&t;0x000130 /* Set if Prof int for A pending   */
DECL|macro|PI_PROF_PEND_B
mdefine_line|#define PI_PROF_PEND_B&t;&t;0x000138 /* Set if Prof int for B pending   */
DECL|macro|PI_RT_EN_A
mdefine_line|#define PI_RT_EN_A&t;&t;0x000140 /* RT int for CPU A enable &t;    */
DECL|macro|PI_RT_EN_B
mdefine_line|#define PI_RT_EN_B&t;&t;0x000148 /* RT int for CPU B enable &t;    */
DECL|macro|PI_PROF_EN_A
mdefine_line|#define PI_PROF_EN_A&t;&t;0x000150 /* PROF int for CPU A enable &t;    */
DECL|macro|PI_PROF_EN_B
mdefine_line|#define PI_PROF_EN_B&t;&t;0x000158 /* PROF int for CPU B enable &t;    */
DECL|macro|PI_RT_LOCAL_CTRL
mdefine_line|#define PI_RT_LOCAL_CTRL&t;0x000160 /* RT control register &t;    */
DECL|macro|PI_RT_FILTER_CTRL
mdefine_line|#define PI_RT_FILTER_CTRL&t;0x000168 /* GCLK Filter control register    */
DECL|macro|PI_COUNT_OFFSET
mdefine_line|#define PI_COUNT_OFFSET&t;&t;0x08&t; /* A to B offset for all counts    */
multiline_comment|/* Built-In Self Test support */
DECL|macro|PI_BIST_WRITE_DATA
mdefine_line|#define PI_BIST_WRITE_DATA&t;0x000200 /* BIST write data &t;&t;    */
DECL|macro|PI_BIST_READ_DATA
mdefine_line|#define PI_BIST_READ_DATA&t;0x000208 /* BIST read data &t;&t;    */
DECL|macro|PI_BIST_COUNT_TARG
mdefine_line|#define PI_BIST_COUNT_TARG&t;0x000210 /* BIST Count and Target &t;    */
DECL|macro|PI_BIST_READY
mdefine_line|#define PI_BIST_READY&t;&t;0x000218 /* BIST Ready indicator &t;    */
DECL|macro|PI_BIST_SHIFT_LOAD
mdefine_line|#define PI_BIST_SHIFT_LOAD&t;0x000220 /* BIST control &t;&t;    */
DECL|macro|PI_BIST_SHIFT_UNLOAD
mdefine_line|#define PI_BIST_SHIFT_UNLOAD&t;0x000228 /* BIST control &t;&t;    */
DECL|macro|PI_BIST_ENTER_RUN
mdefine_line|#define PI_BIST_ENTER_RUN&t;0x000230 /* BIST control &t;&t;    */
multiline_comment|/* Graphics control registers */
DECL|macro|PI_GFX_PAGE_A
mdefine_line|#define PI_GFX_PAGE_A&t;&t;0x000300 /* Graphics page A &t;&t;    */
DECL|macro|PI_GFX_CREDIT_CNTR_A
mdefine_line|#define PI_GFX_CREDIT_CNTR_A&t;0x000308 /* Graphics credit counter A &t;    */
DECL|macro|PI_GFX_BIAS_A
mdefine_line|#define PI_GFX_BIAS_A&t;&t;0x000310 /* Graphics bias A &t;&t;    */
DECL|macro|PI_GFX_INT_CNTR_A
mdefine_line|#define PI_GFX_INT_CNTR_A&t;0x000318 /* Graphics interrupt counter A    */
DECL|macro|PI_GFX_INT_CMP_A
mdefine_line|#define PI_GFX_INT_CMP_A&t;0x000320 /* Graphics interrupt comparator A */
DECL|macro|PI_GFX_PAGE_B
mdefine_line|#define PI_GFX_PAGE_B&t;&t;0x000328 /* Graphics page B &t;&t;    */
DECL|macro|PI_GFX_CREDIT_CNTR_B
mdefine_line|#define PI_GFX_CREDIT_CNTR_B&t;0x000330 /* Graphics credit counter B &t;    */
DECL|macro|PI_GFX_BIAS_B
mdefine_line|#define PI_GFX_BIAS_B&t;&t;0x000338 /* Graphics bias B &t;&t;    */
DECL|macro|PI_GFX_INT_CNTR_B
mdefine_line|#define PI_GFX_INT_CNTR_B&t;0x000340 /* Graphics interrupt counter B    */
DECL|macro|PI_GFX_INT_CMP_B
mdefine_line|#define PI_GFX_INT_CMP_B&t;0x000348 /* Graphics interrupt comparator B */
DECL|macro|PI_GFX_OFFSET
mdefine_line|#define PI_GFX_OFFSET&t;&t;(PI_GFX_PAGE_B - PI_GFX_PAGE_A)
DECL|macro|PI_GFX_PAGE_ENABLE
mdefine_line|#define PI_GFX_PAGE_ENABLE&t;0x0000010000000000LL
multiline_comment|/* Error and timeout registers */
DECL|macro|PI_ERR_INT_PEND
mdefine_line|#define PI_ERR_INT_PEND&t;&t;0x000400 /* Error Interrupt Pending&t;    */
DECL|macro|PI_ERR_INT_MASK_A
mdefine_line|#define PI_ERR_INT_MASK_A&t;0x000408 /* Error Interrupt mask for CPU A  */
DECL|macro|PI_ERR_INT_MASK_B
mdefine_line|#define PI_ERR_INT_MASK_B&t;0x000410 /* Error Interrupt mask for CPU B  */
DECL|macro|PI_ERR_STACK_ADDR_A
mdefine_line|#define PI_ERR_STACK_ADDR_A&t;0x000418 /* Error stack address for CPU A   */ 
DECL|macro|PI_ERR_STACK_ADDR_B
mdefine_line|#define PI_ERR_STACK_ADDR_B&t;0x000420 /* Error stack address for CPU B   */ 
DECL|macro|PI_ERR_STACK_SIZE
mdefine_line|#define PI_ERR_STACK_SIZE&t;0x000428 /* Error Stack Size &t;&t;    */
DECL|macro|PI_ERR_STATUS0_A
mdefine_line|#define PI_ERR_STATUS0_A&t;0x000430 /* Error Status 0A &t;&t;    */
DECL|macro|PI_ERR_STATUS0_A_RCLR
mdefine_line|#define PI_ERR_STATUS0_A_RCLR&t;0x000438 /* Error Status 0A clear on read   */
DECL|macro|PI_ERR_STATUS1_A
mdefine_line|#define PI_ERR_STATUS1_A&t;0x000440 /* Error Status 1A &t;&t;    */
DECL|macro|PI_ERR_STATUS1_A_RCLR
mdefine_line|#define PI_ERR_STATUS1_A_RCLR&t;0x000448 /* Error Status 1A clear on read   */
DECL|macro|PI_ERR_STATUS0_B
mdefine_line|#define PI_ERR_STATUS0_B&t;0x000450 /* Error Status 0B &t;&t;    */
DECL|macro|PI_ERR_STATUS0_B_RCLR
mdefine_line|#define PI_ERR_STATUS0_B_RCLR&t;0x000458 /* Error Status 0B clear on read   */
DECL|macro|PI_ERR_STATUS1_B
mdefine_line|#define PI_ERR_STATUS1_B&t;0x000460 /* Error Status 1B &t;&t;    */
DECL|macro|PI_ERR_STATUS1_B_RCLR
mdefine_line|#define PI_ERR_STATUS1_B_RCLR&t;0x000468 /* Error Status 1B clear on read   */
DECL|macro|PI_SPOOL_CMP_A
mdefine_line|#define PI_SPOOL_CMP_A&t;&t;0x000470 /* Spool compare for CPU A &t;    */
DECL|macro|PI_SPOOL_CMP_B
mdefine_line|#define PI_SPOOL_CMP_B&t;&t;0x000478 /* Spool compare for CPU B &t;    */
DECL|macro|PI_CRB_TIMEOUT_A
mdefine_line|#define PI_CRB_TIMEOUT_A&t;0x000480 /* Timed out CRB entries for A     */
DECL|macro|PI_CRB_TIMEOUT_B
mdefine_line|#define PI_CRB_TIMEOUT_B&t;0x000488 /* Timed out CRB entries for B     */
DECL|macro|PI_SYSAD_ERRCHK_EN
mdefine_line|#define PI_SYSAD_ERRCHK_EN&t;0x000490 /* Enables SYSAD error checking    */
DECL|macro|PI_BAD_CHECK_BIT_A
mdefine_line|#define PI_BAD_CHECK_BIT_A&t;0x000498 /* Force SYSAD check bit error     */
DECL|macro|PI_BAD_CHECK_BIT_B
mdefine_line|#define PI_BAD_CHECK_BIT_B&t;0x0004a0 /* Force SYSAD check bit error     */
DECL|macro|PI_NACK_CNT_A
mdefine_line|#define PI_NACK_CNT_A&t;&t;0x0004a8 /* Consecutive NACK counter &t;    */
DECL|macro|PI_NACK_CNT_B
mdefine_line|#define PI_NACK_CNT_B&t;&t;0x0004b0 /* &t;&quot;&t;&quot; for CPU B &t;    */
DECL|macro|PI_NACK_CMP
mdefine_line|#define PI_NACK_CMP&t;&t;0x0004b8 /* NACK count compare&t;&t;    */
DECL|macro|PI_STACKADDR_OFFSET
mdefine_line|#define PI_STACKADDR_OFFSET&t;(PI_ERR_STACK_ADDR_B - PI_ERR_STACK_ADDR_A)
DECL|macro|PI_ERRSTAT_OFFSET
mdefine_line|#define PI_ERRSTAT_OFFSET&t;(PI_ERR_STATUS0_B - PI_ERR_STATUS0_A)
DECL|macro|PI_RDCLR_OFFSET
mdefine_line|#define PI_RDCLR_OFFSET&t;&t;(PI_ERR_STATUS0_A_RCLR - PI_ERR_STATUS0_A)
multiline_comment|/* Bits in PI_ERR_INT_PEND */
DECL|macro|PI_ERR_SPOOL_CMP_B
mdefine_line|#define PI_ERR_SPOOL_CMP_B&t;0x00000001&t;/* Spool end hit high water */
DECL|macro|PI_ERR_SPOOL_CMP_A
mdefine_line|#define PI_ERR_SPOOL_CMP_A&t;0x00000002
DECL|macro|PI_ERR_SPUR_MSG_B
mdefine_line|#define PI_ERR_SPUR_MSG_B&t;0x00000004&t;/* Spurious message intr.   */
DECL|macro|PI_ERR_SPUR_MSG_A
mdefine_line|#define PI_ERR_SPUR_MSG_A&t;0x00000008
DECL|macro|PI_ERR_WRB_TERR_B
mdefine_line|#define PI_ERR_WRB_TERR_B&t;0x00000010&t;/* WRB TERR&t;&t;    */
DECL|macro|PI_ERR_WRB_TERR_A
mdefine_line|#define PI_ERR_WRB_TERR_A&t;0x00000020
DECL|macro|PI_ERR_WRB_WERR_B
mdefine_line|#define PI_ERR_WRB_WERR_B&t;0x00000040&t;/* WRB WERR &t;&t;    */
DECL|macro|PI_ERR_WRB_WERR_A
mdefine_line|#define PI_ERR_WRB_WERR_A&t;0x00000080
DECL|macro|PI_ERR_SYSSTATE_B
mdefine_line|#define PI_ERR_SYSSTATE_B&t;0x00000100&t;/* SysState parity error    */
DECL|macro|PI_ERR_SYSSTATE_A
mdefine_line|#define PI_ERR_SYSSTATE_A&t;0x00000200
DECL|macro|PI_ERR_SYSAD_DATA_B
mdefine_line|#define PI_ERR_SYSAD_DATA_B&t;0x00000400&t;/* SysAD data parity error  */
DECL|macro|PI_ERR_SYSAD_DATA_A
mdefine_line|#define PI_ERR_SYSAD_DATA_A&t;0x00000800
DECL|macro|PI_ERR_SYSAD_ADDR_B
mdefine_line|#define PI_ERR_SYSAD_ADDR_B&t;0x00001000&t;/* SysAD addr parity error  */
DECL|macro|PI_ERR_SYSAD_ADDR_A
mdefine_line|#define PI_ERR_SYSAD_ADDR_A&t;0x00002000
DECL|macro|PI_ERR_SYSCMD_DATA_B
mdefine_line|#define PI_ERR_SYSCMD_DATA_B&t;0x00004000&t;/* SysCmd data parity error */
DECL|macro|PI_ERR_SYSCMD_DATA_A
mdefine_line|#define PI_ERR_SYSCMD_DATA_A&t;0x00008000
DECL|macro|PI_ERR_SYSCMD_ADDR_B
mdefine_line|#define PI_ERR_SYSCMD_ADDR_B&t;0x00010000&t;/* SysCmd addr parity error */
DECL|macro|PI_ERR_SYSCMD_ADDR_A
mdefine_line|#define PI_ERR_SYSCMD_ADDR_A&t;0x00020000
DECL|macro|PI_ERR_BAD_SPOOL_B
mdefine_line|#define PI_ERR_BAD_SPOOL_B&t;0x00040000&t;/* Error spooling to memory */
DECL|macro|PI_ERR_BAD_SPOOL_A
mdefine_line|#define PI_ERR_BAD_SPOOL_A&t;0x00080000
DECL|macro|PI_ERR_UNCAC_UNCORR_B
mdefine_line|#define PI_ERR_UNCAC_UNCORR_B&t;0x00100000&t;/* Uncached uncorrectable   */
DECL|macro|PI_ERR_UNCAC_UNCORR_A
mdefine_line|#define PI_ERR_UNCAC_UNCORR_A&t;0x00200000
DECL|macro|PI_ERR_SYSSTATE_TAG_B
mdefine_line|#define PI_ERR_SYSSTATE_TAG_B&t;0x00400000&t;/* SysState tag parity error */
DECL|macro|PI_ERR_SYSSTATE_TAG_A
mdefine_line|#define PI_ERR_SYSSTATE_TAG_A&t;0x00800000
DECL|macro|PI_ERR_MD_UNCORR
mdefine_line|#define PI_ERR_MD_UNCORR&t;0x01000000&t;/* Must be cleared in MD    */
DECL|macro|PI_ERR_CLEAR_ALL_A
mdefine_line|#define PI_ERR_CLEAR_ALL_A&t;0x00aaaaaa
DECL|macro|PI_ERR_CLEAR_ALL_B
mdefine_line|#define PI_ERR_CLEAR_ALL_B&t;0x00555555
multiline_comment|/*&n; * The following three macros define all possible error int pends. &n; */
DECL|macro|PI_FATAL_ERR_CPU_A
mdefine_line|#define PI_FATAL_ERR_CPU_A&t;(PI_ERR_SYSSTATE_TAG_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_BAD_SPOOL_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSCMD_ADDR_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSCMD_DATA_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSAD_ADDR_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSAD_DATA_A&t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSSTATE_A)
DECL|macro|PI_MISC_ERR_CPU_A
mdefine_line|#define PI_MISC_ERR_CPU_A&t;(PI_ERR_UNCAC_UNCORR_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_WRB_WERR_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_WRB_TERR_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SPUR_MSG_A &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SPOOL_CMP_A)
DECL|macro|PI_FATAL_ERR_CPU_B
mdefine_line|#define PI_FATAL_ERR_CPU_B&t;(PI_ERR_SYSSTATE_TAG_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_BAD_SPOOL_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSCMD_ADDR_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSCMD_DATA_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSAD_ADDR_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSAD_DATA_B&t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SYSSTATE_B)
DECL|macro|PI_MISC_ERR_CPU_B
mdefine_line|#define PI_MISC_ERR_CPU_B &t;(PI_ERR_UNCAC_UNCORR_B  | &bslash;&n;&t;&t;&t;&t; PI_ERR_WRB_WERR_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_WRB_TERR_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SPUR_MSG_B &t;| &bslash;&n;&t;&t;&t;&t; PI_ERR_SPOOL_CMP_B)
DECL|macro|PI_ERR_GENERIC
mdefine_line|#define PI_ERR_GENERIC&t;(PI_ERR_MD_UNCORR)
multiline_comment|/*&n; * Error types for PI_ERR_STATUS0_[AB] and error stack:&n; * Use the write types if WRBRRB is 1 else use the read types&n; */
multiline_comment|/* Fields in PI_ERR_STATUS0_[AB] */
DECL|macro|PI_ERR_ST0_TYPE_MASK
mdefine_line|#define PI_ERR_ST0_TYPE_MASK&t;0x0000000000000007
DECL|macro|PI_ERR_ST0_TYPE_SHFT
mdefine_line|#define PI_ERR_ST0_TYPE_SHFT&t;0
DECL|macro|PI_ERR_ST0_REQNUM_MASK
mdefine_line|#define PI_ERR_ST0_REQNUM_MASK&t;0x0000000000000038
DECL|macro|PI_ERR_ST0_REQNUM_SHFT
mdefine_line|#define PI_ERR_ST0_REQNUM_SHFT&t;3
DECL|macro|PI_ERR_ST0_SUPPL_MASK
mdefine_line|#define PI_ERR_ST0_SUPPL_MASK&t;0x000000000001ffc0
DECL|macro|PI_ERR_ST0_SUPPL_SHFT
mdefine_line|#define PI_ERR_ST0_SUPPL_SHFT&t;6
DECL|macro|PI_ERR_ST0_CMD_MASK
mdefine_line|#define PI_ERR_ST0_CMD_MASK&t;0x0000000001fe0000
DECL|macro|PI_ERR_ST0_CMD_SHFT
mdefine_line|#define PI_ERR_ST0_CMD_SHFT&t;17
DECL|macro|PI_ERR_ST0_ADDR_MASK
mdefine_line|#define PI_ERR_ST0_ADDR_MASK&t;0x3ffffffffe000000
DECL|macro|PI_ERR_ST0_ADDR_SHFT
mdefine_line|#define PI_ERR_ST0_ADDR_SHFT&t;25
DECL|macro|PI_ERR_ST0_OVERRUN_MASK
mdefine_line|#define PI_ERR_ST0_OVERRUN_MASK&t;0x4000000000000000
DECL|macro|PI_ERR_ST0_OVERRUN_SHFT
mdefine_line|#define PI_ERR_ST0_OVERRUN_SHFT&t;62
DECL|macro|PI_ERR_ST0_VALID_MASK
mdefine_line|#define PI_ERR_ST0_VALID_MASK&t;0x8000000000000000
DECL|macro|PI_ERR_ST0_VALID_SHFT
mdefine_line|#define PI_ERR_ST0_VALID_SHFT&t;63
multiline_comment|/* Fields in PI_ERR_STATUS1_[AB] */
DECL|macro|PI_ERR_ST1_SPOOL_MASK
mdefine_line|#define PI_ERR_ST1_SPOOL_MASK&t;0x00000000001fffff
DECL|macro|PI_ERR_ST1_SPOOL_SHFT
mdefine_line|#define PI_ERR_ST1_SPOOL_SHFT&t;0
DECL|macro|PI_ERR_ST1_TOUTCNT_MASK
mdefine_line|#define PI_ERR_ST1_TOUTCNT_MASK&t;0x000000001fe00000
DECL|macro|PI_ERR_ST1_TOUTCNT_SHFT
mdefine_line|#define PI_ERR_ST1_TOUTCNT_SHFT&t;21
DECL|macro|PI_ERR_ST1_INVCNT_MASK
mdefine_line|#define PI_ERR_ST1_INVCNT_MASK&t;0x0000007fe0000000
DECL|macro|PI_ERR_ST1_INVCNT_SHFT
mdefine_line|#define PI_ERR_ST1_INVCNT_SHFT&t;29
DECL|macro|PI_ERR_ST1_CRBNUM_MASK
mdefine_line|#define PI_ERR_ST1_CRBNUM_MASK&t;0x0000038000000000
DECL|macro|PI_ERR_ST1_CRBNUM_SHFT
mdefine_line|#define PI_ERR_ST1_CRBNUM_SHFT&t;39
DECL|macro|PI_ERR_ST1_WRBRRB_MASK
mdefine_line|#define PI_ERR_ST1_WRBRRB_MASK&t;0x0000040000000000
DECL|macro|PI_ERR_ST1_WRBRRB_SHFT
mdefine_line|#define PI_ERR_ST1_WRBRRB_SHFT&t;42
DECL|macro|PI_ERR_ST1_CRBSTAT_MASK
mdefine_line|#define PI_ERR_ST1_CRBSTAT_MASK&t;0x001ff80000000000
DECL|macro|PI_ERR_ST1_CRBSTAT_SHFT
mdefine_line|#define PI_ERR_ST1_CRBSTAT_SHFT&t;43
DECL|macro|PI_ERR_ST1_MSGSRC_MASK
mdefine_line|#define PI_ERR_ST1_MSGSRC_MASK&t;0xffe0000000000000
DECL|macro|PI_ERR_ST1_MSGSRC_SHFT
mdefine_line|#define PI_ERR_ST1_MSGSRC_SHFT&t;53
multiline_comment|/* Fields in the error stack */
DECL|macro|PI_ERR_STK_TYPE_MASK
mdefine_line|#define PI_ERR_STK_TYPE_MASK&t;0x0000000000000003
DECL|macro|PI_ERR_STK_TYPE_SHFT
mdefine_line|#define PI_ERR_STK_TYPE_SHFT&t;0
DECL|macro|PI_ERR_STK_SUPPL_MASK
mdefine_line|#define PI_ERR_STK_SUPPL_MASK&t;0x0000000000000038
DECL|macro|PI_ERR_STK_SUPPL_SHFT
mdefine_line|#define PI_ERR_STK_SUPPL_SHFT&t;3
DECL|macro|PI_ERR_STK_REQNUM_MASK
mdefine_line|#define PI_ERR_STK_REQNUM_MASK&t;0x00000000000001c0
DECL|macro|PI_ERR_STK_REQNUM_SHFT
mdefine_line|#define PI_ERR_STK_REQNUM_SHFT&t;6
DECL|macro|PI_ERR_STK_CRBNUM_MASK
mdefine_line|#define PI_ERR_STK_CRBNUM_MASK&t;0x0000000000000e00
DECL|macro|PI_ERR_STK_CRBNUM_SHFT
mdefine_line|#define PI_ERR_STK_CRBNUM_SHFT&t;9
DECL|macro|PI_ERR_STK_WRBRRB_MASK
mdefine_line|#define PI_ERR_STK_WRBRRB_MASK&t;0x0000000000001000
DECL|macro|PI_ERR_STK_WRBRRB_SHFT
mdefine_line|#define PI_ERR_STK_WRBRRB_SHFT&t;12
DECL|macro|PI_ERR_STK_CRBSTAT_MASK
mdefine_line|#define PI_ERR_STK_CRBSTAT_MASK&t;0x00000000007fe000
DECL|macro|PI_ERR_STK_CRBSTAT_SHFT
mdefine_line|#define PI_ERR_STK_CRBSTAT_SHFT&t;13
DECL|macro|PI_ERR_STK_CMD_MASK
mdefine_line|#define PI_ERR_STK_CMD_MASK&t;0x000000007f800000
DECL|macro|PI_ERR_STK_CMD_SHFT
mdefine_line|#define PI_ERR_STK_CMD_SHFT&t;23
DECL|macro|PI_ERR_STK_ADDR_MASK
mdefine_line|#define PI_ERR_STK_ADDR_MASK&t;0xffffffff80000000
DECL|macro|PI_ERR_STK_ADDR_SHFT
mdefine_line|#define PI_ERR_STK_ADDR_SHFT&t;31
multiline_comment|/* Error type in the error status or stack on Read CRBs */
DECL|macro|PI_ERR_RD_PRERR
mdefine_line|#define PI_ERR_RD_PRERR&t;&t;1
DECL|macro|PI_ERR_RD_DERR
mdefine_line|#define PI_ERR_RD_DERR&t;&t;2
DECL|macro|PI_ERR_RD_TERR
mdefine_line|#define PI_ERR_RD_TERR&t;&t;3
multiline_comment|/* Error type in the error status or stack on Write CRBs */
DECL|macro|PI_ERR_WR_WERR
mdefine_line|#define PI_ERR_WR_WERR&t;&t;0
DECL|macro|PI_ERR_WR_PWERR
mdefine_line|#define PI_ERR_WR_PWERR&t;&t;1
DECL|macro|PI_ERR_WR_TERR
mdefine_line|#define PI_ERR_WR_TERR&t;&t;3
multiline_comment|/* Read or Write CRB in error status or stack */
DECL|macro|PI_ERR_RRB
mdefine_line|#define PI_ERR_RRB&t;0
DECL|macro|PI_ERR_WRB
mdefine_line|#define PI_ERR_WRB&t;1
DECL|macro|PI_ERR_ANY_CRB
mdefine_line|#define PI_ERR_ANY_CRB&t;2
multiline_comment|/* Address masks in the error status and error stack are not the same */
DECL|macro|ERR_STK_ADDR_SHFT
mdefine_line|#define ERR_STK_ADDR_SHFT&t;7
DECL|macro|ERR_STAT0_ADDR_SHFT
mdefine_line|#define ERR_STAT0_ADDR_SHFT&t;3
DECL|macro|PI_MIN_STACK_SIZE
mdefine_line|#define PI_MIN_STACK_SIZE 4096&t;/* For figuring out the size to set */
DECL|macro|PI_STACK_SIZE_SHFT
mdefine_line|#define PI_STACK_SIZE_SHFT&t;12&t;/* 4k */
DECL|macro|ERR_STACK_SIZE_BYTES
mdefine_line|#define ERR_STACK_SIZE_BYTES(_sz) &bslash;&n;       ((_sz) ? (PI_MIN_STACK_SIZE &lt;&lt; ((_sz) - 1)) : 0)
macro_line|#ifdef _LANGUAGE_C
multiline_comment|/*&n; * format of error stack and error status registers.&n; */
DECL|struct|err_stack_format
r_struct
id|err_stack_format
(brace
DECL|member|sk_addr
id|u64
id|sk_addr
suffix:colon
l_int|33
comma
multiline_comment|/* address */
DECL|member|sk_cmd
id|sk_cmd
suffix:colon
l_int|8
comma
multiline_comment|/* message command */
DECL|member|sk_crb_sts
id|sk_crb_sts
suffix:colon
l_int|10
comma
multiline_comment|/* status from RRB or WRB */
DECL|member|sk_rw_rb
id|sk_rw_rb
suffix:colon
l_int|1
comma
multiline_comment|/* RRB == 0, WRB == 1 */
DECL|member|sk_crb_num
id|sk_crb_num
suffix:colon
l_int|3
comma
multiline_comment|/* WRB (0 to 7) or RRB (0 to 4) */
DECL|member|sk_t5_req
id|sk_t5_req
suffix:colon
l_int|3
comma
multiline_comment|/* RRB T5 request number */
DECL|member|sk_suppl
id|sk_suppl
suffix:colon
l_int|3
comma
multiline_comment|/* lowest 3 bit of supplemental */
DECL|member|sk_err_type
id|sk_err_type
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* error type&t;*/
)brace
suffix:semicolon
DECL|union|pi_err_stack
r_typedef
r_union
id|pi_err_stack
(brace
DECL|member|pi_stk_word
id|u64
id|pi_stk_word
suffix:semicolon
DECL|member|pi_stk_fmt
r_struct
id|err_stack_format
id|pi_stk_fmt
suffix:semicolon
DECL|typedef|pi_err_stack_t
)brace
id|pi_err_stack_t
suffix:semicolon
DECL|struct|err_status0_format
r_struct
id|err_status0_format
(brace
DECL|member|s0_valid
id|u64
id|s0_valid
suffix:colon
l_int|1
comma
multiline_comment|/* Valid */
DECL|member|s0_ovr_run
id|s0_ovr_run
suffix:colon
l_int|1
comma
multiline_comment|/* Overrun, spooled to memory */
DECL|member|s0_addr
id|s0_addr
suffix:colon
l_int|37
comma
multiline_comment|/* address */
DECL|member|s0_cmd
id|s0_cmd
suffix:colon
l_int|8
comma
multiline_comment|/* message command */
DECL|member|s0_supl
id|s0_supl
suffix:colon
l_int|11
comma
multiline_comment|/* message supplemental field */
DECL|member|s0_t5_req
id|s0_t5_req
suffix:colon
l_int|3
comma
multiline_comment|/* RRB T5 request number */
DECL|member|s0_err_type
id|s0_err_type
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* error type */
)brace
suffix:semicolon
DECL|union|pi_err_stat0
r_typedef
r_union
id|pi_err_stat0
(brace
DECL|member|pi_stat0_word
id|u64
id|pi_stat0_word
suffix:semicolon
DECL|member|pi_stat0_fmt
r_struct
id|err_status0_format
id|pi_stat0_fmt
suffix:semicolon
DECL|typedef|pi_err_stat0_t
)brace
id|pi_err_stat0_t
suffix:semicolon
DECL|struct|err_status1_format
r_struct
id|err_status1_format
(brace
DECL|member|s1_src
id|u64
id|s1_src
suffix:colon
l_int|11
comma
multiline_comment|/* message source */
DECL|member|s1_crb_sts
id|s1_crb_sts
suffix:colon
l_int|10
comma
multiline_comment|/* status from RRB or WRB */
DECL|member|s1_rw_rb
id|s1_rw_rb
suffix:colon
l_int|1
comma
multiline_comment|/* RRB == 0, WRB == 1 */
DECL|member|s1_crb_num
id|s1_crb_num
suffix:colon
l_int|3
comma
multiline_comment|/* WRB (0 to 7) or RRB (0 to 4) */
DECL|member|s1_inval_cnt
id|s1_inval_cnt
suffix:colon
l_int|10
comma
multiline_comment|/* signed invalidate counter RRB */
DECL|member|s1_to_cnt
id|s1_to_cnt
suffix:colon
l_int|8
comma
multiline_comment|/* crb timeout counter */
DECL|member|s1_spl_cnt
id|s1_spl_cnt
suffix:colon
l_int|21
suffix:semicolon
multiline_comment|/* number spooled to memory */
)brace
suffix:semicolon
DECL|union|pi_err_stat1
r_typedef
r_union
id|pi_err_stat1
(brace
DECL|member|pi_stat1_word
id|u64
id|pi_stat1_word
suffix:semicolon
DECL|member|pi_stat1_fmt
r_struct
id|err_status1_format
id|pi_stat1_fmt
suffix:semicolon
DECL|typedef|pi_err_stat1_t
)brace
id|pi_err_stat1_t
suffix:semicolon
DECL|typedef|rtc_time_t
r_typedef
id|u64
id|rtc_time_t
suffix:semicolon
macro_line|#endif /* _LANGUAGE_C */
multiline_comment|/* Bits in PI_SYSAD_ERRCHK_EN */
DECL|macro|PI_SYSAD_ERRCHK_ECCGEN
mdefine_line|#define PI_SYSAD_ERRCHK_ECCGEN&t;0x01&t;/* Enable ECC generation&t;    */
DECL|macro|PI_SYSAD_ERRCHK_QUALGEN
mdefine_line|#define PI_SYSAD_ERRCHK_QUALGEN&t;0x02&t;/* Enable data quality signal gen.  */
DECL|macro|PI_SYSAD_ERRCHK_SADP
mdefine_line|#define PI_SYSAD_ERRCHK_SADP&t;0x04&t;/* Enable SysAD parity checking     */
DECL|macro|PI_SYSAD_ERRCHK_CMDP
mdefine_line|#define PI_SYSAD_ERRCHK_CMDP&t;0x08&t;/* Enable SysCmd parity checking    */
DECL|macro|PI_SYSAD_ERRCHK_STATE
mdefine_line|#define PI_SYSAD_ERRCHK_STATE&t;0x10&t;/* Enable SysState parity checking  */
DECL|macro|PI_SYSAD_ERRCHK_QUAL
mdefine_line|#define PI_SYSAD_ERRCHK_QUAL&t;0x20&t;/* Enable data quality checking     */
DECL|macro|PI_SYSAD_CHECK_ALL
mdefine_line|#define PI_SYSAD_CHECK_ALL&t;0x3f&t;/* Generate and check all signals.  */
multiline_comment|/* Interrupt pending bits on R10000 */
DECL|macro|HUB_IP_PEND0
mdefine_line|#define HUB_IP_PEND0&t;&t;0x0400
DECL|macro|HUB_IP_PEND1_CC
mdefine_line|#define HUB_IP_PEND1_CC&t;&t;0x0800
DECL|macro|HUB_IP_RT
mdefine_line|#define HUB_IP_RT&t;&t;0x1000
DECL|macro|HUB_IP_PROF
mdefine_line|#define HUB_IP_PROF&t;&t;0x2000
DECL|macro|HUB_IP_ERROR
mdefine_line|#define HUB_IP_ERROR&t;&t;0x4000
DECL|macro|HUB_IP_MASK
mdefine_line|#define HUB_IP_MASK&t;&t;0x7c00
multiline_comment|/* PI_RT_LOCAL_CTRL mask and shift definitions */
DECL|macro|PRLC_USE_INT_SHFT
mdefine_line|#define PRLC_USE_INT_SHFT&t;16
DECL|macro|PRLC_USE_INT_MASK
mdefine_line|#define PRLC_USE_INT_MASK&t;(UINT64_CAST 1 &lt;&lt; 16)
DECL|macro|PRLC_USE_INT
mdefine_line|#define PRLC_USE_INT&t;&t;(UINT64_CAST 1 &lt;&lt; 16)
DECL|macro|PRLC_GCLK_SHFT
mdefine_line|#define PRLC_GCLK_SHFT&t;&t;15
DECL|macro|PRLC_GCLK_MASK
mdefine_line|#define PRLC_GCLK_MASK&t;&t;(UINT64_CAST 1 &lt;&lt; 15)
DECL|macro|PRLC_GCLK
mdefine_line|#define PRLC_GCLK&t;&t;(UINT64_CAST 1 &lt;&lt; 15)
DECL|macro|PRLC_GCLK_COUNT_SHFT
mdefine_line|#define PRLC_GCLK_COUNT_SHFT&t;8
DECL|macro|PRLC_GCLK_COUNT_MASK
mdefine_line|#define PRLC_GCLK_COUNT_MASK&t;(UINT64_CAST 0x7f &lt;&lt; 8)
DECL|macro|PRLC_MAX_COUNT_SHFT
mdefine_line|#define PRLC_MAX_COUNT_SHFT&t;1
DECL|macro|PRLC_MAX_COUNT_MASK
mdefine_line|#define PRLC_MAX_COUNT_MASK&t;(UINT64_CAST 0x7f &lt;&lt; 1)
DECL|macro|PRLC_GCLK_EN_SHFT
mdefine_line|#define PRLC_GCLK_EN_SHFT&t;0
DECL|macro|PRLC_GCLK_EN_MASK
mdefine_line|#define PRLC_GCLK_EN_MASK&t;(UINT64_CAST 1)
DECL|macro|PRLC_GCLK_EN
mdefine_line|#define PRLC_GCLK_EN&t;&t;(UINT64_CAST 1)
multiline_comment|/* PI_RT_FILTER_CTRL mask and shift definitions */
macro_line|#if 0
multiline_comment|/*&n; * XXX - This register&squot;s definition has changed, but it&squot;s only implemented&n; * in Hub 2.&n; */
mdefine_line|#define PRFC_DROP_COUNT_SHFT&t;27
mdefine_line|#define PRFC_DROP_COUNT_MASK&t;(UINT64_CAST 0x3ff &lt;&lt; 27)
mdefine_line|#define PRFC_DROP_CTR_SHFT&t;18
mdefine_line|#define PRFC_DROP_CTR_MASK&t;(UINT64_CAST 0x1ff &lt;&lt; 18)
mdefine_line|#define PRFC_MASK_ENABLE_SHFT&t;10
mdefine_line|#define PRFC_MASK_ENABLE_MASK&t;(UINT64_CAST 0x7f &lt;&lt; 10)
mdefine_line|#define PRFC_MASK_CTR_SHFT&t;2
mdefine_line|#define PRFC_MASK_CTR_MASK&t;(UINT64_CAST 0xff &lt;&lt; 2)
mdefine_line|#define PRFC_OFFSET_SHFT&t;0
mdefine_line|#define PRFC_OFFSET_MASK&t;(UINT64_CAST 3)
macro_line|#endif /* 0 */
multiline_comment|/*&n; * Bits for NACK_CNT_A/B and NACK_CMP&n; */
DECL|macro|PI_NACK_CNT_EN_SHFT
mdefine_line|#define PI_NACK_CNT_EN_SHFT&t;20
DECL|macro|PI_NACK_CNT_EN_MASK
mdefine_line|#define PI_NACK_CNT_EN_MASK&t;0x100000
DECL|macro|PI_NACK_CNT_MASK
mdefine_line|#define PI_NACK_CNT_MASK&t;0x0fffff
DECL|macro|PI_NACK_CNT_MAX
mdefine_line|#define PI_NACK_CNT_MAX&t;&t;0x0fffff
macro_line|#endif /* _ASM_SN_SN0_HUBPI_H */
eof

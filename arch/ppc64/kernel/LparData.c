multiline_comment|/* &n; * Copyright 2001 Mike Corrigan, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/abs_addr.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpNaca.h&gt;
macro_line|#include &lt;asm/lppaca.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpRegSave.h&gt;
macro_line|#include &lt;asm/paca.h&gt;
macro_line|#include &lt;asm/iSeries/HvReleaseData.h&gt;
macro_line|#include &lt;asm/iSeries/LparMap.h&gt;
macro_line|#include &lt;asm/iSeries/ItVpdAreas.h&gt;
macro_line|#include &lt;asm/iSeries/ItIplParmsReal.h&gt;
macro_line|#include &lt;asm/iSeries/ItExtVpdPanel.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpQueue.h&gt;
macro_line|#include &lt;asm/iSeries/IoHriProcessorVpd.h&gt;
macro_line|#include &lt;asm/iSeries/ItSpCommArea.h&gt;
multiline_comment|/* The LpQueue is used to pass event data from the hypervisor to&n; * the partition.  This is where I/O interrupt events are communicated.&n; */
multiline_comment|/* May be filled in by the hypervisor so cannot end up in the BSS */
DECL|variable|xItLpQueue
r_struct
id|ItLpQueue
id|xItLpQueue
id|__attribute__
c_func
(paren
(paren
id|__section__
c_func
(paren
l_string|&quot;.data&quot;
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* The HvReleaseData is the root of the information shared between &n; * the hypervisor and Linux.  &n; */
DECL|variable|hvReleaseData
r_struct
id|HvReleaseData
id|hvReleaseData
op_assign
(brace
dot
id|xDesc
op_assign
l_int|0xc8a5d9c4
comma
multiline_comment|/* &quot;HvRD&quot; ebcdic */
dot
id|xSize
op_assign
r_sizeof
(paren
r_struct
id|HvReleaseData
)paren
comma
dot
id|xVpdAreasPtrOffset
op_assign
m_offsetof
(paren
r_struct
id|naca_struct
comma
id|xItVpdAreas
)paren
comma
dot
id|xSlicNacaAddr
op_assign
op_amp
id|naca
comma
multiline_comment|/* 64-bit Naca address */
dot
id|xMsNucDataOffset
op_assign
l_int|0x6000
comma
multiline_comment|/* offset of LparMap within loadarea (see head.S) */
dot
id|xTagsMode
op_assign
l_int|1
comma
multiline_comment|/* tags inactive       */
dot
id|xAddressSize
op_assign
l_int|0
comma
multiline_comment|/* 64 bit              */
dot
id|xNoSharedProcs
op_assign
l_int|0
comma
multiline_comment|/* shared processors   */
dot
id|xNoHMT
op_assign
l_int|0
comma
multiline_comment|/* HMT allowed         */
dot
id|xRsvd2
op_assign
l_int|6
comma
multiline_comment|/* TEMP: This allows non-GA driver */
dot
id|xVrmIndex
op_assign
l_int|4
comma
multiline_comment|/* We are v5r2m0               */
dot
id|xMinSupportedPlicVrmIndex
op_assign
l_int|3
comma
multiline_comment|/* v5r1m0 */
dot
id|xMinCompatablePlicVrmIndex
op_assign
l_int|3
comma
multiline_comment|/* v5r1m0 */
dot
id|xVrmName
op_assign
(brace
l_int|0xd3
comma
l_int|0x89
comma
l_int|0x95
comma
l_int|0xa4
comma
multiline_comment|/* &quot;Linux 2.4.64&quot; ebcdic */
l_int|0xa7
comma
l_int|0x40
comma
l_int|0xf2
comma
l_int|0x4b
comma
l_int|0xf4
comma
l_int|0x4b
comma
l_int|0xf6
comma
l_int|0xf4
)brace
comma
)brace
suffix:semicolon
r_extern
r_void
id|system_reset_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|machine_check_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|data_access_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|instruction_access_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|hardware_interrupt_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|alignment_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|program_check_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fp_unavailable_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|decrementer_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|trap_0a_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|trap_0b_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|system_call_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|single_step_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|trap_0e_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|performance_monitor_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|data_access_slb_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|instruction_access_slb_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|itLpNaca
r_struct
id|ItLpNaca
id|itLpNaca
op_assign
(brace
dot
id|xDesc
op_assign
l_int|0xd397d581
comma
multiline_comment|/* &quot;LpNa&quot; ebcdic */
dot
id|xSize
op_assign
l_int|0x0400
comma
multiline_comment|/* size of ItLpNaca */
dot
id|xIntHdlrOffset
op_assign
l_int|0x0300
comma
multiline_comment|/* offset to int array */
dot
id|xMaxIntHdlrEntries
op_assign
l_int|19
comma
multiline_comment|/* # ents */
dot
id|xPrimaryLpIndex
op_assign
l_int|0
comma
multiline_comment|/* Part # of primary */
dot
id|xServiceLpIndex
op_assign
l_int|0
comma
multiline_comment|/* Part # of serv */
dot
id|xLpIndex
op_assign
l_int|0
comma
multiline_comment|/* Part # of me */
dot
id|xMaxLpQueues
op_assign
l_int|0
comma
multiline_comment|/* # of LP queues */
dot
id|xLpQueueOffset
op_assign
l_int|0x100
comma
multiline_comment|/* offset of start of LP queues */
dot
id|xPirEnvironMode
op_assign
l_int|0
comma
multiline_comment|/* Piranha stuff */
dot
id|xPirConsoleMode
op_assign
l_int|0
comma
dot
id|xPirDasdMode
op_assign
l_int|0
comma
dot
id|xLparInstalled
op_assign
l_int|0
comma
dot
id|xSysPartitioned
op_assign
l_int|0
comma
dot
id|xHwSyncedTBs
op_assign
l_int|0
comma
dot
id|xIntProcUtilHmt
op_assign
l_int|0
comma
dot
id|xSpVpdFormat
op_assign
l_int|0
comma
dot
id|xIntProcRatio
op_assign
l_int|0
comma
dot
id|xPlicVrmIndex
op_assign
l_int|0
comma
multiline_comment|/* VRM index of PLIC */
dot
id|xMinSupportedSlicVrmInd
op_assign
l_int|0
comma
multiline_comment|/* min supported SLIC */
dot
id|xMinCompatableSlicVrmInd
op_assign
l_int|0
comma
multiline_comment|/* min compat SLIC */
dot
id|xLoadAreaAddr
op_assign
l_int|0
comma
multiline_comment|/* 64-bit addr of load area */
dot
id|xLoadAreaChunks
op_assign
l_int|0
comma
multiline_comment|/* chunks for load area */
dot
id|xPaseSysCallCRMask
op_assign
l_int|0
comma
multiline_comment|/* PASE mask */
dot
id|xSlicSegmentTablePtr
op_assign
l_int|0
comma
multiline_comment|/* seg table */
dot
id|xOldLpQueue
op_assign
(brace
l_int|0
)brace
comma
multiline_comment|/* Old LP Queue */
dot
id|xInterruptHdlr
op_assign
(brace
(paren
id|u64
)paren
id|system_reset_iSeries
comma
multiline_comment|/* 0x100 System Reset */
(paren
id|u64
)paren
id|machine_check_iSeries
comma
multiline_comment|/* 0x200 Machine Check */
(paren
id|u64
)paren
id|data_access_iSeries
comma
multiline_comment|/* 0x300 Data Access */
(paren
id|u64
)paren
id|instruction_access_iSeries
comma
multiline_comment|/* 0x400 Instruction Access */
(paren
id|u64
)paren
id|hardware_interrupt_iSeries
comma
multiline_comment|/* 0x500 External */
(paren
id|u64
)paren
id|alignment_iSeries
comma
multiline_comment|/* 0x600 Alignment */
(paren
id|u64
)paren
id|program_check_iSeries
comma
multiline_comment|/* 0x700 Program Check */
(paren
id|u64
)paren
id|fp_unavailable_iSeries
comma
multiline_comment|/* 0x800 FP Unavailable */
(paren
id|u64
)paren
id|decrementer_iSeries
comma
multiline_comment|/* 0x900 Decrementer */
(paren
id|u64
)paren
id|trap_0a_iSeries
comma
multiline_comment|/* 0xa00 Trap 0A */
(paren
id|u64
)paren
id|trap_0b_iSeries
comma
multiline_comment|/* 0xb00 Trap 0B */
(paren
id|u64
)paren
id|system_call_iSeries
comma
multiline_comment|/* 0xc00 System Call */
(paren
id|u64
)paren
id|single_step_iSeries
comma
multiline_comment|/* 0xd00 Single Step */
(paren
id|u64
)paren
id|trap_0e_iSeries
comma
multiline_comment|/* 0xe00 Trap 0E */
(paren
id|u64
)paren
id|performance_monitor_iSeries
comma
multiline_comment|/* 0xf00 Performance Monitor */
l_int|0
comma
multiline_comment|/* int 0x1000 */
l_int|0
comma
multiline_comment|/* int 0x1010 */
l_int|0
comma
multiline_comment|/* int 0x1020 CPU ctls */
(paren
id|u64
)paren
id|hardware_interrupt_iSeries
comma
multiline_comment|/* SC Ret Hdlr */
(paren
id|u64
)paren
id|data_access_slb_iSeries
comma
multiline_comment|/* 0x380 D-SLB */
(paren
id|u64
)paren
id|instruction_access_slb_iSeries
multiline_comment|/* 0x480 I-SLB */
)brace
)brace
suffix:semicolon
DECL|variable|itLpNaca
id|EXPORT_SYMBOL
c_func
(paren
id|itLpNaca
)paren
suffix:semicolon
multiline_comment|/* May be filled in by the hypervisor so cannot end up in the BSS */
DECL|variable|xItIplParmsReal
r_struct
id|ItIplParmsReal
id|xItIplParmsReal
id|__attribute__
c_func
(paren
(paren
id|__section__
c_func
(paren
l_string|&quot;.data&quot;
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* May be filled in by the hypervisor so cannot end up in the BSS */
DECL|variable|xItExtVpdPanel
r_struct
id|ItExtVpdPanel
id|xItExtVpdPanel
id|__attribute__
c_func
(paren
(paren
id|__section__
c_func
(paren
l_string|&quot;.data&quot;
)paren
)paren
)paren
suffix:semicolon
DECL|variable|xItExtVpdPanel
id|EXPORT_SYMBOL
c_func
(paren
id|xItExtVpdPanel
)paren
suffix:semicolon
DECL|macro|maxPhysicalProcessors
mdefine_line|#define maxPhysicalProcessors 32
DECL|variable|xIoHriProcessorVpd
r_struct
id|IoHriProcessorVpd
id|xIoHriProcessorVpd
(braket
id|maxPhysicalProcessors
)braket
op_assign
(brace
(brace
dot
id|xInstCacheOperandSize
op_assign
l_int|32
comma
dot
id|xDataCacheOperandSize
op_assign
l_int|32
comma
dot
id|xProcFreq
op_assign
l_int|50000000
comma
dot
id|xTimeBaseFreq
op_assign
l_int|50000000
comma
dot
id|xPVR
op_assign
l_int|0x3600
)brace
)brace
suffix:semicolon
multiline_comment|/* Space for Main Store Vpd 27,200 bytes */
multiline_comment|/* May be filled in by the hypervisor so cannot end up in the BSS */
DECL|variable|xMsVpd
id|u64
id|xMsVpd
(braket
l_int|3400
)braket
id|__attribute__
c_func
(paren
(paren
id|__section__
c_func
(paren
l_string|&quot;.data&quot;
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Space for Recovery Log Buffer */
multiline_comment|/* May be filled in by the hypervisor so cannot end up in the BSS */
DECL|variable|xRecoveryLogBuffer
id|u64
id|xRecoveryLogBuffer
(braket
l_int|32
)braket
id|__attribute__
c_func
(paren
(paren
id|__section__
c_func
(paren
l_string|&quot;.data&quot;
)paren
)paren
)paren
suffix:semicolon
DECL|variable|xSpCommArea
r_struct
id|SpCommArea
id|xSpCommArea
op_assign
(brace
dot
id|xDesc
op_assign
l_int|0xE2D7C3C2
comma
dot
id|xFormat
op_assign
l_int|1
comma
)brace
suffix:semicolon
multiline_comment|/* The LparMap data is now located at offset 0x6000 in head.S&n; * It was put there so that the HvReleaseData could address it&n; * with a 32-bit offset as required by the iSeries hypervisor&n; *&n; * The Naca has a pointer to the ItVpdAreas.  The hypervisor finds&n; * the Naca via the HvReleaseData area.  The HvReleaseData has the&n; * offset into the Naca of the pointer to the ItVpdAreas.&n; */
DECL|variable|itVpdAreas
r_struct
id|ItVpdAreas
id|itVpdAreas
op_assign
(brace
dot
id|xSlicDesc
op_assign
l_int|0xc9a3e5c1
comma
multiline_comment|/* &quot;ItVA&quot; */
dot
id|xSlicSize
op_assign
r_sizeof
(paren
r_struct
id|ItVpdAreas
)paren
comma
dot
id|xSlicVpdEntries
op_assign
id|ItVpdMaxEntries
comma
multiline_comment|/* # VPD array entries */
dot
id|xSlicDmaEntries
op_assign
id|ItDmaMaxEntries
comma
multiline_comment|/* # DMA array entries */
dot
id|xSlicMaxLogicalProcs
op_assign
id|NR_CPUS
op_star
l_int|2
comma
multiline_comment|/* Max logical procs */
dot
id|xSlicMaxPhysicalProcs
op_assign
id|maxPhysicalProcessors
comma
multiline_comment|/* Max physical procs */
dot
id|xSlicDmaToksOffset
op_assign
m_offsetof
(paren
r_struct
id|ItVpdAreas
comma
id|xPlicDmaToks
)paren
comma
dot
id|xSlicVpdAdrsOffset
op_assign
m_offsetof
(paren
r_struct
id|ItVpdAreas
comma
id|xSlicVpdAdrs
)paren
comma
dot
id|xSlicDmaLensOffset
op_assign
m_offsetof
(paren
r_struct
id|ItVpdAreas
comma
id|xPlicDmaLens
)paren
comma
dot
id|xSlicVpdLensOffset
op_assign
m_offsetof
(paren
r_struct
id|ItVpdAreas
comma
id|xSlicVpdLens
)paren
comma
dot
id|xSlicMaxSlotLabels
op_assign
l_int|0
comma
multiline_comment|/* max slot labels */
dot
id|xSlicMaxLpQueues
op_assign
l_int|1
comma
multiline_comment|/* max LP queues */
dot
id|xPlicDmaLens
op_assign
(brace
l_int|0
)brace
comma
multiline_comment|/* DMA lengths */
dot
id|xPlicDmaToks
op_assign
(brace
l_int|0
)brace
comma
multiline_comment|/* DMA tokens */
dot
id|xSlicVpdLens
op_assign
(brace
multiline_comment|/* VPD lengths */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/*  0 - 2 */
r_sizeof
(paren
id|xItExtVpdPanel
)paren
comma
multiline_comment|/*       3 Extended VPD   */
r_sizeof
(paren
r_struct
id|paca_struct
)paren
comma
multiline_comment|/*       4 length of Paca  */
l_int|0
comma
multiline_comment|/*       5 */
r_sizeof
(paren
r_struct
id|ItIplParmsReal
)paren
comma
multiline_comment|/* 6 length of IPL parms */
l_int|26992
comma
multiline_comment|/*&t; 7 length of MS VPD */
l_int|0
comma
multiline_comment|/*       8 */
r_sizeof
(paren
r_struct
id|ItLpNaca
)paren
comma
multiline_comment|/*       9 length of LP Naca */
l_int|0
comma
multiline_comment|/*&t;10 */
l_int|256
comma
multiline_comment|/*&t;11 length of Recovery Log Buf */
r_sizeof
(paren
r_struct
id|SpCommArea
)paren
comma
multiline_comment|/*   12 length of SP Comm Area */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 13 - 15 */
r_sizeof
(paren
r_struct
id|IoHriProcessorVpd
)paren
comma
multiline_comment|/* 16 length of Proc Vpd */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 17 - 22  */
r_sizeof
(paren
r_struct
id|ItLpQueue
)paren
comma
multiline_comment|/*     23 length of Lp Queue */
l_int|0
comma
l_int|0
multiline_comment|/* 24 - 25 */
)brace
comma
dot
id|xSlicVpdAdrs
op_assign
(brace
multiline_comment|/* VPD addresses */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/*&t; 0 -  2 */
op_amp
id|xItExtVpdPanel
comma
multiline_comment|/*       3 Extended VPD */
op_amp
id|paca
(braket
l_int|0
)braket
comma
multiline_comment|/*       4 first Paca */
l_int|0
comma
multiline_comment|/*       5 */
op_amp
id|xItIplParmsReal
comma
multiline_comment|/*&t; 6 IPL parms */
op_amp
id|xMsVpd
comma
multiline_comment|/*&t; 7 MS Vpd */
l_int|0
comma
multiline_comment|/*       8 */
op_amp
id|itLpNaca
comma
multiline_comment|/*       9 LpNaca */
l_int|0
comma
multiline_comment|/*&t;10 */
op_amp
id|xRecoveryLogBuffer
comma
multiline_comment|/*&t;11 Recovery Log Buffer */
op_amp
id|xSpCommArea
comma
multiline_comment|/*&t;12 SP Comm Area */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 13 - 15 */
op_amp
id|xIoHriProcessorVpd
comma
multiline_comment|/*      16 Proc Vpd */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 17 - 22 */
op_amp
id|xItLpQueue
comma
multiline_comment|/*      23 Lp Queue */
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|msChunks
r_struct
id|msChunks
id|msChunks
suffix:semicolon
multiline_comment|/* Depending on whether this is called from iSeries or pSeries setup&n; * code, the location of the msChunks struct may or may not have&n; * to be reloc&squot;d, so we force the caller to do that for us by passing&n; * in a pointer to the structure.&n; */
r_int
r_int
DECL|function|msChunks_alloc
id|msChunks_alloc
c_func
(paren
r_int
r_int
id|mem
comma
r_int
r_int
id|num_chunks
comma
r_int
r_int
id|chunk_size
)paren
(brace
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_struct
id|msChunks
op_star
id|_msChunks
op_assign
id|PTRRELOC
c_func
(paren
op_amp
id|msChunks
)paren
suffix:semicolon
id|_msChunks-&gt;num_chunks
op_assign
id|num_chunks
suffix:semicolon
id|_msChunks-&gt;chunk_size
op_assign
id|chunk_size
suffix:semicolon
id|_msChunks-&gt;chunk_shift
op_assign
id|__ilog2
c_func
(paren
id|chunk_size
)paren
suffix:semicolon
id|_msChunks-&gt;chunk_mask
op_assign
(paren
l_int|1UL
op_lshift
id|_msChunks-&gt;chunk_shift
)paren
op_minus
l_int|1
suffix:semicolon
id|mem
op_assign
id|_ALIGN
c_func
(paren
id|mem
comma
r_sizeof
(paren
id|msChunks_entry
)paren
)paren
suffix:semicolon
id|_msChunks-&gt;abs
op_assign
(paren
id|msChunks_entry
op_star
)paren
(paren
id|mem
op_plus
id|offset
)paren
suffix:semicolon
id|mem
op_add_assign
id|num_chunks
op_star
r_sizeof
(paren
id|msChunks_entry
)paren
suffix:semicolon
r_return
id|mem
suffix:semicolon
)brace
eof

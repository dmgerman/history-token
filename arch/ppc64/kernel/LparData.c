multiline_comment|/* &n; * Copyright 2001 Mike Corrigan, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|macro|__KERNEL__
mdefine_line|#define __KERNEL__ 1
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/init.h&gt;
macro_line|#include &lt;asm/Naca.h&gt;
macro_line|#include &lt;asm/abs_addr.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpNaca.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpPaca.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpRegSave.h&gt;
macro_line|#include &lt;asm/Paca.h&gt;
macro_line|#include &lt;asm/iSeries/HvReleaseData.h&gt;
macro_line|#include &lt;asm/iSeries/LparMap.h&gt;
macro_line|#include &lt;asm/iSeries/ItVpdAreas.h&gt;
macro_line|#include &lt;asm/iSeries/ItIplParmsReal.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpQueue.h&gt;
macro_line|#include &lt;asm/iSeries/IoHriProcessorVpd.h&gt;
macro_line|#include &lt;asm/iSeries/ItSpCommArea.h&gt;
r_extern
r_char
id|_start_boltedStacks
(braket
)braket
suffix:semicolon
multiline_comment|/* The LparMap data is now located at offset 0x6000 in head.S&n; * It was put there so that the HvReleaseData could address it&n; * with a 32-bit offset as required by the iSeries hypervisor&n; *&n; * The Naca has a pointer to the ItVpdAreas.  The hypervisor finds&n; * the Naca via the HvReleaseData area.  The HvReleaseData has the&n; * offset into the Naca of the pointer to the ItVpdAreas.&n; */
r_extern
r_struct
id|ItVpdAreas
id|itVpdAreas
suffix:semicolon
multiline_comment|/* The LpQueue is used to pass event data from the hypervisor to&n; * the partition.  This is where I/O interrupt events are communicated.&n; * The ItLpQueue must be initialized (even though only to all zeros)&n; * If it were uninitialized (in .bss) it would get zeroed after the&n; * kernel gets control.  The hypervisor will have filled in some fields&n; * before the kernel gets control.  By initializing it we keep it out&n; * of the .bss&n; */
DECL|variable|xItLpQueue
r_struct
id|ItLpQueue
id|xItLpQueue
op_assign
(brace
)brace
suffix:semicolon
multiline_comment|/* The HvReleaseData is the root of the information shared between &n; * the hypervisor and Linux.  &n; */
DECL|variable|hvReleaseData
r_struct
id|HvReleaseData
id|hvReleaseData
op_assign
(brace
l_int|0xc8a5d9c4
comma
multiline_comment|/* desc = &quot;HvRD&quot; ebcdic */
r_sizeof
(paren
r_struct
id|HvReleaseData
)paren
comma
m_offsetof
(paren
r_struct
id|Naca
comma
id|xItVpdAreas
)paren
comma
(paren
r_struct
id|Naca
op_star
)paren
(paren
id|KERNELBASE
op_plus
l_int|0x4000
)paren
comma
multiline_comment|/* 64-bit Naca address */
l_int|0x6000
comma
multiline_comment|/* offset of LparMap within loadarea (see head.S) */
l_int|0
comma
l_int|1
comma
multiline_comment|/* tags inactive       */
l_int|0
comma
multiline_comment|/* 64 bit              */
l_int|0
comma
multiline_comment|/* shared processors   */
l_int|0
comma
multiline_comment|/* HMT allowed         */
l_int|6
comma
multiline_comment|/* TEMP: This allows non-GA driver */
l_int|4
comma
multiline_comment|/* We are v5r2m0               */
l_int|3
comma
multiline_comment|/* Min supported PLIC = v5r1m0 */
l_int|3
comma
multiline_comment|/* Min usuable PLIC   = v5r1m0 */
(brace
l_int|0xd3
comma
l_int|0x89
comma
l_int|0x95
comma
l_int|0xa4
comma
multiline_comment|/* &quot;Linux 2.4   &quot;*/
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
(brace
l_int|0
)brace
)brace
suffix:semicolon
r_extern
r_void
id|SystemReset_Iseries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|MachineCheck_Iseries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|DataAccess_Iseries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|InstructionAccess_Iseries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|HardwareInterrupt_Iseries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|Alignment_Iseries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ProgramCheck_Iseries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|FPUnavailable_Iseries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|Decrementer_Iseries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|Trap_0a_Iseries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|Trap_0b_Iseries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|SystemCall_Iseries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|SingleStep_Iseries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|Trap_0e_Iseries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|PerformanceMonitor_Iseries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|DataAccessSLB_Iseries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|InstructionAccessSLB_Iseries
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
l_int|0xd397d581
comma
multiline_comment|/* desc = &quot;LpNa&quot; ebcdic */
l_int|0x0400
comma
multiline_comment|/* size of ItLpNaca     */
l_int|0x0300
comma
l_int|19
comma
multiline_comment|/* offset to int array, # ents */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* Part # of primary, serv, me */
l_int|0
comma
l_int|0x100
comma
multiline_comment|/* # of LP queues, offset */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* Piranha stuff */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* reserved */
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
l_int|0
comma
multiline_comment|/* stuff    */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* reserved */
l_int|0
comma
multiline_comment|/* reserved */
l_int|0
comma
multiline_comment|/* VRM index of PLIC */
l_int|0
comma
l_int|0
comma
multiline_comment|/* min supported, compat SLIC */
l_int|0
comma
multiline_comment|/* 64-bit addr of load area   */
l_int|0
comma
multiline_comment|/* chunks for load area  */
l_int|0
comma
l_int|0
comma
multiline_comment|/* PASE mask, seg table  */
(brace
l_int|0
)brace
comma
multiline_comment|/* 64 reserved bytes  */
(brace
l_int|0
)brace
comma
multiline_comment|/* 128 reserved bytes */
(brace
l_int|0
)brace
comma
multiline_comment|/* Old LP Queue       */
(brace
l_int|0
)brace
comma
multiline_comment|/* 384 reserved bytes */
(brace
(paren
id|u64
)paren
id|SystemReset_Iseries
comma
multiline_comment|/* 0x100 System Reset */
(paren
id|u64
)paren
id|MachineCheck_Iseries
comma
multiline_comment|/* 0x200 Machine Check */
(paren
id|u64
)paren
id|DataAccess_Iseries
comma
multiline_comment|/* 0x300 Data Access */
(paren
id|u64
)paren
id|InstructionAccess_Iseries
comma
multiline_comment|/* 0x400 Instruction Access */
(paren
id|u64
)paren
id|HardwareInterrupt_Iseries
comma
multiline_comment|/* 0x500 External */
(paren
id|u64
)paren
id|Alignment_Iseries
comma
multiline_comment|/* 0x600 Alignment */
(paren
id|u64
)paren
id|ProgramCheck_Iseries
comma
multiline_comment|/* 0x700 Program Check */
(paren
id|u64
)paren
id|FPUnavailable_Iseries
comma
multiline_comment|/* 0x800 FP Unavailable */
(paren
id|u64
)paren
id|Decrementer_Iseries
comma
multiline_comment|/* 0x900 Decrementer */
(paren
id|u64
)paren
id|Trap_0a_Iseries
comma
multiline_comment|/* 0xa00 Trap 0A */
(paren
id|u64
)paren
id|Trap_0b_Iseries
comma
multiline_comment|/* 0xb00 Trap 0B */
(paren
id|u64
)paren
id|SystemCall_Iseries
comma
multiline_comment|/* 0xc00 System Call */
(paren
id|u64
)paren
id|SingleStep_Iseries
comma
multiline_comment|/* 0xd00 Single Step */
(paren
id|u64
)paren
id|Trap_0e_Iseries
comma
multiline_comment|/* 0xe00 Trap 0E */
(paren
id|u64
)paren
id|PerformanceMonitor_Iseries
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
id|HardwareInterrupt_Iseries
comma
multiline_comment|/* SC Ret Hdlr */
(paren
id|u64
)paren
id|DataAccessSLB_Iseries
comma
multiline_comment|/* 0x380 D-SLB */
(paren
id|u64
)paren
id|InstructionAccessSLB_Iseries
multiline_comment|/* 0x480 I-SLB */
)brace
)brace
suffix:semicolon
DECL|variable|xItIplParmsReal
r_struct
id|ItIplParmsReal
id|xItIplParmsReal
op_assign
(brace
)brace
suffix:semicolon
DECL|variable|xIoHriProcessorVpd
r_struct
id|IoHriProcessorVpd
id|xIoHriProcessorVpd
(braket
id|maxProcessors
)braket
op_assign
(brace
(brace
id|xInstCacheOperandSize
suffix:colon
l_int|32
comma
id|xDataCacheOperandSize
suffix:colon
l_int|32
comma
id|xProcFreq
suffix:colon
l_int|50000000
comma
id|xTimeBaseFreq
suffix:colon
l_int|50000000
comma
id|xPVR
suffix:colon
l_int|0x3600
)brace
)brace
suffix:semicolon
DECL|variable|xMsVpd
id|u64
id|xMsVpd
(braket
l_int|3400
)braket
op_assign
(brace
)brace
suffix:semicolon
multiline_comment|/* Space for Main Store Vpd 27,200 bytes */
DECL|variable|xRecoveryLogBuffer
id|u64
id|xRecoveryLogBuffer
(braket
l_int|32
)braket
op_assign
(brace
)brace
suffix:semicolon
multiline_comment|/* Space for Recovery Log Buffer */
DECL|variable|xSpCommArea
r_struct
id|SpCommArea
id|xSpCommArea
op_assign
(brace
l_int|0xE2D7C3C2
comma
l_int|1
comma
(brace
l_int|0
)brace
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|itVpdAreas
r_struct
id|ItVpdAreas
id|itVpdAreas
op_assign
(brace
l_int|0xc9a3e5c1
comma
multiline_comment|/* &quot;ItVA&quot; */
r_sizeof
(paren
r_struct
id|ItVpdAreas
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|26
comma
multiline_comment|/* # VPD array entries */
l_int|10
comma
multiline_comment|/* # DMA array entries */
id|maxProcessors
op_star
l_int|2
comma
id|maxProcessors
comma
multiline_comment|/* Max logical, physical procs */
m_offsetof
(paren
r_struct
id|ItVpdAreas
comma
id|xPlicDmaToks
)paren
comma
multiline_comment|/* offset to DMA toks */
m_offsetof
(paren
r_struct
id|ItVpdAreas
comma
id|xSlicVpdAdrs
)paren
comma
multiline_comment|/* offset to VPD addrs */
m_offsetof
(paren
r_struct
id|ItVpdAreas
comma
id|xPlicDmaLens
)paren
comma
multiline_comment|/* offset to DMA lens */
m_offsetof
(paren
r_struct
id|ItVpdAreas
comma
id|xSlicVpdLens
)paren
comma
multiline_comment|/* offset to VPD lens */
l_int|0
comma
multiline_comment|/* max slot labels */
l_int|1
comma
multiline_comment|/* max LP queues */
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
multiline_comment|/* reserved */
(brace
l_int|0
)brace
comma
multiline_comment|/* DMA lengths */
(brace
l_int|0
)brace
comma
multiline_comment|/* DMA tokens */
(brace
multiline_comment|/* VPD lengths */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/*  0 -  3 */
r_sizeof
(paren
r_struct
id|Paca
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
(brace
multiline_comment|/* VPD addresses */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/*&t; 0 -  3 */
op_amp
id|xPaca
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
multiline_comment|/* Data area used in flush_hash_page  */
DECL|variable|flush_hash_page_hpte
r_int
r_int
id|flush_hash_page_hpte
(braket
l_int|2
)braket
suffix:semicolon
DECL|variable|msChunks
r_struct
id|msChunks
id|msChunks
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
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

multiline_comment|/*&n; * LparData.c&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
DECL|macro|__KERNEL__
mdefine_line|#define __KERNEL__ 1
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/iSeries/Naca.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpNaca.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpPaca.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpRegSave.h&gt;
macro_line|#include &lt;asm/iSeries/Paca.h&gt;
macro_line|#include &lt;asm/iSeries/HvReleaseData.h&gt;
macro_line|#include &lt;asm/iSeries/LparMap.h&gt;
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
macro_line|#include &lt;asm/iSeries/ItVpdAreas.h&gt;
macro_line|#include &lt;asm/iSeries/ItIplParmsReal.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpQueue.h&gt;
macro_line|#include &lt;asm/iSeries/IoHriProcessorVpd.h&gt;
macro_line|#include &lt;asm/iSeries/ItSpCommArea.h&gt;
macro_line|#include &quot;ReleaseData.h&quot;
singleline_comment|// maxProcessors is the number of physical processors
singleline_comment|// The number of logical processors is twice that 
singleline_comment|// number to support hardware multi-threading.
singleline_comment|// If CONFIG_SMP is not defined, then logical
singleline_comment|// processors will be defined, but the other threads
singleline_comment|// will spin forever in iSeries_head.S
DECL|macro|maxProcessors
mdefine_line|#define maxProcessors 16 
r_extern
r_char
id|_start_boltedStacks
(braket
)braket
suffix:semicolon
DECL|variable|maxPacas
r_int
id|maxPacas
op_assign
id|maxProcessors
op_star
l_int|2
suffix:semicolon
singleline_comment|// The LparMap is used by the hypervisor to map the load area.  
singleline_comment|// This indicates that the load area should be mapped to VSID 
singleline_comment|// 0x000000000000C and that this  should be made addressable at 
singleline_comment|// ESID 0x00000000C.  On 32-bit machines this is equivalent to 
singleline_comment|// loading segment register 12 with VSID 12.
singleline_comment|// 8192 indicates to map 8192 pages (32 MB) of the load area.
DECL|variable|xLparMap
r_struct
id|LparMap
id|xLparMap
op_assign
(brace
id|xNumberEsids
suffix:colon
l_int|4
comma
singleline_comment|// Number ESID/VSID pairs
id|xNumberRanges
suffix:colon
l_int|1
comma
singleline_comment|// Number of memory ranges
id|xSegmentTableOffs
suffix:colon
l_int|0
comma
singleline_comment|// Segment Table Page (unused)
id|xKernelEsidC
suffix:colon
l_int|0xC
comma
singleline_comment|// ESID to map
id|xKernelVsidC
suffix:colon
l_int|0xCCC
comma
singleline_comment|// VSID to map
id|xKernelEsidD
suffix:colon
l_int|0xD
comma
singleline_comment|// ESID to map
id|xKernelVsidD
suffix:colon
l_int|0xDDD
comma
singleline_comment|// VSID to map
id|xKernelEsidE
suffix:colon
l_int|0xE
comma
singleline_comment|// ESID to map
id|xKernelVsidE
suffix:colon
l_int|0xEEE
comma
singleline_comment|// VSID to map
id|xKernelEsidF
suffix:colon
l_int|0xF
comma
singleline_comment|// ESID to map
id|xKernelVsidF
suffix:colon
l_int|0xFFF
comma
singleline_comment|// VSID to map
id|xPages
suffix:colon
id|HvPagesToMap
comma
singleline_comment|// # of pages to map (8192)
id|xOffset
suffix:colon
l_int|0
comma
singleline_comment|// Offset into load area
id|xVPN
suffix:colon
l_int|0xCCC0000
singleline_comment|// VPN of first mapped page
)brace
suffix:semicolon
singleline_comment|// The Naca has a pointer to the ItVpdAreas.  The hypervisor finds
singleline_comment|// the Naca via the HvReleaseData area.  The HvReleaseData has the
singleline_comment|// offset into the Naca of the pointer to the ItVpdAreas.
r_extern
r_struct
id|ItVpdAreas
id|itVpdAreas
suffix:semicolon
DECL|variable|xNaca
r_struct
id|Naca
id|xNaca
op_assign
(brace
l_int|0
comma
(paren
r_void
op_star
)paren
op_amp
id|itVpdAreas
comma
l_int|0
comma
l_int|0
comma
singleline_comment|// Ram Disk start
l_int|0
comma
l_int|0
singleline_comment|// Ram Disk size
)brace
suffix:semicolon
singleline_comment|// The LpQueue is used to pass event data from the hypervisor to
singleline_comment|// the partition.  This is where I/O interrupt events are communicated.
singleline_comment|// The ItLpQueue must be initialized (even though only to all zeros)
singleline_comment|// If it were uninitialized (in .bss) it would get zeroed after the
singleline_comment|// kernel gets control.  The hypervisor will have filled in some fields
singleline_comment|// before the kernel gets control.  By initializing it we keep it out
singleline_comment|// of the .bss
DECL|variable|xItLpQueue
r_struct
id|ItLpQueue
id|xItLpQueue
op_assign
(brace
)brace
suffix:semicolon
singleline_comment|// The Paca is an array with one entry per processor.  Each contains an 
singleline_comment|// ItLpPaca, which contains the information shared between the 
singleline_comment|// hypervisor and Linux.  Each also contains an ItLpRegSave area which
singleline_comment|// is used by the hypervisor to save registers.
singleline_comment|// On systems with hardware multi-threading, there are two threads
singleline_comment|// per processor.  The Paca array must contain an entry for each thread.
singleline_comment|// The VPD Areas will give a max logical processors = 2 * max physical
singleline_comment|// processors.  The processor VPD array needs one entry per physical
singleline_comment|// processor (not thread).
DECL|macro|PacaInit
mdefine_line|#define PacaInit( n, start, lpq ) &bslash;&n;&t;{ 0, (struct ItLpPaca *)(((char *)(&amp;xPaca[(n)]))+offsetof(struct Paca, xLpPaca)), &bslash;&n;&t;  0, (struct ItLpRegSave *)(((char *)(&amp;xPaca[(n)]))+offsetof(struct Paca, xRegSav)), &bslash;&n;&t;  0, 0, 0, &t;&t;&bslash;&n;&t;  (n), (start),  &t;&bslash;&n;&t;  0,       &t;&t;&bslash;&n;&t;  0,&t;   &t;&t;&bslash;&n;&t;  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0},&bslash;&n;&t;  (lpq),&t;&t;&bslash;&n;&t;  0, 0, {0},&t;&t;&bslash;&n;&t;  { /* LpPaca */&t;&t;&bslash;&n;&t;&t;xDesc: 0xd397d781, /* &quot;LpPa&quot; */&t;&bslash;&n;&t;&t;xSize: sizeof(struct ItLpPaca),&t;&bslash;&n;&t;&t;xFPRegsInUse:&t;1,&t;&t;&bslash;&n;&t;&t;xDynProcStatus: 2,&t;&t;&bslash;&n;&t;&t;xEndOfQuantum:&t;0xffffffffffffffff&t;&bslash;&n;&t;  },&t;&t;&t;&bslash;&n;&t;  { /* LpRegSave */&t;&bslash;&n;&t;&t;0xd397d9e2,&t;/* &quot;LpRS&quot; */&t;&bslash;&n;&t;&t;sizeof(struct ItLpRegSave)&t;&bslash;&n;&t;  }&t;&t;&t;&bslash;&n;&t;}
DECL|variable|xPaca
r_struct
id|Paca
id|xPaca
(braket
id|maxProcessors
op_star
l_int|2
)braket
op_assign
(brace
id|PacaInit
c_func
(paren
l_int|0
comma
l_int|1
comma
op_amp
id|xItLpQueue
)paren
comma
id|PacaInit
c_func
(paren
l_int|1
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|2
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|3
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|4
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|5
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|6
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|7
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|8
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|9
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|10
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|11
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|12
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|13
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|14
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|15
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|16
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|17
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|18
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|19
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|20
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|21
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|22
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|23
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|24
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|25
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|26
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|27
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|28
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|29
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|30
comma
l_int|0
comma
l_int|0
)paren
comma
id|PacaInit
c_func
(paren
l_int|31
comma
l_int|0
comma
l_int|0
)paren
)brace
suffix:semicolon
singleline_comment|// The HvReleaseData is the root of the information shared between 
singleline_comment|// the hypervisor and Linux.  
r_struct
id|HvReleaseData
DECL|variable|hvReleaseData
id|hvReleaseData
op_assign
(brace
l_int|0xc8a5d9c4
comma
singleline_comment|// desc = &quot;HvRD&quot; ebcdic
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
id|xItVpdAreas64
)paren
comma
l_int|0
comma
op_amp
id|xNaca
comma
singleline_comment|// 64-bit Naca address
(paren
(paren
id|u32
)paren
op_amp
id|xLparMap
op_minus
id|KERNELBASE
)paren
comma
l_int|0
comma
l_int|1
comma
singleline_comment|// tags inactive mode
l_int|1
comma
singleline_comment|// 32-bit mode
l_int|0
comma
singleline_comment|// shared processors
l_int|0
comma
singleline_comment|// hardware multithreading
l_int|6
comma
singleline_comment|// TEMP: set me back to 0
singleline_comment|// this allows non-ga 450 driver
l_int|3
comma
singleline_comment|// We are v5r1m0
l_int|3
comma
singleline_comment|// Min supported PLIC = v5r1m0
l_int|3
comma
singleline_comment|// Min usuable PLIC   = v5r1m0
id|RELEASEDATA
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|itLpNaca
r_struct
id|ItLpNaca
id|itLpNaca
op_assign
(brace
l_int|0xd397d581
comma
singleline_comment|// desc = &quot;LpNa&quot; ebcdic
l_int|0x0400
comma
singleline_comment|// size of ItLpNaca
l_int|0x0300
comma
l_int|19
comma
singleline_comment|// offset to int array, # ents
l_int|0
comma
l_int|0
comma
l_int|0
comma
singleline_comment|// Part # of primary, serv, me
l_int|0
comma
l_int|0x100
comma
singleline_comment|// # of LP queues, offset
l_int|0
comma
l_int|0
comma
l_int|0
comma
singleline_comment|// Piranha stuff
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
singleline_comment|// reserved
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
singleline_comment|// stuff
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
singleline_comment|// reserved
l_int|0
comma
singleline_comment|// reserved
l_int|0
comma
singleline_comment|// VRM index of PLIC
l_int|0
comma
l_int|0
comma
singleline_comment|// min supported, compat SLIC
l_int|0
comma
singleline_comment|// 64-bit addr of load area
l_int|0
comma
singleline_comment|// chunks for load area
l_int|0
comma
singleline_comment|// reserved
(brace
l_int|0
)brace
comma
singleline_comment|// 72 reserved bytes
(brace
l_int|0
)brace
comma
singleline_comment|// 128 reserved bytes
(brace
l_int|0
)brace
comma
singleline_comment|// Old LP Queue
(brace
l_int|0
)brace
comma
singleline_comment|// 384 reserved bytes
(brace
l_int|0xc0000100
comma
singleline_comment|// int 0x100
l_int|0xc0000200
comma
singleline_comment|// int 0x200
l_int|0xc0000300
comma
singleline_comment|// int 0x300
l_int|0xc0000400
comma
singleline_comment|// int 0x400
l_int|0xc0000500
comma
singleline_comment|// int 0x500
l_int|0xc0000600
comma
singleline_comment|// int 0x600
l_int|0xc0000700
comma
singleline_comment|// int 0x700
l_int|0xc0000800
comma
singleline_comment|// int 0x800
l_int|0xc0000900
comma
singleline_comment|// int 0x900
l_int|0xc0000a00
comma
singleline_comment|// int 0xa00
l_int|0xc0000b00
comma
singleline_comment|// int 0xb00
l_int|0xc0000c00
comma
singleline_comment|// int 0xc00
l_int|0xc0000d00
comma
singleline_comment|// int 0xd00
l_int|0xc0000e00
comma
singleline_comment|// int 0xe00
l_int|0xc0000f00
comma
singleline_comment|// int 0xf00
l_int|0xc0001000
comma
singleline_comment|// int 0x1000
l_int|0xc0001010
comma
singleline_comment|// int 0x1010
l_int|0xc0001020
comma
singleline_comment|// int 0x1020 CPU ctls
l_int|0xc0000500
singleline_comment|// SC Ret Hdlr
singleline_comment|// int 0x380
singleline_comment|// int 0x480
)brace
)brace
suffix:semicolon
singleline_comment|// All of the data structures that will be filled in by the hypervisor
singleline_comment|// must be initialized (even if only to zeroes) to keep them out of 
singleline_comment|// the bss.  If in bss, they will be zeroed by the kernel startup code
singleline_comment|// after the hypervisor has filled them in.
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
id|xTimeBaseFreq
suffix:colon
l_int|50000000
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
singleline_comment|// Space for Main Store Vpd 27,200 bytes
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
singleline_comment|// Space for Recovery Log Buffer
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
singleline_comment|// &quot;ItVA&quot;
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
singleline_comment|// # VPD array entries
l_int|10
comma
singleline_comment|// # DMA array entries
id|maxProcessors
op_star
l_int|2
comma
id|maxProcessors
comma
singleline_comment|// Max logical, physical procs
m_offsetof
(paren
r_struct
id|ItVpdAreas
comma
id|xPlicDmaToks
)paren
comma
singleline_comment|// offset to DMA toks
m_offsetof
(paren
r_struct
id|ItVpdAreas
comma
id|xSlicVpdAdrs
)paren
comma
singleline_comment|// offset to VPD addrs
m_offsetof
(paren
r_struct
id|ItVpdAreas
comma
id|xPlicDmaLens
)paren
comma
singleline_comment|// offset to DMA lens
m_offsetof
(paren
r_struct
id|ItVpdAreas
comma
id|xSlicVpdLens
)paren
comma
singleline_comment|// offset to VPD lens
l_int|0
comma
singleline_comment|// max slot labels
l_int|1
comma
singleline_comment|// max LP queues
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
singleline_comment|// reserved
(brace
l_int|0
)brace
comma
singleline_comment|// DMA lengths
(brace
l_int|0
)brace
comma
singleline_comment|// DMA tokens
(brace
singleline_comment|// VPD lengths
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
singleline_comment|//  0 -  3
r_sizeof
(paren
r_struct
id|Paca
)paren
comma
singleline_comment|//       4 length of Paca 
l_int|0
comma
singleline_comment|//       5
r_sizeof
(paren
r_struct
id|ItIplParmsReal
)paren
comma
singleline_comment|// 6 length of IPL parms
l_int|26992
comma
singleline_comment|//&t; 7 length of MS VPD
l_int|0
comma
singleline_comment|//       8
r_sizeof
(paren
r_struct
id|ItLpNaca
)paren
comma
singleline_comment|//       9 length of LP Naca
l_int|0
comma
singleline_comment|//&t;10 
l_int|256
comma
singleline_comment|//&t;11 length of Recovery Log Buf
r_sizeof
(paren
r_struct
id|SpCommArea
)paren
comma
singleline_comment|//   12 length of SP Comm area
l_int|0
comma
l_int|0
comma
l_int|0
comma
singleline_comment|// 13 - 15 
r_sizeof
(paren
r_struct
id|IoHriProcessorVpd
)paren
comma
singleline_comment|// 16 length of Proc Vpd
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
singleline_comment|// 17 - 22 
r_sizeof
(paren
r_struct
id|ItLpQueue
)paren
comma
singleline_comment|//     23 length of Lp Queue
l_int|0
comma
l_int|0
singleline_comment|// 24 - 25
)brace
comma
(brace
singleline_comment|// VPD addresses
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
singleline_comment|//  0 -  3
(brace
l_int|0
comma
op_amp
id|xPaca
(braket
l_int|0
)braket
)brace
comma
singleline_comment|//       4 first Paca
(brace
l_int|0
)brace
comma
singleline_comment|//       5
(brace
l_int|0
comma
op_amp
id|xItIplParmsReal
)brace
comma
singleline_comment|//       6 IPL parms
(brace
l_int|0
comma
op_amp
id|xMsVpd
)brace
comma
singleline_comment|//&t; 7 MS Vpd
(brace
l_int|0
)brace
comma
singleline_comment|//       8
(brace
l_int|0
comma
op_amp
id|itLpNaca
)brace
comma
singleline_comment|//       9 LpNaca
(brace
l_int|0
)brace
comma
singleline_comment|//&t;10
(brace
l_int|0
comma
op_amp
id|xRecoveryLogBuffer
)brace
comma
singleline_comment|//&t;11 Recovery Log Buffer
(brace
l_int|0
comma
op_amp
id|xSpCommArea
)brace
comma
singleline_comment|//&t;12 Sp Comm Area
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
singleline_comment|// 13 - 15 
(brace
l_int|0
comma
op_amp
id|xIoHriProcessorVpd
)brace
comma
singleline_comment|//     16 Proc Vpd
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
comma
singleline_comment|// 17 - 22
(brace
l_int|0
comma
op_amp
id|xItLpQueue
)brace
comma
singleline_comment|//      23 Lp Queue
(brace
l_int|0
)brace
comma
(brace
l_int|0
)brace
)brace
)brace
suffix:semicolon
singleline_comment|// The size of this array determines how much main store can be
singleline_comment|// configured for use in the partition.  16384 allows 16384 * 256KB
singleline_comment|// which is 4GB.  This is enough for the 32-bit
singleline_comment|// implementation, but the msChunks array will need to be dynamically
singleline_comment|// allocated for really big partitions.
DECL|variable|msChunks
id|u32
id|msChunks
(braket
l_int|16384
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|variable|totalLpChunks
id|u32
id|totalLpChunks
op_assign
l_int|0
suffix:semicolon
singleline_comment|// Data area used in flush_hash_page 
DECL|variable|flush_hash_page_hpte
r_int
r_int
id|flush_hash_page_hpte
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|function|virt_to_absolute_outline
id|u64
id|virt_to_absolute_outline
c_func
(paren
id|u32
id|address
)paren
(brace
r_return
id|virt_to_absolute
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
eof

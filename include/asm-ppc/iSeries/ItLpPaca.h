multiline_comment|/*&n; * ItLpPaca.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
singleline_comment|//=============================================================================
singleline_comment|//                                   
singleline_comment|//&t;This control block contains the data that is shared between the 
singleline_comment|//&t;hypervisor (PLIC) and the OS.
singleline_comment|//    
singleline_comment|//
singleline_comment|//----------------------------------------------------------------------------
macro_line|#ifndef  _PPC_TYPES_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#endif
macro_line|#ifndef _ITLPPACA_H
DECL|macro|_ITLPPACA_H
mdefine_line|#define _ITLPPACA_H
DECL|struct|ItLpPaca
r_struct
id|ItLpPaca
(brace
singleline_comment|//=============================================================================
singleline_comment|// CACHE_LINE_1 0x0000 - 0x007F Contains read-only data
singleline_comment|// NOTE: The xDynXyz fields are fields that will be dynamically changed by 
singleline_comment|// PLIC when preparing to bring a processor online or when dispatching a 
singleline_comment|// virtual processor!
singleline_comment|//=============================================================================
DECL|member|xDesc
id|u32
id|xDesc
suffix:semicolon
singleline_comment|// Eye catcher 0xD397D781&t;x00-x03
DECL|member|xSize
id|u16
id|xSize
suffix:semicolon
singleline_comment|// Size of this struct&t;&t;x04-x05
DECL|member|xRsvd1_0
id|u16
id|xRsvd1_0
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x06-x07
DECL|member|xRsvd1_1
id|u16
id|xRsvd1_1
suffix:colon
l_int|14
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x08-x09
DECL|member|xSharedProc
id|u8
id|xSharedProc
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Shared processor indicator&t;...
DECL|member|xSecondaryThread
id|u8
id|xSecondaryThread
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Secondary thread indicator&t;...
DECL|member|xDynProcStatus
r_volatile
id|u8
id|xDynProcStatus
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// Dynamic Status of this proc&t;x0A-x0A
DECL|member|xSecondaryThreadCnt
id|u8
id|xSecondaryThreadCnt
suffix:semicolon
singleline_comment|// Secondary thread count&t;x0B-x0B
DECL|member|xDynHvPhysicalProcIndex
r_volatile
id|u16
id|xDynHvPhysicalProcIndex
suffix:semicolon
singleline_comment|// Dynamic HV Physical Proc Index0C-x0D
DECL|member|xDynHvLogicalProcIndex
r_volatile
id|u16
id|xDynHvLogicalProcIndex
suffix:semicolon
singleline_comment|// Dynamic HV Logical Proc Indexx0E-x0F
DECL|member|xDecrVal
id|u32
id|xDecrVal
suffix:semicolon
singleline_comment|// Value for Decr programming &t;x10-x13
DECL|member|xPMCVal
id|u32
id|xPMCVal
suffix:semicolon
singleline_comment|// Value for PMC regs         &t;x14-x17
DECL|member|xDynHwNodeId
r_volatile
id|u32
id|xDynHwNodeId
suffix:semicolon
singleline_comment|// Dynamic Hardware Node id&t;x18-x1B
DECL|member|xDynHwProcId
r_volatile
id|u32
id|xDynHwProcId
suffix:semicolon
singleline_comment|// Dynamic Hardware Proc Id&t;x1C-x1F
DECL|member|xDynPIR
r_volatile
id|u32
id|xDynPIR
suffix:semicolon
singleline_comment|// Dynamic ProcIdReg value&t;x20-x23
DECL|member|xDseiData
id|u32
id|xDseiData
suffix:semicolon
singleline_comment|// DSEI data                  &t;x24-x27
DECL|member|xSPRG3
id|u64
id|xSPRG3
suffix:semicolon
singleline_comment|// SPRG3 value                &t;x28-x2F
DECL|member|xRsvd1_3
id|u8
id|xRsvd1_3
(braket
l_int|80
)braket
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x30-x7F
singleline_comment|//=============================================================================
singleline_comment|// CACHE_LINE_2 0x0080 - 0x00FF Contains local read-write data
singleline_comment|//=============================================================================
singleline_comment|// This Dword contains a byte for each type of interrupt that can occur.  
singleline_comment|// The IPI is a count while the others are just a binary 1 or 0.
DECL|member|xRsvd
id|u16
id|xRsvd
suffix:semicolon
singleline_comment|// Reserved - cleared by #mpasmbl
DECL|member|xXirrInt
id|u8
id|xXirrInt
suffix:semicolon
singleline_comment|// Indicates xXirrValue is valid or Immed IO
DECL|member|xIpiCnt
id|u8
id|xIpiCnt
suffix:semicolon
singleline_comment|// IPI Count
DECL|member|xDecrInt
id|u8
id|xDecrInt
suffix:semicolon
singleline_comment|// DECR interrupt occurred
DECL|member|xPdcInt
id|u8
id|xPdcInt
suffix:semicolon
singleline_comment|// PDC interrupt occurred
DECL|member|xQuantumInt
id|u8
id|xQuantumInt
suffix:semicolon
singleline_comment|// Interrupt quantum reached
DECL|member|xOldPlicDeferredExtInt
id|u8
id|xOldPlicDeferredExtInt
suffix:semicolon
singleline_comment|// Old PLIC has deferred XIRR pending
DECL|member|xPlicDeferIntsArea
id|u64
id|xPlicDeferIntsArea
suffix:semicolon
singleline_comment|// Used to pass the real SRR0/1 from PLIC to the OS as well as to 
singleline_comment|// pass the target SRR0/1 from the OS to PLIC on a SetAsrAndRfid.
DECL|member|xSavedSrr0
id|u64
id|xSavedSrr0
suffix:semicolon
singleline_comment|// Saved SRR0                   x10-x17
DECL|member|xSavedSrr1
id|u64
id|xSavedSrr1
suffix:semicolon
singleline_comment|// Saved SRR1                   x18-x1F
singleline_comment|// Used to pass parms from the OS to PLIC for SetAsrAndRfid
DECL|member|xSavedGpr3
id|u64
id|xSavedGpr3
suffix:semicolon
singleline_comment|// Saved GPR3                   x20-x27
DECL|member|xSavedGpr4
id|u64
id|xSavedGpr4
suffix:semicolon
singleline_comment|// Saved GPR4                   x28-x2F
DECL|member|xSavedGpr5
id|u64
id|xSavedGpr5
suffix:semicolon
singleline_comment|// Saved GPR5                   x30-x37
DECL|member|xRsvd2_1
id|u8
id|xRsvd2_1
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x38-x38
DECL|member|xCpuCtlsTaskAttributes
id|u8
id|xCpuCtlsTaskAttributes
suffix:semicolon
singleline_comment|// Task attributes for cpuctls  x39-x39
DECL|member|xFPRegsInUse
id|u8
id|xFPRegsInUse
suffix:semicolon
singleline_comment|// FP regs in use               x3A-x3A
DECL|member|xPMCRegsInUse
id|u8
id|xPMCRegsInUse
suffix:semicolon
singleline_comment|// PMC regs in use              x3B-x3B
DECL|member|xSavedDecr
r_volatile
id|u32
id|xSavedDecr
suffix:semicolon
singleline_comment|// Saved Decr Value             x3C-x3F
DECL|member|xEmulatedTimeBase
r_volatile
id|u64
id|xEmulatedTimeBase
suffix:semicolon
singleline_comment|// Emulated TB for this thread  x40-x47
DECL|member|xCurPLICLatency
r_volatile
id|u64
id|xCurPLICLatency
suffix:semicolon
singleline_comment|// Unaccounted PLIC latency     x48-x4F
DECL|member|xTotPLICLatency
id|u64
id|xTotPLICLatency
suffix:semicolon
singleline_comment|// Accumulated PLIC latency     x50-x57   
DECL|member|xWaitStateCycles
id|u64
id|xWaitStateCycles
suffix:semicolon
singleline_comment|// Wait cycles for this proc    x58-x5F
DECL|member|xEndOfQuantum
id|u64
id|xEndOfQuantum
suffix:semicolon
singleline_comment|// TB at end of quantum         x60-x67
DECL|member|xPDCSavedSPRG1
id|u64
id|xPDCSavedSPRG1
suffix:semicolon
singleline_comment|// Saved SPRG1 for PMC int      x68-x6F
DECL|member|xPDCSavedSRR0
id|u64
id|xPDCSavedSRR0
suffix:semicolon
singleline_comment|// Saved SRR0 for PMC int       x70-x77
DECL|member|xVirtualDecr
r_volatile
id|u32
id|xVirtualDecr
suffix:semicolon
singleline_comment|// Virtual DECR for shared procsx78-x7B
DECL|member|xRsvd2_2
id|u32
id|xRsvd2_2
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x7C-x7F
singleline_comment|//=============================================================================
singleline_comment|// CACHE_LINE_3 0x0100 - 0x007F: This line is shared with other processors
singleline_comment|//=============================================================================
singleline_comment|// This is the xYieldCount.  An &quot;odd&quot; value (low bit on) means that 
singleline_comment|// the processor is yielded (either because of an OS yield or a PLIC 
singleline_comment|// preempt).  An even value implies that the processor is currently 
singleline_comment|// executing.
singleline_comment|// NOTE: This value will ALWAYS be zero for dedicated processors and 
singleline_comment|// will NEVER be zero for shared processors (ie, initialized to a 1).
DECL|member|xYieldCount
r_volatile
id|u32
id|xYieldCount
suffix:semicolon
singleline_comment|// PLIC increments each dispatchx00-x03
DECL|member|xRsvd3_0
id|u8
id|xRsvd3_0
(braket
l_int|124
)braket
suffix:semicolon
singleline_comment|// Reserved                     x04-x7F         
singleline_comment|//=============================================================================
singleline_comment|// CACHE_LINE_4-5 0x0100 - 0x01FF Contains PMC interrupt data
singleline_comment|//=============================================================================
DECL|member|xPmcSaveArea
id|u8
id|xPmcSaveArea
(braket
l_int|256
)braket
suffix:semicolon
singleline_comment|// PMC interrupt Area           x00-xFF
)brace
suffix:semicolon
macro_line|#endif 
singleline_comment|// _ITLPPACA_H
eof

multiline_comment|/*&n; * lppaca.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef _ASM_LPPACA_H
DECL|macro|_ASM_LPPACA_H
mdefine_line|#define _ASM_LPPACA_H
singleline_comment|//=============================================================================
singleline_comment|//
singleline_comment|//&t;This control block contains the data that is shared between the
singleline_comment|//&t;hypervisor (PLIC) and the OS.
singleline_comment|//
singleline_comment|//
singleline_comment|//----------------------------------------------------------------------------
macro_line|#include &lt;asm/types.h&gt;
DECL|struct|lppaca
r_struct
id|lppaca
(brace
singleline_comment|//=============================================================================
singleline_comment|// CACHE_LINE_1 0x0000 - 0x007F Contains read-only data
singleline_comment|// NOTE: The xDynXyz fields are fields that will be dynamically changed by
singleline_comment|// PLIC when preparing to bring a processor online or when dispatching a
singleline_comment|// virtual processor!
singleline_comment|//=============================================================================
DECL|member|desc
id|u32
id|desc
suffix:semicolon
singleline_comment|// Eye catcher 0xD397D781&t;x00-x03
DECL|member|size
id|u16
id|size
suffix:semicolon
singleline_comment|// Size of this struct&t;&t;x04-x05
DECL|member|reserved1
id|u16
id|reserved1
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x06-x07
DECL|member|reserved2
id|u16
id|reserved2
suffix:colon
l_int|14
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x08-x09
DECL|member|shared_proc
id|u8
id|shared_proc
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Shared processor indicator&t;...
DECL|member|secondary_thread
id|u8
id|secondary_thread
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Secondary thread indicator&t;...
DECL|member|dyn_proc_status
r_volatile
id|u8
id|dyn_proc_status
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// Dynamic Status of this proc&t;x0A-x0A
DECL|member|secondary_thread_count
id|u8
id|secondary_thread_count
suffix:semicolon
singleline_comment|// Secondary thread count&t;x0B-x0B
DECL|member|dyn_hv_phys_proc_index
r_volatile
id|u16
id|dyn_hv_phys_proc_index
suffix:semicolon
singleline_comment|// Dynamic HV Physical Proc Index0C-x0D
DECL|member|dyn_hv_log_proc_index
r_volatile
id|u16
id|dyn_hv_log_proc_index
suffix:semicolon
singleline_comment|// Dynamic HV Logical Proc Indexx0E-x0F
DECL|member|decr_val
id|u32
id|decr_val
suffix:semicolon
singleline_comment|// Value for Decr programming &t;x10-x13
DECL|member|pmc_val
id|u32
id|pmc_val
suffix:semicolon
singleline_comment|// Value for PMC regs         &t;x14-x17
DECL|member|dyn_hw_node_id
r_volatile
id|u32
id|dyn_hw_node_id
suffix:semicolon
singleline_comment|// Dynamic Hardware Node id&t;x18-x1B
DECL|member|dyn_hw_proc_id
r_volatile
id|u32
id|dyn_hw_proc_id
suffix:semicolon
singleline_comment|// Dynamic Hardware Proc Id&t;x1C-x1F
DECL|member|dyn_pir
r_volatile
id|u32
id|dyn_pir
suffix:semicolon
singleline_comment|// Dynamic ProcIdReg value&t;x20-x23
DECL|member|dsei_data
id|u32
id|dsei_data
suffix:semicolon
singleline_comment|// DSEI data                  &t;x24-x27
DECL|member|sprg3
id|u64
id|sprg3
suffix:semicolon
singleline_comment|// SPRG3 value                &t;x28-x2F
DECL|member|reserved3
id|u8
id|reserved3
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
r_union
(brace
DECL|member|any_int
id|u64
id|any_int
suffix:semicolon
r_struct
(brace
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
singleline_comment|// Reserved - cleared by #mpasmbl
DECL|member|xirr_int
id|u8
id|xirr_int
suffix:semicolon
singleline_comment|// Indicates xXirrValue is valid or Immed IO
DECL|member|ipi_cnt
id|u8
id|ipi_cnt
suffix:semicolon
singleline_comment|// IPI Count
DECL|member|decr_int
id|u8
id|decr_int
suffix:semicolon
singleline_comment|// DECR interrupt occurred
DECL|member|pdc_int
id|u8
id|pdc_int
suffix:semicolon
singleline_comment|// PDC interrupt occurred
DECL|member|quantum_int
id|u8
id|quantum_int
suffix:semicolon
singleline_comment|// Interrupt quantum reached
DECL|member|old_plic_deferred_ext_int
id|u8
id|old_plic_deferred_ext_int
suffix:semicolon
singleline_comment|// Old PLIC has a deferred XIRR pending
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|member|int_dword
)brace
id|int_dword
suffix:semicolon
singleline_comment|// Whenever any fields in this Dword are set then PLIC will defer the
singleline_comment|// processing of external interrupts.  Note that PLIC will store the
singleline_comment|// XIRR directly into the xXirrValue field so that another XIRR will
singleline_comment|// not be presented until this one clears.  The layout of the low
singleline_comment|// 4-bytes of this Dword is upto SLIC - PLIC just checks whether the
singleline_comment|// entire Dword is zero or not.  A non-zero value in the low order
singleline_comment|// 2-bytes will result in SLIC being granted the highest thread
singleline_comment|// priority upon return.  A 0 will return to SLIC as medium priority.
DECL|member|plic_defer_ints_area
id|u64
id|plic_defer_ints_area
suffix:semicolon
singleline_comment|// Entire Dword
singleline_comment|// Used to pass the real SRR0/1 from PLIC to SLIC as well as to
singleline_comment|// pass the target SRR0/1 from SLIC to PLIC on a SetAsrAndRfid.
DECL|member|saved_srr0
id|u64
id|saved_srr0
suffix:semicolon
singleline_comment|// Saved SRR0                   x10-x17
DECL|member|saved_srr1
id|u64
id|saved_srr1
suffix:semicolon
singleline_comment|// Saved SRR1                   x18-x1F
singleline_comment|// Used to pass parms from the OS to PLIC for SetAsrAndRfid
DECL|member|saved_gpr3
id|u64
id|saved_gpr3
suffix:semicolon
singleline_comment|// Saved GPR3                   x20-x27
DECL|member|saved_gpr4
id|u64
id|saved_gpr4
suffix:semicolon
singleline_comment|// Saved GPR4                   x28-x2F
DECL|member|saved_gpr5
id|u64
id|saved_gpr5
suffix:semicolon
singleline_comment|// Saved GPR5                   x30-x37
DECL|member|reserved4
id|u8
id|reserved4
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x38-x38
DECL|member|cpuctls_task_attrs
id|u8
id|cpuctls_task_attrs
suffix:semicolon
singleline_comment|// Task attributes for cpuctls  x39-x39
DECL|member|fpregs_in_use
id|u8
id|fpregs_in_use
suffix:semicolon
singleline_comment|// FP regs in use               x3A-x3A
DECL|member|pmcregs_in_use
id|u8
id|pmcregs_in_use
suffix:semicolon
singleline_comment|// PMC regs in use              x3B-x3B
DECL|member|saved_decr
r_volatile
id|u32
id|saved_decr
suffix:semicolon
singleline_comment|// Saved Decr Value             x3C-x3F
DECL|member|emulated_time_base
r_volatile
id|u64
id|emulated_time_base
suffix:semicolon
singleline_comment|// Emulated TB for this thread  x40-x47
DECL|member|cur_plic_latency
r_volatile
id|u64
id|cur_plic_latency
suffix:semicolon
singleline_comment|// Unaccounted PLIC latency     x48-x4F
DECL|member|tot_plic_latency
id|u64
id|tot_plic_latency
suffix:semicolon
singleline_comment|// Accumulated PLIC latency     x50-x57
DECL|member|wait_state_cycles
id|u64
id|wait_state_cycles
suffix:semicolon
singleline_comment|// Wait cycles for this proc    x58-x5F
DECL|member|end_of_quantum
id|u64
id|end_of_quantum
suffix:semicolon
singleline_comment|// TB at end of quantum         x60-x67
DECL|member|pdc_saved_sprg1
id|u64
id|pdc_saved_sprg1
suffix:semicolon
singleline_comment|// Saved SPRG1 for PMC int      x68-x6F
DECL|member|pdc_saved_srr0
id|u64
id|pdc_saved_srr0
suffix:semicolon
singleline_comment|// Saved SRR0 for PMC int       x70-x77
DECL|member|virtual_decr
r_volatile
id|u32
id|virtual_decr
suffix:semicolon
singleline_comment|// Virtual DECR for shared procsx78-x7B
DECL|member|slb_count
id|u16
id|slb_count
suffix:semicolon
singleline_comment|// # of SLBs to maintain        x7C-x7D
DECL|member|idle
id|u8
id|idle
suffix:semicolon
singleline_comment|// Indicate OS is idle          x7E
DECL|member|reserved5
id|u8
id|reserved5
suffix:semicolon
singleline_comment|// Reserved                     x7F
singleline_comment|//=============================================================================
singleline_comment|// CACHE_LINE_3 0x0100 - 0x007F: This line is shared with other processors
singleline_comment|//=============================================================================
singleline_comment|// This is the yield_count.  An &quot;odd&quot; value (low bit on) means that
singleline_comment|// the processor is yielded (either because of an OS yield or a PLIC
singleline_comment|// preempt).  An even value implies that the processor is currently
singleline_comment|// executing.
singleline_comment|// NOTE: This value will ALWAYS be zero for dedicated processors and
singleline_comment|// will NEVER be zero for shared processors (ie, initialized to a 1).
DECL|member|yield_count
r_volatile
id|u32
id|yield_count
suffix:semicolon
singleline_comment|// PLIC increments each dispatchx00-x03
DECL|member|reserved6
id|u8
id|reserved6
(braket
l_int|124
)braket
suffix:semicolon
singleline_comment|// Reserved                     x04-x7F
singleline_comment|//=============================================================================
singleline_comment|// CACHE_LINE_4-5 0x0100 - 0x01FF Contains PMC interrupt data
singleline_comment|//=============================================================================
DECL|member|pmc_save_area
id|u8
id|pmc_save_area
(braket
l_int|256
)braket
suffix:semicolon
singleline_comment|// PMC interrupt Area           x00-xFF
)brace
suffix:semicolon
macro_line|#endif /* _ASM_LPPACA_H */
eof

multiline_comment|/*&n; * Paca.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
singleline_comment|//============================================================================
singleline_comment|//
singleline_comment|// This control block defines the OS&squot;s PACA which defines the processor 
singleline_comment|// specific data for each logical processor on the system.  
singleline_comment|// There are some pointers defined that are utilized by PLIC.
singleline_comment|//   
macro_line|#ifndef&t;_PPC_TYPES_H
macro_line|#include&t;&lt;asm/types.h&gt;
macro_line|#endif
singleline_comment|//-----------------------------------------------------------------------------
singleline_comment|// Other Includes
singleline_comment|//-----------------------------------------------------------------------------
macro_line|#ifndef&t;_ITLPPACA_H
macro_line|#include&t;&lt;asm/iSeries/ItLpPaca.h&gt;
macro_line|#endif
macro_line|#ifndef&t;_ITLPREGSAVE_H
macro_line|#include&t;&lt;asm/iSeries/ItLpRegSave.h&gt;
macro_line|#endif
macro_line|#ifndef _ITLPQUEUE_H
macro_line|#include&t;&lt;asm/iSeries/ItLpQueue.h&gt;
macro_line|#endif
macro_line|#ifndef _PACA_H
DECL|macro|_PACA_H
mdefine_line|#define _PACA_H
multiline_comment|/* &n; * The bolted stack structure is at the head of each bolted stack&n; * and is simply a singly linked list&n; */
singleline_comment|//============================================================================
singleline_comment|//
singleline_comment|//&t;Defines the layout of the Paca.  
singleline_comment|//
singleline_comment|//&t;This structure is not directly accessed by PLIC or the SP except
singleline_comment|//&t;for the first two pointers that point to the ItLpPaca area and the
singleline_comment|//&t;ItLpRegSave area for this processor.
singleline_comment|//
singleline_comment|//============================================================================
DECL|struct|Paca
r_struct
id|Paca
(brace
singleline_comment|//===========================================================================
singleline_comment|// Following two fields are read by PLIC to find the LpPaca and LpRegSave area
singleline_comment|//===========================================================================
DECL|member|pad1
id|u32
id|pad1
suffix:semicolon
singleline_comment|// Pointer to LpPaca for proc&t;&t;
DECL|member|xLpPacaPtr
r_struct
id|ItLpPaca
op_star
id|xLpPacaPtr
suffix:semicolon
singleline_comment|// Pointer to LpPaca for proc
DECL|member|pad2
id|u32
id|pad2
suffix:semicolon
singleline_comment|// Pointer to LpRegSave for proc
DECL|member|xLpRegSavePtr
r_struct
id|ItLpRegSave
op_star
id|xLpRegSavePtr
suffix:semicolon
singleline_comment|// Pointer to LpRegSave for proc&t;
DECL|member|xR21
id|u64
id|xR21
suffix:semicolon
singleline_comment|// Savearea for GPR21
DECL|member|xR22
id|u64
id|xR22
suffix:semicolon
singleline_comment|// Savearea for GPR22
DECL|member|xKsave
id|u64
id|xKsave
suffix:semicolon
singleline_comment|// Saved Kernel stack addr or zero
DECL|member|xPacaIndex
id|u16
id|xPacaIndex
suffix:semicolon
singleline_comment|// Index into Paca array of this
singleline_comment|// Paca.  This is processor number
DECL|member|xProcStart
id|u8
id|xProcStart
suffix:semicolon
singleline_comment|// At startup, processor spins until
singleline_comment|// xProcStart becomes non-zero.
DECL|member|xProcEnabled
id|u8
id|xProcEnabled
suffix:semicolon
singleline_comment|// 1 - soft enabled, 0 - soft disabled
DECL|member|xrsvd2
id|u32
id|xrsvd2
suffix:semicolon
singleline_comment|// was bolted stacks   
DECL|member|xSavedMsr
id|u32
id|xSavedMsr
suffix:semicolon
singleline_comment|// old msr saved here by HvCall
singleline_comment|// and flush_hash_page.
singleline_comment|// HvCall uses 64-bit registers
singleline_comment|// so it must disable external
singleline_comment|// interrupts to avoid the high
singleline_comment|// half of the regs getting lost
singleline_comment|// It can&squot;t stack a frame because
singleline_comment|// some of the callers can&squot;t 
singleline_comment|// tolerate hpt faults (which might
singleline_comment|// occur on the stack)
DECL|member|xSavedLr
id|u32
id|xSavedLr
suffix:semicolon
singleline_comment|// link register saved here by
singleline_comment|// flush_hash_page
DECL|member|xContextOverflow
id|u8
id|xContextOverflow
suffix:semicolon
singleline_comment|// 1 - context overflow - use temporary
singleline_comment|// context = processor# + 1
DECL|member|rsvd4
id|u8
id|rsvd4
suffix:semicolon
DECL|member|rsvd5
id|u16
id|rsvd5
suffix:semicolon
DECL|member|xSRR0
id|u32
id|xSRR0
suffix:semicolon
singleline_comment|// Used as bolted copies of stack fields
DECL|member|xSRR1
id|u32
id|xSRR1
suffix:semicolon
DECL|member|xGPR0
id|u32
id|xGPR0
suffix:semicolon
DECL|member|xGPR2
id|u32
id|xGPR2
suffix:semicolon
DECL|member|default_decr
id|u32
id|default_decr
suffix:semicolon
singleline_comment|// Default decrementer value
DECL|member|ext_ints
id|u32
id|ext_ints
suffix:semicolon
singleline_comment|// ext ints processed 
DECL|member|rsvd6
id|u32
id|rsvd6
suffix:semicolon
DECL|member|rsvd1
id|u64
id|rsvd1
(braket
l_int|5
)braket
suffix:semicolon
singleline_comment|// Rest of cache line reserved
singleline_comment|//===========================================================================
singleline_comment|// CACHE_LINE_2-3 0x0080 - 0x0180
singleline_comment|//===========================================================================
DECL|member|lpQueuePtr
r_struct
id|ItLpQueue
op_star
id|lpQueuePtr
suffix:semicolon
singleline_comment|// LpQueue handled by this processor
DECL|member|breakpoint_loop
id|u32
id|breakpoint_loop
suffix:semicolon
singleline_comment|// Loop until this field is set
singleline_comment|// non-zero by user.  Then set it
singleline_comment|// back to zero before continuing
DECL|member|debug_regs
id|u64
id|debug_regs
suffix:semicolon
singleline_comment|// Pointer to pt_regs at breakpoint
DECL|member|rsvd3
id|u64
id|rsvd3
(braket
l_int|30
)braket
suffix:semicolon
singleline_comment|// To be used by Linux
singleline_comment|//===========================================================================
singleline_comment|// CACHE_LINE_4-8  0x0180 - 0x03FF Contains ItLpPaca
singleline_comment|//===========================================================================
DECL|member|xLpPaca
r_struct
id|ItLpPaca
id|xLpPaca
suffix:semicolon
singleline_comment|// Space for ItLpPaca&t;&t;
singleline_comment|//===========================================================================
singleline_comment|// CACHE_LINE_9-16 0x0400 - 0x07FF Contains ItLpRegSave
singleline_comment|//===========================================================================
DECL|member|xRegSav
r_struct
id|ItLpRegSave
id|xRegSav
suffix:semicolon
singleline_comment|// Register save for proc&t;
)brace
suffix:semicolon
macro_line|#endif /* _PACA_H */
eof

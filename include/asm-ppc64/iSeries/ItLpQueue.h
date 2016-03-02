multiline_comment|/*&n; * ItLpQueue.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef _ITLPQUEUE_H
DECL|macro|_ITLPQUEUE_H
mdefine_line|#define _ITLPQUEUE_H
singleline_comment|//=============================================================================
singleline_comment|//
singleline_comment|//&t;This control block defines the simple LP queue structure that is 
singleline_comment|//&t;shared between the hypervisor (PLIC) and the OS in order to send 
singleline_comment|//&t;events to an LP.  
singleline_comment|//    
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
r_struct
id|HvLpEvent
suffix:semicolon
DECL|macro|ITMaxLpQueues
mdefine_line|#define ITMaxLpQueues 8
DECL|macro|NotUsed
mdefine_line|#define NotUsed&t;&t;0&t;
singleline_comment|// Queue will not be used by PLIC
DECL|macro|DedicatedIo
mdefine_line|#define DedicatedIo&t;1&t;
singleline_comment|// Queue dedicated to IO processor specified
DECL|macro|DedicatedLp
mdefine_line|#define DedicatedLp&t;2&t;
singleline_comment|// Queue dedicated to LP specified
DECL|macro|Shared
mdefine_line|#define Shared&t;&t;3&t;
singleline_comment|// Queue shared for both IO and LP
DECL|macro|LpEventStackSize
mdefine_line|#define LpEventStackSize 4096
DECL|macro|LpEventMaxSize
mdefine_line|#define LpEventMaxSize   256
DECL|macro|LpEventAlign
mdefine_line|#define LpEventAlign&t; 64
DECL|struct|ItLpQueue
r_struct
id|ItLpQueue
(brace
singleline_comment|//
singleline_comment|//  The xSlicCurEventPtr is the pointer to the next event stack entry that will
singleline_comment|//  become valid.  The OS must peek at this entry to determine if it is valid.
singleline_comment|//  PLIC will set the valid indicator as the very last store into that entry.
singleline_comment|//
singleline_comment|//  When the OS has completed processing of the event then it will mark the event
singleline_comment|//  as invalid so that PLIC knows it can store into that event location again.
singleline_comment|//
singleline_comment|// If the event stack fills and there are overflow events, then PLIC will set 
singleline_comment|// the xPlicOverflowIntPending flag in which case the OS will have to fetch the 
singleline_comment|// additional LP events once they have drained the event stack.
singleline_comment|//
singleline_comment|// The first 16-bytes are known by both the OS and PLIC.  The remainder of the
singleline_comment|// cache line is for use by the OS.
singleline_comment|//
singleline_comment|//=============================================================================
DECL|member|xPlicOverflowIntPending
id|u8
id|xPlicOverflowIntPending
suffix:semicolon
singleline_comment|// 0x00 Overflow events are pending
DECL|member|xPlicStatus
id|u8
id|xPlicStatus
suffix:semicolon
singleline_comment|// 0x01 DedicatedIo or DedicatedLp or NotUsed
DECL|member|xSlicLogicalProcIndex
id|u16
id|xSlicLogicalProcIndex
suffix:semicolon
singleline_comment|// 0x02 Logical Proc Index for correlation
DECL|member|xPlicRsvd
id|u8
id|xPlicRsvd
(braket
l_int|12
)braket
suffix:semicolon
singleline_comment|// 0x04
DECL|member|xSlicCurEventPtr
r_char
op_star
id|xSlicCurEventPtr
suffix:semicolon
singleline_comment|// 0x10
DECL|member|xSlicLastValidEventPtr
r_char
op_star
id|xSlicLastValidEventPtr
suffix:semicolon
singleline_comment|// 0x18
DECL|member|xSlicEventStackPtr
r_char
op_star
id|xSlicEventStackPtr
suffix:semicolon
singleline_comment|// 0x20
DECL|member|xIndex
id|u8
id|xIndex
suffix:semicolon
singleline_comment|// 0x28 unique sequential index.
DECL|member|xSlicRsvd
id|u8
id|xSlicRsvd
(braket
l_int|3
)braket
suffix:semicolon
singleline_comment|// 0x29-2b
DECL|member|xInUseWord
id|u32
id|xInUseWord
suffix:semicolon
singleline_comment|// 0x2C
DECL|member|xLpIntCount
id|u64
id|xLpIntCount
suffix:semicolon
singleline_comment|// 0x30 Total Lp Int msgs processed
DECL|member|xLpIntCountByType
id|u64
id|xLpIntCountByType
(braket
l_int|9
)braket
suffix:semicolon
singleline_comment|// 0x38-0x7F Event counts by type
)brace
suffix:semicolon
r_extern
r_struct
id|ItLpQueue
id|xItLpQueue
suffix:semicolon
r_extern
r_struct
id|HvLpEvent
op_star
id|ItLpQueue_getNextLpEvent
c_func
(paren
r_struct
id|ItLpQueue
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ItLpQueue_isLpIntPending
c_func
(paren
r_struct
id|ItLpQueue
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ItLpQueue_process
c_func
(paren
r_struct
id|ItLpQueue
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ItLpQueue_clearValid
c_func
(paren
r_struct
id|HvLpEvent
op_star
)paren
suffix:semicolon
DECL|function|process_iSeries_events
r_static
id|__inline__
r_void
id|process_iSeries_events
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;&t;li&t;0,0x5555&t;&bslash;n&bslash;&n;&t;&t;sc&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;r0&quot;
comma
l_string|&quot;r3&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ITLPQUEUE_H */
eof

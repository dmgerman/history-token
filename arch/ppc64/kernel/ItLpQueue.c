multiline_comment|/*&n; * ItLpQueue.c&n; * Copyright (C) 2001 Mike Corrigan  IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; */
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/paca.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpQueue.h&gt;
macro_line|#include &lt;asm/iSeries/HvLpEvent.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallEvent.h&gt;
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
DECL|function|set_inUse
r_static
id|__inline__
r_int
id|set_inUse
c_func
(paren
r_struct
id|ItLpQueue
op_star
id|lpQueue
)paren
(brace
r_int
id|t
suffix:semicolon
id|u32
op_star
id|inUseP
op_assign
op_amp
(paren
id|lpQueue-&gt;xInUseWord
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;&n;1:&t;lwarx&t;%0,0,%2&t;&t;&bslash;n&bslash;&n;&t;cmpi&t;0,%0,0&t;&t;&bslash;n&bslash;&n;&t;li&t;%0,0&t;&t;&bslash;n&bslash;&n;&t;bne-&t;2f&t;&t;&bslash;n&bslash;&n;&t;addi&t;%0,%0,1&t;&t;&bslash;n&bslash;&n;&t;stwcx.&t;%0,0,%2&t;&t;&bslash;n&bslash;&n;&t;bne-&t;1b&t;&t;&bslash;n&bslash;&n;2:&t;eieio&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|t
)paren
comma
l_string|&quot;=m&quot;
(paren
id|lpQueue-&gt;xInUseWord
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|inUseP
)paren
comma
l_string|&quot;m&quot;
(paren
id|lpQueue-&gt;xInUseWord
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
DECL|function|clear_inUse
r_static
id|__inline__
r_void
id|clear_inUse
c_func
(paren
r_struct
id|ItLpQueue
op_star
id|lpQueue
)paren
(brace
id|lpQueue-&gt;xInUseWord
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Array of LpEvent handler functions */
r_extern
id|LpEventHandler
id|lpEventHandler
(braket
id|HvLpEvent_Type_NumTypes
)braket
suffix:semicolon
DECL|variable|ItLpQueueInProcess
r_int
r_int
id|ItLpQueueInProcess
op_assign
l_int|0
suffix:semicolon
DECL|function|ItLpQueue_getNextLpEvent
r_struct
id|HvLpEvent
op_star
id|ItLpQueue_getNextLpEvent
c_func
(paren
r_struct
id|ItLpQueue
op_star
id|lpQueue
)paren
(brace
r_struct
id|HvLpEvent
op_star
id|nextLpEvent
op_assign
(paren
r_struct
id|HvLpEvent
op_star
)paren
id|lpQueue-&gt;xSlicCurEventPtr
suffix:semicolon
r_if
c_cond
(paren
id|nextLpEvent-&gt;xFlags.xValid
)paren
(brace
multiline_comment|/* rmb() needed only for weakly consistent machines (regatta) */
id|rmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Set pointer to next potential event */
id|lpQueue-&gt;xSlicCurEventPtr
op_add_assign
(paren
(paren
id|nextLpEvent-&gt;xSizeMinus1
op_plus
id|LpEventAlign
)paren
op_div
id|LpEventAlign
)paren
op_star
id|LpEventAlign
suffix:semicolon
multiline_comment|/* Wrap to beginning if no room at end */
r_if
c_cond
(paren
id|lpQueue-&gt;xSlicCurEventPtr
OG
id|lpQueue-&gt;xSlicLastValidEventPtr
)paren
id|lpQueue-&gt;xSlicCurEventPtr
op_assign
id|lpQueue-&gt;xSlicEventStackPtr
suffix:semicolon
)brace
r_else
id|nextLpEvent
op_assign
l_int|NULL
suffix:semicolon
r_return
id|nextLpEvent
suffix:semicolon
)brace
DECL|function|ItLpQueue_isLpIntPending
r_int
id|ItLpQueue_isLpIntPending
c_func
(paren
r_struct
id|ItLpQueue
op_star
id|lpQueue
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_struct
id|HvLpEvent
op_star
id|nextLpEvent
suffix:semicolon
r_if
c_cond
(paren
id|lpQueue
)paren
(brace
id|nextLpEvent
op_assign
(paren
r_struct
id|HvLpEvent
op_star
)paren
id|lpQueue-&gt;xSlicCurEventPtr
suffix:semicolon
id|retval
op_assign
id|nextLpEvent-&gt;xFlags.xValid
op_or
id|lpQueue-&gt;xPlicOverflowIntPending
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|ItLpQueue_clearValid
r_void
id|ItLpQueue_clearValid
c_func
(paren
r_struct
id|HvLpEvent
op_star
id|event
)paren
(brace
multiline_comment|/* Clear the valid bit of the event&n;&t; * Also clear bits within this event that might&n;&t; * look like valid bits (on 64-byte boundaries)&n;   &t; */
r_int
id|extra
op_assign
(paren
(paren
id|event-&gt;xSizeMinus1
op_plus
id|LpEventAlign
)paren
op_div
id|LpEventAlign
)paren
op_minus
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|extra
)paren
(brace
r_case
l_int|3
suffix:colon
(paren
(paren
r_struct
id|HvLpEvent
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|event
op_plus
l_int|3
op_star
id|LpEventAlign
)paren
)paren
op_member_access_from_pointer
id|xFlags.xValid
op_assign
l_int|0
suffix:semicolon
r_case
l_int|2
suffix:colon
(paren
(paren
r_struct
id|HvLpEvent
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|event
op_plus
l_int|2
op_star
id|LpEventAlign
)paren
)paren
op_member_access_from_pointer
id|xFlags.xValid
op_assign
l_int|0
suffix:semicolon
r_case
l_int|1
suffix:colon
(paren
(paren
r_struct
id|HvLpEvent
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|event
op_plus
l_int|1
op_star
id|LpEventAlign
)paren
)paren
op_member_access_from_pointer
id|xFlags.xValid
op_assign
l_int|0
suffix:semicolon
r_case
l_int|0
suffix:colon
suffix:semicolon
)brace
id|mb
c_func
(paren
)paren
suffix:semicolon
id|event-&gt;xFlags.xValid
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|ItLpQueue_process
r_int
id|ItLpQueue_process
c_func
(paren
r_struct
id|ItLpQueue
op_star
id|lpQueue
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|numIntsProcessed
op_assign
l_int|0
suffix:semicolon
r_struct
id|HvLpEvent
op_star
id|nextLpEvent
suffix:semicolon
multiline_comment|/* If we have recursed, just return */
r_if
c_cond
(paren
op_logical_neg
id|set_inUse
c_func
(paren
id|lpQueue
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ItLpQueueInProcess
op_eq
l_int|0
)paren
id|ItLpQueueInProcess
op_assign
l_int|1
suffix:semicolon
r_else
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|nextLpEvent
op_assign
id|ItLpQueue_getNextLpEvent
c_func
(paren
id|lpQueue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nextLpEvent
)paren
(brace
multiline_comment|/* Count events to return to caller&n;&t;&t;&t; * and count processed events in lpQueue&n; &t;&t;&t; */
op_increment
id|numIntsProcessed
suffix:semicolon
id|lpQueue-&gt;xLpIntCount
op_increment
suffix:semicolon
multiline_comment|/* Call appropriate handler here, passing &n;&t;&t;&t; * a pointer to the LpEvent.  The handler&n;&t;&t;&t; * must make a copy of the LpEvent if it&n;&t;&t;&t; * needs it in a bottom half. (perhaps for&n;&t;&t;&t; * an ACK)&n;&t;&t;&t; *&t;&n;&t;&t;&t; *  Handlers are responsible for ACK processing &n;&t;&t;&t; *&n;&t;&t;&t; * The Hypervisor guarantees that LpEvents will&n;&t;&t;&t; * only be delivered with types that we have&n;&t;&t;&t; * registered for, so no type check is necessary&n;&t;&t;&t; * here!&n;  &t;&t;&t; */
r_if
c_cond
(paren
id|nextLpEvent-&gt;xType
OL
id|HvLpEvent_Type_NumTypes
)paren
id|lpQueue-&gt;xLpIntCountByType
(braket
id|nextLpEvent-&gt;xType
)braket
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|nextLpEvent-&gt;xType
OL
id|HvLpEvent_Type_NumTypes
op_logical_and
id|lpEventHandler
(braket
id|nextLpEvent-&gt;xType
)braket
)paren
id|lpEventHandler
(braket
id|nextLpEvent-&gt;xType
)braket
(paren
id|nextLpEvent
comma
id|regs
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Unexpected Lp Event type=%d&bslash;n&quot;
comma
id|nextLpEvent-&gt;xType
)paren
suffix:semicolon
id|ItLpQueue_clearValid
c_func
(paren
id|nextLpEvent
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|lpQueue-&gt;xPlicOverflowIntPending
)paren
multiline_comment|/*&n;&t;&t;&t; * No more valid events. If overflow events are&n;&t;&t;&t; * pending process them&n;&t;&t;&t; */
id|HvCallEvent_getOverflowLpEvents
c_func
(paren
id|lpQueue-&gt;xIndex
)paren
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
id|ItLpQueueInProcess
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|clear_inUse
c_func
(paren
id|lpQueue
)paren
suffix:semicolon
id|get_paca
c_func
(paren
)paren
op_member_access_from_pointer
id|lpEvent_count
op_add_assign
id|numIntsProcessed
suffix:semicolon
r_return
id|numIntsProcessed
suffix:semicolon
)brace
eof

multiline_comment|/*&n; *  linux/drivers/acorn/scsi/msgqueue.c&n; *&n; *  Copyright (C) 1997-1998 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  message queue handling&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;msgqueue.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Russell King&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SCSI message queue handling&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Function: struct msgqueue_entry *mqe_alloc(MsgQueue_t *msgq)&n; * Purpose : Allocate a message queue entry&n; * Params  : msgq - message queue to claim entry for&n; * Returns : message queue entry or NULL.&n; */
DECL|function|mqe_alloc
r_static
r_struct
id|msgqueue_entry
op_star
id|mqe_alloc
c_func
(paren
id|MsgQueue_t
op_star
id|msgq
)paren
(brace
r_struct
id|msgqueue_entry
op_star
id|mq
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mq
op_assign
id|msgq-&gt;free
)paren
op_ne
l_int|NULL
)paren
id|msgq-&gt;free
op_assign
id|mq-&gt;next
suffix:semicolon
r_return
id|mq
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: void mqe_free(MsgQueue_t *msgq, struct msgqueue_entry *mq)&n; * Purpose : free a message queue entry&n; * Params  : msgq - message queue to free entry from&n; *&t;     mq   - message queue entry to free&n; */
DECL|function|mqe_free
r_static
r_void
id|mqe_free
c_func
(paren
id|MsgQueue_t
op_star
id|msgq
comma
r_struct
id|msgqueue_entry
op_star
id|mq
)paren
(brace
r_if
c_cond
(paren
id|mq
)paren
(brace
id|mq-&gt;next
op_assign
id|msgq-&gt;free
suffix:semicolon
id|msgq-&gt;free
op_assign
id|mq
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function: void msgqueue_initialise(MsgQueue_t *msgq)&n; * Purpose : initialise a message queue&n; * Params  : msgq - queue to initialise&n; */
DECL|function|msgqueue_initialise
r_void
id|msgqueue_initialise
c_func
(paren
id|MsgQueue_t
op_star
id|msgq
)paren
(brace
r_int
id|i
suffix:semicolon
id|msgq-&gt;qe
op_assign
l_int|NULL
suffix:semicolon
id|msgq-&gt;free
op_assign
op_amp
id|msgq-&gt;entries
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_MESSAGES
suffix:semicolon
id|i
op_increment
)paren
id|msgq-&gt;entries
(braket
id|i
)braket
dot
id|next
op_assign
op_amp
id|msgq-&gt;entries
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
id|msgq-&gt;entries
(braket
id|NR_MESSAGES
op_minus
l_int|1
)braket
dot
id|next
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: void msgqueue_free(MsgQueue_t *msgq)&n; * Purpose : free a queue&n; * Params  : msgq - queue to free&n; */
DECL|function|msgqueue_free
r_void
id|msgqueue_free
c_func
(paren
id|MsgQueue_t
op_star
id|msgq
)paren
(brace
)brace
multiline_comment|/*&n; * Function: int msgqueue_msglength(MsgQueue_t *msgq)&n; * Purpose : calculate the total length of all messages on the message queue&n; * Params  : msgq - queue to examine&n; * Returns : number of bytes of messages in queue&n; */
DECL|function|msgqueue_msglength
r_int
id|msgqueue_msglength
c_func
(paren
id|MsgQueue_t
op_star
id|msgq
)paren
(brace
r_struct
id|msgqueue_entry
op_star
id|mq
op_assign
id|msgq-&gt;qe
suffix:semicolon
r_int
id|length
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|mq
op_assign
id|msgq-&gt;qe
suffix:semicolon
id|mq
suffix:semicolon
id|mq
op_assign
id|mq-&gt;next
)paren
id|length
op_add_assign
id|mq-&gt;msg.length
suffix:semicolon
r_return
id|length
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: struct message *msgqueue_getmsg(MsgQueue_t *msgq, int msgno)&n; * Purpose : return a message&n; * Params  : msgq   - queue to obtain message from&n; *&t;   : msgno  - message number&n; * Returns : pointer to message string, or NULL&n; */
DECL|function|msgqueue_getmsg
r_struct
id|message
op_star
id|msgqueue_getmsg
c_func
(paren
id|MsgQueue_t
op_star
id|msgq
comma
r_int
id|msgno
)paren
(brace
r_struct
id|msgqueue_entry
op_star
id|mq
suffix:semicolon
r_for
c_loop
(paren
id|mq
op_assign
id|msgq-&gt;qe
suffix:semicolon
id|mq
op_logical_and
id|msgno
suffix:semicolon
id|mq
op_assign
id|mq-&gt;next
comma
id|msgno
op_decrement
)paren
suffix:semicolon
r_return
id|mq
ques
c_cond
op_amp
id|mq-&gt;msg
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: int msgqueue_addmsg(MsgQueue_t *msgq, int length, ...)&n; * Purpose : add a message onto a message queue&n; * Params  : msgq   - queue to add message on&n; *&t;     length - length of message&n; *&t;     ...    - message bytes&n; * Returns : != 0 if successful&n; */
DECL|function|msgqueue_addmsg
r_int
id|msgqueue_addmsg
c_func
(paren
id|MsgQueue_t
op_star
id|msgq
comma
r_int
id|length
comma
dot
dot
dot
)paren
(brace
r_struct
id|msgqueue_entry
op_star
id|mq
op_assign
id|mqe_alloc
c_func
(paren
id|msgq
)paren
suffix:semicolon
id|va_list
id|ap
suffix:semicolon
r_if
c_cond
(paren
id|mq
)paren
(brace
r_struct
id|msgqueue_entry
op_star
op_star
id|mqp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|length
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|length
suffix:semicolon
id|i
op_increment
)paren
id|mq-&gt;msg.msg
(braket
id|i
)braket
op_assign
id|va_arg
c_func
(paren
id|ap
comma
r_int
r_int
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
id|mq-&gt;msg.length
op_assign
id|length
suffix:semicolon
id|mq-&gt;msg.fifo
op_assign
l_int|0
suffix:semicolon
id|mq-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|mqp
op_assign
op_amp
id|msgq-&gt;qe
suffix:semicolon
r_while
c_loop
(paren
op_star
id|mqp
)paren
id|mqp
op_assign
op_amp
(paren
op_star
id|mqp
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
op_star
id|mqp
op_assign
id|mq
suffix:semicolon
)brace
r_return
id|mq
op_ne
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: void msgqueue_flush(MsgQueue_t *msgq)&n; * Purpose : flush all messages from message queue&n; * Params  : msgq - queue to flush&n; */
DECL|function|msgqueue_flush
r_void
id|msgqueue_flush
c_func
(paren
id|MsgQueue_t
op_star
id|msgq
)paren
(brace
r_struct
id|msgqueue_entry
op_star
id|mq
comma
op_star
id|mqnext
suffix:semicolon
r_for
c_loop
(paren
id|mq
op_assign
id|msgq-&gt;qe
suffix:semicolon
id|mq
suffix:semicolon
id|mq
op_assign
id|mqnext
)paren
(brace
id|mqnext
op_assign
id|mq-&gt;next
suffix:semicolon
id|mqe_free
c_func
(paren
id|msgq
comma
id|mq
)paren
suffix:semicolon
)brace
id|msgq-&gt;qe
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|variable|msgqueue_initialise
id|EXPORT_SYMBOL
c_func
(paren
id|msgqueue_initialise
)paren
suffix:semicolon
DECL|variable|msgqueue_free
id|EXPORT_SYMBOL
c_func
(paren
id|msgqueue_free
)paren
suffix:semicolon
DECL|variable|msgqueue_msglength
id|EXPORT_SYMBOL
c_func
(paren
id|msgqueue_msglength
)paren
suffix:semicolon
DECL|variable|msgqueue_getmsg
id|EXPORT_SYMBOL
c_func
(paren
id|msgqueue_getmsg
)paren
suffix:semicolon
DECL|variable|msgqueue_addmsg
id|EXPORT_SYMBOL
c_func
(paren
id|msgqueue_addmsg
)paren
suffix:semicolon
DECL|variable|msgqueue_flush
id|EXPORT_SYMBOL
c_func
(paren
id|msgqueue_flush
)paren
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|__init
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|__exit
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
eof

multiline_comment|/*&n; *  linux/drivers/acorn/scsi/queue.c: queue handling primitives&n; *&n; *  Copyright (C) 1997-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   15-Sep-1997 RMK&t;Created.&n; *   11-Oct-1997 RMK&t;Corrected problem with queue_remove_exclude&n; *&t;&t;&t;not updating internal linked list properly&n; *&t;&t;&t;(was causing commands to go missing).&n; *   30-Aug-2000 RMK&t;Use Linux list handling and spinlocks&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;../../scsi/scsi.h&quot;
DECL|macro|DEBUG
mdefine_line|#define DEBUG
DECL|struct|queue_entry
r_typedef
r_struct
id|queue_entry
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|SCpnt
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
macro_line|#ifdef DEBUG
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
macro_line|#endif
DECL|typedef|QE_t
)brace
id|QE_t
suffix:semicolon
macro_line|#ifdef DEBUG
DECL|macro|QUEUE_MAGIC_FREE
mdefine_line|#define QUEUE_MAGIC_FREE&t;0xf7e1c9a3
DECL|macro|QUEUE_MAGIC_USED
mdefine_line|#define QUEUE_MAGIC_USED&t;0xf7e1cc33
DECL|macro|SET_MAGIC
mdefine_line|#define SET_MAGIC(q,m)&t;((q)-&gt;magic = (m))
DECL|macro|BAD_MAGIC
mdefine_line|#define BAD_MAGIC(q,m)&t;((q)-&gt;magic != (m))
macro_line|#else
DECL|macro|SET_MAGIC
mdefine_line|#define SET_MAGIC(q,m)&t;do { } while (0)
DECL|macro|BAD_MAGIC
mdefine_line|#define BAD_MAGIC(q,m)&t;(0)
macro_line|#endif
macro_line|#include &quot;queue.h&quot;
DECL|macro|NR_QE
mdefine_line|#define NR_QE&t;32
multiline_comment|/*&n; * Function: void queue_initialise (Queue_t *queue)&n; * Purpose : initialise a queue&n; * Params  : queue - queue to initialise&n; */
DECL|function|queue_initialise
r_int
id|queue_initialise
(paren
id|Queue_t
op_star
id|queue
)paren
(brace
r_int
r_int
id|nqueues
op_assign
id|NR_QE
suffix:semicolon
id|QE_t
op_star
id|q
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|queue-&gt;queue_lock
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|queue-&gt;head
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|queue-&gt;free
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If life was easier, then SCpnt would have a&n;&t; * host-available list head, and we wouldn&squot;t&n;&t; * need to keep free lists or allocate this&n;&t; * memory.&n;&t; */
id|queue-&gt;alloc
op_assign
id|q
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|QE_t
)paren
op_star
id|nqueues
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|nqueues
suffix:semicolon
id|q
op_increment
comma
id|nqueues
op_decrement
)paren
(brace
id|SET_MAGIC
c_func
(paren
id|q
comma
id|QUEUE_MAGIC_FREE
)paren
suffix:semicolon
id|q-&gt;SCpnt
op_assign
l_int|NULL
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|q-&gt;list
comma
op_amp
id|queue-&gt;free
)paren
suffix:semicolon
)brace
)brace
r_return
id|queue-&gt;alloc
op_ne
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: void queue_free (Queue_t *queue)&n; * Purpose : free a queue&n; * Params  : queue - queue to free&n; */
DECL|function|queue_free
r_void
id|queue_free
(paren
id|Queue_t
op_star
id|queue
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|queue-&gt;head
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;freeing non-empty queue %p&bslash;n&quot;
comma
id|queue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|queue-&gt;alloc
)paren
id|kfree
c_func
(paren
id|queue-&gt;alloc
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: int queue_add_cmd(Queue_t *queue, Scsi_Cmnd *SCpnt, int head)&n; * Purpose : Add a new command onto a queue, adding REQUEST_SENSE to head.&n; * Params  : queue - destination queue&n; *&t;     SCpnt - command to add&n; *&t;     head  - add command to head of queue&n; * Returns : 0 on error, !0 on success&n; */
DECL|function|__queue_add
r_int
id|__queue_add
c_func
(paren
id|Queue_t
op_star
id|queue
comma
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
id|head
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|list_head
op_star
id|l
suffix:semicolon
id|QE_t
op_star
id|q
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|queue-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|queue-&gt;free
)paren
)paren
r_goto
id|empty
suffix:semicolon
id|l
op_assign
id|queue-&gt;free.next
suffix:semicolon
id|list_del
c_func
(paren
id|l
)paren
suffix:semicolon
id|q
op_assign
id|list_entry
c_func
(paren
id|l
comma
id|QE_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BAD_MAGIC
c_func
(paren
id|q
comma
id|QUEUE_MAGIC_FREE
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|SET_MAGIC
c_func
(paren
id|q
comma
id|QUEUE_MAGIC_USED
)paren
suffix:semicolon
id|q-&gt;SCpnt
op_assign
id|SCpnt
suffix:semicolon
r_if
c_cond
(paren
id|head
)paren
id|list_add
c_func
(paren
id|l
comma
op_amp
id|queue-&gt;head
)paren
suffix:semicolon
r_else
id|list_add_tail
c_func
(paren
id|l
comma
op_amp
id|queue-&gt;head
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
id|empty
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|queue-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|__queue_remove
r_static
id|Scsi_Cmnd
op_star
id|__queue_remove
c_func
(paren
id|Queue_t
op_star
id|queue
comma
r_struct
id|list_head
op_star
id|ent
)paren
(brace
id|QE_t
op_star
id|q
suffix:semicolon
multiline_comment|/*&n;&t; * Move the entry from the &quot;used&quot; list onto the &quot;free&quot; list&n;&t; */
id|list_del
c_func
(paren
id|ent
)paren
suffix:semicolon
id|q
op_assign
id|list_entry
c_func
(paren
id|ent
comma
id|QE_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BAD_MAGIC
c_func
(paren
id|q
comma
id|QUEUE_MAGIC_USED
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|SET_MAGIC
c_func
(paren
id|q
comma
id|QUEUE_MAGIC_FREE
)paren
suffix:semicolon
id|list_add
c_func
(paren
id|ent
comma
op_amp
id|queue-&gt;free
)paren
suffix:semicolon
r_return
id|q-&gt;SCpnt
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: Scsi_Cmnd *queue_remove_exclude (queue, exclude)&n; * Purpose : remove a SCSI command from a queue&n; * Params  : queue   - queue to remove command from&n; *&t;     exclude - bit array of target&amp;lun which is busy&n; * Returns : Scsi_Cmnd if successful (and a reference), or NULL if no command available&n; */
DECL|function|queue_remove_exclude
id|Scsi_Cmnd
op_star
id|queue_remove_exclude
c_func
(paren
id|Queue_t
op_star
id|queue
comma
r_int
r_int
op_star
id|exclude
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|list_head
op_star
id|l
suffix:semicolon
id|Scsi_Cmnd
op_star
id|SCpnt
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|queue-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|queue-&gt;head
)paren
(brace
id|QE_t
op_star
id|q
op_assign
id|list_entry
c_func
(paren
id|l
comma
id|QE_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|q-&gt;SCpnt-&gt;target
op_star
l_int|8
op_plus
id|q-&gt;SCpnt-&gt;lun
comma
id|exclude
)paren
)paren
(brace
id|SCpnt
op_assign
id|__queue_remove
c_func
(paren
id|queue
comma
id|l
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|queue-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|SCpnt
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: Scsi_Cmnd *queue_remove (queue)&n; * Purpose : removes first SCSI command from a queue&n; * Params  : queue   - queue to remove command from&n; * Returns : Scsi_Cmnd if successful (and a reference), or NULL if no command available&n; */
DECL|function|queue_remove
id|Scsi_Cmnd
op_star
id|queue_remove
c_func
(paren
id|Queue_t
op_star
id|queue
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|Scsi_Cmnd
op_star
id|SCpnt
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|queue-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|queue-&gt;head
)paren
)paren
id|SCpnt
op_assign
id|__queue_remove
c_func
(paren
id|queue
comma
id|queue-&gt;head.next
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|queue-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|SCpnt
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: Scsi_Cmnd *queue_remove_tgtluntag (queue, target, lun, tag)&n; * Purpose : remove a SCSI command from the queue for a specified target/lun/tag&n; * Params  : queue  - queue to remove command from&n; *&t;     target - target that we want&n; *&t;     lun    - lun on device&n; *&t;     tag    - tag on device&n; * Returns : Scsi_Cmnd if successful, or NULL if no command satisfies requirements&n; */
DECL|function|queue_remove_tgtluntag
id|Scsi_Cmnd
op_star
id|queue_remove_tgtluntag
(paren
id|Queue_t
op_star
id|queue
comma
r_int
id|target
comma
r_int
id|lun
comma
r_int
id|tag
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|list_head
op_star
id|l
suffix:semicolon
id|Scsi_Cmnd
op_star
id|SCpnt
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|queue-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|queue-&gt;head
)paren
(brace
id|QE_t
op_star
id|q
op_assign
id|list_entry
c_func
(paren
id|l
comma
id|QE_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;SCpnt-&gt;target
op_eq
id|target
op_logical_and
id|q-&gt;SCpnt-&gt;lun
op_eq
id|lun
op_logical_and
id|q-&gt;SCpnt-&gt;tag
op_eq
id|tag
)paren
(brace
id|SCpnt
op_assign
id|__queue_remove
c_func
(paren
id|queue
comma
id|l
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|queue-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|SCpnt
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: int queue_probetgtlun (queue, target, lun)&n; * Purpose : check to see if we have a command in the queue for the specified&n; *&t;     target/lun.&n; * Params  : queue  - queue to look in&n; *&t;     target - target we want to probe&n; *&t;     lun    - lun on target&n; * Returns : 0 if not found, != 0 if found&n; */
DECL|function|queue_probetgtlun
r_int
id|queue_probetgtlun
(paren
id|Queue_t
op_star
id|queue
comma
r_int
id|target
comma
r_int
id|lun
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|list_head
op_star
id|l
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|queue-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|queue-&gt;head
)paren
(brace
id|QE_t
op_star
id|q
op_assign
id|list_entry
c_func
(paren
id|l
comma
id|QE_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;SCpnt-&gt;target
op_eq
id|target
op_logical_and
id|q-&gt;SCpnt-&gt;lun
op_eq
id|lun
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|queue-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|found
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: int queue_remove_cmd(Queue_t *queue, Scsi_Cmnd *SCpnt)&n; * Purpose : remove a specific command from the queues&n; * Params  : queue - queue to look in&n; *&t;     SCpnt - command to find&n; * Returns : 0 if not found&n; */
DECL|function|queue_remove_cmd
r_int
id|queue_remove_cmd
c_func
(paren
id|Queue_t
op_star
id|queue
comma
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|list_head
op_star
id|l
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|queue-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|queue-&gt;head
)paren
(brace
id|QE_t
op_star
id|q
op_assign
id|list_entry
c_func
(paren
id|l
comma
id|QE_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;SCpnt
op_eq
id|SCpnt
)paren
(brace
id|__queue_remove
c_func
(paren
id|queue
comma
id|l
)paren
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|queue-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|found
suffix:semicolon
)brace
DECL|variable|queue_initialise
id|EXPORT_SYMBOL
c_func
(paren
id|queue_initialise
)paren
suffix:semicolon
DECL|variable|queue_free
id|EXPORT_SYMBOL
c_func
(paren
id|queue_free
)paren
suffix:semicolon
DECL|variable|__queue_add
id|EXPORT_SYMBOL
c_func
(paren
id|__queue_add
)paren
suffix:semicolon
DECL|variable|queue_remove
id|EXPORT_SYMBOL
c_func
(paren
id|queue_remove
)paren
suffix:semicolon
DECL|variable|queue_remove_exclude
id|EXPORT_SYMBOL
c_func
(paren
id|queue_remove_exclude
)paren
suffix:semicolon
DECL|variable|queue_remove_tgtluntag
id|EXPORT_SYMBOL
c_func
(paren
id|queue_remove_tgtluntag
)paren
suffix:semicolon
DECL|variable|queue_remove_cmd
id|EXPORT_SYMBOL
c_func
(paren
id|queue_remove_cmd
)paren
suffix:semicolon
DECL|variable|queue_probetgtlun
id|EXPORT_SYMBOL
c_func
(paren
id|queue_probetgtlun
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Russell King&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SCSI command queueing&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof

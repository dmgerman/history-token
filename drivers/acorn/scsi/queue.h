multiline_comment|/*&n; *  linux/drivers/acorn/scsi/queue.h: queue handling&n; *&n; *  Copyright (C) 1997 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef QUEUE_H
DECL|macro|QUEUE_H
mdefine_line|#define QUEUE_H
r_typedef
r_struct
(brace
DECL|member|head
r_struct
id|list_head
id|head
suffix:semicolon
DECL|member|free
r_struct
id|list_head
id|free
suffix:semicolon
DECL|member|queue_lock
id|spinlock_t
id|queue_lock
suffix:semicolon
DECL|member|alloc
r_void
op_star
id|alloc
suffix:semicolon
multiline_comment|/* start of allocated mem */
DECL|typedef|Queue_t
)brace
id|Queue_t
suffix:semicolon
multiline_comment|/*&n; * Function: void queue_initialise (Queue_t *queue)&n; * Purpose : initialise a queue&n; * Params  : queue - queue to initialise&n; */
r_extern
r_int
id|queue_initialise
(paren
id|Queue_t
op_star
id|queue
)paren
suffix:semicolon
multiline_comment|/*&n; * Function: void queue_free (Queue_t *queue)&n; * Purpose : free a queue&n; * Params  : queue - queue to free&n; */
r_extern
r_void
id|queue_free
(paren
id|Queue_t
op_star
id|queue
)paren
suffix:semicolon
multiline_comment|/*&n; * Function: Scsi_Cmnd *queue_remove (queue)&n; * Purpose : removes first SCSI command from a queue&n; * Params  : queue   - queue to remove command from&n; * Returns : Scsi_Cmnd if successful (and a reference), or NULL if no command available&n; */
r_extern
id|Scsi_Cmnd
op_star
id|queue_remove
(paren
id|Queue_t
op_star
id|queue
)paren
suffix:semicolon
multiline_comment|/*&n; * Function: Scsi_Cmnd *queue_remove_exclude_ref (queue, exclude)&n; * Purpose : remove a SCSI command from a queue&n; * Params  : queue   - queue to remove command from&n; *&t;     exclude - array of busy LUNs&n; * Returns : Scsi_Cmnd if successful (and a reference), or NULL if no command available&n; */
r_extern
id|Scsi_Cmnd
op_star
id|queue_remove_exclude
(paren
id|Queue_t
op_star
id|queue
comma
r_void
op_star
id|exclude
)paren
suffix:semicolon
DECL|macro|queue_add_cmd_ordered
mdefine_line|#define queue_add_cmd_ordered(queue,SCpnt) &bslash;&n;&t;__queue_add(queue,SCpnt,(SCpnt)-&gt;cmnd[0] == REQUEST_SENSE)
DECL|macro|queue_add_cmd_tail
mdefine_line|#define queue_add_cmd_tail(queue,SCpnt) &bslash;&n;&t;__queue_add(queue,SCpnt,0)
multiline_comment|/*&n; * Function: int __queue_add(Queue_t *queue, Scsi_Cmnd *SCpnt, int head)&n; * Purpose : Add a new command onto a queue&n; * Params  : queue - destination queue&n; *&t;     SCpnt - command to add&n; *&t;     head  - add command to head of queue&n; * Returns : 0 on error, !0 on success&n; */
r_extern
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
suffix:semicolon
multiline_comment|/*&n; * Function: Scsi_Cmnd *queue_remove_tgtluntag (queue, target, lun, tag)&n; * Purpose : remove a SCSI command from the queue for a specified target/lun/tag&n; * Params  : queue  - queue to remove command from&n; *&t;     target - target that we want&n; *&t;     lun    - lun on device&n; *&t;     tag    - tag on device&n; * Returns : Scsi_Cmnd if successful, or NULL if no command satisfies requirements&n; */
r_extern
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
suffix:semicolon
multiline_comment|/*&n; * Function: int queue_probetgtlun (queue, target, lun)&n; * Purpose : check to see if we have a command in the queue for the specified&n; *&t;     target/lun.&n; * Params  : queue  - queue to look in&n; *&t;     target - target we want to probe&n; *&t;     lun    - lun on target&n; * Returns : 0 if not found, != 0 if found&n; */
r_extern
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
suffix:semicolon
multiline_comment|/*&n; * Function: int queue_remove_cmd (Queue_t *queue, Scsi_Cmnd *SCpnt)&n; * Purpose : remove a specific command from the queues&n; * Params  : queue - queue to look in&n; *&t;     SCpnt - command to find&n; * Returns : 0 if not found&n; */
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
suffix:semicolon
macro_line|#endif /* QUEUE_H */
eof

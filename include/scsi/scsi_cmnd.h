macro_line|#ifndef _SCSI_SCSI_CMND_H
DECL|macro|_SCSI_SCSI_CMND_H
mdefine_line|#define _SCSI_SCSI_CMND_H
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/types.h&gt;
r_struct
id|request
suffix:semicolon
r_struct
id|scatterlist
suffix:semicolon
r_struct
id|scsi_device
suffix:semicolon
r_struct
id|scsi_request
suffix:semicolon
multiline_comment|/* embedded in scsi_cmnd */
DECL|struct|scsi_pointer
r_struct
id|scsi_pointer
(brace
DECL|member|ptr
r_char
op_star
id|ptr
suffix:semicolon
multiline_comment|/* data pointer */
DECL|member|this_residual
r_int
id|this_residual
suffix:semicolon
multiline_comment|/* left in this buffer */
DECL|member|buffer
r_struct
id|scatterlist
op_star
id|buffer
suffix:semicolon
multiline_comment|/* which buffer */
DECL|member|buffers_residual
r_int
id|buffers_residual
suffix:semicolon
multiline_comment|/* how many buffers left */
DECL|member|dma_handle
id|dma_addr_t
id|dma_handle
suffix:semicolon
DECL|member|Status
r_volatile
r_int
id|Status
suffix:semicolon
DECL|member|Message
r_volatile
r_int
id|Message
suffix:semicolon
DECL|member|have_data_in
r_volatile
r_int
id|have_data_in
suffix:semicolon
DECL|member|sent_command
r_volatile
r_int
id|sent_command
suffix:semicolon
DECL|member|phase
r_volatile
r_int
id|phase
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|scsi_cmnd
r_struct
id|scsi_cmnd
(brace
DECL|member|sc_magic
r_int
id|sc_magic
suffix:semicolon
DECL|member|device
r_struct
id|scsi_device
op_star
id|device
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|owner
r_int
r_int
id|owner
suffix:semicolon
DECL|member|sc_request
r_struct
id|scsi_request
op_star
id|sc_request
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* scsi_cmnd participates in queue lists */
DECL|member|eh_entry
r_struct
id|list_head
id|eh_entry
suffix:semicolon
multiline_comment|/* entry for the host eh_cmd_q */
DECL|member|eh_state
r_int
id|eh_state
suffix:semicolon
multiline_comment|/* Used for state tracking in error handlr */
DECL|member|eh_eflags
r_int
id|eh_eflags
suffix:semicolon
multiline_comment|/* Used by error handlr */
DECL|member|done
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/* Mid-level done function */
multiline_comment|/*&n;&t; * A SCSI Command is assigned a nonzero serial_number when internal_cmnd&n;&t; * passes it to the driver&squot;s queue command function.  The serial_number&n;&t; * is cleared when scsi_done is entered indicating that the command has&n;&t; * been completed.  If a timeout occurs, the serial number at the moment&n;&t; * of timeout is copied into serial_number_at_timeout.  By subsequently&n;&t; * comparing the serial_number and serial_number_at_timeout fields&n;&t; * during abort or reset processing, we can detect whether the command&n;&t; * has already completed.  This also detects cases where the command has&n;&t; * completed and the SCSI Command structure has already being reused&n;&t; * for another command, so that we can avoid incorrectly aborting or&n;&t; * resetting the new command.&n;&t; */
DECL|member|serial_number
r_int
r_int
id|serial_number
suffix:semicolon
DECL|member|serial_number_at_timeout
r_int
r_int
id|serial_number_at_timeout
suffix:semicolon
DECL|member|retries
r_int
id|retries
suffix:semicolon
DECL|member|allowed
r_int
id|allowed
suffix:semicolon
DECL|member|timeout_per_command
r_int
id|timeout_per_command
suffix:semicolon
DECL|member|timeout_total
r_int
id|timeout_total
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
multiline_comment|/*&n;&t; * We handle the timeout differently if it happens when a reset, &n;&t; * abort, etc are in process. &n;&t; */
DECL|member|internal_timeout
r_int
r_volatile
r_char
id|internal_timeout
suffix:semicolon
DECL|member|cmd_len
r_int
r_char
id|cmd_len
suffix:semicolon
DECL|member|old_cmd_len
r_int
r_char
id|old_cmd_len
suffix:semicolon
DECL|member|sc_data_direction
r_enum
id|dma_data_direction
id|sc_data_direction
suffix:semicolon
DECL|member|sc_old_data_direction
r_enum
id|dma_data_direction
id|sc_old_data_direction
suffix:semicolon
multiline_comment|/* These elements define the operation we are about to perform */
DECL|macro|MAX_COMMAND_SIZE
mdefine_line|#define MAX_COMMAND_SIZE&t;16
DECL|member|cmnd
r_int
r_char
id|cmnd
(braket
id|MAX_COMMAND_SIZE
)braket
suffix:semicolon
DECL|member|request_bufflen
r_int
id|request_bufflen
suffix:semicolon
multiline_comment|/* Actual request size */
DECL|member|eh_timeout
r_struct
id|timer_list
id|eh_timeout
suffix:semicolon
multiline_comment|/* Used to time out the command. */
DECL|member|request_buffer
r_void
op_star
id|request_buffer
suffix:semicolon
multiline_comment|/* Actual requested buffer */
multiline_comment|/* These elements define the operation we ultimately want to perform */
DECL|member|data_cmnd
r_int
r_char
id|data_cmnd
(braket
id|MAX_COMMAND_SIZE
)braket
suffix:semicolon
DECL|member|old_use_sg
r_int
r_int
id|old_use_sg
suffix:semicolon
multiline_comment|/* We save  use_sg here when requesting&n;&t;&t;&t;&t;&t; * sense info */
DECL|member|use_sg
r_int
r_int
id|use_sg
suffix:semicolon
multiline_comment|/* Number of pieces of scatter-gather */
DECL|member|sglist_len
r_int
r_int
id|sglist_len
suffix:semicolon
multiline_comment|/* size of malloc&squot;d scatter-gather list */
DECL|member|abort_reason
r_int
r_int
id|abort_reason
suffix:semicolon
multiline_comment|/* If the mid-level code requests an&n;&t;&t;&t;&t;&t; * abort, this is the reason. */
DECL|member|bufflen
r_int
id|bufflen
suffix:semicolon
multiline_comment|/* Size of data buffer */
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
multiline_comment|/* Data buffer */
DECL|member|underflow
r_int
id|underflow
suffix:semicolon
multiline_comment|/* Return error if less than&n;&t;&t;&t;&t;   this amount is transferred */
DECL|member|old_underflow
r_int
id|old_underflow
suffix:semicolon
multiline_comment|/* save underflow here when reusing the&n;&t;&t;&t;&t; * command for error handling */
DECL|member|transfersize
r_int
id|transfersize
suffix:semicolon
multiline_comment|/* How much we are guaranteed to&n;&t;&t;&t;&t;   transfer with each SCSI transfer&n;&t;&t;&t;&t;   (ie, between disconnect / &n;&t;&t;&t;&t;   reconnects.   Probably == sector&n;&t;&t;&t;&t;   size */
DECL|member|resid
r_int
id|resid
suffix:semicolon
multiline_comment|/* Number of bytes requested to be&n;&t;&t;&t;&t;   transferred less actual number&n;&t;&t;&t;&t;   transferred (0 if not supported) */
DECL|member|request
r_struct
id|request
op_star
id|request
suffix:semicolon
multiline_comment|/* The command we are&n;&t;&t;&t;&t;   &t;   working on */
DECL|macro|SCSI_SENSE_BUFFERSIZE
mdefine_line|#define SCSI_SENSE_BUFFERSIZE &t;64
DECL|member|sense_buffer
r_int
r_char
id|sense_buffer
(braket
id|SCSI_SENSE_BUFFERSIZE
)braket
suffix:semicolon
multiline_comment|/* obtained by REQUEST SENSE&n;&t;&t;&t;&t;&t;&t; * when CHECK CONDITION is&n;&t;&t;&t;&t;&t;&t; * received on original command &n;&t;&t;&t;&t;&t;&t; * (auto-sense) */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* Low-level done function - can be used by low-level driver to point&n;&t; *        to completion function.  Not used by mid/upper level code. */
DECL|member|scsi_done
r_void
(paren
op_star
id|scsi_done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The following fields can be written to by the host specific code. &n;&t; * Everything else should be left alone. &n;&t; */
DECL|member|SCp
r_struct
id|scsi_pointer
id|SCp
suffix:semicolon
multiline_comment|/* Scratchpad used by some host adapters */
DECL|member|host_scribble
r_int
r_char
op_star
id|host_scribble
suffix:semicolon
multiline_comment|/* The host adapter is allowed to&n;&t;&t;&t;&t;&t;   * call scsi_malloc and get some memory&n;&t;&t;&t;&t;&t;   * and hang it here.     The host adapter&n;&t;&t;&t;&t;&t;   * is also expected to call scsi_free&n;&t;&t;&t;&t;&t;   * to release this memory.  (The memory&n;&t;&t;&t;&t;&t;   * obtained by scsi_malloc is guaranteed&n;&t;&t;&t;&t;&t;   * to be at an address &lt; 16Mb). */
DECL|member|result
r_int
id|result
suffix:semicolon
multiline_comment|/* Status code from lower level driver */
DECL|member|tag
r_int
r_char
id|tag
suffix:semicolon
multiline_comment|/* SCSI-II queued command tag */
DECL|member|pid
r_int
r_int
id|pid
suffix:semicolon
multiline_comment|/* Process ID, starts at 0 */
)brace
suffix:semicolon
multiline_comment|/*&n; * These are the values that scsi_cmd-&gt;state can take.&n; */
DECL|macro|SCSI_STATE_TIMEOUT
mdefine_line|#define SCSI_STATE_TIMEOUT         0x1000
DECL|macro|SCSI_STATE_FINISHED
mdefine_line|#define SCSI_STATE_FINISHED        0x1001
DECL|macro|SCSI_STATE_FAILED
mdefine_line|#define SCSI_STATE_FAILED          0x1002
DECL|macro|SCSI_STATE_QUEUED
mdefine_line|#define SCSI_STATE_QUEUED          0x1003
DECL|macro|SCSI_STATE_UNUSED
mdefine_line|#define SCSI_STATE_UNUSED          0x1006
DECL|macro|SCSI_STATE_DISCONNECTING
mdefine_line|#define SCSI_STATE_DISCONNECTING   0x1008
DECL|macro|SCSI_STATE_INITIALIZING
mdefine_line|#define SCSI_STATE_INITIALIZING    0x1009
DECL|macro|SCSI_STATE_BHQUEUE
mdefine_line|#define SCSI_STATE_BHQUEUE         0x100a
DECL|macro|SCSI_STATE_MLQUEUE
mdefine_line|#define SCSI_STATE_MLQUEUE         0x100b
r_extern
r_struct
id|scsi_cmnd
op_star
id|scsi_get_command
c_func
(paren
r_struct
id|scsi_device
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|scsi_put_command
c_func
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_io_completion
c_func
(paren
r_struct
id|scsi_cmnd
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* _SCSI_SCSI_CMND_H */
eof

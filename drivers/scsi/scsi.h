multiline_comment|/*&n; *  scsi.h Copyright (C) 1992 Drew Eckhardt &n; *         Copyright (C) 1993, 1994, 1995, 1998, 1999 Eric Youngdale&n; *  generic SCSI package header file by&n; *      Initial versions: Drew Eckhardt&n; *      Subsequent revisions: Eric Youngdale&n; *&n; *  &lt;drew@colorado.edu&gt;&n; *&n; *       Modified by Eric Youngdale eric@andante.org to&n; *       add scatter-gather, multiple outstanding request, and other&n; *       enhancements.&n; */
macro_line|#ifndef _SCSI_H
DECL|macro|_SCSI_H
mdefine_line|#define _SCSI_H
macro_line|#include &lt;linux/config.h&gt;&t;    /* for CONFIG_SCSI_LOGGING */
macro_line|#include &lt;scsi/scsi_cmnd.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi.h&gt;
multiline_comment|/*&n; * These are the values that the SCpnt-&gt;sc_data_direction and &n; * SRpnt-&gt;sr_data_direction can take.  These need to be set&n; * The SCSI_DATA_UNKNOWN value is essentially the default.&n; * In the event that the command creator didn&squot;t bother to&n; * set a value, you will see SCSI_DATA_UNKNOWN.&n; */
DECL|macro|SCSI_DATA_UNKNOWN
mdefine_line|#define SCSI_DATA_UNKNOWN       0
DECL|macro|SCSI_DATA_WRITE
mdefine_line|#define SCSI_DATA_WRITE         1
DECL|macro|SCSI_DATA_READ
mdefine_line|#define SCSI_DATA_READ          2
DECL|macro|SCSI_DATA_NONE
mdefine_line|#define SCSI_DATA_NONE          3
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#if ((SCSI_DATA_UNKNOWN == PCI_DMA_BIDIRECTIONAL) &amp;&amp; (SCSI_DATA_WRITE == PCI_DMA_TODEVICE) &amp;&amp; (SCSI_DATA_READ == PCI_DMA_FROMDEVICE) &amp;&amp; (SCSI_DATA_NONE == PCI_DMA_NONE))
DECL|macro|scsi_to_pci_dma_dir
mdefine_line|#define scsi_to_pci_dma_dir(scsi_dir)&t;((int)(scsi_dir))
macro_line|#else
DECL|function|scsi_to_pci_dma_dir
r_extern
id|__inline__
r_int
id|scsi_to_pci_dma_dir
c_func
(paren
r_int
r_char
id|scsi_dir
)paren
(brace
r_if
c_cond
(paren
id|scsi_dir
op_eq
id|SCSI_DATA_UNKNOWN
)paren
r_return
id|PCI_DMA_BIDIRECTIONAL
suffix:semicolon
r_if
c_cond
(paren
id|scsi_dir
op_eq
id|SCSI_DATA_WRITE
)paren
r_return
id|PCI_DMA_TODEVICE
suffix:semicolon
r_if
c_cond
(paren
id|scsi_dir
op_eq
id|SCSI_DATA_READ
)paren
r_return
id|PCI_DMA_FROMDEVICE
suffix:semicolon
r_return
id|PCI_DMA_NONE
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
macro_line|#if defined(CONFIG_SBUS) &amp;&amp; !defined(CONFIG_SUN3) &amp;&amp; !defined(CONFIG_SUN3X)
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#if ((SCSI_DATA_UNKNOWN == SBUS_DMA_BIDIRECTIONAL) &amp;&amp; (SCSI_DATA_WRITE == SBUS_DMA_TODEVICE) &amp;&amp; (SCSI_DATA_READ == SBUS_DMA_FROMDEVICE) &amp;&amp; (SCSI_DATA_NONE == SBUS_DMA_NONE))
DECL|macro|scsi_to_sbus_dma_dir
mdefine_line|#define scsi_to_sbus_dma_dir(scsi_dir)&t;((int)(scsi_dir))
macro_line|#else
DECL|function|scsi_to_sbus_dma_dir
r_extern
id|__inline__
r_int
id|scsi_to_sbus_dma_dir
c_func
(paren
r_int
r_char
id|scsi_dir
)paren
(brace
r_if
c_cond
(paren
id|scsi_dir
op_eq
id|SCSI_DATA_UNKNOWN
)paren
r_return
id|SBUS_DMA_BIDIRECTIONAL
suffix:semicolon
r_if
c_cond
(paren
id|scsi_dir
op_eq
id|SCSI_DATA_WRITE
)paren
r_return
id|SBUS_DMA_TODEVICE
suffix:semicolon
r_if
c_cond
(paren
id|scsi_dir
op_eq
id|SCSI_DATA_READ
)paren
r_return
id|SBUS_DMA_FROMDEVICE
suffix:semicolon
r_return
id|SBUS_DMA_NONE
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Some defs, in case these are not defined elsewhere.&n; */
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
DECL|macro|MAX_SCSI_DEVICE_CODE
mdefine_line|#define MAX_SCSI_DEVICE_CODE 14
r_extern
r_const
r_char
op_star
r_const
id|scsi_device_types
(braket
id|MAX_SCSI_DEVICE_CODE
)braket
suffix:semicolon
macro_line|#ifdef DEBUG
DECL|macro|SCSI_TIMEOUT
mdefine_line|#define SCSI_TIMEOUT (5*HZ)
macro_line|#else
DECL|macro|SCSI_TIMEOUT
mdefine_line|#define SCSI_TIMEOUT (2*HZ)
macro_line|#endif
multiline_comment|/*&n; *  Use these to separate status msg and our bytes&n; *&n; *  These are set by:&n; *&n; *      status byte = set from target device&n; *      msg_byte    = return status from host adapter itself.&n; *      host_byte   = set by low-level driver to indicate status.&n; *      driver_byte = set by mid-level.&n; */
DECL|macro|status_byte
mdefine_line|#define status_byte(result) (((result) &gt;&gt; 1) &amp; 0x1f)
DECL|macro|msg_byte
mdefine_line|#define msg_byte(result)    (((result) &gt;&gt; 8) &amp; 0xff)
DECL|macro|host_byte
mdefine_line|#define host_byte(result)   (((result) &gt;&gt; 16) &amp; 0xff)
DECL|macro|driver_byte
mdefine_line|#define driver_byte(result) (((result) &gt;&gt; 24) &amp; 0xff)
DECL|macro|suggestion
mdefine_line|#define suggestion(result)  (driver_byte(result) &amp; SUGGEST_MASK)
DECL|macro|sense_class
mdefine_line|#define sense_class(sense)  (((sense) &gt;&gt; 4) &amp; 0x7)
DECL|macro|sense_error
mdefine_line|#define sense_error(sense)  ((sense) &amp; 0xf)
DECL|macro|sense_valid
mdefine_line|#define sense_valid(sense)  ((sense) &amp; 0x80);
DECL|macro|NEEDS_RETRY
mdefine_line|#define NEEDS_RETRY     0x2001
DECL|macro|SUCCESS
mdefine_line|#define SUCCESS         0x2002
DECL|macro|FAILED
mdefine_line|#define FAILED          0x2003
DECL|macro|QUEUED
mdefine_line|#define QUEUED          0x2004
DECL|macro|SOFT_ERROR
mdefine_line|#define SOFT_ERROR      0x2005
DECL|macro|ADD_TO_MLQUEUE
mdefine_line|#define ADD_TO_MLQUEUE  0x2006
DECL|macro|IDENTIFY_BASE
mdefine_line|#define IDENTIFY_BASE       0x80
DECL|macro|IDENTIFY
mdefine_line|#define IDENTIFY(can_disconnect, lun)   (IDENTIFY_BASE |&bslash;&n;&t;&t;     ((can_disconnect) ?  0x40 : 0) |&bslash;&n;&t;&t;     ((lun) &amp; 0x07))
multiline_comment|/* host byte codes */
DECL|macro|DID_OK
mdefine_line|#define DID_OK          0x00&t;/* NO error                                */
DECL|macro|DID_NO_CONNECT
mdefine_line|#define DID_NO_CONNECT  0x01&t;/* Couldn&squot;t connect before timeout period  */
DECL|macro|DID_BUS_BUSY
mdefine_line|#define DID_BUS_BUSY    0x02&t;/* BUS stayed busy through time out period */
DECL|macro|DID_TIME_OUT
mdefine_line|#define DID_TIME_OUT    0x03&t;/* TIMED OUT for other reason              */
DECL|macro|DID_BAD_TARGET
mdefine_line|#define DID_BAD_TARGET  0x04&t;/* BAD target.                             */
DECL|macro|DID_ABORT
mdefine_line|#define DID_ABORT       0x05&t;/* Told to abort for some other reason     */
DECL|macro|DID_PARITY
mdefine_line|#define DID_PARITY      0x06&t;/* Parity error                            */
DECL|macro|DID_ERROR
mdefine_line|#define DID_ERROR       0x07&t;/* Internal error                          */
DECL|macro|DID_RESET
mdefine_line|#define DID_RESET       0x08&t;/* Reset by somebody.                      */
DECL|macro|DID_BAD_INTR
mdefine_line|#define DID_BAD_INTR    0x09&t;/* Got an interrupt we weren&squot;t expecting.  */
DECL|macro|DID_PASSTHROUGH
mdefine_line|#define DID_PASSTHROUGH 0x0a&t;/* Force command past mid-layer            */
DECL|macro|DID_SOFT_ERROR
mdefine_line|#define DID_SOFT_ERROR  0x0b&t;/* The low level driver just wish a retry  */
DECL|macro|DRIVER_OK
mdefine_line|#define DRIVER_OK       0x00&t;/* Driver status                           */
multiline_comment|/*&n; *  These indicate the error that occurred, and what is available.&n; */
DECL|macro|DRIVER_BUSY
mdefine_line|#define DRIVER_BUSY         0x01
DECL|macro|DRIVER_SOFT
mdefine_line|#define DRIVER_SOFT         0x02
DECL|macro|DRIVER_MEDIA
mdefine_line|#define DRIVER_MEDIA        0x03
DECL|macro|DRIVER_ERROR
mdefine_line|#define DRIVER_ERROR        0x04
DECL|macro|DRIVER_INVALID
mdefine_line|#define DRIVER_INVALID      0x05
DECL|macro|DRIVER_TIMEOUT
mdefine_line|#define DRIVER_TIMEOUT      0x06
DECL|macro|DRIVER_HARD
mdefine_line|#define DRIVER_HARD         0x07
DECL|macro|DRIVER_SENSE
mdefine_line|#define DRIVER_SENSE&t;    0x08
DECL|macro|SUGGEST_RETRY
mdefine_line|#define SUGGEST_RETRY       0x10
DECL|macro|SUGGEST_ABORT
mdefine_line|#define SUGGEST_ABORT       0x20
DECL|macro|SUGGEST_REMAP
mdefine_line|#define SUGGEST_REMAP       0x30
DECL|macro|SUGGEST_DIE
mdefine_line|#define SUGGEST_DIE         0x40
DECL|macro|SUGGEST_SENSE
mdefine_line|#define SUGGEST_SENSE       0x80
DECL|macro|SUGGEST_IS_OK
mdefine_line|#define SUGGEST_IS_OK       0xff
DECL|macro|DRIVER_MASK
mdefine_line|#define DRIVER_MASK         0x0f
DECL|macro|SUGGEST_MASK
mdefine_line|#define SUGGEST_MASK        0xf0
multiline_comment|/*&n; *  SCSI command sets&n; */
DECL|macro|SCSI_UNKNOWN
mdefine_line|#define SCSI_UNKNOWN    0
DECL|macro|SCSI_1
mdefine_line|#define SCSI_1          1
DECL|macro|SCSI_1_CCS
mdefine_line|#define SCSI_1_CCS      2
DECL|macro|SCSI_2
mdefine_line|#define SCSI_2          3
DECL|macro|SCSI_3
mdefine_line|#define SCSI_3          4
multiline_comment|/*&n; *  Every SCSI command starts with a one byte OP-code.&n; *  The next byte&squot;s high three bits are the LUN of the&n; *  device.  Any multi-byte quantities are stored high byte&n; *  first, and may have a 5 bit MSB in the same byte&n; *  as the LUN.&n; */
multiline_comment|/*&n; *  As the scsi do command functions are intelligent, and may need to&n; *  redo a command, we need to keep track of the last command&n; *  executed on each one.&n; */
DECL|macro|WAS_RESET
mdefine_line|#define WAS_RESET       0x01
DECL|macro|WAS_TIMEDOUT
mdefine_line|#define WAS_TIMEDOUT    0x02
DECL|macro|WAS_SENSE
mdefine_line|#define WAS_SENSE       0x04
DECL|macro|IS_RESETTING
mdefine_line|#define IS_RESETTING    0x08
DECL|macro|IS_ABORTING
mdefine_line|#define IS_ABORTING     0x10
DECL|macro|ASKED_FOR_SENSE
mdefine_line|#define ASKED_FOR_SENSE 0x20
DECL|macro|SYNC_RESET
mdefine_line|#define SYNC_RESET      0x40
r_struct
id|Scsi_Host
suffix:semicolon
r_struct
id|scsi_cmnd
suffix:semicolon
r_struct
id|scsi_device
suffix:semicolon
r_struct
id|scsi_target
suffix:semicolon
r_struct
id|scatterlist
suffix:semicolon
multiline_comment|/*&n; * These are the error handling functions defined in scsi_error.c&n; */
r_extern
r_void
id|scsi_add_timer
c_func
(paren
r_struct
id|scsi_cmnd
op_star
comma
r_int
comma
r_void
(paren
op_star
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|scsi_delete_timer
c_func
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_block_when_processing_errors
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_sleep
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Prototypes for functions in scsicam.c&n; */
r_extern
r_int
id|scsi_partsize
c_func
(paren
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|capacity
comma
r_int
r_int
op_star
id|cyls
comma
r_int
r_int
op_star
id|hds
comma
r_int
r_int
op_star
id|secs
)paren
suffix:semicolon
multiline_comment|/*&n; * Newer request-based interfaces.&n; */
r_extern
r_struct
id|scsi_request
op_star
id|scsi_allocate_request
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_release_request
c_func
(paren
r_struct
id|scsi_request
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_wait_req
c_func
(paren
r_struct
id|scsi_request
op_star
comma
r_const
r_void
op_star
id|cmnd
comma
r_void
op_star
id|buffer
comma
r_int
id|bufflen
comma
r_int
id|timeout
comma
r_int
id|retries
)paren
suffix:semicolon
r_extern
r_void
id|scsi_do_req
c_func
(paren
r_struct
id|scsi_request
op_star
comma
r_const
r_void
op_star
id|cmnd
comma
r_void
op_star
id|buffer
comma
r_int
id|bufflen
comma
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
comma
r_int
id|timeout
comma
r_int
id|retries
)paren
suffix:semicolon
multiline_comment|/*&n; * Prototypes for functions in constants.c&n; * Some of these used to live in constants.h&n; */
r_extern
r_void
id|print_Scsi_Cmnd
c_func
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
r_extern
r_void
id|print_command
c_func
(paren
r_int
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|print_sense
c_func
(paren
r_const
r_char
op_star
comma
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
r_extern
r_void
id|print_req_sense
c_func
(paren
r_const
r_char
op_star
comma
r_struct
id|scsi_request
op_star
)paren
suffix:semicolon
r_extern
r_void
id|print_driverbyte
c_func
(paren
r_int
id|scsiresult
)paren
suffix:semicolon
r_extern
r_void
id|print_hostbyte
c_func
(paren
r_int
id|scsiresult
)paren
suffix:semicolon
r_extern
r_void
id|print_status
c_func
(paren
r_int
r_char
id|status
)paren
suffix:semicolon
r_extern
r_int
id|print_msg
c_func
(paren
r_const
r_int
r_char
op_star
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|scsi_sense_key_string
c_func
(paren
r_int
r_char
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|scsi_extd_sense_format
c_func
(paren
r_int
r_char
comma
r_int
r_char
)paren
suffix:semicolon
multiline_comment|/*&n; * This is essentially a slimmed down version of Scsi_Cmnd.  The point of&n; * having this is that requests that are injected into the queue as result&n; * of things like ioctls and character devices shouldn&squot;t be using a&n; * Scsi_Cmnd until such a time that the command is actually at the head&n; * of the queue and being sent to the driver.&n; */
DECL|struct|scsi_request
r_struct
id|scsi_request
(brace
DECL|member|sr_magic
r_int
id|sr_magic
suffix:semicolon
DECL|member|sr_result
r_int
id|sr_result
suffix:semicolon
multiline_comment|/* Status code from lower level driver */
DECL|member|sr_sense_buffer
r_int
r_char
id|sr_sense_buffer
(braket
id|SCSI_SENSE_BUFFERSIZE
)braket
suffix:semicolon
multiline_comment|/* obtained by REQUEST SENSE&n;&t;&t;&t;&t;&t;&t; * when CHECK CONDITION is&n;&t;&t;&t;&t;&t;&t; * received on original command &n;&t;&t;&t;&t;&t;&t; * (auto-sense) */
DECL|member|sr_host
r_struct
id|Scsi_Host
op_star
id|sr_host
suffix:semicolon
DECL|member|sr_device
r_struct
id|scsi_device
op_star
id|sr_device
suffix:semicolon
DECL|member|sr_command
r_struct
id|scsi_cmnd
op_star
id|sr_command
suffix:semicolon
DECL|member|sr_request
r_struct
id|request
op_star
id|sr_request
suffix:semicolon
multiline_comment|/* A copy of the command we are&n;&t;&t;&t;&t;   working on */
DECL|member|sr_bufflen
r_int
id|sr_bufflen
suffix:semicolon
multiline_comment|/* Size of data buffer */
DECL|member|sr_buffer
r_void
op_star
id|sr_buffer
suffix:semicolon
multiline_comment|/* Data buffer */
DECL|member|sr_allowed
r_int
id|sr_allowed
suffix:semicolon
DECL|member|sr_data_direction
r_int
r_char
id|sr_data_direction
suffix:semicolon
DECL|member|sr_cmd_len
r_int
r_char
id|sr_cmd_len
suffix:semicolon
DECL|member|sr_cmnd
r_int
r_char
id|sr_cmnd
(braket
id|MAX_COMMAND_SIZE
)braket
suffix:semicolon
DECL|member|sr_done
r_void
(paren
op_star
id|sr_done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/* Mid-level done function */
DECL|member|sr_timeout_per_command
r_int
id|sr_timeout_per_command
suffix:semicolon
DECL|member|sr_use_sg
r_int
r_int
id|sr_use_sg
suffix:semicolon
multiline_comment|/* Number of pieces of scatter-gather */
DECL|member|sr_sglist_len
r_int
r_int
id|sr_sglist_len
suffix:semicolon
multiline_comment|/* size of malloc&squot;d scatter-gather list */
DECL|member|sr_underflow
r_int
id|sr_underflow
suffix:semicolon
multiline_comment|/* Return error if less than&n;&t;&t;&t;&t;   this amount is transferred */
DECL|member|upper_private_data
r_void
op_star
id|upper_private_data
suffix:semicolon
multiline_comment|/* reserved for owner (usually upper&n; &t;&t;&t;&t;&t;   level driver) of this request */
)brace
suffix:semicolon
multiline_comment|/*&n; * Definitions and prototypes used for scsi mid-level queue.&n; */
DECL|macro|SCSI_MLQUEUE_HOST_BUSY
mdefine_line|#define SCSI_MLQUEUE_HOST_BUSY   0x1055
DECL|macro|SCSI_MLQUEUE_DEVICE_BUSY
mdefine_line|#define SCSI_MLQUEUE_DEVICE_BUSY 0x1056
DECL|macro|SCSI_MLQUEUE_EH_RETRY
mdefine_line|#define SCSI_MLQUEUE_EH_RETRY    0x1057
multiline_comment|/*&n; * Reset request from external source&n; */
DECL|macro|SCSI_TRY_RESET_DEVICE
mdefine_line|#define SCSI_TRY_RESET_DEVICE&t;1
DECL|macro|SCSI_TRY_RESET_BUS
mdefine_line|#define SCSI_TRY_RESET_BUS&t;2
DECL|macro|SCSI_TRY_RESET_HOST
mdefine_line|#define SCSI_TRY_RESET_HOST&t;3
r_extern
r_int
id|scsi_reset_provider
c_func
(paren
r_struct
id|scsi_device
op_star
comma
r_int
)paren
suffix:semicolon
DECL|macro|MSG_SIMPLE_TAG
mdefine_line|#define MSG_SIMPLE_TAG&t;0x20
DECL|macro|MSG_HEAD_TAG
mdefine_line|#define MSG_HEAD_TAG&t;0x21
DECL|macro|MSG_ORDERED_TAG
mdefine_line|#define MSG_ORDERED_TAG&t;0x22
DECL|macro|SCSI_NO_TAG
mdefine_line|#define SCSI_NO_TAG&t;(-1)    /* identify no tag in use */
multiline_comment|/**&n; * scsi_activate_tcq - turn on tag command queueing&n; * @SDpnt:&t;device to turn on TCQ for&n; * @depth:&t;queue depth&n; *&n; * Notes:&n; *&t;Eventually, I hope depth would be the maximum depth&n; *&t;the device could cope with and the real queue depth&n; *&t;would be adjustable from 0 to depth.&n; **/
DECL|function|scsi_activate_tcq
r_static
r_inline
r_void
id|scsi_activate_tcq
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_int
id|depth
)paren
(brace
r_if
c_cond
(paren
id|sdev-&gt;tagged_supported
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|blk_queue_tagged
c_func
(paren
id|sdev-&gt;request_queue
)paren
)paren
id|blk_queue_init_tags
c_func
(paren
id|sdev-&gt;request_queue
comma
id|depth
)paren
suffix:semicolon
id|scsi_adjust_queue_depth
c_func
(paren
id|sdev
comma
id|MSG_ORDERED_TAG
comma
id|depth
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * scsi_deactivate_tcq - turn off tag command queueing&n; * @SDpnt:&t;device to turn off TCQ for&n; **/
DECL|function|scsi_deactivate_tcq
r_static
r_inline
r_void
id|scsi_deactivate_tcq
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_int
id|depth
)paren
(brace
r_if
c_cond
(paren
id|blk_queue_tagged
c_func
(paren
id|sdev-&gt;request_queue
)paren
)paren
id|blk_queue_free_tags
c_func
(paren
id|sdev-&gt;request_queue
)paren
suffix:semicolon
id|scsi_adjust_queue_depth
c_func
(paren
id|sdev
comma
l_int|0
comma
id|depth
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_populate_tag_msg - place a tag message in a buffer&n; * @SCpnt:&t;pointer to the Scsi_Cmnd for the tag&n; * @msg:&t;pointer to the area to place the tag&n; *&n; * Notes:&n; *&t;designed to create the correct type of tag message for the &n; *&t;particular request.  Returns the size of the tag message.&n; *&t;May return 0 if TCQ is disabled for this device.&n; **/
DECL|function|scsi_populate_tag_msg
r_static
r_inline
r_int
id|scsi_populate_tag_msg
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
comma
r_char
op_star
id|msg
)paren
(brace
r_struct
id|request
op_star
id|req
op_assign
id|cmd-&gt;request
suffix:semicolon
r_if
c_cond
(paren
id|blk_rq_tagged
c_func
(paren
id|req
)paren
)paren
(brace
r_if
c_cond
(paren
id|req-&gt;flags
op_amp
id|REQ_HARDBARRIER
)paren
op_star
id|msg
op_increment
op_assign
id|MSG_ORDERED_TAG
suffix:semicolon
r_else
op_star
id|msg
op_increment
op_assign
id|MSG_SIMPLE_TAG
suffix:semicolon
op_star
id|msg
op_increment
op_assign
id|req-&gt;tag
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_find_tag - find a tagged command by device&n; * @SDpnt:&t;pointer to the ScSI device&n; * @tag:&t;the tag number&n; *&n; * Notes:&n; *&t;Only works with tags allocated by the generic blk layer.&n; **/
DECL|function|scsi_find_tag
r_static
r_inline
r_struct
id|scsi_cmnd
op_star
id|scsi_find_tag
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_int
id|tag
)paren
(brace
r_struct
id|request
op_star
id|req
suffix:semicolon
r_if
c_cond
(paren
id|tag
op_ne
id|SCSI_NO_TAG
)paren
(brace
id|req
op_assign
id|blk_queue_find_tag
c_func
(paren
id|sdev-&gt;request_queue
comma
id|tag
)paren
suffix:semicolon
r_return
id|req
ques
c_cond
(paren
r_struct
id|scsi_cmnd
op_star
)paren
id|req-&gt;special
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* single command, look in space */
r_return
id|sdev-&gt;current_cmnd
suffix:semicolon
)brace
r_extern
r_int
id|scsi_sysfs_modify_sdev_attribute
c_func
(paren
r_struct
id|device_attribute
op_star
op_star
op_star
id|dev_attrs
comma
r_struct
id|device_attribute
op_star
id|attr
)paren
suffix:semicolon
r_extern
r_int
id|scsi_sysfs_modify_shost_attribute
c_func
(paren
r_struct
id|class_device_attribute
op_star
op_star
op_star
id|class_attrs
comma
r_struct
id|class_device_attribute
op_star
id|attr
)paren
suffix:semicolon
multiline_comment|/*&n; * This is the crap from the old error handling code.  We have it in a special&n; * place so that we can more easily delete it later on.&n; */
macro_line|#include &quot;scsi_obsolete.h&quot;
multiline_comment|/* obsolete typedef junk. */
macro_line|#include &quot;scsi_typedefs.h&quot;
macro_line|#endif /* _SCSI_H */
eof

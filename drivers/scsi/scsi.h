multiline_comment|/*&n; *  scsi.h Copyright (C) 1992 Drew Eckhardt &n; *         Copyright (C) 1993, 1994, 1995, 1998, 1999 Eric Youngdale&n; *  generic SCSI package header file by&n; *      Initial versions: Drew Eckhardt&n; *      Subsequent revisions: Eric Youngdale&n; *&n; *  &lt;drew@colorado.edu&gt;&n; *&n; *       Modified by Eric Youngdale eric@andante.org to&n; *       add scatter-gather, multiple outstanding request, and other&n; *       enhancements.&n; */
macro_line|#ifndef _SCSI_H
DECL|macro|_SCSI_H
mdefine_line|#define _SCSI_H
macro_line|#include &lt;linux/config.h&gt;&t;    /* for CONFIG_SCSI_LOGGING */
macro_line|#include &lt;scsi/scsi_cmnd.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi_eh.h&gt;
macro_line|#include &lt;scsi/scsi_request.h&gt;
macro_line|#include &lt;scsi/scsi_tcq.h&gt;
macro_line|#include &lt;scsi/scsi.h&gt;
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
multiline_comment|/*&n; * Definitions and prototypes used for scsi mid-level queue.&n; */
DECL|macro|SCSI_MLQUEUE_HOST_BUSY
mdefine_line|#define SCSI_MLQUEUE_HOST_BUSY   0x1055
DECL|macro|SCSI_MLQUEUE_DEVICE_BUSY
mdefine_line|#define SCSI_MLQUEUE_DEVICE_BUSY 0x1056
DECL|macro|SCSI_MLQUEUE_EH_RETRY
mdefine_line|#define SCSI_MLQUEUE_EH_RETRY    0x1057
multiline_comment|/*&n; * Legacy dma direction interfaces.&n; *&n; * This assumes the pci/sbus dma mapping flags have the same numercial&n; * values as the generic dma-mapping ones.  Currently they have but there&squot;s&n; * no way to check.  Better don&squot;t use these interfaces!&n; */
DECL|macro|SCSI_DATA_UNKNOWN
mdefine_line|#define SCSI_DATA_UNKNOWN&t;(DMA_BIDIRECTIONAL)
DECL|macro|SCSI_DATA_WRITE
mdefine_line|#define SCSI_DATA_WRITE&t;&t;(DMA_TO_DEVICE)
DECL|macro|SCSI_DATA_READ
mdefine_line|#define SCSI_DATA_READ&t;&t;(DMA_FROM_DEVICE)
DECL|macro|SCSI_DATA_NONE
mdefine_line|#define SCSI_DATA_NONE&t;&t;(DMA_NONE)
DECL|macro|scsi_to_pci_dma_dir
mdefine_line|#define scsi_to_pci_dma_dir(scsi_dir)&t;((int)(scsi_dir))
DECL|macro|scsi_to_sbus_dma_dir
mdefine_line|#define scsi_to_sbus_dma_dir(scsi_dir)&t;((int)(scsi_dir))
multiline_comment|/*&n; * This is the crap from the old error handling code.  We have it in a special&n; * place so that we can more easily delete it later on.&n; */
macro_line|#include &quot;scsi_obsolete.h&quot;
multiline_comment|/* obsolete typedef junk. */
macro_line|#include &quot;scsi_typedefs.h&quot;
macro_line|#endif /* _SCSI_H */
eof

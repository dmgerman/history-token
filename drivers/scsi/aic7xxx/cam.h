multiline_comment|/*&n; * Data structures and definitions for the CAM system.&n; *&n; * Copyright (c) 1997 Justin T. Gibbs.&n; * Copyright (c) 2000 Adaptec Inc.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; * $Id: //depot/aic7xxx/linux/drivers/scsi/aic7xxx/cam.h#15 $&n; */
macro_line|#ifndef _AIC7XXX_CAM_H
DECL|macro|_AIC7XXX_CAM_H
mdefine_line|#define _AIC7XXX_CAM_H 1
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|CAM_BUS_WILDCARD
mdefine_line|#define&t;CAM_BUS_WILDCARD ((u_int)~0)
DECL|macro|CAM_TARGET_WILDCARD
mdefine_line|#define&t;CAM_TARGET_WILDCARD ((u_int)~0)
DECL|macro|CAM_LUN_WILDCARD
mdefine_line|#define&t;CAM_LUN_WILDCARD ((u_int)~0)
multiline_comment|/* CAM Status field values */
r_typedef
r_enum
(brace
DECL|enumerator|CAM_REQ_INPROG
id|CAM_REQ_INPROG
comma
multiline_comment|/* CCB request is in progress */
DECL|enumerator|CAM_REQ_CMP
id|CAM_REQ_CMP
comma
multiline_comment|/* CCB request completed without error */
DECL|enumerator|CAM_REQ_ABORTED
id|CAM_REQ_ABORTED
comma
multiline_comment|/* CCB request aborted by the host */
DECL|enumerator|CAM_UA_ABORT
id|CAM_UA_ABORT
comma
multiline_comment|/* Unable to abort CCB request */
DECL|enumerator|CAM_REQ_CMP_ERR
id|CAM_REQ_CMP_ERR
comma
multiline_comment|/* CCB request completed with an error */
DECL|enumerator|CAM_BUSY
id|CAM_BUSY
comma
multiline_comment|/* CAM subsytem is busy */
DECL|enumerator|CAM_REQ_INVALID
id|CAM_REQ_INVALID
comma
multiline_comment|/* CCB request was invalid */
DECL|enumerator|CAM_PATH_INVALID
id|CAM_PATH_INVALID
comma
multiline_comment|/* Supplied Path ID is invalid */
DECL|enumerator|CAM_SEL_TIMEOUT
id|CAM_SEL_TIMEOUT
comma
multiline_comment|/* Target Selection Timeout */
DECL|enumerator|CAM_CMD_TIMEOUT
id|CAM_CMD_TIMEOUT
comma
multiline_comment|/* Command timeout */
DECL|enumerator|CAM_SCSI_STATUS_ERROR
id|CAM_SCSI_STATUS_ERROR
comma
multiline_comment|/* SCSI error, look at error code in CCB */
DECL|enumerator|CAM_SCSI_BUS_RESET
id|CAM_SCSI_BUS_RESET
comma
multiline_comment|/* SCSI Bus Reset Sent/Received */
DECL|enumerator|CAM_UNCOR_PARITY
id|CAM_UNCOR_PARITY
comma
multiline_comment|/* Uncorrectable parity error occurred */
DECL|enumerator|CAM_AUTOSENSE_FAIL
id|CAM_AUTOSENSE_FAIL
comma
multiline_comment|/* Autosense: request sense cmd fail */
DECL|enumerator|CAM_NO_HBA
id|CAM_NO_HBA
comma
multiline_comment|/* No HBA Detected Error */
DECL|enumerator|CAM_DATA_RUN_ERR
id|CAM_DATA_RUN_ERR
comma
multiline_comment|/* Data Overrun error */
DECL|enumerator|CAM_UNEXP_BUSFREE
id|CAM_UNEXP_BUSFREE
comma
multiline_comment|/* Unexpected Bus Free */
DECL|enumerator|CAM_SEQUENCE_FAIL
id|CAM_SEQUENCE_FAIL
comma
multiline_comment|/* Protocol Violation */
DECL|enumerator|CAM_CCB_LEN_ERR
id|CAM_CCB_LEN_ERR
comma
multiline_comment|/* CCB length supplied is inadequate */
DECL|enumerator|CAM_PROVIDE_FAIL
id|CAM_PROVIDE_FAIL
comma
multiline_comment|/* Unable to provide requested capability */
DECL|enumerator|CAM_BDR_SENT
id|CAM_BDR_SENT
comma
multiline_comment|/* A SCSI BDR msg was sent to target */
DECL|enumerator|CAM_REQ_TERMIO
id|CAM_REQ_TERMIO
comma
multiline_comment|/* CCB request terminated by the host */
DECL|enumerator|CAM_UNREC_HBA_ERROR
id|CAM_UNREC_HBA_ERROR
comma
multiline_comment|/* Unrecoverable Host Bus Adapter Error */
DECL|enumerator|CAM_REQ_TOO_BIG
id|CAM_REQ_TOO_BIG
comma
multiline_comment|/* The request was too large for this host */
DECL|enumerator|CAM_UA_TERMIO
id|CAM_UA_TERMIO
comma
multiline_comment|/* Unable to terminate I/O CCB request */
DECL|enumerator|CAM_MSG_REJECT_REC
id|CAM_MSG_REJECT_REC
comma
multiline_comment|/* Message Reject Received */
DECL|enumerator|CAM_DEV_NOT_THERE
id|CAM_DEV_NOT_THERE
comma
multiline_comment|/* SCSI Device Not Installed/there */
DECL|enumerator|CAM_RESRC_UNAVAIL
id|CAM_RESRC_UNAVAIL
comma
multiline_comment|/* Resource Unavailable */
multiline_comment|/*&n;&t; * This request should be requeued to preserve&n;&t; * transaction ordering.  This typically occurs&n;&t; * when the SIM recognizes an error that should&n;&t; * freeze the queue and must place additional&n;&t; * requests for the target at the sim level&n;&t; * back into the XPT queue.&n;&t; */
DECL|enumerator|CAM_REQUEUE_REQ
id|CAM_REQUEUE_REQ
comma
DECL|enumerator|CAM_DEV_QFRZN
id|CAM_DEV_QFRZN
op_assign
l_int|0x40
comma
DECL|enumerator|CAM_STATUS_MASK
id|CAM_STATUS_MASK
op_assign
l_int|0x3F
DECL|typedef|cam_status
)brace
id|cam_status
suffix:semicolon
multiline_comment|/*&n; * Definitions for the asynchronous callback CCB fields.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|AC_GETDEV_CHANGED
id|AC_GETDEV_CHANGED
op_assign
l_int|0x800
comma
multiline_comment|/* Getdev info might have changed */
DECL|enumerator|AC_INQ_CHANGED
id|AC_INQ_CHANGED
op_assign
l_int|0x400
comma
multiline_comment|/* Inquiry info might have changed */
DECL|enumerator|AC_TRANSFER_NEG
id|AC_TRANSFER_NEG
op_assign
l_int|0x200
comma
multiline_comment|/* New transfer settings in effect */
DECL|enumerator|AC_LOST_DEVICE
id|AC_LOST_DEVICE
op_assign
l_int|0x100
comma
multiline_comment|/* A device went away */
DECL|enumerator|AC_FOUND_DEVICE
id|AC_FOUND_DEVICE
op_assign
l_int|0x080
comma
multiline_comment|/* A new device was found */
DECL|enumerator|AC_PATH_DEREGISTERED
id|AC_PATH_DEREGISTERED
op_assign
l_int|0x040
comma
multiline_comment|/* A path has de-registered */
DECL|enumerator|AC_PATH_REGISTERED
id|AC_PATH_REGISTERED
op_assign
l_int|0x020
comma
multiline_comment|/* A new path has been registered */
DECL|enumerator|AC_SENT_BDR
id|AC_SENT_BDR
op_assign
l_int|0x010
comma
multiline_comment|/* A BDR message was sent to target */
DECL|enumerator|AC_SCSI_AEN
id|AC_SCSI_AEN
op_assign
l_int|0x008
comma
multiline_comment|/* A SCSI AEN has been received */
DECL|enumerator|AC_UNSOL_RESEL
id|AC_UNSOL_RESEL
op_assign
l_int|0x002
comma
multiline_comment|/* Unsolicited reselection occurred */
DECL|enumerator|AC_BUS_RESET
id|AC_BUS_RESET
op_assign
l_int|0x001
multiline_comment|/* A SCSI bus reset occurred */
DECL|typedef|ac_code
)brace
id|ac_code
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|CAM_DIR_IN
id|CAM_DIR_IN
op_assign
id|SCSI_DATA_READ
comma
DECL|enumerator|CAM_DIR_OUT
id|CAM_DIR_OUT
op_assign
id|SCSI_DATA_WRITE
comma
DECL|enumerator|CAM_DIR_NONE
id|CAM_DIR_NONE
op_assign
id|SCSI_DATA_NONE
DECL|typedef|ccb_flags
)brace
id|ccb_flags
suffix:semicolon
macro_line|#endif /* _AIC7XXX_CAM_H */
eof

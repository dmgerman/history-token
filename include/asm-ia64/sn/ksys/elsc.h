multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997, 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; */
macro_line|#ifndef _ASM_SN_KSYS_ELSC_H
DECL|macro|_ASM_SN_KSYS_ELSC_H
mdefine_line|#define _ASM_SN_KSYS_ELSC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/ksys/l1.h&gt;
multiline_comment|/*&n; * Error codes&n; *&n; *   The possible ELSC error codes are a superset of the I2C error codes,&n; *   so ELSC error codes begin at -100.&n; */
DECL|macro|ELSC_ERROR_NONE
mdefine_line|#define ELSC_ERROR_NONE&t;&t;&t;0
DECL|macro|ELSC_ERROR_CMD_SEND
mdefine_line|#define ELSC_ERROR_CMD_SEND&t;       (-100)&t;/* Error sending command    */
DECL|macro|ELSC_ERROR_CMD_CHECKSUM
mdefine_line|#define ELSC_ERROR_CMD_CHECKSUM&t;       (-101)&t;/* Command checksum bad     */
DECL|macro|ELSC_ERROR_CMD_UNKNOWN
mdefine_line|#define ELSC_ERROR_CMD_UNKNOWN&t;       (-102)&t;/* Unknown command          */
DECL|macro|ELSC_ERROR_CMD_ARGS
mdefine_line|#define ELSC_ERROR_CMD_ARGS&t;       (-103)&t;/* Invalid argument(s)      */
DECL|macro|ELSC_ERROR_CMD_PERM
mdefine_line|#define ELSC_ERROR_CMD_PERM&t;       (-104)&t;/* Permission denied&t;    */
DECL|macro|ELSC_ERROR_CMD_STATE
mdefine_line|#define ELSC_ERROR_CMD_STATE&t;       (-105)&t;/* not allowed in this state*/
DECL|macro|ELSC_ERROR_RESP_TIMEOUT
mdefine_line|#define ELSC_ERROR_RESP_TIMEOUT&t;       (-110)&t;/* ELSC response timeout    */
DECL|macro|ELSC_ERROR_RESP_CHECKSUM
mdefine_line|#define ELSC_ERROR_RESP_CHECKSUM       (-111)&t;/* Response checksum bad    */
DECL|macro|ELSC_ERROR_RESP_FORMAT
mdefine_line|#define ELSC_ERROR_RESP_FORMAT&t;       (-112)&t;/* Response format error    */
DECL|macro|ELSC_ERROR_RESP_DIR
mdefine_line|#define ELSC_ERROR_RESP_DIR&t;       (-113)&t;/* Response direction error */
DECL|macro|ELSC_ERROR_MSG_LOST
mdefine_line|#define ELSC_ERROR_MSG_LOST&t;       (-120)&t;/* Queue full; msg. lost    */
DECL|macro|ELSC_ERROR_LOCK_TIMEOUT
mdefine_line|#define ELSC_ERROR_LOCK_TIMEOUT&t;       (-121)&t;/* ELSC response timeout    */
DECL|macro|ELSC_ERROR_DATA_SEND
mdefine_line|#define ELSC_ERROR_DATA_SEND&t;       (-122)&t;/* Error sending data       */
DECL|macro|ELSC_ERROR_NIC
mdefine_line|#define ELSC_ERROR_NIC&t;&t;       (-123)&t;/* NIC processing error     */
DECL|macro|ELSC_ERROR_NVMAGIC
mdefine_line|#define ELSC_ERROR_NVMAGIC&t;       (-124)&t;/* Bad magic no. in NVRAM   */
DECL|macro|ELSC_ERROR_MODULE
mdefine_line|#define ELSC_ERROR_MODULE&t;       (-125)&t;/* Moduleid processing err  */
macro_line|#endif /* _ASM_SN_KSYS_ELSC_H */
eof

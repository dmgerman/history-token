multiline_comment|/*      cops.h: LocalTalk driver for Linux.&n; *&n; *      Authors:&n; *      - Jay Schulist &lt;jschlst@samba.org&gt;&n; */
macro_line|#ifndef __LINUX_COPSLTALK_H
DECL|macro|__LINUX_COPSLTALK_H
mdefine_line|#define __LINUX_COPSLTALK_H
macro_line|#ifdef __KERNEL__
multiline_comment|/* Max LLAP size we will accept. */
DECL|macro|MAX_LLAP_SIZE
mdefine_line|#define MAX_LLAP_SIZE&t;&t;603
multiline_comment|/* Tangent */
DECL|macro|TANG_CARD_STATUS
mdefine_line|#define TANG_CARD_STATUS        1
DECL|macro|TANG_CLEAR_INT
mdefine_line|#define TANG_CLEAR_INT          1
DECL|macro|TANG_RESET
mdefine_line|#define TANG_RESET              3
DECL|macro|TANG_TX_READY
mdefine_line|#define TANG_TX_READY           1
DECL|macro|TANG_RX_READY
mdefine_line|#define TANG_RX_READY           2
multiline_comment|/* Dayna */
DECL|macro|DAYNA_CMD_DATA
mdefine_line|#define DAYNA_CMD_DATA          0
DECL|macro|DAYNA_CLEAR_INT
mdefine_line|#define DAYNA_CLEAR_INT         1
DECL|macro|DAYNA_CARD_STATUS
mdefine_line|#define DAYNA_CARD_STATUS       2
DECL|macro|DAYNA_INT_CARD
mdefine_line|#define DAYNA_INT_CARD          3
DECL|macro|DAYNA_RESET
mdefine_line|#define DAYNA_RESET             4
DECL|macro|DAYNA_RX_READY
mdefine_line|#define DAYNA_RX_READY          0
DECL|macro|DAYNA_TX_READY
mdefine_line|#define DAYNA_TX_READY          1
DECL|macro|DAYNA_RX_REQUEST
mdefine_line|#define DAYNA_RX_REQUEST        3
multiline_comment|/* Same on both card types */
DECL|macro|COPS_CLEAR_INT
mdefine_line|#define COPS_CLEAR_INT  1
multiline_comment|/* LAP response codes received from the cards. */
DECL|macro|LAP_INIT
mdefine_line|#define LAP_INIT        1       /* Init cmd */
DECL|macro|LAP_INIT_RSP
mdefine_line|#define LAP_INIT_RSP    2       /* Init response */
DECL|macro|LAP_WRITE
mdefine_line|#define LAP_WRITE       3       /* Write cmd */
DECL|macro|DATA_READ
mdefine_line|#define DATA_READ       4       /* Data read */
DECL|macro|LAP_RESPONSE
mdefine_line|#define LAP_RESPONSE    4       /* Received ALAP frame response */
DECL|macro|LAP_GETSTAT
mdefine_line|#define LAP_GETSTAT     5       /* Get LAP and HW status */
DECL|macro|LAP_RSPSTAT
mdefine_line|#define LAP_RSPSTAT     6       /* Status response */
macro_line|#endif
multiline_comment|/*&n; *&t;Structure to hold the firmware information.&n; */
DECL|struct|ltfirmware
r_struct
id|ltfirmware
(brace
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DAYNA
mdefine_line|#define DAYNA 1
DECL|macro|TANGENT
mdefine_line|#define TANGENT 2
macro_line|#endif
eof

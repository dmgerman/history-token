multiline_comment|/*&n; * Definitions for XScale 80312 PMON&n; * (C) 2001 Intel Corporation&n; * Author: Chen Chen(chen.chen@intel.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _IOP310_PMON_H_
DECL|macro|_IOP310_PMON_H_
mdefine_line|#define _IOP310_PMON_H_
multiline_comment|/*&n; *  Different modes for Event Select Register for intel 80312&n; */
DECL|macro|IOP310_PMON_MODE0
mdefine_line|#define IOP310_PMON_MODE0                0x00000000
DECL|macro|IOP310_PMON_MODE1
mdefine_line|#define IOP310_PMON_MODE1                0x00000001
DECL|macro|IOP310_PMON_MODE2
mdefine_line|#define IOP310_PMON_MODE2                0x00000002
DECL|macro|IOP310_PMON_MODE3
mdefine_line|#define IOP310_PMON_MODE3                0x00000003
DECL|macro|IOP310_PMON_MODE4
mdefine_line|#define IOP310_PMON_MODE4                0x00000004
DECL|macro|IOP310_PMON_MODE5
mdefine_line|#define IOP310_PMON_MODE5                0x00000005
DECL|macro|IOP310_PMON_MODE6
mdefine_line|#define IOP310_PMON_MODE6                0x00000006
DECL|macro|IOP310_PMON_MODE7
mdefine_line|#define IOP310_PMON_MODE7                0x00000007
DECL|struct|_iop310_pmon_result
r_typedef
r_struct
id|_iop310_pmon_result
(brace
DECL|member|timestamp
id|u32
id|timestamp
suffix:semicolon
multiline_comment|/* Global Time Stamp Register */
DECL|member|timestamp_overflow
id|u32
id|timestamp_overflow
suffix:semicolon
multiline_comment|/* Time Stamp overflow count */
DECL|member|event_count
id|u32
id|event_count
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* Programmable Event Counter&n;&t;&t;&t;&t;&t;   Registers 1-14 */
DECL|member|event_overflow
id|u32
id|event_overflow
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* Overflow counter for PECR1-14 */
DECL|typedef|iop310_pmon_res_t
)brace
id|iop310_pmon_res_t
suffix:semicolon
multiline_comment|/* function prototypes */
multiline_comment|/* Claim IQ80312 PMON for usage */
r_int
id|iop310_pmon_claim
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Start IQ80312 PMON */
r_int
id|iop310_pmon_start
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Stop Performance Monitor Unit */
r_int
id|iop310_pmon_stop
c_func
(paren
id|iop310_pmon_res_t
op_star
)paren
suffix:semicolon
multiline_comment|/* Release IQ80312 PMON */
r_int
id|iop310_pmon_release
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#endif
eof

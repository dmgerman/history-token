multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_KSYS_I2C_H
DECL|macro|_ASM_SN_KSYS_I2C_H
mdefine_line|#define _ASM_SN_KSYS_I2C_H
macro_line|#if _STANDALONE
macro_line|# include &quot;rtc.h&quot;
macro_line|#else
DECL|macro|rtc_time
macro_line|# define rtc_time()&t;(GET_LOCAL_RTC * NSEC_PER_CYCLE / 1000)
DECL|macro|rtc_sleep
macro_line|# define rtc_sleep&t;us_delay
DECL|macro|rtc_time_t
macro_line|# define rtc_time_t&t;uint64_t
macro_line|#endif
DECL|typedef|i2c_addr_t
r_typedef
id|u_char
id|i2c_addr_t
suffix:semicolon
multiline_comment|/* 7-bit address            */
r_int
id|i2c_init
c_func
(paren
id|nasid_t
)paren
suffix:semicolon
r_int
id|i2c_probe
c_func
(paren
id|nasid_t
id|nasid
comma
id|rtc_time_t
id|timeout
)paren
suffix:semicolon
r_int
id|i2c_arb
c_func
(paren
id|nasid_t
comma
id|rtc_time_t
id|timeout
comma
id|rtc_time_t
op_star
id|token_start
)paren
suffix:semicolon
r_int
id|i2c_master_xmit
c_func
(paren
id|nasid_t
comma
id|i2c_addr_t
id|addr
comma
id|u_char
op_star
id|buf
comma
r_int
id|len_max
comma
r_int
op_star
id|len_ptr
comma
id|rtc_time_t
id|timeout
comma
r_int
id|only_if_message
)paren
suffix:semicolon
r_int
id|i2c_master_recv
c_func
(paren
id|nasid_t
comma
id|i2c_addr_t
id|addr
comma
id|u_char
op_star
id|buf
comma
r_int
id|len_max
comma
r_int
op_star
id|len_ptr
comma
r_int
id|emblen
comma
id|rtc_time_t
id|timeout
comma
r_int
id|only_if_message
)paren
suffix:semicolon
r_int
id|i2c_master_xmit_recv
c_func
(paren
id|nasid_t
comma
id|i2c_addr_t
id|addr
comma
id|u_char
op_star
id|xbuf
comma
r_int
id|xlen_max
comma
r_int
op_star
id|xlen_ptr
comma
id|u_char
op_star
id|rbuf
comma
r_int
id|rlen_max
comma
r_int
op_star
id|rlen_ptr
comma
r_int
id|emblen
comma
id|rtc_time_t
id|timeout
comma
r_int
id|only_if_message
)paren
suffix:semicolon
r_char
op_star
id|i2c_errmsg
c_func
(paren
r_int
id|code
)paren
suffix:semicolon
multiline_comment|/*&n; * Error codes&n; */
DECL|macro|I2C_ERROR_NONE
mdefine_line|#define I2C_ERROR_NONE&t;&t; 0
DECL|macro|I2C_ERROR_INIT
mdefine_line|#define I2C_ERROR_INIT&t;&t;-1&t;/* Initialization error             */
DECL|macro|I2C_ERROR_STATE
mdefine_line|#define I2C_ERROR_STATE&t;&t;-2&t;/* Unexpected chip state&t;    */
DECL|macro|I2C_ERROR_NAK
mdefine_line|#define I2C_ERROR_NAK&t;&t;-3&t;/* Addressed slave not responding   */
DECL|macro|I2C_ERROR_TO_ARB
mdefine_line|#define I2C_ERROR_TO_ARB&t;-4&t;/* Timeout waiting for sysctlr arb  */
DECL|macro|I2C_ERROR_TO_BUSY
mdefine_line|#define I2C_ERROR_TO_BUSY&t;-5&t;/* Timeout waiting for busy bus     */
DECL|macro|I2C_ERROR_TO_SENDA
mdefine_line|#define I2C_ERROR_TO_SENDA&t;-6&t;/* Timeout sending address byte     */
DECL|macro|I2C_ERROR_TO_SENDD
mdefine_line|#define I2C_ERROR_TO_SENDD&t;-7&t;/* Timeout sending data byte        */
DECL|macro|I2C_ERROR_TO_RECVA
mdefine_line|#define I2C_ERROR_TO_RECVA&t;-8&t;/* Timeout receiving address byte   */
DECL|macro|I2C_ERROR_TO_RECVD
mdefine_line|#define I2C_ERROR_TO_RECVD&t;-9&t;/* Timeout receiving data byte      */
DECL|macro|I2C_ERROR_NO_MESSAGE
mdefine_line|#define I2C_ERROR_NO_MESSAGE&t;-10&t;/* No message was waiting&t;    */
DECL|macro|I2C_ERROR_NO_ELSC
mdefine_line|#define I2C_ERROR_NO_ELSC&t;-11&t;/* ELSC is disabled for access &t;    */ &t;
macro_line|#endif /* _ASM_SN_KSYS_I2C_H */
eof

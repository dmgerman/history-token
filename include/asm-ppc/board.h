multiline_comment|/*&n; * BK Id: SCCS/s.board.h 1.5 05/17/01 18:14:24 cort&n; */
multiline_comment|/*&n; *&n; *    Copyright (c) 1999 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; *    Module name: board.h&n; *&n; *    Description:&n; *&t;A generic include file which pulls in appropriate include files&n; *      for specific board types based on configuration settings.&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __BOARD_H__
DECL|macro|__BOARD_H__
mdefine_line|#define&t;__BOARD_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_OAK)
macro_line|#include &lt;asm/oak.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_WALNUT)
macro_line|#include &lt;asm/walnut.h&gt;
macro_line|#endif
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
multiline_comment|/*&n; * The &quot;residual&quot; board information structure the boot loader passes&n; * into the kernel.&n; */
r_extern
r_int
r_char
id|__res
(braket
)braket
suffix:semicolon
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif /* __BOARD_H__ */
macro_line|#endif /* __KERNEL__ */
eof

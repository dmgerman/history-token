macro_line|#ifndef _ZFTAPE_CTL_H
DECL|macro|_ZFTAPE_CTL_H
mdefine_line|#define _ZFTAPE_CTL_H
multiline_comment|/*&n; * Copyright (C) 1996, 1997 Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version. &n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/zftape/zftape-ctl.h,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:19:02 $&n; *&n; *      This file contains the non-standard IOCTL related definitions&n; *      for the QIC-40/80 floppy-tape driver for Linux.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/mtio.h&gt;
macro_line|#include &quot;../zftape/zftape-rw.h&quot;
macro_line|#ifdef CONFIG_ZFTAPE_MODULE
DECL|macro|ftape_status
mdefine_line|#define ftape_status (*zft_status)
macro_line|#endif
r_extern
r_int
id|zft_offline
suffix:semicolon
r_extern
r_int
id|zft_mt_compression
suffix:semicolon
r_extern
r_int
id|zft_write_protected
suffix:semicolon
r_extern
r_int
id|zft_header_read
suffix:semicolon
r_extern
r_int
r_int
id|zft_unit
suffix:semicolon
r_extern
r_int
id|zft_resid
suffix:semicolon
r_extern
r_void
id|zft_reset_position
c_func
(paren
id|zft_position
op_star
id|pos
)paren
suffix:semicolon
r_extern
r_int
id|zft_check_write_access
c_func
(paren
id|zft_position
op_star
id|pos
)paren
suffix:semicolon
r_extern
r_int
id|zft_def_idle_state
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*  hooks for the VFS interface &n; */
r_extern
r_int
id|_zft_open
c_func
(paren
r_int
r_int
id|dev_minor
comma
r_int
r_int
id|access_mode
)paren
suffix:semicolon
r_extern
r_int
id|_zft_close
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|_zft_ioctl
c_func
(paren
r_int
r_int
id|command
comma
r_void
id|__user
op_star
id|arg
)paren
suffix:semicolon
macro_line|#endif
eof

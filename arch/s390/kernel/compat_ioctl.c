multiline_comment|/*&n; * ioctl32.c: Conversion between 32bit and 64bit native ioctls.&n; *&n; *  S390 version&n; *    Copyright (C) 2000-2003 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Gerhard Tonn (ton@de.ibm.com)&n; *               Arnd Bergmann (arndb@de.ibm.com)&n; *&n; * Original implementation from 32-bit Sparc compat code which is&n; * Copyright (C) 2000 Silicon Graphics, Inc.&n; * Written by Ulf Carlsson (ulfc@engr.sgi.com) &n; */
macro_line|#include &quot;compat_linux.h&quot;
DECL|macro|INCLUDES
mdefine_line|#define INCLUDES
DECL|macro|CODE
mdefine_line|#define CODE
macro_line|#include &quot;../../../fs/compat_ioctl.c&quot;
macro_line|#include &lt;asm/dasd.h&gt;
macro_line|#include &lt;asm/tape390.h&gt;
DECL|function|do_ioctl32_pointer
r_static
r_int
id|do_ioctl32_pointer
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_struct
id|file
op_star
id|f
)paren
(brace
r_return
id|sys_ioctl
c_func
(paren
id|fd
comma
id|cmd
comma
(paren
r_int
r_int
)paren
id|compat_ptr
c_func
(paren
id|arg
)paren
)paren
suffix:semicolon
)brace
DECL|function|do_ioctl32_ulong
r_static
r_int
id|do_ioctl32_ulong
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_struct
id|file
op_star
id|f
)paren
(brace
r_return
id|sys_ioctl
c_func
(paren
id|fd
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
DECL|macro|COMPATIBLE_IOCTL
mdefine_line|#define COMPATIBLE_IOCTL(cmd)&t;&t;HANDLE_IOCTL((cmd),(ioctl_trans_handler_t)do_ioctl32_pointer)
DECL|macro|ULONG_IOCTL
mdefine_line|#define ULONG_IOCTL(cmd)&t;&t;HANDLE_IOCTL((cmd),(ioctl_trans_handler_t)do_ioctl32_ulong)
DECL|macro|HANDLE_IOCTL
mdefine_line|#define HANDLE_IOCTL(cmd,handler)&t;{ (cmd), (ioctl_trans_handler_t)(handler), NULL },
DECL|variable|ioctl_start
r_struct
id|ioctl_trans
id|ioctl_start
(braket
)braket
op_assign
(brace
multiline_comment|/* architecture independent ioctls */
macro_line|#include &lt;linux/compat_ioctl.h&gt;
DECL|macro|DECLARES
mdefine_line|#define DECLARES
macro_line|#include &quot;../../../fs/compat_ioctl.c&quot;
multiline_comment|/* s390 only ioctls */
macro_line|#if defined(CONFIG_DASD) || defined(CONFIG_DASD_MODULE)
id|COMPATIBLE_IOCTL
c_func
(paren
id|DASDAPIVER
)paren
id|COMPATIBLE_IOCTL
c_func
(paren
id|BIODASDDISABLE
)paren
id|COMPATIBLE_IOCTL
c_func
(paren
id|BIODASDENABLE
)paren
id|COMPATIBLE_IOCTL
c_func
(paren
id|BIODASDRSRV
)paren
id|COMPATIBLE_IOCTL
c_func
(paren
id|BIODASDRLSE
)paren
id|COMPATIBLE_IOCTL
c_func
(paren
id|BIODASDSLCK
)paren
id|COMPATIBLE_IOCTL
c_func
(paren
id|BIODASDINFO
)paren
id|COMPATIBLE_IOCTL
c_func
(paren
id|BIODASDFMT
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_S390_TAPE) || defined(CONFIG_S390_TAPE_MODULE)
id|COMPATIBLE_IOCTL
c_func
(paren
id|TAPE390_DISPLAY
)paren
macro_line|#endif
multiline_comment|/* This one should be architecture independent */
id|COMPATIBLE_IOCTL
c_func
(paren
id|TCSBRKP
)paren
multiline_comment|/* s390 doesn&squot;t need handlers here */
id|COMPATIBLE_IOCTL
c_func
(paren
id|TIOCGSERIAL
)paren
id|COMPATIBLE_IOCTL
c_func
(paren
id|TIOCSSERIAL
)paren
)brace
suffix:semicolon
DECL|variable|ioctl_table_size
r_int
id|ioctl_table_size
op_assign
id|ARRAY_SIZE
c_func
(paren
id|ioctl_start
)paren
suffix:semicolon
eof

multiline_comment|/*********************************************************************&n; *&n; *&t;sir_tty.h:&t;definitions for the irtty_sir client driver (former irtty)&n; *&n; *&t;Copyright (c) 2002 Martin Diehl&n; *&n; *&t;This program is free software; you can redistribute it and/or &n; *&t;modify it under the terms of the GNU General Public License as &n; *&t;published by the Free Software Foundation; either version 2 of &n; *&t;the License, or (at your option) any later version.&n; *&n; ********************************************************************/
macro_line|#ifndef IRTTYSIR_H
DECL|macro|IRTTYSIR_H
mdefine_line|#define IRTTYSIR_H
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;&t;&t;
singleline_comment|// chipio_t
DECL|macro|IRTTY_IOC_MAGIC
mdefine_line|#define IRTTY_IOC_MAGIC &squot;e&squot;
DECL|macro|IRTTY_IOCTDONGLE
mdefine_line|#define IRTTY_IOCTDONGLE  _IO(IRTTY_IOC_MAGIC, 1)
DECL|macro|IRTTY_IOCGET
mdefine_line|#define IRTTY_IOCGET     _IOR(IRTTY_IOC_MAGIC, 2, struct irtty_info)
DECL|macro|IRTTY_IOC_MAXNR
mdefine_line|#define IRTTY_IOC_MAXNR   2
DECL|struct|sirtty_cb
r_struct
id|sirtty_cb
(brace
DECL|member|magic
id|magic_t
id|magic
suffix:semicolon
DECL|member|dev
r_struct
id|sir_dev
op_star
id|dev
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|io
id|chipio_t
id|io
suffix:semicolon
multiline_comment|/* IrDA controller information */
)brace
suffix:semicolon
macro_line|#endif
eof

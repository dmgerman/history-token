multiline_comment|/*&n; * Hardware parameter area specific to Sharp SL series devices&n; *&n; * Copyright (c) 2005 Richard Purdie&n; *&n; * Based on Sharp&squot;s 2.4 kernel patches&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/mach/sharpsl_param.h&gt;
multiline_comment|/*&n; * Certain hardware parameters determined at the time of device manufacture,&n; * typically including LCD parameters are loaded by the bootloader at the&n; * address PARAM_BASE. As the kernel will overwrite them, we need to store&n; * them early in the boot process, then pass them to the appropriate drivers.&n; * Not all devices use all paramaters but the format is common to all.&n; */
macro_line|#ifdef ARCH_SA1100
DECL|macro|PARAM_BASE
mdefine_line|#define PARAM_BASE&t;0xe8ffc000
macro_line|#else
DECL|macro|PARAM_BASE
mdefine_line|#define PARAM_BASE&t;0xa0000a00
macro_line|#endif
DECL|macro|MAGIC_CHG
mdefine_line|#define MAGIC_CHG(a,b,c,d) ( ( d &lt;&lt; 24 ) | ( c &lt;&lt; 16 )  | ( b &lt;&lt; 8 ) | a )
DECL|macro|COMADJ_MAGIC
mdefine_line|#define COMADJ_MAGIC&t;MAGIC_CHG(&squot;C&squot;,&squot;M&squot;,&squot;A&squot;,&squot;D&squot;)
DECL|macro|UUID_MAGIC
mdefine_line|#define UUID_MAGIC&t;MAGIC_CHG(&squot;U&squot;,&squot;U&squot;,&squot;I&squot;,&squot;D&squot;)
DECL|macro|TOUCH_MAGIC
mdefine_line|#define TOUCH_MAGIC&t;MAGIC_CHG(&squot;T&squot;,&squot;U&squot;,&squot;C&squot;,&squot;H&squot;)
DECL|macro|AD_MAGIC
mdefine_line|#define AD_MAGIC&t;MAGIC_CHG(&squot;B&squot;,&squot;V&squot;,&squot;A&squot;,&squot;D&squot;)
DECL|macro|PHAD_MAGIC
mdefine_line|#define PHAD_MAGIC&t;MAGIC_CHG(&squot;P&squot;,&squot;H&squot;,&squot;A&squot;,&squot;D&squot;)
DECL|variable|sharpsl_param
r_struct
id|sharpsl_param_info
id|sharpsl_param
suffix:semicolon
DECL|function|sharpsl_save_param
r_void
id|sharpsl_save_param
c_func
(paren
r_void
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|sharpsl_param
comma
(paren
r_void
op_star
)paren
id|PARAM_BASE
comma
r_sizeof
(paren
r_struct
id|sharpsl_param_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sharpsl_param.comadj_keyword
op_ne
id|COMADJ_MAGIC
)paren
id|sharpsl_param.comadj
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sharpsl_param.phad_keyword
op_ne
id|PHAD_MAGIC
)paren
id|sharpsl_param.phadadj
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sharpsl_param.uuid_keyword
op_ne
id|UUID_MAGIC
)paren
id|sharpsl_param.uuid
(braket
l_int|0
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sharpsl_param.touch_keyword
op_ne
id|TOUCH_MAGIC
)paren
id|sharpsl_param.touch_xp
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sharpsl_param.adadj_keyword
op_ne
id|AD_MAGIC
)paren
id|sharpsl_param.adadj
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
eof

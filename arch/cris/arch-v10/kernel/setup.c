multiline_comment|/* $Id: setup.c,v 1.1 2002/12/11 15:42:02 starvik Exp $&n; *&n; *  linux/arch/cris/arch-v10/kernel/setup.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Copyright (c) 2001-2002  Axis Communications AB&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of initialization&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#ifdef CONFIG_PROC_FS
DECL|macro|HAS_FPU
mdefine_line|#define HAS_FPU&t;&t;0x0001
DECL|macro|HAS_MMU
mdefine_line|#define HAS_MMU&t;&t;0x0002
DECL|macro|HAS_ETHERNET100
mdefine_line|#define HAS_ETHERNET100&t;0x0004
DECL|macro|HAS_TOKENRING
mdefine_line|#define HAS_TOKENRING&t;0x0008
DECL|macro|HAS_SCSI
mdefine_line|#define HAS_SCSI&t;0x0010
DECL|macro|HAS_ATA
mdefine_line|#define HAS_ATA&t;&t;0x0020
DECL|macro|HAS_USB
mdefine_line|#define HAS_USB&t;&t;0x0040
DECL|macro|HAS_IRQ_BUG
mdefine_line|#define HAS_IRQ_BUG&t;0x0080
DECL|macro|HAS_MMU_BUG
mdefine_line|#define HAS_MMU_BUG&t;0x0100
DECL|struct|cpu_info
r_static
r_struct
id|cpu_info
(brace
DECL|member|model
r_char
op_star
id|model
suffix:semicolon
DECL|member|cache
r_int
r_int
id|cache
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|variable|cpu_info
)brace
id|cpu_info
(braket
)braket
op_assign
(brace
multiline_comment|/* The first four models will never ever run this code and are&n;&t;   only here for display.  */
(brace
l_string|&quot;ETRAX 1&quot;
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_string|&quot;ETRAX 2&quot;
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_string|&quot;ETRAX 3&quot;
comma
l_int|0
comma
id|HAS_TOKENRING
)brace
comma
(brace
l_string|&quot;ETRAX 4&quot;
comma
l_int|0
comma
id|HAS_TOKENRING
op_or
id|HAS_SCSI
)brace
comma
(brace
l_string|&quot;Unknown&quot;
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_string|&quot;Unknown&quot;
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_string|&quot;Unknown&quot;
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_string|&quot;Simulator&quot;
comma
l_int|8
comma
id|HAS_ETHERNET100
op_or
id|HAS_SCSI
op_or
id|HAS_ATA
)brace
comma
(brace
l_string|&quot;ETRAX 100&quot;
comma
l_int|8
comma
id|HAS_ETHERNET100
op_or
id|HAS_SCSI
op_or
id|HAS_ATA
op_or
id|HAS_IRQ_BUG
)brace
comma
(brace
l_string|&quot;ETRAX 100&quot;
comma
l_int|8
comma
id|HAS_ETHERNET100
op_or
id|HAS_SCSI
op_or
id|HAS_ATA
)brace
comma
(brace
l_string|&quot;ETRAX 100LX&quot;
comma
l_int|8
comma
id|HAS_ETHERNET100
op_or
id|HAS_SCSI
op_or
id|HAS_ATA
op_or
id|HAS_USB
op_or
id|HAS_MMU
op_or
id|HAS_MMU_BUG
)brace
comma
(brace
l_string|&quot;ETRAX 100LX v2&quot;
comma
l_int|8
comma
id|HAS_ETHERNET100
op_or
id|HAS_SCSI
op_or
id|HAS_ATA
op_or
id|HAS_USB
op_or
id|HAS_MMU
)brace
comma
(brace
l_string|&quot;Unknown&quot;
comma
l_int|0
comma
l_int|0
)brace
multiline_comment|/* This entry MUST be the last */
)brace
suffix:semicolon
DECL|function|show_cpuinfo
r_int
id|show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
r_int
r_int
id|revision
suffix:semicolon
r_struct
id|cpu_info
op_star
id|info
suffix:semicolon
multiline_comment|/* read the version register in the CPU and print some stuff */
id|revision
op_assign
id|rdvr
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revision
op_ge
r_sizeof
id|cpu_info
op_div
r_sizeof
op_star
id|cpu_info
)paren
id|info
op_assign
op_amp
id|cpu_info
(braket
r_sizeof
id|cpu_info
op_div
r_sizeof
op_star
id|cpu_info
op_minus
l_int|1
)braket
suffix:semicolon
r_else
id|info
op_assign
op_amp
id|cpu_info
(braket
id|revision
)braket
suffix:semicolon
r_return
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;processor&bslash;t: 0&bslash;n&quot;
l_string|&quot;cpu&bslash;t&bslash;t: CRIS&bslash;n&quot;
l_string|&quot;cpu revision&bslash;t: %lu&bslash;n&quot;
l_string|&quot;cpu model&bslash;t: %s&bslash;n&quot;
l_string|&quot;cache size&bslash;t: %d kB&bslash;n&quot;
l_string|&quot;fpu&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;mmu&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;mmu DMA bug&bslash;t: %s&bslash;n&quot;
l_string|&quot;ethernet&bslash;t: %s Mbps&bslash;n&quot;
l_string|&quot;token ring&bslash;t: %s&bslash;n&quot;
l_string|&quot;scsi&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;ata&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;usb&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;bogomips&bslash;t: %lu.%02lu&bslash;n&quot;
comma
id|revision
comma
id|info-&gt;model
comma
id|info-&gt;cache
comma
id|info-&gt;flags
op_amp
id|HAS_FPU
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|info-&gt;flags
op_amp
id|HAS_MMU
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|info-&gt;flags
op_amp
id|HAS_MMU_BUG
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|info-&gt;flags
op_amp
id|HAS_ETHERNET100
ques
c_cond
l_string|&quot;10/100&quot;
suffix:colon
l_string|&quot;10&quot;
comma
id|info-&gt;flags
op_amp
id|HAS_TOKENRING
ques
c_cond
l_string|&quot;4/16 Mbps&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|info-&gt;flags
op_amp
id|HAS_SCSI
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|info-&gt;flags
op_amp
id|HAS_ATA
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|info-&gt;flags
op_amp
id|HAS_USB
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
(paren
id|loops_per_jiffy
op_star
id|HZ
op_plus
l_int|500
)paren
op_div
l_int|500000
comma
(paren
(paren
id|loops_per_jiffy
op_star
id|HZ
op_plus
l_int|500
)paren
op_div
l_int|5000
)paren
op_mod
l_int|100
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PROC_FS */
eof

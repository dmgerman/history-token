multiline_comment|/*&n; * kernel/power/pmdisk.c - Suspend-to-disk implmentation&n; *&n; * This STD implementation is initially derived from swsusp (suspend-to-swap).&n; * The original copyright on that was: &n; *&n; * Copyright (C) 1998-2001 Gabor Kuti &lt;seasons@fornax.hu&gt;&n; * Copyright (C) 1998,2001,2002 Pavel Machek &lt;pavel@suse.cz&gt;&n; *&n; * The additional parts are: &n; * &n; * Copyright (C) 2003 Patrick Mochel&n; * Copyright (C) 2003 Open Source Development Lab&n; * &n; * This file is released under the GPLv2. &n; *&n; * For more information, please see the text files in Documentation/power/&n; *&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/swapops.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &quot;power.h&quot;
multiline_comment|/* For resume= kernel option */
DECL|variable|resume_file
r_static
r_char
id|resume_file
(braket
l_int|256
)braket
op_assign
id|CONFIG_PM_DISK_PARTITION
suffix:semicolon
r_extern
id|suspend_pagedir_t
op_star
id|pagedir_save
suffix:semicolon
multiline_comment|/*&n; * Saving part...&n; */
DECL|function|pmdisk_setup
r_static
r_int
id|__init
id|pmdisk_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|str
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;off&quot;
)paren
)paren
id|resume_file
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_else
id|strncpy
c_func
(paren
id|resume_file
comma
id|str
comma
l_int|255
)paren
suffix:semicolon
)brace
r_else
id|resume_file
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;pmdisk=&quot;
comma
id|pmdisk_setup
)paren
suffix:semicolon
eof

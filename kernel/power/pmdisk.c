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
eof

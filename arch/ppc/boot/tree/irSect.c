multiline_comment|/*&n; * BK Id: SCCS/s.irSect.c 1.6 05/18/01 15:17:22 cort&n; */
multiline_comment|/*&n; *&n; *    Copyright (c) 1999 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; *    Module name: irSect.c&n; *&n; *    Description:&n; *      Defines variables to hold the absolute starting address and size&n; *      of the Linux kernel &quot;image&quot; and the initial RAM disk &quot;initrd&quot;&n; *      sections within the boot loader.&n; *&n; */
macro_line|#include &quot;irSect.h&quot;
multiline_comment|/*&n; * The order of globals below must not change. If more globals are added,&n; * you must change the script &squot;mkirimg&squot; accordingly.&n; *&n; */
multiline_comment|/* &n; * irSectStart must be at beginning of file &n; */
DECL|variable|irSectStart
r_int
r_int
id|irSectStart
op_assign
l_int|0xdeadbeaf
suffix:semicolon
DECL|variable|imageSect_start
r_int
r_int
id|imageSect_start
op_assign
l_int|0
suffix:semicolon
DECL|variable|imageSect_size
r_int
r_int
id|imageSect_size
op_assign
l_int|0
suffix:semicolon
DECL|variable|initrdSect_start
r_int
r_int
id|initrdSect_start
op_assign
l_int|0
suffix:semicolon
DECL|variable|initrdSect_size
r_int
r_int
id|initrdSect_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &n; * irSectEnd must be at end of file &n; */
DECL|variable|irSectEnd
r_int
r_int
id|irSectEnd
op_assign
l_int|0xdeadbeaf
suffix:semicolon
eof

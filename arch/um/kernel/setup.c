multiline_comment|/* &n; * Copyright (C) 2000, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;asm/processor.h&quot;
DECL|variable|boot_cpu_data
r_struct
id|cpuinfo_um
id|boot_cpu_data
op_assign
(brace
id|loops_per_jiffy
suffix:colon
l_int|0
comma
id|ipi_pipe
suffix:colon
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof

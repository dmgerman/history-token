multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/pci.h&quot;
DECL|function|resource_fixup
r_int
r_int
id|resource_fixup
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|start
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof

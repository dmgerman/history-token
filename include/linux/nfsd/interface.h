multiline_comment|/*&n; * include/linux/nfsd/interface.h&n; *&n; * defines interface between nfsd and other bits of&n; * the kernel.  Particularly filesystems (eventually).&n; *&n; * Copyright (C) 2000 Neil Brown &lt;neilb@cse.unsw.edu.au&gt;&n; */
macro_line|#ifndef LINUX_NFSD_INTERFACE_H
DECL|macro|LINUX_NFSD_INTERFACE_H
mdefine_line|#define LINUX_NFSD_INTERFACE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef CONFIG_NFSD
macro_line|#ifdef CONFIG_MODULES
DECL|struct|nfsd_linkage
r_extern
r_struct
id|nfsd_linkage
(brace
DECL|member|do_nfsservctl
r_int
(paren
op_star
id|do_nfsservctl
)paren
(paren
r_int
id|cmd
comma
r_void
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
)brace
op_star
id|nfsd_linkage
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#endif /* LINUX_NFSD_INTERFACE_H */
eof

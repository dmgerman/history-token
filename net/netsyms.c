multiline_comment|/*&n; *  linux/net/netsyms.c&n; *&n; *  Symbol table for the linux networking subsystem. Moved here to&n; *  make life simpler in ksyms.c.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/* Needed by unix.o */
DECL|variable|files_stat
id|EXPORT_SYMBOL
c_func
(paren
id|files_stat
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET
DECL|variable|__kill_fasync
id|EXPORT_SYMBOL
c_func
(paren
id|__kill_fasync
)paren
suffix:semicolon
macro_line|#endif  /* CONFIG_NET */
eof

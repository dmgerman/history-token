macro_line|#ifndef _PPC64_PSERIES_RECONFIG_H
DECL|macro|_PPC64_PSERIES_RECONFIG_H
mdefine_line|#define _PPC64_PSERIES_RECONFIG_H
macro_line|#include &lt;linux/notifier.h&gt;
multiline_comment|/*&n; * Use this API if your code needs to know about OF device nodes being&n; * added or removed on pSeries systems.&n; */
DECL|macro|PSERIES_RECONFIG_ADD
mdefine_line|#define PSERIES_RECONFIG_ADD    0x0001
DECL|macro|PSERIES_RECONFIG_REMOVE
mdefine_line|#define PSERIES_RECONFIG_REMOVE 0x0002
macro_line|#ifdef CONFIG_PPC_PSERIES
r_extern
r_int
id|pSeries_reconfig_notifier_register
c_func
(paren
r_struct
id|notifier_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pSeries_reconfig_notifier_unregister
c_func
(paren
r_struct
id|notifier_block
op_star
)paren
suffix:semicolon
macro_line|#else /* !CONFIG_PPC_PSERIES */
DECL|function|pSeries_reconfig_notifier_register
r_static
r_inline
r_int
id|pSeries_reconfig_notifier_register
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pSeries_reconfig_notifier_unregister
r_static
r_inline
r_void
id|pSeries_reconfig_notifier_unregister
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
(brace
)brace
macro_line|#endif /* CONFIG_PPC_PSERIES */
macro_line|#endif /* _PPC64_PSERIES_RECONFIG_H */
eof

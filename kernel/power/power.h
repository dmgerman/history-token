multiline_comment|/* With SUSPEND_CONSOLE defined, it suspend looks *really* cool, but&n;   we probably do not take enough locks for switching consoles, etc,&n;   so bad things might happen.&n;*/
macro_line|#if defined(CONFIG_VT) &amp;&amp; defined(CONFIG_VT_CONSOLE)
DECL|macro|SUSPEND_CONSOLE
mdefine_line|#define SUSPEND_CONSOLE&t;(MAX_NR_CONSOLES-1)
macro_line|#endif
eof

macro_line|#ifndef __LINUX_STRINGIFY_H
DECL|macro|__LINUX_STRINGIFY_H
mdefine_line|#define __LINUX_STRINGIFY_H
multiline_comment|/* Indirect stringification.  Doing two levels allows the parameter to be a&n; * macro itself.  For example, compile with -DFOO=bar, __stringify(FOO)&n; * converts to &quot;bar&quot;.&n; */
DECL|macro|__stringify_1
mdefine_line|#define __stringify_1(x)&t;#x
DECL|macro|__stringify
mdefine_line|#define __stringify(x)&t;&t;__stringify_1(x)
macro_line|#endif&t;/* !__LINUX_STRINGIFY_H */
eof

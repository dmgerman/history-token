macro_line|#include &lt;dlfcn.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &quot;lkc.h&quot;
DECL|macro|P
mdefine_line|#define P(name,type,arg)&t;type (*name ## _p) arg
macro_line|#include &quot;lkc_proto.h&quot;
DECL|macro|P
macro_line|#undef P
DECL|function|kconfig_load
r_void
id|kconfig_load
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|handle
suffix:semicolon
r_char
op_star
id|error
suffix:semicolon
id|handle
op_assign
id|dlopen
c_func
(paren
l_string|&quot;./libkconfig.so&quot;
comma
id|RTLD_LAZY
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handle
)paren
(brace
id|handle
op_assign
id|dlopen
c_func
(paren
l_string|&quot;./scripts/kconfig/libkconfig.so&quot;
comma
id|RTLD_LAZY
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handle
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|dlerror
c_func
(paren
)paren
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|macro|P
mdefine_line|#define P(name,type,arg)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;name ## _p = dlsym(handle, #name);&t;&bslash;&n;        if ((error = dlerror()))  {&t;&t;&bslash;&n;                fprintf(stderr, &quot;%s&bslash;n&quot;, error);&t;&bslash;&n;&t;&t;exit(1);&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#include &quot;lkc_proto.h&quot;
DECL|macro|P
macro_line|#undef P
)brace
eof

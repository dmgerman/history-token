macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;dirent.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;utime.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;sys/vfs.h&gt;
macro_line|#include &lt;sys/ioctl.h&gt;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;mem_user.h&quot;
multiline_comment|/* XXX All the __CONFIG_* stuff is broken because this file can&squot;t include&n; * config.h&n; */
multiline_comment|/* Had to steal this from linux/module.h because that file can&squot;t be included&n; * since this includes various user-level headers.&n; */
DECL|struct|module_symbol
r_struct
id|module_symbol
(brace
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Indirect stringification.  */
DECL|macro|__MODULE_STRING_1
mdefine_line|#define __MODULE_STRING_1(x)&t;#x
DECL|macro|__MODULE_STRING
mdefine_line|#define __MODULE_STRING(x)&t;__MODULE_STRING_1(x)
macro_line|#if !defined(__AUTOCONF_INCLUDED__)
DECL|macro|__EXPORT_SYMBOL
mdefine_line|#define __EXPORT_SYMBOL(sym,str)   error config_must_be_included_before_module
DECL|macro|EXPORT_SYMBOL
mdefine_line|#define EXPORT_SYMBOL(var)&t;   error config_must_be_included_before_module
DECL|macro|EXPORT_SYMBOL_NOVERS
mdefine_line|#define EXPORT_SYMBOL_NOVERS(var)  error config_must_be_included_before_module
macro_line|#elif !defined(__CONFIG_MODULES__)
DECL|macro|__EXPORT_SYMBOL
mdefine_line|#define __EXPORT_SYMBOL(sym,str)
DECL|macro|EXPORT_SYMBOL
mdefine_line|#define EXPORT_SYMBOL(var)
DECL|macro|EXPORT_SYMBOL_NOVERS
mdefine_line|#define EXPORT_SYMBOL_NOVERS(var)
macro_line|#else
DECL|macro|__EXPORT_SYMBOL
mdefine_line|#define __EXPORT_SYMBOL(sym, str)&t;&t;&t;&bslash;&n;const char __kstrtab_##sym[]&t;&t;&t;&t;&bslash;&n;__attribute__((section(&quot;.kstrtab&quot;))) = str;&t;&t;&bslash;&n;const struct module_symbol __ksymtab_##sym &t;&t;&bslash;&n;__attribute__((section(&quot;__ksymtab&quot;))) =&t;&t;&t;&bslash;&n;{ (unsigned long)&amp;sym, __kstrtab_##sym }
macro_line|#if defined(__MODVERSIONS__) || !defined(__CONFIG_MODVERSIONS__)
DECL|macro|EXPORT_SYMBOL
mdefine_line|#define EXPORT_SYMBOL(var)  __EXPORT_SYMBOL(var, __MODULE_STRING(var))
macro_line|#else
DECL|macro|EXPORT_SYMBOL
mdefine_line|#define EXPORT_SYMBOL(var)  __EXPORT_SYMBOL(var, __MODULE_STRING(__VERSIONED_SYMBOL(var)))
macro_line|#endif
DECL|macro|EXPORT_SYMBOL_NOVERS
mdefine_line|#define EXPORT_SYMBOL_NOVERS(var)  __EXPORT_SYMBOL(var, __MODULE_STRING(var))
macro_line|#endif
DECL|variable|__errno_location
id|EXPORT_SYMBOL
c_func
(paren
id|__errno_location
)paren
suffix:semicolon
DECL|variable|access
id|EXPORT_SYMBOL
c_func
(paren
id|access
)paren
suffix:semicolon
DECL|variable|open
id|EXPORT_SYMBOL
c_func
(paren
id|open
)paren
suffix:semicolon
DECL|variable|open64
id|EXPORT_SYMBOL
c_func
(paren
id|open64
)paren
suffix:semicolon
DECL|variable|close
id|EXPORT_SYMBOL
c_func
(paren
id|close
)paren
suffix:semicolon
DECL|variable|read
id|EXPORT_SYMBOL
c_func
(paren
id|read
)paren
suffix:semicolon
DECL|variable|write
id|EXPORT_SYMBOL
c_func
(paren
id|write
)paren
suffix:semicolon
DECL|variable|dup2
id|EXPORT_SYMBOL
c_func
(paren
id|dup2
)paren
suffix:semicolon
DECL|variable|__xstat
id|EXPORT_SYMBOL
c_func
(paren
id|__xstat
)paren
suffix:semicolon
DECL|variable|__lxstat
id|EXPORT_SYMBOL
c_func
(paren
id|__lxstat
)paren
suffix:semicolon
DECL|variable|__lxstat64
id|EXPORT_SYMBOL
c_func
(paren
id|__lxstat64
)paren
suffix:semicolon
DECL|variable|lseek
id|EXPORT_SYMBOL
c_func
(paren
id|lseek
)paren
suffix:semicolon
DECL|variable|lseek64
id|EXPORT_SYMBOL
c_func
(paren
id|lseek64
)paren
suffix:semicolon
DECL|variable|chown
id|EXPORT_SYMBOL
c_func
(paren
id|chown
)paren
suffix:semicolon
DECL|variable|truncate
id|EXPORT_SYMBOL
c_func
(paren
id|truncate
)paren
suffix:semicolon
DECL|variable|utime
id|EXPORT_SYMBOL
c_func
(paren
id|utime
)paren
suffix:semicolon
DECL|variable|chmod
id|EXPORT_SYMBOL
c_func
(paren
id|chmod
)paren
suffix:semicolon
DECL|variable|rename
id|EXPORT_SYMBOL
c_func
(paren
id|rename
)paren
suffix:semicolon
DECL|variable|__xmknod
id|EXPORT_SYMBOL
c_func
(paren
id|__xmknod
)paren
suffix:semicolon
DECL|variable|symlink
id|EXPORT_SYMBOL
c_func
(paren
id|symlink
)paren
suffix:semicolon
DECL|variable|link
id|EXPORT_SYMBOL
c_func
(paren
id|link
)paren
suffix:semicolon
DECL|variable|unlink
id|EXPORT_SYMBOL
c_func
(paren
id|unlink
)paren
suffix:semicolon
DECL|variable|readlink
id|EXPORT_SYMBOL
c_func
(paren
id|readlink
)paren
suffix:semicolon
DECL|variable|mkdir
id|EXPORT_SYMBOL
c_func
(paren
id|mkdir
)paren
suffix:semicolon
DECL|variable|rmdir
id|EXPORT_SYMBOL
c_func
(paren
id|rmdir
)paren
suffix:semicolon
DECL|variable|opendir
id|EXPORT_SYMBOL
c_func
(paren
id|opendir
)paren
suffix:semicolon
DECL|variable|readdir
id|EXPORT_SYMBOL
c_func
(paren
id|readdir
)paren
suffix:semicolon
DECL|variable|closedir
id|EXPORT_SYMBOL
c_func
(paren
id|closedir
)paren
suffix:semicolon
DECL|variable|seekdir
id|EXPORT_SYMBOL
c_func
(paren
id|seekdir
)paren
suffix:semicolon
DECL|variable|telldir
id|EXPORT_SYMBOL
c_func
(paren
id|telldir
)paren
suffix:semicolon
DECL|variable|ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|ioctl
)paren
suffix:semicolon
r_extern
id|ssize_t
id|pread64
(paren
r_int
id|__fd
comma
r_void
op_star
id|__buf
comma
r_int
id|__nbytes
comma
id|__off64_t
id|__offset
)paren
suffix:semicolon
r_extern
id|ssize_t
id|pwrite64
(paren
r_int
id|__fd
comma
id|__const
r_void
op_star
id|__buf
comma
r_int
id|__n
comma
id|__off64_t
id|__offset
)paren
suffix:semicolon
DECL|variable|pread64
id|EXPORT_SYMBOL
c_func
(paren
id|pread64
)paren
suffix:semicolon
DECL|variable|pwrite64
id|EXPORT_SYMBOL
c_func
(paren
id|pwrite64
)paren
suffix:semicolon
DECL|variable|statfs
id|EXPORT_SYMBOL
c_func
(paren
id|statfs
)paren
suffix:semicolon
DECL|variable|statfs64
id|EXPORT_SYMBOL
c_func
(paren
id|statfs64
)paren
suffix:semicolon
DECL|variable|memcpy
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|getuid
id|EXPORT_SYMBOL
c_func
(paren
id|getuid
)paren
suffix:semicolon
DECL|variable|memset
id|EXPORT_SYMBOL
c_func
(paren
id|memset
)paren
suffix:semicolon
DECL|variable|strstr
id|EXPORT_SYMBOL
c_func
(paren
id|strstr
)paren
suffix:semicolon
DECL|variable|find_iomem
id|EXPORT_SYMBOL
c_func
(paren
id|find_iomem
)paren
suffix:semicolon
eof

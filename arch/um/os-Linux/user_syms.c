macro_line|#include &quot;linux/types.h&quot;
macro_line|#include &quot;linux/module.h&quot;
multiline_comment|/* Some of this are builtin function (some are not but could in the future),&n; * so I *must* declare good prototypes for them and then EXPORT them.&n; * The kernel code uses the macro defined by include/linux/string.h,&n; * so I undef macros; the userspace code does not include that and I&n; * add an EXPORT for the glibc one.*/
DECL|macro|strlen
macro_line|#undef strlen
DECL|macro|strstr
macro_line|#undef strstr
DECL|macro|memcpy
macro_line|#undef memcpy
DECL|macro|memset
macro_line|#undef memset
r_extern
r_int
id|strlen
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memcpy
c_func
(paren
r_void
op_star
comma
r_const
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memmove
c_func
(paren
r_void
op_star
comma
r_const
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memset
c_func
(paren
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|printf
c_func
(paren
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|variable|strlen
id|EXPORT_SYMBOL
c_func
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|memcpy
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|memset
id|EXPORT_SYMBOL
c_func
(paren
id|memset
)paren
suffix:semicolon
DECL|variable|printf
id|EXPORT_SYMBOL
c_func
(paren
id|printf
)paren
suffix:semicolon
DECL|variable|strstr
id|EXPORT_SYMBOL
c_func
(paren
id|strstr
)paren
suffix:semicolon
DECL|variable|vsyscall_ehdr
id|EXPORT_SYMBOL
c_func
(paren
id|vsyscall_ehdr
)paren
suffix:semicolon
DECL|variable|vsyscall_end
id|EXPORT_SYMBOL
c_func
(paren
id|vsyscall_end
)paren
suffix:semicolon
multiline_comment|/* Here, instead, I can provide a fake prototype. Yes, someone cares: genksyms.&n; * However, the modules will use the CRC defined *here*, no matter if it is&n; * good; so the versions of these symbols will always match&n; */
DECL|macro|EXPORT_SYMBOL_PROTO
mdefine_line|#define EXPORT_SYMBOL_PROTO(sym)       &bslash;&n;       int sym(void);                  &bslash;&n;       EXPORT_SYMBOL(sym);
DECL|variable|__errno_location
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|__errno_location
)paren
suffix:semicolon
DECL|variable|access
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|access
)paren
suffix:semicolon
DECL|variable|open
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|open
)paren
suffix:semicolon
DECL|variable|open64
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|open64
)paren
suffix:semicolon
DECL|variable|close
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|close
)paren
suffix:semicolon
DECL|variable|read
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|read
)paren
suffix:semicolon
DECL|variable|write
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|write
)paren
suffix:semicolon
DECL|variable|dup2
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|dup2
)paren
suffix:semicolon
DECL|variable|__xstat
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|__xstat
)paren
suffix:semicolon
DECL|variable|__lxstat
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|__lxstat
)paren
suffix:semicolon
DECL|variable|__lxstat64
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|__lxstat64
)paren
suffix:semicolon
DECL|variable|lseek
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|lseek
)paren
suffix:semicolon
DECL|variable|lseek64
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|lseek64
)paren
suffix:semicolon
DECL|variable|chown
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|chown
)paren
suffix:semicolon
DECL|variable|truncate
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|truncate
)paren
suffix:semicolon
DECL|variable|utime
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|utime
)paren
suffix:semicolon
DECL|variable|chmod
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|chmod
)paren
suffix:semicolon
DECL|variable|rename
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|rename
)paren
suffix:semicolon
DECL|variable|__xmknod
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|__xmknod
)paren
suffix:semicolon
DECL|variable|symlink
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|symlink
)paren
suffix:semicolon
DECL|variable|link
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|link
)paren
suffix:semicolon
DECL|variable|unlink
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|unlink
)paren
suffix:semicolon
DECL|variable|readlink
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|readlink
)paren
suffix:semicolon
DECL|variable|mkdir
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|mkdir
)paren
suffix:semicolon
DECL|variable|rmdir
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|rmdir
)paren
suffix:semicolon
DECL|variable|opendir
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|opendir
)paren
suffix:semicolon
DECL|variable|readdir
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|readdir
)paren
suffix:semicolon
DECL|variable|closedir
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|closedir
)paren
suffix:semicolon
DECL|variable|seekdir
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|seekdir
)paren
suffix:semicolon
DECL|variable|telldir
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|telldir
)paren
suffix:semicolon
DECL|variable|ioctl
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|ioctl
)paren
suffix:semicolon
DECL|variable|pread64
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|pread64
)paren
suffix:semicolon
DECL|variable|pwrite64
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|pwrite64
)paren
suffix:semicolon
DECL|variable|statfs
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|statfs
)paren
suffix:semicolon
DECL|variable|statfs64
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|statfs64
)paren
suffix:semicolon
DECL|variable|getuid
id|EXPORT_SYMBOL_PROTO
c_func
(paren
id|getuid
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof

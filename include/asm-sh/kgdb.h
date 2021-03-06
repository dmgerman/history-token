multiline_comment|/*&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * Based on original code by Glenn Engel, Jim Kingdon,&n; * David Grothe &lt;dave@gcom.com&gt;, Tigran Aivazian, &lt;tigran@sco.com&gt; and&n; * Amit S. Kale &lt;akale@veritas.com&gt;&n; * &n; * Super-H port based on sh-stub.c (Ben Lee and Steve Chamberlain) by&n; * Henry Bell &lt;henry.bell@st.com&gt;&n; * &n; * Header file for low-level support for remote debug using GDB. &n; *&n; */
macro_line|#ifndef __KGDB_H
DECL|macro|__KGDB_H
mdefine_line|#define __KGDB_H
macro_line|#include &lt;asm/ptrace.h&gt;
r_struct
id|console
suffix:semicolon
multiline_comment|/* Same as pt_regs but has vbr in place of syscall_nr */
DECL|struct|kgdb_regs
r_struct
id|kgdb_regs
(brace
DECL|member|regs
r_int
r_int
id|regs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
DECL|member|pr
r_int
r_int
id|pr
suffix:semicolon
DECL|member|sr
r_int
r_int
id|sr
suffix:semicolon
DECL|member|gbr
r_int
r_int
id|gbr
suffix:semicolon
DECL|member|mach
r_int
r_int
id|mach
suffix:semicolon
DECL|member|macl
r_int
r_int
id|macl
suffix:semicolon
DECL|member|vbr
r_int
r_int
id|vbr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* State info */
r_extern
r_char
id|kgdb_in_gdb_mode
suffix:semicolon
r_extern
r_int
id|kgdb_done_init
suffix:semicolon
r_extern
r_int
id|kgdb_enabled
suffix:semicolon
r_extern
r_int
id|kgdb_nofault
suffix:semicolon
multiline_comment|/* Ignore bus errors (in gdb mem access) */
r_extern
r_int
id|kgdb_halt
suffix:semicolon
multiline_comment|/* Execute initial breakpoint at startup */
r_extern
r_char
id|in_nmi
suffix:semicolon
multiline_comment|/* Debounce flag to prevent NMI reentry*/
multiline_comment|/* SCI */
r_extern
r_int
id|kgdb_portnum
suffix:semicolon
r_extern
r_int
id|kgdb_baud
suffix:semicolon
r_extern
r_char
id|kgdb_parity
suffix:semicolon
r_extern
r_char
id|kgdb_bits
suffix:semicolon
r_extern
r_int
id|kgdb_console_setup
c_func
(paren
r_struct
id|console
op_star
comma
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* Init and interface stuff */
r_extern
r_int
id|kgdb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|kgdb_serial_setup
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|kgdb_getchar
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|kgdb_putchar
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|struct|kgdb_sermap
r_struct
id|kgdb_sermap
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|namelen
r_int
id|namelen
suffix:semicolon
DECL|member|setup_fn
r_int
(paren
op_star
id|setup_fn
)paren
(paren
r_struct
id|console
op_star
comma
r_char
op_star
)paren
suffix:semicolon
DECL|member|next
r_struct
id|kgdb_sermap
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|kgdb_register_sermap
c_func
(paren
r_struct
id|kgdb_sermap
op_star
id|map
)paren
suffix:semicolon
r_extern
r_struct
id|kgdb_sermap
op_star
id|kgdb_porttype
suffix:semicolon
multiline_comment|/* Trap functions */
DECL|typedef|kgdb_debug_hook_t
r_typedef
r_void
(paren
id|kgdb_debug_hook_t
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|typedef|kgdb_bus_error_hook_t
r_typedef
r_void
(paren
id|kgdb_bus_error_hook_t
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
id|kgdb_debug_hook_t
op_star
id|kgdb_debug_hook
suffix:semicolon
r_extern
id|kgdb_bus_error_hook_t
op_star
id|kgdb_bus_err_hook
suffix:semicolon
r_extern
r_void
id|breakpoint
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Console */
r_struct
id|console
suffix:semicolon
r_void
id|kgdb_console_write
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|s
comma
r_int
id|count
)paren
suffix:semicolon
r_void
id|kgdb_console_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Prototypes for jmp fns */
DECL|macro|_JBLEN
mdefine_line|#define _JBLEN 9
DECL|typedef|jmp_buf
r_typedef
r_int
id|jmp_buf
(braket
id|_JBLEN
)braket
suffix:semicolon
r_extern
r_void
m_longjmp
(paren
id|jmp_buf
id|__jmpb
comma
r_int
id|__retval
)paren
suffix:semicolon
r_extern
r_int
m_setjmp
(paren
id|jmp_buf
id|__jmpb
)paren
suffix:semicolon
multiline_comment|/* Variadic macro to print our own message to the console */
DECL|macro|KGDB_PRINTK
mdefine_line|#define KGDB_PRINTK(...) printk(&quot;KGDB: &quot; __VA_ARGS__)
multiline_comment|/* Forced breakpoint */
DECL|macro|BREAKPOINT
mdefine_line|#define BREAKPOINT() do {                                     &bslash;&n;  if (kgdb_enabled) {                                         &bslash;&n;    asm volatile(&quot;trapa   #0xff&quot;);                            &bslash;&n;  }                                                           &bslash;&n;} while (0)
multiline_comment|/* KGDB should be able to flush all kernel text space */
macro_line|#if defined(CONFIG_CPU_SH4)
DECL|macro|kgdb_flush_icache_range
mdefine_line|#define kgdb_flush_icache_range(start, end) &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;extern void __flush_purge_region(void *, int);&t;&t;&t;&bslash;&n;&t;__flush_purge_region((void*)(start), (int)(end) - (int)(start));&bslash;&n;&t;flush_icache_range((start), (end));&t;&t;&t;&t;&bslash;&n;}
macro_line|#else
DECL|macro|kgdb_flush_icache_range
mdefine_line|#define kgdb_flush_icache_range(start, end)&t;do { } while (0)
macro_line|#endif
multiline_comment|/* Kernel assert macros */
macro_line|#ifdef CONFIG_KGDB_KERNEL_ASSERTS
multiline_comment|/* Predefined conditions */
DECL|macro|KA_VALID_ERRNO
mdefine_line|#define KA_VALID_ERRNO(errno) ((errno) &gt; 0 &amp;&amp; (errno) &lt;= EMEDIUMTYPE)
DECL|macro|KA_VALID_PTR_ERR
mdefine_line|#define KA_VALID_PTR_ERR(ptr) KA_VALID_ERRNO(-PTR_ERR(ptr))
DECL|macro|KA_VALID_KPTR
mdefine_line|#define KA_VALID_KPTR(ptr)  (!(ptr) || &bslash;&n;              ((void *)(ptr) &gt;= (void *)PAGE_OFFSET &amp;&amp;  &bslash;&n;               (void *)(ptr) &lt; ERR_PTR(-EMEDIUMTYPE)))
DECL|macro|KA_VALID_PTRORERR
mdefine_line|#define KA_VALID_PTRORERR(errptr) &bslash;&n;               (KA_VALID_KPTR(errptr) || KA_VALID_PTR_ERR(errptr))
DECL|macro|KA_HELD_GKL
mdefine_line|#define KA_HELD_GKL()  (current-&gt;lock_depth &gt;= 0)
multiline_comment|/* The actual assert */
DECL|macro|KGDB_ASSERT
mdefine_line|#define KGDB_ASSERT(condition, message) do {                   &bslash;&n;       if (!(condition) &amp;&amp; (kgdb_enabled)) {                   &bslash;&n;               KGDB_PRINTK(&quot;Assertion failed at %s:%d: %s&bslash;n&quot;,  &bslash;&n;                                  __FILE__, __LINE__, message);&bslash;&n;               BREAKPOINT();                                   &bslash;&n;       }                                                       &bslash;&n;} while (0)
macro_line|#else
DECL|macro|KGDB_ASSERT
mdefine_line|#define KGDB_ASSERT(condition, message)
macro_line|#endif
macro_line|#endif
eof

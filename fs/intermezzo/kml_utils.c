macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/intermezzo_fs.h&gt;
macro_line|#include &lt;linux/intermezzo_kml.h&gt;
singleline_comment|// dlogit -- oppsite to logit ()
singleline_comment|//         return the sbuf + size;
DECL|function|dlogit
r_char
op_star
id|dlogit
(paren
r_void
op_star
id|tbuf
comma
r_const
r_void
op_star
id|sbuf
comma
r_int
id|size
)paren
(brace
r_char
op_star
id|ptr
op_assign
(paren
r_char
op_star
)paren
id|sbuf
suffix:semicolon
id|memcpy
c_func
(paren
id|tbuf
comma
id|ptr
comma
id|size
)paren
suffix:semicolon
id|ptr
op_add_assign
id|size
suffix:semicolon
r_return
id|ptr
suffix:semicolon
)brace
DECL|variable|kml_lock
r_static
id|spinlock_t
id|kml_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|buf
r_static
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
DECL|function|bdup_printf
r_char
op_star
id|bdup_printf
(paren
r_char
op_star
id|format
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|i
suffix:semicolon
r_char
op_star
id|path
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|kml_lock
comma
id|flags
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|format
)paren
suffix:semicolon
id|i
op_assign
id|vsprintf
c_func
(paren
id|buf
comma
id|format
comma
id|args
)paren
suffix:semicolon
multiline_comment|/* hopefully i &lt; sizeof(buf) */
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|PRESTO_ALLOC
(paren
id|path
comma
r_char
op_star
comma
id|i
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|path
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|strcpy
(paren
id|path
comma
id|buf
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|kml_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|path
suffix:semicolon
)brace
eof

multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2001, 2002, 2004 Ralf Baechle&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* SUPERIO uart register map */
DECL|struct|yo_uartregs
r_struct
id|yo_uartregs
(brace
r_union
(brace
DECL|member|rbr
r_volatile
id|u8
id|rbr
suffix:semicolon
multiline_comment|/* read only, DLAB == 0 */
DECL|member|thr
r_volatile
id|u8
id|thr
suffix:semicolon
multiline_comment|/* write only, DLAB == 0 */
DECL|member|dll
r_volatile
id|u8
id|dll
suffix:semicolon
multiline_comment|/* DLAB == 1 */
DECL|member|u1
)brace
id|u1
suffix:semicolon
r_union
(brace
DECL|member|ier
r_volatile
id|u8
id|ier
suffix:semicolon
multiline_comment|/* DLAB == 0 */
DECL|member|dlm
r_volatile
id|u8
id|dlm
suffix:semicolon
multiline_comment|/* DLAB == 1 */
DECL|member|u2
)brace
id|u2
suffix:semicolon
r_union
(brace
DECL|member|iir
r_volatile
id|u8
id|iir
suffix:semicolon
multiline_comment|/* read only */
DECL|member|fcr
r_volatile
id|u8
id|fcr
suffix:semicolon
multiline_comment|/* write only */
DECL|member|u3
)brace
id|u3
suffix:semicolon
DECL|member|iu_lcr
r_volatile
id|u8
id|iu_lcr
suffix:semicolon
DECL|member|iu_mcr
r_volatile
id|u8
id|iu_mcr
suffix:semicolon
DECL|member|iu_lsr
r_volatile
id|u8
id|iu_lsr
suffix:semicolon
DECL|member|iu_msr
r_volatile
id|u8
id|iu_msr
suffix:semicolon
DECL|member|iu_scr
r_volatile
id|u8
id|iu_scr
suffix:semicolon
DECL|variable|yo_uregs_t
)brace
id|yo_uregs_t
suffix:semicolon
DECL|macro|iu_rbr
mdefine_line|#define iu_rbr u1.rbr
DECL|macro|iu_thr
mdefine_line|#define iu_thr u1.thr
DECL|macro|iu_dll
mdefine_line|#define iu_dll u1.dll
DECL|macro|iu_ier
mdefine_line|#define iu_ier u2.ier
DECL|macro|iu_dlm
mdefine_line|#define iu_dlm u2.dlm
DECL|macro|iu_iir
mdefine_line|#define iu_iir u3.iir
DECL|macro|iu_fcr
mdefine_line|#define iu_fcr u3.fcr
DECL|macro|IO_BASE_64
mdefine_line|#define IO_BASE_64&t;0x9000000000000000ULL
DECL|function|readb_outer_space
r_static
r_int
r_char
id|readb_outer_space
c_func
(paren
r_int
r_int
id|phys
)paren
(brace
r_int
r_int
r_int
id|vaddr
op_assign
id|IO_BASE_64
op_or
id|phys
suffix:semicolon
r_int
r_char
id|res
suffix:semicolon
r_int
r_int
id|sr
suffix:semicolon
id|sr
op_assign
id|read_c0_status
c_func
(paren
)paren
suffix:semicolon
id|write_c0_status
c_func
(paren
(paren
id|sr
op_or
id|ST0_KX
)paren
op_amp
op_complement
id|ST0_IE
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sll&t;$0, $0, 2&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sll&t;$0, $0, 2&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sll&t;$0, $0, 2&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sll&t;$0, $0, 2&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;&t;.set&t;mips3&t;&t;&bslash;n&quot;
l_string|&quot;&t;ld&t;%0, (%0)&t;&bslash;n&quot;
l_string|&quot;&t;lbu&t;%0, (%0)&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;mips0&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
op_amp
id|vaddr
)paren
)paren
suffix:semicolon
id|write_c0_status
c_func
(paren
id|sr
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sll&t;$0, $0, 2&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sll&t;$0, $0, 2&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sll&t;$0, $0, 2&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sll&t;$0, $0, 2&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|writeb_outer_space
r_static
r_void
id|writeb_outer_space
c_func
(paren
r_int
r_int
id|phys
comma
r_int
r_char
id|c
)paren
(brace
r_int
r_int
r_int
id|vaddr
op_assign
id|IO_BASE_64
op_or
id|phys
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_int
r_int
id|sr
suffix:semicolon
id|sr
op_assign
id|read_c0_status
c_func
(paren
)paren
suffix:semicolon
id|write_c0_status
c_func
(paren
(paren
id|sr
op_or
id|ST0_KX
)paren
op_amp
op_complement
id|ST0_IE
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sll&t;$0, $0, 2&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sll&t;$0, $0, 2&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sll&t;$0, $0, 2&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sll&t;$0, $0, 2&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;&t;.set&t;mips3&t;&t;&bslash;n&quot;
l_string|&quot;&t;ld&t;%0, (%1)&t;&bslash;n&quot;
l_string|&quot;&t;sb&t;%2, (%0)&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;mips0&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|vaddr
)paren
comma
l_string|&quot;r&quot;
(paren
id|c
)paren
)paren
suffix:semicolon
id|write_c0_status
c_func
(paren
id|sr
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sll&t;$0, $0, 2&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sll&t;$0, $0, 2&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sll&t;$0, $0, 2&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sll&t;$0, $0, 2&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|prom_putchar
r_void
id|prom_putchar
c_func
(paren
r_char
id|c
)paren
(brace
r_int
r_int
id|lsr
op_assign
l_int|0xfd000008UL
op_plus
m_offsetof
(paren
r_struct
id|yo_uartregs
comma
id|iu_lsr
)paren
suffix:semicolon
r_int
r_int
id|thr
op_assign
l_int|0xfd000008UL
op_plus
m_offsetof
(paren
r_struct
id|yo_uartregs
comma
id|iu_thr
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|readb_outer_space
c_func
(paren
id|lsr
)paren
op_amp
l_int|0x20
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|writeb_outer_space
c_func
(paren
id|thr
comma
id|c
)paren
suffix:semicolon
)brace
DECL|function|prom_getchar
r_char
id|__init
id|prom_getchar
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof

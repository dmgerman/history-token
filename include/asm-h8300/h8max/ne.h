multiline_comment|/* H8MAX RTL8019AS Config */
DECL|macro|NE2000_ADDR
mdefine_line|#define NE2000_ADDR&t;&t;0x800600
DECL|macro|NE2000_IRQ
mdefine_line|#define NE2000_IRQ              4
DECL|macro|NE2000_IRQ_VECTOR
mdefine_line|#define NE2000_IRQ_VECTOR&t;(12 + NE2000_IRQ)
DECL|macro|NE2000_BYTE
mdefine_line|#define&t;NE2000_BYTE&t;&t;volatile unsigned short
DECL|macro|IER
mdefine_line|#define IER                     0xfee015
DECL|macro|ISR
mdefine_line|#define ISR&t;&t;&t;0xfee016
DECL|macro|IRQ_MASK
mdefine_line|#define IRQ_MASK&t;&t;(1 &lt;&lt; NE2000_IRQ)
multiline_comment|/* sorry quick hack */
macro_line|#if defined(outb)
DECL|macro|outb
macro_line|# undef outb
macro_line|#endif
DECL|macro|outb
mdefine_line|#define outb(d,a)               h8max_outb((d),(a) - NE2000_ADDR)
macro_line|#if defined(inb)
DECL|macro|inb
macro_line|# undef inb
macro_line|#endif
DECL|macro|inb
mdefine_line|#define inb(a)                  h8max_inb((a) - NE2000_ADDR)
macro_line|#if defined(outb_p)
DECL|macro|outb_p
macro_line|# undef outb_p
macro_line|#endif
DECL|macro|outb_p
mdefine_line|#define outb_p(d,a)             h8max_outb((d),(a) - NE2000_ADDR)
macro_line|#if defined(inb_p)
DECL|macro|inb_p
macro_line|# undef inb_p
macro_line|#endif
DECL|macro|inb_p
mdefine_line|#define inb_p(a)                h8max_inb((a) - NE2000_ADDR)
macro_line|#if defined(outsw)
DECL|macro|outsw
macro_line|# undef outsw
macro_line|#endif
DECL|macro|outsw
mdefine_line|#define outsw(a,p,l)            h8max_outsw((a) - NE2000_ADDR,(unsigned short *)p,l)
macro_line|#if defined(insw)
DECL|macro|insw
macro_line|# undef insw
macro_line|#endif
DECL|macro|insw
mdefine_line|#define insw(a,p,l)             h8max_insw((a) - NE2000_ADDR,(unsigned short *)p,l)
DECL|macro|H8300_INIT_NE
mdefine_line|#define H8300_INIT_NE()                  &bslash;&n;do {                                     &bslash;&n;&t;wordlength = 2;                  &bslash;&n;&t;h8max_outb(0x49, ioaddr + EN0_DCFG); &bslash;&n;&t;SA_prom[14] = SA_prom[15] = 0x57;&bslash;&n;} while(0)
DECL|function|h8max_outb
r_static
r_inline
r_void
id|h8max_outb
c_func
(paren
r_int
r_char
id|d
comma
r_int
r_char
id|a
)paren
(brace
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|NE2000_ADDR
op_plus
(paren
id|a
op_lshift
l_int|1
)paren
)paren
op_assign
id|d
suffix:semicolon
)brace
DECL|function|h8max_inb
r_static
r_inline
r_int
r_char
id|h8max_inb
c_func
(paren
r_int
r_char
id|a
)paren
(brace
r_return
op_star
(paren
r_int
r_char
op_star
)paren
(paren
id|NE2000_ADDR
op_plus
(paren
id|a
op_lshift
l_int|1
)paren
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|h8max_outsw
r_static
r_inline
r_void
id|h8max_outsw
c_func
(paren
r_int
r_char
id|a
comma
r_int
r_int
op_star
id|p
comma
r_int
r_int
id|l
)paren
(brace
r_int
r_int
id|d
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|l
op_ne
l_int|0
suffix:semicolon
op_decrement
id|l
comma
id|p
op_increment
)paren
(brace
id|d
op_assign
(paren
(paren
(paren
op_star
id|p
)paren
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
op_or
(paren
(paren
op_star
id|p
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|NE2000_ADDR
op_plus
(paren
id|a
op_lshift
l_int|1
)paren
)paren
op_assign
id|d
suffix:semicolon
)brace
)brace
DECL|function|h8max_insw
r_static
r_inline
r_void
id|h8max_insw
c_func
(paren
r_int
r_char
id|a
comma
r_int
r_int
op_star
id|p
comma
r_int
r_int
id|l
)paren
(brace
r_int
r_int
id|d
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|l
op_ne
l_int|0
suffix:semicolon
op_decrement
id|l
comma
id|p
op_increment
)paren
(brace
id|d
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|NE2000_ADDR
op_plus
(paren
id|a
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
op_star
id|p
op_assign
(paren
id|d
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|d
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
)brace
eof

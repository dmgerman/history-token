multiline_comment|/* EDOSK2674 board depend header */
multiline_comment|/* TIMER rate define */
macro_line|#ifdef H8300_TIMER_DEFINE
DECL|macro|H8300_TIMER_COUNT_DATA
mdefine_line|#define H8300_TIMER_COUNT_DATA 33000*10/8192
DECL|macro|H8300_TIMER_FREQ
mdefine_line|#define H8300_TIMER_FREQ 33000*1000/8192
macro_line|#endif
multiline_comment|/* EDOSK-2674R SMSC Network Controler Target Depend impliments */
macro_line|#ifdef H8300_SMSC_DEFINE
DECL|macro|SMSC_BASE
mdefine_line|#define SMSC_BASE 0xf80000
DECL|macro|SMSC_IRQ
mdefine_line|#define SMSC_IRQ 16
multiline_comment|/* sorry quick hack */
macro_line|#if defined(outw)
DECL|macro|outw
macro_line|# undef outw
macro_line|#endif
DECL|macro|outw
mdefine_line|#define outw(d,a) edosk2674_smsc_outw(d,(volatile unsigned short *)(a))
macro_line|#if defined(inw)
DECL|macro|inw
macro_line|# undef inw
macro_line|#endif
DECL|macro|inw
mdefine_line|#define inw(a) edosk2674_smsc_inw((volatile unsigned short *)(a))
macro_line|#if defined(outsw)
DECL|macro|outsw
macro_line|# undef outsw
macro_line|#endif
DECL|macro|outsw
mdefine_line|#define outsw(a,p,l) edosk2674_smsc_outsw((volatile unsigned short *)(a),p,l)
macro_line|#if defined(insw)
DECL|macro|insw
macro_line|# undef insw
macro_line|#endif
DECL|macro|insw
mdefine_line|#define insw(a,p,l) edosk2674_smsc_insw((volatile unsigned short *)(a),p,l)
DECL|function|edosk2674_smsc_outw
r_static
r_inline
r_void
id|edosk2674_smsc_outw
c_func
(paren
r_int
r_int
id|d
comma
r_volatile
r_int
r_int
op_star
id|a
)paren
(brace
op_star
id|a
op_assign
(paren
id|d
op_rshift
l_int|8
)paren
op_or
(paren
id|d
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|edosk2674_smsc_inw
r_static
r_inline
r_int
r_int
id|edosk2674_smsc_inw
c_func
(paren
r_volatile
r_int
r_int
op_star
id|a
)paren
(brace
r_int
r_int
id|d
suffix:semicolon
id|d
op_assign
op_star
id|a
suffix:semicolon
r_return
(paren
id|d
op_rshift
l_int|8
)paren
op_or
(paren
id|d
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|edosk2674_smsc_outsw
r_static
r_inline
r_void
id|edosk2674_smsc_outsw
c_func
(paren
r_volatile
r_int
r_int
op_star
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
op_star
id|a
op_assign
op_star
id|p
suffix:semicolon
)brace
DECL|function|edosk2674_smsc_insw
r_static
r_inline
r_void
id|edosk2674_smsc_insw
c_func
(paren
r_volatile
r_int
r_int
op_star
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
op_star
id|p
op_assign
op_star
id|a
suffix:semicolon
)brace
macro_line|#endif
eof

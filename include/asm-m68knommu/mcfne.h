multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;mcfne.h -- NE2000 in ColdFire eval boards.&n; *&n; *&t;(C) Copyright 1999-2000, Greg Ungerer (gerg@snapgear.com)&n; *&t;(C) Copyright 2000,      Lineo (www.lineo.com)&n; *&t;(C) Copyright 2001,      SnapGear (www.snapgear.com)&n; *&n; *      19990409 David W. Miller  Converted from m5206ne.h for 5307 eval board&n; *&n; *      Hacked support for m5206e Cadre III evaluation board&n; *      Fred Stevens (fred.stevens@pemstar.com) 13 April 1999&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;mcfne_h
DECL|macro|mcfne_h
mdefine_line|#define&t;mcfne_h
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *&t;Support for NE2000 clones devices in ColdFire based boards.&n; *&t;Not all boards address these parts the same way, some use a&n; *&t;direct addressing method, others use a side-band address space&n; *&t;to access odd address registers, some require byte swapping&n; *&t;others do not.&n; */
DECL|macro|BSWAP
mdefine_line|#define&t;BSWAP(w)&t;(((w) &lt;&lt; 8) | ((w) &gt;&gt; 8))
DECL|macro|RSWAP
mdefine_line|#define&t;RSWAP(w)&t;(w)
multiline_comment|/*&n; *&t;Define the basic hardware resources of NE2000 boards.&n; */
macro_line|#if defined(CONFIG_M5206) &amp;&amp; defined(CONFIG_ARNEWSH)
DECL|macro|NE2000_ADDR
mdefine_line|#define NE2000_ADDR&t;&t;0x40000300
DECL|macro|NE2000_ODDOFFSET
mdefine_line|#define NE2000_ODDOFFSET&t;0x00010000
DECL|macro|NE2000_IRQ_VECTOR
mdefine_line|#define&t;NE2000_IRQ_VECTOR&t;0xf0
DECL|macro|NE2000_IRQ_PRIORITY
mdefine_line|#define&t;NE2000_IRQ_PRIORITY&t;2
DECL|macro|NE2000_IRQ_LEVEL
mdefine_line|#define&t;NE2000_IRQ_LEVEL&t;4
DECL|macro|NE2000_BYTE
mdefine_line|#define&t;NE2000_BYTE&t;&t;volatile unsigned short
macro_line|#endif
macro_line|#if defined(CONFIG_M5206e) &amp;&amp; defined(CONFIG_MOTOROLA)
DECL|macro|NE2000_ADDR
mdefine_line|#define&t;NE2000_ADDR&t;&t;0x40000300
DECL|macro|NE2000_ODDOFFSET
mdefine_line|#define&t;NE2000_ODDOFFSET&t;0x00010000
DECL|macro|NE2000_IRQ_VECTOR
mdefine_line|#define&t;NE2000_IRQ_VECTOR&t;0x1c
DECL|macro|NE2000_IRQ_PRIORITY
mdefine_line|#define&t;NE2000_IRQ_PRIORITY&t;2
DECL|macro|NE2000_IRQ_LEVEL
mdefine_line|#define&t;NE2000_IRQ_LEVEL&t;4
DECL|macro|NE2000_BYTE
mdefine_line|#define&t;NE2000_BYTE&t;&t;volatile unsigned short
macro_line|#endif
macro_line|#if defined(CONFIG_M5206e) &amp;&amp; defined(CONFIG_NETtel)
DECL|macro|NE2000_ADDR
mdefine_line|#define NE2000_ADDR&t;&t;0x30000300
DECL|macro|NE2000_IRQ_VECTOR
mdefine_line|#define NE2000_IRQ_VECTOR&t;25
DECL|macro|NE2000_IRQ_PRIORITY
mdefine_line|#define NE2000_IRQ_PRIORITY&t;1
DECL|macro|NE2000_IRQ_LEVEL
mdefine_line|#define NE2000_IRQ_LEVEL&t;3
DECL|macro|NE2000_BYTE
mdefine_line|#define&t;NE2000_BYTE&t;&t;volatile unsigned char
macro_line|#endif
macro_line|#if defined(CONFIG_M5206e) &amp;&amp; defined(CONFIG_CFV240)
DECL|macro|NE2000_ADDR
mdefine_line|#define NE2000_ADDR             0x40010000
DECL|macro|NE2000_ADDR1
mdefine_line|#define NE2000_ADDR1            0x40010001
DECL|macro|NE2000_ODDOFFSET
mdefine_line|#define NE2000_ODDOFFSET        0x00000000
DECL|macro|NE2000_IRQ
mdefine_line|#define NE2000_IRQ              1
DECL|macro|NE2000_IRQ_VECTOR
mdefine_line|#define NE2000_IRQ_VECTOR       0x19
DECL|macro|NE2000_IRQ_PRIORITY
mdefine_line|#define NE2000_IRQ_PRIORITY     2
DECL|macro|NE2000_IRQ_LEVEL
mdefine_line|#define NE2000_IRQ_LEVEL        1
DECL|macro|NE2000_BYTE
mdefine_line|#define&t;NE2000_BYTE&t;&t;volatile unsigned char
macro_line|#endif
macro_line|#if defined(CONFIG_M5307) &amp;&amp; defined(CONFIG_MOTOROLA)
DECL|macro|NE2000_ADDR
mdefine_line|#define NE2000_ADDR&t;&t;0x40000300
DECL|macro|NE2000_ODDOFFSET
mdefine_line|#define NE2000_ODDOFFSET&t;0x00010000
DECL|macro|NE2000_IRQ_VECTOR
mdefine_line|#define NE2000_IRQ_VECTOR&t;0x1b
DECL|macro|NE2000_BYTE
mdefine_line|#define&t;NE2000_BYTE&t;&t;volatile unsigned short
macro_line|#endif
macro_line|#if defined(CONFIG_M5272) &amp;&amp; defined(CONFIG_NETtel)
DECL|macro|NE2000_ADDR
mdefine_line|#define NE2000_ADDR&t;&t;0x30600300
DECL|macro|NE2000_ODDOFFSET
mdefine_line|#define NE2000_ODDOFFSET&t;0x00008000
DECL|macro|NE2000_IRQ_VECTOR
mdefine_line|#define NE2000_IRQ_VECTOR&t;67
DECL|macro|BSWAP
macro_line|#undef&t;BSWAP
DECL|macro|BSWAP
mdefine_line|#define&t;BSWAP(w)&t;&t;(w)
DECL|macro|NE2000_BYTE
mdefine_line|#define&t;NE2000_BYTE&t;&t;volatile unsigned short
DECL|macro|RSWAP
macro_line|#undef&t;RSWAP
DECL|macro|RSWAP
mdefine_line|#define&t;RSWAP(w)&t;&t;(((w) &lt;&lt; 8) | ((w) &gt;&gt; 8))
macro_line|#endif
macro_line|#if defined(CONFIG_M5307) &amp;&amp; defined(CONFIG_NETtel)
DECL|macro|NE2000_ADDR0
mdefine_line|#define NE2000_ADDR0&t;&t;0x30600300
DECL|macro|NE2000_ADDR1
mdefine_line|#define NE2000_ADDR1&t;&t;0x30800300
DECL|macro|NE2000_ODDOFFSET
mdefine_line|#define NE2000_ODDOFFSET&t;0x00008000
DECL|macro|NE2000_IRQ_VECTOR0
mdefine_line|#define NE2000_IRQ_VECTOR0&t;27
DECL|macro|NE2000_IRQ_VECTOR1
mdefine_line|#define NE2000_IRQ_VECTOR1&t;29
DECL|macro|BSWAP
macro_line|#undef&t;BSWAP
DECL|macro|BSWAP
mdefine_line|#define&t;BSWAP(w)&t;&t;(w)
DECL|macro|NE2000_BYTE
mdefine_line|#define&t;NE2000_BYTE&t;&t;volatile unsigned short
DECL|macro|RSWAP
macro_line|#undef&t;RSWAP
DECL|macro|RSWAP
mdefine_line|#define&t;RSWAP(w)&t;&t;(((w) &lt;&lt; 8) | ((w) &gt;&gt; 8))
macro_line|#endif
macro_line|#if defined(CONFIG_M5307) &amp;&amp; defined(CONFIG_SECUREEDGEMP3)
DECL|macro|NE2000_ADDR
mdefine_line|#define NE2000_ADDR&t;&t;0x30600300
DECL|macro|NE2000_ODDOFFSET
mdefine_line|#define NE2000_ODDOFFSET&t;0x00008000
DECL|macro|NE2000_IRQ_VECTOR
mdefine_line|#define NE2000_IRQ_VECTOR&t;27
DECL|macro|BSWAP
macro_line|#undef&t;BSWAP
DECL|macro|BSWAP
mdefine_line|#define&t;BSWAP(w)&t;&t;(w)
DECL|macro|NE2000_BYTE
mdefine_line|#define&t;NE2000_BYTE&t;&t;volatile unsigned short
DECL|macro|RSWAP
macro_line|#undef&t;RSWAP
DECL|macro|RSWAP
mdefine_line|#define&t;RSWAP(w)&t;&t;(((w) &lt;&lt; 8) | ((w) &gt;&gt; 8))
macro_line|#endif
macro_line|#if defined(CONFIG_M5307) &amp;&amp; defined(CONFIG_ARNEWSH)
DECL|macro|NE2000_ADDR
mdefine_line|#define NE2000_ADDR&t;&t;0xfe600300
DECL|macro|NE2000_ODDOFFSET
mdefine_line|#define NE2000_ODDOFFSET&t;0x00010000
DECL|macro|NE2000_IRQ_VECTOR
mdefine_line|#define NE2000_IRQ_VECTOR&t;0x1b
DECL|macro|NE2000_IRQ_PRIORITY
mdefine_line|#define NE2000_IRQ_PRIORITY&t;2
DECL|macro|NE2000_IRQ_LEVEL
mdefine_line|#define NE2000_IRQ_LEVEL&t;3
DECL|macro|NE2000_BYTE
mdefine_line|#define&t;NE2000_BYTE&t;&t;volatile unsigned short
macro_line|#endif
macro_line|#if defined(CONFIG_M5407)
DECL|macro|NE2000_ADDR
mdefine_line|#define NE2000_ADDR&t;&t;0x40000300
DECL|macro|NE2000_ODDOFFSET
mdefine_line|#define NE2000_ODDOFFSET&t;0x00010000
DECL|macro|NE2000_IRQ_VECTOR
mdefine_line|#define NE2000_IRQ_VECTOR&t;0x1b
DECL|macro|NE2000_BYTE
mdefine_line|#define&t;NE2000_BYTE&t;&t;volatile unsigned short
macro_line|#endif
multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;Side-band address space for odd address requires re-mapping&n; *&t;many of the standard ISA access functions.&n; */
macro_line|#ifdef NE2000_ODDOFFSET
DECL|macro|outb
macro_line|#undef outb
DECL|macro|outb_p
macro_line|#undef outb_p
DECL|macro|inb
macro_line|#undef inb
DECL|macro|inb_p
macro_line|#undef inb_p
DECL|macro|outsb
macro_line|#undef outsb
DECL|macro|outsw
macro_line|#undef outsw
DECL|macro|insb
macro_line|#undef insb
DECL|macro|insw
macro_line|#undef insw
DECL|macro|outb
mdefine_line|#define&t;outb&t;ne2000_outb
DECL|macro|inb
mdefine_line|#define&t;inb&t;ne2000_inb
DECL|macro|outb_p
mdefine_line|#define&t;outb_p&t;ne2000_outb
DECL|macro|inb_p
mdefine_line|#define&t;inb_p&t;ne2000_inb
DECL|macro|outsb
mdefine_line|#define&t;outsb&t;ne2000_outsb
DECL|macro|outsw
mdefine_line|#define&t;outsw&t;ne2000_outsw
DECL|macro|insb
mdefine_line|#define&t;insb&t;ne2000_insb
DECL|macro|insw
mdefine_line|#define&t;insw&t;ne2000_insw
macro_line|#ifndef COLDFIRE_NE2000_FUNCS
r_void
id|ne2000_outb
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
r_int
id|ne2000_inb
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_void
id|ne2000_insb
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|vbuf
comma
r_int
r_int
r_int
id|len
)paren
suffix:semicolon
r_void
id|ne2000_insw
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|vbuf
comma
r_int
r_int
id|len
)paren
suffix:semicolon
r_void
id|ne2000_outsb
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|vbuf
comma
r_int
r_int
id|len
)paren
suffix:semicolon
r_void
id|ne2000_outsw
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|vbuf
comma
r_int
r_int
id|len
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/*&n; *&t;This macro converts a conventional register address into the&n; *&t;real memory pointer of the mapped NE2000 device.&n; *&t;On most NE2000 implementations on ColdFire boards the chip is&n; *&t;mapped in kinda funny, due to its ISA heritage.&n; */
macro_line|#ifdef CONFIG_CFV240
DECL|macro|NE2000_PTR
mdefine_line|#define NE2000_PTR(addr)&t;(NE2000_ADDR + ((addr &amp; 0x3f) &lt;&lt; 1) + 1)
DECL|macro|NE2000_DATA_PTR
mdefine_line|#define NE2000_DATA_PTR(addr)&t;(NE2000_ADDR + ((addr &amp; 0x3f) &lt;&lt; 1))
macro_line|#else
DECL|macro|NE2000_PTR
mdefine_line|#define&t;NE2000_PTR(addr)&t;((addr&amp;0x1)?(NE2000_ODDOFFSET+addr-1):(addr))
DECL|macro|NE2000_DATA_PTR
mdefine_line|#define&t;NE2000_DATA_PTR(addr)&t;(addr)
macro_line|#endif
DECL|function|ne2000_outb
r_void
id|ne2000_outb
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|addr
)paren
(brace
id|NE2000_BYTE
op_star
id|rp
suffix:semicolon
id|rp
op_assign
(paren
id|NE2000_BYTE
op_star
)paren
id|NE2000_PTR
c_func
(paren
id|addr
)paren
suffix:semicolon
op_star
id|rp
op_assign
id|RSWAP
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
DECL|function|ne2000_inb
r_int
id|ne2000_inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|NE2000_BYTE
op_star
id|rp
comma
id|val
suffix:semicolon
id|rp
op_assign
(paren
id|NE2000_BYTE
op_star
)paren
id|NE2000_PTR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|val
op_assign
op_star
id|rp
suffix:semicolon
r_return
(paren
r_int
)paren
(paren
(paren
id|NE2000_BYTE
)paren
id|RSWAP
c_func
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
DECL|function|ne2000_insb
r_void
id|ne2000_insb
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|vbuf
comma
r_int
r_int
r_int
id|len
)paren
(brace
id|NE2000_BYTE
op_star
id|rp
comma
id|val
suffix:semicolon
r_int
r_char
op_star
id|buf
suffix:semicolon
id|buf
op_assign
(paren
r_int
r_char
op_star
)paren
id|vbuf
suffix:semicolon
id|rp
op_assign
(paren
id|NE2000_BYTE
op_star
)paren
id|NE2000_DATA_PTR
c_func
(paren
id|addr
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|len
OG
l_int|0
)paren
suffix:semicolon
id|len
op_decrement
)paren
(brace
id|val
op_assign
op_star
id|rp
suffix:semicolon
op_star
id|buf
op_increment
op_assign
id|RSWAP
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
)brace
DECL|function|ne2000_insw
r_void
id|ne2000_insw
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|vbuf
comma
r_int
r_int
id|len
)paren
(brace
r_volatile
r_int
r_int
op_star
id|rp
suffix:semicolon
r_int
r_int
id|w
comma
op_star
id|buf
suffix:semicolon
id|buf
op_assign
(paren
r_int
r_int
op_star
)paren
id|vbuf
suffix:semicolon
id|rp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|NE2000_DATA_PTR
c_func
(paren
id|addr
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|len
OG
l_int|0
)paren
suffix:semicolon
id|len
op_decrement
)paren
(brace
id|w
op_assign
op_star
id|rp
suffix:semicolon
op_star
id|buf
op_increment
op_assign
id|BSWAP
c_func
(paren
id|w
)paren
suffix:semicolon
)brace
)brace
DECL|function|ne2000_outsb
r_void
id|ne2000_outsb
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|vbuf
comma
r_int
r_int
id|len
)paren
(brace
id|NE2000_BYTE
op_star
id|rp
comma
id|val
suffix:semicolon
r_int
r_char
op_star
id|buf
suffix:semicolon
id|buf
op_assign
(paren
r_int
r_char
op_star
)paren
id|vbuf
suffix:semicolon
id|rp
op_assign
(paren
id|NE2000_BYTE
op_star
)paren
id|NE2000_DATA_PTR
c_func
(paren
id|addr
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|len
OG
l_int|0
)paren
suffix:semicolon
id|len
op_decrement
)paren
(brace
id|val
op_assign
op_star
id|buf
op_increment
suffix:semicolon
op_star
id|rp
op_assign
id|RSWAP
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
)brace
DECL|function|ne2000_outsw
r_void
id|ne2000_outsw
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|vbuf
comma
r_int
r_int
id|len
)paren
(brace
r_volatile
r_int
r_int
op_star
id|rp
suffix:semicolon
r_int
r_int
id|w
comma
op_star
id|buf
suffix:semicolon
id|buf
op_assign
(paren
r_int
r_int
op_star
)paren
id|vbuf
suffix:semicolon
id|rp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|NE2000_DATA_PTR
c_func
(paren
id|addr
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|len
OG
l_int|0
)paren
suffix:semicolon
id|len
op_decrement
)paren
(brace
id|w
op_assign
op_star
id|buf
op_increment
suffix:semicolon
op_star
id|rp
op_assign
id|BSWAP
c_func
(paren
id|w
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* COLDFIRE_NE2000_FUNCS */
macro_line|#endif /* NE2000_OFFOFFSET */
multiline_comment|/****************************************************************************/
macro_line|#ifdef COLDFIRE_NE2000_FUNCS
multiline_comment|/*&n; *&t;Lastly the interrupt set up code...&n; *&t;Minor differences between the different board types.&n; */
macro_line|#if defined(CONFIG_M5206) &amp;&amp; defined(CONFIG_ARNEWSH)
DECL|function|ne2000_irqsetup
r_void
id|ne2000_irqsetup
c_func
(paren
r_int
id|irq
)paren
(brace
r_volatile
r_int
r_char
op_star
id|icrp
suffix:semicolon
id|icrp
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|MCF_MBAR
op_plus
id|MCFSIM_ICR4
)paren
suffix:semicolon
op_star
id|icrp
op_assign
id|MCFSIM_ICR_LEVEL4
op_or
id|MCFSIM_ICR_PRI2
suffix:semicolon
id|mcf_setimr
c_func
(paren
id|mcf_getimr
c_func
(paren
)paren
op_amp
op_complement
id|MCFSIM_IMR_EINT4
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_M5206e) &amp;&amp; defined(CONFIG_MOTOROLA)
DECL|function|ne2000_irqsetup
r_void
id|ne2000_irqsetup
c_func
(paren
r_int
id|irq
)paren
(brace
r_volatile
r_int
r_char
op_star
id|icrp
suffix:semicolon
id|icrp
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|MCF_MBAR
op_plus
id|MCFSIM_ICR4
)paren
suffix:semicolon
op_star
id|icrp
op_assign
id|MCFSIM_ICR_LEVEL4
op_or
id|MCFSIM_ICR_PRI2
op_or
id|MCFSIM_ICR_AUTOVEC
suffix:semicolon
id|mcf_setimr
c_func
(paren
id|mcf_getimr
c_func
(paren
)paren
op_amp
op_complement
id|MCFSIM_IMR_EINT4
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_M5206e) &amp;&amp; defined(CONFIG_CFV240)
DECL|function|ne2000_irqsetup
r_void
id|ne2000_irqsetup
c_func
(paren
r_int
id|irq
)paren
(brace
r_volatile
r_int
r_char
op_star
id|icrp
suffix:semicolon
id|icrp
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|MCF_MBAR
op_plus
id|MCFSIM_ICR1
)paren
suffix:semicolon
op_star
id|icrp
op_assign
id|MCFSIM_ICR_LEVEL1
op_or
id|MCFSIM_ICR_PRI2
op_or
id|MCFSIM_ICR_AUTOVEC
suffix:semicolon
id|mcf_setimr
c_func
(paren
id|mcf_getimr
c_func
(paren
)paren
op_amp
op_complement
id|MCFSIM_IMR_EINT1
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_M5206e) &amp;&amp; defined(CONFIG_NETtel)
DECL|function|ne2000_irqsetup
r_void
id|ne2000_irqsetup
c_func
(paren
r_int
id|irq
)paren
(brace
id|mcf_autovector
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_M5272) &amp;&amp; defined(CONFIG_NETtel)
DECL|function|ne2000_irqsetup
r_void
id|ne2000_irqsetup
c_func
(paren
r_int
id|irq
)paren
(brace
r_volatile
r_int
r_int
op_star
id|icrp
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|pitr
suffix:semicolon
multiline_comment|/* The NE2000 device uses external IRQ3 */
id|icrp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|MCF_MBAR
op_plus
id|MCFSIM_ICR1
)paren
suffix:semicolon
op_star
id|icrp
op_assign
(paren
op_star
id|icrp
op_amp
l_int|0x77077777
)paren
op_or
l_int|0x00d00000
suffix:semicolon
id|pitr
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|MCF_MBAR
op_plus
id|MCFSIM_PITR
)paren
suffix:semicolon
op_star
id|pitr
op_assign
op_star
id|pitr
op_or
l_int|0x20000000
suffix:semicolon
)brace
DECL|function|ne2000_irqack
r_void
id|ne2000_irqack
c_func
(paren
r_int
id|irq
)paren
(brace
r_volatile
r_int
r_int
op_star
id|icrp
suffix:semicolon
multiline_comment|/* The NE2000 device uses external IRQ3 */
id|icrp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|MCF_MBAR
op_plus
id|MCFSIM_ICR1
)paren
suffix:semicolon
op_star
id|icrp
op_assign
(paren
op_star
id|icrp
op_amp
l_int|0x77777777
)paren
op_or
l_int|0x00800000
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_M5307) || defined(CONFIG_M5407)
macro_line|#if defined(CONFIG_NETtel) || defined(CONFIG_SECUREEDGEMP3)
DECL|function|ne2000_irqsetup
r_void
id|ne2000_irqsetup
c_func
(paren
r_int
id|irq
)paren
(brace
id|mcf_setimr
c_func
(paren
id|mcf_getimr
c_func
(paren
)paren
op_amp
op_complement
id|MCFSIM_IMR_EINT3
)paren
suffix:semicolon
id|mcf_autovector
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|ne2000_irqsetup
r_void
id|ne2000_irqsetup
c_func
(paren
r_int
id|irq
)paren
(brace
id|mcf_setimr
c_func
(paren
id|mcf_getimr
c_func
(paren
)paren
op_amp
op_complement
id|MCFSIM_IMR_EINT3
)paren
suffix:semicolon
)brace
macro_line|#endif /* ! CONFIG_NETtel || CONFIG_SECUREEDGEMP3 */
macro_line|#endif /* CONFIG_M5307 || CONFIG_M5407 */
macro_line|#endif /* COLDFIRE_NE2000_FUNCS */
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* mcfne_h */
eof

multiline_comment|/*&n; * bus_ops.h 1.10 2000/06/12 21:55:41&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_BUS_OPS_H
DECL|macro|_LINUX_BUS_OPS_H
mdefine_line|#define _LINUX_BUS_OPS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_VIRTUAL_BUS
DECL|struct|bus_operations
r_typedef
r_struct
id|bus_operations
(brace
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
DECL|member|b_in
id|u32
(paren
op_star
id|b_in
)paren
(paren
r_void
op_star
id|bus
comma
id|u32
id|port
comma
id|s32
id|sz
)paren
suffix:semicolon
DECL|member|b_ins
r_void
(paren
op_star
id|b_ins
)paren
(paren
r_void
op_star
id|bus
comma
id|u32
id|port
comma
r_void
op_star
id|buf
comma
id|u32
id|count
comma
id|s32
id|sz
)paren
suffix:semicolon
DECL|member|b_out
r_void
(paren
op_star
id|b_out
)paren
(paren
r_void
op_star
id|bus
comma
id|u32
id|val
comma
id|u32
id|port
comma
id|s32
id|sz
)paren
suffix:semicolon
DECL|member|b_outs
r_void
(paren
op_star
id|b_outs
)paren
(paren
r_void
op_star
id|bus
comma
id|u32
id|port
comma
r_void
op_star
id|buf
comma
id|u32
id|count
comma
id|s32
id|sz
)paren
suffix:semicolon
DECL|member|b_ioremap
r_void
op_star
(paren
op_star
id|b_ioremap
)paren
(paren
r_void
op_star
id|bus
comma
id|u_long
id|ofs
comma
id|u_long
id|sz
)paren
suffix:semicolon
DECL|member|b_iounmap
r_void
(paren
op_star
id|b_iounmap
)paren
(paren
r_void
op_star
id|bus
comma
r_void
op_star
id|addr
)paren
suffix:semicolon
DECL|member|b_read
id|u32
(paren
op_star
id|b_read
)paren
(paren
r_void
op_star
id|bus
comma
r_void
op_star
id|addr
comma
id|s32
id|sz
)paren
suffix:semicolon
DECL|member|b_write
r_void
(paren
op_star
id|b_write
)paren
(paren
r_void
op_star
id|bus
comma
id|u32
id|val
comma
r_void
op_star
id|addr
comma
id|s32
id|sz
)paren
suffix:semicolon
DECL|member|b_copy_from
r_void
(paren
op_star
id|b_copy_from
)paren
(paren
r_void
op_star
id|bus
comma
r_void
op_star
id|d
comma
r_void
op_star
id|s
comma
id|u32
id|count
)paren
suffix:semicolon
DECL|member|b_copy_to
r_void
(paren
op_star
id|b_copy_to
)paren
(paren
r_void
op_star
id|bus
comma
r_void
op_star
id|d
comma
r_void
op_star
id|s
comma
id|u32
id|count
)paren
suffix:semicolon
DECL|member|b_request_irq
r_int
(paren
op_star
id|b_request_irq
)paren
(paren
r_void
op_star
id|bus
comma
id|u_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
id|u_long
id|flags
comma
r_const
r_char
op_star
id|device
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
DECL|member|b_free_irq
r_void
(paren
op_star
id|b_free_irq
)paren
(paren
r_void
op_star
id|bus
comma
id|u_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
DECL|typedef|bus_operations
)brace
id|bus_operations
suffix:semicolon
DECL|macro|bus_inb
mdefine_line|#define bus_inb(b,p)&t;&t;(b)-&gt;b_in((b),(p),0)
DECL|macro|bus_inw
mdefine_line|#define bus_inw(b,p)&t;&t;(b)-&gt;b_in((b),(p),1)
DECL|macro|bus_inl
mdefine_line|#define bus_inl(b,p)&t;&t;(b)-&gt;b_in((b),(p),2)
DECL|macro|bus_inw_ns
mdefine_line|#define bus_inw_ns(b,p)&t;&t;(b)-&gt;b_in((b),(p),-1)
DECL|macro|bus_inl_ns
mdefine_line|#define bus_inl_ns(b,p)&t;&t;(b)-&gt;b_in((b),(p),-2)
DECL|macro|bus_insb
mdefine_line|#define bus_insb(b,p,a,c)&t;(b)-&gt;b_ins((b),(p),(a),(c),0)
DECL|macro|bus_insw
mdefine_line|#define bus_insw(b,p,a,c)&t;(b)-&gt;b_ins((b),(p),(a),(c),1)
DECL|macro|bus_insl
mdefine_line|#define bus_insl(b,p,a,c)&t;(b)-&gt;b_ins((b),(p),(a),(c),2)
DECL|macro|bus_insw_ns
mdefine_line|#define bus_insw_ns(b,p,a,c)&t;(b)-&gt;b_ins((b),(p),(a),(c),-1)
DECL|macro|bus_insl_ns
mdefine_line|#define bus_insl_ns(b,p,a,c)&t;(b)-&gt;b_ins((b),(p),(a),(c),-2)
DECL|macro|bus_outb
mdefine_line|#define bus_outb(b,v,p)&t;&t;(b)-&gt;b_out((b),(v),(p),0)
DECL|macro|bus_outw
mdefine_line|#define bus_outw(b,v,p)&t;&t;(b)-&gt;b_out((b),(v),(p),1)
DECL|macro|bus_outl
mdefine_line|#define bus_outl(b,v,p)&t;&t;(b)-&gt;b_out((b),(v),(p),2)
DECL|macro|bus_outw_ns
mdefine_line|#define bus_outw_ns(b,v,p)&t;(b)-&gt;b_out((b),(v),(p),-1)
DECL|macro|bus_outl_ns
mdefine_line|#define bus_outl_ns(b,v,p)&t;(b)-&gt;b_out((b),(v),(p),-2)
DECL|macro|bus_outsb
mdefine_line|#define bus_outsb(b,p,a,c)&t;(b)-&gt;b_outs((b),(p),(a),(c),0)
DECL|macro|bus_outsw
mdefine_line|#define bus_outsw(b,p,a,c)&t;(b)-&gt;b_outs((b),(p),(a),(c),1)
DECL|macro|bus_outsl
mdefine_line|#define bus_outsl(b,p,a,c)&t;(b)-&gt;b_outs((b),(p),(a),(c),2)
DECL|macro|bus_outsw_ns
mdefine_line|#define bus_outsw_ns(b,p,a,c)&t;(b)-&gt;b_outs((b),(p),(a),(c),-1)
DECL|macro|bus_outsl_ns
mdefine_line|#define bus_outsl_ns(b,p,a,c)&t;(b)-&gt;b_outs((b),(p),(a),(c),-2)
DECL|macro|bus_readb
mdefine_line|#define bus_readb(b,a)&t;&t;(b)-&gt;b_read((b),(a),0)
DECL|macro|bus_readw
mdefine_line|#define bus_readw(b,a)&t;&t;(b)-&gt;b_read((b),(a),1)
DECL|macro|bus_readl
mdefine_line|#define bus_readl(b,a)&t;&t;(b)-&gt;b_read((b),(a),2)
DECL|macro|bus_readw_ns
mdefine_line|#define bus_readw_ns(b,a)&t;(b)-&gt;b_read((b),(a),-1)
DECL|macro|bus_readl_ns
mdefine_line|#define bus_readl_ns(b,a)&t;(b)-&gt;b_read((b),(a),-2)
DECL|macro|bus_writeb
mdefine_line|#define bus_writeb(b,v,a)&t;(b)-&gt;b_write((b),(v),(a),0)
DECL|macro|bus_writew
mdefine_line|#define bus_writew(b,v,a)&t;(b)-&gt;b_write((b),(v),(a),1)
DECL|macro|bus_writel
mdefine_line|#define bus_writel(b,v,a)&t;(b)-&gt;b_write((b),(v),(a),2)
DECL|macro|bus_writew_ns
mdefine_line|#define bus_writew_ns(b,v,a)&t;(b)-&gt;b_write((b),(v),(a),-1)
DECL|macro|bus_writel_ns
mdefine_line|#define bus_writel_ns(b,v,a)&t;(b)-&gt;b_write((b),(v),(a),-2)
DECL|macro|bus_ioremap
mdefine_line|#define bus_ioremap(b,s,n)&t;(b)-&gt;b_ioremap((b),(s),(n))
DECL|macro|bus_iounmap
mdefine_line|#define bus_iounmap(b,a)&t;(b)-&gt;b_iounmap((b),(a))
DECL|macro|bus_memcpy_fromio
mdefine_line|#define bus_memcpy_fromio(b,d,s,n) (b)-&gt;b_copy_from((b),(d),(s),(n))
DECL|macro|bus_memcpy_toio
mdefine_line|#define bus_memcpy_toio(b,d,s,n) (b)-&gt;b_copy_to((b),(d),(s),(n))
DECL|macro|bus_request_irq
mdefine_line|#define bus_request_irq(b,i,h,f,n,d) &bslash;&n;&t;&t;&t;&t;(b)-&gt;b_request_irq((b),(i),(h),(f),(n),(d))
DECL|macro|bus_free_irq
mdefine_line|#define bus_free_irq(b,i,d)&t;(b)-&gt;b_free_irq((b),(i),(d))
macro_line|#else
DECL|macro|bus_inb
mdefine_line|#define bus_inb(b,p)&t;&t;inb(p)
DECL|macro|bus_inw
mdefine_line|#define bus_inw(b,p)&t;&t;inw(p)
DECL|macro|bus_inl
mdefine_line|#define bus_inl(b,p)&t;&t;inl(p)
DECL|macro|bus_inw_ns
mdefine_line|#define bus_inw_ns(b,p)&t;&t;inw_ns(p)
DECL|macro|bus_inl_ns
mdefine_line|#define bus_inl_ns(b,p)&t;&t;inl_ns(p)
DECL|macro|bus_insb
mdefine_line|#define bus_insb(b,p,a,c)&t;insb(p,a,c)
DECL|macro|bus_insw
mdefine_line|#define bus_insw(b,p,a,c)&t;insw(p,a,c)
DECL|macro|bus_insl
mdefine_line|#define bus_insl(b,p,a,c)&t;insl(p,a,c)
DECL|macro|bus_insw_ns
mdefine_line|#define bus_insw_ns(b,p,a,c)&t;insw_ns(p,a,c)
DECL|macro|bus_insl_ns
mdefine_line|#define bus_insl_ns(b,p,a,c)&t;insl_ns(p,a,c)
DECL|macro|bus_outb
mdefine_line|#define bus_outb(b,v,p)&t;&t;outb(b,v,p)
DECL|macro|bus_outw
mdefine_line|#define bus_outw(b,v,p)&t;&t;outw(b,v,p)
DECL|macro|bus_outl
mdefine_line|#define bus_outl(b,v,p)&t;&t;outl(b,v,p)
DECL|macro|bus_outw_ns
mdefine_line|#define bus_outw_ns(b,v,p)&t;outw_ns(b,v,p)
DECL|macro|bus_outl_ns
mdefine_line|#define bus_outl_ns(b,v,p)&t;outl_ns(b,v,p)
DECL|macro|bus_outsb
mdefine_line|#define bus_outsb(b,p,a,c)&t;outsb(p,a,c)
DECL|macro|bus_outsw
mdefine_line|#define bus_outsw(b,p,a,c)&t;outsw(p,a,c)
DECL|macro|bus_outsl
mdefine_line|#define bus_outsl(b,p,a,c)&t;outsl(p,a,c)
DECL|macro|bus_outsw_ns
mdefine_line|#define bus_outsw_ns(b,p,a,c)&t;outsw_ns(p,a,c)
DECL|macro|bus_outsl_ns
mdefine_line|#define bus_outsl_ns(b,p,a,c)&t;outsl_ns(p,a,c)
DECL|macro|bus_readb
mdefine_line|#define bus_readb(b,a)&t;&t;readb(a)
DECL|macro|bus_readw
mdefine_line|#define bus_readw(b,a)&t;&t;readw(a)
DECL|macro|bus_readl
mdefine_line|#define bus_readl(b,a)&t;&t;readl(a)
DECL|macro|bus_readw_ns
mdefine_line|#define bus_readw_ns(b,a)&t;readw_ns(a)
DECL|macro|bus_readl_ns
mdefine_line|#define bus_readl_ns(b,a)&t;readl_ns(a)
DECL|macro|bus_writeb
mdefine_line|#define bus_writeb(b,v,a)&t;writeb(v,a)
DECL|macro|bus_writew
mdefine_line|#define bus_writew(b,v,a)&t;writew(v,a)
DECL|macro|bus_writel
mdefine_line|#define bus_writel(b,v,a)&t;writel(v,a)
DECL|macro|bus_writew_ns
mdefine_line|#define bus_writew_ns(b,v,a)&t;writew_ns(v,a)
DECL|macro|bus_writel_ns
mdefine_line|#define bus_writel_ns(b,v,a)&t;writel_ns(v,a)
DECL|macro|bus_ioremap
mdefine_line|#define bus_ioremap(b,s,n)&t;ioremap(s,n)
DECL|macro|bus_iounmap
mdefine_line|#define bus_iounmap(b,a)&t;iounmap(a)
DECL|macro|bus_memcpy_fromio
mdefine_line|#define bus_memcpy_fromio(b,d,s,n) memcpy_fromio(d,s,n)
DECL|macro|bus_memcpy_toio
mdefine_line|#define bus_memcpy_toio(b,d,s,n) memcpy_toio(d,s,n)
DECL|macro|bus_request_irq
mdefine_line|#define bus_request_irq(b,i,h,f,n,d) request_irq((i),(h),(f),(n),(d))
DECL|macro|bus_free_irq
mdefine_line|#define bus_free_irq(b,i,d)&t;free_irq((i),(d))
macro_line|#endif /* CONFIG_VIRTUAL_BUS */
macro_line|#endif /* _LINUX_BUS_OPS_H */
eof

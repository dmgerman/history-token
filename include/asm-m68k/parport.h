multiline_comment|/*&n; * parport.h: platform-specific PC-style parport initialisation&n; *&n; * Copyright (C) 1999, 2000  Tim Waugh &lt;tim@cyberelk.demon.co.uk&gt;&n; *&n; * This file should only be included by drivers/parport/parport_pc.c.&n; *&n; * RZ: for use with Q40 and other ISA machines&n; */
macro_line|#ifndef _ASM_M68K_PARPORT_H
DECL|macro|_ASM_M68K_PARPORT_H
mdefine_line|#define _ASM_M68K_PARPORT_H 1
DECL|macro|insl
mdefine_line|#define insl(port,buf,len)   isa_insb(port,buf,(len)&lt;&lt;2)
DECL|macro|outsl
mdefine_line|#define outsl(port,buf,len)  isa_outsb(port,buf,(len)&lt;&lt;2)
multiline_comment|/* no dma, or IRQ autoprobing */
r_static
r_int
id|__devinit
id|parport_pc_find_isa_ports
(paren
r_int
id|autoirq
comma
r_int
id|autodma
)paren
suffix:semicolon
DECL|function|parport_pc_find_nonpci_ports
r_static
r_int
id|__devinit
id|parport_pc_find_nonpci_ports
(paren
r_int
id|autoirq
comma
r_int
id|autodma
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|MACH_IS_Q40
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* count=0 */
r_return
id|parport_pc_find_isa_ports
(paren
id|PARPORT_IRQ_NONE
comma
id|PARPORT_DMA_NONE
)paren
suffix:semicolon
)brace
macro_line|#endif /* !(_ASM_M68K_PARPORT_H) */
eof

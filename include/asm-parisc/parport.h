multiline_comment|/* &n; *&n; * parport.h: ia32-compatible parport initialisation&n; *&n; * This file should only be included by drivers/parport/parport_pc.c.&n; */
macro_line|#ifndef _ASM_PARPORT_H
DECL|macro|_ASM_PARPORT_H
mdefine_line|#define _ASM_PARPORT_H 1
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
multiline_comment|/* nothing ! */
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* !(_ASM_PARPORT_H) */
eof

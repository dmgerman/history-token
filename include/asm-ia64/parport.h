multiline_comment|/*&n; * parport.h: platform-specific PC-style parport initialisation&n; *&n; * Copyright (C) 1999, 2000  Tim Waugh &lt;tim@cyberelk.demon.co.uk&gt;&n; *&n; * This file should only be included by drivers/parport/parport_pc.c.&n; */
macro_line|#ifndef _ASM_IA64_PARPORT_H
DECL|macro|_ASM_IA64_PARPORT_H
mdefine_line|#define _ASM_IA64_PARPORT_H 1
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
r_static
r_int
id|__devinit
DECL|function|parport_pc_find_nonpci_ports
id|parport_pc_find_nonpci_ports
(paren
r_int
id|autoirq
comma
r_int
id|autodma
)paren
(brace
r_return
id|parport_pc_find_isa_ports
c_func
(paren
id|autoirq
comma
id|autodma
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ASM_IA64_PARPORT_H */
eof

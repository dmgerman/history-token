multiline_comment|/*&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef _ASM_GT64120_MOMENCO_OCELOT_GT64120_DEP_H
DECL|macro|_ASM_GT64120_MOMENCO_OCELOT_GT64120_DEP_H
mdefine_line|#define _ASM_GT64120_MOMENCO_OCELOT_GT64120_DEP_H
multiline_comment|/*&n; * PCI address allocation&n; */
DECL|macro|GT_PCI_MEM_BASE
mdefine_line|#define GT_PCI_MEM_BASE&t;(0x22000000UL)
DECL|macro|GT_PCI_MEM_SIZE
mdefine_line|#define GT_PCI_MEM_SIZE&t;GT_DEF_PCI0_MEM0_SIZE
DECL|macro|GT_PCI_IO_BASE
mdefine_line|#define GT_PCI_IO_BASE&t;(0x20000000UL)
DECL|macro|GT_PCI_IO_SIZE
mdefine_line|#define GT_PCI_IO_SIZE&t;GT_DEF_PCI0_IO_SIZE
r_extern
r_int
r_int
id|gt64120_base
suffix:semicolon
DECL|macro|GT64120_BASE
mdefine_line|#define GT64120_BASE&t;(gt64120_base)
multiline_comment|/*&n; * GT timer irq&n; */
DECL|macro|GT_TIMER
mdefine_line|#define&t;GT_TIMER&t;&t;6
macro_line|#endif  /* _ASM_GT64120_MOMENCO_OCELOT_GT64120_DEP_H */
eof

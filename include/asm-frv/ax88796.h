multiline_comment|/* ax88796.h: access points to the driver for the AX88796 NE2000 clone&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_AX88796_H
DECL|macro|_ASM_AX88796_H
mdefine_line|#define _ASM_AX88796_H
macro_line|#include &lt;asm/mb-regs.h&gt;
DECL|macro|AX88796_IOADDR
mdefine_line|#define AX88796_IOADDR&t;&t;(__region_CS1 + 0x200)
DECL|macro|AX88796_IRQ
mdefine_line|#define AX88796_IRQ&t;&t;IRQ_CPU_EXTERNAL7
DECL|macro|AX88796_FULL_DUPLEX
mdefine_line|#define AX88796_FULL_DUPLEX&t;0&t;&t;&t;/* force full duplex */
DECL|macro|AX88796_BUS_INFO
mdefine_line|#define AX88796_BUS_INFO&t;&quot;CS1#+0x200&quot;&t;&t;/* bus info for ethtool */
macro_line|#endif /* _ASM_AX88796_H */
eof

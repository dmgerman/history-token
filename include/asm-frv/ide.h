multiline_comment|/* ide.h: FRV IDE declarations&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_IDE_H
DECL|macro|_ASM_IDE_H
mdefine_line|#define _ASM_IDE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|SUPPORT_SLOW_DATA_PORTS
macro_line|#undef SUPPORT_SLOW_DATA_PORTS
DECL|macro|SUPPORT_SLOW_DATA_PORTS
mdefine_line|#define SUPPORT_SLOW_DATA_PORTS 0
DECL|macro|SUPPORT_VLB_SYNC
macro_line|#undef SUPPORT_VLB_SYNC
DECL|macro|SUPPORT_VLB_SYNC
mdefine_line|#define SUPPORT_VLB_SYNC 0
macro_line|#ifndef MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS 8
macro_line|#endif
multiline_comment|/****************************************************************************/
multiline_comment|/*&n; * some bits needed for parts of the IDE subsystem to compile&n; */
DECL|macro|__ide_mm_insw
mdefine_line|#define __ide_mm_insw(port, addr, n)&t;insw(port, addr, n)
DECL|macro|__ide_mm_insl
mdefine_line|#define __ide_mm_insl(port, addr, n)&t;insl(port, addr, n)
DECL|macro|__ide_mm_outsw
mdefine_line|#define __ide_mm_outsw(port, addr, n)&t;outsw(port, addr, n)
DECL|macro|__ide_mm_outsl
mdefine_line|#define __ide_mm_outsl(port, addr, n)&t;outsl(port, addr, n)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_IDE_H */
eof

multiline_comment|/*&n; *  linux/arch/arm/mach-versatile/core.h&n; *&n; *  Copyright (C) 2004 ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_ARCH_VERSATILE_H
DECL|macro|__ASM_ARCH_VERSATILE_H
mdefine_line|#define __ASM_ARCH_VERSATILE_H
macro_line|#include &lt;asm/hardware/amba.h&gt;
r_extern
r_void
id|__init
id|versatile_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|versatile_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|versatile_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|sys_timer
id|versatile_timer
suffix:semicolon
r_extern
r_int
r_int
id|mmc_status
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|macro|AMBA_DEVICE
mdefine_line|#define AMBA_DEVICE(name,busid,base,plat)&t;&t;&t;&bslash;&n;static struct amba_device name##_device = {&t;&t;&t;&bslash;&n;&t;.dev&t;&t;= {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.coherent_dma_mask = ~0,&t;&t;&t;&bslash;&n;&t;&t;.bus_id&t;= busid,&t;&t;&t;&t;&bslash;&n;&t;&t;.platform_data = plat,&t;&t;&t;&t;&bslash;&n;&t;},&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.res&t;&t;= {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.start&t;= VERSATILE_##base##_BASE,&t;&t;&bslash;&n;&t;&t;.end&t;= (VERSATILE_##base##_BASE) + SZ_4K - 1,&bslash;&n;&t;&t;.flags&t;= IORESOURCE_MEM,&t;&t;&t;&bslash;&n;&t;},&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.dma_mask&t;= ~0,&t;&t;&t;&t;&t;&bslash;&n;&t;.irq&t;&t;= base##_IRQ,&t;&t;&t;&t;&bslash;&n;&t;/* .dma&t;&t;= base##_DMA,*/&t;&t;&t;&t;&bslash;&n;}
macro_line|#endif
eof

multiline_comment|/*&n; * include/asm-arm/arch-sa1100/cerf.h&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Apr-2003 : Removed some old PDA crud [FB]&n; */
macro_line|#ifndef _INCLUDE_CERF_H_
DECL|macro|_INCLUDE_CERF_H_
mdefine_line|#define _INCLUDE_CERF_H_
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|CERF_ETH_IO
mdefine_line|#define CERF_ETH_IO&t;&t;&t;0xf0000000
DECL|macro|CERF_ETH_IRQ
mdefine_line|#define CERF_ETH_IRQ IRQ_GPIO26
DECL|macro|CERF_GPIO_CF_BVD2
mdefine_line|#define CERF_GPIO_CF_BVD2&t;&t;GPIO_GPIO (19)
DECL|macro|CERF_GPIO_CF_BVD1
mdefine_line|#define CERF_GPIO_CF_BVD1&t;&t;GPIO_GPIO (20)
DECL|macro|CERF_GPIO_CF_RESET
mdefine_line|#define CERF_GPIO_CF_RESET&t;&t;GPIO_GPIO (21)
DECL|macro|CERF_GPIO_CF_IRQ
mdefine_line|#define CERF_GPIO_CF_IRQ&t;&t;GPIO_GPIO (22)
DECL|macro|CERF_GPIO_CF_CD
mdefine_line|#define CERF_GPIO_CF_CD&t;&t;&t;GPIO_GPIO (23)
DECL|macro|CERF_IRQ_GPIO_CF_BVD2
mdefine_line|#define CERF_IRQ_GPIO_CF_BVD2&t;&t;IRQ_GPIO19
DECL|macro|CERF_IRQ_GPIO_CF_BVD1
mdefine_line|#define CERF_IRQ_GPIO_CF_BVD1&t;&t;IRQ_GPIO20
DECL|macro|CERF_IRQ_GPIO_CF_IRQ
mdefine_line|#define CERF_IRQ_GPIO_CF_IRQ&t;&t;IRQ_GPIO22
DECL|macro|CERF_IRQ_GPIO_CF_CD
mdefine_line|#define CERF_IRQ_GPIO_CF_CD&t;&t;IRQ_GPIO23
macro_line|#endif 
singleline_comment|// _INCLUDE_CERF_H_
eof

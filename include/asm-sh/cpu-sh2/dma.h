multiline_comment|/*&n; * Definitions for the SH-2 DMAC.&n; *&n; * Copyright (C) 2003  Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_CPU_SH2_DMA_H
DECL|macro|__ASM_CPU_SH2_DMA_H
mdefine_line|#define __ASM_CPU_SH2_DMA_H
DECL|macro|SH_MAX_DMA_CHANNELS
mdefine_line|#define SH_MAX_DMA_CHANNELS&t;2
DECL|macro|SAR
mdefine_line|#define SAR&t;((unsigned long[]){ 0xffffff80, 0xffffff90 })
DECL|macro|DAR
mdefine_line|#define DAR&t;((unsigned long[]){ 0xffffff84, 0xffffff94 })
DECL|macro|DMATCR
mdefine_line|#define DMATCR&t;((unsigned long[]){ 0xffffff88, 0xffffff98 })
DECL|macro|CHCR
mdefine_line|#define CHCR&t;((unsigned long[]){ 0xfffffffc, 0xffffff9c })
DECL|macro|DMAOR
mdefine_line|#define DMAOR&t;0xffffffb0
macro_line|#endif /* __ASM_CPU_SH2_DMA_H */
eof

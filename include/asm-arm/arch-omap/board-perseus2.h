multiline_comment|/*&n; *  linux/include/asm-arm/arch-omap/board-perseus2.h&n; *&n; *  Copyright 2003 by Texas Instruments Incorporated&n; *    OMAP730 / Perseus2 support by Jean Pihet&n; *&n; * Copyright (C) 2001 RidgeRun, Inc. (http://www.ridgerun.com)&n; * Author: RidgeRun, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP_PERSEUS2_H
DECL|macro|__ASM_ARCH_OMAP_PERSEUS2_H
mdefine_line|#define __ASM_ARCH_OMAP_PERSEUS2_H
macro_line|#include &lt;asm/arch/fpga.h&gt;
macro_line|#ifndef OMAP_SDRAM_DEVICE
DECL|macro|OMAP_SDRAM_DEVICE
mdefine_line|#define OMAP_SDRAM_DEVICE&t;&t;D256M_1X16_4B
macro_line|#endif
multiline_comment|/*&n; * These definitions define an area of FLASH set aside&n; * for the use of MTD/JFFS2. This is the area of flash&n; * that a JFFS2 filesystem will reside which is mounted&n; * at boot with the &quot;root=/dev/mtdblock/0 rw&quot;&n; * command line option.&n; */
multiline_comment|/* Intel flash_0, partitioned as expected by rrload */
DECL|macro|OMAP_FLASH_0_BASE
mdefine_line|#define OMAP_FLASH_0_BASE&t;0xD8000000&t;/* VA */
DECL|macro|OMAP_FLASH_0_START
mdefine_line|#define OMAP_FLASH_0_START&t;0x00000000&t;/* PA */
DECL|macro|OMAP_FLASH_0_SIZE
mdefine_line|#define OMAP_FLASH_0_SIZE&t;SZ_32M
DECL|macro|MAXIRQNUM
mdefine_line|#define MAXIRQNUM&t;&t;IH_BOARD_BASE
DECL|macro|MAXFIQNUM
mdefine_line|#define MAXFIQNUM&t;&t;MAXIRQNUM
DECL|macro|MAXSWINUM
mdefine_line|#define MAXSWINUM&t;&t;MAXIRQNUM
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;(MAXIRQNUM + 1)
macro_line|#endif
eof

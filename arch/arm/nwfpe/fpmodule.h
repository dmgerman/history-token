multiline_comment|/*&n;    NetWinder Floating Point Emulator&n;    (c) Rebel.com, 1998-1999&n;&n;    Direct questions, comments to Scott Bambrough &lt;scottb@netwinder.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef __FPMODULE_H__
DECL|macro|__FPMODULE_H__
mdefine_line|#define __FPMODULE_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_CPU_32
DECL|macro|REG_ORIG_R0
mdefine_line|#define REG_ORIG_R0&t;17
DECL|macro|REG_CPSR
mdefine_line|#define REG_CPSR&t;16
macro_line|#else
DECL|macro|REG_ORIG_R0
mdefine_line|#define REG_ORIG_R0&t;16
DECL|macro|REG_CPSR
mdefine_line|#define REG_CPSR&t;15
macro_line|#endif
DECL|macro|REG_PC
mdefine_line|#define REG_PC&t;&t;15
DECL|macro|REG_LR
mdefine_line|#define REG_LR&t;&t;14
DECL|macro|REG_SP
mdefine_line|#define REG_SP&t;&t;13
DECL|macro|REG_IP
mdefine_line|#define REG_IP&t;&t;12
DECL|macro|REG_FP
mdefine_line|#define REG_FP&t;&t;11
DECL|macro|REG_R10
mdefine_line|#define REG_R10&t;&t;10
DECL|macro|REG_R9
mdefine_line|#define REG_R9&t;&t;9
DECL|macro|REG_R9
mdefine_line|#define REG_R9&t;&t;9
DECL|macro|REG_R8
mdefine_line|#define REG_R8&t;&t;8
DECL|macro|REG_R7
mdefine_line|#define REG_R7&t;&t;7
DECL|macro|REG_R6
mdefine_line|#define REG_R6&t;&t;6
DECL|macro|REG_R5
mdefine_line|#define REG_R5&t;&t;5
DECL|macro|REG_R4
mdefine_line|#define REG_R4&t;&t;4
DECL|macro|REG_R3
mdefine_line|#define REG_R3&t;&t;3
DECL|macro|REG_R2
mdefine_line|#define REG_R2&t;&t;2
DECL|macro|REG_R1
mdefine_line|#define REG_R1&t;&t;1
DECL|macro|REG_R0
mdefine_line|#define REG_R0&t;&t;0
macro_line|#endif
eof

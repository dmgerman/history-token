multiline_comment|/*&n; * Instruction formats for the sequencer program downloaded to&n; * Aic7xxx SCSI host adapters&n; *&n; * Copyright (c) 1997, 1998, 2000 Justin T. Gibbs.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; * $Id: //depot/src/aic7xxx/aicasm/aicasm_insformat.h#4 $&n; *&n; * $FreeBSD: src/sys/dev/aic7xxx/aicasm/aicasm_insformat.h,v 1.3 2000/09/22 22:19:54 gibbs Exp $&n; */
macro_line|#if linux
macro_line|#include &lt;endian.h&gt;
macro_line|#else
macro_line|#include &lt;machine/endian.h&gt;
macro_line|#endif
DECL|struct|ins_format1
r_struct
id|ins_format1
(brace
macro_line|#if BYTE_ORDER == LITTLE_ENDIAN
DECL|member|immediate
r_uint32
id|immediate
suffix:colon
l_int|8
comma
DECL|member|source
id|source
suffix:colon
l_int|9
comma
DECL|member|destination
id|destination
suffix:colon
l_int|9
comma
DECL|member|ret
id|ret
suffix:colon
l_int|1
comma
DECL|member|opcode
id|opcode
suffix:colon
l_int|4
comma
DECL|member|parity
id|parity
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
r_uint32
id|parity
suffix:colon
l_int|1
comma
id|opcode
suffix:colon
l_int|4
comma
id|ret
suffix:colon
l_int|1
comma
id|destination
suffix:colon
l_int|9
comma
id|source
suffix:colon
l_int|9
comma
id|immediate
suffix:colon
l_int|8
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|ins_format2
r_struct
id|ins_format2
(brace
macro_line|#if BYTE_ORDER == LITTLE_ENDIAN
DECL|member|shift_control
r_uint32
id|shift_control
suffix:colon
l_int|8
comma
DECL|member|source
id|source
suffix:colon
l_int|9
comma
DECL|member|destination
id|destination
suffix:colon
l_int|9
comma
DECL|member|ret
id|ret
suffix:colon
l_int|1
comma
DECL|member|opcode
id|opcode
suffix:colon
l_int|4
comma
DECL|member|parity
id|parity
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
r_uint32
id|parity
suffix:colon
l_int|1
comma
id|opcode
suffix:colon
l_int|4
comma
id|ret
suffix:colon
l_int|1
comma
id|destination
suffix:colon
l_int|9
comma
id|source
suffix:colon
l_int|9
comma
id|shift_control
suffix:colon
l_int|8
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|ins_format3
r_struct
id|ins_format3
(brace
macro_line|#if BYTE_ORDER == LITTLE_ENDIAN
DECL|member|immediate
r_uint32
id|immediate
suffix:colon
l_int|8
comma
DECL|member|source
id|source
suffix:colon
l_int|9
comma
DECL|member|address
id|address
suffix:colon
l_int|10
comma
DECL|member|opcode
id|opcode
suffix:colon
l_int|4
comma
DECL|member|parity
id|parity
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
r_uint32
id|parity
suffix:colon
l_int|1
comma
id|opcode
suffix:colon
l_int|4
comma
id|address
suffix:colon
l_int|10
comma
id|source
suffix:colon
l_int|9
comma
id|immediate
suffix:colon
l_int|8
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|union|ins_formats
r_union
id|ins_formats
(brace
DECL|member|format1
r_struct
id|ins_format1
id|format1
suffix:semicolon
DECL|member|format2
r_struct
id|ins_format2
id|format2
suffix:semicolon
DECL|member|format3
r_struct
id|ins_format3
id|format3
suffix:semicolon
DECL|member|bytes
r_uint8
id|bytes
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|integer
r_uint32
id|integer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|instruction
r_struct
id|instruction
(brace
DECL|member|format
r_union
id|ins_formats
id|format
suffix:semicolon
DECL|member|srcline
id|u_int
id|srcline
suffix:semicolon
DECL|member|patch_label
r_struct
id|symbol
op_star
id|patch_label
suffix:semicolon
id|STAILQ_ENTRY
c_func
(paren
id|instruction
)paren
id|links
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|AIC_OP_OR
mdefine_line|#define&t;AIC_OP_OR&t;0x0
DECL|macro|AIC_OP_AND
mdefine_line|#define&t;AIC_OP_AND&t;0x1
DECL|macro|AIC_OP_XOR
mdefine_line|#define AIC_OP_XOR&t;0x2
DECL|macro|AIC_OP_ADD
mdefine_line|#define&t;AIC_OP_ADD&t;0x3
DECL|macro|AIC_OP_ADC
mdefine_line|#define&t;AIC_OP_ADC&t;0x4
DECL|macro|AIC_OP_ROL
mdefine_line|#define&t;AIC_OP_ROL&t;0x5
DECL|macro|AIC_OP_BMOV
mdefine_line|#define&t;AIC_OP_BMOV&t;0x6
DECL|macro|AIC_OP_JMP
mdefine_line|#define&t;AIC_OP_JMP&t;0x8
DECL|macro|AIC_OP_JC
mdefine_line|#define AIC_OP_JC&t;0x9
DECL|macro|AIC_OP_JNC
mdefine_line|#define AIC_OP_JNC&t;0xa
DECL|macro|AIC_OP_CALL
mdefine_line|#define AIC_OP_CALL&t;0xb
DECL|macro|AIC_OP_JNE
mdefine_line|#define&t;AIC_OP_JNE&t;0xc
DECL|macro|AIC_OP_JNZ
mdefine_line|#define&t;AIC_OP_JNZ&t;0xd
DECL|macro|AIC_OP_JE
mdefine_line|#define&t;AIC_OP_JE&t;0xe
DECL|macro|AIC_OP_JZ
mdefine_line|#define&t;AIC_OP_JZ&t;0xf
multiline_comment|/* Pseudo Ops */
DECL|macro|AIC_OP_SHL
mdefine_line|#define&t;AIC_OP_SHL&t;0x10
DECL|macro|AIC_OP_SHR
mdefine_line|#define&t;AIC_OP_SHR&t;0x20
DECL|macro|AIC_OP_ROR
mdefine_line|#define&t;AIC_OP_ROR&t;0x30
eof

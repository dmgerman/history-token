macro_line|#ifndef _SOUND_PC9800_H_
DECL|macro|_SOUND_PC9800_H_
mdefine_line|#define _SOUND_PC9800_H_
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|PC9800_SOUND_IO_ID
mdefine_line|#define PC9800_SOUND_IO_ID&t;0xa460
multiline_comment|/* Sound Functions ID. */
DECL|macro|PC9800_SOUND_ID
mdefine_line|#define PC9800_SOUND_ID()&t;((inb(PC9800_SOUND_IO_ID) &gt;&gt; 4) &amp; 0x0f)
DECL|macro|PC9800_SOUND_ID_DO
mdefine_line|#define PC9800_SOUND_ID_DO&t;0x0&t;/* PC-98DO+ Internal */
DECL|macro|PC9800_SOUND_ID_GS
mdefine_line|#define PC9800_SOUND_ID_GS&t;0x1&t;/* PC-98GS Internal */
DECL|macro|PC9800_SOUND_ID_73
mdefine_line|#define PC9800_SOUND_ID_73&t;0x2&t;/* PC-9801-73 (base 0x18x) */
DECL|macro|PC9800_SOUND_ID_73A
mdefine_line|#define PC9800_SOUND_ID_73A&t;0x3&t;/* PC-9801-73/76 (base 0x28x) */
DECL|macro|PC9800_SOUND_ID_86
mdefine_line|#define PC9800_SOUND_ID_86&t;0x4&t;/* PC-9801-86 and compatible (base 0x18x) */
DECL|macro|PC9800_SOUND_ID_86A
mdefine_line|#define PC9800_SOUND_ID_86A&t;0x5&t;/* PC-9801-86 (base 0x28x) */
DECL|macro|PC9800_SOUND_ID_NF
mdefine_line|#define PC9800_SOUND_ID_NF&t;0x6&t;/* PC-9821Nf/Np Internal */
DECL|macro|PC9800_SOUND_ID_XMATE
mdefine_line|#define PC9800_SOUND_ID_XMATE&t;0x7&t;/* X-Mate Internal and compatible */
DECL|macro|PC9800_SOUND_ID_118
mdefine_line|#define PC9800_SOUND_ID_118&t;0x8&t;/* PC-9801-118 and compatible(CanBe Internal, etc.) */
DECL|macro|PC9800_SOUND_ID_UNKNOWN
mdefine_line|#define PC9800_SOUND_ID_UNKNOWN&t;0xf&t;/* Unknown (No Sound System or PC-9801-26) */
macro_line|#endif
eof

multiline_comment|/***************************************************************************&n; *           WT register offsets.&n; *&n; *  Wed Oct 22 13:50:20 2003&n; *  Copyright  2003  mjander&n; *  mjander@users.sourceforge.org&n; ****************************************************************************/
macro_line|#ifndef _AU88X0_WT_H
DECL|macro|_AU88X0_WT_H
mdefine_line|#define _AU88X0_WT_H
multiline_comment|/* WT channels are grouped in banks. Each bank has 0x20 channels. */
multiline_comment|/* Bank register address boundary is 0x8000 */
DECL|macro|NR_WT_PB
mdefine_line|#define NR_WT_PB 0x20
multiline_comment|/* WT bank base register (as dword address). */
DECL|macro|WT_BAR
mdefine_line|#define WT_BAR(x) (((x)&amp;0xffe0)&lt;&lt;0x8)
DECL|macro|WT_BANK
mdefine_line|#define WT_BANK(x) (x&gt;&gt;5)
multiline_comment|/* WT Bank registers */
DECL|macro|WT_CTRL
mdefine_line|#define WT_CTRL(bank)&t;(((((bank)&amp;1)&lt;&lt;0xd) + 0x00)&lt;&lt;2)&t;/* 0x0000 */
DECL|macro|WT_SRAMP
mdefine_line|#define WT_SRAMP(bank)&t;(((((bank)&amp;1)&lt;&lt;0xd) + 0x01)&lt;&lt;2)&t;/* 0x0004 */
DECL|macro|WT_DSREG
mdefine_line|#define WT_DSREG(bank)&t;(((((bank)&amp;1)&lt;&lt;0xd) + 0x02)&lt;&lt;2)&t;/* 0x0008 */
DECL|macro|WT_MRAMP
mdefine_line|#define WT_MRAMP(bank)&t;(((((bank)&amp;1)&lt;&lt;0xd) + 0x03)&lt;&lt;2)&t;/* 0x000c */
DECL|macro|WT_GMODE
mdefine_line|#define WT_GMODE(bank)&t;(((((bank)&amp;1)&lt;&lt;0xd) + 0x04)&lt;&lt;2)&t;/* 0x0010 */
DECL|macro|WT_ARAMP
mdefine_line|#define WT_ARAMP(bank)&t;(((((bank)&amp;1)&lt;&lt;0xd) + 0x05)&lt;&lt;2)&t;/* 0x0014 */
multiline_comment|/* WT Voice registers */
DECL|macro|WT_STEREO
mdefine_line|#define WT_STEREO(voice)&t;((WT_BAR(voice)+ 0x20 +(((voice)&amp;0x1f)&gt;&gt;1))&lt;&lt;2)&t;/* 0x0080 */
DECL|macro|WT_MUTE
mdefine_line|#define WT_MUTE(voice)&t;&t;((WT_BAR(voice)+ 0x40 +((voice)&amp;0x1f))&lt;&lt;2)&t;/* 0x0100 */
DECL|macro|WT_RUN
mdefine_line|#define WT_RUN(voice)&t;&t;((WT_BAR(voice)+ 0x60 +((voice)&amp;0x1f))&lt;&lt;2)&t;/* 0x0180 */
multiline_comment|/* Some kind of parameters. */
multiline_comment|/* PARM0, PARM1 : Filter (0xFF000000), SampleRate (0x0000FFFF) */
multiline_comment|/* PARM2, PARM3 : Still unknown */
DECL|macro|WT_PARM
mdefine_line|#define WT_PARM(x,y)&t;(((WT_BAR(x))+ 0x80 +(((x)&amp;0x1f)&lt;&lt;2)+(y))&lt;&lt;2)&t;/* 0x0200 */
DECL|macro|WT_DELAY
mdefine_line|#define WT_DELAY(x,y)&t;(((WT_BAR(x))+ 0x100 +(((x)&amp;0x1f)&lt;&lt;2)+(y))&lt;&lt;2)&t;/* 0x0400 */
multiline_comment|/* Numeric indexes used by SetReg() and GetReg() */
macro_line|#if 0
r_enum
(brace
id|run
op_assign
l_int|0
comma
multiline_comment|/* 0  W 1:run 0:stop */
id|parm0
comma
multiline_comment|/* 1  W filter, samplerate */
id|parm1
comma
multiline_comment|/* 2  W filter, samplerate */
id|parm2
comma
multiline_comment|/* 3  W  */
id|parm3
comma
multiline_comment|/* 4  RW volume. This value is calculated using floating point ops. */
id|sramp
comma
multiline_comment|/* 5  W */
id|mute
comma
multiline_comment|/* 6  W 1:mute, 0:unmute */
id|gmode
comma
multiline_comment|/* 7  RO Looks like only bit0 is used. */
id|aramp
comma
multiline_comment|/* 8  W */
id|mramp
comma
multiline_comment|/* 9  W */
id|ctrl
comma
multiline_comment|/* a  W */
id|delay
comma
multiline_comment|/* b  W All 4 values are written at once with same value. */
id|dsreg
comma
multiline_comment|/* c  (R)W */
)brace
id|wt_reg
suffix:semicolon
macro_line|#endif
r_typedef
r_struct
(brace
DECL|member|parm0
r_int
r_int
id|parm0
suffix:semicolon
multiline_comment|/* this_1E4 */
DECL|member|parm1
r_int
r_int
id|parm1
suffix:semicolon
multiline_comment|/* this_1E8 */
DECL|member|parm2
r_int
r_int
id|parm2
suffix:semicolon
multiline_comment|/* this_1EC */
DECL|member|parm3
r_int
r_int
id|parm3
suffix:semicolon
multiline_comment|/* this_1F0 */
DECL|member|this_1D0
r_int
r_int
id|this_1D0
suffix:semicolon
DECL|typedef|wt_voice_t
)brace
id|wt_voice_t
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _AU88X0_WT_H */
multiline_comment|/* End of file */
eof

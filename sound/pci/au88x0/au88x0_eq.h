macro_line|#ifndef AU88X0_EQ_H
DECL|macro|AU88X0_EQ_H
mdefine_line|#define AU88X0_EQ_H
multiline_comment|/***************************************************************************&n; *            au88x0_eq.h&n; *&n; *  Definitions and constant data for the Aureal Hardware EQ.&n; *&n; *  Sun Jun  8 18:23:38 2003&n; *  Author: Manuel Jander (mjander@users.sourceforge.net)&n; ****************************************************************************/
r_typedef
r_struct
(brace
DECL|member|LeftCoefs
id|u16
id|LeftCoefs
(braket
l_int|50
)braket
suffix:semicolon
singleline_comment|//0x4
DECL|member|RightCoefs
id|u16
id|RightCoefs
(braket
l_int|50
)braket
suffix:semicolon
singleline_comment|// 0x68
DECL|member|LeftGains
id|u16
id|LeftGains
(braket
l_int|20
)braket
suffix:semicolon
singleline_comment|//0xd0
DECL|member|RightGains
id|u16
id|RightGains
(braket
l_int|20
)braket
suffix:semicolon
singleline_comment|//0xe4
DECL|typedef|auxxEqCoeffSet_t
)brace
id|auxxEqCoeffSet_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|this00
r_int
r_int
op_star
id|this00
suffix:semicolon
multiline_comment|/*CAsp4HwIO */
DECL|member|this04
r_int
id|this04
suffix:semicolon
multiline_comment|/* How many filters for each side (default = 10) */
DECL|member|this08
r_int
id|this08
suffix:semicolon
multiline_comment|/* inited to cero. Stereo flag? */
DECL|typedef|eqhw_t
)brace
id|eqhw_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|this00
r_int
r_int
op_star
id|this00
suffix:semicolon
multiline_comment|/*CAsp4Core */
DECL|member|this04
id|eqhw_t
id|this04
suffix:semicolon
multiline_comment|/* CHwEq */
DECL|member|this08
r_int
id|this08
suffix:semicolon
multiline_comment|/* Bad codec flag ? SetBypassGain: bypass gain */
DECL|member|this0a
r_int
id|this0a
suffix:semicolon
DECL|member|this0c
r_int
id|this0c
suffix:semicolon
multiline_comment|/* SetBypassGain: bypass gain when this28 is not set. */
DECL|member|this0e
r_int
id|this0e
suffix:semicolon
DECL|member|this10
r_int
id|this10
suffix:semicolon
multiline_comment|/* How many gains are used for each side (right or left). */
DECL|member|this14
id|u16
id|this14
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* SetLeftGainsTarget: Left (and right?) EQ gains  */
DECL|member|this24
r_int
id|this24
suffix:semicolon
DECL|member|this28
r_int
id|this28
suffix:semicolon
multiline_comment|/* flag related to EQ enabled or not. Gang flag ? */
DECL|member|this54
r_int
id|this54
suffix:semicolon
multiline_comment|/* SetBypass */
DECL|member|this58
r_int
id|this58
suffix:semicolon
DECL|member|this5c
r_int
id|this5c
suffix:semicolon
DECL|member|coefset
multiline_comment|/*0x60 */
id|auxxEqCoeffSet_t
id|coefset
suffix:semicolon
multiline_comment|/* 50 u16 word each channel. */
DECL|member|this130
id|u16
id|this130
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* Left and Right gains */
DECL|typedef|eqlzr_t
)brace
id|eqlzr_t
suffix:semicolon
macro_line|#endif
eof

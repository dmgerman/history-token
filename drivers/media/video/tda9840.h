macro_line|#ifndef __INCLUDED_TDA9840__
DECL|macro|__INCLUDED_TDA9840__
mdefine_line|#define __INCLUDED_TDA9840__
DECL|macro|I2C_TDA9840
mdefine_line|#define&t;I2C_TDA9840&t;&t;0x42
DECL|macro|TDA9840_DETECT
mdefine_line|#define TDA9840_DETECT&t;&t;_IOR(&squot;v&squot;,1,int)
multiline_comment|/* return values for TDA9840_DETCT */
DECL|macro|TDA9840_MONO_DETECT
mdefine_line|#define TDA9840_MONO_DETECT&t;&t;0x0
DECL|macro|TDA9840_DUAL_DETECT
mdefine_line|#define&t;TDA9840_DUAL_DETECT&t;&t;0x1
DECL|macro|TDA9840_STEREO_DETECT
mdefine_line|#define&t;TDA9840_STEREO_DETECT&t;&t;0x2
DECL|macro|TDA9840_INCORRECT_DETECT
mdefine_line|#define&t;TDA9840_INCORRECT_DETECT&t;0x3
DECL|macro|TDA9840_SWITCH
mdefine_line|#define TDA9840_SWITCH&t;&t;_IOW(&squot;v&squot;,2,int)
multiline_comment|/* modes than can be set with TDA9840_SWITCH */
DECL|macro|TDA9840_SET_MUTE
mdefine_line|#define&t;TDA9840_SET_MUTE&t;&t;0x00
DECL|macro|TDA9840_SET_MONO
mdefine_line|#define&t;TDA9840_SET_MONO&t;&t;0x10
DECL|macro|TDA9840_SET_STEREO
mdefine_line|#define&t;TDA9840_SET_STEREO&t;&t;0x2a
DECL|macro|TDA9840_SET_LANG1
mdefine_line|#define&t;TDA9840_SET_LANG1&t;&t;0x12
DECL|macro|TDA9840_SET_LANG2
mdefine_line|#define&t;TDA9840_SET_LANG2&t;&t;0x1e
DECL|macro|TDA9840_SET_BOTH
mdefine_line|#define&t;TDA9840_SET_BOTH&t;&t;0x1a
DECL|macro|TDA9840_SET_BOTH_R
mdefine_line|#define&t;TDA9840_SET_BOTH_R&t;&t;0x16
DECL|macro|TDA9840_SET_EXTERNAL
mdefine_line|#define&t;TDA9840_SET_EXTERNAL&t;&t;0x7a
multiline_comment|/* values may range between +2.5 and -2.0;&n;   the value has to be multiplied with 10 */
DECL|macro|TDA9840_LEVEL_ADJUST
mdefine_line|#define TDA9840_LEVEL_ADJUST&t;_IOW(&squot;v&squot;,3,int)
multiline_comment|/* values may range between +2.5 and -2.4;&n;   the value has to be multiplied with 10 */
DECL|macro|TDA9840_STEREO_ADJUST
mdefine_line|#define TDA9840_STEREO_ADJUST&t;_IOW(&squot;v&squot;,4,int)
multiline_comment|/* currently not implemented */
DECL|macro|TDA9840_TEST
mdefine_line|#define TDA9840_TEST&t;&t;_IOW(&squot;v&squot;,5,int)
macro_line|#endif
eof

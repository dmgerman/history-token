multiline_comment|/*&n; *  $Id: powernow-k7.h,v 1.2 2003/02/10 18:26:01 davej Exp $&n; *  (C) 2003 Dave Jones.&n; *&n; *  Licensed under the terms of the GNU GPL License version 2.&n; *&n; *  AMD-specific information&n; *&n; */
DECL|union|msr_fidvidctl
r_union
id|msr_fidvidctl
(brace
r_struct
(brace
DECL|member|FID
r_int
id|FID
suffix:colon
l_int|5
comma
singleline_comment|// 4:0
DECL|member|reserved1
id|reserved1
suffix:colon
l_int|3
comma
singleline_comment|// 7:5
DECL|member|VID
id|VID
suffix:colon
l_int|5
comma
singleline_comment|// 12:8
DECL|member|reserved2
id|reserved2
suffix:colon
l_int|3
comma
singleline_comment|// 15:13
DECL|member|FIDC
id|FIDC
suffix:colon
l_int|1
comma
singleline_comment|// 16
DECL|member|VIDC
id|VIDC
suffix:colon
l_int|1
comma
singleline_comment|// 17
DECL|member|reserved3
id|reserved3
suffix:colon
l_int|2
comma
singleline_comment|// 19:18
DECL|member|FIDCHGRATIO
id|FIDCHGRATIO
suffix:colon
l_int|1
comma
singleline_comment|// 20
DECL|member|reserved4
id|reserved4
suffix:colon
l_int|11
comma
singleline_comment|// 31-21
DECL|member|SGTC
id|SGTC
suffix:colon
l_int|20
comma
singleline_comment|// 32:51
DECL|member|reserved5
id|reserved5
suffix:colon
l_int|12
suffix:semicolon
singleline_comment|// 63:52
DECL|member|bits
)brace
id|bits
suffix:semicolon
DECL|member|val
r_int
r_int
r_int
id|val
suffix:semicolon
)brace
suffix:semicolon
DECL|union|msr_fidvidstatus
r_union
id|msr_fidvidstatus
(brace
r_struct
(brace
DECL|member|CFID
r_int
id|CFID
suffix:colon
l_int|5
comma
singleline_comment|// 4:0
DECL|member|reserved1
id|reserved1
suffix:colon
l_int|3
comma
singleline_comment|// 7:5
DECL|member|SFID
id|SFID
suffix:colon
l_int|5
comma
singleline_comment|// 12:8
DECL|member|reserved2
id|reserved2
suffix:colon
l_int|3
comma
singleline_comment|// 15:13
DECL|member|MFID
id|MFID
suffix:colon
l_int|5
comma
singleline_comment|// 20:16
DECL|member|reserved3
id|reserved3
suffix:colon
l_int|11
comma
singleline_comment|// 31:21
DECL|member|CVID
id|CVID
suffix:colon
l_int|5
comma
singleline_comment|// 36:32
DECL|member|reserved4
id|reserved4
suffix:colon
l_int|3
comma
singleline_comment|// 39:37
DECL|member|SVID
id|SVID
suffix:colon
l_int|5
comma
singleline_comment|// 44:40
DECL|member|reserved5
id|reserved5
suffix:colon
l_int|3
comma
singleline_comment|// 47:45
DECL|member|MVID
id|MVID
suffix:colon
l_int|5
comma
singleline_comment|// 52:48
DECL|member|reserved6
id|reserved6
suffix:colon
l_int|11
suffix:semicolon
singleline_comment|// 63:53
DECL|member|bits
)brace
id|bits
suffix:semicolon
DECL|member|val
r_int
r_int
r_int
id|val
suffix:semicolon
)brace
suffix:semicolon
eof

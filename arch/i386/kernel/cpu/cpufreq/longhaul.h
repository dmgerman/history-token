multiline_comment|/*&n; *  longhaul.h&n; *  (C) 2003 Dave Jones.&n; *&n; *  Licensed under the terms of the GNU GPL License version 2.&n; *&n; *  VIA-specific information&n; */
DECL|union|msr_longhaul
r_union
id|msr_longhaul
(brace
r_struct
(brace
DECL|member|RevisionID
r_int
id|RevisionID
suffix:colon
l_int|4
comma
singleline_comment|// 3:0
DECL|member|RevisionKey
id|RevisionKey
suffix:colon
l_int|4
comma
singleline_comment|// 7:4
DECL|member|EnableSoftBusRatio
id|EnableSoftBusRatio
suffix:colon
l_int|1
comma
singleline_comment|// 8
DECL|member|EnableSoftVID
id|EnableSoftVID
suffix:colon
l_int|1
comma
singleline_comment|// 9
DECL|member|EnableSoftBSEL
id|EnableSoftBSEL
suffix:colon
l_int|1
comma
singleline_comment|// 10
DECL|member|Reserved
id|Reserved
suffix:colon
l_int|3
comma
singleline_comment|// 11:13
DECL|member|SoftBusRatio4
id|SoftBusRatio4
suffix:colon
l_int|1
comma
singleline_comment|// 14
DECL|member|VRMRev
id|VRMRev
suffix:colon
l_int|1
comma
singleline_comment|// 15
DECL|member|SoftBusRatio
id|SoftBusRatio
suffix:colon
l_int|4
comma
singleline_comment|// 19:16
DECL|member|SoftVID
id|SoftVID
suffix:colon
l_int|5
comma
singleline_comment|// 24:20
DECL|member|Reserved2
id|Reserved2
suffix:colon
l_int|3
comma
singleline_comment|// 27:25
DECL|member|SoftBSEL
id|SoftBSEL
suffix:colon
l_int|2
comma
singleline_comment|// 29:28
DECL|member|Reserved3
id|Reserved3
suffix:colon
l_int|2
comma
singleline_comment|// 31:30
DECL|member|MaxMHzBR
id|MaxMHzBR
suffix:colon
l_int|4
comma
singleline_comment|// 35:32
DECL|member|MaximumVID
id|MaximumVID
suffix:colon
l_int|5
comma
singleline_comment|// 40:36
DECL|member|MaxMHzFSB
id|MaxMHzFSB
suffix:colon
l_int|2
comma
singleline_comment|// 42:41
DECL|member|MaxMHzBR4
id|MaxMHzBR4
suffix:colon
l_int|1
comma
singleline_comment|// 43
DECL|member|Reserved4
id|Reserved4
suffix:colon
l_int|4
comma
singleline_comment|// 47:44
DECL|member|MinMHzBR
id|MinMHzBR
suffix:colon
l_int|4
comma
singleline_comment|// 51:48
DECL|member|MinimumVID
id|MinimumVID
suffix:colon
l_int|5
comma
singleline_comment|// 56:52
DECL|member|MinMHzFSB
id|MinMHzFSB
suffix:colon
l_int|2
comma
singleline_comment|// 58:57
DECL|member|MinMHzBR4
id|MinMHzBR4
suffix:colon
l_int|1
comma
singleline_comment|// 59
DECL|member|Reserved5
id|Reserved5
suffix:colon
l_int|4
suffix:semicolon
singleline_comment|// 63:60
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

multiline_comment|/*&n; *  drivers/s390/s390mach.h&n; *   S/390 data definitions for machine check processing&n; *&n; *  S390 version&n; *    Copyright (C) 2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Ingo Adlung (adlung@de.ibm.com)&n; */
macro_line|#ifndef __s390mach_h
DECL|macro|__s390mach_h
mdefine_line|#define __s390mach_h
macro_line|#include &lt;asm/types.h&gt;
DECL|struct|mci
r_struct
id|mci
(brace
DECL|member|sd
id|__u32
id|sd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 00 system damage */
DECL|member|pd
id|__u32
id|pd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 01 instruction-processing damage */
DECL|member|sr
id|__u32
id|sr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 02 system recovery */
DECL|member|to_be_defined_1
id|__u32
id|to_be_defined_1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 03-06 */
DECL|member|dg
id|__u32
id|dg
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 07 degradation */
DECL|member|w
id|__u32
id|w
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 08 warning pending */
DECL|member|cp
id|__u32
id|cp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 09 channel-report pending */
DECL|member|to_be_defined_2
id|__u32
id|to_be_defined_2
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* 10-15 */
DECL|member|se
id|__u32
id|se
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 16 storage error uncorrected */
DECL|member|sc
id|__u32
id|sc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 17 storage error corrected */
DECL|member|ke
id|__u32
id|ke
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 18 storage-key error uncorrected */
DECL|member|ds
id|__u32
id|ds
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 19 storage degradation */
DECL|member|to_be_defined_3
id|__u32
id|to_be_defined_3
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 20-23 */
DECL|member|fa
id|__u32
id|fa
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 24 failing storage address validity */
DECL|member|to_be_defined_4
id|__u32
id|to_be_defined_4
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* 25-31 */
DECL|member|ie
id|__u32
id|ie
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 32 indirect storage error */
DECL|member|to_be_defined_5
id|__u32
id|to_be_defined_5
suffix:colon
l_int|31
suffix:semicolon
multiline_comment|/* 33-63 */
)brace
suffix:semicolon
multiline_comment|/*&n; * Channel Report Word&n; */
DECL|struct|crw
r_struct
id|crw
(brace
DECL|member|res1
id|__u32
id|res1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved zero */
DECL|member|slct
id|__u32
id|slct
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* solicited */
DECL|member|oflw
id|__u32
id|oflw
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* overflow */
DECL|member|chn
id|__u32
id|chn
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* chained */
DECL|member|rsc
id|__u32
id|rsc
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* reporting source code */
DECL|member|anc
id|__u32
id|anc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ancillary report */
DECL|member|res2
id|__u32
id|res2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved zero */
DECL|member|erc
id|__u32
id|erc
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* error-recovery code */
DECL|member|rsid
id|__u32
id|rsid
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* reporting-source ID */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|CRW_RSC_MONITOR
mdefine_line|#define CRW_RSC_MONITOR  0x2  /* monitoring facility */
DECL|macro|CRW_RSC_SCH
mdefine_line|#define CRW_RSC_SCH      0x3  /* subchannel */
DECL|macro|CRW_RSC_CPATH
mdefine_line|#define CRW_RSC_CPATH    0x4  /* channel path */
DECL|macro|CRW_RSC_CONFIG
mdefine_line|#define CRW_RSC_CONFIG   0x9  /* configuration-alert facility */
DECL|macro|CRW_RSC_CSS
mdefine_line|#define CRW_RSC_CSS      0xB  /* channel subsystem */
DECL|macro|CRW_ERC_EVENT
mdefine_line|#define CRW_ERC_EVENT    0x00 /* event information pending */
DECL|macro|CRW_ERC_AVAIL
mdefine_line|#define CRW_ERC_AVAIL    0x01 /* available */
DECL|macro|CRW_ERC_INIT
mdefine_line|#define CRW_ERC_INIT     0x02 /* initialized */
DECL|macro|CRW_ERC_TERROR
mdefine_line|#define CRW_ERC_TERROR   0x03 /* temporary error */
DECL|macro|CRW_ERC_IPARM
mdefine_line|#define CRW_ERC_IPARM    0x04 /* installed parm initialized */
DECL|macro|CRW_ERC_TERM
mdefine_line|#define CRW_ERC_TERM     0x05 /* terminal */
DECL|macro|CRW_ERC_PERRN
mdefine_line|#define CRW_ERC_PERRN    0x06 /* perm. error, fac. not init */
DECL|macro|CRW_ERC_PERRI
mdefine_line|#define CRW_ERC_PERRI    0x07 /* perm. error, facility init */
DECL|macro|CRW_ERC_PMOD
mdefine_line|#define CRW_ERC_PMOD     0x08 /* installed parameters modified */
DECL|function|stcrw
r_extern
id|__inline__
r_int
id|stcrw
c_func
(paren
r_struct
id|crw
op_star
id|pcrw
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;STCRW 0(%1)&bslash;n&bslash;t&quot;
l_string|&quot;IPM %0&bslash;n&bslash;t&quot;
l_string|&quot;SRL %0,28&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|pcrw
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
macro_line|#endif /* __s390mach */
eof

multiline_comment|/******************************************************************************&n; *&n; * atm_nicstar.h&n; *&n; * Driver-specific declarations for use by NICSTAR driver specific utils.&n; *&n; * Author: Rui Prior&n; *&n; * (C) INESC 1998&n; *&n; ******************************************************************************/
macro_line|#ifndef LINUX_ATM_NICSTAR_H
DECL|macro|LINUX_ATM_NICSTAR_H
mdefine_line|#define LINUX_ATM_NICSTAR_H
multiline_comment|/* Note: non-kernel programs including this file must also include&n; * sys/types.h for struct timeval&n; */
macro_line|#include &lt;linux/atmapi.h&gt;
macro_line|#include &lt;linux/atmioc.h&gt;
DECL|macro|NS_GETPSTAT
mdefine_line|#define NS_GETPSTAT&t;_IOWR(&squot;a&squot;,ATMIOC_SARPRV+1,struct atmif_sioc)
multiline_comment|/* get pool statistics */
DECL|macro|NS_SETBUFLEV
mdefine_line|#define NS_SETBUFLEV&t;_IOW(&squot;a&squot;,ATMIOC_SARPRV+2,struct atmif_sioc)
multiline_comment|/* set buffer level markers */
DECL|macro|NS_ADJBUFLEV
mdefine_line|#define NS_ADJBUFLEV&t;_IO(&squot;a&squot;,ATMIOC_SARPRV+3)
multiline_comment|/* adjust buffer level */
DECL|struct|buf_nr
r_typedef
r_struct
id|buf_nr
(brace
DECL|member|min
r_int
id|min
suffix:semicolon
DECL|member|init
r_int
id|init
suffix:semicolon
DECL|member|max
r_int
id|max
suffix:semicolon
DECL|typedef|buf_nr
)brace
id|buf_nr
suffix:semicolon
DECL|struct|pool_levels
r_typedef
r_struct
id|pool_levels
(brace
DECL|member|buftype
r_int
id|buftype
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* (At least for now) only used in NS_GETPSTAT */
DECL|member|level
id|buf_nr
id|level
suffix:semicolon
DECL|typedef|pool_levels
)brace
id|pool_levels
suffix:semicolon
multiline_comment|/* type must be one of the following: */
DECL|macro|NS_BUFTYPE_SMALL
mdefine_line|#define NS_BUFTYPE_SMALL 1
DECL|macro|NS_BUFTYPE_LARGE
mdefine_line|#define NS_BUFTYPE_LARGE 2
DECL|macro|NS_BUFTYPE_HUGE
mdefine_line|#define NS_BUFTYPE_HUGE 3
DECL|macro|NS_BUFTYPE_IOVEC
mdefine_line|#define NS_BUFTYPE_IOVEC 4
macro_line|#endif /* LINUX_ATM_NICSTAR_H */
eof

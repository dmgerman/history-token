multiline_comment|/*&n; *  arch/s390/kernel/s390dyn.h&n; *   S/390 data definitions for dynamic device attachment&n; *&n; *  S390 version&n; *    Copyright (C) 2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Ingo Adlung (adlung@de.ibm.com)&n; */
macro_line|#ifndef __s390dyn_h
DECL|macro|__s390dyn_h
mdefine_line|#define __s390dyn_h
macro_line|#ifndef _LINUX_LIST_H
macro_line|#include &lt;linux/list.h&gt;
macro_line|#endif
r_struct
id|_devreg
suffix:semicolon
DECL|typedef|oper_handler_func_t
r_typedef
r_int
(paren
op_star
id|oper_handler_func_t
)paren
(paren
r_int
id|irq
comma
r_struct
id|_devreg
op_star
id|dreg
)paren
suffix:semicolon
DECL|struct|_devreg_hc_t
r_typedef
r_struct
id|_devreg_hc_t
(brace
DECL|member|ctype
id|__u16
id|ctype
suffix:semicolon
DECL|member|cmode
id|__u8
id|cmode
suffix:semicolon
DECL|member|dtype
id|__u16
id|dtype
suffix:semicolon
DECL|member|dmode
id|__u8
id|dmode
suffix:semicolon
DECL|typedef|devreg_hc_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|devreg_hc_t
suffix:semicolon
DECL|struct|_devreg
r_typedef
r_struct
id|_devreg
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
r_union
(brace
DECL|member|devno
r_int
id|devno
suffix:semicolon
DECL|member|hc
id|devreg_hc_t
id|hc
suffix:semicolon
multiline_comment|/* has controller info */
DECL|member|ci
)brace
id|ci
suffix:semicolon
DECL|member|flag
r_int
id|flag
suffix:semicolon
DECL|member|oper_func
id|oper_handler_func_t
id|oper_func
suffix:semicolon
DECL|typedef|devreg_t
)brace
id|devreg_t
suffix:semicolon
DECL|macro|DEVREG_EXACT_MATCH
mdefine_line|#define DEVREG_EXACT_MATCH      0x00000001
DECL|macro|DEVREG_MATCH_DEV_TYPE
mdefine_line|#define DEVREG_MATCH_DEV_TYPE   0x00000002
DECL|macro|DEVREG_MATCH_CU_TYPE
mdefine_line|#define DEVREG_MATCH_CU_TYPE    0x00000004
DECL|macro|DEVREG_NO_CU_INFO
mdefine_line|#define DEVREG_NO_CU_INFO       0x00000008
DECL|macro|DEVREG_NO_DEV_INFO
mdefine_line|#define DEVREG_NO_DEV_INFO      0x00000010
DECL|macro|DEVREG_TYPE_DEVNO
mdefine_line|#define DEVREG_TYPE_DEVNO       0x80000000
DECL|macro|DEVREG_TYPE_DEVCHARS
mdefine_line|#define DEVREG_TYPE_DEVCHARS    0x40000000
r_int
id|s390_device_register
(paren
id|devreg_t
op_star
id|drinfo
)paren
suffix:semicolon
r_int
id|s390_device_unregister
c_func
(paren
id|devreg_t
op_star
id|dreg
)paren
suffix:semicolon
id|devreg_t
op_star
id|s390_search_devreg
(paren
id|ioinfo_t
op_star
id|ioinfo
)paren
suffix:semicolon
macro_line|#endif /* __s390dyn */
eof

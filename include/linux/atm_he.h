multiline_comment|/* atm_he.h */
macro_line|#ifndef LINUX_ATM_HE_H
DECL|macro|LINUX_ATM_HE_H
mdefine_line|#define LINUX_ATM_HE_H
macro_line|#include &lt;linux/atmioc.h&gt;
DECL|macro|HE_GET_REG
mdefine_line|#define HE_GET_REG&t;_IOW(&squot;a&squot;, ATMIOC_SARPRV, struct atmif_sioc)
DECL|macro|HE_REGTYPE_PCI
mdefine_line|#define HE_REGTYPE_PCI&t;1
DECL|macro|HE_REGTYPE_RCM
mdefine_line|#define HE_REGTYPE_RCM&t;2
DECL|macro|HE_REGTYPE_TCM
mdefine_line|#define HE_REGTYPE_TCM&t;3
DECL|macro|HE_REGTYPE_MBOX
mdefine_line|#define HE_REGTYPE_MBOX&t;4
DECL|struct|he_ioctl_reg
r_struct
id|he_ioctl_reg
(brace
DECL|member|addr
DECL|member|val
r_int
id|addr
comma
id|val
suffix:semicolon
DECL|member|type
r_char
id|type
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* LINUX_ATM_HE_H */
eof

multiline_comment|/*&n; * ia64/platform/hp/common/hp_acpi.h&n; *&n; * Copyright (C) 2003 Hewlett-Packard&n; * Copyright (C) Alex Williamson&n; * Copyright (C) Bjorn Helgaas&n; *&n; * Vendor specific extensions to ACPI.&n; */
macro_line|#ifndef _ASM_IA64_ACPI_EXT_H
DECL|macro|_ASM_IA64_ACPI_EXT_H
mdefine_line|#define _ASM_IA64_ACPI_EXT_H
macro_line|#include &lt;linux/types.h&gt;
r_extern
id|acpi_status
id|hp_acpi_csr_space
(paren
id|acpi_handle
comma
id|u64
op_star
id|base
comma
id|u64
op_star
id|length
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_ACPI_EXT_H */
eof

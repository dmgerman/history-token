macro_line|#ifndef __linux_video_edid_h__
DECL|macro|__linux_video_edid_h__
mdefine_line|#define __linux_video_edid_h__
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_PPC_OF
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_X86
DECL|struct|edid_info
r_struct
id|edid_info
(brace
DECL|member|dummy
r_int
r_char
id|dummy
(braket
l_int|128
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|edid_info
id|edid_info
suffix:semicolon
r_extern
r_char
op_star
id|get_EDID_from_BIOS
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_X86 */
macro_line|#ifdef CONFIG_PPC_OF
r_extern
r_char
op_star
id|get_EDID_from_OF
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __linux_video_edid_h__ */
eof

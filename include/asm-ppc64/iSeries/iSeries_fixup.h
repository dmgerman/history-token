macro_line|#ifndef&t;__ISERIES_FIXUP_H__
DECL|macro|__ISERIES_FIXUP_H__
mdefine_line|#define&t;__ISERIES_FIXUP_H__
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
r_void
id|iSeries_fixup
(paren
r_void
)paren
suffix:semicolon
r_void
id|iSeries_fixup_bus
(paren
r_struct
id|pci_bus
op_star
)paren
suffix:semicolon
r_int
r_int
id|iSeries_scan_slot
(paren
r_struct
id|pci_dev
op_star
comma
id|u16
comma
id|u8
comma
id|u8
)paren
suffix:semicolon
multiline_comment|/* Need to store information related to the PHB bucc and make it accessible to the hose */
DECL|struct|iSeries_hose_arch_data
r_struct
id|iSeries_hose_arch_data
(brace
DECL|member|hvBusNumber
id|u32
id|hvBusNumber
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif /* __ISERIES_FIXUP_H__ */
eof

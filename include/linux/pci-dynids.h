multiline_comment|/*&n; *&t;PCI defines and function prototypes&n; *&t;Copyright 2003 Dell Inc.&n; *        by Matt Domsch &lt;Matt_Domsch@dell.com&gt;&n; */
macro_line|#ifndef LINUX_PCI_DYNIDS_H
DECL|macro|LINUX_PCI_DYNIDS_H
mdefine_line|#define LINUX_PCI_DYNIDS_H
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/mod_devicetable.h&gt;
DECL|struct|dynid
r_struct
id|dynid
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|id
r_struct
id|pci_device_id
id|id
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof

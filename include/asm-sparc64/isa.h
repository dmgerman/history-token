multiline_comment|/* $Id: isa.h,v 1.1 2001/05/11 04:31:55 davem Exp $&n; * isa.h: Sparc64 layer for PCI to ISA bridge devices.&n; *&n; * Copyright (C) 2001 David S. Miller (davem@redhat.com)&n; */
macro_line|#ifndef __SPARC64_ISA_H
DECL|macro|__SPARC64_ISA_H
mdefine_line|#define __SPARC64_ISA_H
macro_line|#include &lt;asm/pbm.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
r_struct
id|sparc_isa_bridge
suffix:semicolon
DECL|struct|sparc_isa_device
r_struct
id|sparc_isa_device
(brace
DECL|member|next
r_struct
id|sparc_isa_device
op_star
id|next
suffix:semicolon
DECL|member|child
r_struct
id|sparc_isa_device
op_star
id|child
suffix:semicolon
DECL|member|bus
r_struct
id|sparc_isa_bridge
op_star
id|bus
suffix:semicolon
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|compatible
r_char
id|compatible
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|resource
r_struct
id|resource
id|resource
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sparc_isa_bridge
r_struct
id|sparc_isa_bridge
(brace
DECL|member|next
r_struct
id|sparc_isa_bridge
op_star
id|next
suffix:semicolon
DECL|member|devices
r_struct
id|sparc_isa_device
op_star
id|devices
suffix:semicolon
DECL|member|parent
r_struct
id|pci_pbm_info
op_star
id|parent
suffix:semicolon
DECL|member|self
r_struct
id|pci_dev
op_star
id|self
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
DECL|macro|linux_prom_isa_ranges
mdefine_line|#define linux_prom_isa_ranges linux_prom_ebus_ranges
DECL|member|isa_ranges
r_struct
id|linux_prom_isa_ranges
id|isa_ranges
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|member|num_isa_ranges
r_int
id|num_isa_ranges
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sparc_isa_bridge
op_star
id|isa_chain
suffix:semicolon
r_extern
r_void
id|isa_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|for_each_isa
mdefine_line|#define for_each_isa(bus)&t;&t;&t;&t;&t;&t;&bslash;&n;        for((bus) = isa_chain; (bus); (bus) = (bus)-&gt;next)
DECL|macro|for_each_isadev
mdefine_line|#define for_each_isadev(dev, bus)&t;&t;&t;&t;&t;&bslash;&n;        for((dev) = (bus)-&gt;devices; (dev); (dev) = (dev)-&gt;next)
macro_line|#endif /* !(__SPARC64_ISA_H) */
eof

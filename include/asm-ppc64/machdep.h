macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_MACHDEP_H
DECL|macro|_PPC_MACHDEP_H
mdefine_line|#define _PPC_MACHDEP_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
r_struct
id|pt_regs
suffix:semicolon
r_struct
id|pci_bus
suffix:semicolon
r_struct
id|pci_dev
suffix:semicolon
r_struct
id|kbd_repeat
suffix:semicolon
r_struct
id|device_node
suffix:semicolon
r_struct
id|TceTable
suffix:semicolon
r_struct
id|rtc_time
suffix:semicolon
DECL|struct|machdep_calls
r_struct
id|machdep_calls
(brace
multiline_comment|/* High use functions in the first cachelines, low use functions&n;&t; * follow.  DRENG collect profile data.&n;&t; */
DECL|member|hpte_invalidate
r_void
(paren
op_star
id|hpte_invalidate
)paren
(paren
r_int
r_int
id|slot
)paren
suffix:semicolon
DECL|member|hpte_updatepp
r_void
(paren
op_star
id|hpte_updatepp
)paren
(paren
r_int
id|slot
comma
r_int
r_int
id|newpp
comma
r_int
r_int
id|va
)paren
suffix:semicolon
DECL|member|hpte_updateboltedpp
r_void
(paren
op_star
id|hpte_updateboltedpp
)paren
(paren
r_int
r_int
id|newpp
comma
r_int
r_int
id|ea
)paren
suffix:semicolon
DECL|member|hpte_getword0
r_int
r_int
(paren
op_star
id|hpte_getword0
)paren
(paren
r_int
r_int
id|slot
)paren
suffix:semicolon
DECL|member|hpte_find
r_int
(paren
op_star
id|hpte_find
)paren
(paren
r_int
r_int
id|vpn
)paren
suffix:semicolon
DECL|member|hpte_selectslot
r_int
(paren
op_star
id|hpte_selectslot
)paren
(paren
r_int
r_int
id|vpn
)paren
suffix:semicolon
DECL|member|hpte_create_valid
r_void
(paren
op_star
id|hpte_create_valid
)paren
(paren
r_int
r_int
id|slot
comma
r_int
r_int
id|vpn
comma
r_int
r_int
id|prpn
comma
r_int
id|hash
comma
r_void
op_star
id|ptep
comma
r_int
id|hpteflags
comma
r_int
id|bolted
)paren
suffix:semicolon
DECL|member|tce_build
r_void
(paren
op_star
id|tce_build
)paren
(paren
r_struct
id|TceTable
op_star
id|tbl
comma
r_int
id|tcenum
comma
r_int
r_int
id|uaddr
comma
r_int
id|direction
)paren
suffix:semicolon
DECL|member|tce_free
r_void
(paren
op_star
id|tce_free
)paren
(paren
r_struct
id|TceTable
op_star
id|tbl
comma
id|dma_addr_t
id|dma_addr
comma
r_int
id|order
comma
r_int
id|numPages
)paren
suffix:semicolon
DECL|member|smp_message_pass
r_void
(paren
op_star
id|smp_message_pass
)paren
(paren
r_int
id|target
comma
r_int
id|msg
comma
r_int
r_int
id|data
comma
r_int
id|wait
)paren
suffix:semicolon
DECL|member|smp_probe
r_int
(paren
op_star
id|smp_probe
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|smp_kick_cpu
r_void
(paren
op_star
id|smp_kick_cpu
)paren
(paren
r_int
id|nr
)paren
suffix:semicolon
DECL|member|smp_setup_cpu
r_void
(paren
op_star
id|smp_setup_cpu
)paren
(paren
r_int
id|nr
)paren
suffix:semicolon
DECL|member|setup_arch
r_void
(paren
op_star
id|setup_arch
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Optional, may be NULL. */
DECL|member|setup_residual
r_void
(paren
op_star
id|setup_residual
)paren
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_int
id|cpu_id
)paren
suffix:semicolon
multiline_comment|/* Optional, may be NULL. */
DECL|member|get_cpuinfo
r_void
(paren
op_star
id|get_cpuinfo
)paren
(paren
r_struct
id|seq_file
op_star
id|m
)paren
suffix:semicolon
multiline_comment|/* Optional, may be NULL. */
DECL|member|irq_cannonicalize
r_int
r_int
(paren
op_star
id|irq_cannonicalize
)paren
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|member|init_IRQ
r_void
(paren
op_star
id|init_IRQ
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|init_ras_IRQ
r_void
(paren
op_star
id|init_ras_IRQ
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|get_irq
r_int
(paren
op_star
id|get_irq
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|member|post_irq
r_void
(paren
op_star
id|post_irq
)paren
(paren
r_struct
id|pt_regs
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* A general init function, called by ppc_init in init/main.c.&n;&t;   May be NULL. */
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|restart
r_void
(paren
op_star
id|restart
)paren
(paren
r_char
op_star
id|cmd
)paren
suffix:semicolon
DECL|member|power_off
r_void
(paren
op_star
id|power_off
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|halt
r_void
(paren
op_star
id|halt
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|time_init
r_int
(paren
op_star
id|time_init
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Optional, may be NULL */
DECL|member|set_rtc_time
r_int
(paren
op_star
id|set_rtc_time
)paren
(paren
r_struct
id|rtc_time
op_star
)paren
suffix:semicolon
DECL|member|get_rtc_time
r_void
(paren
op_star
id|get_rtc_time
)paren
(paren
r_struct
id|rtc_time
op_star
)paren
suffix:semicolon
DECL|member|get_boot_time
r_void
(paren
op_star
id|get_boot_time
)paren
(paren
r_struct
id|rtc_time
op_star
)paren
suffix:semicolon
DECL|member|calibrate_decr
r_void
(paren
op_star
id|calibrate_decr
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|progress
r_void
(paren
op_star
id|progress
)paren
(paren
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|nvram_read_val
r_int
r_char
(paren
op_star
id|nvram_read_val
)paren
(paren
r_int
id|addr
)paren
suffix:semicolon
DECL|member|nvram_write_val
r_void
(paren
op_star
id|nvram_write_val
)paren
(paren
r_int
id|addr
comma
r_int
r_char
id|val
)paren
suffix:semicolon
multiline_comment|/* Tons of keyboard stuff. */
DECL|member|kbd_setkeycode
r_int
(paren
op_star
id|kbd_setkeycode
)paren
(paren
r_int
r_int
id|scancode
comma
r_int
r_int
id|keycode
)paren
suffix:semicolon
DECL|member|kbd_getkeycode
r_int
(paren
op_star
id|kbd_getkeycode
)paren
(paren
r_int
r_int
id|scancode
)paren
suffix:semicolon
DECL|member|kbd_translate
r_int
(paren
op_star
id|kbd_translate
)paren
(paren
r_int
r_char
id|scancode
comma
r_int
r_char
op_star
id|keycode
comma
r_char
id|raw_mode
)paren
suffix:semicolon
DECL|member|kbd_unexpected_up
r_char
(paren
op_star
id|kbd_unexpected_up
)paren
(paren
r_int
r_char
id|keycode
)paren
suffix:semicolon
DECL|member|kbd_leds
r_void
(paren
op_star
id|kbd_leds
)paren
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
DECL|member|kbd_init_hw
r_void
(paren
op_star
id|kbd_init_hw
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
DECL|member|ppc_kbd_sysrq_xlate
r_int
r_char
op_star
id|ppc_kbd_sysrq_xlate
suffix:semicolon
macro_line|#endif
multiline_comment|/* Debug interface.  Low level I/O to some terminal device */
DECL|member|udbg_putc
r_void
(paren
op_star
id|udbg_putc
)paren
(paren
r_int
r_char
id|c
)paren
suffix:semicolon
DECL|member|udbg_getc
r_int
r_char
(paren
op_star
id|udbg_getc
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|udbg_getc_poll
r_int
(paren
op_star
id|udbg_getc_poll
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* PCI interfaces */
DECL|member|pcibios_read_config_byte
r_int
(paren
op_star
id|pcibios_read_config_byte
)paren
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_int
id|offset
comma
id|u8
op_star
id|val
)paren
suffix:semicolon
DECL|member|pcibios_read_config_word
r_int
(paren
op_star
id|pcibios_read_config_word
)paren
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_int
id|offset
comma
id|u16
op_star
id|val
)paren
suffix:semicolon
DECL|member|pcibios_read_config_dword
r_int
(paren
op_star
id|pcibios_read_config_dword
)paren
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_int
id|offset
comma
id|u32
op_star
id|val
)paren
suffix:semicolon
DECL|member|pcibios_write_config_byte
r_int
(paren
op_star
id|pcibios_write_config_byte
)paren
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_int
id|offset
comma
id|u8
id|val
)paren
suffix:semicolon
DECL|member|pcibios_write_config_word
r_int
(paren
op_star
id|pcibios_write_config_word
)paren
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_int
id|offset
comma
id|u16
id|val
)paren
suffix:semicolon
DECL|member|pcibios_write_config_dword
r_int
(paren
op_star
id|pcibios_write_config_dword
)paren
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_int
id|offset
comma
id|u32
id|val
)paren
suffix:semicolon
multiline_comment|/* Called after scanning the bus, before allocating&n;&t; * resources&n;&t; */
DECL|member|pcibios_fixup
r_void
(paren
op_star
id|pcibios_fixup
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Called for each PCI bus in the system&n;        * when it&squot;s probed&n;        */
DECL|member|pcibios_fixup_bus
r_void
(paren
op_star
id|pcibios_fixup_bus
)paren
(paren
r_struct
id|pci_bus
op_star
)paren
suffix:semicolon
multiline_comment|/* Called when pci_enable_device() is called (initial=0) or&n;        * when a device with no assigned resource is found (initial=1).&n;        * Returns 0 to allow assignement/enabling of the device&n;        */
DECL|member|pcibios_enable_device_hook
r_int
(paren
op_star
id|pcibios_enable_device_hook
)paren
(paren
r_struct
id|pci_dev
op_star
comma
r_int
id|initial
)paren
suffix:semicolon
DECL|member|pci_dev_io_base
r_void
op_star
(paren
op_star
id|pci_dev_io_base
)paren
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|devfn
comma
r_int
id|physical
)paren
suffix:semicolon
DECL|member|pci_dev_mem_base
r_void
op_star
(paren
op_star
id|pci_dev_mem_base
)paren
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|devfn
)paren
suffix:semicolon
DECL|member|pci_dev_root_bridge
r_int
(paren
op_star
id|pci_dev_root_bridge
)paren
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|devfn
)paren
suffix:semicolon
multiline_comment|/* this is for modules, since _machine can be a define -- Cort */
DECL|member|ppc_machine
r_int
id|ppc_machine
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|machdep_calls
id|ppc_md
suffix:semicolon
r_extern
r_char
id|cmd_line
(braket
l_int|512
)braket
suffix:semicolon
r_extern
r_void
id|setup_pci_ptrs
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Power macintoshes have either a CUDA or a PMU controlling&n; * system reset, power, NVRAM, RTC.&n; */
DECL|enum|sys_ctrler_kind
r_typedef
r_enum
id|sys_ctrler_kind
(brace
DECL|enumerator|SYS_CTRLER_UNKNOWN
id|SYS_CTRLER_UNKNOWN
op_assign
l_int|0
comma
DECL|enumerator|SYS_CTRLER_CUDA
id|SYS_CTRLER_CUDA
op_assign
l_int|1
comma
DECL|enumerator|SYS_CTRLER_PMU
id|SYS_CTRLER_PMU
op_assign
l_int|2
comma
DECL|typedef|sys_ctrler_t
)brace
id|sys_ctrler_t
suffix:semicolon
r_extern
id|sys_ctrler_t
id|sys_ctrler
suffix:semicolon
macro_line|#endif /* _PPC_MACHDEP_H */
macro_line|#endif /* __KERNEL__ */
eof
multiline_comment|/*&n; * Linux driver attachment glue for PCI based controllers.&n; *&n; * Copyright (c) 2000 Adaptec Inc.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; * $Id: //depot/src/linux/drivers/scsi/aic7xxx/aic7xxx_linux_pci.c#15 $&n; */
macro_line|#include &quot;aic7xxx_osm.h&quot;
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,4,0)
DECL|struct|pci_device_id
r_struct
id|pci_device_id
(brace
)brace
suffix:semicolon
macro_line|#endif
r_static
r_int
id|ahc_linux_pci_dev_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
r_static
r_void
id|ahc_linux_pci_dev_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
suffix:semicolon
multiline_comment|/* We do our own ID filtering.  So, grab all SCSI storage class devices. */
DECL|variable|ahc_linux_pci_id_table
r_static
r_struct
id|pci_device_id
id|ahc_linux_pci_id_table
(braket
)braket
op_assign
(brace
(brace
l_int|0x9004
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|PCI_CLASS_STORAGE_SCSI
op_lshift
l_int|8
comma
l_int|0xFFFF00
comma
l_int|0
)brace
comma
(brace
l_int|0x9005
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|PCI_CLASS_STORAGE_SCSI
op_lshift
l_int|8
comma
l_int|0xFFFF00
comma
l_int|0
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|aic7xxx_pci_driver
r_static
r_struct
id|pci_driver
id|aic7xxx_pci_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;aic7xxx&quot;
comma
id|probe
suffix:colon
id|ahc_linux_pci_dev_probe
comma
id|remove
suffix:colon
id|ahc_linux_pci_dev_remove
comma
id|id_table
suffix:colon
id|ahc_linux_pci_id_table
)brace
suffix:semicolon
r_static
r_void
DECL|function|ahc_linux_pci_dev_remove
id|ahc_linux_pci_dev_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|ahc_softc
op_star
id|ahc
suffix:semicolon
r_struct
id|ahc_softc
op_star
id|list_ahc
suffix:semicolon
multiline_comment|/*&n;&t; * We should be able to just perform&n;&t; * the free directly, but check our&n;&t; * list for extra sanity.&n;&t; */
id|ahc
op_assign
(paren
r_struct
id|ahc_softc
op_star
)paren
id|pdev-&gt;driver_data
suffix:semicolon
id|TAILQ_FOREACH
c_func
(paren
id|list_ahc
comma
op_amp
id|ahc_tailq
comma
id|links
)paren
(brace
r_if
c_cond
(paren
id|list_ahc
op_eq
id|ahc
)paren
(brace
id|ahc_free
c_func
(paren
id|ahc
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* !LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,4,0) */
r_static
r_int
DECL|function|ahc_linux_pci_dev_probe
id|ahc_linux_pci_dev_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
r_char
id|buf
(braket
l_int|80
)braket
suffix:semicolon
r_struct
id|ahc_softc
op_star
id|ahc
suffix:semicolon
id|ahc_dev_softc_t
id|pci
suffix:semicolon
r_struct
id|ahc_pci_identity
op_star
id|entry
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
id|error
suffix:semicolon
id|pci
op_assign
id|pdev
suffix:semicolon
id|entry
op_assign
id|ahc_find_pci_device
c_func
(paren
id|pci
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
op_eq
l_int|NULL
)paren
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate a softc for this card and&n;&t; * set it up for attachment by our&n;&t; * common detect routine.&n;&t; */
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;ahc_pci:%d:%d:%d&quot;
comma
id|ahc_get_pci_bus
c_func
(paren
id|pci
)paren
comma
id|ahc_get_pci_slot
c_func
(paren
id|pci
)paren
comma
id|ahc_get_pci_function
c_func
(paren
id|pci
)paren
)paren
suffix:semicolon
id|name
op_assign
id|malloc
c_func
(paren
id|strlen
c_func
(paren
id|buf
)paren
op_plus
l_int|1
comma
id|M_DEVBUF
comma
id|M_NOWAIT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name
op_eq
l_int|NULL
)paren
r_return
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|name
comma
id|buf
)paren
suffix:semicolon
id|ahc
op_assign
id|ahc_alloc
c_func
(paren
l_int|NULL
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ahc
op_eq
l_int|NULL
)paren
r_return
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|pdev
)paren
)paren
(brace
id|ahc_free
c_func
(paren
id|ahc
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
id|pci_set_master
c_func
(paren
id|pdev
)paren
suffix:semicolon
macro_line|#endif
id|ahc-&gt;dev_softc
op_assign
id|pci
suffix:semicolon
id|ahc-&gt;platform_data-&gt;irq
op_assign
id|pdev-&gt;irq
suffix:semicolon
id|error
op_assign
id|ahc_pci_config
c_func
(paren
id|ahc
comma
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
l_int|0
)paren
(brace
id|ahc_free
c_func
(paren
id|ahc
)paren
suffix:semicolon
r_return
(paren
op_minus
id|error
)paren
suffix:semicolon
)brace
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
id|pdev-&gt;driver_data
op_assign
id|ahc
suffix:semicolon
r_if
c_cond
(paren
id|aic7xxx_detect_complete
)paren
id|aic7xxx_register_host
c_func
(paren
id|ahc
comma
id|aic7xxx_driver_template
)paren
suffix:semicolon
macro_line|#endif
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_int
DECL|function|ahc_linux_pci_probe
id|ahc_linux_pci_probe
c_func
(paren
id|Scsi_Host_Template
op_star
r_template
)paren
(brace
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
r_return
(paren
id|pci_module_init
c_func
(paren
op_amp
id|aic7xxx_pci_driver
)paren
)paren
suffix:semicolon
macro_line|#else
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
id|u_int
r_class
suffix:semicolon
r_int
id|found
suffix:semicolon
multiline_comment|/* If we don&squot;t have a PCI bus, we can&squot;t find any adapters. */
r_if
c_cond
(paren
id|pci_present
c_func
(paren
)paren
op_eq
l_int|0
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
id|found
op_assign
l_int|0
suffix:semicolon
id|pdev
op_assign
l_int|NULL
suffix:semicolon
r_class
op_assign
id|PCI_CLASS_STORAGE_SCSI
op_lshift
l_int|8
suffix:semicolon
r_while
c_loop
(paren
(paren
id|pdev
op_assign
id|pci_find_class
c_func
(paren
r_class
comma
id|pdev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_struct
id|ahc_softc
op_star
id|ahc
suffix:semicolon
id|ahc_dev_softc_t
id|pci
suffix:semicolon
r_int
id|error
suffix:semicolon
id|pci
op_assign
id|pdev
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Some BIOSen report the same device multiple times.&n;&t;&t; */
id|TAILQ_FOREACH
c_func
(paren
id|ahc
comma
op_amp
id|ahc_tailq
comma
id|links
)paren
(brace
r_struct
id|pci_dev
op_star
id|probed_pdev
suffix:semicolon
id|probed_pdev
op_assign
id|ahc-&gt;dev_softc
suffix:semicolon
r_if
c_cond
(paren
id|probed_pdev-&gt;bus-&gt;number
op_eq
id|pdev-&gt;bus-&gt;number
op_logical_and
id|probed_pdev-&gt;devfn
op_eq
id|pdev-&gt;devfn
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ahc
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Skip duplicate. */
r_continue
suffix:semicolon
)brace
id|error
op_assign
id|ahc_linux_pci_dev_probe
c_func
(paren
id|pdev
comma
multiline_comment|/*pci_devid*/
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
id|found
op_increment
suffix:semicolon
)brace
r_return
(paren
id|found
)paren
suffix:semicolon
macro_line|#endif
)brace
r_int
DECL|function|ahc_pci_map_registers
id|ahc_pci_map_registers
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
(brace
r_uint32
id|command
suffix:semicolon
id|u_long
id|base
suffix:semicolon
id|u_long
id|start
suffix:semicolon
id|u_long
id|base_page
suffix:semicolon
id|u_long
id|base_offset
suffix:semicolon
r_uint8
op_star
id|maddr
suffix:semicolon
id|command
op_assign
id|ahc_pci_read_config
c_func
(paren
id|ahc-&gt;dev_softc
comma
id|PCIR_COMMAND
comma
l_int|4
)paren
suffix:semicolon
id|base
op_assign
l_int|0
suffix:semicolon
id|maddr
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef MMAPIO
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,0)
id|start
op_assign
id|pci_resource_start
c_func
(paren
id|ahc-&gt;dev_softc
comma
l_int|1
)paren
suffix:semicolon
id|base_page
op_assign
id|start
op_amp
id|PAGE_MASK
suffix:semicolon
id|base_offset
op_assign
id|start
op_minus
id|base_page
suffix:semicolon
macro_line|#else
id|start
op_assign
id|ahc_pci_read_config
c_func
(paren
id|ahc-&gt;dev_softc
comma
id|PCIR_MAPS
op_plus
l_int|4
comma
l_int|4
)paren
suffix:semicolon
id|base_offset
op_assign
id|start
op_amp
id|PCI_BASE_ADDRESS_MEM_MASK
suffix:semicolon
id|base_page
op_assign
id|base_offset
op_amp
id|PAGE_MASK
suffix:semicolon
id|base_offset
op_sub_assign
id|base_page
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|start
op_ne
l_int|0
)paren
(brace
id|ahc-&gt;platform_data-&gt;mem_busaddr
op_assign
id|start
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
r_if
c_cond
(paren
id|request_mem_region
c_func
(paren
id|start
comma
l_int|0x1000
comma
l_string|&quot;aic7xxx&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;aic7xxx: PCI%d:%d:%d MEM region 0x%lx &quot;
l_string|&quot;in use. Cannot map device.&bslash;n&quot;
comma
id|ahc_get_pci_bus
c_func
(paren
id|ahc-&gt;dev_softc
)paren
comma
id|ahc_get_pci_slot
c_func
(paren
id|ahc-&gt;dev_softc
)paren
comma
id|ahc_get_pci_function
c_func
(paren
id|ahc-&gt;dev_softc
)paren
comma
id|start
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
id|maddr
op_assign
id|ioremap_nocache
c_func
(paren
id|base_page
comma
id|base_offset
op_plus
l_int|256
)paren
suffix:semicolon
r_if
c_cond
(paren
id|maddr
op_ne
l_int|NULL
)paren
(brace
id|ahc-&gt;tag
op_assign
id|BUS_SPACE_MEMIO
suffix:semicolon
id|ahc-&gt;bsh.maddr
op_assign
id|maddr
op_plus
id|base_offset
suffix:semicolon
id|command
op_or_assign
id|PCIM_CMD_MEMEN
suffix:semicolon
id|ahc_pci_write_config
c_func
(paren
id|ahc-&gt;dev_softc
comma
id|PCIR_COMMAND
comma
id|command
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Do a quick test to see if memory mapped&n;&t;&t;&t; * I/O is functioning correctly.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|HCNTRL
)paren
op_eq
l_int|0xFF
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;aic7xxx: PCI Device %d:%d:%d &quot;
l_string|&quot;failed memory mapped test&bslash;n&quot;
comma
id|ahc_get_pci_bus
c_func
(paren
id|ahc-&gt;dev_softc
)paren
comma
id|ahc_get_pci_slot
c_func
(paren
id|ahc-&gt;dev_softc
)paren
comma
id|ahc_get_pci_function
c_func
(paren
id|ahc-&gt;dev_softc
)paren
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|base_page
)paren
suffix:semicolon
id|maddr
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|command
op_and_assign
op_complement
id|PCIM_CMD_PORTEN
suffix:semicolon
id|ahc_pci_write_config
c_func
(paren
id|ahc-&gt;dev_softc
comma
id|PCIR_COMMAND
comma
id|command
comma
l_int|4
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * We always prefer memory mapped access.  Only&n;&t; * complain about our ioport conflicting with&n;&t; * another device if we are going to use it.&n;&t; */
r_if
c_cond
(paren
id|maddr
op_eq
l_int|NULL
)paren
(brace
id|ahc-&gt;tag
op_assign
id|BUS_SPACE_PIO
suffix:semicolon
id|command
op_and_assign
op_complement
(paren
id|PCIM_CMD_MEMEN
op_or
id|PCIM_CMD_PORTEN
)paren
suffix:semicolon
id|ahc_pci_write_config
c_func
(paren
id|ahc-&gt;dev_softc
comma
id|PCIR_COMMAND
comma
id|command
comma
l_int|4
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,0)
id|base
op_assign
id|pci_resource_start
c_func
(paren
id|ahc-&gt;dev_softc
comma
l_int|0
)paren
suffix:semicolon
macro_line|#else
id|base
op_assign
id|ahc_pci_read_config
c_func
(paren
id|ahc-&gt;dev_softc
comma
id|PCIR_MAPS
comma
l_int|4
)paren
suffix:semicolon
id|base
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|base
op_eq
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;aic7xxx: PCI%d:%d:%d No mapping available. &quot;
l_string|&quot;Cannot map device.&bslash;n&quot;
comma
id|ahc_get_pci_bus
c_func
(paren
id|ahc-&gt;dev_softc
)paren
comma
id|ahc_get_pci_slot
c_func
(paren
id|ahc-&gt;dev_softc
)paren
comma
id|ahc_get_pci_function
c_func
(paren
id|ahc-&gt;dev_softc
)paren
)paren
suffix:semicolon
r_return
(paren
id|ENXIO
)paren
suffix:semicolon
)brace
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,4,0)
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|base
comma
l_int|256
)paren
op_ne
l_int|0
)paren
(brace
macro_line|#else
r_if
c_cond
(paren
id|request_region
c_func
(paren
id|base
comma
l_int|256
comma
l_string|&quot;aic7xxx&quot;
)paren
op_eq
l_int|0
)paren
(brace
macro_line|#endif
id|printf
c_func
(paren
l_string|&quot;aic7xxx: PCI%d:%d:%d IO region 0x%lx[0..255] &quot;
l_string|&quot;in use. Cannot map device.&bslash;n&quot;
comma
id|ahc_get_pci_bus
c_func
(paren
id|ahc-&gt;dev_softc
)paren
comma
id|ahc_get_pci_slot
c_func
(paren
id|ahc-&gt;dev_softc
)paren
comma
id|ahc_get_pci_function
c_func
(paren
id|ahc-&gt;dev_softc
)paren
comma
id|base
)paren
suffix:semicolon
id|base
op_assign
l_int|0
suffix:semicolon
r_return
(paren
id|EBUSY
)paren
suffix:semicolon
)brace
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,4,0)
id|request_region
c_func
(paren
id|base
comma
l_int|256
comma
l_string|&quot;aic7xxx&quot;
)paren
suffix:semicolon
macro_line|#endif
id|ahc-&gt;bsh.ioport
op_assign
id|base
suffix:semicolon
id|command
op_or_assign
id|PCIM_CMD_PORTEN
suffix:semicolon
id|ahc_pci_write_config
c_func
(paren
id|ahc-&gt;dev_softc
comma
id|PCIR_COMMAND
comma
id|command
comma
l_int|4
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_int
DECL|function|ahc_pci_map_int
id|ahc_pci_map_int
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
(brace
r_int
id|error
suffix:semicolon
id|ahc-&gt;platform_data-&gt;irq
op_assign
id|ahc-&gt;dev_softc-&gt;irq
suffix:semicolon
id|error
op_assign
id|request_irq
c_func
(paren
id|ahc-&gt;platform_data-&gt;irq
comma
id|aic7xxx_isr
comma
id|SA_INTERRUPT
op_or
id|SA_SHIRQ
comma
l_string|&quot;aic7xxx&quot;
comma
id|ahc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
id|error
op_assign
id|request_irq
c_func
(paren
id|ahc-&gt;platform_data-&gt;irq
comma
id|aic7xxx_isr
comma
id|SA_SHIRQ
comma
l_string|&quot;aic7xxx&quot;
comma
id|ahc
)paren
suffix:semicolon
r_return
(paren
op_minus
id|error
)paren
suffix:semicolon
)brace
eof

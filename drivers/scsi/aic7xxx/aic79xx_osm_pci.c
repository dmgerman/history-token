multiline_comment|/*&n; * Linux driver attachment glue for PCI based U320 controllers.&n; *&n; * Copyright (c) 2000-2001 Adaptec Inc.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; *&n; * $Id: //depot/aic7xxx/linux/drivers/scsi/aic7xxx/aic79xx_osm_pci.c#23 $&n; */
macro_line|#include &quot;aic79xx_osm.h&quot;
macro_line|#include &quot;aic79xx_inline.h&quot;
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
id|ahd_linux_pci_dev_probe
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
r_static
r_int
id|ahd_linux_pci_reserve_io_regions
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
id|u_long
op_star
id|base
comma
id|u_long
op_star
id|base2
)paren
suffix:semicolon
macro_line|#ifdef MMAPIO
r_static
r_int
id|ahd_linux_pci_reserve_mem_region
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
id|u_long
op_star
id|bus_addr
comma
r_uint8
op_star
op_star
id|maddr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
r_static
r_void
id|ahd_linux_pci_dev_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
suffix:semicolon
multiline_comment|/* We do our own ID filtering.  So, grab all SCSI storage class devices. */
DECL|variable|ahd_linux_pci_id_table
r_static
r_struct
id|pci_device_id
id|ahd_linux_pci_id_table
(braket
)braket
op_assign
(brace
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
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|ahd_linux_pci_id_table
)paren
suffix:semicolon
DECL|variable|aic79xx_pci_driver
r_struct
id|pci_driver
id|aic79xx_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;aic79xx&quot;
comma
dot
id|probe
op_assign
id|ahd_linux_pci_dev_probe
comma
dot
id|remove
op_assign
id|ahd_linux_pci_dev_remove
comma
dot
id|id_table
op_assign
id|ahd_linux_pci_id_table
)brace
suffix:semicolon
r_static
r_void
DECL|function|ahd_linux_pci_dev_remove
id|ahd_linux_pci_dev_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|ahd_softc
op_star
id|ahd
suffix:semicolon
id|u_long
id|l
suffix:semicolon
multiline_comment|/*&n;&t; * We should be able to just perform&n;&t; * the free directly, but check our&n;&t; * list for extra sanity.&n;&t; */
id|ahd_list_lock
c_func
(paren
op_amp
id|l
)paren
suffix:semicolon
id|ahd
op_assign
id|ahd_find_softc
c_func
(paren
(paren
r_struct
id|ahd_softc
op_star
)paren
id|pci_get_drvdata
c_func
(paren
id|pdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ahd
op_ne
l_int|NULL
)paren
(brace
id|u_long
id|s
suffix:semicolon
id|ahd_lock
c_func
(paren
id|ahd
comma
op_amp
id|s
)paren
suffix:semicolon
id|ahd_intr_enable
c_func
(paren
id|ahd
comma
id|FALSE
)paren
suffix:semicolon
id|ahd_unlock
c_func
(paren
id|ahd
comma
op_amp
id|s
)paren
suffix:semicolon
id|ahd_free
c_func
(paren
id|ahd
)paren
suffix:semicolon
)brace
id|ahd_list_unlock
c_func
(paren
op_amp
id|l
)paren
suffix:semicolon
)brace
macro_line|#endif /* !LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,4,0) */
r_static
r_int
DECL|function|ahd_linux_pci_dev_probe
id|ahd_linux_pci_dev_probe
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
id|ahd_softc
op_star
id|ahd
suffix:semicolon
id|ahd_dev_softc_t
id|pci
suffix:semicolon
r_struct
id|ahd_pci_identity
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
multiline_comment|/*&n;&t; * Some BIOSen report the same device multiple times.&n;&t; */
id|TAILQ_FOREACH
c_func
(paren
id|ahd
comma
op_amp
id|ahd_tailq
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
id|ahd-&gt;dev_softc
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
id|ahd
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Skip duplicate. */
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
id|pci
op_assign
id|pdev
suffix:semicolon
id|entry
op_assign
id|ahd_find_pci_device
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
l_string|&quot;ahd_pci:%d:%d:%d&quot;
comma
id|ahd_get_pci_bus
c_func
(paren
id|pci
)paren
comma
id|ahd_get_pci_slot
c_func
(paren
id|pci
)paren
comma
id|ahd_get_pci_function
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
id|ahd
op_assign
id|ahd_alloc
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
id|ahd
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
id|ahd_free
c_func
(paren
id|ahd
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
r_if
c_cond
(paren
r_sizeof
(paren
id|bus_addr_t
)paren
OG
l_int|4
)paren
(brace
r_uint64
id|memsize
suffix:semicolon
id|bus_addr_t
id|mask_64bit
suffix:semicolon
id|bus_addr_t
id|mask_39bit
suffix:semicolon
id|memsize
op_assign
id|ahd_linux_get_memsize
c_func
(paren
)paren
suffix:semicolon
id|mask_64bit
op_assign
(paren
id|bus_addr_t
)paren
(paren
l_int|0xFFFFFFFFFFFFFFFFULL
op_amp
(paren
id|bus_addr_t
)paren
op_complement
l_int|0
)paren
suffix:semicolon
id|mask_39bit
op_assign
(paren
id|bus_addr_t
)paren
(paren
l_int|0x7FFFFFFFFFULL
op_amp
(paren
id|bus_addr_t
)paren
op_complement
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memsize
op_ge
l_int|0x8000000000ULL
op_logical_and
id|ahd_pci_set_dma_mask
c_func
(paren
id|pdev
comma
id|mask_64bit
)paren
op_eq
l_int|0
)paren
(brace
id|ahd-&gt;flags
op_or_assign
id|AHD_64BIT_ADDRESSING
suffix:semicolon
id|ahd-&gt;platform_data-&gt;hw_dma_mask
op_assign
id|mask_64bit
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|memsize
OG
l_int|0x80000000
op_logical_and
id|ahd_pci_set_dma_mask
c_func
(paren
id|pdev
comma
id|mask_39bit
)paren
op_eq
l_int|0
)paren
(brace
id|ahd-&gt;flags
op_or_assign
id|AHD_39BIT_ADDRESSING
suffix:semicolon
id|ahd-&gt;platform_data-&gt;hw_dma_mask
op_assign
id|mask_39bit
suffix:semicolon
)brace
)brace
r_else
(brace
id|ahd_pci_set_dma_mask
c_func
(paren
id|pdev
comma
l_int|0xFFFFFFFF
)paren
suffix:semicolon
id|ahd-&gt;platform_data-&gt;hw_dma_mask
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
)brace
macro_line|#endif
id|ahd-&gt;dev_softc
op_assign
id|pci
suffix:semicolon
id|error
op_assign
id|ahd_pci_config
c_func
(paren
id|ahd
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
id|ahd_free
c_func
(paren
id|ahd
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
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
id|ahd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aic79xx_detect_complete
)paren
(brace
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,0)
id|ahd_linux_register_host
c_func
(paren
id|ahd
comma
op_amp
id|aic79xx_driver_template
)paren
suffix:semicolon
macro_line|#else
id|printf
c_func
(paren
l_string|&quot;aic79xx: ignoring PCI device found after &quot;
l_string|&quot;initialization&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_int
DECL|function|ahd_linux_pci_init
id|ahd_linux_pci_init
c_func
(paren
r_void
)paren
(brace
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
r_return
(paren
id|pci_module_init
c_func
(paren
op_amp
id|aic79xx_pci_driver
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
id|ahd_dev_softc_t
id|pci
suffix:semicolon
r_int
id|error
suffix:semicolon
id|pci
op_assign
id|pdev
suffix:semicolon
id|error
op_assign
id|ahd_linux_pci_dev_probe
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
r_void
DECL|function|ahd_linux_pci_exit
id|ahd_linux_pci_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|aic79xx_pci_driver
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ahd_linux_pci_reserve_io_regions
id|ahd_linux_pci_reserve_io_regions
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
id|u_long
op_star
id|base
comma
id|u_long
op_star
id|base2
)paren
(brace
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,0)
op_star
id|base
op_assign
id|pci_resource_start
c_func
(paren
id|ahd-&gt;dev_softc
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is really the 3rd bar and should be at index 2,&n;&t; * but the Linux PCI code doesn&squot;t know how to &quot;count&quot; 64bit&n;&t; * bars.&n;&t; */
op_star
id|base2
op_assign
id|pci_resource_start
c_func
(paren
id|ahd-&gt;dev_softc
comma
l_int|3
)paren
suffix:semicolon
macro_line|#else
op_star
id|base
op_assign
id|ahd_pci_read_config
c_func
(paren
id|ahd-&gt;dev_softc
comma
id|AHD_PCI_IOADDR0
comma
l_int|4
)paren
suffix:semicolon
op_star
id|base2
op_assign
id|ahd_pci_read_config
c_func
(paren
id|ahd-&gt;dev_softc
comma
id|AHD_PCI_IOADDR1
comma
l_int|4
)paren
suffix:semicolon
op_star
id|base
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
op_star
id|base2
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_star
id|base
op_eq
l_int|0
op_logical_or
op_star
id|base2
op_eq
l_int|0
)paren
r_return
(paren
id|ENOMEM
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,4,0)
r_if
c_cond
(paren
id|check_region
c_func
(paren
op_star
id|base
comma
l_int|256
)paren
op_ne
l_int|0
op_logical_or
id|check_region
c_func
(paren
op_star
id|base2
comma
l_int|256
)paren
op_ne
l_int|0
)paren
r_return
(paren
id|ENOMEM
)paren
suffix:semicolon
id|request_region
c_func
(paren
op_star
id|base
comma
l_int|256
comma
l_string|&quot;aic79xx&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
op_star
id|base2
comma
l_int|256
comma
l_string|&quot;aic79xx&quot;
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|request_region
c_func
(paren
op_star
id|base
comma
l_int|256
comma
l_string|&quot;aic79xx&quot;
)paren
op_eq
l_int|0
)paren
r_return
(paren
id|ENOMEM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_region
c_func
(paren
op_star
id|base2
comma
l_int|256
comma
l_string|&quot;aic79xx&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|release_region
c_func
(paren
op_star
id|base2
comma
l_int|256
)paren
suffix:semicolon
r_return
(paren
id|ENOMEM
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifdef MMAPIO
r_static
r_int
DECL|function|ahd_linux_pci_reserve_mem_region
id|ahd_linux_pci_reserve_mem_region
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
id|u_long
op_star
id|bus_addr
comma
r_uint8
op_star
op_star
id|maddr
)paren
(brace
id|u_long
id|start
suffix:semicolon
id|u_long
id|base_page
suffix:semicolon
id|u_long
id|base_offset
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|aic79xx_allow_memio
op_eq
l_int|0
)paren
r_return
(paren
id|ENOMEM
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ahd-&gt;bugs
op_amp
id|AHD_PCIX_MMAPIO_BUG
)paren
op_ne
l_int|0
)paren
r_return
(paren
id|ENOMEM
)paren
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,0)
id|start
op_assign
id|pci_resource_start
c_func
(paren
id|ahd-&gt;dev_softc
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
id|ahd_pci_read_config
c_func
(paren
id|ahd-&gt;dev_softc
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
op_star
id|bus_addr
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
l_string|&quot;aic79xx&quot;
)paren
op_eq
l_int|0
)paren
id|error
op_assign
id|ENOMEM
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
(brace
op_star
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
op_star
id|maddr
op_eq
l_int|NULL
)paren
(brace
id|error
op_assign
id|ENOMEM
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
id|release_mem_region
c_func
(paren
id|start
comma
l_int|0x1000
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
op_star
id|maddr
op_add_assign
id|base_offset
suffix:semicolon
)brace
)brace
r_else
id|error
op_assign
id|ENOMEM
suffix:semicolon
r_return
(paren
id|error
)paren
suffix:semicolon
)brace
macro_line|#endif
r_int
DECL|function|ahd_pci_map_registers
id|ahd_pci_map_registers
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
(brace
r_uint32
id|command
suffix:semicolon
id|u_long
id|base
suffix:semicolon
r_uint8
op_star
id|maddr
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/*&n;&t; * If its allowed, we prefer memory mapped access.&n;&t; */
id|command
op_assign
id|ahd_pci_read_config
c_func
(paren
id|ahd-&gt;dev_softc
comma
id|PCIR_COMMAND
comma
l_int|4
)paren
suffix:semicolon
id|command
op_and_assign
op_complement
(paren
id|PCIM_CMD_PORTEN
op_or
id|PCIM_CMD_MEMEN
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
id|error
op_assign
id|ahd_linux_pci_reserve_mem_region
c_func
(paren
id|ahd
comma
op_amp
id|base
comma
op_amp
id|maddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
(brace
id|ahd-&gt;platform_data-&gt;mem_busaddr
op_assign
id|base
suffix:semicolon
id|ahd-&gt;tags
(braket
l_int|0
)braket
op_assign
id|BUS_SPACE_MEMIO
suffix:semicolon
id|ahd-&gt;bshs
(braket
l_int|0
)braket
dot
id|maddr
op_assign
id|maddr
suffix:semicolon
id|ahd-&gt;tags
(braket
l_int|1
)braket
op_assign
id|BUS_SPACE_MEMIO
suffix:semicolon
id|ahd-&gt;bshs
(braket
l_int|1
)braket
dot
id|maddr
op_assign
id|maddr
op_plus
l_int|0x100
suffix:semicolon
id|ahd_pci_write_config
c_func
(paren
id|ahd-&gt;dev_softc
comma
id|PCIR_COMMAND
comma
id|command
op_or
id|PCIM_CMD_MEMEN
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ahd_pci_test_register_access
c_func
(paren
id|ahd
)paren
op_ne
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;aic79xx: PCI Device %d:%d:%d &quot;
l_string|&quot;failed memory mapped test.  Using PIO.&bslash;n&quot;
comma
id|ahd_get_pci_bus
c_func
(paren
id|ahd-&gt;dev_softc
)paren
comma
id|ahd_get_pci_slot
c_func
(paren
id|ahd-&gt;dev_softc
)paren
comma
id|ahd_get_pci_function
c_func
(paren
id|ahd-&gt;dev_softc
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
(paren
(paren
id|u_long
)paren
id|maddr
op_amp
id|PAGE_MASK
)paren
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
id|release_mem_region
c_func
(paren
id|ahd-&gt;platform_data-&gt;mem_busaddr
comma
l_int|0x1000
)paren
suffix:semicolon
macro_line|#endif
id|ahd-&gt;bshs
(braket
l_int|0
)braket
dot
id|maddr
op_assign
l_int|NULL
suffix:semicolon
id|maddr
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
id|command
op_or_assign
id|PCIM_CMD_MEMEN
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|bootverbose
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;aic79xx: PCI%d:%d:%d MEM region 0x%lx &quot;
l_string|&quot;unavailable. Cannot memory map device.&bslash;n&quot;
comma
id|ahd_get_pci_bus
c_func
(paren
id|ahd-&gt;dev_softc
)paren
comma
id|ahd_get_pci_slot
c_func
(paren
id|ahd-&gt;dev_softc
)paren
comma
id|ahd_get_pci_function
c_func
(paren
id|ahd-&gt;dev_softc
)paren
comma
id|base
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|maddr
op_eq
l_int|NULL
)paren
(brace
id|u_long
id|base2
suffix:semicolon
id|error
op_assign
id|ahd_linux_pci_reserve_io_regions
c_func
(paren
id|ahd
comma
op_amp
id|base
comma
op_amp
id|base2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
(brace
id|ahd-&gt;tags
(braket
l_int|0
)braket
op_assign
id|BUS_SPACE_PIO
suffix:semicolon
id|ahd-&gt;tags
(braket
l_int|1
)braket
op_assign
id|BUS_SPACE_PIO
suffix:semicolon
id|ahd-&gt;bshs
(braket
l_int|0
)braket
dot
id|ioport
op_assign
id|base
suffix:semicolon
id|ahd-&gt;bshs
(braket
l_int|1
)braket
dot
id|ioport
op_assign
id|base2
suffix:semicolon
id|command
op_or_assign
id|PCIM_CMD_PORTEN
suffix:semicolon
)brace
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;aic79xx: PCI%d:%d:%d IO regions 0x%lx and 0x%lx&quot;
l_string|&quot;unavailable. Cannot map device.&bslash;n&quot;
comma
id|ahd_get_pci_bus
c_func
(paren
id|ahd-&gt;dev_softc
)paren
comma
id|ahd_get_pci_slot
c_func
(paren
id|ahd-&gt;dev_softc
)paren
comma
id|ahd_get_pci_function
c_func
(paren
id|ahd-&gt;dev_softc
)paren
comma
id|base
comma
id|base2
)paren
suffix:semicolon
)brace
)brace
id|ahd_pci_write_config
c_func
(paren
id|ahd-&gt;dev_softc
comma
id|PCIR_COMMAND
comma
id|command
comma
l_int|4
)paren
suffix:semicolon
r_return
(paren
id|error
)paren
suffix:semicolon
)brace
r_int
DECL|function|ahd_pci_map_int
id|ahd_pci_map_int
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|request_irq
c_func
(paren
id|ahd-&gt;dev_softc-&gt;irq
comma
id|ahd_linux_isr
comma
id|SA_SHIRQ
comma
l_string|&quot;aic79xx&quot;
comma
id|ahd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
id|ahd-&gt;platform_data-&gt;irq
op_assign
id|ahd-&gt;dev_softc-&gt;irq
suffix:semicolon
r_return
(paren
op_minus
id|error
)paren
suffix:semicolon
)brace
r_void
DECL|function|ahd_power_state_change
id|ahd_power_state_change
c_func
(paren
r_struct
id|ahd_softc
op_star
id|ahd
comma
id|ahd_power_state
id|new_state
)paren
(brace
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
id|pci_set_power_state
c_func
(paren
id|ahd-&gt;dev_softc
comma
id|new_state
)paren
suffix:semicolon
macro_line|#else
r_uint32
id|cap
suffix:semicolon
id|u_int
id|cap_offset
suffix:semicolon
multiline_comment|/*&n;&t; * Traverse the capability list looking for&n;&t; * the power management capability.&n;&t; */
id|cap
op_assign
l_int|0
suffix:semicolon
id|cap_offset
op_assign
id|ahd_pci_read_config
c_func
(paren
id|ahd-&gt;dev_softc
comma
id|PCIR_CAP_PTR
comma
multiline_comment|/*bytes*/
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|cap_offset
op_ne
l_int|0
)paren
(brace
id|cap
op_assign
id|ahd_pci_read_config
c_func
(paren
id|ahd-&gt;dev_softc
comma
id|cap_offset
comma
multiline_comment|/*bytes*/
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cap
op_amp
l_int|0xFF
)paren
op_eq
l_int|1
op_logical_and
(paren
(paren
id|cap
op_rshift
l_int|16
)paren
op_amp
l_int|0x3
)paren
OG
l_int|0
)paren
(brace
r_uint32
id|pm_control
suffix:semicolon
id|pm_control
op_assign
id|ahd_pci_read_config
c_func
(paren
id|ahd-&gt;dev_softc
comma
id|cap_offset
op_plus
l_int|4
comma
multiline_comment|/*bytes*/
l_int|4
)paren
suffix:semicolon
id|pm_control
op_and_assign
op_complement
l_int|0x3
suffix:semicolon
id|pm_control
op_or_assign
id|new_state
suffix:semicolon
id|ahd_pci_write_config
c_func
(paren
id|ahd-&gt;dev_softc
comma
id|cap_offset
op_plus
l_int|4
comma
id|pm_control
comma
multiline_comment|/*bytes*/
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cap_offset
op_assign
(paren
id|cap
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
)brace
macro_line|#endif 
)brace
eof

multiline_comment|/*&n; * Linux driver attachment glue for aic7770 based controllers.&n; *&n; * Copyright (c) 2000-2003 Adaptec Inc.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; *&n; * $Id: //depot/aic7xxx/linux/drivers/scsi/aic7xxx/aic7770_osm.c#14 $&n; */
macro_line|#include &quot;aic7xxx_osm.h&quot;
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,0)
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/eisa.h&gt;
DECL|macro|EISA_MFCTR_CHAR0
mdefine_line|#define EISA_MFCTR_CHAR0(ID) (char)(((ID&gt;&gt;26) &amp; 0x1F) | &squot;@&squot;)  /* Bits 26-30 */
DECL|macro|EISA_MFCTR_CHAR1
mdefine_line|#define EISA_MFCTR_CHAR1(ID) (char)(((ID&gt;&gt;21) &amp; 0x1F) | &squot;@&squot;)  /* Bits 21-25 */
DECL|macro|EISA_MFCTR_CHAR2
mdefine_line|#define EISA_MFCTR_CHAR2(ID) (char)(((ID&gt;&gt;16) &amp; 0x1F) | &squot;@&squot;)  /* Bits 16-20 */
DECL|macro|EISA_PRODUCT_ID
mdefine_line|#define EISA_PRODUCT_ID(ID)  (short)((ID&gt;&gt;4)  &amp; 0xFFF)        /* Bits  4-15 */
DECL|macro|EISA_REVISION_ID
mdefine_line|#define EISA_REVISION_ID(ID) (uint8_t)(ID &amp; 0x0F)             /* Bits  0-3  */
r_static
r_int
id|aic7770_eisa_dev_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|aic7770_eisa_dev_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|variable|aic7770_driver
r_static
r_struct
id|eisa_driver
id|aic7770_driver
op_assign
(brace
dot
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;aic7xxx&quot;
comma
dot
id|probe
op_assign
id|aic7770_eisa_dev_probe
comma
dot
id|remove
op_assign
id|aic7770_eisa_dev_remove
comma
)brace
)brace
suffix:semicolon
DECL|typedef|aic7770_dev_t
r_typedef
r_struct
id|device
op_star
id|aic7770_dev_t
suffix:semicolon
macro_line|#else
DECL|macro|MINSLOT
mdefine_line|#define MINSLOT&t;&t;&t;1
DECL|macro|NUMSLOTS
mdefine_line|#define NUMSLOTS&t;&t;16
DECL|macro|IDOFFSET
mdefine_line|#define IDOFFSET&t;&t;0x80
DECL|typedef|aic7770_dev_t
r_typedef
r_void
op_star
id|aic7770_dev_t
suffix:semicolon
macro_line|#endif
r_static
r_int
id|aic7770_linux_config
c_func
(paren
r_struct
id|aic7770_identity
op_star
id|entry
comma
id|aic7770_dev_t
id|dev
comma
id|u_int
id|eisaBase
)paren
suffix:semicolon
r_void
DECL|function|ahc_linux_eisa_init
id|ahc_linux_eisa_init
c_func
(paren
r_void
)paren
(brace
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,0)
r_struct
id|eisa_device_id
op_star
id|eid
suffix:semicolon
r_struct
id|aic7770_identity
op_star
id|id
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|aic7xxx_probe_eisa_vl
op_eq
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Linux requires the EISA IDs to be specified in&n;&t; * the EISA ID string format.  Perform the conversion&n;&t; * and setup a table with a NUL terminal entry.&n;&t; */
id|aic7770_driver.id_table
op_assign
id|malloc
c_func
(paren
r_sizeof
(paren
r_struct
id|eisa_device_id
)paren
op_star
(paren
id|ahc_num_aic7770_devs
op_plus
l_int|1
)paren
comma
id|M_DEVBUF
comma
id|M_NOWAIT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aic7770_driver.id_table
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|eid
op_assign
(paren
r_struct
id|eisa_device_id
op_star
)paren
id|aic7770_driver.id_table
comma
id|id
op_assign
id|aic7770_ident_table
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ahc_num_aic7770_devs
suffix:semicolon
id|eid
op_increment
comma
id|id
op_increment
comma
id|i
op_increment
)paren
(brace
id|sprintf
c_func
(paren
id|eid-&gt;sig
comma
l_string|&quot;%c%c%c%03X%01X&quot;
comma
id|EISA_MFCTR_CHAR0
c_func
(paren
id|id-&gt;full_id
)paren
comma
id|EISA_MFCTR_CHAR1
c_func
(paren
id|id-&gt;full_id
)paren
comma
id|EISA_MFCTR_CHAR2
c_func
(paren
id|id-&gt;full_id
)paren
comma
id|EISA_PRODUCT_ID
c_func
(paren
id|id-&gt;full_id
)paren
comma
id|EISA_REVISION_ID
c_func
(paren
id|id-&gt;full_id
)paren
)paren
suffix:semicolon
id|eid-&gt;driver_data
op_assign
id|i
suffix:semicolon
)brace
id|eid-&gt;sig
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|eisa_driver_register
c_func
(paren
op_amp
id|aic7770_driver
)paren
suffix:semicolon
macro_line|#else /* LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0) */
r_struct
id|aic7770_identity
op_star
id|entry
suffix:semicolon
id|u_int
id|slot
suffix:semicolon
id|u_int
id|eisaBase
suffix:semicolon
id|u_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|aic7xxx_probe_eisa_vl
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|eisaBase
op_assign
l_int|0x1000
op_plus
id|AHC_EISA_SLOT_OFFSET
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
l_int|1
suffix:semicolon
id|slot
OL
id|NUMSLOTS
suffix:semicolon
id|eisaBase
op_add_assign
l_int|0x1000
comma
id|slot
op_increment
)paren
(brace
r_uint32
id|eisa_id
suffix:semicolon
r_int
id|id_size
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,4,0)
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|eisaBase
comma
id|AHC_EISA_IOSIZE
)paren
op_ne
l_int|0
)paren
r_continue
suffix:semicolon
id|request_region
c_func
(paren
id|eisaBase
comma
id|AHC_EISA_IOSIZE
comma
l_string|&quot;aic7xxx&quot;
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|request_region
c_func
(paren
id|eisaBase
comma
id|AHC_EISA_IOSIZE
comma
l_string|&quot;aic7xxx&quot;
)paren
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
macro_line|#endif
id|eisa_id
op_assign
l_int|0
suffix:semicolon
id|id_size
op_assign
r_sizeof
(paren
id|eisa_id
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* VLcards require priming*/
id|outb
c_func
(paren
l_int|0x80
op_plus
id|i
comma
id|eisaBase
op_plus
id|IDOFFSET
)paren
suffix:semicolon
id|eisa_id
op_or_assign
id|inb
c_func
(paren
id|eisaBase
op_plus
id|IDOFFSET
op_plus
id|i
)paren
op_lshift
(paren
(paren
id|id_size
op_minus
id|i
op_minus
l_int|1
)paren
op_star
l_int|8
)paren
suffix:semicolon
)brace
id|release_region
c_func
(paren
id|eisaBase
comma
id|AHC_EISA_IOSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eisa_id
op_amp
l_int|0x80000000
)paren
r_continue
suffix:semicolon
multiline_comment|/* no EISA card in slot */
id|entry
op_assign
id|aic7770_find_device
c_func
(paren
id|eisa_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
op_ne
l_int|NULL
)paren
id|aic7770_linux_config
c_func
(paren
id|entry
comma
l_int|NULL
comma
id|eisaBase
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_void
DECL|function|ahc_linux_eisa_exit
id|ahc_linux_eisa_exit
c_func
(paren
r_void
)paren
(brace
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,0)
r_if
c_cond
(paren
id|aic7xxx_probe_eisa_vl
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|aic7770_driver.id_table
op_ne
l_int|NULL
)paren
(brace
id|eisa_driver_unregister
c_func
(paren
op_amp
id|aic7770_driver
)paren
suffix:semicolon
id|free
c_func
(paren
id|aic7770_driver.id_table
comma
id|M_DEVBUF
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_static
r_int
DECL|function|aic7770_linux_config
id|aic7770_linux_config
c_func
(paren
r_struct
id|aic7770_identity
op_star
id|entry
comma
id|aic7770_dev_t
id|dev
comma
id|u_int
id|eisaBase
)paren
(brace
r_struct
id|ahc_softc
op_star
id|ahc
suffix:semicolon
r_char
id|buf
(braket
l_int|80
)braket
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate a softc for this card and&n;&t; * set it up for attachment by our&n;&t; * common detect routine.&n;&t; */
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;ahc_eisa:%d&quot;
comma
id|eisaBase
op_rshift
l_int|12
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
op_amp
id|aic7xxx_driver_template
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
(brace
id|free
c_func
(paren
id|name
comma
id|M_DEVBUF
)paren
suffix:semicolon
r_return
(paren
id|ENOMEM
)paren
suffix:semicolon
)brace
id|error
op_assign
id|aic7770_config
c_func
(paren
id|ahc
comma
id|entry
comma
id|eisaBase
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
id|ahc-&gt;bsh.ioport
op_assign
l_int|0
suffix:semicolon
id|ahc_free
c_func
(paren
id|ahc
)paren
suffix:semicolon
r_return
(paren
id|error
)paren
suffix:semicolon
)brace
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,0)
id|dev-&gt;driver_data
op_assign
(paren
r_void
op_star
)paren
id|ahc
suffix:semicolon
r_if
c_cond
(paren
id|aic7xxx_detect_complete
)paren
id|error
op_assign
id|ahc_linux_register_host
c_func
(paren
id|ahc
comma
op_amp
id|aic7xxx_driver_template
)paren
suffix:semicolon
macro_line|#endif
r_return
(paren
id|error
)paren
suffix:semicolon
)brace
r_int
DECL|function|aic7770_map_registers
id|aic7770_map_registers
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|port
)paren
(brace
multiline_comment|/*&n;&t; * Lock out other contenders for our i/o space.&n;&t; */
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,4,0)
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|port
comma
id|AHC_EISA_IOSIZE
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
id|port
comma
id|AHC_EISA_IOSIZE
comma
l_string|&quot;aic7xxx&quot;
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|request_region
c_func
(paren
id|port
comma
id|AHC_EISA_IOSIZE
comma
l_string|&quot;aic7xxx&quot;
)paren
op_eq
l_int|0
)paren
r_return
(paren
id|ENOMEM
)paren
suffix:semicolon
macro_line|#endif
id|ahc-&gt;tag
op_assign
id|BUS_SPACE_PIO
suffix:semicolon
id|ahc-&gt;bsh.ioport
op_assign
id|port
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_int
DECL|function|aic7770_map_int
id|aic7770_map_int
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|irq
)paren
(brace
r_int
id|error
suffix:semicolon
r_int
id|shared
suffix:semicolon
id|shared
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ahc-&gt;flags
op_amp
id|AHC_EDGE_INTERRUPT
)paren
op_eq
l_int|0
)paren
id|shared
op_assign
id|SA_SHIRQ
suffix:semicolon
id|error
op_assign
id|request_irq
c_func
(paren
id|irq
comma
id|ahc_linux_isr
comma
id|shared
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
op_eq
l_int|0
)paren
id|ahc-&gt;platform_data-&gt;irq
op_assign
id|irq
suffix:semicolon
r_return
(paren
op_minus
id|error
)paren
suffix:semicolon
)brace
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,0)
r_static
r_int
DECL|function|aic7770_eisa_dev_probe
id|aic7770_eisa_dev_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|eisa_device
op_star
id|edev
suffix:semicolon
id|edev
op_assign
id|to_eisa_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
(paren
id|aic7770_linux_config
c_func
(paren
id|aic7770_ident_table
op_plus
id|edev-&gt;id.driver_data
comma
id|dev
comma
id|edev-&gt;base_addr
op_plus
id|AHC_EISA_SLOT_OFFSET
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|aic7770_eisa_dev_remove
id|aic7770_eisa_dev_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|ahc_softc
op_star
id|ahc
suffix:semicolon
id|u_long
id|l
suffix:semicolon
multiline_comment|/*&n;&t; * We should be able to just perform&n;&t; * the free directly, but check our&n;&t; * list for extra sanity.&n;&t; */
id|ahc_list_lock
c_func
(paren
op_amp
id|l
)paren
suffix:semicolon
id|ahc
op_assign
id|ahc_find_softc
c_func
(paren
(paren
r_struct
id|ahc_softc
op_star
)paren
id|dev-&gt;driver_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ahc
op_ne
l_int|NULL
)paren
(brace
id|u_long
id|s
suffix:semicolon
id|ahc_lock
c_func
(paren
id|ahc
comma
op_amp
id|s
)paren
suffix:semicolon
id|ahc_intr_enable
c_func
(paren
id|ahc
comma
id|FALSE
)paren
suffix:semicolon
id|ahc_unlock
c_func
(paren
id|ahc
comma
op_amp
id|s
)paren
suffix:semicolon
id|ahc_free
c_func
(paren
id|ahc
)paren
suffix:semicolon
)brace
id|ahc_list_unlock
c_func
(paren
op_amp
id|l
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
eof

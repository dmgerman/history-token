multiline_comment|/* &n;    ALSA memory allocation module for the RME Digi9652&n;  &n; &t;Copyright(c) 1999 IEM - Winfried Ritsch&n;        Copyright (C) 1999 Paul Barton-Davis &n;&n;    This module is only needed if you compiled the hammerfall driver with&n;    the PREALLOCATE_MEMORY option. It allocates the memory need to&n;    run the board and holds it until the module is unloaded. Because&n;    we need 2 contiguous 1.6MB regions for the board, it can be&n;    a problem getting them once the system memory has become fairly&n;    fragmented. &n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n;&n;    $Id: hammerfall_mem.c,v 1.8 2003/02/25 13:35:44 perex Exp $&n;&n;&n;    Tue Oct 17 2000  Jaroslav Kysela &lt;perex@suse.cz&gt;&n;    &t;* space is allocated only for physical devices&n;        * added support for 2.4 kernels (pci_alloc_consistent)&n;    &n;*/
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
DECL|macro|HAMMERFALL_CARDS
mdefine_line|#define HAMMERFALL_CARDS&t;&t;&t;8
DECL|macro|HAMMERFALL_CHANNEL_BUFFER_SAMPLES
mdefine_line|#define HAMMERFALL_CHANNEL_BUFFER_SAMPLES  (16*1024)
DECL|macro|HAMMERFALL_CHANNEL_BUFFER_BYTES
mdefine_line|#define HAMMERFALL_CHANNEL_BUFFER_BYTES    (4*HAMMERFALL_CHANNEL_BUFFER_SAMPLES)
multiline_comment|/* export */
DECL|variable|enable
r_static
r_int
id|enable
(braket
l_int|8
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|enable
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|HAMMERFALL_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|enable
comma
l_string|&quot;Enable cards to allocate buffers for.&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Winfried Ritsch, Paul Barton-Davis &lt;pbd@op.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Memory allocator for RME Hammerfall&quot;
)paren
suffix:semicolon
id|MODULE_CLASSES
c_func
(paren
l_string|&quot;{sound}&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* Since we don&squot;t know at this point if we&squot;re allocating memory for a&n;   Hammerfall or a Hammerfall/Light, assume the worst and allocate&n;   space for the maximum number of channels.&n;&n;   The extra channel is allocated because we need a 64kB-aligned&n;   buffer in the actual interface driver code (see rme9652.c or hdsp.c&n;   for details)&n;*/
DECL|macro|TOTAL_SIZE
mdefine_line|#define TOTAL_SIZE (26+1)*(HAMMERFALL_CHANNEL_BUFFER_BYTES)
DECL|macro|NBUFS
mdefine_line|#define NBUFS   2*HAMMERFALL_CARDS
DECL|macro|HAMMERFALL_BUF_ALLOCATED
mdefine_line|#define HAMMERFALL_BUF_ALLOCATED 0x1
DECL|macro|HAMMERFALL_BUF_USED
mdefine_line|#define HAMMERFALL_BUF_USED      0x2
DECL|typedef|hammerfall_buf_t
r_typedef
r_struct
id|hammerfall_buf_stru
id|hammerfall_buf_t
suffix:semicolon
DECL|struct|hammerfall_buf_stru
r_struct
id|hammerfall_buf_stru
(brace
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
DECL|member|buf
r_void
op_star
id|buf
suffix:semicolon
DECL|member|addr
id|dma_addr_t
id|addr
suffix:semicolon
DECL|member|flags
r_char
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|hammerfall_buffers
r_static
id|hammerfall_buf_t
id|hammerfall_buffers
(braket
id|NBUFS
)braket
suffix:semicolon
multiline_comment|/* These are here so that we have absolutely no dependencies&n;   on any other modules. Dependencies can (1) cause us to&n;   lose in the rush for 2x1.6MB chunks of contiguous memory&n;   and (2) make driver debugging difficult because unloading&n;   and reloading the snd module causes us to have to do the&n;   same for this one. Since we can rarely if ever allocate&n;   memory after starting things running, that would be very&n;   undesirable.  &n;*/
DECL|function|hammerfall_malloc_pages
r_static
r_void
op_star
id|hammerfall_malloc_pages
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
r_int
id|size
comma
id|dma_addr_t
op_star
id|dmaaddr
)paren
(brace
r_void
op_star
id|res
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2, 3, 0)
id|res
op_assign
(paren
r_void
op_star
)paren
id|pci_alloc_consistent
c_func
(paren
id|pci
comma
id|size
comma
id|dmaaddr
)paren
suffix:semicolon
macro_line|#else
r_int
id|pg
suffix:semicolon
r_for
c_loop
(paren
id|pg
op_assign
l_int|0
suffix:semicolon
id|PAGE_SIZE
op_star
(paren
l_int|1
op_lshift
id|pg
)paren
OL
id|size
suffix:semicolon
id|pg
op_increment
)paren
suffix:semicolon
id|res
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|pg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_ne
l_int|NULL
)paren
op_star
id|dmaaddr
op_assign
id|virt_to_bus
c_func
(paren
id|res
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|res
op_ne
l_int|NULL
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|res
)paren
suffix:semicolon
r_struct
id|page
op_star
id|last_page
op_assign
id|page
op_plus
(paren
id|size
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|page
OL
id|last_page
)paren
id|set_bit
c_func
(paren
id|PG_reserved
comma
op_amp
(paren
id|page
op_increment
)paren
op_member_access_from_pointer
id|flags
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|hammerfall_free_pages
r_static
r_void
id|hammerfall_free_pages
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
r_int
id|size
comma
r_void
op_star
id|ptr
comma
id|dma_addr_t
id|dmaaddr
)paren
(brace
r_struct
id|page
op_star
id|page
comma
op_star
id|last_page
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|page
op_assign
id|virt_to_page
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|last_page
op_assign
id|virt_to_page
c_func
(paren
id|ptr
)paren
op_plus
(paren
id|size
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|page
OL
id|last_page
)paren
id|clear_bit
c_func
(paren
id|PG_reserved
comma
op_amp
(paren
id|page
op_increment
)paren
op_member_access_from_pointer
id|flags
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2, 3, 0)
id|pci_free_consistent
c_func
(paren
id|pci
comma
id|size
comma
id|ptr
comma
id|dmaaddr
)paren
suffix:semicolon
macro_line|#else
(brace
r_int
id|pg
suffix:semicolon
r_for
c_loop
(paren
id|pg
op_assign
l_int|0
suffix:semicolon
id|PAGE_SIZE
op_star
(paren
l_int|1
op_lshift
id|pg
)paren
OL
id|size
suffix:semicolon
id|pg
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus_to_virt
c_func
(paren
id|dmaaddr
)paren
op_ne
id|ptr
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hammerfall_free_pages: dmaaddr != ptr&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|ptr
comma
id|pg
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|snd_hammerfall_get_buffer
r_void
op_star
id|snd_hammerfall_get_buffer
(paren
r_struct
id|pci_dev
op_star
id|pcidev
comma
id|dma_addr_t
op_star
id|dmaaddr
)paren
(brace
r_int
id|i
suffix:semicolon
id|hammerfall_buf_t
op_star
id|rbuf
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
id|NBUFS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rbuf
op_assign
op_amp
id|hammerfall_buffers
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|rbuf-&gt;flags
op_eq
id|HAMMERFALL_BUF_ALLOCATED
)paren
(brace
id|rbuf-&gt;flags
op_or_assign
id|HAMMERFALL_BUF_USED
suffix:semicolon
id|rbuf-&gt;pci
op_assign
id|pcidev
suffix:semicolon
op_star
id|dmaaddr
op_assign
id|rbuf-&gt;addr
suffix:semicolon
r_return
id|rbuf-&gt;buf
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|snd_hammerfall_free_buffer
r_void
id|snd_hammerfall_free_buffer
(paren
r_struct
id|pci_dev
op_star
id|pcidev
comma
r_void
op_star
id|addr
)paren
(brace
r_int
id|i
suffix:semicolon
id|hammerfall_buf_t
op_star
id|rbuf
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
id|NBUFS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rbuf
op_assign
op_amp
id|hammerfall_buffers
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|rbuf-&gt;buf
op_eq
id|addr
op_logical_and
id|rbuf-&gt;pci
op_eq
id|pcidev
)paren
(brace
id|rbuf-&gt;flags
op_and_assign
op_complement
id|HAMMERFALL_BUF_USED
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|printk
(paren
l_string|&quot;Hammerfall memory allocator: unknown buffer address or PCI device ID&quot;
)paren
suffix:semicolon
)brace
DECL|function|hammerfall_free_buffers
r_static
r_void
id|hammerfall_free_buffers
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|hammerfall_buf_t
op_star
id|rbuf
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
id|NBUFS
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* We rely on general module code to prevent&n;&t;&t;   us from being unloaded with buffers in use.&n;&n;&t;&t;   However, not quite. Do not release memory&n;&t;&t;   if it is still marked as in use. This might&n;&t;&t;   be unnecessary.&n;&t;&t;*/
id|rbuf
op_assign
op_amp
id|hammerfall_buffers
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|rbuf-&gt;flags
op_eq
id|HAMMERFALL_BUF_ALLOCATED
)paren
(brace
id|hammerfall_free_pages
(paren
id|rbuf-&gt;pci
comma
id|TOTAL_SIZE
comma
id|rbuf-&gt;buf
comma
id|rbuf-&gt;addr
)paren
suffix:semicolon
id|rbuf-&gt;buf
op_assign
l_int|NULL
suffix:semicolon
id|rbuf-&gt;flags
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
DECL|function|alsa_hammerfall_mem_init
r_static
r_int
id|__init
id|alsa_hammerfall_mem_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pci
op_assign
l_int|NULL
suffix:semicolon
id|hammerfall_buf_t
op_star
id|rbuf
suffix:semicolon
multiline_comment|/* make sure our buffer records are clean */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NBUFS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rbuf
op_assign
op_amp
id|hammerfall_buffers
(braket
id|i
)braket
suffix:semicolon
id|rbuf-&gt;pci
op_assign
l_int|NULL
suffix:semicolon
id|rbuf-&gt;buf
op_assign
l_int|NULL
suffix:semicolon
id|rbuf-&gt;flags
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ensure sane values for the number of buffers */
multiline_comment|/* Remember: 2 buffers per card, one for capture, one for&n;&t;   playback.&n;&t;*/
id|i
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* card number */
id|rbuf
op_assign
id|hammerfall_buffers
suffix:semicolon
r_while
c_loop
(paren
(paren
id|pci
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_XILINX
comma
id|PCI_ANY_ID
comma
id|pci
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|k
suffix:semicolon
multiline_comment|/* check for Hammerfall and Hammerfall DSP cards */
r_if
c_cond
(paren
id|pci-&gt;device
op_ne
l_int|0x3fc4
op_logical_and
id|pci-&gt;device
op_ne
l_int|0x3fc5
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|enable
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|2
suffix:semicolon
op_increment
id|k
)paren
(brace
id|rbuf-&gt;buf
op_assign
id|hammerfall_malloc_pages
c_func
(paren
id|pci
comma
id|TOTAL_SIZE
comma
op_amp
id|rbuf-&gt;addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rbuf-&gt;buf
op_eq
l_int|NULL
)paren
(brace
id|hammerfall_free_buffers
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Hammerfall memory allocator: no memory available for card %d buffer %d&bslash;n&quot;
comma
id|i
comma
id|k
op_plus
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|rbuf-&gt;flags
op_assign
id|HAMMERFALL_BUF_ALLOCATED
suffix:semicolon
id|rbuf
op_increment
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Hammerfall memory allocator: &quot;
l_string|&quot;no Hammerfall cards found...&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Hammerfall memory allocator: &quot;
l_string|&quot;buffers allocated for %d cards&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_hammerfall_mem_exit
r_static
r_void
id|__exit
id|alsa_hammerfall_mem_exit
c_func
(paren
r_void
)paren
(brace
id|hammerfall_free_buffers
c_func
(paren
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_hammerfall_mem_init
)paren
id|module_exit
c_func
(paren
id|alsa_hammerfall_mem_exit
)paren
id|EXPORT_SYMBOL
c_func
(paren
id|snd_hammerfall_get_buffer
)paren
suffix:semicolon
DECL|variable|EXPORT_SYMBOL
id|EXPORT_SYMBOL
c_func
(paren
id|snd_hammerfall_free_buffer
)paren
suffix:semicolon
eof

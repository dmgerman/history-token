multiline_comment|/*&n; *&t;Adaptec AAC series RAID controller driver&n; *&t;(c) Copyright 2001 Red Hat Inc.&t;&lt;alan@redhat.com&gt;&n; *&n; * based on the old aacraid driver that is..&n; * Adaptec aacraid device driver for Linux.&n; *&n; * Copyright (c) 2000 Adaptec, Inc. (aacraid@adaptec.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Module Name:&n; *  comminit.c&n; *&n; * Abstract: This supports the initialization of the host adapter commuication interface.&n; *    This is a platform dependent module for the pci cyclone board.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;aacraid.h&quot;
DECL|variable|aac_config
r_struct
id|aac_common
id|aac_config
suffix:semicolon
DECL|variable|devices
r_static
r_struct
id|aac_dev
op_star
id|devices
suffix:semicolon
DECL|function|aac_alloc_comm
r_static
r_int
id|aac_alloc_comm
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
comma
r_void
op_star
op_star
id|commaddr
comma
r_int
r_int
id|commsize
comma
r_int
r_int
id|commalign
)paren
(brace
r_int
r_char
op_star
id|base
suffix:semicolon
r_int
r_int
id|size
comma
id|align
suffix:semicolon
r_int
r_int
id|fibsize
op_assign
l_int|4096
suffix:semicolon
r_int
r_int
id|printfbufsiz
op_assign
l_int|256
suffix:semicolon
r_struct
id|aac_init
op_star
id|init
suffix:semicolon
id|dma_addr_t
id|phys
suffix:semicolon
id|size
op_assign
id|fibsize
op_plus
r_sizeof
(paren
r_struct
id|aac_init
)paren
op_plus
id|commsize
op_plus
id|commalign
op_plus
id|printfbufsiz
suffix:semicolon
id|base
op_assign
id|pci_alloc_consistent
c_func
(paren
id|dev-&gt;pdev
comma
id|size
comma
op_amp
id|phys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;aacraid: unable to create mapping.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|dev-&gt;comm_addr
op_assign
(paren
r_void
op_star
)paren
id|base
suffix:semicolon
id|dev-&gt;comm_phys
op_assign
id|phys
suffix:semicolon
id|dev-&gt;comm_size
op_assign
id|size
suffix:semicolon
id|dev-&gt;init
op_assign
(paren
r_struct
id|aac_init
op_star
)paren
(paren
id|base
op_plus
id|fibsize
)paren
suffix:semicolon
id|dev-&gt;init_pa
op_assign
id|phys
op_plus
id|fibsize
suffix:semicolon
id|init
op_assign
id|dev-&gt;init
suffix:semicolon
id|init-&gt;InitStructRevision
op_assign
id|cpu_to_le32
c_func
(paren
id|ADAPTER_INIT_STRUCT_REVISION
)paren
suffix:semicolon
id|init-&gt;MiniPortRevision
op_assign
id|cpu_to_le32
c_func
(paren
id|Sa_MINIPORT_REVISION
)paren
suffix:semicolon
id|init-&gt;fsrev
op_assign
id|cpu_to_le32
c_func
(paren
id|dev-&gt;fsrev
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Adapter Fibs are the first thing allocated so that they&n;&t; *&t;start page aligned&n;&t; */
id|dev-&gt;fib_base_va
op_assign
(paren
id|ulong
)paren
id|base
suffix:semicolon
id|init-&gt;AdapterFibsVirtualAddress
op_assign
id|cpu_to_le32
c_func
(paren
(paren
id|u32
)paren
(paren
id|ulong
)paren
id|phys
)paren
suffix:semicolon
id|init-&gt;AdapterFibsPhysicalAddress
op_assign
id|cpu_to_le32
c_func
(paren
(paren
id|u32
)paren
id|phys
)paren
suffix:semicolon
id|init-&gt;AdapterFibsSize
op_assign
id|cpu_to_le32
c_func
(paren
id|fibsize
)paren
suffix:semicolon
id|init-&gt;AdapterFibAlign
op_assign
id|cpu_to_le32
c_func
(paren
r_sizeof
(paren
r_struct
id|hw_fib
)paren
)paren
suffix:semicolon
id|init-&gt;HostPhysMemPages
op_assign
id|cpu_to_le32
c_func
(paren
id|num_physpages
)paren
suffix:semicolon
singleline_comment|// number of 4k pages of host physical memory
multiline_comment|/*&n;&t; * Increment the base address by the amount already used&n;&t; */
id|base
op_assign
id|base
op_plus
id|fibsize
op_plus
r_sizeof
(paren
r_struct
id|aac_init
)paren
suffix:semicolon
id|phys
op_assign
(paren
id|dma_addr_t
)paren
(paren
(paren
id|ulong
)paren
id|phys
op_plus
id|fibsize
op_plus
r_sizeof
(paren
r_struct
id|aac_init
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Align the beginning of Headers to commalign&n;&t; */
id|align
op_assign
(paren
id|commalign
op_minus
(paren
(paren
r_int
r_int
)paren
(paren
id|base
)paren
op_amp
(paren
id|commalign
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
id|base
op_assign
id|base
op_plus
id|align
suffix:semicolon
id|phys
op_assign
id|phys
op_plus
id|align
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Fill in addresses of the Comm Area Headers and Queues&n;&t; */
op_star
id|commaddr
op_assign
id|base
suffix:semicolon
id|init-&gt;CommHeaderAddress
op_assign
id|cpu_to_le32
c_func
(paren
(paren
id|u32
)paren
id|phys
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Increment the base address by the size of the CommArea&n;&t; */
id|base
op_assign
id|base
op_plus
id|commsize
suffix:semicolon
id|phys
op_assign
id|phys
op_plus
id|commsize
suffix:semicolon
multiline_comment|/*&n;&t; *&t; Place the Printf buffer area after the Fast I/O comm area.&n;&t; */
id|dev-&gt;printfbuf
op_assign
(paren
r_void
op_star
)paren
id|base
suffix:semicolon
id|init-&gt;printfbuf
op_assign
id|cpu_to_le32
c_func
(paren
id|phys
)paren
suffix:semicolon
id|init-&gt;printfbufsiz
op_assign
id|cpu_to_le32
c_func
(paren
id|printfbufsiz
)paren
suffix:semicolon
id|memset
c_func
(paren
id|base
comma
l_int|0
comma
id|printfbufsiz
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|aac_queue_init
r_static
r_void
id|aac_queue_init
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
comma
r_struct
id|aac_queue
op_star
id|q
comma
id|u32
op_star
id|mem
comma
r_int
id|qsize
)paren
(brace
id|q-&gt;numpending
op_assign
l_int|0
suffix:semicolon
id|q-&gt;dev
op_assign
id|dev
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|q-&gt;pendingq
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|q-&gt;cmdready
)paren
suffix:semicolon
id|AAC_INIT_LIST_HEAD
c_func
(paren
op_amp
id|q-&gt;cmdq
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|q-&gt;qfull
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|q-&gt;lockdata
)paren
suffix:semicolon
id|q-&gt;lock
op_assign
op_amp
id|q-&gt;lockdata
suffix:semicolon
id|q-&gt;headers.producer
op_assign
id|mem
suffix:semicolon
id|q-&gt;headers.consumer
op_assign
id|mem
op_plus
l_int|1
suffix:semicolon
op_star
(paren
id|q-&gt;headers.producer
)paren
op_assign
id|cpu_to_le32
c_func
(paren
id|qsize
)paren
suffix:semicolon
op_star
(paren
id|q-&gt;headers.consumer
)paren
op_assign
id|cpu_to_le32
c_func
(paren
id|qsize
)paren
suffix:semicolon
id|q-&gt;entries
op_assign
id|qsize
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aac_send_shutdown&t;&t;-&t;shutdown an adapter&n; *&t;@dev: Adapter to shutdown&n; *&n; *&t;This routine will send a VM_CloseAll (shutdown) request to the adapter.&n; */
DECL|function|aac_send_shutdown
r_static
r_int
id|aac_send_shutdown
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
(brace
r_struct
id|fib
op_star
id|fibctx
suffix:semicolon
r_struct
id|aac_close
op_star
id|cmd
suffix:semicolon
r_int
id|status
suffix:semicolon
id|fibctx
op_assign
id|fib_alloc
c_func
(paren
id|dev
)paren
suffix:semicolon
id|fib_init
c_func
(paren
id|fibctx
)paren
suffix:semicolon
id|cmd
op_assign
(paren
r_struct
id|aac_close
op_star
)paren
id|fib_data
c_func
(paren
id|fibctx
)paren
suffix:semicolon
id|cmd-&gt;command
op_assign
id|cpu_to_le32
c_func
(paren
id|VM_CloseAll
)paren
suffix:semicolon
id|cmd-&gt;cid
op_assign
id|cpu_to_le32
c_func
(paren
l_int|0xffffffff
)paren
suffix:semicolon
id|status
op_assign
id|fib_send
c_func
(paren
id|ContainerCommand
comma
id|fibctx
comma
r_sizeof
(paren
r_struct
id|aac_close
)paren
comma
id|FsaNormal
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
l_int|0
)paren
id|fib_complete
c_func
(paren
id|fibctx
)paren
suffix:semicolon
id|fib_free
c_func
(paren
id|fibctx
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aac_detach&t;-&t;detach adapter&n; *&t;@detach: adapter to disconnect&n; *&n; *&t;Disconnect and shutdown an AAC based adapter, freeing resources&n; *&t;as we go.&n; */
DECL|function|aac_detach
r_int
id|aac_detach
c_func
(paren
r_struct
id|aac_dev
op_star
id|detach
)paren
(brace
r_struct
id|aac_dev
op_star
op_star
id|dev
op_assign
op_amp
id|devices
suffix:semicolon
r_while
c_loop
(paren
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_star
id|dev
op_eq
id|detach
)paren
(brace
op_star
id|dev
op_assign
id|detach-&gt;next
suffix:semicolon
id|aac_send_shutdown
c_func
(paren
id|detach
)paren
suffix:semicolon
id|fib_map_free
c_func
(paren
id|detach
)paren
suffix:semicolon
id|pci_free_consistent
c_func
(paren
id|detach-&gt;pdev
comma
id|detach-&gt;comm_size
comma
id|detach-&gt;comm_addr
comma
id|detach-&gt;comm_phys
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|detach-&gt;queues
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|dev
op_assign
op_amp
(paren
(paren
op_star
id|dev
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
)brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aac_comm_init&t;-&t;Initialise FSA data structures&n; *&t;@dev:&t;Adapter to initialise&n; *&n; *&t;Initializes the data structures that are required for the FSA commuication&n; *&t;interface to operate. &n; *&t;Returns&n; *&t;&t;1 - if we were able to init the commuication interface.&n; *&t;&t;0 - If there were errors initing. This is a fatal error.&n; */
DECL|function|aac_comm_init
r_int
id|aac_comm_init
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|hdrsize
op_assign
(paren
r_sizeof
(paren
id|u32
)paren
op_star
id|NUMBER_OF_COMM_QUEUES
)paren
op_star
l_int|2
suffix:semicolon
r_int
r_int
id|queuesize
op_assign
r_sizeof
(paren
r_struct
id|aac_entry
)paren
op_star
id|TOTAL_QUEUE_ENTRIES
suffix:semicolon
id|u32
op_star
id|headers
suffix:semicolon
r_struct
id|aac_entry
op_star
id|queues
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_struct
id|aac_queue_block
op_star
id|comm
op_assign
id|dev-&gt;queues
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Now allocate and initialize the zone structures used as our &n;&t; *&t;pool of FIB context records.  The size of the zone is based&n;&t; *&t;on the system memory size.  We also initialize the mutex used&n;&t; *&t;to protect the zone.&n;&t; */
id|spin_lock_init
c_func
(paren
op_amp
id|dev-&gt;fib_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Allocate the physically contigous space for the commuication&n;&t; *&t;queue headers. &n;&t; */
id|size
op_assign
id|hdrsize
op_plus
id|queuesize
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|aac_alloc_comm
c_func
(paren
id|dev
comma
(paren
r_void
op_star
op_star
)paren
op_amp
id|headers
comma
id|size
comma
id|QUEUE_ALIGNMENT
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|queues
op_assign
(paren
r_struct
id|aac_entry
op_star
)paren
(paren
(paren
(paren
id|ulong
)paren
id|headers
)paren
op_plus
id|hdrsize
)paren
suffix:semicolon
multiline_comment|/* Adapter to Host normal priority Command queue */
id|comm-&gt;queue
(braket
id|HostNormCmdQueue
)braket
dot
id|base
op_assign
id|queues
suffix:semicolon
id|aac_queue_init
c_func
(paren
id|dev
comma
op_amp
id|comm-&gt;queue
(braket
id|HostNormCmdQueue
)braket
comma
id|headers
comma
id|HOST_NORM_CMD_ENTRIES
)paren
suffix:semicolon
id|queues
op_add_assign
id|HOST_NORM_CMD_ENTRIES
suffix:semicolon
id|headers
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* Adapter to Host high priority command queue */
id|comm-&gt;queue
(braket
id|HostHighCmdQueue
)braket
dot
id|base
op_assign
id|queues
suffix:semicolon
id|aac_queue_init
c_func
(paren
id|dev
comma
op_amp
id|comm-&gt;queue
(braket
id|HostHighCmdQueue
)braket
comma
id|headers
comma
id|HOST_HIGH_CMD_ENTRIES
)paren
suffix:semicolon
id|queues
op_add_assign
id|HOST_HIGH_CMD_ENTRIES
suffix:semicolon
id|headers
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* Host to adapter normal priority command queue */
id|comm-&gt;queue
(braket
id|AdapNormCmdQueue
)braket
dot
id|base
op_assign
id|queues
suffix:semicolon
id|aac_queue_init
c_func
(paren
id|dev
comma
op_amp
id|comm-&gt;queue
(braket
id|AdapNormCmdQueue
)braket
comma
id|headers
comma
id|ADAP_NORM_CMD_ENTRIES
)paren
suffix:semicolon
id|queues
op_add_assign
id|ADAP_NORM_CMD_ENTRIES
suffix:semicolon
id|headers
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* host to adapter high priority command queue */
id|comm-&gt;queue
(braket
id|AdapHighCmdQueue
)braket
dot
id|base
op_assign
id|queues
suffix:semicolon
id|aac_queue_init
c_func
(paren
id|dev
comma
op_amp
id|comm-&gt;queue
(braket
id|AdapHighCmdQueue
)braket
comma
id|headers
comma
id|ADAP_HIGH_CMD_ENTRIES
)paren
suffix:semicolon
id|queues
op_add_assign
id|ADAP_HIGH_CMD_ENTRIES
suffix:semicolon
id|headers
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* adapter to host normal priority response queue */
id|comm-&gt;queue
(braket
id|HostNormRespQueue
)braket
dot
id|base
op_assign
id|queues
suffix:semicolon
id|aac_queue_init
c_func
(paren
id|dev
comma
op_amp
id|comm-&gt;queue
(braket
id|HostNormRespQueue
)braket
comma
id|headers
comma
id|HOST_NORM_RESP_ENTRIES
)paren
suffix:semicolon
id|queues
op_add_assign
id|HOST_NORM_RESP_ENTRIES
suffix:semicolon
id|headers
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* adapter to host high priority response queue */
id|comm-&gt;queue
(braket
id|HostHighRespQueue
)braket
dot
id|base
op_assign
id|queues
suffix:semicolon
id|aac_queue_init
c_func
(paren
id|dev
comma
op_amp
id|comm-&gt;queue
(braket
id|HostHighRespQueue
)braket
comma
id|headers
comma
id|HOST_HIGH_RESP_ENTRIES
)paren
suffix:semicolon
id|queues
op_add_assign
id|HOST_HIGH_RESP_ENTRIES
suffix:semicolon
id|headers
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* host to adapter normal priority response queue */
id|comm-&gt;queue
(braket
id|AdapNormRespQueue
)braket
dot
id|base
op_assign
id|queues
suffix:semicolon
id|aac_queue_init
c_func
(paren
id|dev
comma
op_amp
id|comm-&gt;queue
(braket
id|AdapNormRespQueue
)braket
comma
id|headers
comma
id|ADAP_NORM_RESP_ENTRIES
)paren
suffix:semicolon
id|queues
op_add_assign
id|ADAP_NORM_RESP_ENTRIES
suffix:semicolon
id|headers
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* host to adapter high priority response queue */
id|comm-&gt;queue
(braket
id|AdapHighRespQueue
)braket
dot
id|base
op_assign
id|queues
suffix:semicolon
id|aac_queue_init
c_func
(paren
id|dev
comma
op_amp
id|comm-&gt;queue
(braket
id|AdapHighRespQueue
)braket
comma
id|headers
comma
id|ADAP_HIGH_RESP_ENTRIES
)paren
suffix:semicolon
id|comm-&gt;queue
(braket
id|AdapNormCmdQueue
)braket
dot
id|lock
op_assign
id|comm-&gt;queue
(braket
id|HostNormRespQueue
)braket
dot
id|lock
suffix:semicolon
id|comm-&gt;queue
(braket
id|AdapHighCmdQueue
)braket
dot
id|lock
op_assign
id|comm-&gt;queue
(braket
id|HostHighRespQueue
)braket
dot
id|lock
suffix:semicolon
id|comm-&gt;queue
(braket
id|AdapNormRespQueue
)braket
dot
id|lock
op_assign
id|comm-&gt;queue
(braket
id|HostNormCmdQueue
)braket
dot
id|lock
suffix:semicolon
id|comm-&gt;queue
(braket
id|AdapHighRespQueue
)braket
dot
id|lock
op_assign
id|comm-&gt;queue
(braket
id|HostHighCmdQueue
)braket
dot
id|lock
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|aac_init_adapter
r_struct
id|aac_dev
op_star
id|aac_init_adapter
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
(brace
multiline_comment|/*&n;&t; *&t;Ok now init the communication subsystem&n;&t; */
id|dev-&gt;queues
op_assign
(paren
r_struct
id|aac_queue_block
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|aac_queue_block
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;queues
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Error could not allocate comm region.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dev-&gt;queues
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|aac_queue_block
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aac_comm_init
c_func
(paren
id|dev
)paren
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|dev-&gt;queues
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Initialize the list of fibs&n;&t; */
r_if
c_cond
(paren
id|fib_setup
c_func
(paren
id|dev
)paren
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|dev-&gt;queues
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;fib_list
)paren
suffix:semicolon
id|init_completion
c_func
(paren
op_amp
id|dev-&gt;aif_completion
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Add this adapter in to our dev List.&n;&t; */
id|dev-&gt;next
op_assign
id|devices
suffix:semicolon
id|devices
op_assign
id|dev
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
eof

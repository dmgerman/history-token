multiline_comment|/*&n; * SCSI low-level driver for the 53c94 SCSI bus adaptor found&n; * on Power Macintosh computers, controlling the external SCSI chain.&n; * We assume the 53c94 is connected to a DBDMA (descriptor-based DMA)&n; * controller.&n; *&n; * Paul Mackerras, August 1996.&n; * Copyright (C) 1996 Paul Mackerras.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/dbdma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;mac53c94.h&quot;
DECL|enum|fsc_phase
r_enum
id|fsc_phase
(brace
DECL|enumerator|idle
id|idle
comma
DECL|enumerator|selecting
id|selecting
comma
DECL|enumerator|dataing
id|dataing
comma
DECL|enumerator|completing
id|completing
comma
DECL|enumerator|busfreeing
id|busfreeing
comma
)brace
suffix:semicolon
DECL|struct|fsc_state
r_struct
id|fsc_state
(brace
DECL|member|regs
r_volatile
r_struct
id|mac53c94_regs
op_star
id|regs
suffix:semicolon
DECL|member|intr
r_int
id|intr
suffix:semicolon
DECL|member|dma
r_volatile
r_struct
id|dbdma_regs
op_star
id|dma
suffix:semicolon
DECL|member|dmaintr
r_int
id|dmaintr
suffix:semicolon
DECL|member|clk_freq
r_int
id|clk_freq
suffix:semicolon
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|member|next
r_struct
id|fsc_state
op_star
id|next
suffix:semicolon
DECL|member|request_q
id|Scsi_Cmnd
op_star
id|request_q
suffix:semicolon
DECL|member|request_qtail
id|Scsi_Cmnd
op_star
id|request_qtail
suffix:semicolon
DECL|member|current_req
id|Scsi_Cmnd
op_star
id|current_req
suffix:semicolon
multiline_comment|/* req we&squot;re currently working on */
DECL|member|phase
r_enum
id|fsc_phase
id|phase
suffix:semicolon
multiline_comment|/* what we&squot;re currently trying to do */
DECL|member|dma_cmds
r_struct
id|dbdma_cmd
op_star
id|dma_cmds
suffix:semicolon
multiline_comment|/* space for dbdma commands, aligned */
DECL|member|dma_cmd_space
r_void
op_star
id|dma_cmd_space
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|dma_addr
id|dma_addr_t
id|dma_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|all_53c94s
r_static
r_struct
id|fsc_state
op_star
id|all_53c94s
suffix:semicolon
r_static
r_void
id|mac53c94_init
c_func
(paren
r_struct
id|fsc_state
op_star
)paren
suffix:semicolon
r_static
r_void
id|mac53c94_start
c_func
(paren
r_struct
id|fsc_state
op_star
)paren
suffix:semicolon
r_static
r_void
id|mac53c94_interrupt
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_static
id|irqreturn_t
id|do_mac53c94_interrupt
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_static
r_void
id|cmd_done
c_func
(paren
r_struct
id|fsc_state
op_star
comma
r_int
id|result
)paren
suffix:semicolon
r_static
r_void
id|set_dma_cmds
c_func
(paren
r_struct
id|fsc_state
op_star
comma
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|data_goes_out
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
DECL|function|mac53c94_detect
id|mac53c94_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tp
)paren
(brace
r_struct
id|device_node
op_star
id|node
suffix:semicolon
r_int
id|nfscs
suffix:semicolon
r_struct
id|fsc_state
op_star
id|state
comma
op_star
op_star
id|prev_statep
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
r_void
op_star
id|dma_cmd_space
suffix:semicolon
r_int
r_char
op_star
id|clkprop
suffix:semicolon
r_int
id|proplen
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
id|u8
id|pbus
comma
id|devfn
suffix:semicolon
id|nfscs
op_assign
l_int|0
suffix:semicolon
id|prev_statep
op_assign
op_amp
id|all_53c94s
suffix:semicolon
r_for
c_loop
(paren
id|node
op_assign
id|find_devices
c_func
(paren
l_string|&quot;53c94&quot;
)paren
suffix:semicolon
id|node
op_ne
l_int|0
suffix:semicolon
id|node
op_assign
id|node-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|node-&gt;n_addrs
op_ne
l_int|2
op_logical_or
id|node-&gt;n_intrs
op_ne
l_int|2
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mac53c94: expected 2 addrs and intrs&quot;
l_string|&quot; (got %d/%d) for node %s&bslash;n&quot;
comma
id|node-&gt;n_addrs
comma
id|node-&gt;n_intrs
comma
id|node-&gt;full_name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|pdev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|node-&gt;parent
op_ne
l_int|NULL
op_logical_and
op_logical_neg
id|pci_device_from_OF_node
c_func
(paren
id|node-&gt;parent
comma
op_amp
id|pbus
comma
op_amp
id|devfn
)paren
)paren
id|pdev
op_assign
id|pci_find_slot
c_func
(paren
id|pbus
comma
id|devfn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdev
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mac53c94: can&squot;t find PCI device &quot;
l_string|&quot;for %s&bslash;n&quot;
comma
id|node-&gt;full_name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|host
op_assign
id|scsi_register
c_func
(paren
id|tp
comma
r_sizeof
(paren
r_struct
id|fsc_state
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
id|host-&gt;unique_id
op_assign
id|nfscs
suffix:semicolon
id|state
op_assign
(paren
r_struct
id|fsc_state
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
l_int|0
)paren
(brace
multiline_comment|/* &quot;can&squot;t happen&quot; */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mac53c94: no state for %s?!&bslash;n&quot;
comma
id|node-&gt;full_name
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|host
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|state-&gt;host
op_assign
id|host
suffix:semicolon
id|state-&gt;pdev
op_assign
id|pdev
suffix:semicolon
id|state-&gt;regs
op_assign
(paren
r_volatile
r_struct
id|mac53c94_regs
op_star
)paren
id|ioremap
c_func
(paren
id|node-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
l_int|0x1000
)paren
suffix:semicolon
id|state-&gt;intr
op_assign
id|node-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
suffix:semicolon
id|state-&gt;dma
op_assign
(paren
r_volatile
r_struct
id|dbdma_regs
op_star
)paren
id|ioremap
c_func
(paren
id|node-&gt;addrs
(braket
l_int|1
)braket
dot
id|address
comma
l_int|0x1000
)paren
suffix:semicolon
id|state-&gt;dmaintr
op_assign
id|node-&gt;intrs
(braket
l_int|1
)braket
dot
id|line
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;regs
op_eq
l_int|NULL
op_logical_or
id|state-&gt;dma
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mac53c94: ioremap failed for %s&bslash;n&quot;
comma
id|node-&gt;full_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;dma
op_ne
l_int|NULL
)paren
id|iounmap
c_func
(paren
id|state-&gt;dma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;regs
op_ne
l_int|NULL
)paren
id|iounmap
c_func
(paren
id|state-&gt;regs
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|host
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|clkprop
op_assign
id|get_property
c_func
(paren
id|node
comma
l_string|&quot;clock-frequency&quot;
comma
op_amp
id|proplen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clkprop
op_eq
l_int|NULL
op_logical_or
id|proplen
op_ne
r_sizeof
(paren
r_int
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: can&squot;t get clock frequency, &quot;
l_string|&quot;assuming 25MHz&bslash;n&quot;
comma
id|node-&gt;full_name
)paren
suffix:semicolon
id|state-&gt;clk_freq
op_assign
l_int|25000000
suffix:semicolon
)brace
r_else
id|state-&gt;clk_freq
op_assign
op_star
(paren
r_int
op_star
)paren
id|clkprop
suffix:semicolon
multiline_comment|/* Space for dma command list: +1 for stop command,&n;&t;&t;   +1 to allow for aligning. */
id|dma_cmd_space
op_assign
id|kmalloc
c_func
(paren
(paren
id|host-&gt;sg_tablesize
op_plus
l_int|2
)paren
op_star
r_sizeof
(paren
r_struct
id|dbdma_cmd
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma_cmd_space
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mac53c94: couldn&squot;t allocate dma &quot;
l_string|&quot;command space for %s&bslash;n&quot;
comma
id|node-&gt;full_name
)paren
suffix:semicolon
r_goto
id|err_cleanup
suffix:semicolon
)brace
id|state-&gt;dma_cmds
op_assign
(paren
r_struct
id|dbdma_cmd
op_star
)paren
id|DBDMA_ALIGN
c_func
(paren
id|dma_cmd_space
)paren
suffix:semicolon
id|memset
c_func
(paren
id|state-&gt;dma_cmds
comma
l_int|0
comma
(paren
id|host-&gt;sg_tablesize
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_struct
id|dbdma_cmd
)paren
)paren
suffix:semicolon
id|state-&gt;dma_cmd_space
op_assign
id|dma_cmd_space
suffix:semicolon
op_star
id|prev_statep
op_assign
id|state
suffix:semicolon
id|prev_statep
op_assign
op_amp
id|state-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|state-&gt;intr
comma
id|do_mac53c94_interrupt
comma
l_int|0
comma
l_string|&quot;53C94&quot;
comma
id|state
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mac53C94: can&squot;t get irq %d for %s&bslash;n&quot;
comma
id|state-&gt;intr
comma
id|node-&gt;full_name
)paren
suffix:semicolon
id|err_cleanup
suffix:colon
id|iounmap
c_func
(paren
id|state-&gt;dma
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|state-&gt;regs
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|host
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|mac53c94_init
c_func
(paren
id|state
)paren
suffix:semicolon
op_increment
id|nfscs
suffix:semicolon
)brace
r_return
id|nfscs
suffix:semicolon
)brace
r_int
DECL|function|mac53c94_release
id|mac53c94_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
r_struct
id|fsc_state
op_star
id|fp
op_assign
(paren
r_struct
id|fsc_state
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
r_if
c_cond
(paren
id|fp
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fp-&gt;regs
)paren
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|fp-&gt;regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fp-&gt;dma
)paren
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|fp-&gt;dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|fp-&gt;dma_cmd_space
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|fp-&gt;intr
comma
id|fp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|mac53c94_queue
id|mac53c94_queue
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
(brace
r_struct
id|fsc_state
op_star
id|state
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|data_goes_out
c_func
(paren
id|cmd
)paren
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;mac53c94_queue %p: command is&quot;
comma
id|cmd
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
id|cmd-&gt;cmd_len
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot; %.2x&quot;
comma
id|cmd-&gt;cmnd
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
id|KERN_DEBUG
l_string|&quot;use_sg=%d request_bufflen=%d request_buffer=%p&bslash;n&quot;
comma
id|cmd-&gt;use_sg
comma
id|cmd-&gt;request_bufflen
comma
id|cmd-&gt;request_buffer
)paren
suffix:semicolon
)brace
macro_line|#endif
id|cmd-&gt;scsi_done
op_assign
id|done
suffix:semicolon
id|cmd-&gt;host_scribble
op_assign
l_int|NULL
suffix:semicolon
id|state
op_assign
(paren
r_struct
id|fsc_state
op_star
)paren
id|cmd-&gt;device-&gt;host-&gt;hostdata
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;request_q
op_eq
l_int|NULL
)paren
id|state-&gt;request_q
op_assign
id|cmd
suffix:semicolon
r_else
id|state-&gt;request_qtail-&gt;host_scribble
op_assign
(paren
r_void
op_star
)paren
id|cmd
suffix:semicolon
id|state-&gt;request_qtail
op_assign
id|cmd
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;phase
op_eq
id|idle
)paren
id|mac53c94_start
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|mac53c94_abort
id|mac53c94_abort
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
)paren
(brace
r_return
id|SCSI_ABORT_SNOOZE
suffix:semicolon
)brace
r_int
DECL|function|mac53c94_host_reset
id|mac53c94_host_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
)paren
(brace
r_struct
id|fsc_state
op_star
id|state
op_assign
(paren
r_struct
id|fsc_state
op_star
)paren
id|cmd-&gt;device-&gt;host-&gt;hostdata
suffix:semicolon
r_volatile
r_struct
id|mac53c94_regs
op_star
id|regs
op_assign
id|state-&gt;regs
suffix:semicolon
r_volatile
r_struct
id|dbdma_regs
op_star
id|dma
op_assign
id|state-&gt;dma
suffix:semicolon
id|st_le32
c_func
(paren
op_amp
id|dma-&gt;control
comma
(paren
id|RUN
op_or
id|PAUSE
op_or
id|FLUSH
op_or
id|WAKE
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
id|regs-&gt;command
op_assign
id|CMD_SCSI_RESET
suffix:semicolon
multiline_comment|/* assert RST */
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
multiline_comment|/* leave it on for a while (&gt;= 25us) */
id|regs-&gt;command
op_assign
id|CMD_RESET
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|mac53c94_init
c_func
(paren
id|state
)paren
suffix:semicolon
id|regs-&gt;command
op_assign
id|CMD_NOP
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
r_return
id|SUCCESS
suffix:semicolon
)brace
r_static
r_void
DECL|function|mac53c94_init
id|mac53c94_init
c_func
(paren
r_struct
id|fsc_state
op_star
id|state
)paren
(brace
r_volatile
r_struct
id|mac53c94_regs
op_star
id|regs
op_assign
id|state-&gt;regs
suffix:semicolon
r_volatile
r_struct
id|dbdma_regs
op_star
id|dma
op_assign
id|state-&gt;dma
suffix:semicolon
r_int
id|x
suffix:semicolon
id|regs-&gt;config1
op_assign
id|state-&gt;host-&gt;this_id
op_or
id|CF1_PAR_ENABLE
suffix:semicolon
id|regs-&gt;sel_timeout
op_assign
id|TIMO_VAL
c_func
(paren
l_int|250
)paren
suffix:semicolon
multiline_comment|/* 250ms */
id|regs-&gt;clk_factor
op_assign
id|CLKF_VAL
c_func
(paren
id|state-&gt;clk_freq
)paren
suffix:semicolon
id|regs-&gt;config2
op_assign
id|CF2_FEATURE_EN
suffix:semicolon
id|regs-&gt;config3
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;sync_period
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;sync_offset
op_assign
l_int|0
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|x
op_assign
id|regs-&gt;interrupt
suffix:semicolon
id|st_le32
c_func
(paren
op_amp
id|dma-&gt;control
comma
(paren
id|RUN
op_or
id|PAUSE
op_or
id|FLUSH
op_or
id|WAKE
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Start the next command for a 53C94.&n; * Should be called with interrupts disabled.&n; */
r_static
r_void
DECL|function|mac53c94_start
id|mac53c94_start
c_func
(paren
r_struct
id|fsc_state
op_star
id|state
)paren
(brace
id|Scsi_Cmnd
op_star
id|cmd
suffix:semicolon
r_volatile
r_struct
id|mac53c94_regs
op_star
id|regs
op_assign
id|state-&gt;regs
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;phase
op_ne
id|idle
op_logical_or
id|state-&gt;current_req
op_ne
l_int|NULL
)paren
id|panic
c_func
(paren
l_string|&quot;inappropriate mac53c94_start (state=%p)&quot;
comma
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;request_q
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|state-&gt;current_req
op_assign
id|cmd
op_assign
id|state-&gt;request_q
suffix:semicolon
id|state-&gt;request_q
op_assign
(paren
id|Scsi_Cmnd
op_star
)paren
id|cmd-&gt;host_scribble
suffix:semicolon
multiline_comment|/* Off we go */
id|regs-&gt;count_lo
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;count_mid
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;count_hi
op_assign
l_int|0
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|regs-&gt;command
op_assign
id|CMD_NOP
op_plus
id|CMD_DMA_MODE
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|regs-&gt;command
op_assign
id|CMD_FLUSH
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|regs-&gt;dest_id
op_assign
id|cmd-&gt;device-&gt;id
suffix:semicolon
id|regs-&gt;sync_period
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;sync_offset
op_assign
l_int|0
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* load the command into the FIFO */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|cmd-&gt;cmd_len
suffix:semicolon
op_increment
id|i
)paren
(brace
id|regs-&gt;fifo
op_assign
id|cmd-&gt;cmnd
(braket
id|i
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* do select without ATN XXX */
id|regs-&gt;command
op_assign
id|CMD_SELECT
suffix:semicolon
id|state-&gt;phase
op_assign
id|selecting
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;use_sg
OG
l_int|0
op_logical_or
id|cmd-&gt;request_bufflen
op_ne
l_int|0
)paren
id|set_dma_cmds
c_func
(paren
id|state
comma
id|cmd
)paren
suffix:semicolon
)brace
r_static
id|irqreturn_t
DECL|function|do_mac53c94_interrupt
id|do_mac53c94_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|ptregs
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|dev
op_assign
(paren
(paren
r_struct
id|fsc_state
op_star
)paren
id|dev_id
)paren
op_member_access_from_pointer
id|current_req-&gt;device-&gt;host
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
id|dev-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
id|mac53c94_interrupt
c_func
(paren
id|irq
comma
id|dev_id
comma
id|ptregs
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|dev-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_static
r_void
DECL|function|mac53c94_interrupt
id|mac53c94_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|ptregs
)paren
(brace
r_struct
id|fsc_state
op_star
id|state
op_assign
(paren
r_struct
id|fsc_state
op_star
)paren
id|dev_id
suffix:semicolon
r_volatile
r_struct
id|mac53c94_regs
op_star
id|regs
op_assign
id|state-&gt;regs
suffix:semicolon
r_volatile
r_struct
id|dbdma_regs
op_star
id|dma
op_assign
id|state-&gt;dma
suffix:semicolon
id|Scsi_Cmnd
op_star
id|cmd
op_assign
id|state-&gt;current_req
suffix:semicolon
r_int
id|nb
comma
id|stat
comma
id|seq
comma
id|intr
suffix:semicolon
r_static
r_int
id|mac53c94_errors
suffix:semicolon
r_int
id|dma_dir
suffix:semicolon
multiline_comment|/*&n;&t; * Apparently, reading the interrupt register unlatches&n;&t; * the status and sequence step registers.&n;&t; */
id|seq
op_assign
id|regs-&gt;seqstep
suffix:semicolon
id|stat
op_assign
id|regs-&gt;status
suffix:semicolon
id|intr
op_assign
id|regs-&gt;interrupt
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;mac53c94_intr, intr=%x stat=%x seq=%x phase=%d&bslash;n&quot;
comma
id|intr
comma
id|stat
comma
id|seq
comma
id|state-&gt;phase
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|intr
op_amp
id|INTR_RESET
)paren
(brace
multiline_comment|/* SCSI bus was reset */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;external SCSI bus reset detected&bslash;n&quot;
)paren
suffix:semicolon
id|regs-&gt;command
op_assign
id|CMD_NOP
suffix:semicolon
id|st_le32
c_func
(paren
op_amp
id|dma-&gt;control
comma
id|RUN
op_lshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* stop dma */
id|cmd_done
c_func
(paren
id|state
comma
id|DID_RESET
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|intr
op_amp
id|INTR_ILL_CMD
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;53c94: illegal cmd, intr=%x stat=%x seq=%x phase=%d&bslash;n&quot;
comma
id|intr
comma
id|stat
comma
id|seq
comma
id|state-&gt;phase
)paren
suffix:semicolon
id|cmd_done
c_func
(paren
id|state
comma
id|DID_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|stat
op_amp
id|STAT_ERROR
)paren
(brace
macro_line|#if 0
multiline_comment|/* XXX these seem to be harmless? */
id|printk
c_func
(paren
l_string|&quot;53c94: bad error, intr=%x stat=%x seq=%x phase=%d&bslash;n&quot;
comma
id|intr
comma
id|stat
comma
id|seq
comma
id|state-&gt;phase
)paren
suffix:semicolon
macro_line|#endif
op_increment
id|mac53c94_errors
suffix:semicolon
id|regs-&gt;command
op_assign
id|CMD_NOP
op_plus
id|CMD_DMA_MODE
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;53c94: interrupt with no command active?&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|stat
op_amp
id|STAT_PARITY
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mac53c94: parity error&bslash;n&quot;
)paren
suffix:semicolon
id|cmd_done
c_func
(paren
id|state
comma
id|DID_PARITY
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|state-&gt;phase
)paren
(brace
r_case
id|selecting
suffix:colon
r_if
c_cond
(paren
id|intr
op_amp
id|INTR_DISCONNECT
)paren
(brace
multiline_comment|/* selection timed out */
id|cmd_done
c_func
(paren
id|state
comma
id|DID_BAD_TARGET
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|intr
op_ne
id|INTR_BUS_SERV
op_plus
id|INTR_DONE
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;got intr %x during selection&bslash;n&quot;
comma
id|intr
)paren
suffix:semicolon
id|cmd_done
c_func
(paren
id|state
comma
id|DID_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|seq
op_amp
id|SS_MASK
)paren
op_ne
id|SS_DONE
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;seq step %x after command&bslash;n&quot;
comma
id|seq
)paren
suffix:semicolon
id|cmd_done
c_func
(paren
id|state
comma
id|DID_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|regs-&gt;command
op_assign
id|CMD_NOP
suffix:semicolon
multiline_comment|/* set DMA controller going if any data to transfer */
r_if
c_cond
(paren
(paren
id|stat
op_amp
(paren
id|STAT_MSG
op_or
id|STAT_CD
)paren
)paren
op_eq
l_int|0
op_logical_and
(paren
id|cmd-&gt;use_sg
OG
l_int|0
op_logical_or
id|cmd-&gt;request_bufflen
op_ne
l_int|0
)paren
)paren
(brace
id|nb
op_assign
id|cmd-&gt;SCp.this_residual
suffix:semicolon
r_if
c_cond
(paren
id|nb
OG
l_int|0xfff0
)paren
id|nb
op_assign
l_int|0xfff0
suffix:semicolon
id|cmd-&gt;SCp.this_residual
op_sub_assign
id|nb
suffix:semicolon
id|regs-&gt;count_lo
op_assign
id|nb
suffix:semicolon
id|regs-&gt;count_mid
op_assign
id|nb
op_rshift
l_int|8
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|regs-&gt;command
op_assign
id|CMD_DMA_MODE
op_plus
id|CMD_NOP
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|st_le32
c_func
(paren
op_amp
id|dma-&gt;cmdptr
comma
id|virt_to_phys
c_func
(paren
id|state-&gt;dma_cmds
)paren
)paren
suffix:semicolon
id|st_le32
c_func
(paren
op_amp
id|dma-&gt;control
comma
(paren
id|RUN
op_lshift
l_int|16
)paren
op_or
id|RUN
)paren
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|regs-&gt;command
op_assign
id|CMD_DMA_MODE
op_plus
id|CMD_XFER_DATA
suffix:semicolon
id|state-&gt;phase
op_assign
id|dataing
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|stat
op_amp
id|STAT_PHASE
)paren
op_eq
id|STAT_CD
op_plus
id|STAT_IO
)paren
(brace
multiline_comment|/* up to status phase already */
id|regs-&gt;command
op_assign
id|CMD_I_COMPLETE
suffix:semicolon
id|state-&gt;phase
op_assign
id|completing
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;in unexpected phase %x after cmd&bslash;n&quot;
comma
id|stat
op_amp
id|STAT_PHASE
)paren
suffix:semicolon
id|cmd_done
c_func
(paren
id|state
comma
id|DID_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|dataing
suffix:colon
r_if
c_cond
(paren
id|intr
op_ne
id|INTR_BUS_SERV
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;got intr %x before status&bslash;n&quot;
comma
id|intr
)paren
suffix:semicolon
id|cmd_done
c_func
(paren
id|state
comma
id|DID_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd-&gt;SCp.this_residual
op_ne
l_int|0
op_logical_and
(paren
id|stat
op_amp
(paren
id|STAT_MSG
op_or
id|STAT_CD
)paren
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Set up the count regs to transfer more */
id|nb
op_assign
id|cmd-&gt;SCp.this_residual
suffix:semicolon
r_if
c_cond
(paren
id|nb
OG
l_int|0xfff0
)paren
id|nb
op_assign
l_int|0xfff0
suffix:semicolon
id|cmd-&gt;SCp.this_residual
op_sub_assign
id|nb
suffix:semicolon
id|regs-&gt;count_lo
op_assign
id|nb
suffix:semicolon
id|regs-&gt;count_mid
op_assign
id|nb
op_rshift
l_int|8
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|regs-&gt;command
op_assign
id|CMD_DMA_MODE
op_plus
id|CMD_NOP
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|regs-&gt;command
op_assign
id|CMD_DMA_MODE
op_plus
id|CMD_XFER_DATA
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|stat
op_amp
id|STAT_PHASE
)paren
op_ne
id|STAT_CD
op_plus
id|STAT_IO
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;intr %x before data xfer complete&bslash;n&quot;
comma
id|intr
)paren
suffix:semicolon
)brace
id|out_le32
c_func
(paren
op_amp
id|dma-&gt;control
comma
id|RUN
op_lshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* stop dma */
id|dma_dir
op_assign
id|scsi_to_pci_dma_dir
c_func
(paren
id|cmd-&gt;sc_data_direction
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;use_sg
op_ne
l_int|0
)paren
(brace
id|pci_unmap_sg
c_func
(paren
id|state-&gt;pdev
comma
(paren
r_struct
id|scatterlist
op_star
)paren
id|cmd-&gt;request_buffer
comma
id|cmd-&gt;use_sg
comma
id|dma_dir
)paren
suffix:semicolon
)brace
r_else
(brace
id|pci_unmap_single
c_func
(paren
id|state-&gt;pdev
comma
id|state-&gt;dma_addr
comma
id|cmd-&gt;request_bufflen
comma
id|dma_dir
)paren
suffix:semicolon
)brace
multiline_comment|/* should check dma status */
id|regs-&gt;command
op_assign
id|CMD_I_COMPLETE
suffix:semicolon
id|state-&gt;phase
op_assign
id|completing
suffix:semicolon
r_break
suffix:semicolon
r_case
id|completing
suffix:colon
r_if
c_cond
(paren
id|intr
op_ne
id|INTR_DONE
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;got intr %x on completion&bslash;n&quot;
comma
id|intr
)paren
suffix:semicolon
id|cmd_done
c_func
(paren
id|state
comma
id|DID_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cmd-&gt;SCp.Status
op_assign
id|regs-&gt;fifo
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|cmd-&gt;SCp.Message
op_assign
id|regs-&gt;fifo
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|cmd-&gt;result
op_assign
id|regs-&gt;command
op_assign
id|CMD_ACCEPT_MSG
suffix:semicolon
id|state-&gt;phase
op_assign
id|busfreeing
suffix:semicolon
r_break
suffix:semicolon
r_case
id|busfreeing
suffix:colon
r_if
c_cond
(paren
id|intr
op_ne
id|INTR_DISCONNECT
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;got intr %x when expected disconnect&bslash;n&quot;
comma
id|intr
)paren
suffix:semicolon
)brace
id|cmd_done
c_func
(paren
id|state
comma
(paren
id|DID_OK
op_lshift
l_int|16
)paren
op_plus
(paren
id|cmd-&gt;SCp.Message
op_lshift
l_int|8
)paren
op_plus
id|cmd-&gt;SCp.Status
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;don&squot;t know about phase %d&bslash;n&quot;
comma
id|state-&gt;phase
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|cmd_done
id|cmd_done
c_func
(paren
r_struct
id|fsc_state
op_star
id|state
comma
r_int
id|result
)paren
(brace
id|Scsi_Cmnd
op_star
id|cmd
suffix:semicolon
id|cmd
op_assign
id|state-&gt;current_req
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ne
l_int|0
)paren
(brace
id|cmd-&gt;result
op_assign
id|result
suffix:semicolon
(paren
op_star
id|cmd-&gt;scsi_done
)paren
(paren
id|cmd
)paren
suffix:semicolon
id|state-&gt;current_req
op_assign
l_int|NULL
suffix:semicolon
)brace
id|state-&gt;phase
op_assign
id|idle
suffix:semicolon
id|mac53c94_start
c_func
(paren
id|state
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up DMA commands for transferring data.&n; */
r_static
r_void
DECL|function|set_dma_cmds
id|set_dma_cmds
c_func
(paren
r_struct
id|fsc_state
op_star
id|state
comma
id|Scsi_Cmnd
op_star
id|cmd
)paren
(brace
r_int
id|i
comma
id|dma_cmd
comma
id|total
suffix:semicolon
r_struct
id|scatterlist
op_star
id|scl
suffix:semicolon
r_struct
id|dbdma_cmd
op_star
id|dcmds
suffix:semicolon
id|dma_addr_t
id|dma_addr
suffix:semicolon
id|u32
id|dma_len
suffix:semicolon
r_int
id|dma_dir
op_assign
id|scsi_to_pci_dma_dir
c_func
(paren
id|cmd-&gt;sc_data_direction
)paren
suffix:semicolon
id|dma_cmd
op_assign
id|data_goes_out
c_func
(paren
id|cmd
)paren
ques
c_cond
id|OUTPUT_MORE
suffix:colon
id|INPUT_MORE
suffix:semicolon
id|dcmds
op_assign
id|state-&gt;dma_cmds
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;use_sg
OG
l_int|0
)paren
(brace
r_int
id|nseg
suffix:semicolon
id|total
op_assign
l_int|0
suffix:semicolon
id|scl
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|cmd-&gt;buffer
suffix:semicolon
id|nseg
op_assign
id|pci_map_sg
c_func
(paren
id|state-&gt;pdev
comma
id|scl
comma
id|cmd-&gt;use_sg
comma
id|dma_dir
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
id|nseg
suffix:semicolon
op_increment
id|i
)paren
(brace
id|dma_addr
op_assign
id|sg_dma_address
c_func
(paren
id|scl
)paren
suffix:semicolon
id|dma_len
op_assign
id|sg_dma_len
c_func
(paren
id|scl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma_len
OG
l_int|0xffff
)paren
id|panic
c_func
(paren
l_string|&quot;mac53c94: scatterlist element &gt;= 64k&quot;
)paren
suffix:semicolon
id|total
op_add_assign
id|dma_len
suffix:semicolon
id|st_le16
c_func
(paren
op_amp
id|dcmds-&gt;req_count
comma
id|dma_len
)paren
suffix:semicolon
id|st_le16
c_func
(paren
op_amp
id|dcmds-&gt;command
comma
id|dma_cmd
)paren
suffix:semicolon
id|st_le32
c_func
(paren
op_amp
id|dcmds-&gt;phy_addr
comma
id|dma_addr
)paren
suffix:semicolon
id|dcmds-&gt;xfer_status
op_assign
l_int|0
suffix:semicolon
op_increment
id|scl
suffix:semicolon
op_increment
id|dcmds
suffix:semicolon
)brace
)brace
r_else
(brace
id|total
op_assign
id|cmd-&gt;request_bufflen
suffix:semicolon
r_if
c_cond
(paren
id|total
OG
l_int|0xffff
)paren
id|panic
c_func
(paren
l_string|&quot;mac53c94: transfer size &gt;= 64k&quot;
)paren
suffix:semicolon
id|dma_addr
op_assign
id|pci_map_single
c_func
(paren
id|state-&gt;pdev
comma
id|cmd-&gt;request_buffer
comma
id|total
comma
id|dma_dir
)paren
suffix:semicolon
id|state-&gt;dma_addr
op_assign
id|dma_addr
suffix:semicolon
id|st_le16
c_func
(paren
op_amp
id|dcmds-&gt;req_count
comma
id|total
)paren
suffix:semicolon
id|st_le32
c_func
(paren
op_amp
id|dcmds-&gt;phy_addr
comma
id|dma_addr
)paren
suffix:semicolon
id|dcmds-&gt;xfer_status
op_assign
l_int|0
suffix:semicolon
op_increment
id|dcmds
suffix:semicolon
)brace
id|dma_cmd
op_add_assign
id|OUTPUT_LAST
op_minus
id|OUTPUT_MORE
suffix:semicolon
id|st_le16
c_func
(paren
op_amp
id|dcmds
(braket
op_minus
l_int|1
)braket
dot
id|command
comma
id|dma_cmd
)paren
suffix:semicolon
id|st_le16
c_func
(paren
op_amp
id|dcmds-&gt;command
comma
id|DBDMA_STOP
)paren
suffix:semicolon
id|cmd-&gt;SCp.this_residual
op_assign
id|total
suffix:semicolon
)brace
multiline_comment|/*&n; * Work out whether data will be going out from the host adaptor or into it.&n; */
r_static
r_int
DECL|function|data_goes_out
id|data_goes_out
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
)paren
(brace
r_switch
c_cond
(paren
id|cmd-&gt;sc_data_direction
)paren
(brace
r_case
id|SCSI_DATA_WRITE
suffix:colon
r_return
l_int|1
suffix:semicolon
r_case
id|SCSI_DATA_READ
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* for SCSI_DATA_UNKNOWN or SCSI_DATA_NONE, fall back on the&n;&t;   old method for now... */
r_switch
c_cond
(paren
id|cmd-&gt;cmnd
(braket
l_int|0
)braket
)paren
(brace
r_case
id|CHANGE_DEFINITION
suffix:colon
r_case
id|COMPARE
suffix:colon
r_case
id|COPY
suffix:colon
r_case
id|COPY_VERIFY
suffix:colon
r_case
id|FORMAT_UNIT
suffix:colon
r_case
id|LOG_SELECT
suffix:colon
r_case
id|MEDIUM_SCAN
suffix:colon
r_case
id|MODE_SELECT
suffix:colon
r_case
id|MODE_SELECT_10
suffix:colon
r_case
id|REASSIGN_BLOCKS
suffix:colon
r_case
id|RESERVE
suffix:colon
r_case
id|SEARCH_EQUAL
suffix:colon
r_case
id|SEARCH_EQUAL_12
suffix:colon
r_case
id|SEARCH_HIGH
suffix:colon
r_case
id|SEARCH_HIGH_12
suffix:colon
r_case
id|SEARCH_LOW
suffix:colon
r_case
id|SEARCH_LOW_12
suffix:colon
r_case
id|SEND_DIAGNOSTIC
suffix:colon
r_case
id|SEND_VOLUME_TAG
suffix:colon
r_case
id|SET_WINDOW
suffix:colon
r_case
id|UPDATE_BLOCK
suffix:colon
r_case
id|WRITE_BUFFER
suffix:colon
r_case
id|WRITE_6
suffix:colon
r_case
id|WRITE_10
suffix:colon
r_case
id|WRITE_12
suffix:colon
r_case
id|WRITE_LONG
suffix:colon
r_case
id|WRITE_LONG_2
suffix:colon
multiline_comment|/* alternate code for WRITE_LONG */
r_case
id|WRITE_SAME
suffix:colon
r_case
id|WRITE_VERIFY
suffix:colon
r_case
id|WRITE_VERIFY_12
suffix:colon
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
(brace
dot
id|proc_name
op_assign
l_string|&quot;53c94&quot;
comma
dot
id|name
op_assign
l_string|&quot;53C94&quot;
comma
dot
id|detect
op_assign
id|mac53c94_detect
comma
dot
id|release
op_assign
id|mac53c94_release
comma
dot
id|queuecommand
op_assign
id|mac53c94_queue
comma
dot
id|eh_abort_handler
op_assign
id|mac53c94_abort
comma
dot
id|eh_host_reset_handler
op_assign
id|mac53c94_host_reset
comma
dot
id|can_queue
op_assign
l_int|1
comma
dot
id|this_id
op_assign
l_int|7
comma
dot
id|sg_tablesize
op_assign
id|SG_ALL
comma
dot
id|cmd_per_lun
op_assign
l_int|1
comma
dot
id|use_clustering
op_assign
id|DISABLE_CLUSTERING
comma
)brace
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
eof

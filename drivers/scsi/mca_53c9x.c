multiline_comment|/* mca_53c9x.c: Driver for the SCSI adapter found on NCR 35xx&n; *  (and maybe some other) Microchannel machines&n; *&n; * Code taken mostly from Cyberstorm SCSI drivers&n; *   Copyright (C) 1996 Jesper Skov (jskov@cygnus.co.uk)&n; *&n; * Hacked to work with the NCR MCA stuff by Tymm Twillman (tymm@computer.org)&n; *&n; * The CyberStorm SCSI driver (and this driver) is based on David S. Miller&squot;s&n; *   ESP driver  * for the Sparc computers. &n; * &n; * Special thanks to Ken Stewart at Symbios (LSI) for helping with info on&n; *  the 86C01.  I was on the brink of going ga-ga...&n; *&n; * Also thanks to Jesper Skov for helping me with info on how the Amiga&n; *  does things...&n; */
multiline_comment|/*&n; * This is currently only set up to use one 53c9x card at a time; it could be &n; *  changed fairly easily to detect/use more than one, but I&squot;m not too sure how&n; *  many cards that use the 53c9x on MCA systems there are (if, in fact, there&n; *  are cards that use them, other than the one built into some NCR systems)...&n; *  If anyone requests this, I&squot;ll throw it in, otherwise it&squot;s not worth the&n; *  effort.&n; */
multiline_comment|/*&n; * Info on the 86C01 MCA interface chip at the bottom, if you care enough to&n; *  look.&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mca.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mca-legacy.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &quot;NCR53C9x.h&quot;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mca_dma.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/*&n; * From ibmmca.c (IBM scsi controller card driver) -- used for turning PS2 disk&n; *  activity LED on and off&n; */
DECL|macro|PS2_SYS_CTR
mdefine_line|#define PS2_SYS_CTR&t;0x92
multiline_comment|/* Ports the ncr&squot;s 53c94 can be put at; indexed by pos register value */
DECL|macro|MCA_53C9X_IO_PORTS
mdefine_line|#define MCA_53C9X_IO_PORTS {                             &bslash;&n;                         0x0000, 0x0240, 0x0340, 0x0400, &bslash;&n;&t;                 0x0420, 0x3240, 0x8240, 0xA240, &bslash;&n;&t;                }
multiline_comment|/*&n; * Supposedly there were some cards put together with the &squot;c9x and 86c01.  If&n; *   they have different ID&squot;s from the ones on the 3500 series machines, &n; *   you can add them here and hopefully things will work out.&n; */
DECL|macro|MCA_53C9X_IDS
mdefine_line|#define MCA_53C9X_IDS {          &bslash;&n;                         0x7F4C, &bslash;&n;&t;&t;&t; 0x0000, &bslash;&n;                        }
r_static
r_int
id|dma_bytes_sent
c_func
(paren
r_struct
id|NCR_ESP
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|dma_can_transfer
c_func
(paren
r_struct
id|NCR_ESP
op_star
comma
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_void
id|dma_dump_state
c_func
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
r_static
r_void
id|dma_init_read
c_func
(paren
r_struct
id|NCR_ESP
op_star
comma
id|__u32
comma
r_int
)paren
suffix:semicolon
r_static
r_void
id|dma_init_write
c_func
(paren
r_struct
id|NCR_ESP
op_star
comma
id|__u32
comma
r_int
)paren
suffix:semicolon
r_static
r_void
id|dma_ints_off
c_func
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
r_static
r_void
id|dma_ints_on
c_func
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
r_static
r_int
id|dma_irq_p
c_func
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
r_static
r_int
id|dma_ports_p
c_func
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
r_static
r_void
id|dma_setup
c_func
(paren
r_struct
id|NCR_ESP
op_star
comma
id|__u32
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_static
r_void
id|dma_led_on
c_func
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
r_static
r_void
id|dma_led_off
c_func
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
multiline_comment|/* This is where all commands are put before they are trasfered to the &n; *  53c9x via PIO.&n; */
DECL|variable|cmd_buffer
r_static
r_volatile
r_int
r_char
id|cmd_buffer
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/*&n; * We keep the structure that is used to access the registers on the 53c9x&n; *  here.&n; */
DECL|variable|eregs
r_static
r_struct
id|ESP_regs
id|eregs
suffix:semicolon
multiline_comment|/***************************************************************** Detection */
DECL|function|mca_esp_detect
r_int
id|mca_esp_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
r_struct
id|NCR_ESP
op_star
id|esp
suffix:semicolon
r_static
r_int
id|io_port_by_pos
(braket
)braket
op_assign
id|MCA_53C9X_IO_PORTS
suffix:semicolon
r_int
id|mca_53c9x_ids
(braket
)braket
op_assign
id|MCA_53C9X_IDS
suffix:semicolon
r_int
op_star
id|id_to_check
op_assign
id|mca_53c9x_ids
suffix:semicolon
r_int
id|slot
suffix:semicolon
r_int
id|pos
(braket
l_int|3
)braket
suffix:semicolon
r_int
r_int
id|tmp_io_addr
suffix:semicolon
r_int
r_char
id|tmp_byte
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MCA_bus
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|id_to_check
)paren
(brace
r_if
c_cond
(paren
(paren
id|slot
op_assign
id|mca_find_adapter
c_func
(paren
op_star
id|id_to_check
comma
l_int|0
)paren
)paren
op_ne
id|MCA_NOTFOUND
)paren
(brace
id|esp
op_assign
id|esp_allocate
c_func
(paren
id|tpnt
comma
(paren
r_void
op_star
)paren
l_int|NULL
)paren
suffix:semicolon
id|pos
(braket
l_int|0
)braket
op_assign
id|mca_read_stored_pos
c_func
(paren
id|slot
comma
l_int|2
)paren
suffix:semicolon
id|pos
(braket
l_int|1
)braket
op_assign
id|mca_read_stored_pos
c_func
(paren
id|slot
comma
l_int|3
)paren
suffix:semicolon
id|pos
(braket
l_int|2
)braket
op_assign
id|mca_read_stored_pos
c_func
(paren
id|slot
comma
l_int|4
)paren
suffix:semicolon
id|esp-&gt;eregs
op_assign
op_amp
id|eregs
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * IO port base is given in the first (non-ID) pos&n;&t;&t;&t; *  register, like so:&n;&t;&t;&t; *&n;&t;&t;&t; *  Bits 3  2  1       IO base&n;&t;&t;&t; * ----------------------------&n;&t;&t;&t; *       0  0  0       &lt;disabled&gt;&n;&t;&t;&t; *       0  0  1       0x0240&n;&t;&t;&t; *       0  1  0       0x0340&n;&t;&t;&t; *       0  1  1       0x0400&n;&t;&t;&t; *       1  0  0       0x0420&n;&t;&t;&t; *       1  0  1       0x3240&n;&t;&t;&t; *       1  1  0       0x8240&n;&t;&t;&t; *       1  1  1       0xA240&n;&t;&t;&t; */
id|tmp_io_addr
op_assign
id|io_port_by_pos
(braket
(paren
id|pos
(braket
l_int|0
)braket
op_amp
l_int|0x0E
)paren
op_rshift
l_int|1
)braket
suffix:semicolon
id|esp-&gt;eregs-&gt;io_addr
op_assign
id|tmp_io_addr
op_plus
l_int|0x10
suffix:semicolon
r_if
c_cond
(paren
id|esp-&gt;eregs-&gt;io_addr
op_eq
l_int|0x0000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Adapter is disabled.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * IRQ is specified in bits 4 and 5:&n;&t;&t;&t; *&n;&t;&t;&t; *  Bits  4  5        IRQ&n;&t;&t;&t; * -----------------------&n;&t;&t;&t; *        0  0         3&n;&t;&t;&t; *        0  1         5&n;&t;&t;&t; *        1  0         7&n;&t;&t;&t; *        1  1         9&n;&t;&t;&t; */
id|esp-&gt;irq
op_assign
(paren
(paren
id|pos
(braket
l_int|0
)braket
op_amp
l_int|0x30
)paren
op_rshift
l_int|3
)paren
op_plus
l_int|3
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * DMA channel is in the low 3 bits of the second&n;&t;&t;&t; *  POS register&n;&t;&t;&t; */
id|esp-&gt;dma
op_assign
id|pos
(braket
l_int|1
)braket
op_amp
l_int|7
suffix:semicolon
id|esp-&gt;slot
op_assign
id|slot
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|esp-&gt;irq
comma
id|esp_intr
comma
l_int|0
comma
l_string|&quot;NCR 53c9x SCSI&quot;
comma
id|esp-&gt;ehost
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to request IRQ %d.&bslash;n&quot;
comma
id|esp-&gt;irq
)paren
suffix:semicolon
id|esp_deallocate
c_func
(paren
id|esp
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|esp-&gt;ehost
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_dma
c_func
(paren
id|esp-&gt;dma
comma
l_string|&quot;NCR 53c9x SCSI&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to request DMA channel %d.&bslash;n&quot;
comma
id|esp-&gt;dma
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|esp-&gt;irq
comma
id|esp_intr
)paren
suffix:semicolon
id|esp_deallocate
c_func
(paren
id|esp
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|esp-&gt;ehost
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|request_region
c_func
(paren
id|tmp_io_addr
comma
l_int|32
comma
l_string|&quot;NCR 53c9x SCSI&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * 86C01 handles DMA, IO mode, from address&n;&t;&t;&t; *  (base + 0x0a)&n;&t;&t;&t; */
id|mca_disable_dma
c_func
(paren
id|esp-&gt;dma
)paren
suffix:semicolon
id|mca_set_dma_io
c_func
(paren
id|esp-&gt;dma
comma
id|tmp_io_addr
op_plus
l_int|0x0a
)paren
suffix:semicolon
id|mca_enable_dma
c_func
(paren
id|esp-&gt;dma
)paren
suffix:semicolon
multiline_comment|/* Tell the 86C01 to give us interrupts */
id|tmp_byte
op_assign
id|inb
c_func
(paren
id|tmp_io_addr
op_plus
l_int|0x02
)paren
op_or
l_int|0x40
suffix:semicolon
id|outb
c_func
(paren
id|tmp_byte
comma
id|tmp_io_addr
op_plus
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Scsi ID -- general purpose register, hi&n;&t;&t;&t; *  2 bits; add 4 to this number to get the&n;&t;&t;&t; *  ID&n;&t;&t;&t; */
id|esp-&gt;scsi_id
op_assign
(paren
(paren
id|pos
(braket
l_int|2
)braket
op_amp
l_int|0xC0
)paren
op_rshift
l_int|6
)paren
op_plus
l_int|4
suffix:semicolon
multiline_comment|/* Do command transfer with programmed I/O */
id|esp-&gt;do_pio_cmds
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Required functions */
id|esp-&gt;dma_bytes_sent
op_assign
op_amp
id|dma_bytes_sent
suffix:semicolon
id|esp-&gt;dma_can_transfer
op_assign
op_amp
id|dma_can_transfer
suffix:semicolon
id|esp-&gt;dma_dump_state
op_assign
op_amp
id|dma_dump_state
suffix:semicolon
id|esp-&gt;dma_init_read
op_assign
op_amp
id|dma_init_read
suffix:semicolon
id|esp-&gt;dma_init_write
op_assign
op_amp
id|dma_init_write
suffix:semicolon
id|esp-&gt;dma_ints_off
op_assign
op_amp
id|dma_ints_off
suffix:semicolon
id|esp-&gt;dma_ints_on
op_assign
op_amp
id|dma_ints_on
suffix:semicolon
id|esp-&gt;dma_irq_p
op_assign
op_amp
id|dma_irq_p
suffix:semicolon
id|esp-&gt;dma_ports_p
op_assign
op_amp
id|dma_ports_p
suffix:semicolon
id|esp-&gt;dma_setup
op_assign
op_amp
id|dma_setup
suffix:semicolon
multiline_comment|/* Optional functions */
id|esp-&gt;dma_barrier
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;dma_drain
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;dma_invalidate
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;dma_irq_entry
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;dma_irq_exit
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;dma_led_on
op_assign
id|dma_led_on
suffix:semicolon
id|esp-&gt;dma_led_off
op_assign
id|dma_led_off
suffix:semicolon
id|esp-&gt;dma_poll
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;dma_reset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set the command buffer */
id|esp-&gt;esp_command
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
id|cmd_buffer
suffix:semicolon
id|esp-&gt;esp_command_dvma
op_assign
id|isa_virt_to_bus
c_func
(paren
id|cmd_buffer
)paren
suffix:semicolon
multiline_comment|/* SCSI chip speed */
id|esp-&gt;cfreq
op_assign
l_int|25000000
suffix:semicolon
multiline_comment|/* Differential SCSI? I think not. */
id|esp-&gt;diff
op_assign
l_int|0
suffix:semicolon
id|esp_initialize
c_func
(paren
id|esp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; Adapter found in slot %2d: io port 0x%x &quot;
l_string|&quot;irq %d dma channel %d&bslash;n&quot;
comma
id|slot
op_plus
l_int|1
comma
id|tmp_io_addr
comma
id|esp-&gt;irq
comma
id|esp-&gt;dma
)paren
suffix:semicolon
id|mca_set_adapter_name
c_func
(paren
id|slot
comma
l_string|&quot;NCR 53C9X SCSI Adapter&quot;
)paren
suffix:semicolon
id|mca_mark_as_used
c_func
(paren
id|slot
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|id_to_check
op_increment
suffix:semicolon
)brace
r_return
id|esps_in_use
suffix:semicolon
)brace
multiline_comment|/******************************************************************* Release */
DECL|function|mca_esp_release
r_int
id|mca_esp_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
r_struct
id|NCR_ESP
op_star
id|esp
op_assign
(paren
r_struct
id|NCR_ESP
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
r_int
r_char
id|tmp_byte
suffix:semicolon
id|esp_deallocate
c_func
(paren
id|esp
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Tell the 86C01 to stop sending interrupts&n;&t; */
id|tmp_byte
op_assign
id|inb
c_func
(paren
id|esp-&gt;eregs-&gt;io_addr
op_minus
l_int|0x0E
)paren
suffix:semicolon
id|tmp_byte
op_and_assign
op_complement
l_int|0x40
suffix:semicolon
id|outb
c_func
(paren
id|tmp_byte
comma
id|esp-&gt;eregs-&gt;io_addr
op_minus
l_int|0x0E
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|esp-&gt;irq
comma
id|esp_intr
)paren
suffix:semicolon
id|free_dma
c_func
(paren
id|esp-&gt;dma
)paren
suffix:semicolon
id|mca_mark_as_unused
c_func
(paren
id|esp-&gt;slot
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/************************************************************* DMA Functions */
DECL|function|dma_bytes_sent
r_static
r_int
id|dma_bytes_sent
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
comma
r_int
id|fifo_count
)paren
(brace
multiline_comment|/* Ask the 53c9x.  It knows. */
r_return
id|fifo_count
suffix:semicolon
)brace
DECL|function|dma_can_transfer
r_static
r_int
id|dma_can_transfer
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
comma
id|Scsi_Cmnd
op_star
id|sp
)paren
(brace
multiline_comment|/* &n;&t; * The MCA dma channels can only do up to 128K bytes at a time.&n;         *  (16 bit mode)&n;&t; */
r_int
r_int
id|sz
op_assign
id|sp-&gt;SCp.this_residual
suffix:semicolon
r_if
c_cond
(paren
id|sz
OG
l_int|0x20000
)paren
(brace
id|sz
op_assign
l_int|0x20000
suffix:semicolon
)brace
r_return
id|sz
suffix:semicolon
)brace
DECL|function|dma_dump_state
r_static
r_void
id|dma_dump_state
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
(brace
multiline_comment|/*&n;&t; * Doesn&squot;t quite match up to the other drivers, but we do what we&n;&t; *  can.&n;&t; */
id|ESPLOG
c_func
(paren
(paren
l_string|&quot;esp%d: dma channel &lt;%d&gt;&bslash;n&quot;
comma
id|esp-&gt;esp_id
comma
id|esp-&gt;dma
)paren
)paren
suffix:semicolon
id|ESPLOG
c_func
(paren
(paren
l_string|&quot;bytes left to dma: %d&bslash;n&quot;
comma
id|mca_get_dma_residue
c_func
(paren
id|esp-&gt;dma
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|dma_init_read
r_static
r_void
id|dma_init_read
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
comma
id|__u32
id|addr
comma
r_int
id|length
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|mca_disable_dma
c_func
(paren
id|esp-&gt;dma
)paren
suffix:semicolon
id|mca_set_dma_mode
c_func
(paren
id|esp-&gt;dma
comma
id|MCA_DMA_MODE_XFER
op_or
id|MCA_DMA_MODE_16
op_or
id|MCA_DMA_MODE_IO
)paren
suffix:semicolon
id|mca_set_dma_addr
c_func
(paren
id|esp-&gt;dma
comma
id|addr
)paren
suffix:semicolon
id|mca_set_dma_count
c_func
(paren
id|esp-&gt;dma
comma
id|length
op_div
l_int|2
)paren
suffix:semicolon
multiline_comment|/* !!! */
id|mca_enable_dma
c_func
(paren
id|esp-&gt;dma
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|dma_init_write
r_static
r_void
id|dma_init_write
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
comma
id|__u32
id|addr
comma
r_int
id|length
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|mca_disable_dma
c_func
(paren
id|esp-&gt;dma
)paren
suffix:semicolon
id|mca_set_dma_mode
c_func
(paren
id|esp-&gt;dma
comma
id|MCA_DMA_MODE_XFER
op_or
id|MCA_DMA_MODE_WRITE
op_or
id|MCA_DMA_MODE_16
op_or
id|MCA_DMA_MODE_IO
)paren
suffix:semicolon
id|mca_set_dma_addr
c_func
(paren
id|esp-&gt;dma
comma
id|addr
)paren
suffix:semicolon
id|mca_set_dma_count
c_func
(paren
id|esp-&gt;dma
comma
id|length
op_div
l_int|2
)paren
suffix:semicolon
multiline_comment|/* !!! */
id|mca_enable_dma
c_func
(paren
id|esp-&gt;dma
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|dma_ints_off
r_static
r_void
id|dma_ints_off
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
(brace
multiline_comment|/*&n;&t; * Tell the &squot;C01 to shut up.  All interrupts are routed through it.&n;&t; */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|esp-&gt;eregs-&gt;io_addr
op_minus
l_int|0x0E
)paren
op_amp
op_complement
l_int|0x40
comma
id|esp-&gt;eregs-&gt;io_addr
op_minus
l_int|0x0E
)paren
suffix:semicolon
)brace
DECL|function|dma_ints_on
r_static
r_void
id|dma_ints_on
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
(brace
multiline_comment|/*&n;&t; * Ok.  You can speak again.&n;&t; */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|esp-&gt;eregs-&gt;io_addr
op_minus
l_int|0x0E
)paren
op_or
l_int|0x40
comma
id|esp-&gt;eregs-&gt;io_addr
op_minus
l_int|0x0E
)paren
suffix:semicolon
)brace
DECL|function|dma_irq_p
r_static
r_int
id|dma_irq_p
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
(brace
multiline_comment|/*&n;&t; * DaveM says that this should return a &quot;yes&quot; if there is an interrupt&n;&t; *  or a DMA error occurred.  I copied the Amiga driver&squot;s semantics,&n;&t; *  though, because it seems to work and we can&squot;t really tell if&n;&t; *  a DMA error happened.  This gives the &quot;yes&quot; if the scsi chip&n;&t; *  is sending an interrupt and no DMA activity is taking place&n;&t; */
r_return
(paren
op_logical_neg
(paren
id|inb
c_func
(paren
id|esp-&gt;eregs-&gt;io_addr
op_minus
l_int|0x04
)paren
op_amp
l_int|1
)paren
op_logical_and
op_logical_neg
(paren
id|inb
c_func
(paren
id|esp-&gt;eregs-&gt;io_addr
op_minus
l_int|0x04
)paren
op_amp
l_int|2
)paren
)paren
suffix:semicolon
)brace
DECL|function|dma_ports_p
r_static
r_int
id|dma_ports_p
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
(brace
multiline_comment|/*&n;&t; * Check to see if interrupts are enabled on the &squot;C01 (in case abort&n;&t; *  is entered multiple times, so we only do the abort once)&n;&t; */
r_return
(paren
id|inb
c_func
(paren
id|esp-&gt;eregs-&gt;io_addr
op_minus
l_int|0x0E
)paren
op_amp
l_int|0x40
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|dma_setup
r_static
r_void
id|dma_setup
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
comma
id|__u32
id|addr
comma
r_int
id|count
comma
r_int
id|write
)paren
(brace
r_if
c_cond
(paren
id|write
)paren
(brace
id|dma_init_write
c_func
(paren
id|esp
comma
id|addr
comma
id|count
)paren
suffix:semicolon
)brace
r_else
(brace
id|dma_init_read
c_func
(paren
id|esp
comma
id|addr
comma
id|count
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * These will not play nicely with other disk controllers that try to use the&n; *  disk active LED... but what can you do?  Don&squot;t answer that.&n; *&n; * Stolen shamelessly from ibmmca.c -- IBM Microchannel SCSI adapter driver&n; *&n; */
DECL|function|dma_led_on
r_static
r_void
id|dma_led_on
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
(brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|PS2_SYS_CTR
)paren
op_or
l_int|0xc0
comma
id|PS2_SYS_CTR
)paren
suffix:semicolon
)brace
DECL|function|dma_led_off
r_static
r_void
id|dma_led_off
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
(brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|PS2_SYS_CTR
)paren
op_amp
l_int|0x3f
comma
id|PS2_SYS_CTR
)paren
suffix:semicolon
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
l_string|&quot;esp&quot;
comma
dot
id|name
op_assign
l_string|&quot;NCR 53c9x SCSI&quot;
comma
dot
id|detect
op_assign
id|mca_esp_detect
comma
dot
id|slave_alloc
op_assign
id|esp_slave_alloc
comma
dot
id|slave_destroy
op_assign
id|esp_slave_destroy
comma
dot
id|release
op_assign
id|mca_esp_release
comma
dot
id|queuecommand
op_assign
id|esp_queue
comma
dot
id|eh_abort_handler
op_assign
id|esp_abort
comma
dot
id|eh_bus_reset_handler
op_assign
id|esp_reset
comma
dot
id|can_queue
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
id|unchecked_isa_dma
op_assign
l_int|1
comma
dot
id|use_clustering
op_assign
id|DISABLE_CLUSTERING
)brace
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
multiline_comment|/*&n; * OK, here&squot;s the goods I promised.  The NCR 86C01 is an MCA interface chip &n; *  that handles enabling/diabling IRQ, dma interfacing, IO port selection&n; *  and other fun stuff.  It takes up 16 addresses, and the chip it is&n; *  connnected to gets the following 16.  Registers are as follows:&n; *&n; * Offsets 0-1 : Card ID&n; *&n; * Offset    2 : Mode enable register --&n; *                Bit    7 : Data Word width (1 = 16, 0 = 8)&n; *&t;&t;  Bit    6 : IRQ enable (1 = enabled)&n; *                Bits 5,4 : IRQ select&n; *                              0  0 : IRQ 3&n; *&t;&t;&t;        0  1 : IRQ 5&n; * &t;&t;&t;&t;1  0 : IRQ 7&n; *  &t;&t;&t;&t;1  1 : IRQ 9&n; *                Bits 3-1 : Base Address&n; *                           0  0  0 : &lt;disabled&gt;&n; * &t;&t;&t;     0  0  1 : 0x0240&n; *    &t;&t;&t;     0  1  0 : 0x0340&n; *     &t;&t;&t;     0  1  1 : 0x0400&n; * &t;&t;&t;     1  0  0 : 0x0420&n; * &t;&t;&t;     1  0  1 : 0x3240&n; * &t;&t;&t;     1  1  0 : 0x8240&n; * &t;&t;&t;     1  1  1 : 0xA240&n; *&t;&t;  Bit    0 : Card enable (1 = enabled)&n; *&n; * Offset    3 : DMA control register --&n; *                Bit    7 : DMA enable (1 = enabled)&n; *                Bits 6,5 : Preemt Count Select (transfers to complete after&n; *                            &squot;C01 has been preempted on MCA bus)&n; *                              0  0 : 0&n; *                              0  1 : 1&n; *                              1  0 : 3&n; *                              1  1 : 7&n; *  (all these wacky numbers; I&squot;m sure there&squot;s a reason somewhere)&n; *                Bit    4 : Fairness enable (1 = fair bus priority)&n; *                Bits 3-0 : Arbitration level (0-15 consecutive)&n; * &n; * Offset    4 : General purpose register&n; *                Bits 7-3 : User definable (here, 7,6 are SCSI ID)&n; *                Bits 2-0 : reserved&n; *&n; * Offset   10 : DMA decode register (used for IO based DMA; also can do&n; *                PIO through this port)&n; *&n; * Offset   12 : Status&n; *                Bits 7-2 : reserved&n; *                Bit    1 : DMA pending (1 = pending)&n; *                Bit    0 : IRQ pending (0 = pending)&n; *&n; * Exciting, huh?  &n; *&n; */
eof

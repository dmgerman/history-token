multiline_comment|/*&n; * Oktagon_esp.c -- Driver for bsc Oktagon&n; *&n; * Written by Carsten Pluntke 1998&n; *&n; * Based on cyber_esp.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_AMIGA) || defined(CONFIG_APUS)
DECL|macro|USE_BOTTOM_HALF
mdefine_line|#define USE_BOTTOM_HALF
macro_line|#endif
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;NCR53C9x.h&quot;
macro_line|#include &quot;oktagon_esp.h&quot;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#ifdef USE_BOTTOM_HALF
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/unistd.h&gt;
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
suffix:semicolon
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
suffix:semicolon
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
suffix:semicolon
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
id|vaddress
comma
r_int
id|length
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
id|esp
comma
id|__u32
id|vaddress
comma
r_int
id|length
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
id|esp
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
id|esp
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
id|esp
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
id|esp
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
id|esp
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
id|esp
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
suffix:semicolon
r_static
r_void
id|dma_irq_exit
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
suffix:semicolon
r_static
r_void
id|dma_invalidate
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
suffix:semicolon
r_static
r_void
id|dma_mmu_get_scsi_one
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
id|dma_mmu_get_scsi_sgl
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
id|dma_mmu_release_scsi_one
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
id|dma_mmu_release_scsi_sgl
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
id|dma_advance_sg
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|oktagon_notify_reboot
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|code
comma
r_void
op_star
id|x
)paren
suffix:semicolon
r_void
id|esp_bootup_reset
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
comma
r_struct
id|ESP_regs
op_star
id|eregs
)paren
suffix:semicolon
macro_line|#ifdef USE_BOTTOM_HALF
r_static
r_void
id|dma_commit
c_func
(paren
r_void
op_star
id|opaque
)paren
suffix:semicolon
r_int
id|oktag_to_io
c_func
(paren
r_int
op_star
id|paddr
comma
r_int
op_star
id|addr
comma
r_int
id|len
)paren
suffix:semicolon
r_int
id|oktag_from_io
c_func
(paren
r_int
op_star
id|addr
comma
r_int
op_star
id|paddr
comma
r_int
id|len
)paren
suffix:semicolon
r_static
id|DECLARE_WORK
c_func
(paren
id|tq_fake_dma
comma
id|dma_commit
comma
l_int|NULL
)paren
suffix:semicolon
DECL|macro|DMA_MAXTRANSFER
mdefine_line|#define DMA_MAXTRANSFER 0x8000
macro_line|#else
multiline_comment|/*&n; * No bottom half. Use transfer directly from IRQ. Find a narrow path&n; * between too much IRQ overhead and clogging the IRQ for too long.&n; */
DECL|macro|DMA_MAXTRANSFER
mdefine_line|#define DMA_MAXTRANSFER 0x1000
macro_line|#endif
DECL|variable|oktagon_notifier
r_static
r_struct
id|notifier_block
id|oktagon_notifier
op_assign
(brace
id|oktagon_notify_reboot
comma
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|paddress
r_static
r_int
op_star
id|paddress
suffix:semicolon
DECL|variable|address
r_static
r_int
op_star
id|address
suffix:semicolon
DECL|variable|len
r_static
r_int
id|len
suffix:semicolon
DECL|variable|dma_on
r_static
r_int
id|dma_on
suffix:semicolon
DECL|variable|direction
r_static
r_int
id|direction
suffix:semicolon
DECL|variable|current_esp
r_static
r_struct
id|NCR_ESP
op_star
id|current_esp
suffix:semicolon
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
multiline_comment|/* This is where all commands are put&n;&t;&t;&t;&t; * before they are trasfered to the ESP chip&n;&t;&t;&t;&t; * via PIO.&n;&t;&t;&t;&t; */
multiline_comment|/***************************************************************** Detection */
DECL|function|oktagon_esp_detect
r_int
id|oktagon_esp_detect
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
r_struct
id|zorro_dev
op_star
id|z
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
r_struct
id|ESP_regs
op_star
id|eregs
suffix:semicolon
r_while
c_loop
(paren
(paren
id|z
op_assign
id|zorro_find_device
c_func
(paren
id|ZORRO_PROD_BSC_OKTAGON_2008
comma
id|z
)paren
)paren
)paren
(brace
r_int
r_int
id|board
op_assign
id|z-&gt;resource.start
suffix:semicolon
r_if
c_cond
(paren
id|request_mem_region
c_func
(paren
id|board
op_plus
id|OKTAGON_ESP_ADDR
comma
r_sizeof
(paren
r_struct
id|ESP_regs
)paren
comma
l_string|&quot;NCR53C9x&quot;
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * It is a SCSI controller.&n;&t;&t; * Hardwire Host adapter to SCSI ID 7&n;&t;&t; */
id|address
op_assign
(paren
r_int
r_int
)paren
id|ZTWO_VADDR
c_func
(paren
id|board
)paren
suffix:semicolon
id|eregs
op_assign
(paren
r_struct
id|ESP_regs
op_star
)paren
(paren
id|address
op_plus
id|OKTAGON_ESP_ADDR
)paren
suffix:semicolon
multiline_comment|/* This line was 5 lines lower */
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
id|board
op_plus
id|OKTAGON_ESP_ADDR
)paren
suffix:semicolon
multiline_comment|/* we have to shift the registers only one bit for oktagon */
id|esp-&gt;shift
op_assign
l_int|1
suffix:semicolon
id|esp_write
c_func
(paren
id|eregs-&gt;esp_cfg1
comma
(paren
id|ESP_CONFIG1_PENABLE
op_or
l_int|7
)paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|esp_read
c_func
(paren
id|eregs-&gt;esp_cfg1
)paren
op_ne
(paren
id|ESP_CONFIG1_PENABLE
op_or
l_int|7
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Bail out if address did not hold data */
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
op_amp
id|dma_invalidate
suffix:semicolon
id|esp-&gt;dma_irq_entry
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;dma_irq_exit
op_assign
op_amp
id|dma_irq_exit
suffix:semicolon
id|esp-&gt;dma_led_on
op_assign
op_amp
id|dma_led_on
suffix:semicolon
id|esp-&gt;dma_led_off
op_assign
op_amp
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
id|esp-&gt;dma_mmu_get_scsi_one
op_assign
op_amp
id|dma_mmu_get_scsi_one
suffix:semicolon
id|esp-&gt;dma_mmu_get_scsi_sgl
op_assign
op_amp
id|dma_mmu_get_scsi_sgl
suffix:semicolon
id|esp-&gt;dma_mmu_release_scsi_one
op_assign
op_amp
id|dma_mmu_release_scsi_one
suffix:semicolon
id|esp-&gt;dma_mmu_release_scsi_sgl
op_assign
op_amp
id|dma_mmu_release_scsi_sgl
suffix:semicolon
id|esp-&gt;dma_advance_sg
op_assign
op_amp
id|dma_advance_sg
suffix:semicolon
multiline_comment|/* SCSI chip speed */
multiline_comment|/* Looking at the quartz of the SCSI board... */
id|esp-&gt;cfreq
op_assign
l_int|25000000
suffix:semicolon
multiline_comment|/* The DMA registers on the CyberStorm are mapped&n;&t;&t; * relative to the device (i.e. in the same Zorro&n;&t;&t; * I/O block).&n;&t;&t; */
id|esp-&gt;dregs
op_assign
(paren
r_void
op_star
)paren
(paren
id|address
op_plus
id|OKTAGON_DMA_ADDR
)paren
suffix:semicolon
id|paddress
op_assign
(paren
r_int
op_star
)paren
id|esp-&gt;dregs
suffix:semicolon
multiline_comment|/* ESP register base */
id|esp-&gt;eregs
op_assign
id|eregs
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
multiline_comment|/* Yes, the virtual address. See below. */
id|esp-&gt;esp_command_dvma
op_assign
(paren
id|__u32
)paren
id|cmd_buffer
suffix:semicolon
id|esp-&gt;irq
op_assign
id|IRQ_AMIGA_PORTS
suffix:semicolon
id|request_irq
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|esp_intr
comma
id|SA_SHIRQ
comma
l_string|&quot;BSC Oktagon SCSI&quot;
comma
id|esp-&gt;ehost
)paren
suffix:semicolon
multiline_comment|/* Figure out our scsi ID on the bus */
id|esp-&gt;scsi_id
op_assign
l_int|7
suffix:semicolon
multiline_comment|/* We don&squot;t have a differential SCSI-bus. */
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
l_string|&quot;ESP_Oktagon Driver 1.1&quot;
macro_line|#ifdef USE_BOTTOM_HALF
l_string|&quot; [BOTTOM_HALF]&quot;
macro_line|#else
l_string|&quot; [IRQ]&quot;
macro_line|#endif
l_string|&quot; registered.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ESP: Total of %d ESP hosts found, %d actually in use.&bslash;n&quot;
comma
id|nesps
comma
id|esps_in_use
)paren
suffix:semicolon
id|esps_running
op_assign
id|esps_in_use
suffix:semicolon
id|current_esp
op_assign
id|esp
suffix:semicolon
id|register_reboot_notifier
c_func
(paren
op_amp
id|oktagon_notifier
)paren
suffix:semicolon
r_return
id|esps_in_use
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * On certain configurations the SCSI equipment gets confused on reboot,&n; * so we have to reset it then.&n; */
r_static
r_int
DECL|function|oktagon_notify_reboot
id|oktagon_notify_reboot
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|code
comma
r_void
op_star
id|x
)paren
(brace
r_struct
id|NCR_ESP
op_star
id|esp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|code
op_eq
id|SYS_DOWN
op_logical_or
id|code
op_eq
id|SYS_HALT
)paren
op_logical_and
(paren
id|esp
op_assign
id|current_esp
)paren
)paren
(brace
id|esp_bootup_reset
c_func
(paren
id|esp
comma
id|esp-&gt;eregs
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|500
)paren
suffix:semicolon
multiline_comment|/* Settle time. Maybe unneccessary. */
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
macro_line|#ifdef USE_BOTTOM_HALF
multiline_comment|/*&n; * The bsc Oktagon controller has no real DMA, so we have to do the &squot;DMA&n; * transfer&squot; in the interrupt (Yikes!) or use a bottom half to not to clutter&n; * IRQ&squot;s for longer-than-good.&n; *&n; * FIXME&n; * BIG PROBLEM: &squot;len&squot; is usually the buffer length, not the expected length&n; * of the data. So DMA may finish prematurely, further reads lead to&n; * &squot;machine check&squot; on APUS systems (don&squot;t know about m68k systems, AmigaOS&n; * deliberately ignores the bus faults) and a normal copy-loop can&squot;t&n; * be exited prematurely just at the right moment by the dma_invalidate IRQ.&n; * So do it the hard way, write an own copier in assembler and&n; * catch the exception.&n; *                                     -- Carsten&n; */
DECL|function|dma_commit
r_static
r_void
id|dma_commit
c_func
(paren
r_void
op_star
id|opaque
)paren
(brace
r_int
id|wait
comma
id|len2
comma
id|pos
suffix:semicolon
r_struct
id|NCR_ESP
op_star
id|esp
suffix:semicolon
id|ESPDATA
c_func
(paren
(paren
l_string|&quot;Transfer: %ld bytes, Address 0x%08lX, Direction: %d&bslash;n&quot;
comma
id|len
comma
(paren
r_int
)paren
id|address
comma
id|direction
)paren
)paren
suffix:semicolon
id|dma_ints_off
c_func
(paren
id|current_esp
)paren
suffix:semicolon
id|pos
op_assign
l_int|0
suffix:semicolon
id|wait
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|direction
)paren
multiline_comment|/* write? (memory to device) */
(brace
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
id|len2
op_assign
id|oktag_to_io
c_func
(paren
id|paddress
comma
id|address
op_plus
id|pos
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len2
)paren
(brace
r_if
c_cond
(paren
id|wait
OG
l_int|1000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Expedited DMA exit (writing) %ld&bslash;n&quot;
comma
id|len
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|mdelay
c_func
(paren
id|wait
)paren
suffix:semicolon
id|wait
op_mul_assign
l_int|2
suffix:semicolon
)brace
id|pos
op_add_assign
id|len2
suffix:semicolon
id|len
op_sub_assign
id|len2
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
id|len2
op_assign
id|oktag_from_io
c_func
(paren
id|address
op_plus
id|pos
comma
id|paddress
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len2
)paren
(brace
r_if
c_cond
(paren
id|wait
OG
l_int|1000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Expedited DMA exit (reading) %ld&bslash;n&quot;
comma
id|len
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|mdelay
c_func
(paren
id|wait
)paren
suffix:semicolon
id|wait
op_mul_assign
l_int|2
suffix:semicolon
)brace
id|pos
op_add_assign
id|len2
suffix:semicolon
id|len
op_sub_assign
id|len2
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* to make esp-&gt;shift work */
id|esp
op_assign
id|current_esp
suffix:semicolon
macro_line|#if 0
id|len2
op_assign
(paren
id|esp_read
c_func
(paren
id|current_esp-&gt;eregs-&gt;esp_tclow
)paren
op_amp
l_int|0xff
)paren
op_or
(paren
(paren
id|esp_read
c_func
(paren
id|current_esp-&gt;eregs-&gt;esp_tcmed
)paren
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/*&n;     * Uh uh. If you see this, len and transfer count registers were out of&n;     * sync. That means really serious trouble.&n;     */
r_if
c_cond
(paren
id|len2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Eeeek!! Transfer count still %ld!&bslash;n&quot;
comma
id|len2
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;     * Normally we just need to exit and wait for the interrupt to come.&n;     * But at least one device (my Microtek ScanMaker 630) regularly mis-&n;     * calculates the bytes it should send which is really ugly because&n;     * it locks up the SCSI bus if not accounted for.&n;     */
r_if
c_cond
(paren
op_logical_neg
(paren
id|esp_read
c_func
(paren
id|current_esp-&gt;eregs-&gt;esp_status
)paren
op_amp
id|ESP_STAT_INTR
)paren
)paren
(brace
r_int
id|len
op_assign
l_int|100
suffix:semicolon
r_int
id|trash
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/*&n;       * Interrupt bit was not set. Either the device is just plain lazy&n;       * so we give it a 10 ms chance or...&n;       */
r_while
c_loop
(paren
id|len
op_decrement
op_logical_and
(paren
op_logical_neg
(paren
id|esp_read
c_func
(paren
id|current_esp-&gt;eregs-&gt;esp_status
)paren
op_amp
id|ESP_STAT_INTR
)paren
)paren
)paren
(brace
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|esp_read
c_func
(paren
id|current_esp-&gt;eregs-&gt;esp_status
)paren
op_amp
id|ESP_STAT_INTR
)paren
)paren
(brace
multiline_comment|/*&n;&t; * So we think that the transfer count is out of sync. Since we&n;&t; * have all we want we are happy and can ditch the trash.&n;&t; */
id|len
op_assign
id|DMA_MAXTRANSFER
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
op_logical_and
(paren
op_logical_neg
(paren
id|esp_read
c_func
(paren
id|current_esp-&gt;eregs-&gt;esp_status
)paren
op_amp
id|ESP_STAT_INTR
)paren
)paren
)paren
(brace
id|oktag_from_io
c_func
(paren
id|trash
comma
id|paddress
comma
l_int|2
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|esp_read
c_func
(paren
id|current_esp-&gt;eregs-&gt;esp_status
)paren
op_amp
id|ESP_STAT_INTR
)paren
)paren
(brace
multiline_comment|/*&n;           * Things really have gone wrong. If we leave the system in that&n;           * state, the SCSI bus is locked forever. I hope that this will&n;           * turn the system in a more or less running state.&n;           */
id|printk
c_func
(paren
l_string|&quot;Device is bolixed, trying bus reset...&bslash;n&quot;
)paren
suffix:semicolon
id|esp_bootup_reset
c_func
(paren
id|current_esp
comma
id|current_esp-&gt;eregs
)paren
suffix:semicolon
)brace
)brace
)brace
id|ESPDATA
c_func
(paren
(paren
l_string|&quot;Transfer_finale: do_data_finale should come&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
id|dma_on
op_assign
l_int|0
suffix:semicolon
id|dma_ints_on
c_func
(paren
id|current_esp
)paren
suffix:semicolon
)brace
macro_line|#endif
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
multiline_comment|/* Since the CyberStorm DMA is fully dedicated to the ESP chip,&n;&t; * the number of bytes sent (to the ESP chip) equals the number&n;&t; * of bytes in the FIFO - there is no buffering in the DMA controller.&n;&t; * XXXX Do I read this right? It is from host to ESP, right?&n;&t; */
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
id|DMA_MAXTRANSFER
)paren
(brace
id|sz
op_assign
id|DMA_MAXTRANSFER
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
)brace
multiline_comment|/*&n; * What the f$@&amp; is this?&n; *&n; * Some SCSI devices (like my Microtek ScanMaker 630 scanner) want to transfer&n; * more data than requested. How much? Dunno. So ditch the bogus data into&n; * the sink, hoping the device will advance to the next phase sooner or later.&n; *&n; *                         -- Carsten&n; */
DECL|variable|oktag_eva_buffer
r_static
r_int
id|oktag_eva_buffer
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* The data sink */
DECL|function|oktag_check_dma
r_static
r_void
id|oktag_check_dma
c_func
(paren
r_void
)paren
(brace
r_struct
id|NCR_ESP
op_star
id|esp
suffix:semicolon
id|esp
op_assign
id|current_esp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
(brace
id|address
op_assign
id|oktag_eva_buffer
suffix:semicolon
id|len
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* esp_do_data sets them to zero like len */
id|esp_write
c_func
(paren
id|current_esp-&gt;eregs-&gt;esp_tclow
comma
l_int|2
)paren
suffix:semicolon
id|esp_write
c_func
(paren
id|current_esp-&gt;eregs-&gt;esp_tcmed
comma
l_int|0
)paren
suffix:semicolon
)brace
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
id|vaddress
comma
r_int
id|length
)paren
(brace
multiline_comment|/* Zorro is noncached, everything else done using processor. */
multiline_comment|/* cache_clear(addr, length); */
r_if
c_cond
(paren
id|dma_on
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;dma_init_read while dma process is initialized/running!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|direction
op_assign
l_int|0
suffix:semicolon
id|address
op_assign
(paren
r_int
op_star
)paren
id|vaddress
suffix:semicolon
id|current_esp
op_assign
id|esp
suffix:semicolon
id|len
op_assign
id|length
suffix:semicolon
id|oktag_check_dma
c_func
(paren
)paren
suffix:semicolon
id|dma_on
op_assign
l_int|1
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
id|vaddress
comma
r_int
id|length
)paren
(brace
multiline_comment|/* cache_push(addr, length); */
r_if
c_cond
(paren
id|dma_on
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;dma_init_write while dma process is initialized/running!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|direction
op_assign
l_int|1
suffix:semicolon
id|address
op_assign
(paren
r_int
op_star
)paren
id|vaddress
suffix:semicolon
id|current_esp
op_assign
id|esp
suffix:semicolon
id|len
op_assign
id|length
suffix:semicolon
id|oktag_check_dma
c_func
(paren
)paren
suffix:semicolon
id|dma_on
op_assign
l_int|1
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
id|disable_irq
c_func
(paren
id|esp-&gt;irq
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
id|enable_irq
c_func
(paren
id|esp-&gt;irq
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
multiline_comment|/* It&squot;s important to check the DMA IRQ bit in the correct way! */
r_return
(paren
id|esp_read
c_func
(paren
id|esp-&gt;eregs-&gt;esp_status
)paren
op_amp
id|ESP_STAT_INTR
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
)brace
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
r_return
(paren
(paren
id|custom.intenar
)paren
op_amp
id|IF_PORTS
)paren
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
multiline_comment|/* On the Sparc, DMA_ST_WRITE means &quot;move data from device to memory&quot;&n;&t; * so when (write) is true, it actually means READ!&n;&t; */
r_if
c_cond
(paren
id|write
)paren
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
r_else
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
)brace
multiline_comment|/*&n; * IRQ entry when DMA transfer is ready to be started&n; */
DECL|function|dma_irq_exit
r_static
r_void
id|dma_irq_exit
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
(brace
macro_line|#ifdef USE_BOTTOM_HALF
r_if
c_cond
(paren
id|dma_on
)paren
(brace
id|schedule_work
c_func
(paren
op_amp
id|tq_fake_dma
)paren
suffix:semicolon
)brace
macro_line|#else
r_while
c_loop
(paren
id|len
op_logical_and
op_logical_neg
id|dma_irq_p
c_func
(paren
id|esp
)paren
)paren
(brace
r_if
c_cond
(paren
id|direction
)paren
(brace
op_star
id|paddress
op_assign
op_star
id|address
op_increment
suffix:semicolon
)brace
r_else
op_star
id|address
op_increment
op_assign
op_star
id|paddress
suffix:semicolon
id|len
op_sub_assign
(paren
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
)brace
id|len
op_assign
l_int|0
suffix:semicolon
id|dma_on
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * IRQ entry when DMA has just finished&n; */
DECL|function|dma_invalidate
r_static
r_void
id|dma_invalidate
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
(brace
)brace
multiline_comment|/*&n; * Since the processor does the data transfer we have to use the custom&n; * mmu interface to pass the virtual address, not the physical.&n; */
DECL|function|dma_mmu_get_scsi_one
r_void
id|dma_mmu_get_scsi_one
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
id|sp-&gt;SCp.have_data_in
op_assign
(paren
r_int
)paren
id|sp-&gt;SCp.ptr
op_assign
id|sp-&gt;request_buffer
suffix:semicolon
)brace
DECL|function|dma_mmu_get_scsi_sgl
r_void
id|dma_mmu_get_scsi_sgl
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
id|sp-&gt;SCp.ptr
op_assign
id|page_address
c_func
(paren
id|sp-&gt;SCp.buffer-&gt;page
)paren
op_plus
id|sp-&gt;SCp.buffer-&gt;offset
suffix:semicolon
)brace
DECL|function|dma_mmu_release_scsi_one
r_void
id|dma_mmu_release_scsi_one
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
)brace
DECL|function|dma_mmu_release_scsi_sgl
r_void
id|dma_mmu_release_scsi_sgl
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
)brace
DECL|function|dma_advance_sg
r_void
id|dma_advance_sg
c_func
(paren
id|Scsi_Cmnd
op_star
id|sp
)paren
(brace
id|sp-&gt;SCp.ptr
op_assign
id|page_address
c_func
(paren
id|sp-&gt;SCp.buffer-&gt;page
)paren
op_plus
id|sp-&gt;SCp.buffer-&gt;offset
suffix:semicolon
)brace
DECL|macro|HOSTS_C
mdefine_line|#define HOSTS_C
macro_line|#include &quot;oktagon_esp.h&quot;
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
id|SCSI_OKTAGON_ESP
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
DECL|function|oktagon_esp_release
r_int
id|oktagon_esp_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
(brace
macro_line|#ifdef MODULE
r_int
r_int
id|address
op_assign
(paren
r_int
r_int
)paren
(paren
(paren
r_struct
id|NCR_ESP
op_star
)paren
id|instance-&gt;hostdata
)paren
op_member_access_from_pointer
id|edev
suffix:semicolon
id|esp_release
c_func
(paren
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|address
comma
r_sizeof
(paren
r_struct
id|ESP_regs
)paren
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|esp_intr
)paren
suffix:semicolon
id|unregister_reboot_notifier
c_func
(paren
op_amp
id|oktagon_notifier
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof

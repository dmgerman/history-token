multiline_comment|/* sun3x_esp.c:  EnhancedScsiProcessor Sun3x SCSI driver code.&n; *&n; * (C) 1999 Thomas Bogendoerfer (tsbogend@alpha.franken.de)&n; *&n; * Based on David S. Miller&squot;s esp driver&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;NCR53C9x.h&quot;
macro_line|#include &quot;sun3x_esp.h&quot;
macro_line|#include &lt;asm/sun3x.h&gt;
macro_line|#include &lt;asm/dvma.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
r_extern
r_struct
id|NCR_ESP
op_star
id|espchain
suffix:semicolon
r_static
r_void
id|dma_barrier
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
id|dma_drain
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
id|dma_poll
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
comma
r_int
r_char
op_star
id|vaddr
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
id|dma_reset
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
id|dma_mmu_get_scsi_one
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
id|dma_mmu_get_scsi_sgl
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
id|dma_mmu_release_scsi_one
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
id|dma_mmu_release_scsi_sgl
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
id|dma_advance_sg
(paren
id|Scsi_Cmnd
op_star
id|sp
)paren
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
multiline_comment|/* This is where all commands are put&n;                                 * before they are trasfered to the ESP chip&n;                                 * via PIO.&n;                                 */
multiline_comment|/* Detecting ESP chips on the machine.  This is the simple and easy&n; * version.&n; */
DECL|function|sun3x_esp_detect
r_int
id|sun3x_esp_detect
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
id|ConfigDev
op_star
id|esp_dev
suffix:semicolon
id|esp_dev
op_assign
l_int|0
suffix:semicolon
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
id|esp_dev
)paren
suffix:semicolon
multiline_comment|/* Do command transfer with DMA */
id|esp-&gt;do_pio_cmds
op_assign
l_int|0
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
op_amp
id|dma_barrier
suffix:semicolon
id|esp-&gt;dma_invalidate
op_assign
op_amp
id|dma_invalidate
suffix:semicolon
id|esp-&gt;dma_drain
op_assign
op_amp
id|dma_drain
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
l_int|0
suffix:semicolon
id|esp-&gt;dma_led_off
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;dma_poll
op_assign
op_amp
id|dma_poll
suffix:semicolon
id|esp-&gt;dma_reset
op_assign
op_amp
id|dma_reset
suffix:semicolon
multiline_comment|/* virtual DMA functions */
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
id|esp-&gt;cfreq
op_assign
l_int|20000000
suffix:semicolon
id|esp-&gt;eregs
op_assign
(paren
r_struct
id|ESP_regs
op_star
)paren
(paren
id|SUN3X_ESP_BASE
)paren
suffix:semicolon
id|esp-&gt;dregs
op_assign
(paren
r_void
op_star
)paren
id|SUN3X_ESP_DMA
suffix:semicolon
macro_line|#if 0
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
id|dvma_map
c_func
(paren
(paren
r_int
r_int
)paren
id|cmd_buffer
comma
r_sizeof
(paren
id|cmd_buffer
)paren
)paren
suffix:semicolon
macro_line|#else
id|esp-&gt;esp_command
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
id|dvma_malloc
c_func
(paren
id|DVMA_PAGE_SIZE
)paren
suffix:semicolon
id|esp-&gt;esp_command_dvma
op_assign
id|dvma_vtob
c_func
(paren
(paren
r_int
r_int
)paren
id|esp-&gt;esp_command
)paren
suffix:semicolon
macro_line|#endif
id|esp-&gt;irq
op_assign
l_int|2
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
id|SA_INTERRUPT
comma
l_string|&quot;SUN3X SCSI&quot;
comma
id|esp-&gt;ehost
)paren
)paren
(brace
id|esp_deallocate
c_func
(paren
id|esp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|esp-&gt;scsi_id
op_assign
l_int|7
suffix:semicolon
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
multiline_comment|/* for reasons beyond my knowledge (and which should likely be fixed)&n; &t;   sync mode doesn&squot;t work on a 3/80 at 5mhz.  but it does at 4. */
id|esp-&gt;sync_defp
op_assign
l_int|0x3f
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
r_return
id|esps_in_use
suffix:semicolon
)brace
DECL|function|dma_do_drain
r_static
r_void
id|dma_do_drain
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
(brace
r_struct
id|sparc_dma_registers
op_star
id|dregs
op_assign
(paren
r_struct
id|sparc_dma_registers
op_star
)paren
id|esp-&gt;dregs
suffix:semicolon
r_int
id|count
op_assign
l_int|500000
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dregs-&gt;cond_reg
op_amp
id|DMA_PEND_READ
)paren
op_logical_and
(paren
op_decrement
id|count
OG
l_int|0
)paren
)paren
(brace
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s:%d timeout CSR %08lx&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|dregs-&gt;cond_reg
)paren
suffix:semicolon
)brace
id|dregs-&gt;cond_reg
op_or_assign
id|DMA_FIFO_STDRAIN
suffix:semicolon
id|count
op_assign
l_int|500000
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dregs-&gt;cond_reg
op_amp
id|DMA_FIFO_ISDRAIN
)paren
op_logical_and
(paren
op_decrement
id|count
OG
l_int|0
)paren
)paren
(brace
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s:%d timeout CSR %08lx&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|dregs-&gt;cond_reg
)paren
suffix:semicolon
)brace
)brace
DECL|function|dma_barrier
r_static
r_void
id|dma_barrier
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
(brace
r_struct
id|sparc_dma_registers
op_star
id|dregs
op_assign
(paren
r_struct
id|sparc_dma_registers
op_star
)paren
id|esp-&gt;dregs
suffix:semicolon
r_int
id|count
op_assign
l_int|500000
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dregs-&gt;cond_reg
op_amp
id|DMA_PEND_READ
)paren
op_logical_and
(paren
op_decrement
id|count
OG
l_int|0
)paren
)paren
(brace
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s:%d timeout CSR %08lx&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|dregs-&gt;cond_reg
)paren
suffix:semicolon
)brace
id|dregs-&gt;cond_reg
op_and_assign
op_complement
(paren
id|DMA_ENABLE
)paren
suffix:semicolon
)brace
multiline_comment|/* This uses various DMA csr fields and the fifo flags count value to&n; * determine how many bytes were successfully sent/received by the ESP.&n; */
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
r_struct
id|sparc_dma_registers
op_star
id|dregs
op_assign
(paren
r_struct
id|sparc_dma_registers
op_star
)paren
id|esp-&gt;dregs
suffix:semicolon
r_int
id|rval
op_assign
id|dregs-&gt;st_addr
op_minus
id|esp-&gt;esp_command_dvma
suffix:semicolon
r_return
id|rval
op_minus
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
r_return
id|sp-&gt;SCp.this_residual
suffix:semicolon
)brace
DECL|function|dma_drain
r_static
r_void
id|dma_drain
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
(brace
r_struct
id|sparc_dma_registers
op_star
id|dregs
op_assign
(paren
r_struct
id|sparc_dma_registers
op_star
)paren
id|esp-&gt;dregs
suffix:semicolon
r_int
id|count
op_assign
l_int|500000
suffix:semicolon
r_if
c_cond
(paren
id|dregs-&gt;cond_reg
op_amp
id|DMA_FIFO_ISDRAIN
)paren
(brace
id|dregs-&gt;cond_reg
op_or_assign
id|DMA_FIFO_STDRAIN
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dregs-&gt;cond_reg
op_amp
id|DMA_FIFO_ISDRAIN
)paren
op_logical_and
(paren
op_decrement
id|count
OG
l_int|0
)paren
)paren
(brace
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s:%d timeout CSR %08lx&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|dregs-&gt;cond_reg
)paren
suffix:semicolon
)brace
)brace
)brace
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
r_struct
id|sparc_dma_registers
op_star
id|dregs
op_assign
(paren
r_struct
id|sparc_dma_registers
op_star
)paren
id|esp-&gt;dregs
suffix:semicolon
id|__u32
id|tmp
suffix:semicolon
r_int
id|count
op_assign
l_int|500000
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
id|tmp
op_assign
id|dregs-&gt;cond_reg
)paren
op_amp
id|DMA_PEND_READ
)paren
op_logical_and
(paren
op_decrement
id|count
OG
l_int|0
)paren
)paren
(brace
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s:%d timeout CSR %08lx&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|dregs-&gt;cond_reg
)paren
suffix:semicolon
)brace
id|dregs-&gt;cond_reg
op_assign
id|tmp
op_or
id|DMA_FIFO_INV
suffix:semicolon
id|dregs-&gt;cond_reg
op_and_assign
op_complement
id|DMA_FIFO_INV
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
r_struct
id|sparc_dma_registers
op_star
id|dregs
op_assign
(paren
r_struct
id|sparc_dma_registers
op_star
)paren
id|esp-&gt;dregs
suffix:semicolon
id|ESPLOG
c_func
(paren
(paren
l_string|&quot;esp%d: dma -- cond_reg&lt;%08lx&gt; addr&lt;%08lx&gt;&bslash;n&quot;
comma
id|esp-&gt;esp_id
comma
id|dregs-&gt;cond_reg
comma
id|dregs-&gt;st_addr
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
id|vaddress
comma
r_int
id|length
)paren
(brace
r_struct
id|sparc_dma_registers
op_star
id|dregs
op_assign
(paren
r_struct
id|sparc_dma_registers
op_star
)paren
id|esp-&gt;dregs
suffix:semicolon
id|dregs-&gt;st_addr
op_assign
id|vaddress
suffix:semicolon
id|dregs-&gt;cond_reg
op_or_assign
(paren
id|DMA_ST_WRITE
op_or
id|DMA_ENABLE
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
id|vaddress
comma
r_int
id|length
)paren
(brace
r_struct
id|sparc_dma_registers
op_star
id|dregs
op_assign
(paren
r_struct
id|sparc_dma_registers
op_star
)paren
id|esp-&gt;dregs
suffix:semicolon
multiline_comment|/* Set up the DMA counters */
id|dregs-&gt;st_addr
op_assign
id|vaddress
suffix:semicolon
id|dregs-&gt;cond_reg
op_assign
(paren
(paren
id|dregs-&gt;cond_reg
op_amp
op_complement
(paren
id|DMA_ST_WRITE
)paren
)paren
op_or
id|DMA_ENABLE
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
id|DMA_INTSOFF
c_func
(paren
(paren
r_struct
id|sparc_dma_registers
op_star
)paren
id|esp-&gt;dregs
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
id|DMA_INTSON
c_func
(paren
(paren
r_struct
id|sparc_dma_registers
op_star
)paren
id|esp-&gt;dregs
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
r_return
id|DMA_IRQ_P
c_func
(paren
(paren
r_struct
id|sparc_dma_registers
op_star
)paren
id|esp-&gt;dregs
)paren
suffix:semicolon
)brace
DECL|function|dma_poll
r_static
r_void
id|dma_poll
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
comma
r_int
r_char
op_star
id|vaddr
)paren
(brace
r_int
id|count
op_assign
l_int|50
suffix:semicolon
id|dma_do_drain
c_func
(paren
id|esp
)paren
suffix:semicolon
multiline_comment|/* Wait till the first bits settle. */
r_while
c_loop
(paren
(paren
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|vaddr
op_eq
l_int|0xff
)paren
op_logical_and
(paren
op_decrement
id|count
OG
l_int|0
)paren
)paren
(brace
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
(brace
singleline_comment|//&t;&t;printk(&quot;%s:%d timeout expire (data %02x)&bslash;n&quot;, __FILE__, __LINE__,
singleline_comment|//&t;&t;       esp_read(esp-&gt;eregs-&gt;esp_fdata));
singleline_comment|//mach_halt();
id|vaddr
(braket
l_int|0
)braket
op_assign
id|esp_read
c_func
(paren
id|esp-&gt;eregs-&gt;esp_fdata
)paren
suffix:semicolon
id|vaddr
(braket
l_int|1
)braket
op_assign
id|esp_read
c_func
(paren
id|esp-&gt;eregs-&gt;esp_fdata
)paren
suffix:semicolon
)brace
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
(paren
r_struct
id|sparc_dma_registers
op_star
)paren
id|esp-&gt;dregs
)paren
op_member_access_from_pointer
id|cond_reg
op_amp
id|DMA_INT_ENAB
)paren
suffix:semicolon
)brace
multiline_comment|/* Resetting various pieces of the ESP scsi driver chipset/buses. */
DECL|function|dma_reset
r_static
r_void
id|dma_reset
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
(brace
r_struct
id|sparc_dma_registers
op_star
id|dregs
op_assign
(paren
r_struct
id|sparc_dma_registers
op_star
)paren
id|esp-&gt;dregs
suffix:semicolon
multiline_comment|/* Punt the DVMA into a known state. */
id|dregs-&gt;cond_reg
op_or_assign
id|DMA_RST_SCSI
suffix:semicolon
id|dregs-&gt;cond_reg
op_and_assign
op_complement
(paren
id|DMA_RST_SCSI
)paren
suffix:semicolon
id|DMA_INTSON
c_func
(paren
id|dregs
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
r_struct
id|sparc_dma_registers
op_star
id|dregs
op_assign
(paren
r_struct
id|sparc_dma_registers
op_star
)paren
id|esp-&gt;dregs
suffix:semicolon
r_int
r_int
id|nreg
op_assign
id|dregs-&gt;cond_reg
suffix:semicolon
singleline_comment|//&t;printk(&quot;dma_setup %c addr %08x cnt %08x&bslash;n&quot;,
singleline_comment|//&t;       write ? &squot;W&squot; : &squot;R&squot;, addr, count);
id|dma_do_drain
c_func
(paren
id|esp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
)paren
(brace
id|nreg
op_or_assign
id|DMA_ST_WRITE
suffix:semicolon
)brace
r_else
(brace
id|nreg
op_and_assign
op_complement
(paren
id|DMA_ST_WRITE
)paren
suffix:semicolon
)brace
id|nreg
op_or_assign
id|DMA_ENABLE
suffix:semicolon
id|dregs-&gt;cond_reg
op_assign
id|nreg
suffix:semicolon
id|dregs-&gt;st_addr
op_assign
id|addr
suffix:semicolon
)brace
DECL|function|dma_mmu_get_scsi_one
r_static
r_void
id|dma_mmu_get_scsi_one
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
id|dvma_map
c_func
(paren
(paren
r_int
r_int
)paren
id|sp-&gt;SCp.buffer
comma
id|sp-&gt;SCp.this_residual
)paren
suffix:semicolon
id|sp-&gt;SCp.ptr
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|sp-&gt;SCp.have_data_in
)paren
suffix:semicolon
)brace
DECL|function|dma_mmu_get_scsi_sgl
r_static
r_void
id|dma_mmu_get_scsi_sgl
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
id|sz
op_assign
id|sp-&gt;SCp.buffers_residual
suffix:semicolon
r_struct
id|scatterlist
op_star
id|sg
op_assign
id|sp-&gt;SCp.buffer
suffix:semicolon
r_while
c_loop
(paren
id|sz
op_ge
l_int|0
)paren
(brace
id|sg
(braket
id|sz
)braket
dot
id|dvma_address
op_assign
id|dvma_map
c_func
(paren
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|sg
(braket
id|sz
)braket
dot
id|page
)paren
op_plus
id|sg
(braket
id|sz
)braket
dot
id|offset
comma
id|sg
(braket
id|sz
)braket
dot
id|length
)paren
suffix:semicolon
id|sz
op_decrement
suffix:semicolon
)brace
id|sp-&gt;SCp.ptr
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|sp-&gt;SCp.buffer-&gt;dvma_address
)paren
suffix:semicolon
)brace
DECL|function|dma_mmu_release_scsi_one
r_static
r_void
id|dma_mmu_release_scsi_one
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
id|dvma_unmap
c_func
(paren
(paren
r_char
op_star
)paren
id|sp-&gt;SCp.have_data_in
)paren
suffix:semicolon
)brace
DECL|function|dma_mmu_release_scsi_sgl
r_static
r_void
id|dma_mmu_release_scsi_sgl
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
id|sz
op_assign
id|sp-&gt;use_sg
op_minus
l_int|1
suffix:semicolon
r_struct
id|scatterlist
op_star
id|sg
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|sp-&gt;buffer
suffix:semicolon
r_while
c_loop
(paren
id|sz
op_ge
l_int|0
)paren
(brace
id|dvma_unmap
c_func
(paren
(paren
r_char
op_star
)paren
id|sg
(braket
id|sz
)braket
dot
id|dvma_address
)paren
suffix:semicolon
id|sz
op_decrement
suffix:semicolon
)brace
)brace
DECL|function|dma_advance_sg
r_static
r_void
id|dma_advance_sg
(paren
id|Scsi_Cmnd
op_star
id|sp
)paren
(brace
id|sp-&gt;SCp.ptr
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|sp-&gt;SCp.buffer-&gt;dvma_address
)paren
suffix:semicolon
)brace
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
id|SCSI_SUN3X_ESP
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof

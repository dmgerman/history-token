multiline_comment|/*&n; * jazz_esp.c: Driver for SCSI chip on Mips Magnum Boards (JAZZ architecture)&n; *&n; * Copyright (C) 1997 Thomas Bogendoerfer (tsbogend@alpha.franken.de)&n; *&n; * jazz_esp is based on David S. Miller&squot;s ESP driver and cyber_esp&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &quot;NCR53C9x.h&quot;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
macro_line|#include &lt;asm/jazzdma.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
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
DECL|function|jazz_esp_detect
r_int
id|jazz_esp_detect
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
multiline_comment|/*&n;     * first assumption it is there:-)&n;     */
r_if
c_cond
(paren
l_int|1
)paren
(brace
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
id|esp-&gt;dma_poll
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;dma_reset
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;dma_led_off
op_assign
op_amp
id|dma_led_off
suffix:semicolon
id|esp-&gt;dma_led_on
op_assign
op_amp
id|dma_led_on
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
l_int|40000000
suffix:semicolon
multiline_comment|/* &n;&t; * we don&squot;t give the address of DMA channel, but the number&n;&t; * of DMA channel, so we can use the jazz DMA functions&n;&t; * &n;&t; */
id|esp-&gt;dregs
op_assign
id|JAZZ_SCSI_DMA
suffix:semicolon
multiline_comment|/* ESP register base */
id|esp-&gt;eregs
op_assign
(paren
r_struct
id|ESP_regs
op_star
)paren
(paren
id|JAZZ_SCSI_BASE
)paren
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
multiline_comment|/* get virtual dma address for command buffer */
id|esp-&gt;esp_command_dvma
op_assign
id|vdma_alloc
c_func
(paren
id|PHYSADDR
c_func
(paren
id|cmd_buffer
)paren
comma
r_sizeof
(paren
id|cmd_buffer
)paren
)paren
suffix:semicolon
id|esp-&gt;irq
op_assign
id|JAZZ_SCSI_IRQ
suffix:semicolon
id|request_irq
c_func
(paren
id|JAZZ_SCSI_IRQ
comma
id|esp_intr
comma
id|SA_INTERRUPT
comma
l_string|&quot;JAZZ SCSI&quot;
comma
id|esp-&gt;ehost
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME, look if the scsi id is available from NVRAM&n;&t; */
id|esp-&gt;scsi_id
op_assign
l_int|7
suffix:semicolon
multiline_comment|/* Check for differential SCSI-bus */
multiline_comment|/* What is this stuff? */
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jazz_esp_release
r_static
r_int
id|jazz_esp_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
r_if
c_cond
(paren
id|shost-&gt;irq
)paren
id|free_irq
c_func
(paren
id|shost-&gt;irq
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shost-&gt;dma_channel
op_ne
l_int|0xff
)paren
id|free_dma
c_func
(paren
id|shost-&gt;dma_channel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shost-&gt;io_port
op_logical_and
id|shost-&gt;n_io_port
)paren
id|release_region
c_func
(paren
id|shost-&gt;io_port
comma
id|shost-&gt;n_io_port
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|shost
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
multiline_comment|/*&n;     * maximum DMA size is 1MB&n;     */
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
l_int|0x100000
)paren
(brace
id|sz
op_assign
l_int|0x100000
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
id|ESPLOG
c_func
(paren
(paren
l_string|&quot;esp%d: dma -- enable &lt;%08x&gt; residue &lt;%08x&bslash;n&quot;
comma
id|esp-&gt;esp_id
comma
id|vdma_get_enable
c_func
(paren
(paren
r_int
)paren
id|esp-&gt;dregs
)paren
comma
id|vdma_get_residue
c_func
(paren
(paren
r_int
)paren
id|esp-&gt;dregs
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
id|vaddress
comma
r_int
id|length
)paren
(brace
id|dma_cache_wback_inv
(paren
(paren
r_int
r_int
)paren
id|phys_to_virt
c_func
(paren
id|vdma_log2phys
c_func
(paren
id|vaddress
)paren
)paren
comma
id|length
)paren
suffix:semicolon
id|vdma_disable
(paren
(paren
r_int
)paren
id|esp-&gt;dregs
)paren
suffix:semicolon
id|vdma_set_mode
(paren
(paren
r_int
)paren
id|esp-&gt;dregs
comma
id|DMA_MODE_READ
)paren
suffix:semicolon
id|vdma_set_addr
(paren
(paren
r_int
)paren
id|esp-&gt;dregs
comma
id|vaddress
)paren
suffix:semicolon
id|vdma_set_count
(paren
(paren
r_int
)paren
id|esp-&gt;dregs
comma
id|length
)paren
suffix:semicolon
id|vdma_enable
(paren
(paren
r_int
)paren
id|esp-&gt;dregs
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
id|dma_cache_wback_inv
(paren
(paren
r_int
r_int
)paren
id|phys_to_virt
c_func
(paren
id|vdma_log2phys
c_func
(paren
id|vaddress
)paren
)paren
comma
id|length
)paren
suffix:semicolon
id|vdma_disable
(paren
(paren
r_int
)paren
id|esp-&gt;dregs
)paren
suffix:semicolon
id|vdma_set_mode
(paren
(paren
r_int
)paren
id|esp-&gt;dregs
comma
id|DMA_MODE_WRITE
)paren
suffix:semicolon
id|vdma_set_addr
(paren
(paren
r_int
)paren
id|esp-&gt;dregs
comma
id|vaddress
)paren
suffix:semicolon
id|vdma_set_count
(paren
(paren
r_int
)paren
id|esp-&gt;dregs
comma
id|length
)paren
suffix:semicolon
id|vdma_enable
(paren
(paren
r_int
)paren
id|esp-&gt;dregs
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
r_int
id|enable
op_assign
id|vdma_get_enable
c_func
(paren
(paren
r_int
)paren
id|esp-&gt;dregs
)paren
suffix:semicolon
r_return
(paren
id|enable
op_amp
id|R4030_CHNL_ENABLE
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
multiline_comment|/* &n;     * On the Sparc, DMA_ST_WRITE means &quot;move data from device to memory&quot;&n;     * so when (write) is true, it actually means READ!&n;     */
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
id|vdma_alloc
c_func
(paren
id|PHYSADDR
c_func
(paren
id|sp-&gt;SCp.buffer
)paren
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
id|mmu_sglist
op_star
id|sg
op_assign
(paren
r_struct
id|mmu_sglist
op_star
)paren
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
id|dvma_addr
op_assign
id|vdma_alloc
c_func
(paren
id|PHYSADDR
c_func
(paren
id|sg
(braket
id|sz
)braket
dot
id|addr
)paren
comma
id|sg
(braket
id|sz
)braket
dot
id|len
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
id|vdma_free
c_func
(paren
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
id|mmu_sglist
op_star
id|sg
op_assign
(paren
r_struct
id|mmu_sglist
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
id|vdma_free
c_func
(paren
id|sg
(braket
id|sz
)braket
dot
id|dvma_addr
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
DECL|macro|JAZZ_HDC_LED
mdefine_line|#define JAZZ_HDC_LED   0xe000d100 /* FIXME, find correct address */
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
macro_line|#if 0    
op_star
(paren
r_int
r_char
op_star
)paren
id|JAZZ_HDC_LED
op_assign
l_int|0
suffix:semicolon
macro_line|#endif    
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
macro_line|#if 0    
op_star
(paren
r_int
r_char
op_star
)paren
id|JAZZ_HDC_LED
op_assign
l_int|1
suffix:semicolon
macro_line|#endif    
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
l_string|&quot;jazz_esp&quot;
comma
dot
id|proc_info
op_assign
op_amp
id|esp_proc_info
comma
dot
id|name
op_assign
l_string|&quot;ESP 100/100a/200&quot;
comma
dot
id|detect
op_assign
id|jazz_esp_detect
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
id|jazz_esp_release
comma
dot
id|info
op_assign
id|esp_info
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
eof

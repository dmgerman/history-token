multiline_comment|/*&n; * dec_esp.c: Driver for SCSI chips on IOASIC based TURBOchannel DECstations&n; *            and TURBOchannel PMAZ-A cards&n; *&n; * TURBOchannel changes by Harald Koerfgen&n; * PMAZ-A support by David Airlie&n; *&n; * based on jazz_esp.c:&n; * Copyright (C) 1997 Thomas Bogendoerfer (tsbogend@alpha.franken.de)&n; *&n; * jazz_esp is based on David S. Miller&squot;s ESP driver and cyber_esp&n; *&n; * 20000819 - Small PMAZ-AA fixes by Florian Lohoff &lt;flo@rfc822.org&gt;&n; *            Be warned the PMAZ-AA works currently as a single card.&n; *            Dont try to put multiple cards in one machine - They are&n; *            both detected but it may crash under high load garbling your&n; *            data.&n; * 20001005&t;- Initialization fixes for 2.4.0-test9&n; * &t;&t;&t;  Florian Lohoff &lt;flo@rfc822.org&gt;&n; */
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
macro_line|#include &lt;asm/dec/tc.h&gt;
macro_line|#include &lt;asm/dec/interrupts.h&gt;
macro_line|#include &lt;asm/dec/ioasic_addrs.h&gt;
macro_line|#include &lt;asm/dec/ioasic_ints.h&gt;
macro_line|#include &lt;asm/dec/machtype.h&gt;
DECL|macro|DEC_SCSI_SREG
mdefine_line|#define DEC_SCSI_SREG 0
DECL|macro|DEC_SCSI_DMAREG
mdefine_line|#define DEC_SCSI_DMAREG 0x40000
DECL|macro|DEC_SCSI_SRAM
mdefine_line|#define DEC_SCSI_SRAM 0x80000
DECL|macro|DEC_SCSI_DIAG
mdefine_line|#define DEC_SCSI_DIAG 0xC0000
multiline_comment|/*&n; * Once upon a time the pmaz code used to be working but&n; * it hasn&squot;t been maintained for quite some time.&n; * It isn&squot;t working anymore but I&squot;ll leave here as a&n; * starting point. #define this an be prepared for tons&n; * of warnings and errors :)&n; */
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
suffix:semicolon
r_static
r_void
id|dma_advance_sg
c_func
(paren
id|Scsi_Cmnd
op_star
id|sp
)paren
suffix:semicolon
r_static
r_void
id|pmaz_dma_drain
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
id|pmaz_dma_init_read
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
id|pmaz_dma_init_write
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
id|pmaz_dma_ints_off
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
id|pmaz_dma_ints_on
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
id|pmaz_dma_setup
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
id|pmaz_dma_mmu_get_scsi_one
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
DECL|macro|TC_ESP_RAM_SIZE
mdefine_line|#define TC_ESP_RAM_SIZE 0x20000
DECL|macro|ESP_TGT_DMA_SIZE
mdefine_line|#define ESP_TGT_DMA_SIZE ((TC_ESP_RAM_SIZE/7) &amp; ~(sizeof(int)-1))
DECL|macro|ESP_NCMD
mdefine_line|#define ESP_NCMD 7
DECL|macro|TC_ESP_DMAR_MASK
mdefine_line|#define TC_ESP_DMAR_MASK  0x1ffff
DECL|macro|TC_ESP_DMAR_WRITE
mdefine_line|#define TC_ESP_DMAR_WRITE 0x80000000
DECL|macro|TC_ESP_DMA_ADDR
mdefine_line|#define TC_ESP_DMA_ADDR(x) ((unsigned)(x) &amp; TC_ESP_DMAR_MASK)
DECL|variable|esp_virt_buffer
id|__u32
id|esp_virt_buffer
suffix:semicolon
DECL|variable|scsi_current_length
r_int
id|scsi_current_length
suffix:semicolon
DECL|variable|cmd_buffer
r_volatile
r_int
r_char
id|cmd_buffer
(braket
l_int|16
)braket
suffix:semicolon
DECL|variable|pmaz_cmd_buffer
r_volatile
r_int
r_char
id|pmaz_cmd_buffer
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* This is where all commands are put&n;&t;&t;&t;&t; * before they are trasfered to the ESP chip&n;&t;&t;&t;&t; * via PIO.&n;&t;&t;&t;&t; */
DECL|variable|scsi_dma_ptr
r_volatile
r_int
r_int
op_star
id|scsi_dma_ptr
suffix:semicolon
DECL|variable|scsi_next_ptr
r_volatile
r_int
r_int
op_star
id|scsi_next_ptr
suffix:semicolon
DECL|variable|scsi_scr
r_volatile
r_int
r_int
op_star
id|scsi_scr
suffix:semicolon
DECL|variable|ioasic_ssr
r_volatile
r_int
r_int
op_star
id|ioasic_ssr
suffix:semicolon
DECL|variable|scsi_sdr0
r_volatile
r_int
r_int
op_star
id|scsi_sdr0
suffix:semicolon
DECL|variable|scsi_sdr1
r_volatile
r_int
r_int
op_star
id|scsi_sdr1
suffix:semicolon
r_static
r_void
id|scsi_dma_int
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
r_int
id|dec_esp_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
suffix:semicolon
DECL|function|dec_esp_release
r_static
r_int
id|dec_esp_release
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
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
(brace
dot
id|proc_name
op_assign
l_string|&quot;dec_esp&quot;
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
l_string|&quot;NCR53C94&quot;
comma
dot
id|detect
op_assign
id|dec_esp_detect
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
id|dec_esp_release
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
macro_line|#include &quot;scsi_module.c&quot;
multiline_comment|/***************************************************************** Detection */
DECL|function|dec_esp_detect
r_int
id|dec_esp_detect
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
r_int
id|slot
suffix:semicolon
r_int
r_int
id|mem_start
suffix:semicolon
r_if
c_cond
(paren
id|IOASIC
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
id|scsi_dma_ptr
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|system_base
op_plus
id|IOCTL
op_plus
id|SCSI_DMA_P
)paren
suffix:semicolon
id|scsi_next_ptr
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|system_base
op_plus
id|IOCTL
op_plus
id|SCSI_DMA_BP
)paren
suffix:semicolon
id|scsi_scr
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|system_base
op_plus
id|IOCTL
op_plus
id|SCSI_SCR
)paren
suffix:semicolon
id|ioasic_ssr
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|system_base
op_plus
id|IOCTL
op_plus
id|SSR
)paren
suffix:semicolon
id|scsi_sdr0
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|system_base
op_plus
id|IOCTL
op_plus
id|SCSI_SDR0
)paren
suffix:semicolon
id|scsi_sdr1
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|system_base
op_plus
id|IOCTL
op_plus
id|SCSI_SDR1
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
op_amp
id|dma_drain
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
l_int|0
suffix:semicolon
id|esp-&gt;dma_led_on
op_assign
l_int|0
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
l_int|0
suffix:semicolon
id|esp-&gt;dma_mmu_release_scsi_sgl
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;dma_advance_sg
op_assign
op_amp
id|dma_advance_sg
suffix:semicolon
multiline_comment|/* SCSI chip speed */
id|esp-&gt;cfreq
op_assign
l_int|25000000
suffix:semicolon
multiline_comment|/*&n;&t;&t; * we don&squot;t give the address of DMA channel, but the number&n;&t;&t; * of DMA channel, so we can use the jazz DMA functions&n;&t;&t; *&n;&t;&t; */
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
id|system_base
op_plus
id|SCSI
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
(paren
id|__u32
)paren
id|KSEG1ADDR
c_func
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|cmd_buffer
)paren
suffix:semicolon
id|esp-&gt;irq
op_assign
id|SCSI_INT
suffix:semicolon
id|esp-&gt;scsi_id
op_assign
l_int|7
suffix:semicolon
multiline_comment|/* Check for differential SCSI-bus */
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
l_string|&quot;NCR 53C94 SCSI&quot;
comma
id|esp-&gt;ehost
)paren
)paren
r_goto
id|err_dealloc
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|SCSI_DMA_INT
comma
id|scsi_dma_int
comma
id|SA_INTERRUPT
comma
l_string|&quot;JUNKIO SCSI DMA&quot;
comma
id|esp-&gt;ehost
)paren
)paren
r_goto
id|err_free_irq
suffix:semicolon
)brace
r_if
c_cond
(paren
id|TURBOCHANNEL
)paren
(brace
r_while
c_loop
(paren
(paren
id|slot
op_assign
id|search_tc_card
c_func
(paren
l_string|&quot;PMAZ-AA&quot;
)paren
)paren
op_ge
l_int|0
)paren
(brace
id|claim_tc_card
c_func
(paren
id|slot
)paren
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
id|mem_start
op_assign
id|get_tc_base_addr
c_func
(paren
id|slot
)paren
suffix:semicolon
multiline_comment|/* Store base addr into esp struct */
id|esp-&gt;slot
op_assign
id|mem_start
suffix:semicolon
id|esp-&gt;dregs
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;eregs
op_assign
(paren
r_struct
id|ESP_regs
op_star
)paren
(paren
id|mem_start
op_plus
id|DEC_SCSI_SREG
)paren
suffix:semicolon
id|esp-&gt;do_pio_cmds
op_assign
l_int|1
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
id|pmaz_cmd_buffer
suffix:semicolon
multiline_comment|/* get virtual dma address for command buffer */
id|esp-&gt;esp_command_dvma
op_assign
(paren
id|__u32
)paren
id|KSEG0ADDR
c_func
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|pmaz_cmd_buffer
)paren
suffix:semicolon
id|esp-&gt;cfreq
op_assign
id|get_tc_speed
c_func
(paren
)paren
suffix:semicolon
id|esp-&gt;irq
op_assign
id|get_tc_irq_nr
c_func
(paren
id|slot
)paren
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
id|pmaz_dma_init_read
suffix:semicolon
id|esp-&gt;dma_init_write
op_assign
op_amp
id|pmaz_dma_init_write
suffix:semicolon
id|esp-&gt;dma_ints_off
op_assign
op_amp
id|pmaz_dma_ints_off
suffix:semicolon
id|esp-&gt;dma_ints_on
op_assign
op_amp
id|pmaz_dma_ints_on
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
id|pmaz_dma_setup
suffix:semicolon
multiline_comment|/* Optional functions */
id|esp-&gt;dma_barrier
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;dma_drain
op_assign
op_amp
id|pmaz_dma_drain
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
l_int|0
suffix:semicolon
id|esp-&gt;dma_led_on
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;dma_mmu_get_scsi_one
op_assign
id|pmaz_dma_mmu_get_scsi_one
suffix:semicolon
id|esp-&gt;dma_mmu_get_scsi_sgl
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;dma_mmu_release_scsi_one
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;dma_mmu_release_scsi_sgl
op_assign
l_int|0
suffix:semicolon
id|esp-&gt;dma_advance_sg
op_assign
l_int|0
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
l_string|&quot;PMAZ_AA&quot;
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
id|release_tc_card
c_func
(paren
id|slot
)paren
suffix:semicolon
r_continue
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
)brace
)brace
r_if
c_cond
(paren
id|nesps
)paren
(brace
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
id|err_free_irq
suffix:colon
id|free_irq
c_func
(paren
id|esp-&gt;irq
comma
id|esp_intr
)paren
suffix:semicolon
id|err_dealloc
suffix:colon
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
multiline_comment|/************************************************************* DMA Functions */
DECL|function|scsi_dma_int
r_static
r_void
id|scsi_dma_int
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
id|regs
)paren
(brace
r_extern
r_volatile
r_int
r_int
op_star
id|isr
suffix:semicolon
r_int
r_int
id|dummy
suffix:semicolon
r_if
c_cond
(paren
op_star
id|isr
op_amp
id|SCSI_PTR_LOADED
)paren
(brace
multiline_comment|/* next page */
op_star
id|scsi_next_ptr
op_assign
(paren
(paren
op_star
id|scsi_dma_ptr
op_plus
id|PAGE_SIZE
)paren
op_amp
id|PAGE_MASK
)paren
op_lshift
l_int|3
suffix:semicolon
op_star
id|isr
op_and_assign
op_complement
id|SCSI_PTR_LOADED
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_star
id|isr
op_amp
id|SCSI_PAGOVRRUN
)paren
op_star
id|isr
op_and_assign
op_complement
id|SCSI_PAGOVRRUN
suffix:semicolon
r_if
c_cond
(paren
op_star
id|isr
op_amp
id|SCSI_DMA_MEMRDERR
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Got unexpected SCSI DMA Interrupt! &lt; &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SCSI_DMA_MEMRDERR &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&gt;&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|isr
op_and_assign
op_complement
id|SCSI_DMA_MEMRDERR
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * This routine will only work on IOASIC machines&n;&t; * so we can avoid an indirect function call here&n;&t; * and flush the writeback buffer the fast way&n;&t; */
id|dummy
op_assign
op_star
id|isr
suffix:semicolon
id|dummy
op_assign
op_star
id|isr
suffix:semicolon
)brace
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
r_int
r_int
id|nw
op_assign
op_star
id|scsi_scr
suffix:semicolon
r_int
r_int
op_star
id|p
op_assign
(paren
r_int
r_int
op_star
)paren
id|KSEG1ADDR
c_func
(paren
(paren
op_star
id|scsi_dma_ptr
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Is there something in the dma buffers left?&n;     */
r_if
c_cond
(paren
id|nw
)paren
(brace
r_switch
c_cond
(paren
id|nw
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
id|p
op_assign
(paren
r_int
r_int
)paren
op_star
id|scsi_sdr0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|p
op_increment
op_assign
(paren
r_int
r_int
)paren
(paren
op_star
id|scsi_sdr0
)paren
suffix:semicolon
op_star
id|p
op_assign
(paren
r_int
r_int
)paren
(paren
(paren
op_star
id|scsi_sdr0
)paren
op_rshift
l_int|16
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
op_star
id|p
op_increment
op_assign
(paren
r_int
r_int
)paren
(paren
op_star
id|scsi_sdr0
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
(paren
r_int
r_int
)paren
(paren
(paren
op_star
id|scsi_sdr0
)paren
op_rshift
l_int|16
)paren
suffix:semicolon
op_star
id|p
op_assign
(paren
r_int
r_int
)paren
(paren
op_star
id|scsi_sdr1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Strange: %d words in dma buffer left&bslash;n&quot;
comma
(paren
r_int
)paren
id|nw
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
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
multiline_comment|/*&n;    ESPLOG((&quot;esp%d: dma -- enable &lt;%08x&gt; residue &lt;%08x&bslash;n&quot;,&n;&t;    esp-&gt;esp_id, vdma_get_enable((int)esp-&gt;dregs), vdma_get_resdiue((int)esp-&gt;dregs)));&n; */
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
r_extern
r_volatile
r_int
r_int
op_star
id|isr
suffix:semicolon
r_int
r_int
id|dummy
suffix:semicolon
r_if
c_cond
(paren
id|vaddress
op_amp
l_int|3
)paren
id|panic
c_func
(paren
l_string|&quot;dec_efs.c: unable to handle partial word transfers, yet...&quot;
)paren
suffix:semicolon
id|dma_cache_wback_inv
c_func
(paren
(paren
r_int
r_int
)paren
id|phys_to_virt
c_func
(paren
id|vaddress
)paren
comma
id|length
)paren
suffix:semicolon
op_star
id|ioasic_ssr
op_and_assign
op_complement
id|SCSI_DMA_EN
suffix:semicolon
op_star
id|scsi_scr
op_assign
l_int|0
suffix:semicolon
op_star
id|scsi_dma_ptr
op_assign
id|vaddress
op_lshift
l_int|3
suffix:semicolon
multiline_comment|/* prepare for next page */
op_star
id|scsi_next_ptr
op_assign
(paren
(paren
id|vaddress
op_plus
id|PAGE_SIZE
)paren
op_amp
id|PAGE_MASK
)paren
op_lshift
l_int|3
suffix:semicolon
op_star
id|ioasic_ssr
op_or_assign
(paren
id|SCSI_DMA_DIR
op_or
id|SCSI_DMA_EN
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * see above&n;&t; */
id|dummy
op_assign
op_star
id|isr
suffix:semicolon
id|dummy
op_assign
op_star
id|isr
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
r_extern
r_volatile
r_int
r_int
op_star
id|isr
suffix:semicolon
r_int
r_int
id|dummy
suffix:semicolon
r_if
c_cond
(paren
id|vaddress
op_amp
l_int|3
)paren
id|panic
c_func
(paren
l_string|&quot;dec_efs.c: unable to handle partial word transfers, yet...&quot;
)paren
suffix:semicolon
id|dma_cache_wback_inv
c_func
(paren
(paren
r_int
r_int
)paren
id|phys_to_virt
c_func
(paren
id|vaddress
)paren
comma
id|length
)paren
suffix:semicolon
op_star
id|ioasic_ssr
op_and_assign
op_complement
(paren
id|SCSI_DMA_DIR
op_or
id|SCSI_DMA_EN
)paren
suffix:semicolon
op_star
id|scsi_scr
op_assign
l_int|0
suffix:semicolon
op_star
id|scsi_dma_ptr
op_assign
id|vaddress
op_lshift
l_int|3
suffix:semicolon
multiline_comment|/* prepare for next page */
op_star
id|scsi_next_ptr
op_assign
(paren
(paren
id|vaddress
op_plus
id|PAGE_SIZE
)paren
op_amp
id|PAGE_MASK
)paren
op_lshift
l_int|3
suffix:semicolon
op_star
id|ioasic_ssr
op_or_assign
id|SCSI_DMA_EN
suffix:semicolon
multiline_comment|/*&n;&t; * see above&n;&t; */
id|dummy
op_assign
op_star
id|isr
suffix:semicolon
id|dummy
op_assign
op_star
id|isr
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
id|SCSI_DMA_INT
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
id|SCSI_DMA_INT
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
id|esp-&gt;eregs-&gt;esp_status
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
multiline_comment|/*&n; * FIXME: what&squot;s this good for?&n; */
r_return
l_int|1
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
multiline_comment|/*&n;     * On the Sparc, DMA_ST_WRITE means &quot;move data from device to memory&quot;&n;     * so when (write) is true, it actually means READ!&n;     */
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
multiline_comment|/*&n; * These aren&squot;t used yet&n; */
DECL|function|dma_mmu_get_scsi_one
r_static
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
id|sp-&gt;SCp.ptr
op_assign
(paren
r_char
op_star
)paren
id|PHYSADDR
c_func
(paren
id|sp-&gt;SCp.buffer
)paren
suffix:semicolon
)brace
DECL|function|dma_mmu_get_scsi_sgl
r_static
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
DECL|function|dma_advance_sg
r_static
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
DECL|function|pmaz_dma_drain
r_static
r_void
id|pmaz_dma_drain
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
(brace
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|KSEG0ADDR
c_func
(paren
id|esp_virt_buffer
)paren
)paren
comma
(paren
r_void
op_star
)paren
(paren
id|esp-&gt;slot
op_plus
id|DEC_SCSI_SRAM
op_plus
id|ESP_TGT_DMA_SIZE
)paren
comma
id|scsi_current_length
)paren
suffix:semicolon
)brace
DECL|function|pmaz_dma_init_read
r_static
r_void
id|pmaz_dma_init_read
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
r_volatile
r_int
op_star
id|dmareg
op_assign
(paren
r_volatile
r_int
op_star
)paren
(paren
id|esp-&gt;slot
op_plus
id|DEC_SCSI_DMAREG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
id|ESP_TGT_DMA_SIZE
)paren
id|length
op_assign
id|ESP_TGT_DMA_SIZE
suffix:semicolon
op_star
id|dmareg
op_assign
id|TC_ESP_DMA_ADDR
c_func
(paren
id|esp-&gt;slot
op_plus
id|DEC_SCSI_SRAM
op_plus
id|ESP_TGT_DMA_SIZE
)paren
suffix:semicolon
id|esp_virt_buffer
op_assign
id|vaddress
suffix:semicolon
id|scsi_current_length
op_assign
id|length
suffix:semicolon
)brace
DECL|function|pmaz_dma_init_write
r_static
r_void
id|pmaz_dma_init_write
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
r_volatile
r_int
op_star
id|dmareg
op_assign
(paren
r_volatile
r_int
op_star
)paren
(paren
id|esp-&gt;slot
op_plus
id|DEC_SCSI_DMAREG
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|esp-&gt;slot
op_plus
id|DEC_SCSI_SRAM
op_plus
id|ESP_TGT_DMA_SIZE
)paren
comma
(paren
r_void
op_star
)paren
id|KSEG0ADDR
c_func
(paren
id|vaddress
)paren
comma
id|length
)paren
suffix:semicolon
op_star
id|dmareg
op_assign
id|TC_ESP_DMAR_WRITE
op_or
id|TC_ESP_DMA_ADDR
c_func
(paren
id|esp-&gt;slot
op_plus
id|DEC_SCSI_SRAM
op_plus
id|ESP_TGT_DMA_SIZE
)paren
suffix:semicolon
)brace
DECL|function|pmaz_dma_ints_off
r_static
r_void
id|pmaz_dma_ints_off
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
(brace
)brace
DECL|function|pmaz_dma_ints_on
r_static
r_void
id|pmaz_dma_ints_on
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
)paren
(brace
)brace
DECL|function|pmaz_dma_setup
r_static
r_void
id|pmaz_dma_setup
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
multiline_comment|/*&n;&t; * On the Sparc, DMA_ST_WRITE means &quot;move data from device to memory&quot;&n;&t; * so when (write) is true, it actually means READ!&n;&t; */
r_if
c_cond
(paren
id|write
)paren
(brace
id|pmaz_dma_init_read
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
id|pmaz_dma_init_write
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
DECL|function|pmaz_dma_mmu_get_scsi_one
r_static
r_void
id|pmaz_dma_mmu_get_scsi_one
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
(paren
r_char
op_star
)paren
id|KSEG0ADDR
c_func
(paren
(paren
id|sp-&gt;request_buffer
)paren
)paren
suffix:semicolon
)brace
eof

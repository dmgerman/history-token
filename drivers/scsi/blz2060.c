multiline_comment|/* blz2060.c: Driver for Blizzard 2060 SCSI Controller.&n; *&n; * Copyright (C) 1996 Jesper Skov (jskov@cygnus.co.uk)&n; *&n; * This driver is based on the CyberStorm driver, hence the occasional&n; * reference to CyberStorm.&n; */
multiline_comment|/* TODO:&n; *&n; * 1) Figure out how to make a cleaner merge with the sparc driver with regard&n; *    to the caches and the Sparc MMU mapping.&n; * 2) Make as few routines required outside the generic driver. A lot of the&n; *    routines in this file used to be inline!&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &quot;NCR53C9x.h&quot;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/* The controller registers can be found in the Z2 config area at these&n; * offsets:&n; */
DECL|macro|BLZ2060_ESP_ADDR
mdefine_line|#define BLZ2060_ESP_ADDR 0x1ff00
DECL|macro|BLZ2060_DMA_ADDR
mdefine_line|#define BLZ2060_DMA_ADDR 0x1ffe0
multiline_comment|/* The Blizzard 2060 DMA interface&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; * Only two things can be programmed in the Blizzard DMA:&n; *  1) The data direction is controlled by the status of bit 31 (1 = write)&n; *  2) The source/dest address (word aligned, shifted one right) in bits 30-0&n; *&n; * Figure out interrupt status by reading the ESP status byte.&n; */
DECL|struct|blz2060_dma_registers
r_struct
id|blz2060_dma_registers
(brace
DECL|member|dma_led_ctrl
r_volatile
r_int
r_char
id|dma_led_ctrl
suffix:semicolon
multiline_comment|/* DMA led control   [0x000] */
DECL|member|dmapad1
r_int
r_char
id|dmapad1
(braket
l_int|0x0f
)braket
suffix:semicolon
DECL|member|dma_addr0
r_volatile
r_int
r_char
id|dma_addr0
suffix:semicolon
multiline_comment|/* DMA address (MSB) [0x010] */
DECL|member|dmapad2
r_int
r_char
id|dmapad2
(braket
l_int|0x03
)braket
suffix:semicolon
DECL|member|dma_addr1
r_volatile
r_int
r_char
id|dma_addr1
suffix:semicolon
multiline_comment|/* DMA address       [0x014] */
DECL|member|dmapad3
r_int
r_char
id|dmapad3
(braket
l_int|0x03
)braket
suffix:semicolon
DECL|member|dma_addr2
r_volatile
r_int
r_char
id|dma_addr2
suffix:semicolon
multiline_comment|/* DMA address       [0x018] */
DECL|member|dmapad4
r_int
r_char
id|dmapad4
(braket
l_int|0x03
)braket
suffix:semicolon
DECL|member|dma_addr3
r_volatile
r_int
r_char
id|dma_addr3
suffix:semicolon
multiline_comment|/* DMA address (LSB) [0x01c] */
)brace
suffix:semicolon
DECL|macro|BLZ2060_DMA_WRITE
mdefine_line|#define BLZ2060_DMA_WRITE 0x80000000
multiline_comment|/* DMA control bits */
DECL|macro|BLZ2060_DMA_LED
mdefine_line|#define BLZ2060_DMA_LED    0x02&t;&t;/* HD led control 1 = off */
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
id|addr
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
id|addr
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
multiline_comment|/* This is where all commands are put&n;&t;&t;&t;&t; * before they are transferred to the ESP chip&n;&t;&t;&t;&t; * via PIO.&n;&t;&t;&t;&t; */
multiline_comment|/***************************************************************** Detection */
DECL|function|blz2060_esp_detect
r_int
id|__init
id|blz2060_esp_detect
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
r_if
c_cond
(paren
(paren
id|z
op_assign
id|zorro_find_device
c_func
(paren
id|ZORRO_PROD_PHASE5_BLIZZARD_2060
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
id|BLZ2060_ESP_ADDR
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
id|BLZ2060_ESP_ADDR
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
multiline_comment|/* SCSI chip speed */
id|esp-&gt;cfreq
op_assign
l_int|40000000
suffix:semicolon
multiline_comment|/* The DMA registers on the Blizzard are mapped&n;&t;&t; * relative to the device (i.e. in the same Zorro&n;&t;&t; * I/O block).&n;&t;&t; */
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
id|esp-&gt;dregs
op_assign
(paren
r_void
op_star
)paren
(paren
id|address
op_plus
id|BLZ2060_DMA_ADDR
)paren
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
id|address
op_plus
id|BLZ2060_ESP_ADDR
)paren
suffix:semicolon
multiline_comment|/* Set the command buffer */
id|esp-&gt;esp_command
op_assign
id|cmd_buffer
suffix:semicolon
id|esp-&gt;esp_command_dvma
op_assign
id|virt_to_bus
c_func
(paren
(paren
r_void
op_star
)paren
id|cmd_buffer
)paren
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
l_string|&quot;Blizzard 2060 SCSI&quot;
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
)brace
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
multiline_comment|/* Since the Blizzard DMA is fully dedicated to the ESP chip,&n;&t; * the number of bytes sent (to the ESP chip) equals the number&n;&t; * of bytes in the FIFO - there is no buffering in the DMA controller.&n;&t; * XXXX Do I read this right? It is from host to ESP, right?&n;&t; */
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
multiline_comment|/* I don&squot;t think there&squot;s any limit on the Blizzard DMA. So we use what&n;&t; * the ESP chip can handle (24 bit).&n;&t; */
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
l_int|0x1000000
)paren
(brace
id|sz
op_assign
l_int|0x1000000
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
l_string|&quot;intreq:&lt;%04x&gt;, intena:&lt;%04x&gt;&bslash;n&quot;
comma
id|custom.intreqr
comma
id|custom.intenar
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
r_struct
id|blz2060_dma_registers
op_star
id|dregs
op_assign
(paren
r_struct
id|blz2060_dma_registers
op_star
)paren
(paren
id|esp-&gt;dregs
)paren
suffix:semicolon
id|cache_clear
c_func
(paren
id|addr
comma
id|length
)paren
suffix:semicolon
id|addr
op_rshift_assign
l_int|1
suffix:semicolon
id|addr
op_and_assign
op_complement
(paren
id|BLZ2060_DMA_WRITE
)paren
suffix:semicolon
id|dregs-&gt;dma_addr3
op_assign
(paren
id|addr
)paren
op_amp
l_int|0xff
suffix:semicolon
id|dregs-&gt;dma_addr2
op_assign
(paren
id|addr
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|dregs-&gt;dma_addr1
op_assign
(paren
id|addr
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|dregs-&gt;dma_addr0
op_assign
(paren
id|addr
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
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
r_struct
id|blz2060_dma_registers
op_star
id|dregs
op_assign
(paren
r_struct
id|blz2060_dma_registers
op_star
)paren
(paren
id|esp-&gt;dregs
)paren
suffix:semicolon
id|cache_push
c_func
(paren
id|addr
comma
id|length
)paren
suffix:semicolon
id|addr
op_rshift_assign
l_int|1
suffix:semicolon
id|addr
op_or_assign
id|BLZ2060_DMA_WRITE
suffix:semicolon
id|dregs-&gt;dma_addr3
op_assign
(paren
id|addr
)paren
op_amp
l_int|0xff
suffix:semicolon
id|dregs-&gt;dma_addr2
op_assign
(paren
id|addr
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|dregs-&gt;dma_addr1
op_assign
(paren
id|addr
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|dregs-&gt;dma_addr0
op_assign
(paren
id|addr
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
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
(paren
(paren
r_struct
id|blz2060_dma_registers
op_star
)paren
(paren
id|esp-&gt;dregs
)paren
)paren
op_member_access_from_pointer
id|dma_led_ctrl
op_assign
id|BLZ2060_DMA_LED
suffix:semicolon
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
(paren
(paren
r_struct
id|blz2060_dma_registers
op_star
)paren
(paren
id|esp-&gt;dregs
)paren
)paren
op_member_access_from_pointer
id|dma_led_ctrl
op_assign
l_int|0
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
DECL|macro|HOSTS_C
mdefine_line|#define HOSTS_C
DECL|function|blz2060_esp_release
r_int
id|blz2060_esp_release
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
id|esp_deallocate
c_func
(paren
(paren
r_struct
id|NCR_ESP
op_star
)paren
id|instance-&gt;hostdata
)paren
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
macro_line|#endif
r_return
l_int|1
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
l_string|&quot;esp-blz2060&quot;
comma
dot
id|proc_info
op_assign
id|esp_proc_info
comma
dot
id|name
op_assign
l_string|&quot;Blizzard2060 SCSI&quot;
comma
dot
id|detect
op_assign
id|blz2060_esp_detect
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
id|blz2060_esp_release
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
id|ENABLE_CLUSTERING
)brace
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof

multiline_comment|/* cyberstorm.c: Driver for CyberStorm SCSI Controller.&n; *&n; * Copyright (C) 1996 Jesper Skov (jskov@cygnus.co.uk)&n; *&n; * The CyberStorm SCSI driver is based on David S. Miller&squot;s ESP driver&n; * for the Sparc computers. &n; * &n; * This work was made possible by Phase5 who willingly (and most generously)&n; * supported me with hardware and all the information I needed.&n; */
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
DECL|macro|CYBER_ESP_ADDR
mdefine_line|#define CYBER_ESP_ADDR 0xf400
DECL|macro|CYBER_DMA_ADDR
mdefine_line|#define CYBER_DMA_ADDR 0xf800
multiline_comment|/* The CyberStorm DMA interface */
DECL|struct|cyber_dma_registers
r_struct
id|cyber_dma_registers
(brace
DECL|member|dma_addr0
r_volatile
r_int
r_char
id|dma_addr0
suffix:semicolon
multiline_comment|/* DMA address (MSB) [0x000] */
DECL|member|dmapad1
r_int
r_char
id|dmapad1
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|dma_addr1
r_volatile
r_int
r_char
id|dma_addr1
suffix:semicolon
multiline_comment|/* DMA address       [0x002] */
DECL|member|dmapad2
r_int
r_char
id|dmapad2
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|dma_addr2
r_volatile
r_int
r_char
id|dma_addr2
suffix:semicolon
multiline_comment|/* DMA address       [0x004] */
DECL|member|dmapad3
r_int
r_char
id|dmapad3
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|dma_addr3
r_volatile
r_int
r_char
id|dma_addr3
suffix:semicolon
multiline_comment|/* DMA address (LSB) [0x006] */
DECL|member|dmapad4
r_int
r_char
id|dmapad4
(braket
l_int|0x3fb
)braket
suffix:semicolon
DECL|member|cond_reg
r_volatile
r_int
r_char
id|cond_reg
suffix:semicolon
multiline_comment|/* DMA cond    (ro)  [0x402] */
DECL|macro|ctrl_reg
mdefine_line|#define ctrl_reg  cond_reg&t;&t;&t;/* DMA control (wo)  [0x402] */
)brace
suffix:semicolon
multiline_comment|/* DMA control bits */
DECL|macro|CYBER_DMA_LED
mdefine_line|#define CYBER_DMA_LED    0x80&t;/* HD led control 1 = on */
DECL|macro|CYBER_DMA_WRITE
mdefine_line|#define CYBER_DMA_WRITE  0x40&t;/* DMA direction. 1 = write */
DECL|macro|CYBER_DMA_Z3
mdefine_line|#define CYBER_DMA_Z3     0x20&t;/* 16 (Z2) or 32 (CHIP/Z3) bit DMA transfer */
multiline_comment|/* DMA status bits */
DECL|macro|CYBER_DMA_HNDL_INTR
mdefine_line|#define CYBER_DMA_HNDL_INTR 0x80&t;/* DMA IRQ pending? */
multiline_comment|/* The bits below appears to be Phase5 Debug bits only; they were not&n; * described by Phase5 so using them may seem a bit stupid...&n; */
DECL|macro|CYBER_HOST_ID
mdefine_line|#define CYBER_HOST_ID 0x02&t;/* If set, host ID should be 7, otherwise&n;&t;&t;&t;&t; * it should be 6.&n;&t;&t;&t;&t; */
DECL|macro|CYBER_SLOW_CABLE
mdefine_line|#define CYBER_SLOW_CABLE 0x08&t;/* If *not* set, assume SLOW_CABLE */
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
DECL|variable|ctrl_data
r_static
r_int
r_char
id|ctrl_data
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Keep backup of the stuff written&n;&t;&t;&t;&t; * to ctrl_reg. Always write a copy&n;&t;&t;&t;&t; * to this register when writing to&n;&t;&t;&t;&t; * the hardware register!&n;&t;&t;&t;&t; */
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
DECL|function|cyber_esp_detect
r_int
id|__init
id|cyber_esp_detect
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
r_while
c_loop
(paren
(paren
id|z
op_assign
id|zorro_find_device
c_func
(paren
id|ZORRO_WILDCARD
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
(paren
id|z-&gt;id
op_eq
id|ZORRO_PROD_PHASE5_BLIZZARD_1220_CYBERSTORM
op_logical_or
id|z-&gt;id
op_eq
id|ZORRO_PROD_PHASE5_BLIZZARD_1230_II_FASTLANE_Z3_CYBERSCSI_CYBERSTORM060
)paren
op_logical_and
id|request_mem_region
c_func
(paren
id|board
op_plus
id|CYBER_ESP_ADDR
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
multiline_comment|/* Figure out if this is a CyberStorm or really a &n;&t;&t; * Fastlane/Blizzard Mk II by looking at the board size.&n;&t;&t; * CyberStorm maps 64kB&n;&t;&t; * (ZORRO_PROD_PHASE5_BLIZZARD_1220_CYBERSTORM does anyway)&n;&t;&t; */
r_if
c_cond
(paren
id|z-&gt;resource.end
op_minus
id|board
op_ne
l_int|0xffff
)paren
(brace
id|release_mem_region
c_func
(paren
id|board
op_plus
id|CYBER_ESP_ADDR
comma
r_sizeof
(paren
r_struct
id|ESP_regs
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|CYBER_ESP_ADDR
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
multiline_comment|/* The DMA registers on the CyberStorm are mapped&n;&t;&t; * relative to the device (i.e. in the same Zorro&n;&t;&t; * I/O block).&n;&t;&t; */
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
id|CYBER_DMA_ADDR
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
id|CYBER_ESP_ADDR
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
l_string|&quot;CyberStorm SCSI&quot;
comma
id|esp-&gt;ehost
)paren
suffix:semicolon
multiline_comment|/* Figure out our scsi ID on the bus */
multiline_comment|/* The DMA cond flag contains a hardcoded jumper bit&n;&t;&t; * which can be used to select host number 6 or 7.&n;&t;&t; * However, even though it may change, we use a hardcoded&n;&t;&t; * value of 7.&n;&t;&t; */
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
multiline_comment|/* I don&squot;t think there&squot;s any limit on the CyberDMA. So we use what&n;&t; * the ESP chip can handle (24 bit).&n;&t; */
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
l_string|&quot;esp%d: dma -- cond_reg&lt;%02x&gt;&bslash;n&quot;
comma
id|esp-&gt;esp_id
comma
(paren
(paren
r_struct
id|cyber_dma_registers
op_star
)paren
(paren
id|esp-&gt;dregs
)paren
)paren
op_member_access_from_pointer
id|cond_reg
)paren
)paren
suffix:semicolon
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
id|cyber_dma_registers
op_star
id|dregs
op_assign
(paren
r_struct
id|cyber_dma_registers
op_star
)paren
id|esp-&gt;dregs
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
op_and_assign
op_complement
(paren
l_int|1
)paren
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
id|dregs-&gt;dma_addr3
op_assign
(paren
id|addr
)paren
op_amp
l_int|0xff
suffix:semicolon
id|ctrl_data
op_and_assign
op_complement
(paren
id|CYBER_DMA_WRITE
)paren
suffix:semicolon
multiline_comment|/* Check if physical address is outside Z2 space and of&n;&t; * block length/block aligned in memory. If this is the&n;&t; * case, enable 32 bit transfer. In all other cases, fall back&n;&t; * to 16 bit transfer.&n;&t; * Obviously 32 bit transfer should be enabled if the DMA address&n;&t; * and length are 32 bit aligned. However, this leads to some&n;&t; * strange behavior. Even 64 bit aligned addr/length fails.&n;&t; * Until I&squot;ve found a reason for this, 32 bit transfer is only&n;&t; * used for full-block transfers (1kB).&n;&t; *&t;&t;&t;&t;&t;&t;&t;-jskov&n;&t; */
macro_line|#if 0
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|0x3fc
)paren
op_logical_or
id|length
op_amp
l_int|0x3ff
op_logical_or
(paren
(paren
id|addr
OG
l_int|0x200000
)paren
op_logical_and
(paren
id|addr
OL
l_int|0xff0000
)paren
)paren
)paren
(brace
id|ctrl_data
op_and_assign
op_complement
(paren
id|CYBER_DMA_Z3
)paren
suffix:semicolon
)brace
multiline_comment|/* Z2, do 16 bit DMA */
r_else
id|ctrl_data
op_or_assign
id|CYBER_DMA_Z3
suffix:semicolon
multiline_comment|/* CHIP/Z3, do 32 bit DMA */
macro_line|#else
id|ctrl_data
op_and_assign
op_complement
(paren
id|CYBER_DMA_Z3
)paren
suffix:semicolon
multiline_comment|/* Z2, do 16 bit DMA */
macro_line|#endif
id|dregs-&gt;ctrl_reg
op_assign
id|ctrl_data
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
id|cyber_dma_registers
op_star
id|dregs
op_assign
(paren
r_struct
id|cyber_dma_registers
op_star
)paren
id|esp-&gt;dregs
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
op_or_assign
l_int|1
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
id|dregs-&gt;dma_addr3
op_assign
(paren
id|addr
)paren
op_amp
l_int|0xff
suffix:semicolon
id|ctrl_data
op_or_assign
id|CYBER_DMA_WRITE
suffix:semicolon
multiline_comment|/* See comment above */
macro_line|#if 0
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|0x3fc
)paren
op_logical_or
id|length
op_amp
l_int|0x3ff
op_logical_or
(paren
(paren
id|addr
OG
l_int|0x200000
)paren
op_logical_and
(paren
id|addr
OL
l_int|0xff0000
)paren
)paren
)paren
(brace
id|ctrl_data
op_and_assign
op_complement
(paren
id|CYBER_DMA_Z3
)paren
suffix:semicolon
)brace
multiline_comment|/* Z2, do 16 bit DMA */
r_else
id|ctrl_data
op_or_assign
id|CYBER_DMA_Z3
suffix:semicolon
multiline_comment|/* CHIP/Z3, do 32 bit DMA */
macro_line|#else
id|ctrl_data
op_and_assign
op_complement
(paren
id|CYBER_DMA_Z3
)paren
suffix:semicolon
multiline_comment|/* Z2, do 16 bit DMA */
macro_line|#endif
id|dregs-&gt;ctrl_reg
op_assign
id|ctrl_data
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
(paren
id|esp_read
c_func
(paren
id|esp-&gt;eregs-&gt;esp_status
)paren
op_amp
id|ESP_STAT_INTR
)paren
op_logical_and
(paren
(paren
(paren
(paren
r_struct
id|cyber_dma_registers
op_star
)paren
(paren
id|esp-&gt;dregs
)paren
)paren
op_member_access_from_pointer
id|cond_reg
)paren
op_amp
id|CYBER_DMA_HNDL_INTR
)paren
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
id|ctrl_data
op_and_assign
op_complement
id|CYBER_DMA_LED
suffix:semicolon
(paren
(paren
r_struct
id|cyber_dma_registers
op_star
)paren
(paren
id|esp-&gt;dregs
)paren
)paren
op_member_access_from_pointer
id|ctrl_reg
op_assign
id|ctrl_data
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
id|ctrl_data
op_or_assign
id|CYBER_DMA_LED
suffix:semicolon
(paren
(paren
r_struct
id|cyber_dma_registers
op_star
)paren
(paren
id|esp-&gt;dregs
)paren
)paren
op_member_access_from_pointer
id|ctrl_reg
op_assign
id|ctrl_data
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
DECL|function|cyber_esp_release
r_int
id|cyber_esp_release
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
l_string|&quot;esp-cyberstorm&quot;
comma
dot
id|proc_info
op_assign
id|esp_proc_info
comma
dot
id|name
op_assign
l_string|&quot;CyberStorm SCSI&quot;
comma
dot
id|detect
op_assign
id|cyber_esp_detect
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
id|cyber_esp_release
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

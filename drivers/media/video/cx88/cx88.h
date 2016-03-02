multiline_comment|/*&n; * v4l2 device driver for cx2388x based TV cards&n; *&n; * (c) 2003,04 Gerd Knorr &lt;kraxel@bytesex.org&gt; [SUSE Labs]&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;media/video-buf.h&gt;
macro_line|#include &lt;media/tuner.h&gt;
macro_line|#include &lt;media/audiochip.h&gt;
macro_line|#include &quot;btcx-risc.h&quot;
macro_line|#include &quot;cx88-reg.h&quot;
macro_line|#include &lt;linux/version.h&gt;
DECL|macro|CX88_VERSION_CODE
mdefine_line|#define CX88_VERSION_CODE KERNEL_VERSION(0,0,4)
macro_line|#ifndef TRUE
DECL|macro|TRUE
macro_line|# define TRUE (1==1)
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
macro_line|# define FALSE (1==0)
macro_line|#endif
DECL|macro|UNSET
mdefine_line|#define UNSET (-1U)
DECL|macro|CX88_MAXBOARDS
mdefine_line|#define CX88_MAXBOARDS 8
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* defines and enums                                           */
DECL|macro|FORMAT_FLAGS_PACKED
mdefine_line|#define FORMAT_FLAGS_PACKED       0x01
DECL|macro|FORMAT_FLAGS_PLANAR
mdefine_line|#define FORMAT_FLAGS_PLANAR       0x02
DECL|macro|VBI_LINE_COUNT
mdefine_line|#define VBI_LINE_COUNT              17
DECL|macro|VBI_LINE_LENGTH
mdefine_line|#define VBI_LINE_LENGTH           2048
multiline_comment|/* need &quot;shadow&quot; registers for some write-only ones ... */
DECL|macro|SHADOW_AUD_VOL_CTL
mdefine_line|#define SHADOW_AUD_VOL_CTL           1
DECL|macro|SHADOW_AUD_BAL_CTL
mdefine_line|#define SHADOW_AUD_BAL_CTL           2
DECL|macro|SHADOW_MAX
mdefine_line|#define SHADOW_MAX                   2
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* static data                                                 */
DECL|struct|cx8800_tvnorm
r_struct
id|cx8800_tvnorm
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id
id|v4l2_std_id
id|id
suffix:semicolon
DECL|member|cxiformat
id|u32
id|cxiformat
suffix:semicolon
DECL|member|cxoformat
id|u32
id|cxoformat
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cx8800_fmt
r_struct
id|cx8800_fmt
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|fourcc
id|u32
id|fourcc
suffix:semicolon
multiline_comment|/* v4l2 format id */
DECL|member|depth
r_int
id|depth
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|cxformat
id|u32
id|cxformat
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cx88_ctrl
r_struct
id|cx88_ctrl
(brace
DECL|member|v
r_struct
id|v4l2_queryctrl
id|v
suffix:semicolon
DECL|member|off
id|u32
id|off
suffix:semicolon
DECL|member|reg
id|u32
id|reg
suffix:semicolon
DECL|member|sreg
id|u32
id|sreg
suffix:semicolon
DECL|member|mask
id|u32
id|mask
suffix:semicolon
DECL|member|shift
id|u32
id|shift
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* SRAM memory management data (see cx88-core.c)               */
DECL|macro|SRAM_CH21
mdefine_line|#define SRAM_CH21 0   /* video */
DECL|macro|SRAM_CH22
mdefine_line|#define SRAM_CH22 1
DECL|macro|SRAM_CH23
mdefine_line|#define SRAM_CH23 2
DECL|macro|SRAM_CH24
mdefine_line|#define SRAM_CH24 3   /* vbi   */
DECL|macro|SRAM_CH25
mdefine_line|#define SRAM_CH25 4   /* audio */
DECL|macro|SRAM_CH26
mdefine_line|#define SRAM_CH26 5
multiline_comment|/* more */
DECL|struct|sram_channel
r_struct
id|sram_channel
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|cmds_start
id|u32
id|cmds_start
suffix:semicolon
DECL|member|ctrl_start
id|u32
id|ctrl_start
suffix:semicolon
DECL|member|cdt
id|u32
id|cdt
suffix:semicolon
DECL|member|fifo_start
id|u32
id|fifo_start
suffix:semicolon
DECL|member|fifo_size
id|u32
id|fifo_size
suffix:semicolon
DECL|member|ptr1_reg
id|u32
id|ptr1_reg
suffix:semicolon
DECL|member|ptr2_reg
id|u32
id|ptr2_reg
suffix:semicolon
DECL|member|cnt1_reg
id|u32
id|cnt1_reg
suffix:semicolon
DECL|member|cnt2_reg
id|u32
id|cnt2_reg
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sram_channel
id|cx88_sram_channels
(braket
)braket
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* card configuration                                          */
DECL|macro|CX88_BOARD_NOAUTO
mdefine_line|#define CX88_BOARD_NOAUTO        UNSET
DECL|macro|CX88_BOARD_UNKNOWN
mdefine_line|#define CX88_BOARD_UNKNOWN               0
DECL|macro|CX88_BOARD_HAUPPAUGE
mdefine_line|#define CX88_BOARD_HAUPPAUGE             1
DECL|macro|CX88_BOARD_GDI
mdefine_line|#define CX88_BOARD_GDI                   2
DECL|macro|CX88_BOARD_PIXELVIEW
mdefine_line|#define CX88_BOARD_PIXELVIEW             3
DECL|macro|CX88_BOARD_ATI_WONDER_PRO
mdefine_line|#define CX88_BOARD_ATI_WONDER_PRO        4
DECL|macro|CX88_BOARD_WINFAST2000XP
mdefine_line|#define CX88_BOARD_WINFAST2000XP         5
DECL|macro|CX88_BOARD_AVERTV_303
mdefine_line|#define CX88_BOARD_AVERTV_303            6
DECL|macro|CX88_BOARD_MSI_TVANYWHERE_MASTER
mdefine_line|#define CX88_BOARD_MSI_TVANYWHERE_MASTER 7
DECL|macro|CX88_BOARD_WINFAST_DV2000
mdefine_line|#define CX88_BOARD_WINFAST_DV2000        8
DECL|macro|CX88_BOARD_LEADTEK_PVR2000
mdefine_line|#define CX88_BOARD_LEADTEK_PVR2000       9
DECL|macro|CX88_BOARD_IODATA_GVVCP3PCI
mdefine_line|#define CX88_BOARD_IODATA_GVVCP3PCI      10
DECL|macro|CX88_BOARD_PROLINK_PLAYTVPVR
mdefine_line|#define CX88_BOARD_PROLINK_PLAYTVPVR     11
DECL|macro|CX88_BOARD_ASUS_PVR_416
mdefine_line|#define CX88_BOARD_ASUS_PVR_416          12
DECL|macro|CX88_BOARD_MSI_TVANYWHERE
mdefine_line|#define CX88_BOARD_MSI_TVANYWHERE        13
DECL|enum|cx88_itype
r_enum
id|cx88_itype
(brace
DECL|enumerator|CX88_VMUX_COMPOSITE1
id|CX88_VMUX_COMPOSITE1
op_assign
l_int|1
comma
DECL|enumerator|CX88_VMUX_COMPOSITE2
id|CX88_VMUX_COMPOSITE2
op_assign
l_int|2
comma
DECL|enumerator|CX88_VMUX_COMPOSITE3
id|CX88_VMUX_COMPOSITE3
op_assign
l_int|3
comma
DECL|enumerator|CX88_VMUX_COMPOSITE4
id|CX88_VMUX_COMPOSITE4
op_assign
l_int|4
comma
DECL|enumerator|CX88_VMUX_TELEVISION
id|CX88_VMUX_TELEVISION
op_assign
l_int|5
comma
DECL|enumerator|CX88_VMUX_SVIDEO
id|CX88_VMUX_SVIDEO
op_assign
l_int|6
comma
DECL|enumerator|CX88_VMUX_DEBUG
id|CX88_VMUX_DEBUG
op_assign
l_int|7
comma
DECL|enumerator|CX88_RADIO
id|CX88_RADIO
op_assign
l_int|8
comma
)brace
suffix:semicolon
DECL|struct|cx88_input
r_struct
id|cx88_input
(brace
DECL|member|type
r_enum
id|cx88_itype
id|type
suffix:semicolon
DECL|member|vmux
r_int
r_int
id|vmux
suffix:semicolon
DECL|member|gpio0
DECL|member|gpio1
DECL|member|gpio2
DECL|member|gpio3
id|u32
id|gpio0
comma
id|gpio1
comma
id|gpio2
comma
id|gpio3
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cx88_board
r_struct
id|cx88_board
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|tuner_type
r_int
r_int
id|tuner_type
suffix:semicolon
DECL|member|needs_tda9887
r_int
id|needs_tda9887
suffix:colon
l_int|1
suffix:semicolon
DECL|member|input
r_struct
id|cx88_input
id|input
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|radio
r_struct
id|cx88_input
id|radio
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cx88_subid
r_struct
id|cx88_subid
(brace
DECL|member|subvendor
id|u16
id|subvendor
suffix:semicolon
DECL|member|subdevice
id|u16
id|subdevice
suffix:semicolon
DECL|member|card
id|u32
id|card
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INPUT
mdefine_line|#define INPUT(nr) (&amp;cx88_boards[dev-&gt;board].input[nr])
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* device / file handle status                                 */
DECL|macro|RESOURCE_OVERLAY
mdefine_line|#define RESOURCE_OVERLAY       1
DECL|macro|RESOURCE_VIDEO
mdefine_line|#define RESOURCE_VIDEO         2
DECL|macro|RESOURCE_VBI
mdefine_line|#define RESOURCE_VBI           4
singleline_comment|//#define BUFFER_TIMEOUT     (HZ/2)  /* 0.5 seconds */
DECL|macro|BUFFER_TIMEOUT
mdefine_line|#define BUFFER_TIMEOUT     (HZ*2)
r_struct
id|cx8800_dev
suffix:semicolon
multiline_comment|/* buffer for one video frame */
DECL|struct|cx88_buffer
r_struct
id|cx88_buffer
(brace
multiline_comment|/* common v4l buffer stuff -- must be first */
DECL|member|vb
r_struct
id|videobuf_buffer
id|vb
suffix:semicolon
multiline_comment|/* cx88 specific */
DECL|member|bpl
r_int
r_int
id|bpl
suffix:semicolon
DECL|member|risc
r_struct
id|btcx_riscmem
id|risc
suffix:semicolon
DECL|member|fmt
r_struct
id|cx8800_fmt
op_star
id|fmt
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cx88_dmaqueue
r_struct
id|cx88_dmaqueue
(brace
DECL|member|active
r_struct
id|list_head
id|active
suffix:semicolon
DECL|member|queued
r_struct
id|list_head
id|queued
suffix:semicolon
DECL|member|timeout
r_struct
id|timer_list
id|timeout
suffix:semicolon
DECL|member|stopper
r_struct
id|btcx_riscmem
id|stopper
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* video filehandle status */
DECL|struct|cx8800_fh
r_struct
id|cx8800_fh
(brace
DECL|member|dev
r_struct
id|cx8800_dev
op_star
id|dev
suffix:semicolon
DECL|member|type
r_enum
id|v4l2_buf_type
id|type
suffix:semicolon
DECL|member|radio
r_int
id|radio
suffix:semicolon
DECL|member|resources
r_int
r_int
id|resources
suffix:semicolon
multiline_comment|/* video overlay */
DECL|member|win
r_struct
id|v4l2_window
id|win
suffix:semicolon
DECL|member|clips
r_struct
id|v4l2_clip
op_star
id|clips
suffix:semicolon
DECL|member|nclips
r_int
r_int
id|nclips
suffix:semicolon
multiline_comment|/* video capture */
DECL|member|fmt
r_struct
id|cx8800_fmt
op_star
id|fmt
suffix:semicolon
DECL|member|width
DECL|member|height
r_int
r_int
id|width
comma
id|height
suffix:semicolon
DECL|member|vidq
r_struct
id|videobuf_queue
id|vidq
suffix:semicolon
multiline_comment|/* vbi capture */
DECL|member|vbiq
r_struct
id|videobuf_queue
id|vbiq
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cx8800_suspend_state
r_struct
id|cx8800_suspend_state
(brace
DECL|member|pci_cfg
id|u32
id|pci_cfg
(braket
l_int|64
op_div
r_sizeof
(paren
id|u32
)paren
)braket
suffix:semicolon
DECL|member|disabled
r_int
id|disabled
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* global device status */
DECL|struct|cx8800_dev
r_struct
id|cx8800_dev
(brace
DECL|member|devlist
r_struct
id|list_head
id|devlist
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|slock
id|spinlock_t
id|slock
suffix:semicolon
multiline_comment|/* various device info */
DECL|member|resources
r_int
r_int
id|resources
suffix:semicolon
DECL|member|video_dev
r_struct
id|video_device
op_star
id|video_dev
suffix:semicolon
DECL|member|vbi_dev
r_struct
id|video_device
op_star
id|vbi_dev
suffix:semicolon
DECL|member|radio_dev
r_struct
id|video_device
op_star
id|radio_dev
suffix:semicolon
multiline_comment|/* pci i/o */
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
DECL|member|pci_rev
DECL|member|pci_lat
r_int
r_char
id|pci_rev
comma
id|pci_lat
suffix:semicolon
DECL|member|lmmio
id|u32
op_star
id|lmmio
suffix:semicolon
DECL|member|bmmio
id|u8
op_star
id|bmmio
suffix:semicolon
multiline_comment|/* config info */
DECL|member|board
r_int
r_int
id|board
suffix:semicolon
DECL|member|tuner_type
r_int
r_int
id|tuner_type
suffix:semicolon
DECL|member|has_radio
r_int
r_int
id|has_radio
suffix:semicolon
multiline_comment|/* i2c i/o */
DECL|member|i2c_adap
r_struct
id|i2c_adapter
id|i2c_adap
suffix:semicolon
DECL|member|i2c_algo
r_struct
id|i2c_algo_bit_data
id|i2c_algo
suffix:semicolon
DECL|member|i2c_client
r_struct
id|i2c_client
id|i2c_client
suffix:semicolon
DECL|member|i2c_state
DECL|member|i2c_rc
id|u32
id|i2c_state
comma
id|i2c_rc
suffix:semicolon
multiline_comment|/* video overlay */
DECL|member|fbuf
r_struct
id|v4l2_framebuffer
id|fbuf
suffix:semicolon
DECL|member|screen
r_struct
id|cx88_buffer
op_star
id|screen
suffix:semicolon
multiline_comment|/* capture queues */
DECL|member|vidq
r_struct
id|cx88_dmaqueue
id|vidq
suffix:semicolon
DECL|member|vbiq
r_struct
id|cx88_dmaqueue
id|vbiq
suffix:semicolon
multiline_comment|/* various v4l controls */
DECL|member|tvnorm
r_struct
id|cx8800_tvnorm
op_star
id|tvnorm
suffix:semicolon
DECL|member|tvaudio
id|u32
id|tvaudio
suffix:semicolon
DECL|member|input
id|u32
id|input
suffix:semicolon
DECL|member|freq
id|u32
id|freq
suffix:semicolon
multiline_comment|/* other global state info */
DECL|member|shadow
id|u32
id|shadow
(braket
id|SHADOW_MAX
)braket
suffix:semicolon
DECL|member|shutdown
r_int
id|shutdown
suffix:semicolon
DECL|member|tpid
id|pid_t
id|tpid
suffix:semicolon
DECL|member|texit
r_struct
id|completion
id|texit
suffix:semicolon
DECL|member|state
r_struct
id|cx8800_suspend_state
id|state
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
DECL|macro|cx_read
mdefine_line|#define cx_read(reg)             readl(dev-&gt;lmmio + ((reg)&gt;&gt;2))
DECL|macro|cx_write
mdefine_line|#define cx_write(reg,value)      writel((value), dev-&gt;lmmio + ((reg)&gt;&gt;2));
DECL|macro|cx_writeb
mdefine_line|#define cx_writeb(reg,value)     writeb((value), dev-&gt;bmmio + (reg));
DECL|macro|cx_andor
mdefine_line|#define cx_andor(reg,mask,value) &bslash;&n;  writel((readl(dev-&gt;lmmio+((reg)&gt;&gt;2)) &amp; ~(mask)) |&bslash;&n;  ((value) &amp; (mask)), dev-&gt;lmmio+((reg)&gt;&gt;2))
DECL|macro|cx_set
mdefine_line|#define cx_set(reg,bit)          cx_andor((reg),(bit),(bit))
DECL|macro|cx_clear
mdefine_line|#define cx_clear(reg,bit)        cx_andor((reg),(bit),0)
DECL|macro|cx_wait
mdefine_line|#define cx_wait(d) { if (need_resched()) schedule(); else udelay(d); }
multiline_comment|/* shadow registers */
DECL|macro|cx_sread
mdefine_line|#define cx_sread(sreg)&t;&t;    (dev-&gt;shadow[sreg])
DECL|macro|cx_swrite
mdefine_line|#define cx_swrite(sreg,reg,value) &bslash;&n;  (dev-&gt;shadow[sreg] = value, &bslash;&n;   writel(dev-&gt;shadow[sreg], dev-&gt;lmmio + ((reg)&gt;&gt;2)))
DECL|macro|cx_sandor
mdefine_line|#define cx_sandor(sreg,reg,mask,value) &bslash;&n;  (dev-&gt;shadow[sreg] = (dev-&gt;shadow[sreg] &amp; ~(mask)) | ((value) &amp; (mask)), &bslash;&n;   writel(dev-&gt;shadow[sreg], dev-&gt;lmmio + ((reg)&gt;&gt;2)))
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* cx88-core.c                                                 */
r_extern
r_char
op_star
id|cx88_pci_irqs
(braket
l_int|32
)braket
suffix:semicolon
r_extern
r_char
op_star
id|cx88_vid_irqs
(braket
l_int|32
)braket
suffix:semicolon
r_extern
r_void
id|cx88_print_irqbits
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
id|tag
comma
r_char
op_star
op_star
id|strings
comma
id|u32
id|bits
comma
id|u32
id|mask
)paren
suffix:semicolon
r_extern
r_void
id|cx88_print_ioctl
c_func
(paren
r_char
op_star
id|name
comma
r_int
r_int
id|cmd
)paren
suffix:semicolon
r_extern
r_int
id|cx88_risc_buffer
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_struct
id|btcx_riscmem
op_star
id|risc
comma
r_struct
id|scatterlist
op_star
id|sglist
comma
r_int
r_int
id|top_offset
comma
r_int
r_int
id|bottom_offset
comma
r_int
r_int
id|bpl
comma
r_int
r_int
id|padding
comma
r_int
r_int
id|lines
)paren
suffix:semicolon
r_extern
r_int
id|cx88_risc_stopper
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_struct
id|btcx_riscmem
op_star
id|risc
comma
id|u32
id|reg
comma
id|u32
id|mask
comma
id|u32
id|value
)paren
suffix:semicolon
r_extern
r_void
id|cx88_free_buffer
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_struct
id|cx88_buffer
op_star
id|buf
)paren
suffix:semicolon
r_extern
r_void
id|cx88_risc_disasm
c_func
(paren
r_struct
id|cx8800_dev
op_star
id|dev
comma
r_struct
id|btcx_riscmem
op_star
id|risc
)paren
suffix:semicolon
r_extern
r_int
id|cx88_sram_channel_setup
c_func
(paren
r_struct
id|cx8800_dev
op_star
id|dev
comma
r_struct
id|sram_channel
op_star
id|ch
comma
r_int
r_int
id|bpl
comma
id|u32
id|risc
)paren
suffix:semicolon
r_extern
r_void
id|cx88_sram_channel_dump
c_func
(paren
r_struct
id|cx8800_dev
op_star
id|dev
comma
r_struct
id|sram_channel
op_star
id|ch
)paren
suffix:semicolon
r_extern
r_int
id|cx88_pci_quirks
c_func
(paren
r_char
op_star
id|name
comma
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
r_int
op_star
id|latency
)paren
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* cx88-vbi.c                                                  */
r_void
id|cx8800_vbi_fmt
c_func
(paren
r_struct
id|cx8800_dev
op_star
id|dev
comma
r_struct
id|v4l2_format
op_star
id|f
)paren
suffix:semicolon
r_int
id|cx8800_start_vbi_dma
c_func
(paren
r_struct
id|cx8800_dev
op_star
id|dev
comma
r_struct
id|cx88_dmaqueue
op_star
id|q
comma
r_struct
id|cx88_buffer
op_star
id|buf
)paren
suffix:semicolon
r_int
id|cx8800_restart_vbi_queue
c_func
(paren
r_struct
id|cx8800_dev
op_star
id|dev
comma
r_struct
id|cx88_dmaqueue
op_star
id|q
)paren
suffix:semicolon
r_void
id|cx8800_vbi_timeout
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
r_extern
r_struct
id|videobuf_queue_ops
id|cx8800_vbi_qops
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* cx88-i2c.c                                                  */
r_extern
r_int
id|cx8800_i2c_init
c_func
(paren
r_struct
id|cx8800_dev
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|cx8800_call_i2c_clients
c_func
(paren
r_struct
id|cx8800_dev
op_star
id|dev
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* cx88-cards.c                                                */
r_extern
r_struct
id|cx88_board
id|cx88_boards
(braket
)braket
suffix:semicolon
r_extern
r_const
r_int
r_int
id|cx88_bcount
suffix:semicolon
r_extern
r_struct
id|cx88_subid
id|cx88_subids
(braket
)braket
suffix:semicolon
r_extern
r_const
r_int
r_int
id|cx88_idcount
suffix:semicolon
r_extern
r_void
id|cx88_card_list
c_func
(paren
r_struct
id|cx8800_dev
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|cx88_card_setup
c_func
(paren
r_struct
id|cx8800_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* cx88-tvaudio.c                                              */
DECL|macro|WW_NONE
mdefine_line|#define WW_NONE&t;&t; 1
DECL|macro|WW_BTSC
mdefine_line|#define WW_BTSC&t;&t; 2
DECL|macro|WW_NICAM_I
mdefine_line|#define WW_NICAM_I&t; 3
DECL|macro|WW_NICAM_BGDKL
mdefine_line|#define WW_NICAM_BGDKL&t; 4
DECL|macro|WW_A1
mdefine_line|#define WW_A1&t;&t; 5
DECL|macro|WW_A2_BG
mdefine_line|#define WW_A2_BG&t; 6
DECL|macro|WW_A2_DK
mdefine_line|#define WW_A2_DK&t; 7
DECL|macro|WW_A2_M
mdefine_line|#define WW_A2_M&t;&t; 8
DECL|macro|WW_EIAJ
mdefine_line|#define WW_EIAJ&t;&t; 9
DECL|macro|WW_SYSTEM_L_AM
mdefine_line|#define WW_SYSTEM_L_AM&t;10
DECL|macro|WW_I2SPT
mdefine_line|#define WW_I2SPT&t;11
DECL|macro|WW_FM
mdefine_line|#define WW_FM&t;&t;12
r_void
id|cx88_set_tvaudio
c_func
(paren
r_struct
id|cx8800_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|cx88_get_stereo
c_func
(paren
r_struct
id|cx8800_dev
op_star
id|dev
comma
r_struct
id|v4l2_tuner
op_star
id|t
)paren
suffix:semicolon
r_void
id|cx88_set_stereo
c_func
(paren
r_struct
id|cx8800_dev
op_star
id|dev
comma
id|u32
id|mode
)paren
suffix:semicolon
r_int
id|cx88_audio_thread
c_func
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof

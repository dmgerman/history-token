macro_line|#include &lt;linux/config.h&gt;
DECL|macro|PCILYNX_DRIVER_NAME
mdefine_line|#define PCILYNX_DRIVER_NAME      &quot;pcilynx&quot;
DECL|macro|PCILYNX_MAJOR
mdefine_line|#define PCILYNX_MAJOR            177
DECL|macro|PCILYNX_MINOR_AUX_START
mdefine_line|#define PCILYNX_MINOR_AUX_START  0
DECL|macro|PCILYNX_MINOR_ROM_START
mdefine_line|#define PCILYNX_MINOR_ROM_START  16
DECL|macro|PCILYNX_MINOR_RAM_START
mdefine_line|#define PCILYNX_MINOR_RAM_START  32
DECL|macro|PCILYNX_MAX_REGISTER
mdefine_line|#define PCILYNX_MAX_REGISTER     0xfff
DECL|macro|PCILYNX_MAX_MEMORY
mdefine_line|#define PCILYNX_MAX_MEMORY       0xffff
DECL|macro|PCI_DEVICE_ID_TI_PCILYNX
mdefine_line|#define PCI_DEVICE_ID_TI_PCILYNX 0x8000
DECL|macro|MAX_PCILYNX_CARDS
mdefine_line|#define MAX_PCILYNX_CARDS        4
DECL|macro|LOCALRAM_SIZE
mdefine_line|#define LOCALRAM_SIZE            4096
DECL|macro|NUM_ISORCV_PCL
mdefine_line|#define NUM_ISORCV_PCL           4
DECL|macro|MAX_ISORCV_SIZE
mdefine_line|#define MAX_ISORCV_SIZE          2048
DECL|macro|ISORCV_PER_PAGE
mdefine_line|#define ISORCV_PER_PAGE          (PAGE_SIZE / MAX_ISORCV_SIZE)
DECL|macro|ISORCV_PAGES
mdefine_line|#define ISORCV_PAGES             (NUM_ISORCV_PCL / ISORCV_PER_PAGE)
DECL|macro|CHANNEL_LOCALBUS
mdefine_line|#define CHANNEL_LOCALBUS         0
DECL|macro|CHANNEL_ASYNC_RCV
mdefine_line|#define CHANNEL_ASYNC_RCV        1
DECL|macro|CHANNEL_ISO_RCV
mdefine_line|#define CHANNEL_ISO_RCV          2
DECL|macro|CHANNEL_ASYNC_SEND
mdefine_line|#define CHANNEL_ASYNC_SEND       3
DECL|macro|CHANNEL_ISO_SEND
mdefine_line|#define CHANNEL_ISO_SEND         4
DECL|typedef|pcl_t
r_typedef
r_int
id|pcl_t
suffix:semicolon
DECL|struct|ti_lynx
r_struct
id|ti_lynx
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* sequential card number */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_struct
(brace
DECL|member|reg_1394a
r_int
id|reg_1394a
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vendor
id|u32
id|vendor
suffix:semicolon
DECL|member|product
id|u32
id|product
suffix:semicolon
DECL|member|phyic
)brace
id|phyic
suffix:semicolon
DECL|enumerator|clear
DECL|enumerator|have_intr
DECL|enumerator|have_aux_buf
DECL|enumerator|have_pcl_mem
r_enum
(brace
id|clear
comma
id|have_intr
comma
id|have_aux_buf
comma
id|have_pcl_mem
comma
DECL|enumerator|have_1394_buffers
DECL|enumerator|have_iomappings
DECL|enumerator|is_host
DECL|member|state
id|have_1394_buffers
comma
id|have_iomappings
comma
id|is_host
)brace
id|state
suffix:semicolon
multiline_comment|/* remapped memory spaces */
DECL|member|registers
r_void
op_star
id|registers
suffix:semicolon
DECL|member|local_rom
r_void
op_star
id|local_rom
suffix:semicolon
DECL|member|local_ram
r_void
op_star
id|local_ram
suffix:semicolon
DECL|member|aux_port
r_void
op_star
id|aux_port
suffix:semicolon
macro_line|#ifdef CONFIG_IEEE1394_PCILYNX_PORTS
DECL|member|aux_intr_seen
id|atomic_t
id|aux_intr_seen
suffix:semicolon
DECL|member|aux_intr_wait
id|wait_queue_head_t
id|aux_intr_wait
suffix:semicolon
DECL|member|mem_dma_buffer
r_void
op_star
id|mem_dma_buffer
suffix:semicolon
DECL|member|mem_dma_buffer_dma
id|dma_addr_t
id|mem_dma_buffer_dma
suffix:semicolon
DECL|member|mem_dma_mutex
r_struct
id|semaphore
id|mem_dma_mutex
suffix:semicolon
DECL|member|mem_dma_intr_wait
id|wait_queue_head_t
id|mem_dma_intr_wait
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;         * use local RAM of LOCALRAM_SIZE bytes for PCLs, which allows for &n;         * LOCALRAM_SIZE * 8 PCLs (each sized 128 bytes);&n;         * the following is an allocation bitmap &n;         */
DECL|member|pcl_bmap
id|u8
id|pcl_bmap
(braket
id|LOCALRAM_SIZE
op_div
l_int|1024
)braket
suffix:semicolon
macro_line|#ifndef CONFIG_IEEE1394_PCILYNX_LOCALRAM
multiline_comment|/* point to PCLs memory area if needed */
DECL|member|pcl_mem
r_void
op_star
id|pcl_mem
suffix:semicolon
DECL|member|pcl_mem_dma
id|dma_addr_t
id|pcl_mem_dma
suffix:semicolon
macro_line|#endif
multiline_comment|/* PCLs for local mem / aux transfers */
DECL|member|dmem_pcl
id|pcl_t
id|dmem_pcl
suffix:semicolon
multiline_comment|/* IEEE-1394 part follows */
DECL|member|host
r_struct
id|hpsb_host
op_star
id|host
suffix:semicolon
DECL|member|phyid
DECL|member|isroot
r_int
id|phyid
comma
id|isroot
suffix:semicolon
DECL|member|selfid_size
r_int
id|selfid_size
suffix:semicolon
DECL|member|phy_reg0
r_int
id|phy_reg0
suffix:semicolon
DECL|member|phy_reg_lock
id|spinlock_t
id|phy_reg_lock
suffix:semicolon
DECL|member|rcv_pcl_start
DECL|member|rcv_pcl
id|pcl_t
id|rcv_pcl_start
comma
id|rcv_pcl
suffix:semicolon
DECL|member|rcv_page
r_void
op_star
id|rcv_page
suffix:semicolon
DECL|member|rcv_page_dma
id|dma_addr_t
id|rcv_page_dma
suffix:semicolon
DECL|member|rcv_active
r_int
id|rcv_active
suffix:semicolon
DECL|struct|lynx_send_data
r_struct
id|lynx_send_data
(brace
DECL|member|pcl_start
DECL|member|pcl
id|pcl_t
id|pcl_start
comma
id|pcl
suffix:semicolon
DECL|member|queue
DECL|member|queue_last
r_struct
id|hpsb_packet
op_star
id|queue
comma
op_star
id|queue_last
suffix:semicolon
DECL|member|queue_lock
id|spinlock_t
id|queue_lock
suffix:semicolon
DECL|member|header_dma
DECL|member|data_dma
id|dma_addr_t
id|header_dma
comma
id|data_dma
suffix:semicolon
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|async
DECL|member|iso_send
)brace
id|async
comma
id|iso_send
suffix:semicolon
r_struct
(brace
DECL|member|pcl
id|pcl_t
id|pcl
(braket
id|NUM_ISORCV_PCL
)braket
suffix:semicolon
DECL|member|stat
id|u32
id|stat
(braket
id|NUM_ISORCV_PCL
)braket
suffix:semicolon
DECL|member|page
r_void
op_star
id|page
(braket
id|ISORCV_PAGES
)braket
suffix:semicolon
DECL|member|page_dma
id|dma_addr_t
id|page_dma
(braket
id|ISORCV_PAGES
)braket
suffix:semicolon
DECL|member|pcl_start
id|pcl_t
id|pcl_start
suffix:semicolon
DECL|member|chan_count
r_int
id|chan_count
suffix:semicolon
DECL|member|next
DECL|member|last
DECL|member|used
DECL|member|running
r_int
id|next
comma
id|last
comma
id|used
comma
id|running
suffix:semicolon
DECL|member|tq
r_struct
id|tasklet_struct
id|tq
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|iso_rcv
)brace
id|iso_rcv
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* the per-file data structure for mem space access */
DECL|struct|memdata
r_struct
id|memdata
(brace
DECL|member|lynx
r_struct
id|ti_lynx
op_star
id|lynx
suffix:semicolon
DECL|member|cid
r_int
id|cid
suffix:semicolon
DECL|member|aux_intr_last_seen
id|atomic_t
id|aux_intr_last_seen
suffix:semicolon
multiline_comment|/* enum values are the same as LBUS_ADDR_SEL_* values below */
DECL|enumerator|rom
DECL|enumerator|aux
DECL|enumerator|ram
DECL|member|type
r_enum
(brace
id|rom
op_assign
l_int|0x10000
comma
id|aux
op_assign
l_int|0x20000
comma
id|ram
op_assign
l_int|0
)brace
id|type
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Register read and write helper functions.&n; */
DECL|function|reg_write
r_static
r_inline
r_void
id|reg_write
c_func
(paren
r_const
r_struct
id|ti_lynx
op_star
id|lynx
comma
r_int
id|offset
comma
id|u32
id|data
)paren
(brace
id|writel
c_func
(paren
id|data
comma
id|lynx-&gt;registers
op_plus
id|offset
)paren
suffix:semicolon
)brace
DECL|function|reg_read
r_static
r_inline
id|u32
id|reg_read
c_func
(paren
r_const
r_struct
id|ti_lynx
op_star
id|lynx
comma
r_int
id|offset
)paren
(brace
r_return
id|readl
c_func
(paren
id|lynx-&gt;registers
op_plus
id|offset
)paren
suffix:semicolon
)brace
DECL|function|reg_set_bits
r_static
r_inline
r_void
id|reg_set_bits
c_func
(paren
r_const
r_struct
id|ti_lynx
op_star
id|lynx
comma
r_int
id|offset
comma
id|u32
id|mask
)paren
(brace
id|reg_write
c_func
(paren
id|lynx
comma
id|offset
comma
(paren
id|reg_read
c_func
(paren
id|lynx
comma
id|offset
)paren
op_or
id|mask
)paren
)paren
suffix:semicolon
)brace
DECL|function|reg_clear_bits
r_static
r_inline
r_void
id|reg_clear_bits
c_func
(paren
r_const
r_struct
id|ti_lynx
op_star
id|lynx
comma
r_int
id|offset
comma
id|u32
id|mask
)paren
(brace
id|reg_write
c_func
(paren
id|lynx
comma
id|offset
comma
(paren
id|reg_read
c_func
(paren
id|lynx
comma
id|offset
)paren
op_amp
op_complement
id|mask
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* chip register definitions follow */
DECL|macro|PCI_LATENCY_CACHELINE
mdefine_line|#define PCI_LATENCY_CACHELINE             0x0c
DECL|macro|MISC_CONTROL
mdefine_line|#define MISC_CONTROL                      0x40
DECL|macro|MISC_CONTROL_SWRESET
mdefine_line|#define MISC_CONTROL_SWRESET              (1&lt;&lt;0)
DECL|macro|PCI_INT_STATUS
mdefine_line|#define PCI_INT_STATUS                    0x48
DECL|macro|PCI_INT_ENABLE
mdefine_line|#define PCI_INT_ENABLE                    0x4c               
multiline_comment|/* status and enable have identical bit numbers */
DECL|macro|PCI_INT_INT_PEND
mdefine_line|#define PCI_INT_INT_PEND                  (1&lt;&lt;31)
DECL|macro|PCI_INT_FORCED_INT
mdefine_line|#define PCI_INT_FORCED_INT                (1&lt;&lt;30)
DECL|macro|PCI_INT_SLV_ADR_PERR
mdefine_line|#define PCI_INT_SLV_ADR_PERR              (1&lt;&lt;28)
DECL|macro|PCI_INT_SLV_DAT_PERR
mdefine_line|#define PCI_INT_SLV_DAT_PERR              (1&lt;&lt;27)
DECL|macro|PCI_INT_MST_DAT_PERR
mdefine_line|#define PCI_INT_MST_DAT_PERR              (1&lt;&lt;26)
DECL|macro|PCI_INT_MST_DEV_TIMEOUT
mdefine_line|#define PCI_INT_MST_DEV_TIMEOUT           (1&lt;&lt;25)
DECL|macro|PCI_INT_INTERNAL_SLV_TIMEOUT
mdefine_line|#define PCI_INT_INTERNAL_SLV_TIMEOUT      (1&lt;&lt;23)
DECL|macro|PCI_INT_AUX_TIMEOUT
mdefine_line|#define PCI_INT_AUX_TIMEOUT               (1&lt;&lt;18)
DECL|macro|PCI_INT_AUX_INT
mdefine_line|#define PCI_INT_AUX_INT                   (1&lt;&lt;17)
DECL|macro|PCI_INT_1394
mdefine_line|#define PCI_INT_1394                      (1&lt;&lt;16)
DECL|macro|PCI_INT_DMA4_PCL
mdefine_line|#define PCI_INT_DMA4_PCL                  (1&lt;&lt;9)
DECL|macro|PCI_INT_DMA4_HLT
mdefine_line|#define PCI_INT_DMA4_HLT                  (1&lt;&lt;8)
DECL|macro|PCI_INT_DMA3_PCL
mdefine_line|#define PCI_INT_DMA3_PCL                  (1&lt;&lt;7)
DECL|macro|PCI_INT_DMA3_HLT
mdefine_line|#define PCI_INT_DMA3_HLT                  (1&lt;&lt;6)
DECL|macro|PCI_INT_DMA2_PCL
mdefine_line|#define PCI_INT_DMA2_PCL                  (1&lt;&lt;5)
DECL|macro|PCI_INT_DMA2_HLT
mdefine_line|#define PCI_INT_DMA2_HLT                  (1&lt;&lt;4)
DECL|macro|PCI_INT_DMA1_PCL
mdefine_line|#define PCI_INT_DMA1_PCL                  (1&lt;&lt;3)
DECL|macro|PCI_INT_DMA1_HLT
mdefine_line|#define PCI_INT_DMA1_HLT                  (1&lt;&lt;2)
DECL|macro|PCI_INT_DMA0_PCL
mdefine_line|#define PCI_INT_DMA0_PCL                  (1&lt;&lt;1)
DECL|macro|PCI_INT_DMA0_HLT
mdefine_line|#define PCI_INT_DMA0_HLT                  (1&lt;&lt;0)
multiline_comment|/* all DMA interrupts combined: */
DECL|macro|PCI_INT_DMA_ALL
mdefine_line|#define PCI_INT_DMA_ALL                   0x3ff
DECL|macro|PCI_INT_DMA_HLT
mdefine_line|#define PCI_INT_DMA_HLT(chan)             (1 &lt;&lt; (chan * 2))
DECL|macro|PCI_INT_DMA_PCL
mdefine_line|#define PCI_INT_DMA_PCL(chan)             (1 &lt;&lt; (chan * 2 + 1))
DECL|macro|LBUS_ADDR
mdefine_line|#define LBUS_ADDR                         0xb4
DECL|macro|LBUS_ADDR_SEL_RAM
mdefine_line|#define LBUS_ADDR_SEL_RAM                 (0x0&lt;&lt;16)
DECL|macro|LBUS_ADDR_SEL_ROM
mdefine_line|#define LBUS_ADDR_SEL_ROM                 (0x1&lt;&lt;16)
DECL|macro|LBUS_ADDR_SEL_AUX
mdefine_line|#define LBUS_ADDR_SEL_AUX                 (0x2&lt;&lt;16)
DECL|macro|LBUS_ADDR_SEL_ZV
mdefine_line|#define LBUS_ADDR_SEL_ZV                  (0x3&lt;&lt;16)       
DECL|macro|GPIO_CTRL_A
mdefine_line|#define GPIO_CTRL_A                       0xb8
DECL|macro|GPIO_CTRL_B
mdefine_line|#define GPIO_CTRL_B                       0xbc
DECL|macro|GPIO_DATA_BASE
mdefine_line|#define GPIO_DATA_BASE                    0xc0
DECL|macro|DMA_BREG
mdefine_line|#define DMA_BREG(base, chan)              (base + chan * 0x20)
DECL|macro|DMA_SREG
mdefine_line|#define DMA_SREG(base, chan)              (base + chan * 0x10)
DECL|macro|DMA0_PREV_PCL
mdefine_line|#define DMA0_PREV_PCL                     0x100               
DECL|macro|DMA1_PREV_PCL
mdefine_line|#define DMA1_PREV_PCL                     0x120
DECL|macro|DMA2_PREV_PCL
mdefine_line|#define DMA2_PREV_PCL                     0x140
DECL|macro|DMA3_PREV_PCL
mdefine_line|#define DMA3_PREV_PCL                     0x160
DECL|macro|DMA4_PREV_PCL
mdefine_line|#define DMA4_PREV_PCL                     0x180
DECL|macro|DMA_PREV_PCL
mdefine_line|#define DMA_PREV_PCL(chan)                (DMA_BREG(DMA0_PREV_PCL, chan))
DECL|macro|DMA0_CURRENT_PCL
mdefine_line|#define DMA0_CURRENT_PCL                  0x104            
DECL|macro|DMA1_CURRENT_PCL
mdefine_line|#define DMA1_CURRENT_PCL                  0x124
DECL|macro|DMA2_CURRENT_PCL
mdefine_line|#define DMA2_CURRENT_PCL                  0x144
DECL|macro|DMA3_CURRENT_PCL
mdefine_line|#define DMA3_CURRENT_PCL                  0x164
DECL|macro|DMA4_CURRENT_PCL
mdefine_line|#define DMA4_CURRENT_PCL                  0x184
DECL|macro|DMA_CURRENT_PCL
mdefine_line|#define DMA_CURRENT_PCL(chan)             (DMA_BREG(DMA0_CURRENT_PCL, chan))
DECL|macro|DMA0_CHAN_STAT
mdefine_line|#define DMA0_CHAN_STAT                    0x10c
DECL|macro|DMA1_CHAN_STAT
mdefine_line|#define DMA1_CHAN_STAT                    0x12c
DECL|macro|DMA2_CHAN_STAT
mdefine_line|#define DMA2_CHAN_STAT                    0x14c
DECL|macro|DMA3_CHAN_STAT
mdefine_line|#define DMA3_CHAN_STAT                    0x16c
DECL|macro|DMA4_CHAN_STAT
mdefine_line|#define DMA4_CHAN_STAT                    0x18c
DECL|macro|DMA_CHAN_STAT
mdefine_line|#define DMA_CHAN_STAT(chan)               (DMA_BREG(DMA0_CHAN_STAT, chan))
multiline_comment|/* CHAN_STATUS registers share bits */
DECL|macro|DMA_CHAN_STAT_SELFID
mdefine_line|#define DMA_CHAN_STAT_SELFID              (1&lt;&lt;31)
DECL|macro|DMA_CHAN_STAT_ISOPKT
mdefine_line|#define DMA_CHAN_STAT_ISOPKT              (1&lt;&lt;30)
DECL|macro|DMA_CHAN_STAT_PCIERR
mdefine_line|#define DMA_CHAN_STAT_PCIERR              (1&lt;&lt;29)
DECL|macro|DMA_CHAN_STAT_PKTERR
mdefine_line|#define DMA_CHAN_STAT_PKTERR              (1&lt;&lt;28)
DECL|macro|DMA_CHAN_STAT_PKTCMPL
mdefine_line|#define DMA_CHAN_STAT_PKTCMPL             (1&lt;&lt;27)
DECL|macro|DMA_CHAN_STAT_SPECIALACK
mdefine_line|#define DMA_CHAN_STAT_SPECIALACK          (1&lt;&lt;14)
DECL|macro|DMA0_CHAN_CTRL
mdefine_line|#define DMA0_CHAN_CTRL                    0x110              
DECL|macro|DMA1_CHAN_CTRL
mdefine_line|#define DMA1_CHAN_CTRL                    0x130
DECL|macro|DMA2_CHAN_CTRL
mdefine_line|#define DMA2_CHAN_CTRL                    0x150
DECL|macro|DMA3_CHAN_CTRL
mdefine_line|#define DMA3_CHAN_CTRL                    0x170
DECL|macro|DMA4_CHAN_CTRL
mdefine_line|#define DMA4_CHAN_CTRL                    0x190
DECL|macro|DMA_CHAN_CTRL
mdefine_line|#define DMA_CHAN_CTRL(chan)               (DMA_BREG(DMA0_CHAN_CTRL, chan))
multiline_comment|/* CHAN_CTRL registers share bits */
DECL|macro|DMA_CHAN_CTRL_ENABLE
mdefine_line|#define DMA_CHAN_CTRL_ENABLE              (1&lt;&lt;31)      
DECL|macro|DMA_CHAN_CTRL_BUSY
mdefine_line|#define DMA_CHAN_CTRL_BUSY                (1&lt;&lt;30)
DECL|macro|DMA_CHAN_CTRL_LINK
mdefine_line|#define DMA_CHAN_CTRL_LINK                (1&lt;&lt;29)
DECL|macro|DMA0_READY
mdefine_line|#define DMA0_READY                        0x114
DECL|macro|DMA1_READY
mdefine_line|#define DMA1_READY                        0x134
DECL|macro|DMA2_READY
mdefine_line|#define DMA2_READY                        0x154
DECL|macro|DMA3_READY
mdefine_line|#define DMA3_READY                        0x174
DECL|macro|DMA4_READY
mdefine_line|#define DMA4_READY                        0x194
DECL|macro|DMA_READY
mdefine_line|#define DMA_READY(chan)                   (DMA_BREG(DMA0_READY, chan))
DECL|macro|DMA_GLOBAL_REGISTER
mdefine_line|#define DMA_GLOBAL_REGISTER               0x908
DECL|macro|FIFO_SIZES
mdefine_line|#define FIFO_SIZES                        0xa00
DECL|macro|FIFO_CONTROL
mdefine_line|#define FIFO_CONTROL                      0xa10
DECL|macro|FIFO_CONTROL_GRF_FLUSH
mdefine_line|#define FIFO_CONTROL_GRF_FLUSH            (1&lt;&lt;4)
DECL|macro|FIFO_CONTROL_ITF_FLUSH
mdefine_line|#define FIFO_CONTROL_ITF_FLUSH            (1&lt;&lt;3)
DECL|macro|FIFO_CONTROL_ATF_FLUSH
mdefine_line|#define FIFO_CONTROL_ATF_FLUSH            (1&lt;&lt;2)
DECL|macro|FIFO_XMIT_THRESHOLD
mdefine_line|#define FIFO_XMIT_THRESHOLD               0xa14
DECL|macro|DMA0_WORD0_CMP_VALUE
mdefine_line|#define DMA0_WORD0_CMP_VALUE              0xb00
DECL|macro|DMA1_WORD0_CMP_VALUE
mdefine_line|#define DMA1_WORD0_CMP_VALUE              0xb10
DECL|macro|DMA2_WORD0_CMP_VALUE
mdefine_line|#define DMA2_WORD0_CMP_VALUE              0xb20
DECL|macro|DMA3_WORD0_CMP_VALUE
mdefine_line|#define DMA3_WORD0_CMP_VALUE              0xb30
DECL|macro|DMA4_WORD0_CMP_VALUE
mdefine_line|#define DMA4_WORD0_CMP_VALUE              0xb40
DECL|macro|DMA_WORD0_CMP_VALUE
mdefine_line|#define DMA_WORD0_CMP_VALUE(chan)         (DMA_SREG(DMA0_WORD0_CMP_VALUE, chan))
DECL|macro|DMA0_WORD0_CMP_ENABLE
mdefine_line|#define DMA0_WORD0_CMP_ENABLE             0xb04
DECL|macro|DMA1_WORD0_CMP_ENABLE
mdefine_line|#define DMA1_WORD0_CMP_ENABLE             0xb14
DECL|macro|DMA2_WORD0_CMP_ENABLE
mdefine_line|#define DMA2_WORD0_CMP_ENABLE             0xb24
DECL|macro|DMA3_WORD0_CMP_ENABLE
mdefine_line|#define DMA3_WORD0_CMP_ENABLE             0xb34
DECL|macro|DMA4_WORD0_CMP_ENABLE
mdefine_line|#define DMA4_WORD0_CMP_ENABLE             0xb44
DECL|macro|DMA_WORD0_CMP_ENABLE
mdefine_line|#define DMA_WORD0_CMP_ENABLE(chan)        (DMA_SREG(DMA0_WORD0_CMP_ENABLE,chan))
DECL|macro|DMA0_WORD1_CMP_VALUE
mdefine_line|#define DMA0_WORD1_CMP_VALUE              0xb08
DECL|macro|DMA1_WORD1_CMP_VALUE
mdefine_line|#define DMA1_WORD1_CMP_VALUE              0xb18
DECL|macro|DMA2_WORD1_CMP_VALUE
mdefine_line|#define DMA2_WORD1_CMP_VALUE              0xb28
DECL|macro|DMA3_WORD1_CMP_VALUE
mdefine_line|#define DMA3_WORD1_CMP_VALUE              0xb38
DECL|macro|DMA4_WORD1_CMP_VALUE
mdefine_line|#define DMA4_WORD1_CMP_VALUE              0xb48
DECL|macro|DMA_WORD1_CMP_VALUE
mdefine_line|#define DMA_WORD1_CMP_VALUE(chan)         (DMA_SREG(DMA0_WORD1_CMP_VALUE, chan))
DECL|macro|DMA0_WORD1_CMP_ENABLE
mdefine_line|#define DMA0_WORD1_CMP_ENABLE             0xb0c
DECL|macro|DMA1_WORD1_CMP_ENABLE
mdefine_line|#define DMA1_WORD1_CMP_ENABLE             0xb1c
DECL|macro|DMA2_WORD1_CMP_ENABLE
mdefine_line|#define DMA2_WORD1_CMP_ENABLE             0xb2c
DECL|macro|DMA3_WORD1_CMP_ENABLE
mdefine_line|#define DMA3_WORD1_CMP_ENABLE             0xb3c
DECL|macro|DMA4_WORD1_CMP_ENABLE
mdefine_line|#define DMA4_WORD1_CMP_ENABLE             0xb4c
DECL|macro|DMA_WORD1_CMP_ENABLE
mdefine_line|#define DMA_WORD1_CMP_ENABLE(chan)        (DMA_SREG(DMA0_WORD1_CMP_ENABLE,chan))
multiline_comment|/* word 1 compare enable flags */
DECL|macro|DMA_WORD1_CMP_MATCH_OTHERBUS
mdefine_line|#define DMA_WORD1_CMP_MATCH_OTHERBUS      (1&lt;&lt;15)
DECL|macro|DMA_WORD1_CMP_MATCH_BROADCAST
mdefine_line|#define DMA_WORD1_CMP_MATCH_BROADCAST     (1&lt;&lt;14)
DECL|macro|DMA_WORD1_CMP_MATCH_BUS_BCAST
mdefine_line|#define DMA_WORD1_CMP_MATCH_BUS_BCAST     (1&lt;&lt;13)
DECL|macro|DMA_WORD1_CMP_MATCH_LOCAL_NODE
mdefine_line|#define DMA_WORD1_CMP_MATCH_LOCAL_NODE    (1&lt;&lt;12)
DECL|macro|DMA_WORD1_CMP_MATCH_EXACT
mdefine_line|#define DMA_WORD1_CMP_MATCH_EXACT         (1&lt;&lt;11)
DECL|macro|DMA_WORD1_CMP_ENABLE_SELF_ID
mdefine_line|#define DMA_WORD1_CMP_ENABLE_SELF_ID      (1&lt;&lt;10)
DECL|macro|DMA_WORD1_CMP_ENABLE_MASTER
mdefine_line|#define DMA_WORD1_CMP_ENABLE_MASTER       (1&lt;&lt;8)
DECL|macro|LINK_ID
mdefine_line|#define LINK_ID                           0xf00
DECL|macro|LINK_ID_BUS
mdefine_line|#define LINK_ID_BUS(id)                   (id&lt;&lt;22)
DECL|macro|LINK_ID_NODE
mdefine_line|#define LINK_ID_NODE(id)                  (id&lt;&lt;16)
DECL|macro|LINK_CONTROL
mdefine_line|#define LINK_CONTROL                      0xf04
DECL|macro|LINK_CONTROL_BUSY
mdefine_line|#define LINK_CONTROL_BUSY                 (1&lt;&lt;29)
DECL|macro|LINK_CONTROL_TX_ISO_EN
mdefine_line|#define LINK_CONTROL_TX_ISO_EN            (1&lt;&lt;26)
DECL|macro|LINK_CONTROL_RX_ISO_EN
mdefine_line|#define LINK_CONTROL_RX_ISO_EN            (1&lt;&lt;25)
DECL|macro|LINK_CONTROL_TX_ASYNC_EN
mdefine_line|#define LINK_CONTROL_TX_ASYNC_EN          (1&lt;&lt;24)
DECL|macro|LINK_CONTROL_RX_ASYNC_EN
mdefine_line|#define LINK_CONTROL_RX_ASYNC_EN          (1&lt;&lt;23)
DECL|macro|LINK_CONTROL_RESET_TX
mdefine_line|#define LINK_CONTROL_RESET_TX             (1&lt;&lt;21)
DECL|macro|LINK_CONTROL_RESET_RX
mdefine_line|#define LINK_CONTROL_RESET_RX             (1&lt;&lt;20)
DECL|macro|LINK_CONTROL_CYCMASTER
mdefine_line|#define LINK_CONTROL_CYCMASTER            (1&lt;&lt;11)
DECL|macro|LINK_CONTROL_CYCSOURCE
mdefine_line|#define LINK_CONTROL_CYCSOURCE            (1&lt;&lt;10)
DECL|macro|LINK_CONTROL_CYCTIMEREN
mdefine_line|#define LINK_CONTROL_CYCTIMEREN           (1&lt;&lt;9)
DECL|macro|LINK_CONTROL_RCV_CMP_VALID
mdefine_line|#define LINK_CONTROL_RCV_CMP_VALID        (1&lt;&lt;7)
DECL|macro|LINK_CONTROL_SNOOP_ENABLE
mdefine_line|#define LINK_CONTROL_SNOOP_ENABLE         (1&lt;&lt;6)
DECL|macro|CYCLE_TIMER
mdefine_line|#define CYCLE_TIMER                       0xf08
DECL|macro|LINK_PHY
mdefine_line|#define LINK_PHY                          0xf0c
DECL|macro|LINK_PHY_READ
mdefine_line|#define LINK_PHY_READ                     (1&lt;&lt;31)
DECL|macro|LINK_PHY_WRITE
mdefine_line|#define LINK_PHY_WRITE                    (1&lt;&lt;30)
DECL|macro|LINK_PHY_ADDR
mdefine_line|#define LINK_PHY_ADDR(addr)               (addr&lt;&lt;24)
DECL|macro|LINK_PHY_WDATA
mdefine_line|#define LINK_PHY_WDATA(data)              (data&lt;&lt;16)
DECL|macro|LINK_PHY_RADDR
mdefine_line|#define LINK_PHY_RADDR(addr)              (addr&lt;&lt;8)
DECL|macro|LINK_INT_STATUS
mdefine_line|#define LINK_INT_STATUS                   0xf14
DECL|macro|LINK_INT_ENABLE
mdefine_line|#define LINK_INT_ENABLE                   0xf18
multiline_comment|/* status and enable have identical bit numbers */
DECL|macro|LINK_INT_LINK_INT
mdefine_line|#define LINK_INT_LINK_INT                 (1&lt;&lt;31)
DECL|macro|LINK_INT_PHY_TIMEOUT
mdefine_line|#define LINK_INT_PHY_TIMEOUT              (1&lt;&lt;30)
DECL|macro|LINK_INT_PHY_REG_RCVD
mdefine_line|#define LINK_INT_PHY_REG_RCVD             (1&lt;&lt;29)
DECL|macro|LINK_INT_PHY_BUSRESET
mdefine_line|#define LINK_INT_PHY_BUSRESET             (1&lt;&lt;28)
DECL|macro|LINK_INT_TX_RDY
mdefine_line|#define LINK_INT_TX_RDY                   (1&lt;&lt;26)
DECL|macro|LINK_INT_RX_DATA_RDY
mdefine_line|#define LINK_INT_RX_DATA_RDY              (1&lt;&lt;25)
DECL|macro|LINK_INT_ISO_STUCK
mdefine_line|#define LINK_INT_ISO_STUCK                (1&lt;&lt;20)
DECL|macro|LINK_INT_ASYNC_STUCK
mdefine_line|#define LINK_INT_ASYNC_STUCK              (1&lt;&lt;19)
DECL|macro|LINK_INT_SENT_REJECT
mdefine_line|#define LINK_INT_SENT_REJECT              (1&lt;&lt;17)
DECL|macro|LINK_INT_HDR_ERR
mdefine_line|#define LINK_INT_HDR_ERR                  (1&lt;&lt;16)
DECL|macro|LINK_INT_TX_INVALID_TC
mdefine_line|#define LINK_INT_TX_INVALID_TC            (1&lt;&lt;15)
DECL|macro|LINK_INT_CYC_SECOND
mdefine_line|#define LINK_INT_CYC_SECOND               (1&lt;&lt;11)
DECL|macro|LINK_INT_CYC_START
mdefine_line|#define LINK_INT_CYC_START                (1&lt;&lt;10)
DECL|macro|LINK_INT_CYC_DONE
mdefine_line|#define LINK_INT_CYC_DONE                 (1&lt;&lt;9)
DECL|macro|LINK_INT_CYC_PENDING
mdefine_line|#define LINK_INT_CYC_PENDING              (1&lt;&lt;8)
DECL|macro|LINK_INT_CYC_LOST
mdefine_line|#define LINK_INT_CYC_LOST                 (1&lt;&lt;7)
DECL|macro|LINK_INT_CYC_ARB_FAILED
mdefine_line|#define LINK_INT_CYC_ARB_FAILED           (1&lt;&lt;6)
DECL|macro|LINK_INT_GRF_OVERFLOW
mdefine_line|#define LINK_INT_GRF_OVERFLOW             (1&lt;&lt;5)
DECL|macro|LINK_INT_ITF_UNDERFLOW
mdefine_line|#define LINK_INT_ITF_UNDERFLOW            (1&lt;&lt;4)
DECL|macro|LINK_INT_ATF_UNDERFLOW
mdefine_line|#define LINK_INT_ATF_UNDERFLOW            (1&lt;&lt;3)
DECL|macro|LINK_INT_ISOARB_FAILED
mdefine_line|#define LINK_INT_ISOARB_FAILED            (1&lt;&lt;0) 
multiline_comment|/* PHY specifics */
DECL|macro|PHY_VENDORID_TI
mdefine_line|#define PHY_VENDORID_TI                 0x800028
DECL|macro|PHY_PRODUCTID_TSB41LV03
mdefine_line|#define PHY_PRODUCTID_TSB41LV03         0x000000
multiline_comment|/* this is the physical layout of a PCL, its size is 128 bytes */
DECL|struct|ti_pcl
r_struct
id|ti_pcl
(brace
DECL|member|next
id|u32
id|next
suffix:semicolon
DECL|member|async_error_next
id|u32
id|async_error_next
suffix:semicolon
DECL|member|user_data
id|u32
id|user_data
suffix:semicolon
DECL|member|pcl_status
id|u32
id|pcl_status
suffix:semicolon
DECL|member|remaining_transfer_count
id|u32
id|remaining_transfer_count
suffix:semicolon
DECL|member|next_data_buffer
id|u32
id|next_data_buffer
suffix:semicolon
r_struct
(brace
DECL|member|control
id|u32
id|control
suffix:semicolon
DECL|member|pointer
id|u32
id|pointer
suffix:semicolon
DECL|member|buffer
)brace
id|buffer
(braket
l_int|13
)braket
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#include &lt;linux/stddef.h&gt;
DECL|macro|pcloffs
mdefine_line|#define pcloffs(MEMBER) (offsetof(struct ti_pcl, MEMBER))
macro_line|#ifdef CONFIG_IEEE1394_PCILYNX_LOCALRAM
DECL|function|put_pcl
r_static
r_inline
r_void
id|put_pcl
c_func
(paren
r_const
r_struct
id|ti_lynx
op_star
id|lynx
comma
id|pcl_t
id|pclid
comma
r_const
r_struct
id|ti_pcl
op_star
id|pcl
)paren
(brace
r_int
id|i
suffix:semicolon
id|u32
op_star
id|in
op_assign
(paren
id|u32
op_star
)paren
id|pcl
suffix:semicolon
id|u32
op_star
id|out
op_assign
(paren
id|u32
op_star
)paren
(paren
id|lynx-&gt;local_ram
op_plus
id|pclid
op_star
r_sizeof
(paren
r_struct
id|ti_pcl
)paren
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
l_int|32
suffix:semicolon
id|i
op_increment
comma
id|out
op_increment
comma
id|in
op_increment
)paren
(brace
id|writel
c_func
(paren
op_star
id|in
comma
id|out
)paren
suffix:semicolon
)brace
)brace
DECL|function|get_pcl
r_static
r_inline
r_void
id|get_pcl
c_func
(paren
r_const
r_struct
id|ti_lynx
op_star
id|lynx
comma
id|pcl_t
id|pclid
comma
r_struct
id|ti_pcl
op_star
id|pcl
)paren
(brace
r_int
id|i
suffix:semicolon
id|u32
op_star
id|out
op_assign
(paren
id|u32
op_star
)paren
id|pcl
suffix:semicolon
id|u32
op_star
id|in
op_assign
(paren
id|u32
op_star
)paren
(paren
id|lynx-&gt;local_ram
op_plus
id|pclid
op_star
r_sizeof
(paren
r_struct
id|ti_pcl
)paren
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
l_int|32
suffix:semicolon
id|i
op_increment
comma
id|out
op_increment
comma
id|in
op_increment
)paren
(brace
op_star
id|out
op_assign
id|readl
c_func
(paren
id|in
)paren
suffix:semicolon
)brace
)brace
DECL|function|pcl_bus
r_static
r_inline
id|u32
id|pcl_bus
c_func
(paren
r_const
r_struct
id|ti_lynx
op_star
id|lynx
comma
id|pcl_t
id|pclid
)paren
(brace
r_return
id|pci_resource_start
c_func
(paren
id|lynx-&gt;dev
comma
l_int|1
)paren
op_plus
id|pclid
op_star
r_sizeof
(paren
r_struct
id|ti_pcl
)paren
suffix:semicolon
)brace
macro_line|#else /* CONFIG_IEEE1394_PCILYNX_LOCALRAM */
DECL|function|put_pcl
r_static
r_inline
r_void
id|put_pcl
c_func
(paren
r_const
r_struct
id|ti_lynx
op_star
id|lynx
comma
id|pcl_t
id|pclid
comma
r_const
r_struct
id|ti_pcl
op_star
id|pcl
)paren
(brace
id|memcpy_le32
c_func
(paren
(paren
id|u32
op_star
)paren
(paren
id|lynx-&gt;pcl_mem
op_plus
id|pclid
op_star
r_sizeof
(paren
r_struct
id|ti_pcl
)paren
)paren
comma
(paren
id|u32
op_star
)paren
id|pcl
comma
r_sizeof
(paren
r_struct
id|ti_pcl
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_pcl
r_static
r_inline
r_void
id|get_pcl
c_func
(paren
r_const
r_struct
id|ti_lynx
op_star
id|lynx
comma
id|pcl_t
id|pclid
comma
r_struct
id|ti_pcl
op_star
id|pcl
)paren
(brace
id|memcpy_le32
c_func
(paren
(paren
id|u32
op_star
)paren
id|pcl
comma
(paren
id|u32
op_star
)paren
(paren
id|lynx-&gt;pcl_mem
op_plus
id|pclid
op_star
r_sizeof
(paren
r_struct
id|ti_pcl
)paren
)paren
comma
r_sizeof
(paren
r_struct
id|ti_pcl
)paren
)paren
suffix:semicolon
)brace
DECL|function|pcl_bus
r_static
r_inline
id|u32
id|pcl_bus
c_func
(paren
r_const
r_struct
id|ti_lynx
op_star
id|lynx
comma
id|pcl_t
id|pclid
)paren
(brace
r_return
id|lynx-&gt;pcl_mem_dma
op_plus
id|pclid
op_star
r_sizeof
(paren
r_struct
id|ti_pcl
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_IEEE1394_PCILYNX_LOCALRAM */
macro_line|#if defined (CONFIG_IEEE1394_PCILYNX_LOCALRAM) || defined (__BIG_ENDIAN)
DECL|typedef|pcltmp_t
r_typedef
r_struct
id|ti_pcl
id|pcltmp_t
suffix:semicolon
DECL|function|edit_pcl
r_static
r_inline
r_struct
id|ti_pcl
op_star
id|edit_pcl
c_func
(paren
r_const
r_struct
id|ti_lynx
op_star
id|lynx
comma
id|pcl_t
id|pclid
comma
id|pcltmp_t
op_star
id|tmp
)paren
(brace
id|get_pcl
c_func
(paren
id|lynx
comma
id|pclid
comma
id|tmp
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
DECL|function|commit_pcl
r_static
r_inline
r_void
id|commit_pcl
c_func
(paren
r_const
r_struct
id|ti_lynx
op_star
id|lynx
comma
id|pcl_t
id|pclid
comma
id|pcltmp_t
op_star
id|tmp
)paren
(brace
id|put_pcl
c_func
(paren
id|lynx
comma
id|pclid
comma
id|tmp
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|typedef|pcltmp_t
r_typedef
r_int
id|pcltmp_t
suffix:semicolon
multiline_comment|/* just a dummy */
DECL|function|edit_pcl
r_static
r_inline
r_struct
id|ti_pcl
op_star
id|edit_pcl
c_func
(paren
r_const
r_struct
id|ti_lynx
op_star
id|lynx
comma
id|pcl_t
id|pclid
comma
id|pcltmp_t
op_star
id|tmp
)paren
(brace
r_return
id|lynx-&gt;pcl_mem
op_plus
id|pclid
op_star
r_sizeof
(paren
r_struct
id|ti_pcl
)paren
suffix:semicolon
)brace
DECL|function|commit_pcl
r_static
r_inline
r_void
id|commit_pcl
c_func
(paren
r_const
r_struct
id|ti_lynx
op_star
id|lynx
comma
id|pcl_t
id|pclid
comma
id|pcltmp_t
op_star
id|tmp
)paren
(brace
)brace
macro_line|#endif
DECL|function|run_sub_pcl
r_static
r_inline
r_void
id|run_sub_pcl
c_func
(paren
r_const
r_struct
id|ti_lynx
op_star
id|lynx
comma
id|pcl_t
id|pclid
comma
r_int
id|idx
comma
r_int
id|dmachan
)paren
(brace
id|reg_write
c_func
(paren
id|lynx
comma
id|DMA0_CURRENT_PCL
op_plus
id|dmachan
op_star
l_int|0x20
comma
id|pcl_bus
c_func
(paren
id|lynx
comma
id|pclid
)paren
op_plus
id|idx
op_star
l_int|4
)paren
suffix:semicolon
id|reg_write
c_func
(paren
id|lynx
comma
id|DMA0_CHAN_CTRL
op_plus
id|dmachan
op_star
l_int|0x20
comma
id|DMA_CHAN_CTRL_ENABLE
op_or
id|DMA_CHAN_CTRL_LINK
)paren
suffix:semicolon
)brace
DECL|function|run_pcl
r_static
r_inline
r_void
id|run_pcl
c_func
(paren
r_const
r_struct
id|ti_lynx
op_star
id|lynx
comma
id|pcl_t
id|pclid
comma
r_int
id|dmachan
)paren
(brace
id|run_sub_pcl
c_func
(paren
id|lynx
comma
id|pclid
comma
l_int|0
comma
id|dmachan
)paren
suffix:semicolon
)brace
DECL|macro|PCL_NEXT_INVALID
mdefine_line|#define PCL_NEXT_INVALID (1&lt;&lt;0)
multiline_comment|/* transfer commands */
DECL|macro|PCL_CMD_RCV
mdefine_line|#define PCL_CMD_RCV            (0x1&lt;&lt;24)
DECL|macro|PCL_CMD_RCV_AND_UPDATE
mdefine_line|#define PCL_CMD_RCV_AND_UPDATE (0xa&lt;&lt;24)
DECL|macro|PCL_CMD_XMT
mdefine_line|#define PCL_CMD_XMT            (0x2&lt;&lt;24)
DECL|macro|PCL_CMD_UNFXMT
mdefine_line|#define PCL_CMD_UNFXMT         (0xc&lt;&lt;24)
DECL|macro|PCL_CMD_PCI_TO_LBUS
mdefine_line|#define PCL_CMD_PCI_TO_LBUS    (0x8&lt;&lt;24)
DECL|macro|PCL_CMD_LBUS_TO_PCI
mdefine_line|#define PCL_CMD_LBUS_TO_PCI    (0x9&lt;&lt;24)
multiline_comment|/* aux commands */
DECL|macro|PCL_CMD_NOP
mdefine_line|#define PCL_CMD_NOP            (0x0&lt;&lt;24)
DECL|macro|PCL_CMD_LOAD
mdefine_line|#define PCL_CMD_LOAD           (0x3&lt;&lt;24)
DECL|macro|PCL_CMD_STOREQ
mdefine_line|#define PCL_CMD_STOREQ         (0x4&lt;&lt;24)
DECL|macro|PCL_CMD_STORED
mdefine_line|#define PCL_CMD_STORED         (0xb&lt;&lt;24)
DECL|macro|PCL_CMD_STORE0
mdefine_line|#define PCL_CMD_STORE0         (0x5&lt;&lt;24)
DECL|macro|PCL_CMD_STORE1
mdefine_line|#define PCL_CMD_STORE1         (0x6&lt;&lt;24)
DECL|macro|PCL_CMD_COMPARE
mdefine_line|#define PCL_CMD_COMPARE        (0xe&lt;&lt;24)
DECL|macro|PCL_CMD_SWAP_COMPARE
mdefine_line|#define PCL_CMD_SWAP_COMPARE   (0xf&lt;&lt;24)
DECL|macro|PCL_CMD_ADD
mdefine_line|#define PCL_CMD_ADD            (0xd&lt;&lt;24)
DECL|macro|PCL_CMD_BRANCH
mdefine_line|#define PCL_CMD_BRANCH         (0x7&lt;&lt;24)
multiline_comment|/* BRANCH condition codes */
DECL|macro|PCL_COND_DMARDY_SET
mdefine_line|#define PCL_COND_DMARDY_SET    (0x1&lt;&lt;20)
DECL|macro|PCL_COND_DMARDY_CLEAR
mdefine_line|#define PCL_COND_DMARDY_CLEAR  (0x2&lt;&lt;20)
DECL|macro|PCL_GEN_INTR
mdefine_line|#define PCL_GEN_INTR           (1&lt;&lt;19)
DECL|macro|PCL_LAST_BUFF
mdefine_line|#define PCL_LAST_BUFF          (1&lt;&lt;18)
DECL|macro|PCL_LAST_CMD
mdefine_line|#define PCL_LAST_CMD           (PCL_LAST_BUFF)
DECL|macro|PCL_WAITSTAT
mdefine_line|#define PCL_WAITSTAT           (1&lt;&lt;17)
DECL|macro|PCL_BIGENDIAN
mdefine_line|#define PCL_BIGENDIAN          (1&lt;&lt;16)
DECL|macro|PCL_ISOMODE
mdefine_line|#define PCL_ISOMODE            (1&lt;&lt;12)
DECL|macro|_
mdefine_line|#define _(x) (__constant_cpu_to_be32(x))
DECL|variable|lynx_csr_rom
r_static
id|quadlet_t
id|lynx_csr_rom
(braket
)braket
op_assign
(brace
multiline_comment|/* bus info block     offset (hex) */
id|_
c_func
(paren
l_int|0x04040000
)paren
comma
multiline_comment|/* info/CRC length, CRC              400  */
id|_
c_func
(paren
l_int|0x31333934
)paren
comma
multiline_comment|/* 1394 magic number                 404  */
id|_
c_func
(paren
l_int|0xf064a000
)paren
comma
multiline_comment|/* misc. settings                    408  */
id|_
c_func
(paren
l_int|0x08002850
)paren
comma
multiline_comment|/* vendor ID, chip ID high           40c  */
id|_
c_func
(paren
l_int|0x0000ffff
)paren
comma
multiline_comment|/* chip ID low                       410  */
multiline_comment|/* root directory */
id|_
c_func
(paren
l_int|0x00090000
)paren
comma
multiline_comment|/* directory length, CRC             414  */
id|_
c_func
(paren
l_int|0x03080028
)paren
comma
multiline_comment|/* vendor ID (Texas Instr.)          418  */
id|_
c_func
(paren
l_int|0x81000008
)paren
comma
multiline_comment|/* offset to textual ID              41c  */
id|_
c_func
(paren
l_int|0x0c000200
)paren
comma
multiline_comment|/* node capabilities                 420  */
id|_
c_func
(paren
l_int|0x8d00000e
)paren
comma
multiline_comment|/* offset to unique ID               424  */
id|_
c_func
(paren
l_int|0xc7000010
)paren
comma
multiline_comment|/* offset to module independent info 428  */
id|_
c_func
(paren
l_int|0x04000000
)paren
comma
multiline_comment|/* module hardware version           42c  */
id|_
c_func
(paren
l_int|0x81000014
)paren
comma
multiline_comment|/* offset to textual ID              430  */
id|_
c_func
(paren
l_int|0x09000000
)paren
comma
multiline_comment|/* node hardware version             434  */
id|_
c_func
(paren
l_int|0x81000018
)paren
comma
multiline_comment|/* offset to textual ID              438  */
multiline_comment|/* module vendor ID textual */
id|_
c_func
(paren
l_int|0x00070000
)paren
comma
multiline_comment|/* CRC length, CRC                   43c  */
id|_
c_func
(paren
l_int|0x00000000
)paren
comma
multiline_comment|/*                                   440  */
id|_
c_func
(paren
l_int|0x00000000
)paren
comma
multiline_comment|/*                                   444  */
id|_
c_func
(paren
l_int|0x54455841
)paren
comma
multiline_comment|/* &quot;Texas Instruments&quot;               448  */
id|_
c_func
(paren
l_int|0x5320494e
)paren
comma
multiline_comment|/*                                   44c  */
id|_
c_func
(paren
l_int|0x53545255
)paren
comma
multiline_comment|/*                                   450  */
id|_
c_func
(paren
l_int|0x4d454e54
)paren
comma
multiline_comment|/*                                   454  */
id|_
c_func
(paren
l_int|0x53000000
)paren
comma
multiline_comment|/*                                   458  */
multiline_comment|/* node unique ID leaf */
id|_
c_func
(paren
l_int|0x00020000
)paren
comma
multiline_comment|/* CRC length, CRC                   45c  */
id|_
c_func
(paren
l_int|0x08002850
)paren
comma
multiline_comment|/* vendor ID, chip ID high           460  */
id|_
c_func
(paren
l_int|0x0000ffff
)paren
comma
multiline_comment|/* chip ID low                       464  */
multiline_comment|/* module dependent info */
id|_
c_func
(paren
l_int|0x00050000
)paren
comma
multiline_comment|/* CRC length, CRC                   468  */
id|_
c_func
(paren
l_int|0x81000012
)paren
comma
multiline_comment|/* offset to module textual ID       46c  */
id|_
c_func
(paren
l_int|0x81000017
)paren
comma
multiline_comment|/* textual descriptor                470  */
id|_
c_func
(paren
l_int|0x39010000
)paren
comma
multiline_comment|/* SRAM size                         474  */
id|_
c_func
(paren
l_int|0x3a010000
)paren
comma
multiline_comment|/* AUXRAM size                       478  */
id|_
c_func
(paren
l_int|0x3b000000
)paren
comma
multiline_comment|/* AUX device                        47c  */
multiline_comment|/* module textual ID */
id|_
c_func
(paren
l_int|0x00050000
)paren
comma
multiline_comment|/* CRC length, CRC                   480  */
id|_
c_func
(paren
l_int|0x00000000
)paren
comma
multiline_comment|/*                                   484  */
id|_
c_func
(paren
l_int|0x00000000
)paren
comma
multiline_comment|/*                                   488  */
id|_
c_func
(paren
l_int|0x54534231
)paren
comma
multiline_comment|/* &quot;TSB12LV21&quot;                       48c  */
id|_
c_func
(paren
l_int|0x324c5632
)paren
comma
multiline_comment|/*                                   490  */
id|_
c_func
(paren
l_int|0x31000000
)paren
comma
multiline_comment|/*                                   494  */
multiline_comment|/* part number */
id|_
c_func
(paren
l_int|0x00060000
)paren
comma
multiline_comment|/* CRC length, CRC                   498  */
id|_
c_func
(paren
l_int|0x00000000
)paren
comma
multiline_comment|/*                                   49c  */
id|_
c_func
(paren
l_int|0x00000000
)paren
comma
multiline_comment|/*                                   4a0  */
id|_
c_func
(paren
l_int|0x39383036
)paren
comma
multiline_comment|/* &quot;9806000-0001&quot;                    4a4  */
id|_
c_func
(paren
l_int|0x3030302d
)paren
comma
multiline_comment|/*                                   4a8  */
id|_
c_func
(paren
l_int|0x30303031
)paren
comma
multiline_comment|/*                                   4ac  */
id|_
c_func
(paren
l_int|0x20000001
)paren
comma
multiline_comment|/*                                   4b0  */
multiline_comment|/* module hardware version textual */
id|_
c_func
(paren
l_int|0x00050000
)paren
comma
multiline_comment|/* CRC length, CRC                   4b4  */
id|_
c_func
(paren
l_int|0x00000000
)paren
comma
multiline_comment|/*                                   4b8  */
id|_
c_func
(paren
l_int|0x00000000
)paren
comma
multiline_comment|/*                                   4bc  */
id|_
c_func
(paren
l_int|0x5453424b
)paren
comma
multiline_comment|/* &quot;TSBKPCITST&quot;                      4c0  */
id|_
c_func
(paren
l_int|0x50434954
)paren
comma
multiline_comment|/*                                   4c4  */
id|_
c_func
(paren
l_int|0x53540000
)paren
comma
multiline_comment|/*                                   4c8  */
multiline_comment|/* node hardware version textual */
id|_
c_func
(paren
l_int|0x00050000
)paren
comma
multiline_comment|/* CRC length, CRC                   4d0  */
id|_
c_func
(paren
l_int|0x00000000
)paren
comma
multiline_comment|/*                                   4d4  */
id|_
c_func
(paren
l_int|0x00000000
)paren
comma
multiline_comment|/*                                   4d8  */
id|_
c_func
(paren
l_int|0x54534232
)paren
comma
multiline_comment|/* &quot;TSB21LV03&quot;                       4dc  */
id|_
c_func
(paren
l_int|0x314c5630
)paren
comma
multiline_comment|/*                                   4e0  */
id|_
c_func
(paren
l_int|0x33000000
)paren
multiline_comment|/*                                   4e4  */
)brace
suffix:semicolon
DECL|macro|_
macro_line|#undef _
eof

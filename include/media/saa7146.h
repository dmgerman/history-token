macro_line|#ifndef __SAA7146__
DECL|macro|__SAA7146__
mdefine_line|#define __SAA7146__
macro_line|#include &lt;linux/version.h&gt;&t;/* for version macros */
macro_line|#include &lt;linux/module.h&gt;&t;/* for module-version */
macro_line|#include &lt;linux/delay.h&gt;&t;/* for delay-stuff */
macro_line|#include &lt;linux/slab.h&gt;&t;&t;/* for kmalloc/kfree */
macro_line|#include &lt;linux/pci.h&gt;&t;&t;/* for pci-config-stuff, vendor ids etc. */
macro_line|#include &lt;linux/init.h&gt;&t;&t;/* for &quot;__init&quot; */
macro_line|#include &lt;linux/interrupt.h&gt;&t;/* for IMMEDIATE_BH */
macro_line|#include &lt;linux/kmod.h&gt;&t;&t;/* for kernel module loader */
macro_line|#include &lt;linux/i2c.h&gt;&t;&t;/* for i2c subsystem */
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* for accessing devices */
macro_line|#include &lt;linux/stringify.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;&t;/* for vmalloc() */
macro_line|#include &lt;linux/mm.h&gt;&t;&t;/* for vmalloc_to_page() */
multiline_comment|/* ugly, but necessary to build the dvb stuff under 2.4. */
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,51)
macro_line|#include &quot;dvb_functions.h&quot;
macro_line|#endif
DECL|macro|SAA7146_VERSION_CODE
mdefine_line|#define SAA7146_VERSION_CODE KERNEL_VERSION(0,5,0)
DECL|macro|saa7146_write
mdefine_line|#define saa7146_write(sxy,adr,dat)    writel((dat),(sxy-&gt;mem+(adr)))
DECL|macro|saa7146_read
mdefine_line|#define saa7146_read(sxy,adr)         readl(sxy-&gt;mem+(adr))
r_extern
r_int
r_int
id|saa7146_debug
suffix:semicolon
singleline_comment|//#define DEBUG_PROLOG printk(&quot;(0x%08x)(0x%08x) %s: %s(): &quot;,(dev==0?-1:(dev-&gt;mem==0?-1:saa7146_read(dev,RPS_ADDR0))),(dev==0?-1:(dev-&gt;mem==0?-1:saa7146_read(dev,IER))),__stringify(KBUILD_MODNAME),__FUNCTION__)
macro_line|#ifndef DEBUG_VARIABLE
DECL|macro|DEBUG_VARIABLE
mdefine_line|#define DEBUG_VARIABLE saa7146_debug
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,51)
DECL|macro|DEBUG_PROLOG
mdefine_line|#define DEBUG_PROLOG printk(&quot;%s: %s(): &quot;,__stringify(KBUILD_BASENAME),__FUNCTION__)
DECL|macro|INFO
mdefine_line|#define INFO(x) { printk(&quot;%s: &quot;,__stringify(KBUILD_BASENAME)); printk x; }
macro_line|#else
DECL|macro|DEBUG_PROLOG
mdefine_line|#define DEBUG_PROLOG printk(&quot;%s: %s(): &quot;,__stringify(KBUILD_MODNAME),__FUNCTION__)
DECL|macro|INFO
mdefine_line|#define INFO(x) { printk(&quot;%s: &quot;,__stringify(KBUILD_MODNAME)); printk x; }
macro_line|#endif
DECL|macro|ERR
mdefine_line|#define ERR(x) { DEBUG_PROLOG; printk x; }
DECL|macro|DEB_S
mdefine_line|#define DEB_S(x)    if (0!=(DEBUG_VARIABLE&amp;0x01)) { DEBUG_PROLOG; printk x; } /* simple debug messages */
DECL|macro|DEB_D
mdefine_line|#define DEB_D(x)    if (0!=(DEBUG_VARIABLE&amp;0x02)) { DEBUG_PROLOG; printk x; } /* more detailed debug messages */
DECL|macro|DEB_EE
mdefine_line|#define DEB_EE(x)   if (0!=(DEBUG_VARIABLE&amp;0x04)) { DEBUG_PROLOG; printk x; } /* print enter and exit of functions */
DECL|macro|DEB_I2C
mdefine_line|#define DEB_I2C(x)  if (0!=(DEBUG_VARIABLE&amp;0x08)) { DEBUG_PROLOG; printk x; } /* i2c debug messages */
DECL|macro|DEB_VBI
mdefine_line|#define DEB_VBI(x)  if (0!=(DEBUG_VARIABLE&amp;0x10)) { DEBUG_PROLOG; printk x; } /* vbi debug messages */
DECL|macro|DEB_INT
mdefine_line|#define DEB_INT(x)  if (0!=(DEBUG_VARIABLE&amp;0x20)) { DEBUG_PROLOG; printk x; } /* interrupt debug messages */
DECL|macro|DEB_CAP
mdefine_line|#define DEB_CAP(x)  if (0!=(DEBUG_VARIABLE&amp;0x40)) { DEBUG_PROLOG; printk x; } /* capture debug messages */
DECL|macro|IER_DISABLE
mdefine_line|#define IER_DISABLE(x,y) &bslash;&n;&t;saa7146_write(x, IER, saa7146_read(x, IER) &amp; ~(y));
DECL|macro|IER_ENABLE
mdefine_line|#define IER_ENABLE(x,y) &bslash;&n;&t;saa7146_write(x, IER, saa7146_read(x, IER) | (y));
r_struct
id|saa7146_dev
suffix:semicolon
r_struct
id|saa7146_extension
suffix:semicolon
r_struct
id|saa7146_vv
suffix:semicolon
multiline_comment|/* saa7146 page table */
DECL|struct|saa7146_pgtable
r_struct
id|saa7146_pgtable
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|cpu
id|u32
op_star
id|cpu
suffix:semicolon
DECL|member|dma
id|dma_addr_t
id|dma
suffix:semicolon
multiline_comment|/* used for offsets for u,v planes for planar capture modes */
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* used for custom pagetables (used for example by budget dvb cards) */
DECL|member|slist
r_struct
id|scatterlist
op_star
id|slist
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|saa7146_pci_extension_data
r_struct
id|saa7146_pci_extension_data
(brace
DECL|member|ext
r_struct
id|saa7146_extension
op_star
id|ext
suffix:semicolon
DECL|member|ext_priv
r_void
op_star
id|ext_priv
suffix:semicolon
multiline_comment|/* most likely a name string */
)brace
suffix:semicolon
DECL|macro|MAKE_EXTENSION_PCI
mdefine_line|#define MAKE_EXTENSION_PCI(x_var, x_vendor, x_device)&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.vendor    = PCI_VENDOR_ID_PHILIPS,&t;&t;&bslash;&n;&t;&t;.device&t;   = PCI_DEVICE_ID_PHILIPS_SAA7146,&t;&bslash;&n;&t;&t;.subvendor = x_vendor,&t;&t;&t;&t;&bslash;&n;&t;&t;.subdevice = x_device,&t;&t;&t;&t;&bslash;&n;&t;&t;.driver_data = (unsigned long)&amp; x_var,&t;&t;&bslash;&n;&t;}
DECL|struct|saa7146_extension
r_struct
id|saa7146_extension
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* name of the device */
DECL|macro|SAA7146_USE_I2C_IRQ
mdefine_line|#define SAA7146_USE_I2C_IRQ&t;0x1
DECL|macro|SAA7146_I2C_SHORT_DELAY
mdefine_line|#define SAA7146_I2C_SHORT_DELAY&t;0x2
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* pairs of subvendor and subdevice ids for&n;&t;   supported devices, last entry 0xffff, 0xfff */
DECL|member|module
r_struct
id|module
op_star
id|module
suffix:semicolon
DECL|member|driver
r_struct
id|pci_driver
id|driver
suffix:semicolon
DECL|member|pci_tbl
r_struct
id|pci_device_id
op_star
id|pci_tbl
suffix:semicolon
multiline_comment|/* extension functions */
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|saa7146_dev
op_star
)paren
suffix:semicolon
DECL|member|attach
r_int
(paren
op_star
id|attach
)paren
(paren
r_struct
id|saa7146_dev
op_star
comma
r_struct
id|saa7146_pci_extension_data
op_star
)paren
suffix:semicolon
DECL|member|detach
r_int
(paren
op_star
id|detach
)paren
(paren
r_struct
id|saa7146_dev
op_star
)paren
suffix:semicolon
DECL|member|irq_mask
id|u32
id|irq_mask
suffix:semicolon
multiline_comment|/* mask to indicate, which irq-events are handled by the extension */
DECL|member|irq_func
r_void
(paren
op_star
id|irq_func
)paren
(paren
r_struct
id|saa7146_dev
op_star
comma
id|u32
op_star
id|irq_mask
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|saa7146_dma
r_struct
id|saa7146_dma
(brace
DECL|member|dma_handle
id|dma_addr_t
id|dma_handle
suffix:semicolon
DECL|member|cpu_addr
id|u32
op_star
id|cpu_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|saa7146_dev
r_struct
id|saa7146_dev
(brace
DECL|member|module
r_struct
id|module
op_star
id|module
suffix:semicolon
DECL|member|item
r_struct
id|list_head
id|item
suffix:semicolon
multiline_comment|/* different device locks */
DECL|member|slock
id|spinlock_t
id|slock
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|mem
r_int
r_char
id|__iomem
op_star
id|mem
suffix:semicolon
multiline_comment|/* pointer to mapped IO memory */
DECL|member|revision
r_int
id|revision
suffix:semicolon
multiline_comment|/* chip revision; needed for bug-workarounds*/
multiline_comment|/* pci-device &amp; irq stuff*/
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
DECL|member|int_todo
id|u32
id|int_todo
suffix:semicolon
DECL|member|int_slock
id|spinlock_t
id|int_slock
suffix:semicolon
multiline_comment|/* extension handling */
DECL|member|ext
r_struct
id|saa7146_extension
op_star
id|ext
suffix:semicolon
multiline_comment|/* indicates if handled by extension */
DECL|member|ext_priv
r_void
op_star
id|ext_priv
suffix:semicolon
multiline_comment|/* pointer for extension private use (most likely some private data) */
DECL|member|ext_vv_data
r_struct
id|saa7146_ext_vv
op_star
id|ext_vv_data
suffix:semicolon
multiline_comment|/* per device video/vbi informations (if available) */
DECL|member|vv_data
r_struct
id|saa7146_vv
op_star
id|vv_data
suffix:semicolon
DECL|member|vv_callback
r_void
(paren
op_star
id|vv_callback
)paren
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_int
r_int
id|status
)paren
suffix:semicolon
multiline_comment|/* i2c-stuff */
DECL|member|i2c_lock
r_struct
id|semaphore
id|i2c_lock
suffix:semicolon
DECL|member|i2c_bitrate
id|u32
id|i2c_bitrate
suffix:semicolon
DECL|member|d_i2c
r_struct
id|saa7146_dma
id|d_i2c
suffix:semicolon
multiline_comment|/* pointer to i2c memory */
DECL|member|i2c_wq
id|wait_queue_head_t
id|i2c_wq
suffix:semicolon
DECL|member|i2c_op
r_int
id|i2c_op
suffix:semicolon
multiline_comment|/* memories */
DECL|member|d_rps0
r_struct
id|saa7146_dma
id|d_rps0
suffix:semicolon
DECL|member|d_rps1
r_struct
id|saa7146_dma
id|d_rps1
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* from saa7146_i2c.c */
r_int
id|saa7146_i2c_adapter_prepare
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_struct
id|i2c_adapter
op_star
id|i2c_adapter
comma
id|u32
id|bitrate
)paren
suffix:semicolon
r_int
id|saa7146_i2c_transfer
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|saa
comma
r_const
r_struct
id|i2c_msg
id|msgs
(braket
)braket
comma
r_int
id|num
comma
r_int
id|retries
)paren
suffix:semicolon
multiline_comment|/* from saa7146_core.c */
r_extern
r_struct
id|list_head
id|saa7146_devices
suffix:semicolon
r_extern
r_struct
id|semaphore
id|saa7146_devices_lock
suffix:semicolon
r_int
id|saa7146_register_extension
c_func
(paren
r_struct
id|saa7146_extension
op_star
)paren
suffix:semicolon
r_int
id|saa7146_unregister_extension
c_func
(paren
r_struct
id|saa7146_extension
op_star
)paren
suffix:semicolon
r_struct
id|saa7146_format
op_star
id|format_by_fourcc
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_int
id|fourcc
)paren
suffix:semicolon
r_int
id|saa7146_pgtable_alloc
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_struct
id|saa7146_pgtable
op_star
id|pt
)paren
suffix:semicolon
r_void
id|saa7146_pgtable_free
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_struct
id|saa7146_pgtable
op_star
id|pt
)paren
suffix:semicolon
r_int
id|saa7146_pgtable_build_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_struct
id|saa7146_pgtable
op_star
id|pt
comma
r_struct
id|scatterlist
op_star
id|list
comma
r_int
id|length
)paren
suffix:semicolon
r_char
op_star
id|saa7146_vmalloc_build_pgtable
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
id|length
comma
r_struct
id|saa7146_pgtable
op_star
id|pt
)paren
suffix:semicolon
r_void
id|saa7146_setgpio
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_int
id|port
comma
id|u32
id|data
)paren
suffix:semicolon
r_int
id|saa7146_wait_for_debi_done
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* some memory sizes */
DECL|macro|SAA7146_I2C_MEM
mdefine_line|#define SAA7146_I2C_MEM&t;&t;( 1*PAGE_SIZE)
DECL|macro|SAA7146_RPS_MEM
mdefine_line|#define SAA7146_RPS_MEM&t;&t;( 1*PAGE_SIZE)
multiline_comment|/* some i2c constants */
DECL|macro|SAA7146_I2C_TIMEOUT
mdefine_line|#define SAA7146_I2C_TIMEOUT&t;100&t;/* i2c-timeout-value in ms */
DECL|macro|SAA7146_I2C_RETRIES
mdefine_line|#define SAA7146_I2C_RETRIES &t;3&t;/* how many times shall we retry an i2c-operation? */
DECL|macro|SAA7146_I2C_DELAY
mdefine_line|#define SAA7146_I2C_DELAY &t;5&t;/* time we wait after certain i2c-operations */
multiline_comment|/* unsorted defines */
DECL|macro|ME1
mdefine_line|#define ME1    0x0000000800
DECL|macro|PV1
mdefine_line|#define PV1    0x0000000008
multiline_comment|/* gpio defines */
DECL|macro|SAA7146_GPIO_INPUT
mdefine_line|#define SAA7146_GPIO_INPUT 0x00
DECL|macro|SAA7146_GPIO_IRQHI
mdefine_line|#define SAA7146_GPIO_IRQHI 0x10
DECL|macro|SAA7146_GPIO_IRQLO
mdefine_line|#define SAA7146_GPIO_IRQLO 0x20
DECL|macro|SAA7146_GPIO_IRQHL
mdefine_line|#define SAA7146_GPIO_IRQHL 0x30
DECL|macro|SAA7146_GPIO_OUTLO
mdefine_line|#define SAA7146_GPIO_OUTLO 0x40
DECL|macro|SAA7146_GPIO_OUTHI
mdefine_line|#define SAA7146_GPIO_OUTHI 0x50
multiline_comment|/* debi defines */
DECL|macro|DEBINOSWAP
mdefine_line|#define DEBINOSWAP 0x000e0000
multiline_comment|/* define for the register programming sequencer (rps) */
DECL|macro|CMD_NOP
mdefine_line|#define CMD_NOP&t;&t;0x00000000  /* No operation */
DECL|macro|CMD_CLR_EVENT
mdefine_line|#define CMD_CLR_EVENT&t;0x00000000  /* Clear event */
DECL|macro|CMD_SET_EVENT
mdefine_line|#define CMD_SET_EVENT&t;0x10000000  /* Set signal event */
DECL|macro|CMD_PAUSE
mdefine_line|#define CMD_PAUSE&t;0x20000000  /* Pause */
DECL|macro|CMD_CHECK_LATE
mdefine_line|#define CMD_CHECK_LATE&t;0x30000000  /* Check late */
DECL|macro|CMD_UPLOAD
mdefine_line|#define CMD_UPLOAD&t;0x40000000  /* Upload */
DECL|macro|CMD_STOP
mdefine_line|#define CMD_STOP&t;0x50000000  /* Stop */
DECL|macro|CMD_INTERRUPT
mdefine_line|#define CMD_INTERRUPT&t;0x60000000  /* Interrupt */
DECL|macro|CMD_JUMP
mdefine_line|#define CMD_JUMP&t;0x80000000  /* Jump */
DECL|macro|CMD_WR_REG
mdefine_line|#define CMD_WR_REG&t;0x90000000  /* Write (load) register */
DECL|macro|CMD_RD_REG
mdefine_line|#define CMD_RD_REG&t;0xa0000000  /* Read (store) register */
DECL|macro|CMD_WR_REG_MASK
mdefine_line|#define CMD_WR_REG_MASK&t;0xc0000000  /* Write register with mask */
DECL|macro|CMD_OAN
mdefine_line|#define CMD_OAN&t;&t;MASK_27
DECL|macro|CMD_INV
mdefine_line|#define CMD_INV&t;&t;MASK_26
DECL|macro|CMD_SIG4
mdefine_line|#define CMD_SIG4&t;MASK_25
DECL|macro|CMD_SIG3
mdefine_line|#define CMD_SIG3&t;MASK_24
DECL|macro|CMD_SIG2
mdefine_line|#define CMD_SIG2&t;MASK_23
DECL|macro|CMD_SIG1
mdefine_line|#define CMD_SIG1&t;MASK_22
DECL|macro|CMD_SIG0
mdefine_line|#define CMD_SIG0&t;MASK_21
DECL|macro|CMD_O_FID_B
mdefine_line|#define CMD_O_FID_B&t;MASK_14
DECL|macro|CMD_E_FID_B
mdefine_line|#define CMD_E_FID_B&t;MASK_13
DECL|macro|CMD_O_FID_A
mdefine_line|#define CMD_O_FID_A&t;MASK_12
DECL|macro|CMD_E_FID_A
mdefine_line|#define CMD_E_FID_A&t;MASK_11
multiline_comment|/* some events and command modifiers for rps1 squarewave generator */
DECL|macro|EVT_HS
mdefine_line|#define EVT_HS          (1&lt;&lt;15)     
singleline_comment|// Source Line Threshold reached
DECL|macro|EVT_VBI_B
mdefine_line|#define EVT_VBI_B       (1&lt;&lt;9)      
singleline_comment|// VSYNC Event
DECL|macro|RPS_OAN
mdefine_line|#define RPS_OAN         (1&lt;&lt;27)     
singleline_comment|// 1: OR events, 0: AND events
DECL|macro|RPS_INV
mdefine_line|#define RPS_INV         (1&lt;&lt;26)     
singleline_comment|// Invert (compound) event
DECL|macro|GPIO3_MSK
mdefine_line|#define GPIO3_MSK       0xFF000000  
singleline_comment|// GPIO #3 control bits
multiline_comment|/* Bit mask constants */
DECL|macro|MASK_00
mdefine_line|#define MASK_00   0x00000001    /* Mask value for bit 0 */
DECL|macro|MASK_01
mdefine_line|#define MASK_01   0x00000002    /* Mask value for bit 1 */
DECL|macro|MASK_02
mdefine_line|#define MASK_02   0x00000004    /* Mask value for bit 2 */
DECL|macro|MASK_03
mdefine_line|#define MASK_03   0x00000008    /* Mask value for bit 3 */
DECL|macro|MASK_04
mdefine_line|#define MASK_04   0x00000010    /* Mask value for bit 4 */
DECL|macro|MASK_05
mdefine_line|#define MASK_05   0x00000020    /* Mask value for bit 5 */
DECL|macro|MASK_06
mdefine_line|#define MASK_06   0x00000040    /* Mask value for bit 6 */
DECL|macro|MASK_07
mdefine_line|#define MASK_07   0x00000080    /* Mask value for bit 7 */
DECL|macro|MASK_08
mdefine_line|#define MASK_08   0x00000100    /* Mask value for bit 8 */
DECL|macro|MASK_09
mdefine_line|#define MASK_09   0x00000200    /* Mask value for bit 9 */
DECL|macro|MASK_10
mdefine_line|#define MASK_10   0x00000400    /* Mask value for bit 10 */
DECL|macro|MASK_11
mdefine_line|#define MASK_11   0x00000800    /* Mask value for bit 11 */
DECL|macro|MASK_12
mdefine_line|#define MASK_12   0x00001000    /* Mask value for bit 12 */
DECL|macro|MASK_13
mdefine_line|#define MASK_13   0x00002000    /* Mask value for bit 13 */
DECL|macro|MASK_14
mdefine_line|#define MASK_14   0x00004000    /* Mask value for bit 14 */
DECL|macro|MASK_15
mdefine_line|#define MASK_15   0x00008000    /* Mask value for bit 15 */
DECL|macro|MASK_16
mdefine_line|#define MASK_16   0x00010000    /* Mask value for bit 16 */
DECL|macro|MASK_17
mdefine_line|#define MASK_17   0x00020000    /* Mask value for bit 17 */
DECL|macro|MASK_18
mdefine_line|#define MASK_18   0x00040000    /* Mask value for bit 18 */
DECL|macro|MASK_19
mdefine_line|#define MASK_19   0x00080000    /* Mask value for bit 19 */
DECL|macro|MASK_20
mdefine_line|#define MASK_20   0x00100000    /* Mask value for bit 20 */
DECL|macro|MASK_21
mdefine_line|#define MASK_21   0x00200000    /* Mask value for bit 21 */
DECL|macro|MASK_22
mdefine_line|#define MASK_22   0x00400000    /* Mask value for bit 22 */
DECL|macro|MASK_23
mdefine_line|#define MASK_23   0x00800000    /* Mask value for bit 23 */
DECL|macro|MASK_24
mdefine_line|#define MASK_24   0x01000000    /* Mask value for bit 24 */
DECL|macro|MASK_25
mdefine_line|#define MASK_25   0x02000000    /* Mask value for bit 25 */
DECL|macro|MASK_26
mdefine_line|#define MASK_26   0x04000000    /* Mask value for bit 26 */
DECL|macro|MASK_27
mdefine_line|#define MASK_27   0x08000000    /* Mask value for bit 27 */
DECL|macro|MASK_28
mdefine_line|#define MASK_28   0x10000000    /* Mask value for bit 28 */
DECL|macro|MASK_29
mdefine_line|#define MASK_29   0x20000000    /* Mask value for bit 29 */
DECL|macro|MASK_30
mdefine_line|#define MASK_30   0x40000000    /* Mask value for bit 30 */
DECL|macro|MASK_31
mdefine_line|#define MASK_31   0x80000000    /* Mask value for bit 31 */
DECL|macro|MASK_B0
mdefine_line|#define MASK_B0   0x000000ff    /* Mask value for byte 0 */
DECL|macro|MASK_B1
mdefine_line|#define MASK_B1   0x0000ff00    /* Mask value for byte 1 */
DECL|macro|MASK_B2
mdefine_line|#define MASK_B2   0x00ff0000    /* Mask value for byte 2 */
DECL|macro|MASK_B3
mdefine_line|#define MASK_B3   0xff000000    /* Mask value for byte 3 */
DECL|macro|MASK_W0
mdefine_line|#define MASK_W0   0x0000ffff    /* Mask value for word 0 */
DECL|macro|MASK_W1
mdefine_line|#define MASK_W1   0xffff0000    /* Mask value for word 1 */
DECL|macro|MASK_PA
mdefine_line|#define MASK_PA   0xfffffffc    /* Mask value for physical address */
DECL|macro|MASK_PR
mdefine_line|#define MASK_PR   0xfffffffe &t;/* Mask value for protection register */
DECL|macro|MASK_ER
mdefine_line|#define MASK_ER   0xffffffff    /* Mask value for the entire register */
DECL|macro|MASK_NONE
mdefine_line|#define MASK_NONE 0x00000000    /* No mask */
multiline_comment|/* register aliases */
DECL|macro|BASE_ODD1
mdefine_line|#define BASE_ODD1         0x00  /* Video DMA 1 registers  */
DECL|macro|BASE_EVEN1
mdefine_line|#define BASE_EVEN1        0x04
DECL|macro|PROT_ADDR1
mdefine_line|#define PROT_ADDR1        0x08
DECL|macro|PITCH1
mdefine_line|#define PITCH1            0x0C
DECL|macro|BASE_PAGE1
mdefine_line|#define BASE_PAGE1        0x10  /* Video DMA 1 base page */
DECL|macro|NUM_LINE_BYTE1
mdefine_line|#define NUM_LINE_BYTE1    0x14
DECL|macro|BASE_ODD2
mdefine_line|#define BASE_ODD2         0x18  /* Video DMA 2 registers */
DECL|macro|BASE_EVEN2
mdefine_line|#define BASE_EVEN2        0x1C
DECL|macro|PROT_ADDR2
mdefine_line|#define PROT_ADDR2        0x20
DECL|macro|PITCH2
mdefine_line|#define PITCH2            0x24
DECL|macro|BASE_PAGE2
mdefine_line|#define BASE_PAGE2        0x28  /* Video DMA 2 base page */
DECL|macro|NUM_LINE_BYTE2
mdefine_line|#define NUM_LINE_BYTE2    0x2C
DECL|macro|BASE_ODD3
mdefine_line|#define BASE_ODD3         0x30  /* Video DMA 3 registers */
DECL|macro|BASE_EVEN3
mdefine_line|#define BASE_EVEN3        0x34
DECL|macro|PROT_ADDR3
mdefine_line|#define PROT_ADDR3        0x38
DECL|macro|PITCH3
mdefine_line|#define PITCH3            0x3C         
DECL|macro|BASE_PAGE3
mdefine_line|#define BASE_PAGE3        0x40  /* Video DMA 3 base page */
DECL|macro|NUM_LINE_BYTE3
mdefine_line|#define NUM_LINE_BYTE3    0x44
DECL|macro|PCI_BT_V1
mdefine_line|#define PCI_BT_V1         0x48  /* Video/FIFO 1 */
DECL|macro|PCI_BT_V2
mdefine_line|#define PCI_BT_V2         0x49  /* Video/FIFO 2 */
DECL|macro|PCI_BT_V3
mdefine_line|#define PCI_BT_V3         0x4A  /* Video/FIFO 3 */
DECL|macro|PCI_BT_DEBI
mdefine_line|#define PCI_BT_DEBI       0x4B  /* DEBI */
DECL|macro|PCI_BT_A
mdefine_line|#define PCI_BT_A          0x4C  /* Audio */
DECL|macro|DD1_INIT
mdefine_line|#define DD1_INIT          0x50  /* Init setting of DD1 interface */
DECL|macro|DD1_STREAM_B
mdefine_line|#define DD1_STREAM_B      0x54  /* DD1 B video data stream handling */
DECL|macro|DD1_STREAM_A
mdefine_line|#define DD1_STREAM_A      0x56  /* DD1 A video data stream handling */
DECL|macro|BRS_CTRL
mdefine_line|#define BRS_CTRL          0x58  /* BRS control register */
DECL|macro|HPS_CTRL
mdefine_line|#define HPS_CTRL          0x5C  /* HPS control register */
DECL|macro|HPS_V_SCALE
mdefine_line|#define HPS_V_SCALE       0x60  /* HPS vertical scale */
DECL|macro|HPS_V_GAIN
mdefine_line|#define HPS_V_GAIN        0x64  /* HPS vertical ACL and gain */
DECL|macro|HPS_H_PRESCALE
mdefine_line|#define HPS_H_PRESCALE    0x68  /* HPS horizontal prescale   */
DECL|macro|HPS_H_SCALE
mdefine_line|#define HPS_H_SCALE       0x6C  /* HPS horizontal scale */
DECL|macro|BCS_CTRL
mdefine_line|#define BCS_CTRL          0x70  /* BCS control */
DECL|macro|CHROMA_KEY_RANGE
mdefine_line|#define CHROMA_KEY_RANGE  0x74
DECL|macro|CLIP_FORMAT_CTRL
mdefine_line|#define CLIP_FORMAT_CTRL  0x78  /* HPS outputs formats &amp; clipping */
DECL|macro|DEBI_CONFIG
mdefine_line|#define DEBI_CONFIG       0x7C
DECL|macro|DEBI_COMMAND
mdefine_line|#define DEBI_COMMAND      0x80
DECL|macro|DEBI_PAGE
mdefine_line|#define DEBI_PAGE         0x84
DECL|macro|DEBI_AD
mdefine_line|#define DEBI_AD           0x88&t;
DECL|macro|I2C_TRANSFER
mdefine_line|#define I2C_TRANSFER      0x8C&t;
DECL|macro|I2C_STATUS
mdefine_line|#define I2C_STATUS        0x90&t;
DECL|macro|BASE_A1_IN
mdefine_line|#define BASE_A1_IN        0x94&t;/* Audio 1 input DMA */
DECL|macro|PROT_A1_IN
mdefine_line|#define PROT_A1_IN        0x98
DECL|macro|PAGE_A1_IN
mdefine_line|#define PAGE_A1_IN        0x9C
DECL|macro|BASE_A1_OUT
mdefine_line|#define BASE_A1_OUT       0xA0  /* Audio 1 output DMA */
DECL|macro|PROT_A1_OUT
mdefine_line|#define PROT_A1_OUT       0xA4
DECL|macro|PAGE_A1_OUT
mdefine_line|#define PAGE_A1_OUT       0xA8
DECL|macro|BASE_A2_IN
mdefine_line|#define BASE_A2_IN        0xAC  /* Audio 2 input DMA */
DECL|macro|PROT_A2_IN
mdefine_line|#define PROT_A2_IN        0xB0
DECL|macro|PAGE_A2_IN
mdefine_line|#define PAGE_A2_IN        0xB4
DECL|macro|BASE_A2_OUT
mdefine_line|#define BASE_A2_OUT       0xB8  /* Audio 2 output DMA */
DECL|macro|PROT_A2_OUT
mdefine_line|#define PROT_A2_OUT       0xBC
DECL|macro|PAGE_A2_OUT
mdefine_line|#define PAGE_A2_OUT       0xC0
DECL|macro|RPS_PAGE0
mdefine_line|#define RPS_PAGE0         0xC4  /* RPS task 0 page register */
DECL|macro|RPS_PAGE1
mdefine_line|#define RPS_PAGE1         0xC8  /* RPS task 1 page register */
DECL|macro|RPS_THRESH0
mdefine_line|#define RPS_THRESH0       0xCC  /* HBI threshold for task 0 */
DECL|macro|RPS_THRESH1
mdefine_line|#define RPS_THRESH1       0xD0  /* HBI threshold for task 1 */
DECL|macro|RPS_TOV0
mdefine_line|#define RPS_TOV0          0xD4  /* RPS timeout for task 0 */
DECL|macro|RPS_TOV1
mdefine_line|#define RPS_TOV1          0xD8  /* RPS timeout for task 1 */
DECL|macro|IER
mdefine_line|#define IER               0xDC  /* Interrupt enable register */
DECL|macro|GPIO_CTRL
mdefine_line|#define GPIO_CTRL         0xE0  /* GPIO 0-3 register */
DECL|macro|EC1SSR
mdefine_line|#define EC1SSR            0xE4  /* Event cnt set 1 source select */
DECL|macro|EC2SSR
mdefine_line|#define EC2SSR            0xE8  /* Event cnt set 2 source select */
DECL|macro|ECT1R
mdefine_line|#define ECT1R             0xEC  /* Event cnt set 1 thresholds */
DECL|macro|ECT2R
mdefine_line|#define ECT2R             0xF0  /* Event cnt set 2 thresholds */
DECL|macro|ACON1
mdefine_line|#define ACON1             0xF4
DECL|macro|ACON2
mdefine_line|#define ACON2             0xF8
DECL|macro|MC1
mdefine_line|#define MC1               0xFC   /* Main control register 1 */
DECL|macro|MC2
mdefine_line|#define MC2               0x100  /* Main control register 2  */
DECL|macro|RPS_ADDR0
mdefine_line|#define RPS_ADDR0         0x104  /* RPS task 0 address register */
DECL|macro|RPS_ADDR1
mdefine_line|#define RPS_ADDR1         0x108  /* RPS task 1 address register */
DECL|macro|ISR
mdefine_line|#define ISR               0x10C  /* Interrupt status register */                                                             
DECL|macro|PSR
mdefine_line|#define PSR               0x110  /* Primary status register */
DECL|macro|SSR
mdefine_line|#define SSR               0x114  /* Secondary status register */
DECL|macro|EC1R
mdefine_line|#define EC1R              0x118  /* Event counter set 1 register */
DECL|macro|EC2R
mdefine_line|#define EC2R              0x11C  /* Event counter set 2 register */         
DECL|macro|PCI_VDP1
mdefine_line|#define PCI_VDP1          0x120  /* Video DMA pointer of FIFO 1 */
DECL|macro|PCI_VDP2
mdefine_line|#define PCI_VDP2          0x124  /* Video DMA pointer of FIFO 2 */
DECL|macro|PCI_VDP3
mdefine_line|#define PCI_VDP3          0x128  /* Video DMA pointer of FIFO 3 */
DECL|macro|PCI_ADP1
mdefine_line|#define PCI_ADP1          0x12C  /* Audio DMA pointer of audio out 1 */
DECL|macro|PCI_ADP2
mdefine_line|#define PCI_ADP2          0x130  /* Audio DMA pointer of audio in 1 */
DECL|macro|PCI_ADP3
mdefine_line|#define PCI_ADP3          0x134  /* Audio DMA pointer of audio out 2 */
DECL|macro|PCI_ADP4
mdefine_line|#define PCI_ADP4          0x138  /* Audio DMA pointer of audio in 2 */
DECL|macro|PCI_DMA_DDP
mdefine_line|#define PCI_DMA_DDP       0x13C  /* DEBI DMA pointer */
DECL|macro|LEVEL_REP
mdefine_line|#define LEVEL_REP         0x140,
DECL|macro|A_TIME_SLOT1
mdefine_line|#define A_TIME_SLOT1      0x180,  /* from 180 - 1BC */
DECL|macro|A_TIME_SLOT2
mdefine_line|#define A_TIME_SLOT2      0x1C0,  /* from 1C0 - 1FC */
multiline_comment|/* isr masks */
DECL|macro|SPCI_PPEF
mdefine_line|#define SPCI_PPEF       0x80000000  /* PCI parity error */
DECL|macro|SPCI_PABO
mdefine_line|#define SPCI_PABO       0x40000000  /* PCI access error (target or master abort) */
DECL|macro|SPCI_PPED
mdefine_line|#define SPCI_PPED       0x20000000  /* PCI parity error on &squot;real time data&squot; */
DECL|macro|SPCI_RPS_I1
mdefine_line|#define SPCI_RPS_I1     0x10000000  /* Interrupt issued by RPS1 */
DECL|macro|SPCI_RPS_I0
mdefine_line|#define SPCI_RPS_I0     0x08000000  /* Interrupt issued by RPS0 */
DECL|macro|SPCI_RPS_LATE1
mdefine_line|#define SPCI_RPS_LATE1  0x04000000  /* RPS task 1 is late */
DECL|macro|SPCI_RPS_LATE0
mdefine_line|#define SPCI_RPS_LATE0  0x02000000  /* RPS task 0 is late */
DECL|macro|SPCI_RPS_E1
mdefine_line|#define SPCI_RPS_E1     0x01000000  /* RPS error from task 1 */
DECL|macro|SPCI_RPS_E0
mdefine_line|#define SPCI_RPS_E0     0x00800000  /* RPS error from task 0 */
DECL|macro|SPCI_RPS_TO1
mdefine_line|#define SPCI_RPS_TO1    0x00400000  /* RPS timeout task 1 */
DECL|macro|SPCI_RPS_TO0
mdefine_line|#define SPCI_RPS_TO0    0x00200000  /* RPS timeout task 0 */
DECL|macro|SPCI_UPLD
mdefine_line|#define SPCI_UPLD       0x00100000  /* RPS in upload */
DECL|macro|SPCI_DEBI_S
mdefine_line|#define SPCI_DEBI_S     0x00080000  /* DEBI status */
DECL|macro|SPCI_DEBI_E
mdefine_line|#define SPCI_DEBI_E     0x00040000  /* DEBI error */
DECL|macro|SPCI_IIC_S
mdefine_line|#define SPCI_IIC_S      0x00020000  /* I2C status */
DECL|macro|SPCI_IIC_E
mdefine_line|#define SPCI_IIC_E      0x00010000  /* I2C error */
DECL|macro|SPCI_A2_IN
mdefine_line|#define SPCI_A2_IN      0x00008000  /* Audio 2 input DMA protection / limit */
DECL|macro|SPCI_A2_OUT
mdefine_line|#define SPCI_A2_OUT     0x00004000  /* Audio 2 output DMA protection / limit */
DECL|macro|SPCI_A1_IN
mdefine_line|#define SPCI_A1_IN      0x00002000  /* Audio 1 input DMA protection / limit */
DECL|macro|SPCI_A1_OUT
mdefine_line|#define SPCI_A1_OUT     0x00001000  /* Audio 1 output DMA protection / limit */
DECL|macro|SPCI_AFOU
mdefine_line|#define SPCI_AFOU       0x00000800  /* Audio FIFO over- / underflow */
DECL|macro|SPCI_V_PE
mdefine_line|#define SPCI_V_PE       0x00000400  /* Video protection address */
DECL|macro|SPCI_VFOU
mdefine_line|#define SPCI_VFOU       0x00000200  /* Video FIFO over- / underflow */
DECL|macro|SPCI_FIDA
mdefine_line|#define SPCI_FIDA       0x00000100  /* Field ID video port A */
DECL|macro|SPCI_FIDB
mdefine_line|#define SPCI_FIDB       0x00000080  /* Field ID video port B */
DECL|macro|SPCI_PIN3
mdefine_line|#define SPCI_PIN3       0x00000040  /* GPIO pin 3 */
DECL|macro|SPCI_PIN2
mdefine_line|#define SPCI_PIN2       0x00000020  /* GPIO pin 2 */
DECL|macro|SPCI_PIN1
mdefine_line|#define SPCI_PIN1       0x00000010  /* GPIO pin 1 */
DECL|macro|SPCI_PIN0
mdefine_line|#define SPCI_PIN0       0x00000008  /* GPIO pin 0 */
DECL|macro|SPCI_ECS
mdefine_line|#define SPCI_ECS        0x00000004  /* Event counter 1, 2, 4, 5 */
DECL|macro|SPCI_EC3S
mdefine_line|#define SPCI_EC3S       0x00000002  /* Event counter 3 */
DECL|macro|SPCI_EC0S
mdefine_line|#define SPCI_EC0S       0x00000001  /* Event counter 0 */
multiline_comment|/* i2c */
DECL|macro|SAA7146_I2C_ABORT
mdefine_line|#define&t;SAA7146_I2C_ABORT&t;(1&lt;&lt;7)
DECL|macro|SAA7146_I2C_SPERR
mdefine_line|#define&t;SAA7146_I2C_SPERR&t;(1&lt;&lt;6)
DECL|macro|SAA7146_I2C_APERR
mdefine_line|#define&t;SAA7146_I2C_APERR&t;(1&lt;&lt;5)
DECL|macro|SAA7146_I2C_DTERR
mdefine_line|#define&t;SAA7146_I2C_DTERR&t;(1&lt;&lt;4)
DECL|macro|SAA7146_I2C_DRERR
mdefine_line|#define&t;SAA7146_I2C_DRERR&t;(1&lt;&lt;3)
DECL|macro|SAA7146_I2C_AL
mdefine_line|#define&t;SAA7146_I2C_AL&t;&t;(1&lt;&lt;2)
DECL|macro|SAA7146_I2C_ERR
mdefine_line|#define&t;SAA7146_I2C_ERR&t;&t;(1&lt;&lt;1)
DECL|macro|SAA7146_I2C_BUSY
mdefine_line|#define&t;SAA7146_I2C_BUSY&t;(1&lt;&lt;0)
DECL|macro|SAA7146_I2C_START
mdefine_line|#define&t;SAA7146_I2C_START&t;(0x3)
DECL|macro|SAA7146_I2C_CONT
mdefine_line|#define&t;SAA7146_I2C_CONT&t;(0x2)
DECL|macro|SAA7146_I2C_STOP
mdefine_line|#define&t;SAA7146_I2C_STOP&t;(0x1)
DECL|macro|SAA7146_I2C_NOP
mdefine_line|#define&t;SAA7146_I2C_NOP&t;&t;(0x0)
DECL|macro|SAA7146_I2C_BUS_BIT_RATE_6400
mdefine_line|#define SAA7146_I2C_BUS_BIT_RATE_6400&t;(0x500)
DECL|macro|SAA7146_I2C_BUS_BIT_RATE_3200
mdefine_line|#define SAA7146_I2C_BUS_BIT_RATE_3200&t;(0x100)
DECL|macro|SAA7146_I2C_BUS_BIT_RATE_480
mdefine_line|#define SAA7146_I2C_BUS_BIT_RATE_480&t;(0x400)
DECL|macro|SAA7146_I2C_BUS_BIT_RATE_320
mdefine_line|#define SAA7146_I2C_BUS_BIT_RATE_320&t;(0x600)
DECL|macro|SAA7146_I2C_BUS_BIT_RATE_240
mdefine_line|#define SAA7146_I2C_BUS_BIT_RATE_240&t;(0x700)
DECL|macro|SAA7146_I2C_BUS_BIT_RATE_120
mdefine_line|#define SAA7146_I2C_BUS_BIT_RATE_120&t;(0x000)
DECL|macro|SAA7146_I2C_BUS_BIT_RATE_80
mdefine_line|#define SAA7146_I2C_BUS_BIT_RATE_80&t;(0x200)
DECL|macro|SAA7146_I2C_BUS_BIT_RATE_60
mdefine_line|#define SAA7146_I2C_BUS_BIT_RATE_60&t;(0x300)
macro_line|#endif
eof

multiline_comment|/*&n; * Author: Pete Popov &lt;ppopov@mvista.com&gt; or source@mvista.com&n; *&n; * arch/ppc/kernel/ppc405_dma.c&n; *&n; * 2000 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; *&n; * IBM 405 DMA Controller Functions&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/ppc405_dma.h&gt;
multiline_comment|/*&n; * Function prototypes&n; */
r_int
id|hw_init_dma_channel
c_func
(paren
r_int
r_int
comma
id|ppc_dma_ch_t
op_star
)paren
suffix:semicolon
r_int
id|init_dma_channel
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_int
id|get_channel_config
c_func
(paren
r_int
r_int
comma
id|ppc_dma_ch_t
op_star
)paren
suffix:semicolon
r_int
id|set_channel_priority
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_int
r_int
id|get_peripheral_width
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_int
id|alloc_dma_handle
c_func
(paren
id|sgl_handle_t
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|free_dma_handle
c_func
(paren
id|sgl_handle_t
)paren
suffix:semicolon
DECL|variable|dma_channels
id|ppc_dma_ch_t
id|dma_channels
(braket
id|MAX_405GP_DMA_CHANNELS
)braket
suffix:semicolon
multiline_comment|/*&n; * Configures a DMA channel, including the peripheral bus width, if a&n; * peripheral is attached to the channel, the polarity of the DMAReq and&n; * DMAAck signals, etc.  This information should really be setup by the boot&n; * code, since most likely the configuration won&squot;t change dynamically.&n; * If the kernel has to call this function, it&squot;s recommended that it&squot;s&n; * called from platform specific init code.  The driver should not need to&n; * call this function.&n; */
DECL|function|hw_init_dma_channel
r_int
id|hw_init_dma_channel
c_func
(paren
r_int
r_int
id|dmanr
comma
id|ppc_dma_ch_t
op_star
id|p_init
)paren
(brace
r_int
r_int
id|polarity
suffix:semicolon
r_uint32
id|control
op_assign
l_int|0
suffix:semicolon
id|ppc_dma_ch_t
op_star
id|p_dma_ch
op_assign
op_amp
id|dma_channels
(braket
id|dmanr
)braket
suffix:semicolon
macro_line|#ifdef DEBUG_405DMA
r_if
c_cond
(paren
op_logical_neg
id|p_init
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;hw_init_dma_channel: NULL p_init&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|DMA_STATUS_NULL_POINTER
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dmanr
op_ge
id|MAX_405GP_DMA_CHANNELS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;hw_init_dma_channel: bad channel %d&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
r_return
id|DMA_STATUS_BAD_CHANNEL
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if DCRN_POL &gt; 0
id|polarity
op_assign
id|mfdcr
c_func
(paren
id|DCRN_POL
)paren
suffix:semicolon
macro_line|#else
id|polarity
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/* Setup the control register based on the values passed to&n;     * us in p_init.  Then, over-write the control register with this&n;     * new value.&n;     */
id|control
op_or_assign
(paren
id|SET_DMA_CIE_ENABLE
c_func
(paren
id|p_init-&gt;int_enable
)paren
op_or
multiline_comment|/* interrupt enable         */
id|SET_DMA_BEN
c_func
(paren
id|p_init-&gt;buffer_enable
)paren
op_or
multiline_comment|/* buffer enable            */
id|SET_DMA_ETD
c_func
(paren
id|p_init-&gt;etd_output
)paren
op_or
multiline_comment|/* end of transfer pin      */
id|SET_DMA_TCE
c_func
(paren
id|p_init-&gt;tce_enable
)paren
op_or
multiline_comment|/* terminal count enable    */
id|SET_DMA_PL
c_func
(paren
id|p_init-&gt;pl
)paren
op_or
multiline_comment|/* peripheral location      */
id|SET_DMA_DAI
c_func
(paren
id|p_init-&gt;dai
)paren
op_or
multiline_comment|/* dest addr increment      */
id|SET_DMA_SAI
c_func
(paren
id|p_init-&gt;sai
)paren
op_or
multiline_comment|/* src addr increment       */
id|SET_DMA_PRIORITY
c_func
(paren
id|p_init-&gt;cp
)paren
op_or
multiline_comment|/* channel priority        */
id|SET_DMA_PW
c_func
(paren
id|p_init-&gt;pwidth
)paren
op_or
multiline_comment|/* peripheral/bus width    */
id|SET_DMA_PSC
c_func
(paren
id|p_init-&gt;psc
)paren
op_or
multiline_comment|/* peripheral setup cycles */
id|SET_DMA_PWC
c_func
(paren
id|p_init-&gt;pwc
)paren
op_or
multiline_comment|/* peripheral wait cycles  */
id|SET_DMA_PHC
c_func
(paren
id|p_init-&gt;phc
)paren
op_or
multiline_comment|/* peripheral hold cycles  */
id|SET_DMA_PREFETCH
c_func
(paren
id|p_init-&gt;pf
)paren
multiline_comment|/* read prefetch           */
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|dmanr
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* clear all polarity signals and then &quot;or&quot; in new signal levels */
id|polarity
op_and_assign
op_complement
(paren
id|DMAReq0_ActiveLow
op_or
id|DMAAck0_ActiveLow
op_or
id|EOT0_ActiveLow
)paren
suffix:semicolon
id|polarity
op_or_assign
id|p_dma_ch-&gt;polarity
suffix:semicolon
macro_line|#if DCRN_POL &gt; 0
id|mtdcr
c_func
(paren
id|DCRN_POL
comma
id|polarity
)paren
suffix:semicolon
macro_line|#endif
id|mtdcr
c_func
(paren
id|DCRN_DMACR0
comma
id|control
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|polarity
op_and_assign
op_complement
(paren
id|DMAReq1_ActiveLow
op_or
id|DMAAck1_ActiveLow
op_or
id|EOT1_ActiveLow
)paren
suffix:semicolon
id|polarity
op_or_assign
id|p_dma_ch-&gt;polarity
suffix:semicolon
macro_line|#if DCRN_POL &gt; 0
id|mtdcr
c_func
(paren
id|DCRN_POL
comma
id|polarity
)paren
suffix:semicolon
macro_line|#endif
id|mtdcr
c_func
(paren
id|DCRN_DMACR1
comma
id|control
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|polarity
op_and_assign
op_complement
(paren
id|DMAReq2_ActiveLow
op_or
id|DMAAck2_ActiveLow
op_or
id|EOT2_ActiveLow
)paren
suffix:semicolon
id|polarity
op_or_assign
id|p_dma_ch-&gt;polarity
suffix:semicolon
macro_line|#if DCRN_POL &gt; 0
id|mtdcr
c_func
(paren
id|DCRN_POL
comma
id|polarity
)paren
suffix:semicolon
macro_line|#endif
id|mtdcr
c_func
(paren
id|DCRN_DMACR2
comma
id|control
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|polarity
op_and_assign
op_complement
(paren
id|DMAReq3_ActiveLow
op_or
id|DMAAck3_ActiveLow
op_or
id|EOT3_ActiveLow
)paren
suffix:semicolon
id|polarity
op_or_assign
id|p_dma_ch-&gt;polarity
suffix:semicolon
macro_line|#if DCRN_POL &gt; 0
id|mtdcr
c_func
(paren
id|DCRN_POL
comma
id|polarity
)paren
suffix:semicolon
macro_line|#endif
id|mtdcr
c_func
(paren
id|DCRN_DMACR3
comma
id|control
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|DMA_STATUS_BAD_CHANNEL
suffix:semicolon
)brace
multiline_comment|/* save these values in our dma channel structure */
id|memcpy
c_func
(paren
id|p_dma_ch
comma
id|p_init
comma
r_sizeof
(paren
id|ppc_dma_ch_t
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     * The peripheral width values written in the control register are:&n;     *   PW_8                 0&n;     *   PW_16                1&n;     *   PW_32                2&n;     *   PW_64                3&n;     *&n;     *   Since the DMA count register takes the number of &quot;transfers&quot;,&n;     *   we need to divide the count sent to us in certain&n;     *   functions by the appropriate number.  It so happens that our&n;     *   right shift value is equal to the peripheral width value.&n;     */
id|p_dma_ch-&gt;shift
op_assign
id|p_init-&gt;pwidth
suffix:semicolon
multiline_comment|/*&n;     * Save the control word for easy access.&n;     */
id|p_dma_ch-&gt;control
op_assign
id|control
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_DMASR
comma
l_int|0xffffffff
)paren
suffix:semicolon
multiline_comment|/* clear status register */
r_return
id|DMA_STATUS_GOOD
suffix:semicolon
)brace
multiline_comment|/*&n; * This function returns the channel configuration.&n; */
DECL|function|get_channel_config
r_int
id|get_channel_config
c_func
(paren
r_int
r_int
id|dmanr
comma
id|ppc_dma_ch_t
op_star
id|p_dma_ch
)paren
(brace
r_int
r_int
id|polarity
suffix:semicolon
r_int
r_int
id|control
suffix:semicolon
macro_line|#if DCRN_POL &gt; 0
id|polarity
op_assign
id|mfdcr
c_func
(paren
id|DCRN_POL
)paren
suffix:semicolon
macro_line|#else
id|polarity
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|dmanr
)paren
(brace
r_case
l_int|0
suffix:colon
id|p_dma_ch-&gt;polarity
op_assign
id|polarity
op_amp
(paren
id|DMAReq0_ActiveLow
op_or
id|DMAAck0_ActiveLow
op_or
id|EOT0_ActiveLow
)paren
suffix:semicolon
id|control
op_assign
id|mfdcr
c_func
(paren
id|DCRN_DMACR0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|p_dma_ch-&gt;polarity
op_assign
id|polarity
op_amp
(paren
id|DMAReq1_ActiveLow
op_or
id|DMAAck1_ActiveLow
op_or
id|EOT1_ActiveLow
)paren
suffix:semicolon
id|control
op_assign
id|mfdcr
c_func
(paren
id|DCRN_DMACR1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|p_dma_ch-&gt;polarity
op_assign
id|polarity
op_amp
(paren
id|DMAReq2_ActiveLow
op_or
id|DMAAck2_ActiveLow
op_or
id|EOT2_ActiveLow
)paren
suffix:semicolon
id|control
op_assign
id|mfdcr
c_func
(paren
id|DCRN_DMACR2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|p_dma_ch-&gt;polarity
op_assign
id|polarity
op_amp
(paren
id|DMAReq3_ActiveLow
op_or
id|DMAAck3_ActiveLow
op_or
id|EOT3_ActiveLow
)paren
suffix:semicolon
id|control
op_assign
id|mfdcr
c_func
(paren
id|DCRN_DMACR3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|DMA_STATUS_BAD_CHANNEL
suffix:semicolon
)brace
id|p_dma_ch-&gt;cp
op_assign
id|GET_DMA_PRIORITY
c_func
(paren
id|control
)paren
suffix:semicolon
id|p_dma_ch-&gt;pwidth
op_assign
id|GET_DMA_PW
c_func
(paren
id|control
)paren
suffix:semicolon
id|p_dma_ch-&gt;psc
op_assign
id|GET_DMA_PSC
c_func
(paren
id|control
)paren
suffix:semicolon
id|p_dma_ch-&gt;pwc
op_assign
id|GET_DMA_PWC
c_func
(paren
id|control
)paren
suffix:semicolon
id|p_dma_ch-&gt;phc
op_assign
id|GET_DMA_PHC
c_func
(paren
id|control
)paren
suffix:semicolon
id|p_dma_ch-&gt;pf
op_assign
id|GET_DMA_PREFETCH
c_func
(paren
id|control
)paren
suffix:semicolon
id|p_dma_ch-&gt;int_enable
op_assign
id|GET_DMA_CIE_ENABLE
c_func
(paren
id|control
)paren
suffix:semicolon
id|p_dma_ch-&gt;shift
op_assign
id|GET_DMA_PW
c_func
(paren
id|control
)paren
suffix:semicolon
r_return
id|DMA_STATUS_GOOD
suffix:semicolon
)brace
multiline_comment|/*&n; * Sets the priority for the DMA channel dmanr.&n; * Since this is setup by the hardware init function, this function&n; * can be used to dynamically change the priority of a channel.&n; *&n; * Acceptable priorities:&n; *&n; * PRIORITY_LOW&n; * PRIORITY_MID_LOW&n; * PRIORITY_MID_HIGH&n; * PRIORITY_HIGH&n; *&n; */
DECL|function|set_channel_priority
r_int
id|set_channel_priority
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|priority
)paren
(brace
r_int
r_int
id|control
suffix:semicolon
macro_line|#ifdef DEBUG_405DMA
r_if
c_cond
(paren
(paren
id|priority
op_ne
id|PRIORITY_LOW
)paren
op_logical_and
(paren
id|priority
op_ne
id|PRIORITY_MID_LOW
)paren
op_logical_and
(paren
id|priority
op_ne
id|PRIORITY_MID_HIGH
)paren
op_logical_and
(paren
id|priority
op_ne
id|PRIORITY_HIGH
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;set_channel_priority: bad priority: 0x%x&bslash;n&quot;
comma
id|priority
)paren
suffix:semicolon
)brace
macro_line|#endif
r_switch
c_cond
(paren
id|dmanr
)paren
(brace
r_case
l_int|0
suffix:colon
id|control
op_assign
id|mfdcr
c_func
(paren
id|DCRN_DMACR0
)paren
suffix:semicolon
id|control
op_or_assign
id|SET_DMA_PRIORITY
c_func
(paren
id|priority
)paren
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_DMACR0
comma
id|control
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|control
op_assign
id|mfdcr
c_func
(paren
id|DCRN_DMACR1
)paren
suffix:semicolon
id|control
op_or_assign
id|SET_DMA_PRIORITY
c_func
(paren
id|priority
)paren
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_DMACR1
comma
id|control
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|control
op_assign
id|mfdcr
c_func
(paren
id|DCRN_DMACR2
)paren
suffix:semicolon
id|control
op_or_assign
id|SET_DMA_PRIORITY
c_func
(paren
id|priority
)paren
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_DMACR2
comma
id|control
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|control
op_assign
id|mfdcr
c_func
(paren
id|DCRN_DMACR3
)paren
suffix:semicolon
id|control
op_or_assign
id|SET_DMA_PRIORITY
c_func
(paren
id|priority
)paren
suffix:semicolon
id|mtdcr
c_func
(paren
id|DCRN_DMACR3
comma
id|control
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
macro_line|#ifdef DEBUG_405DMA
id|printk
c_func
(paren
l_string|&quot;set_channel_priority: bad channel: %d&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
macro_line|#endif
r_return
id|DMA_STATUS_BAD_CHANNEL
suffix:semicolon
)brace
r_return
id|DMA_STATUS_GOOD
suffix:semicolon
)brace
multiline_comment|/*&n; * Returns the width of the peripheral attached to this channel. This assumes&n; * that someone who knows the hardware configuration, boot code or some other&n; * init code, already set the width.&n; *&n; * The return value is one of:&n; *   PW_8&n; *   PW_16&n; *   PW_32&n; *   PW_64&n; *&n; *   The function returns 0 on error.&n; */
DECL|function|get_peripheral_width
r_int
r_int
id|get_peripheral_width
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_int
r_int
id|control
suffix:semicolon
r_switch
c_cond
(paren
id|dmanr
)paren
(brace
r_case
l_int|0
suffix:colon
id|control
op_assign
id|mfdcr
c_func
(paren
id|DCRN_DMACR0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|control
op_assign
id|mfdcr
c_func
(paren
id|DCRN_DMACR1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|control
op_assign
id|mfdcr
c_func
(paren
id|DCRN_DMACR2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|control
op_assign
id|mfdcr
c_func
(paren
id|DCRN_DMACR3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
macro_line|#ifdef DEBUG_405DMA
id|printk
c_func
(paren
l_string|&quot;get_peripheral_width: bad channel: %d&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|GET_DMA_PW
c_func
(paren
id|control
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *   Create a scatter/gather list handle.  This is simply a structure which&n; *   describes a scatter/gather list.&n; *&n; *   A handle is returned in &quot;handle&quot; which the driver should save in order to&n; *   be able to access this list later.  A chunk of memory will be allocated&n; *   to be used by the API for internal management purposes, including managing&n; *   the sg list and allocating memory for the sgl descriptors.  One page should&n; *   be more than enough for that purpose.  Perhaps it&squot;s a bit wasteful to use&n; *   a whole page for a single sg list, but most likely there will be only one&n; *   sg list per channel.&n; *&n; *   Interrupt notes:&n; *   Each sgl descriptor has a copy of the DMA control word which the DMA engine&n; *   loads in the control register.  The control word has a &quot;global&quot; interrupt&n; *   enable bit for that channel. Interrupts are further qualified by a few bits&n; *   in the sgl descriptor count register.  In order to setup an sgl, we have to&n; *   know ahead of time whether or not interrupts will be enabled at the completion&n; *   of the transfers.  Thus, enable_dma_interrupt()/disable_dma_interrupt() MUST&n; *   be called before calling alloc_dma_handle().  If the interrupt mode will never&n; *   change after powerup, then enable_dma_interrupt()/disable_dma_interrupt()&n; *   do not have to be called -- interrupts will be enabled or disabled based&n; *   on how the channel was configured after powerup by the hw_init_dma_channel()&n; *   function.  Each sgl descriptor will be setup to interrupt if an error occurs;&n; *   however, only the last descriptor will be setup to interrupt. Thus, an&n; *   interrupt will occur (if interrupts are enabled) only after the complete&n; *   sgl transfer is done.&n; */
DECL|function|alloc_dma_handle
r_int
id|alloc_dma_handle
c_func
(paren
id|sgl_handle_t
op_star
id|phandle
comma
r_int
r_int
id|mode
comma
r_int
r_int
id|dmanr
)paren
(brace
id|sgl_list_info_t
op_star
id|psgl
suffix:semicolon
id|dma_addr_t
id|dma_addr
suffix:semicolon
id|ppc_dma_ch_t
op_star
id|p_dma_ch
op_assign
op_amp
id|dma_channels
(braket
id|dmanr
)braket
suffix:semicolon
r_uint32
id|sg_command
suffix:semicolon
r_void
op_star
id|ret
suffix:semicolon
macro_line|#ifdef DEBUG_405DMA
r_if
c_cond
(paren
op_logical_neg
id|phandle
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;alloc_dma_handle: null handle pointer&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|DMA_STATUS_NULL_POINTER
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|DMA_MODE_READ
suffix:colon
r_case
id|DMA_MODE_WRITE
suffix:colon
r_case
id|DMA_MODE_MM
suffix:colon
r_case
id|DMA_MODE_MM_DEVATSRC
suffix:colon
r_case
id|DMA_MODE_MM_DEVATDST
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;alloc_dma_handle: bad mode 0x%x&bslash;n&quot;
comma
id|mode
)paren
suffix:semicolon
r_return
id|DMA_STATUS_BAD_MODE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dmanr
op_ge
id|MAX_405GP_DMA_CHANNELS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;alloc_dma_handle: invalid channel 0x%x&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
r_return
id|DMA_STATUS_BAD_CHANNEL
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Get a page of memory, which is zeroed out by pci_alloc_consistent() */
multiline_comment|/* wrong not a pci device - armin */
multiline_comment|/* psgl = (sgl_list_info_t *) pci_alloc_consistent(NULL, SGL_LIST_SIZE, &amp;dma_addr);&n;*/
id|ret
op_assign
id|consistent_alloc
c_func
(paren
id|GFP_ATOMIC
op_or
id|GFP_DMA
comma
id|SGL_LIST_SIZE
comma
op_amp
id|dma_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|NULL
)paren
(brace
id|memset
c_func
(paren
id|ret
comma
l_int|0
comma
id|SGL_LIST_SIZE
)paren
suffix:semicolon
id|psgl
op_assign
(paren
id|sgl_list_info_t
op_star
)paren
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
id|psgl
op_eq
l_int|NULL
)paren
(brace
op_star
id|phandle
op_assign
(paren
id|sgl_handle_t
)paren
l_int|NULL
suffix:semicolon
r_return
id|DMA_STATUS_OUT_OF_MEMORY
suffix:semicolon
)brace
id|psgl-&gt;dma_addr
op_assign
id|dma_addr
suffix:semicolon
id|psgl-&gt;dmanr
op_assign
id|dmanr
suffix:semicolon
multiline_comment|/*&n;     * Modify and save the control word. These word will get written to each sgl&n;     * descriptor.  The DMA engine then loads this control word into the control&n;     * register every time it reads a new descriptor.&n;     */
id|psgl-&gt;control
op_assign
id|p_dma_ch-&gt;control
suffix:semicolon
id|psgl-&gt;control
op_and_assign
op_complement
(paren
id|DMA_TM_MASK
op_or
id|DMA_TD
)paren
suffix:semicolon
multiline_comment|/* clear all &quot;mode&quot; bits first               */
id|psgl-&gt;control
op_or_assign
(paren
id|mode
op_or
id|DMA_CH_ENABLE
)paren
suffix:semicolon
multiline_comment|/* save the control word along with the mode */
r_if
c_cond
(paren
id|p_dma_ch-&gt;int_enable
)paren
(brace
id|psgl-&gt;control
op_or_assign
id|DMA_CIE_ENABLE
suffix:semicolon
multiline_comment|/* channel interrupt enabled                 */
)brace
r_else
(brace
id|psgl-&gt;control
op_and_assign
op_complement
id|DMA_CIE_ENABLE
suffix:semicolon
)brace
macro_line|#if DCRN_ASGC &gt; 0
id|sg_command
op_assign
id|mfdcr
c_func
(paren
id|DCRN_ASGC
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|dmanr
)paren
(brace
r_case
l_int|0
suffix:colon
id|sg_command
op_or_assign
id|SSG0_MASK_ENABLE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|sg_command
op_or_assign
id|SSG1_MASK_ENABLE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|sg_command
op_or_assign
id|SSG2_MASK_ENABLE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|sg_command
op_or_assign
id|SSG3_MASK_ENABLE
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
macro_line|#ifdef DEBUG_405DMA
id|printk
c_func
(paren
l_string|&quot;alloc_dma_handle: bad channel: %d&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
macro_line|#endif
id|free_dma_handle
c_func
(paren
(paren
id|sgl_handle_t
)paren
id|psgl
)paren
suffix:semicolon
op_star
id|phandle
op_assign
(paren
id|sgl_handle_t
)paren
l_int|NULL
suffix:semicolon
r_return
id|DMA_STATUS_BAD_CHANNEL
suffix:semicolon
)brace
id|mtdcr
c_func
(paren
id|DCRN_ASGC
comma
id|sg_command
)paren
suffix:semicolon
multiline_comment|/* enable writing to this channel&squot;s sgl control bits */
macro_line|#else
(paren
r_void
)paren
id|sg_command
suffix:semicolon
macro_line|#endif
id|psgl-&gt;sgl_control
op_assign
id|SG_ERI_ENABLE
op_or
id|SG_LINK
suffix:semicolon
multiline_comment|/* sgl descriptor control bits */
r_if
c_cond
(paren
id|p_dma_ch-&gt;int_enable
)paren
(brace
r_if
c_cond
(paren
id|p_dma_ch-&gt;tce_enable
)paren
id|psgl-&gt;sgl_control
op_or_assign
id|SG_TCI_ENABLE
suffix:semicolon
r_else
id|psgl-&gt;sgl_control
op_or_assign
id|SG_ETI_ENABLE
suffix:semicolon
)brace
op_star
id|phandle
op_assign
(paren
id|sgl_handle_t
)paren
id|psgl
suffix:semicolon
r_return
id|DMA_STATUS_GOOD
suffix:semicolon
)brace
multiline_comment|/*&n; * Destroy a scatter/gather list handle that was created by alloc_dma_handle().&n; * The list must be empty (contain no elements).&n; */
DECL|function|free_dma_handle
r_void
id|free_dma_handle
c_func
(paren
id|sgl_handle_t
id|handle
)paren
(brace
id|sgl_list_info_t
op_star
id|psgl
op_assign
(paren
id|sgl_list_info_t
op_star
)paren
id|handle
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handle
)paren
(brace
macro_line|#ifdef DEBUG_405DMA
id|printk
c_func
(paren
l_string|&quot;free_dma_handle: got NULL&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|psgl-&gt;phead
)paren
(brace
macro_line|#ifdef DEBUG_405DMA
id|printk
c_func
(paren
l_string|&quot;free_dma_handle: list not empty&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|psgl-&gt;dma_addr
)paren
(brace
multiline_comment|/* should never happen */
macro_line|#ifdef DEBUG_405DMA
id|printk
c_func
(paren
l_string|&quot;free_dma_handle: no dma address&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
multiline_comment|/* wrong not a PCI device -armin */
multiline_comment|/*  pci_free_consistent(NULL, SGL_LIST_SIZE, (void *)psgl, psgl-&gt;dma_addr); */
singleline_comment|//&t;free_pages((unsigned long)psgl, get_order(SGL_LIST_SIZE));
id|consistent_free
c_func
(paren
(paren
r_void
op_star
)paren
id|psgl
)paren
suffix:semicolon
)brace
DECL|variable|hw_init_dma_channel
id|EXPORT_SYMBOL
c_func
(paren
id|hw_init_dma_channel
)paren
suffix:semicolon
DECL|variable|get_channel_config
id|EXPORT_SYMBOL
c_func
(paren
id|get_channel_config
)paren
suffix:semicolon
DECL|variable|set_channel_priority
id|EXPORT_SYMBOL
c_func
(paren
id|set_channel_priority
)paren
suffix:semicolon
DECL|variable|get_peripheral_width
id|EXPORT_SYMBOL
c_func
(paren
id|get_peripheral_width
)paren
suffix:semicolon
DECL|variable|alloc_dma_handle
id|EXPORT_SYMBOL
c_func
(paren
id|alloc_dma_handle
)paren
suffix:semicolon
DECL|variable|free_dma_handle
id|EXPORT_SYMBOL
c_func
(paren
id|free_dma_handle
)paren
suffix:semicolon
DECL|variable|dma_channels
id|EXPORT_SYMBOL
c_func
(paren
id|dma_channels
)paren
suffix:semicolon
eof

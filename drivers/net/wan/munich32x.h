multiline_comment|/*&n; *&t;Defines for comx-hw-slicecom.c - MUNICH32X specific&n; *&n; *&t;Author:        Bartok Istvan &lt;bartoki@itc.hu&gt;&n; *&t;Last modified: Tue Jan 11 14:27:36 CET 2000&n; *&n; *&t;:set tabstop=6&n; */
DECL|macro|TXBUFFER_SIZE
mdefine_line|#define TXBUFFER_SIZE&t;1536&t;&t;&t;/* Max mennyit tud a kartya hardver atvenni&t;&t;&t;&t;*/
DECL|macro|RXBUFFER_SIZE
mdefine_line|#define RXBUFFER_SIZE&t;(TXBUFFER_SIZE+4)&t;/* For Rx reasons it must be a multiple of 4, and =&gt;4 (page 265)&t;*/
multiline_comment|/* +4 .. see page 265, bit FE&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* TOD: a MODE1-be nem is ezt teszem, hanem a TXBUFFER-t, lehet hogy nem is kell? */
singleline_comment|//#define PCI_VENDOR_ID_SIEMENS&t;&t;&t;0x110a
DECL|macro|PCI_DEVICE_ID_SIEMENS_MUNICH32X
mdefine_line|#define PCI_DEVICE_ID_SIEMENS_MUNICH32X&t;0x2101
multiline_comment|/*&n; *&t;PCI config space registers (page 120)&n; */
DECL|macro|MUNICH_PCI_PCIRES
mdefine_line|#define MUNICH_PCI_PCIRES&t;0x4c&t;&t;/* 0xe0000 resets&t;the chip&t;*/
multiline_comment|/*&n; *&t;MUNICH slave register offsets relative to base_address[0] (PCI BAR1) (page 181):&n; *&t;offsets are in bytes, registers are u32&squot;s, so we need a &gt;&gt;2 for indexing&n; *&t;the int[] by byte offsets. Use it like:&n; *&n; *&t;bar1[ STAT ] = ~0L;  or&n; *&t;x = bar1[ STAT ];&n; */
DECL|macro|CONF
mdefine_line|#define CONF&t;(0x00 &gt;&gt; 2)
DECL|macro|CMD
mdefine_line|#define CMD&t;&t;(0x04 &gt;&gt; 2)
DECL|macro|STAT
mdefine_line|#define STAT&t;(0x08 &gt;&gt; 2)
DECL|macro|STACK
mdefine_line|#define STACK&t;(0x08 &gt;&gt; 2)
DECL|macro|IMASK
mdefine_line|#define IMASK&t;(0x0c &gt;&gt; 2)
DECL|macro|PIQBA
mdefine_line|#define PIQBA&t;(0x14 &gt;&gt; 2)
DECL|macro|PIQL
mdefine_line|#define PIQL&t;(0x18 &gt;&gt; 2)
DECL|macro|MODE1
mdefine_line|#define MODE1&t;(0x20 &gt;&gt; 2)
DECL|macro|MODE2
mdefine_line|#define MODE2&t;(0x24 &gt;&gt; 2)
DECL|macro|CCBA
mdefine_line|#define CCBA&t;(0x28 &gt;&gt; 2)
DECL|macro|TXPOLL
mdefine_line|#define TXPOLL&t;(0x2c &gt;&gt; 2)
DECL|macro|TIQBA
mdefine_line|#define TIQBA&t;(0x30 &gt;&gt; 2)
DECL|macro|TIQL
mdefine_line|#define TIQL&t;(0x34 &gt;&gt; 2)
DECL|macro|RIQBA
mdefine_line|#define RIQBA&t;(0x38 &gt;&gt; 2)
DECL|macro|RIQL
mdefine_line|#define RIQL&t;(0x3c &gt;&gt; 2)
DECL|macro|LCONF
mdefine_line|#define LCONF&t;(0x40 &gt;&gt; 2)&t;&t;/* LBI Configuration Register&t;&t;*/
DECL|macro|LCCBA
mdefine_line|#define LCCBA&t;(0x44 &gt;&gt; 2)&t;&t;/* LBI Configuration Control Block&t;*/&t;/* DE: lehet hogy nem is kell? */
DECL|macro|LTIQBA
mdefine_line|#define LTIQBA&t;(0x50 &gt;&gt; 2)&t;&t;/* DE: lehet hogy nem is kell? page 210: LBI DMA Controller intq - nem hasznalunk DMA-t.. */
DECL|macro|LTIQL
mdefine_line|#define LTIQL&t;(0x54 &gt;&gt; 2)&t;&t;/* DE: lehet hogy nem is kell? */
DECL|macro|LRIQBA
mdefine_line|#define LRIQBA&t;(0x58 &gt;&gt; 2)&t;&t;/* DE: lehet hogy nem is kell? */
DECL|macro|LRIQL
mdefine_line|#define LRIQL&t;(0x5c &gt;&gt; 2)&t;&t;/* DE: lehet hogy nem is kell? */
DECL|macro|LREG0
mdefine_line|#define LREG0&t;(0x60 &gt;&gt; 2)&t;&t;/* LBI Indirect External Configuration register 0&t;*/
DECL|macro|LREG1
mdefine_line|#define LREG1&t;(0x64 &gt;&gt; 2)
DECL|macro|LREG2
mdefine_line|#define LREG2&t;(0x68 &gt;&gt; 2)
DECL|macro|LREG3
mdefine_line|#define LREG3&t;(0x6c &gt;&gt; 2)
DECL|macro|LREG4
mdefine_line|#define LREG4&t;(0x70 &gt;&gt; 2)
DECL|macro|LREG5
mdefine_line|#define LREG5&t;(0x74 &gt;&gt; 2)
DECL|macro|LREG6
mdefine_line|#define LREG6&t;(0x78 &gt;&gt; 2)&t;&t;/* LBI Indirect External Configuration register 6&t;&t;*/
DECL|macro|LSTAT
mdefine_line|#define LSTAT&t;(0x7c &gt;&gt; 2)&t;&t;/* LBI Status Register&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|GPDIR
mdefine_line|#define GPDIR&t;(0x80 &gt;&gt; 2)&t;&t;/* General Purpose Bus DIRection - 0..input, 1..output&t;*/
DECL|macro|GPDATA
mdefine_line|#define GPDATA&t;(0x84 &gt;&gt; 2)&t;&t;/* General Purpose Bus DATA&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&n; *&t;MUNICH commands: (they go into register CMD)&n; */
DECL|macro|CMD_ARPCM
mdefine_line|#define CMD_ARPCM&t;0x01&t;&t;&t;/* Action Request Serial PCM Core&t;*/
DECL|macro|CMD_ARLBI
mdefine_line|#define CMD_ARLBI&t;0x02&t;&t;&t;/* Action Request LBI&t;&t;&t;*/
multiline_comment|/*&n; *&t;MUNICH event bits in the STAT, STACK, IMASK registers (page 188,189)&n; */
DECL|macro|STAT_PTI
mdefine_line|#define STAT_PTI&t;(1 &lt;&lt; 15)
DECL|macro|STAT_PRI
mdefine_line|#define STAT_PRI&t;(1 &lt;&lt; 14)
DECL|macro|STAT_LTI
mdefine_line|#define STAT_LTI&t;(1 &lt;&lt; 13)
DECL|macro|STAT_LRI
mdefine_line|#define STAT_LRI&t;(1 &lt;&lt; 12)
DECL|macro|STAT_IOMI
mdefine_line|#define STAT_IOMI&t;(1 &lt;&lt; 11)
DECL|macro|STAT_SSCI
mdefine_line|#define STAT_SSCI&t;(1 &lt;&lt; 10)
DECL|macro|STAT_LBII
mdefine_line|#define STAT_LBII&t;(1 &lt;&lt; 9)
DECL|macro|STAT_MBI
mdefine_line|#define STAT_MBI&t;(1 &lt;&lt; 8)
DECL|macro|STAT_TI
mdefine_line|#define STAT_TI&t;(1 &lt;&lt; 6)
DECL|macro|STAT_TSPA
mdefine_line|#define STAT_TSPA&t;(1 &lt;&lt; 5)
DECL|macro|STAT_RSPA
mdefine_line|#define STAT_RSPA&t;(1 &lt;&lt; 4)
DECL|macro|STAT_LBIF
mdefine_line|#define STAT_LBIF&t;(1 &lt;&lt; 3)
DECL|macro|STAT_LBIA
mdefine_line|#define STAT_LBIA&t;(1 &lt;&lt; 2)
DECL|macro|STAT_PCMF
mdefine_line|#define STAT_PCMF&t;(1 &lt;&lt; 1)
DECL|macro|STAT_PCMA
mdefine_line|#define STAT_PCMA&t;(1) 
multiline_comment|/*&n; *&t;We do not handle these (and do not touch their STAT bits) in the interrupt loop&n; */
DECL|macro|STAT_NOT_HANDLED_BY_INTERRUPT
mdefine_line|#define STAT_NOT_HANDLED_BY_INTERRUPT&t;(STAT_PCMF | STAT_PCMA)
multiline_comment|/*&n; *&t;MUNICH MODE1/MODE2 slave register fields (page 193,196)&n; *&t;these are not all masks, MODE1_XX_YY are my magic values!&n; */
DECL|macro|MODE1_PCM_E1
mdefine_line|#define MODE1_PCM_E1&t;(1 &lt;&lt; 31)&t;&t;/* E1, 2.048 Mbit/sec&t;&t;*/
DECL|macro|MODE1_TBS_4
mdefine_line|#define MODE1_TBS_4&t;(1 &lt;&lt; 24)&t;&t;/* TBS = 4 .. no Tx bit shift&t;*/
DECL|macro|MODE1_RBS_4
mdefine_line|#define MODE1_RBS_4&t;(1 &lt;&lt; 18)&t;&t;/* RBS = 4 .. no Rx bit shift&t;*/
DECL|macro|MODE1_REN
mdefine_line|#define MODE1_REN&t;&t;(1 &lt;&lt; 15)&t;&t;/* Rx Enable&t;&t;&t;*/
DECL|macro|MODE1_MFL_MY
mdefine_line|#define MODE1_MFL_MY&t;TXBUFFER_SIZE&t;/* Maximum Frame Length&t;&t;*/
DECL|macro|MODE1_MAGIC
mdefine_line|#define MODE1_MAGIC&t;(MODE1_PCM_E1 | MODE1_TBS_4 | MODE1_RBS_4 | MODE1_REN | MODE1_MFL_MY)
DECL|macro|MODE2_HPOLL
mdefine_line|#define MODE2_HPOLL&t;(1 &lt;&lt; 8)&t;&t;/* Hold Poll&t;&t;&t;*/
DECL|macro|MODE2_SPOLL
mdefine_line|#define MODE2_SPOLL&t;(1 &lt;&lt; 7)&t;&t;/* Slow Poll&t;&t;&t;*/
DECL|macro|MODE2_TSF
mdefine_line|#define MODE2_TSF&t;&t;(1)&t;&t;&t;/* real magic - discovered by probing :)&t;*/
singleline_comment|// #define MODE2_MAGIC&t;(MODE2_TSF)
DECL|macro|MODE2_MAGIC
mdefine_line|#define MODE2_MAGIC&t;(MODE2_SPOLL | MODE2_TSF)
multiline_comment|/*&n; *&t;LCONF bits (page 205)&n; *&t;these are not all masks, LCONF_XX_YY are my magic values!&n; */
DECL|macro|LCONF_IPA
mdefine_line|#define LCONF_IPA&t;&t;&t;(1 &lt;&lt; 31)&t;/* Interrupt Pass. Use 1 for FALC54&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|LCONF_DCA
mdefine_line|#define LCONF_DCA&t;&t;&t;(1 &lt;&lt; 30)&t;/* Disregard the int&squot;s for Channel A - DMSM does not try to handle them&t;*/
DECL|macro|LCONF_DCB
mdefine_line|#define LCONF_DCB&t;&t;&t;(1 &lt;&lt; 29)&t;/* Disregard the int&squot;s for Channel B&t;&t;&t;&t;&t;&t;*/
DECL|macro|LCONF_EBCRES
mdefine_line|#define LCONF_EBCRES&t;&t;(1 &lt;&lt; 22)&t;/* Reset LBI External Bus Controller, 0..reset, 1..normal operation&t;*/
DECL|macro|LCONF_LBIRES
mdefine_line|#define LCONF_LBIRES&t;&t;(1 &lt;&lt; 21)&t;/* Reset LBI DMSM, 0..reset, 1..normal operation&t;&t;&t;&t;*/
DECL|macro|LCONF_BTYP_16DEMUX
mdefine_line|#define LCONF_BTYP_16DEMUX&t;(1 &lt;&lt; 7)&t;/* 16-bit demultiplexed bus&t;*/
DECL|macro|LCONF_ABM
mdefine_line|#define LCONF_ABM&t;&t;&t;(1 &lt;&lt; 4)&t;/* Arbitration Master&t;&t;*/
multiline_comment|/* writing LCONF_MAGIC1 followed by a LCONF_MAGIC2 into LCONF resets the EBC and DMSM: */
DECL|macro|LCONF_MAGIC1
mdefine_line|#define LCONF_MAGIC1&t;&t;(LCONF_BTYP_16DEMUX | LCONF_ABM | LCONF_IPA | LCONF_DCA | LCONF_DCB)
DECL|macro|LCONF_MAGIC2
mdefine_line|#define LCONF_MAGIC2&t;&t;(LCONF_MAGIC1 | LCONF_EBCRES | LCONF_LBIRES)
multiline_comment|/*&n; *&t;LREGx magic values if a FALC54 is on the LBI (page 217)&n; */
DECL|macro|LREG0_MAGIC
mdefine_line|#define LREG0_MAGIC&t;0x00000264
DECL|macro|LREG1_MAGIC
mdefine_line|#define LREG1_MAGIC&t;0x6e6a6b66
DECL|macro|LREG2_MAGIC
mdefine_line|#define LREG2_MAGIC&t;0x00000264
DECL|macro|LREG3_MAGIC
mdefine_line|#define LREG3_MAGIC&t;0x6e686966
DECL|macro|LREG4_MAGIC
mdefine_line|#define LREG4_MAGIC&t;0x00000000
DECL|macro|LREG5_MAGIC
mdefine_line|#define LREG5_MAGIC&t;( (7&lt;&lt;27) | (3&lt;&lt;24) | (1&lt;&lt;21) | (7&lt;&lt;3) | (2&lt;&lt;9) )
multiline_comment|/*&n; *&t;PCM Action Specification fields (munich_ccb_t.action_spec)&n; */
DECL|macro|CCB_ACTIONSPEC_IN
mdefine_line|#define CCB_ACTIONSPEC_IN&t;&t;&t;(1 &lt;&lt; 15)&t;/* init&t;&t;&t;&t;*/
DECL|macro|CCB_ACTIONSPEC_ICO
mdefine_line|#define CCB_ACTIONSPEC_ICO&t;&t;&t;(1 &lt;&lt; 14)&t;/* init only this channel&t;*/
DECL|macro|CCB_ACTIONSPEC_RES
mdefine_line|#define CCB_ACTIONSPEC_RES&t;&t;&t;(1 &lt;&lt; 6)&t;/* reset all channels&t;&t;*/
DECL|macro|CCB_ACTIONSPEC_LOC
mdefine_line|#define CCB_ACTIONSPEC_LOC&t;&t;&t;(1 &lt;&lt; 5)
DECL|macro|CCB_ACTIONSPEC_LOOP
mdefine_line|#define CCB_ACTIONSPEC_LOOP&t;&t;&t;(1 &lt;&lt; 4)
DECL|macro|CCB_ACTIONSPEC_LOOPI
mdefine_line|#define CCB_ACTIONSPEC_LOOPI&t;&t;&t;(1 &lt;&lt; 3)
DECL|macro|CCB_ACTIONSPEC_IA
mdefine_line|#define CCB_ACTIONSPEC_IA&t;&t;&t;(1 &lt;&lt; 2)
multiline_comment|/*&n; *&t;Interrupt Information bits in the TIQ, RIQ&n; */
DECL|macro|PCM_INT_HI
mdefine_line|#define PCM_INT_HI&t;(1 &lt;&lt; 12)
DECL|macro|PCM_INT_FI
mdefine_line|#define PCM_INT_FI&t;(1 &lt;&lt; 11)
DECL|macro|PCM_INT_IFC
mdefine_line|#define PCM_INT_IFC&t;(1 &lt;&lt; 10)
DECL|macro|PCM_INT_SF
mdefine_line|#define PCM_INT_SF&t;(1 &lt;&lt; 9)
DECL|macro|PCM_INT_ERR
mdefine_line|#define PCM_INT_ERR&t;(1 &lt;&lt; 8)
DECL|macro|PCM_INT_FO
mdefine_line|#define PCM_INT_FO&t;(1 &lt;&lt; 7)
DECL|macro|PCM_INT_FE2
mdefine_line|#define PCM_INT_FE2&t;(1 &lt;&lt; 6)
DECL|macro|PCM_INT_CHANNEL
mdefine_line|#define PCM_INT_CHANNEL( info )&t;(info &amp; 0x1F)
multiline_comment|/*&n; *&t;Rx status info in the rx_desc_t.status&n; */
DECL|macro|RX_STATUS_SF
mdefine_line|#define RX_STATUS_SF&t;(1 &lt;&lt; 6)
DECL|macro|RX_STATUS_LOSS
mdefine_line|#define RX_STATUS_LOSS&t;(1 &lt;&lt; 5)
DECL|macro|RX_STATUS_CRCO
mdefine_line|#define RX_STATUS_CRCO&t;(1 &lt;&lt; 4)
DECL|macro|RX_STATUS_NOB
mdefine_line|#define RX_STATUS_NOB&t;(1 &lt;&lt; 3)
DECL|macro|RX_STATUS_LFD
mdefine_line|#define RX_STATUS_LFD&t;(1 &lt;&lt; 2)
DECL|macro|RX_STATUS_RA
mdefine_line|#define RX_STATUS_RA&t;(1 &lt;&lt; 1)
DECL|macro|RX_STATUS_ROF
mdefine_line|#define RX_STATUS_ROF&t;1 
eof

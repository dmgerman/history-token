multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *  linux/include/asm-arm/arch-l7200/sib.h&n; *&n; *  Registers and helper functions for the Serial Interface Bus.&n; *&n; *  (C) Copyright 2000, S A McConnell  (samcconn@cotw.com)&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
multiline_comment|/****************************************************************************/
DECL|macro|SIB_OFF
mdefine_line|#define SIB_OFF   0x00040000  /* Offset from IO_START to the SIB reg&squot;s. */
multiline_comment|/* IO_START and IO_BASE are defined in hardware.h */
DECL|macro|SIB_START
mdefine_line|#define SIB_START (IO_START + SIB_OFF) /* Physical addr of the SIB reg. */
DECL|macro|SIB_BASE
mdefine_line|#define SIB_BASE  (IO_BASE  + SIB_OFF) /* Virtual addr of the SIB reg.  */
multiline_comment|/* Offsets from the start of the SIB for all the registers. */
multiline_comment|/* Define the SIB registers for use by device drivers and the kernel. */
r_typedef
r_struct
(brace
DECL|member|MCCR
r_int
r_int
id|MCCR
suffix:semicolon
multiline_comment|/* SIB Control Register           Offset: 0x00 */
DECL|member|RES1
r_int
r_int
id|RES1
suffix:semicolon
multiline_comment|/* Reserved                       Offset: 0x04 */
DECL|member|MCDR0
r_int
r_int
id|MCDR0
suffix:semicolon
multiline_comment|/* SIB Data Register 0            Offset: 0x08 */
DECL|member|MCDR1
r_int
r_int
id|MCDR1
suffix:semicolon
multiline_comment|/* SIB Data Register 1            Offset: 0x0c */
DECL|member|MCDR2
r_int
r_int
id|MCDR2
suffix:semicolon
multiline_comment|/* SIB Data Register 2 (UCB1x00)  Offset: 0x10 */
DECL|member|RES2
r_int
r_int
id|RES2
suffix:semicolon
multiline_comment|/* Reserved                       Offset: 0x14 */
DECL|member|MCSR
r_int
r_int
id|MCSR
suffix:semicolon
multiline_comment|/* SIB Status Register            Offset: 0x18 */
DECL|typedef|SIB_Interface
)brace
id|SIB_Interface
suffix:semicolon
DECL|macro|SIB
mdefine_line|#define SIB ((volatile SIB_Interface *) (SIB_BASE))
multiline_comment|/* MCCR */
DECL|macro|INTERNAL_FREQ
mdefine_line|#define INTERNAL_FREQ   9216000  /* Hertz */
DECL|macro|AUDIO_FREQ
mdefine_line|#define AUDIO_FREQ         5000  /* Hertz */
DECL|macro|TELECOM_FREQ
mdefine_line|#define TELECOM_FREQ       5000  /* Hertz */
DECL|macro|AUDIO_DIVIDE
mdefine_line|#define AUDIO_DIVIDE    (INTERNAL_FREQ / (32 * AUDIO_FREQ))
DECL|macro|TELECOM_DIVIDE
mdefine_line|#define TELECOM_DIVIDE  (INTERNAL_FREQ / (32 * TELECOM_FREQ))
DECL|macro|MCCR_ASD57
mdefine_line|#define MCCR_ASD57      AUDIO_DIVIDE
DECL|macro|MCCR_TSD57
mdefine_line|#define MCCR_TSD57      (TELECOM_DIVIDE &lt;&lt; 8)
DECL|macro|MCCR_MCE
mdefine_line|#define MCCR_MCE        (1 &lt;&lt; 16)             /* SIB enable */
DECL|macro|MCCR_ECS
mdefine_line|#define MCCR_ECS        (1 &lt;&lt; 17)             /* External Clock Select */
DECL|macro|MCCR_ADM
mdefine_line|#define MCCR_ADM        (1 &lt;&lt; 18)             /* A/D Data Sampling */
DECL|macro|MCCR_PMC
mdefine_line|#define MCCR_PMC        (1 &lt;&lt; 26)             /* PIN Multiplexer Control */
DECL|macro|GET_ASD
mdefine_line|#define GET_ASD ((SIB-&gt;MCCR &gt;&gt;  0) &amp; 0x3f) /* Audio Sample Rate Div. */
DECL|macro|GET_TSD
mdefine_line|#define GET_TSD ((SIB-&gt;MCCR &gt;&gt;  8) &amp; 0x3f) /* Telcom Sample Rate Div. */
DECL|macro|GET_MCE
mdefine_line|#define GET_MCE ((SIB-&gt;MCCR &gt;&gt; 16) &amp; 0x01) /* SIB Enable */
DECL|macro|GET_ECS
mdefine_line|#define GET_ECS ((SIB-&gt;MCCR &gt;&gt; 17) &amp; 0x01) /* External Clock Select */
DECL|macro|GET_ADM
mdefine_line|#define GET_ADM ((SIB-&gt;MCCR &gt;&gt; 18) &amp; 0x01) /* A/D Data Sampling Mode */
DECL|macro|GET_TTM
mdefine_line|#define GET_TTM ((SIB-&gt;MCCR &gt;&gt; 19) &amp; 0x01) /* Telco Trans. FIFO I mask */ 
DECL|macro|GET_TRM
mdefine_line|#define GET_TRM ((SIB-&gt;MCCR &gt;&gt; 20) &amp; 0x01) /* Telco Recv. FIFO I mask */
DECL|macro|GET_ATM
mdefine_line|#define GET_ATM ((SIB-&gt;MCCR &gt;&gt; 21) &amp; 0x01) /* Audio Trans. FIFO I mask */ 
DECL|macro|GET_ARM
mdefine_line|#define GET_ARM ((SIB-&gt;MCCR &gt;&gt; 22) &amp; 0x01) /* Audio Recv. FIFO I mask */
DECL|macro|GET_LBM
mdefine_line|#define GET_LBM ((SIB-&gt;MCCR &gt;&gt; 23) &amp; 0x01) /* Loop Back Mode */
DECL|macro|GET_ECP
mdefine_line|#define GET_ECP ((SIB-&gt;MCCR &gt;&gt; 24) &amp; 0x03) /* Extern. Clck Prescale sel */
DECL|macro|GET_PMC
mdefine_line|#define GET_PMC ((SIB-&gt;MCCR &gt;&gt; 26) &amp; 0x01) /* PIN Multiplexer Control */
DECL|macro|GET_ERI
mdefine_line|#define GET_ERI ((SIB-&gt;MCCR &gt;&gt; 27) &amp; 0x01) /* External Read Interrupt */
DECL|macro|GET_EWI
mdefine_line|#define GET_EWI ((SIB-&gt;MCCR &gt;&gt; 28) &amp; 0x01) /* External Write Interrupt */
multiline_comment|/* MCDR0 */
DECL|macro|AUDIO_RECV
mdefine_line|#define AUDIO_RECV     ((SIB-&gt;MCDR0 &gt;&gt; 4) &amp; 0xfff)
DECL|macro|AUDIO_WRITE
mdefine_line|#define AUDIO_WRITE(v) ((SIB-&gt;MCDR0 = (v &amp; 0xfff) &lt;&lt; 4))
multiline_comment|/* MCDR1 */
DECL|macro|TELECOM_RECV
mdefine_line|#define TELECOM_RECV     ((SIB-&gt;MCDR1 &gt;&gt; 2) &amp; 032fff)
DECL|macro|TELECOM_WRITE
mdefine_line|#define TELECOM_WRITE(v) ((SIB-&gt;MCDR1 = (v &amp; 0x3fff) &lt;&lt; 2))
multiline_comment|/* MCSR */
DECL|macro|MCSR_ATU
mdefine_line|#define MCSR_ATU (1 &lt;&lt; 4)  /* Audio Transmit FIFO Underrun */
DECL|macro|MCSR_ARO
mdefine_line|#define MCSR_ARO (1 &lt;&lt; 5)  /* Audio Receive  FIFO Underrun */
DECL|macro|MCSR_TTU
mdefine_line|#define MCSR_TTU (1 &lt;&lt; 6)  /* TELECOM Transmit FIFO Underrun */
DECL|macro|MCSR_TRO
mdefine_line|#define MCSR_TRO (1 &lt;&lt; 7)  /* TELECOM Receive  FIFO Underrun */
DECL|macro|MCSR_CLEAR_UNDERUN_BITS
mdefine_line|#define MCSR_CLEAR_UNDERUN_BITS (MCSR_ATU | MCSR_ARO | MCSR_TTU | MCSR_TRO)
DECL|macro|GET_ATS
mdefine_line|#define GET_ATS ((SIB-&gt;MCSR &gt;&gt;  0) &amp; 0x01) /* Audio Transmit FIFO Service Req*/
DECL|macro|GET_ARS
mdefine_line|#define GET_ARS ((SIB-&gt;MCSR &gt;&gt;  1) &amp; 0x01) /* Audio Recv FIFO Service Request*/
DECL|macro|GET_TTS
mdefine_line|#define GET_TTS ((SIB-&gt;MCSR &gt;&gt;  2) &amp; 0x01) /* TELECOM Transmit FIFO  Flag */
DECL|macro|GET_TRS
mdefine_line|#define GET_TRS ((SIB-&gt;MCSR &gt;&gt;  3) &amp; 0x01) /* TELECOM Recv FIFO Service Req. */
DECL|macro|GET_ATU
mdefine_line|#define GET_ATU ((SIB-&gt;MCSR &gt;&gt;  4) &amp; 0x01) /* Audio Transmit FIFO Underrun */
DECL|macro|GET_ARO
mdefine_line|#define GET_ARO ((SIB-&gt;MCSR &gt;&gt;  5) &amp; 0x01) /* Audio Receive  FIFO Underrun */
DECL|macro|GET_TTU
mdefine_line|#define GET_TTU ((SIB-&gt;MCSR &gt;&gt;  6) &amp; 0x01) /* TELECOM Transmit FIFO Underrun */
DECL|macro|GET_TRO
mdefine_line|#define GET_TRO ((SIB-&gt;MCSR &gt;&gt;  7) &amp; 0x01) /* TELECOM Receive  FIFO Underrun */
DECL|macro|GET_ANF
mdefine_line|#define GET_ANF ((SIB-&gt;MCSR &gt;&gt;  8) &amp; 0x01) /* Audio Transmit FIFO not full */
DECL|macro|GET_ANE
mdefine_line|#define GET_ANE ((SIB-&gt;MCSR &gt;&gt;  9) &amp; 0x01) /* Audio Receive FIFO not empty */
DECL|macro|GET_TNF
mdefine_line|#define GET_TNF ((SIB-&gt;MCSR &gt;&gt; 10) &amp; 0x01) /* Telecom Transmit FIFO not full */
DECL|macro|GET_TNE
mdefine_line|#define GET_TNE ((SIB-&gt;MCSR &gt;&gt; 11) &amp; 0x01) /* Telecom Receive FIFO not empty */
DECL|macro|GET_CWC
mdefine_line|#define GET_CWC ((SIB-&gt;MCSR &gt;&gt; 12) &amp; 0x01) /* Codec Write Complete */
DECL|macro|GET_CRC
mdefine_line|#define GET_CRC ((SIB-&gt;MCSR &gt;&gt; 13) &amp; 0x01) /* Codec Read Complete */
DECL|macro|GET_ACE
mdefine_line|#define GET_ACE ((SIB-&gt;MCSR &gt;&gt; 14) &amp; 0x01) /* Audio Codec Enabled */
DECL|macro|GET_TCE
mdefine_line|#define GET_TCE ((SIB-&gt;MCSR &gt;&gt; 15) &amp; 0x01) /* Telecom Codec Enabled */
multiline_comment|/* MCDR2 */
DECL|macro|MCDR2_rW
mdefine_line|#define MCDR2_rW               (1 &lt;&lt; 16)
DECL|macro|WRITE_MCDR2
mdefine_line|#define WRITE_MCDR2(reg, data) (SIB-&gt;MCDR2 =((reg&lt;&lt;17)|MCDR2_rW|(data&amp;0xffff)))
DECL|macro|MCDR2_WRITE_COMPLETE
mdefine_line|#define MCDR2_WRITE_COMPLETE   GET_CWC
DECL|macro|INITIATE_MCDR2_READ
mdefine_line|#define INITIATE_MCDR2_READ(reg) (SIB-&gt;MCDR2 = (reg &lt;&lt; 17))
DECL|macro|MCDR2_READ_COMPLETE
mdefine_line|#define MCDR2_READ_COMPLETE      GET_CRC
DECL|macro|MCDR2_READ
mdefine_line|#define MCDR2_READ               (SIB-&gt;MCDR2 &amp; 0xffff)
eof

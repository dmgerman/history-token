multiline_comment|/*&n; *&t;6522 Versatile Interface Adapter (VIA)&n; *&n; *&t;There are two of these on the Mac II. Some IRQ&squot;s are vectored&n; *&t;via them as are assorted bits and bobs - eg rtc, adb. The picture&n; *&t;is a bit incomplete as the Mac documentation doesnt cover this well&n; */
macro_line|#ifndef _ASM_MAC_VIA_H_
DECL|macro|_ASM_MAC_VIA_H_
mdefine_line|#define _ASM_MAC_VIA_H_
multiline_comment|/*&n; * Base addresses for the VIAs. There are two in every machine,&n; * although on some machines the second is an RBV or an OSS.&n; * The OSS is different enough that it&squot;s handled separately.&n; *&n; * Do not use these values directly; use the via1 and via2 variables&n; * instead (and don&squot;t forget to check rbv_present when using via2!)&n; */
DECL|macro|VIA1_BASE
mdefine_line|#define VIA1_BASE&t;(0x50F00000)
DECL|macro|VIA2_BASE
mdefine_line|#define VIA2_BASE&t;(0x50F02000)
DECL|macro|RBV_BASE
mdefine_line|#define  RBV_BASE&t;(0x50F26000)
multiline_comment|/*&n; *&t;Not all of these are true post MacII I think.&n; *      CSA: probably the ones CHRP marks as &squot;unused&squot; change purposes&n; *      when the IWM becomes the SWIM.&n; *      http://www.rs6000.ibm.com/resource/technology/chrpio/via5.mak.html&n; *      ftp://ftp.austin.ibm.com/pub/technology/spec/chrp/inwork/CHRP_IORef_1.0.pdf&n; *&n; * also, http://developer.apple.com/technotes/hw/hw_09.html claims the&n; * following changes for IIfx:&n; * VIA1A_vSccWrReq not available and that VIA1A_vSync has moved to an IOP.&n; * Also, &quot;All of the functionality of VIA2 has been moved to other chips&quot;.&n; */
DECL|macro|VIA1A_vSccWrReq
mdefine_line|#define VIA1A_vSccWrReq&t;0x80&t;/* SCC write. (input)&n;&t;&t;&t;&t; * [CHRP] SCC WREQ: Reflects the state of the &n;&t;&t;&t;&t; * Wait/Request pins from the SCC.&n;&t;&t;&t;&t; * [Macintosh Family Hardware]&n;&t;&t;&t;&t; * as CHRP on SE/30,II,IIx,IIcx,IIci.&n;&t;&t;&t;&t; * on IIfx, &quot;0 means an active request&quot;&n;&t;&t;&t;&t; */
DECL|macro|VIA1A_vRev8
mdefine_line|#define VIA1A_vRev8&t;0x40&t;/* Revision 8 board ???&n;                                 * [CHRP] En WaitReqB: Lets the WaitReq_L&n;&t;&t;&t;&t; * signal from port B of the SCC appear on&n;&t;&t;&t;&t; * the PA7 input pin. Output.&n;&t;&t;&t;&t; * [Macintosh Family] On the SE/30, this&n;&t;&t;&t;&t; * is the bit to flip screen buffers.&n;&t;&t;&t;&t; * 0=alternate, 1=main.&n;&t;&t;&t;&t; * on II,IIx,IIcx,IIci,IIfx this is a bit&n;&t;&t;&t;&t; * for Rev ID. 0=II,IIx, 1=IIcx,IIci,IIfx&n;&t;&t;&t;&t; */
DECL|macro|VIA1A_vHeadSel
mdefine_line|#define VIA1A_vHeadSel&t;0x20&t;/* Head select for IWM.&n;&t;&t;&t;&t; * [CHRP] unused.&n;&t;&t;&t;&t; * [Macintosh Family] &quot;Floppy disk&n;&t;&t;&t;&t; * state-control line SEL&quot; on all but IIfx&n;&t;&t;&t;&t; */
DECL|macro|VIA1A_vOverlay
mdefine_line|#define VIA1A_vOverlay&t;0x10    /* [Macintosh Family] On SE/30,II,IIx,IIcx&n;&t;&t;&t;&t; * this bit enables the &quot;Overlay&quot; address&n;&t;&t;&t;&t; * map in the address decoders as it is on&n;&t;&t;&t;&t; * reset for mapping the ROM over the reset&n;&t;&t;&t;&t; * vector. 1=use overlay map.&n;&t;&t;&t;&t; * On the IIci,IIfx it is another bit of the&n;&t;&t;&t;&t; * CPU ID: 0=normal IIci, 1=IIci with parity&n;&t;&t;&t;&t; * feature or IIfx.&n;&t;&t;&t;&t; * [CHRP] En WaitReqA: Lets the WaitReq_L&n;&t;&t;&t;&t; * signal from port A of the SCC appear&n;&t;&t;&t;&t; * on the PA7 input pin (CHRP). Output.&n;&t;&t;&t;&t; * [MkLinux] &quot;Drive Select&quot;&n;&t;&t;&t;&t; *  (with 0x20 being &squot;disk head select&squot;)&n;&t;&t;&t;&t; */
DECL|macro|VIA1A_vSync
mdefine_line|#define VIA1A_vSync&t;0x08    /* [CHRP] Sync Modem: modem clock select:&n;                                 * 1: select the external serial clock to&n;&t;&t;&t;&t; *    drive the SCC&squot;s /RTxCA pin.&n;&t;&t;&t;&t; * 0: Select the 3.6864MHz clock to drive&n;&t;&t;&t;&t; *    the SCC cell.&n;&t;&t;&t;&t; * [Macintosh Family] Correct on all but IIfx&n;&t;&t;&t;&t; */
multiline_comment|/* Macintosh Family Hardware sez: bits 0-2 of VIA1A are volume control&n; * on Macs which had the PWM sound hardware.  Reserved on newer models.&n; * On IIci,IIfx, bits 1-2 are the rest of the CPU ID:&n; * bit 2: 1=IIci, 0=IIfx&n; * bit 1: 1 on both IIci and IIfx.&n; * MkLinux sez bit 0 is &squot;burnin flag&squot; in this case.&n; * CHRP sez: VIA1A bits 0-2 and 5 are &squot;unused&squot;: if programmed as&n; * inputs, these bits will read 0.&n; */
DECL|macro|VIA1A_vVolume
mdefine_line|#define VIA1A_vVolume&t;0x07&t;/* Audio volume mask for PWM */
DECL|macro|VIA1A_CPUID0
mdefine_line|#define VIA1A_CPUID0&t;0x02&t;/* CPU id bit 0 on RBV, others */
DECL|macro|VIA1A_CPUID1
mdefine_line|#define VIA1A_CPUID1&t;0x04&t;/* CPU id bit 0 on RBV, others */
DECL|macro|VIA1A_CPUID2
mdefine_line|#define VIA1A_CPUID2&t;0x10&t;/* CPU id bit 0 on RBV, others */
DECL|macro|VIA1A_CPUID3
mdefine_line|#define VIA1A_CPUID3&t;0x40&t;/* CPU id bit 0 on RBV, others */
multiline_comment|/* Info on VIA1B is from Macintosh Family Hardware &amp; MkLinux.&n; * CHRP offers no info. */
DECL|macro|VIA1B_vSound
mdefine_line|#define VIA1B_vSound&t;0x80&t;/* Sound enable (for compatibility with&n;&t;&t;&t;&t; * PWM hardware) 0=enabled.&n;&t;&t;&t;&t; * Also, on IIci w/parity, shows parity error&n;&t;&t;&t;&t; * 0=error, 1=OK. */
DECL|macro|VIA1B_vMystery
mdefine_line|#define VIA1B_vMystery&t;0x40    /* On IIci, parity enable. 0=enabled,1=disabled&n;&t;&t;&t;&t; * On SE/30, vertical sync interrupt enable.&n;&t;&t;&t;&t; * 0=enabled. This vSync interrupt shows up&n;&t;&t;&t;&t; * as a slot $E interrupt. */
DECL|macro|VIA1B_vADBS2
mdefine_line|#define VIA1B_vADBS2&t;0x20&t;/* ADB state input bit 1 (unused on IIfx) */
DECL|macro|VIA1B_vADBS1
mdefine_line|#define VIA1B_vADBS1&t;0x10&t;/* ADB state input bit 0 (unused on IIfx) */
DECL|macro|VIA1B_vADBInt
mdefine_line|#define VIA1B_vADBInt&t;0x08&t;/* ADB interrupt 0=interrupt (unused on IIfx)*/
DECL|macro|VIA1B_vRTCEnb
mdefine_line|#define VIA1B_vRTCEnb&t;0x04&t;/* Enable Real time clock. 0=enabled. */
DECL|macro|VIA1B_vRTCClk
mdefine_line|#define VIA1B_vRTCClk&t;0x02    /* Real time clock serial-clock line. */
DECL|macro|VIA1B_vRTCData
mdefine_line|#define VIA1B_vRTCData&t;0x01    /* Real time clock serial-data line. */
multiline_comment|/* MkLinux defines the following &quot;VIA1 Register B contents where they&n; * differ from standard VIA1&quot;.  From the naming scheme, we assume they&n; * correspond to a VIA work-alike named &squot;EVR&squot;. */
DECL|macro|EVRB_XCVR
mdefine_line|#define&t;EVRB_XCVR&t;0x08&t;/* XCVR_SESSION* */
DECL|macro|EVRB_FULL
mdefine_line|#define&t;EVRB_FULL&t;0x10&t;/* VIA_FULL */
DECL|macro|EVRB_SYSES
mdefine_line|#define&t;EVRB_SYSES&t;0x20&t;/* SYS_SESSION */
DECL|macro|EVRB_AUXIE
mdefine_line|#define&t;EVRB_AUXIE&t;0x00&t;/* Enable A/UX Interrupt Scheme */
DECL|macro|EVRB_AUXID
mdefine_line|#define&t;EVRB_AUXID&t;0x40&t;/* Disable A/UX Interrupt Scheme */
DECL|macro|EVRB_SFTWRIE
mdefine_line|#define&t;EVRB_SFTWRIE&t;0x00&t;/* Software Interrupt ReQuest */
DECL|macro|EVRB_SFTWRID
mdefine_line|#define&t;EVRB_SFTWRID&t;0x80&t;/* Software Interrupt ReQuest */
multiline_comment|/*&n; *&t;VIA2 A register is the interrupt lines raised off the nubus &n; *&t;slots.&n; *      The below info is from &squot;Macintosh Family Hardware.&squot;&n; *      MkLinux calls the &squot;IIci internal video IRQ&squot; below the &squot;RBV slot 0 irq.&squot;&n; *      It also notes that the slot $9 IRQ is the &squot;Ethernet IRQ&squot; and&n; *      defines the &squot;Video IRQ&squot; as 0x40 for the &squot;EVR&squot; VIA work-alike.&n; *      Perhaps OSS uses vRAM1 and vRAM2 for ADB.&n; */
DECL|macro|VIA2A_vRAM1
mdefine_line|#define VIA2A_vRAM1&t;0x80&t;/* RAM size bit 1 (IIci: reserved) */
DECL|macro|VIA2A_vRAM0
mdefine_line|#define VIA2A_vRAM0&t;0x40&t;/* RAM size bit 0 (IIci: internal video IRQ) */
DECL|macro|VIA2A_vIRQE
mdefine_line|#define VIA2A_vIRQE&t;0x20&t;/* IRQ from slot $E */
DECL|macro|VIA2A_vIRQD
mdefine_line|#define VIA2A_vIRQD&t;0x10&t;/* IRQ from slot $D */
DECL|macro|VIA2A_vIRQC
mdefine_line|#define VIA2A_vIRQC&t;0x08&t;/* IRQ from slot $C */
DECL|macro|VIA2A_vIRQB
mdefine_line|#define VIA2A_vIRQB&t;0x04&t;/* IRQ from slot $B */
DECL|macro|VIA2A_vIRQA
mdefine_line|#define VIA2A_vIRQA&t;0x02&t;/* IRQ from slot $A */
DECL|macro|VIA2A_vIRQ9
mdefine_line|#define VIA2A_vIRQ9&t;0x01&t;/* IRQ from slot $9 */
multiline_comment|/* RAM size bits decoded as follows:&n; * bit1 bit0  size of ICs in bank A&n; *  0    0    256 kbit&n; *  0    1    1 Mbit&n; *  1    0    4 Mbit&n; *  1    1   16 Mbit&n; */
multiline_comment|/*&n; *&t;Register B has the fun stuff in it&n; */
DECL|macro|VIA2B_vVBL
mdefine_line|#define VIA2B_vVBL&t;0x80&t;/* VBL output to VIA1 (60.15Hz) driven by&n;&t;&t;&t;&t; * timer T1.&n;&t;&t;&t;&t; * on IIci, parity test: 0=test mode.&n;&t;&t;&t;&t; * [MkLinux] RBV_PARODD: 1=odd,0=even. */
DECL|macro|VIA2B_vSndJck
mdefine_line|#define VIA2B_vSndJck&t;0x40&t;/* External sound jack status.&n;&t;&t;&t;&t; * 0=plug is inserted.  On SE/30, always 0 */
DECL|macro|VIA2B_vTfr0
mdefine_line|#define VIA2B_vTfr0&t;0x20&t;/* Transfer mode bit 0 ack from NuBus */
DECL|macro|VIA2B_vTfr1
mdefine_line|#define VIA2B_vTfr1&t;0x10&t;/* Transfer mode bit 1 ack from NuBus */
DECL|macro|VIA2B_vMode32
mdefine_line|#define VIA2B_vMode32&t;0x08&t;/* 24/32bit switch - doubles as cache flush&n;&t;&t;&t;&t; * on II, AMU/PMMU control.&n;&t;&t;&t;&t; *   if AMU, 0=24bit to 32bit translation&n;&t;&t;&t;&t; *   if PMMU, 1=PMMU is accessing page table.&n;&t;&t;&t;&t; * on SE/30 tied low.&n;&t;&t;&t;&t; * on IIx,IIcx,IIfx, unused.&n;&t;&t;&t;&t; * on IIci/RBV, cache control. 0=flush cache.&n;&t;&t;&t;&t; */
DECL|macro|VIA2B_vPower
mdefine_line|#define VIA2B_vPower&t;0x04&t;/* Power off, 0=shut off power.&n;&t;&t;&t;&t; * on SE/30 this signal sent to PDS card. */
DECL|macro|VIA2B_vBusLk
mdefine_line|#define VIA2B_vBusLk&t;0x02&t;/* Lock NuBus transactions, 0=locked.&n;&t;&t;&t;&t; * on SE/30 sent to PDS card. */
DECL|macro|VIA2B_vCDis
mdefine_line|#define VIA2B_vCDis&t;0x01&t;/* Cache control. On IIci, 1=disable cache card&n;&t;&t;&t;&t; * on others, 0=disable processor&squot;s instruction&n;&t;&t;&t;&t; * and data caches. */
multiline_comment|/* Apple sez: http://developer.apple.com/technotes/ov/ov_04.html&n; * Another example of a valid function that has no ROM support is the use&n; * of the alternate video page for page-flipping animation. Since there&n; * is no ROM call to flip pages, it is necessary to go play with the&n; * right bit in the VIA chip (6522 Versatile Interface Adapter).&n; * [CSA: don&squot;t know which one this is, but it&squot;s one of &squot;em!]&n; */
multiline_comment|/*&n; *&t;6522 registers - see databook.&n; * CSA: Assignments for VIA1 confirmed from CHRP spec.&n; */
multiline_comment|/* partial address decode.  0xYYXX : XX part for RBV, YY part for VIA */
multiline_comment|/* Note: 15 VIA regs, 8 RBV regs */
DECL|macro|vBufB
mdefine_line|#define vBufB&t;0x0000&t;/* [VIA/RBV]  Register B */
DECL|macro|vBufAH
mdefine_line|#define vBufAH&t;0x0200  /* [VIA only] Buffer A, with handshake. DON&squot;T USE! */
DECL|macro|vDirB
mdefine_line|#define vDirB&t;0x0400  /* [VIA only] Data Direction Register B. */
DECL|macro|vDirA
mdefine_line|#define vDirA&t;0x0600  /* [VIA only] Data Direction Register A. */
DECL|macro|vT1CL
mdefine_line|#define vT1CL&t;0x0800  /* [VIA only] Timer one counter low. */
DECL|macro|vT1CH
mdefine_line|#define vT1CH&t;0x0a00  /* [VIA only] Timer one counter high. */
DECL|macro|vT1LL
mdefine_line|#define vT1LL&t;0x0c00  /* [VIA only] Timer one latches low. */
DECL|macro|vT1LH
mdefine_line|#define vT1LH&t;0x0e00  /* [VIA only] Timer one latches high. */
DECL|macro|vT2CL
mdefine_line|#define vT2CL&t;0x1000  /* [VIA only] Timer two counter low. */
DECL|macro|vT2CH
mdefine_line|#define vT2CH&t;0x1200  /* [VIA only] Timer two counter high. */
DECL|macro|vSR
mdefine_line|#define vSR&t;0x1400  /* [VIA only] Shift register. */
DECL|macro|vACR
mdefine_line|#define vACR&t;0x1600  /* [VIA only] Auxilary control register. */
DECL|macro|vPCR
mdefine_line|#define vPCR&t;0x1800  /* [VIA only] Peripheral control register. */
multiline_comment|/*            CHRP sez never ever to *write* this.&n;&t;&t;&t; *            Mac family says never to *change* this.&n;&t;&t;&t; * In fact we need to initialize it once at start. */
DECL|macro|vIFR
mdefine_line|#define vIFR&t;0x1a00  /* [VIA/RBV]  Interrupt flag register. */
DECL|macro|vIER
mdefine_line|#define vIER&t;0x1c00  /* [VIA/RBV]  Interrupt enable register. */
DECL|macro|vBufA
mdefine_line|#define vBufA&t;0x1e00  /* [VIA/RBV] register A (no handshake) */
multiline_comment|/* The RBV only decodes the bottom eight address lines; the VIA doesn&squot;t&n; * decode the bottom eight -- so vBufB | rBufB will always get you BufB */
multiline_comment|/* CSA: in fact, only bits 0,1, and 4 seem to be decoded.&n; * BUT note the values for rIER and rIFR, where the top 8 bits *do* seem&n; * to matter.  In fact *all* of the top 8 bits seem to matter; &n; * setting rIER=0x1813 and rIFR=0x1803 doesn&squot;t work, either.&n; * Perhaps some sort of &squot;compatibility mode&squot; is built-in? [21-May-1999]&n; */
DECL|macro|rBufB
mdefine_line|#define rBufB   0x0000  /* [VIA/RBV]  Register B */
DECL|macro|rExp
mdefine_line|#define rExp&t;0x0001&t;/* [RBV only] RBV future expansion (always 0) */
DECL|macro|rSIFR
mdefine_line|#define rSIFR&t;0x0002  /* [RBV only] RBV slot interrupts register. */
DECL|macro|rIFR
mdefine_line|#define rIFR&t;0x1a03  /* [VIA/RBV]  RBV interrupt flag register. */
DECL|macro|rMonP
mdefine_line|#define rMonP   0x0010  /* [RBV only] RBV video monitor type. */
DECL|macro|rChpT
mdefine_line|#define rChpT   0x0011  /* [RBV only] RBV test mode register (reads as 0). */
DECL|macro|rSIER
mdefine_line|#define rSIER   0x0012  /* [RBV only] RBV slot interrupt enables. */
DECL|macro|rIER
mdefine_line|#define rIER    0x1c13  /* [VIA/RBV]  RBV interrupt flag enable register. */
DECL|macro|rBufA
mdefine_line|#define rBufA&t;rSIFR   /* the &squot;slot interrupts register&squot; is BufA on a VIA */
multiline_comment|/*&n; * Video monitor parameters, for rMonP:&n; */
DECL|macro|RBV_DEPTH
mdefine_line|#define RBV_DEPTH  0x07&t;/* bits per pixel: 000=1,001=2,010=4,011=8 */
DECL|macro|RBV_MONID
mdefine_line|#define RBV_MONID  0x38&t;/* monitor type, as below. */
DECL|macro|RBV_VIDOFF
mdefine_line|#define RBV_VIDOFF 0x40&t;/* 1 turns off onboard video */
multiline_comment|/* Supported monitor types: */
DECL|macro|MON_15BW
mdefine_line|#define MON_15BW   (1&lt;&lt;3) /* 15&quot; BW portrait. */
DECL|macro|MON_IIGS
mdefine_line|#define MON_IIGS   (2&lt;&lt;3) /* 12&quot; color (modified IIGS monitor). */
DECL|macro|MON_15RGB
mdefine_line|#define MON_15RGB  (5&lt;&lt;3) /* 15&quot; RGB portrait. */
DECL|macro|MON_12OR13
mdefine_line|#define MON_12OR13 (6&lt;&lt;3) /* 12&quot; BW or 13&quot; RGB. */
DECL|macro|MON_NONE
mdefine_line|#define MON_NONE   (7&lt;&lt;3) /* No monitor attached. */
multiline_comment|/* To clarify IER manipulations */
DECL|macro|IER_SET_BIT
mdefine_line|#define IER_SET_BIT(b) (0x80 | (1&lt;&lt;(b)) )
DECL|macro|IER_CLR_BIT
mdefine_line|#define IER_CLR_BIT(b) (0x7F &amp; (1&lt;&lt;(b)) )
macro_line|#ifndef __ASSEMBLY__
r_extern
r_volatile
id|__u8
op_star
id|via1
comma
op_star
id|via2
suffix:semicolon
r_extern
r_int
id|rbv_present
comma
id|via_alt_mapping
suffix:semicolon
r_extern
id|__u8
id|rbv_clear
suffix:semicolon
DECL|function|rbv_set_video_bpp
r_extern
id|__inline__
r_int
id|rbv_set_video_bpp
c_func
(paren
r_int
id|bpp
)paren
(brace
r_char
id|val
op_assign
(paren
id|bpp
op_eq
l_int|1
)paren
ques
c_cond
l_int|0
suffix:colon
(paren
id|bpp
op_eq
l_int|2
)paren
ques
c_cond
l_int|1
suffix:colon
(paren
id|bpp
op_eq
l_int|4
)paren
ques
c_cond
l_int|2
suffix:colon
(paren
id|bpp
op_eq
l_int|8
)paren
ques
c_cond
l_int|3
suffix:colon
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rbv_present
op_logical_or
id|val
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|via2
(braket
id|rMonP
)braket
op_assign
(paren
id|via2
(braket
id|rMonP
)braket
op_amp
op_complement
id|RBV_DEPTH
)paren
op_or
id|val
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_MAC_VIA_H_ */
eof

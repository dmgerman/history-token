multiline_comment|/* internal Peripherals Register address define */
multiline_comment|/* CPU: H8/306x                                 */
macro_line|#if !defined(__REGS_H8306x__)
DECL|macro|__REGS_H8306x__
mdefine_line|#define __REGS_H8306x__ 
macro_line|#if defined(__KERNEL__)
DECL|macro|DASTCR
mdefine_line|#define DASTCR 0xFEE01A
DECL|macro|DADR0
mdefine_line|#define DADR0  0xFEE09C
DECL|macro|DADR1
mdefine_line|#define DADR1  0xFEE09D
DECL|macro|DACR
mdefine_line|#define DACR   0xFEE09E
DECL|macro|ADDRAH
mdefine_line|#define ADDRAH 0xFFFFE0
DECL|macro|ADDRAL
mdefine_line|#define ADDRAL 0xFFFFE1
DECL|macro|ADDRBH
mdefine_line|#define ADDRBH 0xFFFFE2
DECL|macro|ADDRBL
mdefine_line|#define ADDRBL 0xFFFFE3
DECL|macro|ADDRCH
mdefine_line|#define ADDRCH 0xFFFFE4
DECL|macro|ADDRCL
mdefine_line|#define ADDRCL 0xFFFFE5
DECL|macro|ADDRDH
mdefine_line|#define ADDRDH 0xFFFFE6
DECL|macro|ADDRDL
mdefine_line|#define ADDRDL 0xFFFFE7
DECL|macro|ADCSR
mdefine_line|#define ADCSR  0xFFFFE8
DECL|macro|ADCR
mdefine_line|#define ADCR   0xFFFFE9
DECL|macro|BRCR
mdefine_line|#define BRCR   0xFEE013
DECL|macro|ADRCR
mdefine_line|#define ADRCR  0xFEE01E
DECL|macro|CSCR
mdefine_line|#define CSCR   0xFEE01F
DECL|macro|ABWCR
mdefine_line|#define ABWCR  0xFEE020
DECL|macro|ASTCR
mdefine_line|#define ASTCR  0xFEE021
DECL|macro|WCRH
mdefine_line|#define WCRH   0xFEE022
DECL|macro|WCRL
mdefine_line|#define WCRL   0xFEE023
DECL|macro|BCR
mdefine_line|#define BCR    0xFEE024
DECL|macro|DRCRA
mdefine_line|#define DRCRA  0xFEE026
DECL|macro|DRCRB
mdefine_line|#define DRCRB  0xFEE027
DECL|macro|RTMCSR
mdefine_line|#define RTMCSR 0xFEE028
DECL|macro|RTCNT
mdefine_line|#define RTCNT  0xFEE029
DECL|macro|RTCOR
mdefine_line|#define RTCOR  0xFEE02A
DECL|macro|MAR0AR
mdefine_line|#define MAR0AR  0xFFFF20
DECL|macro|MAR0AE
mdefine_line|#define MAR0AE  0xFFFF21
DECL|macro|MAR0AH
mdefine_line|#define MAR0AH  0xFFFF22
DECL|macro|MAR0AL
mdefine_line|#define MAR0AL  0xFFFF23
DECL|macro|ETCR0AL
mdefine_line|#define ETCR0AL 0xFFFF24
DECL|macro|ETCR0AH
mdefine_line|#define ETCR0AH 0xFFFF25
DECL|macro|IOAR0A
mdefine_line|#define IOAR0A  0xFFFF26
DECL|macro|DTCR0A
mdefine_line|#define DTCR0A  0xFFFF27
DECL|macro|MAR0BR
mdefine_line|#define MAR0BR  0xFFFF28
DECL|macro|MAR0BE
mdefine_line|#define MAR0BE  0xFFFF29
DECL|macro|MAR0BH
mdefine_line|#define MAR0BH  0xFFFF2A
DECL|macro|MAR0BL
mdefine_line|#define MAR0BL  0xFFFF2B
DECL|macro|ETCR0BL
mdefine_line|#define ETCR0BL 0xFFFF2C
DECL|macro|ETCR0BH
mdefine_line|#define ETCR0BH 0xFFFF2D
DECL|macro|IOAR0B
mdefine_line|#define IOAR0B  0xFFFF2E
DECL|macro|DTCR0B
mdefine_line|#define DTCR0B  0xFFFF2F
DECL|macro|MAR1AR
mdefine_line|#define MAR1AR  0xFFFF30
DECL|macro|MAR1AE
mdefine_line|#define MAR1AE  0xFFFF31
DECL|macro|MAR1AH
mdefine_line|#define MAR1AH  0xFFFF32
DECL|macro|MAR1AL
mdefine_line|#define MAR1AL  0xFFFF33
DECL|macro|ETCR1AL
mdefine_line|#define ETCR1AL 0xFFFF34
DECL|macro|ETCR1AH
mdefine_line|#define ETCR1AH 0xFFFF35
DECL|macro|IOAR1A
mdefine_line|#define IOAR1A  0xFFFF36
DECL|macro|DTCR1A
mdefine_line|#define DTCR1A  0xFFFF37
DECL|macro|MAR1BR
mdefine_line|#define MAR1BR  0xFFFF38
DECL|macro|MAR1BE
mdefine_line|#define MAR1BE  0xFFFF39
DECL|macro|MAR1BH
mdefine_line|#define MAR1BH  0xFFFF3A
DECL|macro|MAR1BL
mdefine_line|#define MAR1BL  0xFFFF3B
DECL|macro|ETCR1BL
mdefine_line|#define ETCR1BL 0xFFFF3C
DECL|macro|ETCR1BH
mdefine_line|#define ETCR1BH 0xFFFF3D
DECL|macro|IOAR1B
mdefine_line|#define IOAR1B  0xFFFF3E
DECL|macro|DTCR1B
mdefine_line|#define DTCR1B  0xFFFF3F
DECL|macro|ISCR
mdefine_line|#define ISCR 0xFEE014
DECL|macro|IER
mdefine_line|#define IER  0xFEE015
DECL|macro|ISR
mdefine_line|#define ISR  0xFEE016
DECL|macro|IPRA
mdefine_line|#define IPRA 0xFEE018
DECL|macro|IPRB
mdefine_line|#define IPRB 0xFEE019
DECL|macro|P1DDR
mdefine_line|#define P1DDR 0xFEE000
DECL|macro|P2DDR
mdefine_line|#define P2DDR 0xFEE001
DECL|macro|P3DDR
mdefine_line|#define P3DDR 0xFEE002
DECL|macro|P4DDR
mdefine_line|#define P4DDR 0xFEE003
DECL|macro|P5DDR
mdefine_line|#define P5DDR 0xFEE004
DECL|macro|P6DDR
mdefine_line|#define P6DDR 0xFEE005
multiline_comment|/*#define P7DDR 0xFEE006*/
DECL|macro|P8DDR
mdefine_line|#define P8DDR 0xFEE007
DECL|macro|P9DDR
mdefine_line|#define P9DDR 0xFEE008
DECL|macro|PADDR
mdefine_line|#define PADDR 0xFEE009
DECL|macro|PBDDR
mdefine_line|#define PBDDR 0xFEE00A
DECL|macro|P1DR
mdefine_line|#define P1DR  0xFFFFD0
DECL|macro|P2DR
mdefine_line|#define P2DR  0xFFFFD1
DECL|macro|P3DR
mdefine_line|#define P3DR  0xFFFFD2
DECL|macro|P4DR
mdefine_line|#define P4DR  0xFFFFD3
DECL|macro|P5DR
mdefine_line|#define P5DR  0xFFFFD4
DECL|macro|P6DR
mdefine_line|#define P6DR  0xFFFFD5
multiline_comment|/*#define P7DR  0xFFFFD6*/
DECL|macro|P8DR
mdefine_line|#define P8DR  0xFFFFD7
DECL|macro|P9DR
mdefine_line|#define P9DR  0xFFFFD8
DECL|macro|PADR
mdefine_line|#define PADR  0xFFFFD9
DECL|macro|PBDR
mdefine_line|#define PBDR  0xFFFFDA
DECL|macro|P2CR
mdefine_line|#define P2CR  0xFEE03C
DECL|macro|P4CR
mdefine_line|#define P4CR  0xFEE03E
DECL|macro|P5CR
mdefine_line|#define P5CR  0xFEE03F
DECL|macro|SMR0
mdefine_line|#define SMR0  0xFFFFB0
DECL|macro|BRR0
mdefine_line|#define BRR0  0xFFFFB1
DECL|macro|SCR0
mdefine_line|#define SCR0  0xFFFFB2
DECL|macro|TDR0
mdefine_line|#define TDR0  0xFFFFB3
DECL|macro|SSR0
mdefine_line|#define SSR0  0xFFFFB4
DECL|macro|RDR0
mdefine_line|#define RDR0  0xFFFFB5
DECL|macro|SCMR0
mdefine_line|#define SCMR0 0xFFFFB6
DECL|macro|SMR1
mdefine_line|#define SMR1  0xFFFFB8
DECL|macro|BRR1
mdefine_line|#define BRR1  0xFFFFB9
DECL|macro|SCR1
mdefine_line|#define SCR1  0xFFFFBA
DECL|macro|TDR1
mdefine_line|#define TDR1  0xFFFFBB
DECL|macro|SSR1
mdefine_line|#define SSR1  0xFFFFBC
DECL|macro|RDR1
mdefine_line|#define RDR1  0xFFFFBD
DECL|macro|SCMR1
mdefine_line|#define SCMR1 0xFFFFBE
DECL|macro|SMR2
mdefine_line|#define SMR2  0xFFFFC0
DECL|macro|BRR2
mdefine_line|#define BRR2  0xFFFFC1
DECL|macro|SCR2
mdefine_line|#define SCR2  0xFFFFC2
DECL|macro|TDR2
mdefine_line|#define TDR2  0xFFFFC3
DECL|macro|SSR2
mdefine_line|#define SSR2  0xFFFFC4
DECL|macro|RDR2
mdefine_line|#define RDR2  0xFFFFC5
DECL|macro|SCMR2
mdefine_line|#define SCMR2 0xFFFFC6
DECL|macro|MDCR
mdefine_line|#define MDCR   0xFEE000
DECL|macro|SYSCR
mdefine_line|#define SYSCR  0xFEE001
DECL|macro|DIVCR
mdefine_line|#define DIVCR  0xFEE01B
DECL|macro|MSTCRH
mdefine_line|#define MSTCRH 0xFEE01C
DECL|macro|MSTCRL
mdefine_line|#define MSTCRL 0xFEE01D
DECL|macro|FLMCR1
mdefine_line|#define FLMCR1 0xFEE030
DECL|macro|FLMCR2
mdefine_line|#define FLMCR2 0xFEE031
DECL|macro|EBR1
mdefine_line|#define EBR1   0xFEE032
DECL|macro|EBR2
mdefine_line|#define EBR2   0xFEE033
DECL|macro|RAMCR
mdefine_line|#define RAMCR  0xFEE077
DECL|macro|TSTR
mdefine_line|#define TSTR   0xFFFF60
DECL|macro|TSNC
mdefine_line|#define TSNC   0XFFFF61
DECL|macro|TMDR
mdefine_line|#define TMDR   0xFFFF62
DECL|macro|TOLR
mdefine_line|#define TOLR   0xFFFF63
DECL|macro|TISRA
mdefine_line|#define TISRA  0xFFFF64
DECL|macro|TISRB
mdefine_line|#define TISRB  0xFFFF65
DECL|macro|TISRC
mdefine_line|#define TISRC  0xFFFF66
DECL|macro|TCR0
mdefine_line|#define TCR0   0xFFFF68
DECL|macro|TIOR0
mdefine_line|#define TIOR0  0xFFFF69
DECL|macro|TCNT0H
mdefine_line|#define TCNT0H 0xFFFF6A
DECL|macro|TCNT0L
mdefine_line|#define TCNT0L 0xFFFF6B
DECL|macro|GRA0H
mdefine_line|#define GRA0H  0xFFFF6C
DECL|macro|GRA0L
mdefine_line|#define GRA0L  0xFFFF6D
DECL|macro|GRB0H
mdefine_line|#define GRB0H  0xFFFF6E
DECL|macro|GRB0L
mdefine_line|#define GRB0L  0xFFFF6F
DECL|macro|TCR1
mdefine_line|#define TCR1   0xFFFF70
DECL|macro|TIOR1
mdefine_line|#define TIOR1  0xFFFF71
DECL|macro|TCNT1H
mdefine_line|#define TCNT1H 0xFFFF72
DECL|macro|TCNT1L
mdefine_line|#define TCNT1L 0xFFFF73
DECL|macro|GRA1H
mdefine_line|#define GRA1H  0xFFFF74
DECL|macro|GRA1L
mdefine_line|#define GRA1L  0xFFFF75
DECL|macro|GRB1H
mdefine_line|#define GRB1H  0xFFFF76
DECL|macro|GRB1L
mdefine_line|#define GRB1L  0xFFFF77
DECL|macro|TCR3
mdefine_line|#define TCR3   0xFFFF78
DECL|macro|TIOR3
mdefine_line|#define TIOR3  0xFFFF79
DECL|macro|TCNT3H
mdefine_line|#define TCNT3H 0xFFFF7A
DECL|macro|TCNT3L
mdefine_line|#define TCNT3L 0xFFFF7B
DECL|macro|GRA3H
mdefine_line|#define GRA3H  0xFFFF7C
DECL|macro|GRA3L
mdefine_line|#define GRA3L  0xFFFF7D
DECL|macro|GRB3H
mdefine_line|#define GRB3H  0xFFFF7E
DECL|macro|GRB3L
mdefine_line|#define GRB3L  0xFFFF7F
DECL|macro|_8TCR0
mdefine_line|#define _8TCR0  0xFFFF80
DECL|macro|_8TCR1
mdefine_line|#define _8TCR1  0xFFFF81
DECL|macro|_8TCSR0
mdefine_line|#define _8TCSR0 0xFFFF82
DECL|macro|_8TCSR1
mdefine_line|#define _8TCSR1 0xFFFF83
DECL|macro|TCORA0
mdefine_line|#define TCORA0 0xFFFF84
DECL|macro|TCORA1
mdefine_line|#define TCORA1 0xFFFF85
DECL|macro|TCORB0
mdefine_line|#define TCORB0 0xFFFF86
DECL|macro|TCORB1
mdefine_line|#define TCORB1 0xFFFF87
DECL|macro|_8TCNT0
mdefine_line|#define _8TCNT0 0xFFFF88
DECL|macro|_8TCNT1
mdefine_line|#define _8TCNT1 0xFFFF89
DECL|macro|_8TCR2
mdefine_line|#define _8TCR2  0xFFFF90
DECL|macro|_8TCR3
mdefine_line|#define _8TCR3  0xFFFF91
DECL|macro|_8TCSR2
mdefine_line|#define _8TCSR2 0xFFFF92
DECL|macro|_8TCSR3
mdefine_line|#define _8TCSR3 0xFFFF93
DECL|macro|TCORA2
mdefine_line|#define TCORA2 0xFFFF94
DECL|macro|TCORA3
mdefine_line|#define TCORA3 0xFFFF95
DECL|macro|TCORB2
mdefine_line|#define TCORB2 0xFFFF96
DECL|macro|TCORB3
mdefine_line|#define TCORB3 0xFFFF97
DECL|macro|_8TCNT2
mdefine_line|#define _8TCNT2 0xFFFF98
DECL|macro|_8TCNT3
mdefine_line|#define _8TCNT3 0xFFFF99
DECL|macro|TCSR
mdefine_line|#define TCSR   0xFFFF8C
DECL|macro|TCNT
mdefine_line|#define TCNT   0xFFFF8D
DECL|macro|RSTCSR
mdefine_line|#define RSTCSR 0xFFFF8F
DECL|macro|TPMR
mdefine_line|#define TPMR  0xFFFFA0
DECL|macro|TPCR
mdefine_line|#define TPCR  0xFFFFA1
DECL|macro|NDERB
mdefine_line|#define NDERB 0xFFFFA2
DECL|macro|NDERA
mdefine_line|#define NDERA 0xFFFFA3
DECL|macro|NDRB1
mdefine_line|#define NDRB1 0xFFFFA4
DECL|macro|NDRA1
mdefine_line|#define NDRA1 0xFFFFA5
DECL|macro|NDRB2
mdefine_line|#define NDRB2 0xFFFFA6
DECL|macro|NDRA2
mdefine_line|#define NDRA2 0xFFFFA7
DECL|macro|TCSR
mdefine_line|#define TCSR    0xFFFF8C
DECL|macro|TCNT
mdefine_line|#define TCNT    0xFFFF8D
DECL|macro|RSTCSRW
mdefine_line|#define RSTCSRW 0xFFFF8E
DECL|macro|RSTCSRR
mdefine_line|#define RSTCSRR 0xFFFF8F
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __REGS_H8306x__ */
eof

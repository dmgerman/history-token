multiline_comment|/* internal Peripherals Register address define */
multiline_comment|/* CPU: H8/306x                                 */
macro_line|#if !defined(__REGS_H8S267x__)
DECL|macro|__REGS_H8S267x__
mdefine_line|#define __REGS_H8S267x__ 
macro_line|#if defined(__KERNEL__)
DECL|macro|DASTCR
mdefine_line|#define DASTCR 0xFEE01A
DECL|macro|DADR0
mdefine_line|#define DADR0  0xFFFFA4
DECL|macro|DADR1
mdefine_line|#define DADR1  0xFFFFA5
DECL|macro|DACR01
mdefine_line|#define DACR01 0xFFFFA6
DECL|macro|DADR2
mdefine_line|#define DADR2  0xFFFFA8
DECL|macro|DADR3
mdefine_line|#define DADR3  0xFFFFA9
DECL|macro|DACR23
mdefine_line|#define DACR23 0xFFFFAA
DECL|macro|ADDRA
mdefine_line|#define ADDRA  0xFFFF90
DECL|macro|ADDRAH
mdefine_line|#define ADDRAH 0xFFFF90
DECL|macro|ADDRAL
mdefine_line|#define ADDRAL 0xFFFF91
DECL|macro|ADDRB
mdefine_line|#define ADDRB  0xFFFF92
DECL|macro|ADDRBH
mdefine_line|#define ADDRBH 0xFFFF92
DECL|macro|ADDRBL
mdefine_line|#define ADDRBL 0xFFFF93
DECL|macro|ADDRC
mdefine_line|#define ADDRC  0xFFFF94
DECL|macro|ADDRCH
mdefine_line|#define ADDRCH 0xFFFF94
DECL|macro|ADDRCL
mdefine_line|#define ADDRCL 0xFFFF95
DECL|macro|ADDRD
mdefine_line|#define ADDRD  0xFFFF96
DECL|macro|ADDRDH
mdefine_line|#define ADDRDH 0xFFFF96
DECL|macro|ADDRDL
mdefine_line|#define ADDRDL 0xFFFF97
DECL|macro|ADDRE
mdefine_line|#define ADDRE  0xFFFF98
DECL|macro|ADDREH
mdefine_line|#define ADDREH 0xFFFF98
DECL|macro|ADDREL
mdefine_line|#define ADDREL 0xFFFF99
DECL|macro|ADDRF
mdefine_line|#define ADDRF  0xFFFF9A
DECL|macro|ADDRFH
mdefine_line|#define ADDRFH 0xFFFF9A
DECL|macro|ADDRFL
mdefine_line|#define ADDRFL 0xFFFF9B
DECL|macro|ADDRG
mdefine_line|#define ADDRG  0xFFFF9C
DECL|macro|ADDRGH
mdefine_line|#define ADDRGH 0xFFFF9C
DECL|macro|ADDRGL
mdefine_line|#define ADDRGL 0xFFFF9D
DECL|macro|ADDRH
mdefine_line|#define ADDRH  0xFFFF9E
DECL|macro|ADDRHH
mdefine_line|#define ADDRHH 0xFFFF9E
DECL|macro|ADDRHL
mdefine_line|#define ADDRHL 0xFFFF9F
DECL|macro|ADCSR
mdefine_line|#define ADCSR  0xFFFFA0
DECL|macro|ADCR
mdefine_line|#define ADCR   0xFFFFA1
DECL|macro|ABWCR
mdefine_line|#define ABWCR  0xFFFEC0
DECL|macro|ASTCR
mdefine_line|#define ASTCR  0xFFFEC1
DECL|macro|WTCRAH
mdefine_line|#define WTCRAH 0xFFFEC2
DECL|macro|WTCRAL
mdefine_line|#define WTCRAL 0xFFFEC3
DECL|macro|WTCRBH
mdefine_line|#define WTCRBH 0xFFFEC4
DECL|macro|WTCRBL
mdefine_line|#define WTCRBL 0xFFFEC5
DECL|macro|RDNCR
mdefine_line|#define RDNCR  0xFFFEC6
DECL|macro|CSACRH
mdefine_line|#define CSACRH 0xFFFEC8
DECL|macro|CSACRL
mdefine_line|#define CSACRL 0xFFFEC9
DECL|macro|BROMCRH
mdefine_line|#define BROMCRH 0xFFFECA
DECL|macro|BROMCRL
mdefine_line|#define BROMCRL 0xFFFECB
DECL|macro|BCR
mdefine_line|#define BCR    0xFFFECC
DECL|macro|DRAMCR
mdefine_line|#define DRAMCR 0xFFFED0
DECL|macro|DRACCR
mdefine_line|#define DRACCR 0xFFFED2
DECL|macro|REFCR
mdefine_line|#define REFCR  0xFFFED4
DECL|macro|RTCNT
mdefine_line|#define RTCNT  0xFFFED6
DECL|macro|RTCOR
mdefine_line|#define RTCOR  0xFFFED7
DECL|macro|MAR0AH
mdefine_line|#define MAR0AH  0xFFFEE0
DECL|macro|MAR0AL
mdefine_line|#define MAR0AL  0xFFFEE2
DECL|macro|IOAR0A
mdefine_line|#define IOAR0A  0xFFFEE4
DECL|macro|ETCR0A
mdefine_line|#define ETCR0A  0xFFFEE6
DECL|macro|MAR0BH
mdefine_line|#define MAR0BH  0xFFFEE8
DECL|macro|MAR0BL
mdefine_line|#define MAR0BL  0xFFFEEA
DECL|macro|IOAR0B
mdefine_line|#define IOAR0B  0xFFFEEC
DECL|macro|ETCR0B
mdefine_line|#define ETCR0B  0xFFFEEE
DECL|macro|MAR1AH
mdefine_line|#define MAR1AH  0xFFFEF0
DECL|macro|MAR1AL
mdefine_line|#define MAR1AL  0xFFFEF2
DECL|macro|IOAR1A
mdefine_line|#define IOAR1A  0xFFFEF4
DECL|macro|ETCR1A
mdefine_line|#define ETCR1A  0xFFFEF6
DECL|macro|MAR1BH
mdefine_line|#define MAR1BH  0xFFFEF8
DECL|macro|MAR1BL
mdefine_line|#define MAR1BL  0xFFFEFA
DECL|macro|IOAR1B
mdefine_line|#define IOAR1B  0xFFFEFC
DECL|macro|ETCR1B
mdefine_line|#define ETCR1B  0xFFFEFE
DECL|macro|DMAWER
mdefine_line|#define DMAWER  0xFFFF20
DECL|macro|DMATCR
mdefine_line|#define DMATCR  0xFFFF21
DECL|macro|DMACR0A
mdefine_line|#define DMACR0A 0xFFFF22
DECL|macro|DMACR0B
mdefine_line|#define DMACR0B 0xFFFF23
DECL|macro|DMACR1A
mdefine_line|#define DMACR1A 0xFFFF24
DECL|macro|DMACR1B
mdefine_line|#define DMACR1B 0xFFFF25
DECL|macro|DMABCRH
mdefine_line|#define DMABCRH 0xFFFF26
DECL|macro|DMABCRL
mdefine_line|#define DMABCRL 0xFFFF27
DECL|macro|EDSAR0
mdefine_line|#define EDSAR0  0xFFFDC0
DECL|macro|EDDAR0
mdefine_line|#define EDDAR0  0xFFFDC4
DECL|macro|EDTCR0
mdefine_line|#define EDTCR0  0xFFFDC8
DECL|macro|EDMDR0
mdefine_line|#define EDMDR0  0xFFFDCC
DECL|macro|EDMDR0H
mdefine_line|#define EDMDR0H 0xFFFDCC
DECL|macro|EDMDR0L
mdefine_line|#define EDMDR0L 0xFFFDCD
DECL|macro|EDACR0
mdefine_line|#define EDACR0  0xFFFDCE
DECL|macro|EDSAR1
mdefine_line|#define EDSAR1  0xFFFDD0
DECL|macro|EDDAR1
mdefine_line|#define EDDAR1  0xFFFDD4
DECL|macro|EDTCR1
mdefine_line|#define EDTCR1  0xFFFDD8
DECL|macro|EDMDR1
mdefine_line|#define EDMDR1  0xFFFDDC
DECL|macro|EDMDR1H
mdefine_line|#define EDMDR1H 0xFFFDDC
DECL|macro|EDMDR1L
mdefine_line|#define EDMDR1L 0xFFFDDD
DECL|macro|EDACR1
mdefine_line|#define EDACR1  0xFFFDDE
DECL|macro|EDSAR2
mdefine_line|#define EDSAR2  0xFFFDE0
DECL|macro|EDDAR2
mdefine_line|#define EDDAR2  0xFFFDE4
DECL|macro|EDTCR2
mdefine_line|#define EDTCR2  0xFFFDE8
DECL|macro|EDMDR2
mdefine_line|#define EDMDR2  0xFFFDEC
DECL|macro|EDMDR2H
mdefine_line|#define EDMDR2H 0xFFFDEC
DECL|macro|EDMDR2L
mdefine_line|#define EDMDR2L 0xFFFDED
DECL|macro|EDACR2
mdefine_line|#define EDACR2  0xFFFDEE
DECL|macro|EDSAR3
mdefine_line|#define EDSAR3  0xFFFDF0
DECL|macro|EDDAR3
mdefine_line|#define EDDAR3  0xFFFDF4
DECL|macro|EDTCR3
mdefine_line|#define EDTCR3  0xFFFDF8
DECL|macro|EDMDR3
mdefine_line|#define EDMDR3  0xFFFDFC
DECL|macro|EDMDR3H
mdefine_line|#define EDMDR3H 0xFFFDFC
DECL|macro|EDMDR3L
mdefine_line|#define EDMDR3L 0xFFFDFD
DECL|macro|EDACR3
mdefine_line|#define EDACR3  0xFFFDFE
DECL|macro|IPRA
mdefine_line|#define IPRA  0xFFFE00
DECL|macro|IPRB
mdefine_line|#define IPRB  0xFFFE02
DECL|macro|IPRC
mdefine_line|#define IPRC  0xFFFE04
DECL|macro|IPRD
mdefine_line|#define IPRD  0xFFFE06
DECL|macro|IPRE
mdefine_line|#define IPRE  0xFFFE08
DECL|macro|IPRF
mdefine_line|#define IPRF  0xFFFE0A
DECL|macro|IPRG
mdefine_line|#define IPRG  0xFFFE0C
DECL|macro|IPRH
mdefine_line|#define IPRH  0xFFFE0E
DECL|macro|IPRI
mdefine_line|#define IPRI  0xFFFE10
DECL|macro|IPRJ
mdefine_line|#define IPRJ  0xFFFE12
DECL|macro|IPRK
mdefine_line|#define IPRK  0xFFFE14
DECL|macro|ITSR
mdefine_line|#define ITSR  0xFFFE16
DECL|macro|SSIER
mdefine_line|#define SSIER 0xFFFE18
DECL|macro|ISCRH
mdefine_line|#define ISCRH 0xFFFE1A
DECL|macro|ISCRL
mdefine_line|#define ISCRL 0xFFFE1C
DECL|macro|INTCR
mdefine_line|#define INTCR 0xFFFF31
DECL|macro|IER
mdefine_line|#define IER   0xFFFF32
DECL|macro|IERH
mdefine_line|#define IERH  0xFFFF32
DECL|macro|IERL
mdefine_line|#define IERL  0xFFFF33
DECL|macro|ISR
mdefine_line|#define ISR   0xFFFF34
DECL|macro|ISRH
mdefine_line|#define ISRH  0xFFFF34
DECL|macro|ISRL
mdefine_line|#define ISRL  0xFFFF35
DECL|macro|P1DDR
mdefine_line|#define P1DDR 0xFFFE20
DECL|macro|P2DDR
mdefine_line|#define P2DDR 0xFFFE21
DECL|macro|P3DDR
mdefine_line|#define P3DDR 0xFFFE22
DECL|macro|P4DDR
mdefine_line|#define P4DDR 0xFFFE23
DECL|macro|P5DDR
mdefine_line|#define P5DDR 0xFFFE24
DECL|macro|P6DDR
mdefine_line|#define P6DDR 0xFFFE25
DECL|macro|P7DDR
mdefine_line|#define P7DDR 0xFFFE26
DECL|macro|P8DDR
mdefine_line|#define P8DDR 0xFFFE27
DECL|macro|P9DDR
mdefine_line|#define P9DDR 0xFFFE28
DECL|macro|PADDR
mdefine_line|#define PADDR 0xFFFE29
DECL|macro|PBDDR
mdefine_line|#define PBDDR 0xFFFE2A
DECL|macro|PCDDR
mdefine_line|#define PCDDR 0xFFFE2B
DECL|macro|PDDDR
mdefine_line|#define PDDDR 0xFFFE2C
DECL|macro|PEDDR
mdefine_line|#define PEDDR 0xFFFE2D
DECL|macro|PFDDR
mdefine_line|#define PFDDR 0xFFFE2E
DECL|macro|PGDDR
mdefine_line|#define PGDDR 0xFFFE2F
DECL|macro|PHDDR
mdefine_line|#define PHDDR 0xFFFF74
DECL|macro|PFCR0
mdefine_line|#define PFCR0 0xFFFE32
DECL|macro|PFCR1
mdefine_line|#define PFCR1 0xFFFE33
DECL|macro|PFCR2
mdefine_line|#define PFCR2 0xFFFE34
DECL|macro|PAPCR
mdefine_line|#define PAPCR 0xFFFE36
DECL|macro|PBPCR
mdefine_line|#define PBPCR 0xFFFE37
DECL|macro|PCPCR
mdefine_line|#define PCPCR 0xFFFE38
DECL|macro|PDPCR
mdefine_line|#define PDPCR 0xFFFE39
DECL|macro|PEPCR
mdefine_line|#define PEPCR 0xFFFE3A
DECL|macro|P3ODR
mdefine_line|#define P3ODR 0xFFFE3C
DECL|macro|PAODR
mdefine_line|#define PAODR 0xFFFE3D
DECL|macro|P1DR
mdefine_line|#define P1DR  0xFFFF60
DECL|macro|P2DR
mdefine_line|#define P2DR  0xFFFF61
DECL|macro|P3DR
mdefine_line|#define P3DR  0xFFFF62
DECL|macro|P4DR
mdefine_line|#define P4DR  0xFFFF63
DECL|macro|P5DR
mdefine_line|#define P5DR  0xFFFF64
DECL|macro|P6DR
mdefine_line|#define P6DR  0xFFFF65
DECL|macro|P7DR
mdefine_line|#define P7DR  0xFFFF66
DECL|macro|P8DR
mdefine_line|#define P8DR  0xFFFF67
DECL|macro|P9DR
mdefine_line|#define P9DR  0xFFFF68
DECL|macro|PADR
mdefine_line|#define PADR  0xFFFF69
DECL|macro|PBDR
mdefine_line|#define PBDR  0xFFFF6A
DECL|macro|PCDR
mdefine_line|#define PCDR  0xFFFF6B
DECL|macro|PDDR
mdefine_line|#define PDDR  0xFFFF6C
DECL|macro|PEDR
mdefine_line|#define PEDR  0xFFFF6D
DECL|macro|PFDR
mdefine_line|#define PFDR  0xFFFF6E
DECL|macro|PGDR
mdefine_line|#define PGDR  0xFFFF6F
DECL|macro|PHDR
mdefine_line|#define PHDR  0xFFFF72
DECL|macro|PORT1
mdefine_line|#define PORT1 0xFFFF50
DECL|macro|PORT2
mdefine_line|#define PORT2 0xFFFF51
DECL|macro|PORT3
mdefine_line|#define PORT3 0xFFFF52
DECL|macro|PORT4
mdefine_line|#define PORT4 0xFFFF53
DECL|macro|PORT5
mdefine_line|#define PORT5 0xFFFF54
DECL|macro|PORT6
mdefine_line|#define PORT6 0xFFFF55
DECL|macro|PORT7
mdefine_line|#define PORT7 0xFFFF56
DECL|macro|PORT8
mdefine_line|#define PORT8 0xFFFF57
DECL|macro|PORT9
mdefine_line|#define PORT9 0xFFFF58
DECL|macro|PORTA
mdefine_line|#define PORTA 0xFFFF59
DECL|macro|PORTB
mdefine_line|#define PORTB 0xFFFF5A
DECL|macro|PORTC
mdefine_line|#define PORTC 0xFFFF5B
DECL|macro|PORTD
mdefine_line|#define PORTD 0xFFFF5C
DECL|macro|PORTE
mdefine_line|#define PORTE 0xFFFF5D
DECL|macro|PORTF
mdefine_line|#define PORTF 0xFFFF5E
DECL|macro|PORTG
mdefine_line|#define PORTG 0xFFFF5F
DECL|macro|PORTH
mdefine_line|#define PORTH 0xFFFF70
DECL|macro|PCR
mdefine_line|#define PCR   0xFFFF46
DECL|macro|PMR
mdefine_line|#define PMR   0xFFFF47
DECL|macro|NDERH
mdefine_line|#define NDERH 0xFFFF48
DECL|macro|NDERL
mdefine_line|#define NDERL 0xFFFF49
DECL|macro|PODRH
mdefine_line|#define PODRH 0xFFFF4A
DECL|macro|PODRL
mdefine_line|#define PODRL 0xFFFF4B
DECL|macro|NDRH1
mdefine_line|#define NDRH1 0xFFFF4C
DECL|macro|NDRL1
mdefine_line|#define NDRL1 0xFFFF4D
DECL|macro|NDRH2
mdefine_line|#define NDRH2 0xFFFF4E
DECL|macro|NDRL2
mdefine_line|#define NDRL2 0xFFFF4F
DECL|macro|SMR0
mdefine_line|#define SMR0  0xFFFF78
DECL|macro|BRR0
mdefine_line|#define BRR0  0xFFFF79
DECL|macro|SCR0
mdefine_line|#define SCR0  0xFFFF7A
DECL|macro|TDR0
mdefine_line|#define TDR0  0xFFFF7B
DECL|macro|SSR0
mdefine_line|#define SSR0  0xFFFF7C
DECL|macro|RDR0
mdefine_line|#define RDR0  0xFFFF7D
DECL|macro|SCMR0
mdefine_line|#define SCMR0 0xFFFF7E
DECL|macro|SMR1
mdefine_line|#define SMR1  0xFFFF80
DECL|macro|BRR1
mdefine_line|#define BRR1  0xFFFF81
DECL|macro|SCR1
mdefine_line|#define SCR1  0xFFFF82
DECL|macro|TDR1
mdefine_line|#define TDR1  0xFFFF83
DECL|macro|SSR1
mdefine_line|#define SSR1  0xFFFF84
DECL|macro|RDR1
mdefine_line|#define RDR1  0xFFFF85
DECL|macro|SCMR1
mdefine_line|#define SCMR1 0xFFFF86
DECL|macro|SMR2
mdefine_line|#define SMR2  0xFFFF88
DECL|macro|BRR2
mdefine_line|#define BRR2  0xFFFF89
DECL|macro|SCR2
mdefine_line|#define SCR2  0xFFFF8A
DECL|macro|TDR2
mdefine_line|#define TDR2  0xFFFF8B
DECL|macro|SSR2
mdefine_line|#define SSR2  0xFFFF8C
DECL|macro|RDR2
mdefine_line|#define RDR2  0xFFFF8D
DECL|macro|SCMR2
mdefine_line|#define SCMR2 0xFFFF8E
DECL|macro|IRCR0
mdefine_line|#define IRCR0 0xFFFE1E
DECL|macro|SEMR
mdefine_line|#define SEMR  0xFFFDA8
DECL|macro|MDCR
mdefine_line|#define MDCR    0xFFFF3E
DECL|macro|SYSCR
mdefine_line|#define SYSCR   0xFFFF3D
DECL|macro|MSTPCRH
mdefine_line|#define MSTPCRH 0xFFFF40
DECL|macro|MSTPCRL
mdefine_line|#define MSTPCRL 0xFFFF41
DECL|macro|FLMCR1
mdefine_line|#define FLMCR1  0xFFFFC8
DECL|macro|FLMCR2
mdefine_line|#define FLMCR2  0xFFFFC9
DECL|macro|EBR1
mdefine_line|#define EBR1    0xFFFFCA
DECL|macro|EBR2
mdefine_line|#define EBR2    0xFFFFCB
DECL|macro|CTGARC_RAMCR
mdefine_line|#define CTGARC_RAMCR   0xFFFECE
DECL|macro|SBYCR
mdefine_line|#define SBYCR   0xFFFF3A
DECL|macro|SCKCR
mdefine_line|#define SCKCR   0xFFFF3B
DECL|macro|PLLCR
mdefine_line|#define PLLCR   0xFFFF45
DECL|macro|TSTR
mdefine_line|#define TSTR   0xFFFFC0
DECL|macro|TSNC
mdefine_line|#define TSNC   0XFFFFC1
DECL|macro|TCR0
mdefine_line|#define TCR0   0xFFFFD0
DECL|macro|TMDR0
mdefine_line|#define TMDR0  0xFFFFD1
DECL|macro|TIORH0
mdefine_line|#define TIORH0 0xFFFFD2
DECL|macro|TIORL0
mdefine_line|#define TIORL0 0xFFFFD3
DECL|macro|TIER0
mdefine_line|#define TIER0  0xFFFFD4
DECL|macro|TSR0
mdefine_line|#define TSR0   0xFFFFD5
DECL|macro|TCNT0
mdefine_line|#define TCNT0  0xFFFFD6
DECL|macro|GRA0
mdefine_line|#define GRA0   0xFFFFD8
DECL|macro|GRB0
mdefine_line|#define GRB0   0xFFFFDA
DECL|macro|GRC0
mdefine_line|#define GRC0   0xFFFFDC
DECL|macro|GRD0
mdefine_line|#define GRD0   0xFFFFDE
DECL|macro|TCR1
mdefine_line|#define TCR1   0xFFFFE0
DECL|macro|TMDR1
mdefine_line|#define TMDR1  0xFFFFE1
DECL|macro|TIORH1
mdefine_line|#define TIORH1 0xFFFFE2
DECL|macro|TIORL1
mdefine_line|#define TIORL1 0xFFFFE3
DECL|macro|TIER1
mdefine_line|#define TIER1  0xFFFFE4
DECL|macro|TSR1
mdefine_line|#define TSR1   0xFFFFE5
DECL|macro|TCNT1
mdefine_line|#define TCNT1  0xFFFFE6
DECL|macro|GRA1
mdefine_line|#define GRA1   0xFFFFE8
DECL|macro|GRB1
mdefine_line|#define GRB1   0xFFFFEA
DECL|macro|TCR2
mdefine_line|#define TCR2   0xFFFFF0
DECL|macro|TMDR2
mdefine_line|#define TMDR2  0xFFFFF1
DECL|macro|TIORH2
mdefine_line|#define TIORH2 0xFFFFF2
DECL|macro|TIORL2
mdefine_line|#define TIORL2 0xFFFFF3
DECL|macro|TIER2
mdefine_line|#define TIER2  0xFFFFF4
DECL|macro|TSR2
mdefine_line|#define TSR2   0xFFFFF5
DECL|macro|TCNT2
mdefine_line|#define TCNT2  0xFFFFF6
DECL|macro|GRA2
mdefine_line|#define GRA2   0xFFFFF8
DECL|macro|GRB2
mdefine_line|#define GRB2   0xFFFFFA
DECL|macro|TCR3
mdefine_line|#define TCR3   0xFFFE80
DECL|macro|TMDR3
mdefine_line|#define TMDR3  0xFFFE81
DECL|macro|TIORH3
mdefine_line|#define TIORH3 0xFFFE82
DECL|macro|TIORL3
mdefine_line|#define TIORL3 0xFFFE83
DECL|macro|TIER3
mdefine_line|#define TIER3  0xFFFE84
DECL|macro|TSR3
mdefine_line|#define TSR3   0xFFFE85
DECL|macro|TCNT3
mdefine_line|#define TCNT3  0xFFFE86
DECL|macro|GRA3
mdefine_line|#define GRA3   0xFFFE88
DECL|macro|GRB3
mdefine_line|#define GRB3   0xFFFE8A
DECL|macro|GRC3
mdefine_line|#define GRC3   0xFFFE8C
DECL|macro|GRD3
mdefine_line|#define GRD3   0xFFFE8E
DECL|macro|TCR4
mdefine_line|#define TCR4   0xFFFE90
DECL|macro|TMDR4
mdefine_line|#define TMDR4  0xFFFE91
DECL|macro|TIORH4
mdefine_line|#define TIORH4 0xFFFE92
DECL|macro|TIORL4
mdefine_line|#define TIORL4 0xFFFE93
DECL|macro|TIER4
mdefine_line|#define TIER4  0xFFFE94
DECL|macro|TSR4
mdefine_line|#define TSR4   0xFFFE95
DECL|macro|TCNT4
mdefine_line|#define TCNT4  0xFFFE96
DECL|macro|GRA4
mdefine_line|#define GRA4   0xFFFE98
DECL|macro|GRB4
mdefine_line|#define GRB4   0xFFFE9A
DECL|macro|TCR5
mdefine_line|#define TCR5   0xFFFEA0
DECL|macro|TMDR5
mdefine_line|#define TMDR5  0xFFFEA1
DECL|macro|TIORH5
mdefine_line|#define TIORH5 0xFFFEA2
DECL|macro|TIORL5
mdefine_line|#define TIORL5 0xFFFEA3
DECL|macro|TIER5
mdefine_line|#define TIER5  0xFFFEA4
DECL|macro|TSR5
mdefine_line|#define TSR5   0xFFFEA5
DECL|macro|TCNT5
mdefine_line|#define TCNT5  0xFFFEA6
DECL|macro|GRA5
mdefine_line|#define GRA5   0xFFFEA8
DECL|macro|GRB5
mdefine_line|#define GRB5   0xFFFEAA
DECL|macro|_8TCR0
mdefine_line|#define _8TCR0   0xFFFFB0
DECL|macro|_8TCR1
mdefine_line|#define _8TCR1   0xFFFFB1
DECL|macro|_8TCSR0
mdefine_line|#define _8TCSR0  0xFFFFB2
DECL|macro|_8TCSR1
mdefine_line|#define _8TCSR1  0xFFFFB3
DECL|macro|_8TCORA0
mdefine_line|#define _8TCORA0 0xFFFFB4
DECL|macro|_8TCORA1
mdefine_line|#define _8TCORA1 0xFFFFB5
DECL|macro|_8TCORB0
mdefine_line|#define _8TCORB0 0xFFFFB6
DECL|macro|_8TCORB1
mdefine_line|#define _8TCORB1 0xFFFFB7
DECL|macro|_8TCNT0
mdefine_line|#define _8TCNT0  0xFFFFB8
DECL|macro|_8TCNT1
mdefine_line|#define _8TCNT1  0xFFFFB9
DECL|macro|TCSR
mdefine_line|#define TCSR    0xFFFFBC
DECL|macro|TCNT
mdefine_line|#define TCNT    0xFFFFBD
DECL|macro|RSTCSRW
mdefine_line|#define RSTCSRW 0xFFFFBE
DECL|macro|RSTCSRR
mdefine_line|#define RSTCSRR 0xFFFFBF
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __REGS_H8S267x__ */
eof

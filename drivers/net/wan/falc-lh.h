multiline_comment|/*&n; *&t;Defines for comx-hw-slicecom.c - FALC-LH specific&n; *&n; *&t;Author:&t;&t;Bartok Istvan &lt;bartoki@itc.hu&gt;&n; *&t;Last modified:&t;Mon Feb  7 20:00:38 CET 2000&n; *&n; *&t;:set tabstop=6&n; */
multiline_comment|/*&n; *&t;Control register offsets on the LBI (page 90)&n; *&t;use it like:&n; *&t;lbi[ MODE ] = 0x34;&n; */
DECL|macro|MODE
mdefine_line|#define MODE&t;0x03
DECL|macro|IPC
mdefine_line|#define IPC&t;&t;0x08
DECL|macro|IMR0
mdefine_line|#define IMR0&t;0x14&t;/* Interrupt Mask Register 0&t;*/
DECL|macro|IMR1
mdefine_line|#define IMR1&t;0x15
DECL|macro|IMR2
mdefine_line|#define IMR2&t;0x16
DECL|macro|IMR3
mdefine_line|#define IMR3&t;0x17
DECL|macro|IMR4
mdefine_line|#define IMR4&t;0x18
DECL|macro|IMR5
mdefine_line|#define IMR5&t;0x19
DECL|macro|FMR0
mdefine_line|#define FMR0&t;0x1a&t;/* Framer Mode Register 0&t;*/
DECL|macro|FMR1
mdefine_line|#define FMR1&t;0x1b
DECL|macro|FMR2
mdefine_line|#define FMR2&t;0x1c
DECL|macro|XSW
mdefine_line|#define XSW&t;&t;0x1e
DECL|macro|XSP
mdefine_line|#define XSP&t;&t;0x1f
DECL|macro|XC0
mdefine_line|#define XC0&t;&t;0x20
DECL|macro|XC1
mdefine_line|#define XC1&t;&t;0x21
DECL|macro|RC0
mdefine_line|#define RC0&t;&t;0x22
DECL|macro|RC1
mdefine_line|#define RC1&t;&t;0x23
DECL|macro|XPM0
mdefine_line|#define XPM0&t;0x24
DECL|macro|XPM1
mdefine_line|#define XPM1&t;0x25
DECL|macro|XPM2
mdefine_line|#define XPM2&t;0x26
DECL|macro|TSWM
mdefine_line|#define TSWM&t;0x27
DECL|macro|IDLE
mdefine_line|#define IDLE&t;0x29&t;/* Idle Code&t;*/
DECL|macro|LIM0
mdefine_line|#define LIM0&t;0x34
DECL|macro|LIM1
mdefine_line|#define LIM1&t;0x35
DECL|macro|PCD
mdefine_line|#define PCD&t;&t;0x36
DECL|macro|PCR
mdefine_line|#define PCR&t;&t;0x37
DECL|macro|LIM2
mdefine_line|#define LIM2&t;0x38
multiline_comment|/*&n; *&t;Status registers on the LBI (page 134)&n; *&t;these are read-only, use it like:&n; *&t;if( lbi[ FRS0 ] ) ...&n; */
DECL|macro|FRS0
mdefine_line|#define FRS0&t;0x4c&t;/* Framer Receive Status register 0&t;*/
DECL|macro|FRS1
mdefine_line|#define FRS1&t;0x4d&t;/* Framer Receive Status register 1&t;*/
DECL|macro|FECL
mdefine_line|#define FECL&t;0x50&t;/* Framing Error Counter low byte&t;*/ /* Counts FAS word receive errors&t;&t;*/
DECL|macro|FECH
mdefine_line|#define FECH&t;0x51&t;/*                       high byte&t;*/
DECL|macro|CVCL
mdefine_line|#define CVCL&t;0x52&t;/* Code Violation Counter low byte&t;*/ /* Counts bipolar and HDB3 code violations&t;*/
DECL|macro|CVCH
mdefine_line|#define CVCH&t;0x53&t;/*                        high byte&t;*/
DECL|macro|CEC1L
mdefine_line|#define CEC1L&t;0x54&t;/* CRC4 Error Counter 1 low byte&t;*/ /* Counts CRC4 errors in the incoming stream&t;*/
DECL|macro|CEC1H
mdefine_line|#define CEC1H&t;0x55&t;/*                      high byte&t;*/
DECL|macro|EBCL
mdefine_line|#define EBCL&t;0x56&t;/* E Bit error Counter low byte&t;*/ /* E-bits: the remote end sends them, when&t;*/
DECL|macro|EBCH
mdefine_line|#define EBCH&t;0x57&t;/*                     high byte&t;*/ /* it detected a CRC4-error&t;&t;&t;*/
DECL|macro|ISR0
mdefine_line|#define ISR0&t;0x68&t;/* Interrupt Status Register 0&t;*/
DECL|macro|ISR1
mdefine_line|#define ISR1&t;0x69&t;/* Interrupt Status Register 1&t;*/
DECL|macro|ISR2
mdefine_line|#define ISR2&t;0x6a&t;/* Interrupt Status Register 2&t;*/
DECL|macro|ISR3
mdefine_line|#define ISR3&t;0x6b&t;/* Interrupt Status Register 3&t;*/
DECL|macro|ISR5
mdefine_line|#define ISR5&t;0x6c&t;/* Interrupt Status Register 5&t;*/
DECL|macro|GIS
mdefine_line|#define GIS&t;0x6e&t;/* Global Interrupt Status Register&t;*/
DECL|macro|VSTR
mdefine_line|#define VSTR&t;0x6f&t;/* version information */
multiline_comment|/*&n; *&t;Bit fields&n; */
DECL|macro|FRS0_LOS
mdefine_line|#define FRS0_LOS&t;&t;(1 &lt;&lt; 7)
DECL|macro|FRS0_AIS
mdefine_line|#define FRS0_AIS&t;&t;(1 &lt;&lt; 6)
DECL|macro|FRS0_LFA
mdefine_line|#define FRS0_LFA&t;&t;(1 &lt;&lt; 5)
DECL|macro|FRS0_RRA
mdefine_line|#define FRS0_RRA&t;&t;(1 &lt;&lt; 4)
DECL|macro|FRS0_AUXP
mdefine_line|#define FRS0_AUXP&t;&t;(1 &lt;&lt; 3)
DECL|macro|FRS0_NMF
mdefine_line|#define FRS0_NMF&t;&t;(1 &lt;&lt; 2)
DECL|macro|FRS0_LMFA
mdefine_line|#define FRS0_LMFA&t;&t;(1 &lt;&lt; 1)
DECL|macro|FRS1_XLS
mdefine_line|#define FRS1_XLS&t;&t;(1 &lt;&lt; 1)
DECL|macro|FRS1_XLO
mdefine_line|#define FRS1_XLO&t;&t;(1)
DECL|macro|ISR2_FAR
mdefine_line|#define ISR2_FAR&t;&t;(1 &lt;&lt; 7)
DECL|macro|ISR2_LFA
mdefine_line|#define ISR2_LFA&t;&t;(1 &lt;&lt; 6)
DECL|macro|ISR2_MFAR
mdefine_line|#define ISR2_MFAR&t;&t;(1 &lt;&lt; 5)
DECL|macro|ISR2_T400MS
mdefine_line|#define ISR2_T400MS&t;(1 &lt;&lt; 4)
DECL|macro|ISR2_AIS
mdefine_line|#define ISR2_AIS&t;&t;(1 &lt;&lt; 3)
DECL|macro|ISR2_LOS
mdefine_line|#define ISR2_LOS&t;&t;(1 &lt;&lt; 2)
DECL|macro|ISR2_RAR
mdefine_line|#define ISR2_RAR&t;&t;(1 &lt;&lt; 1)
DECL|macro|ISR2_RA
mdefine_line|#define ISR2_RA&t;&t;(1)
DECL|macro|ISR3_ES
mdefine_line|#define ISR3_ES&t;&t;(1 &lt;&lt; 7)
DECL|macro|ISR3_SEC
mdefine_line|#define ISR3_SEC&t;&t;(1 &lt;&lt; 6)
DECL|macro|ISR3_LMFA16
mdefine_line|#define ISR3_LMFA16&t;(1 &lt;&lt; 5)
DECL|macro|ISR3_AIS16
mdefine_line|#define ISR3_AIS16&t;(1 &lt;&lt; 4)
DECL|macro|ISR3_RA16
mdefine_line|#define ISR3_RA16&t;&t;(1 &lt;&lt; 3)
DECL|macro|ISR3_API
mdefine_line|#define ISR3_API&t;&t;(1 &lt;&lt; 2)
DECL|macro|ISR3_RSN
mdefine_line|#define ISR3_RSN&t;&t;(1 &lt;&lt; 1)
DECL|macro|ISR3_RSP
mdefine_line|#define ISR3_RSP&t;&t;(1)
DECL|macro|ISR5_XSP
mdefine_line|#define ISR5_XSP&t;&t;(1 &lt;&lt; 7)
DECL|macro|ISR5_XSN
mdefine_line|#define ISR5_XSN&t;&t;(1 &lt;&lt; 6)
eof

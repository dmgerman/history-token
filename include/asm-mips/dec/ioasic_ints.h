multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Definitions for the interrupt related bits in the JUNKIO Asic&n; * interrupt status register (and the interrupt mask register, of course)&n; *&n; * Created with Information from:&n; *&n; * &quot;DEC 3000 300/400/500/600/700/800/900 AXP Models System Programmer&squot;s Manual&quot;&n; *&n; * and the Mach Sources&n; */
multiline_comment|/* &n; * the upper 16 bits are common to all JUNKIO machines&n; * (except the FLOPPY and ISDN bits, which are Maxine sepcific)&n; */
DECL|macro|SCC0_TRANS_PAGEEND
mdefine_line|#define SCC0_TRANS_PAGEEND&t;0x80000000&t;/* Serial DMA Errors&t;*/
DECL|macro|SCC0_TRANS_MEMRDERR
mdefine_line|#define SCC0_TRANS_MEMRDERR&t;0x40000000&t;/* see below&t;&t;*/
DECL|macro|SCC0_RECV_HALFPAGE
mdefine_line|#define SCC0_RECV_HALFPAGE&t;0x20000000
DECL|macro|SCC0_RECV_PAGOVRRUN
mdefine_line|#define&t;SCC0_RECV_PAGOVRRUN&t;0x10000000
DECL|macro|SCC1_TRANS_PAGEEND
mdefine_line|#define SCC1_TRANS_PAGEEND&t;0x08000000&t;/* end of page reached&t;*/
DECL|macro|SCC1_TRANS_MEMRDERR
mdefine_line|#define SCC1_TRANS_MEMRDERR&t;0x04000000&t;/* SCC1 DMA memory err&t;*/
DECL|macro|SCC1_RECV_HALFPAGE
mdefine_line|#define SCC1_RECV_HALFPAGE&t;0x02000000&t;/* SCC1 half page&t;*/
DECL|macro|SCC1_RECV_PAGOVRRUN
mdefine_line|#define&t;SCC1_RECV_PAGOVRRUN&t;0x01000000&t;/* SCC1 receive overrun&t;*/
DECL|macro|FLOPPY_DMA_ERROR
mdefine_line|#define FLOPPY_DMA_ERROR&t;0x00800000&t;/* FDI DMA error&t;*/
DECL|macro|ISDN_TRANS_PTR_LOADED
mdefine_line|#define&t;ISDN_TRANS_PTR_LOADED&t;0x00400000&t;/* xmitbuf ptr loaded&t;*/
DECL|macro|ISDN_RECV_PTR_LOADED
mdefine_line|#define ISDN_RECV_PTR_LOADED&t;0x00200000&t;/* rcvbuf ptr loaded&t;*/
DECL|macro|ISDN_DMA_MEMRDERR
mdefine_line|#define ISDN_DMA_MEMRDERR&t;0x00100000&t;/* read or ovrrun error&t;*/
DECL|macro|SCSI_PTR_LOADED
mdefine_line|#define SCSI_PTR_LOADED&t;&t;0x00080000
DECL|macro|SCSI_PAGOVRRUN
mdefine_line|#define SCSI_PAGOVRRUN&t;&t;0x00040000&t;/* page overrun? */
DECL|macro|SCSI_DMA_MEMRDERR
mdefine_line|#define SCSI_DMA_MEMRDERR&t;0x00020000
DECL|macro|LANCE_DMA_MEMRDERR
mdefine_line|#define LANCE_DMA_MEMRDERR&t;0x00010000
multiline_comment|/*&n; * the lower 16 bits are system specific&n; */
multiline_comment|/*&n; * The following three seem to be in common&n; */
DECL|macro|SCSI_CHIP
mdefine_line|#define SCSI_CHIP&t;&t;0x00000200
DECL|macro|LANCE_CHIP
mdefine_line|#define LANCE_CHIP&t;&t;0x00000100
DECL|macro|SCC1_CHIP
mdefine_line|#define SCC1_CHIP&t;&t;0x00000080&t;/* NOT on maxine&t;*/
DECL|macro|SCC0_CHIP
mdefine_line|#define SCC0_CHIP&t;&t;0x00000040
multiline_comment|/*&n; * The rest is different&n; */
multiline_comment|/* kmin aka 3min aka kn02ba aka DS5000_1xx */
DECL|macro|KMIN_TIMEOUT
mdefine_line|#define KMIN_TIMEOUT&t;&t;0x00001000&t;/* CPU IO-Write Timeout&t;*/
DECL|macro|KMIN_CLOCK
mdefine_line|#define KMIN_CLOCK&t;&t;0x00000020
DECL|macro|KMIN_SCSI_FIFO
mdefine_line|#define KMIN_SCSI_FIFO&t;&t;0x00000004&t;/* SCSI Data Ready&t;*/
multiline_comment|/* kn02ca aka maxine */
DECL|macro|MAXINE_FLOPPY
mdefine_line|#define MAXINE_FLOPPY&t;&t;0x00008000&t;/* FDI Interrupt        */
DECL|macro|MAXINE_TC0
mdefine_line|#define MAXINE_TC0&t;&t;0x00001000&t;/* TC Option 0      &t;*/
DECL|macro|MAXINE_ISDN
mdefine_line|#define MAXINE_ISDN&t;&t;0x00000800&t;/* ISDN&t;Chip&t;&t;*/
DECL|macro|MAXINE_FLOPPY_HDS
mdefine_line|#define MAXINE_FLOPPY_HDS&t;0x00000080&t;/* Floppy Status      &t;*/
DECL|macro|MAXINE_TC1
mdefine_line|#define MAXINE_TC1&t;&t;0x00000020&t;/* TC Option 1&t;&t;*/
DECL|macro|MAXINE_FLOPPY_XDS
mdefine_line|#define MAXINE_FLOPPY_XDS&t;0x00000010&t;/* Floppy Status      &t;*/
DECL|macro|MAXINE_VINT
mdefine_line|#define MAXINE_VINT&t;&t;0x00000008&t;/* Video Frame&t;&t;*/
DECL|macro|MAXINE_N_VINT
mdefine_line|#define MAXINE_N_VINT&t;&t;0x00000004&t;/* Not Video frame&t;*/
DECL|macro|MAXINE_DTOP_TRANS
mdefine_line|#define MAXINE_DTOP_TRANS&t;0x00000002&t;/* DTI Xmit-Rdy&t;&t;*/
DECL|macro|MAXINE_DTOP_RECV
mdefine_line|#define MAXINE_DTOP_RECV&t;0x00000001&t;/* DTI Recv-Available&t;*/
multiline_comment|/* kn03 aka 3max+ aka DS5000_2x0 */
DECL|macro|KN03_TC2
mdefine_line|#define KN03_TC2&t;&t;0x00002000
DECL|macro|KN03_TC1
mdefine_line|#define KN03_TC1&t;&t;0x00001000
DECL|macro|KN03_TC0
mdefine_line|#define KN03_TC0&t;&t;0x00000800
DECL|macro|KN03_SCSI_FIFO
mdefine_line|#define KN03_SCSI_FIFO&t;&t;0x00000004&t;/* ??? Info from Mach&t;*/
multiline_comment|/*&n; * Now form groups, i.e. all serial interrupts, all SCSI interrupts and so on. &n; */
DECL|macro|SERIAL_INTS
mdefine_line|#define SERIAL_INTS&t;(SCC0_TRANS_PAGEEND | SCC0_TRANS_MEMRDERR | &bslash;&n;&t;&t;&t;SCC0_RECV_HALFPAGE | SCC0_RECV_PAGOVRRUN | &bslash;&n;&t;&t;&t;SCC1_TRANS_PAGEEND | SCC1_TRANS_MEMRDERR | &bslash;&n;&t;&t;&t;SCC1_RECV_HALFPAGE | SCC1_RECV_PAGOVRRUN | &bslash;&n;&t;&t;&t;SCC1_CHIP | SCC0_CHIP)
DECL|macro|XINE_SERIAL_INTS
mdefine_line|#define XINE_SERIAL_INTS&t;(SCC0_TRANS_PAGEEND | SCC0_TRANS_MEMRDERR | &bslash;&n;&t;&t;&t;SCC0_RECV_HALFPAGE | SCC0_RECV_PAGOVRRUN | &bslash;&n;&t;&t;&t;SCC0_CHIP)
DECL|macro|SCSI_DMA_INTS
mdefine_line|#define SCSI_DMA_INTS&t;(/* SCSI_PTR_LOADED | */ SCSI_PAGOVRRUN | &bslash;&n;&t;&t;&t;SCSI_DMA_MEMRDERR)
DECL|macro|KMIN_SCSI_INTS
mdefine_line|#define KMIN_SCSI_INTS&t;(SCSI_PTR_LOADED | SCSI_PAGOVRRUN | &bslash;&n;&t;&t;&t;SCSI_DMA_MEMRDERR | SCSI_CHIP | KMIN_SCSI_FIFO)
DECL|macro|LANCE_INTS
mdefine_line|#define LANCE_INTS&t;(LANCE_DMA_MEMRDERR | LANCE_CHIP)
multiline_comment|/*&n; * For future use ...&n; */
DECL|macro|XINE_FLOPPY_INTS
mdefine_line|#define XINE_FLOPPY_INTS (MAXINE_FLOPPY | MAXINE_FLOPPY_HDS | &bslash;&n;&t;&t;&t;FLOPPY_DMA_ERROR | MAXINE_FLOPPY_XDS)
DECL|macro|XINE_ISDN_INTS
mdefine_line|#define XINE_ISDN_INTS&t;(MAXINE_ISDN | ISDN_TRANS_PTR_LOADED | &bslash;&n;&t;&t;&t;ISDN_RECV_PTR_LOADED | ISDN_DMA_MEMRDERR)
DECL|macro|XINE_DTOP_INTS
mdefine_line|#define XINE_DTOP_INTS&t;(MAXINE_DTOP_TRANS | DTOP_RECV | &bslash;&n;&t;&t;&t;ISDN_TRANS_PTR_LOADED | ISDN_RECV_PTR_LOADED | &bslash;&n;&t;&t;&t;ISDN_DMA_MEMRDERR)
eof

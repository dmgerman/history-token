multiline_comment|/* $Id: fore200e.h,v 1.4 2000/04/14 10:10:34 davem Exp $ */
macro_line|#ifndef _FORE200E_H
DECL|macro|_FORE200E_H
mdefine_line|#define _FORE200E_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* rx buffer sizes */
DECL|macro|SMALL_BUFFER_SIZE
mdefine_line|#define SMALL_BUFFER_SIZE    384     /* size of small buffers (multiple of 48 (PCA) and 64 (SBA) bytes) */
DECL|macro|LARGE_BUFFER_SIZE
mdefine_line|#define LARGE_BUFFER_SIZE    4032    /* size of large buffers (multiple of 48 (PCA) and 64 (SBA) bytes) */
DECL|macro|RBD_BLK_SIZE
mdefine_line|#define RBD_BLK_SIZE&t;     32      /* nbr of supplied rx buffers per rbd */
DECL|macro|MAX_PDU_SIZE
mdefine_line|#define MAX_PDU_SIZE&t;     65535   /* maximum PDU size supported by AALs */
DECL|macro|BUFFER_S1_SIZE
mdefine_line|#define BUFFER_S1_SIZE       SMALL_BUFFER_SIZE    /* size of small buffers, scheme 1 */
DECL|macro|BUFFER_L1_SIZE
mdefine_line|#define BUFFER_L1_SIZE       LARGE_BUFFER_SIZE    /* size of large buffers, scheme 1 */
DECL|macro|BUFFER_S2_SIZE
mdefine_line|#define BUFFER_S2_SIZE       SMALL_BUFFER_SIZE    /* size of small buffers, scheme 2 */
DECL|macro|BUFFER_L2_SIZE
mdefine_line|#define BUFFER_L2_SIZE       LARGE_BUFFER_SIZE    /* size of large buffers, scheme 2 */
DECL|macro|BUFFER_S1_NBR
mdefine_line|#define BUFFER_S1_NBR        (RBD_BLK_SIZE * 2)
DECL|macro|BUFFER_L1_NBR
mdefine_line|#define BUFFER_L1_NBR        (RBD_BLK_SIZE * 2)
DECL|macro|BUFFER_S2_NBR
mdefine_line|#define BUFFER_S2_NBR        (RBD_BLK_SIZE * 2)
DECL|macro|BUFFER_L2_NBR
mdefine_line|#define BUFFER_L2_NBR        (RBD_BLK_SIZE * 2)
DECL|macro|QUEUE_SIZE_CMD
mdefine_line|#define QUEUE_SIZE_CMD       16&t;     /* command queue capacity       */
DECL|macro|QUEUE_SIZE_RX
mdefine_line|#define QUEUE_SIZE_RX&t;     64&t;     /* receive queue capacity       */
DECL|macro|QUEUE_SIZE_TX
mdefine_line|#define QUEUE_SIZE_TX&t;     256     /* transmit queue capacity      */
DECL|macro|QUEUE_SIZE_BS
mdefine_line|#define QUEUE_SIZE_BS        16&t;     /* buffer supply queue capacity */
DECL|macro|NBR_CONNECT
mdefine_line|#define NBR_CONNECT          1024    /* number of ATM connections     */
DECL|macro|TSD_FIXED
mdefine_line|#define TSD_FIXED            2
DECL|macro|TSD_EXTENSION
mdefine_line|#define TSD_EXTENSION        0
DECL|macro|TSD_NBR
mdefine_line|#define TSD_NBR              (TSD_FIXED + TSD_EXTENSION)
multiline_comment|/* the cp starts putting a received PDU into one *small* buffer,&n;   then it uses a number of *large* buffers for the trailing data. &n;   we compute here the total number of receive segment descriptors &n;   required to hold the largest possible PDU */
DECL|macro|RSD_REQUIRED
mdefine_line|#define RSD_REQUIRED  (((MAX_PDU_SIZE - SMALL_BUFFER_SIZE + LARGE_BUFFER_SIZE) / LARGE_BUFFER_SIZE) + 1)
DECL|macro|RSD_FIXED
mdefine_line|#define RSD_FIXED     3
multiline_comment|/* RSD_REQUIRED receive segment descriptors are enough to describe a max-sized PDU,&n;   but we have to keep the size of the receive PDU descriptor multiple of 32 bytes,&n;   so we add one extra RSD to RSD_EXTENSION &n;   (WARNING: THIS MAY CHANGE IF BUFFER SIZES ARE MODIFIED) */
DECL|macro|RSD_EXTENSION
mdefine_line|#define RSD_EXTENSION  ((RSD_REQUIRED - RSD_FIXED) + 1)
DECL|macro|RSD_NBR
mdefine_line|#define RSD_NBR         (RSD_FIXED + RSD_EXTENSION)
DECL|macro|FORE200E_DEV
mdefine_line|#define FORE200E_DEV(d)          ((struct fore200e*)((d)-&gt;dev_data))
DECL|macro|FORE200E_VCC
mdefine_line|#define FORE200E_VCC(d)          ((struct fore200e_vcc*)((d)-&gt;dev_data))
multiline_comment|/* bitfields endian games */
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|macro|BITFIELD2
mdefine_line|#define BITFIELD2(b1, b2)                    b1; b2;
DECL|macro|BITFIELD3
mdefine_line|#define BITFIELD3(b1, b2, b3)                b1; b2; b3;
DECL|macro|BITFIELD4
mdefine_line|#define BITFIELD4(b1, b2, b3, b4)            b1; b2; b3; b4;
DECL|macro|BITFIELD5
mdefine_line|#define BITFIELD5(b1, b2, b3, b4, b5)        b1; b2; b3; b4; b5;
DECL|macro|BITFIELD6
mdefine_line|#define BITFIELD6(b1, b2, b3, b4, b5, b6)    b1; b2; b3; b4; b5; b6;
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
DECL|macro|BITFIELD2
mdefine_line|#define BITFIELD2(b1, b2)                                    b2; b1;
DECL|macro|BITFIELD3
mdefine_line|#define BITFIELD3(b1, b2, b3)                            b3; b2; b1;
DECL|macro|BITFIELD4
mdefine_line|#define BITFIELD4(b1, b2, b3, b4)                    b4; b3; b2; b1;
DECL|macro|BITFIELD5
mdefine_line|#define BITFIELD5(b1, b2, b3, b4, b5)            b5; b4; b3; b2; b1;
DECL|macro|BITFIELD6
mdefine_line|#define BITFIELD6(b1, b2, b3, b4, b5, b6)    b6; b5; b4; b3; b2; b1;
macro_line|#else
macro_line|#error unknown bitfield endianess
macro_line|#endif
multiline_comment|/* ATM cell header (minus HEC byte) */
DECL|struct|atm_header
r_typedef
r_struct
id|atm_header
(brace
id|BITFIELD5
c_func
(paren
id|u32
id|clp
suffix:colon
l_int|1
comma
multiline_comment|/* cell loss priority         */
id|u32
id|plt
suffix:colon
l_int|3
comma
multiline_comment|/* payload type               */
id|u32
id|vci
suffix:colon
l_int|16
comma
multiline_comment|/* virtual channel identifier */
id|u32
id|vpi
suffix:colon
l_int|8
comma
multiline_comment|/* virtual path identifier    */
id|u32
id|gfc
suffix:colon
l_int|4
multiline_comment|/* generic flow control       */
)paren
DECL|typedef|atm_header_t
)brace
id|atm_header_t
suffix:semicolon
multiline_comment|/* ATM adaptation layer id */
DECL|enum|fore200e_aal
r_typedef
r_enum
id|fore200e_aal
(brace
DECL|enumerator|FORE200E_AAL0
id|FORE200E_AAL0
op_assign
l_int|0
comma
DECL|enumerator|FORE200E_AAL34
id|FORE200E_AAL34
op_assign
l_int|4
comma
DECL|enumerator|FORE200E_AAL5
id|FORE200E_AAL5
op_assign
l_int|5
comma
DECL|typedef|fore200e_aal_t
)brace
id|fore200e_aal_t
suffix:semicolon
multiline_comment|/* transmit PDU descriptor specification */
DECL|struct|tpd_spec
r_typedef
r_struct
id|tpd_spec
(brace
id|BITFIELD4
c_func
(paren
id|u32
id|length
suffix:colon
l_int|16
comma
multiline_comment|/* total PDU length            */
id|u32
id|nseg
suffix:colon
l_int|8
comma
multiline_comment|/* number of transmit segments */
r_enum
id|fore200e_aal
id|aal
suffix:colon
l_int|4
comma
multiline_comment|/* adaptation layer            */
id|u32
id|intr
suffix:colon
l_int|4
multiline_comment|/* interrupt requested         */
)paren
DECL|typedef|tpd_spec_t
)brace
id|tpd_spec_t
suffix:semicolon
multiline_comment|/* transmit PDU rate control */
DECL|struct|tpd_rate
r_typedef
r_struct
id|tpd_rate
(brace
id|BITFIELD2
c_func
(paren
id|u32
id|idle_cells
suffix:colon
l_int|16
comma
multiline_comment|/* number of idle cells to insert   */
id|u32
id|data_cells
suffix:colon
l_int|16
multiline_comment|/* number of data cells to transmit */
)paren
DECL|typedef|tpd_rate_t
)brace
id|tpd_rate_t
suffix:semicolon
multiline_comment|/* transmit segment descriptor */
DECL|struct|tsd
r_typedef
r_struct
id|tsd
(brace
DECL|member|buffer
id|u32
id|buffer
suffix:semicolon
multiline_comment|/* transmit buffer DMA address */
DECL|member|length
id|u32
id|length
suffix:semicolon
multiline_comment|/* number of bytes in buffer   */
DECL|typedef|tsd_t
)brace
id|tsd_t
suffix:semicolon
multiline_comment|/* transmit PDU descriptor */
DECL|struct|tpd
r_typedef
r_struct
id|tpd
(brace
DECL|member|atm_header
r_struct
id|atm_header
id|atm_header
suffix:semicolon
multiline_comment|/* ATM header minus HEC byte    */
DECL|member|spec
r_struct
id|tpd_spec
id|spec
suffix:semicolon
multiline_comment|/* tpd specification            */
DECL|member|rate
r_struct
id|tpd_rate
id|rate
suffix:semicolon
multiline_comment|/* tpd rate control             */
DECL|member|pad
id|u32
id|pad
suffix:semicolon
multiline_comment|/* reserved                     */
DECL|member|tsd
r_struct
id|tsd
id|tsd
(braket
id|TSD_NBR
)braket
suffix:semicolon
multiline_comment|/* transmit segment descriptors */
DECL|typedef|tpd_t
)brace
id|tpd_t
suffix:semicolon
multiline_comment|/* receive segment descriptor */
DECL|struct|rsd
r_typedef
r_struct
id|rsd
(brace
DECL|member|handle
id|u32
id|handle
suffix:semicolon
multiline_comment|/* host supplied receive buffer handle */
DECL|member|length
id|u32
id|length
suffix:semicolon
multiline_comment|/* number of bytes in buffer           */
DECL|typedef|rsd_t
)brace
id|rsd_t
suffix:semicolon
multiline_comment|/* receive PDU descriptor */
DECL|struct|rpd
r_typedef
r_struct
id|rpd
(brace
DECL|member|atm_header
r_struct
id|atm_header
id|atm_header
suffix:semicolon
multiline_comment|/* ATM header minus HEC byte   */
DECL|member|nseg
id|u32
id|nseg
suffix:semicolon
multiline_comment|/* number of receive segments  */
DECL|member|rsd
r_struct
id|rsd
id|rsd
(braket
id|RSD_NBR
)braket
suffix:semicolon
multiline_comment|/* receive segment descriptors */
DECL|typedef|rpd_t
)brace
id|rpd_t
suffix:semicolon
multiline_comment|/* buffer scheme */
DECL|enum|buffer_scheme
r_typedef
r_enum
id|buffer_scheme
(brace
DECL|enumerator|BUFFER_SCHEME_ONE
id|BUFFER_SCHEME_ONE
comma
DECL|enumerator|BUFFER_SCHEME_TWO
id|BUFFER_SCHEME_TWO
comma
DECL|enumerator|BUFFER_SCHEME_NBR
id|BUFFER_SCHEME_NBR
multiline_comment|/* always last */
DECL|typedef|buffer_scheme_t
)brace
id|buffer_scheme_t
suffix:semicolon
multiline_comment|/* buffer magnitude */
DECL|enum|buffer_magn
r_typedef
r_enum
id|buffer_magn
(brace
DECL|enumerator|BUFFER_MAGN_SMALL
id|BUFFER_MAGN_SMALL
comma
DECL|enumerator|BUFFER_MAGN_LARGE
id|BUFFER_MAGN_LARGE
comma
DECL|enumerator|BUFFER_MAGN_NBR
id|BUFFER_MAGN_NBR
multiline_comment|/* always last */
DECL|typedef|buffer_magn_t
)brace
id|buffer_magn_t
suffix:semicolon
multiline_comment|/* receive buffer descriptor */
DECL|struct|rbd
r_typedef
r_struct
id|rbd
(brace
DECL|member|handle
id|u32
id|handle
suffix:semicolon
multiline_comment|/* host supplied handle            */
DECL|member|buffer_haddr
id|u32
id|buffer_haddr
suffix:semicolon
multiline_comment|/* host DMA address of host buffer */
DECL|typedef|rbd_t
)brace
id|rbd_t
suffix:semicolon
multiline_comment|/* receive buffer descriptor block */
DECL|struct|rbd_block
r_typedef
r_struct
id|rbd_block
(brace
DECL|member|rbd
r_struct
id|rbd
id|rbd
(braket
id|RBD_BLK_SIZE
)braket
suffix:semicolon
multiline_comment|/* receive buffer descriptor */
DECL|typedef|rbd_block_t
)brace
id|rbd_block_t
suffix:semicolon
multiline_comment|/* tpd DMA address */
DECL|struct|tpd_haddr
r_typedef
r_struct
id|tpd_haddr
(brace
id|BITFIELD3
c_func
(paren
id|u32
id|size
suffix:colon
l_int|4
comma
multiline_comment|/* tpd size expressed in 32 byte blocks     */
id|u32
id|pad
suffix:colon
l_int|1
comma
multiline_comment|/* reserved                                 */
id|u32
id|haddr
suffix:colon
l_int|27
multiline_comment|/* tpd DMA addr aligned on 32 byte boundary */
)paren
DECL|typedef|tpd_haddr_t
)brace
id|tpd_haddr_t
suffix:semicolon
multiline_comment|/* cp resident transmit queue entry */
DECL|struct|cp_txq_entry
r_typedef
r_struct
id|cp_txq_entry
(brace
DECL|member|tpd_haddr
r_struct
id|tpd_haddr
id|tpd_haddr
suffix:semicolon
multiline_comment|/* host DMA address of tpd                */
DECL|member|status_haddr
id|u32
id|status_haddr
suffix:semicolon
multiline_comment|/* host DMA address of completion status  */
DECL|typedef|cp_txq_entry_t
)brace
id|cp_txq_entry_t
suffix:semicolon
multiline_comment|/* cp resident receive queue entry */
DECL|struct|cp_rxq_entry
r_typedef
r_struct
id|cp_rxq_entry
(brace
DECL|member|rpd_haddr
id|u32
id|rpd_haddr
suffix:semicolon
multiline_comment|/* host DMA address of rpd                */
DECL|member|status_haddr
id|u32
id|status_haddr
suffix:semicolon
multiline_comment|/* host DMA address of completion status  */
DECL|typedef|cp_rxq_entry_t
)brace
id|cp_rxq_entry_t
suffix:semicolon
multiline_comment|/* cp resident buffer supply queue entry */
DECL|struct|cp_bsq_entry
r_typedef
r_struct
id|cp_bsq_entry
(brace
DECL|member|rbd_block_haddr
id|u32
id|rbd_block_haddr
suffix:semicolon
multiline_comment|/* host DMA address of rbd block          */
DECL|member|status_haddr
id|u32
id|status_haddr
suffix:semicolon
multiline_comment|/* host DMA address of completion status  */
DECL|typedef|cp_bsq_entry_t
)brace
id|cp_bsq_entry_t
suffix:semicolon
multiline_comment|/* completion status */
DECL|enum|status
r_typedef
r_volatile
r_enum
id|status
(brace
DECL|enumerator|STATUS_PENDING
id|STATUS_PENDING
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
multiline_comment|/* initial status (written by host)  */
DECL|enumerator|STATUS_COMPLETE
id|STATUS_COMPLETE
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
multiline_comment|/* completion status (written by cp) */
DECL|enumerator|STATUS_FREE
id|STATUS_FREE
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
multiline_comment|/* initial status (written by host)  */
DECL|enumerator|STATUS_ERROR
id|STATUS_ERROR
op_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
multiline_comment|/* completion status (written by cp) */
DECL|typedef|status_t
)brace
id|status_t
suffix:semicolon
multiline_comment|/* cp operation code */
DECL|enum|opcode
r_typedef
r_enum
id|opcode
(brace
DECL|enumerator|OPCODE_INITIALIZE
id|OPCODE_INITIALIZE
op_assign
l_int|1
comma
multiline_comment|/* initialize board                       */
DECL|enumerator|OPCODE_ACTIVATE_VCIN
id|OPCODE_ACTIVATE_VCIN
comma
multiline_comment|/* activate incoming VCI                  */
DECL|enumerator|OPCODE_ACTIVATE_VCOUT
id|OPCODE_ACTIVATE_VCOUT
comma
multiline_comment|/* activate outgoing VCI                  */
DECL|enumerator|OPCODE_DEACTIVATE_VCIN
id|OPCODE_DEACTIVATE_VCIN
comma
multiline_comment|/* deactivate incoming VCI                */
DECL|enumerator|OPCODE_DEACTIVATE_VCOUT
id|OPCODE_DEACTIVATE_VCOUT
comma
multiline_comment|/* deactivate incoing VCI                 */
DECL|enumerator|OPCODE_GET_STATS
id|OPCODE_GET_STATS
comma
multiline_comment|/* get board statistics                   */
DECL|enumerator|OPCODE_SET_OC3
id|OPCODE_SET_OC3
comma
multiline_comment|/* set OC-3 registers                     */
DECL|enumerator|OPCODE_GET_OC3
id|OPCODE_GET_OC3
comma
multiline_comment|/* get OC-3 registers                     */
DECL|enumerator|OPCODE_RESET_STATS
id|OPCODE_RESET_STATS
comma
multiline_comment|/* reset board statistics                 */
DECL|enumerator|OPCODE_GET_PROM
id|OPCODE_GET_PROM
comma
multiline_comment|/* get expansion PROM data (PCI specific) */
DECL|enumerator|OPCODE_SET_VPI_BITS
id|OPCODE_SET_VPI_BITS
comma
multiline_comment|/* set x bits of those decoded by the&n;&t;&t;&t;&t;       firmware to be low order bits from&n;&t;&t;&t;&t;       the VPI field of the ATM cell header   */
DECL|enumerator|OPCODE_REQUEST_INTR
id|OPCODE_REQUEST_INTR
op_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
multiline_comment|/* request interrupt                      */
DECL|typedef|opcode_t
)brace
id|opcode_t
suffix:semicolon
multiline_comment|/* virtual path / virtual channel identifers */
DECL|struct|vpvc
r_typedef
r_struct
id|vpvc
(brace
id|BITFIELD3
c_func
(paren
id|u32
id|vci
suffix:colon
l_int|16
comma
multiline_comment|/* virtual channel identifier */
id|u32
id|vpi
suffix:colon
l_int|8
comma
multiline_comment|/* virtual path identifier    */
id|u32
id|pad
suffix:colon
l_int|8
multiline_comment|/* reserved                   */
)paren
DECL|typedef|vpvc_t
)brace
id|vpvc_t
suffix:semicolon
multiline_comment|/* activate VC command opcode */
DECL|struct|activate_opcode
r_typedef
r_struct
id|activate_opcode
(brace
id|BITFIELD4
c_func
(paren
r_enum
id|opcode
id|opcode
suffix:colon
l_int|8
comma
multiline_comment|/* cp opcode        */
r_enum
id|fore200e_aal
id|aal
suffix:colon
l_int|8
comma
multiline_comment|/* adaptation layer */
r_enum
id|buffer_scheme
id|scheme
suffix:colon
l_int|8
comma
multiline_comment|/* buffer scheme    */
id|u32
id|pad
suffix:colon
l_int|8
multiline_comment|/* reserved         */
)paren
DECL|typedef|activate_opcode_t
)brace
id|activate_opcode_t
suffix:semicolon
multiline_comment|/* activate VC command block */
DECL|struct|activate_block
r_typedef
r_struct
id|activate_block
(brace
DECL|member|opcode
r_struct
id|activate_opcode
id|opcode
suffix:semicolon
multiline_comment|/* activate VC command opcode */
DECL|member|vpvc
r_struct
id|vpvc
id|vpvc
suffix:semicolon
multiline_comment|/* VPI/VCI                    */
DECL|member|mtu
id|u32
id|mtu
suffix:semicolon
multiline_comment|/* for AAL0 only              */
DECL|typedef|activate_block_t
)brace
id|activate_block_t
suffix:semicolon
multiline_comment|/* deactivate VC command opcode */
DECL|struct|deactivate_opcode
r_typedef
r_struct
id|deactivate_opcode
(brace
id|BITFIELD2
c_func
(paren
r_enum
id|opcode
id|opcode
suffix:colon
l_int|8
comma
multiline_comment|/* cp opcode */
id|u32
id|pad
suffix:colon
l_int|24
multiline_comment|/* reserved  */
)paren
DECL|typedef|deactivate_opcode_t
)brace
id|deactivate_opcode_t
suffix:semicolon
multiline_comment|/* deactivate VC command block */
DECL|struct|deactivate_block
r_typedef
r_struct
id|deactivate_block
(brace
DECL|member|opcode
r_struct
id|deactivate_opcode
id|opcode
suffix:semicolon
multiline_comment|/* deactivate VC command opcode */
DECL|member|vpvc
r_struct
id|vpvc
id|vpvc
suffix:semicolon
multiline_comment|/* VPI/VCI                      */
DECL|typedef|deactivate_block_t
)brace
id|deactivate_block_t
suffix:semicolon
multiline_comment|/* OC-3 registers */
DECL|struct|oc3_regs
r_typedef
r_struct
id|oc3_regs
(brace
DECL|member|reg
id|u32
id|reg
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* see the PMC Sierra PC5346 S/UNI-155-Lite&n;&t;&t;&t;  Saturn User Network Interface documentation&n;&t;&t;&t;  for a description of the OC-3 chip registers */
DECL|typedef|oc3_regs_t
)brace
id|oc3_regs_t
suffix:semicolon
multiline_comment|/* set/get OC-3 regs command opcode */
DECL|struct|oc3_opcode
r_typedef
r_struct
id|oc3_opcode
(brace
id|BITFIELD4
c_func
(paren
r_enum
id|opcode
id|opcode
suffix:colon
l_int|8
comma
multiline_comment|/* cp opcode                           */
id|u32
id|reg
suffix:colon
l_int|8
comma
multiline_comment|/* register index                      */
id|u32
id|value
suffix:colon
l_int|8
comma
multiline_comment|/* register value                      */
id|u32
id|mask
suffix:colon
l_int|8
multiline_comment|/* register mask that specifies which&n;&t;&t;&t;&t;      bits of the register value field&n;&t;&t;&t;&t;      are significant                     */
)paren
DECL|typedef|oc3_opcode_t
)brace
id|oc3_opcode_t
suffix:semicolon
multiline_comment|/* set/get OC-3 regs command block */
DECL|struct|oc3_block
r_typedef
r_struct
id|oc3_block
(brace
DECL|member|opcode
r_struct
id|oc3_opcode
id|opcode
suffix:semicolon
multiline_comment|/* set/get OC-3 regs command opcode     */
DECL|member|regs_haddr
id|u32
id|regs_haddr
suffix:semicolon
multiline_comment|/* host DMA address of OC-3 regs buffer */
DECL|typedef|oc3_block_t
)brace
id|oc3_block_t
suffix:semicolon
multiline_comment|/* physical encoding statistics */
DECL|struct|stats_phy
r_typedef
r_struct
id|stats_phy
(brace
DECL|member|crc_header_errors
id|u32
id|crc_header_errors
suffix:semicolon
multiline_comment|/* cells received with bad header CRC */
DECL|member|framing_errors
id|u32
id|framing_errors
suffix:semicolon
multiline_comment|/* cells received with bad framing    */
DECL|member|pad
id|u32
id|pad
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* i960 padding                       */
DECL|typedef|stats_phy_t
)brace
id|stats_phy_t
suffix:semicolon
multiline_comment|/* OC-3 statistics */
DECL|struct|stats_oc3
r_typedef
r_struct
id|stats_oc3
(brace
DECL|member|section_bip8_errors
id|u32
id|section_bip8_errors
suffix:semicolon
multiline_comment|/* section 8 bit interleaved parity    */
DECL|member|path_bip8_errors
id|u32
id|path_bip8_errors
suffix:semicolon
multiline_comment|/* path 8 bit interleaved parity       */
DECL|member|line_bip24_errors
id|u32
id|line_bip24_errors
suffix:semicolon
multiline_comment|/* line 24 bit interleaved parity      */
DECL|member|line_febe_errors
id|u32
id|line_febe_errors
suffix:semicolon
multiline_comment|/* line far end block errors           */
DECL|member|path_febe_errors
id|u32
id|path_febe_errors
suffix:semicolon
multiline_comment|/* path far end block errors           */
DECL|member|corr_hcs_errors
id|u32
id|corr_hcs_errors
suffix:semicolon
multiline_comment|/* correctable header check sequence   */
DECL|member|ucorr_hcs_errors
id|u32
id|ucorr_hcs_errors
suffix:semicolon
multiline_comment|/* uncorrectable header check sequence */
DECL|member|pad
id|u32
id|pad
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* i960 padding                        */
DECL|typedef|stats_oc3_t
)brace
id|stats_oc3_t
suffix:semicolon
multiline_comment|/* ATM statistics */
DECL|struct|stats_atm
r_typedef
r_struct
id|stats_atm
(brace
DECL|member|cells_transmitted
id|u32
id|cells_transmitted
suffix:semicolon
multiline_comment|/* cells transmitted                 */
DECL|member|cells_received
id|u32
id|cells_received
suffix:semicolon
multiline_comment|/* cells received                    */
DECL|member|vpi_bad_range
id|u32
id|vpi_bad_range
suffix:semicolon
multiline_comment|/* cell drops: VPI out of range      */
DECL|member|vpi_no_conn
id|u32
id|vpi_no_conn
suffix:semicolon
multiline_comment|/* cell drops: no connection for VPI */
DECL|member|vci_bad_range
id|u32
id|vci_bad_range
suffix:semicolon
multiline_comment|/* cell drops: VCI out of range      */
DECL|member|vci_no_conn
id|u32
id|vci_no_conn
suffix:semicolon
multiline_comment|/* cell drops: no connection for VCI */
DECL|member|pad
id|u32
id|pad
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* i960 padding                      */
DECL|typedef|stats_atm_t
)brace
id|stats_atm_t
suffix:semicolon
multiline_comment|/* AAL0 statistics */
DECL|struct|stats_aal0
r_typedef
r_struct
id|stats_aal0
(brace
DECL|member|cells_transmitted
id|u32
id|cells_transmitted
suffix:semicolon
multiline_comment|/* cells transmitted */
DECL|member|cells_received
id|u32
id|cells_received
suffix:semicolon
multiline_comment|/* cells received    */
DECL|member|cells_dropped
id|u32
id|cells_dropped
suffix:semicolon
multiline_comment|/* cells dropped     */
DECL|member|pad
id|u32
id|pad
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* i960 padding      */
DECL|typedef|stats_aal0_t
)brace
id|stats_aal0_t
suffix:semicolon
multiline_comment|/* AAL3/4 statistics */
DECL|struct|stats_aal34
r_typedef
r_struct
id|stats_aal34
(brace
DECL|member|cells_transmitted
id|u32
id|cells_transmitted
suffix:semicolon
multiline_comment|/* cells transmitted from segmented PDUs */
DECL|member|cells_received
id|u32
id|cells_received
suffix:semicolon
multiline_comment|/* cells reassembled into PDUs           */
DECL|member|cells_crc_errors
id|u32
id|cells_crc_errors
suffix:semicolon
multiline_comment|/* payload CRC error count               */
DECL|member|cells_protocol_errors
id|u32
id|cells_protocol_errors
suffix:semicolon
multiline_comment|/* SAR or CS layer protocol errors       */
DECL|member|cells_dropped
id|u32
id|cells_dropped
suffix:semicolon
multiline_comment|/* cells dropped: partial reassembly     */
DECL|member|cspdus_transmitted
id|u32
id|cspdus_transmitted
suffix:semicolon
multiline_comment|/* CS PDUs transmitted                   */
DECL|member|cspdus_received
id|u32
id|cspdus_received
suffix:semicolon
multiline_comment|/* CS PDUs received                      */
DECL|member|cspdus_protocol_errors
id|u32
id|cspdus_protocol_errors
suffix:semicolon
multiline_comment|/* CS layer protocol errors              */
DECL|member|cspdus_dropped
id|u32
id|cspdus_dropped
suffix:semicolon
multiline_comment|/* reassembled PDUs drop&squot;d (in cells)    */
DECL|member|pad
id|u32
id|pad
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* i960 padding                          */
DECL|typedef|stats_aal34_t
)brace
id|stats_aal34_t
suffix:semicolon
multiline_comment|/* AAL5 statistics */
DECL|struct|stats_aal5
r_typedef
r_struct
id|stats_aal5
(brace
DECL|member|cells_transmitted
id|u32
id|cells_transmitted
suffix:semicolon
multiline_comment|/* cells transmitted from segmented SDUs */
DECL|member|cells_received
id|u32
id|cells_received
suffix:semicolon
multiline_comment|/* cells reassembled into SDUs           */
DECL|member|cells_dropped
id|u32
id|cells_dropped
suffix:semicolon
multiline_comment|/* reassembled PDUs dropped (in cells)   */
DECL|member|congestion_experienced
id|u32
id|congestion_experienced
suffix:semicolon
multiline_comment|/* CRC error and length wrong            */
DECL|member|cspdus_transmitted
id|u32
id|cspdus_transmitted
suffix:semicolon
multiline_comment|/* CS PDUs transmitted                   */
DECL|member|cspdus_received
id|u32
id|cspdus_received
suffix:semicolon
multiline_comment|/* CS PDUs received                      */
DECL|member|cspdus_crc_errors
id|u32
id|cspdus_crc_errors
suffix:semicolon
multiline_comment|/* CS PDUs CRC errors                    */
DECL|member|cspdus_protocol_errors
id|u32
id|cspdus_protocol_errors
suffix:semicolon
multiline_comment|/* CS layer protocol errors              */
DECL|member|cspdus_dropped
id|u32
id|cspdus_dropped
suffix:semicolon
multiline_comment|/* reassembled PDUs dropped              */
DECL|member|pad
id|u32
id|pad
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* i960 padding                          */
DECL|typedef|stats_aal5_t
)brace
id|stats_aal5_t
suffix:semicolon
multiline_comment|/* auxiliary statistics */
DECL|struct|stats_aux
r_typedef
r_struct
id|stats_aux
(brace
DECL|member|small_b1_failed
id|u32
id|small_b1_failed
suffix:semicolon
multiline_comment|/* receive BD allocation failures  */
DECL|member|large_b1_failed
id|u32
id|large_b1_failed
suffix:semicolon
multiline_comment|/* receive BD allocation failures  */
DECL|member|small_b2_failed
id|u32
id|small_b2_failed
suffix:semicolon
multiline_comment|/* receive BD allocation failures  */
DECL|member|large_b2_failed
id|u32
id|large_b2_failed
suffix:semicolon
multiline_comment|/* receive BD allocation failures  */
DECL|member|rpd_alloc_failed
id|u32
id|rpd_alloc_failed
suffix:semicolon
multiline_comment|/* receive PDU allocation failures */
DECL|member|receive_carrier
id|u32
id|receive_carrier
suffix:semicolon
multiline_comment|/* no carrier = 0, carrier = 1     */
DECL|member|pad
id|u32
id|pad
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* i960 padding                    */
DECL|typedef|stats_aux_t
)brace
id|stats_aux_t
suffix:semicolon
multiline_comment|/* whole statistics buffer */
DECL|struct|stats
r_typedef
r_struct
id|stats
(brace
DECL|member|phy
r_struct
id|stats_phy
id|phy
suffix:semicolon
multiline_comment|/* physical encoding statistics */
DECL|member|oc3
r_struct
id|stats_oc3
id|oc3
suffix:semicolon
multiline_comment|/* OC-3 statistics              */
DECL|member|atm
r_struct
id|stats_atm
id|atm
suffix:semicolon
multiline_comment|/* ATM statistics               */
DECL|member|aal0
r_struct
id|stats_aal0
id|aal0
suffix:semicolon
multiline_comment|/* AAL0 statistics              */
DECL|member|aal34
r_struct
id|stats_aal34
id|aal34
suffix:semicolon
multiline_comment|/* AAL3/4 statistics            */
DECL|member|aal5
r_struct
id|stats_aal5
id|aal5
suffix:semicolon
multiline_comment|/* AAL5 statistics              */
DECL|member|aux
r_struct
id|stats_aux
id|aux
suffix:semicolon
multiline_comment|/* auxiliary statistics         */
DECL|typedef|stats_t
)brace
id|stats_t
suffix:semicolon
multiline_comment|/* get statistics command opcode */
DECL|struct|stats_opcode
r_typedef
r_struct
id|stats_opcode
(brace
id|BITFIELD2
c_func
(paren
r_enum
id|opcode
id|opcode
suffix:colon
l_int|8
comma
multiline_comment|/* cp opcode */
id|u32
id|pad
suffix:colon
l_int|24
multiline_comment|/* reserved  */
)paren
DECL|typedef|stats_opcode_t
)brace
id|stats_opcode_t
suffix:semicolon
multiline_comment|/* get statistics command block */
DECL|struct|stats_block
r_typedef
r_struct
id|stats_block
(brace
DECL|member|opcode
r_struct
id|stats_opcode
id|opcode
suffix:semicolon
multiline_comment|/* get statistics command opcode    */
DECL|member|stats_haddr
id|u32
id|stats_haddr
suffix:semicolon
multiline_comment|/* host DMA address of stats buffer */
DECL|typedef|stats_block_t
)brace
id|stats_block_t
suffix:semicolon
multiline_comment|/* expansion PROM data (PCI specific) */
DECL|struct|prom_data
r_typedef
r_struct
id|prom_data
(brace
DECL|member|hw_revision
id|u32
id|hw_revision
suffix:semicolon
multiline_comment|/* hardware revision   */
DECL|member|serial_number
id|u32
id|serial_number
suffix:semicolon
multiline_comment|/* board serial number */
DECL|member|mac_addr
id|u8
id|mac_addr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* board MAC address   */
DECL|typedef|prom_data_t
)brace
id|prom_data_t
suffix:semicolon
multiline_comment|/* get expansion PROM data command opcode */
DECL|struct|prom_opcode
r_typedef
r_struct
id|prom_opcode
(brace
id|BITFIELD2
c_func
(paren
r_enum
id|opcode
id|opcode
suffix:colon
l_int|8
comma
multiline_comment|/* cp opcode */
id|u32
id|pad
suffix:colon
l_int|24
multiline_comment|/* reserved  */
)paren
DECL|typedef|prom_opcode_t
)brace
id|prom_opcode_t
suffix:semicolon
multiline_comment|/* get expansion PROM data command block */
DECL|struct|prom_block
r_typedef
r_struct
id|prom_block
(brace
DECL|member|opcode
r_struct
id|prom_opcode
id|opcode
suffix:semicolon
multiline_comment|/* get PROM data command opcode    */
DECL|member|prom_haddr
id|u32
id|prom_haddr
suffix:semicolon
multiline_comment|/* host DMA address of PROM buffer */
DECL|typedef|prom_block_t
)brace
id|prom_block_t
suffix:semicolon
multiline_comment|/* cp command */
DECL|union|cmd
r_typedef
r_union
id|cmd
(brace
DECL|member|opcode
r_enum
id|opcode
id|opcode
suffix:semicolon
multiline_comment|/* operation code          */
DECL|member|activate_block
r_struct
id|activate_block
id|activate_block
suffix:semicolon
multiline_comment|/* activate VC             */
DECL|member|deactivate_block
r_struct
id|deactivate_block
id|deactivate_block
suffix:semicolon
multiline_comment|/* deactivate VC           */
DECL|member|stats_block
r_struct
id|stats_block
id|stats_block
suffix:semicolon
multiline_comment|/* get statistics          */
DECL|member|prom_block
r_struct
id|prom_block
id|prom_block
suffix:semicolon
multiline_comment|/* get expansion PROM data */
DECL|member|oc3_block
r_struct
id|oc3_block
id|oc3_block
suffix:semicolon
multiline_comment|/* get/set OC-3 registers  */
DECL|member|pad
id|u32
id|pad
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* i960 padding            */
DECL|typedef|cmd_t
)brace
id|cmd_t
suffix:semicolon
multiline_comment|/* cp resident command queue */
DECL|struct|cp_cmdq_entry
r_typedef
r_struct
id|cp_cmdq_entry
(brace
DECL|member|cmd
r_union
id|cmd
id|cmd
suffix:semicolon
multiline_comment|/* command                               */
DECL|member|status_haddr
id|u32
id|status_haddr
suffix:semicolon
multiline_comment|/* host DMA address of completion status */
DECL|member|pad
id|u32
id|pad
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* i960 padding                          */
DECL|typedef|cp_cmdq_entry_t
)brace
id|cp_cmdq_entry_t
suffix:semicolon
multiline_comment|/* host resident transmit queue entry */
DECL|struct|host_txq_entry
r_typedef
r_struct
id|host_txq_entry
(brace
DECL|member|cp_entry
r_struct
id|cp_txq_entry
op_star
id|cp_entry
suffix:semicolon
multiline_comment|/* addr of cp resident tx queue entry */
DECL|member|status
r_enum
id|status
op_star
id|status
suffix:semicolon
multiline_comment|/* addr of host resident status       */
DECL|member|tpd
r_struct
id|tpd
op_star
id|tpd
suffix:semicolon
multiline_comment|/* addr of transmit PDU descriptor    */
DECL|member|tpd_dma
id|u32
id|tpd_dma
suffix:semicolon
multiline_comment|/* DMA address of tpd                 */
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* related skb                        */
DECL|member|vcc
r_struct
id|atm_vcc
op_star
id|vcc
suffix:semicolon
multiline_comment|/* related vcc                        */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* copy of misaligned data            */
DECL|typedef|host_txq_entry_t
)brace
id|host_txq_entry_t
suffix:semicolon
multiline_comment|/* host resident receive queue entry */
DECL|struct|host_rxq_entry
r_typedef
r_struct
id|host_rxq_entry
(brace
DECL|member|cp_entry
r_struct
id|cp_rxq_entry
op_star
id|cp_entry
suffix:semicolon
multiline_comment|/* addr of cp resident rx queue entry */
DECL|member|status
r_enum
id|status
op_star
id|status
suffix:semicolon
multiline_comment|/* addr of host resident status       */
DECL|member|rpd
r_struct
id|rpd
op_star
id|rpd
suffix:semicolon
multiline_comment|/* addr of receive PDU descriptor     */
DECL|member|rpd_dma
id|u32
id|rpd_dma
suffix:semicolon
multiline_comment|/* DMA address of rpd                 */
DECL|typedef|host_rxq_entry_t
)brace
id|host_rxq_entry_t
suffix:semicolon
multiline_comment|/* host resident buffer supply queue entry */
DECL|struct|host_bsq_entry
r_typedef
r_struct
id|host_bsq_entry
(brace
DECL|member|cp_entry
r_struct
id|cp_bsq_entry
op_star
id|cp_entry
suffix:semicolon
multiline_comment|/* addr of cp resident buffer supply queue entry */
DECL|member|status
r_enum
id|status
op_star
id|status
suffix:semicolon
multiline_comment|/* addr of host resident status                  */
DECL|member|rbd_block
r_struct
id|rbd_block
op_star
id|rbd_block
suffix:semicolon
multiline_comment|/* addr of receive buffer descriptor block       */
DECL|member|rbd_block_dma
id|u32
id|rbd_block_dma
suffix:semicolon
multiline_comment|/* DMA address od rdb                            */
DECL|typedef|host_bsq_entry_t
)brace
id|host_bsq_entry_t
suffix:semicolon
multiline_comment|/* host resident command queue entry */
DECL|struct|host_cmdq_entry
r_typedef
r_struct
id|host_cmdq_entry
(brace
DECL|member|cp_entry
r_struct
id|cp_cmdq_entry
op_star
id|cp_entry
suffix:semicolon
multiline_comment|/* addr of cp resident cmd queue entry */
DECL|member|status
r_enum
id|status
op_star
id|status
suffix:semicolon
multiline_comment|/* addr of host resident status        */
DECL|typedef|host_cmdq_entry_t
)brace
id|host_cmdq_entry_t
suffix:semicolon
multiline_comment|/* chunk of memory */
DECL|struct|chunk
r_typedef
r_struct
id|chunk
(brace
DECL|member|alloc_addr
r_void
op_star
id|alloc_addr
suffix:semicolon
multiline_comment|/* base address of allocated chunk */
DECL|member|align_addr
r_void
op_star
id|align_addr
suffix:semicolon
multiline_comment|/* base address of aligned chunk   */
DECL|member|dma_addr
id|u32
id|dma_addr
suffix:semicolon
multiline_comment|/* DMA address of aligned chunk    */
DECL|member|direction
r_int
id|direction
suffix:semicolon
multiline_comment|/* direction of DMA mapping        */
DECL|member|alloc_size
id|u32
id|alloc_size
suffix:semicolon
multiline_comment|/* length of allocated chunk       */
DECL|member|align_size
id|u32
id|align_size
suffix:semicolon
multiline_comment|/* length of aligned chunk         */
DECL|typedef|chunk_t
)brace
id|chunk_t
suffix:semicolon
DECL|macro|dma_size
mdefine_line|#define dma_size align_size             /* DMA useable size */
multiline_comment|/* host resident receive buffer */
DECL|struct|buffer
r_typedef
r_struct
id|buffer
(brace
DECL|member|next
r_struct
id|buffer
op_star
id|next
suffix:semicolon
multiline_comment|/* next receive buffer     */
DECL|member|scheme
r_enum
id|buffer_scheme
id|scheme
suffix:semicolon
multiline_comment|/* buffer scheme           */
DECL|member|magn
r_enum
id|buffer_magn
id|magn
suffix:semicolon
multiline_comment|/* buffer magnitude        */
DECL|member|data
r_struct
id|chunk
id|data
suffix:semicolon
multiline_comment|/* data buffer             */
DECL|typedef|buffer_t
)brace
id|buffer_t
suffix:semicolon
macro_line|#if (BITS_PER_LONG == 32)
DECL|macro|FORE200E_BUF2HDL
mdefine_line|#define FORE200E_BUF2HDL(buffer)    ((u32)(buffer))
DECL|macro|FORE200E_HDL2BUF
mdefine_line|#define FORE200E_HDL2BUF(handle)    ((struct buffer*)(handle))
macro_line|#else   /* deal with 64 bit pointers */
DECL|macro|FORE200E_BUF2HDL
mdefine_line|#define FORE200E_BUF2HDL(buffer)    ((u32)((u64)(buffer)))
DECL|macro|FORE200E_HDL2BUF
mdefine_line|#define FORE200E_HDL2BUF(handle)    ((struct buffer*)(((u64)(handle)) | PAGE_OFFSET))
macro_line|#endif
multiline_comment|/* host resident command queue */
DECL|struct|host_cmdq
r_typedef
r_struct
id|host_cmdq
(brace
DECL|member|host_entry
r_struct
id|host_cmdq_entry
id|host_entry
(braket
id|QUEUE_SIZE_CMD
)braket
suffix:semicolon
multiline_comment|/* host resident cmd queue entries        */
DECL|member|head
r_int
id|head
suffix:semicolon
multiline_comment|/* head of cmd queue                      */
DECL|member|status
r_struct
id|chunk
id|status
suffix:semicolon
multiline_comment|/* array of completion status      */
DECL|typedef|host_cmdq_t
)brace
id|host_cmdq_t
suffix:semicolon
multiline_comment|/* host resident transmit queue */
DECL|struct|host_txq
r_typedef
r_struct
id|host_txq
(brace
DECL|member|host_entry
r_struct
id|host_txq_entry
id|host_entry
(braket
id|QUEUE_SIZE_TX
)braket
suffix:semicolon
multiline_comment|/* host resident tx queue entries         */
DECL|member|head
r_int
id|head
suffix:semicolon
multiline_comment|/* head of tx queue                       */
DECL|member|tpd
r_struct
id|chunk
id|tpd
suffix:semicolon
multiline_comment|/* array of tpds                          */
DECL|member|status
r_struct
id|chunk
id|status
suffix:semicolon
multiline_comment|/* arry of completion status              */
DECL|member|txing
r_int
id|txing
suffix:semicolon
multiline_comment|/* number of pending PDUs in tx queue     */
DECL|typedef|host_txq_t
)brace
id|host_txq_t
suffix:semicolon
multiline_comment|/* host resident receive queue */
DECL|struct|host_rxq
r_typedef
r_struct
id|host_rxq
(brace
DECL|member|host_entry
r_struct
id|host_rxq_entry
id|host_entry
(braket
id|QUEUE_SIZE_RX
)braket
suffix:semicolon
multiline_comment|/* host resident rx queue entries         */
DECL|member|head
r_int
id|head
suffix:semicolon
multiline_comment|/* head of rx queue                       */
DECL|member|rpd
r_struct
id|chunk
id|rpd
suffix:semicolon
multiline_comment|/* array of rpds                          */
DECL|member|status
r_struct
id|chunk
id|status
suffix:semicolon
multiline_comment|/* array of completion status             */
DECL|typedef|host_rxq_t
)brace
id|host_rxq_t
suffix:semicolon
multiline_comment|/* host resident buffer supply queues */
DECL|struct|host_bsq
r_typedef
r_struct
id|host_bsq
(brace
DECL|member|host_entry
r_struct
id|host_bsq_entry
id|host_entry
(braket
id|QUEUE_SIZE_BS
)braket
suffix:semicolon
multiline_comment|/* host resident buffer supply queue entries */
DECL|member|head
r_int
id|head
suffix:semicolon
multiline_comment|/* head of buffer supply queue               */
DECL|member|rbd_block
r_struct
id|chunk
id|rbd_block
suffix:semicolon
multiline_comment|/* array of rbds                             */
DECL|member|status
r_struct
id|chunk
id|status
suffix:semicolon
multiline_comment|/* array of completion status                */
DECL|member|buffer
r_struct
id|buffer
op_star
id|buffer
suffix:semicolon
multiline_comment|/* array of rx buffers                       */
DECL|member|free
r_int
id|free
suffix:semicolon
multiline_comment|/* index of first free rx buffer             */
DECL|member|count
r_volatile
r_int
id|count
suffix:semicolon
multiline_comment|/* count of supplied rx buffers              */
DECL|typedef|host_bsq_t
)brace
id|host_bsq_t
suffix:semicolon
multiline_comment|/* header of the firmware image */
DECL|struct|fw_header
r_typedef
r_struct
id|fw_header
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
multiline_comment|/* magic number                               */
DECL|member|version
id|u32
id|version
suffix:semicolon
multiline_comment|/* firware version id                         */
DECL|member|load_offset
id|u32
id|load_offset
suffix:semicolon
multiline_comment|/* fw load offset in board memory             */
DECL|member|start_offset
id|u32
id|start_offset
suffix:semicolon
multiline_comment|/* fw execution start address in board memory */
DECL|typedef|fw_header_t
)brace
id|fw_header_t
suffix:semicolon
DECL|macro|FW_HEADER_MAGIC
mdefine_line|#define FW_HEADER_MAGIC  0x65726f66    /* &squot;fore&squot; */
multiline_comment|/* receive buffer supply queues scheme specification */
DECL|struct|bs_spec
r_typedef
r_struct
id|bs_spec
(brace
DECL|member|queue_length
id|u32
id|queue_length
suffix:semicolon
multiline_comment|/* queue capacity                     */
DECL|member|buffer_size
id|u32
id|buffer_size
suffix:semicolon
multiline_comment|/* host buffer size&t;&t;&t; */
DECL|member|pool_size
id|u32
id|pool_size
suffix:semicolon
multiline_comment|/* number of rbds&t;&t;&t; */
DECL|member|supply_blksize
id|u32
id|supply_blksize
suffix:semicolon
multiline_comment|/* num of rbds in I/O block (multiple&n;&t;&t;&t;      of 4 between 4 and 124 inclusive)&t; */
DECL|typedef|bs_spec_t
)brace
id|bs_spec_t
suffix:semicolon
multiline_comment|/* initialization command block (one-time command, not in cmd queue) */
DECL|struct|init_block
r_typedef
r_struct
id|init_block
(brace
DECL|member|opcode
r_enum
id|opcode
id|opcode
suffix:semicolon
multiline_comment|/* initialize command             */
DECL|member|status
r_enum
id|status
id|status
suffix:semicolon
multiline_comment|/* related status word            */
DECL|member|receive_threshold
id|u32
id|receive_threshold
suffix:semicolon
multiline_comment|/* not used                       */
DECL|member|num_connect
id|u32
id|num_connect
suffix:semicolon
multiline_comment|/* ATM connections                */
DECL|member|cmd_queue_len
id|u32
id|cmd_queue_len
suffix:semicolon
multiline_comment|/* length of command queue        */
DECL|member|tx_queue_len
id|u32
id|tx_queue_len
suffix:semicolon
multiline_comment|/* length of transmit queue       */
DECL|member|rx_queue_len
id|u32
id|rx_queue_len
suffix:semicolon
multiline_comment|/* length of receive queue        */
DECL|member|rsd_extension
id|u32
id|rsd_extension
suffix:semicolon
multiline_comment|/* number of extra 32 byte blocks */
DECL|member|tsd_extension
id|u32
id|tsd_extension
suffix:semicolon
multiline_comment|/* number of extra 32 byte blocks */
DECL|member|conless_vpvc
id|u32
id|conless_vpvc
suffix:semicolon
multiline_comment|/* not used                       */
DECL|member|pad
id|u32
id|pad
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* force quad alignment           */
DECL|member|bs_spec
r_struct
id|bs_spec
id|bs_spec
(braket
id|BUFFER_SCHEME_NBR
)braket
(braket
id|BUFFER_MAGN_NBR
)braket
suffix:semicolon
multiline_comment|/* buffer supply queues spec */
DECL|typedef|init_block_t
)brace
id|init_block_t
suffix:semicolon
DECL|enum|media_type
r_typedef
r_enum
id|media_type
(brace
DECL|enumerator|MEDIA_TYPE_CAT5_UTP
id|MEDIA_TYPE_CAT5_UTP
op_assign
l_int|0x06
comma
multiline_comment|/* unshielded twisted pair */
DECL|enumerator|MEDIA_TYPE_MM_OC3_ST
id|MEDIA_TYPE_MM_OC3_ST
op_assign
l_int|0x16
comma
multiline_comment|/* multimode fiber ST      */
DECL|enumerator|MEDIA_TYPE_MM_OC3_SC
id|MEDIA_TYPE_MM_OC3_SC
op_assign
l_int|0x26
comma
multiline_comment|/* multimode fiber SC      */
DECL|enumerator|MEDIA_TYPE_SM_OC3_ST
id|MEDIA_TYPE_SM_OC3_ST
op_assign
l_int|0x36
comma
multiline_comment|/* single-mode fiber ST    */
DECL|enumerator|MEDIA_TYPE_SM_OC3_SC
id|MEDIA_TYPE_SM_OC3_SC
op_assign
l_int|0x46
multiline_comment|/* single-mode fiber SC    */
DECL|typedef|media_type_t
)brace
id|media_type_t
suffix:semicolon
DECL|macro|FORE200E_MEDIA_INDEX
mdefine_line|#define FORE200E_MEDIA_INDEX(media_type)   ((media_type)&gt;&gt;4)
multiline_comment|/* cp resident queues */
DECL|struct|cp_queues
r_typedef
r_struct
id|cp_queues
(brace
DECL|member|cp_cmdq
id|u32
id|cp_cmdq
suffix:semicolon
multiline_comment|/* command queue                      */
DECL|member|cp_txq
id|u32
id|cp_txq
suffix:semicolon
multiline_comment|/* transmit queue                     */
DECL|member|cp_rxq
id|u32
id|cp_rxq
suffix:semicolon
multiline_comment|/* receive queue                      */
DECL|member|cp_bsq
id|u32
id|cp_bsq
(braket
id|BUFFER_SCHEME_NBR
)braket
(braket
id|BUFFER_MAGN_NBR
)braket
suffix:semicolon
multiline_comment|/* buffer supply queues */
DECL|member|imask
id|u32
id|imask
suffix:semicolon
multiline_comment|/* 1 enables cp to host interrupts  */
DECL|member|istat
id|u32
id|istat
suffix:semicolon
multiline_comment|/* 1 for interrupt posted           */
DECL|member|heap_base
id|u32
id|heap_base
suffix:semicolon
multiline_comment|/* offset form beginning of ram     */
DECL|member|heap_size
id|u32
id|heap_size
suffix:semicolon
multiline_comment|/* space available for queues       */
DECL|member|hlogger
id|u32
id|hlogger
suffix:semicolon
multiline_comment|/* non zero for host logging        */
DECL|member|heartbeat
id|u32
id|heartbeat
suffix:semicolon
multiline_comment|/* cp heartbeat                     */
DECL|member|fw_release
id|u32
id|fw_release
suffix:semicolon
multiline_comment|/* firmware version                 */
DECL|member|mon960_release
id|u32
id|mon960_release
suffix:semicolon
multiline_comment|/* i960 monitor version             */
DECL|member|tq_plen
id|u32
id|tq_plen
suffix:semicolon
multiline_comment|/* transmit throughput measurements */
multiline_comment|/* make sure the init block remains on a quad word boundary              */
DECL|member|init
r_struct
id|init_block
id|init
suffix:semicolon
multiline_comment|/* one time cmd, not in cmd queue   */
DECL|member|media_type
r_enum
id|media_type
id|media_type
suffix:semicolon
multiline_comment|/* media type id                    */
DECL|member|oc3_revision
id|u32
id|oc3_revision
suffix:semicolon
multiline_comment|/* OC-3 revision number             */
DECL|typedef|cp_queues_t
)brace
id|cp_queues_t
suffix:semicolon
multiline_comment|/* boot status */
DECL|enum|boot_status
r_typedef
r_enum
id|boot_status
(brace
DECL|enumerator|BSTAT_COLD_START
id|BSTAT_COLD_START
op_assign
(paren
id|u32
)paren
l_int|0xc01dc01d
comma
multiline_comment|/* cold start              */
DECL|enumerator|BSTAT_SELFTEST_OK
id|BSTAT_SELFTEST_OK
op_assign
(paren
id|u32
)paren
l_int|0x02201958
comma
multiline_comment|/* self-test ok            */
DECL|enumerator|BSTAT_SELFTEST_FAIL
id|BSTAT_SELFTEST_FAIL
op_assign
(paren
id|u32
)paren
l_int|0xadbadbad
comma
multiline_comment|/* self-test failed        */
DECL|enumerator|BSTAT_CP_RUNNING
id|BSTAT_CP_RUNNING
op_assign
(paren
id|u32
)paren
l_int|0xce11feed
comma
multiline_comment|/* cp is running           */
DECL|enumerator|BSTAT_MON_TOO_BIG
id|BSTAT_MON_TOO_BIG
op_assign
(paren
id|u32
)paren
l_int|0x10aded00
multiline_comment|/* i960 monitor is too big */
DECL|typedef|boot_status_t
)brace
id|boot_status_t
suffix:semicolon
multiline_comment|/* software UART */
DECL|struct|soft_uart
r_typedef
r_struct
id|soft_uart
(brace
DECL|member|send
id|u32
id|send
suffix:semicolon
multiline_comment|/* write register */
DECL|member|recv
id|u32
id|recv
suffix:semicolon
multiline_comment|/* read register  */
DECL|typedef|soft_uart_t
)brace
id|soft_uart_t
suffix:semicolon
DECL|macro|FORE200E_CP_MONITOR_UART_FREE
mdefine_line|#define FORE200E_CP_MONITOR_UART_FREE     0x00000000
DECL|macro|FORE200E_CP_MONITOR_UART_AVAIL
mdefine_line|#define FORE200E_CP_MONITOR_UART_AVAIL    0x01000000
multiline_comment|/* i960 monitor */
DECL|struct|cp_monitor
r_typedef
r_struct
id|cp_monitor
(brace
DECL|member|soft_uart
r_struct
id|soft_uart
id|soft_uart
suffix:semicolon
multiline_comment|/* software UART           */
DECL|member|bstat
r_enum
id|boot_status
id|bstat
suffix:semicolon
multiline_comment|/* boot status             */
DECL|member|app_base
id|u32
id|app_base
suffix:semicolon
multiline_comment|/* application base offset */
DECL|member|mon_version
id|u32
id|mon_version
suffix:semicolon
multiline_comment|/* i960 monitor version    */
DECL|typedef|cp_monitor_t
)brace
id|cp_monitor_t
suffix:semicolon
multiline_comment|/* device state */
DECL|enum|fore200e_state
r_typedef
r_enum
id|fore200e_state
(brace
DECL|enumerator|FORE200E_STATE_BLANK
id|FORE200E_STATE_BLANK
comma
multiline_comment|/* initial state                     */
DECL|enumerator|FORE200E_STATE_REGISTER
id|FORE200E_STATE_REGISTER
comma
multiline_comment|/* device registered                 */
DECL|enumerator|FORE200E_STATE_CONFIGURE
id|FORE200E_STATE_CONFIGURE
comma
multiline_comment|/* bus interface configured          */
DECL|enumerator|FORE200E_STATE_MAP
id|FORE200E_STATE_MAP
comma
multiline_comment|/* board space mapped in host memory */
DECL|enumerator|FORE200E_STATE_RESET
id|FORE200E_STATE_RESET
comma
multiline_comment|/* board resetted                    */
DECL|enumerator|FORE200E_STATE_LOAD_FW
id|FORE200E_STATE_LOAD_FW
comma
multiline_comment|/* firmware loaded                   */
DECL|enumerator|FORE200E_STATE_START_FW
id|FORE200E_STATE_START_FW
comma
multiline_comment|/* firmware started                  */
DECL|enumerator|FORE200E_STATE_INITIALIZE
id|FORE200E_STATE_INITIALIZE
comma
multiline_comment|/* initialize command successful     */
DECL|enumerator|FORE200E_STATE_INIT_CMDQ
id|FORE200E_STATE_INIT_CMDQ
comma
multiline_comment|/* command queue initialized         */
DECL|enumerator|FORE200E_STATE_INIT_TXQ
id|FORE200E_STATE_INIT_TXQ
comma
multiline_comment|/* transmit queue initialized        */
DECL|enumerator|FORE200E_STATE_INIT_RXQ
id|FORE200E_STATE_INIT_RXQ
comma
multiline_comment|/* receive queue initialized         */
DECL|enumerator|FORE200E_STATE_INIT_BSQ
id|FORE200E_STATE_INIT_BSQ
comma
multiline_comment|/* buffer supply queue initialized   */
DECL|enumerator|FORE200E_STATE_ALLOC_BUF
id|FORE200E_STATE_ALLOC_BUF
comma
multiline_comment|/* receive buffers allocated         */
DECL|enumerator|FORE200E_STATE_IRQ
id|FORE200E_STATE_IRQ
comma
multiline_comment|/* host interrupt requested          */
DECL|enumerator|FORE200E_STATE_COMPLETE
id|FORE200E_STATE_COMPLETE
multiline_comment|/* initialization completed          */
DECL|typedef|fore200e_state
)brace
id|fore200e_state
suffix:semicolon
multiline_comment|/* PCA-200E registers */
DECL|struct|fore200e_pca_regs
r_typedef
r_struct
id|fore200e_pca_regs
(brace
DECL|member|hcr
r_volatile
id|u32
op_star
id|hcr
suffix:semicolon
multiline_comment|/* address of host control register        */
DECL|member|imr
r_volatile
id|u32
op_star
id|imr
suffix:semicolon
multiline_comment|/* address of host interrupt mask register */
DECL|member|psr
r_volatile
id|u32
op_star
id|psr
suffix:semicolon
multiline_comment|/* address of PCI specific register        */
DECL|typedef|fore200e_pca_regs_t
)brace
id|fore200e_pca_regs_t
suffix:semicolon
multiline_comment|/* SBA-200E registers */
DECL|struct|fore200e_sba_regs
r_typedef
r_struct
id|fore200e_sba_regs
(brace
DECL|member|hcr
r_volatile
id|u32
op_star
id|hcr
suffix:semicolon
multiline_comment|/* address of host control register              */
DECL|member|bsr
r_volatile
id|u32
op_star
id|bsr
suffix:semicolon
multiline_comment|/* address of burst transfer size register       */
DECL|member|isr
r_volatile
id|u32
op_star
id|isr
suffix:semicolon
multiline_comment|/* address of interrupt level selection register */
DECL|typedef|fore200e_sba_regs_t
)brace
id|fore200e_sba_regs_t
suffix:semicolon
multiline_comment|/* model-specific registers */
DECL|union|fore200e_regs
r_typedef
r_union
id|fore200e_regs
(brace
DECL|member|pca
r_struct
id|fore200e_pca_regs
id|pca
suffix:semicolon
multiline_comment|/* PCA-200E registers */
DECL|member|sba
r_struct
id|fore200e_sba_regs
id|sba
suffix:semicolon
multiline_comment|/* SBA-200E registers */
DECL|typedef|fore200e_regs
)brace
id|fore200e_regs
suffix:semicolon
r_struct
id|fore200e
suffix:semicolon
multiline_comment|/* bus-dependent data */
DECL|struct|fore200e_bus
r_typedef
r_struct
id|fore200e_bus
(brace
DECL|member|model_name
r_char
op_star
id|model_name
suffix:semicolon
multiline_comment|/* board model name                       */
DECL|member|proc_name
r_char
op_star
id|proc_name
suffix:semicolon
multiline_comment|/* board name under /proc/atm             */
DECL|member|descr_alignment
r_int
id|descr_alignment
suffix:semicolon
multiline_comment|/* tpd/rpd/rbd DMA alignment requirement  */
DECL|member|buffer_alignment
r_int
id|buffer_alignment
suffix:semicolon
multiline_comment|/* rx buffers DMA alignment requirement   */
DECL|member|status_alignment
r_int
id|status_alignment
suffix:semicolon
multiline_comment|/* status words DMA alignment requirement */
DECL|member|fw_data
r_const
r_int
r_char
op_star
id|fw_data
suffix:semicolon
multiline_comment|/* address of firmware data start         */
DECL|member|fw_size
r_const
r_int
r_int
op_star
id|fw_size
suffix:semicolon
multiline_comment|/* address of firmware data size          */
DECL|member|read
id|u32
(paren
op_star
id|read
)paren
(paren
r_volatile
id|u32
op_star
)paren
suffix:semicolon
DECL|member|write
r_void
(paren
op_star
id|write
)paren
(paren
id|u32
comma
r_volatile
id|u32
op_star
)paren
suffix:semicolon
DECL|member|dma_map
id|u32
(paren
op_star
id|dma_map
)paren
(paren
r_struct
id|fore200e
op_star
comma
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|dma_unmap
r_void
(paren
op_star
id|dma_unmap
)paren
(paren
r_struct
id|fore200e
op_star
comma
id|u32
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|dma_sync
r_void
(paren
op_star
id|dma_sync
)paren
(paren
r_struct
id|fore200e
op_star
comma
id|u32
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|dma_chunk_alloc
r_int
(paren
op_star
id|dma_chunk_alloc
)paren
(paren
r_struct
id|fore200e
op_star
comma
r_struct
id|chunk
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|dma_chunk_free
r_void
(paren
op_star
id|dma_chunk_free
)paren
(paren
r_struct
id|fore200e
op_star
comma
r_struct
id|chunk
op_star
)paren
suffix:semicolon
DECL|member|detect
r_struct
id|fore200e
op_star
(paren
op_star
id|detect
)paren
(paren
r_const
r_struct
id|fore200e_bus
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|configure
r_int
(paren
op_star
id|configure
)paren
(paren
r_struct
id|fore200e
op_star
)paren
suffix:semicolon
DECL|member|map
r_int
(paren
op_star
id|map
)paren
(paren
r_struct
id|fore200e
op_star
)paren
suffix:semicolon
DECL|member|reset
r_void
(paren
op_star
id|reset
)paren
(paren
r_struct
id|fore200e
op_star
)paren
suffix:semicolon
DECL|member|prom_read
r_int
(paren
op_star
id|prom_read
)paren
(paren
r_struct
id|fore200e
op_star
comma
r_struct
id|prom_data
op_star
)paren
suffix:semicolon
DECL|member|unmap
r_void
(paren
op_star
id|unmap
)paren
(paren
r_struct
id|fore200e
op_star
)paren
suffix:semicolon
DECL|member|irq_enable
r_void
(paren
op_star
id|irq_enable
)paren
(paren
r_struct
id|fore200e
op_star
)paren
suffix:semicolon
DECL|member|irq_check
r_int
(paren
op_star
id|irq_check
)paren
(paren
r_struct
id|fore200e
op_star
)paren
suffix:semicolon
DECL|member|irq_ack
r_void
(paren
op_star
id|irq_ack
)paren
(paren
r_struct
id|fore200e
op_star
)paren
suffix:semicolon
DECL|member|proc_read
r_int
(paren
op_star
id|proc_read
)paren
(paren
r_struct
id|fore200e
op_star
comma
r_char
op_star
)paren
suffix:semicolon
DECL|typedef|fore200e_bus_t
)brace
id|fore200e_bus_t
suffix:semicolon
macro_line|#if defined(CONFIG_ATM_FORE200E_SBA)
macro_line|#  if defined(CONFIG_ATM_FORE200E_PCA)
macro_line|#    if (PCI_DMA_BIDIRECTIONAL == SBUS_DMA_BIDIRECTIONAL) &amp;&amp; &bslash;&n;        (PCI_DMA_TODEVICE      == SBUS_DMA_TODEVICE)      &amp;&amp; &bslash;&n;        (PCI_DMA_FROMDEVICE    == SBUS_DMA_FROMDEVICE)
DECL|macro|FORE200E_DMA_BIDIRECTIONAL
macro_line|#      define FORE200E_DMA_BIDIRECTIONAL PCI_DMA_BIDIRECTIONAL
DECL|macro|FORE200E_DMA_TODEVICE
macro_line|#      define FORE200E_DMA_TODEVICE      PCI_DMA_TODEVICE
DECL|macro|FORE200E_DMA_FROMDEVICE
macro_line|#      define FORE200E_DMA_FROMDEVICE    PCI_DMA_FROMDEVICE
macro_line|#    else
multiline_comment|/* in that case, we&squot;ll need to add an extra indirection, e.g.&n;&t;  fore200e-&gt;bus-&gt;dma_direction[ fore200e_dma_direction ] */
macro_line|#      error PCI and SBUS DMA direction flags have different values!
macro_line|#    endif
macro_line|#  else
DECL|macro|FORE200E_DMA_BIDIRECTIONAL
macro_line|#    define FORE200E_DMA_BIDIRECTIONAL SBUS_DMA_BIDIRECTIONAL
DECL|macro|FORE200E_DMA_TODEVICE
macro_line|#    define FORE200E_DMA_TODEVICE      SBUS_DMA_TODEVICE
DECL|macro|FORE200E_DMA_FROMDEVICE
macro_line|#    define FORE200E_DMA_FROMDEVICE    SBUS_DMA_FROMDEVICE
macro_line|#  endif
macro_line|#else
macro_line|#  ifndef CONFIG_ATM_FORE200E_PCA
macro_line|#    warning compiling the fore200e driver without any hardware support enabled!
macro_line|#    include &lt;linux/pci.h&gt;
macro_line|#  endif
DECL|macro|FORE200E_DMA_BIDIRECTIONAL
macro_line|#  define FORE200E_DMA_BIDIRECTIONAL PCI_DMA_BIDIRECTIONAL
DECL|macro|FORE200E_DMA_TODEVICE
macro_line|#  define FORE200E_DMA_TODEVICE      PCI_DMA_TODEVICE
DECL|macro|FORE200E_DMA_FROMDEVICE
macro_line|#  define FORE200E_DMA_FROMDEVICE    PCI_DMA_FROMDEVICE
macro_line|#endif
multiline_comment|/* per-device data */
DECL|struct|fore200e
r_typedef
r_struct
id|fore200e
(brace
DECL|member|next
r_struct
id|fore200e
op_star
id|next
suffix:semicolon
multiline_comment|/* next device                        */
DECL|member|bus
r_const
r_struct
id|fore200e_bus
op_star
id|bus
suffix:semicolon
multiline_comment|/* bus-dependent code and data        */
DECL|member|regs
r_union
id|fore200e_regs
id|regs
suffix:semicolon
multiline_comment|/* bus-dependent registers            */
DECL|member|atm_dev
r_struct
id|atm_dev
op_star
id|atm_dev
suffix:semicolon
multiline_comment|/* ATM device                         */
DECL|member|state
r_enum
id|fore200e_state
id|state
suffix:semicolon
multiline_comment|/* device state                       */
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* device name                        */
DECL|member|bus_dev
r_void
op_star
id|bus_dev
suffix:semicolon
multiline_comment|/* bus-specific kernel data           */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* irq number                         */
DECL|member|phys_base
r_int
r_int
id|phys_base
suffix:semicolon
multiline_comment|/* physical base address              */
DECL|member|virt_base
r_void
op_star
id|virt_base
suffix:semicolon
multiline_comment|/* virtual base address               */
DECL|member|esi
r_int
r_char
id|esi
(braket
id|ESI_LEN
)braket
suffix:semicolon
multiline_comment|/* end system identifier              */
DECL|member|cp_monitor
r_struct
id|cp_monitor
op_star
id|cp_monitor
suffix:semicolon
multiline_comment|/* i960 monitor address               */
DECL|member|cp_queues
r_struct
id|cp_queues
op_star
id|cp_queues
suffix:semicolon
multiline_comment|/* cp resident queues                 */
DECL|member|host_cmdq
r_struct
id|host_cmdq
id|host_cmdq
suffix:semicolon
multiline_comment|/* host resident cmd queue            */
DECL|member|host_txq
r_struct
id|host_txq
id|host_txq
suffix:semicolon
multiline_comment|/* host resident tx queue             */
DECL|member|host_rxq
r_struct
id|host_rxq
id|host_rxq
suffix:semicolon
multiline_comment|/* host resident rx queue             */
multiline_comment|/* host resident buffer supply queues */
DECL|member|host_bsq
r_struct
id|host_bsq
id|host_bsq
(braket
id|BUFFER_SCHEME_NBR
)braket
(braket
id|BUFFER_MAGN_NBR
)braket
suffix:semicolon
DECL|member|available_cell_rate
id|u32
id|available_cell_rate
suffix:semicolon
multiline_comment|/* remaining pseudo-CBR bw on link    */
DECL|member|loop_mode
r_int
id|loop_mode
suffix:semicolon
multiline_comment|/* S/UNI loopback mode                */
DECL|member|stats
r_struct
id|stats
op_star
id|stats
suffix:semicolon
multiline_comment|/* last snapshot of the stats         */
DECL|member|rate_sf
r_struct
id|semaphore
id|rate_sf
suffix:semicolon
multiline_comment|/* protects rate reservation ops      */
DECL|member|tasklet
r_struct
id|tasklet_struct
id|tasklet
suffix:semicolon
multiline_comment|/* performs interrupt work            */
DECL|typedef|fore200e_t
)brace
id|fore200e_t
suffix:semicolon
multiline_comment|/* per-vcc data */
DECL|struct|fore200e_vcc
r_typedef
r_struct
id|fore200e_vcc
(brace
DECL|member|scheme
r_enum
id|buffer_scheme
id|scheme
suffix:semicolon
multiline_comment|/* rx buffer scheme                   */
DECL|member|rate
r_struct
id|tpd_rate
id|rate
suffix:semicolon
multiline_comment|/* tx rate control data               */
DECL|member|rx_min_pdu
r_int
id|rx_min_pdu
suffix:semicolon
multiline_comment|/* size of smallest PDU received      */
DECL|member|rx_max_pdu
r_int
id|rx_max_pdu
suffix:semicolon
multiline_comment|/* size of largest PDU received       */
DECL|member|tx_min_pdu
r_int
id|tx_min_pdu
suffix:semicolon
multiline_comment|/* size of smallest PDU transmitted   */
DECL|member|tx_max_pdu
r_int
id|tx_max_pdu
suffix:semicolon
multiline_comment|/* size of largest PDU transmitted    */
DECL|typedef|fore200e_vcc_t
)brace
id|fore200e_vcc_t
suffix:semicolon
multiline_comment|/* 200E-series common memory layout */
DECL|macro|FORE200E_CP_MONITOR_OFFSET
mdefine_line|#define FORE200E_CP_MONITOR_OFFSET&t;0x00000400    /* i960 monitor interface */
DECL|macro|FORE200E_CP_QUEUES_OFFSET
mdefine_line|#define FORE200E_CP_QUEUES_OFFSET&t;0x00004d40    /* cp resident queues     */
multiline_comment|/* PCA-200E memory layout */
DECL|macro|PCA200E_IOSPACE_LENGTH
mdefine_line|#define PCA200E_IOSPACE_LENGTH&t;        0x00200000
DECL|macro|PCA200E_HCR_OFFSET
mdefine_line|#define PCA200E_HCR_OFFSET&t;&t;0x00100000    /* board control register */
DECL|macro|PCA200E_IMR_OFFSET
mdefine_line|#define PCA200E_IMR_OFFSET&t;&t;0x00100004    /* host IRQ mask register */
DECL|macro|PCA200E_PSR_OFFSET
mdefine_line|#define PCA200E_PSR_OFFSET&t;&t;0x00100008    /* PCI specific register  */
multiline_comment|/* PCA-200E host control register */
DECL|macro|PCA200E_HCR_RESET
mdefine_line|#define PCA200E_HCR_RESET     (1&lt;&lt;0)    /* read / write */
DECL|macro|PCA200E_HCR_HOLD_LOCK
mdefine_line|#define PCA200E_HCR_HOLD_LOCK (1&lt;&lt;1)    /* read / write */
DECL|macro|PCA200E_HCR_I960FAIL
mdefine_line|#define PCA200E_HCR_I960FAIL  (1&lt;&lt;2)    /* read         */
DECL|macro|PCA200E_HCR_INTRB
mdefine_line|#define PCA200E_HCR_INTRB     (1&lt;&lt;2)    /* write        */
DECL|macro|PCA200E_HCR_HOLD_ACK
mdefine_line|#define PCA200E_HCR_HOLD_ACK  (1&lt;&lt;3)    /* read         */
DECL|macro|PCA200E_HCR_INTRA
mdefine_line|#define PCA200E_HCR_INTRA     (1&lt;&lt;3)    /* write        */
DECL|macro|PCA200E_HCR_OUTFULL
mdefine_line|#define PCA200E_HCR_OUTFULL   (1&lt;&lt;4)    /* read         */
DECL|macro|PCA200E_HCR_CLRINTR
mdefine_line|#define PCA200E_HCR_CLRINTR   (1&lt;&lt;4)    /* write        */
DECL|macro|PCA200E_HCR_ESPHOLD
mdefine_line|#define PCA200E_HCR_ESPHOLD   (1&lt;&lt;5)    /* read         */
DECL|macro|PCA200E_HCR_INFULL
mdefine_line|#define PCA200E_HCR_INFULL    (1&lt;&lt;6)    /* read         */
DECL|macro|PCA200E_HCR_TESTMODE
mdefine_line|#define PCA200E_HCR_TESTMODE  (1&lt;&lt;7)    /* read         */
multiline_comment|/* PCA-200E PCI bus interface regs (offsets in PCI config space) */
DECL|macro|PCA200E_PCI_LATENCY
mdefine_line|#define PCA200E_PCI_LATENCY      0x40    /* maximum slave latenty            */
DECL|macro|PCA200E_PCI_MASTER_CTRL
mdefine_line|#define PCA200E_PCI_MASTER_CTRL  0x41    /* master control                   */
DECL|macro|PCA200E_PCI_THRESHOLD
mdefine_line|#define PCA200E_PCI_THRESHOLD    0x42    /* burst / continous req threshold  */
multiline_comment|/* PBI master control register */
DECL|macro|PCA200E_CTRL_DIS_CACHE_RD
mdefine_line|#define PCA200E_CTRL_DIS_CACHE_RD      (1&lt;&lt;0)    /* disable cache-line reads                         */
DECL|macro|PCA200E_CTRL_DIS_WRT_INVAL
mdefine_line|#define PCA200E_CTRL_DIS_WRT_INVAL     (1&lt;&lt;1)    /* disable writes and invalidates                   */
DECL|macro|PCA200E_CTRL_2_CACHE_WRT_INVAL
mdefine_line|#define PCA200E_CTRL_2_CACHE_WRT_INVAL (1&lt;&lt;2)    /* require 2 cache-lines for writes and invalidates */
DECL|macro|PCA200E_CTRL_IGN_LAT_TIMER
mdefine_line|#define PCA200E_CTRL_IGN_LAT_TIMER     (1&lt;&lt;3)    /* ignore the latency timer                         */
DECL|macro|PCA200E_CTRL_ENA_CONT_REQ_MODE
mdefine_line|#define PCA200E_CTRL_ENA_CONT_REQ_MODE (1&lt;&lt;4)    /* enable continuous request mode                   */
DECL|macro|PCA200E_CTRL_LARGE_PCI_BURSTS
mdefine_line|#define PCA200E_CTRL_LARGE_PCI_BURSTS  (1&lt;&lt;5)    /* force large PCI bus bursts                       */
DECL|macro|PCA200E_CTRL_CONVERT_ENDIAN
mdefine_line|#define PCA200E_CTRL_CONVERT_ENDIAN    (1&lt;&lt;6)    /* convert endianess of slave RAM accesses          */
DECL|macro|SBA200E_PROM_NAME
mdefine_line|#define SBA200E_PROM_NAME  &quot;FORE,sba-200e&quot;    /* device name in openprom tree */
multiline_comment|/* size of SBA-200E registers */
DECL|macro|SBA200E_HCR_LENGTH
mdefine_line|#define SBA200E_HCR_LENGTH        4
DECL|macro|SBA200E_BSR_LENGTH
mdefine_line|#define SBA200E_BSR_LENGTH        4
DECL|macro|SBA200E_ISR_LENGTH
mdefine_line|#define SBA200E_ISR_LENGTH        4
DECL|macro|SBA200E_RAM_LENGTH
mdefine_line|#define SBA200E_RAM_LENGTH  0x40000
multiline_comment|/* SBA-200E SBUS burst transfer size register */
DECL|macro|SBA200E_BSR_BURST4
mdefine_line|#define SBA200E_BSR_BURST4   0x04
DECL|macro|SBA200E_BSR_BURST8
mdefine_line|#define SBA200E_BSR_BURST8   0x08
DECL|macro|SBA200E_BSR_BURST16
mdefine_line|#define SBA200E_BSR_BURST16  0x10
multiline_comment|/* SBA-200E host control register */
DECL|macro|SBA200E_HCR_RESET
mdefine_line|#define SBA200E_HCR_RESET        (1&lt;&lt;0)    /* read / write (sticky) */
DECL|macro|SBA200E_HCR_HOLD_LOCK
mdefine_line|#define SBA200E_HCR_HOLD_LOCK    (1&lt;&lt;1)    /* read / write (sticky) */
DECL|macro|SBA200E_HCR_I960FAIL
mdefine_line|#define SBA200E_HCR_I960FAIL     (1&lt;&lt;2)    /* read                  */
DECL|macro|SBA200E_HCR_I960SETINTR
mdefine_line|#define SBA200E_HCR_I960SETINTR  (1&lt;&lt;2)    /* write                 */
DECL|macro|SBA200E_HCR_OUTFULL
mdefine_line|#define SBA200E_HCR_OUTFULL      (1&lt;&lt;3)    /* read                  */
DECL|macro|SBA200E_HCR_INTR_CLR
mdefine_line|#define SBA200E_HCR_INTR_CLR     (1&lt;&lt;3)    /* write                 */
DECL|macro|SBA200E_HCR_INTR_ENA
mdefine_line|#define SBA200E_HCR_INTR_ENA     (1&lt;&lt;4)    /* read / write (sticky) */
DECL|macro|SBA200E_HCR_ESPHOLD
mdefine_line|#define SBA200E_HCR_ESPHOLD      (1&lt;&lt;5)    /* read                  */
DECL|macro|SBA200E_HCR_INFULL
mdefine_line|#define SBA200E_HCR_INFULL       (1&lt;&lt;6)    /* read                  */
DECL|macro|SBA200E_HCR_TESTMODE
mdefine_line|#define SBA200E_HCR_TESTMODE     (1&lt;&lt;7)    /* read                  */
DECL|macro|SBA200E_HCR_INTR_REQ
mdefine_line|#define SBA200E_HCR_INTR_REQ     (1&lt;&lt;8)    /* read                  */
DECL|macro|SBA200E_HCR_STICKY
mdefine_line|#define SBA200E_HCR_STICKY       (SBA200E_HCR_RESET | SBA200E_HCR_HOLD_LOCK | SBA200E_HCR_INTR_ENA)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _FORE200E_H */
eof

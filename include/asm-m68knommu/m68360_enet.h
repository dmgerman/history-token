multiline_comment|/***********************************&n; * $Id: m68360_enet.h,v 1.1 2002/03/02 15:01:07 gerg Exp $&n; ***********************************&n; *&n; ***************************************&n; * Definitions for the ETHERNET controllers&n; ***************************************&n; */
macro_line|#ifndef __ETHER_H
DECL|macro|__ETHER_H
mdefine_line|#define __ETHER_H
macro_line|#include &quot;quicc_simple.h&quot;
multiline_comment|/*&n; * transmit BD&squot;s&n; */
DECL|macro|T_R
mdefine_line|#define T_R     0x8000          /* ready bit */
DECL|macro|E_T_PAD
mdefine_line|#define E_T_PAD 0x4000          /* short frame padding */
DECL|macro|T_W
mdefine_line|#define T_W     0x2000          /* wrap bit */
DECL|macro|T_I
mdefine_line|#define T_I     0x1000          /* interrupt on completion */
DECL|macro|T_L
mdefine_line|#define T_L     0x0800          /* last in frame */
DECL|macro|T_TC
mdefine_line|#define T_TC    0x0400          /* transmit CRC (when last) */
DECL|macro|T_DEF
mdefine_line|#define T_DEF   0x0200          /* defer indication */
DECL|macro|T_HB
mdefine_line|#define T_HB    0x0100          /* heartbeat */
DECL|macro|T_LC
mdefine_line|#define T_LC    0x0080          /* error: late collision */
DECL|macro|T_RL
mdefine_line|#define T_RL    0x0040          /* error: retransmission limit */
DECL|macro|T_RC
mdefine_line|#define T_RC    0x003c          /* retry count */
DECL|macro|T_UN
mdefine_line|#define T_UN    0x0002          /* error: underrun */
DECL|macro|T_CSL
mdefine_line|#define T_CSL   0x0001          /* carier sense lost */
DECL|macro|T_ERROR
mdefine_line|#define T_ERROR (T_HB | T_LC | T_RL | T_UN | T_CSL)
multiline_comment|/*&n; * receive BD&squot;s&n; */
DECL|macro|R_E
mdefine_line|#define R_E     0x8000          /* buffer empty */
DECL|macro|R_W
mdefine_line|#define R_W     0x2000          /* wrap bit */
DECL|macro|R_I
mdefine_line|#define R_I     0x1000          /* interrupt on reception */
DECL|macro|R_L
mdefine_line|#define R_L     0x0800          /* last BD in frame */
DECL|macro|R_F
mdefine_line|#define R_F     0x0400          /* first BD in frame */
DECL|macro|R_M
mdefine_line|#define R_M     0x0100          /* received because of promisc. mode */
DECL|macro|R_LG
mdefine_line|#define R_LG    0x0020          /* frame too long */
DECL|macro|R_NO
mdefine_line|#define R_NO    0x0010          /* non-octet aligned */
DECL|macro|R_SH
mdefine_line|#define R_SH    0x0008          /* short frame */
DECL|macro|R_CR
mdefine_line|#define R_CR    0x0004          /* receive CRC error */
DECL|macro|R_OV
mdefine_line|#define R_OV    0x0002          /* receive overrun */
DECL|macro|R_CL
mdefine_line|#define R_CL    0x0001          /* collision */
DECL|macro|ETHER_R_ERROR
mdefine_line|#define ETHER_R_ERROR (R_LG | R_NO | R_SH | R_CR | R_OV | R_CL)
multiline_comment|/*&n; * ethernet interrupts&n; */
DECL|macro|ETHERNET_GRA
mdefine_line|#define ETHERNET_GRA    0x0080  /* graceful stop complete */
DECL|macro|ETHERNET_TXE
mdefine_line|#define ETHERNET_TXE    0x0010  /* transmit error         */
DECL|macro|ETHERNET_RXF
mdefine_line|#define ETHERNET_RXF    0x0008  /* receive frame          */
DECL|macro|ETHERNET_BSY
mdefine_line|#define ETHERNET_BSY    0x0004  /* busy condition         */
DECL|macro|ETHERNET_TXB
mdefine_line|#define ETHERNET_TXB    0x0002  /* transmit buffer        */
DECL|macro|ETHERNET_RXB
mdefine_line|#define ETHERNET_RXB    0x0001  /* receive buffer         */
multiline_comment|/*&n; * ethernet protocol specific mode register (PSMR)&n; */
DECL|macro|ETHER_HBC
mdefine_line|#define ETHER_HBC       0x8000    /* heartbeat checking      */
DECL|macro|ETHER_FC
mdefine_line|#define ETHER_FC        0x4000    /* force collision         */
DECL|macro|ETHER_RSH
mdefine_line|#define ETHER_RSH       0x2000    /* receive short frames    */
DECL|macro|ETHER_IAM
mdefine_line|#define ETHER_IAM       0x1000    /* individual address mode */
DECL|macro|ETHER_CRC_32
mdefine_line|#define ETHER_CRC_32    (0x2&lt;&lt;10) /* Enable CRC              */
DECL|macro|ETHER_PRO
mdefine_line|#define ETHER_PRO       0x0200    /* promiscuous             */
DECL|macro|ETHER_BRO
mdefine_line|#define ETHER_BRO       0x0100    /* broadcast address       */
DECL|macro|ETHER_SBT
mdefine_line|#define ETHER_SBT       0x0080    /* stop backoff timer      */
DECL|macro|ETHER_LPB
mdefine_line|#define ETHER_LPB       0x0040    /* Loop Back Mode          */
DECL|macro|ETHER_SIP
mdefine_line|#define ETHER_SIP       0x0020    /* sample input pins       */
DECL|macro|ETHER_LCW
mdefine_line|#define ETHER_LCW       0x0010    /* late collision window   */
DECL|macro|ETHER_NIB_13
mdefine_line|#define ETHER_NIB_13    (0x0&lt;&lt;1)  /* # of ignored bits 13    */
DECL|macro|ETHER_NIB_14
mdefine_line|#define ETHER_NIB_14    (0x1&lt;&lt;1)  /* # of ignored bits 14    */
DECL|macro|ETHER_NIB_15
mdefine_line|#define ETHER_NIB_15    (0x2&lt;&lt;1)  /* # of ignored bits 15    */
DECL|macro|ETHER_NIB_16
mdefine_line|#define ETHER_NIB_16    (0x3&lt;&lt;1)  /* # of ignored bits 16    */
DECL|macro|ETHER_NIB_21
mdefine_line|#define ETHER_NIB_21    (0x4&lt;&lt;1)  /* # of ignored bits 21    */
DECL|macro|ETHER_NIB_22
mdefine_line|#define ETHER_NIB_22    (0x5&lt;&lt;1)  /* # of ignored bits 22    */
DECL|macro|ETHER_NIB_23
mdefine_line|#define ETHER_NIB_23    (0x6&lt;&lt;1)  /* # of ignored bits 23    */
DECL|macro|ETHER_NIB_24
mdefine_line|#define ETHER_NIB_24    (0x7&lt;&lt;1)  /* # of ignored bits 24    */
multiline_comment|/*&n; * ethernet specific parameters&n; */
DECL|macro|CRC_WORD
mdefine_line|#define CRC_WORD 4          /* Length in bytes of CRC */               
DECL|macro|C_PRES
mdefine_line|#define C_PRES   0xffffffff /* preform 32 bit CRC */
DECL|macro|C_MASK
mdefine_line|#define C_MASK   0xdebb20e3 /* comply with 32 bit CRC */       
DECL|macro|CRCEC
mdefine_line|#define CRCEC    0x00000000
DECL|macro|ALEC
mdefine_line|#define ALEC     0x00000000
DECL|macro|DISFC
mdefine_line|#define DISFC    0x00000000
DECL|macro|PADS
mdefine_line|#define PADS     0x00000000
DECL|macro|RET_LIM
mdefine_line|#define RET_LIM  0x000f     /* retry 15 times to send a frame before interrupt */
DECL|macro|ETH_MFLR
mdefine_line|#define ETH_MFLR 0x05ee     /* 1518 max frame size */
DECL|macro|MINFLR
mdefine_line|#define MINFLR   0x0040     /* Minimum frame size 64 */
DECL|macro|MAXD1
mdefine_line|#define MAXD1    0x05ee     /* Max dma count 1518 */
DECL|macro|MAXD2
mdefine_line|#define MAXD2    0x05ee
DECL|macro|GADDR1
mdefine_line|#define GADDR1   0x00000000 /* Clear group address */  
DECL|macro|GADDR2
mdefine_line|#define GADDR2   0x00000000
DECL|macro|GADDR3
mdefine_line|#define GADDR3   0x00000000    
DECL|macro|GADDR4
mdefine_line|#define GADDR4   0x00000000    
DECL|macro|P_PER
mdefine_line|#define P_PER    0x00000000 /*not used */              
DECL|macro|IADDR1
mdefine_line|#define IADDR1   0x00000000 /* Individual hash table not used */       
DECL|macro|IADDR2
mdefine_line|#define IADDR2   0x00000000
DECL|macro|IADDR3
mdefine_line|#define IADDR3   0x00000000    
DECL|macro|IADDR4
mdefine_line|#define IADDR4   0x00000000            
DECL|macro|TADDR_H
mdefine_line|#define TADDR_H  0x00000000 /* clear this regs */              
DECL|macro|TADDR_M
mdefine_line|#define TADDR_M  0x00000000            
DECL|macro|TADDR_L
mdefine_line|#define TADDR_L  0x00000000            
multiline_comment|/*       SCC Parameter Ram */
DECL|macro|RFCR
mdefine_line|#define RFCR    0x18 /* normal operation */
DECL|macro|TFCR
mdefine_line|#define TFCR    0x18 /* normal operation */
DECL|macro|E_MRBLR
mdefine_line|#define E_MRBLR 1518 /* Max ethernet frame length */
multiline_comment|/*&n; * ethernet specific structure&n; */
r_typedef
r_union
(brace
DECL|member|b
r_int
r_char
id|b
(braket
l_int|6
)braket
suffix:semicolon
r_struct
(brace
DECL|member|high
r_int
r_int
id|high
suffix:semicolon
DECL|member|middl
r_int
r_int
id|middl
suffix:semicolon
DECL|member|low
r_int
r_int
id|low
suffix:semicolon
DECL|member|w
)brace
id|w
suffix:semicolon
DECL|typedef|ETHER_ADDR
)brace
id|ETHER_ADDR
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|max_frame_length
r_int
id|max_frame_length
suffix:semicolon
DECL|member|promisc_mode
r_int
id|promisc_mode
suffix:semicolon
DECL|member|reject_broadcast
r_int
id|reject_broadcast
suffix:semicolon
DECL|member|phys_adr
id|ETHER_ADDR
id|phys_adr
suffix:semicolon
DECL|typedef|ETHER_SPECIFIC
)brace
id|ETHER_SPECIFIC
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|dst_addr
id|ETHER_ADDR
id|dst_addr
suffix:semicolon
DECL|member|src_addr
id|ETHER_ADDR
id|src_addr
suffix:semicolon
DECL|member|type_or_len
r_int
r_int
id|type_or_len
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|ETHER_FRAME
)brace
id|ETHER_FRAME
suffix:semicolon
DECL|macro|MAX_DATALEN
mdefine_line|#define MAX_DATALEN 1500
r_typedef
r_struct
(brace
DECL|member|dst_addr
id|ETHER_ADDR
id|dst_addr
suffix:semicolon
DECL|member|src_addr
id|ETHER_ADDR
id|src_addr
suffix:semicolon
DECL|member|type_or_len
r_int
r_int
id|type_or_len
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
id|MAX_DATALEN
)braket
suffix:semicolon
DECL|member|fcs
r_int
r_char
id|fcs
(braket
id|CRC_WORD
)braket
suffix:semicolon
DECL|typedef|ETHER_MAX_FRAME
)brace
id|ETHER_MAX_FRAME
suffix:semicolon
multiline_comment|/*&n; * Internal ethernet function prototypes&n; */
r_void
id|ether_interrupt
c_func
(paren
r_int
id|scc_num
)paren
suffix:semicolon
multiline_comment|/* mleslie: debug */
multiline_comment|/* static void ethernet_rx_internal(int scc_num); */
multiline_comment|/* static void ethernet_tx_internal(int scc_num); */
multiline_comment|/*&n; * User callable routines prototypes (ethernet specific)&n; */
r_void
id|ethernet_init
c_func
(paren
r_int
id|scc_number
comma
id|alloc_routine
op_star
id|alloc_buffer
comma
id|free_routine
op_star
id|free_buffer
comma
id|store_rx_buffer_routine
op_star
id|store_rx_buffer
comma
id|handle_tx_error_routine
op_star
id|handle_tx_error
comma
id|handle_rx_error_routine
op_star
id|handle_rx_error
comma
id|handle_lost_error_routine
op_star
id|handle_lost_error
comma
id|ETHER_SPECIFIC
op_star
id|ether_spec
)paren
suffix:semicolon
r_int
id|ethernet_tx
c_func
(paren
r_int
id|scc_number
comma
r_void
op_star
id|buf
comma
r_int
id|length
)paren
suffix:semicolon
macro_line|#endif
eof

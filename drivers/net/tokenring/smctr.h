multiline_comment|/* smctr.h: SMC Token Ring driver header for Linux&n; *&n; * Authors:&n; *  - Jay Schulist &lt;jschlst@samba.org&gt;&n; */
macro_line|#ifndef __LINUX_SMCTR_H
DECL|macro|__LINUX_SMCTR_H
mdefine_line|#define __LINUX_SMCTR_H
macro_line|#ifdef __KERNEL__
DECL|macro|MAX_TX_QUEUE
mdefine_line|#define MAX_TX_QUEUE 10
DECL|macro|SMC_HEADER_SIZE
mdefine_line|#define SMC_HEADER_SIZE 14
DECL|macro|SMC_PAGE_OFFSET
mdefine_line|#define SMC_PAGE_OFFSET(X)          (((unsigned long)(X) - tp-&gt;ram_access) &amp; tp-&gt;page_offset_mask)
DECL|macro|INIT
mdefine_line|#define INIT            0x0D
DECL|macro|RQ_ATTCH
mdefine_line|#define RQ_ATTCH        0x10
DECL|macro|RQ_STATE
mdefine_line|#define RQ_STATE        0x0F
DECL|macro|RQ_ADDR
mdefine_line|#define RQ_ADDR         0x0E
DECL|macro|CHG_PARM
mdefine_line|#define CHG_PARM        0x0C
DECL|macro|RSP
mdefine_line|#define RSP             0x00
DECL|macro|TX_FORWARD
mdefine_line|#define TX_FORWARD      0x09
DECL|macro|AC_FC_DAT
mdefine_line|#define AC_FC_DAT&t;((3&lt;&lt;13) | 1)
DECL|macro|DAT
mdefine_line|#define      DAT             0x07
DECL|macro|RPT_NEW_MON
mdefine_line|#define RPT_NEW_MON     0x25
DECL|macro|RPT_SUA_CHG
mdefine_line|#define RPT_SUA_CHG     0x26
DECL|macro|RPT_ACTIVE_ERR
mdefine_line|#define RPT_ACTIVE_ERR  0x28
DECL|macro|RPT_NN_INCMP
mdefine_line|#define RPT_NN_INCMP    0x27
DECL|macro|RPT_ERROR
mdefine_line|#define RPT_ERROR       0x29
DECL|macro|RQ_INIT
mdefine_line|#define RQ_INIT         0x20
DECL|macro|RPT_ATTCH
mdefine_line|#define RPT_ATTCH       0x24
DECL|macro|RPT_STATE
mdefine_line|#define RPT_STATE       0x23
DECL|macro|RPT_ADDR
mdefine_line|#define RPT_ADDR        0x22
DECL|macro|POSITIVE_ACK
mdefine_line|#define POSITIVE_ACK                    0x0001
DECL|macro|A_FRAME_WAS_FORWARDED
mdefine_line|#define A_FRAME_WAS_FORWARDED           0x8888
DECL|macro|GROUP_ADDRESS
mdefine_line|#define      GROUP_ADDRESS                   0x2B
DECL|macro|PHYSICAL_DROP
mdefine_line|#define      PHYSICAL_DROP                   0x0B
DECL|macro|AUTHORIZED_ACCESS_PRIORITY
mdefine_line|#define      AUTHORIZED_ACCESS_PRIORITY      0x07
DECL|macro|AUTHORIZED_FUNCTION_CLASS
mdefine_line|#define      AUTHORIZED_FUNCTION_CLASS       0x06
DECL|macro|FUNCTIONAL_ADDRESS
mdefine_line|#define      FUNCTIONAL_ADDRESS              0x2C
DECL|macro|RING_STATION_STATUS
mdefine_line|#define      RING_STATION_STATUS             0x29
DECL|macro|TRANSMIT_STATUS_CODE
mdefine_line|#define      TRANSMIT_STATUS_CODE            0x2A
DECL|macro|IBM_PASS_SOURCE_ADDR
mdefine_line|#define      IBM_PASS_SOURCE_ADDR    0x01
DECL|macro|AC_FC_RPT_TX_FORWARD
mdefine_line|#define      AC_FC_RPT_TX_FORWARD            ((0&lt;&lt;13) | 0)
DECL|macro|AC_FC_RPT_STATE
mdefine_line|#define      AC_FC_RPT_STATE                 ((0&lt;&lt;13) | 0)
DECL|macro|AC_FC_RPT_ADDR
mdefine_line|#define      AC_FC_RPT_ADDR                  ((0&lt;&lt;13) | 0)
DECL|macro|CORRELATOR
mdefine_line|#define      CORRELATOR                      0x09
DECL|macro|POSITIVE_ACK
mdefine_line|#define POSITIVE_ACK                    0x0001          /*             */
DECL|macro|E_MAC_DATA_INCOMPLETE
mdefine_line|#define E_MAC_DATA_INCOMPLETE           0x8001          /* not used    */
DECL|macro|E_VECTOR_LENGTH_ERROR
mdefine_line|#define E_VECTOR_LENGTH_ERROR           0x8002          /*             */
DECL|macro|E_UNRECOGNIZED_VECTOR_ID
mdefine_line|#define E_UNRECOGNIZED_VECTOR_ID        0x8003          /*             */
DECL|macro|E_INAPPROPRIATE_SOURCE_CLASS
mdefine_line|#define E_INAPPROPRIATE_SOURCE_CLASS    0x8004          /*             */
DECL|macro|E_SUB_VECTOR_LENGTH_ERROR
mdefine_line|#define E_SUB_VECTOR_LENGTH_ERROR       0x8005          /*             */
DECL|macro|E_TRANSMIT_FORWARD_INVALID
mdefine_line|#define E_TRANSMIT_FORWARD_INVALID      0x8006          /* def. by IBM */
DECL|macro|E_MISSING_SUB_VECTOR
mdefine_line|#define E_MISSING_SUB_VECTOR            0x8007          /*             */
DECL|macro|E_SUB_VECTOR_UNKNOWN
mdefine_line|#define E_SUB_VECTOR_UNKNOWN            0x8008          /*             */
DECL|macro|E_MAC_HEADER_TOO_LONG
mdefine_line|#define E_MAC_HEADER_TOO_LONG           0x8009          /*             */
DECL|macro|E_FUNCTION_DISABLED
mdefine_line|#define E_FUNCTION_DISABLED             0x800A          /* not used    */
DECL|macro|A_FRAME_WAS_FORWARDED
mdefine_line|#define A_FRAME_WAS_FORWARDED           0x8888          /* used by send_TX_FORWARD */
DECL|macro|UPSTREAM_NEIGHBOR_ADDRESS
mdefine_line|#define UPSTREAM_NEIGHBOR_ADDRESS       0x02
DECL|macro|LOCAL_RING_NUMBER
mdefine_line|#define LOCAL_RING_NUMBER               0x03
DECL|macro|ASSIGN_PHYSICAL_DROP
mdefine_line|#define ASSIGN_PHYSICAL_DROP            0x04
DECL|macro|ERROR_TIMER_VALUE
mdefine_line|#define ERROR_TIMER_VALUE               0x05
DECL|macro|AUTHORIZED_FUNCTION_CLASS
mdefine_line|#define AUTHORIZED_FUNCTION_CLASS       0x06
DECL|macro|AUTHORIZED_ACCESS_PRIORITY
mdefine_line|#define AUTHORIZED_ACCESS_PRIORITY      0x07
DECL|macro|CORRELATOR
mdefine_line|#define CORRELATOR                      0x09
DECL|macro|PHYSICAL_DROP
mdefine_line|#define PHYSICAL_DROP                   0x0B
DECL|macro|RESPONSE_CODE
mdefine_line|#define RESPONSE_CODE                   0x20
DECL|macro|ADDRESS_MODIFER
mdefine_line|#define ADDRESS_MODIFER                 0x21
DECL|macro|PRODUCT_INSTANCE_ID
mdefine_line|#define PRODUCT_INSTANCE_ID             0x22
DECL|macro|RING_STATION_VERSION_NUMBER
mdefine_line|#define RING_STATION_VERSION_NUMBER     0x23
DECL|macro|WRAP_DATA
mdefine_line|#define WRAP_DATA                       0x26
DECL|macro|FRAME_FORWARD
mdefine_line|#define FRAME_FORWARD                   0x27
DECL|macro|STATION_IDENTIFER
mdefine_line|#define STATION_IDENTIFER               0x28
DECL|macro|RING_STATION_STATUS
mdefine_line|#define RING_STATION_STATUS             0x29
DECL|macro|TRANSMIT_STATUS_CODE
mdefine_line|#define TRANSMIT_STATUS_CODE            0x2A
DECL|macro|GROUP_ADDRESS
mdefine_line|#define GROUP_ADDRESS                   0x2B
DECL|macro|FUNCTIONAL_ADDRESS
mdefine_line|#define FUNCTIONAL_ADDRESS              0x2C
DECL|macro|F_NO_SUB_VECTORS_FOUND
mdefine_line|#define F_NO_SUB_VECTORS_FOUND                  0x0000
DECL|macro|F_UPSTREAM_NEIGHBOR_ADDRESS
mdefine_line|#define F_UPSTREAM_NEIGHBOR_ADDRESS             0x0001
DECL|macro|F_LOCAL_RING_NUMBER
mdefine_line|#define F_LOCAL_RING_NUMBER                     0x0002
DECL|macro|F_ASSIGN_PHYSICAL_DROP
mdefine_line|#define F_ASSIGN_PHYSICAL_DROP                  0x0004
DECL|macro|F_ERROR_TIMER_VALUE
mdefine_line|#define F_ERROR_TIMER_VALUE                     0x0008
DECL|macro|F_AUTHORIZED_FUNCTION_CLASS
mdefine_line|#define F_AUTHORIZED_FUNCTION_CLASS             0x0010
DECL|macro|F_AUTHORIZED_ACCESS_PRIORITY
mdefine_line|#define F_AUTHORIZED_ACCESS_PRIORITY            0x0020
DECL|macro|F_CORRELATOR
mdefine_line|#define F_CORRELATOR                            0x0040
DECL|macro|F_PHYSICAL_DROP
mdefine_line|#define F_PHYSICAL_DROP                         0x0080
DECL|macro|F_RESPONSE_CODE
mdefine_line|#define F_RESPONSE_CODE                         0x0100
DECL|macro|F_PRODUCT_INSTANCE_ID
mdefine_line|#define F_PRODUCT_INSTANCE_ID                   0x0200
DECL|macro|F_RING_STATION_VERSION_NUMBER
mdefine_line|#define F_RING_STATION_VERSION_NUMBER           0x0400
DECL|macro|F_STATION_IDENTIFER
mdefine_line|#define F_STATION_IDENTIFER                     0x0800
DECL|macro|F_RING_STATION_STATUS
mdefine_line|#define F_RING_STATION_STATUS                   0x1000
DECL|macro|F_GROUP_ADDRESS
mdefine_line|#define F_GROUP_ADDRESS                         0x2000
DECL|macro|F_FUNCTIONAL_ADDRESS
mdefine_line|#define F_FUNCTIONAL_ADDRESS                    0x4000
DECL|macro|F_FRAME_FORWARD
mdefine_line|#define F_FRAME_FORWARD                         0x8000
DECL|macro|R_INIT
mdefine_line|#define R_INIT                                  0x00
DECL|macro|R_RQ_ATTCH_STATE_ADDR
mdefine_line|#define R_RQ_ATTCH_STATE_ADDR                   0x00
DECL|macro|R_CHG_PARM
mdefine_line|#define R_CHG_PARM                              0x00
DECL|macro|R_TX_FORWARD
mdefine_line|#define R_TX_FORWARD                            F_FRAME_FORWARD
DECL|macro|UPSTREAM_NEIGHBOR_ADDRESS
mdefine_line|#define      UPSTREAM_NEIGHBOR_ADDRESS       0x02
DECL|macro|ADDRESS_MODIFER
mdefine_line|#define      ADDRESS_MODIFER                 0x21
DECL|macro|RING_STATION_VERSION_NUMBER
mdefine_line|#define      RING_STATION_VERSION_NUMBER     0x23
DECL|macro|PRODUCT_INSTANCE_ID
mdefine_line|#define      PRODUCT_INSTANCE_ID             0x22
DECL|macro|RPT_TX_FORWARD
mdefine_line|#define      RPT_TX_FORWARD  0x2A
DECL|macro|AC_FC_INIT
mdefine_line|#define AC_FC_INIT                      (3&lt;&lt;13) | 0 /*                     */
DECL|macro|AC_FC_RQ_INIT
mdefine_line|#define AC_FC_RQ_INIT                   ((3&lt;&lt;13) | 0) /*                     */
DECL|macro|AC_FC_RQ_ATTCH
mdefine_line|#define AC_FC_RQ_ATTCH                  (3&lt;&lt;13) | 0 /* DC = SC of rx frame */
DECL|macro|AC_FC_RQ_STATE
mdefine_line|#define AC_FC_RQ_STATE                  (3&lt;&lt;13) | 0 /* DC = SC of rx frame */
DECL|macro|AC_FC_RQ_ADDR
mdefine_line|#define AC_FC_RQ_ADDR                   (3&lt;&lt;13) | 0 /* DC = SC of rx frame */
DECL|macro|AC_FC_CHG_PARM
mdefine_line|#define AC_FC_CHG_PARM                  (3&lt;&lt;13) | 0 /*                     */
DECL|macro|AC_FC_RSP
mdefine_line|#define AC_FC_RSP                       (0&lt;&lt;13) | 0 /* DC = SC of rx frame */
DECL|macro|AC_FC_RPT_ATTCH
mdefine_line|#define AC_FC_RPT_ATTCH                 (0&lt;&lt;13) | 0
DECL|macro|S_UPSTREAM_NEIGHBOR_ADDRESS
mdefine_line|#define S_UPSTREAM_NEIGHBOR_ADDRESS               6 + 2
DECL|macro|S_LOCAL_RING_NUMBER
mdefine_line|#define S_LOCAL_RING_NUMBER                       2 + 2
DECL|macro|S_ASSIGN_PHYSICAL_DROP
mdefine_line|#define S_ASSIGN_PHYSICAL_DROP                    4 + 2
DECL|macro|S_ERROR_TIMER_VALUE
mdefine_line|#define S_ERROR_TIMER_VALUE                       2 + 2
DECL|macro|S_AUTHORIZED_FUNCTION_CLASS
mdefine_line|#define S_AUTHORIZED_FUNCTION_CLASS               2 + 2
DECL|macro|S_AUTHORIZED_ACCESS_PRIORITY
mdefine_line|#define S_AUTHORIZED_ACCESS_PRIORITY              2 + 2
DECL|macro|S_CORRELATOR
mdefine_line|#define S_CORRELATOR                              2 + 2
DECL|macro|S_PHYSICAL_DROP
mdefine_line|#define S_PHYSICAL_DROP                           4 + 2
DECL|macro|S_RESPONSE_CODE
mdefine_line|#define S_RESPONSE_CODE                           4 + 2
DECL|macro|S_ADDRESS_MODIFER
mdefine_line|#define S_ADDRESS_MODIFER                         2 + 2
DECL|macro|S_PRODUCT_INSTANCE_ID
mdefine_line|#define S_PRODUCT_INSTANCE_ID                    18 + 2
DECL|macro|S_RING_STATION_VERSION_NUMBER
mdefine_line|#define S_RING_STATION_VERSION_NUMBER            10 + 2
DECL|macro|S_STATION_IDENTIFER
mdefine_line|#define S_STATION_IDENTIFER                       6 + 2
DECL|macro|S_RING_STATION_STATUS
mdefine_line|#define S_RING_STATION_STATUS                     6 + 2
DECL|macro|S_GROUP_ADDRESS
mdefine_line|#define S_GROUP_ADDRESS                           4 + 2
DECL|macro|S_FUNCTIONAL_ADDRESS
mdefine_line|#define S_FUNCTIONAL_ADDRESS                      4 + 2
DECL|macro|S_FRAME_FORWARD
mdefine_line|#define S_FRAME_FORWARD                         252 + 2
DECL|macro|S_TRANSMIT_STATUS_CODE
mdefine_line|#define S_TRANSMIT_STATUS_CODE                    2 + 2
DECL|macro|ISB_IMC_RES0
mdefine_line|#define ISB_IMC_RES0                    0x0000  /* */
DECL|macro|ISB_IMC_MAC_TYPE_3
mdefine_line|#define ISB_IMC_MAC_TYPE_3              0x0001  /* MAC_ARC_INDICATE */
DECL|macro|ISB_IMC_MAC_ERROR_COUNTERS
mdefine_line|#define ISB_IMC_MAC_ERROR_COUNTERS      0x0002  /* */
DECL|macro|ISB_IMC_RES1
mdefine_line|#define ISB_IMC_RES1                    0x0003  /* */
DECL|macro|ISB_IMC_MAC_TYPE_2
mdefine_line|#define ISB_IMC_MAC_TYPE_2              0x0004  /* QUE_MAC_INDICATE */
DECL|macro|ISB_IMC_TX_FRAME
mdefine_line|#define ISB_IMC_TX_FRAME                0x0005  /* */
DECL|macro|ISB_IMC_END_OF_TX_QUEUE
mdefine_line|#define ISB_IMC_END_OF_TX_QUEUE         0x0006  /* */
DECL|macro|ISB_IMC_NON_MAC_RX_RESOURCE
mdefine_line|#define ISB_IMC_NON_MAC_RX_RESOURCE     0x0007  /* */
DECL|macro|ISB_IMC_MAC_RX_RESOURCE
mdefine_line|#define ISB_IMC_MAC_RX_RESOURCE         0x0008  /* */
DECL|macro|ISB_IMC_NON_MAC_RX_FRAME
mdefine_line|#define ISB_IMC_NON_MAC_RX_FRAME        0x0009  /* */
DECL|macro|ISB_IMC_MAC_RX_FRAME
mdefine_line|#define ISB_IMC_MAC_RX_FRAME            0x000A  /* */
DECL|macro|ISB_IMC_TRC_FIFO_STATUS
mdefine_line|#define ISB_IMC_TRC_FIFO_STATUS         0x000B  /* */
DECL|macro|ISB_IMC_COMMAND_STATUS
mdefine_line|#define ISB_IMC_COMMAND_STATUS          0x000C  /* */
DECL|macro|ISB_IMC_MAC_TYPE_1
mdefine_line|#define ISB_IMC_MAC_TYPE_1              0x000D  /* Self Removed */
DECL|macro|ISB_IMC_TRC_INTRNL_TST_STATUS
mdefine_line|#define ISB_IMC_TRC_INTRNL_TST_STATUS   0x000E  /* */
DECL|macro|ISB_IMC_RES2
mdefine_line|#define ISB_IMC_RES2                    0x000F  /* */
DECL|macro|NON_MAC_RX_RESOURCE_BW
mdefine_line|#define NON_MAC_RX_RESOURCE_BW          0x10    /* shifted right 8 bits */
DECL|macro|NON_MAC_RX_RESOURCE_FW
mdefine_line|#define NON_MAC_RX_RESOURCE_FW          0x20    /* shifted right 8 bits */
DECL|macro|NON_MAC_RX_RESOURCE_BE
mdefine_line|#define NON_MAC_RX_RESOURCE_BE          0x40    /* shifted right 8 bits */
DECL|macro|NON_MAC_RX_RESOURCE_FE
mdefine_line|#define NON_MAC_RX_RESOURCE_FE          0x80    /* shifted right 8 bits */
DECL|macro|RAW_NON_MAC_RX_RESOURCE_BW
mdefine_line|#define RAW_NON_MAC_RX_RESOURCE_BW      0x1000  /* */
DECL|macro|RAW_NON_MAC_RX_RESOURCE_FW
mdefine_line|#define RAW_NON_MAC_RX_RESOURCE_FW      0x2000  /* */
DECL|macro|RAW_NON_MAC_RX_RESOURCE_BE
mdefine_line|#define RAW_NON_MAC_RX_RESOURCE_BE      0x4000  /* */
DECL|macro|RAW_NON_MAC_RX_RESOURCE_FE
mdefine_line|#define RAW_NON_MAC_RX_RESOURCE_FE      0x8000  /* */
DECL|macro|MAC_RX_RESOURCE_BW
mdefine_line|#define MAC_RX_RESOURCE_BW              0x10    /* shifted right 8 bits */
DECL|macro|MAC_RX_RESOURCE_FW
mdefine_line|#define MAC_RX_RESOURCE_FW              0x20    /* shifted right 8 bits */
DECL|macro|MAC_RX_RESOURCE_BE
mdefine_line|#define MAC_RX_RESOURCE_BE              0x40    /* shifted right 8 bits */
DECL|macro|MAC_RX_RESOURCE_FE
mdefine_line|#define MAC_RX_RESOURCE_FE              0x80    /* shifted right 8 bits */
DECL|macro|RAW_MAC_RX_RESOURCE_BW
mdefine_line|#define RAW_MAC_RX_RESOURCE_BW          0x1000  /* */
DECL|macro|RAW_MAC_RX_RESOURCE_FW
mdefine_line|#define RAW_MAC_RX_RESOURCE_FW          0x2000  /* */
DECL|macro|RAW_MAC_RX_RESOURCE_BE
mdefine_line|#define RAW_MAC_RX_RESOURCE_BE          0x4000  /* */
DECL|macro|RAW_MAC_RX_RESOURCE_FE
mdefine_line|#define RAW_MAC_RX_RESOURCE_FE          0x8000  /* */
DECL|macro|TRC_FIFO_STATUS_TX_UNDERRUN
mdefine_line|#define TRC_FIFO_STATUS_TX_UNDERRUN     0x40    /* shifted right 8 bits */
DECL|macro|TRC_FIFO_STATUS_RX_OVERRUN
mdefine_line|#define TRC_FIFO_STATUS_RX_OVERRUN      0x80    /* shifted right 8 bits */
DECL|macro|RAW_TRC_FIFO_STATUS_TX_UNDERRUN
mdefine_line|#define RAW_TRC_FIFO_STATUS_TX_UNDERRUN 0x4000  /* */
DECL|macro|RAW_TRC_FIFO_STATUS_RX_OVERRUN
mdefine_line|#define RAW_TRC_FIFO_STATUS_RX_OVERRUN  0x8000  /* */
DECL|macro|CSR_CLRTINT
mdefine_line|#define       CSR_CLRTINT             0x08
DECL|macro|MSB
mdefine_line|#define MSB(X)                  ((__u8)((__u16) X &gt;&gt; 8))
DECL|macro|LSB
mdefine_line|#define LSB(X)                  ((__u8)((__u16) X &amp;  0xff))
DECL|macro|AC_FC_LOBE_MEDIA_TEST
mdefine_line|#define AC_FC_LOBE_MEDIA_TEST           ((3&lt;&lt;13) | 0)
DECL|macro|S_WRAP_DATA
mdefine_line|#define S_WRAP_DATA                             248 + 2 /* 500 + 2 */
DECL|macro|WRAP_DATA
mdefine_line|#define      WRAP_DATA                       0x26
DECL|macro|LOBE_MEDIA_TEST
mdefine_line|#define LOBE_MEDIA_TEST 0x08
multiline_comment|/* Destination Class (dc) */
DECL|macro|DC_MASK
mdefine_line|#define DC_MASK         0xF0
DECL|macro|DC_RS
mdefine_line|#define DC_RS           0x00
DECL|macro|DC_CRS
mdefine_line|#define DC_CRS          0x40
DECL|macro|DC_RPS
mdefine_line|#define DC_RPS          0x50
DECL|macro|DC_REM
mdefine_line|#define DC_REM          0x60
multiline_comment|/* Source Classes (sc) */
DECL|macro|SC_MASK
mdefine_line|#define SC_MASK         0x0F
DECL|macro|SC_RS
mdefine_line|#define SC_RS           0x00
DECL|macro|SC_CRS
mdefine_line|#define SC_CRS          0x04
DECL|macro|SC_RPS
mdefine_line|#define SC_RPS          0x05
DECL|macro|SC_REM
mdefine_line|#define SC_REM          0x06
DECL|macro|PR
mdefine_line|#define PR&t;&t;0x11
DECL|macro|PR_PAGE_MASK
mdefine_line|#define PR_PAGE_MASK&t;0x0C000
DECL|macro|MICROCHANNEL
mdefine_line|#define MICROCHANNEL&t;0x0008
DECL|macro|INTERFACE_CHIP
mdefine_line|#define INTERFACE_CHIP&t;0x0010
DECL|macro|BOARD_16BIT
mdefine_line|#define BOARD_16BIT&t;0x0040
DECL|macro|PAGED_RAM
mdefine_line|#define PAGED_RAM&t;0x0080
DECL|macro|WD8115TA
mdefine_line|#define WD8115TA&t;(TOKEN_MEDIA | MICROCHANNEL | INTERFACE_CHIP | PAGED_RAM)
DECL|macro|WD8115T
mdefine_line|#define WD8115T&t;&t;(TOKEN_MEDIA | INTERFACE_CHIP | BOARD_16BIT | PAGED_RAM)
DECL|macro|BRD_ID_8316
mdefine_line|#define BRD_ID_8316&t;0x50
DECL|macro|r587_SER
mdefine_line|#define r587_SER&t;0x001
DECL|macro|SER_DIN
mdefine_line|#define SER_DIN&t;&t;0x80
DECL|macro|SER_DOUT
mdefine_line|#define SER_DOUT&t;0x40
DECL|macro|SER_CLK
mdefine_line|#define SER_CLK&t;&t;0x20
DECL|macro|SER_ECS
mdefine_line|#define SER_ECS&t;&t;0x10
DECL|macro|SER_E806
mdefine_line|#define SER_E806&t;0x08
DECL|macro|SER_PNP
mdefine_line|#define SER_PNP&t;&t;0x04
DECL|macro|SER_BIO
mdefine_line|#define SER_BIO&t;&t;0x02
DECL|macro|SER_16B
mdefine_line|#define SER_16B&t;&t;0x01
DECL|macro|r587_IDR
mdefine_line|#define r587_IDR&t;0x004
DECL|macro|IDR_IRQ_MASK
mdefine_line|#define IDR_IRQ_MASK&t;0x0F0
DECL|macro|IDR_DCS_MASK
mdefine_line|#define IDR_DCS_MASK&t;0x007
DECL|macro|IDR_RWS
mdefine_line|#define IDR_RWS&t;&t;0x008
DECL|macro|r587_BIO
mdefine_line|#define r587_BIO&t;0x003
DECL|macro|BIO_ENB
mdefine_line|#define BIO_ENB&t;&t;0x080
DECL|macro|BIO_MASK
mdefine_line|#define BIO_MASK&t;0x03F
DECL|macro|r587_PCR
mdefine_line|#define r587_PCR&t;0x005
DECL|macro|PCR_RAMS
mdefine_line|#define PCR_RAMS&t;0x040
DECL|macro|NUM_ADDR_BITS
mdefine_line|#define NUM_ADDR_BITS&t;8
DECL|macro|ISA_MAX_ADDRESS
mdefine_line|#define ISA_MAX_ADDRESS&t;&t;0x00ffffff
DECL|macro|SMCTR_MAX_ADAPTERS
mdefine_line|#define SMCTR_MAX_ADAPTERS&t;7
DECL|macro|MC_TABLE_ENTRIES
mdefine_line|#define MC_TABLE_ENTRIES      16
DECL|macro|MAXFRAGMENTS
mdefine_line|#define MAXFRAGMENTS          32
DECL|macro|CHIP_REV_MASK
mdefine_line|#define CHIP_REV_MASK         0x3000
DECL|macro|MAX_TX_QS
mdefine_line|#define MAX_TX_QS             8
DECL|macro|NUM_TX_QS_USED
mdefine_line|#define NUM_TX_QS_USED        3
DECL|macro|MAX_RX_QS
mdefine_line|#define MAX_RX_QS             2
DECL|macro|NUM_RX_QS_USED
mdefine_line|#define NUM_RX_QS_USED        2
DECL|macro|INTEL_DATA_FORMAT
mdefine_line|#define INTEL_DATA_FORMAT&t;0x4000
DECL|macro|INTEL_ADDRESS_POINTER_FORMAT
mdefine_line|#define INTEL_ADDRESS_POINTER_FORMAT&t;0x8000
DECL|macro|PAGE_POINTER
mdefine_line|#define PAGE_POINTER(X)&t;&t;((((unsigned long)(X) - tp-&gt;ram_access) &amp; tp-&gt;page_offset_mask) + tp-&gt;ram_access)
DECL|macro|SWAP_WORDS
mdefine_line|#define SWAP_WORDS(X)&t;&t;(((X &amp; 0xFFFF) &lt;&lt; 16) | (X &gt;&gt; 16))
DECL|macro|INTERFACE_CHIP
mdefine_line|#define INTERFACE_CHIP          0x0010          /* Soft Config Adapter */
DECL|macro|ADVANCED_FEATURES
mdefine_line|#define ADVANCED_FEATURES       0x0020          /* Adv. netw. interface features */
DECL|macro|BOARD_16BIT
mdefine_line|#define BOARD_16BIT             0x0040          /* 16 bit capability */
DECL|macro|PAGED_RAM
mdefine_line|#define PAGED_RAM               0x0080          /* Adapter has paged RAM */
DECL|macro|PAGED_ROM
mdefine_line|#define PAGED_ROM               0x0100          /* Adapter has paged ROM */
DECL|macro|RAM_SIZE_UNKNOWN
mdefine_line|#define RAM_SIZE_UNKNOWN        0x0000          /* Unknown RAM size */
DECL|macro|RAM_SIZE_0K
mdefine_line|#define RAM_SIZE_0K             0x0001          /* 0K  RAM */
DECL|macro|RAM_SIZE_8K
mdefine_line|#define RAM_SIZE_8K             0x0002          /* 8k  RAM */
DECL|macro|RAM_SIZE_16K
mdefine_line|#define RAM_SIZE_16K            0x0003          /* 16k RAM */
DECL|macro|RAM_SIZE_32K
mdefine_line|#define RAM_SIZE_32K            0x0004          /* 32k RAM */
DECL|macro|RAM_SIZE_64K
mdefine_line|#define RAM_SIZE_64K            0x0005          /* 64k RAM */
DECL|macro|RAM_SIZE_RESERVED_6
mdefine_line|#define RAM_SIZE_RESERVED_6     0x0006          /* Reserved RAM size */
DECL|macro|RAM_SIZE_RESERVED_7
mdefine_line|#define RAM_SIZE_RESERVED_7     0x0007          /* Reserved RAM size */
DECL|macro|RAM_SIZE_MASK
mdefine_line|#define RAM_SIZE_MASK           0x0007          /* Isolates RAM Size */
DECL|macro|TOKEN_MEDIA
mdefine_line|#define TOKEN_MEDIA           0x0005
DECL|macro|BID_REG_0
mdefine_line|#define BID_REG_0       0x00
DECL|macro|BID_REG_1
mdefine_line|#define BID_REG_1       0x01
DECL|macro|BID_REG_2
mdefine_line|#define BID_REG_2       0x02
DECL|macro|BID_REG_3
mdefine_line|#define BID_REG_3       0x03
DECL|macro|BID_REG_4
mdefine_line|#define BID_REG_4       0x04
DECL|macro|BID_REG_5
mdefine_line|#define BID_REG_5       0x05
DECL|macro|BID_REG_6
mdefine_line|#define BID_REG_6       0x06
DECL|macro|BID_REG_7
mdefine_line|#define BID_REG_7       0x07
DECL|macro|BID_LAR_0
mdefine_line|#define BID_LAR_0       0x08
DECL|macro|BID_LAR_1
mdefine_line|#define BID_LAR_1       0x09
DECL|macro|BID_LAR_2
mdefine_line|#define BID_LAR_2       0x0A
DECL|macro|BID_LAR_3
mdefine_line|#define BID_LAR_3       0x0B
DECL|macro|BID_LAR_4
mdefine_line|#define BID_LAR_4       0x0C
DECL|macro|BID_LAR_5
mdefine_line|#define BID_LAR_5       0x0D
DECL|macro|BID_BOARD_ID_BYTE
mdefine_line|#define BID_BOARD_ID_BYTE       0x0E
DECL|macro|BID_CHCKSM_BYTE
mdefine_line|#define BID_CHCKSM_BYTE         0x0F
DECL|macro|BID_LAR_OFFSET
mdefine_line|#define BID_LAR_OFFSET          0x08  
DECL|macro|BID_MSZ_583_BIT
mdefine_line|#define BID_MSZ_583_BIT         0x08
DECL|macro|BID_SIXTEEN_BIT_BIT
mdefine_line|#define BID_SIXTEEN_BIT_BIT     0x01
DECL|macro|BID_BOARD_REV_MASK
mdefine_line|#define BID_BOARD_REV_MASK      0x1E
DECL|macro|BID_MEDIA_TYPE_BIT
mdefine_line|#define BID_MEDIA_TYPE_BIT      0x01
DECL|macro|BID_SOFT_CONFIG_BIT
mdefine_line|#define BID_SOFT_CONFIG_BIT     0x20
DECL|macro|BID_RAM_SIZE_BIT
mdefine_line|#define BID_RAM_SIZE_BIT        0x40
DECL|macro|BID_BUS_TYPE_BIT
mdefine_line|#define BID_BUS_TYPE_BIT        0x80
DECL|macro|BID_CR
mdefine_line|#define BID_CR          0x10
DECL|macro|BID_TXP
mdefine_line|#define BID_TXP         0x04            /* Transmit Packet Command */
DECL|macro|BID_TCR_DIFF
mdefine_line|#define BID_TCR_DIFF    0x0D    /* Transmit Configuration Register */
DECL|macro|BID_TCR_VAL
mdefine_line|#define BID_TCR_VAL     0x18            /* Value to Test 8390 or 690 */
DECL|macro|BID_PS0
mdefine_line|#define BID_PS0         0x00            /* Register Page Select 0 */
DECL|macro|BID_PS1
mdefine_line|#define BID_PS1         0x40            /* Register Page Select 1 */
DECL|macro|BID_PS2
mdefine_line|#define BID_PS2         0x80            /* Register Page Select 2 */
DECL|macro|BID_PS_MASK
mdefine_line|#define BID_PS_MASK     0x3F            /* For Masking Off Page Select Bits */
DECL|macro|BID_EEPROM_0
mdefine_line|#define BID_EEPROM_0                    0x08
DECL|macro|BID_EEPROM_1
mdefine_line|#define BID_EEPROM_1                    0x09
DECL|macro|BID_EEPROM_2
mdefine_line|#define BID_EEPROM_2                    0x0A
DECL|macro|BID_EEPROM_3
mdefine_line|#define BID_EEPROM_3                    0x0B
DECL|macro|BID_EEPROM_4
mdefine_line|#define BID_EEPROM_4                    0x0C
DECL|macro|BID_EEPROM_5
mdefine_line|#define BID_EEPROM_5                    0x0D
DECL|macro|BID_EEPROM_6
mdefine_line|#define BID_EEPROM_6                    0x0E
DECL|macro|BID_EEPROM_7
mdefine_line|#define BID_EEPROM_7                    0x0F
DECL|macro|BID_OTHER_BIT
mdefine_line|#define BID_OTHER_BIT                   0x02
DECL|macro|BID_ICR_MASK
mdefine_line|#define BID_ICR_MASK                    0x0C
DECL|macro|BID_EAR_MASK
mdefine_line|#define BID_EAR_MASK                    0x0F
DECL|macro|BID_ENGR_PAGE
mdefine_line|#define BID_ENGR_PAGE                   0x0A0
DECL|macro|BID_RLA
mdefine_line|#define BID_RLA                         0x10
DECL|macro|BID_EA6
mdefine_line|#define BID_EA6                         0x80
DECL|macro|BID_RECALL_DONE_MASK
mdefine_line|#define BID_RECALL_DONE_MASK            0x10
DECL|macro|BID_BID_EEPROM_OVERRIDE
mdefine_line|#define BID_BID_EEPROM_OVERRIDE         0xFFB0
DECL|macro|BID_EXTRA_EEPROM_OVERRIDE
mdefine_line|#define BID_EXTRA_EEPROM_OVERRIDE       0xFFD0
DECL|macro|BID_EEPROM_MEDIA_MASK
mdefine_line|#define BID_EEPROM_MEDIA_MASK           0x07
DECL|macro|BID_STARLAN_TYPE
mdefine_line|#define BID_STARLAN_TYPE                0x00
DECL|macro|BID_ETHERNET_TYPE
mdefine_line|#define BID_ETHERNET_TYPE               0x01
DECL|macro|BID_TP_TYPE
mdefine_line|#define BID_TP_TYPE                     0x02
DECL|macro|BID_EW_TYPE
mdefine_line|#define BID_EW_TYPE                     0x03
DECL|macro|BID_TOKEN_RING_TYPE
mdefine_line|#define BID_TOKEN_RING_TYPE             0x04
DECL|macro|BID_UTP2_TYPE
mdefine_line|#define BID_UTP2_TYPE                   0x05
DECL|macro|BID_EEPROM_IRQ_MASK
mdefine_line|#define BID_EEPROM_IRQ_MASK             0x18
DECL|macro|BID_PRIMARY_IRQ
mdefine_line|#define BID_PRIMARY_IRQ                 0x00
DECL|macro|BID_ALTERNATE_IRQ_1
mdefine_line|#define BID_ALTERNATE_IRQ_1             0x08
DECL|macro|BID_ALTERNATE_IRQ_2
mdefine_line|#define BID_ALTERNATE_IRQ_2             0x10
DECL|macro|BID_ALTERNATE_IRQ_3
mdefine_line|#define BID_ALTERNATE_IRQ_3             0x18
DECL|macro|BID_EEPROM_RAM_SIZE_MASK
mdefine_line|#define BID_EEPROM_RAM_SIZE_MASK        0xE0
DECL|macro|BID_EEPROM_RAM_SIZE_RES1
mdefine_line|#define BID_EEPROM_RAM_SIZE_RES1        0x00
DECL|macro|BID_EEPROM_RAM_SIZE_RES2
mdefine_line|#define BID_EEPROM_RAM_SIZE_RES2        0x20
DECL|macro|BID_EEPROM_RAM_SIZE_8K
mdefine_line|#define BID_EEPROM_RAM_SIZE_8K          0x40
DECL|macro|BID_EEPROM_RAM_SIZE_16K
mdefine_line|#define BID_EEPROM_RAM_SIZE_16K         0x60
DECL|macro|BID_EEPROM_RAM_SIZE_32K
mdefine_line|#define BID_EEPROM_RAM_SIZE_32K         0x80
DECL|macro|BID_EEPROM_RAM_SIZE_64K
mdefine_line|#define BID_EEPROM_RAM_SIZE_64K         0xA0
DECL|macro|BID_EEPROM_RAM_SIZE_RES3
mdefine_line|#define BID_EEPROM_RAM_SIZE_RES3        0xC0
DECL|macro|BID_EEPROM_RAM_SIZE_RES4
mdefine_line|#define BID_EEPROM_RAM_SIZE_RES4        0xE0
DECL|macro|BID_EEPROM_BUS_TYPE_MASK
mdefine_line|#define BID_EEPROM_BUS_TYPE_MASK        0x07
DECL|macro|BID_EEPROM_BUS_TYPE_AT
mdefine_line|#define BID_EEPROM_BUS_TYPE_AT          0x00
DECL|macro|BID_EEPROM_BUS_TYPE_MCA
mdefine_line|#define BID_EEPROM_BUS_TYPE_MCA         0x01
DECL|macro|BID_EEPROM_BUS_TYPE_EISA
mdefine_line|#define BID_EEPROM_BUS_TYPE_EISA        0x02
DECL|macro|BID_EEPROM_BUS_TYPE_NEC
mdefine_line|#define BID_EEPROM_BUS_TYPE_NEC         0x03
DECL|macro|BID_EEPROM_BUS_SIZE_MASK
mdefine_line|#define BID_EEPROM_BUS_SIZE_MASK        0x18
DECL|macro|BID_EEPROM_BUS_SIZE_8BIT
mdefine_line|#define BID_EEPROM_BUS_SIZE_8BIT        0x00
DECL|macro|BID_EEPROM_BUS_SIZE_16BIT
mdefine_line|#define BID_EEPROM_BUS_SIZE_16BIT       0x08
DECL|macro|BID_EEPROM_BUS_SIZE_32BIT
mdefine_line|#define BID_EEPROM_BUS_SIZE_32BIT       0x10
DECL|macro|BID_EEPROM_BUS_SIZE_64BIT
mdefine_line|#define BID_EEPROM_BUS_SIZE_64BIT       0x18
DECL|macro|BID_EEPROM_BUS_MASTER
mdefine_line|#define BID_EEPROM_BUS_MASTER           0x20
DECL|macro|BID_EEPROM_RAM_PAGING
mdefine_line|#define BID_EEPROM_RAM_PAGING           0x40
DECL|macro|BID_EEPROM_ROM_PAGING
mdefine_line|#define BID_EEPROM_ROM_PAGING           0x80
DECL|macro|BID_EEPROM_PAGING_MASK
mdefine_line|#define BID_EEPROM_PAGING_MASK          0xC0
DECL|macro|BID_EEPROM_LOW_COST
mdefine_line|#define BID_EEPROM_LOW_COST             0x08
DECL|macro|BID_EEPROM_IO_MAPPED
mdefine_line|#define BID_EEPROM_IO_MAPPED            0x10
DECL|macro|BID_EEPROM_HMI
mdefine_line|#define BID_EEPROM_HMI                  0x01
DECL|macro|BID_EEPROM_AUTO_MEDIA_DETECT
mdefine_line|#define BID_EEPROM_AUTO_MEDIA_DETECT    0x01
DECL|macro|BID_EEPROM_CHIP_REV_MASK
mdefine_line|#define BID_EEPROM_CHIP_REV_MASK        0x0C
DECL|macro|BID_EEPROM_LAN_ADDR
mdefine_line|#define BID_EEPROM_LAN_ADDR             0x30
DECL|macro|BID_EEPROM_MEDIA_OPTION
mdefine_line|#define BID_EEPROM_MEDIA_OPTION         0x54
DECL|macro|BID_EEPROM_MEDIA_UTP
mdefine_line|#define BID_EEPROM_MEDIA_UTP            0x01
DECL|macro|BID_EEPROM_4MB_RING
mdefine_line|#define BID_EEPROM_4MB_RING             0x08
DECL|macro|BID_EEPROM_16MB_RING
mdefine_line|#define BID_EEPROM_16MB_RING            0x10
DECL|macro|BID_EEPROM_MEDIA_STP
mdefine_line|#define BID_EEPROM_MEDIA_STP            0x40
DECL|macro|BID_EEPROM_MISC_DATA
mdefine_line|#define BID_EEPROM_MISC_DATA            0x56
DECL|macro|BID_EEPROM_EARLY_TOKEN_RELEASE
mdefine_line|#define BID_EEPROM_EARLY_TOKEN_RELEASE  0x02
DECL|macro|CNFG_ID_8003E
mdefine_line|#define CNFG_ID_8003E           0x6fc0
DECL|macro|CNFG_ID_8003S
mdefine_line|#define CNFG_ID_8003S           0x6fc1
DECL|macro|CNFG_ID_8003W
mdefine_line|#define CNFG_ID_8003W           0x6fc2
DECL|macro|CNFG_ID_8115TRA
mdefine_line|#define CNFG_ID_8115TRA         0x6ec6
DECL|macro|CNFG_ID_8013E
mdefine_line|#define CNFG_ID_8013E           0x61C8
DECL|macro|CNFG_ID_8013W
mdefine_line|#define CNFG_ID_8013W           0x61C9
DECL|macro|CNFG_ID_BISTRO03E
mdefine_line|#define CNFG_ID_BISTRO03E       0xEFE5
DECL|macro|CNFG_ID_BISTRO13E
mdefine_line|#define CNFG_ID_BISTRO13E       0xEFD5
DECL|macro|CNFG_ID_BISTRO13W
mdefine_line|#define CNFG_ID_BISTRO13W       0xEFD4
DECL|macro|CNFG_MSR_583
mdefine_line|#define CNFG_MSR_583    0x0
DECL|macro|CNFG_ICR_583
mdefine_line|#define CNFG_ICR_583    0x1
DECL|macro|CNFG_IAR_583
mdefine_line|#define CNFG_IAR_583    0x2
DECL|macro|CNFG_BIO_583
mdefine_line|#define CNFG_BIO_583    0x3
DECL|macro|CNFG_EAR_583
mdefine_line|#define CNFG_EAR_583    0x3
DECL|macro|CNFG_IRR_583
mdefine_line|#define CNFG_IRR_583    0x4
DECL|macro|CNFG_LAAR_584
mdefine_line|#define CNFG_LAAR_584   0x5
DECL|macro|CNFG_GP2
mdefine_line|#define CNFG_GP2                0x7
DECL|macro|CNFG_LAAR_MASK
mdefine_line|#define CNFG_LAAR_MASK          0x1F
DECL|macro|CNFG_LAAR_ZWS
mdefine_line|#define CNFG_LAAR_ZWS           0x20
DECL|macro|CNFG_LAAR_L16E
mdefine_line|#define CNFG_LAAR_L16E          0x40
DECL|macro|CNFG_ICR_IR2_584
mdefine_line|#define CNFG_ICR_IR2_584        0x04
DECL|macro|CNFG_ICR_MASK
mdefine_line|#define CNFG_ICR_MASK       0x08
DECL|macro|CNFG_ICR_MSZ
mdefine_line|#define CNFG_ICR_MSZ        0x08
DECL|macro|CNFG_ICR_RLA
mdefine_line|#define CNFG_ICR_RLA        0x10
DECL|macro|CNFG_ICR_STO
mdefine_line|#define CNFG_ICR_STO        0x80
DECL|macro|CNFG_IRR_IRQS
mdefine_line|#define CNFG_IRR_IRQS           0x60
DECL|macro|CNFG_IRR_IEN
mdefine_line|#define CNFG_IRR_IEN            0x80
DECL|macro|CNFG_IRR_ZWS
mdefine_line|#define CNFG_IRR_ZWS            0x01
DECL|macro|CNFG_GP2_BOOT_NIBBLE
mdefine_line|#define CNFG_GP2_BOOT_NIBBLE    0x0F
DECL|macro|CNFG_IRR_OUT2
mdefine_line|#define CNFG_IRR_OUT2       0x04
DECL|macro|CNFG_IRR_OUT1
mdefine_line|#define CNFG_IRR_OUT1       0x02
DECL|macro|CNFG_SIZE_8KB
mdefine_line|#define CNFG_SIZE_8KB           8
DECL|macro|CNFG_SIZE_16KB
mdefine_line|#define CNFG_SIZE_16KB          16
DECL|macro|CNFG_SIZE_32KB
mdefine_line|#define CNFG_SIZE_32KB          32
DECL|macro|CNFG_SIZE_64KB
mdefine_line|#define CNFG_SIZE_64KB          64
DECL|macro|CNFG_SIZE_128KB
mdefine_line|#define CNFG_SIZE_128KB     128
DECL|macro|CNFG_SIZE_256KB
mdefine_line|#define CNFG_SIZE_256KB     256
DECL|macro|ROM_DISABLE
mdefine_line|#define ROM_DISABLE             0x0
DECL|macro|CNFG_SLOT_ENABLE_BIT
mdefine_line|#define CNFG_SLOT_ENABLE_BIT    0x08
DECL|macro|CNFG_POS_CONTROL_REG
mdefine_line|#define CNFG_POS_CONTROL_REG    0x096
DECL|macro|CNFG_POS_REG0
mdefine_line|#define CNFG_POS_REG0           0x100
DECL|macro|CNFG_POS_REG1
mdefine_line|#define CNFG_POS_REG1           0x101
DECL|macro|CNFG_POS_REG2
mdefine_line|#define CNFG_POS_REG2           0x102
DECL|macro|CNFG_POS_REG3
mdefine_line|#define CNFG_POS_REG3           0x103
DECL|macro|CNFG_POS_REG4
mdefine_line|#define CNFG_POS_REG4           0x104
DECL|macro|CNFG_POS_REG5
mdefine_line|#define CNFG_POS_REG5           0x105
DECL|macro|CNFG_ADAPTER_TYPE_MASK
mdefine_line|#define CNFG_ADAPTER_TYPE_MASK  0x0e
DECL|macro|SLOT_16BIT
mdefine_line|#define SLOT_16BIT              0x0008
DECL|macro|INTERFACE_5X3_CHIP
mdefine_line|#define INTERFACE_5X3_CHIP      0x0000          /* 0000 = 583 or 593 chips */
DECL|macro|NIC_690_BIT
mdefine_line|#define NIC_690_BIT                     0x0010          /* NIC is 690 */
DECL|macro|ALTERNATE_IRQ_BIT
mdefine_line|#define ALTERNATE_IRQ_BIT       0x0020          /* Alternate IRQ is used */
DECL|macro|INTERFACE_584_CHIP
mdefine_line|#define INTERFACE_584_CHIP      0x0040          /* 0001 = 584 chip */
DECL|macro|INTERFACE_594_CHIP
mdefine_line|#define INTERFACE_594_CHIP      0x0080          /* 0010 = 594 chip */
DECL|macro|INTERFACE_585_CHIP
mdefine_line|#define INTERFACE_585_CHIP      0x0100          /* 0100 = 585/790 chip */
DECL|macro|INTERFACE_CHIP_MASK
mdefine_line|#define INTERFACE_CHIP_MASK     0x03C0          /* Isolates Intfc Chip Type */
DECL|macro|BOARD_16BIT
mdefine_line|#define BOARD_16BIT             0x0040
DECL|macro|NODE_ADDR_CKSUM
mdefine_line|#define NODE_ADDR_CKSUM &t;0xEE
DECL|macro|BRD_ID_8115T
mdefine_line|#define BRD_ID_8115T    &t;0x04
DECL|macro|NIC_825_BIT
mdefine_line|#define NIC_825_BIT             0x0400          /* TRC 83C825 NIC */
DECL|macro|NIC_790_BIT
mdefine_line|#define NIC_790_BIT             0x0800          /* NIC is 83C790 Ethernet */
DECL|macro|CHIP_REV_MASK
mdefine_line|#define CHIP_REV_MASK           0x3000
DECL|macro|HWR_CBUSY
mdefine_line|#define HWR_CBUSY&t;&t;&t;0x02
DECL|macro|HWR_CA
mdefine_line|#define HWR_CA&t;&t;&t;&t;0x01
DECL|macro|MAC_QUEUE
mdefine_line|#define MAC_QUEUE                       0
DECL|macro|NON_MAC_QUEUE
mdefine_line|#define NON_MAC_QUEUE                   1
DECL|macro|BUG_QUEUE
mdefine_line|#define BUG_QUEUE                       2       /* NO RECEIVE QUEUE, ONLY TX */
DECL|macro|NUM_MAC_TX_FCBS
mdefine_line|#define NUM_MAC_TX_FCBS                 8
DECL|macro|NUM_MAC_TX_BDBS
mdefine_line|#define NUM_MAC_TX_BDBS                 NUM_MAC_TX_FCBS
DECL|macro|NUM_MAC_RX_FCBS
mdefine_line|#define NUM_MAC_RX_FCBS                 7
DECL|macro|NUM_MAC_RX_BDBS
mdefine_line|#define NUM_MAC_RX_BDBS                 8
DECL|macro|NUM_NON_MAC_TX_FCBS
mdefine_line|#define NUM_NON_MAC_TX_FCBS             6
DECL|macro|NUM_NON_MAC_TX_BDBS
mdefine_line|#define NUM_NON_MAC_TX_BDBS             NUM_NON_MAC_TX_FCBS
DECL|macro|NUM_NON_MAC_RX_BDBS
mdefine_line|#define NUM_NON_MAC_RX_BDBS             0       /* CALCULATED DYNAMICALLY */
DECL|macro|NUM_BUG_TX_FCBS
mdefine_line|#define NUM_BUG_TX_FCBS                 8
DECL|macro|NUM_BUG_TX_BDBS
mdefine_line|#define NUM_BUG_TX_BDBS                 NUM_BUG_TX_FCBS
DECL|macro|MAC_TX_BUFFER_MEMORY
mdefine_line|#define MAC_TX_BUFFER_MEMORY            1024
DECL|macro|NON_MAC_TX_BUFFER_MEMORY
mdefine_line|#define NON_MAC_TX_BUFFER_MEMORY        (20 * 1024)
DECL|macro|BUG_TX_BUFFER_MEMORY
mdefine_line|#define BUG_TX_BUFFER_MEMORY            (NUM_BUG_TX_FCBS * 32)
DECL|macro|RX_BUFFER_MEMORY
mdefine_line|#define RX_BUFFER_MEMORY                0       /* CALCULATED DYNAMICALLY */
DECL|macro|RX_DATA_BUFFER_SIZE
mdefine_line|#define RX_DATA_BUFFER_SIZE             256
DECL|macro|RX_BDB_SIZE_SHIFT
mdefine_line|#define RX_BDB_SIZE_SHIFT               3       /* log2(RX_DATA_BUFFER_SIZE)-log2(sizeof(BDBlock)) */
DECL|macro|RX_BDB_SIZE_MASK
mdefine_line|#define RX_BDB_SIZE_MASK                (sizeof(BDBlock) - 1)
DECL|macro|RX_DATA_BUFFER_SIZE_MASK
mdefine_line|#define RX_DATA_BUFFER_SIZE_MASK        (RX_DATA_BUFFER_SIZE-1)
DECL|macro|NUM_OF_INTERRUPTS
mdefine_line|#define NUM_OF_INTERRUPTS               0x20
DECL|macro|NOT_TRANSMITING
mdefine_line|#define NOT_TRANSMITING                 0
DECL|macro|TRANSMITING
mdefine_line|#define TRANSMITING&t;&t;&t;1
DECL|macro|TRC_INTERRUPT_ENABLE_MASK
mdefine_line|#define TRC_INTERRUPT_ENABLE_MASK       0x7FF6
DECL|macro|UCODE_VERSION
mdefine_line|#define UCODE_VERSION                   0x58
DECL|macro|UCODE_SIZE_OFFSET
mdefine_line|#define UCODE_SIZE_OFFSET               0x0000  /* WORD */
DECL|macro|UCODE_CHECKSUM_OFFSET
mdefine_line|#define UCODE_CHECKSUM_OFFSET           0x0002  /* WORD */
DECL|macro|UCODE_VERSION_OFFSET
mdefine_line|#define UCODE_VERSION_OFFSET            0x0004  /* BYTE */
DECL|macro|CS_RAM_SIZE
mdefine_line|#define CS_RAM_SIZE                     0X2000
DECL|macro|CS_RAM_CHECKSUM_OFFSET
mdefine_line|#define CS_RAM_CHECKSUM_OFFSET          0x1FFE  /* WORD 1FFE(MSB)-1FFF(LSB)*/
DECL|macro|CS_RAM_VERSION_OFFSET
mdefine_line|#define CS_RAM_VERSION_OFFSET           0x1FFC  /* WORD 1FFC(MSB)-1FFD(LSB)*/
DECL|macro|MISC_DATA_SIZE
mdefine_line|#define MISC_DATA_SIZE                  128
DECL|macro|NUM_OF_ACBS
mdefine_line|#define NUM_OF_ACBS                     1
DECL|macro|ACB_COMMAND_NOT_DONE
mdefine_line|#define ACB_COMMAND_NOT_DONE            0x0000  /* Init, command not done */
DECL|macro|ACB_COMMAND_DONE
mdefine_line|#define ACB_COMMAND_DONE                0x8000  /* TRC says command done */
DECL|macro|ACB_COMMAND_STATUS_MASK
mdefine_line|#define ACB_COMMAND_STATUS_MASK         0x00FF  /* low byte is status */
DECL|macro|ACB_COMMAND_SUCCESSFUL
mdefine_line|#define ACB_COMMAND_SUCCESSFUL          0x0000  /* means cmd was successful */
DECL|macro|ACB_NOT_CHAIN_END
mdefine_line|#define ACB_NOT_CHAIN_END               0x0000  /* tell TRC more CBs in chain */
DECL|macro|ACB_CHAIN_END
mdefine_line|#define ACB_CHAIN_END                   0x8000  /* tell TRC last CB in chain */
DECL|macro|ACB_COMMAND_NO_INTERRUPT
mdefine_line|#define ACB_COMMAND_NO_INTERRUPT        0x0000  /* tell TRC no INT after CB */
DECL|macro|ACB_COMMAND_INTERRUPT
mdefine_line|#define ACB_COMMAND_INTERRUPT           0x2000  /* tell TRC to INT after CB */
DECL|macro|ACB_SUB_CMD_NOP
mdefine_line|#define ACB_SUB_CMD_NOP                 0x0000
DECL|macro|ACB_CMD_HIC_NOP
mdefine_line|#define ACB_CMD_HIC_NOP                 0x0080
DECL|macro|ACB_CMD_MCT_NOP
mdefine_line|#define ACB_CMD_MCT_NOP                 0x0000
DECL|macro|ACB_CMD_MCT_TEST
mdefine_line|#define ACB_CMD_MCT_TEST                0x0001
DECL|macro|ACB_CMD_HIC_TEST
mdefine_line|#define ACB_CMD_HIC_TEST                0x0081
DECL|macro|ACB_CMD_INSERT
mdefine_line|#define ACB_CMD_INSERT                  0x0002
DECL|macro|ACB_CMD_REMOVE
mdefine_line|#define ACB_CMD_REMOVE                  0x0003
DECL|macro|ACB_CMD_MCT_WRITE_VALUE
mdefine_line|#define ACB_CMD_MCT_WRITE_VALUE         0x0004
DECL|macro|ACB_CMD_HIC_WRITE_VALUE
mdefine_line|#define ACB_CMD_HIC_WRITE_VALUE         0x0084
DECL|macro|ACB_CMD_MCT_READ_VALUE
mdefine_line|#define ACB_CMD_MCT_READ_VALUE          0x0005
DECL|macro|ACB_CMD_HIC_READ_VALUE
mdefine_line|#define ACB_CMD_HIC_READ_VALUE          0x0085
DECL|macro|ACB_CMD_INIT_TX_RX
mdefine_line|#define ACB_CMD_INIT_TX_RX              0x0086
DECL|macro|ACB_CMD_INIT_TRC_TIMERS
mdefine_line|#define ACB_CMD_INIT_TRC_TIMERS         0x0006
DECL|macro|ACB_CMD_READ_TRC_STATUS
mdefine_line|#define ACB_CMD_READ_TRC_STATUS         0x0007
DECL|macro|ACB_CMD_CHANGE_JOIN_STATE
mdefine_line|#define ACB_CMD_CHANGE_JOIN_STATE       0x0008
DECL|macro|ACB_CMD_RESERVED_9
mdefine_line|#define ACB_CMD_RESERVED_9              0x0009
DECL|macro|ACB_CMD_RESERVED_A
mdefine_line|#define ACB_CMD_RESERVED_A              0x000A
DECL|macro|ACB_CMD_RESERVED_B
mdefine_line|#define ACB_CMD_RESERVED_B              0x000B
DECL|macro|ACB_CMD_RESERVED_C
mdefine_line|#define ACB_CMD_RESERVED_C              0x000C
DECL|macro|ACB_CMD_RESERVED_D
mdefine_line|#define ACB_CMD_RESERVED_D              0x000D
DECL|macro|ACB_CMD_RESERVED_E
mdefine_line|#define ACB_CMD_RESERVED_E              0x000E
DECL|macro|ACB_CMD_RESERVED_F
mdefine_line|#define ACB_CMD_RESERVED_F              0x000F
DECL|macro|TRC_MAC_REGISTERS_TEST
mdefine_line|#define TRC_MAC_REGISTERS_TEST          0x0000
DECL|macro|TRC_INTERNAL_LOOPBACK
mdefine_line|#define TRC_INTERNAL_LOOPBACK           0x0001
DECL|macro|TRC_TRI_LOOPBACK
mdefine_line|#define TRC_TRI_LOOPBACK                0x0002
DECL|macro|TRC_INTERNAL_ROM_TEST
mdefine_line|#define TRC_INTERNAL_ROM_TEST           0x0003
DECL|macro|TRC_LOBE_MEDIA_TEST
mdefine_line|#define TRC_LOBE_MEDIA_TEST             0x0004
DECL|macro|TRC_ANALOG_TEST
mdefine_line|#define TRC_ANALOG_TEST                 0x0005
DECL|macro|TRC_HOST_INTERFACE_REG_TEST
mdefine_line|#define TRC_HOST_INTERFACE_REG_TEST     0x0003
DECL|macro|TEST_DMA_1
mdefine_line|#define TEST_DMA_1                      0x0000
DECL|macro|TEST_DMA_2
mdefine_line|#define TEST_DMA_2                      0x0001
DECL|macro|TEST_MCT_ROM
mdefine_line|#define TEST_MCT_ROM                    0x0002
DECL|macro|HIC_INTERNAL_DIAG
mdefine_line|#define HIC_INTERNAL_DIAG               0x0003
DECL|macro|ABORT_TRANSMIT_PRIORITY_0
mdefine_line|#define ABORT_TRANSMIT_PRIORITY_0       0x0001
DECL|macro|ABORT_TRANSMIT_PRIORITY_1
mdefine_line|#define ABORT_TRANSMIT_PRIORITY_1       0x0002
DECL|macro|ABORT_TRANSMIT_PRIORITY_2
mdefine_line|#define ABORT_TRANSMIT_PRIORITY_2       0x0004
DECL|macro|ABORT_TRANSMIT_PRIORITY_3
mdefine_line|#define ABORT_TRANSMIT_PRIORITY_3       0x0008
DECL|macro|ABORT_TRANSMIT_PRIORITY_4
mdefine_line|#define ABORT_TRANSMIT_PRIORITY_4       0x0010
DECL|macro|ABORT_TRANSMIT_PRIORITY_5
mdefine_line|#define ABORT_TRANSMIT_PRIORITY_5       0x0020
DECL|macro|ABORT_TRANSMIT_PRIORITY_6
mdefine_line|#define ABORT_TRANSMIT_PRIORITY_6       0x0040
DECL|macro|ABORT_TRANSMIT_PRIORITY_7
mdefine_line|#define ABORT_TRANSMIT_PRIORITY_7       0x0080
DECL|macro|TX_PENDING_PRIORITY_0
mdefine_line|#define TX_PENDING_PRIORITY_0           0x0001
DECL|macro|TX_PENDING_PRIORITY_1
mdefine_line|#define TX_PENDING_PRIORITY_1           0x0002
DECL|macro|TX_PENDING_PRIORITY_2
mdefine_line|#define TX_PENDING_PRIORITY_2           0x0004
DECL|macro|TX_PENDING_PRIORITY_3
mdefine_line|#define TX_PENDING_PRIORITY_3           0x0008
DECL|macro|TX_PENDING_PRIORITY_4
mdefine_line|#define TX_PENDING_PRIORITY_4           0x0010
DECL|macro|TX_PENDING_PRIORITY_5
mdefine_line|#define TX_PENDING_PRIORITY_5           0x0020
DECL|macro|TX_PENDING_PRIORITY_6
mdefine_line|#define TX_PENDING_PRIORITY_6           0x0040
DECL|macro|TX_PENDING_PRIORITY_7
mdefine_line|#define TX_PENDING_PRIORITY_7           0x0080
DECL|macro|FCB_FRAME_LENGTH
mdefine_line|#define FCB_FRAME_LENGTH                0x100
DECL|macro|FCB_COMMAND_DONE
mdefine_line|#define FCB_COMMAND_DONE                0x8000  /* FCB Word 0 */
DECL|macro|FCB_NOT_CHAIN_END
mdefine_line|#define FCB_NOT_CHAIN_END               0x0000  /* FCB Word 1 */
DECL|macro|FCB_CHAIN_END
mdefine_line|#define FCB_CHAIN_END                   0x8000
DECL|macro|FCB_NO_WARNING
mdefine_line|#define FCB_NO_WARNING                  0x0000
DECL|macro|FCB_WARNING
mdefine_line|#define FCB_WARNING                     0x4000
DECL|macro|FCB_INTERRUPT_DISABLE
mdefine_line|#define FCB_INTERRUPT_DISABLE           0x0000
DECL|macro|FCB_INTERRUPT_ENABLE
mdefine_line|#define FCB_INTERRUPT_ENABLE            0x2000
DECL|macro|FCB_ENABLE_IMA
mdefine_line|#define FCB_ENABLE_IMA                  0x0008
DECL|macro|FCB_ENABLE_TES
mdefine_line|#define FCB_ENABLE_TES                  0x0004  /* Guarantee Tx before Int */
DECL|macro|FCB_ENABLE_TFS
mdefine_line|#define FCB_ENABLE_TFS                  0x0002  /* Post Tx Frame Status */
DECL|macro|FCB_ENABLE_NTC
mdefine_line|#define FCB_ENABLE_NTC                  0x0001  /* No Tx CRC */
DECL|macro|FCB_TX_STATUS_CR2
mdefine_line|#define FCB_TX_STATUS_CR2               0x0004
DECL|macro|FCB_TX_STATUS_AR2
mdefine_line|#define FCB_TX_STATUS_AR2               0x0008
DECL|macro|FCB_TX_STATUS_CR1
mdefine_line|#define FCB_TX_STATUS_CR1               0x0040
DECL|macro|FCB_TX_STATUS_AR1
mdefine_line|#define FCB_TX_STATUS_AR1               0x0080
DECL|macro|FCB_TX_AC_BITS
mdefine_line|#define FCB_TX_AC_BITS                  (FCB_TX_STATUS_AR1+FCB_TX_STATUS_AR2+FCB_TX_STATUS_CR1+FCB_TX_STATUS_CR2)
DECL|macro|FCB_TX_STATUS_E
mdefine_line|#define FCB_TX_STATUS_E                 0x0100
DECL|macro|FCB_RX_STATUS_ANY_ERROR
mdefine_line|#define FCB_RX_STATUS_ANY_ERROR         0x0001
DECL|macro|FCB_RX_STATUS_FCS_ERROR
mdefine_line|#define FCB_RX_STATUS_FCS_ERROR         0x0002
DECL|macro|FCB_RX_STATUS_IA_MATCHED
mdefine_line|#define FCB_RX_STATUS_IA_MATCHED        0x0400
DECL|macro|FCB_RX_STATUS_IGA_BSGA_MATCHED
mdefine_line|#define FCB_RX_STATUS_IGA_BSGA_MATCHED  0x0500
DECL|macro|FCB_RX_STATUS_FA_MATCHED
mdefine_line|#define FCB_RX_STATUS_FA_MATCHED        0x0600
DECL|macro|FCB_RX_STATUS_BA_MATCHED
mdefine_line|#define FCB_RX_STATUS_BA_MATCHED        0x0700
DECL|macro|FCB_RX_STATUS_DA_MATCHED
mdefine_line|#define FCB_RX_STATUS_DA_MATCHED        0x0400
DECL|macro|FCB_RX_STATUS_SOURCE_ROUTING
mdefine_line|#define FCB_RX_STATUS_SOURCE_ROUTING    0x0800
DECL|macro|BDB_BUFFER_SIZE
mdefine_line|#define BDB_BUFFER_SIZE                 0x100
DECL|macro|BDB_NOT_CHAIN_END
mdefine_line|#define BDB_NOT_CHAIN_END               0x0000
DECL|macro|BDB_CHAIN_END
mdefine_line|#define BDB_CHAIN_END                   0x8000
DECL|macro|BDB_NO_WARNING
mdefine_line|#define BDB_NO_WARNING                  0x0000
DECL|macro|BDB_WARNING
mdefine_line|#define BDB_WARNING                     0x4000
DECL|macro|ERROR_COUNTERS_CHANGED
mdefine_line|#define ERROR_COUNTERS_CHANGED          0x0001
DECL|macro|TI_NDIS_RING_STATUS_CHANGED
mdefine_line|#define TI_NDIS_RING_STATUS_CHANGED     0x0002
DECL|macro|UNA_CHANGED
mdefine_line|#define UNA_CHANGED                     0x0004
DECL|macro|READY_TO_SEND_RQ_INIT
mdefine_line|#define READY_TO_SEND_RQ_INIT           0x0008
DECL|macro|SCGB_ADDRESS_POINTER_FORMAT
mdefine_line|#define SCGB_ADDRESS_POINTER_FORMAT     INTEL_ADDRESS_POINTER_FORMAT
DECL|macro|SCGB_DATA_FORMAT
mdefine_line|#define SCGB_DATA_FORMAT                INTEL_DATA_FORMAT
DECL|macro|SCGB_MULTI_WORD_CONTROL
mdefine_line|#define SCGB_MULTI_WORD_CONTROL         0
DECL|macro|SCGB_BURST_LENGTH
mdefine_line|#define SCGB_BURST_LENGTH               0x000E  /* DMA Burst Length */
DECL|macro|SCGB_CONFIG
mdefine_line|#define SCGB_CONFIG                     (INTEL_ADDRESS_POINTER_FORMAT+INTEL_DATA_FORMAT+SCGB_BURST_LENGTH)
DECL|macro|ISCP_BLOCK_SIZE
mdefine_line|#define ISCP_BLOCK_SIZE                 0x0A
DECL|macro|RAM_SIZE
mdefine_line|#define RAM_SIZE                        0x10000
DECL|macro|INIT_SYS_CONFIG_PTR_OFFSET
mdefine_line|#define INIT_SYS_CONFIG_PTR_OFFSET      (RAM_SIZE-ISCP_BLOCK_SIZE)
DECL|macro|SCGP_BLOCK_OFFSET
mdefine_line|#define SCGP_BLOCK_OFFSET               0
DECL|macro|SCLB_NOT_VALID
mdefine_line|#define SCLB_NOT_VALID                  0x0000  /* Initially, SCLB not valid */
DECL|macro|SCLB_VALID
mdefine_line|#define SCLB_VALID                      0x8000  /* Host tells TRC SCLB valid */
DECL|macro|SCLB_PROCESSED
mdefine_line|#define SCLB_PROCESSED                  0x0000  /* TRC says SCLB processed */
DECL|macro|SCLB_RESUME_CONTROL_NOT_VALID
mdefine_line|#define SCLB_RESUME_CONTROL_NOT_VALID   0x0000  /* Initially, RC not valid */
DECL|macro|SCLB_RESUME_CONTROL_VALID
mdefine_line|#define SCLB_RESUME_CONTROL_VALID       0x4000  /* Host tells TRC RC valid */
DECL|macro|SCLB_IACK_CODE_NOT_VALID
mdefine_line|#define SCLB_IACK_CODE_NOT_VALID        0x0000  /* Initially, IACK not valid */
DECL|macro|SCLB_IACK_CODE_VALID
mdefine_line|#define SCLB_IACK_CODE_VALID            0x2000  /* Host tells TRC IACK valid */
DECL|macro|SCLB_CMD_NOP
mdefine_line|#define SCLB_CMD_NOP                    0x0000
DECL|macro|SCLB_CMD_REMOVE
mdefine_line|#define SCLB_CMD_REMOVE                 0x0001
DECL|macro|SCLB_CMD_SUSPEND_ACB_CHAIN
mdefine_line|#define SCLB_CMD_SUSPEND_ACB_CHAIN      0x0002
DECL|macro|SCLB_CMD_SET_INTERRUPT_MASK
mdefine_line|#define SCLB_CMD_SET_INTERRUPT_MASK     0x0003
DECL|macro|SCLB_CMD_CLEAR_INTERRUPT_MASK
mdefine_line|#define SCLB_CMD_CLEAR_INTERRUPT_MASK   0x0004
DECL|macro|SCLB_CMD_RESERVED_5
mdefine_line|#define SCLB_CMD_RESERVED_5             0x0005
DECL|macro|SCLB_CMD_RESERVED_6
mdefine_line|#define SCLB_CMD_RESERVED_6             0x0006
DECL|macro|SCLB_CMD_RESERVED_7
mdefine_line|#define SCLB_CMD_RESERVED_7             0x0007
DECL|macro|SCLB_CMD_RESERVED_8
mdefine_line|#define SCLB_CMD_RESERVED_8             0x0008
DECL|macro|SCLB_CMD_RESERVED_9
mdefine_line|#define SCLB_CMD_RESERVED_9             0x0009
DECL|macro|SCLB_CMD_RESERVED_A
mdefine_line|#define SCLB_CMD_RESERVED_A             0x000A
DECL|macro|SCLB_CMD_RESERVED_B
mdefine_line|#define SCLB_CMD_RESERVED_B             0x000B
DECL|macro|SCLB_CMD_RESERVED_C
mdefine_line|#define SCLB_CMD_RESERVED_C             0x000C
DECL|macro|SCLB_CMD_RESERVED_D
mdefine_line|#define SCLB_CMD_RESERVED_D             0x000D
DECL|macro|SCLB_CMD_RESERVED_E
mdefine_line|#define SCLB_CMD_RESERVED_E             0x000E
DECL|macro|SCLB_CMD_RESERVED_F
mdefine_line|#define SCLB_CMD_RESERVED_F             0x000F
DECL|macro|SCLB_RC_ACB
mdefine_line|#define SCLB_RC_ACB                     0x0001  /* Action Command Block Chain */
DECL|macro|SCLB_RC_RES0
mdefine_line|#define SCLB_RC_RES0                    0x0002  /* Always Zero */
DECL|macro|SCLB_RC_RES1
mdefine_line|#define SCLB_RC_RES1                    0x0004  /* Always Zero */
DECL|macro|SCLB_RC_RES2
mdefine_line|#define SCLB_RC_RES2                    0x0008  /* Always Zero */
DECL|macro|SCLB_RC_RX_MAC_FCB
mdefine_line|#define SCLB_RC_RX_MAC_FCB              0x0010  /* RX_MAC_FCB Chain */
DECL|macro|SCLB_RC_RX_MAC_BDB
mdefine_line|#define SCLB_RC_RX_MAC_BDB              0x0020  /* RX_MAC_BDB Chain */
DECL|macro|SCLB_RC_RX_NON_MAC_FCB
mdefine_line|#define SCLB_RC_RX_NON_MAC_FCB          0x0040  /* RX_NON_MAC_FCB Chain */
DECL|macro|SCLB_RC_RX_NON_MAC_BDB
mdefine_line|#define SCLB_RC_RX_NON_MAC_BDB          0x0080  /* RX_NON_MAC_BDB Chain */
DECL|macro|SCLB_RC_TFCB0
mdefine_line|#define SCLB_RC_TFCB0                   0x0100  /* TX Priority 0 FCB Chain */
DECL|macro|SCLB_RC_TFCB1
mdefine_line|#define SCLB_RC_TFCB1                   0x0200  /* TX Priority 1 FCB Chain */
DECL|macro|SCLB_RC_TFCB2
mdefine_line|#define SCLB_RC_TFCB2                   0x0400  /* TX Priority 2 FCB Chain */
DECL|macro|SCLB_RC_TFCB3
mdefine_line|#define SCLB_RC_TFCB3                   0x0800  /* TX Priority 3 FCB Chain */
DECL|macro|SCLB_RC_TFCB4
mdefine_line|#define SCLB_RC_TFCB4                   0x1000  /* TX Priority 4 FCB Chain */
DECL|macro|SCLB_RC_TFCB5
mdefine_line|#define SCLB_RC_TFCB5                   0x2000  /* TX Priority 5 FCB Chain */
DECL|macro|SCLB_RC_TFCB6
mdefine_line|#define SCLB_RC_TFCB6                   0x4000  /* TX Priority 6 FCB Chain */
DECL|macro|SCLB_RC_TFCB7
mdefine_line|#define SCLB_RC_TFCB7                   0x8000  /* TX Priority 7 FCB Chain */
DECL|macro|SCLB_IMC_RES0
mdefine_line|#define SCLB_IMC_RES0                   0x0001  /* */
DECL|macro|SCLB_IMC_MAC_TYPE_3
mdefine_line|#define SCLB_IMC_MAC_TYPE_3             0x0002  /* MAC_ARC_INDICATE */
DECL|macro|SCLB_IMC_MAC_ERROR_COUNTERS
mdefine_line|#define SCLB_IMC_MAC_ERROR_COUNTERS     0x0004  /* */
DECL|macro|SCLB_IMC_RES1
mdefine_line|#define SCLB_IMC_RES1                   0x0008  /* */
DECL|macro|SCLB_IMC_MAC_TYPE_2
mdefine_line|#define SCLB_IMC_MAC_TYPE_2             0x0010  /* QUE_MAC_INDICATE */
DECL|macro|SCLB_IMC_TX_FRAME
mdefine_line|#define SCLB_IMC_TX_FRAME               0x0020  /* */
DECL|macro|SCLB_IMC_END_OF_TX_QUEUE
mdefine_line|#define SCLB_IMC_END_OF_TX_QUEUE        0x0040  /* */
DECL|macro|SCLB_IMC_NON_MAC_RX_RESOURCE
mdefine_line|#define SCLB_IMC_NON_MAC_RX_RESOURCE    0x0080  /* */
DECL|macro|SCLB_IMC_MAC_RX_RESOURCE
mdefine_line|#define SCLB_IMC_MAC_RX_RESOURCE        0x0100  /* */
DECL|macro|SCLB_IMC_NON_MAC_RX_FRAME
mdefine_line|#define SCLB_IMC_NON_MAC_RX_FRAME       0x0200  /* */
DECL|macro|SCLB_IMC_MAC_RX_FRAME
mdefine_line|#define SCLB_IMC_MAC_RX_FRAME           0x0400  /* */
DECL|macro|SCLB_IMC_TRC_FIFO_STATUS
mdefine_line|#define SCLB_IMC_TRC_FIFO_STATUS        0x0800  /* */
DECL|macro|SCLB_IMC_COMMAND_STATUS
mdefine_line|#define SCLB_IMC_COMMAND_STATUS         0x1000  /* */
DECL|macro|SCLB_IMC_MAC_TYPE_1
mdefine_line|#define SCLB_IMC_MAC_TYPE_1             0x2000  /* Self Removed */
DECL|macro|SCLB_IMC_TRC_INTRNL_TST_STATUS
mdefine_line|#define SCLB_IMC_TRC_INTRNL_TST_STATUS  0x4000  /* */
DECL|macro|SCLB_IMC_RES2
mdefine_line|#define SCLB_IMC_RES2                   0x8000  /* */
DECL|macro|DMA_TRIGGER
mdefine_line|#define DMA_TRIGGER                     0x0004
DECL|macro|FREQ_16MB_BIT
mdefine_line|#define FREQ_16MB_BIT                   0x0010
DECL|macro|THDREN
mdefine_line|#define THDREN                          0x0020
DECL|macro|CFG0_RSV1
mdefine_line|#define CFG0_RSV1                       0x0040
DECL|macro|CFG0_RSV2
mdefine_line|#define CFG0_RSV2                       0x0080
DECL|macro|ETREN
mdefine_line|#define ETREN                           0x0100
DECL|macro|RX_OWN_BIT
mdefine_line|#define RX_OWN_BIT                      0x0200
DECL|macro|RXATMAC
mdefine_line|#define RXATMAC                         0x0400
DECL|macro|PROMISCUOUS_BIT
mdefine_line|#define PROMISCUOUS_BIT                 0x0800
DECL|macro|USETPT
mdefine_line|#define USETPT                          0x1000
DECL|macro|SAVBAD_BIT
mdefine_line|#define SAVBAD_BIT                      0x2000
DECL|macro|ONEQUE
mdefine_line|#define ONEQUE                          0x4000
DECL|macro|NO_AUTOREMOVE
mdefine_line|#define NO_AUTOREMOVE                   0x8000
DECL|macro|RX_FCB_AREA_8316
mdefine_line|#define RX_FCB_AREA_8316        0x00000000
DECL|macro|RX_BUFF_AREA_8316
mdefine_line|#define RX_BUFF_AREA_8316       0x00000000
DECL|macro|TRC_POINTER
mdefine_line|#define TRC_POINTER(X)          ((unsigned long)(X) - tp-&gt;ram_access)
DECL|macro|RX_FCB_TRC_POINTER
mdefine_line|#define RX_FCB_TRC_POINTER(X)   ((unsigned long)(X) - tp-&gt;ram_access + RX_FCB_AREA_8316)
DECL|macro|RX_BUFF_TRC_POINTER
mdefine_line|#define RX_BUFF_TRC_POINTER(X) ((unsigned long)(X) - tp-&gt;ram_access + RX_BUFF_AREA_8316)
singleline_comment|// Offset 0: MSR - Memory Select Register
singleline_comment|//
DECL|macro|r587_MSR
mdefine_line|#define r587_MSR        0x000   
singleline_comment|// Register Offset
singleline_comment|//#define       MSR_RST         0x080   // LAN Controller Reset
DECL|macro|MSR_MENB
mdefine_line|#define MSR_MENB        0x040   
singleline_comment|// Shared Memory Enable
DECL|macro|MSR_RA18
mdefine_line|#define MSR_RA18        0x020   
singleline_comment|// Ram Address bit 18   (583, 584, 587)
DECL|macro|MSR_RA17
mdefine_line|#define MSR_RA17        0x010   
singleline_comment|// Ram Address bit 17   (583, 584, 585/790)
DECL|macro|MSR_RA16
mdefine_line|#define MSR_RA16        0x008   
singleline_comment|// Ram Address bit 16   (583, 584, 585/790)
DECL|macro|MSR_RA15
mdefine_line|#define MSR_RA15        0x004   
singleline_comment|// Ram Address bit 15   (583, 584, 585/790)
DECL|macro|MSR_RA14
mdefine_line|#define MSR_RA14        0x002   
singleline_comment|// Ram Address bit 14   (583, 584, 585/790)
DECL|macro|MSR_RA13
mdefine_line|#define MSR_RA13        0x001   
singleline_comment|// Ram Address bit 13   (583, 584, 585/790)
DECL|macro|MSR_MASK
mdefine_line|#define MSR_MASK        0x03F   
singleline_comment|// Mask for Address bits RA18-RA13 (583, 584, 587)
DECL|macro|MSR
mdefine_line|#define MSR                     0x00
DECL|macro|IRR
mdefine_line|#define IRR                     0x04
DECL|macro|HWR
mdefine_line|#define HWR                     0x04
DECL|macro|LAAR
mdefine_line|#define LAAR                    0x05
DECL|macro|IMCCR
mdefine_line|#define IMCCR                   0x05
DECL|macro|LAR0
mdefine_line|#define LAR0                    0x08
DECL|macro|BDID
mdefine_line|#define BDID                    0x0E    
singleline_comment|// Adapter ID byte register offset
DECL|macro|CSR
mdefine_line|#define CSR                     0x10
DECL|macro|PR
mdefine_line|#define PR                      0x11
DECL|macro|MSR_RST
mdefine_line|#define MSR_RST                 0x80
DECL|macro|MSR_MEMB
mdefine_line|#define MSR_MEMB                0x40
DECL|macro|MSR_0WS
mdefine_line|#define MSR_0WS                 0x20
DECL|macro|FORCED_16BIT_MODE
mdefine_line|#define FORCED_16BIT_MODE       0x0002
DECL|macro|INTERFRAME_SPACING_16
mdefine_line|#define INTERFRAME_SPACING_16           0x0003  /* 6 bytes */
DECL|macro|INTERFRAME_SPACING_4
mdefine_line|#define INTERFRAME_SPACING_4            0x0001  /* 2 bytes */
DECL|macro|MULTICAST_ADDRESS_BIT
mdefine_line|#define MULTICAST_ADDRESS_BIT           0x0010
DECL|macro|NON_SRC_ROUTING_BIT
mdefine_line|#define NON_SRC_ROUTING_BIT             0x0020
DECL|macro|LOOPING_MODE_MASK
mdefine_line|#define LOOPING_MODE_MASK       0x0007
multiline_comment|/*&n; * Decode firmware defines.&n; */
DECL|macro|SWAP_BYTES
mdefine_line|#define SWAP_BYTES(X)&t;&t;((X &amp; 0xff) &lt;&lt; 8) | (X &gt;&gt; 8)
DECL|macro|WEIGHT_OFFSET
mdefine_line|#define WEIGHT_OFFSET&t;&t;5
DECL|macro|TREE_SIZE_OFFSET
mdefine_line|#define TREE_SIZE_OFFSET&t;9
DECL|macro|TREE_OFFSET
mdefine_line|#define TREE_OFFSET&t;&t;11
multiline_comment|/* The Huffman Encoding Tree is constructed of these nodes. */
r_typedef
r_struct
(brace
DECL|member|llink
id|__u8
id|llink
suffix:semicolon
multiline_comment|/* Short version of above node. */
DECL|member|tag
id|__u8
id|tag
suffix:semicolon
DECL|member|info
id|__u8
id|info
suffix:semicolon
multiline_comment|/* This node is used on decodes. */
DECL|member|rlink
id|__u8
id|rlink
suffix:semicolon
DECL|typedef|DECODE_TREE_NODE
)brace
id|DECODE_TREE_NODE
suffix:semicolon
DECL|macro|ROOT
mdefine_line|#define ROOT&t;0&t;/* Branch value. */
DECL|macro|LEAF
mdefine_line|#define LEAF&t;0&t;/* Tag field value. */
DECL|macro|BRANCH
mdefine_line|#define BRANCH&t;1&t;/* Tag field value. */
multiline_comment|/*&n; * Multicast Table Structure&n; */
r_typedef
r_struct
(brace
DECL|member|address
id|__u8
id|address
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|instance_count
id|__u8
id|instance_count
suffix:semicolon
DECL|typedef|McTable
)brace
id|McTable
suffix:semicolon
multiline_comment|/*&n; * Fragment Descriptor Definition&n; */
r_typedef
r_struct
(brace
DECL|member|fragment_ptr
id|__u8
op_star
id|fragment_ptr
suffix:semicolon
DECL|member|fragment_length
id|__u32
id|fragment_length
suffix:semicolon
DECL|typedef|FragmentStructure
)brace
id|FragmentStructure
suffix:semicolon
multiline_comment|/*&n; * Data Buffer Structure Definition&n; */
r_typedef
r_struct
(brace
DECL|member|fragment_count
id|__u32
id|fragment_count
suffix:semicolon
DECL|member|fragment_list
id|FragmentStructure
id|fragment_list
(braket
id|MAXFRAGMENTS
)braket
suffix:semicolon
DECL|typedef|DataBufferStructure
)brace
id|DataBufferStructure
suffix:semicolon
macro_line|#pragma pack(1)
r_typedef
r_struct
(brace
DECL|member|IType
id|__u8
id|IType
suffix:semicolon
DECL|member|ISubtype
id|__u8
id|ISubtype
suffix:semicolon
DECL|typedef|Interrupt_Status_Word
)brace
id|Interrupt_Status_Word
suffix:semicolon
macro_line|#pragma pack(1)
DECL|struct|BDBlockType
r_typedef
r_struct
id|BDBlockType
(brace
DECL|member|info
id|__u16
id|info
suffix:semicolon
multiline_comment|/* 02 */
DECL|member|trc_next_ptr
id|__u32
id|trc_next_ptr
suffix:semicolon
multiline_comment|/* 06 */
DECL|member|trc_data_block_ptr
id|__u32
id|trc_data_block_ptr
suffix:semicolon
multiline_comment|/* 10 */
DECL|member|buffer_length
id|__u16
id|buffer_length
suffix:semicolon
multiline_comment|/* 12 */
DECL|member|data_block_ptr
id|__u16
op_star
id|data_block_ptr
suffix:semicolon
multiline_comment|/* 16 */
DECL|member|next_ptr
r_struct
id|BDBlockType
op_star
id|next_ptr
suffix:semicolon
multiline_comment|/* 20 */
DECL|member|back_ptr
r_struct
id|BDBlockType
op_star
id|back_ptr
suffix:semicolon
multiline_comment|/* 24 */
DECL|member|filler
id|__u8
id|filler
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 32 */
DECL|typedef|BDBlock
)brace
id|BDBlock
suffix:semicolon
macro_line|#pragma pack(1)
DECL|struct|FCBlockType
r_typedef
r_struct
id|FCBlockType
(brace
DECL|member|frame_status
id|__u16
id|frame_status
suffix:semicolon
multiline_comment|/* 02 */
DECL|member|info
id|__u16
id|info
suffix:semicolon
multiline_comment|/* 04 */
DECL|member|trc_next_ptr
id|__u32
id|trc_next_ptr
suffix:semicolon
multiline_comment|/* 08 */
DECL|member|trc_bdb_ptr
id|__u32
id|trc_bdb_ptr
suffix:semicolon
multiline_comment|/* 12 */
DECL|member|frame_length
id|__u16
id|frame_length
suffix:semicolon
multiline_comment|/* 14 */
DECL|member|bdb_ptr
id|BDBlock
op_star
id|bdb_ptr
suffix:semicolon
multiline_comment|/* 18 */
DECL|member|next_ptr
r_struct
id|FCBlockType
op_star
id|next_ptr
suffix:semicolon
multiline_comment|/* 22 */
DECL|member|back_ptr
r_struct
id|FCBlockType
op_star
id|back_ptr
suffix:semicolon
multiline_comment|/* 26 */
DECL|member|memory_alloc
id|__u16
id|memory_alloc
suffix:semicolon
multiline_comment|/* 28 */
DECL|member|filler
id|__u8
id|filler
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 32 */
DECL|typedef|FCBlock
)brace
id|FCBlock
suffix:semicolon
macro_line|#pragma pack(1)
DECL|struct|SBlockType
r_typedef
r_struct
id|SBlockType
(brace
DECL|member|Internal_Error_Count
id|__u8
id|Internal_Error_Count
suffix:semicolon
DECL|member|Line_Error_Count
id|__u8
id|Line_Error_Count
suffix:semicolon
DECL|member|AC_Error_Count
id|__u8
id|AC_Error_Count
suffix:semicolon
DECL|member|Burst_Error_Count
id|__u8
id|Burst_Error_Count
suffix:semicolon
DECL|member|RESERVED_COUNTER_0
id|__u8
id|RESERVED_COUNTER_0
suffix:semicolon
DECL|member|AD_TRANS_Count
id|__u8
id|AD_TRANS_Count
suffix:semicolon
DECL|member|RCV_Congestion_Count
id|__u8
id|RCV_Congestion_Count
suffix:semicolon
DECL|member|Lost_FR_Error_Count
id|__u8
id|Lost_FR_Error_Count
suffix:semicolon
DECL|member|FREQ_Error_Count
id|__u8
id|FREQ_Error_Count
suffix:semicolon
DECL|member|FR_Copied_Error_Count
id|__u8
id|FR_Copied_Error_Count
suffix:semicolon
DECL|member|RESERVED_COUNTER_1
id|__u8
id|RESERVED_COUNTER_1
suffix:semicolon
DECL|member|Token_Error_Count
id|__u8
id|Token_Error_Count
suffix:semicolon
DECL|member|TI_NDIS_Ring_Status
id|__u16
id|TI_NDIS_Ring_Status
suffix:semicolon
DECL|member|BCN_Type
id|__u16
id|BCN_Type
suffix:semicolon
DECL|member|Error_Code
id|__u16
id|Error_Code
suffix:semicolon
DECL|member|SA_of_Last_AMP_SMP
id|__u16
id|SA_of_Last_AMP_SMP
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|UNA
id|__u16
id|UNA
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|Ucode_Version_Number
id|__u16
id|Ucode_Version_Number
suffix:semicolon
DECL|member|Status_CHG_Indicate
id|__u16
id|Status_CHG_Indicate
suffix:semicolon
DECL|member|RESERVED_STATUS_0
id|__u16
id|RESERVED_STATUS_0
suffix:semicolon
DECL|typedef|SBlock
)brace
id|SBlock
suffix:semicolon
macro_line|#pragma pack(1)
DECL|struct|ACBlockType
r_typedef
r_struct
id|ACBlockType
(brace
DECL|member|cmd_done_status
id|__u16
id|cmd_done_status
suffix:semicolon
multiline_comment|/* 02 */
DECL|member|cmd_info
id|__u16
id|cmd_info
suffix:semicolon
multiline_comment|/* 04 */
DECL|member|trc_next_ptr
id|__u32
id|trc_next_ptr
suffix:semicolon
multiline_comment|/* 08 */
DECL|member|cmd
id|__u16
id|cmd
suffix:semicolon
multiline_comment|/* 10 */
DECL|member|subcmd
id|__u16
id|subcmd
suffix:semicolon
multiline_comment|/* 12 */
DECL|member|data_offset_lo
id|__u16
id|data_offset_lo
suffix:semicolon
multiline_comment|/* 14 */
DECL|member|data_offset_hi
id|__u16
id|data_offset_hi
suffix:semicolon
multiline_comment|/* 16 */
DECL|member|next_ptr
r_struct
id|ACBlockType
op_star
id|next_ptr
suffix:semicolon
multiline_comment|/* 20 */
DECL|member|filler
id|__u8
id|filler
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* 32 */
DECL|typedef|ACBlock
)brace
id|ACBlock
suffix:semicolon
DECL|macro|NUM_OF_INTERRUPTS
mdefine_line|#define NUM_OF_INTERRUPTS               0x20
macro_line|#pragma pack(1)
r_typedef
r_struct
(brace
DECL|member|IStatus
id|Interrupt_Status_Word
id|IStatus
(braket
id|NUM_OF_INTERRUPTS
)braket
suffix:semicolon
DECL|typedef|ISBlock
)brace
id|ISBlock
suffix:semicolon
macro_line|#pragma pack(1)
r_typedef
r_struct
(brace
DECL|member|valid_command
id|__u16
id|valid_command
suffix:semicolon
multiline_comment|/* 02 */
DECL|member|iack_code
id|__u16
id|iack_code
suffix:semicolon
multiline_comment|/* 04 */
DECL|member|resume_control
id|__u16
id|resume_control
suffix:semicolon
multiline_comment|/* 06 */
DECL|member|int_mask_control
id|__u16
id|int_mask_control
suffix:semicolon
multiline_comment|/* 08 */
DECL|member|int_mask_state
id|__u16
id|int_mask_state
suffix:semicolon
multiline_comment|/* 10 */
DECL|member|filler
id|__u8
id|filler
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* 16 */
DECL|typedef|SCLBlock
)brace
id|SCLBlock
suffix:semicolon
macro_line|#pragma pack(1)
r_typedef
r_struct
(brace
DECL|member|config
id|__u16
id|config
suffix:semicolon
multiline_comment|/* 02 */
DECL|member|trc_sclb_ptr
id|__u32
id|trc_sclb_ptr
suffix:semicolon
multiline_comment|/* 06 */
DECL|member|trc_acb_ptr
id|__u32
id|trc_acb_ptr
suffix:semicolon
multiline_comment|/* 10 */
DECL|member|trc_isb_ptr
id|__u32
id|trc_isb_ptr
suffix:semicolon
multiline_comment|/* 14 */
DECL|member|isbsiz
id|__u16
id|isbsiz
suffix:semicolon
multiline_comment|/* 16 */
DECL|member|sclb_ptr
id|SCLBlock
op_star
id|sclb_ptr
suffix:semicolon
multiline_comment|/* 20 */
DECL|member|acb_ptr
id|ACBlock
op_star
id|acb_ptr
suffix:semicolon
multiline_comment|/* 24 */
DECL|member|isb_ptr
id|ISBlock
op_star
id|isb_ptr
suffix:semicolon
multiline_comment|/* 28 */
DECL|member|Non_Mac_Rx_Bdbs
id|__u16
id|Non_Mac_Rx_Bdbs
suffix:semicolon
multiline_comment|/* 30 DEBUG */
DECL|member|filler
id|__u8
id|filler
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 32 */
DECL|typedef|SCGBlock
)brace
id|SCGBlock
suffix:semicolon
macro_line|#pragma pack(1)
r_typedef
r_struct
(brace
DECL|member|trc_scgb_ptr
id|__u32
id|trc_scgb_ptr
suffix:semicolon
DECL|member|scgb_ptr
id|SCGBlock
op_star
id|scgb_ptr
suffix:semicolon
DECL|typedef|ISCPBlock
)brace
id|ISCPBlock
suffix:semicolon
macro_line|#pragma pack()
DECL|struct|net_local
r_typedef
r_struct
id|net_local
(brace
DECL|member|iscpb_ptr
id|ISCPBlock
op_star
id|iscpb_ptr
suffix:semicolon
DECL|member|scgb_ptr
id|SCGBlock
op_star
id|scgb_ptr
suffix:semicolon
DECL|member|sclb_ptr
id|SCLBlock
op_star
id|sclb_ptr
suffix:semicolon
DECL|member|isb_ptr
id|ISBlock
op_star
id|isb_ptr
suffix:semicolon
DECL|member|acb_head
id|ACBlock
op_star
id|acb_head
suffix:semicolon
DECL|member|acb_curr
id|ACBlock
op_star
id|acb_curr
suffix:semicolon
DECL|member|acb_next
id|ACBlock
op_star
id|acb_next
suffix:semicolon
DECL|member|adapter_name
id|__u8
id|adapter_name
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|num_rx_bdbs
id|__u16
id|num_rx_bdbs
(braket
id|NUM_RX_QS_USED
)braket
suffix:semicolon
DECL|member|num_rx_fcbs
id|__u16
id|num_rx_fcbs
(braket
id|NUM_RX_QS_USED
)braket
suffix:semicolon
DECL|member|num_tx_bdbs
id|__u16
id|num_tx_bdbs
(braket
id|NUM_TX_QS_USED
)braket
suffix:semicolon
DECL|member|num_tx_fcbs
id|__u16
id|num_tx_fcbs
(braket
id|NUM_TX_QS_USED
)braket
suffix:semicolon
DECL|member|num_of_tx_buffs
id|__u16
id|num_of_tx_buffs
suffix:semicolon
DECL|member|tx_buff_size
id|__u16
id|tx_buff_size
(braket
id|NUM_TX_QS_USED
)braket
suffix:semicolon
DECL|member|tx_buff_used
id|__u16
id|tx_buff_used
(braket
id|NUM_TX_QS_USED
)braket
suffix:semicolon
DECL|member|tx_queue_status
id|__u16
id|tx_queue_status
(braket
id|NUM_TX_QS_USED
)braket
suffix:semicolon
DECL|member|tx_fcb_head
id|FCBlock
op_star
id|tx_fcb_head
(braket
id|NUM_TX_QS_USED
)braket
suffix:semicolon
DECL|member|tx_fcb_curr
id|FCBlock
op_star
id|tx_fcb_curr
(braket
id|NUM_TX_QS_USED
)braket
suffix:semicolon
DECL|member|tx_fcb_end
id|FCBlock
op_star
id|tx_fcb_end
(braket
id|NUM_TX_QS_USED
)braket
suffix:semicolon
DECL|member|tx_bdb_head
id|BDBlock
op_star
id|tx_bdb_head
(braket
id|NUM_TX_QS_USED
)braket
suffix:semicolon
DECL|member|tx_buff_head
id|__u16
op_star
id|tx_buff_head
(braket
id|NUM_TX_QS_USED
)braket
suffix:semicolon
DECL|member|tx_buff_end
id|__u16
op_star
id|tx_buff_end
(braket
id|NUM_TX_QS_USED
)braket
suffix:semicolon
DECL|member|tx_buff_curr
id|__u16
op_star
id|tx_buff_curr
(braket
id|NUM_TX_QS_USED
)braket
suffix:semicolon
DECL|member|num_tx_fcbs_used
id|__u16
id|num_tx_fcbs_used
(braket
id|NUM_TX_QS_USED
)braket
suffix:semicolon
DECL|member|rx_fcb_head
id|FCBlock
op_star
id|rx_fcb_head
(braket
id|NUM_RX_QS_USED
)braket
suffix:semicolon
DECL|member|rx_fcb_curr
id|FCBlock
op_star
id|rx_fcb_curr
(braket
id|NUM_RX_QS_USED
)braket
suffix:semicolon
DECL|member|rx_bdb_head
id|BDBlock
op_star
id|rx_bdb_head
(braket
id|NUM_RX_QS_USED
)braket
suffix:semicolon
DECL|member|rx_bdb_curr
id|BDBlock
op_star
id|rx_bdb_curr
(braket
id|NUM_RX_QS_USED
)braket
suffix:semicolon
DECL|member|rx_bdb_end
id|BDBlock
op_star
id|rx_bdb_end
(braket
id|NUM_RX_QS_USED
)braket
suffix:semicolon
DECL|member|rx_buff_head
id|__u16
op_star
id|rx_buff_head
(braket
id|NUM_RX_QS_USED
)braket
suffix:semicolon
DECL|member|rx_buff_end
id|__u16
op_star
id|rx_buff_end
(braket
id|NUM_RX_QS_USED
)braket
suffix:semicolon
DECL|member|ptr_local_ring_num
id|__u32
op_star
id|ptr_local_ring_num
suffix:semicolon
DECL|member|sh_mem_used
id|__u32
id|sh_mem_used
suffix:semicolon
DECL|member|page_offset_mask
id|__u16
id|page_offset_mask
suffix:semicolon
DECL|member|authorized_function_classes
id|__u16
id|authorized_function_classes
suffix:semicolon
DECL|member|authorized_access_priority
id|__u16
id|authorized_access_priority
suffix:semicolon
DECL|member|num_acbs
id|__u16
id|num_acbs
suffix:semicolon
DECL|member|num_acbs_used
id|__u16
id|num_acbs_used
suffix:semicolon
DECL|member|acb_pending
id|__u16
id|acb_pending
suffix:semicolon
DECL|member|current_isb_index
id|__u16
id|current_isb_index
suffix:semicolon
DECL|member|monitor_state
id|__u8
id|monitor_state
suffix:semicolon
DECL|member|monitor_state_ready
id|__u8
id|monitor_state_ready
suffix:semicolon
DECL|member|ring_status
id|__u16
id|ring_status
suffix:semicolon
DECL|member|ring_status_flags
id|__u8
id|ring_status_flags
suffix:semicolon
DECL|member|current_ring_status
id|__u8
id|current_ring_status
suffix:semicolon
DECL|member|state
id|__u8
id|state
suffix:semicolon
DECL|member|join_state
id|__u8
id|join_state
suffix:semicolon
DECL|member|slot_num
id|__u8
id|slot_num
suffix:semicolon
DECL|member|pos_id
id|__u16
id|pos_id
suffix:semicolon
DECL|member|ptr_una
id|__u32
op_star
id|ptr_una
suffix:semicolon
DECL|member|ptr_bcn_type
id|__u32
op_star
id|ptr_bcn_type
suffix:semicolon
DECL|member|ptr_tx_fifo_underruns
id|__u32
op_star
id|ptr_tx_fifo_underruns
suffix:semicolon
DECL|member|ptr_rx_fifo_underruns
id|__u32
op_star
id|ptr_rx_fifo_underruns
suffix:semicolon
DECL|member|ptr_rx_fifo_overruns
id|__u32
op_star
id|ptr_rx_fifo_overruns
suffix:semicolon
DECL|member|ptr_tx_fifo_overruns
id|__u32
op_star
id|ptr_tx_fifo_overruns
suffix:semicolon
DECL|member|ptr_tx_fcb_overruns
id|__u32
op_star
id|ptr_tx_fcb_overruns
suffix:semicolon
DECL|member|ptr_rx_fcb_overruns
id|__u32
op_star
id|ptr_rx_fcb_overruns
suffix:semicolon
DECL|member|ptr_tx_bdb_overruns
id|__u32
op_star
id|ptr_tx_bdb_overruns
suffix:semicolon
DECL|member|ptr_rx_bdb_overruns
id|__u32
op_star
id|ptr_rx_bdb_overruns
suffix:semicolon
DECL|member|receive_queue_number
id|__u16
id|receive_queue_number
suffix:semicolon
DECL|member|rx_fifo_overrun_count
id|__u8
id|rx_fifo_overrun_count
suffix:semicolon
DECL|member|tx_fifo_overrun_count
id|__u8
id|tx_fifo_overrun_count
suffix:semicolon
DECL|member|adapter_flags
id|__u16
id|adapter_flags
suffix:semicolon
DECL|member|adapter_flags1
id|__u16
id|adapter_flags1
suffix:semicolon
DECL|member|misc_command_data
id|__u16
op_star
id|misc_command_data
suffix:semicolon
DECL|member|max_packet_size
id|__u16
id|max_packet_size
suffix:semicolon
DECL|member|config_word0
id|__u16
id|config_word0
suffix:semicolon
DECL|member|config_word1
id|__u16
id|config_word1
suffix:semicolon
DECL|member|trc_mask
id|__u8
id|trc_mask
suffix:semicolon
DECL|member|source_ring_number
id|__u16
id|source_ring_number
suffix:semicolon
DECL|member|target_ring_number
id|__u16
id|target_ring_number
suffix:semicolon
DECL|member|microcode_version
id|__u16
id|microcode_version
suffix:semicolon
DECL|member|bic_type
id|__u16
id|bic_type
suffix:semicolon
DECL|member|nic_type
id|__u16
id|nic_type
suffix:semicolon
DECL|member|board_id
id|__u16
id|board_id
suffix:semicolon
DECL|member|rom_size
id|__u16
id|rom_size
suffix:semicolon
DECL|member|rom_base
id|__u32
id|rom_base
suffix:semicolon
DECL|member|ram_size
id|__u16
id|ram_size
suffix:semicolon
DECL|member|ram_usable
id|__u16
id|ram_usable
suffix:semicolon
DECL|member|ram_base
id|__u32
id|ram_base
suffix:semicolon
DECL|member|ram_access
id|__u32
id|ram_access
suffix:semicolon
DECL|member|extra_info
id|__u16
id|extra_info
suffix:semicolon
DECL|member|mode_bits
id|__u16
id|mode_bits
suffix:semicolon
DECL|member|media_menu
id|__u16
id|media_menu
suffix:semicolon
DECL|member|media_type
id|__u16
id|media_type
suffix:semicolon
DECL|member|adapter_bus
id|__u16
id|adapter_bus
suffix:semicolon
DECL|member|status
id|__u16
id|status
suffix:semicolon
DECL|member|receive_mask
id|__u16
id|receive_mask
suffix:semicolon
DECL|member|group_address_0
id|__u16
id|group_address_0
suffix:semicolon
DECL|member|group_address
id|__u16
id|group_address
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|functional_address_0
id|__u16
id|functional_address_0
suffix:semicolon
DECL|member|functional_address
id|__u16
id|functional_address
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|bitwise_group_address
id|__u16
id|bitwise_group_address
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ptr_ucode
id|__u8
op_star
id|ptr_ucode
suffix:semicolon
DECL|member|cleanup
id|__u8
id|cleanup
suffix:semicolon
DECL|member|SendSkbQueue
r_struct
id|sk_buff_head
id|SendSkbQueue
suffix:semicolon
DECL|member|QueueSkb
id|__u16
id|QueueSkb
suffix:semicolon
DECL|member|MacStat
r_struct
id|tr_statistics
id|MacStat
suffix:semicolon
multiline_comment|/* MAC statistics structure */
DECL|typedef|NET_LOCAL
)brace
id|NET_LOCAL
suffix:semicolon
multiline_comment|/************************************&n; * SNMP-ON-BOARD Agent Link Structure&n; ************************************/
r_typedef
r_struct
(brace
DECL|member|LnkSigStr
id|__u8
id|LnkSigStr
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* signature string &quot;SmcLinkTable&quot; */
DECL|member|LnkDrvTyp
id|__u8
id|LnkDrvTyp
suffix:semicolon
multiline_comment|/* 1=Redbox ODI, 2=ODI DOS, 3=ODI OS/2, 4=NDIS DOS */
DECL|member|LnkFlg
id|__u8
id|LnkFlg
suffix:semicolon
multiline_comment|/* 0 if no agent linked, 1 if agent linked */
DECL|member|LnkNfo
r_void
op_star
id|LnkNfo
suffix:semicolon
multiline_comment|/* routine which returns pointer to NIC info */
DECL|member|LnkAgtRcv
r_void
op_star
id|LnkAgtRcv
suffix:semicolon
multiline_comment|/* pointer to agent receive trap entry */
DECL|member|LnkAgtXmt
r_void
op_star
id|LnkAgtXmt
suffix:semicolon
multiline_comment|/* pointer to agent transmit trap&n;entry  */
DECL|member|LnkGet
r_void
op_star
id|LnkGet
suffix:semicolon
multiline_comment|/* pointer to NIC receive data&n;copy routine */
DECL|member|LnkSnd
r_void
op_star
id|LnkSnd
suffix:semicolon
multiline_comment|/* pointer to NIC send routine&n;*/
DECL|member|LnkRst
r_void
op_star
id|LnkRst
suffix:semicolon
multiline_comment|/* pointer to NIC driver reset&n;routine */
DECL|member|LnkMib
r_void
op_star
id|LnkMib
suffix:semicolon
multiline_comment|/* pointer to MIB data base */
DECL|member|LnkMibAct
r_void
op_star
id|LnkMibAct
suffix:semicolon
multiline_comment|/* pointer to MIB action routine list */
DECL|member|LnkCntOffset
id|__u16
id|LnkCntOffset
suffix:semicolon
multiline_comment|/* offset to error counters */
DECL|member|LnkCntNum
id|__u16
id|LnkCntNum
suffix:semicolon
multiline_comment|/* number of error counters */
DECL|member|LnkCntSize
id|__u16
id|LnkCntSize
suffix:semicolon
multiline_comment|/* size of error counters i.e. 32 = 32 bits */
DECL|member|LnkISR
r_void
op_star
id|LnkISR
suffix:semicolon
multiline_comment|/* pointer to interrupt vector */
DECL|member|LnkFrmTyp
id|__u8
id|LnkFrmTyp
suffix:semicolon
multiline_comment|/* 1=Ethernet, 2=Token Ring */
DECL|member|LnkDrvVer1
id|__u8
id|LnkDrvVer1
suffix:semicolon
multiline_comment|/* driver major version */
DECL|member|LnkDrvVer2
id|__u8
id|LnkDrvVer2
suffix:semicolon
multiline_comment|/* driver minor version */
DECL|typedef|AgentLink
)brace
id|AgentLink
suffix:semicolon
multiline_comment|/*&n; * Definitions for pcm_card_flags(bit_mapped)&n; */
DECL|macro|REG_COMPLETE
mdefine_line|#define REG_COMPLETE   0x0001
DECL|macro|INSERTED
mdefine_line|#define INSERTED       0x0002
DECL|macro|PCC_INSERTED
mdefine_line|#define PCC_INSERTED   0x0004         /* 1=currently inserted, 0=cur removed */
multiline_comment|/*&n; * Adapter RAM test patterns&n; */
DECL|macro|RAM_PATTERN_1
mdefine_line|#define RAM_PATTERN_1  0x55AA
DECL|macro|RAM_PATTERN_2
mdefine_line|#define RAM_PATTERN_2  0x9249
DECL|macro|RAM_PATTERN_3
mdefine_line|#define RAM_PATTERN_3  0xDB6D
multiline_comment|/*&n; * definitions for RAM test&n; */
DECL|macro|ROM_SIGNATURE
mdefine_line|#define ROM_SIGNATURE  0xAA55
DECL|macro|MIN_ROM_SIZE
mdefine_line|#define MIN_ROM_SIZE   0x2000
multiline_comment|/*&n; * Return Codes&n; */
DECL|macro|SUCCESS
mdefine_line|#define SUCCESS                 0x0000
DECL|macro|ADAPTER_AND_CONFIG
mdefine_line|#define ADAPTER_AND_CONFIG      0x0001
DECL|macro|ADAPTER_NO_CONFIG
mdefine_line|#define ADAPTER_NO_CONFIG       0x0002
DECL|macro|NOT_MY_INTERRUPT
mdefine_line|#define NOT_MY_INTERRUPT        0x0003
DECL|macro|FRAME_REJECTED
mdefine_line|#define FRAME_REJECTED          0x0004
DECL|macro|EVENTS_DISABLED
mdefine_line|#define EVENTS_DISABLED         0x0005
DECL|macro|OUT_OF_RESOURCES
mdefine_line|#define OUT_OF_RESOURCES        0x0006
DECL|macro|INVALID_PARAMETER
mdefine_line|#define INVALID_PARAMETER       0x0007
DECL|macro|INVALID_FUNCTION
mdefine_line|#define INVALID_FUNCTION        0x0008
DECL|macro|INITIALIZE_FAILED
mdefine_line|#define INITIALIZE_FAILED       0x0009
DECL|macro|CLOSE_FAILED
mdefine_line|#define CLOSE_FAILED            0x000A
DECL|macro|MAX_COLLISIONS
mdefine_line|#define MAX_COLLISIONS          0x000B
DECL|macro|NO_SUCH_DESTINATION
mdefine_line|#define NO_SUCH_DESTINATION     0x000C
DECL|macro|BUFFER_TOO_SMALL_ERROR
mdefine_line|#define BUFFER_TOO_SMALL_ERROR  0x000D
DECL|macro|ADAPTER_CLOSED
mdefine_line|#define ADAPTER_CLOSED          0x000E
DECL|macro|UCODE_NOT_PRESENT
mdefine_line|#define UCODE_NOT_PRESENT       0x000F
DECL|macro|FIFO_UNDERRUN
mdefine_line|#define FIFO_UNDERRUN           0x0010
DECL|macro|DEST_OUT_OF_RESOURCES
mdefine_line|#define DEST_OUT_OF_RESOURCES   0x0011
DECL|macro|ADAPTER_NOT_INITIALIZED
mdefine_line|#define ADAPTER_NOT_INITIALIZED 0x0012
DECL|macro|PENDING
mdefine_line|#define PENDING                 0x0013
DECL|macro|UCODE_PRESENT
mdefine_line|#define UCODE_PRESENT           0x0014
DECL|macro|NOT_INIT_BY_BRIDGE
mdefine_line|#define NOT_INIT_BY_BRIDGE      0x0015
DECL|macro|OPEN_FAILED
mdefine_line|#define OPEN_FAILED             0x0080
DECL|macro|HARDWARE_FAILED
mdefine_line|#define HARDWARE_FAILED         0x0081
DECL|macro|SELF_TEST_FAILED
mdefine_line|#define SELF_TEST_FAILED        0x0082
DECL|macro|RAM_TEST_FAILED
mdefine_line|#define RAM_TEST_FAILED         0x0083
DECL|macro|RAM_CONFLICT
mdefine_line|#define RAM_CONFLICT            0x0084
DECL|macro|ROM_CONFLICT
mdefine_line|#define ROM_CONFLICT            0x0085
DECL|macro|UNKNOWN_ADAPTER
mdefine_line|#define UNKNOWN_ADAPTER         0x0086
DECL|macro|CONFIG_ERROR
mdefine_line|#define CONFIG_ERROR            0x0087
DECL|macro|CONFIG_WARNING
mdefine_line|#define CONFIG_WARNING          0x0088
DECL|macro|NO_FIXED_CNFG
mdefine_line|#define NO_FIXED_CNFG           0x0089
DECL|macro|EEROM_CKSUM_ERROR
mdefine_line|#define EEROM_CKSUM_ERROR       0x008A
DECL|macro|ROM_SIGNATURE_ERROR
mdefine_line|#define ROM_SIGNATURE_ERROR     0x008B
DECL|macro|ROM_CHECKSUM_ERROR
mdefine_line|#define ROM_CHECKSUM_ERROR      0x008C
DECL|macro|ROM_SIZE_ERROR
mdefine_line|#define ROM_SIZE_ERROR          0x008D
DECL|macro|UNSUPPORTED_NIC_CHIP
mdefine_line|#define UNSUPPORTED_NIC_CHIP    0x008E
DECL|macro|NIC_REG_ERROR
mdefine_line|#define NIC_REG_ERROR           0x008F
DECL|macro|BIC_REG_ERROR
mdefine_line|#define BIC_REG_ERROR           0x0090
DECL|macro|MICROCODE_TEST_ERROR
mdefine_line|#define MICROCODE_TEST_ERROR    0x0091
DECL|macro|LOBE_MEDIA_TEST_FAILED
mdefine_line|#define LOBE_MEDIA_TEST_FAILED  0x0092
DECL|macro|ADAPTER_FOUND_LAN_CORRUPT
mdefine_line|#define ADAPTER_FOUND_LAN_CORRUPT 0x009B
DECL|macro|ADAPTER_NOT_FOUND
mdefine_line|#define ADAPTER_NOT_FOUND       0xFFFF
DECL|macro|ILLEGAL_FUNCTION
mdefine_line|#define ILLEGAL_FUNCTION        INVALID_FUNCTION
multiline_comment|/* Errors */
DECL|macro|IO_BASE_INVALID
mdefine_line|#define IO_BASE_INVALID         0x0001
DECL|macro|IO_BASE_RANGE
mdefine_line|#define IO_BASE_RANGE           0x0002
DECL|macro|IRQ_INVALID
mdefine_line|#define IRQ_INVALID             0x0004
DECL|macro|IRQ_RANGE
mdefine_line|#define IRQ_RANGE               0x0008
DECL|macro|RAM_BASE_INVALID
mdefine_line|#define RAM_BASE_INVALID        0x0010
DECL|macro|RAM_BASE_RANGE
mdefine_line|#define RAM_BASE_RANGE          0x0020
DECL|macro|RAM_SIZE_RANGE
mdefine_line|#define RAM_SIZE_RANGE          0x0040
DECL|macro|MEDIA_INVALID
mdefine_line|#define MEDIA_INVALID           0x0800
multiline_comment|/* Warnings */
DECL|macro|IRQ_MISMATCH
mdefine_line|#define IRQ_MISMATCH            0x0080
DECL|macro|RAM_BASE_MISMATCH
mdefine_line|#define RAM_BASE_MISMATCH       0x0100
DECL|macro|RAM_SIZE_MISMATCH
mdefine_line|#define RAM_SIZE_MISMATCH       0x0200
DECL|macro|BUS_MODE_MISMATCH
mdefine_line|#define BUS_MODE_MISMATCH       0x0400
DECL|macro|RX_CRC_ERROR
mdefine_line|#define RX_CRC_ERROR                            0x01
DECL|macro|RX_ALIGNMENT_ERROR
mdefine_line|#define RX_ALIGNMENT_ERROR              0x02
DECL|macro|RX_HW_FAILED
mdefine_line|#define RX_HW_FAILED                            0x80
multiline_comment|/*&n; * Definitions for the field RING_STATUS_FLAGS&n; */
DECL|macro|RING_STATUS_CHANGED
mdefine_line|#define RING_STATUS_CHANGED                     0X01
DECL|macro|MONITOR_STATE_CHANGED
mdefine_line|#define MONITOR_STATE_CHANGED                   0X02
DECL|macro|JOIN_STATE_CHANGED
mdefine_line|#define JOIN_STATE_CHANGED                      0X04
multiline_comment|/*&n; * Definitions for the field JOIN_STATE&n; */
DECL|macro|JS_BYPASS_STATE
mdefine_line|#define JS_BYPASS_STATE                         0x00
DECL|macro|JS_LOBE_TEST_STATE
mdefine_line|#define JS_LOBE_TEST_STATE                      0x01
DECL|macro|JS_DETECT_MONITOR_PRESENT_STATE
mdefine_line|#define JS_DETECT_MONITOR_PRESENT_STATE         0x02
DECL|macro|JS_AWAIT_NEW_MONITOR_STATE
mdefine_line|#define JS_AWAIT_NEW_MONITOR_STATE              0x03
DECL|macro|JS_DUPLICATE_ADDRESS_TEST_STATE
mdefine_line|#define JS_DUPLICATE_ADDRESS_TEST_STATE         0x04
DECL|macro|JS_NEIGHBOR_NOTIFICATION_STATE
mdefine_line|#define JS_NEIGHBOR_NOTIFICATION_STATE          0x05
DECL|macro|JS_REQUEST_INITIALIZATION_STATE
mdefine_line|#define JS_REQUEST_INITIALIZATION_STATE         0x06
DECL|macro|JS_JOIN_COMPLETE_STATE
mdefine_line|#define JS_JOIN_COMPLETE_STATE                  0x07
DECL|macro|JS_BYPASS_WAIT_STATE
mdefine_line|#define JS_BYPASS_WAIT_STATE                    0x08
multiline_comment|/*&n; * Definitions for the field MONITOR_STATE&n; */
DECL|macro|MS_MONITOR_FSM_INACTIVE
mdefine_line|#define MS_MONITOR_FSM_INACTIVE                 0x00
DECL|macro|MS_REPEAT_BEACON_STATE
mdefine_line|#define MS_REPEAT_BEACON_STATE                  0x01
DECL|macro|MS_REPEAT_CLAIM_TOKEN_STATE
mdefine_line|#define MS_REPEAT_CLAIM_TOKEN_STATE             0x02
DECL|macro|MS_TRANSMIT_CLAIM_TOKEN_STATE
mdefine_line|#define MS_TRANSMIT_CLAIM_TOKEN_STATE           0x03
DECL|macro|MS_STANDBY_MONITOR_STATE
mdefine_line|#define MS_STANDBY_MONITOR_STATE                0x04
DECL|macro|MS_TRANSMIT_BEACON_STATE
mdefine_line|#define MS_TRANSMIT_BEACON_STATE                0x05
DECL|macro|MS_ACTIVE_MONITOR_STATE
mdefine_line|#define MS_ACTIVE_MONITOR_STATE                 0x06
DECL|macro|MS_TRANSMIT_RING_PURGE_STATE
mdefine_line|#define MS_TRANSMIT_RING_PURGE_STATE            0x07
DECL|macro|MS_BEACON_TEST_STATE
mdefine_line|#define MS_BEACON_TEST_STATE                    0x09
multiline_comment|/*&n; * Definitions for the bit-field RING_STATUS&n; */
DECL|macro|SIGNAL_LOSS
mdefine_line|#define SIGNAL_LOSS                             0x8000
DECL|macro|HARD_ERROR
mdefine_line|#define HARD_ERROR                              0x4000
DECL|macro|SOFT_ERROR
mdefine_line|#define SOFT_ERROR                              0x2000
DECL|macro|TRANSMIT_BEACON
mdefine_line|#define TRANSMIT_BEACON                         0x1000
DECL|macro|LOBE_WIRE_FAULT
mdefine_line|#define LOBE_WIRE_FAULT                         0x0800
DECL|macro|AUTO_REMOVAL_ERROR
mdefine_line|#define AUTO_REMOVAL_ERROR                      0x0400
DECL|macro|REMOVE_RECEIVED
mdefine_line|#define REMOVE_RECEIVED                         0x0100
DECL|macro|COUNTER_OVERFLOW
mdefine_line|#define COUNTER_OVERFLOW                        0x0080
DECL|macro|SINGLE_STATION
mdefine_line|#define SINGLE_STATION                          0x0040
DECL|macro|RING_RECOVERY
mdefine_line|#define RING_RECOVERY                           0x0020
multiline_comment|/*&n; * Definitions for the field BUS_TYPE&n; */
DECL|macro|AT_BUS
mdefine_line|#define AT_BUS                  0x00
DECL|macro|MCA_BUS
mdefine_line|#define MCA_BUS                 0x01
DECL|macro|EISA_BUS
mdefine_line|#define EISA_BUS                0x02
DECL|macro|PCI_BUS
mdefine_line|#define PCI_BUS                 0x03
DECL|macro|PCMCIA_BUS
mdefine_line|#define PCMCIA_BUS              0x04
multiline_comment|/*&n; * Definitions for adapter_flags&n; */
DECL|macro|RX_VALID_LOOKAHEAD
mdefine_line|#define RX_VALID_LOOKAHEAD      0x0001
DECL|macro|FORCED_16BIT_MODE
mdefine_line|#define FORCED_16BIT_MODE       0x0002
DECL|macro|ADAPTER_DISABLED
mdefine_line|#define ADAPTER_DISABLED        0x0004
DECL|macro|TRANSMIT_CHAIN_INT
mdefine_line|#define TRANSMIT_CHAIN_INT      0x0008
DECL|macro|EARLY_RX_FRAME
mdefine_line|#define EARLY_RX_FRAME          0x0010
DECL|macro|EARLY_TX
mdefine_line|#define EARLY_TX                0x0020
DECL|macro|EARLY_RX_COPY
mdefine_line|#define EARLY_RX_COPY           0x0040
DECL|macro|USES_PHYSICAL_ADDR
mdefine_line|#define USES_PHYSICAL_ADDR      0x0080&t;&t;/* Rsvd for DEC PCI and 9232 */
DECL|macro|NEEDS_PHYSICAL_ADDR
mdefine_line|#define NEEDS_PHYSICAL_ADDR  &t;0x0100       &t;/* Reserved*/
DECL|macro|RX_STATUS_PENDING
mdefine_line|#define RX_STATUS_PENDING       0x0200
DECL|macro|ERX_DISABLED
mdefine_line|#define ERX_DISABLED         &t;0x0400       &t;/* EARLY_RX_ENABLE rcv_mask */
DECL|macro|ENABLE_TX_PENDING
mdefine_line|#define ENABLE_TX_PENDING       0x0800
DECL|macro|ENABLE_RX_PENDING
mdefine_line|#define ENABLE_RX_PENDING       0x1000
DECL|macro|PERM_CLOSE
mdefine_line|#define PERM_CLOSE              0x2000  
DECL|macro|IO_MAPPED
mdefine_line|#define IO_MAPPED               0x4000  &t;/* IOmapped bus interface 795 */
DECL|macro|ETX_DISABLED
mdefine_line|#define ETX_DISABLED            0x8000
multiline_comment|/*&n; * Definitions for adapter_flags1&n; */
DECL|macro|TX_PHY_RX_VIRT
mdefine_line|#define TX_PHY_RX_VIRT          0x0001 
DECL|macro|NEEDS_HOST_RAM
mdefine_line|#define NEEDS_HOST_RAM          0x0002
DECL|macro|NEEDS_MEDIA_TYPE
mdefine_line|#define NEEDS_MEDIA_TYPE        0x0004
DECL|macro|EARLY_RX_DONE
mdefine_line|#define EARLY_RX_DONE           0x0008
DECL|macro|PNP_BOOT_BIT
mdefine_line|#define PNP_BOOT_BIT            0x0010  /* activates PnP &amp; config on power-up */
multiline_comment|/* clear =&gt; regular PnP operation */
DECL|macro|PNP_ENABLE
mdefine_line|#define PNP_ENABLE              0x0020  /* regular PnP operation clear =&gt; */
multiline_comment|/* no PnP, overrides PNP_BOOT_BIT */
DECL|macro|SATURN_ENABLE
mdefine_line|#define SATURN_ENABLE           0x0040
DECL|macro|ADAPTER_REMOVABLE
mdefine_line|#define ADAPTER_REMOVABLE       0x0080 &t;/* adapter is hot swappable */
DECL|macro|TX_PHY
mdefine_line|#define TX_PHY                  0x0100  /* Uses physical address for tx bufs */
DECL|macro|RX_PHY
mdefine_line|#define RX_PHY                  0x0200  /* Uses physical address for rx bufs */
DECL|macro|TX_VIRT
mdefine_line|#define TX_VIRT                 0x0400  /* Uses virtual addr for tx bufs */
DECL|macro|RX_VIRT
mdefine_line|#define RX_VIRT                 0x0800 
DECL|macro|NEEDS_SERVICE
mdefine_line|#define NEEDS_SERVICE           0x1000 
multiline_comment|/*&n; * Adapter Status Codes&n; */
DECL|macro|OPEN
mdefine_line|#define OPEN                    0x0001
DECL|macro|INITIALIZED
mdefine_line|#define INITIALIZED             0x0002
DECL|macro|CLOSED
mdefine_line|#define CLOSED                  0x0003
DECL|macro|FAILED
mdefine_line|#define FAILED                  0x0005
DECL|macro|NOT_INITIALIZED
mdefine_line|#define NOT_INITIALIZED         0x0006
DECL|macro|IO_CONFLICT
mdefine_line|#define IO_CONFLICT             0x0007
DECL|macro|CARD_REMOVED
mdefine_line|#define CARD_REMOVED            0x0008
DECL|macro|CARD_INSERTED
mdefine_line|#define CARD_INSERTED           0x0009
multiline_comment|/*&n; * Mode Bit Definitions&n; */
DECL|macro|INTERRUPT_STATUS_BIT
mdefine_line|#define INTERRUPT_STATUS_BIT    0x8000  /* PC Interrupt Line: 0 = Not Enabled */
DECL|macro|BOOT_STATUS_MASK
mdefine_line|#define BOOT_STATUS_MASK        0x6000  /* Mask to isolate BOOT_STATUS */
DECL|macro|BOOT_INHIBIT
mdefine_line|#define BOOT_INHIBIT            0x0000  /* BOOT_STATUS is &squot;inhibited&squot; */
DECL|macro|BOOT_TYPE_1
mdefine_line|#define BOOT_TYPE_1             0x2000  /* Unused BOOT_STATUS value */
DECL|macro|BOOT_TYPE_2
mdefine_line|#define BOOT_TYPE_2             0x4000  /* Unused BOOT_STATUS value */
DECL|macro|BOOT_TYPE_3
mdefine_line|#define BOOT_TYPE_3             0x6000  /* Unused BOOT_STATUS value */
DECL|macro|ZERO_WAIT_STATE_MASK
mdefine_line|#define ZERO_WAIT_STATE_MASK    0x1800  /* Mask to isolate Wait State flags */
DECL|macro|ZERO_WAIT_STATE_8_BIT
mdefine_line|#define ZERO_WAIT_STATE_8_BIT   0x1000  /* 0 = Disabled (Inserts Wait States) */
DECL|macro|ZERO_WAIT_STATE_16_BIT
mdefine_line|#define ZERO_WAIT_STATE_16_BIT  0x0800  /* 0 = Disabled (Inserts Wait States) */
DECL|macro|LOOPING_MODE_MASK
mdefine_line|#define LOOPING_MODE_MASK       0x0007
DECL|macro|LOOPBACK_MODE_0
mdefine_line|#define LOOPBACK_MODE_0         0x0000
DECL|macro|LOOPBACK_MODE_1
mdefine_line|#define LOOPBACK_MODE_1         0x0001
DECL|macro|LOOPBACK_MODE_2
mdefine_line|#define LOOPBACK_MODE_2         0x0002
DECL|macro|LOOPBACK_MODE_3
mdefine_line|#define LOOPBACK_MODE_3         0x0003
DECL|macro|LOOPBACK_MODE_4
mdefine_line|#define LOOPBACK_MODE_4         0x0004
DECL|macro|LOOPBACK_MODE_5
mdefine_line|#define LOOPBACK_MODE_5         0x0005
DECL|macro|LOOPBACK_MODE_6
mdefine_line|#define LOOPBACK_MODE_6         0x0006
DECL|macro|LOOPBACK_MODE_7
mdefine_line|#define LOOPBACK_MODE_7         0x0007
DECL|macro|AUTO_MEDIA_DETECT
mdefine_line|#define AUTO_MEDIA_DETECT       0x0008
DECL|macro|MANUAL_CRC
mdefine_line|#define MANUAL_CRC              0x0010
DECL|macro|EARLY_TOKEN_REL
mdefine_line|#define EARLY_TOKEN_REL         0x0020  /* Early Token Release for Token Ring */
DECL|macro|UMAC
mdefine_line|#define UMAC               0x0040 
DECL|macro|UTP2_PORT
mdefine_line|#define UTP2_PORT               0x0080  /* For 8216T2, 0=port A, 1=Port B. */
DECL|macro|BNC_10BT_INTERFACE
mdefine_line|#define BNC_10BT_INTERFACE      0x0600  /* BNC and UTP current media set */
DECL|macro|UTP_INTERFACE
mdefine_line|#define UTP_INTERFACE           0x0500  /* Ethernet UTP Only. */
DECL|macro|BNC_INTERFACE
mdefine_line|#define BNC_INTERFACE           0x0400
DECL|macro|AUI_INTERFACE
mdefine_line|#define AUI_INTERFACE           0x0300
DECL|macro|AUI_10BT_INTERFACE
mdefine_line|#define AUI_10BT_INTERFACE      0x0200
DECL|macro|STARLAN_10_INTERFACE
mdefine_line|#define STARLAN_10_INTERFACE    0x0100
DECL|macro|INTERFACE_TYPE_MASK
mdefine_line|#define INTERFACE_TYPE_MASK     0x0700
multiline_comment|/*&n; * Media Type Bit Definitions&n; *&n; * legend:      TP = Twisted Pair&n; *              STP = Shielded twisted pair&n; *              UTP = Unshielded twisted pair&n; */
DECL|macro|CNFG_MEDIA_TYPE_MASK
mdefine_line|#define CNFG_MEDIA_TYPE_MASK    0x001e  /* POS Register 3 Mask         */
DECL|macro|MEDIA_S10
mdefine_line|#define MEDIA_S10               0x0000  /* Ethernet adapter, TP.        */
DECL|macro|MEDIA_AUI_UTP
mdefine_line|#define MEDIA_AUI_UTP           0x0001  /* Ethernet adapter, AUI/UTP media */
DECL|macro|MEDIA_BNC
mdefine_line|#define MEDIA_BNC               0x0002  /* Ethernet adapter, BNC media. */
DECL|macro|MEDIA_AUI
mdefine_line|#define MEDIA_AUI               0x0003  /* Ethernet Adapter, AUI media. */
DECL|macro|MEDIA_STP_16
mdefine_line|#define MEDIA_STP_16            0x0004  /* TokenRing adap, 16Mbit STP.  */
DECL|macro|MEDIA_STP_4
mdefine_line|#define MEDIA_STP_4             0x0005  /* TokenRing adap, 4Mbit STP.   */
DECL|macro|MEDIA_UTP_16
mdefine_line|#define MEDIA_UTP_16            0x0006  /* TokenRing adap, 16Mbit UTP.  */
DECL|macro|MEDIA_UTP_4
mdefine_line|#define MEDIA_UTP_4             0x0007  /* TokenRing adap, 4Mbit UTP.   */
DECL|macro|MEDIA_UTP
mdefine_line|#define MEDIA_UTP               0x0008  /* Ethernet adapter, UTP media (no AUI)&n;*/
DECL|macro|MEDIA_BNC_UTP
mdefine_line|#define MEDIA_BNC_UTP           0x0010  /* Ethernet adapter, BNC/UTP media */
DECL|macro|MEDIA_UTPFD
mdefine_line|#define MEDIA_UTPFD             0x0011  /* Ethernet adapter, TP full duplex */
DECL|macro|MEDIA_UTPNL
mdefine_line|#define MEDIA_UTPNL             0x0012  /* Ethernet adapter, TP with link integrity test disabled */
DECL|macro|MEDIA_AUI_BNC
mdefine_line|#define MEDIA_AUI_BNC           0x0013  /* Ethernet adapter, AUI/BNC media */
DECL|macro|MEDIA_AUI_BNC_UTP
mdefine_line|#define MEDIA_AUI_BNC_UTP       0x0014  /* Ethernet adapter, AUI_BNC/UTP */
DECL|macro|MEDIA_UTPA
mdefine_line|#define MEDIA_UTPA              0x0015  /* Ethernet UTP-10Mbps Ports A */
DECL|macro|MEDIA_UTPB
mdefine_line|#define MEDIA_UTPB              0x0016  /* Ethernet UTP-10Mbps Ports B */
DECL|macro|MEDIA_STP_16_UTP_16
mdefine_line|#define MEDIA_STP_16_UTP_16     0x0017  /* Token Ring STP-16Mbps/UTP-16Mbps */
DECL|macro|MEDIA_STP_4_UTP_4
mdefine_line|#define MEDIA_STP_4_UTP_4       0x0018  /* Token Ring STP-4Mbps/UTP-4Mbps */
DECL|macro|MEDIA_STP100_UTP100
mdefine_line|#define MEDIA_STP100_UTP100     0x0020  /* Ethernet STP-100Mbps/UTP-100Mbps */
DECL|macro|MEDIA_UTP100FD
mdefine_line|#define MEDIA_UTP100FD          0x0021  /* Ethernet UTP-100Mbps, full duplex */
DECL|macro|MEDIA_UTP100
mdefine_line|#define MEDIA_UTP100            0x0022  /* Ethernet UTP-100Mbps */
DECL|macro|MEDIA_UNKNOWN
mdefine_line|#define MEDIA_UNKNOWN           0xFFFF  /* Unknown adapter/media type   */
multiline_comment|/*&n; * Definitions for the field:&n; * media_type2&n; */
DECL|macro|MEDIA_TYPE_MII
mdefine_line|#define MEDIA_TYPE_MII              0x0001
DECL|macro|MEDIA_TYPE_UTP
mdefine_line|#define MEDIA_TYPE_UTP              0x0002
DECL|macro|MEDIA_TYPE_BNC
mdefine_line|#define MEDIA_TYPE_BNC              0x0004
DECL|macro|MEDIA_TYPE_AUI
mdefine_line|#define MEDIA_TYPE_AUI              0x0008
DECL|macro|MEDIA_TYPE_S10
mdefine_line|#define MEDIA_TYPE_S10              0x0010
DECL|macro|MEDIA_TYPE_AUTO_SENSE
mdefine_line|#define MEDIA_TYPE_AUTO_SENSE       0x1000
DECL|macro|MEDIA_TYPE_AUTO_DETECT
mdefine_line|#define MEDIA_TYPE_AUTO_DETECT      0x4000
DECL|macro|MEDIA_TYPE_AUTO_NEGOTIATE
mdefine_line|#define MEDIA_TYPE_AUTO_NEGOTIATE   0x8000
multiline_comment|/*&n; * Definitions for the field:&n; * line_speed&n; */
DECL|macro|LINE_SPEED_UNKNOWN
mdefine_line|#define LINE_SPEED_UNKNOWN          0x0000
DECL|macro|LINE_SPEED_4
mdefine_line|#define LINE_SPEED_4                0x0001
DECL|macro|LINE_SPEED_10
mdefine_line|#define LINE_SPEED_10               0x0002
DECL|macro|LINE_SPEED_16
mdefine_line|#define LINE_SPEED_16               0x0004
DECL|macro|LINE_SPEED_100
mdefine_line|#define LINE_SPEED_100              0x0008
DECL|macro|LINE_SPEED_T4
mdefine_line|#define LINE_SPEED_T4               0x0008  /* 100BaseT4 aliased for 9332BVT */
DECL|macro|LINE_SPEED_FULL_DUPLEX
mdefine_line|#define LINE_SPEED_FULL_DUPLEX      0x8000
multiline_comment|/*&n; * Definitions for the field:&n; * bic_type (Bus interface chip type)&n; */
DECL|macro|BIC_NO_CHIP
mdefine_line|#define BIC_NO_CHIP             0x0000  /* Bus interface chip not implemented */
DECL|macro|BIC_583_CHIP
mdefine_line|#define BIC_583_CHIP            0x0001  /* 83C583 bus interface chip */
DECL|macro|BIC_584_CHIP
mdefine_line|#define BIC_584_CHIP            0x0002  /* 83C584 bus interface chip */
DECL|macro|BIC_585_CHIP
mdefine_line|#define BIC_585_CHIP            0x0003  /* 83C585 bus interface chip */
DECL|macro|BIC_593_CHIP
mdefine_line|#define BIC_593_CHIP            0x0004  /* 83C593 bus interface chip */
DECL|macro|BIC_594_CHIP
mdefine_line|#define BIC_594_CHIP            0x0005  /* 83C594 bus interface chip */
DECL|macro|BIC_564_CHIP
mdefine_line|#define BIC_564_CHIP            0x0006  /* PCMCIA Bus interface chip */
DECL|macro|BIC_790_CHIP
mdefine_line|#define BIC_790_CHIP            0x0007  /* 83C790 bus i-face/Ethernet NIC chip */
DECL|macro|BIC_571_CHIP
mdefine_line|#define BIC_571_CHIP            0x0008  /* 83C571 EISA bus master i-face */
DECL|macro|BIC_587_CHIP
mdefine_line|#define BIC_587_CHIP            0x0009  /* Token Ring AT bus master i-face */
DECL|macro|BIC_574_CHIP
mdefine_line|#define BIC_574_CHIP            0x0010  /* FEAST bus interface chip */
DECL|macro|BIC_8432_CHIP
mdefine_line|#define BIC_8432_CHIP           0x0011  /* 8432 bus i-face/Ethernet NIC(DEC PCI) */
DECL|macro|BIC_9332_CHIP
mdefine_line|#define BIC_9332_CHIP           0x0012  /* 9332 bus i-face/100Mbps Ether NIC(DEC PCI) */
DECL|macro|BIC_8432E_CHIP
mdefine_line|#define BIC_8432E_CHIP          0x0013  /* 8432 Enhanced bus iface/Ethernet NIC(DEC) */
DECL|macro|BIC_EPIC100_CHIP
mdefine_line|#define BIC_EPIC100_CHIP        0x0014  /* EPIC/100 10/100 Mbps Ethernet BIC/NIC */
DECL|macro|BIC_C94_CHIP
mdefine_line|#define BIC_C94_CHIP            0x0015  /* 91C94 bus i-face in PCMCIA mode */
DECL|macro|BIC_X8020_CHIP
mdefine_line|#define BIC_X8020_CHIP          0x0016  /* Xilinx PCMCIA multi-func i-face */
multiline_comment|/*&n; * Definitions for the field:&n; * nic_type (Bus interface chip type)&n; */
DECL|macro|NIC_UNK_CHIP
mdefine_line|#define NIC_UNK_CHIP            0x0000  /* Unknown NIC chip      */
DECL|macro|NIC_8390_CHIP
mdefine_line|#define NIC_8390_CHIP           0x0001  /* DP8390 Ethernet NIC   */
DECL|macro|NIC_690_CHIP
mdefine_line|#define NIC_690_CHIP            0x0002  /* 83C690 Ethernet NIC   */
DECL|macro|NIC_825_CHIP
mdefine_line|#define NIC_825_CHIP            0x0003  /* 83C825 Token Ring NIC */
multiline_comment|/*      #define NIC_???_CHIP    0x0004  */
multiline_comment|/* Not used           */
multiline_comment|/*      #define NIC_???_CHIP    0x0005  */
multiline_comment|/* Not used           */
multiline_comment|/*      #define NIC_???_CHIP    0x0006  */
multiline_comment|/* Not used           */
DECL|macro|NIC_790_CHIP
mdefine_line|#define NIC_790_CHIP            0x0007  /* 83C790 bus i-face/Ethernet NIC chip */
DECL|macro|NIC_C100_CHIP
mdefine_line|#define NIC_C100_CHIP           0x0010  /* FEAST 100Mbps Ethernet NIC */
DECL|macro|NIC_8432_CHIP
mdefine_line|#define NIC_8432_CHIP           0x0011  /* 8432 bus i-face/Ethernet NIC(DEC PCI) */
DECL|macro|NIC_9332_CHIP
mdefine_line|#define NIC_9332_CHIP           0x0012  /* 9332 bus i-face/100Mbps Ether NIC(DEC PCI) */
DECL|macro|NIC_8432E_CHIP
mdefine_line|#define NIC_8432E_CHIP          0x0013  /* 8432 enhanced bus iface/Ethernet NIC(DEC) */
DECL|macro|NIC_EPIC100_CHIP
mdefine_line|#define NIC_EPIC100_CHIP        0x0014   /* EPIC/100 10/100 Mbps Ethernet BIC/NIC */
DECL|macro|NIC_C94_CHIP
mdefine_line|#define NIC_C94_CHIP            0x0015  /* 91C94 PC Card with multi func */
multiline_comment|/*&n; * Definitions for the field:&n; * adapter_type The adapter_type field describes the adapter/bus&n; *              configuration.&n; */
DECL|macro|BUS_ISA16_TYPE
mdefine_line|#define BUS_ISA16_TYPE          0x0001  /* 16 bit adap in 16 bit (E)ISA slot  */
DECL|macro|BUS_ISA8_TYPE
mdefine_line|#define BUS_ISA8_TYPE           0x0002  /* 8/16b adap in 8 bit XT/(E)ISA slot */
DECL|macro|BUS_MCA_TYPE
mdefine_line|#define BUS_MCA_TYPE            0x0003  /* Micro Channel adapter              */
multiline_comment|/*&n; * Receive Mask definitions&n; */
DECL|macro|ACCEPT_MULTICAST
mdefine_line|#define ACCEPT_MULTICAST                0x0001
DECL|macro|ACCEPT_BROADCAST
mdefine_line|#define ACCEPT_BROADCAST                0x0002
DECL|macro|PROMISCUOUS_MODE
mdefine_line|#define PROMISCUOUS_MODE                0x0004
DECL|macro|ACCEPT_SOURCE_ROUTING
mdefine_line|#define ACCEPT_SOURCE_ROUTING           0x0008
DECL|macro|ACCEPT_ERR_PACKETS
mdefine_line|#define ACCEPT_ERR_PACKETS              0x0010
DECL|macro|ACCEPT_ATT_MAC_FRAMES
mdefine_line|#define ACCEPT_ATT_MAC_FRAMES           0x0020
DECL|macro|ACCEPT_MULTI_PROM
mdefine_line|#define ACCEPT_MULTI_PROM               0x0040
DECL|macro|TRANSMIT_ONLY
mdefine_line|#define TRANSMIT_ONLY                   0x0080
DECL|macro|ACCEPT_EXT_MAC_FRAMES
mdefine_line|#define ACCEPT_EXT_MAC_FRAMES           0x0100
DECL|macro|EARLY_RX_ENABLE
mdefine_line|#define EARLY_RX_ENABLE                 0x0200
DECL|macro|PKT_SIZE_NOT_NEEDED
mdefine_line|#define PKT_SIZE_NOT_NEEDED             0x0400
DECL|macro|ACCEPT_SOURCE_ROUTING_SPANNING
mdefine_line|#define ACCEPT_SOURCE_ROUTING_SPANNING  0x0808
DECL|macro|ACCEPT_ALL_MAC_FRAMES
mdefine_line|#define ACCEPT_ALL_MAC_FRAMES           0x0120
multiline_comment|/*&n; * config_mode defs&n; */
DECL|macro|STORE_EEROM
mdefine_line|#define STORE_EEROM             0x0001  /* Store config in EEROM. */
DECL|macro|STORE_REGS
mdefine_line|#define STORE_REGS              0x0002  /* Store config in register set. */
multiline_comment|/*&n; * equates for lmac_flags in adapter structure (Ethernet)&n; */
DECL|macro|MEM_DISABLE
mdefine_line|#define         MEM_DISABLE     0x0001
DECL|macro|RX_STATUS_POLL
mdefine_line|#define         RX_STATUS_POLL  0x0002
DECL|macro|USE_RE_BIT
mdefine_line|#define         USE_RE_BIT      0x0004
multiline_comment|/*#define       RESERVED        0x0008 */
multiline_comment|/*#define       RESERVED        0x0010 */
multiline_comment|/*#define       RESERVED        0x0020 */
multiline_comment|/*#define       RESERVED        0x0040 */
multiline_comment|/*#define       RESERVED        0x0080 */
multiline_comment|/*#define       RESERVED        0x0100 */
multiline_comment|/*#define       RESERVED        0x0200 */
multiline_comment|/*#define       RESERVED        0x0400 */
multiline_comment|/*#define       RESERVED        0x0800 */
multiline_comment|/*#define       RESERVED        0x1000 */
multiline_comment|/*#define       RESERVED        0x2000 */
multiline_comment|/*#define       RESERVED        0x4000 */
multiline_comment|/*#define       RESERVED        0x8000 */
multiline_comment|/* media_opts &amp; media_set Fields bit defs for Ethernet ... */
DECL|macro|MED_OPT_BNC
mdefine_line|#define         MED_OPT_BNC     0x01
DECL|macro|MED_OPT_UTP
mdefine_line|#define         MED_OPT_UTP     0x02
DECL|macro|MED_OPT_AUI
mdefine_line|#define         MED_OPT_AUI     0x04
DECL|macro|MED_OPT_10MB
mdefine_line|#define         MED_OPT_10MB    0x08
DECL|macro|MED_OPT_100MB
mdefine_line|#define         MED_OPT_100MB   0x10
DECL|macro|MED_OPT_S10
mdefine_line|#define         MED_OPT_S10     0x20
multiline_comment|/* media_opts &amp; media_set Fields bit defs for Token Ring ... */
DECL|macro|MED_OPT_4MB
mdefine_line|#define         MED_OPT_4MB     0x08
DECL|macro|MED_OPT_16MB
mdefine_line|#define         MED_OPT_16MB    0x10
DECL|macro|MED_OPT_STP
mdefine_line|#define         MED_OPT_STP     0x40
DECL|macro|MAX_8023_SIZE
mdefine_line|#define MAX_8023_SIZE           1500    /* Max 802.3 size of frame. */
DECL|macro|DEFAULT_ERX_VALUE
mdefine_line|#define DEFAULT_ERX_VALUE       4       /* Number of 16-byte blocks for 790B early Rx. */
DECL|macro|DEFAULT_ETX_VALUE
mdefine_line|#define DEFAULT_ETX_VALUE       32      /* Number of bytes for 790B early Tx. */
DECL|macro|DEFAULT_TX_RETRIES
mdefine_line|#define DEFAULT_TX_RETRIES      3       /* Number of transmit retries */
DECL|macro|LPBK_FRAME_SIZE
mdefine_line|#define LPBK_FRAME_SIZE         1024    /* Default loopback frame for Rx calibration test. */
DECL|macro|MAX_LOOKAHEAD_SIZE
mdefine_line|#define MAX_LOOKAHEAD_SIZE      252     /* Max lookahead size for ethernet. */
DECL|macro|RW_MAC_STATE
mdefine_line|#define RW_MAC_STATE                    0x1101
DECL|macro|RW_SA_OF_LAST_AMP_OR_SMP
mdefine_line|#define RW_SA_OF_LAST_AMP_OR_SMP        0x2803
DECL|macro|RW_PHYSICAL_DROP_NUMBER
mdefine_line|#define RW_PHYSICAL_DROP_NUMBER         0x3B02
DECL|macro|RW_UPSTREAM_NEIGHBOR_ADDRESS
mdefine_line|#define RW_UPSTREAM_NEIGHBOR_ADDRESS    0x3E03
DECL|macro|RW_PRODUCT_INSTANCE_ID
mdefine_line|#define RW_PRODUCT_INSTANCE_ID          0x4B09
DECL|macro|RW_TRC_STATUS_BLOCK
mdefine_line|#define RW_TRC_STATUS_BLOCK             0x5412
DECL|macro|RW_MAC_ERROR_COUNTERS_NO_CLEAR
mdefine_line|#define RW_MAC_ERROR_COUNTERS_NO_CLEAR  0x8006
DECL|macro|RW_MAC_ERROR_COUNTER_CLEAR
mdefine_line|#define RW_MAC_ERROR_COUNTER_CLEAR      0x7A06
DECL|macro|RW_CONFIG_REGISTER_0
mdefine_line|#define RW_CONFIG_REGISTER_0            0xA001
DECL|macro|RW_CONFIG_REGISTER_1
mdefine_line|#define RW_CONFIG_REGISTER_1            0xA101
DECL|macro|RW_PRESCALE_TIMER_THRESHOLD
mdefine_line|#define RW_PRESCALE_TIMER_THRESHOLD     0xA201
DECL|macro|RW_TPT_THRESHOLD
mdefine_line|#define RW_TPT_THRESHOLD                0xA301
DECL|macro|RW_TQP_THRESHOLD
mdefine_line|#define RW_TQP_THRESHOLD                0xA401
DECL|macro|RW_TNT_THRESHOLD
mdefine_line|#define RW_TNT_THRESHOLD                0xA501
DECL|macro|RW_TBT_THRESHOLD
mdefine_line|#define RW_TBT_THRESHOLD                0xA601
DECL|macro|RW_TSM_THRESHOLD
mdefine_line|#define RW_TSM_THRESHOLD                0xA701
DECL|macro|RW_TAM_THRESHOLD
mdefine_line|#define RW_TAM_THRESHOLD                0xA801
DECL|macro|RW_TBR_THRESHOLD
mdefine_line|#define RW_TBR_THRESHOLD                0xA901
DECL|macro|RW_TER_THRESHOLD
mdefine_line|#define RW_TER_THRESHOLD                0xAA01
DECL|macro|RW_TGT_THRESHOLD
mdefine_line|#define RW_TGT_THRESHOLD                0xAB01
DECL|macro|RW_THT_THRESHOLD
mdefine_line|#define RW_THT_THRESHOLD                0xAC01
DECL|macro|RW_TRR_THRESHOLD
mdefine_line|#define RW_TRR_THRESHOLD                0xAD01
DECL|macro|RW_TVX_THRESHOLD
mdefine_line|#define RW_TVX_THRESHOLD                0xAE01
DECL|macro|RW_INDIVIDUAL_MAC_ADDRESS
mdefine_line|#define RW_INDIVIDUAL_MAC_ADDRESS       0xB003
DECL|macro|RW_INDIVIDUAL_GROUP_ADDRESS
mdefine_line|#define RW_INDIVIDUAL_GROUP_ADDRESS     0xB303  /* all of group addr */
DECL|macro|RW_INDIVIDUAL_GROUP_ADDR_WORD_0
mdefine_line|#define RW_INDIVIDUAL_GROUP_ADDR_WORD_0 0xB301  /* 1st word of group addr */
DECL|macro|RW_INDIVIDUAL_GROUP_ADDR
mdefine_line|#define RW_INDIVIDUAL_GROUP_ADDR        0xB402  /* 2nd-3rd word of group addr */
DECL|macro|RW_FUNCTIONAL_ADDRESS
mdefine_line|#define RW_FUNCTIONAL_ADDRESS           0xB603  /* all of functional addr */
DECL|macro|RW_FUNCTIONAL_ADDR_WORD_0
mdefine_line|#define RW_FUNCTIONAL_ADDR_WORD_0       0xB601  /* 1st word of func  addr */
DECL|macro|RW_FUNCTIONAL_ADDR
mdefine_line|#define RW_FUNCTIONAL_ADDR              0xB702  /* 2nd-3rd word func addr */
DECL|macro|RW_BIT_SIGNIFICANT_GROUP_ADDR
mdefine_line|#define RW_BIT_SIGNIFICANT_GROUP_ADDR   0xB902
DECL|macro|RW_SOURCE_RING_BRIDGE_NUMBER
mdefine_line|#define RW_SOURCE_RING_BRIDGE_NUMBER    0xBB01
DECL|macro|RW_TARGET_RING_NUMBER
mdefine_line|#define RW_TARGET_RING_NUMBER           0xBC01
DECL|macro|RW_HIC_INTERRUPT_MASK
mdefine_line|#define RW_HIC_INTERRUPT_MASK           0xC601
DECL|macro|SOURCE_ROUTING_SPANNING_BITS
mdefine_line|#define SOURCE_ROUTING_SPANNING_BITS    0x00C0  /* Spanning Tree Frames */
DECL|macro|SOURCE_ROUTING_EXPLORER_BIT
mdefine_line|#define SOURCE_ROUTING_EXPLORER_BIT     0x0040  /* Explorer and Single Route */
multiline_comment|/* write */
DECL|macro|CSR_MSK_ALL
mdefine_line|#define CSR_MSK_ALL             0x80    
singleline_comment|// Bic 587 Only
DECL|macro|CSR_MSKTINT
mdefine_line|#define CSR_MSKTINT             0x20
DECL|macro|CSR_MSKCBUSY
mdefine_line|#define CSR_MSKCBUSY            0x10
DECL|macro|CSR_CLRTINT
mdefine_line|#define CSR_CLRTINT             0x08
DECL|macro|CSR_CLRCBUSY
mdefine_line|#define CSR_CLRCBUSY            0x04
DECL|macro|CSR_WCSS
mdefine_line|#define CSR_WCSS                0x02
DECL|macro|CSR_CA
mdefine_line|#define CSR_CA                  0x01
multiline_comment|/* read */
DECL|macro|CSR_TINT
mdefine_line|#define CSR_TINT                0x20
DECL|macro|CSR_CINT
mdefine_line|#define CSR_CINT                0x10
DECL|macro|CSR_TSTAT
mdefine_line|#define CSR_TSTAT               0x08
DECL|macro|CSR_CSTAT
mdefine_line|#define CSR_CSTAT               0x04
DECL|macro|CSR_FAULT
mdefine_line|#define CSR_FAULT               0x02
DECL|macro|CSR_CBUSY
mdefine_line|#define CSR_CBUSY               0x01
DECL|macro|LAAR_MEM16ENB
mdefine_line|#define LAAR_MEM16ENB           0x80
DECL|macro|Zws16
mdefine_line|#define Zws16                   0x20
DECL|macro|IRR_IEN
mdefine_line|#define IRR_IEN                 0x80
DECL|macro|Zws8
mdefine_line|#define Zws8                    0x01
DECL|macro|IMCCR_EIL
mdefine_line|#define IMCCR_EIL               0x04
r_typedef
r_struct
(brace
DECL|member|ac
id|__u8
id|ac
suffix:semicolon
multiline_comment|/* Access Control */
DECL|member|fc
id|__u8
id|fc
suffix:semicolon
multiline_comment|/* Frame Control */
DECL|member|da
id|__u8
id|da
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Dest Addr */
DECL|member|sa
id|__u8
id|sa
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Source Addr */
DECL|member|vl
id|__u16
id|vl
suffix:semicolon
multiline_comment|/* Vector Length */
DECL|member|dc_sc
id|__u8
id|dc_sc
suffix:semicolon
multiline_comment|/* Dest/Source Class */
DECL|member|vc
id|__u8
id|vc
suffix:semicolon
multiline_comment|/* Vector Code */
DECL|typedef|MAC_HEADER
)brace
id|MAC_HEADER
suffix:semicolon
DECL|macro|MAX_SUB_VECTOR_INFO
mdefine_line|#define MAX_SUB_VECTOR_INFO     (RX_DATA_BUFFER_SIZE - sizeof(MAC_HEADER) - 2)
r_typedef
r_struct
(brace
DECL|member|svl
id|__u8
id|svl
suffix:semicolon
multiline_comment|/* Sub-vector Length */
DECL|member|svi
id|__u8
id|svi
suffix:semicolon
multiline_comment|/* Sub-vector Code */
DECL|member|svv
id|__u8
id|svv
(braket
id|MAX_SUB_VECTOR_INFO
)braket
suffix:semicolon
multiline_comment|/* Sub-vector Info */
DECL|typedef|MAC_SUB_VECTOR
)brace
id|MAC_SUB_VECTOR
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __LINUX_SMCTR_H */
eof

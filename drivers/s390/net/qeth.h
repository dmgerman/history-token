multiline_comment|/*&n; * linux/drivers/s390/net/qeth.h&n; *&n; * Linux on zSeries OSA Express and HiperSockets support&n; *&n; * Copyright 2000,2003 IBM Corporation&n; * Author(s): Utz Bacher &lt;utz.bacher@de.ibm.com&gt;&n; *&n; */
macro_line|#ifndef __QETH_H__
DECL|macro|__QETH_H__
mdefine_line|#define __QETH_H__
macro_line|#include &lt;asm/qdio.h&gt;
DECL|macro|QETH_NAME
mdefine_line|#define QETH_NAME &quot; qeth&quot;
DECL|macro|VERSION_QETH_H
mdefine_line|#define VERSION_QETH_H &quot;$Revision: 1.47 $&quot;
multiline_comment|/******************** CONFIG STUFF ***********************/
singleline_comment|//#define QETH_DBF_LIKE_HELL
macro_line|#ifdef CONFIG_QETH_IPV6
DECL|macro|QETH_IPV6
mdefine_line|#define QETH_IPV6
DECL|macro|QETH_VERSION_IPV6
mdefine_line|#define QETH_VERSION_IPV6 &quot;:IPv6&quot;
macro_line|#else
DECL|macro|QETH_VERSION_IPV6
mdefine_line|#define QETH_VERSION_IPV6 &quot;&quot;
macro_line|#endif&t;/* CONFIG_QETH_IPV6 */
macro_line|#ifdef CONFIG_QETH_VLAN
DECL|macro|QETH_VLAN
mdefine_line|#define QETH_VLAN
DECL|macro|QETH_VERSION_VLAN
mdefine_line|#define QETH_VERSION_VLAN &quot;:VLAN&quot;
macro_line|#else
DECL|macro|QETH_VERSION_VLAN
mdefine_line|#define QETH_VERSION_VLAN &quot;&quot;
macro_line|#endif&t;/* CONFIG_QETH_VLAN */
multiline_comment|/* these values match CHECKSUM_* in include/linux/skbuff.h */
DECL|macro|SW_CHECKSUMMING
mdefine_line|#define SW_CHECKSUMMING 0
DECL|macro|HW_CHECKSUMMING
mdefine_line|#define HW_CHECKSUMMING 1
DECL|macro|NO_CHECKSUMMING
mdefine_line|#define NO_CHECKSUMMING 2
DECL|macro|QETH_CHECKSUM_DEFAULT
mdefine_line|#define QETH_CHECKSUM_DEFAULT NO_CHECKSUMMING
DECL|macro|QETH_PRIOQ_DEFAULT
mdefine_line|#define QETH_PRIOQ_DEFAULT NO_PRIO_QUEUEING
DECL|macro|QETH_DEFAULT_QUEUE
mdefine_line|#define QETH_DEFAULT_QUEUE 2
multiline_comment|/******************** CONFIG STUFF END ***********************/
multiline_comment|/********************* TUNING STUFF **************************/
DECL|macro|HIGH_WATERMARK_PACK
mdefine_line|#define HIGH_WATERMARK_PACK&t;&t;5
DECL|macro|LOW_WATERMARK_PACK
mdefine_line|#define LOW_WATERMARK_PACK&t;&t;2
DECL|macro|WATERMARK_FUZZ
mdefine_line|#define WATERMARK_FUZZ&t;&t;&t;2
DECL|macro|QETH_MAX_INPUT_THRESHOLD
mdefine_line|#define QETH_MAX_INPUT_THRESHOLD 500
DECL|macro|QETH_MAX_OUTPUT_THRESHOLD
mdefine_line|#define QETH_MAX_OUTPUT_THRESHOLD 300&t;/* ? */
multiline_comment|/* only the MAX values are used */
DECL|macro|QETH_MIN_INPUT_THRESHOLD
mdefine_line|#define QETH_MIN_INPUT_THRESHOLD 1
DECL|macro|QETH_MIN_OUTPUT_THRESHOLD
mdefine_line|#define QETH_MIN_OUTPUT_THRESHOLD 1
DECL|macro|QETH_REQUEUE_THRESHOLD
mdefine_line|#define QETH_REQUEUE_THRESHOLD (card-&gt;options.inbound_buffer_count/4)
macro_line|#ifdef CONFIG_QETH_PERF_STATS
DECL|macro|QETH_PERFORMANCE_STATS
mdefine_line|#define QETH_PERFORMANCE_STATS
macro_line|#endif&t;/* CONFIG_QETH_PERF_STATS */
macro_line|#ifdef QETH_DBF_LIKE_HELL
DECL|macro|QETH_VERBOSE_LEVEL
mdefine_line|#define QETH_VERBOSE_LEVEL 8
macro_line|#else /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_VERBOSE_LEVEL
mdefine_line|#define QETH_VERBOSE_LEVEL 5
macro_line|#endif /* QETH_DBF_LIKE_HELL */
DECL|macro|PCI_THRESHOLD_A
mdefine_line|#define PCI_THRESHOLD_A (card-&gt;options.inbound_buffer_count+1)&t;
multiline_comment|/* buffers we have to be behind before we get a PCI */
DECL|macro|PCI_THRESHOLD_B
mdefine_line|#define PCI_THRESHOLD_B 0&t;/* enqueued free buffers left before we get a PCI */
DECL|macro|PCI_TIMER_VALUE
mdefine_line|#define PCI_TIMER_VALUE 3&t;/* not used, unless the microcode gets patched */
DECL|macro|DEFAULT_SPARE_BUFFERS
mdefine_line|#define DEFAULT_SPARE_BUFFERS 0
DECL|macro|MAX_SPARE_BUFFERS
mdefine_line|#define MAX_SPARE_BUFFERS 1024
DECL|macro|SPAREBUF_MASK
mdefine_line|#define SPAREBUF_MASK 65536
DECL|macro|MAX_PORTNO
mdefine_line|#define MAX_PORTNO 15
DECL|macro|QETH_PROCFILE_NAME
mdefine_line|#define QETH_PROCFILE_NAME &quot;qeth&quot;
DECL|macro|QETH_PERF_PROCFILE_NAME
mdefine_line|#define QETH_PERF_PROCFILE_NAME &quot;qeth_perf&quot;
DECL|macro|QETH_IPA_PROCFILE_NAME
mdefine_line|#define QETH_IPA_PROCFILE_NAME &quot;qeth_ipa_takeover&quot;
DECL|macro|SEND_RETRIES_ALLOWED
mdefine_line|#define SEND_RETRIES_ALLOWED 5
DECL|macro|QETH_ROUTING_ATTEMPTS
mdefine_line|#define QETH_ROUTING_ATTEMPTS 2
DECL|macro|QETH_HARDSETUP_LAPS
mdefine_line|#define QETH_HARDSETUP_LAPS 5
DECL|macro|QETH_HARDSETUP_CLEAR_LAPS
mdefine_line|#define QETH_HARDSETUP_CLEAR_LAPS 3
DECL|macro|QETH_RECOVERY_HARDSETUP_RETRY
mdefine_line|#define QETH_RECOVERY_HARDSETUP_RETRY 2
multiline_comment|/************************* DEBUG FACILITY STUFF *********************/
DECL|macro|QETH_DBF_HEX
mdefine_line|#define QETH_DBF_HEX(ex,name,level,addr,len) &bslash;&n;        do { &bslash;&n;        if (ex) &bslash;&n;                debug_exception(qeth_dbf_##name,level,(void*)addr,len); &bslash;&n;        else &bslash;&n;                debug_event(qeth_dbf_##name,level,(void*)addr,len); &bslash;&n;        } while (0)
DECL|macro|QETH_DBF_TEXT
mdefine_line|#define QETH_DBF_TEXT(ex,name,level,text) &bslash;&n;        do { &bslash;&n;        if (ex) &bslash;&n;                debug_text_exception(qeth_dbf_##name,level,text); &bslash;&n;        else &bslash;&n;                debug_text_event(qeth_dbf_##name,level,text); &bslash;&n;        } while (0)
DECL|macro|QETH_DBF_HEX0
mdefine_line|#define QETH_DBF_HEX0(ex,name,addr,len) QETH_DBF_HEX(ex,name,0,addr,len)
DECL|macro|QETH_DBF_HEX1
mdefine_line|#define QETH_DBF_HEX1(ex,name,addr,len) QETH_DBF_HEX(ex,name,1,addr,len)
DECL|macro|QETH_DBF_HEX2
mdefine_line|#define QETH_DBF_HEX2(ex,name,addr,len) QETH_DBF_HEX(ex,name,2,addr,len)
macro_line|#ifdef QETH_DBF_LIKE_HELL
DECL|macro|QETH_DBF_HEX3
mdefine_line|#define QETH_DBF_HEX3(ex,name,addr,len) QETH_DBF_HEX(ex,name,3,addr,len)
DECL|macro|QETH_DBF_HEX4
mdefine_line|#define QETH_DBF_HEX4(ex,name,addr,len) QETH_DBF_HEX(ex,name,4,addr,len)
DECL|macro|QETH_DBF_HEX5
mdefine_line|#define QETH_DBF_HEX5(ex,name,addr,len) QETH_DBF_HEX(ex,name,5,addr,len)
DECL|macro|QETH_DBF_HEX6
mdefine_line|#define QETH_DBF_HEX6(ex,name,addr,len) QETH_DBF_HEX(ex,name,6,addr,len)
macro_line|#else /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_HEX3
mdefine_line|#define QETH_DBF_HEX3(ex,name,addr,len) do {} while (0)
DECL|macro|QETH_DBF_HEX4
mdefine_line|#define QETH_DBF_HEX4(ex,name,addr,len) do {} while (0)
DECL|macro|QETH_DBF_HEX5
mdefine_line|#define QETH_DBF_HEX5(ex,name,addr,len) do {} while (0)
DECL|macro|QETH_DBF_HEX6
mdefine_line|#define QETH_DBF_HEX6(ex,name,addr,len) do {} while (0)
macro_line|#endif /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_TEXT0
mdefine_line|#define QETH_DBF_TEXT0(ex,name,text) QETH_DBF_TEXT(ex,name,0,text)
DECL|macro|QETH_DBF_TEXT1
mdefine_line|#define QETH_DBF_TEXT1(ex,name,text) QETH_DBF_TEXT(ex,name,1,text)
DECL|macro|QETH_DBF_TEXT2
mdefine_line|#define QETH_DBF_TEXT2(ex,name,text) QETH_DBF_TEXT(ex,name,2,text)
macro_line|#ifdef QETH_DBF_LIKE_HELL
DECL|macro|QETH_DBF_TEXT3
mdefine_line|#define QETH_DBF_TEXT3(ex,name,text) QETH_DBF_TEXT(ex,name,3,text)
DECL|macro|QETH_DBF_TEXT4
mdefine_line|#define QETH_DBF_TEXT4(ex,name,text) QETH_DBF_TEXT(ex,name,4,text)
DECL|macro|QETH_DBF_TEXT5
mdefine_line|#define QETH_DBF_TEXT5(ex,name,text) QETH_DBF_TEXT(ex,name,5,text)
DECL|macro|QETH_DBF_TEXT6
mdefine_line|#define QETH_DBF_TEXT6(ex,name,text) QETH_DBF_TEXT(ex,name,6,text)
macro_line|#else /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_TEXT3
mdefine_line|#define QETH_DBF_TEXT3(ex,name,text) do {} while (0)
DECL|macro|QETH_DBF_TEXT4
mdefine_line|#define QETH_DBF_TEXT4(ex,name,text) do {} while (0)
DECL|macro|QETH_DBF_TEXT5
mdefine_line|#define QETH_DBF_TEXT5(ex,name,text) do {} while (0)
DECL|macro|QETH_DBF_TEXT6
mdefine_line|#define QETH_DBF_TEXT6(ex,name,text) do {} while (0)
macro_line|#endif /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_SETUP_NAME
mdefine_line|#define QETH_DBF_SETUP_NAME &quot;qeth_setup&quot;
DECL|macro|QETH_DBF_SETUP_LEN
mdefine_line|#define QETH_DBF_SETUP_LEN 8
DECL|macro|QETH_DBF_SETUP_INDEX
mdefine_line|#define QETH_DBF_SETUP_INDEX 3
DECL|macro|QETH_DBF_SETUP_NR_AREAS
mdefine_line|#define QETH_DBF_SETUP_NR_AREAS 1
macro_line|#ifdef QETH_DBF_LIKE_HELL
DECL|macro|QETH_DBF_SETUP_LEVEL
mdefine_line|#define QETH_DBF_SETUP_LEVEL 6
macro_line|#else /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_SETUP_LEVEL
mdefine_line|#define QETH_DBF_SETUP_LEVEL 3
macro_line|#endif /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_MISC_NAME
mdefine_line|#define QETH_DBF_MISC_NAME &quot;qeth_misc&quot;
DECL|macro|QETH_DBF_MISC_LEN
mdefine_line|#define QETH_DBF_MISC_LEN 128
DECL|macro|QETH_DBF_MISC_INDEX
mdefine_line|#define QETH_DBF_MISC_INDEX 1
DECL|macro|QETH_DBF_MISC_NR_AREAS
mdefine_line|#define QETH_DBF_MISC_NR_AREAS 1
macro_line|#ifdef QETH_DBF_LIKE_HELL
DECL|macro|QETH_DBF_MISC_LEVEL
mdefine_line|#define QETH_DBF_MISC_LEVEL 6
macro_line|#else /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_MISC_LEVEL
mdefine_line|#define QETH_DBF_MISC_LEVEL 2
macro_line|#endif /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_DATA_NAME
mdefine_line|#define QETH_DBF_DATA_NAME &quot;qeth_data&quot;
DECL|macro|QETH_DBF_DATA_LEN
mdefine_line|#define QETH_DBF_DATA_LEN 96
DECL|macro|QETH_DBF_DATA_INDEX
mdefine_line|#define QETH_DBF_DATA_INDEX 3
DECL|macro|QETH_DBF_DATA_NR_AREAS
mdefine_line|#define QETH_DBF_DATA_NR_AREAS 1
macro_line|#ifdef QETH_DBF_LIKE_HELL
DECL|macro|QETH_DBF_DATA_LEVEL
mdefine_line|#define QETH_DBF_DATA_LEVEL 6
macro_line|#else /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_DATA_LEVEL
mdefine_line|#define QETH_DBF_DATA_LEVEL 2
macro_line|#endif /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_CONTROL_NAME
mdefine_line|#define QETH_DBF_CONTROL_NAME &quot;qeth_control&quot;
multiline_comment|/* buffers are 255 bytes long, but no prob */
DECL|macro|QETH_DBF_CONTROL_LEN
mdefine_line|#define QETH_DBF_CONTROL_LEN 256
DECL|macro|QETH_DBF_CONTROL_INDEX
mdefine_line|#define QETH_DBF_CONTROL_INDEX 3
DECL|macro|QETH_DBF_CONTROL_NR_AREAS
mdefine_line|#define QETH_DBF_CONTROL_NR_AREAS 2
macro_line|#ifdef QETH_DBF_LIKE_HELL
DECL|macro|QETH_DBF_CONTROL_LEVEL
mdefine_line|#define QETH_DBF_CONTROL_LEVEL 6
macro_line|#else /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_CONTROL_LEVEL
mdefine_line|#define QETH_DBF_CONTROL_LEVEL 2
macro_line|#endif /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_TRACE_NAME
mdefine_line|#define QETH_DBF_TRACE_NAME &quot;qeth_trace&quot;
DECL|macro|QETH_DBF_TRACE_LEN
mdefine_line|#define QETH_DBF_TRACE_LEN 8
macro_line|#ifdef QETH_DBF_LIKE_HELL
DECL|macro|QETH_DBF_TRACE_INDEX
mdefine_line|#define QETH_DBF_TRACE_INDEX 3
macro_line|#else /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_TRACE_INDEX
mdefine_line|#define QETH_DBF_TRACE_INDEX 2
macro_line|#endif /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_TRACE_NR_AREAS
mdefine_line|#define QETH_DBF_TRACE_NR_AREAS 2
macro_line|#ifdef QETH_DBF_LIKE_HELL
DECL|macro|QETH_DBF_TRACE_LEVEL
mdefine_line|#define QETH_DBF_TRACE_LEVEL 6
macro_line|#else /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_TRACE_LEVEL
mdefine_line|#define QETH_DBF_TRACE_LEVEL 2
macro_line|#endif /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_SENSE_NAME
mdefine_line|#define QETH_DBF_SENSE_NAME &quot;qeth_sense&quot;
DECL|macro|QETH_DBF_SENSE_LEN
mdefine_line|#define QETH_DBF_SENSE_LEN 64
DECL|macro|QETH_DBF_SENSE_INDEX
mdefine_line|#define QETH_DBF_SENSE_INDEX 1
DECL|macro|QETH_DBF_SENSE_NR_AREAS
mdefine_line|#define QETH_DBF_SENSE_NR_AREAS 1
macro_line|#ifdef QETH_DBF_LIKE_HELL
DECL|macro|QETH_DBF_SENSE_LEVEL
mdefine_line|#define QETH_DBF_SENSE_LEVEL 6
macro_line|#else /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_SENSE_LEVEL
mdefine_line|#define QETH_DBF_SENSE_LEVEL 2
macro_line|#endif /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_QERR_NAME
mdefine_line|#define QETH_DBF_QERR_NAME &quot;qeth_qerr&quot;
DECL|macro|QETH_DBF_QERR_LEN
mdefine_line|#define QETH_DBF_QERR_LEN 8
DECL|macro|QETH_DBF_QERR_INDEX
mdefine_line|#define QETH_DBF_QERR_INDEX 1
DECL|macro|QETH_DBF_QERR_NR_AREAS
mdefine_line|#define QETH_DBF_QERR_NR_AREAS 2
macro_line|#ifdef QETH_DBF_LIKE_HELL
DECL|macro|QETH_DBF_QERR_LEVEL
mdefine_line|#define QETH_DBF_QERR_LEVEL 6
macro_line|#else /* QETH_DBF_LIKE_HELL */
DECL|macro|QETH_DBF_QERR_LEVEL
mdefine_line|#define QETH_DBF_QERR_LEVEL 2
macro_line|#endif /* QETH_DBF_LIKE_HELL */
multiline_comment|/****************** END OF DEBUG FACILITY STUFF *********************/
multiline_comment|/********************* CARD DATA STUFF **************************/
DECL|macro|QETH_MAX_PARAMS
mdefine_line|#define QETH_MAX_PARAMS 150
DECL|macro|QETH_CARD_TYPE_UNKNOWN
mdefine_line|#define QETH_CARD_TYPE_UNKNOWN&t;0
DECL|macro|QETH_CARD_TYPE_OSAE
mdefine_line|#define QETH_CARD_TYPE_OSAE&t;10
DECL|macro|QETH_CARD_TYPE_IQD
mdefine_line|#define QETH_CARD_TYPE_IQD&t;1234
DECL|macro|QETH_IDX_FUNC_LEVEL_OSAE_ENA_IPAT
mdefine_line|#define QETH_IDX_FUNC_LEVEL_OSAE_ENA_IPAT 0x0101
DECL|macro|QETH_IDX_FUNC_LEVEL_OSAE_DIS_IPAT
mdefine_line|#define QETH_IDX_FUNC_LEVEL_OSAE_DIS_IPAT 0x0101
DECL|macro|QETH_IDX_FUNC_LEVEL_IQD_ENA_IPAT
mdefine_line|#define QETH_IDX_FUNC_LEVEL_IQD_ENA_IPAT 0x4108
DECL|macro|QETH_IDX_FUNC_LEVEL_IQD_DIS_IPAT
mdefine_line|#define QETH_IDX_FUNC_LEVEL_IQD_DIS_IPAT 0x5108
DECL|macro|QETH_MAX_QUEUES
mdefine_line|#define QETH_MAX_QUEUES 4
DECL|macro|UNIQUE_ID_IF_CREATE_ADDR_FAILED
mdefine_line|#define UNIQUE_ID_IF_CREATE_ADDR_FAILED 0xfffe
DECL|macro|UNIQUE_ID_NOT_BY_CARD
mdefine_line|#define UNIQUE_ID_NOT_BY_CARD 0x10000
multiline_comment|/* &n; * CU type &amp; model, Dev type &amp; model, card_type, odd_even_restriction,&n; * func level, no of queues, multicast is different (multicast-queue_no + 0x100)&n; */
DECL|macro|QETH_MODELLIST_ARRAY
mdefine_line|#define QETH_MODELLIST_ARRAY &bslash;&n;&t;{{0x1731,0x01,0x1732,0x01,QETH_CARD_TYPE_OSAE,1, &bslash;&n;&t;  QETH_IDX_FUNC_LEVEL_OSAE_ENA_IPAT, &bslash;&n;&t;  QETH_IDX_FUNC_LEVEL_OSAE_DIS_IPAT, &bslash;&n;&t;  QETH_MAX_QUEUES,0}, &bslash;&n;&t; {0x1731,0x05,0x1732,0x05,QETH_CARD_TYPE_IQD,0, &bslash;&n;&t;  QETH_IDX_FUNC_LEVEL_IQD_ENA_IPAT, &bslash;&n;&t;  QETH_IDX_FUNC_LEVEL_IQD_DIS_IPAT, &bslash;&n;&t;  QETH_MAX_QUEUES,0x103}, &bslash;&n;&t; {0,0,0,0,0,0,0,0,0}}
DECL|macro|QETH_MPC_DIFINFO_LEN_INDICATES_LINK_TYPE
mdefine_line|#define QETH_MPC_DIFINFO_LEN_INDICATES_LINK_TYPE 0x18
multiline_comment|/* only the first two bytes are looked at in qeth_get_cardname_short */
DECL|macro|QETH_MPC_LINK_TYPE_FAST_ETHERNET
mdefine_line|#define QETH_MPC_LINK_TYPE_FAST_ETHERNET 0x01
DECL|macro|QETH_MPC_LINK_TYPE_HSTR
mdefine_line|#define QETH_MPC_LINK_TYPE_HSTR 0x02
DECL|macro|QETH_MPC_LINK_TYPE_GIGABIT_ETHERNET
mdefine_line|#define QETH_MPC_LINK_TYPE_GIGABIT_ETHERNET 0x03
DECL|macro|QETH_MPC_LINK_TYPE_10GIGABIT_ETHERNET
mdefine_line|#define QETH_MPC_LINK_TYPE_10GIGABIT_ETHERNET 0x10
DECL|macro|QETH_MPC_LINK_TYPE_LANE_ETH100
mdefine_line|#define QETH_MPC_LINK_TYPE_LANE_ETH100 0x81
DECL|macro|QETH_MPC_LINK_TYPE_LANE_TR
mdefine_line|#define QETH_MPC_LINK_TYPE_LANE_TR 0x82
DECL|macro|QETH_MPC_LINK_TYPE_LANE_ETH1000
mdefine_line|#define QETH_MPC_LINK_TYPE_LANE_ETH1000 0x83
DECL|macro|QETH_MPC_LINK_TYPE_LANE
mdefine_line|#define QETH_MPC_LINK_TYPE_LANE 0x88
DECL|macro|QETH_MPC_LINK_TYPE_ATM_NATIVE
mdefine_line|#define QETH_MPC_LINK_TYPE_ATM_NATIVE 0x90
DECL|macro|DEFAULT_ADD_HHLEN
mdefine_line|#define DEFAULT_ADD_HHLEN 0
DECL|macro|MAX_ADD_HHLEN
mdefine_line|#define MAX_ADD_HHLEN 1024
DECL|macro|QETH_HEADER_SIZE
mdefine_line|#define QETH_HEADER_SIZE&t;32
DECL|macro|QETH_IP_HEADER_SIZE
mdefine_line|#define QETH_IP_HEADER_SIZE&t;40
DECL|macro|QETH_HEADER_LEN_POS
mdefine_line|#define QETH_HEADER_LEN_POS&t;8
multiline_comment|/* flags for the header: */
DECL|macro|QETH_HEADER_PASSTHRU
mdefine_line|#define QETH_HEADER_PASSTHRU&t;0x10
DECL|macro|QETH_HEADER_IPV6
mdefine_line|#define QETH_HEADER_IPV6&t;0x80
DECL|macro|QETH_CAST_FLAGS
mdefine_line|#define QETH_CAST_FLAGS&t;&t;0x07
DECL|macro|QETH_CAST_UNICAST
mdefine_line|#define QETH_CAST_UNICAST&t;6
DECL|macro|QETH_CAST_MULTICAST
mdefine_line|#define QETH_CAST_MULTICAST&t;4
DECL|macro|QETH_CAST_BROADCAST
mdefine_line|#define QETH_CAST_BROADCAST&t;5
DECL|macro|QETH_CAST_ANYCAST
mdefine_line|#define QETH_CAST_ANYCAST&t;7
DECL|macro|QETH_CAST_NOCAST
mdefine_line|#define QETH_CAST_NOCAST&t;0
multiline_comment|/* VLAN defines */
DECL|macro|QETH_EXT_HEADER_VLAN_FRAME
mdefine_line|#define QETH_EXT_HEADER_VLAN_FRAME&t;  0x01
DECL|macro|QETH_EXT_HEADER_TOKEN_ID
mdefine_line|#define QETH_EXT_HEADER_TOKEN_ID&t;  0x02
DECL|macro|QETH_EXT_HEADER_INCLUDE_VLAN_TAG
mdefine_line|#define QETH_EXT_HEADER_INCLUDE_VLAN_TAG  0x04
DECL|macro|QETH_EXT_HEADER_SRC_MAC_ADDRESS
mdefine_line|#define QETH_EXT_HEADER_SRC_MAC_ADDRESS   0x08
DECL|macro|QETH_EXT_HEADER_CSUM_HDR_REQ
mdefine_line|#define QETH_EXT_HEADER_CSUM_HDR_REQ      0x10
DECL|macro|QETH_EXT_HEADER_CSUM_TRANSP_REQ
mdefine_line|#define QETH_EXT_HEADER_CSUM_TRANSP_REQ   0x20
DECL|macro|QETH_EXT_HEADER_CSUM_TRANSP_FRAME_TYPE
mdefine_line|#define QETH_EXT_HEADER_CSUM_TRANSP_FRAME_TYPE   0x40
DECL|macro|QETH_UDP_CSUM_OFFSET
mdefine_line|#define QETH_UDP_CSUM_OFFSET&t;6
DECL|macro|QETH_TCP_CSUM_OFFSET
mdefine_line|#define QETH_TCP_CSUM_OFFSET&t;16
DECL|macro|QETH_VERIFY_IS_REAL_DEV
mdefine_line|#define QETH_VERIFY_IS_REAL_DEV               1
DECL|macro|QETH_VERIFY_IS_VLAN_DEV
mdefine_line|#define QETH_VERIFY_IS_VLAN_DEV               2
r_inline
r_static
r_int
r_int
DECL|function|qeth_get_ipa_timeout
id|qeth_get_ipa_timeout
c_func
(paren
r_int
id|cardtype
)paren
(brace
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
l_int|2000
suffix:semicolon
r_default
suffix:colon
r_return
l_int|20000
suffix:semicolon
)brace
)brace
r_inline
r_static
r_int
r_int
DECL|function|qeth_get_additional_dev_flags
id|qeth_get_additional_dev_flags
c_func
(paren
r_int
id|cardtype
)paren
(brace
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
id|IFF_NOARP
suffix:semicolon
macro_line|#ifdef QETH_IPV6
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
macro_line|#else /* QETH_IPV6 */
r_default
suffix:colon
r_return
id|IFF_NOARP
suffix:semicolon
macro_line|#endif /* QETH_IPV6 */
)brace
)brace
r_inline
r_static
r_int
DECL|function|qeth_get_hlen
id|qeth_get_hlen
c_func
(paren
id|__u8
id|link_type
)paren
(brace
macro_line|#ifdef QETH_IPV6
r_switch
c_cond
(paren
id|link_type
)paren
(brace
r_case
id|QETH_MPC_LINK_TYPE_HSTR
suffix:colon
r_case
id|QETH_MPC_LINK_TYPE_LANE_TR
suffix:colon
r_return
id|QETH_HEADER_SIZE
op_plus
id|TR_HLEN
suffix:semicolon
r_default
suffix:colon
macro_line|#ifdef QETH_VLAN
r_return
id|QETH_HEADER_SIZE
op_plus
id|VLAN_ETH_HLEN
suffix:semicolon
macro_line|#else
r_return
id|QETH_HEADER_SIZE
op_plus
id|ETH_HLEN
suffix:semicolon
macro_line|#endif
)brace
macro_line|#else /* QETH_IPV6 */
macro_line|#ifdef QETH_VLAN
r_return
id|QETH_HEADER_SIZE
op_plus
id|VLAN_HLEN
suffix:semicolon
macro_line|#else
r_return
id|QETH_HEADER_SIZE
suffix:semicolon
macro_line|#endif
macro_line|#endif /* QETH_IPV6 */
)brace
DECL|variable|qeth_my_eth_header
r_static
r_int
(paren
op_star
id|qeth_my_eth_header
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
comma
r_int
r_int
comma
r_void
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_TR
DECL|variable|qeth_my_tr_header
r_static
r_int
(paren
op_star
id|qeth_my_tr_header
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
comma
r_int
r_int
comma
r_void
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_TR */
DECL|variable|qeth_my_eth_rebuild_header
r_static
r_int
(paren
op_star
id|qeth_my_eth_rebuild_header
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_TR
DECL|variable|qeth_my_tr_rebuild_header
r_static
r_int
(paren
op_star
id|qeth_my_tr_rebuild_header
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_TR */
DECL|variable|qeth_my_eth_header_cache
r_static
r_int
(paren
op_star
id|qeth_my_eth_header_cache
)paren
(paren
r_struct
id|neighbour
op_star
comma
r_struct
id|hh_cache
op_star
)paren
suffix:semicolon
DECL|variable|qeth_my_eth_header_cache_update
r_static
r_void
(paren
op_star
id|qeth_my_eth_header_cache_update
)paren
(paren
r_struct
id|hh_cache
op_star
comma
r_struct
id|net_device
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
macro_line|#ifdef QETH_IPV6
DECL|typedef|__qeth_temp1
r_typedef
r_int
(paren
op_star
id|__qeth_temp1
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
comma
r_int
r_int
comma
r_void
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_inline
r_static
id|__qeth_temp1
DECL|function|qeth_get_hard_header
id|qeth_get_hard_header
c_func
(paren
id|__u8
id|link_type
)paren
(brace
r_switch
c_cond
(paren
id|link_type
)paren
(brace
macro_line|#ifdef CONFIG_TR
r_case
id|QETH_MPC_LINK_TYPE_HSTR
suffix:colon
r_case
id|QETH_MPC_LINK_TYPE_LANE_TR
suffix:colon
r_return
id|qeth_my_tr_header
suffix:semicolon
macro_line|#endif /* CONFIG_TR */
r_default
suffix:colon
r_return
id|qeth_my_eth_header
suffix:semicolon
)brace
)brace
DECL|typedef|__qeth_temp2
r_typedef
r_int
(paren
op_star
id|__qeth_temp2
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_inline
r_static
id|__qeth_temp2
DECL|function|qeth_get_rebuild_header
id|qeth_get_rebuild_header
c_func
(paren
id|__u8
id|link_type
)paren
(brace
r_switch
c_cond
(paren
id|link_type
)paren
(brace
macro_line|#ifdef CONFIG_TR
r_case
id|QETH_MPC_LINK_TYPE_HSTR
suffix:colon
r_case
id|QETH_MPC_LINK_TYPE_LANE_TR
suffix:colon
r_return
id|qeth_my_tr_rebuild_header
suffix:semicolon
macro_line|#endif /* CONFIG_TR */
r_default
suffix:colon
r_return
id|qeth_my_eth_rebuild_header
suffix:semicolon
)brace
)brace
DECL|typedef|__qeth_temp3
r_typedef
r_int
(paren
op_star
id|__qeth_temp3
)paren
(paren
r_struct
id|neighbour
op_star
comma
r_struct
id|hh_cache
op_star
)paren
suffix:semicolon
r_inline
r_static
id|__qeth_temp3
DECL|function|qeth_get_hard_header_cache
id|qeth_get_hard_header_cache
c_func
(paren
id|__u8
id|link_type
)paren
(brace
r_switch
c_cond
(paren
id|link_type
)paren
(brace
r_case
id|QETH_MPC_LINK_TYPE_HSTR
suffix:colon
r_case
id|QETH_MPC_LINK_TYPE_LANE_TR
suffix:colon
r_return
l_int|NULL
suffix:semicolon
r_default
suffix:colon
r_return
id|qeth_my_eth_header_cache
suffix:semicolon
)brace
)brace
DECL|typedef|__qeth_temp4
r_typedef
r_void
(paren
op_star
id|__qeth_temp4
)paren
(paren
r_struct
id|hh_cache
op_star
comma
r_struct
id|net_device
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
r_inline
r_static
id|__qeth_temp4
DECL|function|qeth_get_header_cache_update
id|qeth_get_header_cache_update
c_func
(paren
id|__u8
id|link_type
)paren
(brace
r_switch
c_cond
(paren
id|link_type
)paren
(brace
r_case
id|QETH_MPC_LINK_TYPE_HSTR
suffix:colon
r_case
id|QETH_MPC_LINK_TYPE_LANE_TR
suffix:colon
r_return
l_int|NULL
suffix:semicolon
r_default
suffix:colon
r_return
id|qeth_my_eth_header_cache_update
suffix:semicolon
)brace
)brace
r_static
r_int
r_int
DECL|function|qeth_eth_type_trans
id|qeth_eth_type_trans
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|ethhdr
op_star
id|eth
suffix:semicolon
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|ETH_ALEN
op_star
l_int|2
op_plus
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|eth
op_assign
id|skb-&gt;mac.ethernet
suffix:semicolon
r_if
c_cond
(paren
op_star
id|eth-&gt;h_dest
op_amp
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|eth-&gt;h_dest
comma
id|dev-&gt;broadcast
comma
id|ETH_ALEN
)paren
op_eq
l_int|0
)paren
id|skb-&gt;pkt_type
op_assign
id|PACKET_BROADCAST
suffix:semicolon
r_else
id|skb-&gt;pkt_type
op_assign
id|PACKET_MULTICAST
suffix:semicolon
)brace
r_else
(brace
id|skb-&gt;pkt_type
op_assign
id|PACKET_OTHERHOST
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|eth-&gt;h_proto
)paren
op_ge
l_int|1536
)paren
r_return
id|eth-&gt;h_proto
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|skb-&gt;data
)paren
op_eq
l_int|0xFFFF
)paren
r_return
id|htons
c_func
(paren
id|ETH_P_802_3
)paren
suffix:semicolon
r_return
id|htons
c_func
(paren
id|ETH_P_802_2
)paren
suffix:semicolon
)brace
DECL|typedef|__qeth_temp5
r_typedef
r_int
r_int
(paren
op_star
id|__qeth_temp5
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_inline
r_static
id|__qeth_temp5
DECL|function|qeth_get_type_trans
id|qeth_get_type_trans
c_func
(paren
id|__u8
id|link_type
)paren
(brace
r_switch
c_cond
(paren
id|link_type
)paren
(brace
macro_line|#ifdef CONFIG_TR
r_case
id|QETH_MPC_LINK_TYPE_HSTR
suffix:colon
r_case
id|QETH_MPC_LINK_TYPE_LANE_TR
suffix:colon
r_return
id|tr_type_trans
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
id|qeth_eth_type_trans
suffix:semicolon
)brace
)brace
macro_line|#endif /* QETH_IPV6 */
r_inline
r_static
r_const
r_char
op_star
DECL|function|qeth_get_link_type_name
id|qeth_get_link_type_name
c_func
(paren
r_int
id|cardtype
comma
id|__u8
id|linktype
)paren
(brace
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|QETH_CARD_TYPE_UNKNOWN
suffix:colon
r_return
l_string|&quot;unknown&quot;
suffix:semicolon
r_case
id|QETH_CARD_TYPE_OSAE
suffix:colon
r_switch
c_cond
(paren
id|linktype
)paren
(brace
r_case
id|QETH_MPC_LINK_TYPE_FAST_ETHERNET
suffix:colon
r_return
l_string|&quot;Fast Eth&quot;
suffix:semicolon
r_case
id|QETH_MPC_LINK_TYPE_HSTR
suffix:colon
r_return
l_string|&quot;HSTR&quot;
suffix:semicolon
r_case
id|QETH_MPC_LINK_TYPE_GIGABIT_ETHERNET
suffix:colon
r_return
l_string|&quot;Gigabit Eth&quot;
suffix:semicolon
r_case
id|QETH_MPC_LINK_TYPE_LANE_ETH100
suffix:colon
r_return
l_string|&quot;LANE Eth100&quot;
suffix:semicolon
r_case
id|QETH_MPC_LINK_TYPE_LANE_TR
suffix:colon
r_return
l_string|&quot;LANE TR&quot;
suffix:semicolon
r_case
id|QETH_MPC_LINK_TYPE_LANE_ETH1000
suffix:colon
r_return
l_string|&quot;LANE Eth1000&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;unknown&quot;
suffix:semicolon
)brace
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
l_string|&quot;magic&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;unknown&quot;
suffix:semicolon
)brace
)brace
r_inline
r_static
r_const
r_char
op_star
DECL|function|qeth_get_dev_basename
id|qeth_get_dev_basename
c_func
(paren
r_int
id|cardtype
comma
id|__u8
id|link_type
)paren
(brace
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|QETH_CARD_TYPE_UNKNOWN
suffix:colon
r_return
l_string|&quot;eth&quot;
suffix:semicolon
r_case
id|QETH_CARD_TYPE_OSAE
suffix:colon
r_switch
c_cond
(paren
id|link_type
)paren
(brace
r_case
id|QETH_MPC_LINK_TYPE_LANE_TR
suffix:colon
multiline_comment|/* fallthrough */
r_case
id|QETH_MPC_LINK_TYPE_HSTR
suffix:colon
r_return
l_string|&quot;tr&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;eth&quot;
suffix:semicolon
)brace
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
l_string|&quot;hsi&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;eth&quot;
suffix:semicolon
)brace
)brace
multiline_comment|/* inbound: */
DECL|macro|DEFAULT_BUFFER_SIZE
mdefine_line|#define DEFAULT_BUFFER_SIZE 65536
DECL|macro|DEFAULT_BUFFER_COUNT
mdefine_line|#define DEFAULT_BUFFER_COUNT 128
DECL|macro|BUFCNT_MIN
mdefine_line|#define BUFCNT_MIN 8
DECL|macro|BUFCNT_MAX
mdefine_line|#define BUFCNT_MAX 128
DECL|macro|BUFFER_SIZE
mdefine_line|#define BUFFER_SIZE (card-&gt;inbound_buffer_size)
DECL|macro|BUFFER_MAX_ELEMENTS
mdefine_line|#define BUFFER_MAX_ELEMENTS (BUFFER_SIZE&gt;&gt;12)
multiline_comment|/* 8k for each pair header-buffer: */
r_inline
r_static
r_int
DECL|function|qeth_sbal_packing_on_card
id|qeth_sbal_packing_on_card
c_func
(paren
r_int
id|cardtype
)paren
(brace
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* &n; * do it this way round -&gt; __MODULE_STRING needs with&n; * QETH_PRIO_NICE_LEVELS a single number&n; */
DECL|macro|QETH_MAX_PRIO_QUEUES
mdefine_line|#define QETH_MAX_PRIO_QUEUES QETH_PRIO_NICE_LEVELS+1
r_static
r_inline
r_int
DECL|function|qeth_sbalf15_in_retrieable_range
id|qeth_sbalf15_in_retrieable_range
c_func
(paren
r_int
id|sbalf15
)paren
(brace
r_return
(paren
(paren
id|sbalf15
op_ge
l_int|15
)paren
op_logical_and
(paren
id|sbalf15
op_le
l_int|31
)paren
)paren
suffix:semicolon
)brace
DECL|macro|INBOUND_BUFFER_POS
mdefine_line|#define INBOUND_BUFFER_POS(card,bufno,sbale) &bslash;&n;&t;( (bufno&amp;SPAREBUF_MASK)? &bslash;&n;&t;  ( &bslash;&n;&t;    (sparebufs[bufno&amp;(~SPAREBUF_MASK)].buf+ &bslash;&n;&t;     PAGE_SIZE*sbale) &bslash;&n;&t;  ):( &bslash;&n;&t;      (card-&gt;inbound_buffer_pool_entry[card-&gt; &bslash;&n;&t;       inbound_buffer_entry_no[bufno]][sbale]) &bslash;&n;&t;    ) )
DECL|macro|SPAREBUF_UNAVAIL
mdefine_line|#define SPAREBUF_UNAVAIL 0
DECL|macro|SPAREBUF_FREE
mdefine_line|#define SPAREBUF_FREE 1
DECL|macro|SPAREBUF_USED
mdefine_line|#define SPAREBUF_USED 2
DECL|struct|sparebufs
r_struct
id|sparebufs
(brace
DECL|member|buf
r_char
op_star
id|buf
suffix:semicolon
DECL|member|status
id|atomic_t
id|status
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SEND_STATE_INACTIVE
mdefine_line|#define SEND_STATE_INACTIVE&t;&t;0
DECL|macro|SEND_STATE_DONT_PACK
mdefine_line|#define SEND_STATE_DONT_PACK&t;&t;1
DECL|macro|SEND_STATE_PACK
mdefine_line|#define SEND_STATE_PACK&t;&t;&t;2
DECL|macro|QETH_LOCK_UNLOCKED
mdefine_line|#define QETH_LOCK_UNLOCKED 0
DECL|macro|QETH_LOCK_NORMAL
mdefine_line|#define QETH_LOCK_NORMAL 1
DECL|macro|QETH_LOCK_FLUSH
mdefine_line|#define QETH_LOCK_FLUSH 2
DECL|macro|QETH_MAX_DEVICES
mdefine_line|#define QETH_MAX_DEVICES 16
multiline_comment|/* DEPENDENCY ON QETH_MAX_DEVICES.&n;&t; *__MOUDLE_STRING expects simple literals */
DECL|macro|QETH_MAX_DEVICES_TIMES_4
mdefine_line|#define QETH_MAX_DEVICES_TIMES_4 64
DECL|macro|QETH_MAX_DEVNAMES
mdefine_line|#define QETH_MAX_DEVNAMES 16
DECL|macro|QETH_DEVNAME
mdefine_line|#define QETH_DEVNAME &quot;eth&quot;
DECL|macro|QETH_TX_TIMEOUT
mdefine_line|#define QETH_TX_TIMEOUT 100*HZ&t;/* 100 seconds */
DECL|macro|QETH_REMOVE_WAIT_TIME
mdefine_line|#define QETH_REMOVE_WAIT_TIME 200
DECL|macro|QETH_WAIT_FOR_THREAD_TIME
mdefine_line|#define QETH_WAIT_FOR_THREAD_TIME 20
DECL|macro|QETH_IDLE_WAIT_TIME
mdefine_line|#define QETH_IDLE_WAIT_TIME 10
DECL|macro|QETH_WAIT_BEFORE_2ND_DOIO
mdefine_line|#define QETH_WAIT_BEFORE_2ND_DOIO 1000
DECL|macro|QETH_MAX_PARM_LEN
mdefine_line|#define QETH_MAX_PARM_LEN 128
DECL|macro|QETH_FAKE_LL_LEN
mdefine_line|#define QETH_FAKE_LL_LEN ETH_HLEN&t;/* 14 */
DECL|macro|QETH_FAKE_LL_PROT_LEN
mdefine_line|#define QETH_FAKE_LL_PROT_LEN 2
DECL|macro|QETH_FAKE_LL_ADDR_LEN
mdefine_line|#define QETH_FAKE_LL_ADDR_LEN ETH_ALEN&t;/* 6 */
DECL|macro|QETH_FAKE_LL_DEST_MAC_POS
mdefine_line|#define QETH_FAKE_LL_DEST_MAC_POS 0
DECL|macro|QETH_FAKE_LL_SRC_MAC_POS
mdefine_line|#define QETH_FAKE_LL_SRC_MAC_POS 6
DECL|macro|QETH_FAKE_LL_SRC_MAC_POS_IN_QDIO_HDR
mdefine_line|#define QETH_FAKE_LL_SRC_MAC_POS_IN_QDIO_HDR 6
DECL|macro|QETH_FAKE_LL_PROT_POS
mdefine_line|#define QETH_FAKE_LL_PROT_POS 12
DECL|macro|QETH_FAKE_LL_V4_ADDR_POS
mdefine_line|#define QETH_FAKE_LL_V4_ADDR_POS 16
DECL|macro|QETH_FAKE_LL_V6_ADDR_POS
mdefine_line|#define QETH_FAKE_LL_V6_ADDR_POS 24
DECL|macro|DEV_NAME_LEN
mdefine_line|#define DEV_NAME_LEN 16
DECL|macro|IOCTL_MAX_TRANSFER_SIZE
mdefine_line|#define IOCTL_MAX_TRANSFER_SIZE 65535
DECL|macro|IP_TOS_LOWDELAY
mdefine_line|#define IP_TOS_LOWDELAY 0x10
DECL|macro|IP_TOS_HIGHTHROUGHPUT
mdefine_line|#define IP_TOS_HIGHTHROUGHPUT 0x08
DECL|macro|IP_TOS_HIGHRELIABILITY
mdefine_line|#define IP_TOS_HIGHRELIABILITY 0x04
DECL|macro|IP_TOS_NOTIMPORTANT
mdefine_line|#define IP_TOS_NOTIMPORTANT 0x02
DECL|macro|QETH_RCD_LENGTH
mdefine_line|#define QETH_RCD_LENGTH 128
DECL|macro|__max
mdefine_line|#define __max(a,b) ( ((a)&gt;(b))?(a):(b) )
DECL|macro|__min
mdefine_line|#define __min(a,b) ( ((a)&lt;(b))?(a):(b) )
DECL|macro|QETH_BUFSIZE
mdefine_line|#define QETH_BUFSIZE __max(__max(IPA_PDU_HEADER_SIZE+sizeof(struct arp_cmd), &bslash;&n;&t;&t;&t;&t; IPA_PDU_HEADER_SIZE+sizeof(struct ipa_cmd)), &bslash;&n;&t;&t;&t;   QETH_RCD_LENGTH)
DECL|macro|QETH_FINAL_STATUS_TIMEOUT
mdefine_line|#define QETH_FINAL_STATUS_TIMEOUT 1500
DECL|macro|QETH_CLEAR_TIMEOUT
mdefine_line|#define QETH_CLEAR_TIMEOUT 1500
DECL|macro|QETH_RCD_TIMEOUT
mdefine_line|#define QETH_RCD_TIMEOUT 1500
DECL|macro|QETH_NOP_TIMEOUT
mdefine_line|#define QETH_NOP_TIMEOUT 1500
DECL|macro|QETH_QUIESCE_NETDEV_TIME
mdefine_line|#define QETH_QUIESCE_NETDEV_TIME 300
DECL|macro|QETH_QUIESCE_WAIT_BEFORE_CLEAR
mdefine_line|#define QETH_QUIESCE_WAIT_BEFORE_CLEAR 4000
DECL|macro|QETH_QUIESCE_WAIT_AFTER_CLEAR
mdefine_line|#define QETH_QUIESCE_WAIT_AFTER_CLEAR 4000
DECL|macro|NOP_STATE
mdefine_line|#define NOP_STATE 0x1001
DECL|macro|READ_CONF_DATA_STATE
mdefine_line|#define READ_CONF_DATA_STATE 0x1002
DECL|macro|IDX_ACTIVATE_READ_STATE
mdefine_line|#define IDX_ACTIVATE_READ_STATE 0x1003
DECL|macro|IDX_ACTIVATE_WRITE_STATE
mdefine_line|#define IDX_ACTIVATE_WRITE_STATE 0x1004
DECL|macro|MPC_SETUP_STATE
mdefine_line|#define MPC_SETUP_STATE 0x1005
DECL|macro|CLEAR_STATE
mdefine_line|#define CLEAR_STATE 0x1006
DECL|macro|IPA_CMD_STATE
mdefine_line|#define IPA_CMD_STATE 0x1007
DECL|macro|IPA_IOCTL_STATE
mdefine_line|#define IPA_IOCTL_STATE 0x1009
DECL|macro|IPA_SETIP_FLAG
mdefine_line|#define IPA_SETIP_FLAG 0x100000
DECL|macro|QETH_REMOVE_CARD_PROPER
mdefine_line|#define QETH_REMOVE_CARD_PROPER 1
DECL|macro|QETH_REMOVE_CARD_QUICK
mdefine_line|#define QETH_REMOVE_CARD_QUICK 2
DECL|macro|NO_PRIO_QUEUEING
mdefine_line|#define NO_PRIO_QUEUEING 0
DECL|macro|PRIO_QUEUEING_PREC
mdefine_line|#define PRIO_QUEUEING_PREC 1
DECL|macro|PRIO_QUEUEING_TOS
mdefine_line|#define PRIO_QUEUEING_TOS 2
DECL|macro|NO_ROUTER
mdefine_line|#define NO_ROUTER 0
DECL|macro|PRIMARY_ROUTER
mdefine_line|#define PRIMARY_ROUTER 1
DECL|macro|SECONDARY_ROUTER
mdefine_line|#define SECONDARY_ROUTER 2
DECL|macro|MULTICAST_ROUTER
mdefine_line|#define MULTICAST_ROUTER 3
DECL|macro|PRIMARY_CONNECTOR
mdefine_line|#define PRIMARY_CONNECTOR 4
DECL|macro|SECONDARY_CONNECTOR
mdefine_line|#define SECONDARY_CONNECTOR 5
DECL|macro|ROUTER_MASK
mdefine_line|#define ROUTER_MASK 0xf&t;&t;/* used to remove SET_ROUTING_FLAG&n;&t;&t;&t;&t;   from routing_type */
DECL|macro|RESET_ROUTING_FLAG
mdefine_line|#define RESET_ROUTING_FLAG 0x10&t;/* used to indicate, that setting&n;&t;&t;&t;&t;   the routing type is desired */
DECL|macro|BROADCAST_ALLRINGS
mdefine_line|#define BROADCAST_ALLRINGS 0
DECL|macro|BROADCAST_LOCAL
mdefine_line|#define BROADCAST_LOCAL 1
DECL|macro|MACADDR_NONCANONICAL
mdefine_line|#define MACADDR_NONCANONICAL 0
DECL|macro|MACADDR_CANONICAL
mdefine_line|#define MACADDR_CANONICAL 1
DECL|macro|MEMUSAGE_DISCONTIG
mdefine_line|#define MEMUSAGE_DISCONTIG 0
DECL|macro|MEMUSAGE_CONTIG
mdefine_line|#define MEMUSAGE_CONTIG 1
DECL|macro|ENABLE_TAKEOVER
mdefine_line|#define ENABLE_TAKEOVER 0
DECL|macro|DISABLE_TAKEOVER
mdefine_line|#define DISABLE_TAKEOVER 1
DECL|macro|FAKE_BROADCAST
mdefine_line|#define FAKE_BROADCAST 0
DECL|macro|DONT_FAKE_BROADCAST
mdefine_line|#define DONT_FAKE_BROADCAST 1
DECL|macro|FAKE_LL
mdefine_line|#define FAKE_LL 0
DECL|macro|DONT_FAKE_LL
mdefine_line|#define DONT_FAKE_LL 1
DECL|macro|SYNC_IQD
mdefine_line|#define SYNC_IQD 0
DECL|macro|ASYNC_IQD
mdefine_line|#define ASYNC_IQD 1
DECL|macro|QETH_BREAKOUT_LEAVE
mdefine_line|#define QETH_BREAKOUT_LEAVE 1
DECL|macro|QETH_BREAKOUT_AGAIN
mdefine_line|#define QETH_BREAKOUT_AGAIN 2
DECL|macro|QETH_WAIT_FOR_LOCK
mdefine_line|#define QETH_WAIT_FOR_LOCK 0
DECL|macro|QETH_DONT_WAIT_FOR_LOCK
mdefine_line|#define QETH_DONT_WAIT_FOR_LOCK 1
DECL|macro|QETH_LOCK_ALREADY_HELD
mdefine_line|#define QETH_LOCK_ALREADY_HELD 2
DECL|macro|PROBLEM_CARD_HAS_STARTLANED
mdefine_line|#define PROBLEM_CARD_HAS_STARTLANED 1
DECL|macro|PROBLEM_RECEIVED_IDX_TERMINATE
mdefine_line|#define PROBLEM_RECEIVED_IDX_TERMINATE 2
DECL|macro|PROBLEM_ACTIVATE_CHECK_CONDITION
mdefine_line|#define PROBLEM_ACTIVATE_CHECK_CONDITION 3
DECL|macro|PROBLEM_RESETTING_EVENT_INDICATOR
mdefine_line|#define PROBLEM_RESETTING_EVENT_INDICATOR 4
DECL|macro|PROBLEM_COMMAND_REJECT
mdefine_line|#define PROBLEM_COMMAND_REJECT 5
DECL|macro|PROBLEM_ZERO_SENSE_DATA
mdefine_line|#define PROBLEM_ZERO_SENSE_DATA 6
DECL|macro|PROBLEM_GENERAL_CHECK
mdefine_line|#define PROBLEM_GENERAL_CHECK 7
DECL|macro|PROBLEM_BAD_SIGA_RESULT
mdefine_line|#define PROBLEM_BAD_SIGA_RESULT 8
DECL|macro|PROBLEM_USER_TRIGGERED_RECOVERY
mdefine_line|#define PROBLEM_USER_TRIGGERED_RECOVERY 9
DECL|macro|PROBLEM_AFFE
mdefine_line|#define PROBLEM_AFFE 10
DECL|macro|PROBLEM_MACHINE_CHECK
mdefine_line|#define PROBLEM_MACHINE_CHECK 11
DECL|macro|PROBLEM_TX_TIMEOUT
mdefine_line|#define PROBLEM_TX_TIMEOUT 12
DECL|macro|SENSE_COMMAND_REJECT_BYTE
mdefine_line|#define SENSE_COMMAND_REJECT_BYTE 0
DECL|macro|SENSE_COMMAND_REJECT_FLAG
mdefine_line|#define SENSE_COMMAND_REJECT_FLAG 0x80
DECL|macro|SENSE_RESETTING_EVENT_BYTE
mdefine_line|#define SENSE_RESETTING_EVENT_BYTE 1
DECL|macro|SENSE_RESETTING_EVENT_FLAG
mdefine_line|#define SENSE_RESETTING_EVENT_FLAG 0x80
DECL|macro|DEFAULT_RCD_CMD
mdefine_line|#define DEFAULT_RCD_CMD 0x72
DECL|macro|DEFAULT_RCD_COUNT
mdefine_line|#define DEFAULT_RCD_COUNT 0x80
DECL|macro|BUFFER_USED
mdefine_line|#define BUFFER_USED 1
DECL|macro|BUFFER_UNUSED
mdefine_line|#define BUFFER_UNUSED -1
DECL|typedef|reg_notifier_t
r_typedef
r_int
(paren
op_star
id|reg_notifier_t
)paren
(paren
r_struct
id|notifier_block
op_star
)paren
suffix:semicolon
DECL|struct|ipato_entry
r_struct
id|ipato_entry
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|addr
id|__u8
id|addr
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|mask_bits
r_int
id|mask_bits
suffix:semicolon
DECL|member|dev_name
r_char
id|dev_name
(braket
id|DEV_NAME_LEN
)braket
suffix:semicolon
DECL|member|next
r_struct
id|ipato_entry
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|qeth_vipa_entry
r_struct
id|qeth_vipa_entry
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|ip
id|__u8
id|ip
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|flag
r_int
id|flag
suffix:semicolon
DECL|member|state
r_volatile
r_int
id|state
suffix:semicolon
DECL|member|next
r_struct
id|qeth_vipa_entry
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ip_state
r_struct
id|ip_state
(brace
DECL|member|ip_ifa
r_struct
id|in_ifaddr
op_star
id|ip_ifa
suffix:semicolon
multiline_comment|/* pointer to IPv4 adresses */
DECL|member|ip6_ifa
r_struct
id|inet6_ifaddr
op_star
id|ip6_ifa
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|qeth_ipm_mac
r_struct
id|qeth_ipm_mac
(brace
DECL|member|mac
id|__u8
id|mac
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|ip
id|__u8
id|ip
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|next
r_struct
id|qeth_ipm_mac
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ip_mc_state
r_struct
id|ip_mc_state
(brace
DECL|member|ipm_ifa
r_struct
id|qeth_ipm_mac
op_star
id|ipm_ifa
suffix:semicolon
DECL|member|ipm6_ifa
r_struct
id|qeth_ipm_mac
op_star
id|ipm6_ifa
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|addr_request
r_struct
id|addr_request
(brace
DECL|member|next
r_struct
id|addr_request
op_star
id|next
suffix:semicolon
DECL|member|request_type
r_int
id|request_type
suffix:semicolon
DECL|member|mac
id|__u8
id|mac
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|ip
id|__u8
id|ip
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|qeth_card_options
r_struct
id|qeth_card_options
(brace
DECL|member|devname
r_char
id|devname
(braket
id|DEV_NAME_LEN
)braket
suffix:semicolon
DECL|member|routing_type4
r_volatile
r_int
id|routing_type4
suffix:semicolon
macro_line|#ifdef QETH_IPV6
DECL|member|routing_type6
r_volatile
r_int
id|routing_type6
suffix:semicolon
macro_line|#endif /* QETH_IPV6 */
DECL|member|checksum_type
r_int
id|checksum_type
suffix:semicolon
DECL|member|do_prio_queueing
r_int
id|do_prio_queueing
suffix:semicolon
DECL|member|default_queue
r_int
id|default_queue
suffix:semicolon
DECL|member|inbound_buffer_count
r_int
id|inbound_buffer_count
suffix:semicolon
DECL|member|polltime
r_int
id|polltime
suffix:semicolon
DECL|member|portname
r_char
id|portname
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|portno
r_int
id|portno
suffix:semicolon
DECL|member|memusage
r_int
id|memusage
suffix:semicolon
DECL|member|broadcast_mode
r_int
id|broadcast_mode
suffix:semicolon
DECL|member|macaddr_mode
r_int
id|macaddr_mode
suffix:semicolon
DECL|member|ena_ipat
r_int
id|ena_ipat
suffix:semicolon
DECL|member|fake_broadcast
r_int
id|fake_broadcast
suffix:semicolon
DECL|member|add_hhlen
r_int
id|add_hhlen
suffix:semicolon
DECL|member|fake_ll
r_int
id|fake_ll
suffix:semicolon
DECL|member|async_iqd
r_int
id|async_iqd
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|qeth_hdr
r_struct
id|qeth_hdr
(brace
DECL|member|id
id|__u8
id|id
suffix:semicolon
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
DECL|member|inbound_checksum
id|__u16
id|inbound_checksum
suffix:semicolon
DECL|member|token
id|__u32
id|token
suffix:semicolon
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|member|vlan_prio
id|__u8
id|vlan_prio
suffix:semicolon
DECL|member|ext_flags
id|__u8
id|ext_flags
suffix:semicolon
DECL|member|vlan_id
id|__u16
id|vlan_id
suffix:semicolon
DECL|member|frame_offset
id|__u16
id|frame_offset
suffix:semicolon
DECL|member|dest_addr
id|__u8
id|dest_addr
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|qeth_ringbuffer_element
r_struct
id|qeth_ringbuffer_element
(brace
DECL|member|skb_list
r_struct
id|sk_buff_head
id|skb_list
suffix:semicolon
DECL|member|next_element_to_fill
r_int
id|next_element_to_fill
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|qeth_ringbuffer
r_struct
id|qeth_ringbuffer
(brace
DECL|member|buffer
r_struct
id|qdio_buffer
id|buffer
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
DECL|member|ringbuf_element
r_struct
id|qeth_ringbuffer_element
id|ringbuf_element
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
id|PAGE_SIZE
)paren
)paren
)paren
suffix:semicolon
DECL|struct|qeth_dma_stuff
r_struct
id|qeth_dma_stuff
(brace
DECL|member|sendbuf
r_int
r_char
op_star
id|sendbuf
suffix:semicolon
DECL|member|recbuf
r_int
r_char
op_star
id|recbuf
suffix:semicolon
DECL|member|read_ccw
r_struct
id|ccw1
id|read_ccw
suffix:semicolon
DECL|member|write_ccw
r_struct
id|ccw1
id|write_ccw
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
id|PAGE_SIZE
)paren
)paren
)paren
suffix:semicolon
DECL|struct|qeth_perf_stats
r_struct
id|qeth_perf_stats
(brace
DECL|member|skbs_rec
r_int
r_int
id|skbs_rec
suffix:semicolon
DECL|member|bufs_rec
r_int
r_int
id|bufs_rec
suffix:semicolon
DECL|member|skbs_sent
r_int
r_int
id|skbs_sent
suffix:semicolon
DECL|member|bufs_sent
r_int
r_int
id|bufs_sent
suffix:semicolon
DECL|member|skbs_sent_dont_pack
r_int
r_int
id|skbs_sent_dont_pack
suffix:semicolon
DECL|member|bufs_sent_dont_pack
r_int
r_int
id|bufs_sent_dont_pack
suffix:semicolon
DECL|member|skbs_sent_pack
r_int
r_int
id|skbs_sent_pack
suffix:semicolon
DECL|member|bufs_sent_pack
r_int
r_int
id|bufs_sent_pack
suffix:semicolon
DECL|member|skbs_sent_pack_better
r_int
r_int
id|skbs_sent_pack_better
suffix:semicolon
DECL|member|bufs_sent_pack_better
r_int
r_int
id|bufs_sent_pack_better
suffix:semicolon
DECL|member|sc_dp_p
r_int
r_int
id|sc_dp_p
suffix:semicolon
DECL|member|sc_p_dp
r_int
r_int
id|sc_p_dp
suffix:semicolon
DECL|member|inbound_start_time
id|__u64
id|inbound_start_time
suffix:semicolon
DECL|member|inbound_cnt
r_int
r_int
id|inbound_cnt
suffix:semicolon
DECL|member|inbound_time
r_int
r_int
id|inbound_time
suffix:semicolon
DECL|member|outbound_start_time
id|__u64
id|outbound_start_time
suffix:semicolon
DECL|member|outbound_cnt
r_int
r_int
id|outbound_cnt
suffix:semicolon
DECL|member|outbound_time
r_int
r_int
id|outbound_time
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ugly. I know. */
DECL|struct|qeth_card
r_struct
id|qeth_card
(brace
multiline_comment|/* pointed to by dev-&gt;priv */
DECL|member|easy_copy_cap
r_int
id|easy_copy_cap
suffix:semicolon
multiline_comment|/* pointer to options (defaults + parameters) */
DECL|member|options
r_struct
id|qeth_card_options
id|options
suffix:semicolon
DECL|member|is_startlaned
id|atomic_t
id|is_startlaned
suffix:semicolon
multiline_comment|/* card did not get a stoplan */
multiline_comment|/* also 0 when card is gone after a&n;&t;                         * machine check */
DECL|member|link_type
id|__u8
id|link_type
suffix:semicolon
DECL|member|is_guest_lan
r_int
id|is_guest_lan
suffix:semicolon
multiline_comment|/* inbound buffer management */
DECL|member|inbound_buffer_refcnt
id|atomic_t
id|inbound_buffer_refcnt
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
DECL|member|inbound_qdio_buffers
r_struct
id|qdio_buffer
id|inbound_qdio_buffers
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
multiline_comment|/* inbound data area */
DECL|member|inbound_buffer_pool_entry
r_void
op_star
id|inbound_buffer_pool_entry
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
(braket
id|QDIO_MAX_ELEMENTS_PER_BUFFER
)braket
suffix:semicolon
DECL|member|inbound_buffer_pool_entry_used
r_volatile
r_int
id|inbound_buffer_pool_entry_used
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
DECL|member|inbound_buffer_entry_no
r_int
id|inbound_buffer_entry_no
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
multiline_comment|/* for requeueing of buffers */
DECL|member|requeue_input_lock
id|spinlock_t
id|requeue_input_lock
suffix:semicolon
DECL|member|requeue_position
id|atomic_t
id|requeue_position
suffix:semicolon
DECL|member|requeue_counter
id|atomic_t
id|requeue_counter
suffix:semicolon
multiline_comment|/* outbound QDIO stuff */
DECL|member|send_state
r_volatile
r_int
id|send_state
(braket
id|QETH_MAX_QUEUES
)braket
suffix:semicolon
DECL|member|outbound_first_free_buffer
r_volatile
r_int
id|outbound_first_free_buffer
(braket
id|QETH_MAX_QUEUES
)braket
suffix:semicolon
DECL|member|outbound_used_buffers
id|atomic_t
id|outbound_used_buffers
(braket
id|QETH_MAX_QUEUES
)braket
suffix:semicolon
DECL|member|outbound_buffer_send_state
r_int
id|outbound_buffer_send_state
(braket
id|QETH_MAX_QUEUES
)braket
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
DECL|member|send_retries
r_int
id|send_retries
(braket
id|QETH_MAX_QUEUES
)braket
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
DECL|member|outbound_bytes_in_buffer
r_volatile
r_int
id|outbound_bytes_in_buffer
(braket
id|QETH_MAX_QUEUES
)braket
suffix:semicolon
DECL|member|outbound_ringbuffer
r_struct
id|qeth_ringbuffer
op_star
id|outbound_ringbuffer
(braket
id|QETH_MAX_QUEUES
)braket
suffix:semicolon
DECL|member|outbound_ringbuffer_lock
id|atomic_t
id|outbound_ringbuffer_lock
(braket
id|QETH_MAX_QUEUES
)braket
suffix:semicolon
DECL|member|last_pci_pos
id|atomic_t
id|last_pci_pos
(braket
id|QETH_MAX_QUEUES
)braket
suffix:semicolon
macro_line|#ifdef QETH_IPV6
DECL|member|hard_header
r_int
(paren
op_star
id|hard_header
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
comma
r_int
r_int
comma
r_void
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|rebuild_header
r_int
(paren
op_star
id|rebuild_header
)paren
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
DECL|member|hard_header_cache
r_int
(paren
op_star
id|hard_header_cache
)paren
(paren
r_struct
id|neighbour
op_star
comma
r_struct
id|hh_cache
op_star
)paren
suffix:semicolon
DECL|member|header_cache_update
r_void
(paren
op_star
id|header_cache_update
)paren
(paren
r_struct
id|hh_cache
op_star
comma
r_struct
id|net_device
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
DECL|member|type_trans
r_int
r_int
(paren
op_star
id|type_trans
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
macro_line|#endif /* QETH_IPV6 */
macro_line|#ifdef QETH_VLAN
DECL|member|vlangrp
r_struct
id|vlan_group
op_star
id|vlangrp
suffix:semicolon
DECL|member|vlan_lock
id|spinlock_t
id|vlan_lock
suffix:semicolon
macro_line|#endif
DECL|member|dev_name
r_char
id|dev_name
(braket
id|DEV_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* pointed to by dev-&gt;name */
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
op_star
id|stats
suffix:semicolon
DECL|member|no_queues
r_int
id|no_queues
suffix:semicolon
macro_line|#ifdef QETH_PERFORMANCE_STATS
DECL|member|perf_stats
r_struct
id|qeth_perf_stats
id|perf_stats
suffix:semicolon
macro_line|#endif /* QETH_PERFORMANCE_STATS */
multiline_comment|/* our state */
DECL|member|is_registered
id|atomic_t
id|is_registered
suffix:semicolon
multiline_comment|/* card registered as netdev? */
DECL|member|is_hardsetup
id|atomic_t
id|is_hardsetup
suffix:semicolon
multiline_comment|/* card has gone through hardsetup */
DECL|member|is_softsetup
id|atomic_t
id|is_softsetup
suffix:semicolon
multiline_comment|/* card is setup by softsetup */
DECL|member|is_open
id|atomic_t
id|is_open
suffix:semicolon
multiline_comment|/* card is in use */
multiline_comment|/* prevents deadlocks :-O */
DECL|member|softsetup_lock
id|spinlock_t
id|softsetup_lock
suffix:semicolon
DECL|member|hardsetup_lock
id|spinlock_t
id|hardsetup_lock
suffix:semicolon
DECL|member|ioctl_lock
id|spinlock_t
id|ioctl_lock
suffix:semicolon
DECL|member|softsetup_thread_is_running
id|atomic_t
id|softsetup_thread_is_running
suffix:semicolon
DECL|member|softsetup_thread_sem
r_struct
id|semaphore
id|softsetup_thread_sem
suffix:semicolon
DECL|member|tqueue_sst
r_struct
id|work_struct
id|tqueue_sst
suffix:semicolon
DECL|member|escape_softsetup
id|atomic_t
id|escape_softsetup
suffix:semicolon
multiline_comment|/* active, when recovery has to&n;&t;&t;&t;&t;&t;   wait for softsetup */
DECL|member|reinit_thread_sem
r_struct
id|semaphore
id|reinit_thread_sem
suffix:semicolon
DECL|member|in_recovery
id|atomic_t
id|in_recovery
suffix:semicolon
DECL|member|reinit_counter
id|atomic_t
id|reinit_counter
suffix:semicolon
multiline_comment|/* problem management */
DECL|member|break_out
id|atomic_t
id|break_out
suffix:semicolon
DECL|member|problem
id|atomic_t
id|problem
suffix:semicolon
DECL|member|tqueue
r_struct
id|work_struct
id|tqueue
suffix:semicolon
r_struct
(brace
DECL|member|trans_hdr
id|__u32
id|trans_hdr
suffix:semicolon
DECL|member|pdu_hdr
id|__u32
id|pdu_hdr
suffix:semicolon
DECL|member|pdu_hdr_ack
id|__u32
id|pdu_hdr_ack
suffix:semicolon
DECL|member|ipa
id|__u32
id|ipa
suffix:semicolon
DECL|member|seqno
)brace
id|seqno
suffix:semicolon
r_struct
(brace
DECL|member|issuer_rm_w
id|__u32
id|issuer_rm_w
suffix:semicolon
DECL|member|issuer_rm_r
id|__u32
id|issuer_rm_r
suffix:semicolon
DECL|member|cm_filter_w
id|__u32
id|cm_filter_w
suffix:semicolon
DECL|member|cm_filter_r
id|__u32
id|cm_filter_r
suffix:semicolon
DECL|member|cm_connection_w
id|__u32
id|cm_connection_w
suffix:semicolon
DECL|member|cm_connection_r
id|__u32
id|cm_connection_r
suffix:semicolon
DECL|member|ulp_filter_w
id|__u32
id|ulp_filter_w
suffix:semicolon
DECL|member|ulp_filter_r
id|__u32
id|ulp_filter_r
suffix:semicolon
DECL|member|ulp_connection_w
id|__u32
id|ulp_connection_w
suffix:semicolon
DECL|member|ulp_connection_r
id|__u32
id|ulp_connection_r
suffix:semicolon
DECL|member|token
)brace
id|token
suffix:semicolon
multiline_comment|/* this is card-related */
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|func_level
id|__u16
id|func_level
suffix:semicolon
DECL|member|initial_mtu
r_int
id|initial_mtu
suffix:semicolon
DECL|member|max_mtu
r_int
id|max_mtu
suffix:semicolon
DECL|member|inbound_buffer_size
r_int
id|inbound_buffer_size
suffix:semicolon
DECL|member|is_multicast_different
r_int
id|is_multicast_different
suffix:semicolon
multiline_comment|/* if multicast traffic is to be sent&n;&t;&t;&t;&t;&t;   on a different queue, this is the&n;&t;&t;&t;&t;&t;   queue+no_queues */
DECL|member|can_do_async_iqd
r_int
id|can_do_async_iqd
suffix:semicolon
multiline_comment|/* 1 only on IQD that provides async&n;&t;&t;&t;&t;   unicast sigas */
DECL|member|ipa_supported
id|__u32
id|ipa_supported
suffix:semicolon
DECL|member|ipa_enabled
id|__u32
id|ipa_enabled
suffix:semicolon
DECL|member|ipa6_supported
id|__u32
id|ipa6_supported
suffix:semicolon
DECL|member|ipa6_enabled
id|__u32
id|ipa6_enabled
suffix:semicolon
DECL|member|adp_supported
id|__u32
id|adp_supported
suffix:semicolon
DECL|member|startlan_attempts
id|atomic_t
id|startlan_attempts
suffix:semicolon
DECL|member|enable_routing_attempts4
id|atomic_t
id|enable_routing_attempts4
suffix:semicolon
DECL|member|rt4fld
id|atomic_t
id|rt4fld
suffix:semicolon
macro_line|#ifdef QETH_IPV6
DECL|member|enable_routing_attempts6
id|atomic_t
id|enable_routing_attempts6
suffix:semicolon
DECL|member|rt6fld
id|atomic_t
id|rt6fld
suffix:semicolon
macro_line|#endif /* QETH_IPV6 */
DECL|member|unique_id
r_int
id|unique_id
suffix:semicolon
multiline_comment|/* device and I/O data */
DECL|member|rdev
r_struct
id|ccw_device
op_star
id|rdev
suffix:semicolon
DECL|member|wdev
r_struct
id|ccw_device
op_star
id|wdev
suffix:semicolon
DECL|member|ddev
r_struct
id|ccw_device
op_star
id|ddev
suffix:semicolon
DECL|member|unit_addr2
r_int
r_int
id|unit_addr2
suffix:semicolon
DECL|member|cula
r_int
r_int
id|cula
suffix:semicolon
DECL|member|chpid
r_int
r_int
id|chpid
suffix:semicolon
DECL|member|ipa_buf
r_int
r_char
id|ipa_buf
(braket
id|QETH_BUFSIZE
)braket
suffix:semicolon
DECL|member|send_buf
r_int
r_char
id|send_buf
(braket
id|QETH_BUFSIZE
)braket
suffix:semicolon
multiline_comment|/* IOCTL Stuff */
DECL|member|ioctl_data_buffer
r_int
r_char
op_star
id|ioctl_data_buffer
suffix:semicolon
DECL|member|ioctl_buffer_pointer
r_int
r_char
op_star
id|ioctl_buffer_pointer
suffix:semicolon
DECL|member|ioctl_returncode
r_int
id|ioctl_returncode
suffix:semicolon
DECL|member|ioctl_buffersize
r_int
id|ioctl_buffersize
suffix:semicolon
DECL|member|number_of_entries
r_int
id|number_of_entries
suffix:semicolon
DECL|member|ioctl_data_has_arrived
id|atomic_t
id|ioctl_data_has_arrived
suffix:semicolon
DECL|member|ioctl_wait_q
id|wait_queue_head_t
id|ioctl_wait_q
suffix:semicolon
DECL|member|ioctl_wait_q_active
id|atomic_t
id|ioctl_wait_q_active
suffix:semicolon
DECL|member|ioctl_wait_q_lock
id|spinlock_t
id|ioctl_wait_q_lock
suffix:semicolon
multiline_comment|/* stuff under 2 gb */
DECL|member|dma_stuff
r_struct
id|qeth_dma_stuff
op_star
id|dma_stuff
suffix:semicolon
DECL|member|ipa_timeout
r_int
r_int
id|ipa_timeout
suffix:semicolon
DECL|member|write_busy
id|atomic_t
id|write_busy
suffix:semicolon
multiline_comment|/* vipa stuff */
DECL|member|vipa_list_lock
id|rwlock_t
id|vipa_list_lock
suffix:semicolon
DECL|member|vipa_list
r_struct
id|qeth_vipa_entry
op_star
id|vipa_list
suffix:semicolon
multiline_comment|/* state information when doing I/O */
DECL|member|shutdown_phase
id|atomic_t
id|shutdown_phase
suffix:semicolon
DECL|member|data_has_arrived
id|atomic_t
id|data_has_arrived
suffix:semicolon
DECL|member|wait_q
id|wait_queue_head_t
id|wait_q
suffix:semicolon
DECL|member|wait_q_active
id|atomic_t
id|wait_q_active
suffix:semicolon
DECL|member|wait_q_lock
id|spinlock_t
id|wait_q_lock
suffix:semicolon
multiline_comment|/* for wait_q_active and wait_q */
DECL|member|clear_succeeded0
id|atomic_t
id|clear_succeeded0
suffix:semicolon
DECL|member|clear_succeeded1
id|atomic_t
id|clear_succeeded1
suffix:semicolon
DECL|member|clear_succeeded2
id|atomic_t
id|clear_succeeded2
suffix:semicolon
multiline_comment|/* bookkeeping of IP and multicast addresses */
DECL|member|ip_current_state
r_struct
id|ip_state
id|ip_current_state
suffix:semicolon
DECL|member|ip_new_state
r_struct
id|ip_state
id|ip_new_state
suffix:semicolon
DECL|member|ip_mc_current_state
r_struct
id|ip_mc_state
id|ip_mc_current_state
suffix:semicolon
DECL|member|ip_mc_new_state
r_struct
id|ip_mc_state
id|ip_mc_new_state
suffix:semicolon
DECL|member|broadcast_capable
r_int
id|broadcast_capable
suffix:semicolon
DECL|member|portname_required
r_int
id|portname_required
suffix:semicolon
DECL|member|realloc_message
r_int
id|realloc_message
suffix:semicolon
DECL|member|level
r_char
id|level
(braket
id|QETH_MCL_LENGTH
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|saved_dev_flags
r_volatile
r_int
id|saved_dev_flags
suffix:semicolon
multiline_comment|/* for our linked list */
DECL|member|next
r_struct
id|qeth_card
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
r_inline
r_static
r_int
DECL|function|qeth_get_arphrd_type
id|qeth_get_arphrd_type
c_func
(paren
r_int
id|cardtype
comma
r_int
id|linktype
)paren
(brace
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|QETH_CARD_TYPE_OSAE
suffix:colon
r_switch
c_cond
(paren
id|linktype
)paren
(brace
r_case
id|QETH_MPC_LINK_TYPE_LANE_TR
suffix:colon
multiline_comment|/* fallthrough */
r_case
id|QETH_MPC_LINK_TYPE_HSTR
suffix:colon
r_return
id|ARPHRD_IEEE802
suffix:semicolon
r_default
suffix:colon
r_return
id|ARPHRD_ETHER
suffix:semicolon
)brace
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
id|ARPHRD_ETHER
suffix:semicolon
r_default
suffix:colon
r_return
id|ARPHRD_ETHER
suffix:semicolon
)brace
)brace
r_inline
r_static
r_int
DECL|function|qeth_determine_easy_copy_cap
id|qeth_determine_easy_copy_cap
c_func
(paren
r_int
id|cardtype
)paren
(brace
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|QETH_CARD_TYPE_UNKNOWN
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* better be cautious */
r_case
id|QETH_CARD_TYPE_OSAE
suffix:colon
r_return
l_int|1
suffix:semicolon
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* ?? */
)brace
)brace
r_inline
r_static
id|__u8
DECL|function|qeth_get_adapter_type_for_ipa
id|qeth_get_adapter_type_for_ipa
c_func
(paren
r_int
id|link_type
)paren
(brace
r_switch
c_cond
(paren
id|link_type
)paren
(brace
r_case
id|QETH_MPC_LINK_TYPE_HSTR
suffix:colon
r_return
l_int|2
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_inline
r_static
r_const
r_char
op_star
DECL|function|qeth_get_cardname
id|qeth_get_cardname
c_func
(paren
r_int
id|cardtype
comma
r_int
id|is_guest_lan
)paren
(brace
r_if
c_cond
(paren
id|is_guest_lan
)paren
(brace
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|QETH_CARD_TYPE_UNKNOWN
suffix:colon
r_return
l_string|&quot;n unknown&quot;
suffix:semicolon
r_case
id|QETH_CARD_TYPE_OSAE
suffix:colon
r_return
l_string|&quot; Guest LAN QDIO&quot;
suffix:semicolon
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
l_string|&quot; Guest LAN Hiper&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot; strange&quot;
suffix:semicolon
)brace
)brace
r_else
(brace
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|QETH_CARD_TYPE_UNKNOWN
suffix:colon
r_return
l_string|&quot;n unknown&quot;
suffix:semicolon
r_case
id|QETH_CARD_TYPE_OSAE
suffix:colon
r_return
l_string|&quot;n OSD Express&quot;
suffix:semicolon
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
l_string|&quot; HiperSockets&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot; strange&quot;
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* max length to be returned: 14 */
r_inline
r_static
r_const
r_char
op_star
DECL|function|qeth_get_cardname_short
id|qeth_get_cardname_short
c_func
(paren
r_int
id|cardtype
comma
id|__u8
id|link_type
comma
r_int
id|is_guest_lan
)paren
(brace
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|QETH_CARD_TYPE_UNKNOWN
suffix:colon
r_return
l_string|&quot;unknown&quot;
suffix:semicolon
r_case
id|QETH_CARD_TYPE_OSAE
suffix:colon
r_if
c_cond
(paren
id|is_guest_lan
)paren
r_return
l_string|&quot;GuestLAN QDIO&quot;
suffix:semicolon
r_switch
c_cond
(paren
id|link_type
)paren
(brace
r_case
id|QETH_MPC_LINK_TYPE_FAST_ETHERNET
suffix:colon
r_return
l_string|&quot;OSD_100&quot;
suffix:semicolon
r_case
id|QETH_MPC_LINK_TYPE_HSTR
suffix:colon
r_return
l_string|&quot;HSTR&quot;
suffix:semicolon
r_case
id|QETH_MPC_LINK_TYPE_GIGABIT_ETHERNET
suffix:colon
r_return
l_string|&quot;OSD_1000&quot;
suffix:semicolon
r_case
id|QETH_MPC_LINK_TYPE_LANE_ETH100
suffix:colon
r_return
l_string|&quot;OSD_FE_LANE&quot;
suffix:semicolon
r_case
id|QETH_MPC_LINK_TYPE_LANE_TR
suffix:colon
r_return
l_string|&quot;OSD_TR_LANE&quot;
suffix:semicolon
r_case
id|QETH_MPC_LINK_TYPE_LANE_ETH1000
suffix:colon
r_return
l_string|&quot;OSD_GbE_LANE&quot;
suffix:semicolon
r_case
id|QETH_MPC_LINK_TYPE_LANE
suffix:colon
r_return
l_string|&quot;OSD_ATM_LANE&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;OSD_Express&quot;
suffix:semicolon
)brace
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
id|is_guest_lan
ques
c_cond
l_string|&quot;GuestLAN Hiper&quot;
suffix:colon
l_string|&quot;HiperSockets&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot; strange&quot;
suffix:semicolon
)brace
)brace
r_inline
r_static
r_int
DECL|function|qeth_mtu_is_valid
id|qeth_mtu_is_valid
c_func
(paren
r_struct
id|qeth_card
op_star
id|card
comma
r_int
id|mtu
)paren
(brace
r_switch
c_cond
(paren
id|card-&gt;type
)paren
(brace
r_case
id|QETH_CARD_TYPE_UNKNOWN
suffix:colon
r_return
l_int|1
suffix:semicolon
r_case
id|QETH_CARD_TYPE_OSAE
suffix:colon
r_return
(paren
(paren
id|mtu
op_ge
l_int|576
)paren
op_logical_and
(paren
id|mtu
op_le
l_int|61440
)paren
)paren
suffix:semicolon
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
(paren
(paren
id|mtu
op_ge
l_int|576
)paren
op_logical_and
(paren
id|mtu
op_le
id|card-&gt;max_mtu
op_plus
l_int|4096
op_minus
l_int|32
)paren
)paren
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_inline
r_static
r_int
DECL|function|qeth_get_initial_mtu_for_card
id|qeth_get_initial_mtu_for_card
c_func
(paren
r_struct
id|qeth_card
op_star
id|card
)paren
(brace
r_switch
c_cond
(paren
id|card-&gt;type
)paren
(brace
r_case
id|QETH_CARD_TYPE_UNKNOWN
suffix:colon
r_return
l_int|1500
suffix:semicolon
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
id|card-&gt;max_mtu
suffix:semicolon
r_case
id|QETH_CARD_TYPE_OSAE
suffix:colon
r_switch
c_cond
(paren
id|card-&gt;link_type
)paren
(brace
r_case
id|QETH_MPC_LINK_TYPE_HSTR
suffix:colon
r_case
id|QETH_MPC_LINK_TYPE_LANE_TR
suffix:colon
r_return
l_int|2000
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1492
suffix:semicolon
)brace
r_default
suffix:colon
r_return
l_int|1500
suffix:semicolon
)brace
)brace
r_inline
r_static
r_int
DECL|function|qeth_get_max_mtu_for_card
id|qeth_get_max_mtu_for_card
c_func
(paren
r_int
id|cardtype
)paren
(brace
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|QETH_CARD_TYPE_UNKNOWN
suffix:colon
r_return
l_int|61440
suffix:semicolon
r_case
id|QETH_CARD_TYPE_OSAE
suffix:colon
r_return
l_int|61440
suffix:semicolon
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
l_int|57344
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1500
suffix:semicolon
)brace
)brace
r_inline
r_static
r_int
DECL|function|qeth_get_mtu_out_of_mpc
id|qeth_get_mtu_out_of_mpc
c_func
(paren
r_int
id|cardtype
)paren
(brace
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_inline
r_static
r_int
DECL|function|qeth_get_mtu_outof_framesize
id|qeth_get_mtu_outof_framesize
c_func
(paren
r_int
id|framesize
)paren
(brace
r_switch
c_cond
(paren
id|framesize
)paren
(brace
r_case
l_int|0x4000
suffix:colon
r_return
l_int|8192
suffix:semicolon
r_case
l_int|0x6000
suffix:colon
r_return
l_int|16384
suffix:semicolon
r_case
l_int|0xa000
suffix:colon
r_return
l_int|32768
suffix:semicolon
r_case
l_int|0xffff
suffix:colon
r_return
l_int|57344
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_inline
r_static
r_int
DECL|function|qeth_get_buffersize_for_card
id|qeth_get_buffersize_for_card
c_func
(paren
r_int
id|cardtype
)paren
(brace
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|QETH_CARD_TYPE_UNKNOWN
suffix:colon
r_return
l_int|65536
suffix:semicolon
r_case
id|QETH_CARD_TYPE_OSAE
suffix:colon
r_return
l_int|65536
suffix:semicolon
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
l_int|16384
suffix:semicolon
r_default
suffix:colon
r_return
l_int|65536
suffix:semicolon
)brace
)brace
r_inline
r_static
r_int
DECL|function|qeth_get_min_number_of_buffers
id|qeth_get_min_number_of_buffers
c_func
(paren
r_int
id|cardtype
)paren
(brace
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|QETH_CARD_TYPE_UNKNOWN
suffix:colon
r_return
l_int|32
suffix:semicolon
r_case
id|QETH_CARD_TYPE_OSAE
suffix:colon
r_return
l_int|32
suffix:semicolon
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
l_int|64
suffix:semicolon
r_default
suffix:colon
r_return
l_int|64
suffix:semicolon
)brace
)brace
r_inline
r_static
r_int
DECL|function|qeth_get_q_format
id|qeth_get_q_format
c_func
(paren
r_int
id|cardtype
)paren
(brace
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|QETH_CARD_TYPE_IQD
suffix:colon
r_return
l_int|2
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_inline
r_static
r_int
DECL|function|qeth_get_device_tx_q_len
id|qeth_get_device_tx_q_len
c_func
(paren
r_int
id|cardtype
)paren
(brace
r_return
l_int|100
suffix:semicolon
)brace
r_inline
r_static
r_int
DECL|function|qeth_get_max_number_of_buffers
id|qeth_get_max_number_of_buffers
c_func
(paren
r_int
id|cardtype
)paren
(brace
r_return
l_int|127
suffix:semicolon
)brace
multiline_comment|/******************** OUTPUT FACILITIES **************************/
macro_line|#ifdef PRINT_INFO
DECL|macro|PRINTK_HEADER
macro_line|#undef PRINTK_HEADER
DECL|macro|PRINT_STUPID
macro_line|#undef PRINT_STUPID
DECL|macro|PRINT_ALL
macro_line|#undef PRINT_ALL
DECL|macro|PRINT_INFO
macro_line|#undef PRINT_INFO
DECL|macro|PRINT_WARN
macro_line|#undef PRINT_WARN
DECL|macro|PRINT_ERR
macro_line|#undef PRINT_ERR
DECL|macro|PRINT_CRIT
macro_line|#undef PRINT_CRIT
DECL|macro|PRINT_ALERT
macro_line|#undef PRINT_ALERT
DECL|macro|PRINT_EMERG
macro_line|#undef PRINT_EMERG
macro_line|#endif&t;&t;&t;&t;/* PRINT_INFO */
DECL|macro|PRINTK_HEADER
mdefine_line|#define PRINTK_HEADER QETH_NAME &quot;: &quot;
macro_line|#if QETH_VERBOSE_LEVEL&gt;8
DECL|macro|PRINT_STUPID
mdefine_line|#define PRINT_STUPID(x...) printk( KERN_DEBUG PRINTK_HEADER x)
macro_line|#else
DECL|macro|PRINT_STUPID
mdefine_line|#define PRINT_STUPID(x...)
macro_line|#endif
macro_line|#if QETH_VERBOSE_LEVEL&gt;7
DECL|macro|PRINT_ALL
mdefine_line|#define PRINT_ALL(x...) printk( KERN_DEBUG PRINTK_HEADER x)
macro_line|#else
DECL|macro|PRINT_ALL
mdefine_line|#define PRINT_ALL(x...)
macro_line|#endif
macro_line|#if QETH_VERBOSE_LEVEL&gt;6
DECL|macro|PRINT_INFO
mdefine_line|#define PRINT_INFO(x...) printk( KERN_INFO PRINTK_HEADER x)
macro_line|#else
DECL|macro|PRINT_INFO
mdefine_line|#define PRINT_INFO(x...)
macro_line|#endif
macro_line|#if QETH_VERBOSE_LEVEL&gt;5
DECL|macro|PRINT_WARN
mdefine_line|#define PRINT_WARN(x...) printk( KERN_WARNING PRINTK_HEADER x)
macro_line|#else
DECL|macro|PRINT_WARN
mdefine_line|#define PRINT_WARN(x...)
macro_line|#endif
macro_line|#if QETH_VERBOSE_LEVEL&gt;4
DECL|macro|PRINT_ERR
mdefine_line|#define PRINT_ERR(x...) printk( KERN_ERR PRINTK_HEADER x)
macro_line|#else
DECL|macro|PRINT_ERR
mdefine_line|#define PRINT_ERR(x...)
macro_line|#endif
macro_line|#if QETH_VERBOSE_LEVEL&gt;3
DECL|macro|PRINT_CRIT
mdefine_line|#define PRINT_CRIT(x...) printk( KERN_CRIT PRINTK_HEADER x)
macro_line|#else
DECL|macro|PRINT_CRIT
mdefine_line|#define PRINT_CRIT(x...)
macro_line|#endif
macro_line|#if QETH_VERBOSE_LEVEL&gt;2
DECL|macro|PRINT_ALERT
mdefine_line|#define PRINT_ALERT(x...) printk( KERN_ALERT PRINTK_HEADER x)
macro_line|#else
DECL|macro|PRINT_ALERT
mdefine_line|#define PRINT_ALERT(x...)
macro_line|#endif
macro_line|#if QETH_VERBOSE_LEVEL&gt;1
DECL|macro|PRINT_EMERG
mdefine_line|#define PRINT_EMERG(x...) printk( KERN_EMERG PRINTK_HEADER x)
macro_line|#else
DECL|macro|PRINT_EMERG
mdefine_line|#define PRINT_EMERG(x...)
macro_line|#endif
DECL|macro|HEXDUMP16
mdefine_line|#define HEXDUMP16(importance,header,ptr) &bslash;&n;PRINT_##importance(header &quot;%02x %02x %02x %02x  %02x %02x %02x %02x  &quot; &bslash;&n;&t;&t;   &quot;%02x %02x %02x %02x  %02x %02x %02x %02x&bslash;n&quot;, &bslash;&n;&t;&t;   *(((char*)ptr)),*(((char*)ptr)+1),*(((char*)ptr)+2), &bslash;&n;&t;&t;   *(((char*)ptr)+3),*(((char*)ptr)+4),*(((char*)ptr)+5), &bslash;&n;&t;&t;   *(((char*)ptr)+6),*(((char*)ptr)+7),*(((char*)ptr)+8), &bslash;&n;&t;&t;   *(((char*)ptr)+9),*(((char*)ptr)+10),*(((char*)ptr)+11), &bslash;&n;&t;&t;   *(((char*)ptr)+12),*(((char*)ptr)+13), &bslash;&n;&t;&t;   *(((char*)ptr)+14),*(((char*)ptr)+15)); &bslash;&n;PRINT_##importance(header &quot;%02x %02x %02x %02x  %02x %02x %02x %02x  &quot; &bslash;&n;&t;&t;   &quot;%02x %02x %02x %02x  %02x %02x %02x %02x&bslash;n&quot;, &bslash;&n;&t;&t;   *(((char*)ptr)+16),*(((char*)ptr)+17), &bslash;&n;&t;&t;   *(((char*)ptr)+18),*(((char*)ptr)+19), &bslash;&n;&t;&t;   *(((char*)ptr)+20),*(((char*)ptr)+21), &bslash;&n;&t;&t;   *(((char*)ptr)+22),*(((char*)ptr)+23), &bslash;&n;&t;&t;   *(((char*)ptr)+24),*(((char*)ptr)+25), &bslash;&n;&t;&t;   *(((char*)ptr)+26),*(((char*)ptr)+27), &bslash;&n;&t;&t;   *(((char*)ptr)+28),*(((char*)ptr)+29), &bslash;&n;&t;&t;   *(((char*)ptr)+30),*(((char*)ptr)+31));
macro_line|#endif /* __QETH_H__ */
eof

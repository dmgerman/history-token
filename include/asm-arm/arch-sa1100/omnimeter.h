multiline_comment|/* -*- Mode: c++ -*-&n; *&n; *  Copyright 2000 Massachusetts Institute of Technology&n; *&n; *  Permission to use, copy, modify, distribute, and sell this software and its&n; *  documentation for any purpose is hereby granted without fee, provided that&n; *  the above copyright notice appear in all copies and that both that&n; *  copyright notice and this permission notice appear in supporting&n; *  documentation, and that the name of M.I.T. not be used in advertising or&n; *  publicity pertaining to distribution of the software without specific,&n; *  written prior permission.  M.I.T. makes no representations about the&n; *  suitability of this software for any purpose.  It is provided &quot;as is&quot;&n; *  without express or implied warranty.&n; *&n; */
macro_line|#ifndef OMNIMETER_H
DECL|macro|OMNIMETER_H
mdefine_line|#define OMNIMETER_H
singleline_comment|// use the address of the second socket for both sockets
singleline_comment|// (divide address space in half and use offsets to wrap second card accesses back to start of address space)
singleline_comment|// Following values for programming Cirrus Logic chip
DECL|macro|Socket1Base
mdefine_line|#define Socket1Base 0x40
DECL|macro|SocketMemoryWindowLen
mdefine_line|#define SocketMemoryWindowLen    (0x00400000)
DECL|macro|Socket0MemoryWindowStart
mdefine_line|#define Socket0MemoryWindowStart (0x00800000)
DECL|macro|Socket1MemoryWindowStart
mdefine_line|#define Socket1MemoryWindowStart (Socket0MemoryWindowStart + SocketMemoryWindowLen)
DECL|macro|SocketIOWindowLen
mdefine_line|#define SocketIOWindowLen        (0x00008000)
DECL|macro|Socket1IOWindowStart
mdefine_line|#define Socket1IOWindowStart     (SocketIOWindowLen)
DECL|macro|Socket1IOWindowOffset
mdefine_line|#define Socket1IOWindowOffset    (0x00010000 - Socket1IOWindowStart)
singleline_comment|// Following values for run-time access
singleline_comment|//#define PCCardBase     (0xe4000000) //jca (0x30000000)
singleline_comment|//#define PCCardBase     (0x30000000)
DECL|macro|PCCardBase
mdefine_line|#define PCCardBase     (0xe0000000)  
singleline_comment|//jag
DECL|macro|PCCard0IOBase
mdefine_line|#define PCCard0IOBase (PCCardBase)
singleline_comment|//#define PCCard0AttrBase (0xec000000) //jca (PCCardBase + 0x08000000)
DECL|macro|PCCard0AttrBase
mdefine_line|#define PCCard0AttrBase (0xe8000000)
singleline_comment|//#define PCCard0AttrBase (PCCardBase + 0x08000000)
singleline_comment|//#define PCCard0MemBase (0xf4000000) //jca (PCCardBase + 0x0C000000)
singleline_comment|//#define PCCard0MemBase (PCCardBase + 0x0C000000)
DECL|macro|PCCard0MemBase
mdefine_line|#define PCCard0MemBase (0xf0000000)
singleline_comment|//#define PCCard1IOBase (PCCardBase + SocketIOWindowLen)  //jag
DECL|macro|PCCard1IOBase
mdefine_line|#define PCCard1IOBase (0xe4000000)
singleline_comment|//#define PCCard1AttrBase (0xec000000 + SocketMemoryWindowLen)  //jag
DECL|macro|PCCard1AttrBase
mdefine_line|#define PCCard1AttrBase (0xec000000)
singleline_comment|//#define PCCard1MemBase (0xf4000000 + SocketMemoryWindowLen)  //jag
DECL|macro|PCCard1MemBase
mdefine_line|#define PCCard1MemBase (0xf4000000)
DECL|macro|PCCardIndexRegister
mdefine_line|#define PCCardIndexRegister (PCCard0IOBase + 0x000003E0) 
singleline_comment|//altered
DECL|macro|PCCardDataRegister
mdefine_line|#define PCCardDataRegister  (PCCardIndexRegister + 1)
multiline_comment|/* interrupts */
DECL|macro|PIN_cardInt2
mdefine_line|#define PIN_cardInt2&t;13
DECL|macro|PIN_cardInt1
mdefine_line|#define PIN_cardInt1&t;5
r_void
id|SMBOn
c_func
(paren
r_int
r_char
id|SMBaddress
)paren
suffix:semicolon
r_void
id|SetSMB
c_func
(paren
r_int
r_char
id|SMBaddress
comma
r_int
r_int
id|dacValue
)paren
suffix:semicolon
DECL|macro|GPIO_key6
mdefine_line|#define GPIO_key6&t;0x00040000
DECL|macro|GPIO_scl
mdefine_line|#define GPIO_scl&t;0x01000000  
singleline_comment|// output,   SMB clock
DECL|macro|GPIO_sda
mdefine_line|#define GPIO_sda&t;0x02000000  
singleline_comment|// bidirect, SMB data
DECL|macro|SMB_LCDVEE
mdefine_line|#define SMB_LCDVEE 0x2C
DECL|macro|DefaultLCDContrast
mdefine_line|#define DefaultLCDContrast&t;16
DECL|macro|LEDBacklightOn
mdefine_line|#define LEDBacklightOn()&t;ClearGPIOpin(GPIO_key6)
DECL|macro|LEDBacklightOff
mdefine_line|#define LEDBacklightOff()&t;SetGPIOpin(GPIO_key6)
DECL|macro|LCDPowerOn
mdefine_line|#define LCDPowerOn()&t;&t;&t;SMBOn(SMB_LCDVEE)
DECL|macro|LCDPowerOff
mdefine_line|#define LCDPowerOff()&t;&t;&t;SMBOff(SMB_LCDVEE)
DECL|macro|SetLCDContrast
mdefine_line|#define SetLCDContrast(d)&t;&t;SetSMB(SMB_LCDVEE, d)
DECL|macro|WritePort32
mdefine_line|#define WritePort32(port,value) (port = (value))
DECL|macro|ReadPort32
mdefine_line|#define ReadPort32(port) (port)
DECL|macro|SetGPIOpin
mdefine_line|#define SetGPIOpin(pin)&t;&t;WritePort32(GPSR,pin)
DECL|macro|ClearGPIOpin
mdefine_line|#define ClearGPIOpin(pin)&t;WritePort32(GPCR,pin)
r_void
id|jcaoutb
c_func
(paren
r_int
id|p
comma
r_int
r_char
id|data
)paren
suffix:semicolon
r_int
r_char
id|jcainb
c_func
(paren
r_int
id|p
)paren
suffix:semicolon
r_void
id|jcaoutw
c_func
(paren
r_int
id|p
comma
r_int
r_int
id|data
)paren
suffix:semicolon
r_int
r_int
id|jcainw_p
c_func
(paren
r_int
id|p
)paren
suffix:semicolon
macro_line|#endif
eof

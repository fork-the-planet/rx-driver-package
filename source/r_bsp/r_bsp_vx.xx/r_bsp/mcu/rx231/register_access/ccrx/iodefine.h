/*
* Copyright (c) 2014(2015-2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/*********************************************************************************
*
* Device     : RX/RX200/RX231
*
* File Name  : iodefine.h
*
* Abstract   : Definition of I/O Register.
*
* History    : 0.5A  (2014-09-18)  [Hardware Manual Revision : 0.50]
*            : 1.0A  (2015-05-18)  [Hardware Manual Revision : 1.00]
*            : 1.0C  (2015-07-21)  [Hardware Manual Revision : 1.00]
*            : 1.0D  (2015-09-02)  [Hardware Manual Revision : 1.00]
*            : 1.0E  (2016-02-05)  [Hardware Manual Revision : 1.00]
*            : 1.0F  (2016-02-26)  [Hardware Manual Revision : 1.00]
*            : 1.0G  (2016-11-10)  [Hardware Manual Revision : 1.00]
*            : 1.0H  (2016-12-06)  [Hardware Manual Revision : 1.00]
*            : 1.0I  (2017-04-24)  [Hardware Manual Revision : 1.00]
*            : 1.0J  (2023-03-03)  [Hardware Manual Revision : 1.00]
*            : 1.00K (2025-02-14)  [Hardware Manual Revision : 1.00]
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
*********************************************************************************/
/********************************************************************************/
/*                                                                              */
/*  DESCRIPTION : Definition of ICU Register                                    */
/*  CPU TYPE    : RX231                                                         */
/*                                                                              */
/*  Usage : IR,DTCER,IER,IPR of ICU Register                                    */
/*     The following IR, DTCE, IEN, IPR macro functions simplify usage.         */
/*     The bit access operation is "Bit_Name(interrupt source,name)".           */
/*     A part of the name can be omitted.                                       */
/*     for example :                                                            */
/*       IR(MTU0,TGIA0) = 0;     expands to :                                   */
/*         ICU.IR[114].BIT.IR = 0;                                              */
/*                                                                              */
/*       DTCE(ICU,IRQ0) = 1;     expands to :                                   */
/*         ICU.DTCER[64].BIT.DTCE = 1;                                          */
/*                                                                              */
/*       IEN(CMT0,CMI0) = 1;     expands to :                                   */
/*         ICU.IER[0x03].BIT.IEN4 = 1;                                          */
/*                                                                              */
/*       IPR(MTU1,TGIA1) = 2;    expands to :                                   */
/*       IPR(MTU1,TGI  ) = 2;    // TGIA1,TGIB1 share IPR level.                */
/*         ICU.IPR[121].BIT.IPR = 2;                                            */
/*                                                                              */
/*       IPR(SCI0,ERI0) = 3;     expands to :                                   */
/*       IPR(SCI0,    ) = 3;     // SCI0 uses single IPR for all sources.       */
/*         ICU.IPR[214].BIT.IPR = 3;                                            */
/*                                                                              */
/*  Usage : #pragma interrupt Function_Identifier(vect=**)                      */
/*     The number of vector is "(interrupt source, name)".                      */
/*     for example :                                                            */
/*       #pragma interrupt INT_IRQ0(vect=VECT(ICU,IRQ0))          expands to :  */
/*         #pragma interrupt INT_IRQ0(vect=64)                                  */
/*       #pragma interrupt INT_CMT0_CMI0(vect=VECT(CMT0,CMI0))    expands to :  */
/*         #pragma interrupt INT_CMT0_CMI0(vect=28)                             */
/*       #pragma interrupt INT_MTU0_TGIA0(vect=VECT(MTU0,TGIA0))  expands to :  */
/*         #pragma interrupt INT_MTU0_TGIA0(vect=114)                           */
/*       #pragma interrupt INT_TPU0_TGI0A(vect=VECT(TPU0,TGI0A))  expands to :  */
/*         #pragma interrupt INT_TPU0_TGI0A(vect=142)                           */
/*                                                                              */
/*  Usage : MSTPCRA,MSTPCRB,MSTPCRC of SYSTEM Register                          */
/*     The bit access operation is "MSTP(name)".                                */
/*     The name that can be used is a macro name defined with "iodefine.h".     */
/*     for example :                                                            */
/*       MSTP(TMR2) = 0;    // TMR2,TMR3,TMR23                    expands to :  */
/*         SYSTEM.MSTPCRA.BIT.MSTPA4  = 0;                                      */
/*       MSTP(SCI0) = 0;    // SCI0,SMCI0                         expands to :  */
/*         SYSTEM.MSTPCRB.BIT.MSTPB31 = 0;                                      */
/*       MSTP(MTU4) = 0;    // MTU,MTU0,MTU1,MTU2,MTU3,MTU4,MTU5  expands to :  */
/*         SYSTEM.MSTPCRA.BIT.MSTPA9  = 0;                                      */
/*       MSTP(TPU4) = 0;    // TPU,TPU0,TPU1,TPU2,TPU3,TPU4,TPU5  expands to :  */
/*         SYSTEM.MSTPCRA.BIT.MSTPA13 = 0;                                      */
/*       MSTP(CMT3) = 0;    // CMT2,CMT3                          expands to :  */
/*         SYSTEM.MSTPCRA.BIT.MSTPA14 = 0;                                      */
/*                                                                              */
/*                                                                              */
/********************************************************************************/
#ifndef __RX231IODEFINE_HEADER__
#define __RX231IODEFINE_HEADER__
#pragma bit_order left
#pragma unpack
struct st_bsc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char STSCLR:1;
		} BIT;
	} BERCLR;
	char           wk0[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char TOEN:1;
			unsigned char IGAEN:1;
		} BIT;
	} BEREN;
	char           wk1[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char MST:3;
			unsigned char :2;
			unsigned char TO:1;
			unsigned char IA:1;
		} BIT;
	} BERSR1;
	char           wk2[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short ADDR:13;
			unsigned short :3;
		} BIT;
	} BERSR2;
	char           wk3[4];
	union {
		unsigned short WORD;
		struct {
			unsigned short :2;
			unsigned short BPEB:2;
			unsigned short BPFB:2;
			unsigned short BPHB:2;
			unsigned short BPGB:2;
			unsigned short BPIB:2;
			unsigned short BPRO:2;
			unsigned short BPRA:2;
		} BIT;
	} BUSPRI;
	char           wk4[7408];
	union {
		unsigned short WORD;
		struct {
			unsigned short PRMOD:1;
			unsigned short :5;
			unsigned short PWENB:1;
			unsigned short PRENB:1;
			unsigned short :4;
			unsigned short EWENB:1;
			unsigned short :2;
			unsigned short WRMOD:1;
		} BIT;
	} CS0MOD;
	union {
		unsigned long LONG;
		struct {
			unsigned long :3;
			unsigned long CSRWAIT:5;
			unsigned long :3;
			unsigned long CSWWAIT:5;
			unsigned long :5;
			unsigned long CSPRWAIT:3;
			unsigned long :5;
			unsigned long CSPWWAIT:3;
		} BIT;
	} CS0WCR1;
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long CSON:3;
			unsigned long :1;
			unsigned long WDON:3;
			unsigned long :1;
			unsigned long WRON:3;
			unsigned long :1;
			unsigned long RDON:3;
			unsigned long :2;
			unsigned long AWAIT:2;
			unsigned long :1;
			unsigned long WDOFF:3;
			unsigned long :1;
			unsigned long CSWOFF:3;
			unsigned long :1;
			unsigned long CSROFF:3;
		} BIT;
	} CS0WCR2;
	char           wk5[6];
	union {
		unsigned short WORD;
		struct {
			unsigned short PRMOD:1;
			unsigned short :5;
			unsigned short PWENB:1;
			unsigned short PRENB:1;
			unsigned short :4;
			unsigned short EWENB:1;
			unsigned short :2;
			unsigned short WRMOD:1;
		} BIT;
	} CS1MOD;
	union {
		unsigned long LONG;
		struct {
			unsigned long :3;
			unsigned long CSRWAIT:5;
			unsigned long :3;
			unsigned long CSWWAIT:5;
			unsigned long :5;
			unsigned long CSPRWAIT:3;
			unsigned long :5;
			unsigned long CSPWWAIT:3;
		} BIT;
	} CS1WCR1;
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long CSON:3;
			unsigned long :1;
			unsigned long WDON:3;
			unsigned long :1;
			unsigned long WRON:3;
			unsigned long :1;
			unsigned long RDON:3;
			unsigned long :2;
			unsigned long AWAIT:2;
			unsigned long :1;
			unsigned long WDOFF:3;
			unsigned long :1;
			unsigned long CSWOFF:3;
			unsigned long :1;
			unsigned long CSROFF:3;
		} BIT;
	} CS1WCR2;
	char           wk6[6];
	union {
		unsigned short WORD;
		struct {
			unsigned short PRMOD:1;
			unsigned short :5;
			unsigned short PWENB:1;
			unsigned short PRENB:1;
			unsigned short :4;
			unsigned short EWENB:1;
			unsigned short :2;
			unsigned short WRMOD:1;
		} BIT;
	} CS2MOD;
	union {
		unsigned long LONG;
		struct {
			unsigned long :3;
			unsigned long CSRWAIT:5;
			unsigned long :3;
			unsigned long CSWWAIT:5;
			unsigned long :5;
			unsigned long CSPRWAIT:3;
			unsigned long :5;
			unsigned long CSPWWAIT:3;
		} BIT;
	} CS2WCR1;
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long CSON:3;
			unsigned long :1;
			unsigned long WDON:3;
			unsigned long :1;
			unsigned long WRON:3;
			unsigned long :1;
			unsigned long RDON:3;
			unsigned long :2;
			unsigned long AWAIT:2;
			unsigned long :1;
			unsigned long WDOFF:3;
			unsigned long :1;
			unsigned long CSWOFF:3;
			unsigned long :1;
			unsigned long CSROFF:3;
		} BIT;
	} CS2WCR2;
	char           wk7[6];
	union {
		unsigned short WORD;
		struct {
			unsigned short PRMOD:1;
			unsigned short :5;
			unsigned short PWENB:1;
			unsigned short PRENB:1;
			unsigned short :4;
			unsigned short EWENB:1;
			unsigned short :2;
			unsigned short WRMOD:1;
		} BIT;
	} CS3MOD;
	union {
		unsigned long LONG;
		struct {
			unsigned long :3;
			unsigned long CSRWAIT:5;
			unsigned long :3;
			unsigned long CSWWAIT:5;
			unsigned long :5;
			unsigned long CSPRWAIT:3;
			unsigned long :5;
			unsigned long CSPWWAIT:3;
		} BIT;
	} CS3WCR1;
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long CSON:3;
			unsigned long :1;
			unsigned long WDON:3;
			unsigned long :1;
			unsigned long WRON:3;
			unsigned long :1;
			unsigned long RDON:3;
			unsigned long :2;
			unsigned long AWAIT:2;
			unsigned long :1;
			unsigned long WDOFF:3;
			unsigned long :1;
			unsigned long CSWOFF:3;
			unsigned long :1;
			unsigned long CSROFF:3;
		} BIT;
	} CS3WCR2;
	char           wk8[1990];
	union {
		unsigned short WORD;
		struct {
			unsigned short :3;
			unsigned short MPXEN:1;
			unsigned short :3;
			unsigned short EMODE:1;
			unsigned short :2;
			unsigned short BSIZE:2;
			unsigned short :3;
			unsigned short EXENB:1;
		} BIT;
	} CS0CR;
	char           wk9[6];
	union {
		unsigned short WORD;
		struct {
			unsigned short :4;
			unsigned short WRCV:4;
			unsigned short :4;
			unsigned short RRCV:4;
		} BIT;
	} CS0REC;
	char           wk10[6];
	union {
		unsigned short WORD;
		struct {
			unsigned short :3;
			unsigned short MPXEN:1;
			unsigned short :3;
			unsigned short EMODE:1;
			unsigned short :2;
			unsigned short BSIZE:2;
			unsigned short :3;
			unsigned short EXENB:1;
		} BIT;
	} CS1CR;
	char           wk11[6];
	union {
		unsigned short WORD;
		struct {
			unsigned short :4;
			unsigned short WRCV:4;
			unsigned short :4;
			unsigned short RRCV:4;
		} BIT;
	} CS1REC;
	char           wk12[6];
	union {
		unsigned short WORD;
		struct {
			unsigned short :3;
			unsigned short MPXEN:1;
			unsigned short :3;
			unsigned short EMODE:1;
			unsigned short :2;
			unsigned short BSIZE:2;
			unsigned short :3;
			unsigned short EXENB:1;
		} BIT;
	} CS2CR;
	char           wk13[6];
	union {
		unsigned short WORD;
		struct {
			unsigned short :4;
			unsigned short WRCV:4;
			unsigned short :4;
			unsigned short RRCV:4;
		} BIT;
	} CS2REC;
	char           wk14[6];
	union {
		unsigned short WORD;
		struct {
			unsigned short :3;
			unsigned short MPXEN:1;
			unsigned short :3;
			unsigned short EMODE:1;
			unsigned short :2;
			unsigned short BSIZE:2;
			unsigned short :3;
			unsigned short EXENB:1;
		} BIT;
	} CS3CR;
	char           wk15[6];
	union {
		unsigned short WORD;
		struct {
			unsigned short :4;
			unsigned short WRCV:4;
			unsigned short :4;
			unsigned short RRCV:4;
		} BIT;
	} CS3REC;
	char           wk16[68];
	union {
		unsigned short WORD;
		struct {
			unsigned short RCVENM7:1;
			unsigned short RCVENM6:1;
			unsigned short RCVENM5:1;
			unsigned short RCVENM4:1;
			unsigned short RCVENM3:1;
			unsigned short RCVENM2:1;
			unsigned short RCVENM1:1;
			unsigned short RCVENM0:1;
			unsigned short RCVEN7:1;
			unsigned short RCVEN6:1;
			unsigned short RCVEN5:1;
			unsigned short RCVEN4:1;
			unsigned short RCVEN3:1;
			unsigned short RCVEN2:1;
			unsigned short RCVEN1:1;
			unsigned short RCVEN0:1;
		} BIT;
	} CSRECEN;
};

struct st_cac {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char CFME:1;
		} BIT;
	} CACR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char EDGES:2;
			unsigned char TCSS:2;
			unsigned char FMCS:3;
			unsigned char CACREFE:1;
		} BIT;
	} CACR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DFS:2;
			unsigned char RCDS:2;
			unsigned char RSCS:3;
			unsigned char RPS:1;
		} BIT;
	} CACR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char OVFFCL:1;
			unsigned char MENDFCL:1;
			unsigned char FERRFCL:1;
			unsigned char :1;
			unsigned char OVFIE:1;
			unsigned char MENDIE:1;
			unsigned char FERRIE:1;
		} BIT;
	} CAICR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char OVFF:1;
			unsigned char MENDF:1;
			unsigned char FERRF:1;
		} BIT;
	} CASTR;
	char           wk0[1];
	unsigned short CAULVR;
	unsigned short CALLVR;
	unsigned short CACNTBR;
};

struct st_rscan {
	union {
		unsigned short WORD;
		struct {
			unsigned short :3;
			unsigned short TSSS:1;
			unsigned short TSP:4;
			unsigned short :3;
			unsigned short DCS:1;
			unsigned short MME:1;
			unsigned short DRE:1;
			unsigned short DCE:1;
			unsigned short TPRI:1;
		} BIT;
	} GCFGL;
	union {
		unsigned short WORD;
		struct {
			unsigned short ITRCP:16;
		} BIT;
	} GCFGH;
	union {
		unsigned short WORD;
		struct {
			unsigned short :5;
			unsigned short THLEIE:1;
			unsigned short MEIE:1;
			unsigned short DEIE:1;
			unsigned short :5;
			unsigned short GSLPR:1;
			unsigned short GMDC:2;
		} BIT;
	} GCTRL;
	union {
		unsigned short WORD;
		struct {
			unsigned short :15;
			unsigned short TSRST:1;
		} BIT;
	} GCTRH;
	union {
		unsigned short WORD;
		struct {
			unsigned short :12;
			unsigned short GRAMINIT:1;
			unsigned short GSLPSTS:1;
			unsigned short GHLTSTS:1;
			unsigned short GRSTSTS:1;
		} BIT;
	} GSTS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char THLES:1;
			unsigned char MES:1;
			unsigned char DEF:1;
		} BIT;
	} GERFLL;
	char           wk0[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short TS:16;
		} BIT;
	} GTSC;
	union {
		unsigned short WORD;
		struct {
			unsigned short :11;
			unsigned short RNC0:5;
		} BIT;
	} GAFLCFG;
	union {
		unsigned short WORD;
		struct {
			unsigned short :11;
			unsigned short NRXMB:5;
		} BIT;
	} RMNB;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMNS:16;
		} BIT;
	} RMND0;
	char           wk1[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short RFIGCV:3;
			unsigned short RFIM:1;
			unsigned short :1;
			unsigned short RFDC:3;
			unsigned short :6;
			unsigned short RFIE:1;
			unsigned short RFE:1;
		} BIT;
	} RFCC0;
	union {
		unsigned short WORD;
		struct {
			unsigned short RFIGCV:3;
			unsigned short RFIM:1;
			unsigned short :1;
			unsigned short RFDC:3;
			unsigned short :6;
			unsigned short RFIE:1;
			unsigned short RFE:1;
		} BIT;
	} RFCC1;
	char           wk2[4];
	union {
		unsigned short WORD;
		struct {
			unsigned short :2;
			unsigned short RFMC:6;
			unsigned short :4;
			unsigned short RFIF:1;
			unsigned short RFMLT:1;
			unsigned short RFFLL:1;
			unsigned short RFEMP:1;
		} BIT;
	} RFSTS0;
	union {
		unsigned short WORD;
		struct {
			unsigned short :2;
			unsigned short RFMC:6;
			unsigned short :4;
			unsigned short RFIF:1;
			unsigned short RFMLT:1;
			unsigned short RFFLL:1;
			unsigned short RFEMP:1;
		} BIT;
	} RFSTS1;
	char           wk3[4];
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short RFPC:8;
		} BIT;
	} RFPCTR0;
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short RFPC:8;
		} BIT;
	} RFPCTR1;
	char           wk4[20];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char RF1MLT:1;
			unsigned char RF0MLT:1;
		} BIT;
	} RFMSTS;
	char           wk5[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char RF1IF:1;
			unsigned char RF0IF:1;
		} BIT;
	} RFISTS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char CF0IF:1;
		} BIT;
	} CFISTS;
	char           wk6[36];
	union {
		unsigned short WORD;
		struct {
			unsigned short :12;
			unsigned short THIF0:1;
			unsigned short CFTIF0:1;
			unsigned short TAIF0:1;
			unsigned short TSIF0:1;
		} BIT;
	} GTINTSTS;
	union {
		unsigned short WORD;
		struct {
			unsigned short :15;
			unsigned short RPAGE:1;
		} BIT;
	} GRWCR;
	union {
		unsigned short WORD;
		struct {
			unsigned short :5;
			unsigned short RTMPS:3;
			unsigned short :8;
		} BIT;
	} GTSTCFG;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char RTME:1;
			unsigned char :2;
		} BIT;
	} GTSTCTRL;
	char           wk7[5];
	union {
		unsigned short WORD;
		struct {
			unsigned short LOCK:16;
		} BIT;
	} GLOCKK;
	char           wk8[10];
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLID:16;
			} BIT;
		} GAFLIDL0;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMID:16;
			} BIT;
		} RMIDL0;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDE:1;
				unsigned short GAFLRTR:1;
				unsigned short GAFLLB:1;
				unsigned short GAFLID:13;
			} BIT;
		} GAFLIDH0;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMIDE:1;
				unsigned short RMRTR:1;
				unsigned short :1;
				unsigned short RMID:13;
			} BIT;
		} RMIDH0;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDM:16;
			} BIT;
		} GAFLML0;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMTS:16;
			} BIT;
		} RMTS0;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDEM:1;
				unsigned short GAFLRTRM:1;
				unsigned short :1;
				unsigned short GAFLIDM:13;
			} BIT;
		} GAFLMH0;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDLC:4;
				unsigned short RMPTR:12;
			} BIT;
		} RMPTR0;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLRMV:1;
				unsigned short GAFLRMDP:7;
				unsigned short :3;
				unsigned short GAFLFDP4:1;
				unsigned short :2;
				unsigned short GAFLFDP1:1;
				unsigned short GAFLFDP0:1;
			} BIT;
		} GAFLPL0;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB1:8;
				unsigned short RMDB0:8;
			} BIT;
		} RMDF00;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLDLC:4;
				unsigned short GAFLPTR:12;
			} BIT;
		} GAFLPH0;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB3:8;
				unsigned short RMDB2:8;
			} BIT;
		} RMDF10;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLID:16;
			} BIT;
		} GAFLIDL1;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB5:8;
				unsigned short RMDB4:8;
			} BIT;
		} RMDF20;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDE:1;
				unsigned short GAFLRTR:1;
				unsigned short GAFLLB:1;
				unsigned short GAFLID:13;
			} BIT;
		} GAFLIDH1;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB7:8;
				unsigned short RMDB6:8;
			} BIT;
		} RMDF30;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDM:16;
			} BIT;
		} GAFLML1;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMID:16;
			} BIT;
		} RMIDL1;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDEM:1;
				unsigned short GAFLRTRM:1;
				unsigned short :1;
				unsigned short GAFLIDM:13;
			} BIT;
		} GAFLMH1;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMIDE:1;
				unsigned short RMRTR:1;
				unsigned short :1;
				unsigned short RMID:13;
			} BIT;
		} RMIDH1;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLRMV:1;
				unsigned short GAFLRMDP:7;
				unsigned short :3;
				unsigned short GAFLFDP4:1;
				unsigned short :2;
				unsigned short GAFLFDP1:1;
				unsigned short GAFLFDP0:1;
			} BIT;
		} GAFLPL1;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMTS:16;
			} BIT;
		} RMTS1;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLDLC:4;
				unsigned short GAFLPTR:12;
			} BIT;
		} GAFLPH1;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDLC:4;
				unsigned short RMPTR:12;
			} BIT;
		} RMPTR1;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLID:16;
			} BIT;
		} GAFLIDL2;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB1:8;
				unsigned short RMDB0:8;
			} BIT;
		} RMDF01;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDE:1;
				unsigned short GAFLRTR:1;
				unsigned short GAFLLB:1;
				unsigned short GAFLID:13;
			} BIT;
		} GAFLIDH2;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB3:8;
				unsigned short RMDB2:8;
			} BIT;
		} RMDF11;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDM:16;
			} BIT;
		} GAFLML2;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB5:8;
				unsigned short RMDB4:8;
			} BIT;
		} RMDF21;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDEM:1;
				unsigned short GAFLRTRM:1;
				unsigned short :1;
				unsigned short GAFLIDM:13;
			} BIT;
		} GAFLMH2;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB7:8;
				unsigned short RMDB6:8;
			} BIT;
		} RMDF31;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLRMV:1;
				unsigned short GAFLRMDP:7;
				unsigned short :3;
				unsigned short GAFLFDP4:1;
				unsigned short :2;
				unsigned short GAFLFDP1:1;
				unsigned short GAFLFDP0:1;
			} BIT;
		} GAFLPL2;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMID:16;
			} BIT;
		} RMIDL2;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLDLC:4;
				unsigned short GAFLPTR:12;
			} BIT;
		} GAFLPH2;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMIDE:1;
				unsigned short RMRTR:1;
				unsigned short :1;
				unsigned short RMID:13;
			} BIT;
		} RMIDH2;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLID:16;
			} BIT;
		} GAFLIDL3;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMTS:16;
			} BIT;
		} RMTS2;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDE:1;
				unsigned short GAFLRTR:1;
				unsigned short GAFLLB:1;
				unsigned short GAFLID:13;
			} BIT;
		} GAFLIDH3;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDLC:4;
				unsigned short RMPTR:12;
			} BIT;
		} RMPTR2;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDM:16;
			} BIT;
		} GAFLML3;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB1:8;
				unsigned short RMDB0:8;
			} BIT;
		} RMDF02;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDEM:1;
				unsigned short GAFLRTRM:1;
				unsigned short :1;
				unsigned short GAFLIDM:13;
			} BIT;
		} GAFLMH3;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB3:8;
				unsigned short RMDB2:8;
			} BIT;
		} RMDF12;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLRMV:1;
				unsigned short GAFLRMDP:7;
				unsigned short :3;
				unsigned short GAFLFDP4:1;
				unsigned short :2;
				unsigned short GAFLFDP1:1;
				unsigned short GAFLFDP0:1;
			} BIT;
		} GAFLPL3;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB5:8;
				unsigned short RMDB4:8;
			} BIT;
		} RMDF22;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLDLC:4;
				unsigned short GAFLPTR:12;
			} BIT;
		} GAFLPH3;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB7:8;
				unsigned short RMDB6:8;
			} BIT;
		} RMDF32;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLID:16;
			} BIT;
		} GAFLIDL4;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMID:16;
			} BIT;
		} RMIDL3;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDE:1;
				unsigned short GAFLRTR:1;
				unsigned short GAFLLB:1;
				unsigned short GAFLID:13;
			} BIT;
		} GAFLIDH4;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMIDE:1;
				unsigned short RMRTR:1;
				unsigned short :1;
				unsigned short RMID:13;
			} BIT;
		} RMIDH3;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDM:16;
			} BIT;
		} GAFLML4;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMTS:16;
			} BIT;
		} RMTS3;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDEM:1;
				unsigned short GAFLRTRM:1;
				unsigned short :1;
				unsigned short GAFLIDM:13;
			} BIT;
		} GAFLMH4;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDLC:4;
				unsigned short RMPTR:12;
			} BIT;
		} RMPTR3;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLRMV:1;
				unsigned short GAFLRMDP:7;
				unsigned short :3;
				unsigned short GAFLFDP4:1;
				unsigned short :2;
				unsigned short GAFLFDP1:1;
				unsigned short GAFLFDP0:1;
			} BIT;
		} GAFLPL4;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB1:8;
				unsigned short RMDB0:8;
			} BIT;
		} RMDF03;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLDLC:4;
				unsigned short GAFLPTR:12;
			} BIT;
		} GAFLPH4;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB3:8;
				unsigned short RMDB2:8;
			} BIT;
		} RMDF13;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLID:16;
			} BIT;
		} GAFLIDL5;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB5:8;
				unsigned short RMDB4:8;
			} BIT;
		} RMDF23;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDE:1;
				unsigned short GAFLRTR:1;
				unsigned short GAFLLB:1;
				unsigned short GAFLID:13;
			} BIT;
		} GAFLIDH5;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB7:8;
				unsigned short RMDB6:8;
			} BIT;
		} RMDF33;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDM:16;
			} BIT;
		} GAFLML5;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMID:16;
			} BIT;
		} RMIDL4;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDEM:1;
				unsigned short GAFLRTRM:1;
				unsigned short :1;
				unsigned short GAFLIDM:13;
			} BIT;
		} GAFLMH5;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMIDE:1;
				unsigned short RMRTR:1;
				unsigned short :1;
				unsigned short RMID:13;
			} BIT;
		} RMIDH4;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLRMV:1;
				unsigned short GAFLRMDP:7;
				unsigned short :3;
				unsigned short GAFLFDP4:1;
				unsigned short :2;
				unsigned short GAFLFDP1:1;
				unsigned short GAFLFDP0:1;
			} BIT;
		} GAFLPL5;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMTS:16;
			} BIT;
		} RMTS4;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLDLC:4;
				unsigned short GAFLPTR:12;
			} BIT;
		} GAFLPH5;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDLC:4;
				unsigned short RMPTR:12;
			} BIT;
		} RMPTR4;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLID:16;
			} BIT;
		} GAFLIDL6;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB1:8;
				unsigned short RMDB0:8;
			} BIT;
		} RMDF04;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDE:1;
				unsigned short GAFLRTR:1;
				unsigned short GAFLLB:1;
				unsigned short GAFLID:13;
			} BIT;
		} GAFLIDH6;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB3:8;
				unsigned short RMDB2:8;
			} BIT;
		} RMDF14;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDM:16;
			} BIT;
		} GAFLML6;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB5:8;
				unsigned short RMDB4:8;
			} BIT;
		} RMDF24;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDEM:1;
				unsigned short GAFLRTRM:1;
				unsigned short :1;
				unsigned short GAFLIDM:13;
			} BIT;
		} GAFLMH6;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB7:8;
				unsigned short RMDB6:8;
			} BIT;
		} RMDF34;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLRMV:1;
				unsigned short GAFLRMDP:7;
				unsigned short :3;
				unsigned short GAFLFDP4:1;
				unsigned short :2;
				unsigned short GAFLFDP1:1;
				unsigned short GAFLFDP0:1;
			} BIT;
		} GAFLPL6;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMID:16;
			} BIT;
		} RMIDL5;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLDLC:4;
				unsigned short GAFLPTR:12;
			} BIT;
		} GAFLPH6;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMIDE:1;
				unsigned short RMRTR:1;
				unsigned short :1;
				unsigned short RMID:13;
			} BIT;
		} RMIDH5;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLID:16;
			} BIT;
		} GAFLIDL7;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMTS:16;
			} BIT;
		} RMTS5;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDE:1;
				unsigned short GAFLRTR:1;
				unsigned short GAFLLB:1;
				unsigned short GAFLID:13;
			} BIT;
		} GAFLIDH7;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDLC:4;
				unsigned short RMPTR:12;
			} BIT;
		} RMPTR5;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDM:16;
			} BIT;
		} GAFLML7;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB1:8;
				unsigned short RMDB0:8;
			} BIT;
		} RMDF05;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDEM:1;
				unsigned short GAFLRTRM:1;
				unsigned short :1;
				unsigned short GAFLIDM:13;
			} BIT;
		} GAFLMH7;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB3:8;
				unsigned short RMDB2:8;
			} BIT;
		} RMDF15;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLRMV:1;
				unsigned short GAFLRMDP:7;
				unsigned short :3;
				unsigned short GAFLFDP4:1;
				unsigned short :2;
				unsigned short GAFLFDP1:1;
				unsigned short GAFLFDP0:1;
			} BIT;
		} GAFLPL7;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB5:8;
				unsigned short RMDB4:8;
			} BIT;
		} RMDF25;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLDLC:4;
				unsigned short GAFLPTR:12;
			} BIT;
		} GAFLPH7;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB7:8;
				unsigned short RMDB6:8;
			} BIT;
		} RMDF35;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLID:16;
			} BIT;
		} GAFLIDL8;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMID:16;
			} BIT;
		} RMIDL6;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDE:1;
				unsigned short GAFLRTR:1;
				unsigned short GAFLLB:1;
				unsigned short GAFLID:13;
			} BIT;
		} GAFLIDH8;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMIDE:1;
				unsigned short RMRTR:1;
				unsigned short :1;
				unsigned short RMID:13;
			} BIT;
		} RMIDH6;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDM:16;
			} BIT;
		} GAFLML8;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMTS:16;
			} BIT;
		} RMTS6;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDEM:1;
				unsigned short GAFLRTRM:1;
				unsigned short :1;
				unsigned short GAFLIDM:13;
			} BIT;
		} GAFLMH8;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDLC:4;
				unsigned short RMPTR:12;
			} BIT;
		} RMPTR6;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLRMV:1;
				unsigned short GAFLRMDP:7;
				unsigned short :3;
				unsigned short GAFLFDP4:1;
				unsigned short :2;
				unsigned short GAFLFDP1:1;
				unsigned short GAFLFDP0:1;
			} BIT;
		} GAFLPL8;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB1:8;
				unsigned short RMDB0:8;
			} BIT;
		} RMDF06;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLDLC:4;
				unsigned short GAFLPTR:12;
			} BIT;
		} GAFLPH8;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB3:8;
				unsigned short RMDB2:8;
			} BIT;
		} RMDF16;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLID:16;
			} BIT;
		} GAFLIDL9;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB5:8;
				unsigned short RMDB4:8;
			} BIT;
		} RMDF26;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDE:1;
				unsigned short GAFLRTR:1;
				unsigned short GAFLLB:1;
				unsigned short GAFLID:13;
			} BIT;
		} GAFLIDH9;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB7:8;
				unsigned short RMDB6:8;
			} BIT;
		} RMDF36;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDM:16;
			} BIT;
		} GAFLML9;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMID:16;
			} BIT;
		} RMIDL7;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDEM:1;
				unsigned short GAFLRTRM:1;
				unsigned short :1;
				unsigned short GAFLIDM:13;
			} BIT;
		} GAFLMH9;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMIDE:1;
				unsigned short RMRTR:1;
				unsigned short :1;
				unsigned short RMID:13;
			} BIT;
		} RMIDH7;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLRMV:1;
				unsigned short GAFLRMDP:7;
				unsigned short :3;
				unsigned short GAFLFDP4:1;
				unsigned short :2;
				unsigned short GAFLFDP1:1;
				unsigned short GAFLFDP0:1;
			} BIT;
		} GAFLPL9;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMTS:16;
			} BIT;
		} RMTS7;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLDLC:4;
				unsigned short GAFLPTR:12;
			} BIT;
		} GAFLPH9;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDLC:4;
				unsigned short RMPTR:12;
			} BIT;
		} RMPTR7;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLID:16;
			} BIT;
		} GAFLIDL10;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB1:8;
				unsigned short RMDB0:8;
			} BIT;
		} RMDF07;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDE:1;
				unsigned short GAFLRTR:1;
				unsigned short GAFLLB:1;
				unsigned short GAFLID:13;
			} BIT;
		} GAFLIDH10;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB3:8;
				unsigned short RMDB2:8;
			} BIT;
		} RMDF17;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDM:16;
			} BIT;
		} GAFLML10;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB5:8;
				unsigned short RMDB4:8;
			} BIT;
		} RMDF27;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDEM:1;
				unsigned short GAFLRTRM:1;
				unsigned short :1;
				unsigned short GAFLIDM:13;
			} BIT;
		} GAFLMH10;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB7:8;
				unsigned short RMDB6:8;
			} BIT;
		} RMDF37;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLRMV:1;
				unsigned short GAFLRMDP:7;
				unsigned short :3;
				unsigned short GAFLFDP4:1;
				unsigned short :2;
				unsigned short GAFLFDP1:1;
				unsigned short GAFLFDP0:1;
			} BIT;
		} GAFLPL10;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMID:16;
			} BIT;
		} RMIDL8;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLDLC:4;
				unsigned short GAFLPTR:12;
			} BIT;
		} GAFLPH10;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMIDE:1;
				unsigned short RMRTR:1;
				unsigned short :1;
				unsigned short RMID:13;
			} BIT;
		} RMIDH8;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLID:16;
			} BIT;
		} GAFLIDL11;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMTS:16;
			} BIT;
		} RMTS8;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDE:1;
				unsigned short GAFLRTR:1;
				unsigned short GAFLLB:1;
				unsigned short GAFLID:13;
			} BIT;
		} GAFLIDH11;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDLC:4;
				unsigned short RMPTR:12;
			} BIT;
		} RMPTR8;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDM:16;
			} BIT;
		} GAFLML11;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB1:8;
				unsigned short RMDB0:8;
			} BIT;
		} RMDF08;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDEM:1;
				unsigned short GAFLRTRM:1;
				unsigned short :1;
				unsigned short GAFLIDM:13;
			} BIT;
		} GAFLMH11;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB3:8;
				unsigned short RMDB2:8;
			} BIT;
		} RMDF18;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLRMV:1;
				unsigned short GAFLRMDP:7;
				unsigned short :3;
				unsigned short GAFLFDP4:1;
				unsigned short :2;
				unsigned short GAFLFDP1:1;
				unsigned short GAFLFDP0:1;
			} BIT;
		} GAFLPL11;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB5:8;
				unsigned short RMDB4:8;
			} BIT;
		} RMDF28;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLDLC:4;
				unsigned short GAFLPTR:12;
			} BIT;
		} GAFLPH11;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB7:8;
				unsigned short RMDB6:8;
			} BIT;
		} RMDF38;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLID:16;
			} BIT;
		} GAFLIDL12;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMID:16;
			} BIT;
		} RMIDL9;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDE:1;
				unsigned short GAFLRTR:1;
				unsigned short GAFLLB:1;
				unsigned short GAFLID:13;
			} BIT;
		} GAFLIDH12;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMIDE:1;
				unsigned short RMRTR:1;
				unsigned short :1;
				unsigned short RMID:13;
			} BIT;
		} RMIDH9;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDM:16;
			} BIT;
		} GAFLML12;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMTS:16;
			} BIT;
		} RMTS9;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDEM:1;
				unsigned short GAFLRTRM:1;
				unsigned short :1;
				unsigned short GAFLIDM:13;
			} BIT;
		} GAFLMH12;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDLC:4;
				unsigned short RMPTR:12;
			} BIT;
		} RMPTR9;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLRMV:1;
				unsigned short GAFLRMDP:7;
				unsigned short :3;
				unsigned short GAFLFDP4:1;
				unsigned short :2;
				unsigned short GAFLFDP1:1;
				unsigned short GAFLFDP0:1;
			} BIT;
		} GAFLPL12;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB1:8;
				unsigned short RMDB0:8;
			} BIT;
		} RMDF09;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLDLC:4;
				unsigned short GAFLPTR:12;
			} BIT;
		} GAFLPH12;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB3:8;
				unsigned short RMDB2:8;
			} BIT;
		} RMDF19;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLID:16;
			} BIT;
		} GAFLIDL13;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB5:8;
				unsigned short RMDB4:8;
			} BIT;
		} RMDF29;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDE:1;
				unsigned short GAFLRTR:1;
				unsigned short GAFLLB:1;
				unsigned short GAFLID:13;
			} BIT;
		} GAFLIDH13;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB7:8;
				unsigned short RMDB6:8;
			} BIT;
		} RMDF39;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDM:16;
			} BIT;
		} GAFLML13;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMID:16;
			} BIT;
		} RMIDL10;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDEM:1;
				unsigned short GAFLRTRM:1;
				unsigned short :1;
				unsigned short GAFLIDM:13;
			} BIT;
		} GAFLMH13;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMIDE:1;
				unsigned short RMRTR:1;
				unsigned short :1;
				unsigned short RMID:13;
			} BIT;
		} RMIDH10;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLRMV:1;
				unsigned short GAFLRMDP:7;
				unsigned short :3;
				unsigned short GAFLFDP4:1;
				unsigned short :2;
				unsigned short GAFLFDP1:1;
				unsigned short GAFLFDP0:1;
			} BIT;
		} GAFLPL13;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMTS:16;
			} BIT;
		} RMTS10;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLDLC:4;
				unsigned short GAFLPTR:12;
			} BIT;
		} GAFLPH13;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDLC:4;
				unsigned short RMPTR:12;
			} BIT;
		} RMPTR10;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLID:16;
			} BIT;
		} GAFLIDL14;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB1:8;
				unsigned short RMDB0:8;
			} BIT;
		} RMDF010;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDE:1;
				unsigned short GAFLRTR:1;
				unsigned short GAFLLB:1;
				unsigned short GAFLID:13;
			} BIT;
		} GAFLIDH14;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB3:8;
				unsigned short RMDB2:8;
			} BIT;
		} RMDF110;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDM:16;
			} BIT;
		} GAFLML14;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB5:8;
				unsigned short RMDB4:8;
			} BIT;
		} RMDF210;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDEM:1;
				unsigned short GAFLRTRM:1;
				unsigned short :1;
				unsigned short GAFLIDM:13;
			} BIT;
		} GAFLMH14;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB7:8;
				unsigned short RMDB6:8;
			} BIT;
		} RMDF310;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLRMV:1;
				unsigned short GAFLRMDP:7;
				unsigned short :3;
				unsigned short GAFLFDP4:1;
				unsigned short :2;
				unsigned short GAFLFDP1:1;
				unsigned short GAFLFDP0:1;
			} BIT;
		} GAFLPL14;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMID:16;
			} BIT;
		} RMIDL11;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLDLC:4;
				unsigned short GAFLPTR:12;
			} BIT;
		} GAFLPH14;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMIDE:1;
				unsigned short RMRTR:1;
				unsigned short :1;
				unsigned short RMID:13;
			} BIT;
		} RMIDH11;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLID:16;
			} BIT;
		} GAFLIDL15;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMTS:16;
			} BIT;
		} RMTS11;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDE:1;
				unsigned short GAFLRTR:1;
				unsigned short GAFLLB:1;
				unsigned short GAFLID:13;
			} BIT;
		} GAFLIDH15;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDLC:4;
				unsigned short RMPTR:12;
			} BIT;
		} RMPTR11;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDM:16;
			} BIT;
		} GAFLML15;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB1:8;
				unsigned short RMDB0:8;
			} BIT;
		} RMDF011;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLIDEM:1;
				unsigned short GAFLRTRM:1;
				unsigned short :1;
				unsigned short GAFLIDM:13;
			} BIT;
		} GAFLMH15;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB3:8;
				unsigned short RMDB2:8;
			} BIT;
		} RMDF111;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLRMV:1;
				unsigned short GAFLRMDP:7;
				unsigned short :3;
				unsigned short GAFLFDP4:1;
				unsigned short :2;
				unsigned short GAFLFDP1:1;
				unsigned short GAFLFDP0:1;
			} BIT;
		} GAFLPL15;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB5:8;
				unsigned short RMDB4:8;
			} BIT;
		} RMDF211;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short GAFLDLC:4;
				unsigned short GAFLPTR:12;
			} BIT;
		} GAFLPH15;
		union {
			unsigned short WORD;
			struct {
				unsigned short RMDB7:8;
				unsigned short RMDB6:8;
			} BIT;
		} RMDF311;
	};
	union {
		unsigned short WORD;
		struct {
			unsigned short RMID:16;
		} BIT;
	} RMIDL12;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMIDE:1;
			unsigned short RMRTR:1;
			unsigned short :1;
			unsigned short RMID:13;
		} BIT;
	} RMIDH12;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMTS:16;
		} BIT;
	} RMTS12;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDLC:4;
			unsigned short RMPTR:12;
		} BIT;
	} RMPTR12;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDB1:8;
			unsigned short RMDB0:8;
		} BIT;
	} RMDF012;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDB3:8;
			unsigned short RMDB2:8;
		} BIT;
	} RMDF112;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDB5:8;
			unsigned short RMDB4:8;
		} BIT;
	} RMDF212;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDB7:8;
			unsigned short RMDB6:8;
		} BIT;
	} RMDF312;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMID:16;
		} BIT;
	} RMIDL13;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMIDE:1;
			unsigned short RMRTR:1;
			unsigned short :1;
			unsigned short RMID:13;
		} BIT;
	} RMIDH13;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMTS:16;
		} BIT;
	} RMTS13;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDLC:4;
			unsigned short RMPTR:12;
		} BIT;
	} RMPTR13;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDB1:8;
			unsigned short RMDB0:8;
		} BIT;
	} RMDF013;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDB3:8;
			unsigned short RMDB2:8;
		} BIT;
	} RMDF113;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDB5:8;
			unsigned short RMDB4:8;
		} BIT;
	} RMDF213;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDB7:8;
			unsigned short RMDB6:8;
		} BIT;
	} RMDF313;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMID:16;
		} BIT;
	} RMIDL14;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMIDE:1;
			unsigned short RMRTR:1;
			unsigned short :1;
			unsigned short RMID:13;
		} BIT;
	} RMIDH14;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMTS:16;
		} BIT;
	} RMTS14;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDLC:4;
			unsigned short RMPTR:12;
		} BIT;
	} RMPTR14;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDB1:8;
			unsigned short RMDB0:8;
		} BIT;
	} RMDF014;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDB3:8;
			unsigned short RMDB2:8;
		} BIT;
	} RMDF114;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDB5:8;
			unsigned short RMDB4:8;
		} BIT;
	} RMDF214;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDB7:8;
			unsigned short RMDB6:8;
		} BIT;
	} RMDF314;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMID:16;
		} BIT;
	} RMIDL15;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMIDE:1;
			unsigned short RMRTR:1;
			unsigned short :1;
			unsigned short RMID:13;
		} BIT;
	} RMIDH15;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMTS:16;
		} BIT;
	} RMTS15;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDLC:4;
			unsigned short RMPTR:12;
		} BIT;
	} RMPTR15;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDB1:8;
			unsigned short RMDB0:8;
		} BIT;
	} RMDF015;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDB3:8;
			unsigned short RMDB2:8;
		} BIT;
	} RMDF115;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDB5:8;
			unsigned short RMDB4:8;
		} BIT;
	} RMDF215;
	union {
		unsigned short WORD;
		struct {
			unsigned short RMDB7:8;
			unsigned short RMDB6:8;
		} BIT;
	} RMDF315;
	char           wk9[224];
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC0;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC1;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC2;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC3;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC4;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC5;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC6;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC7;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC8;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC9;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC10;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC11;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC12;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC13;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC14;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC15;
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short RFID:16;
			} BIT;
		} RFIDL0;
		union {
			unsigned short WORD;
			struct {
				unsigned short RDTA:16;
			} BIT;
		} RPGACC16;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short RFIDE:1;
				unsigned short RFRTR:1;
				unsigned short :1;
				unsigned short RFID:13;
			} BIT;
		} RFIDH0;
		union {
			unsigned short WORD;
			struct {
				unsigned short RDTA:16;
			} BIT;
		} RPGACC17;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short RFTS:16;
			} BIT;
		} RFTS0;
		union {
			unsigned short WORD;
			struct {
				unsigned short RDTA:16;
			} BIT;
		} RPGACC18;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short RFDLC:4;
				unsigned short RFPTR:12;
			} BIT;
		} RFPTR0;
		union {
			unsigned short WORD;
			struct {
				unsigned short RDTA:16;
			} BIT;
		} RPGACC19;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short RFDB1:8;
				unsigned short RFDB0:8;
			} BIT;
		} RFDF00;
		union {
			unsigned short WORD;
			struct {
				unsigned short RDTA:16;
			} BIT;
		} RPGACC20;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short RFDB3:8;
				unsigned short RFDB2:8;
			} BIT;
		} RFDF10;
		union {
			unsigned short WORD;
			struct {
				unsigned short RDTA:16;
			} BIT;
		} RPGACC21;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short RFDB5:8;
				unsigned short RFDB4:8;
			} BIT;
		} RFDF20;
		union {
			unsigned short WORD;
			struct {
				unsigned short RDTA:16;
			} BIT;
		} RPGACC22;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short RFDB7:8;
				unsigned short RFDB6:8;
			} BIT;
		} RFDF30;
		union {
			unsigned short WORD;
			struct {
				unsigned short RDTA:16;
			} BIT;
		} RPGACC23;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short RFID:16;
			} BIT;
		} RFIDL1;
		union {
			unsigned short WORD;
			struct {
				unsigned short RDTA:16;
			} BIT;
		} RPGACC24;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short RFIDE:1;
				unsigned short RFRTR:1;
				unsigned short :1;
				unsigned short RFID:13;
			} BIT;
		} RFIDH1;
		union {
			unsigned short WORD;
			struct {
				unsigned short RDTA:16;
			} BIT;
		} RPGACC25;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short RFTS:16;
			} BIT;
		} RFTS1;
		union {
			unsigned short WORD;
			struct {
				unsigned short RDTA:16;
			} BIT;
		} RPGACC26;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short RFDLC:4;
				unsigned short RFPTR:12;
			} BIT;
		} RFPTR1;
		union {
			unsigned short WORD;
			struct {
				unsigned short RDTA:16;
			} BIT;
		} RPGACC27;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short RFDB1:8;
				unsigned short RFDB0:8;
			} BIT;
		} RFDF01;
		union {
			unsigned short WORD;
			struct {
				unsigned short RDTA:16;
			} BIT;
		} RPGACC28;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short RFDB3:8;
				unsigned short RFDB2:8;
			} BIT;
		} RFDF11;
		union {
			unsigned short WORD;
			struct {
				unsigned short RDTA:16;
			} BIT;
		} RPGACC29;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short RFDB5:8;
				unsigned short RFDB4:8;
			} BIT;
		} RFDF21;
		union {
			unsigned short WORD;
			struct {
				unsigned short RDTA:16;
			} BIT;
		} RPGACC30;
	};
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short RFDB7:8;
				unsigned short RFDB6:8;
			} BIT;
		} RFDF31;
		union {
			unsigned short WORD;
			struct {
				unsigned short RDTA:16;
			} BIT;
		} RPGACC31;
	};
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC32;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC33;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC34;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC35;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC36;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC37;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC38;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC39;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC40;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC41;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC42;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC43;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC44;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC45;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC46;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC47;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC48;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC49;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC50;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC51;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC52;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC53;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC54;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC55;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC56;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC57;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC58;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC59;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC60;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC61;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC62;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC63;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC64;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC65;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC66;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC67;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC68;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC69;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC70;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC71;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC72;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC73;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC74;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC75;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC76;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC77;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC78;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC79;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC80;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC81;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC82;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC83;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC84;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC85;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC86;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC87;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC88;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC89;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC90;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC91;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC92;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC93;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC94;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC95;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC96;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC97;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC98;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC99;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC100;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC101;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC102;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC103;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC104;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC105;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC106;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC107;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC108;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC109;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC110;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC111;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC112;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC113;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC114;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC115;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC116;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC117;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC118;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC119;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC120;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC121;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC122;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC123;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC124;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC125;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC126;
	union {
		unsigned short WORD;
		struct {
			unsigned short RDTA:16;
		} BIT;
	} RPGACC127;
};

struct st_rscan0 {
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short BRP:10;
		} BIT;
	} CFGL;
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short SJW:2;
			unsigned short :1;
			unsigned short TSEG2:3;
			unsigned short TSEG1:4;
		} BIT;
	} CFGH;
	union {
		unsigned short WORD;
		struct {
			unsigned short ALIE:1;
			unsigned short BLIE:1;
			unsigned short OLIE:1;
			unsigned short BORIE:1;
			unsigned short BOEIE:1;
			unsigned short EPIE:1;
			unsigned short EWIE:1;
			unsigned short BEIE:1;
			unsigned short :4;
			unsigned short RTBO:1;
			unsigned short CSLPR:1;
			unsigned short CHMDC:2;
		} BIT;
	} CTRL;
	union {
		unsigned short WORD;
		struct {
			unsigned short :5;
			unsigned short CTMS:2;
			unsigned short CTME:1;
			unsigned short ERRD:1;
			unsigned short BOM:2;
			unsigned short :4;
			unsigned short TAIE:1;
		} BIT;
	} CTRH;
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short COMSTS:1;
			unsigned short RECSTS:1;
			unsigned short TRMSTS:1;
			unsigned short BOSTS:1;
			unsigned short EPSTS:1;
			unsigned short CSLPSTS:1;
			unsigned short CHLTSTS:1;
			unsigned short CRSTSTS:1;
		} BIT;
	} STSL;
	union {
		unsigned short WORD;
		struct {
			unsigned short TEC:8;
			unsigned short REC:8;
		} BIT;
	} STSH;
	union {
		unsigned short WORD;
		struct {
			unsigned short :1;
			unsigned short ADERR:1;
			unsigned short B0ERR:1;
			unsigned short B1ERR:1;
			unsigned short CERR:1;
			unsigned short AERR:1;
			unsigned short FERR:1;
			unsigned short SERR:1;
			unsigned short ALF:1;
			unsigned short BLF:1;
			unsigned short OVLF:1;
			unsigned short BORF:1;
			unsigned short BOEF:1;
			unsigned short EPF:1;
			unsigned short EWF:1;
			unsigned short BEF:1;
		} BIT;
	} ERFLL;
	union {
		unsigned short WORD;
		struct {
			unsigned short :1;
			unsigned short CRCREG:15;
		} BIT;
	} ERFLH;
	char           wk0[64];
	union {
		unsigned short WORD;
		struct {
			unsigned short CFIGCV:3;
			unsigned short CFIM:1;
			unsigned short :1;
			unsigned short CFDC:3;
			unsigned short :5;
			unsigned short CFTXIE:1;
			unsigned short CFRXIE:1;
			unsigned short CFE:1;
		} BIT;
	} CFCCL0;
	union {
		unsigned short WORD;
		struct {
			unsigned short CFITT:8;
			unsigned short :2;
			unsigned short CFTML:2;
			unsigned short CFITR:1;
			unsigned short CFITSS:1;
			unsigned short CFM:2;
		} BIT;
	} CFCCH0;
	char           wk1[4];
	union {
		unsigned short WORD;
		struct {
			unsigned short :2;
			unsigned short CFMC:6;
			unsigned short :3;
			unsigned short CFTXIF:1;
			unsigned short CFRXIF:1;
			unsigned short CFMLT:1;
			unsigned short CFFLL:1;
			unsigned short CFEMP:1;
		} BIT;
	} CFSTS0;
	char           wk2[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short CFPC:8;
		} BIT;
	} CFPCTR0;
	char           wk3[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char CF0MLT:1;
		} BIT;
	} CFMSTS;
	char           wk4[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char TMOM:1;
			unsigned char TMTAR:1;
			unsigned char TMTR:1;
		} BIT;
	} TMC0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char TMOM:1;
			unsigned char TMTAR:1;
			unsigned char TMTR:1;
		} BIT;
	} TMC1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char TMOM:1;
			unsigned char TMTAR:1;
			unsigned char TMTR:1;
		} BIT;
	} TMC2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char TMOM:1;
			unsigned char TMTAR:1;
			unsigned char TMTR:1;
		} BIT;
	} TMC3;
	char           wk5[4];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char TMTARM:1;
			unsigned char TMTRM:1;
			unsigned char TMTRF:2;
			unsigned char TMTSTS:1;
		} BIT;
	} TMSTS0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char TMTARM:1;
			unsigned char TMTRM:1;
			unsigned char TMTRF:2;
			unsigned char TMTSTS:1;
		} BIT;
	} TMSTS1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char TMTARM:1;
			unsigned char TMTRM:1;
			unsigned char TMTRF:2;
			unsigned char TMTSTS:1;
		} BIT;
	} TMSTS2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char TMTARM:1;
			unsigned char TMTRM:1;
			unsigned char TMTRF:2;
			unsigned char TMTSTS:1;
		} BIT;
	} TMSTS3;
	char           wk6[4];
	union {
		unsigned short WORD;
		struct {
			unsigned short :12;
			unsigned short TMTRSTS3:1;
			unsigned short TMTRSTS2:1;
			unsigned short TMTRSTS1:1;
			unsigned short TMTRSTS0:1;
		} BIT;
	} TMTRSTS;
	union {
		unsigned short WORD;
		struct {
			unsigned short :12;
			unsigned short TMTCSTS3:1;
			unsigned short TMTCSTS2:1;
			unsigned short TMTCSTS1:1;
			unsigned short TMTCSTS0:1;
		} BIT;
	} TMTCSTS;
	union {
		unsigned short WORD;
		struct {
			unsigned short :12;
			unsigned short TMTASTS3:1;
			unsigned short TMTASTS2:1;
			unsigned short TMTASTS1:1;
			unsigned short TMTASTS0:1;
		} BIT;
	} TMTASTS;
	union {
		unsigned short WORD;
		struct {
			unsigned short :12;
			unsigned short TMIE3:1;
			unsigned short TMIE2:1;
			unsigned short TMIE1:1;
			unsigned short TMIE0:1;
		} BIT;
	} TMIEC;
	union {
		unsigned short WORD;
		struct {
			unsigned short :5;
			unsigned short THLDTE:1;
			unsigned short THLIM:1;
			unsigned short THLIE:1;
			unsigned short :7;
			unsigned short THLE:1;
		} BIT;
	} THLCC0;
	char           wk7[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short :4;
			unsigned short THLMC:4;
			unsigned short :4;
			unsigned short THLIF:1;
			unsigned short THLELT:1;
			unsigned short THLFLL:1;
			unsigned short THLEMP:1;
		} BIT;
	} THLSTS0;
	char           wk8[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short THLPC:8;
		} BIT;
	} THLPCTR0;
	char           wk9[602];
	union {
		unsigned short WORD;
		struct {
			unsigned short CFID:16;
		} BIT;
	} CFIDL0;
	union {
		unsigned short WORD;
		struct {
			unsigned short CFIDE:1;
			unsigned short CFRTR:1;
			unsigned short THLEN:1;
			unsigned short CFID:13;
		} BIT;
	} CFIDH0;
	union {
		unsigned short WORD;
		struct {
			unsigned short CFTS:16;
		} BIT;
	} CFTS0;
	union {
		unsigned short WORD;
		struct {
			unsigned short CFDLC:4;
			unsigned short CFPTR:12;
		} BIT;
	} CFPTR0;
	union {
		unsigned short WORD;
		struct {
			unsigned short CFDB1:8;
			unsigned short CFDB0:8;
		} BIT;
	} CFDF00;
	union {
		unsigned short WORD;
		struct {
			unsigned short CFDB3:8;
			unsigned short CFDB2:8;
		} BIT;
	} CFDF10;
	union {
		unsigned short WORD;
		struct {
			unsigned short CFDB5:8;
			unsigned short CFDB4:8;
		} BIT;
	} CFDF20;
	union {
		unsigned short WORD;
		struct {
			unsigned short CFDB7:8;
			unsigned short CFDB6:8;
		} BIT;
	} CFDF30;
	char           wk10[16];
	union {
		unsigned short WORD;
		struct {
			unsigned short TMID:16;
		} BIT;
	} TMIDL0;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMIDE:1;
			unsigned short TMRTR:1;
			unsigned short THLEN:1;
			unsigned short TMID:13;
		} BIT;
	} TMIDH0;
	char           wk11[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDLC:4;
			unsigned short :4;
			unsigned short TMPTR:8;
		} BIT;
	} TMPTR0;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDB1:8;
			unsigned short TMDB0:8;
		} BIT;
	} TMDF00;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDB3:8;
			unsigned short TMDB2:8;
		} BIT;
	} TMDF10;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDB5:8;
			unsigned short TMDB4:8;
		} BIT;
	} TMDF20;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDB7:8;
			unsigned short TMDB6:8;
		} BIT;
	} TMDF30;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMID:16;
		} BIT;
	} TMIDL1;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMIDE:1;
			unsigned short TMRTR:1;
			unsigned short THLEN:1;
			unsigned short TMID:13;
		} BIT;
	} TMIDH1;
	char           wk12[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDLC:4;
			unsigned short :4;
			unsigned short TMPTR:8;
		} BIT;
	} TMPTR1;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDB1:8;
			unsigned short TMDB0:8;
		} BIT;
	} TMDF01;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDB3:8;
			unsigned short TMDB2:8;
		} BIT;
	} TMDF11;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDB5:8;
			unsigned short TMDB4:8;
		} BIT;
	} TMDF21;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDB7:8;
			unsigned short TMDB6:8;
		} BIT;
	} TMDF31;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMID:16;
		} BIT;
	} TMIDL2;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMIDE:1;
			unsigned short TMRTR:1;
			unsigned short THLEN:1;
			unsigned short TMID:13;
		} BIT;
	} TMIDH2;
	char           wk13[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDLC:4;
			unsigned short :4;
			unsigned short TMPTR:8;
		} BIT;
	} TMPTR2;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDB1:8;
			unsigned short TMDB0:8;
		} BIT;
	} TMDF02;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDB3:8;
			unsigned short TMDB2:8;
		} BIT;
	} TMDF12;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDB5:8;
			unsigned short TMDB4:8;
		} BIT;
	} TMDF22;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDB7:8;
			unsigned short TMDB6:8;
		} BIT;
	} TMDF32;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMID:16;
		} BIT;
	} TMIDL3;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMIDE:1;
			unsigned short TMRTR:1;
			unsigned short THLEN:1;
			unsigned short TMID:13;
		} BIT;
	} TMIDH3;
	char           wk14[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDLC:4;
			unsigned short :4;
			unsigned short TMPTR:8;
		} BIT;
	} TMPTR3;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDB1:8;
			unsigned short TMDB0:8;
		} BIT;
	} TMDF03;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDB3:8;
			unsigned short TMDB2:8;
		} BIT;
	} TMDF13;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDB5:8;
			unsigned short TMDB4:8;
		} BIT;
	} TMDF23;
	union {
		unsigned short WORD;
		struct {
			unsigned short TMDB7:8;
			unsigned short TMDB6:8;
		} BIT;
	} TMDF33;
	char           wk15[64];
	union {
		unsigned short WORD;
		struct {
			unsigned short TID:8;
			unsigned short :3;
			unsigned short BN:2;
			unsigned short :1;
			unsigned short BT:2;
		} BIT;
	} THLACC0;
};

struct st_cmpb {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char CPB1INI:1;
			unsigned char :3;
			unsigned char CPB0INI:1;
		} BIT;
	} CPBCNT1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char CPB1WCP:1;
			unsigned char :3;
			unsigned char CPB0WCP:1;
		} BIT;
	} CPBCNT2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CPB1OUT:1;
			unsigned char :3;
			unsigned char CPB0OUT:1;
			unsigned char :3;
		} BIT;
	} CPBFLG;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char CPB1INTPL:1;
			unsigned char CPB1INTEG:1;
			unsigned char CPB1INTEN:1;
			unsigned char :1;
			unsigned char CPB0INTPL:1;
			unsigned char CPB0INTEG:1;
			unsigned char CPB0INTEN:1;
		} BIT;
	} CPBINT;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CPB1F:2;
			unsigned char :1;
			unsigned char CPB1FEN:1;
			unsigned char CPB0F:2;
			unsigned char :1;
			unsigned char CPB0FEN:1;
		} BIT;
	} CPBF;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char CPBSPDMD:1;
		} BIT;
	} CPBMD;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char CPB1VRF:1;
			unsigned char :3;
			unsigned char CPB0VRF:1;
		} BIT;
	} CPBREF;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char CPB1OP:1;
			unsigned char CPB1OE:1;
			unsigned char :2;
			unsigned char CPB0OP:1;
			unsigned char CPB0OE:1;
		} BIT;
	} CPBOCR;
	char           wk0[24];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char CPB3INI:1;
			unsigned char :3;
			unsigned char CPB2INI:1;
		} BIT;
	} CPB1CNT1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char CPB3WCP:1;
			unsigned char :3;
			unsigned char CPB2WCP:1;
		} BIT;
	} CPB1CNT2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CPB3OUT:1;
			unsigned char :3;
			unsigned char CPB2OUT:1;
			unsigned char :3;
		} BIT;
	} CPB1FLG;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char CPB3INTPL:1;
			unsigned char CPB3INTEG:1;
			unsigned char CPB3INTEN:1;
			unsigned char :1;
			unsigned char CPB2INTPL:1;
			unsigned char CPB2INTEG:1;
			unsigned char CPB2INTEN:1;
		} BIT;
	} CPB1INT;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CPB3F:2;
			unsigned char :1;
			unsigned char CPB3FEN:1;
			unsigned char CPB2F:2;
			unsigned char :1;
			unsigned char CPB2FEN:1;
		} BIT;
	} CPB1F;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char CPB1SPDMD:1;
		} BIT;
	} CPB1MD;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char CPB3VRF:1;
			unsigned char :3;
			unsigned char CPB2VRF:1;
		} BIT;
	} CPB1REF;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char CPB3OP:1;
			unsigned char CPB3OE:1;
			unsigned char :2;
			unsigned char CPB2OP:1;
			unsigned char CPB2OE:1;
		} BIT;
	} CPB1OCR;
};

struct st_cmt {
	union {
		unsigned short WORD;
		struct {
			unsigned short :14;
			unsigned short STR1:1;
			unsigned short STR0:1;
		} BIT;
	} CMSTR0;
	char           wk0[14];
	union {
		unsigned short WORD;
		struct {
			unsigned short :14;
			unsigned short STR3:1;
			unsigned short STR2:1;
		} BIT;
	} CMSTR1;
};

struct st_cmt0 {
	union {
		unsigned short WORD;
		struct {
			unsigned short :9;
			unsigned short CMIE:1;
			unsigned short :4;
			unsigned short CKS:2;
		} BIT;
	} CMCR;
	unsigned short CMCNT;
	unsigned short CMCOR;
};

struct st_crc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char DORCLR:1;
			unsigned char :4;
			unsigned char LMS:1;
			unsigned char GPS:2;
		} BIT;
	} CRCCR;
	unsigned char  CRCDIR;
	unsigned short CRCDOR;
};

struct st_ctsu {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char :2;
			unsigned char CTSUINIT:1;
			unsigned char CTSUIOC:1;
			unsigned char CTSUSNZ:1;
			unsigned char CTSUCAP:1;
			unsigned char CTSUSTRT:1;
		} BIT;
	} CTSUCR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CTSUMD:2;
			unsigned char CTSUCLK:2;
			unsigned char CTSUATUNE1:1;
			unsigned char CTSUATUNE0:1;
			unsigned char CTSUCSW:1;
			unsigned char CTSUPON:1;
		} BIT;
	} CTSUCR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char CTSUSOFF:1;
			unsigned char CTSUPRMODE:2;
			unsigned char CTSUPRRATIO:4;
		} BIT;
	} CTSUSDPRS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CTSUSST:8;
		} BIT;
	} CTSUSST;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char CTSUMCH0:6;
		} BIT;
	} CTSUMCH0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char CTSUMCH1:6;
		} BIT;
	} CTSUMCH1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CTSUCHAC07:1;
			unsigned char CTSUCHAC06:1;
			unsigned char CTSUCHAC05:1;
			unsigned char CTSUCHAC04:1;
			unsigned char CTSUCHAC03:1;
			unsigned char CTSUCHAC02:1;
			unsigned char CTSUCHAC01:1;
			unsigned char CTSUCHAC00:1;
		} BIT;
	} CTSUCHAC0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CTSUCHAC17:1;
			unsigned char CTSUCHAC16:1;
			unsigned char CTSUCHAC15:1;
			unsigned char CTSUCHAC14:1;
			unsigned char CTSUCHAC13:1;
			unsigned char CTSUCHAC12:1;
			unsigned char CTSUCHAC11:1;
			unsigned char CTSUCHAC10:1;
		} BIT;
	} CTSUCHAC1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CTSUCHAC27:1;
			unsigned char CTSUCHAC26:1;
			unsigned char CTSUCHAC25:1;
			unsigned char CTSUCHAC24:1;
			unsigned char CTSUCHAC23:1;
			unsigned char CTSUCHAC22:1;
			unsigned char CTSUCHAC21:1;
			unsigned char CTSUCHAC20:1;
		} BIT;
	} CTSUCHAC2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CTSUCHAC37:1;
			unsigned char CTSUCHAC36:1;
			unsigned char CTSUCHAC35:1;
			unsigned char CTSUCHAC34:1;
			unsigned char CTSUCHAC33:1;
			unsigned char CTSUCHAC32:1;
			unsigned char CTSUCHAC31:1;
			unsigned char CTSUCHAC30:1;
		} BIT;
	} CTSUCHAC3;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char CTSUCHAC43:1;
			unsigned char CTSUCHAC42:1;
			unsigned char CTSUCHAC41:1;
			unsigned char CTSUCHAC40:1;
		} BIT;
	} CTSUCHAC4;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CTSUCHTRC07:1;
			unsigned char CTSUCHTRC06:1;
			unsigned char CTSUCHTRC05:1;
			unsigned char CTSUCHTRC04:1;
			unsigned char CTSUCHTRC03:1;
			unsigned char CTSUCHTRC02:1;
			unsigned char CTSUCHTRC01:1;
			unsigned char CTSUCHTRC00:1;
		} BIT;
	} CTSUCHTRC0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CTSUCHTRC17:1;
			unsigned char CTSUCHTRC16:1;
			unsigned char CTSUCHTRC15:1;
			unsigned char CTSUCHTRC14:1;
			unsigned char CTSUCHTRC13:1;
			unsigned char CTSUCHTRC12:1;
			unsigned char CTSUCHTRC11:1;
			unsigned char CTSUCHTRC10:1;
		} BIT;
	} CTSUCHTRC1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CTSUCHTRC27:1;
			unsigned char CTSUCHTRC26:1;
			unsigned char CTSUCHTRC25:1;
			unsigned char CTSUCHTRC24:1;
			unsigned char CTSUCHTRC23:1;
			unsigned char CTSUCHTRC22:1;
			unsigned char CTSUCHTRC21:1;
			unsigned char CTSUCHTRC20:1;
		} BIT;
	} CTSUCHTRC2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CTSUCHTRC37:1;
			unsigned char CTSUCHTRC36:1;
			unsigned char CTSUCHTRC35:1;
			unsigned char CTSUCHTRC34:1;
			unsigned char CTSUCHTRC33:1;
			unsigned char CTSUCHTRC32:1;
			unsigned char CTSUCHTRC31:1;
			unsigned char CTSUCHTRC30:1;
		} BIT;
	} CTSUCHTRC3;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char CTSUCHTRC43:1;
			unsigned char CTSUCHTRC42:1;
			unsigned char CTSUCHTRC41:1;
			unsigned char CTSUCHTRC40:1;
		} BIT;
	} CTSUCHTRC4;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char CTSUSSCNT:2;
			unsigned char :2;
			unsigned char CTSUSSMOD:2;
		} BIT;
	} CTSUDCLKC;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CTSUPS:1;
			unsigned char CTSUROVF:1;
			unsigned char CTSUSOVF:1;
			unsigned char CTSUDTSR:1;
			unsigned char :1;
			unsigned char CTSUSTC:3;
		} BIT;
	} CTSUST;
	union {
		unsigned short WORD;
		struct {
			unsigned short :4;
			unsigned short CTSUSSDIV:4;
			unsigned short :8;
		} BIT;
	} CTSUSSC;
	union {
		unsigned short WORD;
		struct {
			unsigned short CTSUSNUM:6;
			unsigned short CTSUSO:10;
		} BIT;
	} CTSUSO0;
	union {
		unsigned short WORD;
		struct {
			unsigned short :1;
			unsigned short CTSUICOG:2;
			unsigned short CTSUSDPA:5;
			unsigned short CTSURICOA:8;
		} BIT;
	} CTSUSO1;
	union {
		unsigned short WORD;
		struct {
			unsigned short CTSUSC:16;
		} BIT;
	} CTSUSC;
	union {
		unsigned short WORD;
		struct {
			unsigned short CTSURC:16;
		} BIT;
	} CTSURC;
	union {
		unsigned short WORD;
		struct {
			unsigned short CTSUICOMP:1;
			unsigned short :7;
			unsigned short CTSUTSOC:1;
			unsigned short CTSUCLKSEL1:1;
			unsigned short :2;
			unsigned short CTSUDRV:1;
			unsigned short CTSUTSOD:1;
			unsigned short CTSUSPMD:2;
		} BIT;
	} CTSUERRS;
	char           wk0[7730848];
	unsigned char  CTSUTRMR;
};

struct st_da {
	unsigned short DADR0;
	unsigned short DADR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DAOE1:1;
			unsigned char DAOE0:1;
			unsigned char :6;
		} BIT;
	} DACR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DPSEL:1;
			unsigned char :7;
		} BIT;
	} DADPR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DAADST:1;
			unsigned char :7;
		} BIT;
	} DAADSCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char REF:3;
		} BIT;
	} DAVREFCR;
};

struct st_dmac {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char DMST:1;
		} BIT;
	} DMAST;
};

struct st_dmac0 {
	void          *DMSAR;
	void          *DMDAR;
	unsigned long  DMCRA;
	unsigned short DMCRB;
	char           wk0[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short MD:2;
			unsigned short DTS:2;
			unsigned short :2;
			unsigned short SZ:2;
			unsigned short :6;
			unsigned short DCTG:2;
		} BIT;
	} DMTMD;
	char           wk1[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char DTIE:1;
			unsigned char ESIE:1;
			unsigned char RPTIE:1;
			unsigned char SARIE:1;
			unsigned char DARIE:1;
		} BIT;
	} DMINT;
	union {
		unsigned short WORD;
		struct {
			unsigned short SM:2;
			unsigned short :1;
			unsigned short SARA:5;
			unsigned short DM:2;
			unsigned short :1;
			unsigned short DARA:5;
		} BIT;
	} DMAMD;
	char           wk2[2];
	unsigned long  DMOFR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char DTE:1;
		} BIT;
	} DMCNT;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char CLRS:1;
			unsigned char :3;
			unsigned char SWREQ:1;
		} BIT;
	} DMREQ;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ACT:1;
			unsigned char :2;
			unsigned char DTIF:1;
			unsigned char :3;
			unsigned char ESIF:1;
		} BIT;
	} DMSTS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char DISEL:1;
		} BIT;
	} DMCSL;
};

struct st_dmac1 {
	void          *DMSAR;
	void          *DMDAR;
	unsigned long  DMCRA;
	unsigned short DMCRB;
	char           wk0[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short MD:2;
			unsigned short DTS:2;
			unsigned short :2;
			unsigned short SZ:2;
			unsigned short :6;
			unsigned short DCTG:2;
		} BIT;
	} DMTMD;
	char           wk1[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char DTIE:1;
			unsigned char ESIE:1;
			unsigned char RPTIE:1;
			unsigned char SARIE:1;
			unsigned char DARIE:1;
		} BIT;
	} DMINT;
	union {
		unsigned short WORD;
		struct {
			unsigned short SM:2;
			unsigned short :1;
			unsigned short SARA:5;
			unsigned short DM:2;
			unsigned short :1;
			unsigned short DARA:5;
		} BIT;
	} DMAMD;
	char           wk2[6];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char DTE:1;
		} BIT;
	} DMCNT;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char CLRS:1;
			unsigned char :3;
			unsigned char SWREQ:1;
		} BIT;
	} DMREQ;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ACT:1;
			unsigned char :2;
			unsigned char DTIF:1;
			unsigned char :3;
			unsigned char ESIF:1;
		} BIT;
	} DMSTS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char DISEL:1;
		} BIT;
	} DMCSL;
};

struct st_doc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char DOPCFCL:1;
			unsigned char DOPCF:1;
			unsigned char DOPCIE:1;
			unsigned char :1;
			unsigned char DCSEL:1;
			unsigned char OMS:2;
		} BIT;
	} DOCR;
	char           wk0[1];
	unsigned short DODIR;
	unsigned short DODSR;
};

struct st_dtc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char RRS:1;
			unsigned char :4;
		} BIT;
	} DTCCR;
	char           wk0[3];
	void          *DTCVBR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char SHORT:1;
		} BIT;
	} DTCADMOD;
	char           wk1[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char DTCST:1;
		} BIT;
	} DTCST;
	char           wk2[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short ACT:1;
			unsigned short :7;
			unsigned short VECN:8;
		} BIT;
	} DTCSTS;
};

struct st_elc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELCON:1;
			unsigned char :7;
		} BIT;
	} ELCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR[30];
	union {
		unsigned char BYTE;
		struct {
			unsigned char MTU3MD:2;
			unsigned char MTU2MD:2;
			unsigned char MTU1MD:2;
			unsigned char :2;
		} BIT;
	} ELOPA;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char MTU4MD:2;
		} BIT;
	} ELOPB;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char LPTMD:2;
			unsigned char CMT1MD:2;
			unsigned char :2;
		} BIT;
	} ELOPC;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char TMR2MD:2;
			unsigned char :2;
			unsigned char TMR0MD:2;
		} BIT;
	} ELOPD;
	union {
		unsigned char BYTE;
		struct {
			unsigned char PGR7:1;
			unsigned char PGR6:1;
			unsigned char PGR5:1;
			unsigned char PGR4:1;
			unsigned char PGR3:1;
			unsigned char PGR2:1;
			unsigned char PGR1:1;
			unsigned char PGR0:1;
		} BIT;
	} PGR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char PGR7:1;
			unsigned char PGR6:1;
			unsigned char PGR5:1;
			unsigned char PGR4:1;
			unsigned char PGR3:1;
			unsigned char PGR2:1;
			unsigned char PGR1:1;
			unsigned char PGR0:1;
		} BIT;
	} PGR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char PGCO:3;
			unsigned char :1;
			unsigned char PGCOVE:1;
			unsigned char PGCI:2;
		} BIT;
	} PGC1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char PGCO:3;
			unsigned char :1;
			unsigned char PGCOVE:1;
			unsigned char PGCI:2;
		} BIT;
	} PGC2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char PDBF7:1;
			unsigned char PDBF6:1;
			unsigned char PDBF5:1;
			unsigned char PDBF4:1;
			unsigned char PDBF3:1;
			unsigned char PDBF2:1;
			unsigned char PDBF1:1;
			unsigned char PDBF0:1;
		} BIT;
	} PDBF1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char PDBF7:1;
			unsigned char PDBF6:1;
			unsigned char PDBF5:1;
			unsigned char PDBF4:1;
			unsigned char PDBF3:1;
			unsigned char PDBF2:1;
			unsigned char PDBF1:1;
			unsigned char PDBF0:1;
		} BIT;
	} PDBF2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char PSM:2;
			unsigned char PSP:2;
			unsigned char PSB:3;
		} BIT;
	} PEL0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char PSM:2;
			unsigned char PSP:2;
			unsigned char PSB:3;
		} BIT;
	} PEL1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char PSM:2;
			unsigned char PSP:2;
			unsigned char PSB:3;
		} BIT;
	} PEL2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char PSM:2;
			unsigned char PSP:2;
			unsigned char PSB:3;
		} BIT;
	} PEL3;
	union {
		unsigned char BYTE;
		struct {
			unsigned char WI:1;
			unsigned char WE:1;
			unsigned char :5;
			unsigned char SEG:1;
		} BIT;
	} ELSEGR;
};

struct st_flash {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char DFLEN:1;
		} BIT;
	} DFLCTL;
	char           wk0[111];
	union {
		unsigned char BYTE;
		struct {
			unsigned char FMS2:1;
			unsigned char LVPE:1;
			unsigned char :1;
			unsigned char FMS1:1;
			unsigned char RPDIS:1;
			unsigned char :1;
			unsigned char FMS0:1;
			unsigned char :1;
		} BIT;
	} FPMCR;
	char           wk1[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char EXS:1;
		} BIT;
	} FASR;
	char           wk2[3];
	unsigned short FSARL;
	char           wk3[6];
	unsigned short FSARH;
	char           wk4[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char OPST:1;
			unsigned char STOP:1;
			unsigned char :2;
			unsigned char CMD:4;
		} BIT;
	} FCR;
	char           wk5[3];
	unsigned short FEARL;
	char           wk6[6];
	unsigned short FEARH;
	char           wk7[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char FRESET:1;
		} BIT;
	} FRESETR;
	char           wk8[7];
	union {
		unsigned char BYTE;
		struct {
			unsigned char EXRDY:1;
			unsigned char FRDY:1;
			unsigned char :6;
		} BIT;
	} FSTATR1;
	char           wk9[3];
	unsigned short FWB0;
	char           wk10[6];
	unsigned short FWB1;
	char           wk11[6];
	unsigned short FWB2;
	char           wk12[2];
	unsigned short FWB3;
	char           wk13[58];
	unsigned char  FPR;
	char           wk14[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char PERR:1;
		} BIT;
	} FPSR;
	char           wk15[59];
	union {
		unsigned short WORD;
		struct {
			unsigned short :7;
			unsigned short SASMF:1;
			unsigned short :8;
		} BIT;
	} FSCMR;
	char           wk16[6];
	unsigned short FAWSMR;
	char           wk17[6];
	unsigned short FAWEMR;
	char           wk18[6];
	union {
		unsigned char BYTE;
		struct {
			unsigned char SAS:2;
			unsigned char :1;
			unsigned char PCKA:5;
		} BIT;
	} FISR;
	char           wk19[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char OPST:1;
			unsigned char :4;
			unsigned char CMD:3;
		} BIT;
	} FEXCR;
	char           wk20[3];
	unsigned short FEAML;
	char           wk21[6];
	unsigned short FEAMH;
	char           wk22[6];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char EILGLERR:1;
			unsigned char ILGLERR:1;
			unsigned char BCERR:1;
			unsigned char :1;
			unsigned char PRGERR:1;
			unsigned char ERERR:1;
		} BIT;
	} FSTATR0;
	char           wk23[15809];
	union {
		unsigned short WORD;
		struct {
			unsigned short FEKEY:8;
			unsigned short FENTRYD:1;
			unsigned short :6;
			unsigned short FENTRY0:1;
		} BIT;
	} FENTRYR;
};

struct st_flashconst {
	unsigned long  UIDR0;
	unsigned long  UIDR1;
	unsigned long  UIDR2;
	unsigned long  UIDR3;
};

struct st_icu {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char IR:1;
		} BIT;
	} IR[254];
	char           wk0[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char DTCE:1;
		} BIT;
	} DTCER[253];
	char           wk1[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char IEN7:1;
			unsigned char IEN6:1;
			unsigned char IEN5:1;
			unsigned char IEN4:1;
			unsigned char IEN3:1;
			unsigned char IEN2:1;
			unsigned char IEN1:1;
			unsigned char IEN0:1;
		} BIT;
	} IER[32];
	char           wk2[192];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char SWINT:1;
		} BIT;
	} SWINTR;
	char           wk3[15];
	union {
		unsigned short WORD;
		struct {
			unsigned short FIEN:1;
			unsigned short :7;
			unsigned short FVCT:8;
		} BIT;
	} FIR;
	char           wk4[14];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char IPR:4;
		} BIT;
	} IPR[251];
	char           wk5[5];
	unsigned char  DMRSR0;
	char           wk6[3];
	unsigned char  DMRSR1;
	char           wk7[3];
	unsigned char  DMRSR2;
	char           wk8[3];
	unsigned char  DMRSR3;
	char           wk9[243];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char IRQMD:2;
			unsigned char :2;
		} BIT;
	} IRQCR[8];
	char           wk10[8];
	union {
		unsigned char BYTE;
		struct {
			unsigned char FLTEN7:1;
			unsigned char FLTEN6:1;
			unsigned char FLTEN5:1;
			unsigned char FLTEN4:1;
			unsigned char FLTEN3:1;
			unsigned char FLTEN2:1;
			unsigned char FLTEN1:1;
			unsigned char FLTEN0:1;
		} BIT;
	} IRQFLTE0;
	char           wk11[3];
	union {
		unsigned short WORD;
		struct {
			unsigned short FCLKSEL7:2;
			unsigned short FCLKSEL6:2;
			unsigned short FCLKSEL5:2;
			unsigned short FCLKSEL4:2;
			unsigned short FCLKSEL3:2;
			unsigned short FCLKSEL2:2;
			unsigned short FCLKSEL1:2;
			unsigned short FCLKSEL0:2;
		} BIT;
	} IRQFLTC0;
	char           wk12[106];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char VBATST:1;
			unsigned char LVD2ST:1;
			unsigned char LVD1ST:1;
			unsigned char IWDTST:1;
			unsigned char WDTST:1;
			unsigned char OSTST:1;
			unsigned char NMIST:1;
		} BIT;
	} NMISR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char VBATEN:1;
			unsigned char LVD2EN:1;
			unsigned char LVD1EN:1;
			unsigned char IWDTEN:1;
			unsigned char WDTEN:1;
			unsigned char OSTEN:1;
			unsigned char NMIEN:1;
		} BIT;
	} NMIER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char VBATCLR:1;
			unsigned char LVD2CLR:1;
			unsigned char LVD1CLR:1;
			unsigned char IWDTCLR:1;
			unsigned char WDTCLR:1;
			unsigned char OSTCLR:1;
			unsigned char NMICLR:1;
		} BIT;
	} NMICLR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char NMIMD:1;
			unsigned char :3;
		} BIT;
	} NMICR;
	char           wk13[12];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char NFLTEN:1;
		} BIT;
	} NMIFLTE;
	char           wk14[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char NFCLKSEL:2;
		} BIT;
	} NMIFLTC;
};

struct st_irda {
	union {
		unsigned char BYTE;
		struct {
			unsigned char IRE:1;
			unsigned char IRCKS:3;
			unsigned char IRTXINV:1;
			unsigned char IRRXINV:1;
			unsigned char :2;
		} BIT;
	} IRCR;
};

struct st_iwdt {
	unsigned char  IWDTRR;
	char           wk0[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short :2;
			unsigned short RPSS:2;
			unsigned short :2;
			unsigned short RPES:2;
			unsigned short CKS:4;
			unsigned short :2;
			unsigned short TOPS:2;
		} BIT;
	} IWDTCR;
	union {
		unsigned short WORD;
		struct {
			unsigned short REFEF:1;
			unsigned short UNDFF:1;
			unsigned short CNTVAL:14;
		} BIT;
	} IWDTSR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char RSTIRQS:1;
			unsigned char :7;
		} BIT;
	} IWDTRCR;
	char           wk1[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char SLCSTP:1;
			unsigned char :7;
		} BIT;
	} IWDTCSTPR;
};

struct st_lpt {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char LPCMRE0:1;
			unsigned char :1;
			unsigned char LPCNTCKSEL:1;
			unsigned char :1;
			unsigned char LPCNTPSSEL:3;
		} BIT;
	} LPTCR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char LPCNTSTP:1;
		} BIT;
	} LPTCR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char LPCNTRST:1;
			unsigned char LPCNTEN:1;
		} BIT;
	} LPTCR3;
	char           wk0[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short LPCNTPRD:16;
		} BIT;
	} LPTPRD;
	char           wk1[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short LPCMR0:16;
		} BIT;
	} LPCMR0;
	char           wk2[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short LPWKUPEN:1;
			unsigned short :15;
		} BIT;
	} LPWUCR;
};

struct st_mpc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char CS7E:1;
			unsigned char CS6E:1;
			unsigned char CS5E:1;
			unsigned char CS4E:1;
			unsigned char CS3E:1;
			unsigned char CS2E:1;
			unsigned char CS1E:1;
			unsigned char CS0E:1;
		} BIT;
	} PFCSE;
	char           wk0[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char A15E:1;
			unsigned char A14E:1;
			unsigned char A13E:1;
			unsigned char A12E:1;
			unsigned char A11E:1;
			unsigned char A10E:1;
			unsigned char A9E:1;
			unsigned char A8E:1;
		} BIT;
	} PFAOE0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char A23E:1;
			unsigned char A22E:1;
			unsigned char A21E:1;
			unsigned char A20E:1;
			unsigned char A19E:1;
			unsigned char A18E:1;
			unsigned char A17E:1;
			unsigned char A16E:1;
		} BIT;
	} PFAOE1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char WR1BC1E:1;
			unsigned char :1;
			unsigned char DHE:1;
			unsigned char :3;
			unsigned char ADRLE:1;
		} BIT;
	} PFBCR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char ALEOE:1;
			unsigned char WAITS:2;
		} BIT;
	} PFBCR1;
	char           wk1[23];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B0WI:1;
			unsigned char PFSWE:1;
			unsigned char :6;
		} BIT;
	} PWPR;
	char           wk2[35];
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :2;
			unsigned char PSEL:5;
		} BIT;
	} P03PFS;
	char           wk3[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :2;
			unsigned char PSEL:5;
		} BIT;
	} P05PFS;
	char           wk4[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P07PFS;
	char           wk5[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P12PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P13PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P14PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P15PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P16PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P17PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P20PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P21PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P22PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P23PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P24PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P25PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :2;
			unsigned char PSEL:5;
		} BIT;
	} P26PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :2;
			unsigned char PSEL:5;
		} BIT;
	} P27PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P30PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P31PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P32PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P33PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P34PFS;
	char           wk6[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P40PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P41PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P42PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P43PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P44PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P45PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P46PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P47PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P50PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P51PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P52PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P53PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P54PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P55PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P56PFS;
	char           wk7[33];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PA0PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PA1PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PA2PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PA3PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PA4PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PA5PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PA6PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PA7PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PB0PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PB1PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PB2PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PB3PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PB4PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PB5PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PB6PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PB7PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PC0PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PC1PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PC2PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PC3PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PC4PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PC5PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PC6PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PC7PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PD0PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PD1PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PD2PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PD3PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PD4PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PD5PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PD6PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PD7PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :2;
			unsigned char PSEL:5;
		} BIT;
	} PE0PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :2;
			unsigned char PSEL:5;
		} BIT;
	} PE1PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PE2PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :2;
			unsigned char PSEL:5;
		} BIT;
	} PE3PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :2;
			unsigned char PSEL:5;
		} BIT;
	} PE4PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PE5PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PE6PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PE7PFS;
	char           wk8[16];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PH0PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PH1PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PH2PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PH3PFS;
	char           wk9[7];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PJ3PFS;
};

struct st_mpu {
	union {
		unsigned long LONG;
		struct {
			unsigned long RSPN:28;
			unsigned long :4;
		} BIT;
	} RSPAGE0;
	union {
		unsigned long LONG;
		struct {
			unsigned long REPN:28;
			unsigned long UAC:3;
			unsigned long V:1;
		} BIT;
	} REPAGE0;
	union {
		unsigned long LONG;
		struct {
			unsigned long RSPN:28;
			unsigned long :4;
		} BIT;
	} RSPAGE1;
	union {
		unsigned long LONG;
		struct {
			unsigned long REPN:28;
			unsigned long UAC:3;
			unsigned long V:1;
		} BIT;
	} REPAGE1;
	union {
		unsigned long LONG;
		struct {
			unsigned long RSPN:28;
			unsigned long :4;
		} BIT;
	} RSPAGE2;
	union {
		unsigned long LONG;
		struct {
			unsigned long REPN:28;
			unsigned long UAC:3;
			unsigned long V:1;
		} BIT;
	} REPAGE2;
	union {
		unsigned long LONG;
		struct {
			unsigned long RSPN:28;
			unsigned long :4;
		} BIT;
	} RSPAGE3;
	union {
		unsigned long LONG;
		struct {
			unsigned long REPN:28;
			unsigned long UAC:3;
			unsigned long V:1;
		} BIT;
	} REPAGE3;
	union {
		unsigned long LONG;
		struct {
			unsigned long RSPN:28;
			unsigned long :4;
		} BIT;
	} RSPAGE4;
	union {
		unsigned long LONG;
		struct {
			unsigned long REPN:28;
			unsigned long UAC:3;
			unsigned long V:1;
		} BIT;
	} REPAGE4;
	union {
		unsigned long LONG;
		struct {
			unsigned long RSPN:28;
			unsigned long :4;
		} BIT;
	} RSPAGE5;
	union {
		unsigned long LONG;
		struct {
			unsigned long REPN:28;
			unsigned long UAC:3;
			unsigned long V:1;
		} BIT;
	} REPAGE5;
	union {
		unsigned long LONG;
		struct {
			unsigned long RSPN:28;
			unsigned long :4;
		} BIT;
	} RSPAGE6;
	union {
		unsigned long LONG;
		struct {
			unsigned long REPN:28;
			unsigned long UAC:3;
			unsigned long V:1;
		} BIT;
	} REPAGE6;
	union {
		unsigned long LONG;
		struct {
			unsigned long RSPN:28;
			unsigned long :4;
		} BIT;
	} RSPAGE7;
	union {
		unsigned long LONG;
		struct {
			unsigned long REPN:28;
			unsigned long UAC:3;
			unsigned long V:1;
		} BIT;
	} REPAGE7;
	char           wk0[192];
	union {
		unsigned long LONG;
		struct {
			unsigned long :31;
			unsigned long MPEN:1;
		} BIT;
	} MPEN;
	union {
		unsigned long LONG;
		struct {
			unsigned long :28;
			unsigned long UBAC:3;
			unsigned long :1;
		} BIT;
	} MPBAC;
	union {
		unsigned long LONG;
		struct {
			unsigned long :31;
			unsigned long CLR:1;
		} BIT;
	} MPECLR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :29;
			unsigned long DRW:1;
			unsigned long DMPER:1;
			unsigned long IMPER:1;
		} BIT;
	} MPESTS;
	char           wk1[4];
	union {
		unsigned long LONG;
		struct {
			unsigned long DEA:32;
		} BIT;
	} MPDEA;
	char           wk2[8];
	union {
		unsigned long LONG;
		struct {
			unsigned long SA:32;
		} BIT;
	} MPSA;
	union {
		unsigned short WORD;
		struct {
			unsigned short :15;
			unsigned short S:1;
		} BIT;
	} MPOPS;
	union {
		unsigned short WORD;
		struct {
			unsigned short :15;
			unsigned short INV:1;
		} BIT;
	} MPOPI;
	union {
		unsigned long LONG;
		struct {
			unsigned long :8;
			unsigned long HITI:8;
			unsigned long :12;
			unsigned long UHACI:3;
			unsigned long :1;
		} BIT;
	} MHITI;
	union {
		unsigned long LONG;
		struct {
			unsigned long :8;
			unsigned long HITD:8;
			unsigned long :12;
			unsigned long UHACD:3;
			unsigned long :1;
		} BIT;
	} MHITD;
};

struct st_mtu {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char OE4D:1;
			unsigned char OE4C:1;
			unsigned char OE3D:1;
			unsigned char OE4B:1;
			unsigned char OE4A:1;
			unsigned char OE3B:1;
		} BIT;
	} TOER;
	char           wk0[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char BDC:1;
			unsigned char N:1;
			unsigned char P:1;
			unsigned char FB:1;
			unsigned char WF:1;
			unsigned char VF:1;
			unsigned char UF:1;
		} BIT;
	} TGCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char PSYE:1;
			unsigned char :2;
			unsigned char TOCL:1;
			unsigned char TOCS:1;
			unsigned char OLSN:1;
			unsigned char OLSP:1;
		} BIT;
	} TOCR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char BF:2;
			unsigned char OLS3N:1;
			unsigned char OLS3P:1;
			unsigned char OLS2N:1;
			unsigned char OLS2P:1;
			unsigned char OLS1N:1;
			unsigned char OLS1P:1;
		} BIT;
	} TOCR2;
	char           wk1[4];
	unsigned short TCDR;
	unsigned short TDDR;
	char           wk2[8];
	unsigned short TCNTS;
	unsigned short TCBR;
	char           wk3[12];
	union {
		unsigned char BYTE;
		struct {
			unsigned char T3AEN:1;
			unsigned char T3ACOR:3;
			unsigned char T4VEN:1;
			unsigned char T4VCOR:3;
		} BIT;
	} TITCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char T3ACNT:3;
			unsigned char :1;
			unsigned char T4VCNT:3;
		} BIT;
	} TITCNT;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char BTE:2;
		} BIT;
	} TBTER;
	char           wk4[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char TDER:1;
		} BIT;
	} TDER;
	char           wk5[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char OLS3N:1;
			unsigned char OLS3P:1;
			unsigned char OLS2N:1;
			unsigned char OLS2P:1;
			unsigned char OLS1N:1;
			unsigned char OLS1P:1;
		} BIT;
	} TOLBR;
	char           wk6[41];
	union {
		unsigned char BYTE;
		struct {
			unsigned char CCE:1;
			unsigned char :6;
			unsigned char WRE:1;
		} BIT;
	} TWCR;
	char           wk7[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char CST4:1;
			unsigned char CST3:1;
			unsigned char :3;
			unsigned char CST2:1;
			unsigned char CST1:1;
			unsigned char CST0:1;
		} BIT;
	} TSTR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char SYNC4:1;
			unsigned char SYNC3:1;
			unsigned char :3;
			unsigned char SYNC2:1;
			unsigned char SYNC1:1;
			unsigned char SYNC0:1;
		} BIT;
	} TSYR;
	char           wk8[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char RWE:1;
		} BIT;
	} TRWER;
};

struct st_mtu0 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char NFCS:2;
			unsigned char NFDEN:1;
			unsigned char NFCEN:1;
			unsigned char NFBEN:1;
			unsigned char NFAEN:1;
		} BIT;
	} NFCR;
	char           wk0[111];
	union {
		unsigned char BYTE;
		struct {
			unsigned char CCLR:3;
			unsigned char CKEG:2;
			unsigned char TPSC:3;
		} BIT;
	} TCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char BFE:1;
			unsigned char BFB:1;
			unsigned char BFA:1;
			unsigned char MD:4;
		} BIT;
	} TMDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IOB:4;
			unsigned char IOA:4;
		} BIT;
	} TIORH;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IOD:4;
			unsigned char IOC:4;
		} BIT;
	} TIORL;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TTGE:1;
			unsigned char :2;
			unsigned char TCIEV:1;
			unsigned char TGIED:1;
			unsigned char TGIEC:1;
			unsigned char TGIEB:1;
			unsigned char TGIEA:1;
		} BIT;
	} TIER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCFD:1;
			unsigned char :7;
		} BIT;
	} TSR;
	unsigned short TCNT;
	unsigned short TGRA;
	unsigned short TGRB;
	unsigned short TGRC;
	unsigned short TGRD;
	char           wk1[16];
	unsigned short TGRE;
	unsigned short TGRF;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char TGIEF:1;
			unsigned char TGIEE:1;
		} BIT;
	} TIER2;
	char           wk2[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char TTSE:1;
			unsigned char TTSB:1;
			unsigned char TTSA:1;
		} BIT;
	} TBTM;
};

struct st_mtu1 {
	char           wk0[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char NFCS:2;
			unsigned char NFDEN:1;
			unsigned char NFCEN:1;
			unsigned char NFBEN:1;
			unsigned char NFAEN:1;
		} BIT;
	} NFCR;
	char           wk1[238];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char CCLR:2;
			unsigned char CKEG:2;
			unsigned char TPSC:3;
		} BIT;
	} TCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char MD:4;
		} BIT;
	} TMDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IOB:4;
			unsigned char IOA:4;
		} BIT;
	} TIOR;
	char           wk2[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TTGE:1;
			unsigned char :1;
			unsigned char TCIEU:1;
			unsigned char TCIEV:1;
			unsigned char :2;
			unsigned char TGIEB:1;
			unsigned char TGIEA:1;
		} BIT;
	} TIER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCFD:1;
			unsigned char :7;
		} BIT;
	} TSR;
	unsigned short TCNT;
	unsigned short TGRA;
	unsigned short TGRB;
	char           wk3[4];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char I2BE:1;
			unsigned char I2AE:1;
			unsigned char I1BE:1;
			unsigned char I1AE:1;
		} BIT;
	} TICCR;
};

struct st_mtu2 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char NFCS:2;
			unsigned char NFDEN:1;
			unsigned char NFCEN:1;
			unsigned char NFBEN:1;
			unsigned char NFAEN:1;
		} BIT;
	} NFCR;
	char           wk0[365];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char CCLR:2;
			unsigned char CKEG:2;
			unsigned char TPSC:3;
		} BIT;
	} TCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char MD:4;
		} BIT;
	} TMDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IOB:4;
			unsigned char IOA:4;
		} BIT;
	} TIOR;
	char           wk1[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TTGE:1;
			unsigned char :1;
			unsigned char TCIEU:1;
			unsigned char TCIEV:1;
			unsigned char :2;
			unsigned char TGIEB:1;
			unsigned char TGIEA:1;
		} BIT;
	} TIER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCFD:1;
			unsigned char :7;
		} BIT;
	} TSR;
	unsigned short TCNT;
	unsigned short TGRA;
	unsigned short TGRB;
};

struct st_mtu3 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char CCLR:3;
			unsigned char CKEG:2;
			unsigned char TPSC:3;
		} BIT;
	} TCR;
	char           wk0[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char BFB:1;
			unsigned char BFA:1;
			unsigned char MD:4;
		} BIT;
	} TMDR;
	char           wk1[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char IOB:4;
			unsigned char IOA:4;
		} BIT;
	} TIORH;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IOD:4;
			unsigned char IOC:4;
		} BIT;
	} TIORL;
	char           wk2[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TTGE:1;
			unsigned char :2;
			unsigned char TCIEV:1;
			unsigned char TGIED:1;
			unsigned char TGIEC:1;
			unsigned char TGIEB:1;
			unsigned char TGIEA:1;
		} BIT;
	} TIER;
	char           wk3[7];
	unsigned short TCNT;
	char           wk4[6];
	unsigned short TGRA;
	unsigned short TGRB;
	char           wk5[8];
	unsigned short TGRC;
	unsigned short TGRD;
	char           wk6[4];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCFD:1;
			unsigned char :7;
		} BIT;
	} TSR;
	char           wk7[11];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char TTSE:1;
			unsigned char TTSB:1;
			unsigned char TTSA:1;
		} BIT;
	} TBTM;
	char           wk8[90];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char NFCS:2;
			unsigned char NFDEN:1;
			unsigned char NFCEN:1;
			unsigned char NFBEN:1;
			unsigned char NFAEN:1;
		} BIT;
	} NFCR;
};

struct st_mtu4 {
	char           wk0[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char CCLR:3;
			unsigned char CKEG:2;
			unsigned char TPSC:3;
		} BIT;
	} TCR;
	char           wk1[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char BFB:1;
			unsigned char BFA:1;
			unsigned char MD:4;
		} BIT;
	} TMDR;
	char           wk2[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char IOB:4;
			unsigned char IOA:4;
		} BIT;
	} TIORH;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IOD:4;
			unsigned char IOC:4;
		} BIT;
	} TIORL;
	char           wk3[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TTGE:1;
			unsigned char TTGE2:1;
			unsigned char :1;
			unsigned char TCIEV:1;
			unsigned char TGIED:1;
			unsigned char TGIEC:1;
			unsigned char TGIEB:1;
			unsigned char TGIEA:1;
		} BIT;
	} TIER;
	char           wk4[8];
	unsigned short TCNT;
	char           wk5[8];
	unsigned short TGRA;
	unsigned short TGRB;
	char           wk6[8];
	unsigned short TGRC;
	unsigned short TGRD;
	char           wk7[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCFD:1;
			unsigned char :7;
		} BIT;
	} TSR;
	char           wk8[11];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char TTSE:1;
			unsigned char TTSB:1;
			unsigned char TTSA:1;
		} BIT;
	} TBTM;
	char           wk9[6];
	union {
		unsigned short WORD;
		struct {
			unsigned short BF:2;
			unsigned short :6;
			unsigned short UT4AE:1;
			unsigned short DT4AE:1;
			unsigned short UT4BE:1;
			unsigned short DT4BE:1;
			unsigned short ITA3AE:1;
			unsigned short ITA4VE:1;
			unsigned short ITB3AE:1;
			unsigned short ITB4VE:1;
		} BIT;
	} TADCR;
	char           wk10[2];
	unsigned short TADCORA;
	unsigned short TADCORB;
	unsigned short TADCOBRA;
	unsigned short TADCOBRB;
	char           wk11[72];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char NFCS:2;
			unsigned char NFDEN:1;
			unsigned char NFCEN:1;
			unsigned char NFBEN:1;
			unsigned char NFAEN:1;
		} BIT;
	} NFCR;
};

struct st_mtu5 {
	char           wk0[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char NFCS:2;
			unsigned char :1;
			unsigned char NFWEN:1;
			unsigned char NFVEN:1;
			unsigned char NFUEN:1;
		} BIT;
	} NFCR;
	char           wk1[490];
	unsigned short TCNTU;
	unsigned short TGRU;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char TPSC:2;
		} BIT;
	} TCRU;
	char           wk2[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char IOC:5;
		} BIT;
	} TIORU;
	char           wk3[9];
	unsigned short TCNTV;
	unsigned short TGRV;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char TPSC:2;
		} BIT;
	} TCRV;
	char           wk4[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char IOC:5;
		} BIT;
	} TIORV;
	char           wk5[9];
	unsigned short TCNTW;
	unsigned short TGRW;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char TPSC:2;
		} BIT;
	} TCRW;
	char           wk6[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char IOC:5;
		} BIT;
	} TIORW;
	char           wk7[11];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char TGIE5U:1;
			unsigned char TGIE5V:1;
			unsigned char TGIE5W:1;
		} BIT;
	} TIER;
	char           wk8[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char CSTU5:1;
			unsigned char CSTV5:1;
			unsigned char CSTW5:1;
		} BIT;
	} TSTR;
	char           wk9[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char CMPCLR5U:1;
			unsigned char CMPCLR5V:1;
			unsigned char CMPCLR5W:1;
		} BIT;
	} TCNTCMPCLR;
};

struct st_poe {
	union {
		unsigned short WORD;
		struct {
			unsigned char H;
			unsigned char L;
		} BYTE;
		struct {
			unsigned char POE3F:1;
			unsigned char POE2F:1;
			unsigned char POE1F:1;
			unsigned char POE0F:1;
			unsigned char :3;
			unsigned char PIE1:1;
			unsigned char POE3M:2;
			unsigned char POE2M:2;
			unsigned char POE1M:2;
			unsigned char POE0M:2;
		} BIT;
	} ICSR1;
	union {
		unsigned short WORD;
		struct {
			unsigned char H;
			unsigned char L;
		} BYTE;
		struct {
			unsigned char OSF1:1;
			unsigned char :5;
			unsigned char OCE1:1;
			unsigned char OIE1:1;
			unsigned char :8;
		} BIT;
	} OCSR1;
	char           wk0[4];
	union {
		unsigned short WORD;
		struct {
			unsigned char H;
			unsigned char L;
		} BYTE;
		struct {
			unsigned char :3;
			unsigned char POE8F:1;
			unsigned char :2;
			unsigned char POE8E:1;
			unsigned char PIE2:1;
			unsigned char :6;
			unsigned char POE8M:2;
		} BIT;
	} ICSR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char CH0HIZ:1;
			unsigned char CH34HIZ:1;
		} BIT;
	} SPOER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char PE3ZE:1;
			unsigned char PE2ZE:1;
			unsigned char PE1ZE:1;
			unsigned char PE0ZE:1;
		} BIT;
	} POECR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char P1CZEA:1;
			unsigned char P2CZEA:1;
			unsigned char P3CZEA:1;
			unsigned char :4;
		} BIT;
	} POECR2;
	char           wk1[1];
	union {
		unsigned short WORD;
		struct {
			unsigned char H;
			unsigned char L;
		} BYTE;
		struct {
			unsigned char :3;
			unsigned char OSTSTF:1;
			unsigned char :2;
			unsigned char OSTSTE:1;
			unsigned char :8;
			unsigned char :1;
		} BIT;
	} ICSR3;
};

struct st_port {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char PSEL5:1;
			unsigned char :1;
			unsigned char PSEL3:1;
			unsigned char :1;
			unsigned char PSEL1:1;
			unsigned char PSEL0:1;
		} BIT;
	} PSRB;
	union {
		unsigned char BYTE;
		struct {
			unsigned char PSEL7:1;
			unsigned char PSEL6:1;
			unsigned char :6;
		} BIT;
	} PSRA;
};

struct st_port0 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char :1;
			unsigned char B5:1;
			unsigned char :1;
			unsigned char B3:1;
			unsigned char :3;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char :1;
			unsigned char B5:1;
			unsigned char :1;
			unsigned char B3:1;
			unsigned char :3;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char :1;
			unsigned char B5:1;
			unsigned char :1;
			unsigned char B3:1;
			unsigned char :3;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char :1;
			unsigned char B5:1;
			unsigned char :1;
			unsigned char B3:1;
			unsigned char :3;
		} BIT;
	} PMR;
	char           wk3[95];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char :1;
			unsigned char B5:1;
			unsigned char :1;
			unsigned char B3:1;
			unsigned char :3;
		} BIT;
	} PCR;
};

struct st_port1 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char :2;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char :2;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char :2;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char :2;
		} BIT;
	} PMR;
	char           wk3[32];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :4;
		} BIT;
	} ODR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR1;
	char           wk4[61];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char :2;
		} BIT;
	} PCR;
	char           wk5[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char :2;
		} BIT;
	} DSCR;
};

struct st_port2 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[33];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR1;
	char           wk4[60];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
	char           wk5[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} DSCR;
};

struct st_port3 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[34];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :3;
			unsigned char B0:1;
		} BIT;
	} ODR1;
	char           wk4[59];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
	char           wk5[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} DSCR;
};

struct st_port4 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[95];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
};

struct st_port5 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[36];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR1;
	char           wk4[57];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
	char           wk5[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} DSCR;
};

struct st_porta {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[41];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR1;
	char           wk4[52];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
	char           wk5[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} DSCR;
};

struct st_portb {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[42];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR1;
	char           wk4[51];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
	char           wk5[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} DSCR;
};

struct st_portc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[43];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR1;
	char           wk4[50];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
	char           wk5[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} DSCR;
};

struct st_portd {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[95];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
	char           wk4[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} DSCR;
};

struct st_porte {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[45];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR1;
	char           wk4[48];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
	char           wk5[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} DSCR;
};

struct st_porth {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[95];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
	char           wk4[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} DSCR;
};

struct st_portj {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char B3:1;
			unsigned char :3;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char B3:1;
			unsigned char :3;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char B3:1;
			unsigned char :3;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char B3:1;
			unsigned char :3;
		} BIT;
	} PMR;
	char           wk3[49];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :6;
		} BIT;
	} ODR0;
	char           wk4[45];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char B3:1;
			unsigned char :3;
		} BIT;
	} PCR;
	char           wk5[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char B3:1;
			unsigned char :3;
		} BIT;
	} DSCR;
};

struct st_riic {
	union {
		unsigned char BYTE;
		struct {
			unsigned char ICE:1;
			unsigned char IICRST:1;
			unsigned char CLO:1;
			unsigned char SOWP:1;
			unsigned char SCLO:1;
			unsigned char SDAO:1;
			unsigned char SCLI:1;
			unsigned char SDAI:1;
		} BIT;
	} ICCR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char BBSY:1;
			unsigned char MST:1;
			unsigned char TRS:1;
			unsigned char :1;
			unsigned char SP:1;
			unsigned char RS:1;
			unsigned char ST:1;
			unsigned char :1;
		} BIT;
	} ICCR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char MTWP:1;
			unsigned char CKS:3;
			unsigned char BCWP:1;
			unsigned char BC:3;
		} BIT;
	} ICMR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DLCS:1;
			unsigned char SDDL:3;
			unsigned char :1;
			unsigned char TMOH:1;
			unsigned char TMOL:1;
			unsigned char TMOS:1;
		} BIT;
	} ICMR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char SMBS:1;
			unsigned char WAIT:1;
			unsigned char RDRFS:1;
			unsigned char ACKWP:1;
			unsigned char ACKBT:1;
			unsigned char ACKBR:1;
			unsigned char NF:2;
		} BIT;
	} ICMR3;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char SCLE:1;
			unsigned char NFE:1;
			unsigned char NACKE:1;
			unsigned char SALE:1;
			unsigned char NALE:1;
			unsigned char MALE:1;
			unsigned char TMOE:1;
		} BIT;
	} ICFER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char HOAE:1;
			unsigned char :1;
			unsigned char DIDE:1;
			unsigned char :1;
			unsigned char GCAE:1;
			unsigned char SAR2E:1;
			unsigned char SAR1E:1;
			unsigned char SAR0E:1;
		} BIT;
	} ICSER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TIE:1;
			unsigned char TEIE:1;
			unsigned char RIE:1;
			unsigned char NAKIE:1;
			unsigned char SPIE:1;
			unsigned char STIE:1;
			unsigned char ALIE:1;
			unsigned char TMOIE:1;
		} BIT;
	} ICIER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char HOA:1;
			unsigned char :1;
			unsigned char DID:1;
			unsigned char :1;
			unsigned char GCA:1;
			unsigned char AAS2:1;
			unsigned char AAS1:1;
			unsigned char AAS0:1;
		} BIT;
	} ICSR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TDRE:1;
			unsigned char TEND:1;
			unsigned char RDRF:1;
			unsigned char NACKF:1;
			unsigned char STOP:1;
			unsigned char START:1;
			unsigned char AL:1;
			unsigned char TMOF:1;
		} BIT;
	} ICSR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char SVA:7;
			unsigned char SVA0:1;
		} BIT;
	} SARL0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char SVA:2;
			unsigned char FS:1;
		} BIT;
	} SARU0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char SVA:7;
			unsigned char SVA0:1;
		} BIT;
	} SARL1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char SVA:2;
			unsigned char FS:1;
		} BIT;
	} SARU1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char SVA:7;
			unsigned char SVA0:1;
		} BIT;
	} SARL2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char SVA:2;
			unsigned char FS:1;
		} BIT;
	} SARU2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char BRL:5;
		} BIT;
	} ICBRL;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char BRH:5;
		} BIT;
	} ICBRH;
	unsigned char  ICDRT;
	unsigned char  ICDRR;
};

struct st_rspi {
	union {
		unsigned char BYTE;
		struct {
			unsigned char SPRIE:1;
			unsigned char SPE:1;
			unsigned char SPTIE:1;
			unsigned char SPEIE:1;
			unsigned char MSTR:1;
			unsigned char MODFEN:1;
			unsigned char TXMD:1;
			unsigned char SPMS:1;
		} BIT;
	} SPCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char SSL3P:1;
			unsigned char SSL2P:1;
			unsigned char SSL1P:1;
			unsigned char SSL0P:1;
		} BIT;
	} SSLP;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char MOIFE:1;
			unsigned char MOIFV:1;
			unsigned char :2;
			unsigned char SPLP2:1;
			unsigned char SPLP:1;
		} BIT;
	} SPPCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char SPRF:1;
			unsigned char :1;
			unsigned char SPTEF:1;
			unsigned char :1;
			unsigned char PERF:1;
			unsigned char MODF:1;
			unsigned char IDLNF:1;
			unsigned char OVRF:1;
		} BIT;
	} SPSR;
	union {
		unsigned long LONG;
		struct {
			unsigned short H;
		} WORD;
	} SPDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char SPSLN:3;
		} BIT;
	} SPSCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char SPECM:3;
			unsigned char :1;
			unsigned char SPCP:3;
		} BIT;
	} SPSSR;
	unsigned char  SPBR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char SPLW:1;
			unsigned char SPRDTD:1;
			unsigned char :2;
			unsigned char SPFC:2;
		} BIT;
	} SPDCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char SCKDL:3;
		} BIT;
	} SPCKD;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char SLNDL:3;
		} BIT;
	} SSLND;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char SPNDL:3;
		} BIT;
	} SPND;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char SCKASE:1;
			unsigned char PTE:1;
			unsigned char SPIIE:1;
			unsigned char SPOE:1;
			unsigned char SPPE:1;
		} BIT;
	} SPCR2;
	union {
		unsigned short WORD;
		struct {
			unsigned short SCKDEN:1;
			unsigned short SLNDEN:1;
			unsigned short SPNDEN:1;
			unsigned short LSBF:1;
			unsigned short SPB:4;
			unsigned short SSLKP:1;
			unsigned short SSLA:3;
			unsigned short BRDV:2;
			unsigned short CPOL:1;
			unsigned short CPHA:1;
		} BIT;
	} SPCMD0;
	union {
		unsigned short WORD;
		struct {
			unsigned short SCKDEN:1;
			unsigned short SLNDEN:1;
			unsigned short SPNDEN:1;
			unsigned short LSBF:1;
			unsigned short SPB:4;
			unsigned short SSLKP:1;
			unsigned short SSLA:3;
			unsigned short BRDV:2;
			unsigned short CPOL:1;
			unsigned short CPHA:1;
		} BIT;
	} SPCMD1;
	union {
		unsigned short WORD;
		struct {
			unsigned short SCKDEN:1;
			unsigned short SLNDEN:1;
			unsigned short SPNDEN:1;
			unsigned short LSBF:1;
			unsigned short SPB:4;
			unsigned short SSLKP:1;
			unsigned short SSLA:3;
			unsigned short BRDV:2;
			unsigned short CPOL:1;
			unsigned short CPHA:1;
		} BIT;
	} SPCMD2;
	union {
		unsigned short WORD;
		struct {
			unsigned short SCKDEN:1;
			unsigned short SLNDEN:1;
			unsigned short SPNDEN:1;
			unsigned short LSBF:1;
			unsigned short SPB:4;
			unsigned short SSLKP:1;
			unsigned short SSLA:3;
			unsigned short BRDV:2;
			unsigned short CPOL:1;
			unsigned short CPHA:1;
		} BIT;
	} SPCMD3;
	union {
		unsigned short WORD;
		struct {
			unsigned short SCKDEN:1;
			unsigned short SLNDEN:1;
			unsigned short SPNDEN:1;
			unsigned short LSBF:1;
			unsigned short SPB:4;
			unsigned short SSLKP:1;
			unsigned short SSLA:3;
			unsigned short BRDV:2;
			unsigned short CPOL:1;
			unsigned short CPHA:1;
		} BIT;
	} SPCMD4;
	union {
		unsigned short WORD;
		struct {
			unsigned short SCKDEN:1;
			unsigned short SLNDEN:1;
			unsigned short SPNDEN:1;
			unsigned short LSBF:1;
			unsigned short SPB:4;
			unsigned short SSLKP:1;
			unsigned short SSLA:3;
			unsigned short BRDV:2;
			unsigned short CPOL:1;
			unsigned short CPHA:1;
		} BIT;
	} SPCMD5;
	union {
		unsigned short WORD;
		struct {
			unsigned short SCKDEN:1;
			unsigned short SLNDEN:1;
			unsigned short SPNDEN:1;
			unsigned short LSBF:1;
			unsigned short SPB:4;
			unsigned short SSLKP:1;
			unsigned short SSLA:3;
			unsigned short BRDV:2;
			unsigned short CPOL:1;
			unsigned short CPHA:1;
		} BIT;
	} SPCMD6;
	union {
		unsigned short WORD;
		struct {
			unsigned short SCKDEN:1;
			unsigned short SLNDEN:1;
			unsigned short SPNDEN:1;
			unsigned short LSBF:1;
			unsigned short SPB:4;
			unsigned short SSLKP:1;
			unsigned short SSLA:3;
			unsigned short BRDV:2;
			unsigned short CPOL:1;
			unsigned short CPHA:1;
		} BIT;
	} SPCMD7;
};

struct st_rtc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char F1HZ:1;
			unsigned char F2HZ:1;
			unsigned char F4HZ:1;
			unsigned char F8HZ:1;
			unsigned char F16HZ:1;
			unsigned char F32HZ:1;
			unsigned char F64HZ:1;
		} BIT;
	} R64CNT;
	char           wk0[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char SEC10:3;
				unsigned char SEC1:4;
			} BIT;
		} RSECCNT;
		unsigned char  BCNT0;
	};
	char           wk1[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char MIN10:3;
				unsigned char MIN1:4;
			} BIT;
		} RMINCNT;
		unsigned char  BCNT1;
	};
	char           wk2[1];
	union {
		unsigned char  BCNT2;
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char PM:1;
				unsigned char HR10:2;
				unsigned char HR1:4;
			} BIT;
		} RHRCNT;
	};
	char           wk3[1];
	union {
		unsigned char  BCNT3;
		union {
			unsigned char BYTE;
			struct {
				unsigned char :5;
				unsigned char DAYW:3;
			} BIT;
		} RWKCNT;
	};
	char           wk4[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char DATE10:2;
			unsigned char DATE1:4;
		} BIT;
	} RDAYCNT;
	char           wk5[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char MON10:1;
			unsigned char MON1:4;
		} BIT;
	} RMONCNT;
	char           wk6[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short YR10:4;
			unsigned short YR1:4;
		} BIT;
	} RYRCNT;
	union {
		unsigned char  BCNT0AR;
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:1;
				unsigned char SEC10:3;
				unsigned char SEC1:4;
			} BIT;
		} RSECAR;
	};
	char           wk7[1];
	union {
		unsigned char  BCNT1AR;
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:1;
				unsigned char MIN10:3;
				unsigned char MIN1:4;
			} BIT;
		} RMINAR;
	};
	char           wk8[1];
	union {
		unsigned char  BCNT2AR;
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:1;
				unsigned char PM:1;
				unsigned char HR10:2;
				unsigned char HR1:4;
			} BIT;
		} RHRAR;
	};
	char           wk9[1];
	union {
		unsigned char  BCNT3AR;
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:1;
				unsigned char :4;
				unsigned char DAYW:3;
			} BIT;
		} RWKAR;
	};
	char           wk10[1];
	union {
		unsigned char  BCNT0AER;
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:1;
				unsigned char :1;
				unsigned char DATE10:2;
				unsigned char DATE1:4;
			} BIT;
		} RDAYAR;
	};
	char           wk11[1];
	union {
		unsigned char  BCNT1AER;
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:1;
				unsigned char :2;
				unsigned char MON10:1;
				unsigned char MON1:4;
			} BIT;
		} RMONAR;
	};
	char           wk12[1];
	union {
		unsigned short BCNT2AER;
		union {
			unsigned short WORD;
			struct {
				unsigned short :8;
				unsigned short YR10:4;
				unsigned short YR1:4;
			} BIT;
		} RYRAR;
	};
	union {
		unsigned char  BCNT3AER;
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:1;
				unsigned char :7;
			} BIT;
		} RYRAREN;
	};
	char           wk13[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char PES:4;
			unsigned char RTCOS:1;
			unsigned char PIE:1;
			unsigned char CIE:1;
			unsigned char AIE:1;
		} BIT;
	} RCR1;
	char           wk14[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char CNTMD:1;
			unsigned char HR24:1;
			unsigned char AADJP:1;
			unsigned char AADJE:1;
			unsigned char RTCOE:1;
			unsigned char ADJ30:1;
			unsigned char RESET:1;
			unsigned char START:1;
		} BIT;
	} RCR2;
	char           wk15[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char RTCDV:3;
			unsigned char RTCEN:1;
		} BIT;
	} RCR3;
	char           wk16[7];
	union {
		unsigned char BYTE;
		struct {
			unsigned char PMADJ:2;
			unsigned char ADJ:6;
		} BIT;
	} RADJ;
	char           wk17[17];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCEN:1;
			unsigned char :1;
			unsigned char TCNF:2;
			unsigned char :1;
			unsigned char TCST:1;
			unsigned char TCCT:2;
		} BIT;
	} RTCCR0;
	char           wk18[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCEN:1;
			unsigned char :1;
			unsigned char TCNF:2;
			unsigned char :1;
			unsigned char TCST:1;
			unsigned char TCCT:2;
		} BIT;
	} RTCCR1;
	char           wk19[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCEN:1;
			unsigned char :1;
			unsigned char TCNF:2;
			unsigned char :1;
			unsigned char TCST:1;
			unsigned char TCCT:2;
		} BIT;
	} RTCCR2;
	char           wk20[13];
	union {
		unsigned char  BCNT0CP0;
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char SEC10:3;
				unsigned char SEC1:4;
			} BIT;
		} RSECCP0;
	};
	char           wk21[1];
	union {
		unsigned char  BCNT1CP0;
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char MIN10:3;
				unsigned char MIN1:4;
			} BIT;
		} RMINCP0;
	};
	char           wk22[1];
	union {
		unsigned char  BCNT2CP0;
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char PM:1;
				unsigned char HR10:2;
				unsigned char HR1:4;
			} BIT;
		} RHRCP0;
	};
	char           wk23[3];
	union {
		unsigned char  BCNT3CP0;
		union {
			unsigned char BYTE;
			struct {
				unsigned char :2;
				unsigned char DATE10:2;
				unsigned char DATE1:4;
			} BIT;
		} RDAYCP0;
	};
	char           wk24[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char MON10:1;
			unsigned char MON1:4;
		} BIT;
	} RMONCP0;
	char           wk25[5];
	union {
		unsigned char  BCNT0CP1;
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char SEC10:3;
				unsigned char SEC1:4;
			} BIT;
		} RSECCP1;
	};
	char           wk26[1];
	union {
		unsigned char  BCNT1CP1;
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char MIN10:3;
				unsigned char MIN1:4;
			} BIT;
		} RMINCP1;
	};
	char           wk27[1];
	union {
		unsigned char  BCNT2CP1;
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char PM:1;
				unsigned char HR10:2;
				unsigned char HR1:4;
			} BIT;
		} RHRCP1;
	};
	char           wk28[3];
	union {
		unsigned char  BCNT3CP1;
		union {
			unsigned char BYTE;
			struct {
				unsigned char :2;
				unsigned char DATE10:2;
				unsigned char DATE1:4;
			} BIT;
		} RDAYCP1;
	};
	char           wk29[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char MON10:1;
			unsigned char MON1:4;
		} BIT;
	} RMONCP1;
	char           wk30[5];
	union {
		unsigned char  BCNT0CP2;
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char SEC10:3;
				unsigned char SEC1:4;
			} BIT;
		} RSECCP2;
	};
	char           wk31[1];
	union {
		unsigned char  BCNT1CP2;
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char MIN10:3;
				unsigned char MIN1:4;
			} BIT;
		} RMINCP2;
	};
	char           wk32[1];
	union {
		unsigned char  BCNT2CP2;
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char PM:1;
				unsigned char HR10:2;
				unsigned char HR1:4;
			} BIT;
		} RHRCP2;
	};
	char           wk33[3];
	union {
		unsigned char  BCNT3CP2;
		union {
			unsigned char BYTE;
			struct {
				unsigned char :2;
				unsigned char DATE10:2;
				unsigned char DATE1:4;
			} BIT;
		} RDAYCP2;
	};
	char           wk34[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char MON10:1;
			unsigned char MON1:4;
		} BIT;
	} RMONCP2;
};

struct st_s12ad {
	union {
		unsigned short WORD;
		struct {
			unsigned short ADST:1;
			unsigned short ADCS:2;
			unsigned short ADIE:1;
			unsigned short :1;
			unsigned short ADHSC:1;
			unsigned short TRGE:1;
			unsigned short EXTRG:1;
			unsigned short DBLE:1;
			unsigned short GBADIE:1;
			unsigned short :1;
			unsigned short DBLANS:5;
		} BIT;
	} ADCSR;
	char           wk0[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short ANSA007:1;
			unsigned short ANSA006:1;
			unsigned short ANSA005:1;
			unsigned short ANSA004:1;
			unsigned short ANSA003:1;
			unsigned short ANSA002:1;
			unsigned short ANSA001:1;
			unsigned short ANSA000:1;
		} BIT;
	} ADANSA0;
	union {
		unsigned short WORD;
		struct {
			unsigned short ANSA115:1;
			unsigned short ANSA114:1;
			unsigned short ANSA113:1;
			unsigned short ANSA112:1;
			unsigned short ANSA111:1;
			unsigned short ANSA110:1;
			unsigned short ANSA109:1;
			unsigned short ANSA108:1;
			unsigned short ANSA107:1;
			unsigned short ANSA106:1;
			unsigned short ANSA105:1;
			unsigned short ANSA104:1;
			unsigned short ANSA103:1;
			unsigned short ANSA102:1;
			unsigned short ANSA101:1;
			unsigned short ANSA100:1;
		} BIT;
	} ADANSA1;
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short ADS007:1;
			unsigned short ADS006:1;
			unsigned short ADS005:1;
			unsigned short ADS004:1;
			unsigned short ADS003:1;
			unsigned short ADS002:1;
			unsigned short ADS001:1;
			unsigned short ADS000:1;
		} BIT;
	} ADADS0;
	union {
		unsigned short WORD;
		struct {
			unsigned short ADS115:1;
			unsigned short ADS114:1;
			unsigned short ADS113:1;
			unsigned short ADS112:1;
			unsigned short ADS111:1;
			unsigned short ADS110:1;
			unsigned short ADS109:1;
			unsigned short ADS108:1;
			unsigned short ADS107:1;
			unsigned short ADS106:1;
			unsigned short ADS105:1;
			unsigned short ADS104:1;
			unsigned short ADS103:1;
			unsigned short ADS102:1;
			unsigned short ADS101:1;
			unsigned short ADS100:1;
		} BIT;
	} ADADS1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char AVEE:1;
			unsigned char :4;
			unsigned char ADC:3;
		} BIT;
	} ADADC;
	char           wk1[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short ADRFMT:1;
			unsigned short :3;
			unsigned short DIAGM:1;
			unsigned short DIAGLD:1;
			unsigned short DIAGVAL:2;
			unsigned short :2;
			unsigned short ACE:1;
			unsigned short :5;
		} BIT;
	} ADCER;
	union {
		unsigned short WORD;
		struct {
			unsigned short :2;
			unsigned short TRSA:6;
			unsigned short :2;
			unsigned short TRSB:6;
		} BIT;
	} ADSTRGR;
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short OCSA:1;
			unsigned short TSSA:1;
			unsigned short :6;
			unsigned short OCSAD:1;
			unsigned short TSSAD:1;
		} BIT;
	} ADEXICR;
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short ANSB007:1;
			unsigned short ANSB006:1;
			unsigned short ANSB005:1;
			unsigned short ANSB004:1;
			unsigned short ANSB003:1;
			unsigned short ANSB002:1;
			unsigned short ANSB001:1;
			unsigned short ANSB000:1;
		} BIT;
	} ADANSB0;
	union {
		unsigned short WORD;
		struct {
			unsigned short ANSB115:1;
			unsigned short ANSB114:1;
			unsigned short ANSB113:1;
			unsigned short ANSB112:1;
			unsigned short ANSB111:1;
			unsigned short ANSB110:1;
			unsigned short ANSB109:1;
			unsigned short ANSB108:1;
			unsigned short ANSB107:1;
			unsigned short ANSB106:1;
			unsigned short ANSB105:1;
			unsigned short ANSB104:1;
			unsigned short ANSB103:1;
			unsigned short ANSB102:1;
			unsigned short ANSB101:1;
			unsigned short ANSB100:1;
		} BIT;
	} ADANSB1;
	unsigned short ADDBLDR;
	unsigned short ADTSDR;
	unsigned short ADOCDR;
	union {
		unsigned short WORD;
		union {
			struct {
				unsigned short DIAGST:2;
				unsigned short :2;
				unsigned short AD:12;
			} RIGHT;
			struct {
				unsigned short AD:12;
				unsigned short :2;
				unsigned short DIAGST:2;
			} LEFT;
		} BIT;
	} ADRD;
	unsigned short ADDR0;
	unsigned short ADDR1;
	unsigned short ADDR2;
	unsigned short ADDR3;
	unsigned short ADDR4;
	unsigned short ADDR5;
	unsigned short ADDR6;
	unsigned short ADDR7;
	char           wk2[16];
	unsigned short ADDR16;
	unsigned short ADDR17;
	unsigned short ADDR18;
	unsigned short ADDR19;
	unsigned short ADDR20;
	unsigned short ADDR21;
	unsigned short ADDR22;
	unsigned short ADDR23;
	unsigned short ADDR24;
	unsigned short ADDR25;
	unsigned short ADDR26;
	unsigned short ADDR27;
	unsigned short ADDR28;
	unsigned short ADDR29;
	unsigned short ADDR30;
	unsigned short ADDR31;
	char           wk4[26];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char ADNDIS:5;
		} BIT;
	} ADDISCR;
	char           wk5[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char ELCC:2;
		} BIT;
	} ADELCCR;
	char           wk6[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short GBRP:1;
			unsigned short :13;
			unsigned short GBRSCN:1;
			unsigned short PGS:1;
		} BIT;
	} ADGSPCR;
	char           wk7[8];
	union {
		unsigned char BYTE;
		struct {
			unsigned char ADSLP:1;
			unsigned char :2;
			unsigned char LVSEL:1;
			unsigned char :2;
			unsigned char HVSEL:2;
		} BIT;
	} ADHVREFCNT;
	char           wk8[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char MONCMPB:1;
			unsigned char MONCMPA:1;
			unsigned char :3;
			unsigned char MONCOMB:1;
		} BIT;
	} ADWINMON;
	char           wk9[3];
	union {
		unsigned short WORD;
		struct {
			unsigned short :1;
			unsigned short WCMPE:1;
			unsigned short :2;
			unsigned short CMPAE:1;
			unsigned short :1;
			unsigned short CMPBE:1;
			unsigned short :7;
			unsigned short CMPAB:2;
		} BIT;
	} ADCMPCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char CMPOCA:1;
			unsigned char CMPTSA:1;
		} BIT;
	} ADCMPANSER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char CMPLOCA:1;
			unsigned char CMPLTSA:1;
		} BIT;
	} ADCMPLER;
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short CMPCHA007:1;
			unsigned short CMPCHA006:1;
			unsigned short CMPCHA005:1;
			unsigned short CMPCHA004:1;
			unsigned short CMPCHA003:1;
			unsigned short CMPCHA002:1;
			unsigned short CMPCHA001:1;
			unsigned short CMPCHA000:1;
		} BIT;
	} ADCMPANSR0;
	union {
		unsigned short WORD;
		struct {
			unsigned short CMPCHA115:1;
			unsigned short CMPCHA114:1;
			unsigned short CMPCHA113:1;
			unsigned short CMPCHA112:1;
			unsigned short CMPCHA111:1;
			unsigned short CMPCHA110:1;
			unsigned short CMPCHA109:1;
			unsigned short CMPCHA108:1;
			unsigned short CMPCHA107:1;
			unsigned short CMPCHA106:1;
			unsigned short CMPCHA105:1;
			unsigned short CMPCHA104:1;
			unsigned short CMPCHA103:1;
			unsigned short CMPCHA102:1;
			unsigned short CMPCHA101:1;
			unsigned short CMPCHA100:1;
		} BIT;
	} ADCMPANSR1;
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short CMPLCHA007:1;
			unsigned short CMPLCHA006:1;
			unsigned short CMPLCHA005:1;
			unsigned short CMPLCHA004:1;
			unsigned short CMPLCHA003:1;
			unsigned short CMPLCHA002:1;
			unsigned short CMPLCHA001:1;
			unsigned short CMPLCHA000:1;
		} BIT;
	} ADCMPLR0;
	union {
		unsigned short WORD;
		struct {
			unsigned short CMPLCHA115:1;
			unsigned short CMPLCHA114:1;
			unsigned short CMPLCHA113:1;
			unsigned short CMPLCHA112:1;
			unsigned short CMPLCHA111:1;
			unsigned short CMPLCHA110:1;
			unsigned short CMPLCHA109:1;
			unsigned short CMPLCHA108:1;
			unsigned short CMPLCHA107:1;
			unsigned short CMPLCHA106:1;
			unsigned short CMPLCHA105:1;
			unsigned short CMPLCHA104:1;
			unsigned short CMPLCHA103:1;
			unsigned short CMPLCHA102:1;
			unsigned short CMPLCHA101:1;
			unsigned short CMPLCHA100:1;
		} BIT;
	} ADCMPLR1;
	unsigned short ADCMPDR0;
	unsigned short ADCMPDR1;
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short CMPSTCHA007:1;
			unsigned short CMPSTCHA006:1;
			unsigned short CMPSTCHA005:1;
			unsigned short CMPSTCHA004:1;
			unsigned short CMPSTCHA003:1;
			unsigned short CMPSTCHA002:1;
			unsigned short CMPSTCHA001:1;
			unsigned short CMPSTCHA000:1;
		} BIT;
	} ADCMPSR0;
	union {
		unsigned short WORD;
		struct {
			unsigned short CMPSTCHA115:1;
			unsigned short CMPSTCHA114:1;
			unsigned short CMPSTCHA113:1;
			unsigned short CMPSTCHA112:1;
			unsigned short CMPSTCHA111:1;
			unsigned short CMPSTCHA110:1;
			unsigned short CMPSTCHA109:1;
			unsigned short CMPSTCHA108:1;
			unsigned short CMPSTCHA107:1;
			unsigned short CMPSTCHA106:1;
			unsigned short CMPSTCHA105:1;
			unsigned short CMPSTCHA104:1;
			unsigned short CMPSTCHA103:1;
			unsigned short CMPSTCHA102:1;
			unsigned short CMPSTCHA101:1;
			unsigned short CMPSTCHA100:1;
		} BIT;
	} ADCMPSR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char CMPSTOCA:1;
			unsigned char CMPSTTSA:1;
		} BIT;
	} ADCMPSER;
	char           wk10[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char CMPLB:1;
			unsigned char :1;
			unsigned char CMPCHB:6;
		} BIT;
	} ADCMPBNSR;
	char           wk11[1];
	unsigned short ADWINLLB;
	unsigned short ADWINULB;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char CMPSTB:1;
		} BIT;
	} ADCMPBSR;
	char           wk12[3];
	unsigned short ADBUF0;
	unsigned short ADBUF1;
	unsigned short ADBUF2;
	unsigned short ADBUF3;
	unsigned short ADBUF4;
	unsigned short ADBUF5;
	unsigned short ADBUF6;
	unsigned short ADBUF7;
	unsigned short ADBUF8;
	unsigned short ADBUF9;
	unsigned short ADBUF10;
	unsigned short ADBUF11;
	unsigned short ADBUF12;
	unsigned short ADBUF13;
	unsigned short ADBUF14;
	unsigned short ADBUF15;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char BUFEN:1;
		} BIT;
	} ADBUFEN;
	char           wk13[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PTROVF:1;
			unsigned char BUFPTR:4;
		} BIT;
	} ADBUFPTR;
	char           wk14[10];
	unsigned char  ADSSTRL;
	unsigned char  ADSSTRT;
	unsigned char  ADSSTRO;
	unsigned char  ADSSTR0;
	unsigned char  ADSSTR1;
	unsigned char  ADSSTR2;
	unsigned char  ADSSTR3;
	unsigned char  ADSSTR4;
	unsigned char  ADSSTR5;
	unsigned char  ADSSTR6;
	unsigned char  ADSSTR7;
};

struct st_sci0 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char CM:1;
			unsigned char CHR:1;
			unsigned char PE:1;
			unsigned char PM:1;
			unsigned char STOP:1;
			unsigned char MP:1;
			unsigned char CKS:2;
		} BIT;
	} SMR;
	unsigned char  BRR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TIE:1;
			unsigned char RIE:1;
			unsigned char TE:1;
			unsigned char RE:1;
			unsigned char MPIE:1;
			unsigned char TEIE:1;
			unsigned char CKE:2;
		} BIT;
	} SCR;
	unsigned char  TDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TDRE:1;
			unsigned char RDRF:1;
			unsigned char ORER:1;
			unsigned char FER:1;
			unsigned char PER:1;
			unsigned char TEND:1;
			unsigned char MPB:1;
			unsigned char MPBT:1;
		} BIT;
	} SSR;
	unsigned char  RDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCP2:1;
			unsigned char :2;
			unsigned char CHR1:1;
			unsigned char SDIR:1;
			unsigned char SINV:1;
			unsigned char :1;
			unsigned char SMIF:1;
		} BIT;
	} SCMR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char RXDESEL:1;
			unsigned char BGDM:1;
			unsigned char NFEN:1;
			unsigned char ABCS:1;
			unsigned char :1;
			unsigned char BRME:1;
			unsigned char :1;
			unsigned char ACS0:1;
		} BIT;
	} SEMR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char NFCS:3;
		} BIT;
	} SNFR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IICDL:5;
			unsigned char :2;
			unsigned char IICM:1;
		} BIT;
	} SIMR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char IICACKT:1;
			unsigned char :3;
			unsigned char IICCSC:1;
			unsigned char IICINTM:1;
		} BIT;
	} SIMR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IICSCLS:2;
			unsigned char IICSDAS:2;
			unsigned char IICSTIF:1;
			unsigned char IICSTPREQ:1;
			unsigned char IICRSTAREQ:1;
			unsigned char IICSTAREQ:1;
		} BIT;
	} SIMR3;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char IICACKR:1;
		} BIT;
	} SISR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CKPH:1;
			unsigned char CKPOL:1;
			unsigned char :1;
			unsigned char MFF:1;
			unsigned char :1;
			unsigned char MSS:1;
			unsigned char CTSE:1;
			unsigned char SSE:1;
		} BIT;
	} SPMR;
	union {
		unsigned short WORD;
		struct {
			unsigned char TDRH;
			unsigned char TDRL;
		} BYTE;
	} TDRHL;
	union {
		unsigned short WORD;
		struct {
			unsigned char RDRH;
			unsigned char RDRL;
		} BYTE;
	} RDRHL;
	unsigned char  MDDR;
};

struct st_sci12 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char CM:1;
			unsigned char CHR:1;
			unsigned char PE:1;
			unsigned char PM:1;
			unsigned char STOP:1;
			unsigned char MP:1;
			unsigned char CKS:2;
		} BIT;
	} SMR;
	unsigned char  BRR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TIE:1;
			unsigned char RIE:1;
			unsigned char TE:1;
			unsigned char RE:1;
			unsigned char MPIE:1;
			unsigned char TEIE:1;
			unsigned char CKE:2;
		} BIT;
	} SCR;
	unsigned char  TDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TDRE:1;
			unsigned char RDRF:1;
			unsigned char ORER:1;
			unsigned char FER:1;
			unsigned char PER:1;
			unsigned char TEND:1;
			unsigned char MPB:1;
			unsigned char MPBT:1;
		} BIT;
	} SSR;
	unsigned char  RDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCP2:1;
			unsigned char :2;
			unsigned char CHR1:1;
			unsigned char SDIR:1;
			unsigned char SINV:1;
			unsigned char :1;
			unsigned char SMIF:1;
		} BIT;
	} SCMR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char RXDESEL:1;
			unsigned char BGDM:1;
			unsigned char NFEN:1;
			unsigned char ABCS:1;
			unsigned char :1;
			unsigned char BRME:1;
			unsigned char :1;
			unsigned char ACS0:1;
		} BIT;
	} SEMR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char NFCS:3;
		} BIT;
	} SNFR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IICDL:5;
			unsigned char :2;
			unsigned char IICM:1;
		} BIT;
	} SIMR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char IICACKT:1;
			unsigned char :3;
			unsigned char IICCSC:1;
			unsigned char IICINTM:1;
		} BIT;
	} SIMR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IICSCLS:2;
			unsigned char IICSDAS:2;
			unsigned char IICSTIF:1;
			unsigned char IICSTPREQ:1;
			unsigned char IICRSTAREQ:1;
			unsigned char IICSTAREQ:1;
		} BIT;
	} SIMR3;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char IICACKR:1;
		} BIT;
	} SISR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CKPH:1;
			unsigned char CKPOL:1;
			unsigned char :1;
			unsigned char MFF:1;
			unsigned char :1;
			unsigned char MSS:1;
			unsigned char CTSE:1;
			unsigned char SSE:1;
		} BIT;
	} SPMR;
	union {
		unsigned short WORD;
		struct {
			unsigned char TDRH;
			unsigned char TDRL;
		} BYTE;
	} TDRHL;
	union {
		unsigned short WORD;
		struct {
			unsigned char RDRH;
			unsigned char RDRL;
		} BYTE;
	} RDRHL;
	unsigned char  MDDR;
	char           wk0[13];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char ESME:1;
		} BIT;
	} ESMER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char BRME:1;
			unsigned char RXDSF:1;
			unsigned char SFSF:1;
			unsigned char :1;
		} BIT;
	} CR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char PIBS:3;
			unsigned char PIBE:1;
			unsigned char CF1DS:2;
			unsigned char CF0RE:1;
			unsigned char BFE:1;
		} BIT;
	} CR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char RTS:2;
			unsigned char BCCS:2;
			unsigned char :1;
			unsigned char DFCS:3;
		} BIT;
	} CR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char SDST:1;
		} BIT;
	} CR3;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char SHARPS:1;
			unsigned char :2;
			unsigned char RXDXPS:1;
			unsigned char TXDXPS:1;
		} BIT;
	} PCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char AEDIE:1;
			unsigned char BCDIE:1;
			unsigned char PIBDIE:1;
			unsigned char CF1MIE:1;
			unsigned char CF0MIE:1;
			unsigned char BFDIE:1;
		} BIT;
	} ICR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char AEDF:1;
			unsigned char BCDF:1;
			unsigned char PIBDF:1;
			unsigned char CF1MF:1;
			unsigned char CF0MF:1;
			unsigned char BFDF:1;
		} BIT;
	} STR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char AEDCL:1;
			unsigned char BCDCL:1;
			unsigned char PIBDCL:1;
			unsigned char CF1MCL:1;
			unsigned char CF0MCL:1;
			unsigned char BFDCL:1;
		} BIT;
	} STCR;
	unsigned char  CF0DR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CF0CE7:1;
			unsigned char CF0CE6:1;
			unsigned char CF0CE5:1;
			unsigned char CF0CE4:1;
			unsigned char CF0CE3:1;
			unsigned char CF0CE2:1;
			unsigned char CF0CE1:1;
			unsigned char CF0CE0:1;
		} BIT;
	} CF0CR;
	unsigned char  CF0RR;
	unsigned char  PCF1DR;
	unsigned char  SCF1DR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CF1CE7:1;
			unsigned char CF1CE6:1;
			unsigned char CF1CE5:1;
			unsigned char CF1CE4:1;
			unsigned char CF1CE3:1;
			unsigned char CF1CE2:1;
			unsigned char CF1CE1:1;
			unsigned char CF1CE0:1;
		} BIT;
	} CF1CR;
	unsigned char  CF1RR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char TCST:1;
		} BIT;
	} TCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char TCSS:3;
			unsigned char TWRC:1;
			unsigned char :1;
			unsigned char TOMS:2;
		} BIT;
	} TMR;
	unsigned char  TPRE;
	unsigned char  TCNT;
};

struct st_sdhi {
	union {
		unsigned long LONG;
//		struct {
//			unsigned long :16;
//			unsigned long CMD12AT:2;
//			unsigned long TRSTP:1;
//			unsigned long CMDRW:1;
//			unsigned long CMDTP:1;
//			unsigned long RSPTP:3;
//			unsigned long ACMD:2;
//			unsigned long CMDIDX:6;
//		} BIT;
	} SDCMD;
	char           wk0[4];
	unsigned long  SDARG;
	char           wk1[4];
	union {
		unsigned long LONG;
		struct {
			unsigned long :23;
			unsigned long SDBLKCNTEN:1;
			unsigned long :7;
			unsigned long STP:1;
		} BIT;
	} SDSTOP;
	unsigned long  SDBLKCNT;
	unsigned long  SDRSP10;
	char           wk2[4];
	unsigned long  SDRSP32;
	char           wk3[4];
	unsigned long  SDRSP54;
	char           wk4[4];
	unsigned long  SDRSP76;
	char           wk5[4];
	union {
		unsigned long LONG;
//		struct {
//			unsigned long :21;
//			unsigned long SDD3MON:1;
//			unsigned long SDD3IN:1;
//			unsigned long SDD3RM:1;
//			unsigned long SDWPMON:1;
//			unsigned long :1;
//			unsigned long SDCDMON:1;
//			unsigned long SDCDIN:1;
//			unsigned long SDCDRM:1;
//			unsigned long ACEND:1;
//			unsigned long :1;
//			unsigned long RSPEND:1;
//		} BIT;
	} SDSTS1;
	union {
		unsigned long LONG;
//		struct {
//			unsigned long :16;
//			unsigned long ILA:1;
//			unsigned long CBSY:1;
//			unsigned long SDCLKCREN:1;
//			unsigned long :3;
//			unsigned long BWE:1;
//			unsigned long BRE:1;
//			unsigned long SDD0MON:1;
//			unsigned long RSPTO:1;
//			unsigned long ILR:1;
//			unsigned long ILW:1;
//			unsigned long DTO:1;
//			unsigned long ENDE:1;
//			unsigned long CRCE:1;
//			unsigned long CMDE:1;
//		} BIT;
	} SDSTS2;
	union {
		unsigned long LONG;
		struct {
			unsigned long :22;
			unsigned long SDD3INM:1;
			unsigned long SDD3RMM:1;
			unsigned long :3;
			unsigned long SDCDINM:1;
			unsigned long SDCDRMM:1;
			unsigned long ACENDM:1;
			unsigned long :1;
			unsigned long RSPENDM:1;
		} BIT;
	} SDIMSK1;
	union {
		unsigned long LONG;
		struct {
			unsigned long :16;
			unsigned long ILAM:1;
			unsigned long :5;
			unsigned long BWEM:1;
			unsigned long BREM:1;
			unsigned long :1;
			unsigned long RSPTOM:1;
			unsigned long ILRM:1;
			unsigned long ILWM:1;
			unsigned long DTTOM:1;
			unsigned long ENDEM:1;
			unsigned long CRCEM:1;
			unsigned long CMDEM:1;
		} BIT;
	} SDIMSK2;
	union {
		unsigned long LONG;
		struct {
			unsigned long :22;
			unsigned long CLKCTRLEN:1;
			unsigned long CLKEN:1;
			unsigned long CLKSEL:8;
		} BIT;
	} SDCLKCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :22;
			unsigned long LEN:10;
		} BIT;
	} SDSIZE;
	union {
		unsigned long LONG;
		struct {
			unsigned long :16;
			unsigned long WIDTH:1;
			unsigned long :7;
			unsigned long TOP:4;
			unsigned long CTOP:4;
		} BIT;
	} SDOPT;
	char           wk6[4];
	union {
		unsigned long LONG;
		struct {
			unsigned long :17;
			unsigned long CRCTK:3;
			unsigned long CRCTKE:1;
			unsigned long RDCRCE:1;
			unsigned long RSPCRCE1:1;
			unsigned long RSPCRCE0:1;
			unsigned long :2;
			unsigned long CRCLENE:1;
			unsigned long RDLENE:1;
			unsigned long RSPLENE1:1;
			unsigned long RSPLENE0:1;
			unsigned long CMDE1:1;
			unsigned long CMDE0:1;
		} BIT;
	} SDERSTS1;
	union {
		unsigned long LONG;
		struct {
			unsigned long :25;
			unsigned long CRCBSYTO:1;
			unsigned long CRCTO:1;
			unsigned long RDTO:1;
			unsigned long BSYTO1:1;
			unsigned long BSYTO0:1;
			unsigned long RSPTO1:1;
			unsigned long RSPTO0:1;
		} BIT;
	} SDERSTS2;
	unsigned long  SDBUFR;
	char           wk7[4];
	union {
		unsigned long LONG;
		struct {
			unsigned long :22;
			unsigned long C52PUB:1;
			unsigned long IOABT:1;
			unsigned long :5;
			unsigned long RWREQ:1;
			unsigned long :1;
			unsigned long INTEN:1;
		} BIT;
	} SDIOMD;
	union {
		unsigned long LONG;
//		struct {
//			unsigned long :16;
//			unsigned long EXWT:1;
//			unsigned long EXPUB52:1;
//			unsigned long :13;
//			unsigned long IOIRQ:1;
//		} BIT;
	} SDIOSTS;
	union {
		unsigned long LONG;
		struct {
			unsigned long :16;
			unsigned long EXWTM:1;
			unsigned long EXPUB52M:1;
			unsigned long :13;
			unsigned long IOIRQM:1;
		} BIT;
	} SDIOIMSK;
	char           wk8[316];
	union {
		unsigned long LONG;
		struct {
			unsigned long :30;
			unsigned long DMAEN:1;
			unsigned long :1;
		} BIT;
	} SDDMAEN;
	char           wk9[12];
	union {
		unsigned long LONG;
		struct {
			unsigned long :31;
			unsigned long SDRST:1;
		} BIT;
	} SDRST;
	char           wk10[28];
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long BRSWP:1;
			unsigned long BWSWP:1;
			unsigned long :6;
		} BIT;
	} SDSWAP;
};

struct st_smci {
	union {
		unsigned char BYTE;
		struct {
			unsigned char GM:1;
			unsigned char BLK:1;
			unsigned char PE:1;
			unsigned char PM:1;
			unsigned char BCP:2;
			unsigned char CKS:2;
		} BIT;
	} SMR;
	unsigned char  BRR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TIE:1;
			unsigned char RIE:1;
			unsigned char TE:1;
			unsigned char RE:1;
			unsigned char MPIE:1;
			unsigned char TEIE:1;
			unsigned char CKE:2;
		} BIT;
	} SCR;
	unsigned char  TDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TDRE:1;
			unsigned char RDRF:1;
			unsigned char ORER:1;
			unsigned char ERS:1;
			unsigned char PER:1;
			unsigned char TEND:1;
			unsigned char MPB:1;
			unsigned char MPBT:1;
		} BIT;
	} SSR;
	unsigned char  RDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCP2:1;
			unsigned char :2;
			unsigned char CHR1:1;
			unsigned char SDIR:1;
			unsigned char SINV:1;
			unsigned char :1;
			unsigned char SMIF:1;
		} BIT;
	} SCMR;
	char           wk0[7];
	union {
		unsigned short WORD;
		struct {
			unsigned char TDRH;
			unsigned char TDRL;
		} BYTE;
	} TDRHL;
	union {
		unsigned short WORD;
		struct {
			unsigned char RDRH;
			unsigned char RDRL;
		} BYTE;
	} RDRHL;
	unsigned char  MDDR;
};

struct st_ssi {
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long CKS:1;
			unsigned long TUIEN:1;
			unsigned long TOIEN:1;
			unsigned long RUIEN:1;
			unsigned long ROIEN:1;
			unsigned long IIEN:1;
			unsigned long :1;
			unsigned long CHNL:2;
			unsigned long DWL:3;
			unsigned long SWL:3;
			unsigned long SCKD:1;
			unsigned long SWSD:1;
			unsigned long SCKP:1;
			unsigned long SWSP:1;
			unsigned long SPDP:1;
			unsigned long SDTA:1;
			unsigned long PDTA:1;
			unsigned long DEL:1;
			unsigned long CKDV:4;
			unsigned long MUEN:1;
			unsigned long :1;
			unsigned long TEN:1;
			unsigned long REN:1;
		} BIT;
	} SSICR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :2;
			unsigned long TUIRQ:1;
			unsigned long TOIRQ:1;
			unsigned long RUIRQ:1;
			unsigned long ROIRQ:1;
			unsigned long IIRQ:1;
			unsigned long :18;
			unsigned long TCHNO:2;
			unsigned long TSWNO:1;
			unsigned long RCHNO:2;
			unsigned long RSWNO:1;
			unsigned long IDST:1;
		} BIT;
	} SSISR;
	char           wk0[8];
	union {
		unsigned long LONG;
		struct {
			unsigned long AUCKE:1;
			unsigned long :14;
			unsigned long SSIRST:1;
			unsigned long :8;
			unsigned long TTRG:2;
			unsigned long RTRG:2;
			unsigned long TIE:1;
			unsigned long RIE:1;
			unsigned long TFRST:1;
			unsigned long RFRST:1;
		} BIT;
	} SSIFCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :4;
			unsigned long TDC:4;
			unsigned long :7;
			unsigned long TDE:1;
			unsigned long :4;
			unsigned long RDC:4;
			unsigned long :7;
			unsigned long RDF:1;
		} BIT;
	} SSIFSR;
	unsigned long  SSIFTDR;
	unsigned long  SSIFRDR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :23;
			unsigned long CONT:1;
			unsigned long :8;
		} BIT;
	} SSITDMR;
};

struct st_system {
	union {
		unsigned short WORD;
		struct {
			unsigned short :15;
			unsigned short MD:1;
		} BIT;
	} MDMONR;
	char           wk0[4];
	union {
		unsigned short WORD;
		struct {
			unsigned short KEY:8;
			unsigned short :6;
			unsigned short EXBE:1;
			unsigned short ROME:1;
		} BIT;
	} SYSCR0;
	union {
		unsigned short WORD;
		struct {
			unsigned short :15;
			unsigned short RAME:1;
		} BIT;
	} SYSCR1;
	char           wk1[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short SSBY:1;
			unsigned short OPE:1;
			unsigned short :14;
		} BIT;
	} SBYCR;
	char           wk2[2];
	union {
		unsigned long LONG;
		struct {
			unsigned long :3;
			unsigned long MSTPA28:1;
			unsigned long :8;
			unsigned long MSTPA19:1;
			unsigned long :1;
			unsigned long MSTPA17:1;
			unsigned long :1;
			unsigned long MSTPA15:1;
			unsigned long MSTPA14:1;
			unsigned long MSTPA13:1;
			unsigned long :3;
			unsigned long MSTPA9:1;
			unsigned long :3;
			unsigned long MSTPA5:1;
			unsigned long MSTPA4:1;
			unsigned long :4;
		} BIT;
	} MSTPCRA;
	union {
		unsigned long LONG;
		struct {
			unsigned long MSTPB31:1;
			unsigned long MSTPB30:1;
			unsigned long :3;
			unsigned long MSTPB26:1;
			unsigned long MSTPB25:1;
			unsigned long :1;
			unsigned long MSTPB23:1;
			unsigned long :1;
			unsigned long MSTPB21:1;
			unsigned long :1;
			unsigned long MSTPB19:1;
			unsigned long :1;
			unsigned long MSTPB17:1;
			unsigned long :6;
			unsigned long MSTPB10:1;
			unsigned long MSTPB9:1;
			unsigned long :2;
			unsigned long MSTPB6:1;
			unsigned long :1;
			unsigned long MSTPB4:1;
			unsigned long :3;
			unsigned long MSTPB0:1;
		} BIT;
	} MSTPCRB;
	union {
		unsigned long LONG;
		struct {
			unsigned long DSLPE:1;
			unsigned long MSTPC30:1;
			unsigned long MSTPC29:1;
			unsigned long MSTPC28:1;
			unsigned long MSTPC27:1;
			unsigned long MSTPC26:1;
			unsigned long :5;
			unsigned long MSTPC20:1;
			unsigned long MSTPC19:1;
			unsigned long :17;
			unsigned long :1;
			unsigned long MSTPC0:1;
		} BIT;
	} MSTPCRC;
	union {
		unsigned long LONG;
		struct {
			unsigned long MSTPD31:1;
			unsigned long :11;
			unsigned long MSTPD19:1;
			unsigned long :3;
			unsigned long MSTPD15:1;
			unsigned long :4;
			unsigned long MSTPD10:1;
			unsigned long :10;
		} BIT;
	} MSTPCRD;
	union {
		unsigned long LONG;
		struct {
			unsigned long FCK:4;
			unsigned long ICK:4;
			unsigned long PSTOP1:1;
			unsigned long :3;
			unsigned long BCK:4;
			unsigned long PCKA:4;
			unsigned long PCKB:4;
			unsigned long :4;
			unsigned long PCKD:4;
		} BIT;
	} SCKCR;
	char           wk3[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short :5;
			unsigned short CKSEL:3;
			unsigned short :8;
		} BIT;
	} SCKCR3;
	union {
		unsigned short WORD;
		struct {
			unsigned short :2;
			unsigned short STC:6;
			unsigned short :6;
			unsigned short PLIDIV:2;
		} BIT;
	} PLLCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char PLLEN:1;
		} BIT;
	} PLLCR2;
	char           wk4[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short :2;
			unsigned short USTC:6;
			unsigned short :3;
			unsigned short UCKUPLLSEL:1;
			unsigned short :2;
			unsigned short UPLIDIV:2;
		} BIT;
	} UPLLCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char UPLLEN:1;
		} BIT;
	} UPLLCR2;
	char           wk5[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char BCLKDIV:1;
		} BIT;
	} BCKCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char MEMWAIT:1;
		} BIT;
	} MEMWAIT;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char MOSTP:1;
		} BIT;
	} MOSCCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char SOSTP:1;
		} BIT;
	} SOSCCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char LCSTP:1;
		} BIT;
	} LOCOCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char ILCSTP:1;
		} BIT;
	} ILOCOCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char HCSTP:1;
		} BIT;
	} HOCOCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char HCFRQ:2;
		} BIT;
	} HOCOCR2;
	char           wk6[4];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char UPLOVF:1;
			unsigned char :1;
			unsigned char HCOVF:1;
			unsigned char PLOVF:1;
			unsigned char :1;
			unsigned char MOOVF:1;
		} BIT;
	} OSCOVFSR;
	char           wk7[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short CKOSTP:1;
			unsigned short CKODIV:3;
			unsigned short CKOSEL:4;
			unsigned short :8;
		} BIT;
	} CKOCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char OSTDE:1;
			unsigned char :6;
			unsigned char OSTDIE:1;
		} BIT;
	} OSTDCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char OSTDF:1;
		} BIT;
	} OSTDSR;
	char           wk8[30];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char LOCOTRD:5;
		} BIT;
	} LOCOTRR;
	char           wk9[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char ILOCOTRD:5;
		} BIT;
	} ILOCOTRR;
	char           wk10[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char HOCOTRD:6;
		} BIT;
	} HOCOTRR0;
	char           wk11[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char HOCOTRD:6;
		} BIT;
	} HOCOTRR3;
	char           wk12[52];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char OPCMTSF:1;
			unsigned char :1;
			unsigned char OPCM:3;
		} BIT;
	} OPCCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char RSTCKEN:1;
			unsigned char :4;
			unsigned char RSTCKSEL:3;
		} BIT;
	} RSTCKCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char MSTS:5;
		} BIT;
	} MOSCWTCR;
	char           wk13[7];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char SOPCMTSF:1;
			unsigned char :3;
			unsigned char SOPCM:1;
		} BIT;
	} SOPCCR;
	char           wk14[21];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char SWRF:1;
			unsigned char WDTRF:1;
			unsigned char IWDTRF:1;
		} BIT;
	} RSTSR2;
	char           wk15[1];
	unsigned short SWRR;
	char           wk16[28];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char LVD1IRQSEL:1;
			unsigned char LVD1IDTSEL:2;
		} BIT;
	} LVD1CR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char LVD1MON:1;
			unsigned char LVD1DET:1;
		} BIT;
	} LVD1SR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char LVD2IRQSEL:1;
			unsigned char LVD2IDTSEL:2;
		} BIT;
	} LVD2CR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char LVD2MON:1;
			unsigned char LVD2DET:1;
		} BIT;
	} LVD2SR;
	char           wk17[794];
	union {
		unsigned short WORD;
		struct {
			unsigned short PRKEY:8;
			unsigned short :4;
			unsigned short PRC3:1;
			unsigned short PRC2:1;
			unsigned short PRC1:1;
			unsigned short PRC0:1;
		} BIT;
	} PRCR;
	char           wk18[48784];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char LVD2RF:1;
			unsigned char LVD1RF:1;
			unsigned char LVD0RF:1;
			unsigned char PORF:1;
		} BIT;
	} RSTSR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char CWSF:1;
		} BIT;
	} RSTSR1;
	char           wk19[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char MOSEL:1;
			unsigned char MODRV21:1;
			unsigned char :5;
		} BIT;
	} MOFCR;
	char           wk20[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char LVD2E:1;
			unsigned char LVD1E:1;
			unsigned char :1;
			unsigned char EXVCCINP2:1;
			unsigned char :3;
		} BIT;
	} LVCMPCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char LVD2LVL:2;
			unsigned char LVD1LVL:4;
		} BIT;
	} LVDLVLR;
	char           wk21[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char LVD1RN:1;
			unsigned char LVD1RI:1;
			unsigned char :3;
			unsigned char LVD1CMPE:1;
			unsigned char :1;
			unsigned char LVD1RIE:1;
		} BIT;
	} LVD1CR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char LVD2RN:1;
			unsigned char LVD2RI:1;
			unsigned char :3;
			unsigned char LVD2CMPE:1;
			unsigned char :1;
			unsigned char LVD2RIE:1;
		} BIT;
	} LVD2CR0;
	char           wk22[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char VBTLVDLVL:2;
			unsigned char :1;
			unsigned char VBTLVDEN:1;
			unsigned char :3;
			unsigned char VBATTDIS:1;
		} BIT;
	} VBATTCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char VBTLVDMON:1;
			unsigned char VBATRLVDETF:1;
		} BIT;
	} VBATTSR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char VBTLVDISEL:1;
			unsigned char VBTLVDIE:1;
		} BIT;
	} VBTLVDICR;
};

struct st_tempsconst {
	unsigned char  TSCDRL;
	unsigned char  TSCDRH;
};

struct st_tmr0 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char CMIEB:1;
			unsigned char CMIEA:1;
			unsigned char OVIE:1;
			unsigned char CCLR:2;
			unsigned char :3;
		} BIT;
	} TCR;
	char           wk0[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char OSB:2;
			unsigned char OSA:2;
		} BIT;
	} TCSR;
	char           wk1[1];
	unsigned char  TCORA;
	char           wk2[1];
	unsigned char  TCORB;
	char           wk3[1];
	unsigned char  TCNT;
	char           wk4[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TMRIS:1;
			unsigned char :2;
			unsigned char CSS:2;
			unsigned char CKS:3;
		} BIT;
	} TCCR;
	char           wk5[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char TCS:1;
		} BIT;
	} TCSTR;
};

struct st_tmr1 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char CMIEB:1;
			unsigned char CMIEA:1;
			unsigned char OVIE:1;
			unsigned char CCLR:2;
			unsigned char :3;
		} BIT;
	} TCR;
	char           wk0[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char OSB:2;
			unsigned char OSA:2;
		} BIT;
	} TCSR;
	char           wk1[1];
	unsigned char  TCORA;
	char           wk2[1];
	unsigned char  TCORB;
	char           wk3[1];
	unsigned char  TCNT;
	char           wk4[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TMRIS:1;
			unsigned char :2;
			unsigned char CSS:2;
			unsigned char CKS:3;
		} BIT;
	} TCCR;
};

struct st_tmr01 {
	unsigned short TCORA;
	unsigned short TCORB;
	unsigned short TCNT;
	unsigned short TCCR;
};

struct st_tpu {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char CST5:1;
			unsigned char CST4:1;
			unsigned char CST3:1;
			unsigned char CST2:1;
			unsigned char CST1:1;
			unsigned char CST0:1;
		} BIT;
	} TSTR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char SYNC5:1;
			unsigned char SYNC4:1;
			unsigned char SYNC3:1;
			unsigned char SYNC2:1;
			unsigned char SYNC1:1;
			unsigned char SYNC0:1;
		} BIT;
	} TSYR;
};

struct st_tpu0 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char NFCS:2;
			unsigned char NFDEN:1;
			unsigned char NFCEN:1;
			unsigned char NFBEN:1;
			unsigned char NFAEN:1;
		} BIT;
	} NFCR;
	char           wk0[7];
	union {
		unsigned char BYTE;
		struct {
			unsigned char CCLR:3;
			unsigned char CKEG:2;
			unsigned char TPSC:3;
		} BIT;
	} TCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ICSELD:1;
			unsigned char ICSELB:1;
			unsigned char BFB:1;
			unsigned char BFA:1;
			unsigned char MD:4;
		} BIT;
	} TMDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IOB:4;
			unsigned char IOA:4;
		} BIT;
	} TIORH;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IOD:4;
			unsigned char IOC:4;
		} BIT;
	} TIORL;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TTGE:1;
			unsigned char :1;
			unsigned char TCIEU:1;
			unsigned char TCIEV:1;
			unsigned char TGIED:1;
			unsigned char TGIEC:1;
			unsigned char TGIEB:1;
			unsigned char TGIEA:1;
		} BIT;
	} TIER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCFD:1;
			unsigned char :1;
			unsigned char TCFU:1;
			unsigned char TCFV:1;
			unsigned char TGFD:1;
			unsigned char TGFC:1;
			unsigned char TGFB:1;
			unsigned char TGFA:1;
		} BIT;
	} TSR;
	unsigned short TCNT;
	unsigned short TGRA;
	unsigned short TGRB;
	unsigned short TGRC;
	unsigned short TGRD;
};

struct st_tpu1 {
	char           wk0[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char NFCS:2;
			unsigned char NFDEN:1;
			unsigned char NFCEN:1;
			unsigned char NFBEN:1;
			unsigned char NFAEN:1;
		} BIT;
	} NFCR;
	char           wk1[22];
	union {
		unsigned char BYTE;
		struct {
			unsigned char CCLR:3;
			unsigned char CKEG:2;
			unsigned char TPSC:3;
		} BIT;
	} TCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ICSELD:1;
			unsigned char ICSELB:1;
			unsigned char BFB:1;
			unsigned char BFA:1;
			unsigned char MD:4;
		} BIT;
	} TMDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IOB:4;
			unsigned char IOA:4;
		} BIT;
	} TIOR;
	char           wk2[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TTGE:1;
			unsigned char :1;
			unsigned char TCIEU:1;
			unsigned char TCIEV:1;
			unsigned char TGIED:1;
			unsigned char TGIEC:1;
			unsigned char TGIEB:1;
			unsigned char TGIEA:1;
		} BIT;
	} TIER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCFD:1;
			unsigned char :1;
			unsigned char TCFU:1;
			unsigned char TCFV:1;
			unsigned char TGFD:1;
			unsigned char TGFC:1;
			unsigned char TGFB:1;
			unsigned char TGFA:1;
		} BIT;
	} TSR;
	unsigned short TCNT;
	unsigned short TGRA;
	unsigned short TGRB;
};

struct st_tpu2 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char NFCS:2;
			unsigned char NFDEN:1;
			unsigned char NFCEN:1;
			unsigned char NFBEN:1;
			unsigned char NFAEN:1;
		} BIT;
	} NFCR;
	char           wk0[37];
	union {
		unsigned char BYTE;
		struct {
			unsigned char CCLR:3;
			unsigned char CKEG:2;
			unsigned char TPSC:3;
		} BIT;
	} TCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ICSELD:1;
			unsigned char ICSELB:1;
			unsigned char BFB:1;
			unsigned char BFA:1;
			unsigned char MD:4;
		} BIT;
	} TMDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IOB:4;
			unsigned char IOA:4;
		} BIT;
	} TIOR;
	char           wk1[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TTGE:1;
			unsigned char :1;
			unsigned char TCIEU:1;
			unsigned char TCIEV:1;
			unsigned char TGIED:1;
			unsigned char TGIEC:1;
			unsigned char TGIEB:1;
			unsigned char TGIEA:1;
		} BIT;
	} TIER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCFD:1;
			unsigned char :1;
			unsigned char TCFU:1;
			unsigned char TCFV:1;
			unsigned char TGFD:1;
			unsigned char TGFC:1;
			unsigned char TGFB:1;
			unsigned char TGFA:1;
		} BIT;
	} TSR;
	unsigned short TCNT;
	unsigned short TGRA;
	unsigned short TGRB;
};

struct st_tpu3 {
	char           wk0[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char NFCS:2;
			unsigned char NFDEN:1;
			unsigned char NFCEN:1;
			unsigned char NFBEN:1;
			unsigned char NFAEN:1;
		} BIT;
	} NFCR;
	char           wk1[52];
	union {
		unsigned char BYTE;
		struct {
			unsigned char CCLR:3;
			unsigned char CKEG:2;
			unsigned char TPSC:3;
		} BIT;
	} TCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ICSELD:1;
			unsigned char ICSELB:1;
			unsigned char BFB:1;
			unsigned char BFA:1;
			unsigned char MD:4;
		} BIT;
	} TMDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IOB:4;
			unsigned char IOA:4;
		} BIT;
	} TIORH;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IOD:4;
			unsigned char IOC:4;
		} BIT;
	} TIORL;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TTGE:1;
			unsigned char :1;
			unsigned char TCIEU:1;
			unsigned char TCIEV:1;
			unsigned char TGIED:1;
			unsigned char TGIEC:1;
			unsigned char TGIEB:1;
			unsigned char TGIEA:1;
		} BIT;
	} TIER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCFD:1;
			unsigned char :1;
			unsigned char TCFU:1;
			unsigned char TCFV:1;
			unsigned char TGFD:1;
			unsigned char TGFC:1;
			unsigned char TGFB:1;
			unsigned char TGFA:1;
		} BIT;
	} TSR;
	unsigned short TCNT;
	unsigned short TGRA;
	unsigned short TGRB;
	unsigned short TGRC;
	unsigned short TGRD;
};

struct st_tpu4 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char NFCS:2;
			unsigned char NFDEN:1;
			unsigned char NFCEN:1;
			unsigned char NFBEN:1;
			unsigned char NFAEN:1;
		} BIT;
	} NFCR;
	char           wk0[67];
	union {
		unsigned char BYTE;
		struct {
			unsigned char CCLR:3;
			unsigned char CKEG:2;
			unsigned char TPSC:3;
		} BIT;
	} TCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ICSELD:1;
			unsigned char ICSELB:1;
			unsigned char BFB:1;
			unsigned char BFA:1;
			unsigned char MD:4;
		} BIT;
	} TMDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IOB:4;
			unsigned char IOA:4;
		} BIT;
	} TIOR;
	char           wk1[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TTGE:1;
			unsigned char :1;
			unsigned char TCIEU:1;
			unsigned char TCIEV:1;
			unsigned char TGIED:1;
			unsigned char TGIEC:1;
			unsigned char TGIEB:1;
			unsigned char TGIEA:1;
		} BIT;
	} TIER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCFD:1;
			unsigned char :1;
			unsigned char TCFU:1;
			unsigned char TCFV:1;
			unsigned char TGFD:1;
			unsigned char TGFC:1;
			unsigned char TGFB:1;
			unsigned char TGFA:1;
		} BIT;
	} TSR;
	unsigned short TCNT;
	unsigned short TGRA;
	unsigned short TGRB;
};

struct st_tpu5 {
	char           wk0[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char NFCS:2;
			unsigned char NFDEN:1;
			unsigned char NFCEN:1;
			unsigned char NFBEN:1;
			unsigned char NFAEN:1;
		} BIT;
	} NFCR;
	char           wk1[82];
	union {
		unsigned char BYTE;
		struct {
			unsigned char CCLR:3;
			unsigned char CKEG:2;
			unsigned char TPSC:3;
		} BIT;
	} TCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ICSELD:1;
			unsigned char ICSELB:1;
			unsigned char BFB:1;
			unsigned char BFA:1;
			unsigned char MD:4;
		} BIT;
	} TMDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IOB:4;
			unsigned char IOA:4;
		} BIT;
	} TIOR;
	char           wk2[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TTGE:1;
			unsigned char :1;
			unsigned char TCIEU:1;
			unsigned char TCIEV:1;
			unsigned char TGIED:1;
			unsigned char TGIEC:1;
			unsigned char TGIEB:1;
			unsigned char TGIEA:1;
		} BIT;
	} TIER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCFD:1;
			unsigned char :1;
			unsigned char TCFU:1;
			unsigned char TCFV:1;
			unsigned char TGFD:1;
			unsigned char TGFC:1;
			unsigned char TGFB:1;
			unsigned char TGFA:1;
		} BIT;
	} TSR;
	unsigned short TCNT;
	unsigned short TGRA;
	unsigned short TGRB;
};

struct st_usb0 {
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :5;
//			unsigned short SCKE:1;
//			unsigned short :1;
//			unsigned short CNEN:1;
//			unsigned short :1;
//			unsigned short DCFM:1;
//			unsigned short DRPD:1;
//			unsigned short DPRPU:1;
//			unsigned short DMRPU:1;
//			unsigned short :2;
//			unsigned short USBE:1;
//		} BIT;
	} SYSCFG;
	char           wk0[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short OVCMON:2;
			unsigned short :7;
			unsigned short HTACT:1;
			unsigned short :3;
			unsigned short IDMON:1;
			unsigned short LNST:2;
		} BIT;
	} SYSSTS0;
	char           wk1[2];
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :4;
//			unsigned short HNPBTOA:1;
//			unsigned short EXICEN:1;
//			unsigned short VBUSEN:1;
//			unsigned short WKUP:1;
//			unsigned short RWUPE:1;
//			unsigned short USBRST:1;
//			unsigned short RESUME:1;
//			unsigned short UACT:1;
//			unsigned short :1;
//			unsigned short RHST:3;
//		} BIT;
	} DVSTCTR0;
	char           wk2[10];
	union {
		unsigned short WORD;
		struct {
			unsigned char L;
			unsigned char H;
		} BYTE;
	} CFIFO;
	char           wk3[2];
	union {
		unsigned short WORD;
		struct {
			unsigned char L;
			unsigned char H;
		} BYTE;
	} D0FIFO;
	char           wk4[2];
	union {
		unsigned short WORD;
		struct {
			unsigned char L;
			unsigned char H;
		} BYTE;
	} D1FIFO;
	char           wk5[2];
	union {
		unsigned short WORD;
//		struct {
//			unsigned short RCNT:1;
//			unsigned short REW:1;
//			unsigned short :3;
//			unsigned short MBW:1;
//			unsigned short :1;
//			unsigned short BIGEND:1;
//			unsigned short :2;
//			unsigned short ISEL:1;
//			unsigned short :1;
//			unsigned short CURPIPE:4;
//		} BIT;
	} CFIFOSEL;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short BVAL:1;
//			unsigned short BCLR:1;
//			unsigned short FRDY:1;
//			unsigned short :4;
//			unsigned short DTLN:9;
//		} BIT;
	} CFIFOCTR;
	char           wk6[4];
	union {
		unsigned short WORD;
//		struct {
//			unsigned short RCNT:1;
//			unsigned short REW:1;
//			unsigned short DCLRM:1;
//			unsigned short DREQE:1;
//			unsigned short :1;
//			unsigned short MBW:1;
//			unsigned short :1;
//			unsigned short BIGEND:1;
//			unsigned short :4;
//			unsigned short CURPIPE:4;
//		} BIT;
	} D0FIFOSEL;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short BVAL:1;
//			unsigned short BCLR:1;
//			unsigned short FRDY:1;
//			unsigned short :4;
//			unsigned short DTLN:9;
//		} BIT;
	} D0FIFOCTR;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short RCNT:1;
//			unsigned short REW:1;
//			unsigned short DCLRM:1;
//			unsigned short DREQE:1;
//			unsigned short :1;
//			unsigned short MBW:1;
//			unsigned short :1;
//			unsigned short BIGEND:1;
//			unsigned short :4;
//			unsigned short CURPIPE:4;
//		} BIT;
	} D1FIFOSEL;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short BVAL:1;
//			unsigned short BCLR:1;
//			unsigned short FRDY:1;
//			unsigned short :4;
//			unsigned short DTLN:9;
//		} BIT;
	} D1FIFOCTR;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short VBSE:1;
//			unsigned short RSME:1;
//			unsigned short SOFE:1;
//			unsigned short DVSE:1;
//			unsigned short CTRE:1;
//			unsigned short BEMPE:1;
//			unsigned short NRDYE:1;
//			unsigned short BRDYE:1;
//			unsigned short :8;
//		} BIT;
	} INTENB0;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short OVRCRE:1;
//			unsigned short BCHGE:1;
//			unsigned short :1;
//			unsigned short DTCHE:1;
//			unsigned short ATTCHE:1;
//			unsigned short :4;
//			unsigned short EOFERRE:1;
//			unsigned short SIGNE:1;
//			unsigned short SACKE:1;
//			unsigned short :3;
//			unsigned short PDDETINTE0:1;
//		} BIT;
	} INTENB1;
	char           wk7[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short PIPE9BRDYE:1;
			unsigned short PIPE8BRDYE:1;
			unsigned short PIPE7BRDYE:1;
			unsigned short PIPE6BRDYE:1;
			unsigned short PIPE5BRDYE:1;
			unsigned short PIPE4BRDYE:1;
			unsigned short PIPE3BRDYE:1;
			unsigned short PIPE2BRDYE:1;
			unsigned short PIPE1BRDYE:1;
			unsigned short PIPE0BRDYE:1;
		} BIT;
	} BRDYENB;
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short PIPE9NRDYE:1;
			unsigned short PIPE8NRDYE:1;
			unsigned short PIPE7NRDYE:1;
			unsigned short PIPE6NRDYE:1;
			unsigned short PIPE5NRDYE:1;
			unsigned short PIPE4NRDYE:1;
			unsigned short PIPE3NRDYE:1;
			unsigned short PIPE2NRDYE:1;
			unsigned short PIPE1NRDYE:1;
			unsigned short PIPE0NRDYE:1;
		} BIT;
	} NRDYENB;
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short PIPE9BEMPE:1;
			unsigned short PIPE8BEMPE:1;
			unsigned short PIPE7BEMPE:1;
			unsigned short PIPE6BEMPE:1;
			unsigned short PIPE5BEMPE:1;
			unsigned short PIPE4BEMPE:1;
			unsigned short PIPE3BEMPE:1;
			unsigned short PIPE2BEMPE:1;
			unsigned short PIPE1BEMPE:1;
			unsigned short PIPE0BEMPE:1;
		} BIT;
	} BEMPENB;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :7;
//			unsigned short TRNENSEL:1;
//			unsigned short :1;
//			unsigned short BRDYM:1;
//			unsigned short :1;
//			unsigned short EDGESTS:1;
//			unsigned short :4;
//		} BIT;
	} SOFCFG;
	char           wk8[2];
	union {
		unsigned short WORD;
//		struct {
//			unsigned short VBINT:1;
//			unsigned short RESM:1;
//			unsigned short SOFR:1;
//			unsigned short DVST:1;
//			unsigned short CTRT:1;
//			unsigned short BEMP:1;
//			unsigned short NRDY:1;
//			unsigned short BRDY:1;
//			unsigned short VBSTS:1;
//			unsigned short DVSQ:3;
//			unsigned short VALID:1;
//			unsigned short CTSQ:3;
//		} BIT;
	} INTSTS0;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short OVRCR:1;
//			unsigned short BCHG:1;
//			unsigned short :1;
//			unsigned short DTCH:1;
//			unsigned short ATTCH:1;
//			unsigned short :4;
//			unsigned short EOFERR:1;
//			unsigned short SIGN:1;
//			unsigned short SACK:1;
//			unsigned short :3;
//			unsigned short PDDETINT0:1;
//		} BIT;
	} INTSTS1;
	char           wk9[2];
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :6;
//			unsigned short PIPE9BRDY:1;
//			unsigned short PIPE8BRDY:1;
//			unsigned short PIPE7BRDY:1;
//			unsigned short PIPE6BRDY:1;
//			unsigned short PIPE5BRDY:1;
//			unsigned short PIPE4BRDY:1;
//			unsigned short PIPE3BRDY:1;
//			unsigned short PIPE2BRDY:1;
//			unsigned short PIPE1BRDY:1;
//			unsigned short PIPE0BRDY:1;
//		} BIT;
	} BRDYSTS;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :6;
//			unsigned short PIPE9NRDY:1;
//			unsigned short PIPE8NRDY:1;
//			unsigned short PIPE7NRDY:1;
//			unsigned short PIPE6NRDY:1;
//			unsigned short PIPE5NRDY:1;
//			unsigned short PIPE4NRDY:1;
//			unsigned short PIPE3NRDY:1;
//			unsigned short PIPE2NRDY:1;
//			unsigned short PIPE1NRDY:1;
//			unsigned short PIPE0NRDY:1;
//		} BIT;
	} NRDYSTS;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :6;
//			unsigned short PIPE9BEMP:1;
//			unsigned short PIPE8BEMP:1;
//			unsigned short PIPE7BEMP:1;
//			unsigned short PIPE6BEMP:1;
//			unsigned short PIPE5BEMP:1;
//			unsigned short PIPE4BEMP:1;
//			unsigned short PIPE3BEMP:1;
//			unsigned short PIPE2BEMP:1;
//			unsigned short PIPE1BEMP:1;
//			unsigned short PIPE0BEMP:1;
//		} BIT;
	} BEMPSTS;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short OVRN:1;
//			unsigned short CRCE:1;
//			unsigned short :3;
//			unsigned short FRNM:11;
//		} BIT;
	} FRMNUM;
	char           wk10[6];
	union {
		unsigned short WORD;
		struct {
			unsigned short BREQUEST:8;
			unsigned short BMREQUESTTYPE:8;
		} BIT;
	} USBREQ;
	unsigned short USBVAL;
	unsigned short USBINDX;
	unsigned short USBLENG;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :8;
//			unsigned short SHTNAK:1;
//			unsigned short :2;
//			unsigned short DIR:1;
//			unsigned short :4;
//		} BIT;
	} DCPCFG;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short DEVSEL:4;
//			unsigned short :5;
//			unsigned short MXPS:7;
//		} BIT;
	} DCPMAXP;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short BSTS:1;
//			unsigned short SUREQ:1;
//			unsigned short :2;
//			unsigned short SUREQCLR:1;
//			unsigned short :2;
//			unsigned short SQCLR:1;
//			unsigned short SQSET:1;
//			unsigned short SQMON:1;
//			unsigned short PBUSY:1;
//			unsigned short :2;
//			unsigned short CCPL:1;
//			unsigned short PID:2;
//		} BIT;
	} DCPCTR;
	char           wk11[2];
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :12;
//			unsigned short PIPESEL:4;
//		} BIT;
	} PIPESEL;
	char           wk12[2];
	union {
		unsigned short WORD;
//		struct {
//			unsigned short TYPE:2;
//			unsigned short :3;
//			unsigned short BFRE:1;
//			unsigned short DBLB:1;
//			unsigned short :1;
//			unsigned short SHTNAK:1;
//			unsigned short :2;
//			unsigned short DIR:1;
//			unsigned short EPNUM:4;
//		} BIT;
	} PIPECFG;
	char           wk13[2];
	union {
		unsigned short WORD;
//		struct {
//			unsigned short DEVSEL:4;
//			unsigned short :3;
//			unsigned short MXPS:9;
//		} BIT;
	} PIPEMAXP;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :3;
//			unsigned short IFIS:1;
//			unsigned short :9;
//			unsigned short IITV:3;
//		} BIT;
	} PIPEPERI;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short BSTS:1;
//			unsigned short INBUFM:1;
//			unsigned short :3;
//			unsigned short ATREPM:1;
//			unsigned short ACLRM:1;
//			unsigned short SQCLR:1;
//			unsigned short SQSET:1;
//			unsigned short SQMON:1;
//			unsigned short PBUSY:1;
//			unsigned short :3;
//			unsigned short PID:2;
//		} BIT;
	} PIPE1CTR;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short BSTS:1;
//			unsigned short INBUFM:1;
//			unsigned short :3;
//			unsigned short ATREPM:1;
//			unsigned short ACLRM:1;
//			unsigned short SQCLR:1;
//			unsigned short SQSET:1;
//			unsigned short SQMON:1;
//			unsigned short PBUSY:1;
//			unsigned short :3;
//			unsigned short PID:2;
//		} BIT;
	} PIPE2CTR;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short BSTS:1;
//			unsigned short INBUFM:1;
//			unsigned short :3;
//			unsigned short ATREPM:1;
//			unsigned short ACLRM:1;
//			unsigned short SQCLR:1;
//			unsigned short SQSET:1;
//			unsigned short SQMON:1;
//			unsigned short PBUSY:1;
//			unsigned short :3;
//			unsigned short PID:2;
//		} BIT;
	} PIPE3CTR;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short BSTS:1;
//			unsigned short INBUFM:1;
//			unsigned short :3;
//			unsigned short ATREPM:1;
//			unsigned short ACLRM:1;
//			unsigned short SQCLR:1;
//			unsigned short SQSET:1;
//			unsigned short SQMON:1;
//			unsigned short PBUSY:1;
//			unsigned short :3;
//			unsigned short PID:2;
//		} BIT;
	} PIPE4CTR;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short BSTS:1;
//			unsigned short INBUFM:1;
//			unsigned short :3;
//			unsigned short ATREPM:1;
//			unsigned short ACLRM:1;
//			unsigned short SQCLR:1;
//			unsigned short SQSET:1;
//			unsigned short SQMON:1;
//			unsigned short PBUSY:1;
//			unsigned short :3;
//			unsigned short PID:2;
//		} BIT;
	} PIPE5CTR;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short BSTS:1;
//			unsigned short :5;
//			unsigned short ACLRM:1;
//			unsigned short SQCLR:1;
//			unsigned short SQSET:1;
//			unsigned short SQMON:1;
//			unsigned short PBUSY:1;
//			unsigned short :3;
//			unsigned short PID:2;
//		} BIT;
	} PIPE6CTR;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short BSTS:1;
//			unsigned short :5;
//			unsigned short ACLRM:1;
//			unsigned short SQCLR:1;
//			unsigned short SQSET:1;
//			unsigned short SQMON:1;
//			unsigned short PBUSY:1;
//			unsigned short :3;
//			unsigned short PID:2;
//		} BIT;
	} PIPE7CTR;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short BSTS:1;
//			unsigned short :5;
//			unsigned short ACLRM:1;
//			unsigned short SQCLR:1;
//			unsigned short SQSET:1;
//			unsigned short SQMON:1;
//			unsigned short PBUSY:1;
//			unsigned short :3;
//			unsigned short PID:2;
//		} BIT;
	} PIPE8CTR;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short BSTS:1;
//			unsigned short :5;
//			unsigned short ACLRM:1;
//			unsigned short SQCLR:1;
//			unsigned short SQSET:1;
//			unsigned short SQMON:1;
//			unsigned short PBUSY:1;
//			unsigned short :3;
//			unsigned short PID:2;
//		} BIT;
	} PIPE9CTR;
	char           wk14[14];
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :6;
//			unsigned short TRENB:1;
//			unsigned short TRCLR:1;
//			unsigned short :8;
//		} BIT;
	} PIPE1TRE;
	unsigned short PIPE1TRN;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :6;
//			unsigned short TRENB:1;
//			unsigned short TRCLR:1;
//			unsigned short :8;
//		} BIT;
	} PIPE2TRE;
	unsigned short PIPE2TRN;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :6;
//			unsigned short TRENB:1;
//			unsigned short TRCLR:1;
//			unsigned short :8;
//		} BIT;
	} PIPE3TRE;
	unsigned short PIPE3TRN;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :6;
//			unsigned short TRENB:1;
//			unsigned short TRCLR:1;
//			unsigned short :8;
//		} BIT;
	} PIPE4TRE;
	unsigned short PIPE4TRN;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :6;
//			unsigned short TRENB:1;
//			unsigned short TRCLR:1;
//			unsigned short :8;
//		} BIT;
	} PIPE5TRE;
	unsigned short PIPE5TRN;
	char           wk15[12];
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short PDDETSTS0:1;
			unsigned short CHGDETSTS0:1;
			unsigned short BATCHGE0:1;
			unsigned short :1;
			unsigned short VDMSRCE0:1;
			unsigned short IDPSINKE0:1;
			unsigned short VDPSRCE0:1;
			unsigned short IDMSINKE0:1;
			unsigned short IDPSRCE0:1;
			unsigned short RPDME0:1;
		} BIT;
	} USBBCCTRL0;
	char           wk16[26];
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short VDCEN:1;
			unsigned short :6;
			unsigned short VDDUSBE:1;
		} BIT;
	} USBMC;
	char           wk17[2];
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :8;
//			unsigned short USBSPD:2;
//			unsigned short :6;
//		} BIT;
	} DEVADD0;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :8;
//			unsigned short USBSPD:2;
//			unsigned short :6;
//		} BIT;
	} DEVADD1;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :8;
//			unsigned short USBSPD:2;
//			unsigned short :6;
//		} BIT;
	} DEVADD2;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :8;
//			unsigned short USBSPD:2;
//			unsigned short :6;
//		} BIT;
	} DEVADD3;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :8;
//			unsigned short USBSPD:2;
//			unsigned short :6;
//		} BIT;
	} DEVADD4;
	union {
		unsigned short WORD;
//		struct {
//			unsigned short :8;
//			unsigned short USBSPD:2;
//			unsigned short :6;
//		} BIT;
	} DEVADD5;
};

struct st_wdt {
	unsigned char  WDTRR;
	char           wk0[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short :2;
			unsigned short RPSS:2;
			unsigned short :2;
			unsigned short RPES:2;
			unsigned short CKS:4;
			unsigned short :2;
			unsigned short TOPS:2;
		} BIT;
	} WDTCR;
	union {
		unsigned short WORD;
		struct {
			unsigned short REFEF:1;
			unsigned short UNDFF:1;
			unsigned short CNTVAL:14;
		} BIT;
	} WDTSR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char RSTIRQS:1;
			unsigned char :7;
		} BIT;
	} WDTRCR;
};

enum enum_ir {
IR_BSC_BUSERR=16,IR_FCU_FRDYI=23,
IR_ICU_SWINT=27,
IR_CMT0_CMI0,IR_CMT1_CMI1,
IR_CMT2_CMI2,IR_CMT3_CMI3,
IR_CAC_FERRF,IR_CAC_MENDF,IR_CAC_OVFF,
IR_USB0_D0FIFO0=36,IR_USB0_D1FIFO0,IR_USB0_USBI0,
IR_SDHI_SBFAI=40,IR_SDHI_CDETI,IR_SDHI_CACI,IR_SDHI_SDACI,
IR_RSPI0_SPEI0,IR_RSPI0_SPRI0,IR_RSPI0_SPTI0,IR_RSPI0_SPII0,
IR_RSCAN_COMFRXINT=52,IR_RSCAN_RXFINT,IR_RSCAN_TXINT,IR_RSCAN_CHERRINT,IR_RSCAN_GLERRINT,
IR_DOC_DOPCF,
IR_CMPB_CMPB0,IR_CMPB_CMPB1,
IR_CTSU_CTSUWR,IR_CTSU_CTSURD,IR_CTSU_CTSUFN,
IR_RTC_CUP,
IR_ICU_IRQ0,IR_ICU_IRQ1,IR_ICU_IRQ2,IR_ICU_IRQ3,IR_ICU_IRQ4,IR_ICU_IRQ5,IR_ICU_IRQ6,IR_ICU_IRQ7,
IR_ELC_ELSR8I=80,
IR_LVD_LVD1=88,IR_LVD_LVD2,
IR_CMPA_CMPA1=88,IR_CMPA_CMPA2,
IR_USB0_USBR0,
IR_VBATT_VBTLVDI,
IR_RTC_ALM,IR_RTC_PRD,
IR_S12AD_S12ADI0=102,IR_S12AD_GBADI,
IR_CMPB1_CMPB2,IR_CMPB1_CMPB3,
IR_ELC_ELSR18I,IR_ELC_ELSR19I,
IR_SSI0_SSIF0,IR_SSI0_SSIRXI0,IR_SSI0_SSITXI0,
IR_SECURITY_RD,IR_SECURITY_WR,IR_SECURITY_ERR,
IR_MTU0_TGIA0,IR_MTU0_TGIB0,IR_MTU0_TGIC0,IR_MTU0_TGID0,IR_MTU0_TCIV0,IR_MTU0_TGIE0,IR_MTU0_TGIF0,
IR_MTU1_TGIA1,IR_MTU1_TGIB1,IR_MTU1_TCIV1,IR_MTU1_TCIU1,
IR_MTU2_TGIA2,IR_MTU2_TGIB2,IR_MTU2_TCIV2,IR_MTU2_TCIU2,
IR_MTU3_TGIA3,IR_MTU3_TGIB3,IR_MTU3_TGIC3,IR_MTU3_TGID3,IR_MTU3_TCIV3,
IR_MTU4_TGIA4,IR_MTU4_TGIB4,IR_MTU4_TGIC4,IR_MTU4_TGID4,IR_MTU4_TCIV4,
IR_MTU5_TGIU5,IR_MTU5_TGIV5,IR_MTU5_TGIW5,
IR_TPU0_TGI0A,IR_TPU0_TGI0B,IR_TPU0_TGI0C,IR_TPU0_TGI0D,IR_TPU0_TCI0V,
IR_TPU1_TGI1A,IR_TPU1_TGI1B,IR_TPU1_TCI1V,IR_TPU1_TCI1U,
IR_TPU2_TGI2A,IR_TPU2_TGI2B,IR_TPU2_TCI2V,IR_TPU2_TCI2U,
IR_TPU3_TGI3A,IR_TPU3_TGI3B,IR_TPU3_TGI3C,IR_TPU3_TGI3D,IR_TPU3_TCI3V,
IR_TPU4_TGI4A,IR_TPU4_TGI4B,IR_TPU4_TCI4V,IR_TPU4_TCI4U,
IR_TPU5_TGI5A,IR_TPU5_TGI5B,IR_TPU5_TCI5V,IR_TPU5_TCI5U,
IR_POE_OEI1=170,IR_POE_OEI2,
IR_TMR0_CMIA0=174,IR_TMR0_CMIB0,IR_TMR0_OVI0,
IR_TMR1_CMIA1,IR_TMR1_CMIB1,IR_TMR1_OVI1,
IR_TMR2_CMIA2,IR_TMR2_CMIB2,IR_TMR2_OVI2,
IR_TMR3_CMIA3,IR_TMR3_CMIB3,IR_TMR3_OVI3,
IR_DMAC_DMAC0I=198,IR_DMAC_DMAC1I,IR_DMAC_DMAC2I,IR_DMAC_DMAC3I,
IR_SCI0_ERI0=214,IR_SCI0_RXI0,IR_SCI0_TXI0,IR_SCI0_TEI0,
IR_SCI1_ERI1,IR_SCI1_RXI1,IR_SCI1_TXI1,IR_SCI1_TEI1,
IR_SCI5_ERI5,IR_SCI5_RXI5,IR_SCI5_TXI5,IR_SCI5_TEI5,
IR_SCI6_ERI6,IR_SCI6_RXI6,IR_SCI6_TXI6,IR_SCI6_TEI6,
IR_SCI8_ERI8,IR_SCI8_RXI8,IR_SCI8_TXI8,IR_SCI8_TEI8,
IR_SCI9_ERI9,IR_SCI9_RXI9,IR_SCI9_TXI9,IR_SCI9_TEI9,
IR_SCI12_ERI12,IR_SCI12_RXI12,IR_SCI12_TXI12,IR_SCI12_TEI12,IR_SCI12_SCIX0,IR_SCI12_SCIX1,IR_SCI12_SCIX2,IR_SCI12_SCIX3,
IR_RIIC0_EEI0,IR_RIIC0_RXI0,IR_RIIC0_TXI0,IR_RIIC0_TEI0
};

enum enum_dtce {
DTCE_ICU_SWINT=27,
DTCE_CMT0_CMI0,DTCE_CMT1_CMI1,
DTCE_CMT2_CMI2,DTCE_CMT3_CMI3,
DTCE_USB0_D0FIFO0=36,DTCE_USB0_D1FIFO0,
DTCE_SDHI_SBFAI=40,
DTCE_RSPI0_SPRI0=45,DTCE_RSPI0_SPTI0,
DTCE_RSCAN_COMFRXINT=52,
DTCE_CMPB_CMPB0=58,DTCE_CMPB_CMPB1,
DTCE_CTSU_CTSUWR,DTCE_CTSU_CTSURD,
DTCE_ICU_IRQ0=64,DTCE_ICU_IRQ1,DTCE_ICU_IRQ2,DTCE_ICU_IRQ3,DTCE_ICU_IRQ4,DTCE_ICU_IRQ5,DTCE_ICU_IRQ6,DTCE_ICU_IRQ7,
DTCE_S12AD_S12ADI0=102,DTCE_S12AD_GBADI,
DTCE_CMPB1_CMPB2,DTCE_CMPB1_CMPB3,
DTCE_ELC_ELSR18I,DTCE_ELC_ELSR19I,
DTCE_SSI0_SSIRXI0=109,DTCE_SSI0_SSITXI0,
DTCE_SECURITY_RD,DTCE_SECURITY_WR,
DTCE_MTU0_TGIA0=114,DTCE_MTU0_TGIB0,DTCE_MTU0_TGIC0,DTCE_MTU0_TGID0,
DTCE_MTU1_TGIA1=121,DTCE_MTU1_TGIB1,
DTCE_MTU2_TGIA2=125,DTCE_MTU2_TGIB2,
DTCE_MTU3_TGIA3=129,DTCE_MTU3_TGIB3,DTCE_MTU3_TGIC3,DTCE_MTU3_TGID3,
DTCE_MTU4_TGIA4=134,DTCE_MTU4_TGIB4,DTCE_MTU4_TGIC4,DTCE_MTU4_TGID4,DTCE_MTU4_TCIV4,
DTCE_MTU5_TGIU5,DTCE_MTU5_TGIV5,DTCE_MTU5_TGIW5,
DTCE_TPU0_TGI0A,DTCE_TPU0_TGI0B,DTCE_TPU0_TGI0C,DTCE_TPU0_TGI0D,
DTCE_TPU1_TGI1A=147,DTCE_TPU1_TGI1B,
DTCE_TPU2_TGI2A=151,DTCE_TPU2_TGI2B,
DTCE_TPU3_TGI3A=155,DTCE_TPU3_TGI3B,DTCE_TPU3_TGI3C,DTCE_TPU3_TGI3D,
DTCE_TPU4_TGI4A=160,DTCE_TPU4_TGI4B,
DTCE_TPU5_TGI5A=164,DTCE_TPU5_TGI5B,
DTCE_TMR0_CMIA0=174,DTCE_TMR0_CMIB0,
DTCE_TMR1_CMIA1=177,DTCE_TMR1_CMIB1,
DTCE_TMR2_CMIA2=180,DTCE_TMR2_CMIB2,
DTCE_TMR3_CMIA3=183,DTCE_TMR3_CMIB3,
DTCE_DMAC_DMAC0I=198,DTCE_DMAC_DMAC1I,DTCE_DMAC_DMAC2I,DTCE_DMAC_DMAC3I,
DTCE_SCI0_RXI0=215,DTCE_SCI0_TXI0,
DTCE_SCI1_RXI1=219,DTCE_SCI1_TXI1,
DTCE_SCI5_RXI5=223,DTCE_SCI5_TXI5,
DTCE_SCI6_RXI6=227,DTCE_SCI6_TXI6,
DTCE_SCI8_RXI8=231,DTCE_SCI8_TXI8,
DTCE_SCI9_RXI9=235,DTCE_SCI9_TXI9,
DTCE_SCI12_RXI12=239,DTCE_SCI12_TXI12,
DTCE_RIIC0_RXI0=247,DTCE_RIIC0_TXI0
};

enum enum_ier {
IER_BSC_BUSERR=0x02,
IER_FCU_FRDYI=0x02,
IER_ICU_SWINT=0x03,
IER_CMT0_CMI0=0x03,IER_CMT1_CMI1=0x03,
IER_CMT2_CMI2=0x03,IER_CMT3_CMI3=0x03,
IER_CAC_FERRF=0x04,IER_CAC_MENDF=0x04,IER_CAC_OVFF=0x04,
IER_USB0_D0FIFO0=0x04,IER_USB0_D1FIFO0=0x04,IER_USB0_USBI0=0x04,
IER_SDHI_SBFAI=0x05,IER_SDHI_CDETI=0x05,IER_SDHI_CACI=0x05,IER_SDHI_SDACI=0x05,
IER_RSPI0_SPEI0=0x05,IER_RSPI0_SPRI0=0x05,IER_RSPI0_SPTI0=0x05,IER_RSPI0_SPII0=0x05,
IER_RSCAN_COMFRXINT=0x06,IER_RSCAN_RXFINT=0x06,IER_RSCAN_TXINT=0x06,IER_RSCAN_CHERRINT=0x06,IER_RSCAN_GLERRINT=0x07,
IER_DOC_DOPCF=0x07,
IER_CMPB_CMPB0=0x07,IER_CMPB_CMPB1=0x07,
IER_CTSU_CTSUWR=0x07,IER_CTSU_CTSURD=0x07,IER_CTSU_CTSUFN=0x07,
IER_RTC_CUP=0x07,
IER_ICU_IRQ0=0x08,IER_ICU_IRQ1=0x08,IER_ICU_IRQ2=0x08,IER_ICU_IRQ3=0x08,IER_ICU_IRQ4=0x08,IER_ICU_IRQ5=0x08,IER_ICU_IRQ6=0x08,IER_ICU_IRQ7=0x08,
IER_ELC_ELSR8I=0x0A,
IER_LVD_LVD1=0x0B,IER_LVD_LVD2=0x0B,
IER_CMPA_CMPA1=0x0B,IER_CMPA_CMPA2=0x0B,
IER_USB0_USBR0=0x0B,
IER_VBATT_VBTLVDI=0x0B,
IER_RTC_ALM=0x0B,IER_RTC_PRD=0x0B,
IER_S12AD_S12ADI0=0x0C,IER_S12AD_GBADI=0x0C,
IER_CMPB1_CMPB2=0x0D,IER_CMPB1_CMPB3=0x0D,
IER_ELC_ELSR18I=0x0D,IER_ELC_ELSR19I=0x0D,
IER_SSI0_SSIF0=0x0D,IER_SSI0_SSIRXI0=0x0D,IER_SSI0_SSITXI0=0x0D,
IER_SECURITY_RD=0x0D,IER_SECURITY_WR=0x0E,IER_SECURITY_ERR=0x0E,
IER_MTU0_TGIA0=0x0E,IER_MTU0_TGIB0=0x0E,IER_MTU0_TGIC0=0x0E,IER_MTU0_TGID0=0x0E,IER_MTU0_TCIV0=0x0E,IER_MTU0_TGIE0=0x0E,IER_MTU0_TGIF0=0x0F,
IER_MTU1_TGIA1=0x0F,IER_MTU1_TGIB1=0x0F,IER_MTU1_TCIV1=0x0F,IER_MTU1_TCIU1=0x0F,
IER_MTU2_TGIA2=0x0F,IER_MTU2_TGIB2=0x0F,IER_MTU2_TCIV2=0x0F,IER_MTU2_TCIU2=0x10,
IER_MTU3_TGIA3=0x10,IER_MTU3_TGIB3=0x10,IER_MTU3_TGIC3=0x10,IER_MTU3_TGID3=0x10,IER_MTU3_TCIV3=0x10,
IER_MTU4_TGIA4=0x10,IER_MTU4_TGIB4=0x10,IER_MTU4_TGIC4=0x11,IER_MTU4_TGID4=0x11,IER_MTU4_TCIV4=0x11,
IER_MTU5_TGIU5=0x11,IER_MTU5_TGIV5=0x11,IER_MTU5_TGIW5=0x11,
IER_TPU0_TGI0A=0x11,IER_TPU0_TGI0B=0x11,IER_TPU0_TGI0C=0x12,IER_TPU0_TGI0D=0x12,IER_TPU0_TCI0V=0x12,
IER_TPU1_TGI1A=0x12,IER_TPU1_TGI1B=0x12,IER_TPU1_TCI1V=0x12,IER_TPU1_TCI1U=0x12,
IER_TPU2_TGI2A=0x12,IER_TPU2_TGI2B=0x13,IER_TPU2_TCI2V=0x13,IER_TPU2_TCI2U=0x13,
IER_TPU3_TGI3A=0x13,IER_TPU3_TGI3B=0x13,IER_TPU3_TGI3C=0x13,IER_TPU3_TGI3D=0x13,IER_TPU3_TCI3V=0x13,
IER_TPU4_TGI4A=0x14,IER_TPU4_TGI4B=0x14,IER_TPU4_TCI4V=0x14,IER_TPU4_TCI4U=0x14,
IER_TPU5_TGI5A=0x14,IER_TPU5_TGI5B=0x14,IER_TPU5_TCI5V=0x14,IER_TPU5_TCI5U=0x14,
IER_POE_OEI1=0x15,IER_POE_OEI2=0x15,
IER_TMR0_CMIA0=0x15,IER_TMR0_CMIB0=0x15,IER_TMR0_OVI0=0x16,
IER_TMR1_CMIA1=0x16,IER_TMR1_CMIB1=0x16,IER_TMR1_OVI1=0x16,
IER_TMR2_CMIA2=0x16,IER_TMR2_CMIB2=0x16,IER_TMR2_OVI2=0x16,
IER_TMR3_CMIA3=0x16,IER_TMR3_CMIB3=0x17,IER_TMR3_OVI3=0x17,
IER_DMAC_DMAC0I=0x18,IER_DMAC_DMAC1I=0x18,IER_DMAC_DMAC2I=0x19,IER_DMAC_DMAC3I=0x19,
IER_SCI0_ERI0=0x1A,IER_SCI0_RXI0=0x1A,IER_SCI0_TXI0=0x1B,IER_SCI0_TEI0=0x1B,
IER_SCI1_ERI1=0x1B,IER_SCI1_RXI1=0x1B,IER_SCI1_TXI1=0x1B,IER_SCI1_TEI1=0x1B,
IER_SCI5_ERI5=0x1B,IER_SCI5_RXI5=0x1B,IER_SCI5_TXI5=0x1C,IER_SCI5_TEI5=0x1C,
IER_SCI6_ERI6=0x1C,IER_SCI6_RXI6=0x1C,IER_SCI6_TXI6=0x1C,IER_SCI6_TEI6=0x1C,
IER_SCI8_ERI8=0x1C,IER_SCI8_RXI8=0x1C,IER_SCI8_TXI8=0x1D,IER_SCI8_TEI8=0x1D,
IER_SCI9_ERI9=0x1D,IER_SCI9_RXI9=0x1D,IER_SCI9_TXI9=0x1D,IER_SCI9_TEI9=0x1D,
IER_SCI12_ERI12=0x1D,IER_SCI12_RXI12=0x1D,IER_SCI12_TXI12=0x1E,IER_SCI12_TEI12=0x1E,IER_SCI12_SCIX0=0x1E,IER_SCI12_SCIX1=0x1E,IER_SCI12_SCIX2=0x1E,IER_SCI12_SCIX3=0x1E,
IER_RIIC0_EEI0=0x1E,IER_RIIC0_RXI0=0x1E,IER_RIIC0_TXI0=0x1F,IER_RIIC0_TEI0=0x1F
};

enum enum_ipr {
IPR_BSC_BUSERR=0,
IPR_FCU_FRDYI=2,
IPR_ICU_SWINT=3,
IPR_CMT0_CMI0=4,IPR_CMT1_CMI1=5,
IPR_CMT2_CMI2=6,IPR_CMT3_CMI3=7,
IPR_CAC_FERRF=32,IPR_CAC_MENDF=33,IPR_CAC_OVFF=34,
IPR_USB0_D0FIFO0=36,IPR_USB0_D1FIFO0=37,IPR_USB0_USBI0=38,
IPR_SDHI_SBFAI=40,IPR_SDHI_CDETI=41,IPR_SDHI_CACI=42,IPR_SDHI_SDACI=43,
IPR_RSPI0_SPEI0=44,IPR_RSPI0_SPRI0=44,IPR_RSPI0_SPTI0=44,IPR_RSPI0_SPII0=44,
IPR_RSCAN_COMFRXINT=52,IPR_RSCAN_RXFINT=53,IPR_RSCAN_TXINT=54,IPR_RSCAN_CHERRINT=55,IPR_RSCAN_GLERRINT=56,
IPR_DOC_DOPCF=57,
IPR_CMPB_CMPB0=58,IPR_CMPB_CMPB1=59,
IPR_CTSU_CTSUWR=60,IPR_CTSU_CTSURD=60,IPR_CTSU_CTSUFN=60,
IPR_RTC_CUP=63,
IPR_ICU_IRQ0=64,IPR_ICU_IRQ1=65,IPR_ICU_IRQ2=66,IPR_ICU_IRQ3=67,IPR_ICU_IRQ4=68,IPR_ICU_IRQ5=69,IPR_ICU_IRQ6=70,IPR_ICU_IRQ7=71,
IPR_ELC_ELSR8I=80,
IPR_LVD_LVD1=88,IPR_LVD_LVD2=89,
IPR_CMPA_CMPA1=88,IPR_CMPA_CMPA2=89,
IPR_USB0_USBR0=90,
IPR_VBATT_VBTLVDI=91,
IPR_RTC_ALM=92,IPR_RTC_PRD=93,
IPR_S12AD_S12ADI0=102,IPR_S12AD_GBADI=103,
IPR_CMPB1_CMPB2=104,IPR_CMPB1_CMPB3=105,
IPR_ELC_ELSR18I=106,IPR_ELC_ELSR19I=107,
IPR_SSI0_SSIF0=108,IPR_SSI0_SSIRXI0=108,IPR_SSI0_SSITXI0=108,
IPR_SECURITY_RD=111,IPR_SECURITY_WR=111,IPR_SECURITY_ERR=113,
IPR_MTU0_TGIA0=114,IPR_MTU0_TGIB0=114,IPR_MTU0_TGIC0=114,IPR_MTU0_TGID0=114,IPR_MTU0_TCIV0=118,IPR_MTU0_TGIE0=118,IPR_MTU0_TGIF0=118,
IPR_MTU1_TGIA1=121,IPR_MTU1_TGIB1=121,IPR_MTU1_TCIV1=123,IPR_MTU1_TCIU1=123,
IPR_MTU2_TGIA2=125,IPR_MTU2_TGIB2=125,IPR_MTU2_TCIV2=127,IPR_MTU2_TCIU2=127,
IPR_MTU3_TGIA3=129,IPR_MTU3_TGIB3=129,IPR_MTU3_TGIC3=129,IPR_MTU3_TGID3=129,IPR_MTU3_TCIV3=133,
IPR_MTU4_TGIA4=134,IPR_MTU4_TGIB4=134,IPR_MTU4_TGIC4=134,IPR_MTU4_TGID4=134,IPR_MTU4_TCIV4=138,
IPR_MTU5_TGIU5=139,IPR_MTU5_TGIV5=139,IPR_MTU5_TGIW5=139,
IPR_TPU0_TGI0A=142,IPR_TPU0_TGI0B=142,IPR_TPU0_TGI0C=142,IPR_TPU0_TGI0D=142,IPR_TPU0_TCI0V=146,
IPR_TPU1_TGI1A=147,IPR_TPU1_TGI1B=147,IPR_TPU1_TCI1V=149,IPR_TPU1_TCI1U=149,
IPR_TPU2_TGI2A=151,IPR_TPU2_TGI2B=151,IPR_TPU2_TCI2V=153,IPR_TPU2_TCI2U=153,
IPR_TPU3_TGI3A=155,IPR_TPU3_TGI3B=155,IPR_TPU3_TGI3C=155,IPR_TPU3_TGI3D=155,IPR_TPU3_TCI3V=159,
IPR_TPU4_TGI4A=160,IPR_TPU4_TGI4B=160,IPR_TPU4_TCI4V=162,IPR_TPU4_TCI4U=162,
IPR_TPU5_TGI5A=164,IPR_TPU5_TGI5B=164,IPR_TPU5_TCI5V=166,IPR_TPU5_TCI5U=166,
IPR_POE_OEI1=170,IPR_POE_OEI2=171,
IPR_TMR0_CMIA0=174,IPR_TMR0_CMIB0=174,IPR_TMR0_OVI0=174,
IPR_TMR1_CMIA1=177,IPR_TMR1_CMIB1=177,IPR_TMR1_OVI1=177,
IPR_TMR2_CMIA2=180,IPR_TMR2_CMIB2=180,IPR_TMR2_OVI2=180,
IPR_TMR3_CMIA3=183,IPR_TMR3_CMIB3=183,IPR_TMR3_OVI3=183,
IPR_DMAC_DMAC0I=198,IPR_DMAC_DMAC1I=199,IPR_DMAC_DMAC2I=200,IPR_DMAC_DMAC3I=201,
IPR_SCI0_ERI0=214,IPR_SCI0_RXI0=214,IPR_SCI0_TXI0=214,IPR_SCI0_TEI0=214,
IPR_SCI1_ERI1=218,IPR_SCI1_RXI1=218,IPR_SCI1_TXI1=218,IPR_SCI1_TEI1=218,
IPR_SCI5_ERI5=222,IPR_SCI5_RXI5=222,IPR_SCI5_TXI5=222,IPR_SCI5_TEI5=222,
IPR_SCI6_ERI6=226,IPR_SCI6_RXI6=226,IPR_SCI6_TXI6=226,IPR_SCI6_TEI6=226,
IPR_SCI8_ERI8=230,IPR_SCI8_RXI8=230,IPR_SCI8_TXI8=230,IPR_SCI8_TEI8=230,
IPR_SCI9_ERI9=234,IPR_SCI9_RXI9=234,IPR_SCI9_TXI9=234,IPR_SCI9_TEI9=234,
IPR_SCI12_ERI12=238,IPR_SCI12_RXI12=238,IPR_SCI12_TXI12=238,IPR_SCI12_TEI12=238,IPR_SCI12_SCIX0=242,IPR_SCI12_SCIX1=243,IPR_SCI12_SCIX2=244,IPR_SCI12_SCIX3=245,
IPR_RIIC0_EEI0=246,IPR_RIIC0_RXI0=247,IPR_RIIC0_TXI0=248,IPR_RIIC0_TEI0=249,
IPR_BSC_=0,
IPR_FCU_=2,
IPR_RSPI0_=44,
IPR_DOC_=57,
IPR_VBATT_=91,
IPR_MTU1_TGI=121,
IPR_MTU1_TCI=123,
IPR_MTU2_TGI=125,
IPR_MTU2_TCI=127,
IPR_MTU3_TGI=129,
IPR_MTU4_TGI=134,
IPR_MTU5_=139,
IPR_MTU5_TGI=139,
IPR_TPU0_TGI=142,
IPR_TPU1_TGI=147,
IPR_TPU1_TCI=149,
IPR_TPU2_TGI=151,
IPR_TPU2_TCI=153,
IPR_TPU3_TGI=155,
IPR_TPU4_TGI=160,
IPR_TPU4_TCI=162,
IPR_TPU5_TGI=164,
IPR_TPU5_TCI=166,
IPR_TMR0_=174,
IPR_TMR1_=177,
IPR_TMR2_=180,
IPR_TMR3_=183,
IPR_SCI0_=214,
IPR_SCI1_=218,
IPR_SCI5_=222,
IPR_SCI6_=226,
IPR_SCI8_=230,
IPR_SCI9_=234
};

#define	IEN_BSC_BUSERR		IEN0
#define	IEN_FCU_FRDYI		IEN7
#define	IEN_ICU_SWINT		IEN3
#define	IEN_CMT0_CMI0		IEN4
#define	IEN_CMT1_CMI1		IEN5
#define	IEN_CMT2_CMI2		IEN6
#define	IEN_CMT3_CMI3		IEN7
#define	IEN_CAC_FERRF		IEN0
#define	IEN_CAC_MENDF		IEN1
#define	IEN_CAC_OVFF		IEN2
#define	IEN_USB0_D0FIFO0	IEN4
#define	IEN_USB0_D1FIFO0	IEN5
#define	IEN_USB0_USBI0		IEN6
#define	IEN_SDHI_SBFAI		IEN0
#define	IEN_SDHI_CDETI		IEN1
#define	IEN_SDHI_CACI		IEN2
#define	IEN_SDHI_SDACI		IEN3
#define	IEN_RSPI0_SPEI0		IEN4
#define	IEN_RSPI0_SPRI0		IEN5
#define	IEN_RSPI0_SPTI0		IEN6
#define	IEN_RSPI0_SPII0		IEN7
#define	IEN_RSCAN_COMFRXINT	IEN4
#define	IEN_RSCAN_RXFINT	IEN5
#define	IEN_RSCAN_TXINT		IEN6
#define	IEN_RSCAN_CHERRINT	IEN7
#define	IEN_RSCAN_GLERRINT	IEN0
#define	IEN_DOC_DOPCF		IEN1
#define	IEN_CMPB_CMPB0		IEN2
#define	IEN_CMPB_CMPB1		IEN3
#define	IEN_CTSU_CTSUWR		IEN4
#define	IEN_CTSU_CTSURD		IEN5
#define	IEN_CTSU_CTSUFN		IEN6
#define	IEN_RTC_CUP			IEN7
#define	IEN_ICU_IRQ0		IEN0
#define	IEN_ICU_IRQ1		IEN1
#define	IEN_ICU_IRQ2		IEN2
#define	IEN_ICU_IRQ3		IEN3
#define	IEN_ICU_IRQ4		IEN4
#define	IEN_ICU_IRQ5		IEN5
#define	IEN_ICU_IRQ6		IEN6
#define	IEN_ICU_IRQ7		IEN7
#define	IEN_ELC_ELSR8I		IEN0
#define	IEN_LVD_LVD1		IEN0
#define	IEN_LVD_LVD2		IEN1
#define	IEN_CMPA_CMPA1		IEN0
#define	IEN_CMPA_CMPA2		IEN1
#define	IEN_USB0_USBR0		IEN2
#define	IEN_VBATT_VBTLVDI	IEN3
#define	IEN_RTC_ALM			IEN4
#define	IEN_RTC_PRD			IEN5
#define	IEN_S12AD_S12ADI0	IEN6
#define	IEN_S12AD_GBADI		IEN7
#define	IEN_CMPB1_CMPB2		IEN0
#define	IEN_CMPB1_CMPB3		IEN1
#define	IEN_ELC_ELSR18I		IEN2
#define	IEN_ELC_ELSR19I		IEN3
#define	IEN_SSI0_SSIF0		IEN4
#define	IEN_SSI0_SSIRXI0	IEN5
#define	IEN_SSI0_SSITXI0	IEN6
#define	IEN_SECURITY_RD		IEN7
#define	IEN_SECURITY_WR		IEN0
#define	IEN_SECURITY_ERR	IEN1
#define	IEN_MTU0_TGIA0		IEN2
#define	IEN_MTU0_TGIB0		IEN3
#define	IEN_MTU0_TGIC0		IEN4
#define	IEN_MTU0_TGID0		IEN5
#define	IEN_MTU0_TCIV0		IEN6
#define	IEN_MTU0_TGIE0		IEN7
#define	IEN_MTU0_TGIF0		IEN0
#define	IEN_MTU1_TGIA1		IEN1
#define	IEN_MTU1_TGIB1		IEN2
#define	IEN_MTU1_TCIV1		IEN3
#define	IEN_MTU1_TCIU1		IEN4
#define	IEN_MTU2_TGIA2		IEN5
#define	IEN_MTU2_TGIB2		IEN6
#define	IEN_MTU2_TCIV2		IEN7
#define	IEN_MTU2_TCIU2		IEN0
#define	IEN_MTU3_TGIA3		IEN1
#define	IEN_MTU3_TGIB3		IEN2
#define	IEN_MTU3_TGIC3		IEN3
#define	IEN_MTU3_TGID3		IEN4
#define	IEN_MTU3_TCIV3		IEN5
#define	IEN_MTU4_TGIA4		IEN6
#define	IEN_MTU4_TGIB4		IEN7
#define	IEN_MTU4_TGIC4		IEN0
#define	IEN_MTU4_TGID4		IEN1
#define	IEN_MTU4_TCIV4		IEN2
#define	IEN_MTU5_TGIU5		IEN3
#define	IEN_MTU5_TGIV5		IEN4
#define	IEN_MTU5_TGIW5		IEN5
#define	IEN_TPU0_TGI0A		IEN6
#define	IEN_TPU0_TGI0B		IEN7
#define	IEN_TPU0_TGI0C		IEN0
#define	IEN_TPU0_TGI0D		IEN1
#define	IEN_TPU0_TCI0V		IEN2
#define	IEN_TPU1_TGI1A		IEN3
#define	IEN_TPU1_TGI1B		IEN4
#define	IEN_TPU1_TCI1V		IEN5
#define	IEN_TPU1_TCI1U		IEN6
#define	IEN_TPU2_TGI2A		IEN7
#define	IEN_TPU2_TGI2B		IEN0
#define	IEN_TPU2_TCI2V		IEN1
#define	IEN_TPU2_TCI2U		IEN2
#define	IEN_TPU3_TGI3A		IEN3
#define	IEN_TPU3_TGI3B		IEN4
#define	IEN_TPU3_TGI3C		IEN5
#define	IEN_TPU3_TGI3D		IEN6
#define	IEN_TPU3_TCI3V		IEN7
#define	IEN_TPU4_TGI4A		IEN0
#define	IEN_TPU4_TGI4B		IEN1
#define	IEN_TPU4_TCI4V		IEN2
#define	IEN_TPU4_TCI4U		IEN3
#define	IEN_TPU5_TGI5A		IEN4
#define	IEN_TPU5_TGI5B		IEN5
#define	IEN_TPU5_TCI5V		IEN6
#define	IEN_TPU5_TCI5U		IEN7
#define	IEN_POE_OEI1		IEN2
#define	IEN_POE_OEI2		IEN3
#define	IEN_TMR0_CMIA0		IEN6
#define	IEN_TMR0_CMIB0		IEN7
#define	IEN_TMR0_OVI0		IEN0
#define	IEN_TMR1_CMIA1		IEN1
#define	IEN_TMR1_CMIB1		IEN2
#define	IEN_TMR1_OVI1		IEN3
#define	IEN_TMR2_CMIA2		IEN4
#define	IEN_TMR2_CMIB2		IEN5
#define	IEN_TMR2_OVI2		IEN6
#define	IEN_TMR3_CMIA3		IEN7
#define	IEN_TMR3_CMIB3		IEN0
#define	IEN_TMR3_OVI3		IEN1
#define	IEN_DMAC_DMAC0I		IEN6
#define	IEN_DMAC_DMAC1I		IEN7
#define	IEN_DMAC_DMAC2I		IEN0
#define	IEN_DMAC_DMAC3I		IEN1
#define	IEN_SCI0_ERI0		IEN6
#define	IEN_SCI0_RXI0		IEN7
#define	IEN_SCI0_TXI0		IEN0
#define	IEN_SCI0_TEI0		IEN1
#define	IEN_SCI1_ERI1		IEN2
#define	IEN_SCI1_RXI1		IEN3
#define	IEN_SCI1_TXI1		IEN4
#define	IEN_SCI1_TEI1		IEN5
#define	IEN_SCI5_ERI5		IEN6
#define	IEN_SCI5_RXI5		IEN7
#define	IEN_SCI5_TXI5		IEN0
#define	IEN_SCI5_TEI5		IEN1
#define	IEN_SCI6_ERI6		IEN2
#define	IEN_SCI6_RXI6		IEN3
#define	IEN_SCI6_TXI6		IEN4
#define	IEN_SCI6_TEI6		IEN5
#define	IEN_SCI8_ERI8		IEN6
#define	IEN_SCI8_RXI8		IEN7
#define	IEN_SCI8_TXI8		IEN0
#define	IEN_SCI8_TEI8		IEN1
#define	IEN_SCI9_ERI9		IEN2
#define	IEN_SCI9_RXI9		IEN3
#define	IEN_SCI9_TXI9		IEN4
#define	IEN_SCI9_TEI9		IEN5
#define	IEN_SCI12_ERI12		IEN6
#define	IEN_SCI12_RXI12		IEN7
#define	IEN_SCI12_TXI12		IEN0
#define	IEN_SCI12_TEI12		IEN1
#define	IEN_SCI12_SCIX0		IEN2
#define	IEN_SCI12_SCIX1		IEN3
#define	IEN_SCI12_SCIX2		IEN4
#define	IEN_SCI12_SCIX3		IEN5
#define	IEN_RIIC0_EEI0		IEN6
#define	IEN_RIIC0_RXI0		IEN7
#define	IEN_RIIC0_TXI0		IEN0
#define	IEN_RIIC0_TEI0		IEN1

#define	VECT_BSC_BUSERR		16
#define	VECT_FCU_FRDYI		23
#define	VECT_ICU_SWINT		27
#define	VECT_CMT0_CMI0		28
#define	VECT_CMT1_CMI1		29
#define	VECT_CMT2_CMI2		30
#define	VECT_CMT3_CMI3		31
#define	VECT_CAC_FERRF		32
#define	VECT_CAC_MENDF		33
#define	VECT_CAC_OVFF		34
#define	VECT_USB0_D0FIFO0	36
#define	VECT_USB0_D1FIFO0	37
#define	VECT_USB0_USBI0		38
#define	VECT_SDHI_SBFAI		40
#define	VECT_SDHI_CDETI		41
#define	VECT_SDHI_CACI		42
#define	VECT_SDHI_SDACI		43
#define	VECT_RSPI0_SPEI0	44
#define	VECT_RSPI0_SPRI0	45
#define	VECT_RSPI0_SPTI0	46
#define	VECT_RSPI0_SPII0	47
#define	VECT_RSCAN_COMFRXINT	52
#define	VECT_RSCAN_RXFINT	53
#define	VECT_RSCAN_TXINT	54
#define	VECT_RSCAN_CHERRINT	55
#define	VECT_RSCAN_GLERRINT	56
#define	VECT_DOC_DOPCF		57
#define	VECT_CMPB_CMPB0		58
#define	VECT_CMPB_CMPB1		59
#define	VECT_CTSU_CTSUWR	60
#define	VECT_CTSU_CTSURD	61
#define	VECT_CTSU_CTSUFN	62
#define	VECT_RTC_CUP		63
#define	VECT_ICU_IRQ0		64
#define	VECT_ICU_IRQ1		65
#define	VECT_ICU_IRQ2		66
#define	VECT_ICU_IRQ3		67
#define	VECT_ICU_IRQ4		68
#define	VECT_ICU_IRQ5		69
#define	VECT_ICU_IRQ6		70
#define	VECT_ICU_IRQ7		71
#define	VECT_ELC_ELSR8I		80
#define	VECT_LVD_LVD1		88
#define	VECT_LVD_LVD2		89
#define	VECT_CMPA_CMPA1		88
#define	VECT_CMPA_CMPA2		89
#define	VECT_USB0_USBR0		90
#define	VECT_VBATT_VBTLVDI	91
#define	VECT_RTC_ALM		92
#define	VECT_RTC_PRD		93
#define	VECT_S12AD_S12ADI0	102
#define	VECT_S12AD_GBADI	103
#define	VECT_CMPB1_CMPB2	104
#define	VECT_CMPB1_CMPB3	105
#define	VECT_ELC_ELSR18I	106
#define	VECT_ELC_ELSR19I	107
#define	VECT_SSI0_SSIF0		108
#define	VECT_SSI0_SSIRXI0	109
#define	VECT_SSI0_SSITXI0	110
#define	VECT_SECURITY_RD	111
#define	VECT_SECURITY_WR	112
#define	VECT_SECURITY_ERR	113
#define	VECT_MTU0_TGIA0		114
#define	VECT_MTU0_TGIB0		115
#define	VECT_MTU0_TGIC0		116
#define	VECT_MTU0_TGID0		117
#define	VECT_MTU0_TCIV0		118
#define	VECT_MTU0_TGIE0		119
#define	VECT_MTU0_TGIF0		120
#define	VECT_MTU1_TGIA1		121
#define	VECT_MTU1_TGIB1		122
#define	VECT_MTU1_TCIV1		123
#define	VECT_MTU1_TCIU1		124
#define	VECT_MTU2_TGIA2		125
#define	VECT_MTU2_TGIB2		126
#define	VECT_MTU2_TCIV2		127
#define	VECT_MTU2_TCIU2		128
#define	VECT_MTU3_TGIA3		129
#define	VECT_MTU3_TGIB3		130
#define	VECT_MTU3_TGIC3		131
#define	VECT_MTU3_TGID3		132
#define	VECT_MTU3_TCIV3		133
#define	VECT_MTU4_TGIA4		134
#define	VECT_MTU4_TGIB4		135
#define	VECT_MTU4_TGIC4		136
#define	VECT_MTU4_TGID4		137
#define	VECT_MTU4_TCIV4		138
#define	VECT_MTU5_TGIU5		139
#define	VECT_MTU5_TGIV5		140
#define	VECT_MTU5_TGIW5		141
#define	VECT_TPU0_TGI0A		142
#define	VECT_TPU0_TGI0B		143
#define	VECT_TPU0_TGI0C		144
#define	VECT_TPU0_TGI0D		145
#define	VECT_TPU0_TCI0V		146
#define	VECT_TPU1_TGI1A		147
#define	VECT_TPU1_TGI1B		148
#define	VECT_TPU1_TCI1V		149
#define	VECT_TPU1_TCI1U		150
#define	VECT_TPU2_TGI2A		151
#define	VECT_TPU2_TGI2B		152
#define	VECT_TPU2_TCI2V		153
#define	VECT_TPU2_TCI2U		154
#define	VECT_TPU3_TGI3A		155
#define	VECT_TPU3_TGI3B		156
#define	VECT_TPU3_TGI3C		157
#define	VECT_TPU3_TGI3D		158
#define	VECT_TPU3_TCI3V		159
#define	VECT_TPU4_TGI4A		160
#define	VECT_TPU4_TGI4B		161
#define	VECT_TPU4_TCI4V		162
#define	VECT_TPU4_TCI4U		163
#define	VECT_TPU5_TGI5A		164
#define	VECT_TPU5_TGI5B		165
#define	VECT_TPU5_TCI5V		166
#define	VECT_TPU5_TCI5U		167
#define	VECT_POE_OEI1		170
#define	VECT_POE_OEI2		171
#define	VECT_TMR0_CMIA0		174
#define	VECT_TMR0_CMIB0		175
#define	VECT_TMR0_OVI0		176
#define	VECT_TMR1_CMIA1		177
#define	VECT_TMR1_CMIB1		178
#define	VECT_TMR1_OVI1		179
#define	VECT_TMR2_CMIA2		180
#define	VECT_TMR2_CMIB2		181
#define	VECT_TMR2_OVI2		182
#define	VECT_TMR3_CMIA3		183
#define	VECT_TMR3_CMIB3		184
#define	VECT_TMR3_OVI3		185
#define	VECT_DMAC_DMAC0I	198
#define	VECT_DMAC_DMAC1I	199
#define	VECT_DMAC_DMAC2I	200
#define	VECT_DMAC_DMAC3I	201
#define	VECT_SCI0_ERI0		214
#define	VECT_SCI0_RXI0		215
#define	VECT_SCI0_TXI0		216
#define	VECT_SCI0_TEI0		217
#define	VECT_SCI1_ERI1		218
#define	VECT_SCI1_RXI1		219
#define	VECT_SCI1_TXI1		220
#define	VECT_SCI1_TEI1		221
#define	VECT_SCI5_ERI5		222
#define	VECT_SCI5_RXI5		223
#define	VECT_SCI5_TXI5		224
#define	VECT_SCI5_TEI5		225
#define	VECT_SCI6_ERI6		226
#define	VECT_SCI6_RXI6		227
#define	VECT_SCI6_TXI6		228
#define	VECT_SCI6_TEI6		229
#define	VECT_SCI8_ERI8		230
#define	VECT_SCI8_RXI8		231
#define	VECT_SCI8_TXI8		232
#define	VECT_SCI8_TEI8		233
#define	VECT_SCI9_ERI9		234
#define	VECT_SCI9_RXI9		235
#define	VECT_SCI9_TXI9		236
#define	VECT_SCI9_TEI9		237
#define	VECT_SCI12_ERI12	238
#define	VECT_SCI12_RXI12	239
#define	VECT_SCI12_TXI12	240
#define	VECT_SCI12_TEI12	241
#define	VECT_SCI12_SCIX0	242
#define	VECT_SCI12_SCIX1	243
#define	VECT_SCI12_SCIX2	244
#define	VECT_SCI12_SCIX3	245
#define	VECT_RIIC0_EEI0		246
#define	VECT_RIIC0_RXI0		247
#define	VECT_RIIC0_TXI0		248
#define	VECT_RIIC0_TEI0		249

#define	MSTP_DMAC	SYSTEM.MSTPCRA.BIT.MSTPA28
#define	MSTP_DMAC0	SYSTEM.MSTPCRA.BIT.MSTPA28
#define	MSTP_DMAC1	SYSTEM.MSTPCRA.BIT.MSTPA28
#define	MSTP_DMAC2	SYSTEM.MSTPCRA.BIT.MSTPA28
#define	MSTP_DMAC3	SYSTEM.MSTPCRA.BIT.MSTPA28
#define	MSTP_DTC	SYSTEM.MSTPCRA.BIT.MSTPA28
#define	MSTP_DA		SYSTEM.MSTPCRA.BIT.MSTPA19
#define	MSTP_S12AD	SYSTEM.MSTPCRA.BIT.MSTPA17
#define	MSTP_CMT0	SYSTEM.MSTPCRA.BIT.MSTPA15
#define	MSTP_CMT1	SYSTEM.MSTPCRA.BIT.MSTPA15
#define	MSTP_CMT2	SYSTEM.MSTPCRA.BIT.MSTPA14
#define	MSTP_CMT3	SYSTEM.MSTPCRA.BIT.MSTPA14
#define	MSTP_TPU	SYSTEM.MSTPCRA.BIT.MSTPA13
#define	MSTP_TPU0	SYSTEM.MSTPCRA.BIT.MSTPA13
#define	MSTP_TPU1	SYSTEM.MSTPCRA.BIT.MSTPA13
#define	MSTP_TPU2	SYSTEM.MSTPCRA.BIT.MSTPA13
#define	MSTP_TPU3	SYSTEM.MSTPCRA.BIT.MSTPA13
#define	MSTP_TPU4	SYSTEM.MSTPCRA.BIT.MSTPA13
#define	MSTP_TPU5	SYSTEM.MSTPCRA.BIT.MSTPA13
#define	MSTP_MTU	SYSTEM.MSTPCRA.BIT.MSTPA9
#define	MSTP_MTU0	SYSTEM.MSTPCRA.BIT.MSTPA9
#define	MSTP_MTU1	SYSTEM.MSTPCRA.BIT.MSTPA9
#define	MSTP_MTU2	SYSTEM.MSTPCRA.BIT.MSTPA9
#define	MSTP_MTU3	SYSTEM.MSTPCRA.BIT.MSTPA9
#define	MSTP_MTU4	SYSTEM.MSTPCRA.BIT.MSTPA9
#define	MSTP_MTU5	SYSTEM.MSTPCRA.BIT.MSTPA9
#define	MSTP_TMR0	SYSTEM.MSTPCRA.BIT.MSTPA5
#define	MSTP_TMR1	SYSTEM.MSTPCRA.BIT.MSTPA5
#define	MSTP_TMR01	SYSTEM.MSTPCRA.BIT.MSTPA5
#define	MSTP_TMR2	SYSTEM.MSTPCRA.BIT.MSTPA4
#define	MSTP_TMR3	SYSTEM.MSTPCRA.BIT.MSTPA4
#define	MSTP_TMR23	SYSTEM.MSTPCRA.BIT.MSTPA4
#define	MSTP_SCI0	SYSTEM.MSTPCRB.BIT.MSTPB31
#define	MSTP_SMCI0	SYSTEM.MSTPCRB.BIT.MSTPB31
#define	MSTP_SCI1	SYSTEM.MSTPCRB.BIT.MSTPB30
#define	MSTP_SMCI1	SYSTEM.MSTPCRB.BIT.MSTPB30
#define	MSTP_SCI5	SYSTEM.MSTPCRB.BIT.MSTPB26
#define	MSTP_SMCI5	SYSTEM.MSTPCRB.BIT.MSTPB26
#define	MSTP_SCI6	SYSTEM.MSTPCRB.BIT.MSTPB25
#define	MSTP_SMCI6	SYSTEM.MSTPCRB.BIT.MSTPB25
#define	MSTP_CRC	SYSTEM.MSTPCRB.BIT.MSTPB23
#define	MSTP_RIIC0	SYSTEM.MSTPCRB.BIT.MSTPB21
#define	MSTP_USB0	SYSTEM.MSTPCRB.BIT.MSTPB19
#define	MSTP_RSPI0	SYSTEM.MSTPCRB.BIT.MSTPB17
#define	MSTP_CMPB	SYSTEM.MSTPCRB.BIT.MSTPB10
#define	MSTP_ELC	SYSTEM.MSTPCRB.BIT.MSTPB9
#define	MSTP_DOC	SYSTEM.MSTPCRB.BIT.MSTPB6
#define	MSTP_SCI12	SYSTEM.MSTPCRB.BIT.MSTPB4
#define	MSTP_SMCI12	SYSTEM.MSTPCRB.BIT.MSTPB4
#define	MSTP_RSCAN	SYSTEM.MSTPCRB.BIT.MSTPB0
#define	MSTP_RSCAN0	SYSTEM.MSTPCRB.BIT.MSTPB0
#define	MSTP_SCI8	SYSTEM.MSTPCRC.BIT.MSTPC27
#define	MSTP_SMCI8	SYSTEM.MSTPCRC.BIT.MSTPC27
#define	MSTP_SCI9	SYSTEM.MSTPCRC.BIT.MSTPC26
#define	MSTP_SMCI9	SYSTEM.MSTPCRC.BIT.MSTPC26
#define	MSTP_IRDA	SYSTEM.MSTPCRC.BIT.MSTPC20
#define	MSTP_CAC	SYSTEM.MSTPCRC.BIT.MSTPC19
#define	MSTP_RAM0	SYSTEM.MSTPCRC.BIT.MSTPC0
#define	MSTP_TSIP	SYSTEM.MSTPCRD.BIT.MSTPD31
#define	MSTP_SDHI	SYSTEM.MSTPCRD.BIT.MSTPD19
#define	MSTP_SSI0	SYSTEM.MSTPCRD.BIT.MSTPD15
#define	MSTP_CTSU	SYSTEM.MSTPCRD.BIT.MSTPD10

#define	__IR( x )		ICU.IR[ IR ## x ].BIT.IR
#define	 _IR( x )		__IR( x )
#define	  IR( x , y )	_IR( _ ## x ## _ ## y )
#define	__DTCE( x )		ICU.DTCER[ DTCE ## x ].BIT.DTCE
#define	 _DTCE( x )		__DTCE( x )
#define	  DTCE( x , y )	_DTCE( _ ## x ## _ ## y )
#define	__IEN( x )		ICU.IER[ IER ## x ].BIT.IEN ## x
#define	 _IEN( x )		__IEN( x )
#define	  IEN( x , y )	_IEN( _ ## x ## _ ## y )
#define	__IPR( x )		ICU.IPR[ IPR ## x ].BIT.IPR
#define	 _IPR( x )		__IPR( x )
#define	  IPR( x , y )	_IPR( _ ## x ## _ ## y )
#define	__VECT( x )		VECT ## x
#define	 _VECT( x )		__VECT( x )
#define	  VECT( x , y )	_VECT( _ ## x ## _ ## y )
#define	__MSTP( x )		MSTP ## x
#define	 _MSTP( x )		__MSTP( x )
#define	  MSTP( x )		_MSTP( _ ## x )

#define	BSC		(*(volatile struct st_bsc        __evenaccess *)0x81300)
#define	CAC		(*(volatile struct st_cac        __evenaccess *)0x8B000)
#define	CMPB	(*(volatile struct st_cmpb       __evenaccess *)0x8C580)
#define	CMT		(*(volatile struct st_cmt        __evenaccess *)0x88000)
#define	CMT0	(*(volatile struct st_cmt0       __evenaccess *)0x88002)
#define	CMT1	(*(volatile struct st_cmt0       __evenaccess *)0x88008)
#define	CMT2	(*(volatile struct st_cmt0       __evenaccess *)0x88012)
#define	CMT3	(*(volatile struct st_cmt0       __evenaccess *)0x88018)
#define	CRC		(*(volatile struct st_crc        __evenaccess *)0x88280)
#define	CTSU	(*(volatile struct st_ctsu       __evenaccess *)0xA0900)
#define	DA		(*(volatile struct st_da         __evenaccess *)0x88040)
#define	DMAC	(*(volatile struct st_dmac       __evenaccess *)0x82200)
#define	DMAC0	(*(volatile struct st_dmac0      __evenaccess *)0x82000)
#define	DMAC1	(*(volatile struct st_dmac1      __evenaccess *)0x82040)
#define	DMAC2	(*(volatile struct st_dmac1      __evenaccess *)0x82080)
#define	DMAC3	(*(volatile struct st_dmac1      __evenaccess *)0x820C0)
#define	DOC		(*(volatile struct st_doc        __evenaccess *)0x8B080)
#define	DTC		(*(volatile struct st_dtc        __evenaccess *)0x82400)
#define	ELC		(*(volatile struct st_elc        __evenaccess *)0x8B100)
#define	FLASH	(*(volatile struct st_flash      __evenaccess *)0x7FC090)
#define	FLASHCONST		(*(volatile struct st_flashconst __evenaccess *)0x7FC350)
#define	ICU		(*(volatile struct st_icu        __evenaccess *)0x87000)
#define	IRDA	(*(volatile struct st_irda       __evenaccess *)0x88410)
#define	IWDT	(*(volatile struct st_iwdt       __evenaccess *)0x88030)
#define	LPT		(*(volatile struct st_lpt        __evenaccess *)0x800B0)
#define	MPC		(*(volatile struct st_mpc        __evenaccess *)0x8C100)
#define	MPU		(*(volatile struct st_mpu        __evenaccess *)0x86400)
#define	MTU		(*(volatile struct st_mtu        __evenaccess *)0xD0A0A)
#define	MTU0	(*(volatile struct st_mtu0       __evenaccess *)0xD0A90)
#define	MTU1	(*(volatile struct st_mtu1       __evenaccess *)0xD0A90)
#define	MTU2	(*(volatile struct st_mtu2       __evenaccess *)0xD0A92)
#define	MTU3	(*(volatile struct st_mtu3       __evenaccess *)0xD0A00)
#define	MTU4	(*(volatile struct st_mtu4       __evenaccess *)0xD0A00)
#define	MTU5	(*(volatile struct st_mtu5       __evenaccess *)0xD0A94)
#define	POE		(*(volatile struct st_poe        __evenaccess *)0x88900)
#define	PORT	(*(volatile struct st_port       __evenaccess *)0x8C120)
#define	PORT0	(*(volatile struct st_port0      __evenaccess *)0x8C000)
#define	PORT1	(*(volatile struct st_port1      __evenaccess *)0x8C001)
#define	PORT2	(*(volatile struct st_port2      __evenaccess *)0x8C002)
#define	PORT3	(*(volatile struct st_port3      __evenaccess *)0x8C003)
#define	PORT4	(*(volatile struct st_port4      __evenaccess *)0x8C004)
#define	PORT5	(*(volatile struct st_port5      __evenaccess *)0x8C005)
#define	PORTA	(*(volatile struct st_porta      __evenaccess *)0x8C00A)
#define	PORTB	(*(volatile struct st_portb      __evenaccess *)0x8C00B)
#define	PORTC	(*(volatile struct st_portc      __evenaccess *)0x8C00C)
#define	PORTD	(*(volatile struct st_portd      __evenaccess *)0x8C00D)
#define	PORTE	(*(volatile struct st_porte      __evenaccess *)0x8C00E)
#define	PORTH	(*(volatile struct st_porth      __evenaccess *)0x8C011)
#define	PORTJ	(*(volatile struct st_portj      __evenaccess *)0x8C012)
#define	RIIC0	(*(volatile struct st_riic       __evenaccess *)0x88300)
#define	RSCAN	(*(volatile struct st_rscan      __evenaccess *)0xA8322)
#define	RSCAN0	(*(volatile struct st_rscan0     __evenaccess *)0xA8300)
#define	RSPI0	(*(volatile struct st_rspi       __evenaccess *)0x88380)
#define	RTC		(*(volatile struct st_rtc        __evenaccess *)0x8C400)
#define	S12AD	(*(volatile struct st_s12ad      __evenaccess *)0x89000)
#define	SCI0	(*(volatile struct st_sci0       __evenaccess *)0x8A000)
#define	SCI1	(*(volatile struct st_sci0       __evenaccess *)0x8A020)
#define	SCI5	(*(volatile struct st_sci0       __evenaccess *)0x8A0A0)
#define	SCI6	(*(volatile struct st_sci0       __evenaccess *)0x8A0C0)
#define	SCI8	(*(volatile struct st_sci0       __evenaccess *)0x8A100)
#define	SCI9	(*(volatile struct st_sci0       __evenaccess *)0x8A120)
#define	SCI12	(*(volatile struct st_sci12      __evenaccess *)0x8B300)
#define	SDHI	(*(volatile struct st_sdhi       __evenaccess *)0x8AC00)
#define	SMCI0	(*(volatile struct st_smci       __evenaccess *)0x8A000)
#define	SMCI1	(*(volatile struct st_smci       __evenaccess *)0x8A020)
#define	SMCI2	(*(volatile struct st_smci       __evenaccess *)0x8A040)
#define	SMCI3	(*(volatile struct st_smci       __evenaccess *)0x8A060)
#define	SMCI4	(*(volatile struct st_smci       __evenaccess *)0x8A080)
#define	SMCI5	(*(volatile struct st_smci       __evenaccess *)0x8A0A0)
#define	SMCI6	(*(volatile struct st_smci       __evenaccess *)0x8A0C0)
#define	SMCI7	(*(volatile struct st_smci       __evenaccess *)0x8A0E0)
#define	SMCI8	(*(volatile struct st_smci       __evenaccess *)0x8A100)
#define	SMCI9	(*(volatile struct st_smci       __evenaccess *)0x8A120)
#define	SMCI10	(*(volatile struct st_smci       __evenaccess *)0x8A140)
#define	SMCI11	(*(volatile struct st_smci       __evenaccess *)0x8A150)
#define	SMCI12	(*(volatile struct st_smci       __evenaccess *)0x8B300)
#define	SSI0	(*(volatile struct st_ssi        __evenaccess *)0x8A500)
#define	SYSTEM	(*(volatile struct st_system     __evenaccess *)0x80000)
#define	TEMPSCONST		(*(volatile struct st_tempsconst __evenaccess *)0x7FC0AC)
#define	TMR0	(*(volatile struct st_tmr0       __evenaccess *)0x88200)
#define	TMR1	(*(volatile struct st_tmr1       __evenaccess *)0x88201)
#define	TMR2	(*(volatile struct st_tmr0       __evenaccess *)0x88210)
#define	TMR3	(*(volatile struct st_tmr1       __evenaccess *)0x88211)
#define	TMR01	(*(volatile struct st_tmr01      __evenaccess *)0x88204)
#define	TMR23	(*(volatile struct st_tmr01      __evenaccess *)0x88214)
#define	TPU		(*(volatile struct st_tpu        __evenaccess *)0x88100)
#define	TPU0	(*(volatile struct st_tpu0       __evenaccess *)0x88108)
#define	TPU1	(*(volatile struct st_tpu1       __evenaccess *)0x88108)
#define	TPU2	(*(volatile struct st_tpu2       __evenaccess *)0x8810A)
#define	TPU3	(*(volatile struct st_tpu3       __evenaccess *)0x8810A)
#define	TPU4	(*(volatile struct st_tpu4       __evenaccess *)0x8810C)
#define	TPU5	(*(volatile struct st_tpu5       __evenaccess *)0x8810C)
#define	USB0	(*(volatile struct st_usb0       __evenaccess *)0xA0000)
#define	WDT		(*(volatile struct st_wdt        __evenaccess *)0x88020)
#pragma bit_order
#pragma packoption
#endif
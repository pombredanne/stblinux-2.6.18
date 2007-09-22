/* header auto-generated by pidl */

#include "librpc/gen_ndr/srvsvc.h"

#ifndef _HEADER_NDR_srvsvc
#define _HEADER_NDR_srvsvc

#include "librpc/ndr/libndr.h"
#define DCERPC_SRVSVC_UUID "4b324fc8-1670-01d3-1278-5a47bf6ee188"
#define DCERPC_SRVSVC_VERSION 3.0
#define DCERPC_SRVSVC_NAME "srvsvc"
#define DCERPC_SRVSVC_HELPSTRING "Server Service"
extern const struct dcerpc_interface_table dcerpc_table_srvsvc;
NTSTATUS dcerpc_server_srvsvc_init(void);
#define DCERPC_SRVSVC_NETCHARDEVENUM (0x00)

#define DCERPC_SRVSVC_NETCHARDEVGETINFO (0x01)

#define DCERPC_SRVSVC_NETCHARDEVCONTROL (0x02)

#define DCERPC_SRVSVC_NETCHARDEVQENUM (0x03)

#define DCERPC_SRVSVC_NETCHARDEVQGETINFO (0x04)

#define DCERPC_SRVSVC_NETCHARDEVQSETINFO (0x05)

#define DCERPC_SRVSVC_NETCHARDEVQPURGE (0x06)

#define DCERPC_SRVSVC_NETCHARDEVQPURGESELF (0x07)

#define DCERPC_SRVSVC_NETCONNENUM (0x08)

#define DCERPC_SRVSVC_NETFILEENUM (0x09)

#define DCERPC_SRVSVC_NETFILEGETINFO (0x0a)

#define DCERPC_SRVSVC_NETFILECLOSE (0x0b)

#define DCERPC_SRVSVC_NETSESSENUM (0x0c)

#define DCERPC_SRVSVC_NETSESSDEL (0x0d)

#define DCERPC_SRVSVC_NETSHAREADD (0x0e)

#define DCERPC_SRVSVC_NETSHAREENUMALL (0x0f)

#define DCERPC_SRVSVC_NETSHAREGETINFO (0x10)

#define DCERPC_SRVSVC_NETSHARESETINFO (0x11)

#define DCERPC_SRVSVC_NETSHAREDEL (0x12)

#define DCERPC_SRVSVC_NETSHAREDELSTICKY (0x13)

#define DCERPC_SRVSVC_NETSHARECHECK (0x14)

#define DCERPC_SRVSVC_NETSRVGETINFO (0x15)

#define DCERPC_SRVSVC_NETSRVSETINFO (0x16)

#define DCERPC_SRVSVC_NETDISKENUM (0x17)

#define DCERPC_SRVSVC_NETSERVERSTATISTICSGET (0x18)

#define DCERPC_SRVSVC_NETTRANSPORTADD (0x19)

#define DCERPC_SRVSVC_NETTRANSPORTENUM (0x1a)

#define DCERPC_SRVSVC_NETTRANSPORTDEL (0x1b)

#define DCERPC_SRVSVC_NETREMOTETOD (0x1c)

#define DCERPC_SRVSVC_NETSETSERVICEBITS (0x1d)

#define DCERPC_SRVSVC_NETPATHTYPE (0x1e)

#define DCERPC_SRVSVC_NETPATHCANONICALIZE (0x1f)

#define DCERPC_SRVSVC_NETPATHCOMPARE (0x20)

#define DCERPC_SRVSVC_NETNAMEVALIDATE (0x21)

#define DCERPC_SRVSVC_NETRPRNAMECANONICALIZE (0x22)

#define DCERPC_SRVSVC_NETPRNAMECOMPARE (0x23)

#define DCERPC_SRVSVC_NETSHAREENUM (0x24)

#define DCERPC_SRVSVC_NETSHAREDELSTART (0x25)

#define DCERPC_SRVSVC_NETSHAREDELCOMMIT (0x26)

#define DCERPC_SRVSVC_NETGETFILESECURITY (0x27)

#define DCERPC_SRVSVC_NETSETFILESECURITY (0x28)

#define DCERPC_SRVSVC_NETSERVERTRANSPORTADDEX (0x29)

#define DCERPC_SRVSVC_NETSERVERSETSERVICEBITSEX (0x2a)

#define DCERPC_SRVSVC_NETRDFSGETVERSION (0x2b)

#define DCERPC_SRVSVC_NETRDFSCREATELOCALPARTITION (0x2c)

#define DCERPC_SRVSVC_NETRDFSDELETELOCALPARTITION (0x2d)

#define DCERPC_SRVSVC_NETRDFSSETLOCALVOLUMESTATE (0x2e)

#define DCERPC_SRVSVC_NETRDFSSETSERVERINFO (0x2f)

#define DCERPC_SRVSVC_NETRDFSCREATEEXITPOINT (0x30)

#define DCERPC_SRVSVC_NETRDFSDELETEEXITPOINT (0x31)

#define DCERPC_SRVSVC_NETRDFSMODIFYPREFIX (0x32)

#define DCERPC_SRVSVC_NETRDFSFIXLOCALVOLUME (0x33)

#define DCERPC_SRVSVC_NETRDFSMANAGERREPORTSITEINFO (0x34)

#define DCERPC_SRVSVC_NETRSERVERTRANSPORTDELEX (0x35)

#define DCERPC_SRVSVC_CALL_COUNT (54)
void ndr_print_srvsvc_NetCharDevInfo0(struct ndr_print *ndr, const char *name, const struct srvsvc_NetCharDevInfo0 *r);
void ndr_print_srvsvc_NetCharDevCtr0(struct ndr_print *ndr, const char *name, const struct srvsvc_NetCharDevCtr0 *r);
void ndr_print_srvsvc_NetCharDevInfo1(struct ndr_print *ndr, const char *name, const struct srvsvc_NetCharDevInfo1 *r);
void ndr_print_srvsvc_NetCharDevCtr1(struct ndr_print *ndr, const char *name, const struct srvsvc_NetCharDevCtr1 *r);
void ndr_print_srvsvc_NetCharDevInfo(struct ndr_print *ndr, const char *name, const union srvsvc_NetCharDevInfo *r);
void ndr_print_srvsvc_NetCharDevCtr(struct ndr_print *ndr, const char *name, const union srvsvc_NetCharDevCtr *r);
void ndr_print_srvsvc_NetCharDevQInfo0(struct ndr_print *ndr, const char *name, const struct srvsvc_NetCharDevQInfo0 *r);
void ndr_print_srvsvc_NetCharDevQCtr0(struct ndr_print *ndr, const char *name, const struct srvsvc_NetCharDevQCtr0 *r);
void ndr_print_srvsvc_NetCharDevQInfo1(struct ndr_print *ndr, const char *name, const struct srvsvc_NetCharDevQInfo1 *r);
void ndr_print_srvsvc_NetCharDevQCtr1(struct ndr_print *ndr, const char *name, const struct srvsvc_NetCharDevQCtr1 *r);
void ndr_print_srvsvc_NetCharDevQInfo(struct ndr_print *ndr, const char *name, const union srvsvc_NetCharDevQInfo *r);
void ndr_print_srvsvc_NetCharDevQCtr(struct ndr_print *ndr, const char *name, const union srvsvc_NetCharDevQCtr *r);
void ndr_print_srvsvc_NetConnInfo0(struct ndr_print *ndr, const char *name, const struct srvsvc_NetConnInfo0 *r);
void ndr_print_srvsvc_NetConnCtr0(struct ndr_print *ndr, const char *name, const struct srvsvc_NetConnCtr0 *r);
void ndr_print_srvsvc_NetConnInfo1(struct ndr_print *ndr, const char *name, const struct srvsvc_NetConnInfo1 *r);
void ndr_print_srvsvc_NetConnCtr1(struct ndr_print *ndr, const char *name, const struct srvsvc_NetConnCtr1 *r);
void ndr_print_srvsvc_NetConnCtr(struct ndr_print *ndr, const char *name, const union srvsvc_NetConnCtr *r);
void ndr_print_srvsvc_NetFileInfo2(struct ndr_print *ndr, const char *name, const struct srvsvc_NetFileInfo2 *r);
void ndr_print_srvsvc_NetFileCtr2(struct ndr_print *ndr, const char *name, const struct srvsvc_NetFileCtr2 *r);
void ndr_print_srvsvc_NetFileInfo3(struct ndr_print *ndr, const char *name, const struct srvsvc_NetFileInfo3 *r);
void ndr_print_srvsvc_NetFileCtr3(struct ndr_print *ndr, const char *name, const struct srvsvc_NetFileCtr3 *r);
void ndr_print_srvsvc_NetFileInfo(struct ndr_print *ndr, const char *name, const union srvsvc_NetFileInfo *r);
void ndr_print_srvsvc_NetFileCtr(struct ndr_print *ndr, const char *name, const union srvsvc_NetFileCtr *r);
void ndr_print_srvsvc_NetSessInfo0(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSessInfo0 *r);
void ndr_print_srvsvc_NetSessCtr0(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSessCtr0 *r);
void ndr_print_srvsvc_NetSessInfo1(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSessInfo1 *r);
void ndr_print_srvsvc_NetSessCtr1(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSessCtr1 *r);
void ndr_print_srvsvc_NetSessInfo2(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSessInfo2 *r);
void ndr_print_srvsvc_NetSessCtr2(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSessCtr2 *r);
void ndr_print_srvsvc_NetSessInfo10(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSessInfo10 *r);
void ndr_print_srvsvc_NetSessCtr10(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSessCtr10 *r);
void ndr_print_srvsvc_NetSessInfo502(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSessInfo502 *r);
void ndr_print_srvsvc_NetSessCtr502(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSessCtr502 *r);
void ndr_print_srvsvc_NetSessCtr(struct ndr_print *ndr, const char *name, const union srvsvc_NetSessCtr *r);
void ndr_print_srvsvc_ShareType(struct ndr_print *ndr, const char *name, enum srvsvc_ShareType r);
void ndr_print_srvsvc_NetShareInfo0(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareInfo0 *r);
void ndr_print_srvsvc_NetShareCtr0(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareCtr0 *r);
void ndr_print_srvsvc_NetShareInfo1(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareInfo1 *r);
void ndr_print_srvsvc_NetShareCtr1(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareCtr1 *r);
void ndr_print_srvsvc_NetShareInfo2(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareInfo2 *r);
void ndr_print_srvsvc_NetShareCtr2(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareCtr2 *r);
void ndr_print_srvsvc_NetShareInfo501(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareInfo501 *r);
void ndr_print_srvsvc_NetShareCtr501(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareCtr501 *r);
void ndr_print_srvsvc_NetShareInfo502(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareInfo502 *r);
void ndr_print_srvsvc_NetShareCtr502(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareCtr502 *r);
void ndr_print_srvsvc_NetShareInfo1004(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareInfo1004 *r);
void ndr_print_srvsvc_NetShareCtr1004(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareCtr1004 *r);
void ndr_print_NetShareInfo1005Flags(struct ndr_print *ndr, const char *name, uint32_t r);
void ndr_print_srvsvc_NetShareInfo1005(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareInfo1005 *r);
void ndr_print_srvsvc_NetShareCtr1005(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareCtr1005 *r);
void ndr_print_srvsvc_NetShareInfo1006(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareInfo1006 *r);
void ndr_print_srvsvc_NetShareCtr1006(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareCtr1006 *r);
void ndr_print_srvsvc_NetShareInfo1007(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareInfo1007 *r);
void ndr_print_srvsvc_NetShareCtr1007(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareCtr1007 *r);
void ndr_print_srvsvc_NetShareCtr1501(struct ndr_print *ndr, const char *name, const struct srvsvc_NetShareCtr1501 *r);
void ndr_print_srvsvc_NetShareInfo(struct ndr_print *ndr, const char *name, const union srvsvc_NetShareInfo *r);
void ndr_print_srvsvc_NetShareCtr(struct ndr_print *ndr, const char *name, const union srvsvc_NetShareCtr *r);
NTSTATUS ndr_push_srvsvc_PlatformId(struct ndr_push *ndr, int ndr_flags, enum srvsvc_PlatformId r);
NTSTATUS ndr_pull_srvsvc_PlatformId(struct ndr_pull *ndr, int ndr_flags, enum srvsvc_PlatformId *r);
void ndr_print_srvsvc_PlatformId(struct ndr_print *ndr, const char *name, enum srvsvc_PlatformId r);
void ndr_print_srvsvc_NetSrvInfo100(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo100 *r);
void ndr_print_srvsvc_NetSrvInfo101(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo101 *r);
void ndr_print_srvsvc_NetSrvInfo102(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo102 *r);
void ndr_print_srvsvc_NetSrvInfo402(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo402 *r);
void ndr_print_srvsvc_NetSrvInfo403(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo403 *r);
void ndr_print_srvsvc_NetSrvInfo502(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo502 *r);
void ndr_print_srvsvc_NetSrvInfo503(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo503 *r);
void ndr_print_srvsvc_NetSrvInfo599(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo599 *r);
void ndr_print_srvsvc_NetSrvInfo1005(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1005 *r);
void ndr_print_srvsvc_NetSrvInfo1010(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1010 *r);
void ndr_print_srvsvc_NetSrvInfo1016(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1016 *r);
void ndr_print_srvsvc_NetSrvInfo1017(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1017 *r);
void ndr_print_srvsvc_NetSrvInfo1018(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1018 *r);
void ndr_print_srvsvc_NetSrvInfo1107(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1107 *r);
void ndr_print_srvsvc_NetSrvInfo1501(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1501 *r);
void ndr_print_srvsvc_NetSrvInfo1502(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1502 *r);
void ndr_print_srvsvc_NetSrvInfo1503(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1503 *r);
void ndr_print_srvsvc_NetSrvInfo1506(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1506 *r);
void ndr_print_srvsvc_NetSrvInfo1509(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1509 *r);
void ndr_print_srvsvc_NetSrvInfo1510(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1510 *r);
void ndr_print_srvsvc_NetSrvInfo1511(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1511 *r);
void ndr_print_srvsvc_NetSrvInfo1512(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1512 *r);
void ndr_print_srvsvc_NetSrvInfo1513(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1513 *r);
void ndr_print_srvsvc_NetSrvInfo1514(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1514 *r);
void ndr_print_srvsvc_NetSrvInfo1515(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1515 *r);
void ndr_print_srvsvc_NetSrvInfo1516(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1516 *r);
void ndr_print_srvsvc_NetSrvInfo1518(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1518 *r);
void ndr_print_srvsvc_NetSrvInfo1520(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1520 *r);
void ndr_print_srvsvc_NetSrvInfo1521(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1521 *r);
void ndr_print_srvsvc_NetSrvInfo1522(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1522 *r);
void ndr_print_srvsvc_NetSrvInfo1523(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1523 *r);
void ndr_print_srvsvc_NetSrvInfo1524(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1524 *r);
void ndr_print_srvsvc_NetSrvInfo1525(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1525 *r);
void ndr_print_srvsvc_NetSrvInfo1528(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1528 *r);
void ndr_print_srvsvc_NetSrvInfo1529(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1529 *r);
void ndr_print_srvsvc_NetSrvInfo1530(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1530 *r);
void ndr_print_srvsvc_NetSrvInfo1533(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1533 *r);
void ndr_print_srvsvc_NetSrvInfo1534(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1534 *r);
void ndr_print_srvsvc_NetSrvInfo1535(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1535 *r);
void ndr_print_srvsvc_NetSrvInfo1536(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1536 *r);
void ndr_print_srvsvc_NetSrvInfo1537(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1537 *r);
void ndr_print_srvsvc_NetSrvInfo1538(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1538 *r);
void ndr_print_srvsvc_NetSrvInfo1539(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1539 *r);
void ndr_print_srvsvc_NetSrvInfo1540(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1540 *r);
void ndr_print_srvsvc_NetSrvInfo1541(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1541 *r);
void ndr_print_srvsvc_NetSrvInfo1542(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1542 *r);
void ndr_print_srvsvc_NetSrvInfo1543(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1543 *r);
void ndr_print_srvsvc_NetSrvInfo1544(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1544 *r);
void ndr_print_srvsvc_NetSrvInfo1545(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1545 *r);
void ndr_print_srvsvc_NetSrvInfo1546(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1546 *r);
void ndr_print_srvsvc_NetSrvInfo1547(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1547 *r);
void ndr_print_srvsvc_NetSrvInfo1548(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1548 *r);
void ndr_print_srvsvc_NetSrvInfo1549(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1549 *r);
void ndr_print_srvsvc_NetSrvInfo1550(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1550 *r);
void ndr_print_srvsvc_NetSrvInfo1552(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1552 *r);
void ndr_print_srvsvc_NetSrvInfo1553(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1553 *r);
void ndr_print_srvsvc_NetSrvInfo1554(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1554 *r);
void ndr_print_srvsvc_NetSrvInfo1555(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1555 *r);
void ndr_print_srvsvc_NetSrvInfo1556(struct ndr_print *ndr, const char *name, const struct srvsvc_NetSrvInfo1556 *r);
void ndr_print_srvsvc_NetSrvInfo(struct ndr_print *ndr, const char *name, const union srvsvc_NetSrvInfo *r);
void ndr_print_srvsvc_NetDiskInfo0(struct ndr_print *ndr, const char *name, const struct srvsvc_NetDiskInfo0 *r);
void ndr_print_srvsvc_NetDiskInfo(struct ndr_print *ndr, const char *name, const struct srvsvc_NetDiskInfo *r);
void ndr_print_srvsvc_Statistics(struct ndr_print *ndr, const char *name, const struct srvsvc_Statistics *r);
void ndr_print_srvsvc_NetTransportInfo0(struct ndr_print *ndr, const char *name, const struct srvsvc_NetTransportInfo0 *r);
void ndr_print_srvsvc_NetTransportCtr0(struct ndr_print *ndr, const char *name, const struct srvsvc_NetTransportCtr0 *r);
void ndr_print_srvsvc_NetTransportInfo1(struct ndr_print *ndr, const char *name, const struct srvsvc_NetTransportInfo1 *r);
void ndr_print_srvsvc_NetTransportCtr1(struct ndr_print *ndr, const char *name, const struct srvsvc_NetTransportCtr1 *r);
void ndr_print_srvsvc_NetTransportInfo2(struct ndr_print *ndr, const char *name, const struct srvsvc_NetTransportInfo2 *r);
void ndr_print_srvsvc_NetTransportCtr2(struct ndr_print *ndr, const char *name, const struct srvsvc_NetTransportCtr2 *r);
void ndr_print_srvsvc_NetTransportInfo3(struct ndr_print *ndr, const char *name, const struct srvsvc_NetTransportInfo3 *r);
void ndr_print_srvsvc_NetTransportCtr3(struct ndr_print *ndr, const char *name, const struct srvsvc_NetTransportCtr3 *r);
void ndr_print_srvsvc_NetTransportCtr(struct ndr_print *ndr, const char *name, const union srvsvc_NetTransportCtr *r);
void ndr_print_srvsvc_NetRemoteTODInfo(struct ndr_print *ndr, const char *name, const struct srvsvc_NetRemoteTODInfo *r);
void ndr_print_srvsvc_NetTransportInfo(struct ndr_print *ndr, const char *name, const union srvsvc_NetTransportInfo *r);
void ndr_print_srvsvc_NetCharDevEnum(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetCharDevEnum *r);
void ndr_print_srvsvc_NetCharDevGetInfo(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetCharDevGetInfo *r);
void ndr_print_srvsvc_NetCharDevControl(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetCharDevControl *r);
void ndr_print_srvsvc_NetCharDevQEnum(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetCharDevQEnum *r);
void ndr_print_srvsvc_NetCharDevQGetInfo(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetCharDevQGetInfo *r);
void ndr_print_srvsvc_NetCharDevQSetInfo(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetCharDevQSetInfo *r);
void ndr_print_srvsvc_NetCharDevQPurge(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetCharDevQPurge *r);
void ndr_print_srvsvc_NetCharDevQPurgeSelf(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetCharDevQPurgeSelf *r);
void ndr_print_srvsvc_NetConnEnum(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetConnEnum *r);
void ndr_print_srvsvc_NetFileEnum(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetFileEnum *r);
void ndr_print_srvsvc_NetFileGetInfo(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetFileGetInfo *r);
void ndr_print_srvsvc_NetFileClose(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetFileClose *r);
void ndr_print_srvsvc_NetSessEnum(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetSessEnum *r);
void ndr_print_srvsvc_NetSessDel(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetSessDel *r);
void ndr_print_srvsvc_NetShareAdd(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetShareAdd *r);
void ndr_print_srvsvc_NetShareEnumAll(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetShareEnumAll *r);
void ndr_print_srvsvc_NetShareGetInfo(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetShareGetInfo *r);
void ndr_print_srvsvc_NetShareSetInfo(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetShareSetInfo *r);
void ndr_print_srvsvc_NetShareDel(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetShareDel *r);
void ndr_print_srvsvc_NetShareDelSticky(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetShareDelSticky *r);
void ndr_print_srvsvc_NetShareCheck(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetShareCheck *r);
void ndr_print_srvsvc_NetSrvGetInfo(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetSrvGetInfo *r);
void ndr_print_srvsvc_NetSrvSetInfo(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetSrvSetInfo *r);
void ndr_print_srvsvc_NetDiskEnum(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetDiskEnum *r);
void ndr_print_srvsvc_NetServerStatisticsGet(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetServerStatisticsGet *r);
void ndr_print_srvsvc_NetTransportAdd(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetTransportAdd *r);
void ndr_print_srvsvc_NetTransportEnum(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetTransportEnum *r);
void ndr_print_srvsvc_NetTransportDel(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetTransportDel *r);
void ndr_print_srvsvc_NetRemoteTOD(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetRemoteTOD *r);
void ndr_print_srvsvc_NetSetServiceBits(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetSetServiceBits *r);
void ndr_print_srvsvc_NetPathType(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetPathType *r);
void ndr_print_srvsvc_NetPathCanonicalize(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetPathCanonicalize *r);
void ndr_print_srvsvc_NetPathCompare(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetPathCompare *r);
void ndr_print_srvsvc_NetNameValidate(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetNameValidate *r);
void ndr_print_srvsvc_NETRPRNAMECANONICALIZE(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NETRPRNAMECANONICALIZE *r);
void ndr_print_srvsvc_NetPRNameCompare(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetPRNameCompare *r);
void ndr_print_srvsvc_NetShareEnum(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetShareEnum *r);
void ndr_print_srvsvc_NetShareDelStart(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetShareDelStart *r);
void ndr_print_srvsvc_NetShareDelCommit(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetShareDelCommit *r);
void ndr_print_srvsvc_NetGetFileSecurity(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetGetFileSecurity *r);
void ndr_print_srvsvc_NetSetFileSecurity(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetSetFileSecurity *r);
void ndr_print_srvsvc_NetServerTransportAddEx(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetServerTransportAddEx *r);
void ndr_print_srvsvc_NetServerSetServiceBitsEx(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NetServerSetServiceBitsEx *r);
void ndr_print_srvsvc_NETRDFSGETVERSION(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NETRDFSGETVERSION *r);
void ndr_print_srvsvc_NETRDFSCREATELOCALPARTITION(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NETRDFSCREATELOCALPARTITION *r);
void ndr_print_srvsvc_NETRDFSDELETELOCALPARTITION(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NETRDFSDELETELOCALPARTITION *r);
void ndr_print_srvsvc_NETRDFSSETLOCALVOLUMESTATE(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NETRDFSSETLOCALVOLUMESTATE *r);
void ndr_print_srvsvc_NETRDFSSETSERVERINFO(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NETRDFSSETSERVERINFO *r);
void ndr_print_srvsvc_NETRDFSCREATEEXITPOINT(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NETRDFSCREATEEXITPOINT *r);
void ndr_print_srvsvc_NETRDFSDELETEEXITPOINT(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NETRDFSDELETEEXITPOINT *r);
void ndr_print_srvsvc_NETRDFSMODIFYPREFIX(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NETRDFSMODIFYPREFIX *r);
void ndr_print_srvsvc_NETRDFSFIXLOCALVOLUME(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NETRDFSFIXLOCALVOLUME *r);
void ndr_print_srvsvc_NETRDFSMANAGERREPORTSITEINFO(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NETRDFSMANAGERREPORTSITEINFO *r);
void ndr_print_srvsvc_NETRSERVERTRANSPORTDELEX(struct ndr_print *ndr, const char *name, int flags, const struct srvsvc_NETRSERVERTRANSPORTDELEX *r);
#endif /* _HEADER_NDR_srvsvc */

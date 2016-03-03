/**
 * Copyright (C) 2015,  Netronome Systems, Inc.  All rights reserved.
 *
 * @file          nfd_user_cfg.h
 * @brief         File for specifying user configuration parameters
 */
#ifndef _NFD_USER_CFG_H_
#define _NFD_USER_CFG_H_

/* Include BLM defines for BLM_NBI8_BLQ0_EMU_Q_BASE */
#if !defined(__NFP_LANG_ASM)
#include <blm/blm.h>
#endif

#ifndef NFD_MAX_VF_QUEUES
#define NFD_MAX_VF_QUEUES       1
#endif

#ifndef NFD_MAX_PF_QUEUES
#define NFD_MAX_PF_QUEUES       32
#endif

/* No VFs needed */
#ifndef NFD_MAX_VFS
#define NFD_MAX_VFS             0
#endif

/* Configure VF expansion BARs to access the NFP, this seems to be required
 * even when just using the PF */
#define NFD_VNIC_VF

/* Use a service ME which will handle MSIX generation when enabled */
#define USE_SVC_ME

#define NFD_PCIE0_EMEM          emem0

#define NFD_IN_DATA_OFFSET      64

#define NFD_OUT_3_PD_MES        1

/* Number of credits allocated per VNIC queue */
#ifndef NFD_QUEUE_CREDITS
#define NFD_QUEUE_CREDITS       256
#endif

/* Configuration mechanism defines */
#define NFD_CFG_MAX_MTU         9216

#define NFD_CFG_VF_CAP                                          \
    (NFP_NET_CFG_CTRL_ENABLE | NFP_NET_CFG_CTRL_PROMISC |       \
     NFP_NET_CFG_CTRL_L2BC | NFP_NET_CFG_CTRL_L2MC |            \
     NFP_NET_CFG_CTRL_RXCSUM | NFP_NET_CFG_CTRL_TXCSUM |        \
     NFP_NET_CFG_CTRL_RXVLAN | NFP_NET_CFG_CTRL_TXVLAN |        \
     NFP_NET_CFG_CTRL_RSS    | NFP_NET_CFG_CTRL_MSIXAUTO |      \
     NFP_NET_CFG_CTRL_L2SWITCH | NFP_NET_CFG_CTRL_GATHER |      \
     NFP_NET_CFG_CTRL_IRQMOD | NFP_NET_CFG_CTRL_LSO |           \
     NFP_NET_CFG_CTRL_VXLAN  | NFP_NET_CFG_CTRL_NVGRE)

#define NFD_CFG_PF_CAP                                          \
    (NFP_NET_CFG_CTRL_ENABLE | NFP_NET_CFG_CTRL_PROMISC |       \
     NFP_NET_CFG_CTRL_L2BC | NFP_NET_CFG_CTRL_L2MC |            \
     NFP_NET_CFG_CTRL_RXCSUM | NFP_NET_CFG_CTRL_TXCSUM |        \
     NFP_NET_CFG_CTRL_RXVLAN | NFP_NET_CFG_CTRL_TXVLAN |        \
     NFP_NET_CFG_CTRL_RSS    | NFP_NET_CFG_CTRL_MSIXAUTO |      \
     NFP_NET_CFG_CTRL_L2SWITCH | NFP_NET_CFG_CTRL_GATHER |      \
     NFP_NET_CFG_CTRL_IRQMOD | NFP_NET_CFG_CTRL_LSO |           \
     NFP_NET_CFG_CTRL_VXLAN  | NFP_NET_CFG_CTRL_NVGRE)

#define NFD_CFG_RING_EMEM       emem0

/* Signal number used for APP MASTER to NIC APP MEs signaling of
 * configuration changes to the config BAR */
#define APP_ME_CONFIG_SIGNAL_NUM 11
/* Xfer number used for APP MASTER to NIC APP MEs signaling of
 * configuration changes to the config BAR - holds pci island and
 * vnic number */
#define APP_ME_CONFIG_XFER_NUM 11


/* PCI.IN block defines */
#define NFD_IN_BLM_REG_BLS      0
#define NFD_IN_BLM_REG_POOL     BLM_NBI8_BLQ0_EMU_QID
#define NFD_IN_BLM_REG_SIZE     (10 * 1024)
#define NFD_IN_BLM_JUMBO_BLS    0
#define NFD_IN_BLM_JUMBO_POOL   BLM_NBI8_BLQ0_EMU_QID
#define NFD_IN_BLM_RADDR        __LoadTimeConstant("__addr_emem0")
#define NFD_IN_HAS_ISSUE0       1
#define NFD_IN_HAS_ISSUE1       1
#define NFD_IN_ISSUE_DMA_QSHIFT 1
#define NFD_IN_ISSUE_DMA_QXOR   0

/* NFD_IN_WQ_SZ must be large enough to hold an nfd_in_pkt_desc (16B) for each
 * MU in the system. BLM_NBI8_BLQ0_Q_SIZE is the max number of MUs in the
 * system * MU descr size (4B). So NFD_IN_WQ_SZ = (BLM_NBI8_BLQ0_Q_SIZE/4)*16
 */
#define NFD_IN_WQ_SZ           ((BLM_NBI8_BLQ0_Q_SIZE/4) * 16)

/* Optional defines */
#define NFD_IN_ADD_SEQN
#define NFD_IN_NUM_WQS          8

/* PCI.OUT block defines */
#define NFD_OUT_BLM_POOL_START  BLM_NBI8_BLQ0_EMU_QID
#define NFD_OUT_BLM_RADDR       __LoadTimeConstant("__addr_emem0")
#define NFD_OUT_BLM_RADDR_UC    __ADDR_EMEM0

/* Set either NFP_CACHED or HOST_ISSUED credits
 * Only NFP_CACHED are officially supported currently */
/* #define NFD_OUT_CREDITS_HOST_ISSUED */
#define NFD_OUT_CREDITS_NFP_CACHED

/* NFD_OUT_RING_SZ must be set to hold double the maximum number of credits
 * that might be issued at any time. */
#define NFD_OUT_RING_SZ         (2 * 16 * 64 * NFD_QUEUE_CREDITS)

#define NFD_OUT_RX_OFFSET       NFP_NET_RX_OFFSET

#endif /* !_NFD_USER_CFG_H_ */
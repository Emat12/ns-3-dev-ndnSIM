/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2006 INRIA
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */
#ifndef ARP_H
#define ARP_H

#include <list>
#include "ipv4-address.h"
#include "mac-address.h"
#include "l3-protocol.h"

namespace ns3 {

class ArpCache;
class NetDevice;
class Node;
class Packet;
class TraceResolver;
class TraceContext;

class Arp : public L3Protocol
{
public:
  static const uint16_t PROT_NUMBER;

  Arp (Node *node);
  ~Arp ();
  virtual Arp *Copy (Node *node) const;

  virtual void Dispose (void);

  virtual TraceResolver *CreateTraceResolver (TraceContext const &context);

  virtual void Receive(Packet& p, NetDevice *device);
  bool Lookup (Packet &p, Ipv4Address destination, 
	       NetDevice *device,
	       MacAddress *hardwareDestination);
private:
  typedef std::list<ArpCache *> CacheList;
  ArpCache *FindCache (NetDevice *device);
  void SendArpRequest (ArpCache const *cache, Ipv4Address to);
  void SendArpReply (ArpCache const *cache, Ipv4Address toIp, MacAddress toMac);
  CacheList m_cacheList;
  Node *m_node;
};

}//namespace ns3


#endif /* ARP_H */

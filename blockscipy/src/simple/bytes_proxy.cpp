//
//  uint256_proxy.cpp
//  blocksci
//
//  Created by Harry Kalodner on 9/22/18.
//
//

#include "simple_proxies.hpp"
#include "proxy/range.hpp"
#include "proxy/basic.hpp"
#include "proxy/optional.hpp"

#include <blocksci/chain/block.hpp>
#include <blocksci/cluster/cluster.hpp>
#include <blocksci/address/equiv_address.hpp>

void addBytesProxyMethods(AllProxyClasses<pybind11::bytes> &cls) {
	cls.setupBasicProxy(AddProxyMethods{});
	cls.optional.applyToAll(AddProxyOptionalMethods{});
}
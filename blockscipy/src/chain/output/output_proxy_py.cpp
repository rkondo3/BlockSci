//
//  output_proxy_py.cpp
//  blocksci
//
//  Created by Harry Kalodner on 9/22/18.
//
//

#include "output_proxy_py.hpp"
#include "output_py.hpp"
#include "proxy_apply_py.hpp"
#include "proxy/equality.hpp"
#include "proxy/comparison.hpp"
#include "proxy/optional.hpp"

#include <blocksci/chain/block.hpp>
#include <blocksci/cluster/cluster.hpp>

struct AddOutputProxyMethods {
	void operator()(pybind11::class_<Proxy<blocksci::Output>> &cl) {
		applyMethodsToProxy(cl, AddOutputMethods{});
	}
};

void addOutputProxyMethods(AllProxyClasses<blocksci::Output> &cls) {
	addOutputProxyMethodsMain(cls);
	addOutputProxyMethodsRange(cls);
	addOutputProxyMethodsRangeMap(cls);
	addOutputProxyMethodsRangeMapOptional(cls);
	addOutputProxyMethodsRangeMapSequence(cls);
	cls.optional.applyToAll(AddProxyOptionalMethods{});
	cls.optional.applyToAll(AddProxyOptionalMapMethods{});

	cls.base.applyToAll(AddOutputProxyMethods{});
	cls.base.applyToAll(AddProxyEqualityMethods{});
	cls.base.applyToAll(AddProxyComparisonMethods{});
}

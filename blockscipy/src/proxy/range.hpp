//
//  range.hpp
//  blocksci_interface
//
//  Created by Harry Kalodner on 9/23/18.
//


#ifndef proxy_range_hpp
#define proxy_range_hpp

#include "proxy_py.hpp"
#include "proxy_utils.hpp"

#include <range/v3/view/filter.hpp>
#include <range/v3/view/stride.hpp>
#include <range/v3/view/slice.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/size.hpp>
#include <range/v3/distance.hpp>

struct AddProxySequenceMethods {
	template<typename T, ranges::category range_cat>
	void operator()(pybind11::class_<Proxy<ranges::any_view<T, range_cat>>> &cl) {
		using R = ranges::any_view<T, range_cat>;
		using P = Proxy<R>;

		cl
		.def("any", [](P &p, Proxy<bool> &p2) -> Proxy<bool> {
			return lift(p, [=](ranges::any_view<T, range_cat> && val) -> bool {
				return ranges::any_of(val, [=](std::any item) {
					return p2(item);
				});
			});
		})
		.def("all", [](P &p, Proxy<bool> &p2) -> Proxy<bool> {
			return lift(p, [=](ranges::any_view<T, range_cat> && val) -> bool {
				return ranges::all_of(val, [=](std::any item) {
					return p2(item);
				});
			});
		})
		.def_property_readonly("size", [](P &p) -> Proxy<int64_t> {
			return lift(p, [](ranges::any_view<ranges::optional<T>, range_cat> &&r) -> int64_t {
				return ranges::distance(r);
			});
		})
		.def("where", [](P &p, Proxy<bool> &p2) -> Proxy<ranges::any_view<T>> {
			return lift(p, [=](ranges::any_view<T, range_cat> && range) -> ranges::any_view<T> {
				return range | ranges::view::filter([=](T item) {
					return p2(std::move(item));
				});
			});
		})
	    .def_property_readonly_static("nested_proxy", [](pybind11::object &) -> Proxy<T> {
	        return makeProxy<T>();
	    })
	    .def_property_readonly_static("self_proxy", [](pybind11::object &) -> Proxy<R> {
	        return makeProxy<R>();
	    })
		;
	}
};

struct AddProxyRangeMethods {
	template<typename T>
	void operator()(pybind11::class_<Proxy<Range<T>>> &cl) {
		using R = Range<T>;
		using P = Proxy<R>;

		cl
	    .def("__getitem__", [](P &p, int64_t posIndex) -> Proxy<T> {
	    	return lift(p, [=](Range<T> && range) -> T {
				auto chainSize = static_cast<int64_t>(range.size());
				auto pos = posIndex;
		        if (pos < 0) {
		            pos += chainSize;
		        }
		        if (pos < 0 || pos >= chainSize) {
		            throw pybind11::index_error();
		        }
		        return range[pos];
			});
	    }, pybind11::arg("index"))
	    .def("__getitem__", [](P &p, pybind11::slice slice) -> Proxy<Range<T>> {
	    	return lift(p, [=](Range<T> && range) -> Range<T> {
		        size_t start, stop, step, slicelength;
		        const auto &constRange = range;
		        auto chainSize = ranges::size(constRange);
		        if (!slice.compute(chainSize, &start, &stop, &step, &slicelength))
		            throw pybind11::error_already_set();
		        
		        auto subset =  range[{static_cast<ranges::range_size_type_t<R>>(start), static_cast<ranges::range_size_type_t<R>>(stop)}];
		        return subset | ranges::view::stride(step);
		    });
	    }, pybind11::arg("slice"))
		;

	}
};

template <typename T>
void setupRangesProxy(AllProxyClasses<T> &cls) {
	cls.iterator.applyToAll(AddProxySequenceMethods{});
	cls.range.applyToAll(AddProxySequenceMethods{});
	cls.range.applyToAll(AddProxyRangeMethods{});
}


#endif /* proxy_range_hpp */

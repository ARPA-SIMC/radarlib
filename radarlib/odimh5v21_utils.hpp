/*
 * odimh5v21_utils - odimh5v21 utilities
 *
 * Copyright (C) 2013 ARPA-SIM <urpsim@smr.arpa.emr.it>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Author: Emanuele Di Giacomo <edigiacomo@arpa.emr.it>
 */
#ifndef __RADAR_ODIMH5V21_UTILS_HPP__
#define __RADAR_ODIMH5V21_UTILS_HPP__
/**
 * \file
 * \brief odimh5v21 utilities
 */

#include <radarlib/odimh5v21_classes.hpp>

namespace OdimH5v21 {
/// utilities
namespace utils {

/**
 * \brief Generic OdimObject visitor
 *
 * This class allows to visit a concrete odim object given a generic one. When
 * the method visitObject(OdimH5v21::OdimObject&) is called, visitor invokes the
 * proper methot visit(). A concrete visitor should override one or more of the
 * visit() methods (the default behaviour is a noop).
 *
 * For example, the following class prints the number of scans if a polar volume
 * is found, otherwise does nothing:
 * @code
 * struct MyVisitor : public OdimObjectVisitor {
 *   protected:
 *     virtual void visit(OdimH5v21::PolarVolume& obj) {
 *       std::cout 
 *         << "Polar volume: #scans: " << obj.getScanCount() << std::endl;
 *     }
 * };
 * @endcode
 */
class OdimObjectVisitor {
 public:
	/**
	 * \brief Visit a generic object and call the proper method visit()
	 *
	 * This method accepts a generic OdimObject, casts it to the proper concrete
	 * class (based on OdimObject::getObject()) and call the proper visit()
	 * method.
	 *
	 * If the object type is not supported, the visitor calls visitDefault().
	 *
	 * If the object type and the class are not consistent, an exception is
	 * thrown.
	 */
	void visitObject(OdimH5v21::OdimObject& obj);
 protected:
	/// Called when the visited OdimObject is not supported (noop)
	virtual void visitDefault(OdimH5v21::OdimObject& obj) {}
	/// Called when the visited OdimObject is a PolarVolume (noop)
	virtual void visit(OdimH5v21::PolarVolume& obj) {}
	/// Called when the visited OdimObject is a ImageObject (noop)
	virtual void visit(OdimH5v21::ImageObject& obj) {}
	/// Called when the visited OdimObject is a CompObject (noop)
	virtual void visit(OdimH5v21::CompObject& obj) {}
	/// Called when the visited OdimObject is a XsecObject (noop)
	virtual void visit(OdimH5v21::XsecObject& obj) {}

 private:
	/// Called by visitObject(OdimObject) to cast and visit the concrete object
	template <class T>
	void castAndVisitObject(OdimH5v21::OdimObject& obj) {
		T& x = dynamic_cast<T&>(obj);
		this->visit(x);
	}
};
/**
 * \brief Generic 2D product visitor
 *
 * This class allows to visit a concrete odim 2D product given a generic one.
 * When the method visitProduct2D(OdimH5v21::Product2D&) is called, visitor
 * invokes the proper methot visit(). A concrete visitor should override one or
 * more of the visit() methods (the default behaviour is a noop).
 */
class OdimProduct2DVisitor {
 public:
	/**
	 * \brief Visit a generic 2D product and call the proper method visit()
	 *
	 * This method accepts a generic Product_2D, casts it to the proper concrete
	 * class (based on Product_2D::getProduct()) and call the proper visit()
	 * method.
	 *
	 * If the product type is not supported, the visitor calls visitDefault().
	 *
	 * If the product type and the class are not consistent, an exception is
	 * thrown.
	 */
	void visitProduct2D(OdimH5v21::Product_2D& prod);
 protected:
	/// Called when the visited Product_2D is not supported (noop)
	virtual void visitDefault(OdimH5v21::Product_2D& prod) {}
	/// Called when the visited Product_2D is a PPI product (noop)
	virtual void visit(OdimH5v21::Product_PPI& prod) {}
	/// Called when the visited Product_2D is a CAPPI product (noop)
	virtual void visit(OdimH5v21::Product_CAPPI& prod) {}
	/// Called when the visited Product_2D is a PCAPPI product (noop)
	virtual void visit(OdimH5v21::Product_PCAPPI& prod) {}
	/// Called when the visited Product_2D is a ETOP product (noop)
	virtual void visit(OdimH5v21::Product_ETOP& prod) {}
	/// Called when the visited Product_2D is a MAX product (noop)
	virtual void visit(OdimH5v21::Product_MAX& prod) {}
	/// Called when the visited Product_2D is a RR product (noop)
	virtual void visit(OdimH5v21::Product_RR& prod) {}
	/// Called when the visited Product_2D is a VIL product (noop)
	virtual void visit(OdimH5v21::Product_VIL& prod) {}
	/// Called when the visited Product_2D is a LBM product (noop)
	virtual void visit(OdimH5v21::Product_LBM& prod) {}
	/// Called when the visited Product_2D is a POH product (noop)
	virtual void visit(OdimH5v21::Product_POH& prod) {}
	/// Called when the visited Product_2D is a COMP product (noop)
	virtual void visit(OdimH5v21::Product_COMP& prod) {}
	/// Called when the visited Product_2D is a XSEC product (noop)
	virtual void visit(OdimH5v21::Product_XSEC& prod) {}
	/// Called when the visited Product_2D is a RHI product (noop)
	virtual void visit(OdimH5v21::Product_RHI& prod) {}
	/// Called when the visited Product_2D is a VSP product (noop)
	virtual void visit(OdimH5v21::Product_VSP& prod) {}
	/// Called when the visited Product_2D is a HSP product (noop)
	virtual void visit(OdimH5v21::Product_HSP& prod) {}
 private:
	template<class T>
	void castAndVisitProduct2D(OdimH5v21::Product_2D& prod) {
		T&x = dynamic_cast<T&>(prod);
		this->visit(x);
	}
};

}
}
#endif

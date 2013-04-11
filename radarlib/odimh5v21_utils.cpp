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
#include <radarlib/odimh5v21_utils.hpp>
namespace OdimH5v21 {
namespace utils {

void OdimObjectVisitor::visitObject(OdimObject& obj) {
	const std::string& type = obj.getObject();
	if (type == OBJECT_PVOL)
		castAndVisitObject<PolarVolume>(obj);
	else if (type == OBJECT_IMAGE)
		castAndVisitObject<ImageObject>(obj);
	else if (type == OBJECT_COMP)
		castAndVisitObject<CompObject>(obj);
	else if (type == OBJECT_XSEC)
		castAndVisitObject<XsecObject>(obj);
	else
		visitDefault(obj);
}

void OdimProduct2DVisitor::visitProduct2D(OdimH5v21::Product_2D& prod) {
	const std::string& type = prod.getProduct();
	if (type == PRODUCT_PPI)
		castAndVisitProduct2D<Product_PPI>(prod);
	if (type == PRODUCT_CAPPI)
		castAndVisitProduct2D<Product_CAPPI>(prod);
	if (type == PRODUCT_PCAPPI)
		castAndVisitProduct2D<Product_PCAPPI>(prod);
	if (type == PRODUCT_ETOP)
		castAndVisitProduct2D<Product_ETOP>(prod);
	if (type == PRODUCT_MAX)
		castAndVisitProduct2D<Product_MAX>(prod);
	if (type == PRODUCT_RR)
		castAndVisitProduct2D<Product_RR>(prod);
	if (type == PRODUCT_VIL)
		castAndVisitProduct2D<Product_VIL>(prod);
	if (type == PRODUCT_LBM_ARPA)
		castAndVisitProduct2D<Product_LBM>(prod);
	if (type == PRODUCT_COMP)
		castAndVisitProduct2D<Product_COMP>(prod);
	if (type == PRODUCT_XSEC)
		castAndVisitProduct2D<Product_XSEC>(prod);
	if (type == PRODUCT_RHI)
		castAndVisitProduct2D<Product_RHI>(prod);
	if (type == PRODUCT_VSP)
		castAndVisitProduct2D<Product_VSP>(prod);
	if (type == PRODUCT_HSP)
		castAndVisitProduct2D<Product_HSP>(prod);
	else
		visitDefault(prod);
}

}
}

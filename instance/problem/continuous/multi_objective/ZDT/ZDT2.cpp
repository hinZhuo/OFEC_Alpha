#include "ZDT2.h"

namespace OFEC {
	ZDT2::ZDT2(param_map & v) :  ZDT2(v.at("proName"), v.at("numDim")) { //param_numDim = 30 is suggested
		
	}
	ZDT2::ZDT2(const std::string & name, size_t size_var) : problem(name, size_var, 2), ZDT(name, size_var) {
		
	}

	void ZDT2::evaluate_objective(real *x, std::vector<real> &obj) {
		real g = 0;
		for (size_t n = 1; n<m_variable_size; n++)
			g = g + x[n];
		g = 1 + 9 * g / (m_variable_size - 1);
		obj[0] = x[0];
		obj[1] = g*(1 - pow(obj[0] / g, 2));
	}
}

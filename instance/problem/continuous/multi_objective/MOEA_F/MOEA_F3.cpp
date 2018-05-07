#include "MOEA_F3.h"

namespace OFEC {
	MOEA_F3::MOEA_F3(param_map & v) :
		MOEA_F3(v.at("proName"), v.at("numDim")) {
		
	}
	MOEA_F3::MOEA_F3(const std::string & name, size_t size_var) : problem(name, size_var, 2), \
		MOEA_FBase(name, size_var, 2) {
		
	}
	void MOEA_F3::initialize() {
		std::vector<std::pair<real, real>> range(m_variable_size, std::make_pair(-1, 1));
		range[0].first = 0;
		set_range(range);
		m_dtype = 1;
		m_ptype = 21;
		m_ltype = 23;
	}
}
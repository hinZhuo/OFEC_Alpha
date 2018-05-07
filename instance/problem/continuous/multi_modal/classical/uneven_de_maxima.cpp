#include "uneven_de_maxima.h"

namespace OFEC {
	
	uneven_de_maxima::uneven_de_maxima(param_map &v) : 
		uneven_de_maxima((v.at("proName")), 1, 1) {

		
		
	}
	uneven_de_maxima::uneven_de_maxima(const std::string &name, size_t size_var, size_t size_obj) : problem(name, size_var, size_obj), \
		function(name, size_var, size_obj) {
		
	}

	void uneven_de_maxima::initialize() { 
		set_range(0, 1.); // note
		set_init_range(0, 1.); // note

		m_opt_mode[0] = optimization_mode::Maximization;
		m_objective_accuracy = 0.01;
		m_variable_accuracy = 1.e-4;
		m_objective_monitor = true;
		
		std::vector<std::vector<real>> obj_data(1, std::vector<real>(m_objective_size, 1.));
		for (auto &i : obj_data)
			m_original_optima.append(i);
		m_optima = m_original_optima;
		
	}
	void uneven_de_maxima::evaluate__(real *x, std::vector<real>& obj) {
		double tmp1 = -2 * log(2)*((x[0] - 0.08) / 0.854)*((x[0] - 0.08) / 0.854);
		double tmp2 = sin(5 * OFEC_PI*(pow(x[0], 3.0 / 4.0) - 0.05));
		double s = exp(tmp1) * pow(tmp2, 6);
		obj[0] = s + m_bias;  // note
	}
	
}
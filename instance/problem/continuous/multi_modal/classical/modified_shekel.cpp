/*************************************************************************
* Project:Open Frameworks for Evolutionary Computation (OFEC)
*************************************************************************
* Author: Changhe Li
* Email: changhe.lw@gmail.com 
* Language: C++
*************************************************************************
*  This file is part of OFEC. This library is free software;
*  you can redistribute it and/or modify it under the terms of the
*  GNU General Public License as published by the Free Software
*  Foundation; either version 2, or (at your option) any later version.
******************************************************************************************
*  Paper; A sequential niching memetic algorithm for continuous multimodal
*		  Appled Mathematics and Computation 218(2012) 8242-8259
*******************************************************************************************/

#include "modified_shekel.h"
namespace OFEC {
	
	modified_shekel::modified_shekel(param_map &v) : 
		modified_shekel((v.at("proName")), (v.at("numDim")), 1) {
		
	}
	modified_shekel::modified_shekel(const std::string &name, size_t size_var, size_t size_obj) : problem(name, size_var, size_obj), \
		function(name, size_var, size_obj) {
		
	}

	void modified_shekel::initialize() {
		if (m_variable_size > 5) throw myexcept("number of dim must be <=5@ modified_shekel::modified_shekel");
		set_range(0.0, 11.0);
		set_init_range(0.0, 11.0);
		real a[8][5] = { 4,4,6.3,4,4,1,1,8.5,1,1,6,6,9.1,6,6,3.5,7.5,4,9,4,5,5,3,3,9,9.1,8.2,2,3,9,1.5,9.3,7.4,3,9,7.8,2.2,5.3,9,3 };
		real c[8] = { 0.1,0.2,0.4,0.15,0.6,0.2,0.06,0.18 };
		std::copy(c, c + 8, m_c);
		m_variable_monitor = true;
		for (size_t i = 0; i < 8; ++i) std::copy(a[i], a[i] + 5, m_a[i]);
		m_opt_mode[0] = optimization_mode::Maximization;
		m_objective_accuracy = 0.2;
		m_variable_accuracy = 1.e-3;

		 //1 gopt+7 lopt
		set_original_global_opt(m_a[6]);
		for (size_t m = 0; m < 8; ++m) {
			if (m == 6) continue;
			set_original_global_opt(m_a[m]);
		}
		m_optima = m_original_optima;
		m_initialized = true;
	}
	void modified_shekel::evaluate_objective(real *x, std::vector<real> &obj) {
		real s = 0;

		for (int i = 0; i < 8; ++i) {
			real b = 0;
			for (int j = 0; j < m_variable_size; ++j) {
				b += (x[j] - m_a[i][j])*(x[j] - m_a[i][j]);
			}
			s += pow(b + m_c[i], -1);
		}

		obj[0] = s + m_bias;
	}
	
}
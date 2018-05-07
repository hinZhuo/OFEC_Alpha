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
*  Paper: Multimodal Optimization by Means of a Topological Species Conservation Algorithm
*		  IEEE TRANSACTIONS ON EVOLUTIONARY COMPUTATION, VOL.14,NO.6,DECEMBER 2010
*******************************************************************************************/

#include "six_hump_camel_back.h"
namespace OFEC {
	
<<<<<<< HEAD
	six_hump_camel_back::six_hump_camel_back(param_map &v) :problem((v.at("proName")), 2, 1), \
		function((v.at("proName")), 2, 1) {
=======
	six_hump_camel_back::six_hump_camel_back(param_map &v) :
		six_hump_camel_back((v.at("proName")), 2, 1) {
>>>>>>> zhou_li
		
	}
	six_hump_camel_back::six_hump_camel_back(const std::string &name, size_t size_var, size_t size_obj) :problem(name, size_var, size_obj), \
		function(name, size_var, size_obj) {

	}

	void six_hump_camel_back::initialize() {
<<<<<<< HEAD
		m_opt_mode[0] = optimization_mode::Minimization;
=======
		
>>>>>>> zhou_li
		std::vector<std::pair<real, real>> range;
		range.push_back(std::make_pair(-1.9, 1.9));
		range.push_back(std::make_pair(-1.1, 1.1));
		set_range(range);
		set_range(std::move(range));

		m_variable_accuracy = 1.e-4;
		m_objective_accuracy = 0.1;
		m_variable_monitor = true;
		// 2gopt+ 4 lopt
		std::vector<std::vector<real>> var_data = { {-0.089842, 0.712656 }, {0.712656, -0.712656}, {-1.70361, 0.796084}, {1.70361, -0.796084}, {-1.6071,-0.56865}, {1.6071, 0.56865} };

		for (auto &i : var_data) {
			set_original_global_opt(i.data());
		}
		m_optima = m_original_optima;
		

	}
	void six_hump_camel_back::evaluate__(real *x, std::vector<real>& obj) {

		double s = x[0] * x[0], t = x[1] * x[1];
		s = (4 - 2.1*s + pow(x[0], 4) / 3)*s + x[0] * x[1] + (-4 + 4 * t)*t;
		obj[0] = s + m_bias;
	}
	
}
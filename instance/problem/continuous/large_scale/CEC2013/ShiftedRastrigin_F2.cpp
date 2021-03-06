/*************************************************************************
* Project:Open Frameworks for Evolutionary Computation (OFEC)
/*************************************************************************
* Project:Open Frameworks for Evolutionary Computation (OFEC)
*************************************************************************
* Author: Changhe Li and Li Zhou
* Email: changhe.lw@gmail.com, 441837060@qq.com
* Language: C++
*************************************************************************
*  This file is part of OFEC. This library is free software;
*  you can redistribute it and/or modify it under the terms of the
*  GNU General Public License as published by the Free Software
*  Foundation; either version 2, or (at your option) any later version.
*************************************************************************/
#include "ShiftedRastrigin_F2.h"
namespace OFEC {
	namespace CEC2013 {
		ShiftedRastrigin_F2::ShiftedRastrigin_F2(param_map &v) :
			ShiftedRastrigin_F2((v.at("proName")), (v.at("numDim")), 1) \
		{
			
		}

		ShiftedRastrigin_F2::ShiftedRastrigin_F2(const std::string &name, size_t size_var, size_t size_obj) : problem(name, size_var, size_obj), \
			function_CEC2013(name, size_var, size_obj) \
		{
			
		}

		ShiftedRastrigin_F2::~ShiftedRastrigin_F2() {
			delete[] mp_Ovector;
			delete[] mp_anotherz;
		}

		void ShiftedRastrigin_F2::initialize() {
			m_variable_monitor = true;
			set_range(-5, 5);
			set_init_range(-5, 5);
			ID = 2;
			mp_anotherz = new real[m_variable_size];

			// Ovector = createShiftVector(dimension,minX,maxX);
			mp_Ovector = readOvector();

			set_original_global_opt();
			set_global_opt(mp_Ovector);
			m_initialized = true;
		}

		void ShiftedRastrigin_F2::evaluate_objective(real *x, std::vector<real> &obj) {
			size_t i;
			for (i = 0; i < m_variable_size; ++i) {
				mp_anotherz[i] = x[i] - mp_Ovector[i];
			}
			obj[0] = rastrigin(mp_anotherz, m_variable_size);
		}
	}
}
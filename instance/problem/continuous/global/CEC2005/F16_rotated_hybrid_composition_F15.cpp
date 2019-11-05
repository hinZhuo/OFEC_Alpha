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
*************************************************************************/

#include "F16_rotated_hybrid_composition_F15.h"
#include "../classical/sphere.h"
#include "../classical/ackley.h"
#include "../classical/griewank.h"
#include "../classical/rastrigin.h"
#include "../classical/weierstrass.h"
#include <numeric>

namespace OFEC {
	namespace CEC2005 {
		F16_rotated_hybrid_composition_F15::F16_rotated_hybrid_composition_F15(param_map &v) :
			F16_rotated_hybrid_composition_F15((v.at("proName")), (v.at("numDim")), 1) {

			
		}
		F16_rotated_hybrid_composition_F15::F16_rotated_hybrid_composition_F15(const std::string &name, size_t size_var, size_t size_obj) :problem(name, size_var, size_obj), \
			composition(name, size_var, size_obj) {

			
		}

		void F16_rotated_hybrid_composition_F15::initialize() {
			set_range(-5., 5.);
			m_height_normalize_severity = 2000.;
			set_function();
			for (auto &i : m_function) {
				i->set_original_global_opt();
			}
			load_rotation("instance/problem/continuous/global/classical/CEC2005/data/");
			
			compute_fmax();

			load_translation("instance/problem/continuous/global/classical/CEC2005/data/");  //data path
			
			for (auto &i : m_function) {
				i->set_global_opt(i->translation().data());
			}
			// Set optimal solution

            solution<variable_vector<real>, real> s(m_objective_size, num_constraints(), m_variable_size);
            s.variable().vect() = m_function[0]->translation();

			m_optima.append(s.variable());
			m_optima.set_flag_variable(true);

            s.evaluate(false, caller::Problem);
			m_optima.append(s.objective());
			// end set
			m_objective_monitor = true;
			m_objective_accuracy = 1.0e-8;

			m_variable_partition.clear();
			m_variable_partition.push_back(std::vector<size_t>(m_variable_size));
			std::iota(m_variable_partition[0].begin(), m_variable_partition[0].end(), 0);
			m_initialized = true;
		}

		void F16_rotated_hybrid_composition_F15::evaluate_objective(real *x, std::vector<real> &obj) {
			composition::evaluate_objective(x, obj);
			obj[0] += 120.; // add m_bias
		}


		void F16_rotated_hybrid_composition_F15::set_function() {
			basic_func f(5);
			f[0] = &create_function<rastrigin>;
			f[1] = &create_function<weierstrass>;
			f[2] = &create_function<griewank>;
			f[3] = &create_function<ackley>;
			f[4] = &create_function<sphere>;

			for (size_t i = 0; i < m_num_function; ++i) {
				m_function[i] = dynamic_cast<function*>(f[i / 2]("", m_variable_size, m_objective_size));
				m_function[i]->set_bias(0);
			}

			for (auto &i : m_function)
				i->set_condition_number(2.);

			for (int i = 0; i < m_num_function; i++) {
				m_height[i] = 100 * i;
				m_converge_severity[i] = 1.;
			}

			m_function[0]->set_range(-5, 5);     m_function[1]->set_range(-5, 5);
			m_function[2]->set_range(-0.5, 0.5); m_function[3]->set_range(-0.5, 0.5);
			m_function[4]->set_range(-60, 60); m_function[5]->set_range(-60, 60);
			m_function[6]->set_range(-32, 32);   m_function[7]->set_range(-32, 32);
			m_function[8]->set_range(-100, 100); m_function[9]->set_range(-100, 100);

			m_stretch_severity[0] = 1.;		m_stretch_severity[1] = 1.;
			m_stretch_severity[2] = 10.;		m_stretch_severity[3] = 10.;
			m_stretch_severity[4] = 5. / 60;  m_stretch_severity[5] = 5. / 60;
			m_stretch_severity[6] = 5. / 32;	m_stretch_severity[7] = 5. / 32;
			m_stretch_severity[8] = 5. / 100;  m_stretch_severity[9] = 5. / 100;

			for (int i = 0; i < m_num_function; i++) {
				m_function[i]->set_scale(m_stretch_severity[i]);
			}

			//set_bias(120.);
		}
	}
}



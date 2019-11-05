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
******************************************************************************************
*  Paper: Problem Definitions and Evaluation Criteria for the CEC 2015
*  Competition on Single Objective Multi-Niche Optimization.
*******************************************************************************************/


#ifndef OFEC_CEC2015_F12_COMPOSITION4_H
#define OFEC_CEC2015_F12_COMPOSITION4_H

#include "../../expensive/CEC2015/composition_2015.h"


namespace OFEC {
	namespace CEC2015 {
		class F12_composition2015_C4 final : public composition_2015
		{
		public:
			F12_composition2015_C4(param_map &v);
			F12_composition2015_C4(const std::string &name, size_t size_var, size_t size_obj);
			void initialize();
		protected:
			void evaluate_objective(real *x, std::vector<real>& obj) override;
			void set_function();

			bool load_optima(const std::string &path);
			void load_optima_(const std::string &path);
			void set_optima();

			void evaluate_optima();
			void rotate(size_t num, real *x);
			void scale(size_t num, real *x);

			bool load_translation(const std::string &path);
			void set_translation();

			void set_weight(std::vector<real>& weight, const std::vector<real>&x);
		private:
		};
	}
	using CEC2015_MMOP_F12 = CEC2015::F12_composition2015_C4;
}
#endif // !OFEC_CEC2015_F12_COMPOSITION4_H









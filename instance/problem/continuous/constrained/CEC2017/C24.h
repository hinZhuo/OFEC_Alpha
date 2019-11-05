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


#ifndef OFEC_C24_H
#define OFEC_C24_H

#include "../../../../../core/problem/continuous/function.h"

namespace OFEC {
	namespace CEC2017 {
		class C24 final: public function
		{
		public:
			C24(param_map &v);
			C24(const std::string &name, size_t size_var, size_t size_obj);
			void initialize();
		protected:
			void evaluate_obj_nd_con(real *x, std::vector<real>& obj, std::vector<real> &con) override;
		private:

		};
	}
	using CEC2017_COP_F24 = CEC2017::C24;
}
#endif // ! OFEC_C24_H
















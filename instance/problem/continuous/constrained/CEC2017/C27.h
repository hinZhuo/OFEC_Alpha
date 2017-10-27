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


#ifndef OFEC_C27_H
#define OFEC_C27_H

#include "../../../../../core/problem/continuous/constraint.h"

namespace OFEC {
	namespace CEC2017 {
		class C27 : public constraint
		{
		public:
			C27(param_map &v);
			C27(const std::string &name, size_t size_var, size_t size_obj);
			virtual ~C27();
		protected:
			void initialize();
			void evaluate__(real *x, std::vector<real>& obj, double & cons);
		private:

		};


	}
}
#endif // ! OFEC_C27_H


















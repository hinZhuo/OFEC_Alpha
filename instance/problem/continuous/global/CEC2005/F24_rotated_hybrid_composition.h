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

#ifndef OFEC_F24_ROTATED_HYBRID_COMPOSITION_H
#define OFEC_F24_ROTATED_HYBRID_COMPOSITION_H

#include "composition.h"

namespace OFEC {
	namespace CEC2005 {
		class F24_rotated_hybrid_composition final : public composition
		{
		public:
			F24_rotated_hybrid_composition(param_map &v);
			F24_rotated_hybrid_composition(const std::string &name, size_t size_var, size_t size_obj);
			void initialize();
		protected:
			void evaluate_objective(real *x, std::vector<real>& obj) override;
			void set_function();

		private:

		};
	}
	using CEC2005_GOP_F24 = CEC2005::F24_rotated_hybrid_composition;
}
#endif // !OFEC_F21_ROTATED_HYBRID_COMPOSITION_H


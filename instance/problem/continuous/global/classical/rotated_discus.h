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

#ifndef OFEC_ROTATED_DISCUS_H
#define OFEC_ROTATED_DISCUS_H

#include "../../../../../instance/problem/continuous/global/classical/discus.h"
namespace OFEC {

	class rotated_discus : public discus
	{
	public:
		rotated_discus(param_map &v);
		rotated_discus(const std::string &name, size_t size_var, size_t size_obj);
		void initialize();
	protected:
		void evaluate_objective(real *x, std::vector<real>& obj) override;
	private:
	};

}
#endif // !OFEC_ROTATED_DISCUS_H



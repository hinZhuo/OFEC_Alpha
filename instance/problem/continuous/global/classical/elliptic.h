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

#ifndef OFEC_ELLIPTIC_H
#define OFEC_ELLIPTIC_H

#include "../../../../../core/problem/continuous/function.h"
namespace OFEC {
	
	class elliptic : public function
	{
	public:
		elliptic(param_map &v);
		elliptic(const std::string &name, size_t size_var, size_t size_obj);
		void initialize();
	protected:
		void evaluate_objective(real *x, std::vector<real>& obj) override;

	private:
	};
	
}

#endif // !OFEC_ELLIPTIC_H

/*************************************************************************
* Project: Library of Open Frameworks for Evolutionary Computation (OFEC)
*************************************************************************
* Author: Changhe Li & Yong Xia
* Email: changhe.lw@google.com  Or cugxiayong@gmail.com
* Language: C++
*************************************************************************
*  This file is part of OFEC. This library is free software;
*  you can redistribute it and/or modify it under the terms of the
*  GNU General Public License as published by the Free Software
*  Foundation; either version 2, or (at your option) any later version.
*************************************************************************/
// Created: 18 Apr 2016
// Modified: 14 Mar 2018 By Junchen Wang (wangjunchen@cug.edu.cn)

#ifndef QAP_H
#define QAP_H

#include "../../../../core/problem/problem.h"
#include "../../../../core/problem/optima.h"
#include "../../../../core/problem/domain.h"

namespace OFEC {
#define CAST_QAP dynamic_cast<quadratic_assignment *>(global::ms_global->m_problem.get())
	class quadratic_assignment :public problem
{
protected:
	std::vector<std::vector<real> > mvv_flow;
	std::vector<std::vector<real> > mvv_distance;
	std::string m_file_name;
	domain<int> m_domain;
	optima<variable_vector<int>, real> m_optima;
	bool m_if_valid_check = true;
public:
	quadratic_assignment(param_map& v);
	quadratic_assignment(const std::string& pro_name, size_t size_var, const std::string& file_name);
	~quadratic_assignment();
	evaluation_tag evaluate_(solution_base &s, caller call, bool effective, bool constructed);
	bool is_valid(const solution_base &s) const;
	void read_problem();    //read source data from file
	bool get_optimal_obj(std::vector<real> &opt);
	bool get_optimal_obj(std::vector<std::vector<real>> &opt);
	const optima<variable_vector<int>, real> & get_optima()const;
	optima<variable_vector<int>, real> & get_optima();
	bool is_optima_given();
	quadratic_assignment *get_type_ptr();
	quadratic_assignment &get_type_ref();
	bool is_optima_found();
	void initialize_solution(solution_base &s) const;
	bool same(const solution_base &s1, const solution_base &s2) const;
	real variable_distance(const solution_base &s1, const solution_base &s2) const;
	real variable_distance(const variable_base &s1, const variable_base &s2) const;
	void initialize();
};
}

#endif // !QAP_H


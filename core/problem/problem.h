/******************************************************************************
* Project:Open Frameworks for Evolutionary Computation (OFEC)
*******************************************************************************
* Author: Changhe Li
* Email: changhe.lw@gmail.com
* Language: C++
*-------------------------------------------------------------------------------
*  This file is part of OFEC. This library is free software;
*  you can redistribute it and/or modify it under the terms of the
*  GNU General Public License as published by the Free Software
*  Foundation; either version 2, or (at your option) any later version.
*
*  see https://github.com/Changhe160/OFEC for more information
*
*-------------------------------------------------------------------------------
* the abstract of different types of problems
*
*
*********************************************************************************/
#ifndef OFEC_PROBLEM_H
#define OFEC_PROBLEM_H
#include <string>
#include <limits>
#include <map>
#include <memory>
#include <set>
#include <sstream>

#include "../definition.h"
#include "../algorithm/encoding.h"

namespace OFEC {
	class problem {
	public:
		problem(const std::string &name, size_t size_var, size_t size_obj);
		virtual ~problem() {}
		problem(const problem&) = delete;

		optimization_mode opt_mode(size_t idx) const {
			return m_opt_mode[idx];
		}
		const std::vector<optimization_mode>& opt_mode() const {
			return m_opt_mode;
		}
		virtual bool same(const solution_base &s1, const solution_base &s2) const = 0;
		virtual double variable_distance(const solution_base &s1, const solution_base &s2) const = 0;
		virtual double variable_distance(const variable_base &s1, const variable_base &s2) const = 0;

		template<typename Solution>
		evaluation_tag evaluate(Solution &s, caller call, bool effective_eval = true) {
			evaluation_tag tag = evaluate_(s, call, effective_eval, true);
			if (m_eval_monitor&&effective_eval) {
				update_objective_minmax(s, m_opt_mode);
			}
			++m_total_eval;
			return tag;
		}
		virtual evaluation_tag evaluate_(solution_base &s, caller call, bool effective_fes, bool constructed) = 0;

		const std::string& name() const {
			return m_name;
		}

		virtual violation_type check_boundary_violation(const solution_base &) const {
			return violation_type::None;
		}
		virtual violation_type check_constraint_violation(const solution_base &) const {
			return violation_type::None;
		}
		virtual void constraint_value(const solution_base &, std::pair<double, std::vector<double>>&) {};


		template<typename Solution>
		static void update_objective_minmax(const Solution &s, std::vector<optimization_mode> & mode) {
			if (ms_minmax_objective.size() != s.objective_size()) {
				ms_minmax_objective.clear();
				for (size_t i = 0; i < s.objective_size(); ++i) {
					ms_minmax_objective.emplace(i, std::make_pair(std::unique_ptr<Solution>(new Solution(s)), std::unique_ptr<Solution>(new Solution(s))));
				}
			}
			else {
				for (int i = 0; i < s.objective_size(); ++i) {
					Solution *first = dynamic_cast<Solution *>(ms_minmax_objective[i].first.get());
					Solution *second = dynamic_cast<Solution *>(ms_minmax_objective[i].second.get());

					if (mode[i] == optimization_mode::Minimization) {
						if (first->objective(i) > s.objective(i))
							*first = s;
						if (second->objective(i) < s.objective(i))
							*second = s;
					}
					else {
						if (first->objective(i) < s.objective(i))
							*first = s;
						if (second->objective(i) > s.objective(i))
							*second = s;
					}
				}
			}
		}

		virtual void initialize_solution(solution_base &s) const = 0;

		virtual double feasible_ratio() { return 1.0; }

		size_t variable_size() const {
			return m_variable_size;
		}
		size_t objective_size() const {
			return m_objective_size;
		}
		void set_tag(const std::set<problem_tag> &tag) {
			m_tag = tag;
		}

		void add_tag(problem_tag tag) {
			if (!has_tag(tag))	m_tag.insert(tag);
		}
		bool has_tag(problem_tag tag) {
			if (m_tag.find(tag) != m_tag.end())	return true;
			else return false;
		}
		bool solved() {
			return m_solved;
		}
		size_t evaluations() {
			return m_effective_eval;
		}
		size_t total_evaluations() {
			return m_total_eval;
		}

		void set_opt_mode(optimization_mode m, size_t idx = 0) {
			m_opt_mode[idx] = m;
		}
		template<typename Solution>
		static Solution * get_sofar_best(size_t i) {
			return dynamic_cast<Solution *>(ms_minmax_objective[i].first.get());
		}

		template<typename Solution>
		static Solution * get_sofar_worst(size_t i) {
			return dynamic_cast<Solution *>(ms_minmax_objective[i].second.get());
		}

		virtual void initialize() =0;
		void set_eval_monitor_flag(bool flag);
		virtual bool is_optimal_given() { return false; }
	protected:
		problem& operator=(const problem& rhs);  // assignment is not allowed outside
		problem& operator=(problem&& rhs);
		virtual void copy(const problem *); // copy parameter values of a problem when it changes
		virtual void resize_variable(size_t n);
		virtual void resize_objective(size_t n);
	protected:
		std::string m_name;
		size_t m_effective_eval = 0, m_total_eval = 0;
		size_t m_objective_size;
		size_t m_variable_size;
		std::vector<optimization_mode> m_opt_mode;
		double m_objective_accuracy = 1.0e-6;
		std::set<problem_tag> m_tag;
		std::stringstream m_paramters;
		bool m_solved = false;
		bool m_eval_monitor = false;
		
#ifdef OFEC_CONSOLE
		static thread_local std::map<int, std::pair<std::unique_ptr<solution_base>, std::unique_ptr<solution_base>>> ms_minmax_objective; // the best and worst so far solutions of each objective 
#endif
#ifdef OFEC_DEMON
		static std::map<int, std::pair<unique_ptr<solution_base>, std::unique_ptr<solution_base>>> ms_minmax_objective; // the best and worst so far solutions of each objective 
#endif	

	};

}


#endif // !OFEC_PROBLEM_H

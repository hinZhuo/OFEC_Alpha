/******************************************************************************
* Project:Open Frameworks for Evolutionary Computation (OFEC)
*******************************************************************************
* Author: Changhe Li and Li Zhou
* Email: changhe.lw@gmail.com, 441837060@qq.com
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
* class function defines basic operations for function/numerical optimization problems
*
*********************************************************************************/

#ifndef OFEC_FUNCTION_H
#define OFEC_FUNCTION_H

#include "continuous.h"
#include "../../../utility/matrix.h"
#include <algorithm>

namespace OFEC {
	class function :public continuous {
	public:
		function(const std::string &name, size_t size_var, size_t size_obj = 1);

		void set_bias(real val);
		void set_scale(real val);
		void set_rotation_flag(bool flag);
		void set_tranlation_flag(bool flag);
		void set_scale_flag(bool flag);

		real translation(size_t i) const;
		std::vector<real>& translation();
		matrix& rotation();
		real condition_number();
		real bias();
		real scale();
		void set_condition_number(real c);
		optima<variable_vector<real>, real>& get_original_optima();
		void set_global_opt(real *tran = 0);
		void set_original_global_opt(real *opt = 0);
	protected:
		virtual void clear();
	
		void translate_zero();

		virtual bool load_translation(const std::string &path);
		virtual void load_translation_(const std::string &path);
		virtual void set_translation(const real *opt_var);

		virtual bool load_rotation(const std::string &path);
		virtual void load_rotation_(const std::string &path);
		virtual void set_rotation();

		void resize_translation(size_t n);
		void resize_rotation(size_t n);

		void irregularize(real *x);
		void asyemmetricalize(real *x, real belta);
		void translate(real *x);
		void translate_origin(real *x);
		void rotate(real *x);
		void scale(real *x);
		void update_parameters();
	protected:
		std::vector<real> m_translation;
		bool m_scale_flag = false, m_rotation_flag = false, m_translation_flag = false, m_noise_flag = false;
		real m_scale, m_bias = 0.;
		real m_condition_number;
		matrix m_rotation;
		optima<variable_vector<real>, real> m_original_optima;
	};
	template<typename T> problem * create_function(const std::string &name, size_t size_var, size_t size_obj) {
		return new T(name, size_var, size_obj);
	}
	typedef problem *(*pFun)(const std::string &name, size_t size_var, size_t size_obj);
	typedef std::vector<pFun> basic_func;
}
#endif // !OFEC_FUNCTION_H
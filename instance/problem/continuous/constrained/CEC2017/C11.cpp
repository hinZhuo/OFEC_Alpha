#include "C11.h"

namespace OFEC {
	namespace CEC2017 {
		C11::C11(param_map &v) :problem((v[param_proName]), (v[param_numDim]), 1), \
			function((v[param_proName]), (v[param_numDim]), 1) {
			set_range(-100., 100.);
			initialize();
		}
		C11::C11(const std::string &name, size_t size_var, size_t size_obj) :problem(name, size_var, size_obj), \
			function(name, size_var, size_obj) {
			set_range(-100., 100.);
			initialize();
		}

		void C11::initialize() {
			add_tag(problem_tag::COP);
			//std::vector<real> data(m_variable_size, 0);
			//set_original_global_opt(data.data());
			m_translation.resize(m_variable_size);
			bool is_load = load_translation("instance/problem/continuous/constrained/CEC2017/data/");  //data path
			if (!is_load) {
				std::vector<real> temp_var(m_variable_size);
				for (size_t i = 0; i < m_variable_size; ++i)
					temp_var[i] = 0;
				set_translation(temp_var);
			}

			//set_global_opt(m_translation.data());
		}
		void C11::evaluate__(real *x, std::vector<real>& obj, double & cons_first, std::vector<double> &cons_second) {
			for (size_t i = 0; i < m_variable_size; ++i)
				x[i] -= m_translation[i];

			size_t i;
			obj[0] = 0.;
			for (i = 0; i < m_variable_size ; ++i)
			{
				obj[0] += x[i];
			}

			obj[0] += m_bias;

			
			double temp = 0.;
			double sum1 = 0., sum2 = 0.;

			std::vector<double> eq_cons;
			std::vector<double> ineq_cons;
				
			for (i = 0; i < m_variable_size - 1; ++i)
			{
				temp += (x[i] - x[i + 1])*(x[i] - x[i + 1]);
			}
			eq_cons.push_back(temp);
			temp = 1.;
			for (auto &i : eq_cons) {
				if (fabs(i) - 1e-4 <= 0) i = 0;
				else i = fabs(i);
				sum1 += i;
			}

				
			for (i = 0; i < m_variable_size ; ++i)
			{
				temp *= x[i];
			}
			ineq_cons.push_back(temp);
			temp = 0.;

			for (auto &i : ineq_cons) {
				if (i <= 0) i = 0;
				sum2 += i;
			}
			for (auto &i : ineq_cons)
				cons_second.push_back(i);
			for (auto &i : eq_cons)
				cons_second.push_back(i);
			cons_first = (sum1 + sum2) / (double)(eq_cons.size() + ineq_cons.size());
			
		}
	}
}
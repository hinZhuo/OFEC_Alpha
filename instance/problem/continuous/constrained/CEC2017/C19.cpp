#include "C19.h"

namespace OFEC {
	namespace CEC2017 {
<<<<<<< HEAD
		C19::C19(param_map &v) :problem((v.at("proName")), (v.at("numDim")), 1), \
			function((v.at("proName")), (v.at("numDim")), 1) {
=======
		C19::C19(param_map &v) :
			C19((v.at("proName")), (v.at("numDim")), 1) {
>>>>>>> zhou_li
			
		}
		C19::C19(const std::string &name, size_t size_var, size_t size_obj) :problem(name, size_var, size_obj), \
			function(name, size_var, size_obj) {
			
		}

		void C19::initialize() {
			m_variable_monitor = true;
			set_range(-50., 50.);
			set_init_range(-50., 50.);

<<<<<<< HEAD
			add_tag(problem_tag::COP);
=======
			 
>>>>>>> zhou_li
			
			load_translation("instance/problem/continuous/constrained/CEC2017/data/");  //data path
			set_original_global_opt(m_translation.data());
			m_optima = m_original_optima;
		}
		void C19::evaluate__(real *x, std::vector<real>& obj, double & cons_value, std::vector<double> &cons_values) {
			for (size_t i = 0; i < m_variable_size; ++i)
				x[i] -= m_translation[i];
			
			size_t i;
			obj[0] = 0.;

			for (i = 0; i<m_variable_size; ++i)
			{
				obj[0] += (pow(fabs(x[i]), 0.5) + 2 * sin(pow(x[i], 3)));
			}
			obj[0] += m_bias;

			double temp = 0.;
			double sum = 0.;

				
			std::vector<double> ineq_cons;
			
			for (i = 0; i<m_variable_size - 1; ++i)
			{
				temp += -10 * exp(-0.2*sqrt(x[i] * x[i] + x[i + 1] * x[i + 1]));
			}
			temp += (m_variable_size - 1) * 10 / exp(-5.0);
			ineq_cons.push_back(temp);
			temp = 0.;
			for (i = 0; i<m_variable_size; ++i)
			{
				temp += sin(2 * x[i])*sin(2 * x[i]);
			}
			temp -= 0.5 * m_variable_size;
			ineq_cons.push_back(temp);

			for (auto &i : ineq_cons) {
				if (i <= 0) i = 0;
				sum += i;
			}
			cons_values.clear();
			for (auto &i : ineq_cons)
				cons_values.push_back(i);
			cons_value = sum / (double)ineq_cons.size();
			
		}
	}
}
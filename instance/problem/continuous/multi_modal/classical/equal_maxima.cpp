#include "equal_maxima.h"

namespace OFEC {
	
		equal_maxima::equal_maxima(param_map &v) :
			equal_maxima((v.at("proName")), 1, 1) {

			
		}
		equal_maxima::equal_maxima(const std::string &name, size_t size_var, size_t size_obj) :problem(name, size_var, size_obj), \
			function(name, size_var, size_obj) {
			
		}
		void equal_maxima::initialize() {
			set_range(0, 1.); 
			set_init_range(0, 1.);
			m_opt_mode[0] = optimization_mode::Maximization;
			m_objective_monitor = true;
			m_objective_accuracy = 1.e-4;
			m_variable_accuracy = 1.e-2;
			
			std::vector<std::vector<real>> obj_data(5, std::vector<real>(1, 1.));
			for (auto &i : obj_data) {
				m_original_optima.append(i[0]);
			}
			m_optima = m_original_optima;
			

		}
		void equal_maxima::evaluate__(real *x, std::vector<real>& obj) {
			double s;
			s = pow(sin(5 * OFEC_PI*x[0]), 6);
			obj[0] = s + m_bias;  // note
		}
	
}
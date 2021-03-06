#include "michalewicz.h"
namespace OFEC {
	
	michalewicz::michalewicz(param_map &v) :
		michalewicz((v.at("proName")), 2, 1) {
		
	}
	michalewicz::michalewicz(const std::string &name, size_t size_var, size_t size_obj) : problem(name, size_var, size_obj), \
		function(name, size_var, size_obj), m_m(20) {

	
	}

	void michalewicz::initialize() {

		set_range(0, OFEC_PI);
		set_init_range(0, OFEC_PI);
		m_variable_accuracy = 1.e-3;
		m_objective_accuracy = 0.2;
		m_variable_monitor = true;
		m_opt_mode[0] = optimization_mode::Maximization;

		 //1 gopt + 1 lopt
		std::vector<std::vector<real>> var_data = { { 2.20291f, 1.5708f },{ 2.20291f, 2.71157f } };
		for (auto &i : var_data) {
			set_original_global_opt(i.data());
		}

		m_optima = m_original_optima;
		m_initialized = true;
	}
	void michalewicz::evaluate_objective(real *x, std::vector<real> &obj) {
		real s = 0;

		for (int i = 0; i < m_variable_size; ++i) {
			s += sin(x[i])*pow(sin((i + 1)*x[i] * x[i] / OFEC_PI), m_m);
		}
		obj[0] = s + m_bias;
	}
	
}
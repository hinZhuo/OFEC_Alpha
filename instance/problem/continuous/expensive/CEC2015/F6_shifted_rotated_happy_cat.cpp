#include "F6_shifted_rotated_happy_cat.h"

namespace OFEC {
	namespace CEC2015 {
		F6_shifted_rotated_happy_cat::F6_shifted_rotated_happy_cat(param_map &v) :
			F6_shifted_rotated_happy_cat((v.at("proName")), (v.at("numDim")), 1) {

			
		}
		F6_shifted_rotated_happy_cat::F6_shifted_rotated_happy_cat(const std::string &name, size_t size_var, size_t size_obj) :problem(name, size_var, size_obj), \
			happy_cat(name, size_var, size_obj) {

			
		}

		void F6_shifted_rotated_happy_cat::initialize() {
			m_variable_monitor = true;
			set_range(-100., 100.);
			set_init_range(-100., 100.);
			set_original_global_opt();

			set_bias(600);

			load_translation("instance/problem/continuous/expensive/CEC2015/data/");  //data path
			
			load_rotation("instance/problem/continuous/expensive/CEC2015/data/");
			
			set_global_opt(m_translation.data());
			m_initialized = true;
		}
		void F6_shifted_rotated_happy_cat::evaluate_objective(real *x, std::vector<real> &obj) {
			happy_cat::evaluate_objective(x, obj);
		}
	}
}
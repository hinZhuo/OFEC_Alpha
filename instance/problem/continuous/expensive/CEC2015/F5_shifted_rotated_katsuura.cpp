#include "F5_shifted_rotated_katsuura.h"

namespace OFEC {
	namespace CEC2015 {
<<<<<<< HEAD
		F5_shifted_rotated_katsuura::F5_shifted_rotated_katsuura(param_map &v) :problem((v.at("proName")), (v.at("numDim")), 1), \
			katsuura((v.at("proName")), (v.at("numDim")), 1) {
=======
		F5_shifted_rotated_katsuura::F5_shifted_rotated_katsuura(param_map &v) :
			F5_shifted_rotated_katsuura((v.at("proName")), (v.at("numDim")), 1) {
>>>>>>> zhou_li

			
		}
		F5_shifted_rotated_katsuura::F5_shifted_rotated_katsuura(const std::string &name, size_t size_var, size_t size_obj) :problem(name, size_var, size_obj), \
			katsuura(name, size_var, size_obj) {

			
		}

		void F5_shifted_rotated_katsuura::initialize() {
			m_variable_monitor = true;
			set_range(-100., 100.);
			set_init_range(-100., 100.);
			set_original_global_opt();

			
			set_bias(500);

			load_translation("instance/problem/continuous/expensive/CEC2015/data/");  //data path
			
			load_rotation("instance/problem/continuous/expensive/CEC2015/data/");
			
			set_global_opt(m_translation.data());
		}
		void F5_shifted_rotated_katsuura::evaluate__(real *x, std::vector<real>& obj) {
			katsuura::evaluate__(x, obj);
		}
	}
}
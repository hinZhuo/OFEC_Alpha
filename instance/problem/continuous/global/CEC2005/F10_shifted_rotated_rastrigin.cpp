#include "F10_shifted_rotated_rastrigin.h"

namespace OFEC {
	namespace CEC2005 {
		F10_shifted_rotated_rastrigin::F10_shifted_rotated_rastrigin(param_map &v) :problem((v[param_proName]), (v[param_numDim]), 1), \
			rastrigin((v[param_proName]), (v[param_numDim]), 1) {
			initialize();
		}
		F10_shifted_rotated_rastrigin::F10_shifted_rotated_rastrigin(const std::string &name, size_t size_var, size_t size_obj) :problem(name, size_var, size_obj), \
			rastrigin(name, size_var, size_obj) {
			initialize();
		}

		void F10_shifted_rotated_rastrigin::initialize() {

			set_bias(-330);
			set_condition_number(2);

			std::vector<real> temp_var(m_variable_size);
			for (size_t i = 0; i < m_variable_size; ++i)
				temp_var[i] = m_original_optima.variable(0)[i];
			load_translation("instance/problem/continuous/global/CEC2005/data/", temp_var.data());  //data path
			load_rotation("instance/problem/continuous/global/CEC2005/data/");
			m_optima.clear();
			set_global_opt(m_translation.data());
		}
		void F10_shifted_rotated_rastrigin::evaluate__(real *x, vector<real>& obj) {

			rastrigin::evaluate__(x, obj);
		}
	}
}
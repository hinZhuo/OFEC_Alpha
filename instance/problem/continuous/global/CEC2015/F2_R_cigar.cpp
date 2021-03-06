
#include "F2_R_cigar.h"
namespace OFEC {
	namespace CEC2015 {
		F2_R_cigar::F2_R_cigar(param_map &v) :
			F2_R_cigar((v.at("proName")), (v.at("numDim")), 1) {

			
		}
		F2_R_cigar::F2_R_cigar(const std::string &name, size_t size_var, size_t size_obj) :problem(name, size_var, size_obj), \
			bent_cigar(name, size_var, size_obj) {

			
		}

		void F2_R_cigar::initialize() {
			m_variable_monitor = true;
			set_range(-100., 100.);
			set_init_range(-100., 100.);

			set_original_global_opt();
			set_condition_number(1.);
			set_bias(200.);
			load_translation("instance/problem/continuous/global/CEC2015/data/");
			load_rotation("instance/problem/continuous/global/CEC2015/data/");
			
			set_global_opt(m_translation.data());
			m_initialized = true;
		}



		void F2_R_cigar::evaluate_objective(real *x, std::vector<real> &obj) {
			bent_cigar::evaluate_objective(x, obj);
		}
	}
}
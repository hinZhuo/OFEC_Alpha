#include "F8_shifted_rotated_griewank_rosenbrock.h"

namespace OFEC {
	namespace CEC2015 {
		F8_shifted_rotated_griewank_rosenbrock::F8_shifted_rotated_griewank_rosenbrock(param_map &v) :problem((v.at("proName")), (v.at("numDim")), 1), \
			griewank_rosenbrock((v.at("proName")), (v.at("numDim")), 1) {

			
		}
		F8_shifted_rotated_griewank_rosenbrock::F8_shifted_rotated_griewank_rosenbrock(const std::string &name, size_t size_var, size_t size_obj) :problem(name, size_var, size_obj), \
			griewank_rosenbrock(name, size_var, size_obj) {

			
		}

		void F8_shifted_rotated_griewank_rosenbrock::initialize() {
			set_tag(std::set<problem_tag>({ problem_tag::EOP, problem_tag::CONT }));
			m_variable_monitor = true;
			set_range(-5, 5);
			set_init_range(-5., 5.);
			set_original_global_opt();
			set_bias(800);

			load_translation("instance/problem/continuous/expensive/CEC2015/data/");  //data path
			
			load_rotation("instance/problem/continuous/expensive/CEC2015/data/");
			
			set_global_opt(m_translation.data());
		}
		void F8_shifted_rotated_griewank_rosenbrock::evaluate__(real *x, std::vector<real>& obj) {
			griewank_rosenbrock::evaluate__(x, obj);
		}
	}
}
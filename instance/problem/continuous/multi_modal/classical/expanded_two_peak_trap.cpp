#include "expanded_two_peak_trap.h"

namespace OFEC {
	
		expanded_two_peak_trap::expanded_two_peak_trap(param_map &v) :
			expanded_two_peak_trap((v.at("proName")), (v.at("numDim")), 1) {

			
		}
		expanded_two_peak_trap::expanded_two_peak_trap(const std::string &name, size_t size_var, size_t size_obj) :problem(name, size_var, size_obj), \
			function(name, size_var, size_obj) {
			
		}

		void expanded_two_peak_trap::initialize() {
			set_range(-40., 40.);
			set_init_range(-40., 40.);
			
			m_variable_accuracy = 0.01;
			m_objective_accuracy = 1.e-4;
			m_variable_monitor = true;
			// 1 gopt 
			std::vector<std::vector<real>> var_data(1, std::vector<real>(m_variable_size,0));
			
			for (auto &i : var_data) {
				set_original_global_opt(i.data());
			}
			m_optima = m_original_optima;
			m_initialized = true;
		}
		void expanded_two_peak_trap::evaluate_objective(real *x, std::vector<real> &obj) {
			if (m_translation_flag)
				translate(x);
			if (m_scale_flag)
				scale(x);
			if (m_rotation_flag)
				rotate(x);
			if (m_translation_flag)
				translate_origin(x);
			size_t i;
			obj[0] = 0.0;
			
			for (i = 0; i<m_variable_size; ++i)
			{
				x[i] += 20.0;
				if ((x[i]<15.0)&(x[i] >= 0.0))
				{
					obj[0] += -(160.0 / 15.0)*(15.0 - x[i]);
				}
				else if ((x[i] <= 20.0)&(x[i] >= 15.0))
				{
					obj[0] += -40.0*(x[i] - 15.0);
				}
				else if (x[i]<0.0)
				{
					obj[0] += -160.0 + pow(x[i], 2.0);
				}
				else
				{
					obj[0] += -200.0 + pow(x[i] - 20.0, 2.0);
				}
			}
			obj[0] += 200.0*m_variable_size;

		}
	
}
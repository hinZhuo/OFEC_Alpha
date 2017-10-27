#include "C10.h"

namespace OFEC {
	namespace CEC2017 {
		C10::C10(param_map &v) :problem((v[param_proName]), (v[param_numDim]), 1), \
			constraint((v[param_proName]), (v[param_numDim]), 1) {
			set_range(-100., 100.);
			initialize();
		}
		C10::C10(const std::string &name, size_t size_var, size_t size_obj) :problem(name, size_var, size_obj), \
			constraint(name, size_var, size_obj) {
			set_range(-100., 100.);
			initialize();
		}

		C10::~C10() {
			//dtor
		}
		void C10::initialize() {
			std::vector<real> data(m_variable_size, -100);
			set_original_global_opt(data.data());
			m_translation.resize(m_variable_size);
			bool is_load = load_translation("instance/problem/continuous/constrained/CEC2017/data/");  //data path
			if (!is_load) {
				std::vector<real> temp_var(m_variable_size);
				for (size_t i = 0; i < m_variable_size; ++i)
					temp_var[i] = m_original_optima.variable(0)[i];
				set_translation(temp_var);
			}

			set_global_opt(m_translation.data());
		}
		void C10::evaluate__(real *x, std::vector<real>& obj, double & cons) {
			if (m_translation_flag) {
				translate(x);
				translate_origin(x);
			}

			size_t i,j;
			obj[0] = *max_element(x, x + m_variable_size);

			obj[0] += m_bias;

			if (m_translation_flag) {
				
				double temp = 0.;
				double sum = 0.;

				std::vector<double> eq_cons;
				
				for (i = 1; i < m_variable_size + 1; ++i)
				{
					double m = 0.;
					
					for (j = 0; j<i; j++)
					{
						m += x[j];
					}
					temp += m*m;
				}
				eq_cons.push_back(temp);
				temp = 0.;
				for (i = 0; i < m_variable_size - 1; ++i)
				{
					temp += pow((x[i] - x[i+1]),2);
				}
				eq_cons.push_back(temp);
				temp = 0.;
				for (auto &i : eq_cons) {
					if (fabs(i) - m_epsilon <= 0) i = 0;
					else i = fabs(i);
					sum += i;
				}
				cons = sum / (double)eq_cons.size();
			}
		}
	}
}
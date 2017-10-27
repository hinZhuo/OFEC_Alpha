#include "C22.h"

namespace OFEC {
	namespace CEC2017 {
		C22::C22(param_map &v) :problem((v[param_proName]), (v[param_numDim]), 1), \
			constraint((v[param_proName]), (v[param_numDim]), 1) {
			set_range(-100., 100.);
			initialize();
		}
		C22::C22(const std::string &name, size_t size_var, size_t size_obj) :problem(name, size_var, size_obj), \
			constraint(name, size_var, size_obj) {
			set_range(-100., 100.);
			initialize();
		}

		C22::~C22() {
			//dtor
		}
		void C22::initialize() {
			std::vector<real> data(m_variable_size, 1);
			set_original_global_opt(data.data());
			m_translation.resize(m_variable_size);
			bool is_load = load_translation("instance/problem/continuous/constrained/CEC2217/data/");  //data path
			if (!is_load) {
				std::vector<real> temp_var(m_variable_size);
				for (size_t i = 0; i < m_variable_size; ++i)
					temp_var[i] = m_original_optima.variable(0)[i];
				set_translation(temp_var);
			}
			m_rotation.resize(1);
			resize_rotation(m_variable_size);
			load_rotation("instance/problem/continuous/constrained/CEC2217/data/");
			set_global_opt(m_translation.data());
		}
		void C22::evaluate__(real *x, std::vector<real>& obj, double & cons) {
			std::vector<real> x_ori(x, x + m_variable_size);
			if (m_translation_flag) {
				translate(x);
				rotate(x);
				translate_origin(x);
			}

			size_t i;

			obj[0] = 0.;
			for (i = 0; i<m_variable_size - 1; ++i)
			{
				obj[0] += (100 * (x[i] * x[i] - x_ori[i + 1])*(x[i] * x[i] - x_ori[i + 1]) + (x[i] - 1)*(x[i] - 1));
			}
			obj[0] += m_bias;

			if (m_translation_flag) {
				double temp = 0.;
				double sum = 0.;

				std::vector<double> ineq_cons;

				for (i = 0; i < m_variable_size; ++i)
				{
					temp += x[i] * x[i] - 10 * cos(2 * OFEC_PI*x[i]) + 10;
				}
				ineq_cons.push_back(temp);
				temp = 0.;

				for (i = 0; i < m_variable_size; ++i)
				{
					temp += x[i];
				}
				temp -= 2 * m_variable_size;
				ineq_cons.push_back(temp);
				temp = 0.;
				for (i = 0; i < m_variable_size; ++i)
				{
					temp += x[i];
				}
				temp = 5 - temp;
				ineq_cons.push_back(temp);
				for (auto &i : ineq_cons) {
					if (i <= 0) i = 0;
					sum += i;
				}

				cons = sum / (double)ineq_cons.size();
			}
		}
	}
}
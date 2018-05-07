#include "C14.h"

namespace OFEC {
	namespace CEC2017 {
		C14::C14(param_map &v) :
			C14((v.at("proName")), (v.at("numDim")), 1) {
			
		}
		C14::C14(const std::string &name, size_t size_var, size_t size_obj) :problem(name, size_var, size_obj), \
			function(name, size_var, size_obj) {
			
		}

		void C14::initialize() {
			m_variable_monitor = true;
			set_range(-100., 100.);
			set_init_range(-100., 100.);

			 
			
			load_translation("instance/problem/continuous/constrained/CEC2017/data/");  //data path
			set_original_global_opt(m_translation.data());
			m_optima = m_original_optima;
		}
		void C14::evaluate__(real *x, std::vector<real>& obj, double & cons_value, std::vector<double> &cons_values) {
			
			for (size_t i = 0; i < m_variable_size; ++i)
				x[i] -= m_translation[i];
			

			size_t i;
			real num1=0., num2=0.;
			obj[0] = 0.;
			for (i = 0; i<m_variable_size; ++i)
			{
				num1 += x[i] * x[i];
			}
			num1 = sqrt(num1 / m_variable_size);
			for (i = 0; i<m_variable_size; ++i)
			{
				num2 += cos(2 * OFEC_PI*x[i]);
			}
			num2 /= m_variable_size;
			obj[0] = -20 * exp(-0.2*num1) + 20 - exp(num2) + exp(1.0);
			obj[0] += m_bias;

			
			double temp = 0.;
			double sum1 = 0., sum2 = 0.;

			std::vector<double> eq_cons;
			std::vector<double> ineq_cons;

			for (i = 0; i < m_variable_size; ++i)
			{
				temp += x[i] * x[i];
			}
			temp -= 4;
			eq_cons.push_back(temp);
			temp = 0.;
			for (auto &i : eq_cons) {
				if (fabs(i) - 1e-4 <= 0) i = 0;
				else i = fabs(i);
				sum1 += i;
			}


			for (i = 1; i < m_variable_size; ++i)
			{
				temp += pow(x[i],2);
			}
			temp += 1 - fabs(x[0]);
			ineq_cons.push_back(temp);
			temp = 0.;

			for (auto &i : ineq_cons) {
				if (i <= 0) i = 0;
				sum2 += i;
			}
			cons_values.clear();
			for (auto &i : ineq_cons)
				cons_values.push_back(i);
			for (auto &i : eq_cons)
				cons_values.push_back(i);
			cons_value = (sum1 + sum2) / (double)(eq_cons.size() + ineq_cons.size());
			
		}
	}
}
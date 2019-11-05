
#include "F6_hybrid1.h"
#include "../../global/classical/modified_schwefel.h"
#include "../../global/classical/rastrigin.h"
#include "../../global/classical/elliptic.h"
namespace OFEC {
	namespace CEC2015 {
		F6_hybrid1::F6_hybrid1(param_map &v) :
			F6_hybrid1((v.at("proName")), (v.at("numDim")), 1) {
			
			
		}
		F6_hybrid1::F6_hybrid1(const std::string &name, size_t size_var, size_t size_obj) :problem(name, size_var, size_obj), \
			hybrid(name, size_var, size_obj) {
			
			
		}

		void F6_hybrid1::initialize() {
			m_variable_monitor = true;
			m_num_function = 3;
			m_function.resize(m_num_function);
			m_start.resize(m_num_function);
			m_dim.resize(m_num_function);
			set_range(-100., 100.);
			set_init_range(-100., 100.);
			set_function();
			size_t count = 0;
			for (auto &i : m_random_perm)
				i = count++;
			global::ms_global->m_uniform[caller::Problem]->shuffle(m_random_perm.begin(), m_random_perm.end());
			// Set optimal solution
            solution<variable_vector<real>, real> s(m_objective_size, num_constraints(), m_variable_size);
			for (size_t i = 0; i < m_variable_size; ++i) {
				s.variable()[i] = 0;
			}
			m_optima.append(s.variable());

            s.evaluate(false, caller::Problem);
            m_optima.append(s.objective());
			// end set
			m_initialized = true;

		}
		void F6_hybrid1::set_function() {
			size_t i, tmp;
			real f_p[3] = { 0.3,0.3,0.4 };
			basic_func f(3);
			f[0] = &create_function<modified_schwefel>;
			f[1] = &create_function<rastrigin>;
			f[2] = &create_function<elliptic>;

			tmp = 0;
			for (i = 0; i<m_num_function - 1; ++i)
			{
				m_dim[i] = (size_t)ceil(f_p[i] * m_variable_size);
				tmp += m_dim[i];
			}
			m_dim[m_num_function - 1] = m_variable_size - tmp;
			m_start[0] = 0;
			for (i = 1; i<m_num_function; ++i)
			{
				m_start[i] = m_start[i - 1] + m_dim[i - 1];
			}
			for (size_t i = 0; i < m_num_function; ++i) {
				m_function[i] = dynamic_cast<function*>(f[i]("", m_dim[i], m_objective_size));
				m_function[i]->initialize();
				m_function[i]->set_bias(0);
			}
		}


		void F6_hybrid1::evaluate_objective(real *x, std::vector<real> &obj) {
			hybrid::evaluate_objective(x, obj);
			obj[0] += 600;
		}


	}
}

#include "ShiftedRosenbrock_F12.h"
namespace OFEC {
	namespace CEC2013 {
		ShiftedRosenbrock_F12::ShiftedRosenbrock_F12(param_map &v) : 
			ShiftedRosenbrock_F12((v.at("proName")), (v.at("numDim")), 1) \
		{
			
		}

		ShiftedRosenbrock_F12::ShiftedRosenbrock_F12(const std::string &name, size_t size_var, size_t size_obj) : problem(name, size_var, size_obj), \
			function_CEC2013(name, size_var, size_obj) \
		{
			
		}

		ShiftedRosenbrock_F12::~ShiftedRosenbrock_F12() {
			delete[] mp_Ovector;

			delete[] mp_anotherz;

		}

		void ShiftedRosenbrock_F12::initialize() {
			m_variable_monitor = true;
			set_range(-100, 100);
			set_init_range(-100, 100);
			ID = 12;
			mp_anotherz = new real[m_variable_size];

			// Ovector = createShiftVector(dimension,minX,maxX);
			mp_Ovector = readOvector();

			//set_original_global_opt();
			std::vector<real> data(m_variable_size,1);
			for (size_t i = 0; i < m_variable_size; ++i)
				data[i] += mp_Ovector[i];
			set_global_opt(data.data());
			m_initialized = true;
		}

		void ShiftedRosenbrock_F12::evaluate_objective(real *x, std::vector<real> &obj) {
			int i;
			real result = 0.0;

			for (i = 0; i < m_variable_size; i++)
			{
				mp_anotherz[i] = x[i] - mp_Ovector[i];
			}

			result = rosenbrock(mp_anotherz, m_variable_size);

			obj[0] = result;
		}
	}
}

#include "ShiftedSchwefel_F15.h"
namespace OFEC {
	namespace CEC2013 {
		ShiftedSchwefel_F15::ShiftedSchwefel_F15(param_map &v) : 
			ShiftedSchwefel_F15((v.at("proName")), (v.at("numDim")), 1) \
		{
			
		}

		ShiftedSchwefel_F15::ShiftedSchwefel_F15(const std::string &name, size_t size_var, size_t size_obj) : problem(name, size_var, size_obj), \
			function_CEC2013(name, size_var, size_obj) \
		{
			
		}

		ShiftedSchwefel_F15::~ShiftedSchwefel_F15() {
			delete[] mp_Ovector;

			delete[] mp_anotherz;

		}

		void ShiftedSchwefel_F15::initialize() {
			m_variable_monitor = true;
			set_range(-100, 100);
			set_init_range(-100, 100);
			ID = 15;
			mp_anotherz = new real[m_variable_size];

			// Ovector = createShiftVector(dimension,minX,maxX);
			mp_Ovector = readOvector();

			//set_original_global_opt();	
			set_global_opt(mp_Ovector);
			m_initialized = true;
		}

		void ShiftedSchwefel_F15::evaluate_objective(real *x, std::vector<real> &obj) {
			int i;
			real result = 0.0;



			for (i = 0; i < m_variable_size; i++)
			{
				mp_anotherz[i] = x[i] - mp_Ovector[i];
			}

			result = schwefel(mp_anotherz, m_variable_size);

			obj[0] = result;
		}
	}
}

#include "N7S1_SR_Elliptic_F4.h"
namespace OFEC {
	namespace CEC2013 {
		N7S1_SR_Elliptic_F4::N7S1_SR_Elliptic_F4(param_map &v) : 
			N7S1_SR_Elliptic_F4((v.at("proName")), (v.at("numDim")), 1) \
		{
			
		}

		N7S1_SR_Elliptic_F4::N7S1_SR_Elliptic_F4(const std::string &name, size_t size_var, size_t size_obj) : problem(name, size_var, size_obj), \
			function_CEC2013(name, size_var, size_obj) \
		{
			
		}

		N7S1_SR_Elliptic_F4::~N7S1_SR_Elliptic_F4() {
			delete[] mp_Ovector;
			delete[] mp_Pvector;
			delete[] mp_anotherz;

			for (int i = 0; i < 25; ++i)
				delete[] mpp_r25[i];
		
			for (int i = 0; i < 50; ++i)
				delete[] mpp_r50[i];
			
			for (int i = 0; i < 100; ++i)
				delete[] mpp_r100[i];
			
			delete[] mpp_r25;
			delete[] mpp_r50;
			delete[] mpp_r100;
			delete[] mp_s;
			delete[] mp_w;
		}

		void N7S1_SR_Elliptic_F4::initialize() {
			m_variable_monitor = true;
			set_range(-100, 100);
			set_init_range(-100, 100);
			ID = 4;
			m_nonSeparableGroupNumber = 7;
			mp_anotherz = new real[m_variable_size];

			// Ovector = createShiftVector(dimension,minX,maxX);
			mp_Ovector = readOvector();
			mp_Pvector = readPermVector();
			mpp_r25 = readR(25);
			mpp_r50 = readR(50);
			mpp_r100 = readR(100);
			mp_s = readS(m_nonSeparableGroupNumber);
			mp_w = readW(m_nonSeparableGroupNumber);

			set_original_global_opt();
			set_global_opt(mp_Ovector);
			m_initialized = true;
		}

		void N7S1_SR_Elliptic_F4::evaluate_objective(real *x, std::vector<real> &obj) {
			size_t    i;
			real result(0.);
			for (i = 0; i < m_variable_size; ++i) {
				mp_anotherz[i] = x[i] - mp_Ovector[i];
			}

			size_t c = 0;
			for (i = 0; i < m_nonSeparableGroupNumber; i++)
			{
				mp_anotherz1 = rotate_vector(i, c);
				result += mp_w[i] * elliptic(mp_anotherz1, mp_s[i]);
				delete[] mp_anotherz1;
			}

			// one separable part without rotation
			real* z = new real[m_variable_size - c];
			for (i = c; i < m_variable_size; i++)
			{
				z[i - c] = mp_anotherz[mp_Pvector[i]];
			}

			result += elliptic(z, m_variable_size - c);
			delete[] z;
			obj[0] = result;
		}
	}
}
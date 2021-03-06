#include "quadratic_assignment.h"
#include <fstream>
#include <cstring>
#include <cstdlib>
namespace OFEC {
	quadratic_assignment::quadratic_assignment(param_map & v) :quadratic_assignment(v.at("proName"), v.at("numDim"), v.at("dataFile1"))
	{

	}

	quadratic_assignment::quadratic_assignment(const std::string& pro_name, size_t size_var, const std::string& file_name)
		:problem(pro_name, size_var, 1), m_domain(m_variable_size)
	{
		m_file_name = file_name;
	}

	quadratic_assignment::~quadratic_assignment() = default;

	void quadratic_assignment::initialize() {
		mvv_flow.resize(m_variable_size);
		mvv_distance.resize(m_variable_size);
		for (size_t i = 0; i < m_variable_size; i++) {
			mvv_flow[i].resize(m_variable_size);
			mvv_distance[i].resize(m_variable_size);
		}
		
		read_problem();

		for (size_t i = 0; i < m_variable_size; ++i)
			m_domain.set_range(0, m_variable_size - 1, i);

		global::ms_sample_fre  = m_variable_size * 2;
		m_initialized = true;
	}
	evaluation_tag quadratic_assignment::evaluate_(solution_base & s, caller call, bool effective, bool constructed)
	{
		variable_vector<int> &x = dynamic_cast< solution<variable_vector<int>, real> &>(s).variable();
		std::vector<real> &obj = dynamic_cast< solution<variable_vector<int>, real> &>(s).objective();

		for (size_t i = 0; i<m_objective_size; i++)
			obj[i] = 0;
		int row, col;
		for (size_t n = 0; n<m_objective_size; n++)
		{
			for (size_t i = 0; i<m_variable_size; i++)
			{
				row = x[i];
				for (size_t j = 0; j < m_variable_size; j++) {
					col = x[j];
					obj[n] += mvv_distance[i][j] * mvv_flow[row][col];
				}
			}
		}

		if (constructed) {
			if (effective)		m_effective_eval++;
			m_optima.is_optimal_objective(obj, m_objective_accuracy);
			if (m_optima.is_objective_found())
				m_solved = true;
			if (call == caller::Algorithm&& global::ms_global->m_algorithm&&global::ms_global->m_algorithm->terminating())
				return evaluation_tag::Terminate;
		}
		return evaluation_tag::Normal;
	}

	bool quadratic_assignment::is_valid(const solution_base & s) const
	{
		if (!m_if_valid_check) 
			return true;

		const variable_vector<int> &x = dynamic_cast<const solution<variable_vector<int>, real> &>(s).variable();

		for (int i = 0; i < m_variable_size; i++)  //judge the range		
			if ((x[i]) < m_domain.range(i).limit.first || (x[i]) > m_domain.range(i).limit.second)
				return false;
	
		std::vector<int> flag(m_variable_size, 0);  //judge whether has the same gene
		int temp;
		for (int i = 0; i<m_variable_size; i++)
		{
			temp = x[i];
			flag[temp] = 1;
		}
		for (int i = 0; i<m_variable_size; i++)
			if (flag[i] == 0)
				return false;
		return true;
	}
	void quadratic_assignment::read_problem()
	{
#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__APPLE__)
#define	strtok_s strtok_r
#endif
		size_t i;
		std::string Line;
		char *Keyword = nullptr;
		const char *Delimiters = " ():=\n\t\r\f\v\xef\xbb\xbf";
		std::ostringstream oss;
		std::ifstream infile;
		oss << "./instance/problem/combination/QAP/data/" << m_file_name << ".qap";
		infile.open(oss.str().c_str());
		if (!infile) {
			throw myexcept("read Quadratic Assignment data error");
		}
		char *savePtr;
		while (getline(infile, Line))
		{
			if (!(Keyword = strtok_s((char*)Line.c_str(), Delimiters, &savePtr)))
				continue;
			for (i = 0; i<strlen(Keyword); i++)
				Keyword[i] = toupper(Keyword[i]);
			if (!strcmp(Keyword, "DIM"))
			{
				char *token = strtok_s(nullptr, Delimiters, &savePtr);
				m_variable_size = atoi(token);
			}
			else if (!strcmp(Keyword, "FLOW"))
			{
				for (size_t n = 0; n < m_variable_size; n++)
					for (i = 0; i < m_variable_size; i++)
						infile >> mvv_flow[n][i];
			}
			else if (!strcmp(Keyword, "DISTANCE"))
			{
				for (size_t n = 0; n < m_variable_size; n++)
					for (i = 0; i < m_variable_size; i++)
						infile >> mvv_distance[n][i];
			}
			else if (!strcmp(Keyword, "OPT_OBJ"))
			{
				char *token = strtok_s(nullptr, Delimiters, &savePtr);
				m_optima.append(std::vector<real>(1, atof(token)));
			}
			else if (!strcmp(Keyword, "OPT_SOLUTION"))
			{
				getline(infile, Line);
				std::istringstream ss(Line);
				variable_vector<int> temp(m_variable_size);
				for (i = 0; i < m_variable_size; ++i) {
					ss >> temp[i];
				}
				m_optima.append(temp);
			}
		}
		infile.close();
		infile.clear();
	}
	bool quadratic_assignment::get_optimal_obj(std::vector<real>& opt)
	{
		if (m_optima.objective_given()) {
			opt = m_optima.objective();
			return true;
		}
		return false;
	}

	bool quadratic_assignment::get_optimal_obj(std::vector<std::vector<real>>& opt)
	{
		if (m_optima.objective_given()) {
			opt.clear();
			for (size_t i = 0; i<m_optima.number_objective(); ++i)
				opt.push_back(m_optima.objective(i));
			return true;
		}
		return false;
	}

	const optima<variable_vector<int>, real>& quadratic_assignment::get_optima() const
	{
		return m_optima;
	}
	optima<variable_vector<int>, real>& quadratic_assignment::get_optima()
	{
		return m_optima;
	}
	bool quadratic_assignment::is_optima_given()
	{
		return (m_optima.variable_given() || m_optima.objective_given());
	}
	quadratic_assignment * quadratic_assignment::get_type_ptr()
	{
		return this;
	}
	quadratic_assignment & quadratic_assignment::get_type_ref()
	{
		return *this;
	}
	bool quadratic_assignment::is_optima_found()
	{
		if (is_optima_given()) {
			if (m_optima.is_variable_found() || m_optima.is_objective_found()) 
				return true;
		}
		return false;
	}
	void quadratic_assignment::initialize_solution(solution_base &s) const
	{
		variable_vector<int>& x = dynamic_cast< solution<variable_vector<int>, real>&>(s).variable();
		std::vector<int> temp;
		int i, pos, num = x.size();
		for (i = 0; i<num; i++)
			temp.push_back(int(i));
		for (i = 0; i<num; i++)
		{
			pos = int((num - 1 - i) * global::ms_global->m_uniform[caller::Problem]->next());
			x[i] = temp[pos];
			temp[pos] = temp[num - 1 - i];
		}
		if (!is_valid(s))
			throw myexcept("error in @quadratic_assignment::initialize_solution() in quadratic_assignment.cpp");
	}
	bool quadratic_assignment::same(const solution_base & s1, const solution_base & s2) const
	{
		const variable_vector<int> &x1 = dynamic_cast<const solution<variable_vector<int>, real> &>(s1).variable();
		const variable_vector<int> &x2 = dynamic_cast<const solution<variable_vector<int>, real> &>(s2).variable();
		for (int i = 0; i < m_variable_size; i++)
			if (x1[i] != x2[i])
				return false;
		return true;
	}

	real quadratic_assignment::variable_distance(const solution_base & s1, const solution_base & s2) const
	{
		const variable_vector<int> &x1 = dynamic_cast<const solution<variable_vector<int>, real> &>(s1).variable();
		const variable_vector<int> &x2 = dynamic_cast<const solution<variable_vector<int>, real> &>(s2).variable();
		real dis = 0;
		for (int i = 0; i < m_variable_size; i++)
			if (x1[i] != x2[i])
				dis++;
		return dis;
	}

	real quadratic_assignment::variable_distance(const variable_base & s1, const variable_base & s2) const
	{
		const auto &x1 = dynamic_cast<const variable_vector<int>&>(s1);
		const auto &x2 = dynamic_cast<const variable_vector<int>&>(s2);
		real dis = 0;
		for (int i = 0; i < m_variable_size; i++)
			if (x1[i] != x2[i])
				dis++;
		return dis;
	}
}
/******************************************************************************
* Project:Open Frameworks for Evolutionary Computation (OFEC)
*******************************************************************************
* Author: Changhe Li
* Email: changhe.lw@gmail.com
* Language: C++
*-------------------------------------------------------------------------------
*  This file is part of OFEC. This library is free software;
*  you can redistribute it and/or modify it under the terms of the
*  GNU General Public License as published by the Free Software
*  Foundation; either version 2, or (at your option) any later version.
*
*  see https://github.com/Changhe160/OFEC for more information
*
*-------------------------------------------------------------------------------
* The vector-based objective_ encoding schme and a vector-based variable_ encoding scheme
* is defined.
*
*********************************************************************************/

#ifndef OFEC_ENCODING_H
#define OFEC_ENCODING_H

#include <vector>
#include <functional>

namespace OFEC {
	class solution_base {
	public:
		virtual evaluation_tag evaluate(bool=true, caller= caller::Algorithm) = 0;
		virtual ~solution_base() {};
		solution_base(const solution_base&) = default;
		solution_base(solution_base&&) = default;
		solution_base() = default;
		solution_base& operator=(const solution_base&) = default;
		solution_base& operator=(solution_base&&) = default;
	};


//	template<typename T = real>
//	class objective_vector {
//	public:
//		using value_type = T;
//		using encoding = std::vector<value_type>;
//		using iterator_type = typename std::vector<value_type>::iterator;
//		using const_iterator = typename std::vector<value_type>::const_iterator;
//		explicit objective_vector(size_t n=0) :m_o(n) {}
//		objective_vector(const objective_vector& rhs) = default;
//		explicit objective_vector(const std::vector<value_type>& rhs) :m_o(rhs) {}
//		objective_vector& operator=(const objective_vector& rhs) = default;
//		objective_vector& operator=(objective_vector&& rhs) noexcept = default;
//		objective_vector(objective_vector&& rhs) noexcept = default;
//
//		void resize(size_t n) {
//			m_o.resize(n);
//		}
//		std::vector<value_type>& vect() noexcept {
//			return m_o;
//		}
//		const std::vector<value_type>& vect() const noexcept {
//			return m_o;
//		}
//
//		value_type& operator[](size_t n) {
//			return m_o[n];
//		}
//
//		const value_type& operator[](size_t n)const {
//			return m_o[n];
//		}
//
//		iterator_type begin() noexcept {
//			return m_o.begin();
//		}
//
//		const_iterator begin() const noexcept {
//			return m_o.cbegin();
//		}
//
//		iterator_type end() noexcept {
//			return m_o.end();
//		}
//
//		const_iterator end() const noexcept {
//			return m_o.cend();
//		}
//
//		size_t size() const noexcept{
//			return m_o.size();
//		}
//	protected:
//		std::vector<value_type> m_o;
//
//	};

	class variable_base {
	public:
		virtual ~variable_base() = default;
	};

	template <typename VariableType>
	class variable_vector:public variable_base {
	public:
		using value_type = VariableType;
		using encoding = std::vector<value_type>;
		using iterator_type = typename std::vector<value_type>::iterator;
		using const_iterator = typename std::vector<value_type>::const_iterator;
		explicit variable_vector(size_t n=0) :m_x(n){}
		variable_vector(size_t n, const VariableType& val) : m_x(n, val) {}
		variable_vector(const variable_vector& rhs) = default;
		variable_vector(variable_vector&& rhs) noexcept = default;
		explicit variable_vector(const std::vector<value_type>& x) : m_x(x) {}
		variable_vector& operator=(const variable_vector& rhs) = default;
		variable_vector& operator=(variable_vector&& rhs) noexcept = default;

		void resize(size_t n) {
			m_x.resize(n);
		}
		size_t size() const noexcept {
			return m_x.size();
		}

		iterator_type begin() noexcept {
			return m_x.begin();
		}

		iterator_type end() noexcept {
			return m_x.end();
		}
		
		const_iterator begin() const noexcept {
			return m_x.begin();
		}

		const_iterator end() const noexcept {
			return m_x.end();
		}

		const value_type& operator[](size_t i)const{
			return m_x[i];
		}
		value_type& operator[](size_t i){
			return m_x[i];
		}
		value_type* data() noexcept {
			return m_x.data();
		}
		const value_type* data() const noexcept {
			return m_x.data();
		}
		std::vector<value_type>& vect() noexcept{
			return m_x;
		}
		const std::vector<value_type>& vect() const noexcept {
			return m_x;
		}
	protected:
		std::vector<value_type> m_x;
	};

}

#endif // !OFEC_ENCODING_H


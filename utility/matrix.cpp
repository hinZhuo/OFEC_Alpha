#include "matrix.h"
#include "myexcept.h"

namespace OFEC {

	matrix::matrix(int dim) :m_col_size(dim), m_row_size(dim) {
		if (m_row_size == 0) return;
		resize(m_row_size, m_col_size);
		m_eigen_value = new double[m_row_size];
		m_eigen_vector = new double*[m_row_size];
		for (int i = 0; i< m_row_size; i++)
		{
			m_eigen_vector[i] = new double[m_row_size];
		}
	}
	matrix::matrix(int r, int c) : m_col_size(c), m_row_size(r) {
		resize(m_row_size, m_col_size);
		m_eigen_value = new double[m_row_size];
		m_eigen_vector = new double*[m_row_size];
		for (int i = 0; i< m_row_size; i++)
		{
			m_eigen_vector[i] = new double[m_row_size];
		}
	}

	matrix::~matrix() {
		for (int i = 0; i < m_row_size; ++i)
		{
			delete[] m_eigen_vector[i];
			m_eigen_vector[i] = nullptr;
		}
		delete[] m_eigen_value;
		m_eigen_value = nullptr;
	}
	void matrix::set_row(const double *d, const int c, const int r) {
		if (r != m_row_size) return;
		for (int i = 0; i<m_row_size; i++)
			for (int j = 0; j<m_col_size; j++)
				m_row[i][j] = d[j];
	}
	void matrix::set_col(const double *d, const int r, const int c) {
		if (c != m_col_size) return;
		for (int i = 0; i<m_row_size; i++)
			for (int j = 0; j<m_col_size; j++)
				m_row[i][j] = d[i];

	}
	void matrix::set(const double * const * d) {
		for (int i = 0; i<m_row_size; i++)
			for (int j = 0; j<m_col_size; j++)
				m_row[i][j] = d[i][j];
	}

	matrix & matrix::operator *=(const matrix &m) {
		//TODO: GPU computing
		if (m_col_size != m.m_row_size) throw myexcept("can not *, m_col_size of 1st matrix must be equal to m_row_size of 2nd matrix@ matrix::operator *=");

		matrix r(m.m_col_size, m_row_size);
		for (int i = 0; i<m_row_size; i++) {
			for (int j = 0; j<m.m_col_size; j++) {
				r.m_row[i][j] = 0;
				for (int k = 0; k<m_col_size; k++)
					r.m_row[i][j] += m_row[i][k] * m.m_row[k][j];
			}
		}
		if (m_row_size != m.m_row_size || m_col_size != m.m_col_size) {
			clear();
			resize(r.m_row_size, r.m_col_size);
		}
		copy(r.m_row.begin(), r.m_row.end(), this->m_row.begin());

		return *this;
	}
	matrix & matrix::operator *=(double x) {
		for (int i = 0; i<m_row_size; i++) {
			m_row[i] *= x;
		}
		return *this;
	}

	matrix&matrix::operator =(const matrix &m) {
		if (m_row_size != m.m_row_size || m_col_size != m.m_col_size) {
			throw myexcept("Assiment operator matrix@matrix::operator =");
		}
		if (this == &m) return *this;
		m_row = m.m_row;
		return *this;
	}
	bool matrix::identify() {
		if (m_row_size != m_col_size) return false;
		for (int i = 0; i<m_row_size; i++)
			for (int j = 0; j<m_col_size; j++)
				m_row[i][j] = (j == i);

		return true;
	}
	bool matrix::is_identity() {
		if (m_row_size != m_col_size) return false;
		for (int i = 0; i<m_row_size; i++) {
			for (int j = 0; j<m_col_size; j++) {
				if (m_row[i][j] != (i == j ? 1. : 0)) {
					return false;
				}
			}
		}
		return true;
	}
	void matrix::diagonalize(normal * rand, double CondiNum) {
		if (m_row_size != m_col_size) throw myexcept("can not be diagonal, matrix must be squre@matrix::diagonalize");

		double min, max;
		double *r = new double[m_row_size];
		for (int i = 0; i < m_row_size; i++)	r[i] = rand->next_non_standard(1., m_row_size*1.0);

		min = max = r[0];
		for (int i = 0; i < m_row_size; i++) {
			if (min > r[i])min = r[i];
			if (max < r[i]) max = r[i];
		}
		for (int i = 0; i < m_row_size; i++) {
			for (int j = 0; j < m_col_size; j++)
				if (j != i) m_row[i][j] = 0.;
				else m_row[i][j] = pow(CondiNum, (r[i] - min) / (max - min));
		}
		delete[]r;

	}
	void matrix::zero() {
		for (int i = 0; i<m_row_size; i++)
			for (int j = 0; j<m_col_size; j++)
				m_row[i][j] = 0.;
	}
	void matrix::set_rotation_axes(int r, int c, double angle) {
		identify();
		m_row[r][r] = cos(angle);
		m_row[r][c] = -sin(angle);
		m_row[c][r] = sin(angle);
		m_row[c][c] = cos(angle);
	}


	void matrix::generate_rotation(normal *rand, double CondiNum) {
		/*P. N. Suganthan, N. Hansen, J. J. Liang, K. Deb, Y.-P. Chen, A. Auger and S. Tiwari,
		"Problem Definitions and Evaluation Criteria for the CEC 2005 Special Session on Real-Parameter
		Optimization", Technical Report, Nanyang Technological University, Singapore, May 2005 AND KanGAL
		Report #2005005, IIT Kanpur, India.*/

		matrix ortholeft(m_row_size), orthoright(m_row_size), diagonal(m_row_size);
		ortholeft.randomize(rand);
		ortholeft.orthonormalize();
		orthoright.randomize(rand);
		orthoright.orthonormalize();
		diagonal.diagonalize(rand, CondiNum);
		ortholeft *= diagonal;
		ortholeft *= orthoright;
		*this = ortholeft;
	}

	void matrix::randomize(uniform * rand, real min, real max) {
		for (int i = 0; i<m_row_size; i++)
			m_row[i].randomize(rand, min, max);
	}
	void matrix::randomize(normal *rand) {
		for (int i = 0; i<m_row_size; i++)
			m_row[i].randomize(rand);
	}

	void matrix::orthonormalize() {
		if (m_row_size != m_col_size) throw myexcept("cannot perform orthonormalization, matrix must be squre@matrix::orthonormalize");
		//if (!(is_inverse())) throw myexcept("cannot perform function orthonormalize(), matrix must be reversible@matrix::orthonormalize");
		Vector v(m_col_size), q(m_col_size);
		double r = 0;
		//modified Gram schmidt process
		for (int i = 0; i<m_row_size; i++) {
			v = m_row[i];
			q = m_row[i];
			for (int j = 0; j<i; j++) {
				r = v * m_row[j];
				v -= m_row[j] * r;
			}
			r = v.length();
			m_row[i] = v / r;
		}
		// normalize each vector
		for (int i = 0; i < m_row_size; i++) m_row[i].normalize();
	}
	bool matrix::is_orthogonal() {
		/*if (m_row_size != m_col_size) throw myexcept("cannot perform function is_orthogonal(), matrix must be squre@matrix::orthonormalize");
		matrix temp1 = *this;
		temp1.transpose();
		const matrix& temp2 = temp1;
		temp1 *= temp2;
		return temp1.is_identity();*/
		if (m_row_size != m_col_size) throw myexcept("cannot perform function is_orthogonal(), matrix must be squre@matrix::is_orthogonal");

		for (int i = 0; i < m_row_size; i++) {
			for (int j = i + 1; j < m_row_size; j++) {
				if (fabs(m_row[i] * m_row[j]) > 1e-4) return false;
			}
			if (m_row[i].length()!=1.) return false;
		}
		return true;
	}
	void matrix::transpose() {
		std::vector<Vector> temp(m_col_size, Vector(m_row_size));
		for (int i = 0; i<m_row_size; i++)
			for (int j = 0; j<m_col_size; j++) {
				temp[j][i] = m_row[i][j];
			}
		m_row = std::move(temp);
	}

	void matrix::inverse() {
		if (m_row_size != m_col_size) throw myexcept("cannot perform function inverse(), matrix must be squre@matrix::inverse");
		if(!(is_inverse())) throw myexcept("cannot perform function inverse(), matrix must be reversible@matrix::inverse");
		if (is_diagonal()) {
			for (int i = 0; i < m_row_size; i++)
				if (m_row[i][i] != 0)m_row[i][i] = 1. / m_row[i][i];
		}
		else {
			double **a;

			a = new double*[m_row_size];
			for (int i = 0; i < m_row_size; i++) a[i] = new double[2 * m_col_size];

			for (int i = 0; i < m_row_size; i++) {
				for (int j = 0; j < m_col_size; j++) {
					a[i][j] = m_row[i][j];
				}
			}

			for (int i = 0; i < m_row_size; i++) {
				for (int j = m_col_size; j < m_col_size * 2; j++)
					a[i][j] = (j - i == m_col_size) ? (1.0) : (0.0);
			}

			for (int i = 0; i < m_row_size; i++)
			{
				if (a[i][i] != 1.0)
				{
					double tmp = a[i][i];
					a[i][i] = 1.0;
					for (int j = i; j < m_col_size * 2; j++)
						a[i][j] /= tmp;
				}
				for (int k = 0; k < m_row_size; k++)
				{
					if (i != k)
					{
						double tmp = a[k][i];
						for (int j = 0; j < m_col_size * 2; j++)
							a[k][j] -= (tmp*a[i][j]);
					}
					else continue;
				}
			}

			for (int i = 0; i < m_row_size; i++) {
				for (int j = m_col_size; j < m_col_size * 2; j++)
					m_row[i][j - m_col_size] = a[i][j];
			}

			for (int i = 0; i < m_row_size; i++) delete[] a[i];
			delete[] a;
		}
	}

	std::vector<Vector>& matrix::data() {
		return m_row;
	}

	bool matrix::is_inverse() {
		
		return !(fabs(determinant()) <= 1e-8);
	}

	double matrix::determinant() {
		if (m_row_size != m_col_size) throw myexcept("cannot perform function determinant(), matrix must be squre@matrix::determinant");
		if (m_is_det_flag) return m_det;
		m_det = determinant_(m_row, m_col_size);
		m_is_det_flag = true;
	}

	double matrix::determinant_(std::vector<Vector>& temp, int num ) {
		
		int i = 0, j = 0, c = 0; /*i，j为行与列,c为向量b的行*/
		std::vector<Vector> temp_b(m_row_size, Vector(m_col_size, 0.)); /*定义向量b并初始化*/
		int p = 0, q = 0;/*p,q为中间变量*/
		double sum = 0;

		if (num == 1)
			return temp[0][0];
		for (i = 0; i<num; i++)/*此处大循环实现将余子式存入向量b中*/
		{
			for (c = 0; c<num - 1; c++)
			{
				if (c<i)    /*借助c判断每行的移动方法*/
					p = 0;

				else
					p = 1;

				for (j = 0; j<num - 1; j++)
				{
					temp_b[c][j] = temp[c + p][j + 1];
				}
			}
			if (i % 2 == 0)  q = 1;
			else  q = (-1);

			sum = sum + temp[i][0] * q*determinant_(temp_b, num - 1);
		}
		//m_is_det_flag = true;
		return sum;
		
	}
	void matrix::clear() {
		m_row.clear();
	}
	void matrix::resize(int row, int col) {
		m_col_size = col;
		m_row_size = row;
		m_row.resize(row);
		for (int i = 0; i<row; i++)
			m_row[i].resize(col);

	}

	Vector & matrix::operator[](const int idx) {
		return m_row[idx];
	}

	const Vector & matrix::operator[](const int idx)const {
		return m_row[idx];
	}


	void matrix::diagonalize(double alpha) {
		for (int i = 0; i<m_row_size; i++) {
			for (int j = 0; j < m_col_size; j++)
				if (i == j) m_row[i][j] = pow(alpha, 0.5*(i / (m_col_size - 1)));
				else m_row[i][j] = 0;
		}
	}

	bool matrix::is_diagonal() {
		if (m_row_size != m_col_size) throw myexcept("cannot perform function is_diagonal(), matrix must be squre@matrix::is_diagonal");
		for (int i = 0; i<m_row_size; i++) {
			for (int j = 0; j < m_col_size; j++) {
				if (i == j) continue;
				if (!(fabs(m_row[i][j]) < 1e-8)) return false;
			}
		}
		return true;
	}

	void matrix::eigendecomposition() {
		/*
		Calculating eigenvalues and vectors.
		Input:
		N: dimension.
		C: symmetric (1:N)xN-matrix, solely used to copy data to Q
		niter: number of maximal iterations for QL-Algorithm.
		rgtmp: N+1-dimensional vector for temporal use.
		Output:
		diag: N eigenvalues.
		Q: Columns are normalized eigenvectors.
		*/
	
	
		double* temp_vec = new double[m_row_size + 1];
		
		

		//std::vector<Vector> temp_row(m_row_size,Vector(m_col_size));
		for (int i = 0; i<m_row_size; i++) {
			for (int j = 0; j < m_col_size; j++) {
				m_eigen_vector[i][j] = m_row[i][j];
			}
		}

		Householder2(m_row_size, m_eigen_vector, m_eigen_value, temp_vec);
		QLalgo2(m_row_size, m_eigen_value, temp_vec, m_eigen_vector);

		delete[] temp_vec;
		temp_vec = nullptr;
		
	}

	void matrix::Householder2(int n, double **V, double *d, double *e) {
		/*
		Householder transformation of a symmetric matrix V into tridiagonal form.
		-> n             : dimension
		-> V             : symmetric nxn-matrix
		<- V             : orthogonal transformation matrix:
		tridiag matrix == V * V_in * V^t
		<- d             : diagonal
		<- e[0..n-1]     : off diagonal (elements 1..n-1)

		code slightly adapted from the Java JAMA package, function private tred2()

		*/

		int i, j, k;

		for (j = 0; j < n; j++) {
			d[j] = V[n - 1][j];
		}

		/* Householder reduction to tridiagonal form */

		for (i = n - 1; i > 0; i--) {

			/* Scale to avoid under/overflow */

			double scale = 0.0;
			double h = 0.0;
			for (k = 0; k < i; k++) {
				scale = scale + fabs(d[k]);
			}
			if (scale == 0.0) {
				e[i] = d[i - 1];
				for (j = 0; j < i; j++) {
					d[j] = V[i - 1][j];
					V[i][j] = 0.0;
					V[j][i] = 0.0;
				}
			}
			else {

				/* Generate Householder vector */

				double f, g, hh;

				for (k = 0; k < i; k++) {
					d[k] /= scale;
					h += d[k] * d[k];
				}
				f = d[i - 1];
				g = sqrt(h);
				if (f > 0) {
					g = -g;
				}
				e[i] = scale * g;
				h = h - f * g;
				d[i - 1] = f - g;
				for (j = 0; j < i; j++) {
					e[j] = 0.0;
				}

				/* Apply similarity transformation to remaining columns */

				for (j = 0; j < i; j++) {
					f = d[j];
					V[j][i] = f;
					g = e[j] + V[j][j] * f;
					for (k = j + 1; k <= i - 1; k++) {
						g += V[k][j] * d[k];
						e[k] += V[k][j] * f;
					}
					e[j] = g;
				}
				f = 0.0;
				for (j = 0; j < i; j++) {
					e[j] /= h;
					f += e[j] * d[j];
				}
				hh = f / (h + h);
				for (j = 0; j < i; j++) {
					e[j] -= hh * d[j];
				}
				for (j = 0; j < i; j++) {
					f = d[j];
					g = e[j];
					for (k = j; k <= i - 1; k++) {
						V[k][j] -= (f * e[k] + g * d[k]);
					}
					d[j] = V[i - 1][j];
					V[i][j] = 0.0;
				}
			}
			d[i] = h;
		}

		/* Accumulate transformations */

		for (i = 0; i < n - 1; i++) {
			double h;
			V[n - 1][i] = V[i][i];
			V[i][i] = 1.0;
			h = d[i + 1];
			if (h != 0.0) {
				for (k = 0; k <= i; k++) {
					d[k] = V[k][i + 1] / h;
				}
				for (j = 0; j <= i; j++) {
					double g = 0.0;
					for (k = 0; k <= i; k++) {
						g += V[k][i + 1] * V[k][j];
					}
					for (k = 0; k <= i; k++) {
						V[k][j] -= g * d[k];
					}
				}
			}
			for (k = 0; k <= i; k++) {
				V[k][i + 1] = 0.0;
			}
		}
		for (j = 0; j < n; j++) {
			d[j] = V[n - 1][j];
			V[n - 1][j] = 0.0;
		}
		V[n - 1][n - 1] = 1.0;
		e[0] = 0.0;

	}

	void matrix::QLalgo2(int n, double *d, double *e, double **V) {
		/*
		-> n     : Dimension.
		-> d     : Diagonale of tridiagonal matrix.
		-> e[1..n-1] : off-diagonal, output from Householder
		-> V     : matrix output von Householder
		<- d     : eigenvalues
		<- e     : garbage?
		<- V     : basis of eigenvectors, according to d

		Symmetric tridiagonal QL algorithm, iterative
		Computes the eigensystem from a tridiagonal matrix in roughtly 3N^3 operations

		code adapted from Java JAMA package, function tql2.
		*/

		int i, k, l, m;
		double f = 0.0;
		double tst1 = 0.0;
		double eps = 2.22e-16; /* Math.pow(2.0,-52.0);  == 2.22e-16 */

							   /* shift input e */
		for (i = 1; i < n; i++) {
			e[i - 1] = e[i];
		}
		e[n - 1] = 0.0; /* never changed again */

		for (l = 0; l < n; l++) {

			/* Find small subdiagonal element */

			if (tst1 < fabs(d[l]) + fabs(e[l]))
				tst1 = fabs(d[l]) + fabs(e[l]);
			m = l;
			while (m < n) {
				if (fabs(e[m]) <= eps*tst1) {
					/* if (fabs(e[m]) + fabs(d[m]+d[m+1]) == fabs(d[m]+d[m+1])) { */
					break;
				}
				m++;
			}

			/* If m == l, d[l] is an eigenvalue, */
			/* otherwise, iterate. */

			if (m > l) {  /* TODO: check the case m == n, should be rejected here!? */
				int iter = 0;
				do { /* while (fabs(e[l]) > eps*tst1); */
					double dl1, h;
					double g = d[l];
					double p = (d[l + 1] - g) / (2.0 * e[l]);
					double r = myhypot(p, 1.);

					iter = iter + 1;  /* Could check iteration count here */

									  /* Compute implicit shift */

					if (p < 0) {
						r = -r;
					}
					d[l] = e[l] / (p + r);
					d[l + 1] = e[l] * (p + r);
					dl1 = d[l + 1];
					h = g - d[l];
					for (i = l + 2; i < n; i++) {
						d[i] -= h;
					}
					f = f + h;

					/* Implicit QL transformation. */

					p = d[m];
					{
						double c = 1.0;
						double c2 = c;
						double c3 = c;
						double el1 = e[l + 1];
						double s = 0.0;
						double s2 = 0.0;
						for (i = m - 1; i >= l; i--) {
							c3 = c2;
							c2 = c;
							s2 = s;
							g = c * e[i];
							h = c * p;
							r = myhypot(p, e[i]);
							e[i + 1] = s * r;
							s = e[i] / r;
							c = p / r;
							p = c * d[i] - s * g;
							d[i + 1] = h + s * (c * g + s * d[i]);

							/* Accumulate transformation. */

							for (k = 0; k < n; k++) {
								h = V[k][i + 1];
								V[k][i + 1] = s * V[k][i] + c * h;
								V[k][i] = c * V[k][i] - s * h;
							}
						}
						p = -s * s2 * c3 * el1 * e[l] / dl1;
						e[l] = s * p;
						d[l] = c * p;
					}

					/* Check for convergence. */

				} while (fabs(e[l]) > eps*tst1);
			}
			d[l] = d[l] + f;
			e[l] = 0.0;
		}

		/* Sort eigenvalues and corresponding vectors. */
#if 1
		/* TODO: really needed here? So far not, but practical and only O(n^2) */
		{
			int j;
			double p;
			for (i = 0; i < n - 1; i++) {
				k = i;
				p = d[i];
				for (j = i + 1; j < n; j++) {
					if (d[j] < p) {
						k = j;
						p = d[j];
					}
				}
				if (k != i) {
					d[k] = d[i];
					d[i] = p;
					for (j = 0; j < n; j++) {
						p = V[j][i];
						V[j][i] = V[j][k];
						V[j][k] = p;
					}
				}
			}
		}
#endif 
	}

	double* matrix::get_eigen_value() {
		return m_eigen_value;
	}
	double** matrix::get_eigen_vector() {
		return m_eigen_vector;
	}

	void matrix::load(std::ifstream &in) {
		for (int i = 0; i<m_row_size; i++) {
			in >> m_row[i];
		}
	};
	void matrix::print(std::ofstream & out) {
		for (int i = 0; i<m_row_size; i++) {
			for (int j = 0; j<m_col_size; j++)
				out << m_row[i][j] << " ";
			out << std::endl;
		};
	}
	double matrix::myhypot(double a, double b)
		/* sqrt(a^2 + b^2) numerically stable. */
	{
		double r = 0;
		if (fabs(a) > fabs(b)) {
			r = b / a;
			r = fabs(a)*sqrt(1 + r*r);
		}
		else if (b != 0) {
			r = a / b;
			r = fabs(b)*sqrt(1 + r*r);
		}
		return r;
	}
}
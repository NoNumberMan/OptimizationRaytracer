#pragma once
#include <algorithm>
#include <cassert>
#include <cmath>

typedef unsigned char byte;

namespace raytracer {

	//declarations

	template<typename Scalar, int D>
	struct vec {
		private:
		Scalar _elements[D] = {};

		public:
		vec();
		explicit vec(const Scalar& v0);
		vec(const Scalar& v0, const Scalar& v1);
		vec(const Scalar& v0, const Scalar& v1, const Scalar& v2);
		vec(const Scalar& v0, const Scalar& v1, const Scalar& v2, const Scalar& v3);
		vec(const vec<Scalar, D>& v);
		vec(const vec<Scalar, D>&& v) noexcept;

		Scalar& x();
		Scalar& y();
		Scalar& z();
		Scalar& w();
		const Scalar& x() const;
		const Scalar& y() const;
		const Scalar& z() const;
		const Scalar& w() const;
		vec<Scalar, 2> xy() const;
		vec<Scalar, 3> xyz() const;

		Scalar dot(const vec<Scalar, D>& v) const;
		Scalar len() const;
		Scalar lenSquared() const;
		Scalar dist(const vec<Scalar, D>& v) const;
		Scalar distSquared(const vec<Scalar, D>& v) const;

		void normalize();
		vec<Scalar, D> normalized() const;

		vec<Scalar, D> mul(const Scalar f) const;
		vec<Scalar, D> mul(const vec<Scalar, D>& v) const;
		vec<Scalar, D> div(const Scalar f) const;
		vec<Scalar, D> div(const vec<Scalar, D>& v) const;
		vec<Scalar, D> add(const vec<Scalar, D>& v) const;
		vec<Scalar, D> sub(const vec<Scalar, D>& v) const;
		vec<Scalar, D> cross(const vec<Scalar, D>& v) const;

		vec<Scalar, D> operator* (const vec<Scalar, D>& v) const;
		vec<Scalar, D> operator/ (const vec<Scalar, D>& v) const;
		vec<Scalar, D> operator* (const Scalar f) const;
		vec<Scalar, D> operator/ (const Scalar f) const;
		vec<Scalar, D> operator+ (const vec<Scalar, D>& v) const;
		vec<Scalar, D> operator- (const vec<Scalar, D>& v) const;

		vec<Scalar, D>& operator*= (const vec<Scalar, D>& v);
		vec<Scalar, D>& operator/= (const vec<Scalar, D>& v);
		vec<Scalar, D>& operator*= (const Scalar f);
		vec<Scalar, D>& operator/= (const Scalar f);
		vec<Scalar, D>& operator+= (const vec<Scalar, D>& v);
		vec<Scalar, D>& operator-= (const vec<Scalar, D>& v);

		bool operator== (const vec<Scalar, D>& v) const;
		bool operator!= (const vec<Scalar, D>& v) const;
		bool operator> (const vec<Scalar, D>& v) const;
		bool operator< (const vec<Scalar, D>& v) const;
		bool operator>= (const vec<Scalar, D>& v) const;
		bool operator<= (const vec<Scalar, D>& v) const;

		float& operator[] (const size_t idx);
		const float& operator[] (const size_t idx) const;

		float& operator() (const size_t idx);
		const float& operator() (const size_t idx) const;

		//vec<Scalar, D>& operator=(vec<Scalar, D> v) noexcept;
		vec<Scalar, D>& operator=(const vec<Scalar, D>& v);
		//vec<Scalar, D>& operator=(vec<Scalar, D>&& v) noexcept;
	};

	template <typename Scalar, int D>
	vec<Scalar, D> operator*(const Scalar f, const vec<Scalar, D>& v);

	template <typename Scalar, int D>
	vec<Scalar, D> operator/(const Scalar f, const vec<Scalar, D>& v);

	typedef vec<float, 1> vec1f;
	typedef vec<float, 2> vec2f;
	typedef vec<float, 3> vec3f;
	typedef vec<float, 4> vec4f;

	typedef vec<double, 1> vec1d;
	typedef vec<double, 2> vec2d;
	typedef vec<double, 3> vec3d;
	typedef vec<double, 4> vec4d;

	typedef vec<int, 1> vec1i;
	typedef vec<int, 2> vec2i;
	typedef vec<int, 3> vec3i;
	typedef vec<int, 4> vec4i;


	//definitions

	template <typename Scalar, int D>
	vec<Scalar, D>::vec() {
		for (int i = 0; i < D; ++i) { _elements[i] = 0; }
	}

	template <typename Scalar, int D>
	vec<Scalar, D>::vec(const Scalar& v0) {
		assert(D >= 1 && "vector dimension too small!");
		_elements[0] = v0;
	}

	template <typename Scalar, int D>
	vec<Scalar, D>::vec(const Scalar& v0, const Scalar& v1) {
		assert(D >= 2 && "vector dimension too small!");
		_elements[0] = v0;
		_elements[1] = v1;
	}

	template <typename Scalar, int D>
	vec<Scalar, D>::vec(const Scalar& v0, const Scalar& v1, const Scalar& v2) {
		assert(D >= 3 && "vector dimension too small!");
		_elements[0] = v0;
		_elements[1] = v1;
		_elements[2] = v2;
	}

	template <typename Scalar, int D>
	vec<Scalar, D>::vec(const Scalar& v0, const Scalar& v1, const Scalar& v2, const Scalar& v3) {
		assert(D >= 4 && "vector dimension too small!");
		_elements[0] = v0;
		_elements[1] = v1;
		_elements[2] = v2;
		_elements[3] = v3;
	}

	template <typename Scalar, int D>
	vec<Scalar, D>::vec(const vec<Scalar, D>& v) {
		memcpy(_elements, v._elements, D * sizeof(Scalar));
	}

	template <typename Scalar, int D>
	vec<Scalar, D>::vec(const vec<Scalar, D>&& v) noexcept {
		memcpy(_elements, v._elements, D * sizeof(Scalar));
	}

	template <typename Scalar, int D>
	Scalar& vec<Scalar, D>::x() {
		assert(D >= 1 && "vector dimension too small!");
		return _elements[0];
	}

	template <typename Scalar, int D>
	Scalar& vec<Scalar, D>::y() {
		assert(D >= 2 && "vector dimension too small!");
		return _elements[1];
	}

	template <typename Scalar, int D>
	Scalar& vec<Scalar, D>::z() {
		assert(D >= 3 && "vector dimension too small!");
		return _elements[2];
	}

	template <typename Scalar, int D>
	Scalar& vec<Scalar, D>::w() {
		assert(D >= 4 && "vector dimension too small!");
		return _elements[3];
	}

	template <typename Scalar, int D>
	const Scalar& vec<Scalar, D>::x() const {
		assert(D >= 1 && "vector dimension too small!");
		return _elements[0];
	}

	template <typename Scalar, int D>
	const Scalar& vec<Scalar, D>::y() const {
		assert(D >= 2 && "vector dimension too small!");
		return _elements[1];
	}

	template <typename Scalar, int D>
	const Scalar& vec<Scalar, D>::z() const {
		assert(D >= 3 && "vector dimension too small!");
		return _elements[2];
	}

	template <typename Scalar, int D>
	const Scalar& vec<Scalar, D>::w() const {
		assert(D >= 4 && "vector dimension too small!");
		return _elements[3];
	}

	template <typename Scalar, int D>
	vec<Scalar, 2> vec<Scalar, D>::xy() const {
		assert(D >= 2 && "vector dimension too small!");
		return vec<Scalar, 2>(_elements[0], _elements[1]);
	}

	template <typename Scalar, int D>
	vec<Scalar, 3> vec<Scalar, D>::xyz() const {
		assert(D >= 3 && "vector dimension too small!");
		return vec<Scalar, 3>(_elements[0], _elements[1], _elements[2]);
	}

	template <typename Scalar, int D>
	Scalar vec<Scalar, D>::dot(const vec<Scalar, D>& v) const {
		Scalar result = static_cast<Scalar>(0);
		for (int i = 0; i < D; ++i) result += _elements[i] * v[i];
		return result;
	}

	template <typename Scalar, int D>
	Scalar vec<Scalar, D>::len() const {
		return static_cast<Scalar>(std::sqrt(static_cast<double>(lenSquared())));
	}

	template <typename Scalar, int D>
	Scalar vec<Scalar, D>::lenSquared() const {
		Scalar result = static_cast<Scalar>(0);
		for (int i = 0; i < D; ++i) result += _elements[i] * _elements[i];
		return result;
	}

	template <typename Scalar, int D>
	Scalar vec<Scalar, D>::dist(const vec<Scalar, D>& v) const {
		const vec<Scalar, D> dv = *this - v;
		return dv.len();
	}

	template <typename Scalar, int D>
	Scalar vec<Scalar, D>::distSquared(const vec<Scalar, D>& v) const {
		const vec<Scalar, D> dv = *this - v;
		return dv.lenSquared();
	}

	template <typename Scalar, int D>
	void vec<Scalar, D>::normalize() {
		const Scalar len = len();
		assert(len != static_cast<Scalar>(0) && "cannot normalize zero vector!");
		*this /= len;
	}

	template <typename Scalar, int D>
	vec<Scalar, D> vec<Scalar, D>::normalized() const {
		const Scalar len = this->len();
		assert(len != static_cast<Scalar>(0) && "cannot normalize zero vector!");
		return *this / len;
	}

	template <typename Scalar, int D>
	vec<Scalar, D> vec<Scalar, D>::mul(const Scalar f) const {
		vec<Scalar, D> result;
		for (int i = 0; i < D; ++i) result[i] = _elements[i] * f;
		return result;
	}

	template <typename Scalar, int D>
	vec<Scalar, D> vec<Scalar, D>::mul(const vec<Scalar, D>& v) const {
		vec<Scalar, D> result;
		for (int i = 0; i < D; ++i) result[i] = _elements[i] * v[i];
		return result;
	}

	template <typename Scalar, int D>
	vec<Scalar, D> vec<Scalar, D>::div(const Scalar f) const {
		assert(f != static_cast<Scalar>(0) && "cannot divide by zero!");
		vec<Scalar, D> result;
		for (int i = 0; i < D; ++i) result[i] = _elements[i] / f;
		return result;
	}

	template <typename Scalar, int D>
	vec<Scalar, D> vec<Scalar, D>::div(const vec<Scalar, D>& v) const {
		vec<Scalar, D> result;
		for (int i = 0; i < D; ++i) result[i] = _elements[i] / v[i];
		return result;
	}

	template <typename Scalar, int D>
	vec<Scalar, D> vec<Scalar, D>::add(const vec<Scalar, D>& v) const {
		vec<Scalar, D> result;
		for (int i = 0; i < D; ++i) result[i] = _elements[i] + v[i];
		return result;
	}

	template <typename Scalar, int D>
	vec<Scalar, D> vec<Scalar, D>::sub(const vec<Scalar, D>& v) const {
		vec<Scalar, D> result;
		for (int i = 0; i < D; ++i) result[i] = _elements[i] - v[i];
		return result;
	}

	template <typename Scalar, int D>
	vec<Scalar, D> vec<Scalar, D>::cross(const vec<Scalar, D>& v) const {
		assert(D == 3 && "dimension must be 3!");
		vec<Scalar, D> result;
		for (int i = 0; i < D; ++i) {
			result[i] = _elements[(i + 1) % 3] * v[(i + 2) % 3] - _elements[(i + 2) % 3] * v[(i + 1) % 3];
		}

		return result;
	}

	template <typename Scalar, int D>
	vec<Scalar, D> vec<Scalar, D>::operator*(const vec<Scalar, D>& v) const {
		return mul(v);
	}

	template <typename Scalar, int D>
	vec<Scalar, D> vec<Scalar, D>::operator/(const vec<Scalar, D>& v) const {
		return div(v);
	}

	template <typename Scalar, int D>
	vec<Scalar, D> vec<Scalar, D>::operator*(const Scalar f) const {
		return mul(f);
	}

	template <typename Scalar, int D>
	vec<Scalar, D> vec<Scalar, D>::operator/(const Scalar f) const {
		return div(f);
	}

	template <typename Scalar, int D>
	vec<Scalar, D> vec<Scalar, D>::operator+(const vec<Scalar, D>& v) const {
		return add(v);
	}

	template <typename Scalar, int D>
	vec<Scalar, D> vec<Scalar, D>::operator-(const vec<Scalar, D>& v) const {
		return sub(v);
	}

	template <typename Scalar, int D>
	vec<Scalar, D>& vec<Scalar, D>::operator*=(const vec<Scalar, D>& v) {
		for (int i = 0; i < D; ++i) _elements[i] *= v[i];
		return *this;
	}

	template <typename Scalar, int D>
	vec<Scalar, D>& vec<Scalar, D>::operator/=(const vec<Scalar, D>& v) {
		for (int i = 0; i < D; ++i) _elements[i] /= v[i];
		return *this;
	}

	template <typename Scalar, int D>
	vec<Scalar, D>& vec<Scalar, D>::operator*=(const Scalar f) {
		for (int i = 0; i < D; ++i) _elements[i] *= f;
		return *this;
	}

	template <typename Scalar, int D>
	vec<Scalar, D>& vec<Scalar, D>::operator/=(const Scalar f) {
		assert(f);
		for (int i = 0; i < D; ++i) _elements[i] /= f;
		return *this;
	}

	template <typename Scalar, int D>
	vec<Scalar, D>& vec<Scalar, D>::operator+=(const vec<Scalar, D>& v) {
		for (int i = 0; i < D; ++i) _elements[i] += v[i];
		return *this;
	}

	template <typename Scalar, int D>
	vec<Scalar, D>& vec<Scalar, D>::operator-=(const vec<Scalar, D>& v) {
		for (int i = 0; i < D; ++i) _elements[i] -= v[i];
		return *this;
	}

	template <typename Scalar, int D>
	bool vec<Scalar, D>::operator==(const vec<Scalar, D>& v) const {
		bool result = true;
		for (int i = 0; i < D; ++i) {
			if (_elements[i] != v[i]) {
				result = false;
				break;
			}
		}

		return result;
	}

	template <typename Scalar, int D>
	bool vec<Scalar, D>::operator!=(const vec<Scalar, D>& v) const {
		return !(*this == v);
	}

	template <typename Scalar, int D>
	bool vec<Scalar, D>::operator>(const vec<Scalar, D>& v) const {
		return lenSquared() > v.lenSquared(); //iff a.lenSquared > b.lenSquared, then also a.len > b.len
	}

	template <typename Scalar, int D>
	bool vec<Scalar, D>::operator<(const vec<Scalar, D>& v) const {
		return lenSquared() < v.lenSquared();
	}

	template <typename Scalar, int D>
	bool vec<Scalar, D>::operator>=(const vec<Scalar, D>& v) const {
		return lenSquared() >= v.lenSquared();
	}

	template <typename Scalar, int D>
	bool vec<Scalar, D>::operator<=(const vec<Scalar, D>& v) const {
		return lenSquared() <= v.lenSquared();
	}

	template <typename Scalar, int D>
	float& vec<Scalar, D>::operator[](const size_t idx) {
		assert(idx >= 0 && idx < D && "index out of range!");
		return _elements[idx];
	}

	template <typename Scalar, int D>
	const float& vec<Scalar, D>::operator[](const size_t idx) const {
		assert(idx >= 0 && idx < D && "index out of range!");
		return _elements[idx];
	}

	template <typename Scalar, int D>
	float& vec<Scalar, D>::operator()(const size_t idx) {
		assert(idx >= 0 && idx < D && "index out of range!");
		return _elements[idx];
	}

	template <typename Scalar, int D>
	const float& vec<Scalar, D>::operator()(const size_t idx) const {
		assert(idx >= 0 && idx < D && "index out of range!");
		return _elements[idx];
	}

	template <typename Scalar, int D>
	vec<Scalar, D>& vec<Scalar, D>::operator=(const vec<Scalar, D>& v) {
		if (this != &v) {
			memcpy(_elements, v._elements, D * sizeof(Scalar));
		}

		return *this;
	}


	template <typename Scalar, int D>
	vec<Scalar, D> operator*(const Scalar f, const vec<Scalar, D>& v) {
		return v.mul(f);
	}

	template <typename Scalar, int D>
	vec<Scalar, D> operator/(const Scalar f, const vec<Scalar, D>& v) {
		return v.div(f);
	}
}

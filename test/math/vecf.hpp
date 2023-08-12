#pragma once

namespace math {
	class vecf {
		public:
			float x, y, z;

			vecf();
			vecf(float x, float y, float z);
			vecf(const vecf& other);

			vecf& operator =(const vecf& other);
	};
}
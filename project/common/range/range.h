#pragma once

#include <algorithm>
#include <iostream>

#include "common/external/glm.h"

namespace 				range_implementation
{
	template			<class type>
	struct				default_min
	{
		type			operator() (const type &left, const type &right) const
		{
			return (std::min(left, right));
		}
	};

	template			<class type>
	struct				default_max
	{
		type			operator() (const type &left, const type &right) const
		{
			return (std::max(left, right));
		}
	};

	struct				vec3_min
	{
		glm::vec3		operator() (const glm::vec3 &left, const glm::vec3 &right) const
		{
			return
			{
				std::min(left.x, right.x),
				std::min(left.y, right.y),
				std::min(left.z, right.z)
			};
		}
	};

	struct				vec3_max
	{
		glm::vec3		operator() (const glm::vec3 &left, const glm::vec3 &right) const
		{
			return
			{
				std::max(left.x, right.x),
				std::max(left.y, right.y),
				std::max(left.z, right.z)
			};
		}
	};

	template			<class type, class min = default_min<type>, class max = default_max<type>>
	class				range
	{
		using			own_type = range<type, min, max>;

	public :
						range() = default;
						~range() = default;

						range(type lower, type higher) :
							lower(lower),
							higher(higher)
		{
			update();
		}

		template		<class numeric_type>
		own_type		operator + (numeric_type value) const
		{
			return {lower + value, higher + value};
		}

		template		<class numeric_type>
		own_type		operator - (numeric_type value) const
		{
			return {lower - value, higher - value};
		}

		template		<class numeric_type>
		own_type		operator * (numeric_type value) const
		{
			return {lower * value, higher * value};
		}

		template		<class numeric_type>
		own_type		operator / (numeric_type value) const
		{
			return {lower / value, higher / value};
		}

		template		<class numeric_type>
		own_type		&operator *= (numeric_type value)
		{
			lower *= value;
			higher *= value;
			update();

			return (*this);
		}

		template		<class numeric_type>
		[[nodiscard]]
		bool			is_inside(const numeric_type &value) const
		{
			return (lower < value and value < higher);
		}

		template		<class range_type>
		[[nodiscard]]
		bool			operator || (const range_type &that) const
		{
			return (that.is_inside(lower) || that.is_inside(higher));
		}

		template		<class range_type>
		[[nodiscard]]
		bool			operator && (const range_type &that) const
		{
			return (that.is_inside(lower) && that.is_inside(higher));
		}

		friend
		std::ostream	&operator << (std::ostream &out, const range &range)
		{
			return (out << "{" << range.lower << ", " << range.higher << "}");
		}

		type			lower;
		type			higher;

	private :

		void			update()
		{
			const type	lower_copy = lower;
			const type	higher_copy = higher;

			lower = min()(lower_copy, higher_copy);
			higher = max()(lower_copy, higher_copy);
		}
	};

	using				int_range = range<int>;
	using				float_range = range<float>;
	using				vec3_range = range<glm::vec3, vec3_min, vec3_max>;
}

namespace				common
{
	using				range_implementation::int_range;
	using				range_implementation::float_range;
	using				range_implementation::vec3_range;
}
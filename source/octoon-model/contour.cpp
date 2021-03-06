#include <octoon/model/contour.h>
#include <octoon/math/math.h>

namespace octoon
{
	namespace model
	{
		Contour::Contour() noexcept
			: clockwise_(false)
		{
		}

		Contour::Contour(const math::float3s& points) noexcept
			: Contour()
		{
			for (auto& it : points_)
				this->addPoints(it);
		}

		Contour::Contour(const math::float3& pt1, const math::float3& pt2, std::uint16_t steps) noexcept
			: Contour()
		{
			this->addPoints(pt1, pt2, steps);
		}

		Contour::Contour(const math::float3& a, const math::float3& b, const math::float3& c, std::uint16_t bezierSteps) noexcept
			: Contour()
		{
			this->addPoints(a, b, c, bezierSteps);
		}

		Contour::Contour(const math::float3& a, const math::float3& b, const math::float3& c, const math::float3& d, std::uint16_t bezierSteps) noexcept
			: Contour()
		{
			this->addPoints(a, b, c, bezierSteps);
		}

		math::float3&
		Contour::at(std::size_t index) noexcept
		{
			return points_[index];
		}

		const math::float3&
		Contour::at(std::size_t index) const noexcept
		{
			return points_[index];
		}

		math::float3s&
		Contour::points() noexcept
		{
			return points_;
		}

		const math::float3s&
		Contour::points() const noexcept
		{
			return points_;
		}

		std::size_t
		Contour::count() const noexcept
		{
			return points_.size();
		}

		void
		Contour::isClockwise(bool clockwise) noexcept
		{
			clockwise_ = clockwise;
		}

		bool
		Contour::isClockwise() const noexcept
		{
			return clockwise_;
		}

		void
		Contour::addPoints(const math::float3& point) noexcept
		{
			points_.push_back(point);
		}

		void
		Contour::addPoints(const math::float3& pt1, const math::float3& pt2, std::uint16_t steps) noexcept
		{
			this->addPoints(pt1);

			for (std::size_t i = 0; i < steps; i++)
			{
				float t = (float)i / steps;
				this->addPoints(math::lerp(pt1, pt2, t));
			}
		}

		void
		Contour::addPoints(const math::float3& A, const math::float3& B, const math::float3& C, std::uint16_t bezierSteps) noexcept
		{
			for (std::size_t i = 1; i < bezierSteps; i++)
			{
				float t = (float)i / bezierSteps;
				float t2 = 1.0f - t;

				math::float3 u = t2 * A + t * B;
				math::float3 v = t2 * B + t * C;

				this->addPoints(t2 * u + t * v);
			}
		}

		void
		Contour::addPoints(const math::float3& A, const math::float3& B, const math::float3& C, const math::float3& D, std::uint16_t bezierSteps) noexcept
		{
			for (std::size_t i = 0; i < bezierSteps; i++)
			{
				float t = (float)i / bezierSteps;
				float t2 = 1.0f - t;

				math::float3 u = t2 * A + t * B;
				math::float3 v = t2 * B + t * C;
				math::float3 w = t2 * C + t * D;

				math::float3 m = t2 * u + t * v;
				math::float3 n = t2 * v + t * w;

				this->addPoints(t2 * m + t * n);
			}
		}
	}
}
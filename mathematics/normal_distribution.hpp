#ifndef __QFINLIB_NORMAL_DISTRIBUTION_HPP__
#define __QFINLIB_NORMAL_DISTRIBUTION_HPP__

namespace qfinlib
{
	class NormalDistribution
	{
	public:
		static double cdf(const double x);
		static double pdf(const double x);

	private:
	};
}

#endif /* __QFINLIB_NORMAL_DISTRIBUTION_HPP__ */

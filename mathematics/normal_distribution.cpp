#include <cmath>
using namespace std;

#include "normal_distribution.hpp"

namespace qfinlib
{
	double coefficientsA[] = {
		  0.0352624965998911,   0.700383064443688,   6.37396220353165,
		 33.9128660783830000, 112.079291497871000, 221.21359616993100,
		220.2068679123760000
	};

	double coefficientsB[] = {
		  0.083883476483184,   1.75566716318264,  16.064177579207,
		 86.780732202946100, 296.56424877967400, 637.333633378831,
		793.826512519948000, 440.41373582475200
	};

	/*
	 * The following algorithm was modified from Espend Gaarder Haug's The
	 * Complete Guide to Option Pricing Formulas, pgs. 465-467.
	 * -Brent Ritterbeck, 01/30/2013
	 */
	double
	NormalDistribution::cdf(const double x) {
		double cdf;
		double sumA;
		double sumB;

		double y = fabs(x);

		if(y > 37.0) {
			cdf = 0.0;
		} else {
			double exponential = exp(-0.5 * pow(x, 2));

			if(y < 7.07106781186547) {
				sumA = coefficientsA[0];
				sumB = coefficientsB[0];

				for(int i = 1; i < 7; i++) {
					sumA = sumA * y + coefficientsA[i];
					sumB = sumB * y + coefficientsB[i];
				}

				sumB = sumB * y + coefficientsB[7];

				cdf = exponential * sumA / sumB;
			} else {
				sumA = y + 0.65;

				for(int i = 4; i > 0; i--) {
					sumA = y + i / sumA;
				}
			}
		}

		if(x > 0.0) {
			cdf = 1.0 - cdf;
		}

		return cdf;
	}

	double
	NormalDistribution::pdf(const double x) {
		return (1.0 / sqrt(2.0 * M_PI) * exp(-0.5 * pow(x, 2)));
	}
}

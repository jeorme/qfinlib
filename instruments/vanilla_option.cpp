#include <cmath>
using namespace std;

#include "normal_distribution.hpp"
#include "option_type.hpp"
#include "vanilla_option.hpp"

namespace qfinlib
{
	VanillaOption::VanillaOption() {
		reset();
	}

	VanillaOption::~VanillaOption() {
	}

	double
	VanillaOption::getCostOfCarry() const {
		return costOfCarry_;
	}

	double
	VanillaOption::getInterestRate() const {
		return interestRate_;
	}

	double
	VanillaOption::getStrikePrice() const {
		return strikePrice_;
	}

	double
	VanillaOption::getTimeUntilExpiration() const {
		return timeUntilExpiration_;
	}

	double
	VanillaOption::getUnderlyingPrice() const {
		return underlyingPrice_;
	}

	double
	VanillaOption::getVolatility() const {
		return volatility_;
	}

	OptionType
	VanillaOption::getOptionType() const {
		return optionType_;
	}

	void
	VanillaOption::setCostOfCarry(const double costOfCarry) {
		costOfCarry_ = costOfCarry;
	}

	void
	VanillaOption::setInterestRate(const double interestRate) {
		interestRate_ = interestRate;
	}

	void
	VanillaOption::setStrikePrice(const double strikePrice) {
		strikePrice_ = strikePrice;
	}

	void
	VanillaOption::setTimeUntilExpiration(const double timeUntilExpiration) {
		timeUntilExpiration_ = timeUntilExpiration;
	}

	void
	VanillaOption::setUnderlyingPrice(const double underlyingPrice) {
		underlyingPrice_ = underlyingPrice;
	}

	void
	VanillaOption::setVolatility(const double volatility) {
		volatility_ = volatility;
	}

	void
	VanillaOption::setOptionType(const OptionType optionType) {
		optionType_ = optionType;
	}

	double
	VanillaOption::getValue() const {
		return computeValue();
	}

	void
	VanillaOption::reset() {
		costOfCarry_         = -1.0;
		interestRate_        = -1.0;
		strikePrice_         = -1.0;
		timeUntilExpiration_ = -1.0;
		underlyingPrice_     = -1.0;
		volatility_          = -1.0;

		optionType_          = CALL;
	}

	double
	VanillaOption::computeD1() const {
		double d1 = (costOfCarry_ + 0.5 * pow(volatility_, 2));
		d1 *= timeUntilExpiration_;
		d1 += log(underlyingPrice_ / strikePrice_);
		d1 /= (volatility_ * sqrt(timeUntilExpiration_));
		return d1;
	}

	double
	VanillaOption::computeD2() const {
		double d2 = (costOfCarry_ - 0.5 * pow(volatility_, 2));
		d2 *= timeUntilExpiration_;
		d2 += log(underlyingPrice_ / strikePrice_);
		d2 /= (volatility_ * sqrt(timeUntilExpiration_));
		return d2;
	}

	double
	VanillaOption::computeValue() const {
		double piece1 = NormalDistribution::cdf(optionType_ * computeD1());
		piece1 *= exp((costOfCarry_ - interestRate_) * timeUntilExpiration_);
		piece1 *= (optionType_ * underlyingPrice_);

		double piece2 = NormalDistribution::cdf(optionType_ * computeD2());
		piece2 *= exp(-interestRate_ * timeUntilExpiration_);
		piece2 *= (-optionType_ * strikePrice_);

		return (piece1 + piece2);
	}
}

#include <cmath>
#include <cstdlib>
using namespace std;

#include "binary_option.hpp"
#include "binary_type.hpp"
#include "normal_distribution.hpp"
#include "option_type.hpp"

namespace qfinlib
{
	BinaryOption::BinaryOption() {
		reset();
	}

	BinaryOption::~BinaryOption() {
	}

	double
	BinaryOption::getCostOfCarry() const {
		return costOfCarry_;
	}

	double
	BinaryOption::getInterestRate() const {
		return interestRate_;
	}

	double
	BinaryOption::getPayoff() const {
		return payoff_;
	}

	double
	BinaryOption::getStrikePrice() const {
		return strikePrice_;
	}

	double
	BinaryOption::getTimeUntilExpiration() const {
		return timeUntilExpiration_;
	}

	double
	BinaryOption::getUnderlyingPrice() const {
		return underlyingPrice_;
	}

	double
	BinaryOption::getVolatility() const {
		return volatility_;
	}

	BinaryType
	BinaryOption::getBinaryType() const {
		return binaryType_;
	}

	OptionType
	BinaryOption::getOptionType() const {
		return optionType_;
	}

	void
	BinaryOption::setCostOfCarry(const double costOfCarry) {
		costOfCarry_ = costOfCarry;
	}

	void
	BinaryOption::setInterestRate(const double interestRate) {
		interestRate_ = interestRate;
	}

	void
	BinaryOption::setPayoff(const double payoff) {
		payoff_ = payoff;
	}

	void
	BinaryOption::setStrikePrice(const double strikePrice) {
		strikePrice_ = strikePrice;
	}

	void
	BinaryOption::setTimeUntilExpiration(const double timeUntilExpiration) {
		timeUntilExpiration_ = timeUntilExpiration;
	}

	void
	BinaryOption::setUnderlyingPrice(const double underlyingPrice) {
		underlyingPrice_ = underlyingPrice;
	}

	void
	BinaryOption::setVolatility(const double volatility) {
		volatility_ = volatility;
	}

	void
	BinaryOption::setBinaryType(const BinaryType binaryType) {
		binaryType_ = binaryType;
	}

	void
	BinaryOption::setOptionType(const OptionType optionType) {
		optionType_ = optionType;
	}

	double
	BinaryOption::getD1() const {
		return computeD1();
	}

	double
	BinaryOption::getD2() const {
		return computeD2();
	}

	double
	BinaryOption::getValue() const {
		return computeValue();
	}
	
	void
	BinaryOption::reset() {
		costOfCarry_         = -1.0;
		interestRate_        = -1.0;
		payoff_              = -1.0;
		strikePrice_         = -1.0;
		timeUntilExpiration_ = -1.0;
		underlyingPrice_     = -1.0;
		volatility_          = -1.0;

		binaryType_          = CASH;
		optionType_          = CALL;
	}

	double
	BinaryOption::computeD1() const {
		double d1 = (costOfCarry_ + 0.5 * pow(volatility_, 2));
		d1 *= timeUntilExpiration_;
		d1 += log(underlyingPrice_ / strikePrice_);
		d1 /= (volatility_ * sqrt(timeUntilExpiration_));
		return d1;
	}

	double
	BinaryOption::computeD2() const {
		double d2 = (costOfCarry_ - 0.5 * pow(volatility_, 2));
		d2 *= timeUntilExpiration_;
		d2 += log(underlyingPrice_ / strikePrice_);
		d2 /= (volatility_ * sqrt(timeUntilExpiration_));
		return d2;
	}

	double
	BinaryOption::computeValue() const {
		double value;

		if(binaryType_ == ASSET) {
			value  = NormalDistribution::cdf(optionType_ * computeD1());
			value *= exp((costOfCarry_ - interestRate_) * timeUntilExpiration_);
			value *= underlyingPrice_;
		} else if(binaryType_ == CASH) {
			value  = NormalDistribution::cdf(optionType_ * computeD2());
			value *= exp(-interestRate_ * timeUntilExpiration_);
			value *= payoff_;
		} else {
			abort();
		}

		return value;
	}
}

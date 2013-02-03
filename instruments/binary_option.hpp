#ifndef __QFINLIB_BINARY_OPTION_HPP__
#define __QFINLIB_BINARY_OPTION_HPP__

#include "binary_type.hpp"
#include "option_type.hpp"

namespace qfinlib
{
	class BinaryOption
	{
	public:
		BinaryOption();
		~BinaryOption();

		double getCostOfCarry() const;
		double getInterestRate() const;
		double getPayoff() const;
		double getStrikePrice() const;
		double getTimeUntilExpiration() const;
		double getUnderlyingPrice() const;
		double getVolatility() const;

		BinaryType getBinaryType() const;
		OptionType getOptionType() const;

		void setCostOfCarry(const double costOfCarry);
		void setInterestRate(const double interestRate);
		void setPayoff(const double payoff);
		void setStrikePrice(const double strikePrice);
		void setTimeUntilExpiration(const double timeUntilExpiration);
		void setUnderlyingPrice(const double underlyingPrice);
		void setVolatility(const double volatility);

		void setBinaryType(const BinaryType binaryType);
		void setOptionType(const OptionType optionType);

		double getD1() const;
		double getD2() const;
		double getValue() const;

		void reset();

	private:
		double computeD1() const;
		double computeD2() const;
		double computeValue() const;

		double costOfCarry_;
		double interestRate_;
		double payoff_;
		double strikePrice_;
		double timeUntilExpiration_;
		double underlyingPrice_;
		double volatility_;

		BinaryType binaryType_;
		OptionType optionType_;
	};
}

#endif /* __QFINLIB_BINARY_OPTION_HPP__ */

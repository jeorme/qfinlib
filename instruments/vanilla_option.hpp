#ifndef __QFINLIB_VANILLA_OPTION_HPP__
#define __QFINLIB_VANILLA_OPTION_HPP__

#include "option_type.hpp"

namespace qfinlib
{
	class VanillaOption
	{
	public:
		VanillaOption();
		~VanillaOption();

		double getCostOfCarry() const;
		double getInterestRate() const;
		double getStrikePrice() const;
		double getTimeUntilExpiration() const;
		double getUnderlyingPrice() const;
		double getVolatility() const;

		OptionType getOptionType() const;

		void setCostOfCarry(const double costOfCarry);
		void setInterestRate(const double interestRate);
		void setStrikePrice(const double strikePrice);
		void setTimeUntilExpiration(const double timeUntilExpiration);
		void setUnderlyingPrice(const double underlyingPrice);
		void setVolatility(const double volatility);

		void setOptionType(const OptionType optionType);

		double getValue() const;

		void reset();

	private:
		double computeD1() const;
		double computeD2() const;
		double computeValue() const;

		double costOfCarry_;
		double interestRate_;
		double strikePrice_;
		double timeUntilExpiration_;
		double underlyingPrice_;
		double volatility_;

		OptionType optionType_;
	};
}

#endif /* __QFINLIB_VANILLA_OPTION_HPP__ */

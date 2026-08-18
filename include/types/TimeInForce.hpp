#pragma once
namespace lob {
	enum class TimeInForce {
		Day,
		IOC, // Immediate Or Cancel
		FOK,  // Fill Or Kill
		GTC // Good Till Cancelled
	};
}
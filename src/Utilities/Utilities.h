// Copyright (c) 2018-2019, The TurtleCoin Developers
// Copyright (c) 2019, The CryoNero Developers
//
// Please see the included LICENSE file for more information.

#pragma once
#include <atomic>
#include <chrono>
#include <CryptoNote.h>
#include <iomanip>
#include <string>
#include <vector>
#include <Errors/Errors.h>
namespace Utilities
{
    uint64_t getTransactionSum(const std::vector<std::pair<std::string, uint64_t>> destinations);
    uint64_t getUpperBound(const uint64_t val, const uint64_t nearestMultiple);
    uint64_t getLowerBound(const uint64_t val, const uint64_t nearestMultiple);
    bool isInputUnlocked(
        const uint64_t unlockTime,
        const uint64_t currentHeight);
    uint64_t getMaxTxSize(const uint64_t currentHeight);
    void sleepUnlessStopping(
        const std::chrono::milliseconds duration,
        std::atomic<bool> &condition);
    uint64_t scanHeightToTimestamp(const uint64_t scanHeight);
    uint64_t timestampToScanHeight(const uint64_t timestamp);
    uint64_t getCurrentTimestampAdjusted();
    bool isSubtractionSafe(int64_t currentValue, uint64_t transferAmount);
    bool parseDaemonAddressFromString(std::string &host, uint16_t &port, std::string address);
    size_t getApproximateMaximumInputCount(
        const size_t transactionSize,
        const size_t outputCount,
        const size_t mixinCount);
    template<typename T>
    bool additionWillOverflow(T a, T b)
    {
        static_assert(std::is_integral<T>::value, "additionWillOverflow can only be used for integral inputs!");

        T result = a + b;

        T larger = std::max(a, b);

        if (a < 0 || b < 0)
        {
            return result > larger;
        }
        return result < larger;
    }
    template<typename T>
    bool subtractionWillOverflow(T a, T b)
    {
        return additionWillOverflow(a, -b);
    }
    template<typename T>
    bool sumWillOverflow(std::vector<T> amounts)
    {
        T sum = 0;
        for (const auto item : amounts)
        {
            if (additionWillOverflow(item, sum))
            {
                return true;
            }

            sum += item;
        }
        return false;
    }
}

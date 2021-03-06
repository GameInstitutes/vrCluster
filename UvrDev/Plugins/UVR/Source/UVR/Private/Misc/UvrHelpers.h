// Copyright 2016 Pixela Labs. All Rights Reserved.
#pragma once

#include "Engine.h"
#include "Networking.h"
#include "UvrTypesConverter.h"


namespace UvrHelpers
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Common String helpers
	//////////////////////////////////////////////////////////////////////////////////////////////
	namespace str
	{
		static constexpr auto StrFalse = TEXT("false");
		static constexpr auto StrTrue  = TEXT("true");

		static inline auto BoolToStr(bool bVal)
		{
			return (bVal ? StrTrue : StrFalse);
		}

		static void DustCommandLineValue(FString& val, bool bTrimQuotes = true)
		{
			val.RemoveFromStart(UvrStrings::strKeyValSeparator);
			
			if(bTrimQuotes)
				val = val.TrimQuotes();
		}

		template<typename T>
		static bool ExtractCommandLineValue(const FString& line, const FString& argName, T& argVal)
		{
			FString tmp;
			if (FParse::Value(*line, *argName, tmp, false))
			{
				DustCommandLineValue(tmp, false);
				argVal = UvrTypesConverter::FromString<T>(tmp);
				return true;
			}
			return false;
		}

#if 0
		bool GetPair(FString& line, FString& pair)
		{
			if (line.IsEmpty())
				return false;

			if (line.Split(FString(" "), &pair, &line) == false)
			{
				pair = line;
				line.Empty();
				return true;
			}

			line = line.Trim().TrimTrailing();
			pair = pair.Trim().TrimTrailing();

			return true;
		}

		bool GetKeyVal(FString& line, FString& key, FString& val)
		{
			FString pair;
			if (GetPair(line, pair) == false)
				return false;

			if (pair.Split(FString(UvrStrings::cfg::spec::KeyValSeparator), &key, &val) == false)
				return false;

			key = key.Trim().TrimTrailing();
			val = val.Trim().TrimTrailing();

			return true;
		}
#endif
	};


	//////////////////////////////////////////////////////////////////////////////////////////////
	// Network helpers
	//////////////////////////////////////////////////////////////////////////////////////////////
	namespace net
	{
		static bool GenIPv4Endpoint(const FString& addr, const int32 port, FIPv4Endpoint& ep)
		{
			FIPv4Address ipAddr;
			if (!FIPv4Address::Parse(addr, ipAddr))
				return false;

			ep = FIPv4Endpoint(ipAddr, port);
			return true;
		}
	};

	//////////////////////////////////////////////////////////////////////////////////////////////
	// Array helpers
	//////////////////////////////////////////////////////////////////////////////////////////////	struct str
	namespace arrays
	{
		// Max element in array
		template<typename T>
		T max(const T* data, int size)
		{
			T result = data[0];
			for (int i = 1; i < size; i++)
				if (result < data[i])
					result = data[i];
			return result;
		}

		// Max element's index in array
		template<typename T>
		size_t max_idx(const T* data, int size)
		{
			size_t idx = 0;
			T result = data[0];
			for (int i = 1; i < size; i++)
				if (result < data[i])
				{
					result = data[i];
					idx = i;
				}
			return idx;
		}

		// Min element in array
		template<typename T>
		T min(const T* data, int size)
		{
			T result = data[0];
			for (int i = 1; i < size; i++)
				if (result > data[i])
					result = data[i];
			return result;
		}

		// Min element's index in array
		template<typename T>
		size_t min_idx(const T* data, int size)
		{
			size_t idx = 0;
			T result = data[0];
			for (int i = 1; i < size; i++)
				if (result > data[i])
				{
					result = data[i];
					idx = i;
				}
			return idx;
		}

		// Helper for array size
		template <typename T, size_t n>
		constexpr size_t array_size(const T(&)[n])
		{
			return n;
		}
	}
};

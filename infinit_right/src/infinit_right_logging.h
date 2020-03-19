#pragma once

namespace IR {

	namespace Logging {
		static const auto g_AppStart = std::chrono::system_clock::now();

		enum ELogType
		{
			ERROR,
			INFO,
			WARN,
			DEBUG,
			UNDO,
			ASSERT
		};

		static IRString GetPrefixString(ELogType type)
		{
			std::chrono::duration<double> duration = std::chrono::system_clock::now() - g_AppStart;
			switch (type)
			{
			case IR::Logging::ERROR:
				return "[ERROR]" + std::to_string(duration.count()) + "[";
				break;
			case IR::Logging::ASSERT:
				return "[ASSERT]" + std::to_string(duration.count()) + "[";
				break;
			case IR::Logging::INFO:
				return "[INFO]" + std::to_string(duration.count()) + "[";
				break;
			case IR::Logging::WARN:
				return "[WARN]" + std::to_string(duration.count()) + "[";
				break;
			case IR::Logging::DEBUG:
				return "[DEBUG]" + std::to_string(duration.count()) + "[";
				break;
			case IR::Logging::UNDO:
				return "[UNDO]" + std::to_string(duration.count()) + "[";
				break;
			default:
				break;
			}
			return "";
		}

		static void Log(ELogType type, const char* str, u32 line, const char* file)
		{
			std::cout << GetPrefixString(type) << file << "l." << line << "]" << str << std::endl;
		}


	}

}

#define IR_ERROR(x) ::IR::Logging::Log(::IR::Logging::ELogType::ERROR, x, __LINE__, __FILE__)
#define IR_DEBUG(x) ::IR::Logging::Log(::IR::Logging::ELogType::DEBUG, x, __LINE__, __FILE__)
#define IR_UNDO(x) ::IR::Logging::Log(::IR::Logging::ELogType::UNDO, x, __LINE__, __FILE__)
#define IR_WARN(x) ::IR::Logging::Log(::IR::Logging::ELogType::WARN, x, __LINE__, __FILE__)
#define IR_INFO(x) ::IR::Logging::Log(::IR::Logging::ELogType::INFO, x, __LINE__, __FILE__)

#define IR_ASSERT(x, msg) if (!(x)) { ::IR::Logging::Log(::IR::Logging::ELogType::ASSERT, msg, __LINE__, __FILE__); } 
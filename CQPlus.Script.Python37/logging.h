#pragma once

#include "./api.h"
#include "./string.h"
#include "./json.h"

#undef ERROR

#define DEFAULT_LOG_TAG "CQPLUS.SCRIPT"

namespace cqplus::logging {
    enum Level {
        DEBUG = 0,
        INFO = 10,
        INFOSUCCESS = 11,
        INFORECV = 12,
        INFOSEND = 13,
        WARNING = 20,
        ERROR = 30,
        FATAL = 40,
    };

    inline void log(const Json::Value& env, const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG, const Level level = INFO) {
        CQPLUS_API_INIT_PARAMS();
        CQPLUS_API_PARAMS["level"] = static_cast<int32_t>(level);
        CQPLUS_API_PARAMS["msg"] = msg;
        CQPLUS_API_PARAMS["tag"] = tag;
        CQPLUS_API_INVOKE("log");
    }

    inline void debug(const Json::Value& env, const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) { log(env, msg, tag, DEBUG); }

    inline void info(const Json::Value& env, const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) { log(env, msg, tag, INFO); }

    inline void info_success(const Json::Value& env, const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) { log(env, msg, tag, INFOSUCCESS); }

    inline void info_recv(const Json::Value& env, const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) { log(env, msg, tag, INFORECV); }

    inline void info_send(const Json::Value& env, const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) { log(env, msg, tag, INFOSEND); }

    inline void warning(const Json::Value& env, const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) { log(env, msg, tag, WARNING); }

    inline void error(const Json::Value& env, const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) { log(env, msg, tag, ERROR); }

    inline void fatal(const Json::Value& env, const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) { log(env, msg, tag, FATAL); }
} // namespace cqplus::logging

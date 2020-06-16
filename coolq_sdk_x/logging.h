#pragma once

#include "./api.h"
#include "./string.h"
#include "./json.h"

#undef ERROR

#define DEFAULT_LOG_TAG "CQPLUS"

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

    inline void log(const Level level, const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) {
        CQPLUS_API_INIT_PARAMS();
        CQPLUS_API_PARAMS["level"] = static_cast<int32_t>(level);
        CQPLUS_API_PARAMS["msg"] = msg;
        CQPLUS_API_PARAMS["tag"] = tag;
        CQPLUS_API_INVOKE("log");
    }

    inline void debug(const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) { log(DEBUG, msg, tag); }

    inline void info(const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) { log(INFO, msg, tag); }

    inline void info_success(const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) { log(INFOSUCCESS, msg, tag); }

    inline void info_recv(const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) { log(INFORECV, msg, tag); }

    inline void info_send(const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) { log(INFOSEND, msg, tag); }

    inline void warning(const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) { log(WARNING, msg, tag); }

    inline void error(const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) { log(ERROR, msg, tag); }

    inline void fatal(const std::string &msg, const std::string &tag = DEFAULT_LOG_TAG) { log(FATAL, msg, tag); }
} // namespace cqplus::logging

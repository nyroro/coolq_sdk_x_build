#include "stdafx.h"

#include "./settings.h"

#include "./app.h"
#include "./json.h"
#include "./logging.h"
#include "./utils.h"
#include <string>
#include <fstream>

namespace cqplus::settings {
    Json::Value raw;
    bool IS_DEBUG = true;
    std::map<std::string, int32_t> TIMER;
    std::string RUNTIME_NAME;

    void init() {
        std::string script_home = path_join(str_list(cqplus::utils::string_to_coolq(cqplus::app::cq_home), "app", cqplus::app::app_id));
        os_makedirs(script_home);
        
        std::string settings_json_filename = path_join(str_list(script_home, "settings.json"));
        std::string settings_json_filename_t = cqplus::utils::string_from_coolq(settings_json_filename);

        if (path_isfile(settings_json_filename)) {
            cqplus::logging::debug(u8"加载配置文件：" + settings_json_filename_t);
            std::ifstream ifs;
            ifs.open(settings_json_filename);
            if (ifs.is_open()) {
                Json::Value settings;
                Json::CharReaderBuilder reader_builder;
                try {
                    Json::parseFromStream(reader_builder, ifs, &settings, NULL);

                    raw = settings;

                    IS_DEBUG = settings.get("DEBUG", true).asBool();

                    Json::Value TIMER_d = settings.get("TIMER", Json::objectValue);
                    auto TIMER_keys = TIMER_d.getMemberNames();
                    for (auto it=TIMER_keys.cbegin(); it != TIMER_keys.cend(); it++)
                    {
                        TIMER[*it] = TIMER_d.get(*it, 0).asInt();
                    }

                    RUNTIME_NAME = settings.get("RUNTIME_NAME", "").asString();
                    
                    if (RUNTIME_NAME.empty())
                    {
                        cqplus::logging::error(u8"未在配置文件中指定RUNTIME_NAME"); 
                    } 
                    else
                    {
                        cqplus::logging::debug(u8"RUNTIME_NAME=" + RUNTIME_NAME);
                    }
                }
                catch (const std::exception &) {
                    cqplus::logging::error(u8"解析配置文件失败：" + settings_json_filename_t);
                }
                ifs.close();
            }
            else {
                cqplus::logging::error(u8"加载配置文件失败：" + settings_json_filename_t);
            }
        }
        else {
            cqplus::logging::error(u8"配置文件不存在：" + settings_json_filename_t);
        }
    }
}

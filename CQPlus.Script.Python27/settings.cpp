#include "stdafx.h"

#include "./settings.h"

#include "./app.h"
#include "./json.h"
#include "./logging.h"
#include "./utils.h"
#include "./script_engine_def.h"
#include <string>
#include <fstream>

namespace cqplus::settings {
    Json::Value raw;
    std::string RUNTIME_NAME;
    std::string RUNTIME_HOME;

    void init() {
        RUNTIME_NAME = SCRIPT_ENGINE_NAME;

        std::string settings_json_filename = path_join(str_list(cqplus::utils::string_to_coolq(cqplus::app::cq_home), "conf", "CQPlus.json"));
        std::string settings_json_filename_t = cqplus::utils::string_from_coolq(settings_json_filename);

        if (path_isfile(settings_json_filename)) {
            std::ifstream ifs;
            ifs.open(settings_json_filename);
            if (ifs.is_open()) {
                Json::Value settings_global;
                Json::CharReaderBuilder reader_builder;
                try {
                    Json::parseFromStream(reader_builder, ifs, &settings_global, NULL);

                    const Json::Value& settings_runtime = settings_global.get("RUNTIME", Json::objectValue);
                    const Json::Value& settings = settings_runtime.get(RUNTIME_NAME, Json::objectValue);

                    RUNTIME_NAME = settings.get("RUNTIME_NAME", RUNTIME_NAME).asString();
                    RUNTIME_HOME = settings.get("RUNTIME_HOME", "").asString();
                }
                catch (const std::exception &) {
                }
                ifs.close();
            }
            else {
            }
        }
        else {
        }
    }
}

#include "stdafx.h"

#include "./timer.h"
#include "./logging.h"
#include "./settings.h"

#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

#include <vector>
#include <string>
#include <map>

static std::vector<UINT> timer_id_list;
static std::map<UINT, std::string> timer_id2name;
static std::map<std::string, UINT> timer_name2id;

void WINAPI TimerCallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);

namespace cqplus::timer {
    std::function<void(const std::string&)> on_timer;

    void init() {
        for (auto it=cqplus::settings::TIMER.cbegin(); it!=cqplus::settings::TIMER.cend(); ++it)
        {
            if (it->second > 0)
            {
                auto timer_id = timeSetEvent(max(it->second, 100), 1, (LPTIMECALLBACK)TimerCallback, NULL, TIME_PERIODIC);
                timer_id_list.push_back(timer_id);
                timer_id2name[timer_id] = it->first;
                timer_name2id[it->first] = timer_id;
            }
        }
    }

    void fini() {
        for (auto it=timer_id_list.cbegin(); it!=timer_id_list.cend(); ++it)
        {
            timeKillEvent(*it);
        }
        timer_id_list.clear();
        timer_id2name.clear();
        timer_name2id.clear();
    }
}

void WINAPI TimerCallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
    auto it = timer_id2name.find(uTimerID);
    if (it != timer_id2name.end())
    {
        auto name = it->second;
        cqplus::utils::call_if_valid(cqplus::timer::on_timer, name);
    }
}

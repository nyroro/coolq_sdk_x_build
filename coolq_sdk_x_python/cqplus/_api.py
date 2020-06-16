# -*- coding:utf-8 -*-

import _cqplus
import json
from cqplus._context import CQPlusContext


def api_invoke(method, params):
    ret_s = _cqplus.api_invoke(method, json.dumps(params))
    try:
        ret = json.loads(ret_s)
    except:
        ret = None
    return ret


########################################################################


def send_private_msg(env, user_id, msg):
    p = dict()
    p['env'] = env
    p['user_id'] = user_id
    p['msg'] = msg
    return api_invoke('send_private_msg', p)


def send_group_msg(env, group_id, msg):
    p = dict()
    p['env'] = env
    p['group_id'] = group_id
    p['msg'] = msg
    return api_invoke('send_group_msg', p)


def send_discuss_msg(env, discuss_id, msg):
    p = dict()
    p['env'] = env
    p['discuss_id'] = discuss_id
    p['msg'] = msg
    return api_invoke('send_discuss_msg', p)


def delete_msg(env, msg_id):
    p = dict()
    p['env'] = env
    p['msg_id'] = msg_id
    return api_invoke('delete_msg', p)


def send_like(env, user_id, times):
    p = dict()
    p['env'] = env
    p['user_id'] = user_id
    p['times'] = times
    return api_invoke('send_like', p)


def set_group_kick(env, group_id, user_id, reject_add_request=False):
    p = dict()
    p['env'] = env
    p['group_id'] = group_id
    p['user_id'] = user_id
    p['reject_add_request'] = reject_add_request
    return api_invoke('set_group_kick', p)


def set_group_ban(env, group_id, user_id, duration):
    p = dict()
    p['env'] = env
    p['group_id'] = group_id
    p['user_id'] = user_id
    p['duration'] = duration
    return api_invoke('set_group_ban', p)


def set_group_anonymous_ban(env, group_id, flag, duration):
    p = dict()
    p['env'] = env
    p['group_id'] = group_id
    p['flag'] = flag
    p['duration'] = duration
    return api_invoke('set_group_anonymous_ban', p)


def set_group_whole_ban(env, group_id, enable):
    p = dict()
    p['env'] = env
    p['group_id'] = group_id
    p['enable'] = enable
    return api_invoke('set_group_whole_ban', p)


def set_group_admin(env, group_id, user_id, enable):
    p = dict()
    p['env'] = env
    p['group_id'] = group_id
    p['user_id'] = user_id
    p['enable'] = enable
    return api_invoke('set_group_admin', p)


def set_group_anonymous(env, group_id, enable):
    p = dict()
    p['group_id'] = group_id
    p['enable'] = enable
    return api_invoke('set_group_anonymous', p)


def set_group_card(env, group_id, user_id, card):
    p = dict()
    p['env'] = env
    p['group_id'] = group_id
    p['user_id'] = user_id
    p['card'] = card
    return api_invoke('set_group_card', p)


def set_group_leave(env, group_id, is_dismiss):
    p = dict()
    p['env'] = env
    p['group_id'] = group_id
    p['is_dismiss'] = is_dismiss
    return api_invoke('set_group_leave', p)


def set_group_special_title(env, group_id, user_id, special_title, duration):
    p = dict()
    p['env'] = env
    p['group_id'] = group_id
    p['user_id'] = user_id
    p['special_title'] = special_title
    p['duration'] = duration
    return api_invoke('set_group_special_title', p)


def set_discuss_leave(env, discuss_id):
    p = dict()
    p['env'] = env
    p['discuss_id'] = discuss_id
    return api_invoke('set_discuss_leave', p)


def set_friend_add_request(env, flag, operation, remark):
    p = dict()
    p['env'] = env
    p['flag'] = flag
    p['operation'] = operation
    p['remark'] = remark
    return api_invoke('set_friend_add_request', p)


def set_group_add_request(env, flag, type, operation, reason):
    p = dict()
    p['env'] = env
    p['flag'] = flag
    p['type'] = type
    p['operation'] = operation
    p['reason'] = reason
    return api_invoke('set_group_add_request', p)


def get_login_user_id(env):
    p = dict()
    p['env'] = env
    return api_invoke('get_login_user_id', p)


def get_login_nickname(env):
    p = dict()
    p['env'] = env
    return api_invoke('get_login_nickname', p)


def get_cookies(env):
    p = dict()
    p['env'] = env
    return api_invoke('get_cookies', p)


def get_csrf_token(env):
    p = dict()
    p['env'] = env
    return api_invoke('get_csrf_token', p)


def get_app_directory(env):
    p = dict()
    p['env'] = env
    return api_invoke('get_app_directory', p)


def get_record(env, file, out_format):
    p = dict()
    p['env'] = env
    p['file'] = file
    p['out_format'] = out_format
    return api_invoke('get_record', p)


def get_stranger_info(env, user_id, no_cache=False):
    p = dict()
    p['env'] = env
    p['user_id'] = user_id
    p['no_cache'] = no_cache
    return api_invoke('get_stranger_info', p)


def get_group_list(env):
    p = dict()
    p['env'] = env
    return api_invoke('get_group_list', p)


def get_group_member_list(env, group_id):
    p = dict()
    p['env'] = env
    p['group_id'] = group_id
    return api_invoke('get_group_member_list', p)


def get_group_member_info(env, group_id, user_id, no_cache):
    p = dict()
    p['env'] = env
    p['group_id'] = group_id
    p['user_id'] = user_id
    p['no_cache'] = no_cache
    return api_invoke('get_group_member_info', p)


class CQPlusApi(object):
    def __init__(self, context):
        assert isinstance(context, CQPlusContext)
        self._context = context

    @property
    def _env(self):
        return self._context.env

    def send_private_msg(self, user_id, msg):
        return send_private_msg(self._env, user_id, msg)

    def send_group_msg(self, group_id, msg):
        return send_group_msg(self._env, group_id, msg)

    def send_discuss_msg(self, discuss_id, msg):
        return send_discuss_msg(self._env, discuss_id, msg)

    def delete_msg(self, msg_id):
        return delete_msg(self._env, msg_id)

    def send_like(self, user_id, times):
        return send_like(self._env, user_id, times)

    def set_group_kick(self, group_id, user_id, reject_add_request=False):
        return set_group_kick(self._env, group_id, user_id, reject_add_request)

    def set_group_ban(self, group_id, user_id, duration):
        return set_group_ban(self._env, group_id, user_id, duration)

    def set_group_anonymous_ban(self, group_id, flag, duration):
        return set_group_anonymous_ban(self._env, group_id, flag, duration)

    def set_group_whole_ban(self, group_id, enable):
        return set_group_whole_ban(self._env, group_id, enable)

    def set_group_admin(self, group_id, user_id, enable):
        return set_group_admin(self._env, group_id, user_id, enable)

    def set_group_anonymous(self, group_id, enable):
        return set_group_anonymous(self._env, group_id, enable)

    def set_group_card(self, group_id, user_id, card):
        return set_group_card(self._env, group_id, user_id, card)

    def set_group_leave(self, group_id, is_dismiss):
        return set_group_leave(self._env, group_id, is_dismiss)

    def set_group_special_title(self, group_id, user_id, special_title, duration):
        return set_group_special_title(self._env, group_id, user_id, special_title, duration)

    def set_discuss_leave(self, discuss_id):
        return set_discuss_leave(self._env, discuss_id)

    def set_friend_add_request(self, flag, operation, remark):
        return set_friend_add_request(self._env, flag, operation, remark)

    def set_group_add_request(self, flag, type, operation, reason):
        return set_group_add_request(self._env, flag, type, operation, reason)

    def get_login_user_id(self):
        return get_login_user_id(self._env)

    def get_login_nickname(self):
        return get_login_nickname(self._env)

    def get_cookies(self):
        return get_cookies(self._env)

    def get_csrf_token(self):
        return get_csrf_token(self._env)

    def get_app_directory(self):
        return get_app_directory(self._env)

    def get_record(self, file, out_format):
        return get_record(self._env, file, out_format)

    def get_stranger_info(self, user_id, no_cache=False):
        return get_stranger_info(self._env, user_id, no_cache)

    def get_group_list(self):
        return get_group_list(self._env)

    def get_group_member_list(self, group_id):
        return get_group_member_list(self._env, group_id)

    def get_group_member_info(self, group_id, user_id, no_cache):
        return get_group_member_info(self._env, group_id, user_id, no_cache)

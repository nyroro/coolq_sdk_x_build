# -*- coding:utf-8 -*-

import cqplus._api
from cqplus._context import CQPlusContext


DEFAULT_LOG_TAG = "CQPLUS.PY"


class Level:
    DEBUG = 0
    INFO = 10
    INFOSUCCESS = 11
    INFORECV = 12
    INFOSEND = 13
    WARNING = 20
    ERROR = 30
    FATAL = 40


def log(env, msg, tag, level):
    params = dict()
    params['env'] = env
    params['msg'] = msg
    params['tag'] = tag
    params['level'] = level
    cqplus._api.api_invoke('log', params)


def debug(env, msg, tag=DEFAULT_LOG_TAG):
    log(env, msg, tag, Level.DEBUG)


def info(env, msg, tag=DEFAULT_LOG_TAG):
    log(env, msg, tag, Level.INFO)


def info_success(env, msg, tag=DEFAULT_LOG_TAG):
    log(env, msg, tag, Level.INFOSUCCESS)


def info_recv(env, msg, tag=DEFAULT_LOG_TAG):
    log(env, msg, tag, Level.INFORECV)


def info_send(env, msg, tag=DEFAULT_LOG_TAG):
    log(env, msg, tag, Level.INFOSEND)


def warning(env, msg, tag=DEFAULT_LOG_TAG):
    log(env, msg, tag, Level.WARNING)


def error(env, msg, tag=DEFAULT_LOG_TAG):
    log(env, msg, tag, Level.ERROR)


def fatal(env, msg, tag=DEFAULT_LOG_TAG):
    log(env, msg, tag, Level.FATAL)


class CQPlusLogging(object):
    def __init__(self, context):
        assert isinstance(context, CQPlusContext)
        self._context = context

    @property
    def _env(self):
        return self._context.env

    def debug(self, msg, tag=DEFAULT_LOG_TAG):
        debug(self._env, msg, tag)

    def info(self, msg, tag=DEFAULT_LOG_TAG):
        info(self._env, msg, tag)

    def info_success(self, msg, tag=DEFAULT_LOG_TAG):
        info_success(self._env, msg, tag)

    def info_recv(self, msg, tag=DEFAULT_LOG_TAG):
        info_recv(self._env, msg, tag)

    def info_send(self, msg, tag=DEFAULT_LOG_TAG):
        info_send(self._env, msg, tag)

    def warning(self, msg, tag=DEFAULT_LOG_TAG):
        warning(self._env, msg, tag)

    def error(self, msg, tag=DEFAULT_LOG_TAG):
        error(self._env, msg, tag)

    def fatal(self, msg, tag=DEFAULT_LOG_TAG):
        fatal(self._env, msg, tag)

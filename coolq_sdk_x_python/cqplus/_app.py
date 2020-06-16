# -*- coding:utf-8 -*-

import os
import sys
import cqplus.six as six
from cqplus._context import CQPlusContext
from cqplus._logging import CQPlusLogging
from cqplus._api import CQPlusApi


class CQPlusHandler(object):
    def __init__(self):
        self._context = CQPlusContext()
        self._logging = CQPlusLogging(self._context)
        self._api = CQPlusApi(self._context)

    def __set_env__(self, env):
        assert isinstance(env, dict)
        self._context.env = env.copy()

    @property
    def logging(self):
        return self._logging  # type: CQPlusLogging

    @property
    def api(self):
        return self._api  # type: CQPlusApi


class CQPlusApp(object):
    def __init__(self, env, *a, **kw):
        self.env = env
        self.handler = None
        self.handler_module = None

    def handle_event(self, event, params):
        self.before_event(event, params)

        ret = self.on_event(event, params)

        self.after_event(event, params)

        return ret

    def load_handler(self, script_home):
        sys_path_bak = list(sys.path)
        sys.path.insert(0, script_home)

        if self.handler_module:
            six.moves.reload_module(self.handler_module)
        else:
            self.handler_module = __import__('CQPlusHandler')

        handler_class = getattr(self.handler_module, 'MainHandler')
        assert issubclass(handler_class, CQPlusHandler)
        handler_inst = handler_class()
        assert isinstance(handler_inst, CQPlusHandler)
        handler_inst.__set_env__(self.env)
        self.handler = handler_inst

        sys.path = sys_path_bak

    def free_handler(self):
        self.handler = None

    def before_event(self, event, params):
        env = params['env']  # type: dict
        script_home = os.path.join(env['CQ_HOME'], 'app', env['CQ_APP_ID'])

        settings = params['settings']
        if settings.get('DEBUG', True) or event == 'on_enable':
            self.load_handler(script_home)

    def after_event(self, event, params):
        if event == 'on_disable':
            self.free_handler()

    def on_event(self, event, params):
        ret = None

        if self.handler:
            func = getattr(self.handler, 'handle_event', None)
            if callable(func):
                ret = func(event, params.copy())
            else:
                func = getattr(self.handler, event, None)

                if callable(func):
                    ret = func(params.copy())

        return ret

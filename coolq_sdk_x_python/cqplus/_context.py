# -*- coding:utf-8 -*-


class CQPlusContext(object):
    def __init__(self, env=None):
        assert isinstance(env, dict) or env is None
        self._env = env

    @property
    def env(self):
        return self._env  # type: dict

    @env.setter
    def env(self, e):
        assert isinstance(e, dict)
        self._env = e

    @property
    def cq_home(self):
        return self.env.get('CQ_HOME')  # type: str

    @property
    def app_id(self):
        return self.env.get('CQ_APP_ID')  # type: str

    @property
    def auth_code(self):
        return self.env.get('CQ_AUTH_CODE')  # type: str
